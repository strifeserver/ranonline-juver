#include "stdafx.h"

#include "../Common/SerialFile.h"
#include "../../DxCommon/TextureManager.h"
#include "../Meshs/DxSkinChar.h"

/*ABL system, Juver, 2017/05/29 */
#include "../Meshs/DxAttBone.h"
#include "../Meshs/DxAttBoneRender.h"

/*vehicle system, Juver, 2017/08/03 */
#include "../Meshs/DxVehicle.h"

#include "./DxEffAniFaceOff.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DWORD		DxEffAniData_FaceOff::TYPEID	= EMEFFANI_FACEOFF;
DWORD		DxEffAniData_FaceOff::VERSION	= 0x0100;
TCHAR		DxEffAniData_FaceOff::NAME[64]	= _T("DxEffAniData_FaceOff");

DxEffAni* DxEffAniData_FaceOff::NEWOBJ( SAnimContainer* pAnimContainer )
{
	DxEffAniFaceOff*	pEff = new DxEffAniFaceOff;

	StringCchCopy( pEff->m_szTexture, 32, m_szTexture );

	pEff->Create ( m_pd3dDevice, pAnimContainer );

	return	pEff;
}

HRESULT	DxEffAniData_FaceOff::LoadFile ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr;
	DWORD dwVer, dwSize, dwTypeID;

	SFile >> dwTypeID;
	SFile >> dwVer;
	SFile >> dwSize;

	//	Note : ������ ��ġ�� ���. 
	//
	if ( dwVer == VERSION )
	{
		SFile.ReadBuffer ( &m_Property, sizeof(m_Property) );
	}
	else
	{
		CDebugSet::ErrorVersion( "DxEffAniData_FaceOff::LoadFile", SFile.GetFileName(), dwVer );
		SFile.SetOffSet ( SFile.GetfTell()+dwSize );
		return E_FAIL;
	}

	if ( pd3dDevice )
	{
		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;
	}

	return S_OK;
}

HRESULT	DxEffAniData_FaceOff::SaveFile ( CSerialFile &SFile )
{
	SFile << TYPEID;
	SFile << VERSION;

	SFile << (DWORD) ( sizeof(m_Property) );

	//	Note : ����Ʈ�� Property �� ����.
	//
	SFile.WriteBuffer ( &m_Property, sizeof(m_Property) );

	return S_OK;
}

BOOL DxEffAniData_FaceOff::CheckEff ( DWORD dwCurKeyTime, DWORD dwPrevFrame )
{
	if ( !m_bCreated )			// �������� ���� ȿ���� �� �������� �ʴ´�.
	{
		m_bCreated = TRUE;

		return TRUE;
	}

	return FALSE;		
}

//	-----------------------------------------------	--------------------------------------------------

DxEffAniFaceOff::DxEffAniFaceOff(void) :
	DxEffAni(),
	m_pd3dDevice(NULL),
	m_pSavedBaseSB(NULL),
	m_pEffectBaseSB(NULL),
	m_pTexture(NULL)
{
}

DxEffAniFaceOff::~DxEffAniFaceOff(void)
{
	m_pd3dDevice = NULL;
	CleanUp ();
}

HRESULT DxEffAniFaceOff::CreateDevice ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	return S_OK;
}

HRESULT DxEffAniFaceOff::ReleaseDevice ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	return S_OK;
}

HRESULT DxEffAniFaceOff::OneTimeSceneInit ()
{
	return S_OK;
}

HRESULT DxEffAniFaceOff::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	m_pd3dDevice = pd3dDevice;
	TextureManager::LoadTexture( m_szTexture, pd3dDevice, m_pTexture, 0L, 0L, TRUE );

	return S_OK;
}

