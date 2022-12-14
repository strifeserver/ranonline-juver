#include "StdAfx.h"
#include "./DxCharSham.h"
#include "./G-Logic/GLogicData.h"
#include "./G-Logic/GLItemMan.h"

#include "../Lib_Engine/DxCommon/DxMethods.h"
#include "../Lib_Engine/DxCommon/DxShadowMap.h"
#include "../Lib_Engine/DxCommon/EditMeshs.h"
#include "../Lib_Engine/DxEffect/DxEffectMan.h"
#include "../Lib_Engine/DxEffect/Single/DxEffGroupPlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DxCharSham::DxCharSham(void) :
	m_pd3dDevice(NULL),
	m_pSkinChar(NULL),

	m_vDir(D3DXVECTOR3(0,0,-1)),
	m_vDirOrig(D3DXVECTOR3(0,0,-1)),
	m_vPos(D3DXVECTOR3(0,0,0)),

	m_nID(0),
	m_bSelect(FALSE),
	m_bEffect(FALSE),

	m_fAge(),
	m_Action(GLAT_IDLE),
	m_fIdleTime(0.0f),
	m_bPeaceZone(TRUE),
	m_bIdleReserv(FALSE),

	m_vMaxOrg(3,18,3),
	m_vMinOrg(-3,0,-3),

	m_vMax(3,18,3),
	m_vMin(-3,0,-3),

	m_dwRevData(NULL),
	m_bNeedData(FALSE)
{
}

DxCharSham::~DxCharSham(void)
{
	SAFE_DELETE(m_pSkinChar);
}

void DxCharSham::GetAABB ( D3DXVECTOR3 &vMax, D3DXVECTOR3 &vMin )
{
	vMax = m_vMax;
	vMin = m_vMin;
}

HRESULT DxCharSham::SetCharInfo ( const SCHARINFO_LOBBY &CharInfo, const BOOL bThread )
{
	m_dwRevData |= RECEIVE_CHARDATA;

	m_CharInfo = CharInfo;

	//	Note : 케릭터의 외형을 설정.
	StringCchCopy ( GLCHARLOGIC::m_szName, CHAR_SZNAME, m_CharInfo.m_szName );
	GLCHARLOGIC::m_emClass = m_CharInfo.m_emClass;
	GLCHARLOGIC::m_wSchool = m_CharInfo.m_wSchool;
	GLCHARLOGIC::m_wHair = m_CharInfo.m_wHair;
	GLCHARLOGIC::m_wHairColor = m_CharInfo.m_wHairColor;
	GLCHARLOGIC::m_wFace = m_CharInfo.m_wFace;

	GLCHARLOGIC::m_wLevel = m_CharInfo.m_wLevel;
	GLCHARLOGIC::m_sStats = m_CharInfo.m_sStats;

	GLCHARLOGIC::m_fScaleRange = m_CharInfo.m_fScaleRange;

//  LOBY data 수정
//	memcpy ( GLCHARLOGIC::m_PutOnItems, m_CharInfo.m_PutOnItems, sizeof(SITEMCUSTOM)*SLOT_TSIZE );

	for ( int i = 0; i < SLOT_TSIZE; ++i )
	{
		GLCHARLOGIC::m_PutOnItems[i].Assign(  m_CharInfo.m_PutOnItems[i] );
	}


	GLCHARLOGIC::INIT_DATA ( FALSE, FALSE );

	//	Note : 케릭터의 외형을 설정.
	EMCHARINDEX emIndex = CharClassToIndex(m_CharInfo.m_emClass);

	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData( GLCONST_CHAR::szCharSkin[emIndex], m_pd3dDevice, bThread );
	if ( !pSkinChar )	return E_FAIL;

	SAFE_DELETE(m_pSkinChar);
	m_pSkinChar = new DxSkinChar;
	m_pSkinChar->SetCharData ( pSkinChar, m_pd3dDevice );
	if ( m_pd3dDevice )	UpdateSuit ();

	//	Note : 에니메이션 초기화.
	//
	m_pSkinChar->SELECTANI ( AN_PLACID, AN_SUB_NONE );

	return S_OK;
}

