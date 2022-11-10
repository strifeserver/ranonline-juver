#ifndef GLQUEST_H_
#define GLQUEST_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>

#include "./GLItem.h"
#include "./GLogicData.h"

#include "../../Lib_Engine/G-Logic/GLDefine.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/COMMON/StringFile.h"

#include "./GLQuestGenItem.h"
#include "./GLQuestStart.h"
#include "./GLQuestStep.h"

enum EMQUESTFLAGS
{
	EMQF_REPEAT		= 0x0001,		//	�Ϸ�� ����Ʈ ���� ���� ����.
	EMQF_AGAIN		= 0x0002,		//	������ ����Ʈ ���� ���� ����.
	EMQF_ONLYONE	= 0x0004,		//	�� ����Ʈ�� �ٸ� ����Ʈ�� ���� ���� �Ұ���.
	EMQF_GIVEUP		= 0x0008,		//	����Ʈ ���� ���� ����.
	
	EMQF_PARTY		= 0x1000,		//	��Ƽ�� ���� ������ ����Ʈ.
	EMQF_PARTYQUEST	= 0x2000,		//	��Ƽ�� ���� ���� ����Ʈ.
};

enum EMQUESTPROGRESS
{
	EMQP_NON_EVENT = 0, // �̺�Ʈ ����
	EMQP_CHAR_DEAD,		// ĳ���� ���
	EMQP_START_MOVE,	// ������������ �̵�
    EMQP_SELECT_MOVE,   // ������ ��ġ�� �̵�
	EMQP_SIZE,
};

enum EMFAILTYPE
{
	EMFAIL_NONE		= 0x0000,		// Ÿ�Ծ���
	EMFAIL_TIMEOVER = 0x0001,		// Ÿ�ӿ����� ���н�
	EMFAIL_DIE      = 0x0002,		// �׾ ���н�
	EMFAIL_LEAVE    = 0x0004,		// Ư�� �ʿ��� ������ ���н�
};

enum EMQUEST_AREA
{
	EMQUEST_AREA_00		= 0,
	EMQUEST_AREA_01		= 1,
	EMQUEST_AREA_02		= 2,
	EMQUEST_AREA_03		= 3,
	EMQUEST_AREA_04		= 4,
	EMQUEST_AREA_05		= 5,
	EMQUEST_AREA_06		= 6,
	EMQUEST_AREA_07		= 7,
	EMQUEST_AREA_08		= 8,
	EMQUEST_AREA_09		= 9,
	EMQUEST_AREA_10		= 10,
	EMQUEST_AREA_11		= 11,
	EMQUEST_AREA_12		= 12,
	EMQUEST_AREA_13		= 13,
	EMQUEST_AREA_14		= 14,
	EMQUEST_AREA_15		= 15,
	EMQUEST_AREA_16		= 16,
	EMQUEST_AREA_17		= 17,
	EMQUEST_AREA_18		= 18,
	EMQUEST_AREA_19		= 19,
	EMQUEST_AREA_20		= 20,
	EMQUEST_AREA_21		= 21,
	EMQUEST_AREA_22		= 22,
	EMQUEST_AREA_23		= 23,
	EMQUEST_AREA_24		= 24,
	EMQUEST_AREA_25		= 25,
	EMQUEST_AREA_26		= 26,
	EMQUEST_AREA_27		= 27,
	EMQUEST_AREA_28		= 28,
	EMQUEST_AREA_29		= 29,
	EMQUEST_AREA_SIZE	= 30,
};

struct GLQUEST_PROGRESS 
{
	DWORD dwStartProgress;  // ���۽� �̺�Ʈ
	DWORD dwEndProgress;	  // ����� �̺�Ʈ
	DWORD dwFailProgress;	  // ���н� �̺�Ʈ
		
	DWORD	dwfailType;		  // ������ ����

	GLQUEST_PROGRESS_MAP startMap;
	GLQUEST_PROGRESS_MAP endMap;
	GLQUEST_PROGRESS_MAP failMap;

	bool	bUseProgressEvent;

	GLQUEST_PROGRESS()
	{
		Init();
	}

