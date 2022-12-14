#include "stdafx.h"

#include "../DxEffect/DxEffectMan.h"

#include "../DxEffect/Single/DxEffSingle.h"
#include "../Single/DxEffSinglePropGMan.h"
#include "../Common/SerialFile.h"

#include "../DxCommon/DxWeatherMan.h"
#include "../Meshs/DxCharPart.h"
#include "../Meshs/DxSkinPieceContainer.h"

#include "../DxCommon/EDITMESHS.h"

#include "./DxEffCharSingle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DWORD		DxEffCharSingle::TYPEID				= EMEFFCHAR_SINGLE;
DWORD		DxEffCharSingle::VERSION			= 0x0200;
char		DxEffCharSingle::NAME[MAX_PATH]		= "DxEffCharSingle";

DxEffCharSingle::DxEffCharSingle(void) :
	DxEffChar(),

	m_pPropGroup(NULL),
	m_vTransUp(0.f,0.f,0.f),
	m_vPrevUp(0.f,0.f,0.f),
	m_vTransDown(0.f,0.f,0.f),
	m_vBackUp(0.f,0.f,0.f),
	m_fTarDirection(0.f),
	m_vDirection(0,0,0),
	m_fCoolTime(10.f),
	m_fCoolTimeADD(0.f),
	m_vCurPos(0.f,0.f,0.f),
	m_pSkinMesh(NULL),
	m_fPlayTime(0.f),
	m_bNewMatrix(FALSE)
{
	memset( m_szFileName, 0, sizeof(char)*MAX_PATH );
	memset( m_szTrace, 0, sizeof(char)*STRACE_NSIZE );
	memset( m_szTraceBack, 0, sizeof(char)*STRACE_NSIZE );
	D3DXMatrixIdentity( &m_matEffLocal );

	m_pSingleGroup = NULL;
}

DxEffCharSingle::~DxEffCharSingle(void)
{
	CleanUp ();
}

DxEffChar* DxEffCharSingle::CloneInstance ( LPDIRECT3DDEVICEQ pd3dDevice, DxCharPart* pCharPart, DxSkinPiece* pSkinPiece )
{
	HRESULT hr;
	DxEffCharSingle *pEffCharSingle = new DxEffCharSingle;
	pEffCharSingle->SetLinkObj ( pCharPart, pSkinPiece );
	pEffCharSingle->SetProperty ( &m_Property );

	hr = pEffCharSingle->Create ( pd3dDevice );
	if ( FAILED(hr) )
	{
		SAFE_DELETE(pEffCharSingle);
		return NULL;
	}

	return pEffCharSingle;
}

HRESULT DxEffCharSingle::CreateDevice ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	return S_OK;
}

HRESULT DxEffCharSingle::ReleaseDevice ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	return S_OK;
}

HRESULT DxEffCharSingle::OneTimeSceneInit ()
{

	if ( m_pSingleGroup )		m_pSingleGroup->OneTimeSceneInit ();

	return S_OK;
}

HRESULT DxEffCharSingle::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;

	if ( m_pCharPart )
	{
		m_pSkinMesh = m_pCharPart->m_pSkinMesh;
	}
	else if ( m_pSkinPiece )
	{
		m_pSkinMesh = m_pSkinPiece->m_pSkinMesh;
	}

	m_pPropGroup = DxEffSinglePropGMan::GetInstance().LoadEffectGProp ( m_szFileName );
	if ( !m_pPropGroup )	return E_FAIL;

	if ( m_pPropGroup )
	{
		D3DXVECTOR3	vNormal;
	
		SAFE_DELETE(m_pSingleGroup);						// ÀÌÀü µ¥ÀÌÅÍ´Â Áö¿öÁØ´Ù.
		m_pSingleGroup = m_pPropGroup->NEWEFFGROUP ();
		if ( !m_pSingleGroup )	return E_FAIL;

		//	Note : Eff Group Create Dev.
		//
		m_pSingleGroup->Create ( pd3dDevice );

		//	Note : Eff GroupÀÇ ¸ÅÆ®¸¯½º Æ®·£½ºÆû ÁöÁ¤.
		//
		if ( m_szTrace[0]==NULL )	return E_FAIL;
		
		if ( m_pCharPart )
		{
			hr = m_pCharPart->CalculateVertexInflu ( m_szTrace, m_vTransUp, vNormal );
			if ( FAILED(hr) )	return E_FAIL;
			D3DXMatrixTranslation ( &m_matTrans, m_vTransUp.x, m_vTransUp.y, m_vTransUp.z );
		}
		else if ( m_pSkinPiece )
		{
			hr = m_pSkinPiece->CalculateVertexInflu ( m_szTrace, m_vTransUp, vNormal );
			if ( FAILED(hr) )	return E_FAIL;
			D3DXMatrixTranslation ( &m_matTrans, m_vTransUp.x, m_vTransUp.y, m_vTransUp.z );
		}

		m_fPlayTime = 0.f;
		m_pSingleGroup->m_matWorld = m_matTrans;
	}

	if ( m_pSingleGroup )		m_pSingleGroup->InitDeviceObjects ( pd3dDevice );

	return S_OK;
}

