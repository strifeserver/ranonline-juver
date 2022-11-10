
#pragma once

#include "./DxAniKeys.h"
#include "./CharacterSound.h"
#include "./DxPieceDefine.h"
#include "./DxAniBoneScale.h"
#include "../DxEffect/EffAni/DxEffAni.h"

enum EMANICONINFO
{
	ACF_NEWINFO		= 0x0001,
	ACF_LOOP		= 0x0010,
	ACF_UPBODY		= 0x0100,	// UPBODY ����.		// UP DOWN �� ���� �ȵ� ���� ����Ʈ�� ��ü��.
	ACF_DOWNBODY	= 0x0200,	// UP�� ���� DOWN�� ���� �� ��� UP�� DOWN�� ������ �޾ƾ� �Ѵ�.
	ACF_SZNAME		= 128,
	ACF_DIV			= 8,
	ACF_STRIKE		= 9,
};

struct SANIMCONINFO_101
{
	TCHAR			m_szName[ACF_SZNAME];		//	�̸�.
	TCHAR			m_szSkeletion[ACF_SZNAME];	//	���ٱ� �̸�.

	DWORD			m_dwFlag;					//	��Ÿ �Ӽ�.
	DWORD			m_dwSTime;					//	���� �ð�.
	DWORD			m_dwETime, m_dwETimeOrig;	//	�� �ð�.
	DWORD			m_UNITTIME;					//	Ű���� �ð�.

	EMANI_MAINTYPE	m_MainType;
	EMANI_SUBTYPE	m_SubType;

	WORD			m_wDivCount;				//	���ϸ��̼� ���� Ű ����.
	WORD			m_wDivFrame[ACF_DIV];		//	���ϸ��̼� ���� Ű��..

	SANIMCONINFO_101()
	{
		memset( m_szName, 0, sizeof(TCHAR)*ACF_SZNAME );
		memset( m_szSkeletion, 0, sizeof(TCHAR)*ACF_SZNAME );
	}
};

struct SANIMCONINFO_102
{
	TCHAR			m_szName[ACF_SZNAME];		//	�̸�.
	TCHAR			m_szSkeletion[ACF_SZNAME];	//	���ٱ� �̸�.

	DWORD			m_dwFlag;					//	��Ÿ �Ӽ�.
	DWORD			m_dwSTime;					//	���� �ð�.
	DWORD			m_dwETime, m_dwETimeOrig;	//	�� �ð�.
	DWORD			m_UNITTIME;					//	Ű���� �ð�.

	EMANI_MAINTYPE	m_MainType;
	EMANI_SUBTYPE	m_SubType;

	WORD			m_wDivCount;				//	���ϸ��̼� ���� Ű ����.
	WORD			m_wDivFrame[ACF_DIV];		//	���ϸ��̼� ���� Ű��..

	SChaSoundData_102	m_ChaSoundData;				//	���� ����Ÿ

	SANIMCONINFO_102()
	{
		memset( m_szName, 0, sizeof(TCHAR)*ACF_SZNAME );
		memset( m_szSkeletion, 0, sizeof(TCHAR)*ACF_SZNAME );
	}
};

struct SANIMCONINFO_103
{
	TCHAR			m_szName[ACF_SZNAME];
	TCHAR			m_szSkeletion[ACF_SZNAME];

	DWORD			m_dwFlag;
	DWORD			m_dwSTime;
	DWORD			m_dwETime, m_dwETimeOrig;
	DWORD			m_UNITTIME;

	EMANI_MAINTYPE	m_MainType;
	EMANI_SUBTYPE	m_SubType;

	WORD			m_wDivCount;
	WORD			m_wDivFrame[ACF_DIV];

	SChaSoundData_103	m_ChaSoundData;

	SANIMCONINFO_103()
	{
		memset( m_szName, 0, sizeof(TCHAR)*ACF_SZNAME );
		memset( m_szSkeletion, 0, sizeof(TCHAR)*ACF_SZNAME );
	}
};