HRESULT DxCharSham::Create ( D3DXVECTOR3* pvPos, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, BOOL bNeedData, int nID )
{
	m_pd3dDevice = pd3dDevice;

	m_nID = nID;
	m_bNeedData = bNeedData;

	//	Note : 케릭터의 외형을 설정.
	EMCHARINDEX emIndex = CharClassToIndex(m_CharInfo.m_emClass);
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData( GLCONST_CHAR::szCharSkin[emIndex], pd3dDevice, bThread );
	GASSERT(pSkinChar&&"DxCharSham::Create()->DxSkinCharData::Load()");
	if ( !pSkinChar )	return E_FAIL;

	SAFE_DELETE(m_pSkinChar);
	m_pSkinChar = new DxSkinChar;

	m_pSkinChar->SetCharData( pSkinChar, pd3dDevice );
	UpdateSuit ();

	//	Note : 이동 제어 초기화.
	if ( pvPos )	m_vPos = *pvPos;

	return S_OK;
}

HRESULT DxCharSham::UpdateSuit ()
{
	GASSERT(m_pd3dDevice);

	if ( !m_pSkinChar )										
		return S_FALSE;

	EMCHARINDEX emIndex = CharClassToIndex(m_emClass);
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().FindData ( GLCONST_CHAR::szCharSkin[emIndex] );
	if ( !pSkinChar )	return E_FAIL;

	const GLCONST_CHARCLASS &sCONST = GLCONST_CHAR::cCONSTCLASS[emIndex];

	if ( sCONST.dwHEADNUM > m_wFace )
	{
		std::string strHEAD_CPS = sCONST.strHEAD_CPS[m_wFace];
	
		PDXCHARPART pCharPart = NULL;
		pCharPart = m_pSkinChar->GetPiece(PIECE_HEAD);		//	현제 장착 스킨.

		if ( pCharPart && strcmp(strHEAD_CPS.c_str(),pCharPart->GetFileName()) )
		{
			m_pSkinChar->SetPiece( strHEAD_CPS.c_str(), m_pd3dDevice );
		}
	}

	if ( sCONST.dwHAIRNUM > m_wHair )
	{
		std::string strHAIR_CPS = sCONST.strHAIR_CPS[m_wHair];
	
		PDXCHARPART pCharPart = NULL;
		pCharPart = m_pSkinChar->GetPiece(PIECE_HAIR);		//	현제 장착 스킨.

		if ( pCharPart && strcmp(strHAIR_CPS.c_str(),pCharPart->GetFileName()) )
		{
			m_pSkinChar->SetPiece( strHAIR_CPS.c_str(), m_pd3dDevice );
		}
	}

	// 헤어컬러 세팅
	m_pSkinChar->SetHairColor( m_wHairColor );

	for ( int i=0; i<SLOT_NSIZE_S_2; i++ )
	{
		// 보조무기는 셋팅하지 않는다.
		if( EMSLOT(i) == SLOT_RHAND_S || EMSLOT(i) == SLOT_LHAND_S ) continue;

		SITEMCUSTOM ItemCustom = m_PutOnItems[i];

		/*ABL system, Juver, 2017/06/02 */
		if ( i == SLOT_LHAND  )	ItemCustom = m_PutOnItems[SLOT_RHAND];
		if ( i == SLOT_LHAND_S  )	ItemCustom = m_PutOnItems[SLOT_RHAND_S];

		SNATIVEID nidITEM = ItemCustom.nidDISGUISE;
		if ( nidITEM==SNATIVEID(false) )	nidITEM = ItemCustom.sNativeID;

		if ( !m_bVehicle && i == SLOT_VEHICLE  ) nidITEM = SNATIVEID(false);

		if ( nidITEM == SNATIVEID(false) )
		{
			//	Note : 기본 스킨과 지금 장착된 스킨이 틀릴 경우.
			//	SLOT->PIECE.
			PDXSKINPIECE pSkinPiece = NULL;	//	기본 스킨.
			PDXCHARPART pCharPart = NULL;	//	현제 장착 스킨.

			/*ABL system, Juver, 2017/06/02 */
			DxAttBoneLink* pBoneLink = NULL;
			DxAttBone* pAttBone = NULL;

			EMPIECECHAR emPiece = SLOT_2_PIECE(EMSLOT(i));
			if ( emPiece!=PIECE_SIZE )
			{
				pSkinPiece = pSkinChar->GetPiece(emPiece);	//	기본 스킨.
				pCharPart = m_pSkinChar->GetPiece(emPiece);	//	현제 장착 스킨.

				/*ABL system, Juver, 2017/06/02 */
				pBoneLink = pSkinChar->GetAttBone(emPiece);
				pAttBone = m_pSkinChar->GetAttBone(emPiece);
			}

			/*ABL system, Juver, 2017/06/02 */
			if ( pBoneLink )
			{
				if ( pAttBone && strcmp( pBoneLink->GetFileName(), pAttBone->GetFileName() ) )
				{
					m_pSkinChar->SetAttBone( pBoneLink, m_pd3dDevice );
				}
				else if ( !pAttBone )
				{
					m_pSkinChar->SetAttBone( pBoneLink, m_pd3dDevice );
				}
			}
			else if ( pSkinPiece )
			{
				if ( pCharPart && strcmp(pSkinPiece->m_szFileName,pCharPart->GetFileName()) )
					m_pSkinChar->SetPiece( pSkinPiece->m_szFileName, m_pd3dDevice );
			}
			else
			{
				if ( pCharPart )	m_pSkinChar->ResetPiece(emPiece);
			}

			/*upgrade effect, Juver, 2017/09/01 */
			EMPIECECHAR piece_reset = SLOT_2_UPGRADEPIECE( EMSLOT(i) );
			if ( piece_reset != PIECE_SIZE )	
				m_pSkinChar->ResetPiece( piece_reset );
		}
		else
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem ( nidITEM );
			if ( pItem )
			{
				/*Item Self Effect, Juver, 2017/06/09 */
				std::string strSelfEffect = pItem->GetSelfBodyEffect();

				if ( pItem->sBasicOp.emItemType != ITEM_VEHICLE )
				{
					/*ABL system, Juver, 2017/06/02 */
					std::string strFileName = pItem->GetWearingFileR( emIndex );
					if ( i == SLOT_LHAND || i == SLOT_LHAND_S )	strFileName = pItem->GetWearingFileL( emIndex );

					DxAttBoneLink* pBoneLink = DxAttBoneLinkContainer::GetInstance().LoadData( strFileName.c_str(), m_pd3dDevice, TRUE );
					if ( pBoneLink )	m_pSkinChar->SetAttBone( pBoneLink, m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), FALSE, strSelfEffect.c_str() );
					else	m_pSkinChar->SetPiece ( strFileName.c_str(), m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), FALSE, strSelfEffect.c_str() );
				
					/*item color, Juver, 2018/01/10 */
					EMPIECECHAR piece_color = SLOT_2_PIECE(EMSLOT(i));
					if ( piece_color != PIECE_SIZE )
					{
						m_pSkinChar->SetColor1( piece_color, ItemCustom.wColor1 );
						m_pSkinChar->SetColor2( piece_color, ItemCustom.wColor2 );
					}
					
					/*upgrade effect, Juver, 2017/09/01 */
					BOOL bResetUpgradeEffect = TRUE;
					if( ItemCustom.GETGRADE_EFFECT() >= 6 && ( i == SLOT_UPPER || i == SLOT_LOWER || i == SLOT_HAND || i == SLOT_FOOT ) )
					{
						EMCHARGENDER emGender = CharClassToGender( m_emClass );
						std::string strPartName[4] = { "body", "leg", "hand", "foot" };
						std::string strGender[2] = { "w", "m" };

						CString strUpgradeFileName;
						strUpgradeFileName.Format("%s_bs_%s_enchent+%d.cps", strGender[emGender].c_str(), strPartName[i-1].c_str(), ItemCustom.GETGRADE_EFFECT() );
						HRESULT hrSetUpgrade = m_pSkinChar->SetPiece ( strUpgradeFileName.GetString(), m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
						if ( hrSetUpgrade == S_OK )	bResetUpgradeEffect = FALSE;
					}

					if ( bResetUpgradeEffect )
					{
						EMPIECECHAR piece_reset = SLOT_2_UPGRADEPIECE( EMSLOT(i) );
						if ( piece_reset != PIECE_SIZE )	
							m_pSkinChar->ResetPiece( piece_reset );
					}
				}
				else
				{
					m_pSkinChar->SetPiece( pItem->GetWearingFileR(emIndex), m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), FALSE, strSelfEffect.c_str() );
				}	
			}
		}
	}

	return S_OK;
}