HRESULT DxEffCharSingle::RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( m_pSingleGroup )		m_pSingleGroup->RestoreDeviceObjects ( pd3dDevice );

	return S_OK;
}

HRESULT DxEffCharSingle::InvalidateDeviceObjects ()
{
	if ( m_pSingleGroup )		m_pSingleGroup->InvalidateDeviceObjects ();

	return S_OK;
}

HRESULT DxEffCharSingle::DeleteDeviceObjects ()
{
	if ( m_pSingleGroup )		m_pSingleGroup->DeleteDeviceObjects ();

	return S_OK;
}

HRESULT DxEffCharSingle::FinalCleanup ()
{
	if ( m_pSingleGroup )		m_pSingleGroup->FinalCleanup();
	SAFE_DELETE(m_pSingleGroup);

	return S_OK;
}

HRESULT DxEffCharSingle::FrameMove ( float fTime, float fElapsedTime )
{
	HRESULT hr = S_OK;

	if ( !SetWeather() )		return S_OK;

	m_fTime = fTime;
	m_fPlayTime += fElapsedTime;

	if ( m_pSingleGroup )
	{
		m_pSingleGroup->FrameMove ( fTime, fElapsedTime );

		if ( m_dwFlag&USE_REPEAT )
		{
			m_fCoolTimeADD += fElapsedTime;
			if ( m_fCoolTimeADD > m_fCoolTime )
			{
				m_fCoolTimeADD = 0.f;
				m_pSingleGroup->ReStartEff();
			}
		}
		else
		{
			if ( m_pSingleGroup->m_dwAliveCount == 0 )
			{
				SetEnd();
			}
		}
	}

	return S_OK;
}