enum EMSTRIKE_EFF
{
	EMSF_NULL		= 0,
	EMSF_SELFBODY	= 1,
	EMSF_TARGET		= 2,

	EMSF_SIZE		= 3
};

struct SANIMSTRIKE
{
	EMPIECECHAR		m_emPiece;
	EMSTRIKE_EFF	m_emEffect;
	DWORD			m_dwFrame;

	SANIMSTRIKE () :
	m_emPiece(PIECE_RHAND),
		m_emEffect(EMSF_TARGET),
		m_dwFrame(0)
	{
	}
};

struct SANIMCONINFO_104
{
	TCHAR			m_szName[ACF_SZNAME];		//	�̸�.
	TCHAR			m_szSkeletion[ACF_SZNAME];	//	���ٱ� �̸�.

	DWORD			m_dwFlag;					//	��Ÿ �Ӽ�.
	DWORD			m_dwSTime;					//	���� �ð�.
	DWORD			m_dwETime, m_dwETimeOrig;	//	�� �ð�.
	DWORD			m_UNITTIME;					//	Ű���� �ð�.

	EMANI_MAINTYPE	m_MainType;
	EMANI_SUBTYPE	m_SubType;

	WORD			m_wDivCount;				//	���ϸ��̼� ���� Ű ����.
	WORD			m_wDivFrame[ACF_DIV];		//	���ϸ��̼� ���� Ű��.

	WORD			m_wStrikeCount;
	SANIMSTRIKE		m_sStrikeEff[ACF_STRIKE];	//	Ÿ�� ����Ʈ ������.

	SChaSoundData_103	m_ChaSoundData;				//	���� ����Ÿ

	SANIMCONINFO_104()
	{
		memset( m_szName, 0, sizeof(TCHAR)*ACF_SZNAME );
		memset( m_szSkeletion, 0, sizeof(TCHAR)*ACF_SZNAME );
	}
};

struct SANIMCONINFO_105
{
	typedef std::list<DxEffAniData*>				EFFANILIST;			
	typedef std::list<DxEffAniData*>::iterator		EFFANILIST_ITER;

	TCHAR			m_szName[ACF_SZNAME];		//	�̸�.
	TCHAR			m_szSkeletion[ACF_SZNAME];	//	���ٱ� �̸�.

	DWORD			m_dwFlag;					//	��Ÿ �Ӽ�.
	DWORD			m_dwSTime;					//	���� �ð�.
	DWORD			m_dwETime, m_dwETimeOrig;	//	�� �ð�.
	DWORD			m_UNITTIME;					//	Ű���� �ð�.

	EMANI_MAINTYPE	m_MainType;
	EMANI_SUBTYPE	m_SubType;

	WORD			m_wDivCount;				//	���ϸ��̼� ���� Ű ����.
	WORD			m_wDivFrame[ACF_DIV];		//	���ϸ��̼� ���� Ű��.

	WORD			m_wStrikeCount;
	SANIMSTRIKE		m_sStrikeEff[ACF_STRIKE];	//	Ÿ�� ����Ʈ ������.

	SChaSoundData_103	m_ChaSoundData;				//	���� ����Ÿ

	EFFANILIST		m_listEffAni;				// ��� ȿ�� !

	SANIMCONINFO_105()
	{
		memset( m_szName, 0, sizeof(TCHAR)*ACF_SZNAME );
		memset( m_szSkeletion, 0, sizeof(TCHAR)*ACF_SZNAME );
	}
};

struct SANIMCONINFO_106
{
	typedef std::list<DxEffAniData*>				EFFANILIST;			
	typedef std::list<DxEffAniData*>::iterator		EFFANILIST_ITER;

	TCHAR			m_szName[ACF_SZNAME];		//	�̸�.
	TCHAR			m_szSkeletion[ACF_SZNAME];	//	���ٱ� �̸�.