	VOID Init()
	{
		dwStartProgress = EMQP_NON_EVENT;
		dwEndProgress   = EMQP_NON_EVENT;
		dwFailProgress  = EMQP_NON_EVENT;

		dwfailType    = 0;

		startMap.Init();	
		endMap.Init();
		failMap.Init();

		bUseProgressEvent = FALSE;
	};

	bool IsTIMEOVER ()		{ return (dwfailType&EMFAIL_TIMEOVER)!=NULL; }
	bool IsDIE ()			{ return (dwfailType&EMFAIL_DIE)!=NULL; }	
	bool IsLEAVE ()			{ return (dwfailType&EMFAIL_LEAVE)!=NULL; }	
    
};

class GLQUEST
{
public:
	enum { VERSION = 0x0202, };

	typedef std::vector<GLQUEST_STEP>	VECQSTEP;
	typedef VECQSTEP::iterator			VECQSTEP_ITER;

public:
	SNATIVEID		m_sNID;					//	���� ID. 
	DWORD			m_dwEDITVER;			//	���� ����.
	std::string		m_strTITLE;				//	����Ʈ Ÿ��Ʋ.
	std::string		m_strCOMMENT;			//	����Ʈ ����.	
	DWORD			m_dwFlags;				//	�Ӽ�.
	EMQUEST_AREA	m_emQuestArea;	
	GLQUEST_START	m_sSTARTOPT;			//	�ڵ� ���� ����.
	DWORD			m_dwBeginPartyMemNum;	//	����Ʈ�� �ޱ� ���� �ּ� ��Ƽ �ο�.
	DWORD			m_dwBeginMoney;			//	����Ʈ �ޱ� ���� ���.
	DWORD			m_dwLimitTime;			//	���� �ð�.	( ���� �ð��� �д���. )
	bool			m_bNonDie;				//	���� ���� ����ϸ� �ȵ�.
	DWORD			m_dwLimitPartyMemNum;	//	���� ��Ƽ �ο�.
	VECQSTEP		m_vecProgStep;			//	��ü ���� ���� ����.
	DWORD			m_dwGiftMONEY;			//	�Ϸ�� ����.
	LONGLONG		m_llGiftEXP;
	DWORD			m_dwGiftSKILLPOINT;
	DWORD			m_dwGiftSTATSPOINT;
	DWORD			m_dwGiftLIFEPOINT;
	DWORD			m_dwGiftDisPK;
	DWORD			m_dwGiftELEMENT;
	DWORD			m_dwGiftQUEST;
	INVENQARRAY		m_vecGiftITEM;
	DWQARRAY		m_vecGiftSKILL;
	GLQUEST_PROGRESS m_ProgressEvent;		//	����Ʈ ���� �߿� ����Ǵ� �̺�Ʈ

public:
	GLQUEST () :
		m_dwEDITVER(1),
		m_strTITLE("Quest Title"),
		m_strCOMMENT("Quest Description"),
		m_dwFlags(0),
		m_emQuestArea(EMQUEST_AREA_00),
		m_dwBeginPartyMemNum(0),
		m_dwBeginMoney(0),
		m_dwLimitTime(0),
		m_bNonDie(false),
		m_dwLimitPartyMemNum(0),
		m_dwGiftMONEY(0),
		m_llGiftEXP(0),
		m_dwGiftSKILLPOINT(0),
		m_dwGiftSTATSPOINT(0),
		m_dwGiftLIFEPOINT(0),
		m_dwGiftDisPK(0),
		m_dwGiftELEMENT(0),
		m_dwGiftQUEST(UINT_MAX)
	{
	}

	GLQUEST& operator= ( const GLQUEST &rVALUE );

public:
	const char* GetTITLE()			{ return m_strTITLE.c_str(); }
	DWORD GetSTEPNUM ()				{ return (DWORD) m_vecProgStep.size(); }
	GLQUEST::VECQSTEP& GetSTEP ()	{ return m_vecProgStep; }
	GLQUEST_STEP* GetSTEP ( DWORD dwSTEP );

public:
	DWORD ToUpStep ( DWORD dwSTEP );
	DWORD ToDownStep ( DWORD dwSTEP );

public:
	bool IsREPEAT ()		{ return (m_dwFlags&EMQF_REPEAT)!=NULL; }		//	������ ���� ����.
	bool IsAGAIN ()			{ return (m_dwFlags&EMQF_AGAIN)!=NULL; }		//	(�����Ѱ�) �ٽ� ���� ����.
	bool IsPARTY ()			{ return (m_dwFlags&EMQF_PARTY)!=NULL; }		//	��Ƽ�϶� ���� ����.
	bool IsPARTYQUEST ()	{ return (m_dwFlags&EMQF_PARTYQUEST)!=NULL; }	//	��Ƽ�� ���� ���� ����Ʈ.

