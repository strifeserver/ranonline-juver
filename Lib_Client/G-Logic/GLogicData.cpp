#include "StdAfx.h"
#include "StringFile.h"
#include "StringUtils.h"
#include "GLogic.h"
#include "GLCharData.h"
#include "GLCrowData.h"
#include "GLItemMan.h"
#include "DxSkinDataDummy.h"
#include "GLQuestMan.h"
#include "GLBusStation.h"
#include "GLTaxiStation.h"
#include "GLPeriod.h"
#include "GLogicData.h"
#include "GLCommentFile.h"
#include "GLStringTable.h"
#include "Unzipper.h"
#include "GLTexfile.h"
#include "GLItemMixMan.h"

/*activity system, Juver, 2017/10/21 */
#include "GLActivity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// note : zip ���� �н� ����
//
namespace GLOGIC
{
	std::string	strGLOGIC_ZIPFILE;
	std::string	strQUEST_ZIPFILE;
	std::string	strLEVEL_ZIPFILE;
	std::string	strNPCTALK_ZIPFILE;

	void SetFullPath( BOOL bPack )
	{
		if( bPack )
		{
			strGLOGIC_ZIPFILE	= "\\data\\glogic\\";
			strQUEST_ZIPFILE	= "\\data\\glogic\\quest\\";
			strLEVEL_ZIPFILE	= "\\data\\glogic\\level\\";
			strNPCTALK_ZIPFILE	= "\\data\\glogic\\npctalk\\";
		}
		else
		{
			strGLOGIC_ZIPFILE = GLOGIC::GetPath();
			strGLOGIC_ZIPFILE += "GLogic.rcc";

			strQUEST_ZIPFILE = GLOGIC::GetPath();
			strQUEST_ZIPFILE += "Quest\\Quest.rcc";

			strLEVEL_ZIPFILE = GLOGIC::GetPath();
			strLEVEL_ZIPFILE += "Level\\Level.rcc";

			strNPCTALK_ZIPFILE = GLOGIC::GetPath();
			strNPCTALK_ZIPFILE += "NpcTalk\\NpcTalk.rcc";
			
			CUnzipper::LOADFILE_RCC( strGLOGIC_ZIPFILE );
			CUnzipper::LOADFILE_RCC( strQUEST_ZIPFILE );
			CUnzipper::LOADFILE_RCC( strLEVEL_ZIPFILE );
			CUnzipper::LOADFILE_RCC( strNPCTALK_ZIPFILE );
		}
	}
};

//----------------------------------------------------------------------------------------
void GLCONST_CHARCLASS::LoadAniSet ( char* szSkinObj )
{
	if ( szSkinObj[0]=='\0' )	return;

	DxSkinDataDummy DataDummy;
	BOOL bOK = DataDummy.LoadFile ( szSkinObj );
	if ( !bOK )
	{
		CString StrMsg;
		StrMsg.Format ( "[%s] Skin File Load Fail.", szSkinObj );
		MessageBox ( NULL, StrMsg.GetString(), "ERROR", MB_OK );
		return;
	}

	size_t nSIZE = DataDummy.m_vecANIMINFO.size();
	for ( size_t n=0; n<nSIZE; ++n )
	{
		const SANIMCONINFO *pAnimConInfo = DataDummy.m_vecANIMINFO[n];

		SANIATTACK sAniAttack;
		sAniAttack.Assign ( pAnimConInfo );
		m_ANIMATION[pAnimConInfo->m_MainType][pAnimConInfo->m_SubType].push_back ( sAniAttack );
	}
}

void GLCONST_CHARCLASS::ClearAniSet ()
{
	for ( int i=0; i<AN_SUB_00_SIZE; ++i )
	for ( int j=0; j<AN_TYPE_SIZE; ++j )
	{
		m_ANIMATION[j][i].clear ();
	}
}


//----------------------------------------------------------------------------------------
namespace GLCONST_CHAR
{
	BOOL		bTESTSERVER			= FALSE;			//	�׽�Ʈ �������� ����.
	INT			nUI_KEYBOARD		= 0;				// �������̽� Ű���� ����. �⺻ ���� Ű����, UI �Ѵ� ���
	BOOL		bBATTLEROYAL		= FALSE;			// ��Ʋ�ξ�
	INT			nMAX_FRIEND_NUMBER	= 100;				// �ִ� ģ��, ���� ��� ����
	WORD		wLEVEL_FOR_EXTREME	= 192;				// �ذ��θ� �����ϱ� ���� �����Ǿ�� �ϴ� ����(lv.192)
	BOOL 		bClickToUnlockSkills = TRUE; 			// TDEV DISABLE CLICK TO UNLOCK SKILLS
		
	float		fFIELD_NEXTPICK		= 0.4f;
	WORD		wSERVER_NORMAL		= 40;				//	���� ����.
	WORD		wSERVER_CONGEST		= 70;				//	���� ȥ��.
	WORD		wSERVER_NOVACANCY	= 95;				//  ���� Ǯ, ���� �Ұ�

//	float		fDISPRICE			= 0.3f;				//	������ ���Ǹ� ����.
	WORD		wMAXITEM_AGE		= 120;
	WORD		wMAXITEM_HOLD		= 10;

	float		fCHAR_HEIGHT[GLCI_NUM_8CLASS]	= { 20.0f, 20.0f, 17.0f, 17.0f, 20.0f, 17.0f, 17.0f, 17.0f, 20.0f, 20.0f, 20.0f, 17.0f, 20.0f, 17.0f, 20.0f, 17.0f };

	//	Note : ĳ���� �⺻ ���.
	//
	WORD		wSCHOOLNUM = 1;
	std::string	strSCHOOLNAME[MAX_SCHOOL]	= { "Sacred Gate", "Mystic Peak", "Phoenix" };
	SNATIVEID	nidSTARTMAP[MAX_SCHOOL]		= { SNATIVEID(0,0) };
	DWORD		dwSTARTGATE[MAX_SCHOOL]		= { 0 };

	BOOL		bPARTY_2OTHERSCHOOL = TRUE;
	BOOL		bCLUB_2OTHERSCHOOL = TRUE;

	//userpanel
	WORD			wGameTimeDiv = 60;			//	������ ���� ����Ʈ �ο���.
	WORD			wGameTimeRes = 3;			//	������ ���� ����Ʈ �ο���.

	WORD		wMAX_LEVEL			= 255;			//	���� �ִ� ����.
	WORD		wMAX_EXTREME_LEVEL	= 255;			//	�ذ��� ���� �ִ� ����.
	WORD		wLVL_STATS_P		= 3;			//	������ ���� ����Ʈ �ο���.
	WORD		wLVL_2ndSTATS_P		= 4;			//	������ ���� ����Ʈ �ο���. �ذ���
	float		fLVL_EXP_G			= 25.0f;		//	���� ����ġ ���⿡ �ʿ��� ȯ�� ����.
	float		fLVL_EXP_S			= 1.3f;			//	���� ����ġ ���⿡ �ʿ��� ȯ�� ����.
	float		fREC_EXP_RATE		= 2.0f;			//	������ ȸ������ �ٶ� ȹ���ϴ� ����ġ�� ����.
	float		fKILL_EXP_RATE		= 0.5f;			//	"��ȹ�� ���� ����ġ" * ���϶� ����ġ.

