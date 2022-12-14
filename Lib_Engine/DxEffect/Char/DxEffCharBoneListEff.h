#pragma once

#include <vector>
#include "CMemPool.h"
#include "DxVertexFVF.h"
#include "DxSequenceUV.h"

#include "DxEffChar.h"

#define	BONELISTEFF_TEXNAME_SIZE	64
#define	MAX_FACE					500

struct EFF_PROPGROUP;
class DxEffSingleGroup;

#define	USE_REMAIN		0x0001	// 파티클을 남긴다.
#define	USE_ABSOLUTE	0x0002	// 절대좌표 : 상대좌표
#define	USE_RANDOMRANGE	0x0004	// 랜덤한 범위
#define	USE_SEQUENCE	0x0008	// 시퀀스 사용
#define	USE_ROTATE		0x0010	// 회전 사용

#define	USE_PLAY		0x0001	// 절대좌표일 경우 Play 하는지 안 하는지 알려줌.
#define	USE_POS1		0x0002	// 위치 1개 얻음.

struct EFFCHAR_PROPERTY_BONELISTEFF_100
{
	DWORD		m_dwFlag;
	DWORD		m_dwParticlePec;	// 초당 나오는 파티클 갯수
	DWORD		m_dwColor;
	D3DXVECTOR2	m_vLife;			// 최소,최대
	D3DXVECTOR2	m_vRotate;			// 최소,최대
	D3DXVECTOR2	m_vVelocity;		// 최소,최대
	D3DXVECTOR3 m_vSize;			// 최소,최대,변화률
	DWORD		m_dwSequenceCol;
	DWORD		m_dwSequenceRow;
	float		m_fCreateLength;	// 생성 될때 일정거리만큼 떨어뜨려준다.
	char		m_szTexture[BONELISTEFF_TEXNAME_SIZE];

	EFFCHAR_PROPERTY_BONELISTEFF_100()
	{
		SecureZeroMemory( m_szTexture, sizeof(char)*BONELISTEFF_TEXNAME_SIZE );
	}
};

struct EFFCHAR_PROPERTY_BONELISTEFF : public EFFCHAR_PROPERTY
{
	DWORD		m_dwFlag;
	DWORD		m_dwParticlePec;	// 초당 나오는 파티클 갯수
	DWORD		m_dwColor;
	DWORD		m_dwSequenceCol;
	DWORD		m_dwSequenceRow;
	float		m_fCreateLength;	// 생성 될때 일정거리만큼 떨어뜨려준다.
	D3DXVECTOR2	m_vLife;			// 최소,최대
	D3DXVECTOR2	m_vRotate;			// 최소,최대
	D3DXVECTOR2	m_vVelocity;		// 최소,최대
	D3DXVECTOR3 m_vSize;			// 최소,최대,변화률
	char		m_szTexture[BONELISTEFF_TEXNAME_SIZE];

	EFFCHAR_PROPERTY_BONELISTEFF() :
		m_dwFlag(0L),
		m_dwParticlePec(5),
		m_dwColor(0xffffffff),
		m_dwSequenceCol(8),
		m_dwSequenceRow(8),
		m_fCreateLength(1.f),
		m_vLife(2.f,3.f),
		m_vRotate(1.f,5.f),
		m_vVelocity(0.5f,1.f),
		m_vSize(5.f,8.f,1.f)
		
	{
		m_dwFlag = 0L;

		SecureZeroMemory( m_szTexture, sizeof(char)*BONELISTEFF_TEXNAME_SIZE );

		StringCchCopy( m_szTexture, BONELISTEFF_TEXNAME_SIZE, "" );
	}
};

struct DXCUSTOMBONE
{
	std::string		strBoneName;
	DxBoneTrans*	pBoneTran;
	BOOL			bVertex;
	D3DXVECTOR3		vVertex;

	DXCUSTOMBONE() :
		pBoneTran(NULL),
		bVertex(FALSE),
		vVertex(0.f,0.f,0.f)
	{
		strBoneName = "";
	}

	void RenderCount( DWORD nCount, const D3DXMATRIX& matWorld );

