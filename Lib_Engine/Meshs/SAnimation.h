
#pragma once

#include <GASSERT.h>

#include <map>
#include <list>
#include <string>
#include <vector>

#include "../Common/SerialFile.h"
#include "./DxBoneCollector.h"

#include "./SAnimationInfo.h"

//struct DxBoneTrans;
//class DxEffAniData;
//class DxAniScale;

struct SAnimation
{
	enum { VERSION = 0x0103, };

	// animation information
	SPositionKey	*m_pPositionKeys;	//	�̵� ����Ű.
	UINT			m_cPositionKeys;
	
	SRotateKey		*m_pRotateKeys;		//	ȸ�� ����Ű.
	UINT			m_cRotateKeys;
	
	SScaleKey		*m_pScaleKeys;		//	ũ�� ����Ű.
	UINT			m_cScaleKeys;
	
	SMatrixKey		*m_pMatrixKeys;		// Matrix
	UINT			m_cMatrixKeys;

	SQuatPosKey*	m_pQuatPosKeys;		// Quaternion �׽�Ʈ �� ���̴�..  �ϼ��Ǹ� Matrix�� ��� �� �� ����.
	UINT			m_cQuatPosKeys;
	D3DXQUATERNION*	m_pQuatOrigRot;		// ������ ȸ��.. ���� �����̴�. MIX �ø� ����Ѵ�. ~!!

	TSTRING		m_strBone;
	DxBoneTrans		*pBoneToAnimate;	//	����� BONE �� ����.

	DWORD			m_dwCurKey;
	float			m_fDivFullTime;		// Opitimize - ������ �� �� 1.f/m_pMatrixKeys[m_cMatrixKeys-1].fTime
	float			m_fMatrixKeys;		// Opitimize - ������ �� �� m_cMatrixKeys

	SAnimation() :
			m_pPositionKeys(NULL),
			m_cPositionKeys(0),
			m_pScaleKeys(NULL),
			m_cScaleKeys(0),
			m_pRotateKeys(NULL),
			m_cRotateKeys(0),
			m_pMatrixKeys(NULL),
			m_cMatrixKeys(0),
			m_pQuatPosKeys(NULL),
			m_cQuatPosKeys(0),
			m_pQuatOrigRot(NULL),

			pBoneToAnimate(NULL),
			m_dwCurKey(0),
			m_fDivFullTime(0.f),
			m_fMatrixKeys(0.f)
	{
	}

	~SAnimation()
	{
		SAFE_DELETE_ARRAY(m_pPositionKeys);
		SAFE_DELETE_ARRAY(m_pRotateKeys);
		SAFE_DELETE_ARRAY(m_pScaleKeys);
		SAFE_DELETE_ARRAY(m_pMatrixKeys);
		SAFE_DELETE_ARRAY(m_pQuatPosKeys);
		SAFE_DELETE_ARRAY(m_pQuatOrigRot);

		// do NOT delete pToAnimate
	}

	void SetTime ( float fTime, float fWeight, BOOL bFirst );
	void SetMix ( float fTime );

	UINT GetThisKey ( float fTime ) const;
	const SMatrixKey* GetMapThisKey ( float fGlobalTime ) const;

	void SetMatrix ( UINT iKey );
	void SetMatrix ( const SMatrixKey* pMatrixKey )	{ pBoneToAnimate->matRot = pMatrixKey->mat; }

	void ConvertMatToQuat();

	HRESULT LoadFromFile ( CSerialFile &SFile, const DxSkeleton* pSkeleton );
	HRESULT Load_0100( CSerialFile &SFile, const DxSkeleton* pSkeleton );
	HRESULT Load_0101( CSerialFile &SFile, const DxSkeleton* pSkeleton );
	HRESULT Load_0102( CSerialFile &SFile, const DxSkeleton* pSkeleton );
	HRESULT Load_0103( CSerialFile &SFile, const DxSkeleton* pSkeleton );
	HRESULT SaveToFile ( CSerialFile &SFile );
};