	bool IsONLYONE ()		{ return (m_dwFlags&EMQF_ONLYONE)!=NULL; }		//	���ÿ� ����Ұ�?
	bool IsGIVEUP ()		{ return (m_dwFlags&EMQF_GIVEUP)!=NULL; }		//	���� ����
	
	bool IsLIMITTIME ()		{ return m_dwLimitTime!=0; }
	bool IsNonDIE ()		{ return m_bNonDie; }

protected:
	bool LOAD_0001 ( basestream &SFile );
	bool LOAD_0002 ( basestream &SFile );
	bool LOAD_0003 ( basestream &SFile );
	bool LOAD_0004 ( basestream &SFile );
	bool LOAD_0005 ( basestream &SFile );
	bool LOAD_0006 ( basestream &SFile );
	bool LOAD_0007 ( basestream &SFile );
	bool LOAD_0008 ( basestream &SFile );
	bool LOAD_0009 ( basestream &SFile );
	bool LOAD_0010 ( basestream &SFile );
	bool LOAD_0011 ( basestream &SFile );
	bool LOAD_0012 ( basestream &SFile );
	bool LOAD_0013 ( basestream &SFile );
	bool LOAD_0014 ( basestream &SFile );
	bool LOAD_0015 ( basestream &SFile );
	bool LOAD_0016 ( basestream &SFile );
	bool LOAD_0200 ( basestream &SFile );
	bool LOAD_0201 ( basestream &SFile );
	bool LOAD_0202 ( basestream &SFile );
	
public:
	bool LOAD ( const char *szFile );
	bool SAVE ( const char *szFile );

	void SaveCsv( std::fstream &SFile, CString strFileName );
	void SaveCsvInfoHead( std::fstream &SFile, CString strFileName );
	void SaveCsvBaseHead( std::fstream &SFile );
	void SaveCsvInfoData( std::fstream &SFile );
	void SaveCsvBaseData( std::fstream &SFile );
	void SaveCsvProgress( std::fstream &SFile );
	void SaveCsvProgressBaseHead( std::fstream &SFile );
	void SaveCsvProgressBaseData( std::fstream &SFile );

	void LoadCsv( CStringArray &StrArray, CStringArray &StrArrayProgress );
	void LoadCsvInfoDate( CStringArray &StrArray );
	void LoadCsvBaseData( CStringArray &StrArray );
	void LoadCsvProgress( CStringArray &StrArray );
	void LoadCsvProgressBaseHead( CStringArray &StrArray );
	void LoadCsvProgressBaseData( CStringArray &StrArray );

	void ExportText( std::fstream &SFile );
	void ExportTextSubJect( std::fstream &SFile );
	void ExportTextProgress( std::fstream &SFile );
	void ImportText( CStringFile& strFile );
	void ImportTextSubject( CStringFile& strFile );
	void ImportTextProgress( CStringFile& strFile );
};

enum EMQUESTPROG
{
	EMQP_REQREADING		= 0x0001,	// ����Ʈ�� ��� �о�⸦ ��û.
};

struct GLQUESTPROG_STEP
{
	enum { VERSION = 0x0002, };

	//	�̼� ����.
	bool		m_bTALK;					//	��ȭ�ߴ��� ����.
	bool		m_bQITEM;					//	�ʿ� ����Ʈ ������ ���.

	bool		m_bMOBKILL_ALL;				//	�׿����� Mob ��� ����.
	DWORD		m_dwNUM_MOBKILL;			//	���� Mob ����.
	bool		m_bNPCGUARD_DEATH;			//	��ȣ�ؾ��� NPC ��� ����.

	bool		m_bREACH_ZONE;				//	���� ��ġ�� ���� ����.
	