	void Save( basestream& SFile );
	void Load( basestream& SFile );
};
typedef std::list<DXCUSTOMBONE>		LISTCUSTOMBONE;
typedef LISTCUSTOMBONE::iterator	LISTCUSTOMBONE_ITER;

class DxEffCharBoneListEff : public DxEffChar
{
public:
	static DWORD		TYPEID;
	static DWORD		VERSION;
	static char			NAME[MAX_PATH];

	virtual DWORD GetTypeID ()		{ return TYPEID; }
	virtual DWORD GetFlag ()		{ return NULL; }
	virtual const char* GetName ()	{ return NAME; }

protected:
	union
	{
		struct
		{
			EFFCHAR_PROPERTY_BONELISTEFF m_Property;
		};
		
		struct
		{
			DWORD		m_dwFlag;
			DWORD		m_dwParticlePec;	// 초당 나오는 파티클 갯수
			DWORD		m_dwColor;
			DWORD		m_dwSequenceCol;
			DWORD		m_dwSequenceRow;
			float		m_fCreateLength;	// 생성 될때 일정거리만큼 떨어뜨려준다.
			D3DXVECTOR2	m_vLife;			// 최소,최대
			D3DXVECTOR2	m_vRotate;			// 최소,최대
			D3DXVECTOR2	m_vVelocity;		// 최소,최대
			D3DXVECTOR3 m_vSize;			// 최소,최대,변화률
			char		m_szTexture[BONELISTEFF_TEXNAME_SIZE];
		};
	};

public:
	virtual void SetProperty ( EFFCHAR_PROPERTY *pProperty )
	{
		m_Property = *((EFFCHAR_PROPERTY_BONELISTEFF*)pProperty);
	}
	
	virtual EFFCHAR_PROPERTY* GetProperty ()
	{
		return &m_Property;
	}

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
	virtual void	RenderEff( LPDIRECT3DDEVICEQ pd3dDevice, LPD3DXMATRIX pMatrix, const float fScale );

	virtual DWORD GetStateOrder () const						{ return EMEFFSO_SINGLE_EFF; }

	// Note : 선택된 본을 알기 위함.
private:
	DxBoneTrans*	m_pBoneTran;

	// Note : 전체 디퓨즈의 데이터
	//		작은 파티클로 넣기 위함.
public:
	struct DXDATA
	{
		DWORD dwColorR;
		DWORD dwColorG;
		DWORD dwColorB;
		DWORD dwColorBASE;
	};

private:
	DXDATA m_sPlayData;

	// Note : DXPOSDELTA
private:
	struct DXPOSDELTA
	{
		std::string		strBoneName;	// SAVE 
		DxBoneTrans*	pBoneTran;		// ----
		BOOL			bVertex;		// SAVE	// 본위치가 아닌 본에 영향받은 위치를 사용할 것인가 ?
		D3DXVECTOR3		vPos;			// ----	// 위치
		D3DXVECTOR3		vBase;			// SAVE // 기본 위치
		float			fRate;			// SAVE // 자신의 위치 값

		void Save( basestream& SFile );
		void Load( basestream& SFile );

		DXPOSDELTA() :
			pBoneTran(NULL),
			bVertex(FALSE),
			vPos(0.f,0.f,0.f),
			vBase(0.f,0.f,0.f),
			fRate(0.f)			
		{
			strBoneName = "";
		}
	};
	typedef std::vector<DXPOSDELTA>	VECPOSITION;

	// Note : DXPARTICLE
private:
	struct DXPARTICLE
	{
		// Note : 고정 값
		float		m_fLife;		// 이 오브젝트의 생명.	// 알파는 생명으로써 빼어주도록 하자.	삶 으로서 속도를 결정한다.
		D3DXVECTOR3	m_vPosOffSet;	// 일정거리를 띄운다.

		//Note : 변화 하는 값
		float		m_fTime;			// 현재 생명
		D3DXVECTOR3 m_vPos;				// 현재 위치.
		float		m_fSize;			// 크기
		float		m_fRotate;			// 회전값
		DWORD		m_dwColor;			// 최종 컬러
		float		m_fRate;			// 생명의 비율
		DWORD		m_dwSequenceCount;	// 시퀀스의 Count

		// Note : 변화를 위해 저장해 놓는 값.
		float		m_fSizeBase;
		float		m_fSizeDiff;
		float		m_fRotateVel;