	float	fDIE_DECEXP[DIE_DECEXP_NUM] =		// ������ ���̴� ����ġ ����
	{
		0, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	float	fDIE_RECOVERYEXP[DIE_DECEXP_NUM] =	// �׾����� ȸ���Ҽ� �ִ� ����ġ ����
	{
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	float	fEXP_RATE_MONEY[DIE_DECEXP_NUM]	=	// ����ġ�� �ݾ� ����
	{
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	WORD		wGRADE_MAX			= 9;			//	���� �Ҽ� �ִ� ��� ����ġ 
	WORD		wGRADE_MAX_REGI		= 9;

	WORD		wDAMAGE_GRADE		= 3;			//	�� ��޴� ���� ���ݷ� ��ġ.
	WORD		wDEFENSE_GRADE		= 2;			//	�� ��޴� ���� ���� ��ġ.

	float		fDAMAGE_GRADE		= 10;			//	�� ��޴� ������ ���ݷ� ��ġ.
	float		fDEFENSE_GRADE		= 5;			//	�� ��޴� ������ ���� ��ġ.

	float		fSORTTIME			= 10.0f;		//Sort by NaJ

	float		fDAMAGE_GRADE_TOP[GRADE_LIMIT_MAX-GRADE_HIGH]	=	// �ֻ��� ��� ���ݷ� ������
	{
		1.0f, 1.0f, 1.0f, 1.0f,	1.0f, 1.0f
	};

	float		fDEFENSE_GRADE_TOP[GRADE_LIMIT_MAX-GRADE_HIGH]	=	// �ֻ��� ��� ���ݷ� ������
	{
		1.0f, 1.0f, 1.0f, 1.0f,	1.0f, 1.0f
	};

	WORD		wUSE_GRADE_NUM[GRADE_LIMIT_MAX-GRADE_HIGH]	=	// �ֻ��� ��޽� �ʿ��� ������ ����
	{
		1, 2, 3, 4, 5, 6	
	};

	WORD		wRESIST_FIRE_GRADE	= 2;			//	�� ��޴� ���� ����(ȭ) ��ġ.
	WORD		wRESIST_ICE_GRADE	= 2;			//	�� ��޴� ���� ����(��) ��ġ.
	WORD		wRESIST_ELEC_GRADE	= 2;			//	�� ��޴� ���� ����(��) ��ġ.
	WORD		wRESIST_POISON_GRADE= 2;			//	�� ��޴� ���� ����(��) ��ġ.
	WORD		wRESIST_SPIRIT_GRADE= 2;			//	�� ��޴� ���� ����(��) ��ġ.

	WORD		wLVL_SKILL_P		= 1;			//	������ ��ų ����Ʈ �ο���.
	WORD		wLVL_2ndSKILL_P		= 2;			//	������ ��ų ����Ʈ �ο���. �ذ���

	WORD		wMAXATRANGE_SHORT	= 2;			//	���� ���ݰŸ�.
	float		fPUSHPULL_VELO		= 40.0f;		//	�аų� ��涧 �̵� �ӵ�.
	WORD		wMAXMOB_TRACKING	= 3;			//	�ִ� �� ���� ��.

	float		fMOB_TRACING		= 90.0f;		//	�� ���� �Ÿ�.
	float		fLOW_SEED_DAMAGE	= 0.05f;		//	damage ���� ���� ���� damage ����.
	float		fCONFT_SPTY_EXP		= 0.005f;		//	�б� ��� �¸��ÿ� ��ü ����ġ �й�.

	WORD		wBODYRADIUS			= 4;			//	ĳ���� ��ü �ݰ�.
	float		fWALKVELO			= 10.0f;		//	ĳ���� �ȱ� �ӵ�.
	float		fRUNVELO			= 36.0f;		//	ĳ���� �ٱ� �ӵ�.

	float		fREACT_VALID_SCALE	= 4.0f;			//	�׼��� ��ȿ �Ÿ� ����.

	float		fUNIT_TIME			= 1.0f;			//	ȸ�� ���� �ð�.
	float		fHP_INC_PER			= 0.3f*0.01f;	//	�����ð��� HP ȸ����(%)
	float		fMP_INC_PER			= 0.3f*0.01f;	//	�����ð��� MP ȸ����(%)
	float		fSP_INC_PER			= 0.5f*0.01f;	//	�����ð��� SP ȸ����.

	float		fHP_INC				= 0;			//	�����ð��� HP ȸ����.
	float		fMP_INC				= 0;			//	�����ð��� MP ȸ����.
	float		fSP_INC				= 0;			//	�����ð��� SP ȸ����.

	float		fRESIST_PHYSIC_G	= 0.5f;			//	���� ���ݽ� �Ӽ� ����ġ ���� ����.
	float		fRESIST_G			= 0.5f;			//	���� ���ݽ� �Ӽ� ����ġ ���� ����.
	WORD		wBASIC_DIS_SP		= 1;			//	�⺻ ���ݽ� �Ҹ� SP ��.

	float		fLOWSP_MOTION		= 0.20f;		//	���¹̳� (%) ���� ������ ��� ó��.
	float		fLOWSP_DAMAGE		= 0.50f;		//	���¹̳� ������ Damage ����.
	float		fLOWSP_HIT_DROP		= 0.25f;		//	���¹̳� ������ ������ ����.
	float		fLOWSP_AVOID_DROP	= 0.50f;		//	���¹̳� ������ ȸ���� ����.
	DWORD		dwACCEPT_LOWERSTATS	= 5;			//	stats �������� ���¹̳��� Ŀ���� �� �ִ� ���� �ѵ�. ( ���� ���⿡ ����. )

	float		fDAMAGE_DEC_RATE	= 40000.0f;		//	����� �����(�ݺ��)
	float		fDAMAGE_GRADE_K		= 10.0f;		//	(�⺻����+�������) ����� �ݿ���.(�ݺ��)

	DWORD		dwCRITICAL_DAMAGE	= 120;			//	ũ��Ƽ�� ������ ����
	DWORD		dwCRITICAL_MAX		= 40;			//	ũ��Ƽ�� Ȯ�� MAX

	float		fPKCOMBO_RANGE_TIME	= 15.0f;

	DWORD		dwCRUSHING_BLOW_DAMAGE	= 150;		//  ����Ÿ�� ������ ����
	DWORD		dwCRUSHING_BLOW_MAX		= 20;		//  ����Ÿ�� Ȯ�� max
	float		fCRUSH_BLOW_RANGE		= 10.0f;	//  ����Ÿ�ݽ� �з����� �Ÿ� ( ������ ) 

	float		fCONFRONT_TIME		= 180.0f;		//	��� ���� �ð�.
	float		fCONFRONT_ELAP		= 60.0f;		//	���� ��� ���� ���� �ð�.
	DWORD		dwCONFRONT_MAX		= 3;			//	���� ��� �� ���� Ƚ��.
	float		fCONFRONT_RESET		= 3600.0f;		//	���� ��� ���� ���� �ð�.
	float		fCONFRONT_ONE_DIST	= 0;			//	��� �Ÿ� ����. ( 0�� ��� ���Ѵ�. )
	float		fCONFRONT_PY_DIST	= 0;			//	��� �Ÿ� ����. ( 0�� ��� ���Ѵ�. )
	float		fCONFRONT_CLB_DIST	= 0;			//	��� �Ÿ� ����. ( 0�� ��� ���Ѵ�. )

	int			nCONFRONT_WIN_LP	= 1;			//	��� �¸��� living point ( ��Ȱ ���� ).
	int			nCONFRONT_LOSS_LP	= -1;			//	��� �й�� living point ( ��Ȱ ���� ).

	int			nCONFRONT_CLB_WIN_LP	= 5;
	int			nCONFRONT_CLB_LOSS_LP	= -5;

	WORD		wCONFRONT_SCHOOL_LIMIT_NUM		= 4;	//	�б��� ��� �ּ� �ο�.
	WORD		wCONFRONT_SCHOOL_LIMIT_LEVEL	= 20;	//	�б��� ��� �ּ� ����.
	float		fCONFRONT_SCHOOL_EXP_SCALE		= 1.5f;	//	�б��� ��ý� ���� ����ġ ������.

	WORD		wCONFRONT_SCHOOL_WIN_NUM		= 200;	//	�ְ� �¼� �б� ���� �ּ� �¼�.
	WORD		wCONFRONT_SCHOOL_WIN_RATE		= 30;	//	�ְ� �¼� �б� ���� �ּ� ����.
	float		fCONFRONT_SCHOOL_GENITEM		= 1.1f;	//	�ְ� �¼� �б����� ������ ��� ������.

    WORD		wCONFT_RC_TYPE[EMCONFT_RC_TYPENUM] = { 0, 4, 6, 8, 10, 12, 16, 20, 30, 0xffff };			//	��� ȸ���� ��밡�� Ƚ��.
	float		fCONFT_STATE_TYPE[EMCONFT_STATE_TYPENUM] = { 1.0f, 1.2f, 1.5f, 1.6f, 2.0f, 2.5f, 3.0f, 4.0f };	//	��� ü�� Ȯ�� ����.

	int			nSTATEBLOW_LEVEL[EMSTATEBLOW_LEVEL_SIZE] = { +10,  +8,  +6, +3, 0,  -2,  -4,  -6,  -8,  -10 };

	BOOL		bPK_MODE = TRUE;
	BOOL		bPKLESS = FALSE;
	int			nPK_LIMIT_LEVEL = 20;			//	pk ���� ����.
	int			nPK_LIMIT_DX_LEVEL = 10;		//	pk ������ ���� ����.
	int			nPK_TRY_BRIGHT_POINT = -1;		//	pk �õ��� ����Ʈ.
	int			nPK_KILL_BRIGHT_POINT = -9;		//	pk �׿��� ��� ����Ʈ.
	int			nPK_TRY_LIVING_POINT = -1;		//	pk �õ��� ����Ʈ.
	int			nPK_KILL_LIVING_POINT = -10;	//	pk �׿��� ��� ����Ʈ.
	float		fNONPK_ITEM_DROP = 0;			//	non pk �� ������ �����.
	float		fPK_ITEM_DROP = 0;				//	pk �� ������ �����.

	DWORD		dwPK_RECALL_ENABLE_LEVEL = 1;	//	��ȯ ��� ���� ���� ����.
	DWORD		dwPK_DRUG_ENABLE_LEVEL = 2;		//	ȸ���� ��� ���� ���� ����.

	float		fPK_JUSTNESS_TIME = 60.0f;		//	�ݰ� ������ ������� �ð�.
	float		fPK_SAFE_TIME = 10.0f;			//	pk ���� �ð�.

	DWORD		dwPK_NORMAL_NAME_COLOR = 0xffffffff;	//	pk ��ġ�� ������ �̸� ����.
	float		fPK_POINT_DEC_RATE = 4.0f*3600.0f/GLPeriod::REALTIME_TO_VBR;	//	pk ��ġ ������. ( �ð���. )
	float		fPK_POINT_DEC_PHY = 0.5f;		//  pk ������ ������ ( ���� ).
	float		fPK_POINT_DEC_MAGIC = 0.5f;		//  pk ������ ������ ( ���� ).


	SPLAYERKILL	sPK_STATE[EMPK_STATE_LEVEL] =
	{
		SPLAYERKILL(5,0xFFFF00,-20,"�Ϲ��л�",120.0f,1,10.0f,130.0f,90.0f),
		SPLAYERKILL(4,0xFFE400,-80,"�ҷ��л�",140.0f,2,10.0f,0.0f,0.0f),
		SPLAYERKILL(3,0xFFBC00,-160,"������",180.0f,3,30.0f,0.0f,0.0f),
		SPLAYERKILL(2,0xFF9700,-300,"���θ�",240.0f,4,60.0f,0.0f,0.0f),
		SPLAYERKILL(1,0xFF0000,-INT_MAX,"���α�",350.0f,5,90.0f,0.0f,0.0f),
	};

	//	Note : ����ġ Table
	//
	//
	WORD		wEXPTABLE[EXPTABLE_SIZE][EXPTABLE_LVL] = 
	{
		{ 0, 0, 1, 1, 2, 3, 4, 9, 15, 24, 30, 36, 44, 55, 70, 90, 116, 149, 190 },
		{ 0, 0, 1, 1, 2, 3, 4, 9, 15, 24, 30, 37, 46, 58, 74, 95, 122, 156, 198 },
		{ 0, 0, 1, 1, 2, 3, 4, 9, 15, 24, 30, 38, 48, 61, 78, 100, 128, 163, 206 },
		{ 0, 0, 1, 1, 2, 3, 4, 9, 15, 24, 30, 39, 50, 64, 82, 105, 134, 170, 214 },
		{ 0, 0, 1, 1, 2, 3, 4, 9, 15, 24, 30, 40, 52, 67, 86, 110, 140, 177, 222 },
		{ 0, 0, 1, 1, 2, 3, 4, 9, 15, 24, 30, 41, 54, 70, 90, 115, 146, 184, 230 },
		{ 0, 0, 1, 1, 2, 3, 4, 9, 15, 24, 30, 42, 56, 73, 94, 120, 152, 191, 238 },
		{ 0, 0, 1, 1, 2, 3, 4, 9, 15, 24, 31, 44, 59, 77, 99, 126, 159, 199, 247 },
		{ 0, 0, 1, 1, 2, 3, 4, 9, 16, 25, 32, 46, 62, 81, 104, 132, 166, 207, 256 },
		{ 0, 0, 1, 1, 2, 3, 4, 9, 16, 26, 33, 48, 65, 85, 109, 138, 173, 215, 265 },
		{ 0, 0, 1, 2, 2, 3, 5, 10, 17, 27, 34, 50, 68, 89, 114, 144, 180, 223, 274 },
		{ 0, 0, 1, 2, 2, 3, 5, 10, 17, 28, 35, 52, 71, 93, 119, 150, 187, 231, 283 },
		{ 0, 0, 1, 2, 2, 3, 5, 10, 18, 28, 36, 54, 74, 97, 124, 156, 194, 239, 292 },
		{ 0, 0, 1, 2, 2, 3, 5, 11, 18, 29, 37, 56, 77, 101, 129, 162, 201, 247, 301 },
		{ 0, 0, 1, 2, 3, 3, 5, 11, 19, 30, 38, 58, 80, 105, 134, 168, 208, 255, 310 },
		{ 0, 0, 1, 2, 3, 3, 5, 11, 19, 31, 39, 60, 83, 109, 139, 174, 215, 263, 319 },
		{ 0, 0, 1, 2, 3, 4, 6, 12, 20, 32, 40, 62, 86, 113, 144, 180, 222, 271, 328 },
		{ 0, 0, 1, 2, 3, 4, 6, 12, 20, 32, 41, 64, 89, 117, 149, 186, 229, 279, 337 },
		{ 0, 0, 1, 2, 3, 4, 6, 12, 21, 33, 42, 66, 92, 121, 154, 192, 236, 287, 346 },
		{ 0, 0, 1, 2, 3, 4, 6, 13, 22, 35, 44, 69, 96, 126, 160, 199, 244, 296, 356 },
		{ 0, 0, 1, 2, 3, 4, 6, 13, 23, 36, 46, 72, 100, 131, 166, 206, 252, 305, 366 },
		{ 0, 0, 1, 2, 3, 4, 7, 14, 24, 38, 48, 75, 104, 136, 172, 213, 260, 314, 376 },
		{ 0, 1, 2, 3, 4, 5, 7, 15, 25, 40, 50, 78, 108, 141, 178, 220, 268, 323, 386 },
		{ 0, 1, 2, 3, 4, 5, 7, 15, 26, 41, 52, 81, 112, 146, 184, 227, 276, 332, 396 },
		{ 0, 1, 2, 3, 4, 5, 8, 16, 27, 43, 54, 84, 116, 151, 190, 234, 284, 341, 406 },
		{ 0, 1, 2, 3, 4, 5, 8, 16, 28, 44, 56, 87, 120, 156, 196, 241, 292, 350, 416 },
		{ 0, 1, 2, 3, 4, 5, 8, 17, 29, 46, 58, 90, 124, 161, 202, 248, 300, 359, 426 },
		{ 0, 1, 2, 3, 4, 6, 9, 18, 30, 48, 60, 93, 128, 166, 208, 255, 308, 368, 436 },
		{ 0, 1, 2, 3, 4, 6, 9, 18, 31, 49, 62, 96, 132, 171, 214, 262, 316, 377, 446 },
		{ 0, 1, 2, 3, 5, 6, 9, 19, 32, 51, 64, 99, 136, 176, 220, 269, 324, 386, 456 },
		{ 0, 1, 2, 3, 5, 6, 9, 19, 33, 52, 66, 102, 140, 181, 226, 276, 332, 395, 466 },
		{ 0, 1, 2, 4, 5, 6, 10, 20, 34, 54, 68, 105, 144, 186, 232, 283, 340, 404, 476 },
		{ 0, 1, 2, 4, 5, 7, 10, 21, 35, 56, 71, 109, 149, 192, 239, 291, 349, 414, 487 },
		{ 0, 1, 2, 4, 5, 7, 11, 22, 37, 59, 74, 113, 154, 198, 246, 299, 358, 424, 498 },
		{ 0, 1, 3, 4, 6, 7, 11, 23, 38, 61, 77, 117, 159, 204, 253, 307, 367, 434, 509 },
		{ 0, 1, 3, 4, 6, 8, 12, 24, 40, 64, 80, 121, 164, 210, 260, 315, 376, 444, 520 },
		{ 0, 1, 3, 4, 6, 8, 12, 24, 41, 66, 83, 125, 169, 216, 267, 323, 385, 454, 531 },
		{ 0, 1, 3, 5, 6, 8, 12, 25, 43, 68, 86, 129, 174, 222, 274, 331, 394, 464, 542 },
		{ 0, 1, 3, 5, 7, 8, 13, 26, 44, 71, 89, 133, 179, 228, 281, 339, 403, 474, 553 },
		{ 0, 1, 3, 5, 7, 9, 13, 27, 46, 73, 92, 137, 184, 234, 288, 347, 412, 484, 564 },
		{ 0, 1, 3, 5, 7, 9, 14, 28, 47, 76, 95, 141, 189, 240, 295, 355, 421, 494, 575 },
		{ 0, 1, 3, 5, 7, 9, 14, 29, 49, 78, 98, 145, 194, 246, 302, 363, 430, 504, 586 },
		{ 1, 2, 4, 6, 8, 10, 15, 30, 50, 80, 101, 149, 199, 252, 309, 371, 439, 514, 597 },
		{ 1, 2, 4, 6, 8, 10, 15, 31, 52, 83, 104, 153, 204, 258, 316, 379, 448, 524, 608 },
		{ 1, 2, 4, 6, 8, 10, 16, 32, 54, 86, 108, 158, 210, 265, 324, 388, 458, 535, 620 },
		{ 1, 2, 4, 6, 8, 11, 16, 33, 56, 89, 112, 163, 216, 272, 332, 397, 468, 546, 632 },
		{ 1, 2, 4, 6, 9, 11, 17, 34, 58, 92, 116, 168, 222, 279, 340, 406, 478, 557, 644 },
		{ 1, 2, 4, 7, 9, 12, 18, 36, 60, 96, 120, 173, 228, 286, 348, 415, 488, 568, 656 },
		{ 1, 2, 4, 7, 9, 12, 18, 37, 62, 99, 124, 178, 234, 293, 356, 424, 498, 579, 668 },
		{ 1, 2, 5, 7, 10, 12, 19, 38, 64, 102, 128, 183, 240, 300, 364, 433, 508, 590, 680 },
		{ 1, 2, 5, 7, 10, 13, 19, 39, 66, 105, 132, 188, 246, 307, 372, 442, 518, 601, 692 },
		{ 1, 2, 5, 8, 10, 13, 20, 40, 68, 108, 136, 193, 252, 314, 380, 451, 528, 612, 704 },
	};

	float		fEXP_RATE_TABLE[EXPTABLE_RANGE] = 
	{
		//-30 -29   -28   -27   -26   -25   -24   -23   -22   -21
		0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		//-20 -19   -18   -17   -16   -15   -14   -13   -12   -11   -10   -9    -8    -7    -6    -5    -4    -3    -2    -1    0
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		//+1  +2   +3     +4    +5    +6    +7    +8    +9    +10   +11   +12   +13   +14   +15   +16   +17   +18   +19   +20
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		//+21 +22   +23   +24   +25   +26   +27   +28   +29   +30
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	LONGLONG	lnEXP_MAX_TABLE[MAX_LEVEL];
	LONGLONG	lnEXP_MAX_TABLE_2nd[MAX_LEVEL];
	DWORD		dwEXP_PC_TABLE[MAX_LEVEL];

	float		fPARTYEXPRANGE		= 80.0f;			//	����ġ ������ ������ �ִ� �Ÿ�.
	float		fPARTYEXP_S			= 0.006f;			//	��Ƽ ����ġ �й�� �������̿� ���� ���Һ���.
	//											  1    2    3    4    5    6    7    8   
	WORD		aPARTYEXP_ONE[MAXPARTY]		= {   100, 100, 100, 100, 100, 100, 100, 100 };
	WORD		aPARTYKILLEXP_ONE[MAXPARTY]	= {   100, 100, 100, 100, 100, 100, 100, 100 };

	DWORD		dwCLUB_PARTYNUM				= 5;		//	Ŭ�� â���� �ּ� ��Ƽ(�ʱ�) �ο�.
	DWORD		dwCLUB_DISSOLUTION_DAY		= 7;		//	Ŭ�� ��ü ���� ��.
	DWORD		dwCLUB_JOINBLOCK_DAY		= 5;		//	Ŭ�� Ż��� ���� ���� ��.
	DWORD		dwCLUB_AUTHORITY			= 24;		//	Ŭ�������� ���� ���� �ð�			
	DWORD		dwCLUB_ALLIANCE_SEC			= 24;		//	Ŭ�� ���� Ż��, ����� �簡�� ���ѽð�.
	DWORD		dwCLUB_ALLIANCE_DIS			= 24;		//	Ŭ�� ���� ��ü�� �Ἲ ���ѽð�.
	DWORD		dwCLUB_ALLIANCE_NUM			= 3;		//	Ŭ�� ���� �ִ� ����.

    DWORD		bCLUB_BATTLE				= FALSE;	//	Ŭ�� ��Ʋ ���� ����
	DWORD		dwCLUB_BATTLE_RANK			= 1;		//	Ŭ�� ��ũ Ȯ��
	DWORD		dwCLUB_BATTLE_MAX			= 5;		//  Ŭ�� ��Ʋ ���� ���� ����
	DWORD		dwCLUB_BATTLE_TIME			= 20;		//  Ŭ�� ��Ʋ �ð�(��) - �Է� ������� ������
	DWORD		dwCLUB_BATTLE_TIMEMIN		= 10;		//	Ŭ�� ��Ʋ �ּҽð�(��)
	DWORD		dwCLUB_BATTLE_TIMEMAX		= 1200;		//	Ŭ�� ��Ʋ �ִ�ð�(��)
	DWORD		dwCLUB_BATTLE_GUID_TIME		= 24;		//  Ŭ�� ��Ʋ ������ ���� �ð�(��)
	DWORD		dwCLUB_BATTLE_DIS_TIME		= 1;		//  Ŭ�� ��Ʋ ���� �� �׺� ������ �ð�(��)
	BOOL		bCLUB_BATTLE_ALLIANCE		= FALSE;	//  ���� Ŭ�� ���� ����

	BOOL		bCLUB_DEATHMATCH			= FALSE;	//	Ŭ�� ������ġ ���� ����
	DWORD		dwCLUB_DEATHMATCH_MEM		= 7;		//	Ŭ�� ������ġ ���� �����

	DWORD		dwMAX_CLUBRANK				= 5;		//  �ִ� Ŭ�� ��ũ

	GLCLUBRANK	sCLUBRANK[MAX_CLUBRANK]		=			//	Ŭ�� ��ũ�� ���.
	{
		GLCLUBRANK(30,0,1000000,15),
		GLCLUBRANK(45,80,2000000,20),
		GLCLUBRANK(60,100,3500000,30),
		GLCLUBRANK(80,140,5000000,40),
		GLCLUBRANK(100,180,7000000,50),
		GLCLUBRANK(120,220,10000000,60),
		GLCLUBRANK(130,230,20000000,70),
		GLCLUBRANK(140,240,30000000,80),
		GLCLUBRANK(150,250,40000000,90),
		GLCLUBRANK(160,260,50000000,100),
	};

	float fMAX_COMMISSION				= 50;		//	�ִ� ���� ���� ������ ����.
	float fDEFAULT_COMMISSION			= 5;		//	�� ���� ������ ������.
	float fEARNING_RATE					= 0.2f;		//	Ŭ�� ������ ������.
	float fEARNING_RATE_NPC				= 0.2f;		//	NPC ȣ�� ������ ������ 

	float fCDCERTIFY_DIST				= 30;		//	���� ���� �Ÿ�.
	float fCDCERTIFY_DIST2				= 5;		//	���� ���� �Ÿ�.
	float fCDCERTIFY_TIME				= 60;		//	���� �ҿ� �ð�.

	//	Note : ����ġ ����.
	float fEXP_SCALE = 1.0f;

	//	Note : ������ �����.
	float fITEM_DROP_SCALE = 1.0f;

	//	Note : �� �����.
	float fMONEY_DROP_SCALE = 1.0f;

	//	Note : ��� ������ �����.
	float fITEM_DROP_LOWER_SCALE = 1.0f;

	float fEXP_SCALE_BACKUP = fEXP_SCALE;
	float fITEM_DROP_SCALE_BACKUP = fITEM_DROP_SCALE;
	float fMONEY_DROP_SCALE_BACKUP = fMONEY_DROP_SCALE;

	//	Note : ----------------------------------------------------------------
	bool bSCHOOL_FREE_PK_ALWAYS = false;	//	�п��� ���� pk �׻� ���� ����.
	bool bSCHOOL_FREE_PK = false;			//	�п��� ���� pk on/off.
	bool bSCHOOL_FREE_PK_TIME_REAL = false;	//	�п��� ���� pk ���� �ð� ( on : ���� �ð�, off : ���ӽð� )
	bool bSCHOOL_FREE_PK_Z_FORCED = true;	//	�п��� ���� pk ���� ����.
	DWORD dwSCHOOL_FREE_PK_TIME_START = 21;	//	�п��� ���� pk ���� �ð�.
	DWORD dwSCHOOL_FREE_PK_TIME_TERM = 7;	//	�п��� ���� pk ���� �ð�.
	float fSCHOOL_FREE_PK_ITEM_DROP = 3;	//	�п��� ���� pk ������ ����� ���갪. ( �⺻ ����� + ���갪. )
	//	Note : ----------------------------------------------------------------

	bool bENCHANT_TERMINATE_ITEM = false;	//	��þƮ�� ������ �ļ� ����.

	//	Note : ----------------------------------------------------------------��� ����.
	bool bMONEY_DROP2FIELD = true;			//	�� �ٴڿ� ������ ���� ����.

	//	Note : ----------------------------------------------------------------���� Ȯ��.
	//													  1 -15
	float fGRADE_RATE[GRADE_LIMIT_MAX]				= {    100,    100,    100,    100, 33.33f, 
													    25.00f, 20.00f, 16.67f, 15.00f, 15.00f,
														15.00f, 15.00f, 15.00f, 15.00f, 15.00f };
	float fGRADE_RESET_RATE[GRADE_LIMIT_MAX]		= {      0,      0,      0,      0, 10.00f, 
														20.00f, 30.00f, 40.00f, 50.00f, 50.00f, 
														50.00f, 50.00f, 50.00f, 50.00f, 50.00f };
	float fGRADE_TERMINATE_RATE[GRADE_LIMIT_MAX]	= {      0,      0,      0,      0, 40.00f, 
														50.00f, 60.00f, 70.00f, 70.00f, 70.00f,
														70.00f,	70.00f,	70.00f,	70.00f,	70.00f };
		
	//add stats limit
	DWORD		dwPowMax = 65000;
	DWORD		dwStrMax = 65000;
	DWORD		dwSpiMax = 65000;
	DWORD		dwDexMax = 65000;
	DWORD		dwIntMax = 65000;
	DWORD		dwStaMax = 65000;

	//	Note : ----------------------------------------------------------------���� ����.
	std::string	strGRINDING_SUCCEED			= "";
	std::string	strGRINDING_FAIL			= "";
	std::string	strGRINDING_RESET			= "";
	std::string	strGRINDING_BROKEN			= "";

	std::string	strGAMBLING_SHUFFLE			= "";		// Monster7j
	std::string	strGAMBLING_WIN				= "";
	std::string	strGAMBLING_LOSE			= "";

	std::string	strITEMDROP_SUIT			= "";
	std::string	strITEMDROP_WAPON			= "";
	std::string	strITEMDROP_SHOES			= "";
	std::string	strITEMDROP_RING			= "";
	std::string	strITEMDROP_QBOX			= "";

	std::string	strITEMDROP_SCROLL			= "";
	std::string	strITEMDROP_COIN			= "";
	std::string	strITEMDROP_DRUGS			= "";

	std::string	strPICKUP_ITEM				= "";
	std::string	strQITEM_FACT				= "";
	std::string	strQITEM_BGM[QUESTION_SIZE];

	std::string	strSELECT_CHAR				= "";

	std::string	strREBIRTH_EFFECT			= "";
	std::string	strLEVELUP_EFFECT			= "";
	std::string	strSRIKE_EFFECT				= "";
	std::string	strSRIKE_ELMT_EFFECT[EMELEMENT_MAXNUM]	= { "", "", "", "", "", "", "", "", "" };

	std::string	strAMBIENT_EFFECT			= "";
	std::string	strERASE_EFFECT				= "";

	std::string	strSKILL_LEARN_EFFECT		= "";
	std::string	strSKILL_UP_EFFECT			= "";

	std::string strQUEST_START				= "";
	std::string strQUEST_END_SUCCEED		= "";
	std::string strQUEST_END_FAIL			= "";

	std::string	strMOB_GEM_EFFECT			= "";
	std::string	strMOB_DIE_BLOOD			= "";

	// PET
	std::string	strPET_GEN_EFFECT           = "";
	
	// vehicle
	std::string strVEHICLE_GEN_EFFECT		= "";

	std::string	strCONFRONT_BOUND			= "";
	std::string	strHALFALPHA_EFFECT			= "";

	std::string	strBLOW_NUMB_EFFECT			= "";
	std::string	strBLOW_STUN_EFFECT			= "";
	std::string	strBLOW_STONE_EFFECT		= "";
	std::string	strBLOW_BURN_EFFECT			= "";
	std::string	strBLOW_FROZEN_EFFECT		= "";

	std::string	strBLOW_MAD_EFFECT			= "";
	std::string	strBLOW_POISON_EFFECT		= "";
	std::string	strBLOW_CURSE_EFFECT		= "";

	std::string	strBLOW_BODY_NUMB_EFFECT	= "";
	std::string	strBLOW_BODY_STUN_EFFECT	= "";
	std::string	strBLOW_BODY_STONE_EFFECT	= "";
	std::string	strBLOW_BODY_BURN_EFFECT	= "";
	std::string	strBLOW_BODY_FROZEN_EFFECT	= "";

	std::string	strBLOW_BODY_MAD_EFFECT		= "";
	std::string	strBLOW_BODY_POISON_EFFECT	= "";
	std::string	strBLOW_BODY_CURSE_EFFECT	= "";

	std::string	strBLOW_EFFECTS[EMBLOW_SIZE];
	std::string	strBLOW_BODY_EFFECTS[EMBLOW_SIZE];

	std::string strCRUSHING_BLOW_EFFECT;		// ����Ÿ�� ����Ʈ

	std::string	strPKCOMBO_DOUBLE			= "";
	std::string	strPKCOMBO_TRIPLE			= "";
	std::string	strPKCOMBO_ULTRA			= "";
	std::string	strPKCOMBO_RAMPAGE			= "";

	GLCONST_CHARCLASS	cCONSTCLASS[GLCI_NUM_8CLASS] = 
	{
		GLCONST_CHARCLASS ( 10.0f, 0.9f, 1.00f, 0.08f,
							0.08f, 0.4f, 0.4f, 0.2f,
							SCHARSTATS(15,13,20,10,0,20), FCHARSTATS(2,3,1,1,1,3),
							35, 15, 5, 4,
							2, 2, 3, 1 ),

		GLCONST_CHARCLASS ( 12.0f, 0.8f, 1.00f, 0.07f,
							0.07f, 0.5f, 0.5f, 0.1f,
							SCHARSTATS(20,15,10,8,0,15), FCHARSTATS(3,2,1,1,1,2),
							40, 25, 5, 3,
							1, 3, 2, 1 ),

		GLCONST_CHARCLASS ( 9.0f, 1.0f, 1.00f, 0.09f,
							0.09f, 0.4f, 0.4f, 0.3f,
							SCHARSTATS(10,11,15,15,0,10), FCHARSTATS(2,1,1,1,1,1),
							25, 20, 3, 7,
							2, 2, 1, 3 ),
		
		GLCONST_CHARCLASS ( 8.0f, 1.2f, 1.00f, 0.10f,
							0.10f, 0.3f, 0.3f, 0.3f,
							SCHARSTATS(10,10,30,12,0,15), FCHARSTATS(1,1,1,1,1,1),
							20, 30, 3, 5,
							1, 3, 1, 2 ),
		
		GLCONST_CHARCLASS ( 1.7f, 0.84f, 1.1f, 0,
							0, 0.1f, 0.22f, 0.1f,
							SCHARSTATS(7,34,18,10,0,7), FCHARSTATS(0.3f,4.3f,0.66f,0.4f,0,2.7f),
							4, 5, 4, 3,
							0.9f, 0.1f, 0.4f, 0.3f ),
		
		GLCONST_CHARCLASS ( 1.7f, 0.8f, 1.1f, 0,
							0, 0.1f, 0.22f, 0.1f,
							SCHARSTATS(7,34,18,10,0,7), FCHARSTATS(0.3f,4.3f,0.66f,0.38f,0,2.7f),
							4, 5, 4, 3,
							1.0f, 0.1f, 0.4f, 0.2f ),
		
		GLCONST_CHARCLASS ( 10.0f, 0.9f, 1.00f, 0.08f,
							0.08f, 0.4f, 0.4f, 0.2f,
							SCHARSTATS(15,13,20,10,0,20), FCHARSTATS(2,3,1,1,1,3),
							35, 15, 5, 4,
							2, 2, 3, 1 ),
		
		GLCONST_CHARCLASS ( 12.0f, 0.8f, 1.00f, 0.07f,
							0.07f, 0.5f, 0.5f, 0.1f,
							SCHARSTATS(20,15,10,8,0,15), FCHARSTATS(3,2,1,1,1,2),
							40, 25, 5, 3,
							1, 3, 2, 1 ),
		
		GLCONST_CHARCLASS ( 9.0f, 1.0f, 1.00f, 0.09f,
							0.09f, 0.4f, 0.4f, 0.3f,
							SCHARSTATS(10,11,15,15,0,10), FCHARSTATS(2,1,1,1,1,1),
							25, 20, 3, 7,
							2, 2, 1, 3 ),
		
		GLCONST_CHARCLASS ( 8.0f, 1.2f, 1.00f, 0.10f,
							0.10f, 0.3f, 0.3f, 0.3f,
							SCHARSTATS(10,10,30,12,0,15), FCHARSTATS(1,1,1,1,1,1),
							20, 30, 3, 5,
							1, 3, 1, 2 ),

		GLCONST_CHARCLASS ( 9.0f, 1.0f, 1.00f, 0.09f,
							0.09f, 0.4f, 0.4f, 0.3f,
							SCHARSTATS(10,11,15,15,0,10), FCHARSTATS(2,1,1,1,1,1),
							25, 20, 3, 7,
							2, 2, 1, 3 ),

		GLCONST_CHARCLASS ( 9.0f, 1.0f, 1.00f, 0.09f,
							0.09f, 0.4f, 0.4f, 0.3f,
							SCHARSTATS(10,11,15,15,0,10), FCHARSTATS(2,1,1,1,1,1),
							25, 20, 3, 7,
							2, 2, 1, 3 ),

		GLCONST_CHARCLASS ( 9.0f, 1.0f, 1.00f, 0.09f,
							0.09f, 0.4f, 0.4f, 0.3f,
							SCHARSTATS(10,11,15,15,0,10), FCHARSTATS(2,1,1,1,1,1),
							25, 20, 3, 7,
							2, 2, 1, 3 ),

		GLCONST_CHARCLASS ( 9.0f, 1.0f, 1.00f, 0.09f,
							0.09f, 0.4f, 0.4f, 0.3f,
							SCHARSTATS(10,11,15,15,0,10), FCHARSTATS(2,1,1,1,1,1),
							25, 20, 3, 7,
							2, 2, 1, 3 ),

		GLCONST_CHARCLASS ( 9.0f, 1.0f, 1.00f, 0.09f,
							0.09f, 0.4f, 0.4f, 0.3f,
							SCHARSTATS(10,11,15,15,0,10), FCHARSTATS(2,1,1,1,1,1),
							25, 20, 3, 7,
							2, 2, 1, 3 ),

		GLCONST_CHARCLASS ( 9.0f, 1.0f, 1.00f, 0.09f,
							0.09f, 0.4f, 0.4f, 0.3f,
							SCHARSTATS(10,11,15,15,0,10), FCHARSTATS(2,1,1,1,1,1),
							25, 20, 3, 7,
							2, 2, 1, 3 ),
	};

	std::vector<std::string>	vecGUIDANCE_FILE;
	std::vector<std::string>	vecClubDM_FILE;


	std::string					strCLICK_EFFECT = "";
	std::string					strTARGET_EFFECT = "";
	std::string					strMINE_EFFECT = "";
	std::string					strCOMPLETE_NPC_EFFECT = "";

	/*combatpoint logic, Juver, 2017/05/27 */
	WORD	wCombatPoint_MAX = 8000;
	WORD	wCombatPoint_PK = 200;

	/*vehicle booster system, Juver, 2017/08/11 */
	float	fVehicleBoosterChargeTime	= 20.0f;
	float	fVehicleBoosterBoostTime	= 10.0f;
	float	fVehicleBoosterAddSpeed		= 100.0f;

	/*Money Luck, Juver, 2017/08/24 */
	float fMONEY_LUCK_RATE = 1.0f;

	/*pvp tyranny, Juver, 2017/08/25 */
	std::string	strTyrannyFile = "";
	std::string	strSchoolEffect[TYRANNY_SCHOOL_SIZE]	= { "NULL", "NULL", "NULL" };

	/*quest rate, Juver, 2017/09/27 */
	float fQuestExpRate = 1.0f;
	float fQuestMoneyRate = 1.0f;

	/*character simple, Juver, 2017/10/01 */
	std::string	strSimpleWearM[SLOT_WEAR_SIMPLE]	= { "", "", "", "", "" };
	std::string	strSimpleWearF[SLOT_WEAR_SIMPLE]	= { "", "", "", "", "" };

	/*contribution/activity bonus, Juver, 2017/10/14 */
	BOOL bContributionPointBonusTimer = FALSE;
	float fContributionPointBonusTime = 60.0f;
	WORD wContributionPointBonusAdd = 1;

	BOOL bActivityPointBonusTimer = FALSE;
	float fActivityPointBonusTime = 60.0f;
	WORD wActivityPointBonusAdd = 1;
	
	/*activity system, Juver, 2017/10/30 */
	std::string strCOMPLETE_ACTIVITY_EFFECT = "";

	/*school wars, Juver, 2018/01/19 */
	std::string	strSchoolWarsFile = "";

	/*pvp capture the flag, Juver, 2018/01/23 */
	std::string strCaptureTheFlagFile = "";
	std::string	strCaptureTheFlagEffect[CAPTURE_THE_FLAG_TEAM_SIZE]	= { "", "" };
	std::string	strCaptureTheFlagDirectionEffect[CAPTURE_THE_FLAG_TEAM_SIZE]	= { "", "" };

	char		szCharSkin[GLCI_NUM_8CLASS][MAX_PATH] =
	{
		"o_m.chf", "o_m.chf", "o_w.chf", "o_w.chf", "o_m.chf", "o_w.chf", "o_w.chf", "o_w.chf", "o_m.chf", "o_m.chf",
		"o_m.chf", "o_w.chf", "o_m.chf", "o_w.chf", "o_m.chf", "o_w.chf",
	};

	std::string strCLASS_INIT[MAX_SCHOOL][GLCI_NUM_8CLASS] =
	{
		{ "class00.charset", "class01.charset", "class02.charset", "class03.charset", "class04.charset", "class05.charset", "class06.charset", "class07.charset", "class08.charset", "class09.charset",
			"class0A.charset", "class0B.charset", "class0C.charset", "class0D.charset", "class0E.charset", "class0F.charset" },
		{ "class10.charset", "class11.charset", "class12.charset", "class13.charset", "class14.charset", "class15.charset", "class16.charset", "class17.charset", "class18.charset", "class19.charset",
			"class1A.charset", "class1B.charset", "class1C.charset", "class1D.charset", "class1E.charset", "class1F.charset" },
		{ "class20.charset", "class21.charset", "class22.charset", "class23.charset", "class24.charset", "class25.charset", "class26.charset", "class27.charset", "class28.charset", "class29.charset",
			"class2A.charset", "class2B.charset", "class2C.charset", "class2D.charset", "class2E.charset", "class2F.charset" },
	};

	PCHARDATA2	pCharData2[MAX_SCHOOL][GLCI_NUM_8CLASS] =
	{
		{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	};

	BOOL VAID_CHAR_DATA2 ( WORD wSchool, EMCHARINDEX emIndex )	{ return pCharData2[wSchool][emIndex] != NULL; }
	SCHARDATA2& GET_CHAR_DATA2 ( WORD wSchool, EMCHARINDEX emIndex )
	{
		GASSERT(wSchool<MAX_SCHOOL);
		GASSERT(emIndex<GLCI_NUM_8CLASS);

		return *pCharData2[wSchool][emIndex];
	}

	void SETEXP_SCALE ( float fScale )
	{
		if ( fScale < 1.0f )	fScale = 1.0f;
		if ( fScale > 10.0f )	fScale = 10.0f;

		fEXP_SCALE = fScale;
	}

	float GETEXP_SCALE ()
	{
		return fEXP_SCALE;
	}

	const char* GETSCHOOLNAME ( WORD wSCHOOL )
	{
		if ( wSCHOOL >= MAX_SCHOOL )	return NULL;
		return strSCHOOLNAME[wSCHOOL].c_str();
	}

	DWORD GETEXP ( int nAttackerLev, int nDefenserLev )
	{
		//	Note : ����ġ ���̺� ������.  (GLCONST_CHAR::EXPBASEINDEX+1) ���� +1�� �������̸� ������ �ȵ�����
		//			�ʹ� ������ +1 ������ �����Ǿ� ��� �����ǰ� �ִ� ��Ȳ��.
		int	nDiffLev = nDefenserLev - nAttackerLev;
		int nResultIndex = nDiffLev + GLCONST_CHAR::EXPBASEINDEX+1;
		
		if ( nResultIndex > (GLCONST_CHAR::EXPTABLE_LVL - 1) )		nResultIndex = GLCONST_CHAR::EXPTABLE_LVL - 1;
		else if ( nResultIndex < 0 )								nResultIndex = 0;
		GASSERT ( 0 <= nResultIndex && nResultIndex < GLCONST_CHAR::EXPTABLE_LVL );
		
		int nexp_lvl = nAttackerLev / EXP_LVL_STEP;
		if ( nexp_lvl < 0 )						nexp_lvl = 0;
		else if ( nexp_lvl >= EXPTABLE_SIZE )	nexp_lvl = EXPTABLE_SIZE-1;

		return (DWORD)(GLCONST_CHAR::wEXPTABLE[nexp_lvl][nResultIndex]*GETEXP_SCALE());
	}

	DWORD GETEXP_PC ( WORD wLev )
	{
		WORD wLEVEL = wLev-1;
		if ( wLEVEL >= MAX_LEVEL )		return 0;
		
		return dwEXP_PC_TABLE[wLEVEL];
	}

	float GETEXP_RATE ( int nAttackerLev, int nDefenserLev )
	{
		int	nDiffLev = nDefenserLev - nAttackerLev;
		int nResultIndex = nDiffLev + GLCONST_CHAR::EXPTABLE_RANGE_BASE;

		if ( nResultIndex >= GLCONST_CHAR::EXPTABLE_RANGE )		nResultIndex = GLCONST_CHAR::EXPTABLE_RANGE-1;
		else if ( nResultIndex < 0 )							nResultIndex = 0;

		return GLCONST_CHAR::fEXP_RATE_TABLE[nResultIndex];
	}
};
	
namespace GLCONST_PET
{
	PGLPET			pGLPET[PET_TYPE_SIZE] = 
	{  
		NULL, NULL, NULL, NULL, 
		NULL, NULL, NULL, NULL, 
		NULL, NULL, NULL, NULL, 
		NULL, NULL  
	};

	char			szPetInit[PET_TYPE_SIZE][MAX_PATH] = 
	{ 
		"pet_01.charset", "pet_02.charset", "pet_03.charset", "pet_04.charset" , 
		"pet_05.charset", "pet_06.charset", "pet_07.charset", "pet_08.charset" ,
		"pet_09.charset", "pet_10.charset", "pet_11.charset", "pet_12.charset" ,
		"pet_13.charset", "pet_14.charset"
	};

	PETSTYLE		sPETSTYLE[PET_TYPE_SIZE];

	BOOL			bCHANGEABLECOLOR[PET_TYPE_SIZE] = 
	{ 
		FALSE, FALSE, FALSE, FALSE,
		FALSE, FALSE, FALSE, FALSE,
		FALSE, FALSE, FALSE, FALSE,
		FALSE, FALSE
	};


	int				nFullDecrement[PET_TYPE_SIZE]; // ������ ����ġ
	
	float			fRunArea	   = 60.0f; // �޷��߸� �ϴ� �Ÿ�
	float			fWalkArea	   = 40.0f; // �ɾ�߸� �ϴ� �Ÿ�
	float			fOwnerDistance = 20.0f; // ���ΰ��� ���� �Ÿ�
	int				nMAXVIEWRANGE  = 50;    // �ֺ� �������� Ž���� �� �ִ� �Ÿ�
	float			fMaginotLineHP  = 20.0f; // �ڵ����� ��ų�� ������ ������ �Դ� ��ġ(%) - HP
	float			fMaginotLineMP  = 20.0f; // �ڵ����� ��ų�� ������ ������ �Դ� ��ġ(%) - MP
	float			fMaginotLineSP  = 20.0f; // �ڵ����� ��ų�� ������ ������ �Դ� ��ġ(%) - SP

	PGLPET GetPetData ( PETTYPE emTYPE )
	{
		for ( WORD i = 0; i < PET_TYPE_SIZE; ++i )
		{
			if ( pGLPET[i]->m_emTYPE == emTYPE ) return pGLPET[i];
		}

		return NULL;
	}

	PETSTYLE GetPetStyle ( PETTYPE emTYPE )
	{
		for ( WORD i = 0; i < PET_TYPE_SIZE; ++i )
		{
			if ( pGLPET[i]->m_emTYPE == emTYPE ) return sPETSTYLE[i];
		}

		return PETSTYLE();
	}
	BOOL IsChangeablePetColor ( PETTYPE emTYPE ) { return bCHANGEABLECOLOR[emTYPE]; }
};

namespace MINIGAME_ODDEVEN // �̴� ����, Ȧ¦ ����
{
	float	fReturnRate[MAX_ROUND]	= {1.5f,2.0f,3.0f,4.0f,5.0f};	// ���� ���� �μ�(�������� = ����*1ȸ���μ�*2ȸ���μ�...)
	float	fSuccessRate[MAX_ROUND]	= {0.5f,0.4f,0.2f,0.1f,0.05f};	// ���� Ȱ��
	float	fTimeLimit				= 60.0f;						// ���� �ð�(��)
	float	fShuffleTime			= 2.0f;							// ���� �ð�(��)
	UINT	uiMaxBattingMoney		= 1000000000;					// �ִ� ���� ���� �ݾ�
};

namespace GLCONST_SUMMON
{
	PGLSUMMON		pGLSUMMON[SUMMON_TYPE_SIZE] = { NULL };
	char			szSummonInit[SUMMON_TYPE_SIZE][MAX_PATH] = { "Summon_01.charset", "Summon_02.charset", "Summon_03.charset", "Summon_04.charset" };
	DWORD			m_dwMaxSummon[SUMMON_TYPE_SIZE] = { 1, 1, 1, 1 };

	PGLSUMMON GetSummonData ( SUMMON_TYPE emTYPE )
	{	
		for ( WORD i = 0; i < SUMMON_TYPE_SIZE; ++i )
		{
			if ( pGLSUMMON[i]->m_emTYPE == emTYPE ) return pGLSUMMON[i];
		}

		return NULL;
	}

	DWORD GetMaxSummon( SUMMON_TYPE emTYPE )
	{
		if ( emTYPE >= SUMMON_TYPE_SIZE )	return 0;
		return m_dwMaxSummon[emTYPE];
	}

}

namespace GLCONST_VEHICLE
{
	PGLVEHICLE		pGLVEHICLE[VEHICLE_TYPE_SIZE] = { NULL, NULL, NULL, NULL };
	char			szVehicleInit[VEHICLE_TYPE_SIZE][MAX_PATH] = { "Vehicle_01.charset", "Vehicle_02.charset", "Vehicle_03.charset", "Vehicle_04.charset"  };

	int				nFullDecrVehicle[VEHICLE_TYPE_SIZE]; // ������ ����ġ
	
	PGLVEHICLE GetVehicleData ( VEHICLE_TYPE emTYPE )
	{
		for ( WORD i = 0; i < VEHICLE_TYPE_SIZE; ++i )
		{
			if ( pGLVEHICLE[i]->m_emTYPE == emTYPE ) return pGLVEHICLE[i];
		}

		return NULL;
	}
};

namespace GLCONST_ATTENDANCE
{	
	ATTEND_REWARD	sATEEND_REWARD[MAX_REWARD];
	DWORD			dwMAXREWARD = 0;
	DWORD			dwAttendTime = 0;
};

namespace HAIRCOLOR
{
	WORD wHairColor[GLCI_NUM_8CLASS][MAX_HAIR] = 
	{ 
		22923, 30719, 32486, 24447, 32258, 32594, 31743, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,	// �����γ�
		30719, 22923, 32486, 24447, 32258, 32594, 31743, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,	// �˵��γ�
		18008, 30278, 31503, 24004, 32488, 27245, 28364, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,	// ��úο�
		30278, 18008, 31503, 24004, 32488, 27245, 28364, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,	// �⿹�ο�
		22923, 30719, 32486, 24447, 32258, 32594, 31743, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,	// �ذ��γ�
		18008, 30278, 31503, 24004, 32488, 27245, 28364, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,	// �ذ��ο�
		30278, 18008, 31503, 24004, 32488, 27245, 28364, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,	// �����ο�
		18008, 30278, 31503, 24004, 32488, 27245, 28364, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,	// �˵��ο�
		30719, 22923, 32486, 24447, 32258, 32594, 31743, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,	// ��úγ�
		22923, 30719, 32486, 24447, 32258, 32594, 31743, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,	// �⿹�γ�
		30719, 22923, 32486, 24447, 32258, 32594, 31743, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,
		18008, 30278, 31503, 24004, 32488, 27245, 28364, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,
		30719, 22923, 32486, 24447, 32258, 32594, 31743, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,
		18008, 30278, 31503, 24004, 32488, 27245, 28364, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,
		30719, 22923, 32486, 24447, 32258, 32594, 31743, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,
		18008, 30278, 31503, 24004, 32488, 27245, 28364, 32767,	0, 31744, 31775, 992, 1023, 31, 32736, 32224, 15391, 12794, 32499, 20831,
	};

	WORD GetHairColor ( WORD wClass, WORD wStyle ) { return wHairColor[wClass][wStyle]; }
};


//----------------------------------------------------------------------------------------
GLogicData& GLogicData::GetInstance()
{
	static GLogicData Instance;
	return Instance;
}

GLogicData::GLogicData(void)
{
}

GLogicData::~GLogicData(void)
{
	ClearData ();
}

HRESULT GLogicData::LoadData ( BOOL bServer, bool bPastLoad /*= FALSE */ )
{
	CGLCommentFile glCommentFile;
	if( glCommentFile.LOADFILE("comment.ini") == FALSE ) return E_FAIL;

	// Note : ��Ʈ�����̺��� �ε��Ѵ�. by ���
	//
	GLStringTable::GetInstance().CLEAR();
	GLStringTable::GetInstance().LOADFILE( GLItemMan::GetInstance()._STRINGTABLE, GLStringTable::ITEM );
	GLStringTable::GetInstance().LOADFILE( GLSkillMan::GetInstance()._STRINGTABLE, GLStringTable::SKILL );
	GLStringTable::GetInstance().LOADFILE( GLCrowDataMan::GetInstance()._STRINGTABLE, GLStringTable::CROW );

	//if( GLItemMan::GetInstance().LoadFile ( "item.isf", bServer, bPastLoad ) == E_FAIL ) return E_FAIL;
	//if( GLCrowDataMan::GetInstance().LoadFile ( "Crow.mnsf", bServer, bPastLoad ) == E_FAIL ) return E_FAIL;
	//if( GLSkillMan::GetInstance().LoadFile ( "skill.ssf", bPastLoad ) == E_FAIL ) return E_FAIL;
	if( GLItemMan::GetInstance().LoadFile ( "item.isf", bServer, TRUE ) == E_FAIL ) return E_FAIL;
	if( GLCrowDataMan::GetInstance().LoadFile ( "Crow.mnsf", bServer, TRUE ) == E_FAIL ) return E_FAIL;
	if( GLSkillMan::GetInstance().LoadFile ( "skill.ssf", TRUE ) == E_FAIL ) return E_FAIL;
	GLQuestMan::GetInstance().LoadFile ( "quest.lst", bServer==TRUE );

	GLCONST_CHAR::LOADFILE ( "default.charclass", bServer );
	GLCONST_ATTENDANCE::LoadFile ( "Attendance.ini", bServer );

	GLBusStation::GetInstance().LOAD( "busstation.ini" );
	GLTaxiStation::GetInstance().LoadFile( "taxistation.tsf" );
	GLItemMixMan::GetInstance().LoadFile( "ItemMix.ims", bServer );

	/*activity system, Juver, 2017/10/21 */
	GLActivity::GetInstance().LoadFile( "Activity.asf", bServer );

	for ( WORD i=0; i<MAX_SCHOOL; i++ )
	{
		for ( WORD j=0; j<GLCI_NUM_8CLASS; j++ )
		{
			PCHARDATA2 pNEW_CHARDATA = new SCHARDATA2;
       		pNEW_CHARDATA->LOADFILE ( GLCONST_CHAR::strCLASS_INIT[i][j].c_str() );

			SAFE_DELETE(GLCONST_CHAR::pCharData2[i][j]);
			GLCONST_CHAR::pCharData2[i][j] = pNEW_CHARDATA;
		}
	}

	if ( bServer )
	{
		for ( int nClass=0; nClass<GLCI_NUM_8CLASS; ++nClass )
		{
			GLCONST_CHAR::cCONSTCLASS[nClass].LoadAniSet ( GLCONST_CHAR::szCharSkin[nClass] );
		}
	}

	// PET Data �ε�
	for ( WORD i = PET_TYPE_A; i < PET_TYPE_SIZE; ++i )
	{
		PGLPET pPet = new GLPET;
		if( !pPet->LoadFile ( GLCONST_PET::szPetInit[i], (PETTYPE)i ) )
		{
			return E_FAIL;
		}
	}

	// Ż�� data �ε� ( �ȿ� ���� ���� )
	for ( WORD i = VEHICLE_TYPE_BOARD; i < VEHICLE_TYPE_SIZE; ++i )
	{
		PGLVEHICLE pVehicle = new GLVEHICLE;
		if ( !pVehicle->LoadFile( GLCONST_VEHICLE::szVehicleInit[i], (VEHICLE_TYPE) i ))
		{
			return E_FAIL;
		}
	}

	/*skill summon, Juver, 2017/10/08 */
	// ��ȯ�� data �ε� ( �ȿ� ���� ���� )
	for ( WORD i = SUMMON_TYPE_A; i < SUMMON_TYPE_SIZE; ++i )
	{
		PGLSUMMON pSummon = new GLSUMMON;
		if ( !pSummon->LoadFile( GLCONST_SUMMON::szSummonInit[i], (SUMMON_TYPE) i ))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

HRESULT GLogicData::ClearData ()
{
	GLCrowDataMan::GetInstance().FinalCleanup ();
	GLSkillMan::GetInstance().FinalCleanup ();

	for ( int i=0; i<GLCI_NUM_8CLASS; i++ )	GLCONST_CHAR::cCONSTCLASS[i].ClearAniSet();
	
	for ( int i=0; i<MAX_SCHOOL; i++ )
	for ( int j=0; j<GLCI_NUM_8CLASS; j++ )
	{
		SAFE_DELETE(GLCONST_CHAR::pCharData2[i][j]);
	}

	for ( int i = 0; i < PET_TYPE_SIZE; ++i )
	{
		SAFE_DELETE( GLCONST_PET::pGLPET[i] );
	}

	for ( WORD i = VEHICLE_TYPE_BOARD; i < VEHICLE_TYPE_SIZE; ++i )
	{
		SAFE_DELETE( GLCONST_VEHICLE::pGLVEHICLE[i] );
	}

	for ( WORD i = SUMMON_TYPE_A; i < SUMMON_TYPE_SIZE; ++i )
	{
		SAFE_DELETE( GLCONST_SUMMON::pGLSUMMON[i] );
	}

	return S_OK;
}

HRESULT GLogicData::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr=S_OK;

	hr = GLItemMan::GetInstance().InitDeviceObjects ( pd3dDevice );
	if ( FAILED(hr) )	return hr;

	return S_OK;
}

HRESULT GLogicData::DeleteDeviceObjects ()
{
	HRESULT hr=S_OK;

	hr = GLItemMan::GetInstance().DeleteDeviceObjects ();
	if ( FAILED(hr) )	return hr;

	return S_OK;
}

