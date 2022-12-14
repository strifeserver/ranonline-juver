#include "stdafx.h"
#include "./DbActionLogic.h"
#include "./G-Logic/GLGaeaServer.h"
#include "./G-Logic/GLChar.h"

#include "../Lib_Network/s_CSessionServer.h"
#include "../Lib_Network/s_CFieldServer.h"
#include "../Lib_Network/s_CAgentServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDbActSaveChar::CDbActSaveChar () 
	: m_dwClient(UINT_MAX)
	, m_dwGaea(GAEAID_NULL)
{
}

CDbActSaveChar::~CDbActSaveChar()
{
}

bool CDbActSaveChar::SetInfo ( DWORD dwClient, DWORD dwGaea, SCHARDATA2 *pCHARDATA )
{
	if ( !pCHARDATA )	return false;

	m_dwClient = dwClient;
	m_dwGaea = dwGaea;
	m_sCHARDATA.Assign ( *pCHARDATA );

	return true;
}

int CDbActSaveChar::Execute ( CServer* pServer )
{
	if ( pServer==NULL )			return NET_ERROR;
	if ( m_dwClient==UINT_MAX )		return NET_ERROR;

	m_pDbManager->SaveCharacter(&m_sCHARDATA);

	GLGaeaServer::GetInstance().ResetSaveDBUserID ( m_sCHARDATA.GetUserID() );

	return NET_OK;
}

CDbActToAgentMsg::CDbActToAgentMsg () 
	: m_dwClientID(UINT_MAX)
{
	memset(m_aryMsg, 0, NET_DATA_BUFSIZE);
	NET_MSG_GENERIC *nmg = (NET_MSG_GENERIC *) m_aryMsg;
	
	nmg->dwSize = sizeof(NET_MSG_GENERIC);
	nmg->nType = NET_MSG_BASE_ZERO;
}

CDbActToAgentMsg::~CDbActToAgentMsg()
{
}
	
bool CDbActToAgentMsg::SetMsg ( DWORD dwClient, NET_MSG_GENERIC *nmg )
{
	if (nmg == NULL)
	{
		return false;
	}
	else
	{
		if (nmg->dwSize < NET_DATA_BUFSIZE) 
		{
			m_dwClientID = dwClient;
			memcpy ( m_aryMsg, nmg, sizeof(BYTE) * nmg->dwSize );
			return true;
		}
		else
		{
			return false;
		}
	}
}

int CDbActToAgentMsg::Execute ( CServer* pServer )
{
	if (pServer == NULL)
	{
		return NET_ERROR;
	}
	else
	{
		CFieldServer* pTemp = reinterpret_cast<CFieldServer*> (pServer);
		pTemp->SendAgent ( m_dwClientID, m_aryMsg );
		return NET_OK;
	}
}

CDelChaFriend::CDelChaFriend(int nChaP, int nChaS)
{
    m_nChaP = nChaP;
	m_nChaS = nChaS;
}

int CDelChaFriend::Execute(CServer* pServer)
{
    m_pDbManager->DelChaFriend(m_nChaP, m_nChaS);
	return NET_OK;
}

CAddChaFriend::CAddChaFriend(int nChaP, int nChaS)
{
	m_nChaP = nChaP;
	m_nChaS = nChaS;
}

int CAddChaFriend::Execute(CServer* pServer)
{
	m_pDbManager->AddChaFriend(m_nChaP, m_nChaS);
	return NET_OK;
}

CSetChaFriend::CSetChaFriend(int nChaP, int nChaS, int nFlag)
{
    m_nChaP = nChaP;
	m_nChaS = nChaS;
	m_nFlag = nFlag;
}