void	DxEffCharSingle::RenderEff( LPDIRECT3DDEVICEQ pd3dDevice, LPD3DXMATRIX pMatrix, const float fScale )
{
	HRESULT hr = S_OK;
	D3DXVECTOR3 vNormalUp;
	D3DXVECTOR3 vNormalDown;
	D3DXMATRIX matVertex;

	if ( !SetWeather() )		return;

	if ( m_dwFlag&(USE_1POINT | USE_MATRIX | USE_MATRIX2 ) )
	{
		if ( m_pCharPart )
		{
			hr = m_pCharPart->CalculateVertexInflu ( m_szTrace, m_vTransUp, vNormalUp, &matVertex );
			if ( FAILED(hr) )	return;
		}
		else if ( m_pSkinPiece )
		{
			hr = m_pSkinPiece->CalculateVertexInflu ( m_szTrace, m_vTransUp, vNormalUp, &matVertex );
			if ( FAILED(hr) )	return;
		}
	}
	else if ( m_dwFlag&USE_2POINT )
	{
		if ( m_pCharPart )
		{
			hr = m_pCharPart->CalculateVertexInflu ( m_szTrace, m_vTransUp, vNormalUp, &matVertex );
			if ( FAILED(hr) )	return;

			hr = m_pCharPart->CalculateVertexInflu ( m_szTraceBack, m_vTransDown, vNormalDown, &matVertex );
			if ( FAILED(hr) )	return;
		}
		else if ( m_pSkinPiece )
		{
			hr = m_pSkinPiece->CalculateVertexInflu ( m_szTrace, m_vTransUp, vNormalUp, &matVertex );
			if ( FAILED(hr) )	return;

			hr = m_pSkinPiece->CalculateVertexInflu ( m_szTraceBack, m_vTransDown, vNormalDown, &matVertex );
			if ( FAILED(hr) )	return;
		}
	}
	

	BOOL bUse = TRUE;
	if ( (m_nAniMType==1) && (m_CurAniMType!=AN_ATTACK) )		bUse = FALSE;		// °ø°Ý½Ã ¾²ÀÓ
	else if ( (m_nAniMType==2) && (m_CurAniMType==AN_ATTACK) )	bUse = FALSE;	// °ø°Ý ¿Ü¿¡ ¾²ÀÓ

	if( m_dwFlag&USE_1POINT )
	{
		m_pSingleGroup->m_bOut_Particle = bUse;

		if ( m_vBackUp != m_vTransUp )
		{
			m_vPrevUp = m_vBackUp;
			m_vBackUp = m_vTransUp;
		}


		D3DXMATRIX	matRotate;	

		D3DXMatrixRotationY ( &matRotate, m_fTarDirection+(D3DX_PI*0.5f) );

		m_vTransUp = m_vTransUp - (vNormalUp*m_fDepthUp);
		D3DXMatrixTranslation ( &m_matTrans, m_vTransUp.x, m_vTransUp.y, m_vTransUp.z );

		D3DXMatrixMultiply( &m_pSingleGroup->m_matWorld, &matRotate, &m_matTrans );
		
		m_pSingleGroup->m_fOut_Scale = m_fScale;				// ½ºÄÉÀÏ

		if ( m_pSingleGroup )
			m_pSingleGroup->Render ( pd3dDevice );
	}
	else if( m_dwFlag&USE_2POINT )
	{
		m_pSingleGroup->m_bOut_Particle = bUse;

		if ( m_vBackUp != m_vTransUp )
		{
			m_vPrevUp = m_vBackUp;
			m_vBackUp = m_vTransUp;
		}

		m_pSingleGroup->m_vTargetPos	= m_vTransDown - (vNormalDown*m_fDepthDown);					// ¸ñÇ¥ À§Ä¡
		m_pSingleGroup->m_vStartPos		= m_vTransUp - (vNormalUp*m_fDepthUp);							// ½ÃÀÛ À§Ä¡
		m_pSingleGroup->m_vDirect		= m_pSingleGroup->m_vTargetPos - m_pSingleGroup->m_vStartPos;	// ¹æÇâ

		if( m_dwFlag&USE_REPEATMOVE )
		{
			m_vCurPos = m_pSingleGroup->m_vStartPos + ( m_pSingleGroup->m_vDirect * (sinf(m_fTime*m_fRepeatSpeed)+1.f)*0.5f);
		}
		else
		{
			if ( m_dwFlag&USE_AUTOMOVE )	m_vCurPos = m_pSingleGroup->m_vStartPos + ( m_pSingleGroup->m_vDirect * (m_fPlayTime*m_fRepeatSpeed));
			else							m_vCurPos = m_pSingleGroup->m_vStartPos;
		}
		
		m_pSingleGroup->m_matWorld._41 = m_vCurPos.x;
		m_pSingleGroup->m_matWorld._42 = m_vCurPos.y;
		m_pSingleGroup->m_matWorld._43 = m_vCurPos.z;

		if ( m_dwFlag&USE_AUTOMOVE )	m_pSingleGroup->m_bAutoMove = TRUE;
		else							m_pSingleGroup->m_bAutoMove = FALSE;

		m_pSingleGroup->m_bOut_Direct	= TRUE;			// ¹æÇâ±îÁö ³Ö¾î ÁØ´Ù.

		m_pSingleGroup->m_fOut_Scale	= m_fScale;		// ½ºÄÉÀÏ

		m_pSingleGroup->m_matOutRotate	= DxBillboardLookAtDir ( &m_pSingleGroup->m_vDirect );			// ¿ÜºÎÀÇ ¸ÅÆ®¸¯½º

		if ( m_pSingleGroup )
			m_pSingleGroup->Render ( pd3dDevice );
	}
	else if( m_dwFlag&USE_MATRIX )
	{
		// ´Üµ¶ ÀÌÆåÆ® ¹æÇâ¼ºÀ» ÁöÁ¤ÀÌ ÇÊ¿äÇÒ¶§ »ç¿ë
		m_pSingleGroup->m_bOut_Particle = bUse;

		if ( m_vBackUp != m_vTransUp )
		{
			m_vPrevUp = m_vBackUp;
			m_vBackUp = m_vTransUp;
		}


		D3DXMATRIX	matRotate, matRotateCombine ;
		D3DXMatrixIdentity( &matRotate );

		if ( m_pCharPart )
		{
			if( !m_pCharPart->m_pmcMesh->pSkinInfo )
				matRotateCombine = m_pCharPart->GetMatCombine();
			else
				matRotateCombine = matVertex;

			D3DXMatrixRotationY ( &matRotate, m_fTarDirection+(D3DX_PI*0.5f) );

			D3DXMatrixMultiply( &matRotate, &matRotate,  &matRotateCombine );
			
			matRotate._41 = 0.0f;
			matRotate._42 = 0.0f;
			matRotate._43 = 0.0f;
		}
		else
		{
			D3DXMatrixRotationY ( &matRotate, m_fTarDirection+(D3DX_PI*0.5f) );
		}
		
		m_vTransUp = m_vTransUp - (vNormalUp*m_fDepthUp);
		D3DXMatrixTranslation ( &m_matTrans, m_vTransUp.x, m_vTransUp.y, m_vTransUp.z );

		D3DXMatrixMultiply( &m_pSingleGroup->m_matWorld, &matRotate, &m_matTrans );
		
		m_pSingleGroup->m_fOut_Scale = m_fScale;				// ½ºÄÉÀÏ

		if ( m_pSingleGroup )
			m_pSingleGroup->Render ( pd3dDevice );
	}
	else if( m_dwFlag&USE_MATRIX2 )
	{
		//custom render method
		//may not fix all official effect bugs 
	
		// ´Üµ¶ ÀÌÆåÆ® ¹æÇâ¼ºÀ» ÁöÁ¤ÀÌ ÇÊ¿äÇÒ¶§ »ç¿ë
		m_pSingleGroup->m_bOut_Particle = bUse;

		if ( m_bNewMatrix )
		{
			if ( m_vBackUp != m_vTransUp )
			{
				m_vPrevUp = m_vBackUp;
				m_vBackUp = m_vTransUp;
			}

			D3DXMATRIX	matRotate1, matRotate2, matRotateCombine, matEffWorld;
			D3DXMatrixIdentity( &matRotate1 );
			
			if ( m_pCharPart )
			{
				matRotateCombine = m_pCharPart->GetMatCombine();
				if( m_pCharPart->m_pmcMesh->pSkinInfo )
					matRotateCombine = matVertex;				
			}
			else if ( m_pSkinPiece )
			{
				if ( m_pSkinPiece->m_pmcMesh &&
					m_pSkinPiece->m_pmcMesh->pSkinInfo)
				{
					matRotateCombine = matVertex;
				}else{
					D3DXMatrixIdentity( &matRotateCombine );
				}
			}

			if ( m_pCharPart || m_pSkinPiece )
			{
				D3DXMatrixRotationY ( &matRotate1, m_fTarDirection+(D3DX_PI*0.5f) );
				D3DXMatrixMultiply( &matRotateCombine, &matRotate1, &matRotateCombine );
				D3DXMatrixIdentity( &matRotate2 );

				matRotateCombine._41 = 0.0f;
				matRotateCombine._42 = 0.0f;
				matRotateCombine._43 = 0.0f;
			}
			
			m_vTransUp = m_vTransUp - (vNormalUp*m_fDepthUp);
			D3DXMatrixTranslation ( &m_matTrans, m_vTransUp.x, m_vTransUp.y, m_vTransUp.z );
			D3DXMatrixMultiply( &matEffWorld, &matRotateCombine, &m_matTrans );
			D3DXMatrixMultiply( &matEffWorld, &m_matEffLocal, &matEffWorld );
			D3DXMatrixMultiply( &m_pSingleGroup->m_matWorld, &matRotate2, &matEffWorld );

			m_pSingleGroup->m_fOut_Scale = m_fScale;

			if ( m_pSingleGroup )
				m_pSingleGroup->Render ( pd3dDevice );
		}
		else
		{
			if ( m_vBackUp != m_vTransUp )
			{
				m_vPrevUp = m_vBackUp;
				m_vBackUp = m_vTransUp;
			}

			D3DXMATRIX	matRotate1, matRotateCombine, matEffWorld;
			D3DXMatrixIdentity( &matRotate1 );

			if ( m_pCharPart )
			{
				matRotateCombine = m_pCharPart->GetMatCombine();
				if( m_pCharPart->m_pmcMesh->pSkinInfo )
					matRotateCombine = matVertex;	
			}
			else if ( m_pSkinPiece )
			{
				if ( m_pSkinPiece->m_pmcMesh &&
					m_pSkinPiece->m_pmcMesh->pSkinInfo)
				{
					matRotateCombine = matVertex;
				}else{
					D3DXMatrixIdentity( &matRotateCombine );
				}	
			}

			if ( m_pCharPart || m_pSkinPiece )
			{
				matRotateCombine._41 = 0.0f;
				matRotateCombine._42 = 0.0f;
				matRotateCombine._43 = 0.0f;
			}

			D3DXMatrixRotationY ( &matRotate1, m_fTarDirection+(D3DX_PI*0.5f) );
			m_vTransUp = m_vTransUp - (vNormalUp*m_fDepthUp);
			D3DXMatrixTranslation ( &m_matTrans, m_vTransUp.x, m_vTransUp.y, m_vTransUp.z );
			D3DXMatrixMultiply( &matEffWorld, &matRotateCombine, &m_matTrans );
			D3DXMatrixMultiply( &matEffWorld, &m_matEffLocal, &matEffWorld );
			D3DXMatrixMultiply( &m_pSingleGroup->m_matWorld, &matRotate1, &matEffWorld );

			m_pSingleGroup->m_fOut_Scale = m_fScale;

			if ( m_pSingleGroup )
				m_pSingleGroup->Render ( pd3dDevice );
		}
	}

	m_vBackUp = m_vTransUp;
}

