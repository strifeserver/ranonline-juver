#pragma once

#include <list>

class DxEffAni;
class DxSkinChar;
/*ABL system, Juver, 2017/05/29 */
class DxAttBone;
class DxAttBoneRender;

/*vehicle system, Juver, 2017/08/03 */
class DxVehicle;

struct SKINEFFDATA;

//	Note : "class DxEffSingleGroup"�ν��Ͻ����� (��, ���� �����ϰ� �ִ� "����Ʈ �׷�"��ü���� ���� ��Ƽ� �����ϰ�
//			�̸� ���۽�Ű�� ������ �Ѵ�. ( Update & Render ) ���� �̵��� �Ҹ���������� üũ���� �Ҹ�ǰ� �Ѵ�.
//
class DxEffAniPlayer
{
protected:
	typedef std::list<DxEffAni*>		EFFLIST;
	typedef EFFLIST::iterator			EFFLIST_ITER;

protected:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;

	float				m_fTimer;
	EFFLIST				m_listAni;		// Ani Key�� ���� ȿ���� ����.
	EFFLIST				m_listOneSet;	// 1���� ȿ���� ����.

protected:
	void	CreateEff ( DxEffAniData* pEff, PSANIMCONTAINER pAnimContainer );

public:
	void	CheckCreateEff( PSANIMCONTAINER pAnimContainer );										// Note : 1�� ������ �������� ����.
	void	CheckCreateEff( PSANIMCONTAINER pAnimContainer, int dwPrevFrame, DWORD dwCurKeyTime );	// Note : �Ź� Ani Key�� �� �� Eff ����.
	void	ResetEff( PSANIMCONTAINER pAnimContainer );

public:
	DWORD	GetAmount ()				{ return DWORD(m_listAni.size()); }
	
	void	SetTime ( float fTimer )	{ m_fTimer = fTimer; }
	float	GetTime ()					{ return m_fTimer; }

	HRESULT RemoveAllEff ();
	HRESULT DeleteEff ( const TCHAR* szFile );

public:
	HRESULT FrameMove ( PSANIMCONTAINER pAnimContainer, float fTime, float fElapsedTime, SKINEFFDATA& sSKINEFFDATA );
	HRESULT	Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxSkinChar* pSkinChar, const D3DXMATRIX& matCurPos );

	/*ABL system, Juver, 2017/05/29 */
	HRESULT	Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxAttBone* pAttBone, const D3DXMATRIX& matCurPos );
	HRESULT	Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxAttBoneRender* pAttBone, const D3DXMATRIX& matCurPos );

	/*vehicle system, Juver, 2017/08/03 */
	HRESULT	Render ( const LPDIRECT3DDEVICEQ pd3dDevice, DxVehicle* pVehicle, const D3DXMATRIX& matCurPos );

public:
	HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RestoreDeviceObjects ();

	HRESULT InvalidateDeviceObjects ();
	HRESULT DeleteDeviceObjects ();

public:
	DxEffAniPlayer (void);

public:
	~DxEffAniPlayer (void);
};