// �� �����ӿ��� ������ ���� �ִϸ��̼� ����
struct SAnimContainer : public SANIMCONINFO
{
public:
	enum 
	{ 
		VERSION			= 0x0200, 
		VERSION_ENCRYPT = 0x0200, 
	};

	const static TCHAR szFILETYPE[];

	typedef std::list<SAnimation*>		SANILIST;
	typedef SANILIST::iterator			SANILIST_ITER;

protected:
	DWORD					m_dwRefCount;

	bool					m_bLOAD;
	bool					m_bVALID;
	SANILIST				m_listAnimation;	// ��ü ���� �ִϸ��̼� ��.
	SANILIST				m_listAniUPBODY;	// ��ü ���� �ִϸ��̼� ��.	// Ver.101���� �� ��.

public:
	DxSkeleton*				m_pSkeleton;		// �� ������.

public:
	DWORD AddRef()		{ return m_dwRefCount++; }
	DWORD Release()		{ if (m_dwRefCount!=0) m_dwRefCount--; return m_dwRefCount; }

protected:
	HRESULT LoadAnimationSet ( LPDIRECTXFILEDATA pxofobjCur );
	HRESULT LoadAnimation ( LPDIRECTXFILEDATA pxofobjCur );

public:
	HRESULT CreateAnimationData ( SANIMCONINFO &AnimInfo, LPDIRECT3DDEVICEQ pd3dDevice, bool bREPRESH=false );
	BOOL	IsValidateANI();

public:
	HRESULT SaveToFile ();

public:
	//	�⺻ ���� ����.
	HRESULT SetInfo ( SANIMCONINFO &sAnimInfo, LPDIRECT3DDEVICEQ pd3dDevice );

	//	���Ͽ��� �б�.
	HRESULT LoadAnimFromFile ( const TSTRING &strFilePath );
	void SetAnimFromList ( SANILIST &listANI, SANILIST &listANIUPBODY );

	//	���Ͽ��� �б�. ( �������. )
	static HRESULT LoadAnimFromFile ( const TSTRING &strFilePath, const DxSkeleton* pSkeleton, SANILIST &listANI, SANILIST &listANIUPBODY );

	HRESULT  Load_0100( CSerialFile &SFile );
	HRESULT  Load_0101( CSerialFile &SFile );
	HRESULT  Load_0102( CSerialFile &SFile );
	HRESULT  Load_0103( CSerialFile &SFile );
	HRESULT  Load_0104( CSerialFile &SFile );
	HRESULT  Load_0200( CSerialFile &SFile );

	//	������� 
	static HRESULT  Load_0100( CSerialFile &SFile, const DxSkeleton* pSkeleton, SANILIST &listANI, SANILIST &listANIUPBODY );
	static HRESULT  Load_0101( CSerialFile &SFile, const DxSkeleton* pSkeleton, SANILIST &listANI, SANILIST &listANIUPBODY );
	static HRESULT  Load_0102( CSerialFile &SFile, const DxSkeleton* pSkeleton, SANILIST &listANI, SANILIST &listANIUPBODY );
	static HRESULT  Load_0103( CSerialFile &SFile, const DxSkeleton* pSkeleton, SANILIST &listANI, SANILIST &listANIUPBODY );
	static HRESULT  Load_0104( CSerialFile &SFile, const DxSkeleton* pSkeleton, SANILIST &listANI, SANILIST &listANIUPBODY );
	static HRESULT  Load_0200( CSerialFile &SFile, const DxSkeleton* pSkeleton, SANILIST &listANI, SANILIST &listANIUPBODY );

public:
	bool UpdateTime ( float fCurTime, float fWeight=1.f, BOOL bFirst=TRUE, EMBODY emBody=EMBODY_DEFAULT );
	bool UpdateMix ( float fCurMixTime );
	void UpdateBoneScale( float fWeight, BOOL bFirst, float fTime );

public:
	SAnimContainer();
	virtual ~SAnimContainer();
};
typedef SAnimContainer* PSANIMCONTAINER;
