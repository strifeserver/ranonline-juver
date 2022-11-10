#include "stdafx.h"
#include "./GLChar.h"
#include "./GLGaeaServer.h"
#include "./GLItemMan.h"
#include "./GLSkill.h"
#include "./GLItemMixMan.h"

#include "RANPARAM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgReqGetRightOfItem_A ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A* pNetMsg = ( GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A* ) nmg;

	// �̷� ��� ����� �ȵǴµ�...
	if ( pNetMsg->dwGUID != m_dwPetGUID ) return E_FAIL;

	switch ( pNetMsg->emSkill )
	{
	case EMPETSKILL_GETALL:		MsgGetFieldAllItem_A ( nmg ); 	break;
	case EMPETSKILL_GETRARE:	MsgGetFieldRareItem_A ( nmg );	break;
	case EMPETSKILL_GETPOTIONS: MsgGetFieldPotions_A ( nmg );	break;
	case EMPETSKILL_GETMONEY:	MsgGetFieldMoney_A ( nmg );		break;
	case EMPETSKILL_GETSTONE:	MsgGetFieldStone_A ( nmg );		break;
	};

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgReqGetRightOfItem_B ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B* pNetMsg = ( GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B* ) nmg;

	// �̷� ��� ����� �ȵǴµ�...
	if ( pNetMsg->dwGUID != m_dwPetGUID ) return E_FAIL;

	switch ( pNetMsg->emSkill )
	{
	case EMPETSKILL_GETALL:		MsgGetFieldAllItem_B ( nmg ); 	break;
	case EMPETSKILL_GETRARE:	MsgGetFieldRareItem_B ( nmg );	break;
	case EMPETSKILL_GETPOTIONS: MsgGetFieldPotions_B ( nmg );	break;
	case EMPETSKILL_GETMONEY:	MsgGetFieldMoney_B ( nmg );		break;
	case EMPETSKILL_GETSTONE:	MsgGetFieldStone_B ( nmg );		break;
	};

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgGetFieldAllItem_A ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
		//	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop )
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldAllItem()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;

/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ���� �����Ѵ�
					// m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	�ι��� �������� �������� ������ ������ �˸� 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// ?�������̸�
				if ( pItem->sBasicOp.emItemType==ITEM_QITEM ) continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 