HRESULT DxEffAniFaceOff::RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( !pd3dDevice )	return S_OK;

	D3DCAPSQ d3dCaps;
	pd3dDevice->GetDeviceCaps ( &d3dCaps );

	m_pd3dDevice = pd3dDevice;

	for( UINT which=0; which<2; which++ )
	{
		pd3dDevice->BeginStateBlock();

		//	Note : SetRenderState() ����
		pd3dDevice->SetRenderState ( D3DRS_ZWRITEENABLE,		FALSE );
		pd3dDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE,	TRUE );
		pd3dDevice->SetRenderState ( D3DRS_FOGENABLE,			FALSE );

		pd3dDevice->SetRenderState ( D3DRS_SRCBLEND,			D3DBLEND_SRCALPHA );
		pd3dDevice->SetRenderState ( D3DRS_DESTBLEND,			D3DBLEND_INVSRCALPHA );

		pd3dDevice->SetRenderState ( D3DRS_TEXTUREFACTOR,		0xffffffff );

		//	Note : SetTextureStageState() ����
		pd3dDevice->SetTextureStageState ( 0, D3DTSS_COLORARG1,	D3DTA_TEXTURE );
		pd3dDevice->SetTextureStageState ( 0, D3DTSS_COLORARG2,	D3DTA_DIFFUSE );
		pd3dDevice->SetTextureStageState ( 0, D3DTSS_COLOROP,	D3DTOP_MODULATE );

		pd3dDevice->SetTextureStageState ( 1, D3DTSS_COLORARG1,	D3DTA_CURRENT );
		pd3dDevice->SetTextureStageState ( 1, D3DTSS_COLORARG2,	D3DTA_TFACTOR );
		pd3dDevice->SetTextureStageState ( 1, D3DTSS_COLOROP,	D3DTOP_MODULATE );

		pd3dDevice->SetTextureStageState ( 0, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE );
		pd3dDevice->SetTextureStageState ( 0, D3DTSS_ALPHAARG2,	D3DTA_TFACTOR );
		pd3dDevice->SetTextureStageState ( 0, D3DTSS_ALPHAOP,	D3DTOP_MODULATE );

		if( which==0 )	pd3dDevice->EndStateBlock( &m_pSavedBaseSB );
		else			pd3dDevice->EndStateBlock( &m_pEffectBaseSB );
	}

	return S_OK;
}

HRESULT DxEffAniFaceOff::InvalidateDeviceObjects ()
{
	SAFE_RELEASE( m_pSavedBaseSB );
	SAFE_RELEASE( m_pEffectBaseSB );

	return S_OK;
}

HRESULT DxEffAniFaceOff::DeleteDeviceObjects ()
{
	TextureManager::ReleaseTexture( m_szTexture, m_pTexture );

	return S_OK;
}

HRESULT DxEffAniFaceOff::FinalCleanup ()
{
	return S_OK;
}

HRESULT DxEffAniFaceOff::FrameMove ( float fTime, float fElapsedTime )
{
	return S_OK;
}

HRESULT	DxEffAniFaceOff::Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxSkinChar* pSkinChar, const D3DXMATRIX& matCurPos )
{
	if( !m_bFrameMove )	return S_OK;	// �ִϸ��̼��� ������ �ʴ�.

	if ( !pSkinChar->m_PartArray[PIECE_HEAD].m_pSkinMesh )	return S_OK;
	if ( !pSkinChar->m_PartArray[PIECE_HEAD].m_pmcMesh )	return S_OK;

	pSkinChar->m_sSkinEffData.m_rFaceTex = m_pTexture;
	pd3dDevice->SetTexture( 0, m_pTexture );

	CHARSETTING sCharSetting;
	sCharSetting.pMeshContainerBase = pSkinChar->m_PartArray[PIECE_HEAD].m_pmcMesh;
	sCharSetting.pmtrlPiece			= NULL;
	sCharSetting.pmtrlSpecular		= NULL;
	sCharSetting.bWorldIdentity		= FALSE;
	sCharSetting.emRDOP				= CTOP_NEWTEX;

	pSkinChar->m_PartArray[PIECE_HEAD].m_pSkinMesh->SetDrawState( TRUE, FALSE, FALSE, FALSE );
	pSkinChar->m_PartArray[PIECE_HEAD].m_pSkinMesh->DrawMeshContainer( pd3dDevice, sCharSetting	);

	return S_OK;
}

BOOL DxEffAniFaceOff::IsHeadDrawChild()	
{ 
	if( m_bFrameMove )	return TRUE;
	else				return FALSE; 
}

