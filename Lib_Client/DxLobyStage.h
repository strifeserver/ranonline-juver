#pragma once

#include "./G-Logic/GLogicData.h"
#include "DxCharSham.h"
#include "../Lib_Engine/GUInterface/UIDataType.h"

#include "DxLandMan.h"
#include "DxStage.h"


struct GLCHAR_NEWINFO
{
	char				m_szName[CHAR_SZNAME];		//	�̸�. (����)

	EMCHARINDEX			m_emIndex;					//	����. (����)
	WORD				m_wSchool;					//	�п�.
	WORD				m_wHair;					//	�Ӹ�ī��.
	WORD				m_wHairColor;				//  �Ӹ�����
	WORD				m_wFace;					//	�󱼸��.
	WORD				m_wSex;						//  ����
	float				m_fScaleRange;

	GLCHAR_NEWINFO () :
		m_emIndex(GLCI_NUM_8CLASS),
		m_wSchool(0),
		m_wHair(0),
		m_wHairColor(0),
		m_wSex(0),
		m_wFace(0),
		m_fScaleRange(1.0f)
	{
	}

	EMCHARCLASS GetClass ()		{ return CharIndexToClass(m_emIndex); }

	bool CHECKVALID () const
	{
		if ( m_emIndex>=GLCI_NUM_8CLASS )	return false;
		return true;
	}

	void RESET ()
	{
		m_emIndex = (GLCI_NUM_8CLASS);
		m_wSchool = (0);
		m_wHair = (0);
		m_wFace = (0);
		m_wHairColor = 0;
		m_wSex = 0;
		m_fScaleRange = 1.0f;
	}
};

class DxLobyStage : public DxStage
{
public:
	enum EMSHIFT
	{
		EM_BEGIN,
		EM_PREV,
		EM_NEXT,
	};

protected:
	D3DCAPSQ			m_d3dCaps;
	D3DSURFACE_DESC		m_d3dsdBackBuffer;

	DxLandMan			m_LandCharSlt;
	DxLandMan			m_LandLogin;
	DxLandMan			m_LandCreate;

	int					m_nStartCharNum;			//	������ ������ �ɸ� ����.
	int					m_nStartCharLoad;			//	Ŭ���̾�Ʈ�� �ε�� �ɸ� ����. ( ���� ���ŵ�. )

	int					m_nChaSNum;					//	������ �ɸ��� ����. ( ���� �ɸ� �� + ���� ������ �ɸ� �� )
	int					m_nChaIDs[MAX_SERVERCHAR];

	DWORD				m_dwCharSelect;
	SCHARINFO_LOBBY		m_CharInfo[MAX_SERVERCHAR];

	int					m_nCharStart;
	DxCharSham			m_CharSham[MAX_SELECTCHAR];
	DxCharSham			m_NewCharSham;

	GLCHAR_NEWINFO		m_sCharNewInfo;

	float				m_fShiftTime;
	BOOL				m_bShiftButton;
	BOOL				m_bShiftLBDown;
	BOOL				m_bShiftRBDown;

	BOOL				m_bUseInterface;
	BOOL				m_bRenderSkip;
	float				m_fRenderSkipTime;

	bool				m_bStyle;
	D3DXVECTOR3			m_vDir;

public:
	BOOL				m_bGameJoin;				// ������ ������ ���� �޼����� ������ �ʱ� ���� �÷���


public:
	EMCHARINDEX GetCreateClass ()				{ return m_sCharNewInfo.m_emIndex; }
	WORD GetCreateSchool ()						{ return m_sCharNewInfo.m_wSchool; }

	const GLCHAR_NEWINFO& GetNewCharInfo ()		{ return m_sCharNewInfo; }
	const int GetChaSNum () const				{ return m_nChaSNum; }

	void  SetStyleStep( bool bStyle );
	void  RotateChar( bool bLeft );

protected:
	void ShiftChar( float fElapsedTime );
	BOOL ShiftRightChar();
	BOOL ShiftLeftChar();
	void ShiftCharInfo();

	void InitRenderSkip();

public:	
	//void ToCameraPos ( int n );

	void SelCharClass ( WORD nIndex );
	void SelCharSchool ( WORD nIndex );

	void SelCharFace ( WORD nIndex )			{ m_sCharNewInfo.m_wFace = nIndex; }
	void SelCharHair ( WORD nIndex )			{ m_sCharNewInfo.m_wHair = nIndex; }
	void SelCharHairColor ( WORD wColor )		{ m_sCharNewInfo.m_wHairColor = wColor; }
	void SelCharScaleRange( float fScale )		{ m_sCharNewInfo.m_fScaleRange = fScale; }

	WORD ShiftCharClass ( EMSHIFT emShift, WORD wClassMax );
	void ShiftCharSchool ( EMSHIFT emShift );
	void ShiftCharFace ( EMSHIFT emShift );
	void ShiftCharHair ( EMSHIFT emShift );


	void DelChar ( int nCharID );
	void ShiftLBDown()							{ m_bShiftLBDown = TRUE; }
	void ShiftRBDown()							{ m_bShiftRBDown = TRUE; }
	BOOL IsShiftLeft()							{ return (m_nCharStart-MAX_SELECTCHAR)>=0;}
	BOOL IsShiftRight()							{ return (m_nCharStart+MAX_SELECTCHAR)<m_nChaSNum;}
	INT GetPageNum()							{ return (m_nCharStart/MAX_SELECTCHAR)+1; }
	void SelectChar( DWORD dwCharID );

public:
	SCHARINFO_LOBBY* GetSelectCharInfo();
	SCHARINFO_LOBBY* GetCharInfo( int nSelect );
	DWORD IsCharSelect()						{ return (m_dwCharSelect!=MAX_SELECTCHAR); }
	BOOL IsStartReady ()						{ return m_nStartCharNum==m_nStartCharLoad; }
	

public:
	void OnInitLogin ();

public:
	virtual HRESULT OneTimeSceneInit ( HWND hWnd, WORD wWidth, WORD wHeight, const char* szAppPath );
	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT RestoreDeviceObjects ();
	virtual HRESULT InvalidateDeviceObjects ();
	virtual HRESULT DeleteDeviceObjects ();
	virtual HRESULT FinalCleanup();

protected:
	void UpdateSelSkinChar ( DxSkinChar* pSkinObj, EMCHARINDEX emIndex, WORD wFace, WORD wHair, WORD wHairColor );

public:
	virtual HRESULT FrameMove ( float fTime, float fElapsedTime );
	virtual HRESULT Render ();

public:
	virtual void MsgProcess ( NET_MSG_GENERIC* nmg );
	virtual HRESULT ReSizeWindow ( WORD wWidth, WORD wHeight );

public:
	DxLobyStage(void);
	~DxLobyStage(void);
};