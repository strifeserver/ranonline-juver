#include "StdAfx.h"
#include "CharacterWindowCharRender.h"

#include "../DxCommon/DxBackUpRendTarget.h"

#include "GLItemMan.h"
#include "GLogicData.h"
#include "DxEffcharData.h"
#include "RANPARAM.h"
#include "GLGaeaClient.h"
#include "DxGlobalStage.h"

#include "DxEffectMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern BOOL g_bPREVIEW_CHAR_RENDER;

CCharacterWindowCharRender::CCharacterWindowCharRender () 
	: m_pSkinChar( NULL )
	, m_wLastFace(0)
	, m_wLastHair(0)
	, m_fDelay(0.0f)
{
	D3DXMatrixIdentity ( &m_matTrans );
}

CCharacterWindowCharRender::~CCharacterWindowCharRender ()
{
}

void CCharacterWindowCharRender::CreateSubControl ()
{
}

void CCharacterWindowCharRender::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

HRESULT CCharacterWindowCharRender::RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
		m_pSkinChar->RestoreDeviceObjects( pd3dDevice );

	hr = CUIGroup::RestoreDeviceObjects( pd3dDevice );
	return hr;
}

HRESULT CCharacterWindowCharRender::DeleteDeviceObjects ()
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
		m_pSkinChar->DeleteDeviceObjects ();

	hr = CUIGroup::DeleteDeviceObjects ();

	return hr;
}

HRESULT CCharacterWindowCharRender::Render ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
	{
		g_bPREVIEW_CHAR_RENDER = TRUE;
	
		if ( m_fDelay < 0.3 ) return S_OK;

		DWORD dwAlphaBlendEnable, dwSrcBlend, dwDestBlend, dwZWriteEnable, dwZEnable, dwZFunc, dwClipPlaneEnable, dwFogEnable, dwAmbient, dwLighting;
		DWORD dwColorOP, dwAlphaOP, dwMinFilter, dwMagFilter, dwMipFilter;
		D3DXMATRIX		matOrgView, matOrgProj, matOrgWorld;
		D3DVIEWPORTQ OrgViewPort;

		pd3dDevice->GetViewport(&OrgViewPort);

		pd3dDevice->GetTransform ( D3DTS_VIEW, &matOrgView );
		pd3dDevice->GetTransform ( D3DTS_PROJECTION, &matOrgProj );
		pd3dDevice->GetTransform ( D3DTS_WORLD, &matOrgWorld );

		DxBackUpRendTarget sBackupTarget ( pd3dDevice );

		pd3dDevice->GetRenderState( D3DRS_ALPHABLENDENABLE,	&dwAlphaBlendEnable );
		pd3dDevice->GetRenderState( D3DRS_SRCBLEND,			&dwSrcBlend );
		pd3dDevice->GetRenderState( D3DRS_DESTBLEND,		&dwDestBlend );
		pd3dDevice->GetRenderState( D3DRS_ZWRITEENABLE,		&dwZWriteEnable );
		pd3dDevice->GetRenderState( D3DRS_ZENABLE,			&dwZEnable );
		pd3dDevice->GetRenderState( D3DRS_ZFUNC,			&dwZFunc);
		pd3dDevice->GetRenderState( D3DRS_CLIPPLANEENABLE,	&dwClipPlaneEnable );
		pd3dDevice->GetRenderState( D3DRS_FOGENABLE,		&dwFogEnable );
		pd3dDevice->GetRenderState( D3DRS_AMBIENT,			&dwAmbient );
		pd3dDevice->GetRenderState( D3DRS_LIGHTING,			&dwLighting );

		pd3dDevice->GetTextureStageState( 0, D3DTSS_COLOROP,	&dwColorOP );
		pd3dDevice->GetTextureStageState( 0, D3DTSS_ALPHAOP,	&dwAlphaOP );

		pd3dDevice->GetSamplerState( 0, D3DSAMP_MINFILTER,	&dwMinFilter );
		pd3dDevice->GetSamplerState( 0, D3DSAMP_MAGFILTER,	&dwMagFilter );
		pd3dDevice->GetSamplerState( 0, D3DSAMP_MIPFILTER,	&dwMipFilter );
		
		pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0xffa08080, 1.0f, 0 ) ;

		pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,		TRUE );
		pd3dDevice->SetRenderState( D3DRS_ZENABLE,			D3DZB_TRUE );
		pd3dDevice->SetRenderState( D3DRS_ZFUNC,			D3DCMP_LESSEQUAL);
		pd3dDevice->SetRenderState( D3DRS_AMBIENT,			D3DCOLOR_XRGB(220,220,220) );
		pd3dDevice->SetRenderState( D3DRS_LIGHTING,			FALSE );

		D3DXMATRIX		matView, matProj, matWorld;

		D3DVIEWPORTQ ViewPort;
		ViewPort.X      = (DWORD)GetGlobalPos().left;
		ViewPort.Y      = (DWORD)GetGlobalPos().top;
		ViewPort.Width  = (DWORD)GetGlobalPos().sizeX;
		ViewPort.Height = (DWORD)GetGlobalPos().sizeY;
		ViewPort.MinZ = 0.0f;
		ViewPort.MaxZ = 1.0f;
		pd3dDevice->SetViewport(&ViewPort);

		D3DXVECTOR3 vFromPt		= D3DXVECTOR3( 0.0f, 0.3f, -35.0f );
		D3DXVECTOR3 vLookatPt	= D3DXVECTOR3( -0.02f, 0.0f, 5.0f );
		D3DXVECTOR3 vUpVec		= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		D3DXMatrixLookAtLH ( &matView, &vFromPt, &vLookatPt, &vUpVec );
		pd3dDevice->SetTransform ( D3DTS_VIEW, &matView );

		float fFieldOfView = D3DX_PI/4.0f;
		float fAspectRatio = ((float)ViewPort.Width) / (float)ViewPort.Height;
		D3DXMatrixPerspectiveFovLH ( &matProj, fFieldOfView, fAspectRatio, 1.0f, 80.0f );
		pd3dDevice->SetTransform ( D3DTS_PROJECTION, &matProj );
		
		D3DXMatrixIdentity ( &matWorld );
		pd3dDevice->SetTransform ( D3DTS_WORLD, &matWorld );

		RenderModel( pd3dDevice );

		sBackupTarget.RestoreTarget ( pd3dDevice );

		pd3dDevice->SetTransform ( D3DTS_VIEW, &matOrgView );
		pd3dDevice->SetTransform ( D3DTS_PROJECTION, &matOrgProj );
		pd3dDevice->SetTransform ( D3DTS_WORLD, &matOrgWorld );

		pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,	dwAlphaBlendEnable );
		pd3dDevice->SetRenderState( D3DRS_SRCBLEND,			dwSrcBlend );
		pd3dDevice->SetRenderState( D3DRS_DESTBLEND,		dwDestBlend );
		pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,		dwZWriteEnable );
		pd3dDevice->SetRenderState( D3DRS_ZENABLE,			dwZEnable );
		pd3dDevice->SetRenderState( D3DRS_ZFUNC,			dwZFunc);
		pd3dDevice->SetRenderState( D3DRS_CLIPPLANEENABLE,	dwClipPlaneEnable );
		pd3dDevice->SetRenderState( D3DRS_FOGENABLE,		dwFogEnable );
		pd3dDevice->SetRenderState( D3DRS_AMBIENT,			dwAmbient );
		pd3dDevice->SetRenderState( D3DRS_LIGHTING,			dwLighting );

		pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,	dwColorOP );
		pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,	dwAlphaOP );

		pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER,	dwMinFilter );
		pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER,	dwMagFilter );
		pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER,	dwMipFilter );

		pd3dDevice->SetViewport(&OrgViewPort);	

		g_bPREVIEW_CHAR_RENDER = FALSE;
	}else{
		CreateModel( pd3dDevice );
	}

	hr = CUIGroup::Render ( pd3dDevice );
	return hr;
}

