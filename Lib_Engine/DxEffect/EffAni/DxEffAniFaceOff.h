#pragma once

#include "DxEffAni.h"
#include "DxMethods.h"

#include <list>

class DxSkinChar;
/*ABL system, Juver, 2017/05/29 */
class DxAttBone;
class DxAttBoneRender;

/*vehicle system, Juver, 2017/08/03 */
class DxVehicle;

struct EFF_PROPGROUP;
class DxEffSingleGroup;

struct EFFANI_PROPERTY_FACEOFF : public EFFANI_PROPERTY
{
	TCHAR		m_szTexture[32];	// 텍스쳐 종류.

	EFFANI_PROPERTY_FACEOFF ()
	{
		StringCchCopy( m_szTexture, 32, _T("") );
	}
};

class DxEffAniData_FaceOff : public DxEffAniData
{
public:
	static DWORD		VERSION;
	static DWORD		TYPEID;
	static TCHAR		NAME[64];

public:
	virtual DWORD GetTypeID ()		{ return TYPEID; }
	virtual DWORD GetFlag ()		{ return NULL; }
	virtual const TCHAR* GetName ()	{ return NAME; }

public:
	union
	{
		struct
		{
			EFFANI_PROPERTY_FACEOFF		m_Property;
		};

		struct
		{
			TCHAR		m_szTexture[32];	// 텍스쳐 종류.
		};
	};

public:
	BOOL				m_bCreated;
	void	SetCreated ( BOOL bCreated )	{ m_bCreated = bCreated; }

public:
	BOOL CheckEff ( DWORD dwCurKeyTime, DWORD dwPrevFrame );

public:
	virtual void SetProperty ( EFFANI_PROPERTY *pProperty )
	{
		m_Property = *((EFFANI_PROPERTY_FACEOFF*)pProperty);
	}
	
	virtual EFFANI_PROPERTY* GetProperty ()
	{
		return &m_Property;
	}

public:
	virtual DxEffAni* NEWOBJ( SAnimContainer* pAnimContainer );		//	Note : 이팩트 생성자.
	virtual HRESULT LoadFile ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT SaveFile ( CSerialFile &SFile );

public:
	DxEffAniData_FaceOff () : 
		DxEffAniData(),
		m_bCreated(FALSE)
	{
	}
};

class DxEffAniFaceOff : public DxEffAni
{
public:
	TCHAR		m_szTexture[32];	// 텍스쳐 종류.

private:
	LPDIRECT3DTEXTUREQ		m_pTexture;

protected:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;

	LPDIRECT3DSTATEBLOCK9	m_pSavedBaseSB;
	LPDIRECT3DSTATEBLOCK9	m_pEffectBaseSB;

public:
	static HRESULT CreateDevice ( LPDIRECT3DDEVICEQ pd3dDevice );
	static HRESULT ReleaseDevice ( LPDIRECT3DDEVICEQ pd3dDevice );

public:
	virtual HRESULT OneTimeSceneInit ();
	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT InvalidateDeviceObjects ();
	virtual HRESULT DeleteDeviceObjects ();
	virtual HRESULT FinalCleanup ();

public:
	virtual HRESULT FrameMove ( float fTime, float fElapsedTime );
	virtual HRESULT	Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxSkinChar* pSkinChar, const D3DXMATRIX& matCurPos );

	/*ABL system, Juver, 2017/05/29 */
	virtual HRESULT	Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxAttBone* pAttBone, const D3DXMATRIX& matCurPos );
	virtual HRESULT	Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxAttBoneRender* pAttBone, const D3DXMATRIX& matCurPos );

	/*vehicle system, Juver, 2017/08/02 */
	virtual HRESULT	Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxVehicle* pVehicle, const D3DXMATRIX& matCurPos );

public:
	virtual BOOL IsHeadDrawChild();

public:
	DxEffAniFaceOff(void);
	~DxEffAniFaceOff(void);
};