		// Note : 절대좌표의 퍼짐으로 작동될 경우	// 절대좌표일때만 초기화 함.
		BOOL		m_dwFlag;
		float		m_fVelocity;
		float		m_fFirstPosRate;
		D3DXVECTOR3 m_vFirstPos;
		D3DXVECTOR3	m_vDirDiff;

		DXPARTICLE* m_pNext;

		void ComputeCreatePos( VECPOSITION& vecData );
		BOOL FrameMove( EFFCHAR_PROPERTY_BONELISTEFF& sProp, DXDATA& sData, VECPOSITION& vecData, const float fElpasedTime );
		BOOL FrameMoveAbsolute( EFFCHAR_PROPERTY_BONELISTEFF& sProp, DXDATA& sData, VECPOSITION& vecData, const float fElpasedTime );

		DXPARTICLE() :
			m_fTime(0.f),
			m_vPos(0.f,0.f,0.f),
			m_fRotate(0.f),
			m_dwColor(0L),
			m_fRate(0.f),
			m_dwSequenceCount(0L),
			m_fSizeBase(0.f),
			m_fSizeDiff(0.f),
			m_fRotateVel(0.f),
			m_pNext(NULL)
		{
		}
	};
	typedef CMemPool<DXPARTICLE> PARTICLEPOOL;

public:
	static PARTICLEPOOL*			m_pParticlePool;
	static VERTEXCOLORTEX2			m_pVertices[MAX_FACE*4];

private:
	DXPARTICLE*				m_pParticleHEAD;
	LPDIRECT3DTEXTUREQ		m_pTexture;

private:
	float	m_fElapsedTime;
	int		m_nPrevKeyTime;
	float	m_fParticleADD;	// Particle을 더함.

	float	m_fSizeDiff;
	float	m_fLifeDiff;
	float	m_fRotateDiff;
	float	m_fVelocityDiff;
	DxSequenceUV	m_sSequenceUV;

private:
	void ComputeCreatePos();							// 애니메이션이 바뀔때만 동작.
	void CreateFrameMoveParticle( float fElapsedTime );	// 
	void DxCreateParticle( DWORD dwNUM );				// 새로운 파티클 생성.

	// Note : 렌더시.
private:
	VECPOSITION		m_vecPosition;

	// Note : Edit 시에 쓰이는 것
	LISTCUSTOMBONE	m_listCustomBone;

private:
	void UpdateVECPOSION();

	// Note : Edit에서 사용하는 함수.
public:
	void InsertBone( const char* szName );
	BOOL DeleteBone( const DWORD dwIndex );
	int DataUp( DWORD dwIndex );			// Note : Return 값으로 선택되었던 위치를 가르킨다.
	int DataDown( DWORD dwIndex );			// Note : Return 값으로 선택되었던 위치를 가르킨다.

	std::string GetBoneString( const DWORD dwIndex );
	void SetCheckBone( const DWORD dwIndex );					// Bone을 선택한다.
	BOOL GetEnableBonePos();									// Bone Pos가 Enable 되었는지 알려준다.
	D3DXVECTOR3 GetInfluencePosition();							// Bone 옵션의 vVertex가 무엇인지 알려준다.
	D3DXMATRIX GetInfluenceMatrix();							// Bone Matrix를 돌려준다.
	D3DXVECTOR3 SetChangeMatrix( const D3DXMATRIX& matWorld );	// 변한 Matrix를 가지고 원래의 위치값을 얻어온다.
	void		SetCheckBoneOffSetPos( BOOL bEnable );			// Bone 옵션의 bVertex의 값을 수정한다.
	void	ResetLocalPos();

	DWORD GetCustomBoneSize()								{ return (DWORD)m_listCustomBone.size(); }

	BOOL EditApplyResetData();

	// Note : Clone, Save, Load
public:
	virtual DxEffChar* CloneInstance ( LPDIRECT3DDEVICEQ pd3dDevice, DxCharPart* pCharPart, DxSkinPiece* pSkinPiece );

	virtual HRESULT LoadFile ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT SaveFile ( basestream &SFile );

public:
	DxEffCharBoneListEff(void);
	~DxEffCharBoneListEff(void);
};