void DxCharSham::SetSelect ( BOOL bSel, BOOL bReserv )	
{ 
	m_bSelect = bSel;

	if ( m_bSelect )
	{
		if( m_Action == GLAT_IDLE )
			TurnAction ( GLAT_CONFT_END );

		m_bIdleReserv = FALSE;
	}
	else
	{
		if( bReserv )
			m_bIdleReserv = TRUE;
		else
			TurnAction ( GLAT_IDLE );
	}
}

void DxCharSham::TurnAction ( EMACTIONTYPE toAction )
{
	//	Note : 이전 액션 취소.
	//
	//switch ( m_Action )
	//{
	//case GLAT_IDLE:			break;
	//case GLAT_CONFT_END:	break;
	//case GLAT_ATTACK:		break;
	//default:				break;
	//};

	m_Action = toAction;

	//	Note : 액션 초기화.
	//
	switch ( m_Action )
	{
	case GLAT_IDLE:
		m_bIdleReserv = FALSE;
		m_bPeaceZone = TRUE;
		break;

	case GLAT_CONFT_END:
		m_bPeaceZone = FALSE;
		break;

	case GLAT_ATTACK:
		m_bPeaceZone = FALSE;
		m_fIdleTime = 0.0f;
		break;

	default:
		break;
	};
}