HRESULT CCharacterWindowCharRender::FrameMove( LPDIRECT3DDEVICEQ pd3dDevice, float fTime, float fElapsedTime )
{
	HRESULT hr = S_OK;

	m_fDelay += fElapsedTime;

	if ( m_pSkinChar )
	{
		m_pSkinChar->FrameMove ( fTime, fElapsedTime, TRUE, FALSE, FALSE );
	}

	GLCharacter* pChar = GLGaeaClient::GetInstance().GetCharacter();
	if ( pChar )
	{
		UpdateSuit( pd3dDevice );
	}

	hr = CUIGroup::FrameMove( pd3dDevice, fTime, fElapsedTime );
	return hr;
}

void CCharacterWindowCharRender::CreateModel( LPDIRECT3DDEVICEQ pd3dDevice )
{
	GLCharacter* pChar = GLGaeaClient::GetInstance().GetCharacter();
	if ( !pChar )		return;

	EMCHARINDEX emIndex = CharClassToIndex( DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass );
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData ( GLCONST_CHAR::szCharSkin[emIndex], pd3dDevice, true  );

	if ( !pSkinChar )	return;

	SAFE_DELETE(m_pSkinChar);
	m_pSkinChar = new DxSkinChar;
	m_pSkinChar->InitDeviceObjects( pd3dDevice );
	m_pSkinChar->SetCharData ( pSkinChar, pd3dDevice );
	m_pSkinChar->SELECTANI( AN_PLACID, AN_SUB_NONE );
	UpdateSuit( pd3dDevice );

	m_fDelay = 0.0f;
}

void CCharacterWindowCharRender::RenderModel( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( m_pSkinChar )
	{
		float fScale = 1.0f;
		D3DXMATRIX matTrans, matScale;

		D3DXMatrixScaling( &matScale, fScale, fScale, fScale );
		D3DXMatrixTranslation( &matTrans, 0.0f, -12.0f, 0.0f );

		m_matTrans = matScale*matTrans;

		m_pSkinChar->Render( pd3dDevice, m_matTrans/*, FALSE, FALSE, FALSE */);
	}
}