BOOL	DxEffCharSingle::SetWeather ()
{
	if ( m_nWeather == 1 )		// ¸¼Àº³¯
	{
		if ( DxWeatherMan::GetInstance()->GetRain()->UseRain() ) return FALSE;
	}
	else if ( m_nWeather == 2 )		// ºñ¿À´Â³¯
	{
		if ( !DxWeatherMan::GetInstance()->GetRain()->UseRain() ) return FALSE;
	}

	return TRUE;
}

void DxEffCharSingle::ConvertTracePoint()
{
	if( strcmp( m_szTrace, _T("ENERGY02") ) == 0 )
	{
		StringCchCopy( m_szTrace, STRACE_NSIZE, _T("ENERGY01") );
	}
	if( strcmp( m_szTraceBack, _T("ENERGY02") ) == 0 )
	{
		StringCchCopy( m_szTraceBack, STRACE_NSIZE, _T("ENERGY01") );
	}

	if( strcmp( m_szTrace, _T("IMAGE02") ) == 0 )
	{
		StringCchCopy( m_szTrace, STRACE_NSIZE, _T("IMAGE01") );
	}
	if( strcmp( m_szTraceBack, _T("IMAGE02") ) == 0 )
	{
		StringCchCopy( m_szTraceBack, STRACE_NSIZE, _T("IMAGE01") );
	}
}