HRESULT DxCharSham::FrameMove ( float fTime, float fElapsedTime )
{
	if ( !m_pSkinChar )										
		return S_FALSE;

	switch ( m_Action )
	{
	case GLAT_IDLE:
		{
			m_fIdleTime += fElapsedTime;

			if( m_pSkinChar->GETCURMTYPE() != AN_PLACID )
				m_pSkinChar->SELECTANI ( AN_PLACID, AN_SUB_NONE );

			/*ABL system, Juver, 2017/06/02 */
			for ( int i=0; i<PIECE_SIZE; ++i )
			{
				if ( m_pSkinChar->m_pAttBone[i] )
				{
					if ( m_pSkinChar->m_pAttBone[i]->GETCURMTYPE() != AN_ABL_STAY )
						m_pSkinChar->m_pAttBone[i]->SELECTANI( AN_ABL_STAY, AN_SUB_NONE );
				}
			}
		}
		break;

	case GLAT_CONFT_END:
		{
			if( m_pSkinChar->GETCURMTYPE() != AN_CONFT_WIN && 
				m_pSkinChar->GETCURMTYPE() != AN_GUARD_N )
				m_pSkinChar->SELECTANI ( AN_CONFT_WIN, AN_SUB_NONE );

			if( m_pSkinChar->ISENDANIM() )
				TurnAction ( GLAT_ATTACK );

			/*ABL system, Juver, 2017/06/02 */
			for ( int i=0; i<PIECE_SIZE; ++i )
			{
				if ( m_pSkinChar->m_pAttBone[i] )	
				{
					if ( m_pSkinChar->m_pAttBone[i]->GETCURMTYPE() != AN_ABL_STAY )
						m_pSkinChar->m_pAttBone[i]->SELECTANI( AN_ABL_STAY, AN_SUB_NONE );
				}
			}
		}
		break;

	case GLAT_ATTACK:
		{
			if( m_pSkinChar->GETCURMTYPE() != AN_GUARD_N )		
				m_pSkinChar->SELECTANI ( AN_GUARD_N, GLCHARLOGIC::m_emANISUBTYPE );

			if( m_fIdleTime == m_pSkinChar->GETENDTIME() && m_bIdleReserv )
			{
				TurnAction ( GLAT_IDLE );
				break;
			}

			if( (m_fIdleTime*1000.0f) > (m_pSkinChar->GETENDTIME()/2.0f) )
			{
				m_fIdleTime = m_pSkinChar->GETENDTIME();
			}
			else
			{
				m_fIdleTime += fElapsedTime;
			}

			/*ABL system, Juver, 2017/06/02 */
			for ( int i=0; i<PIECE_SIZE; ++i )
			{
				if ( m_pSkinChar->m_pAttBone[i] )	
				{
					if ( m_pSkinChar->m_pAttBone[i]->GETCURMTYPE() != AN_ABL_STAY )
						m_pSkinChar->m_pAttBone[i]->SELECTANI( AN_ABL_STAY, AN_SUB_NONE );
				}
			}
		}
		break;
	};

	if ( m_bSelect )
	{
		STARGETID sTARID(CROW_PC,m_nID);
		DxEffGroupPlayer::GetInstance().PassiveEffect ( GLCONST_CHAR::strSELECT_CHAR.c_str(), m_matTrans, sTARID );
	}
	else
	{
		m_bEffect = FALSE;
		STARGETID sTARID(CROW_PC,m_nID);
		DxEffGroupPlayer::GetInstance().DeletePassiveEffect ( GLCONST_CHAR::strSELECT_CHAR.c_str(), sTARID );
	}

	//	Note : 스킨 업데이트.
	//
	m_pSkinChar->SetPosition ( m_vPos );
	m_pSkinChar->FrameMove ( fTime, fElapsedTime, TRUE, FALSE, !m_bPeaceZone );

	//	Note : 현제 위치와 방향으로 Transform 메트릭스 계산.
	//
	D3DXMATRIX matTrans, matYRot;
	D3DXMatrixTranslation ( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	float fThetaY = DXGetThetaYFromDirection ( m_vDir, m_vDirOrig );
	D3DXMatrixRotationY ( &matYRot, fThetaY );

	m_matTrans = matYRot * matTrans;

	//	Note : AABB 계산.
	//
	m_vMax = m_vPos + m_vMaxOrg;
	m_vMin = m_vPos + m_vMinOrg;

	return S_OK;
}

HRESULT DxCharSham::Render ( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv, BOOL bRendAABB )
{
	if ( m_bNeedData && !(m_dwRevData&RECEIVE_CHARDATA) )	return S_FALSE;
	if ( !m_pSkinChar )										return S_FALSE;

	if ( bRendAABB ) EDITMESHS::RENDERAABB ( pd3dDevice, m_vMax, m_vMin );	//	테스트용.

	HRESULT hr;
	m_pSkinChar->SetScaleAdjust( m_fScaleRange );
	hr = m_pSkinChar->Render ( pd3dDevice, m_matTrans );
	if ( FAILED(hr) )	return hr;

	return S_OK;
}

HRESULT DxCharSham::RenderShadow ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( m_bNeedData && !(m_dwRevData&RECEIVE_CHARDATA) )	return S_FALSE;
	if ( !m_pSkinChar )										return S_FALSE;

	//	Note : 그림자 랜더링.
	//
	DxShadowMap::GetInstance().RenderShadowCharMob ( m_pSkinChar, m_matTrans, pd3dDevice );

	return S_OK;
}

HRESULT DxCharSham::RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( m_pSkinChar )	
		m_pSkinChar->RestoreDeviceObjects ( pd3dDevice );

	return S_OK;
}

HRESULT DxCharSham::InvalidateDeviceObjects ()
{
	if ( m_pSkinChar )	
		m_pSkinChar->InvalidateDeviceObjects ();

	return S_OK;
}