/*ABL system, Juver, 2017/05/29 */
HRESULT	DxEffAniFaceOff::Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxAttBone* pAttBone, const D3DXMATRIX& matCurPos )
{
	if( !m_bFrameMove )	return S_OK;	// �ִϸ��̼��� ������ �ʴ�.

	if ( !pAttBone->m_PartArray[PIECE_HEAD].m_pSkinMesh )	return S_OK;
	if ( !pAttBone->m_PartArray[PIECE_HEAD].m_pmcMesh )	return S_OK;

	pAttBone->m_sSkinEffData.m_rFaceTex = m_pTexture;
	pd3dDevice->SetTexture( 0, m_pTexture );

	CHARSETTING sCharSetting;
	sCharSetting.pMeshContainerBase = pAttBone->m_PartArray[PIECE_HEAD].m_pmcMesh;
	sCharSetting.pmtrlPiece			= NULL;
	sCharSetting.pmtrlSpecular		= NULL;
	sCharSetting.bWorldIdentity		= FALSE;
	sCharSetting.emRDOP				= CTOP_NEWTEX;

	pAttBone->m_PartArray[PIECE_HEAD].m_pSkinMesh->SetDrawState( TRUE, FALSE, FALSE, FALSE );
	pAttBone->m_PartArray[PIECE_HEAD].m_pSkinMesh->DrawMeshContainer( pd3dDevice, sCharSetting	);

	return S_OK;
}

/*ABL system, Juver, 2017/05/29 */
HRESULT	DxEffAniFaceOff::Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxAttBoneRender* pAttBone, const D3DXMATRIX& matCurPos )
{
	if( !m_bFrameMove )	return S_OK;	// �ִϸ��̼��� ������ �ʴ�.

	if ( !pAttBone->m_PartArray[PIECE_HEAD].m_pSkinMesh )	return S_OK;
	if ( !pAttBone->m_PartArray[PIECE_HEAD].m_pmcMesh )	return S_OK;

	pAttBone->m_sSkinEffData.m_rFaceTex = m_pTexture;
	pd3dDevice->SetTexture( 0, m_pTexture );

	CHARSETTING sCharSetting;
	sCharSetting.pMeshContainerBase = pAttBone->m_PartArray[PIECE_HEAD].m_pmcMesh;
	sCharSetting.pmtrlPiece			= NULL;
	sCharSetting.pmtrlSpecular		= NULL;
	sCharSetting.bWorldIdentity		= FALSE;
	sCharSetting.emRDOP				= CTOP_NEWTEX;

	pAttBone->m_PartArray[PIECE_HEAD].m_pSkinMesh->SetDrawState( TRUE, FALSE, FALSE, FALSE );
	pAttBone->m_PartArray[PIECE_HEAD].m_pSkinMesh->DrawMeshContainer( pd3dDevice, sCharSetting	);

	return S_OK;
}

/*vehicle system, Juver, 2017/08/03 */
HRESULT	DxEffAniFaceOff::Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxVehicle* pVehicle, const D3DXMATRIX& matCurPos )
{
	if( !m_bFrameMove )	return S_OK;	// �ִϸ��̼��� ������ �ʴ�.

	if ( !pVehicle->m_PartArray[PIECE_HEAD].m_pSkinMesh )	return S_OK;
	if ( !pVehicle->m_PartArray[PIECE_HEAD].m_pmcMesh )	return S_OK;

	pVehicle->m_sSkinEffData.m_rFaceTex = m_pTexture;
	pd3dDevice->SetTexture( 0, m_pTexture );

	CHARSETTING sCharSetting;
	sCharSetting.pMeshContainerBase = pVehicle->m_PartArray[PIECE_HEAD].m_pmcMesh;
	sCharSetting.pmtrlPiece			= NULL;
	sCharSetting.pmtrlSpecular		= NULL;
	sCharSetting.bWorldIdentity		= FALSE;
	sCharSetting.emRDOP				= CTOP_NEWTEX;

	pVehicle->m_PartArray[PIECE_HEAD].m_pSkinMesh->SetDrawState( TRUE, FALSE, FALSE, FALSE );
	pVehicle->m_PartArray[PIECE_HEAD].m_pSkinMesh->DrawMeshContainer( pd3dDevice, sCharSetting	);

	return S_OK;
}