	bool		m_bDEFENSE_ZONE_BEGIN;		//	��� ��ġ ��� ���� ����.
	bool		m_bDEFENSE_ZONE_COMPLETE;	//	��� ��ġ ��� �Ϸ�.
	float		m_fDEFENSE_ZONE_TIMER;		//	��� ��ġ ��� ����ð�.

	bool		m_bLevel;

public:
	GLQUESTPROG_STEP () :
		m_bTALK(true),
		m_bQITEM(true),

		m_bMOBKILL_ALL(true),
		m_dwNUM_MOBKILL(UINT_MAX),
		m_bNPCGUARD_DEATH(false),

		m_bREACH_ZONE(true),

		m_bDEFENSE_ZONE_BEGIN(true),
		m_bDEFENSE_ZONE_COMPLETE(true),
		m_fDEFENSE_ZONE_TIMER(FLT_MAX),

		m_bLevel(true)
	{
	}

public:
	bool BEGIN_PROG ( const GLQUEST_STEP &sSTEP );
	void RESET ();

public:
	bool IsCOMPLETE ();

public:
	GLQUESTPROG_STEP& operator= ( const GLQUESTPROG_STEP &rVALUE );

public:
	BOOL SET_BYBUFFER ( CByteStream &ByteStream ) const;
	BOOL GET_BYBUFFER ( CByteStream &ByteStream );
};

class GLQUESTPROG
{
public:
	enum { VERSION = 0x0002, INVEN_SIZEX=8, INVEN_SIZEY=1 };

	typedef std::vector<DWORD>	DWARRAY;
	typedef DWARRAY::iterator	DWARRAY_ITER;

public:
	SNATIVEID	m_sNID;					//	���� ID.
	DWORD		m_dwEDITVER;
	DWORD		m_dwFlags;				//	�Ӽ�.
	DWORD		m_dwCOUNT;				//	�õ� Ƚ��.

	bool		m_bCOMPLETE;			//	�Ϸ� ����.
	float		m_fLAPSTIME;			//	������ ��� �ð�.

	DWORD				m_dwSTEP;		//	���� ���� ����Ʈ STEP.
	GLQUESTPROG_STEP	m_sSTEP_PROG;	//	���� ���� ����.

	GLInventory			m_sINVENTORY;	//	����Ʈ ���� �κ�.

	__time64_t			m_tStartTime;		//	����Ʈ ���� �ð�

public:
	bool START ( GLQUEST* pQUEST, GLQUESTPROG *pOLD_PROG );
	bool DoPROGRESS ( bool &_bModifyInven, GLQUEST_PROGRESS_MAP &stepMoveMap );
	void DoGIVEUP ();
	bool DoCOMPLETE ();

	bool CheckCOMPLETE ();
	bool CheckTIMEOVER ();

public:
	HRESULT FrameMove ( float fTime, float fElapsedTime );

public:
	void ResetReqREADING ()	{ m_dwFlags &= ~EMQP_REQREADING; }

public:
	void ReqREADING ()		{ m_dwFlags |= EMQP_REQREADING; }
	bool IsReqREADING ()	{ return (m_dwFlags&EMQP_REQREADING)!=NULL; }
	bool IsNonDIE ();

public:
	GLQUESTPROG& operator= ( const GLQUESTPROG &rVALUE );

public:
	BOOL SET_BYBUFFER ( CByteStream &ByteStream ) const;
	BOOL GET_BYBUFFER ( CByteStream &ByteStream );

public:
	BOOL LOAD_001 ( CByteStream &ByteStream );
	BOOL LOAD_002 ( CByteStream &ByteStream );

public:
	GLQUESTPROG () :
		m_sNID(false),
		m_dwEDITVER(1),
		m_dwFlags(NULL),
		m_bCOMPLETE(false),
		m_dwCOUNT(0),
		m_fLAPSTIME(0.0f),
		m_tStartTime(0),
		m_dwSTEP(0)
	{
		m_sINVENTORY.SetState ( INVEN_SIZEX, INVEN_SIZEY );
	}
};

namespace COMMENT
{
	extern std::string QUEST_PROGRESS[EMQP_SIZE];
	extern std::string QUEST_AREA[EMQUEST_AREA_SIZE];
}

#endif // GLQUEST_H_