	DWORD			m_dwFlag;					//	��Ÿ �Ӽ�.
	DWORD			m_dwSTime;					//	���� �ð�.
	DWORD			m_dwETime, m_dwETimeOrig;	//	�� �ð�.
	DWORD			m_UNITTIME;					//	Ű���� �ð�.

	EMANI_MAINTYPE	m_MainType;
	EMANI_SUBTYPE	m_SubType;

	WORD			m_wDivCount;				//	���ϸ��̼� ���� Ű ����.
	WORD			m_wDivFrame[ACF_DIV];		//	���ϸ��̼� ���� Ű��.

	WORD			m_wStrikeCount;
	SANIMSTRIKE		m_sStrikeEff[ACF_STRIKE];	//	Ÿ�� ����Ʈ ������.

	SChaSoundData	m_ChaSoundData;				//	���� ����Ÿ

	EFFANILIST		m_listEffAni;				// ��� ȿ�� !

	SANIMCONINFO_106 () :
		m_dwFlag(ACF_LOOP|ACF_NEWINFO),
		m_dwSTime(0),
		m_dwETime(0),
		m_dwETimeOrig(0),
		m_UNITTIME(0),
		m_MainType(AN_GUARD_N),
		m_SubType(AN_SUB_NONE),

		m_wDivCount(0),
		m_wStrikeCount(0)
	{
		memset( m_szName, 0, sizeof(TCHAR)*ACF_SZNAME );
		memset( m_szSkeletion, 0, sizeof(TCHAR)*ACF_SZNAME );
		memset ( m_wDivFrame, 0, sizeof(WORD)*ACF_DIV );
	}
};

struct SANIMCONINFO	
{
	enum 
	{ 
		VERSION			= 0x0200,
		VERSION_ENCODE	= 0x0200, 
	};

	typedef std::list<DxEffAniData*>				EFFANILIST;			
	typedef std::list<DxEffAniData*>::iterator		EFFANILIST_ITER;

	TCHAR			m_szName[ACF_SZNAME];		//	�̸�.
	TCHAR			m_szSkeletion[ACF_SZNAME];	//	���ٱ� �̸�.

	DWORD			m_dwFlag;					//	��Ÿ �Ӽ�.
	DWORD			m_dwSTime;					//	���� �ð�.
	DWORD			m_dwETime, m_dwETimeOrig;	//	�� �ð�.
	DWORD			m_UNITTIME;					//	Ű���� �ð�.

	EMANI_MAINTYPE	m_MainType;
	EMANI_SUBTYPE	m_SubType;

	WORD			m_wDivCount;				//	���ϸ��̼� ���� Ű ����.
	WORD			m_wDivFrame[ACF_DIV];		//	���ϸ��̼� ���� Ű��.

	WORD			m_wStrikeCount;
	SANIMSTRIKE		m_sStrikeEff[ACF_STRIKE];	//	Ÿ�� ����Ʈ ������.

	SChaSoundData	m_ChaSoundData;				//	���� ����Ÿ

	EFFANILIST		m_listEffAni;				// ��� ȿ�� !
	DxAniScale*		m_pAniScale;				// �ִϸ��̼� ������.~!

	SANIMCONINFO();
	~SANIMCONINFO();
	void CleanUp();

	BOOL LoadFile ( const TCHAR *szFileName, LPDIRECT3DDEVICEQ pd3dDevice=NULL );
	void LoadFile_0101 ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	void LoadFile_0102 ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	void LoadFile_0103 ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	void LoadFile_0104 ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	void LoadFile_0105 ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	void LoadFile_0106 ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	void LoadFile_0107 ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	
	//official version partial read only
	void LoadFile_0108_0109_0110 ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	void LoadFile_0111_0112_0114_0115 ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	
	void LoadFile_0200 ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );

	BOOL SaveFile ( const TCHAR *szFileName );

	SANIMCONINFO& operator = ( SANIMCONINFO &value );
};