HRESULT	DxEffCharSingle::LoadFile ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr;
	DWORD dwVer, dwSize;

	SFile >> dwVer;
	SFile >> dwSize;

	//	Note : ¹öÀüÀÌ ÀÏÄ¡ÇÒ °æ¿ì. 
	//
	if ( dwVer == VERSION )
	{
		//	Note : ÀÌÆÑÆ®ÀÇ Property ¸¦ ÀúÀå.
		//
		SFile.ReadBuffer ( &m_Property, sizeof(m_Property) );

		//	Note : Device ÀÚ¿øÀ» »ý¼ºÇÑ´Ù.
		//
		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;

	}
	else if( dwVer == 0x0108 )
	{
		EFFCHAR_PROPERTY_SINGLE_108 	sProperty;
		SFile.ReadBuffer ( &sProperty, sizeof(EFFCHAR_PROPERTY_SINGLE_108) );

		m_dwFlag		= sProperty.m_dwFlag;
		m_dwPlaySlngle	= sProperty.m_dwPlaySlngle;
		m_nWeather		= sProperty.m_nWeather;						//	??..
		m_nAniMType		= sProperty.m_nAniMType;					//	?? ??	0 ??, 1 ??, 2, ?? ?
		m_fCoolTime		= sProperty.m_fCoolTime;
		m_fScale		= sProperty.m_fScale;
		m_fDepthUp		= sProperty.m_fDepthUp;
		m_fDepthDown	= sProperty.m_fDepthDown;
		m_fRepeatSpeed	= sProperty.m_fRepeatSpeed;
		m_matEffLocal	= sProperty.m_matEffLocal;
		m_bNewMatrix	= sProperty.m_bNewMatrix;

		StringCchCopy( m_szFileName, MAX_PATH, sProperty.m_szFileName );	
		StringCchCopy( m_szTrace, STRACE_NSIZE, sProperty.m_szTrace );	
		StringCchCopy( m_szTraceBack, STRACE_NSIZE, sProperty.m_szTraceBack );

		if ( m_dwFlag & USE_MATRIX )	
		{
			m_dwFlag &= ~USE_MATRIX;
			m_dwFlag |= USE_MATRIX2;
		} 

		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;
	}
	else if( dwVer == 0x0107 )
	{
		EFFCHAR_PROPERTY_SINGLE_107 	sProperty;
		SFile.ReadBuffer ( &sProperty, sizeof(EFFCHAR_PROPERTY_SINGLE_107) );

		m_dwFlag		= sProperty.m_dwFlag;
		m_dwPlaySlngle	= sProperty.m_dwPlaySlngle;
		m_nWeather		= sProperty.m_nWeather;						//	??..
		m_nAniMType		= sProperty.m_nAniMType;					//	?? ??	0 ??, 1 ??, 2, ?? ?
		m_fCoolTime		= sProperty.m_fCoolTime;
		m_fScale		= sProperty.m_fScale;
		m_fDepthUp		= sProperty.m_fDepthUp;
		m_fDepthDown	= sProperty.m_fDepthDown;
		m_fRepeatSpeed	= sProperty.m_fRepeatSpeed;
		m_matEffLocal	= sProperty.m_matEffLocal;

		StringCchCopy( m_szFileName, MAX_PATH, sProperty.m_szFileName );	
		StringCchCopy( m_szTrace, STRACE_NSIZE, sProperty.m_szTrace );	
		StringCchCopy( m_szTraceBack, STRACE_NSIZE, sProperty.m_szTraceBack );

		if ( m_dwFlag & USE_MATRIX )	
		{
			m_dwFlag &= ~USE_MATRIX;
			m_dwFlag |= USE_MATRIX2;
		} 

		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;
	}
	else if( dwVer == 0x0106 )
	{
		EFFCHAR_PROPERTY_SINGLE_106 	sProperty;
		SFile.ReadBuffer ( &sProperty, sizeof(EFFCHAR_PROPERTY_SINGLE_106) );

		m_dwFlag		= sProperty.m_dwFlag;
		m_dwPlaySlngle	= sProperty.m_dwPlaySlngle;
		m_nWeather		= sProperty.m_nWeather;						//	??..
		m_nAniMType		= sProperty.m_nAniMType;					//	?? ??	0 ??, 1 ??, 2, ?? ?
		m_fCoolTime		= sProperty.m_fCoolTime;
		m_fScale		= sProperty.m_fScale;
		m_fDepthUp		= sProperty.m_fDepthUp;
		m_fDepthDown	= sProperty.m_fDepthDown;
		m_fRepeatSpeed	= sProperty.m_fRepeatSpeed;

		StringCchCopy( m_szFileName, MAX_PATH, sProperty.m_szFileName );	
		StringCchCopy( m_szTrace, STRACE_NSIZE, sProperty.m_szTrace );	
		StringCchCopy( m_szTraceBack, STRACE_NSIZE, sProperty.m_szTraceBack );

		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;
	}
	else if( dwVer == 0x0105 )
	{
		EFFCHAR_PROPERTY_SINGLE_105 	sProperty;
		SFile.ReadBuffer ( &sProperty, sizeof(EFFCHAR_PROPERTY_SINGLE_105) );

		m_dwFlag		= sProperty.m_dwFlag;
		m_dwPlaySlngle	= sProperty.m_dwPlaySlngle;
		m_nWeather		= sProperty.m_nWeather;						//	??..
		m_nAniMType		= sProperty.m_nAniMType;					//	?? ??	0 ??, 1 ??, 2, ?? ?
		m_fCoolTime		= sProperty.m_fCoolTime;
		m_fScale		= sProperty.m_fScale;
		m_fDepthUp		= sProperty.m_fDepthUp;
		m_fDepthDown	= sProperty.m_fDepthDown;
		m_fRepeatSpeed	= sProperty.m_fRepeatSpeed;

		StringCchCopy( m_szFileName, MAX_PATH, sProperty.m_szFileName );	
		StringCchCopy( m_szTrace, STRACE_NSIZE, sProperty.m_szTrace );	
		StringCchCopy( m_szTraceBack, STRACE_NSIZE, sProperty.m_szTraceBack );

		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;
	}
	else if( dwVer == 0x0104 )
	{
		EFFCHAR_PROPERTY_SINGLE_104 	sProperty;

		//	Note : ÀÌÆÑÆ®ÀÇ Property ¸¦ ÀúÀå.
		//
		SFile.ReadBuffer ( &sProperty, sizeof(EFFCHAR_PROPERTY_SINGLE_104) );

		m_dwPlaySlngle	= sProperty.m_dwPlaySlngle;
		m_nAniMType		= sProperty.m_nAniMType;
		m_nWeather		= sProperty.m_nWeather;
		m_fScale		= sProperty.m_fScale;

		//	Ver.103 ¿¡¼­ Ãß°¡
		m_fDepthUp		= sProperty.m_fDepthUp;
		m_fDepthDown	= sProperty.m_fDepthDown;

		//	Ver.104 ¿¡¼­ Ãß°¡
		m_dwFlag		= sProperty.m_dwFlag;
		m_fCoolTime		= sProperty.m_fCoolTime;

		//	Ver.105 ¿¡¼­ Ãß°¡
		m_fRepeatSpeed	= 1.f;
		if ( sProperty.m_nType )	
		{
			m_dwFlag |= USE_2POINT;
			m_dwFlag &= ~USE_1POINT;

			m_dwFlag |= USE_AUTOMOVE;
		}
		else
		{
			m_dwFlag |= USE_1POINT;
			m_dwFlag &= ~USE_2POINT;
		}

		StringCchCopy(m_szFileName,	MAX_PATH, sProperty.m_szFileName);	
		StringCchCopy(m_szTrace, STRACE_NSIZE, sProperty.m_szTrace);	
		StringCchCopy(m_szTraceBack, STRACE_NSIZE, sProperty.m_szTraceBack);

		//	Note : Device ÀÚ¿øÀ» »ý¼ºÇÑ´Ù.
		//
		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;
	}
	else if ( dwVer == 0x0103 )
	{
		EFFCHAR_PROPERTY_SINGLE_103 	sProperty;

		//	Note : ÀÌÆÑÆ®ÀÇ Property ¸¦ ÀúÀå.
		//
		SFile.ReadBuffer ( &sProperty, sizeof(EFFCHAR_PROPERTY_SINGLE_103) );

		m_dwPlaySlngle	= sProperty.m_dwPlaySlngle;
		m_nAniMType		= sProperty.m_nAniMType;
		m_nWeather		= sProperty.m_nWeather;
		m_fScale		= sProperty.m_fScale;

		//	Ver.103 ¿¡¼­ Ãß°¡
		m_fDepthUp		= sProperty.m_fDepthUp;
		m_fDepthDown	= sProperty.m_fDepthDown;

		//	Ver.104 ¿¡¼­ Ãß°¡
		m_dwFlag		= 0L;
		m_fCoolTime		= 10.f;

		//	Ver.105 ¿¡¼­ Ãß°¡
		m_fRepeatSpeed	= 1.f;
		if ( sProperty.m_nType )	
		{
			m_dwFlag |= USE_2POINT;
			m_dwFlag &= ~USE_1POINT;

			m_dwFlag |= USE_AUTOMOVE;
		}
		else
		{
			m_dwFlag |= USE_1POINT;
			m_dwFlag &= ~USE_2POINT;
		}

		StringCchCopy(m_szFileName,	MAX_PATH, sProperty.m_szFileName);	
		StringCchCopy(m_szTrace, STRACE_NSIZE, sProperty.m_szTrace);	
		StringCchCopy(m_szTraceBack, STRACE_NSIZE, sProperty.m_szTraceBack);

		//	Note : Device ÀÚ¿øÀ» »ý¼ºÇÑ´Ù.
		//
		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;
	}
	else if ( dwVer == 0x0102 )
	{
		EFFCHAR_PROPERTY_SINGLE_102		sProperty;

		//	Note : ÀÌÆÑÆ®ÀÇ Property ¸¦ ÀúÀå.
		//
		SFile.ReadBuffer ( &sProperty, sizeof(EFFCHAR_PROPERTY_SINGLE_102) );

		m_dwPlaySlngle	= sProperty.m_dwPlaySlngle;
		m_nAniMType		= sProperty.m_nAniMType;
		m_nWeather		= sProperty.m_nWeather;
		m_fScale		= sProperty.m_fScale;

		//	Ver.103 ¿¡¼­ Ãß°¡
		m_fDepthUp		= 0.5f;
		m_fDepthDown	= 0.5f;

		//	Ver.104 ¿¡¼­ Ãß°¡
		m_dwFlag		= 0L;
		m_fCoolTime		= 10.f;

		//	Ver.105 ¿¡¼­ Ãß°¡
		m_fRepeatSpeed	= 1.f;
		if ( sProperty.m_nType )	
		{
			m_dwFlag |= USE_2POINT;
			m_dwFlag &= ~USE_1POINT;

			m_dwFlag |= USE_AUTOMOVE;
		}
		else
		{
			m_dwFlag |= USE_1POINT;
			m_dwFlag &= ~USE_2POINT;
		}

		StringCchCopy(m_szFileName,	MAX_PATH, sProperty.m_szFileName);	
		StringCchCopy(m_szTrace, STRACE_NSIZE, sProperty.m_szTrace);	
		StringCchCopy(m_szTraceBack, STRACE_NSIZE, sProperty.m_szTraceBack);

		//	Note : Device ÀÚ¿øÀ» »ý¼ºÇÑ´Ù.
		//
		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;
	}
	else if ( dwVer == 0x0101 )
	{
		EFFCHAR_PROPERTY_SINGLE_101		sProperty;

		//	Note : ÀÌÆÑÆ®ÀÇ Property ¸¦ ÀúÀå.
		//
		SFile.ReadBuffer ( &sProperty, sizeof(EFFCHAR_PROPERTY_SINGLE_101) );

		m_nWeather	= sProperty.m_nWeather;						//	³¯¾¾..
		m_nAniMType = 0;					//	°ø°Ý Å¸ÀÓ
		m_fScale = 1.f;

		//	Ver.103 ¿¡¼­ Ãß°¡
		m_fDepthUp		= 0.5f;
		m_fDepthDown	= 0.5f;

		//	Ver.104 ¿¡¼­ Ãß°¡
		m_dwFlag		= 0L;
		m_fCoolTime		= 10.f;

		//	Ver.105 ¿¡¼­ Ãß°¡
		m_fRepeatSpeed	= 1.f;
		if ( sProperty.m_nType )	
		{
			m_dwFlag |= USE_2POINT;
			m_dwFlag &= ~USE_1POINT;

			m_dwFlag |= USE_AUTOMOVE;
		}
		else
		{
			m_dwFlag |= USE_1POINT;
			m_dwFlag &= ~USE_2POINT;
		}

		StringCchCopy(m_szFileName,	MAX_PATH, sProperty.m_szFileName);	
		StringCchCopy(m_szTrace, STRACE_NSIZE, sProperty.m_szTrace);	
		StringCchCopy(m_szTraceBack, STRACE_NSIZE, sProperty.m_szTraceBack);

		//	Note : Device ÀÚ¿øÀ» »ý¼ºÇÑ´Ù.
		//
		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;
	}
	else if ( dwVer == 0x0100 )
	{
		EFFCHAR_PROPERTY_SINGLE_100		sProperty;

		//	Note : ÀÌÆÑÆ®ÀÇ Property ¸¦ ÀúÀå.
		//
		SFile.ReadBuffer ( &sProperty, sizeof(EFFCHAR_PROPERTY_SINGLE_100) );

		m_nWeather	= sProperty.m_nWeather;						//	³¯¾¾..
		m_nAniMType = 0;					//	°ø°Ý Å¸ÀÓ
		m_fScale = 1.f;

		//	Ver.103 ¿¡¼­ Ãß°¡
		m_fDepthUp		= 0.5f;
		m_fDepthDown	= 0.5f;

		//	Ver.104 ¿¡¼­ Ãß°¡
		m_dwFlag		= 0L;
		m_fCoolTime		= 10.f;

		//	Ver.105 ¿¡¼­ Ãß°¡
		m_fRepeatSpeed	= 1.f;
		if ( sProperty.m_nType )	
		{
			m_dwFlag |= USE_2POINT;
			m_dwFlag &= ~USE_1POINT;

			m_dwFlag |= USE_AUTOMOVE;
		}
		else
		{
			m_dwFlag |= USE_1POINT;
			m_dwFlag &= ~USE_2POINT;
		}

		StringCchCopy(m_szFileName,	MAX_PATH, sProperty.m_szFileName);	
		StringCchCopy(m_szTrace, STRACE_NSIZE, sProperty.m_szTrace);	
		StringCchCopy(m_szTraceBack, STRACE_NSIZE, sProperty.m_szTraceBack);

		//	Note : Device ÀÚ¿øÀ» »ý¼ºÇÑ´Ù.
		//
		hr = Create ( pd3dDevice );
		if ( FAILED(hr) )	return hr;
	}
	else
	{
		CDebugSet::ErrorVersion( "DxEffCharSingle::LoadFile", SFile.GetFileName(), dwVer );

		//	Note : ¹öÀüÀÌ Æ²¸± °æ¿ì¿¡´Â ÆÄÀÏ¿¡ ¾²¿©Áø DATA¿µ¿ªÀ» °Ç´õ ¶ç´Â ÀÛ¾÷À» ÁøÇà.
		//
		SFile.SetOffSet ( SFile.GetfTell()+dwSize );
		
		return E_FAIL;
	}

	return S_OK;
}

HRESULT	DxEffCharSingle::SaveFile ( basestream &SFile )
{
	SFile << TYPEID;
	SFile << VERSION;

	//	Note : DATAÀÇ »çÀÌÁî¸¦ ±â·ÏÇÑ´Ù. Load ½Ã¿¡ ¹öÀüÀÌ Æ²¸± °æ¿ì »ç¿ëµÊ.
	//
	SFile << (DWORD) ( sizeof(m_Property) );

	//	Note : ÀÌÆÑÆ®ÀÇ Property ¸¦ ÀúÀå.
	//
	SFile.WriteBuffer ( &m_Property, sizeof(m_Property) );

	return S_OK;
}