void CCharacterWindowCharRender::UpdateSuit( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( !m_pSkinChar )	return;

	GLCharacter* pChar = GLGaeaClient::GetInstance().GetCharacter();
	if ( !pChar )		return;

	EMCHARINDEX emIndex = CharClassToIndex( pChar->m_emClass );
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().FindData ( GLCONST_CHAR::szCharSkin[emIndex] );
	if ( !pSkinChar )	return;

	const GLCONST_CHARCLASS &sCONST = GLCONST_CHAR::cCONSTCLASS[emIndex];

	WORD m_wFace = pChar->m_wFace;
	WORD m_wHair = pChar->m_wHair;
	WORD m_wHairColor = pChar->m_wHairColor;

	if ( sCONST.dwHEADNUM > m_wFace )
	{
		std::string strHEAD_CPS = sCONST.strHEAD_CPS[m_wFace];
		PDXCHARPART pCharPart = NULL;
		pCharPart = m_pSkinChar->GetPiece(PIECE_HEAD);
		if ( pCharPart && strcmp(strHEAD_CPS.c_str(),pCharPart->m_szFileName) )
			m_pSkinChar->SetPiece ( strHEAD_CPS.c_str(), pd3dDevice, 0x0, 0, TRUE );

	}

	if ( sCONST.dwHAIRNUM > m_wHair )
	{
		std::string strHAIR_CPS = sCONST.strHAIR_CPS[m_wHair];
		PDXCHARPART pCharPart = NULL;
		pCharPart = m_pSkinChar->GetPiece(PIECE_HAIR);
		if ( pCharPart && strcmp(strHAIR_CPS.c_str(),pCharPart->m_szFileName) )
			m_pSkinChar->SetPiece ( strHAIR_CPS.c_str(), pd3dDevice, 0x0, 0, TRUE );
	}

	m_pSkinChar->SetHairColor( m_wHairColor );

	// Fix CharRender Arvin.BC
	for ( int i=0; i<SLOT_NSIZE_S_2; i++ )
	{	
		SITEMCUSTOM ItemCustom = pChar->m_PutOnItems[i];
	
		SITEM* pItem = GLItemMan::GetInstance().GetItem( ItemCustom.sNativeID );
		if ( pItem )
		{
			if ( pItem->sBasicOp.emItemType != ITEM_VEHICLE )
			{
				std::string strRight = pItem->GetWearingFileR( emIndex );
				std::string strLeft = pItem->GetWearingFileL( emIndex );
				std::string strSelfEffect = pItem->GetSelfBodyEffect();

				{
					DxAttBoneLink* pBoneLink = DxAttBoneLinkContainer::GetInstance().LoadData( strRight.c_str(), pd3dDevice, TRUE );
					if ( pBoneLink )	m_pSkinChar->SetAttBone( pBoneLink, pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE, strSelfEffect.c_str() );
					else	m_pSkinChar->SetPiece ( strRight.c_str(), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE, strSelfEffect.c_str() );
				}
				{
					DxAttBoneLink* pBoneLink = DxAttBoneLinkContainer::GetInstance().LoadData( strLeft.c_str(), pd3dDevice, TRUE );
					if ( pBoneLink )	m_pSkinChar->SetAttBone( pBoneLink, pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE, strSelfEffect.c_str() );
					else	m_pSkinChar->SetPiece ( strLeft.c_str(), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE, strSelfEffect.c_str() );
				}

				/*upgrade effect, Juver, 2017/09/01 */
				BOOL bResetUpgradeEffect = TRUE;
				if( ItemCustom.GETGRADE_EFFECT() >= 6 && ( i == SLOT_UPPER || i == SLOT_LOWER || i == SLOT_HAND || i == SLOT_FOOT ) )
				{
					EMCHARGENDER emGender = CharClassToGender( pChar->m_emClass );
					std::string strPartName[4] = { "body", "leg", "hand", "foot" };
					std::string strGender[2] = { "w", "m" };

					CString strUpgradeFileName;
					strUpgradeFileName.Format("%s_bs_%s_enchent+%d.cps", strGender[emGender].c_str(), strPartName[i-1].c_str(), ItemCustom.GETGRADE_EFFECT() );
					HRESULT hrSetUpgrade = m_pSkinChar->SetPiece ( strUpgradeFileName.GetString(), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
					if ( hrSetUpgrade == S_OK )	bResetUpgradeEffect = FALSE;
				}

				if ( bResetUpgradeEffect )
				{
					EMPIECECHAR piece_reset = SLOT_2_UPGRADEPIECE( EMSLOT(i) );
					if ( piece_reset != PIECE_SIZE )	
						m_pSkinChar->ResetPiece( piece_reset );
				}
			}
		}
	}
}

void CCharacterWindowCharRender::ClearRender()
{
	if ( m_pSkinChar )
	{
		SAFE_DELETE ( m_pSkinChar );
		m_fDelay = 0.0f;
	}
}