int CSetChaFriend::Execute(CServer* pServer)
{
    m_pDbManager->SetChaFriend(m_nChaP, m_nChaS, m_nFlag);
	return NET_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ?????????????? ??????
// ?????????? ?????????? ?????? ?????? 1 ??????????.
CItemChaCreateNumIncrease::CItemChaCreateNumIncrease(int nUserNum)
{
    m_nUserNum = nUserNum;
}

int CItemChaCreateNumIncrease::Execute(CServer* pServer)
{    
	return m_pDbManager->UserChaNumIncrease(m_nUserNum);
}

///////////////////////////////////////////////////////////////////////////////
// ???? ???? ?????????? ??????.
// 1 ?? 5 ?? ?????? ???? ?? ????.
// 2, 3, 4 ?? ?????? ?????????? ???? ?? ????.
// ????
// nChaNum : ??????????
// nStorageNum : ???????? ????
// tTime : ????????
// ????
// -1 : DB_ERROR
//  0 : DB_OK
CSetChaStorageDate::CSetChaStorageDate(int nUserNum, int nStorageNum, __time64_t tTime)
{
    m_nUserNum    = nUserNum;
    m_nStorageNum = nStorageNum;
    m_tTime       = tTime;
}

int CSetChaStorageDate::Execute(CServer* pServer)
{
    return m_pDbManager->SetChaStorageDate(m_nUserNum, m_nStorageNum, m_tTime);
}

///////////////////////////////////////////////////////////////////////////////
// ???? ???????? ???????? ???? ?????? ????????.
// ????
// nChaNum : ??????????
// wInvenLine : ???????? 
// ???? 
// ???? 0 ???? ???? ?????? 1 ?? ????
// ???? ???? ???????? ?? ???? ?????? 2 ?? ???? (???? ?????? ????????)
// ???? ???? ???????? ???? ?????? 3 ?? ????
// ???? 3?????? ????????.
CSetChaInvenNum::CSetChaInvenNum(int nChaNum, WORD wInvenLine)
{
    m_nChaNum    = nChaNum;
    m_wInvenLine = wInvenLine;
}

int CSetChaInvenNum::Execute(CServer* pServer)
{
    return m_pDbManager->SetChaInvenNum(m_nChaNum, m_wInvenLine);
}

///////////////////////////////////////////////////////////////////////////////
// ???? ???????? ???????? ?????? ????????.
CSetPremiumTime::CSetPremiumTime(int nUserNum, __time64_t tPremiumTime)
{
    m_nUserNum     = nUserNum;
    m_tPremiumTime = tPremiumTime;
}

int CSetPremiumTime::Execute(CServer* pServer)
{
    return m_pDbManager->SetPremiumTime(m_nUserNum, m_tPremiumTime);
}

///////////////////////////////////////////////////////////////////////////
// ???????????? ?????????????? ????????.
// nUserNum : ??????????
CGetChatBlockTime::CGetChatBlockTime(int nUserNum)
{
	m_nUserNum = nUserNum;
}

int CGetChatBlockTime::Execute(CServer* pServer)
{
	// ???????? ???? ?????????? ????????.
	m_pDbManager->GetChatBlockTime(m_nUserNum);
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////
// ???????????? ?????????????? ????????.
// nUserNum : ??????????
// tBlockTime : ???? ???? ????????
CSetChatBlockTime::CSetChatBlockTime(int nUserNum, __time64_t tBlockTime)
{
	m_nUserNum = nUserNum;
	m_tBlockTime = tBlockTime;
}

int CSetChatBlockTime::Execute(CServer* pServer)
{
	return m_pDbManager->SetChatBlockTime(m_nUserNum, m_tBlockTime);
}

///////////////////////////////////////////////////////////////////////////////
// ???????? ???? ?????? ???? ???????? ????????.
CSetLastCallPos::CSetLastCallPos(int nChaNum, DWORD dwMapID, D3DXVECTOR3 vPos)
{
    m_nChaNum = nChaNum;
    m_dwMapID = dwMapID;
    m_vPos    = vPos;
}

int CSetLastCallPos::Execute(CServer* pServer)
{
    return m_pDbManager->SetLastCallPos(m_nChaNum, m_dwMapID, m_vPos);
}

///////////////////////////////////////////////////////////////////////////
// ???? ???????? ???????? ????????.
// ????
// nChaNum : ??????????
// llExp : ??????
// ???? 
// ???????????? 0 ???? ????????.
// ???????? 0 ???? ????????.
CSetChaExp::CSetChaExp(int nChaNum, LONGLONG llExp) :
    m_nChaNum(0),
    m_llExp(0)
{
    m_nChaNum = nChaNum;
    m_llExp = llExp;
}

int CSetChaExp::Execute(CServer* pServer)
{
    return m_pDbManager->SetChaExp(m_nChaNum, m_llExp);
}

///////////////////////////////////////////////////////////////////////////
// ???? ???????? ???????? ????????.
// ????
// nChaNum : ??????????
// ????
// LONGLONG : ??????
// ???? 
// ???????????? 0 ???? ????????.
// ???????? 0 ???? ?????? ????????.
CGetChaExp::CGetChaExp(int nChaNum) :
    m_nChaNum(0)
{
    m_nChaNum = nChaNum;
}

int CGetChaExp::Execute(CServer* pServer)
{
    LONGLONG llChaExp;
    llChaExp = m_pDbManager->GetChaExp(m_nChaNum);
    if (llChaExp < 0)
    {
        // ????
        return DB_ERROR;
    }
    else
    {
        // ?????? ???????? ??????...

        return DB_OK;
    }
}

///////////////////////////////////////////////////////////////////////////
// ?????? ???????? ?????? ???? ?????? ??????.
// dwRegionID : ???? ID
// dwClub : ???? ID
// fTax : ????
CSetClubRegion::CSetClubRegion(DWORD dwRegionID, DWORD dwClub, float fTax)
{
	m_dwRegionID = dwRegionID;
	m_dwClub = dwClub;
	m_fTax = fTax;
}

int CSetClubRegion::Execute(CServer* pServer)
{
	return m_pDbManager->SetClubRegion(m_dwRegionID, m_dwClub, m_fTax);
}


///////////////////////////////////////////////////////////////////////////
// ???? ?????? ???? ?????? ????????.
// ???? : ???????? ID ?? ???? ID ?? DB ?????? ?????? ???????? ?????? ????????.
// dwRegionID : ???? ID
// dwClub : ???? ID
CDelClubRegion::CDelClubRegion(DWORD dwRegionID, DWORD dwClub)
{
	m_dwRegionID = dwRegionID;
	m_dwClub     = dwClub;
}

int CDelClubRegion::Execute(CServer* pServer)
{
	return m_pDbManager->DelClubRegion(m_dwRegionID, m_dwClub);
}

/**
* ?????? ?????? ????????.
* m_dwChaNum ??????????
* m_szCharName ?????? ??????????
*/
CRenameCharacter::CRenameCharacter(
	DWORD dwClientID, 
	DWORD dwChaNum, 
	const char* szCharName,
	WORD wPosX,
	WORD wPosY )
{	
	memset(m_szCharName, 0, sizeof(char) * CHR_ID_LENGTH);
	m_dwClient = dwClientID;
	m_dwChaNum = dwChaNum;	
	m_wPosX = wPosX;
	m_wPosY = wPosY;
	if (szCharName != NULL)
	{
		StringCchCopy(m_szCharName, CHR_ID_LENGTH, szCharName);
	}
}

int CRenameCharacter::Execute (CServer* pServer)
{
	if (pServer == NULL)
	{
		return DB_ERROR;
	}
	else
	{
		int nRESULT = m_pDbManager->RenameCharacter(m_dwChaNum, m_szCharName);

		GLMSG::SNETPC_INVEN_RENAME_FROM_DB NetMsgDB2Fld;

		if ( nRESULT == DB_OK ) // ???????? ????
		{
			NetMsgDB2Fld.emFB = EMINVEN_RENAME_FROM_DB_OK;
			NetMsgDB2Fld.wPosX = m_wPosX;
			NetMsgDB2Fld.wPosY = m_wPosY;
			//NetMsg.dwCharID = m_dwChaNum;
			StringCchCopy ( NetMsgDB2Fld.szName, CHAR_SZNAME, m_szCharName );
		}
		else if( nRESULT == -2 )
		{
			NetMsgDB2Fld.emFB = EMINVEN_RENAME_FROM_DB_BAD;
			StringCchCopy ( NetMsgDB2Fld.szName, CHAR_SZNAME, m_szCharName );
		}
		else // ???????? ????
		{
			NetMsgDB2Fld.emFB = EMINVEN_RENAME_FROM_DB_FAIL;
			StringCchCopy ( NetMsgDB2Fld.szName, CHAR_SZNAME, m_szCharName );
		}

		CFieldServer* pTemp = reinterpret_cast<CFieldServer*> (pServer);
		pTemp->InsertMsg(m_dwClient, (char*) &NetMsgDB2Fld );
		return nRESULT;
	}
}


//! ???????? ???????? ????????.
//! m_dwChaNum : ??????????
//! m_nHairColor : ????????
CSetChaHairColor::CSetChaHairColor(
	DWORD dwChaNum,
	int nHairColor )
{
	m_dwChaNum = dwChaNum;
	m_nHairColor = nHairColor;
}

int CSetChaHairColor::Execute(CServer* pServer)
{
	return m_pDbManager->SetChaHairColor(m_dwChaNum, m_nHairColor);
}

//! ???????? ???????????? ????????.
//! m_dwChaNum : ?????? ????
//! m_nHairStyle : ??????????
CSetChaHairStyle::CSetChaHairStyle(
	DWORD dwChaNum,
	int nHairStyle )
{
	m_dwChaNum = dwChaNum;
	m_nHairStyle = nHairStyle;
}
	
int CSetChaHairStyle::Execute(CServer* pServer)
{
	return m_pDbManager->SetChaHairStyle(m_dwChaNum, m_nHairStyle);
}

//! ???????? ???????????? ????????.
//! m_dwChaNum : ?????? ????
//! m_nFaceStyle : ??????????
CSetChaFaceStyle::CSetChaFaceStyle(
	DWORD dwChaNum,
	int nFaceStyle )
{
	m_dwChaNum = dwChaNum;
	m_nFaceStyle = nFaceStyle;
}
	
int CSetChaFaceStyle::Execute(CServer* pServer)
{
	return m_pDbManager->SetChaFaceStyle(m_dwChaNum, m_nFaceStyle);
}


// ?????? ?????? ????????.
CSetChaGenderChange::CSetChaGenderChange(
	 DWORD dwChaNum, 
	 int nClass,
	 int nSex,
	 int nFace, 
	 int nHair, 
	 int nHairColor  ) 
	 : m_dwChaNum ( dwChaNum )
	 , m_nClass ( nClass )
	 , m_nSex ( nSex )
	 , m_nFace ( nFace )
	 , m_nHair ( nHair )
	 , m_nHairColor ( nHairColor )
{
}
	
int CSetChaGenderChange::Execute(CServer* pServer)
{
	return m_pDbManager->SetChaGenderChange(m_dwChaNum, m_nClass,m_nSex, m_nFace,m_nHair,m_nHairColor );
}

//! ???????? ?????????? ????????.
//! \param dwChaNum ?????? ????
//! \param dwStartmapID ???????? ?? ????
//! \param dwStartGate ???????? ?????? ????
//! \param fStartPosX ???????? X ????
//! \param fStartPosY ???????? Y ????
//! \param fStartPosZ ???????? Z ????
//! \param dwSaveMapID ?????????? ???????? ?? ????
//! \param fSavePosX ?????????? ???????? X ????
//! \param fSavePosY ?????????? ???????? Y ????
//! \param fSavePosZ ?????????? ???????? Z ????
//! \param dwLastCallMapID ???? ?????????? ?????? ?? ????
//! \param fLastCallPosX ???? ?????????? ?????? X ????
//! \param fLastCallPosY ???? ?????????? ?????? Y ????
//! \param fLastCallPosZ ???? ?????????? ?????? Z ????
//! \return DB_OK, DB_ERROR
CSaveChaPos::CSaveChaPos(
	DWORD dwClientID,
	DWORD dwChaNum,
	DWORD dwFieldServer,
	DWORD dwStartMapID,
	DWORD dwStartGate,
	FLOAT fStartPosX,
	FLOAT fStartPosY,
	FLOAT fStartPosZ,
	DWORD dwSaveMapID,
	FLOAT fSavePosX,
	FLOAT fSavePosY,
	FLOAT fSavePosZ,
	DWORD dwLastCallMapID,
	FLOAT fLastCallPosX,
	FLOAT fLastCallPosY,
	FLOAT fLastCallPosZ )
 	: m_dwChaNum(dwChaNum)
	, m_dwFieldServer(dwFieldServer)
	, m_dwStartMapID(dwStartMapID)
	, m_dwStartGate(dwStartGate)
	, m_fStartPosX(fStartPosX)
	, m_fStartPosY(fStartPosY)
	, m_fStartPosZ(fStartPosZ)
	, m_dwSaveMapID(dwSaveMapID)
	, m_fSavePosX(fSavePosX)
	, m_fSavePosY(fSavePosY)
	, m_fSavePosZ(fSavePosZ)
	, m_dwLastCallMapID(dwLastCallMapID)
	, m_fLastCallPosX(fLastCallPosX)
	, m_fLastCallPosY(fLastCallPosY)
	, m_fLastCallPosZ(fLastCallPosZ)
{
	m_dwClient = dwClientID;
}

int CSaveChaPos::Execute(CServer* pServer)
{

	int nResult = m_pDbManager->SaveChaPos(m_dwChaNum,
								m_dwStartMapID,
								m_dwStartGate,
								m_fStartPosX,
								m_fStartPosY,
								m_fStartPosZ,
								m_dwSaveMapID,
								m_fSavePosX,
								m_fSavePosY,
								m_fSavePosZ,
								m_dwLastCallMapID,
								m_fLastCallPosX,
								m_fLastCallPosY,
								m_fLastCallPosZ);

	GLMSG::SNETPC_SAVECHARPOSRST_FROMDB NetMsgDb2Agt;

	if ( nResult == DB_OK )
	{
		NetMsgDb2Agt.emFB		   = EMSAVECHARPOS_FB_OK;
		NetMsgDb2Agt.dwCharID	   = m_dwChaNum;
		NetMsgDb2Agt.dwFieldServer = m_dwFieldServer;
	}

	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);
	pTemp->InsertMsg ( m_dwClient, (char*) &NetMsgDb2Agt );

	return nResult;
}

CInsertUserAttend::CInsertUserAttend( 
    DWORD dwUserID
  , int nComboAttend
  , int nAttendReward )
{
	m_dwUserID = dwUserID;
	m_nComboAttend = nComboAttend;
	m_nAttendReward = nAttendReward;
}

int CInsertUserAttend::Execute( CServer* pServer )
{
	return m_pDbManager->InsertUserAttend ( m_dwUserID, m_nComboAttend, m_nAttendReward );
}

CInsertAttendItem::CInsertAttendItem( 
	const CString& strPurKey, 
	const CString& strUserID, 
	int nItemMID, 
	int nItemSID )
{
	m_strPurKey = strPurKey;
	m_strUserID = strUserID;
	m_nItemMID = nItemMID;
	m_nItemSID = nItemSID;
}

int CInsertAttendItem::Execute( CServer* pServer )
{
	return m_pDbManager->InsertAttendItem ( m_strPurKey, m_strUserID, m_nItemMID, m_nItemSID );
}

CThaiCafeClassCheck::CThaiCafeClassCheck( const DWORD dwClientID, const DWORD dwCClassType, const TCHAR *pszIP )
{
	m_dwClient	   = dwClientID;
	m_dwCClassType = dwCClassType;
	StringCchCopy(m_szIp, MAX_IP_LENGTH+1, pszIP);
}

int CThaiCafeClassCheck::Execute( CServer* pserver )
{
	int nResult = m_pDbManager->ThaiUserClassCheck( m_szIp );
	if( nResult != m_dwCClassType )
	{
		GLMSG::SNET_CYBERCAFECLASS_UPDATE NetMsg;
		NetMsg.dwCyberCafeClass = nResult;

		CAgentServer* pTemp1 = reinterpret_cast<CAgentServer*> (pserver);
		pTemp1->InsertMsg ( m_dwClient, (char*) &NetMsg );
	}
	return nResult;
}

CMyCafeClassCheck::CMyCafeClassCheck( const DWORD dwClientID, const DWORD dwCClassType, const TCHAR *pszIP )
{
	m_dwClient	   = dwClientID;
	m_dwCClassType = dwCClassType;
	StringCchCopy(m_szIp, MAX_IP_LENGTH+1, pszIP);
}

int CMyCafeClassCheck::Execute( CServer* pserver )
{
	int nResult = m_pDbManager->MyUserClassCheck( m_szIp );
	if( nResult != m_dwCClassType )
	{
		GLMSG::SNET_CYBERCAFECLASS_UPDATE NetMsg;
		NetMsg.dwCyberCafeClass = nResult;

		CAgentServer* pTemp1 = reinterpret_cast<CAgentServer*> (pserver);
		pTemp1->InsertMsg ( m_dwClient, (char*) &NetMsg );
	}
	return nResult;
}

CUpdateUserMoneyAdd::CUpdateUserMoneyAdd( const DWORD dwUserID, const LONGLONG lnUserMoney )
{
	m_dwUserID = dwUserID;
	m_lnUserMoney = lnUserMoney;
}

int CUpdateUserMoneyAdd::Execute( CServer* pserver )
{
	return m_pDbManager->UpdateUserMoneyAdd ( m_dwUserID, m_lnUserMoney );
}

CUpdateUserLastInfoAdd::CUpdateUserLastInfoAdd( const DWORD dwUserID, const LONGLONG lnUserMoney )
{
	m_dwUserID = dwUserID;
	m_lnUserMoney = lnUserMoney;
}

int CUpdateUserLastInfoAdd::Execute( CServer* pserver )
{
	return m_pDbManager->UpdateUserLastInfoAdd ( m_dwUserID, m_lnUserMoney );
}