/*
				// ��Ƽ���̰� �̺�Ʈ �������� �ƴҶ� ��Ƽ �������� �˻��� ó��.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					i = 0;
				}
	
			}
		}

		//	Note : - Money - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		MONEYDROPNODE *pMoneyNode = pQuadNode->pData->m_MoneyList.m_pHead;
		for ( ; pMoneyNode; pMoneyNode = pMoneyNode->pNext )
		{
			PMONEYDROP pMoneyDrop = pMoneyNode->Data;
			if ( !pMoneyDrop ) 
			{
				DEBUGMSG_WRITE ( "Money is Lost in MsgGetFieldAllItem()" );
				continue;
			}
			nX = int(pMoneyDrop->vPos.x); nZ = int(pMoneyDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pMoneyDrop->dwGlobID;
				if ( dwID>=MAXMONEY ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pMoneyDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 
/*
				// ��Ƽ ���ð˻�
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty )
				{
					bool ballot = pParty->DOMONEY_ALLOT ( this, pMoneyDrop, m_pLandMan, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pMoneyDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_MONEY;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					i = 0;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgGetFieldAllItem_B ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
		//	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop )
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldAllItem()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;

/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ���� �����Ѵ�
					// m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	�ι��� �������� �������� ������ ������ �˸� 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// ?�������̸�
				if ( pItem->sBasicOp.emItemType==ITEM_QITEM ) continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 
/*
				// ��Ƽ���̰� �̺�Ʈ �������� �ƴҶ� ��Ƽ �������� �˻��� ó��.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					i = 0;
				}
	
			}
		}

		//	Note : - Money - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		MONEYDROPNODE *pMoneyNode = pQuadNode->pData->m_MoneyList.m_pHead;
		for ( ; pMoneyNode; pMoneyNode = pMoneyNode->pNext )
		{
			PMONEYDROP pMoneyDrop = pMoneyNode->Data;
			if ( !pMoneyDrop ) 
			{
				DEBUGMSG_WRITE ( "Money is Lost in MsgGetFieldAllItem()" );
				continue;
			}
			nX = int(pMoneyDrop->vPos.x); nZ = int(pMoneyDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pMoneyDrop->dwGlobID;
				if ( dwID>=MAXMONEY ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pMoneyDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 
/*
				// ��Ƽ ���ð˻�
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty )
				{
					bool ballot = pParty->DOMONEY_ALLOT ( this, pMoneyDrop, m_pLandMan, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pMoneyDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_MONEY;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					i = 0;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgGetFieldRareItem_A ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop ) 
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldRareItem()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;
/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ���� �����Ѵ�
					//m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	�ι��� �������� �������� ������ ������ �˸� 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// ����������� �ƴϸ�
				if ( pItem->sBasicOp.emLevel != LEVEL_RARE ) continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 
/*
				// ��Ƽ���̰� �̺�Ʈ �������� �ƴҶ� ��Ƽ �������� �˻��� ó��.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgGetFieldRareItem_B ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop ) 
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldRareItem()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;
/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ���� �����Ѵ�
					//m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	�ι��� �������� �������� ������ ������ �˸� 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// ����������� �ƴϸ�
				if ( pItem->sBasicOp.emLevel != LEVEL_RARE ) continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 
/*
				// ��Ƽ���̰� �̺�Ʈ �������� �ƴҶ� ��Ƽ �������� �˻��� ó��.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgGetFieldPotions_A ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop )
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldPotions()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;
/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ���� �����Ѵ�
					//m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	�ι��� �������� �������� ������ ������ �˸� 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// ������ �ƴϸ�
				if ( pItem->sBasicOp.emItemType != ITEM_CURE ) continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 

/*
				// ��Ƽ���̰� �̺�Ʈ �������� �ƴҶ� ��Ƽ �������� �˻��� ó��.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgGetFieldPotions_B ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop )
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldPotions()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;
/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ���� �����Ѵ�
					//m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	�ι��� �������� �������� ������ ������ �˸� 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// ������ �ƴϸ�
				if ( pItem->sBasicOp.emItemType != ITEM_CURE ) continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 

/*
				// ��Ƽ���̰� �̺�Ʈ �������� �ƴҶ� ��Ƽ �������� �˻��� ó��.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgGetFieldMoney_A ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Money - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		MONEYDROPNODE *pMoneyNode = pQuadNode->pData->m_MoneyList.m_pHead;
		for ( ; pMoneyNode; pMoneyNode = pMoneyNode->pNext )
		{
			PMONEYDROP pMoneyDrop = pMoneyNode->Data;
			if ( !pMoneyDrop ) 
			{
				DEBUGMSG_WRITE ( "Money is Lost in MsgGetFieldMoney()" );
				continue;
			}
			nX = int(pMoneyDrop->vPos.x); nZ = int(pMoneyDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pMoneyDrop->dwGlobID;
				if ( dwID>=MAXMONEY ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pMoneyDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 
/*
				// ��Ƽ ���ð˻�
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty )
				{
					bool ballot = pParty->DOMONEY_ALLOT ( this, pMoneyDrop, m_pLandMan, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pMoneyDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_MONEY;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgGetFieldMoney_B ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Money - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		MONEYDROPNODE *pMoneyNode = pQuadNode->pData->m_MoneyList.m_pHead;
		for ( ; pMoneyNode; pMoneyNode = pMoneyNode->pNext )
		{
			PMONEYDROP pMoneyDrop = pMoneyNode->Data;
			if ( !pMoneyDrop ) 
			{
				DEBUGMSG_WRITE ( "Money is Lost in MsgGetFieldMoney()" );
				continue;
			}
			nX = int(pMoneyDrop->vPos.x); nZ = int(pMoneyDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pMoneyDrop->dwGlobID;
				if ( dwID>=MAXMONEY ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pMoneyDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 
/*
				// ��Ƽ ���ð˻�
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty )
				{
					bool ballot = pParty->DOMONEY_ALLOT ( this, pMoneyDrop, m_pLandMan, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pMoneyDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_MONEY;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgGetFieldStone_A ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop ) 
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldSton()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;
/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ���� �����Ѵ�
					//m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	�ι��� �������� �������� ������ ������ �˸� 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// �������� �ƴϸ�
				if ( pItem->sBasicOp.emItemType != ITEM_GRINDING 
					&& pItem->sBasicOp.emItemType != ITEM_MATERIALS )
					continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 
/*
				// ��Ƽ���̰� �̺�Ʈ �������� �ƴҶ� ��Ƽ �������� �˻��� ó��.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

/*dual pet skill, Juver, 2017/12/28 */
HRESULT GLChar::MsgGetFieldStone_B ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ���� �߰��Ǵ� ���� ���� ��带 ǥ��.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop ) 
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldSton()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	�������� �ٸ� ������� ����Ǿ� ������
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;
/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ���� �����Ѵ�
					//m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	�ι��� �������� �������� ������ ������ �˸� 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// �������� �ƴϸ�
				if ( pItem->sBasicOp.emItemType != ITEM_GRINDING 
					&& pItem->sBasicOp.emItemType != ITEM_MATERIALS )
					continue;

				// ��������� ��Ƽ���� ����������� �ʴ� ���׷� ����
				// ��Ÿ�� ���� �˻�� ���⼭ ���� �ʰ� ���� ������ �ݴ�
				// �������� ó���ϵ��� ����. 
/*
				// ��Ƽ���̰� �̺�Ʈ �������� �ƴҶ� ��Ƽ �������� �˻��� ó��.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}