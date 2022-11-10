#ifndef GLSKILL_APPLY_H_
#define GLSKILL_APPLY_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../Lib_Engine/Common/BaseStream.h"
#include "../../Lib_Engine/Common/StringFile.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/Common/STRINGUTILS.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"

#include "./GLCharDefine.h"
#include "./GLSkillDefine.h"

namespace SKILL
{
	enum EMTYPES
	{
		EMFOR_HP				= 0,	//	ü��ġ ��ȭ.
		EMFOR_MP				= 1,	//	���ġ ��ȭ.
		EMFOR_SP				= 2,	//	�ٷ�ġ ��ȭ.

		EMFOR_VARHP				= 3,	//	ä��ġ ��ȭ��.
		EMFOR_VARMP				= 4,	//	���ġ ��ȭ��.
		EMFOR_VARSP				= 5,	//	�ٷ�ġ ��ȭ��.

		EMFOR_DEFENSE			= 6,	//	���ġ ��ȭ.
		EMFOR_CURE				= 7,	//	�ص�. ( �ص� ���� �ʿ� )

		EMFOR_HITRATE			= 8,	//	������.
		EMFOR_AVOIDRATE			= 9,	//	ȸ����.

		EMFOR_VARAP				= 10,	//	��� (ä��,���,�ٷ�) ��ȭ��.

		EMFOR_VARDAMAGE			= 11,	//	����ġ ��ȭ��.
		EMFOR_VARDEFENSE		= 12,	//	���ġ ��ȭ��.

		EMFOR_PA				= 13,	//	����ġ.
		EMFOR_SA				= 14,	//	���ġ.
		EMFOR_MA				= 15,	//	���ġ.

		EMFOR_HP_RATE			= 16,	//	HP ������.
		EMFOR_MP_RATE			= 17,	//	MP ������.
		EMFOR_SP_RATE			= 18,	//	SP ������.

		EMFOR_PET_GETALLITEMS	= 19,	//	��� ������ �ݱ�	// PetData
		EMFOR_PET_GETRAREITEMS	= 20,	//	���� �����۸� �ݱ�
		EMFOR_PET_GETPOTIONS	= 21,	//	��ǰ�� �����۸� �ݱ�
		EMFOR_PET_GETMONEY		= 22,	//	���� �ݱ�
		EMFOR_PET_GETSTONE		= 23,	//	������ �����۸� �ݱ�
		EMFOR_PET_HEAL			= 24,	//	������ HP ȸ�� �ӵ� ���
		EMFOR_PET_SUPPROT		= 25,	//	������ HP, MP, SP ȸ���� ���
		EMFOR_PET_BACKUP_ATK	= 26,	//	������ ���ݷ�(��) ���
		EMFOR_PET_BACKUP_DEF	= 27,	//	������ ����(��) ���
		EMFOR_PET_AUTOMEDISON	= 28,	//	�ڵ� ��ǰ ���
		EMFOR_PET_PROTECTITEMS	= 29,	//	������ ������ �Ҿ������ �ʵ��� ��ȣ

		EMFOR_RESIST			= 30,	//	���� ��ȭ��

		EMFOR_SUMMONTIME		= 31,	/*summon time, Juver, 2017/12/12 */

		FOR_TYPE_SIZE			= 32
	};

	struct SSTATE_BLOW
	{
		float			fRATE;		//	�߻� Ȯ��.
		float			fVAR1;		//	���� �� 1.
		float			fVAR2;		//	���� �� 2.

		SSTATE_BLOW () :
			fRATE(0.0f),
			fVAR1(0.0f),
			fVAR2(0.0f)
		{
		}
	};

	struct SSPEC_100
	{
		float	fVAR1;
		float	fVAR2;
		DWORD	dwFLAG;

		SSPEC_100 () :
			fVAR1(0.0f),
			fVAR2(0.0f),
			dwFLAG(NULL)
		{
		}
	};

	struct SSPEC_108
	{
		float		fVAR1;
		float		fVAR2;
		DWORD		dwFLAG;
		SNATIVEID	dwNativeID;

		SSPEC_108 () :
			fVAR1(0.0f),
			fVAR2(0.0f),
			dwFLAG(NULL),
			dwNativeID(NATIVEID_NULL())
		{
		}
	};

	struct SSPEC
	{
		float		fVAR1;
		float		fVAR2;
		float		fVAR3;
		float		fVAR4;
		DWORD		dwFLAG;
		SNATIVEID	dwNativeID;

		SSPEC () :
			fVAR1(0.0f),
			fVAR2(0.0f),
			fVAR3(1.0f),
			fVAR4(1.0f),
			dwFLAG(NULL),
			dwNativeID(NATIVEID_NULL())
		{
		}

		void Assign( SSPEC_100 &sOldData )
		{
			fVAR1 = sOldData.fVAR1;
			fVAR2 = sOldData.fVAR2;
			fVAR3 = 1.0f;
			fVAR4 = 1.0f;
			dwFLAG = sOldData.dwFLAG;
		}

		void Assign( SSPEC_108 &sOldData )
		{
			fVAR1 = sOldData.fVAR1;
			fVAR2 = sOldData.fVAR2;
			fVAR3 = 1.0f;
			fVAR4 = 1.0f;
			dwFLAG = sOldData.dwFLAG;
			dwNativeID = sOldData.dwNativeID;
		}
	};

	struct CDATA_LVL_100
	{
		float			fDELAYTIME;			//	������ Ÿ��.
		float			fLIFE;				//	���ӽð�.
		WORD			wAPPLYRANGE;		//	���� ����.
		WORD			wAPPLYNUM;			//	���� ����.
		WORD			wAPPLYANGLE;		//	���� ����.
		WORD			wPIERCENUM;			//	���� ����.
		float			fBASIC_VAR;			//	��ȭ��.
		WORD			wUSE_ARROWNUM;		//	�Ҹ� ȭ�� ����.
		WORD			wUSE_HP;			//	���� HP ������.
		WORD			wUSE_MP;			//	���� MP ������.
		WORD			wUSE_SP;			//	���� SP ������.
		WORD			wUSE_HP_PTY;		//	���� HP ��Ƽ�� ������.
		WORD			wUSE_MP_PTY;		//	���� MP ��Ƽ�� ������.
		WORD			wUSE_SP_PTY;		//	���� SP ��Ƽ�� ������.
	};

	struct CDATA_LVL_101
	{
		float			fDELAYTIME;			//	������ Ÿ��.
		float			fLIFE;				//	���ӽð�.
		WORD			wAPPLYRANGE;		//	���� ����.
		WORD			wAPPLYNUM;			//	���� ����.
		WORD			wAPPLYANGLE;		//	���� ����.
		WORD			wPIERCENUM;			//	���� ����.
		WORD			wTARNUM;			//	Ÿ�� ����.
		float			fBASIC_VAR;			//	��ȭ��.
		WORD			wUSE_ARROWNUM;		//	�Ҹ� ȭ�� ����.
		WORD			wUSE_CHARMNUM;		//	�Ҹ� ���� ����.
		WORD			wUSE_EXP;			//	���� EXP ������.
		WORD			wUSE_HP;			//	���� HP ������.
		WORD			wUSE_MP;			//	���� MP ������.
		WORD			wUSE_SP;			//	���� SP ������.
		WORD			wUSE_HP_PTY;		//	���� HP ��Ƽ�� ������.
		WORD			wUSE_MP_PTY;		//	���� MP ��Ƽ�� ������.
		WORD			wUSE_SP_PTY;		//	���� SP ��Ƽ�� ������.
	};

	struct CDATA_LVL_102
	{
		float			fDELAYTIME;			//	������ Ÿ��.
		float			fLIFE;				//	���ӽð�.
		WORD			wAPPLYRANGE;		//	���� ����.
		WORD			wAPPLYNUM;			//	���� ����.
		WORD			wAPPLYANGLE;		//	���� ����.
		WORD			wPIERCENUM;			//	���� ����.
		WORD			wTARNUM;			//	Ÿ�� ����.
		float			fBASIC_VAR;			//	��ȭ��.
		WORD			wUSE_ARROWNUM;		//	�Ҹ� ȭ�� ����.
		WORD			wUSE_CHARMNUM;		//	�Ҹ� ���� ����.
		WORD			wUSE_BULLETNUM;	
		WORD			wUSE_EXP;			//	���� EXP ������.
		WORD			wUSE_HP;			//	���� HP ������.
		WORD			wUSE_MP;			//	���� MP ������.
		WORD			wUSE_SP;			//	���� SP ������.
		WORD			wUSE_CP;
		WORD			wUSE_HP_PTY;		//	���� HP ��Ƽ�� ������.
		WORD			wUSE_MP_PTY;		//	���� MP ��Ƽ�� ������.
		WORD			wUSE_SP_PTY;		//	���� SP ��Ƽ�� ������.
	};

	//	���� �� ���뺰 ����.
	struct CDATA_LVL
	{
		float			fDELAYTIME;			//	������ Ÿ��.
		float			fLIFE;				//	���ӽð�.
		WORD			wAPPLYRANGE;		//	���� ����.
		WORD			wAPPLYNUM;			//	���� ����.
		WORD			wAPPLYANGLE;		//	���� ����.
		WORD			wPIERCENUM;			//	���� ����.
		WORD			wTARNUM;			//	Ÿ�� ����.
		float			fBASIC_VAR;			//	��ȭ��.
		WORD			wUSE_ARROWNUM;		//	�Ҹ� ȭ�� ����.
		WORD			wUSE_CHARMNUM;		//	�Ҹ� ���� ����.
		WORD			wUSE_BULLETNUM;	
		WORD			wUSE_EXP;			//	���� EXP ������.
		WORD			wUSE_HP;			//	���� HP ������.
		WORD			wUSE_MP;			//	���� MP ������.
		WORD			wUSE_SP;			//	���� SP ������.
		WORD			wUSE_CP;
		DWORD			dwDATA;				// official unknown data
		WORD			wUSE_HP_PTY;		//	���� HP ��Ƽ�� ������.
		WORD			wUSE_MP_PTY;		//	���� MP ��Ƽ�� ������.
		WORD			wUSE_SP_PTY;		//	���� SP ��Ƽ�� ������.

		void Assign ( CDATA_LVL_100 &sOldData );
		void Assign ( CDATA_LVL_101 &sOldData );
		void Assign ( CDATA_LVL_102 &sOldData );

		CDATA_LVL (void) :
			fDELAYTIME(0.0f),
			fLIFE(0.0f),
			wAPPLYRANGE(0),
			wAPPLYNUM(1),
			wAPPLYANGLE(0),
			wPIERCENUM(1),
			wTARNUM(1),
			fBASIC_VAR(0.0f),
			wUSE_ARROWNUM(0),
			wUSE_CHARMNUM(0),
			wUSE_BULLETNUM(0),
			wUSE_EXP(0),
			wUSE_HP(0),
			wUSE_MP(0),
			wUSE_SP(0),
			wUSE_CP(0),
			dwDATA(0),
			wUSE_HP_PTY(0),
			wUSE_MP_PTY(0),
			wUSE_SP_PTY(0)
		{
		}
	};

	struct SIMPACTS_108
	{
		EMIMPACT_ADDON		emADDON;					//	�ΰ�ȿ�� ����.
		float				fADDON_VAR[MAX_LEVEL];		//	��ȭ ��ġ.

		SIMPACTS_108()
			: emADDON(EMIMPACTA_NONE)
		{
			for ( int i=0; i<MAX_LEVEL; ++i )	
				fADDON_VAR[i] = 0;
		};
	};

	struct SSPECS_108
	{
		EMSPEC_ADDON		emSPEC;						//	Ư��.
		SKILL::SSPEC_108	sSPEC[MAX_LEVEL];			//	Ư�� ��� ������.

		SSPECS_108()
			: emSPEC(EMSPECA_NULL)
		{
			for ( int i=0; i<MAX_LEVEL; ++i )	
				sSPEC[i] = SKILL::SSPEC_108();
		};
	};

	struct SIMPACTS
	{
		EMIMPACT_ADDON		emADDON;					//	�ΰ�ȿ�� ����.
		float				fADDON_VAR[MAX_LEVEL];		//	��ȭ ��ġ.
		float				fADDON_VAR2[MAX_LEVEL];

		SIMPACTS()
			: emADDON(EMIMPACTA_NONE)
		{
			for ( int i=0; i<MAX_LEVEL; ++i )
			{
				fADDON_VAR[i] = 0.0f;
				fADDON_VAR2[i] = 1.0f;
			}
		};

		void Assign ( SIMPACTS_108 &sOldData )
		{
			emADDON = sOldData.emADDON;

			for ( int i=0; i<MAX_LEVEL; ++i )
			{
				fADDON_VAR[i] = sOldData.fADDON_VAR[i];
				fADDON_VAR2[i] = 1.0f;
			}
		}
	};

	struct SSPECS
	{
		EMSPEC_ADDON		emSPEC;						//	Ư��.
		SKILL::SSPEC		sSPEC[MAX_LEVEL];			//	Ư�� ��� ������.

		SSPECS()
			: emSPEC(EMSPECA_NULL)
		{
			for ( int i=0; i<MAX_LEVEL; ++i )	
				sSPEC[i] = SKILL::SSPEC();
		};

		void Assign ( SSPECS_108 &sOldData )
		{
			emSPEC = sOldData.emSPEC;

			for ( int i=0; i<MAX_LEVEL; ++i )	
				sSPEC[i].Assign( sOldData.sSPEC[i] );
		}
	};

	
	struct SAPPLY_100
	{
		//	�⺻ ���밪 ����.
		SKILL::EMTYPES		emBASIC_TYPE;				//	���밪 Ÿ��.
		EMELEMENT			emELEMENT;					//	( ��, ��, ȭ, ��, ���� ) �Ӽ�.
		DWORD				dwCUREFLAG;					//	�ص� ����.
		SKILL::CDATA_LVL_100 sDATA_LVL[MAX_LEVEL];		//	������ ���� ��.

		//	�ΰ� ȿ�� ����.
		EMIMPACT_ADDON		emADDON;					//	�ΰ�ȿ�� ����.
		float				fADDON_VAR[MAX_LEVEL];		//	��ȭ ��ġ.

		//	�����̻� ����.
		EMSTATE_BLOW		emSTATE_BLOW;				//	���� �̻� ���� Ÿ��.
		SKILL::SSTATE_BLOW	sSTATE_BLOW[MAX_LEVEL];		//	���� �̻� ��ġ��.

		//	Ư����� ����.
		EMSPEC_ADDON		emSPEC;						//	Ư��.
		SKILL::SSPEC_100	sSPEC[MAX_LEVEL];			//	Ư�� ��� ������.
	};

	struct SAPPLY_101
	{
		//	�⺻ ���밪 ����.
		SKILL::EMTYPES		emBASIC_TYPE;				//	���밪 Ÿ��.
		EMELEMENT			emELEMENT;					//	( ��, ��, ȭ, ��, ���� ) �Ӽ�.
		DWORD				dwCUREFLAG;					//	�ص� ����.
		SKILL::CDATA_LVL_101	sDATA_LVL[MAX_LEVEL];		//	������ ���� ��.

		//	�ΰ� ȿ�� ����.
		EMIMPACT_ADDON		emADDON;					//	�ΰ�ȿ�� ����.
		float				fADDON_VAR[MAX_LEVEL];		//	��ȭ ��ġ.

		//	�����̻� ����.
		EMSTATE_BLOW		emSTATE_BLOW;				//	���� �̻� ���� Ÿ��.
		SKILL::SSTATE_BLOW	sSTATE_BLOW[MAX_LEVEL];		//	���� �̻� ��ġ��.

		//	Ư����� ����.
		EMSPEC_ADDON		emSPEC;						//	Ư��.
		SKILL::SSPEC_100	sSPEC[MAX_LEVEL];			//	Ư�� ��� ������.
	};

	struct SAPPLY_102
	{
		//	�⺻ ���밪 ����.
		SKILL::EMTYPES		emBASIC_TYPE;				//	���밪 Ÿ��.
		EMELEMENT			emELEMENT;					//	( ��, ��, ȭ, ��, ���� ) �Ӽ�.
		DWORD				dwCUREFLAG;					//	�ص� ����.
		SKILL::CDATA_LVL_101	sDATA_LVL[MAX_LEVEL];		//	������ ���� ��.

		//	�ΰ� ȿ�� ����.
		EMIMPACT_ADDON		emADDON;					//	�ΰ�ȿ�� ����.
		float				fADDON_VAR[MAX_LEVEL];		//	��ȭ ��ġ.

		//	�����̻� ����.
		EMSTATE_BLOW		emSTATE_BLOW;				//	���� �̻� ���� Ÿ��.
		SKILL::SSTATE_BLOW	sSTATE_BLOW[MAX_LEVEL];		//	���� �̻� ��ġ��.

		//	Ư����� ����.
		EMSPEC_ADDON		emSPEC;						//	Ư��.
		SKILL::SSPEC_100	sSPEC[MAX_LEVEL];			//	Ư�� ��� ������.
	};

	struct SAPPLY_103
	{
		//	�⺻ ���밪 ����.
		SKILL::EMTYPES		emBASIC_TYPE;				//	���밪 Ÿ��.
		EMELEMENT			emELEMENT;					//	( ��, ��, ȭ, ��, ���� ) �Ӽ�.
		DWORD				dwCUREFLAG;					//	�ص� ����.
		SKILL::CDATA_LVL_101	sDATA_LVL[MAX_LEVEL];		//	������ ���� ��.

		//	�ΰ� ȿ�� ����.
		EMIMPACT_ADDON		emADDON;					//	�ΰ�ȿ�� ����.
		float				fADDON_VAR[MAX_LEVEL];		//	��ȭ ��ġ.

		//	�����̻� ����.
		EMSTATE_BLOW		emSTATE_BLOW;				//	���� �̻� ���� Ÿ��.
		SKILL::SSTATE_BLOW	sSTATE_BLOW[MAX_LEVEL];		//	���� �̻� ��ġ��.

		//	Ư����� ����.
		EMSPEC_ADDON		emSPEC;						//	Ư��.
		SKILL::SSPEC_108	sSPEC[MAX_LEVEL];			//	Ư�� ��� ������.
	};

	struct SAPPLY_200
	{
		//	�⺻ ���밪 ����.
		SKILL::EMTYPES		emBASIC_TYPE;				//	���밪 Ÿ��.
		EMELEMENT			emELEMENT;					//	( ��, ��, ȭ, ��, ���� ) �Ӽ�.
		DWORD				dwCUREFLAG;					//	�ص� ����.
		SKILL::CDATA_LVL_101	sDATA_LVL[MAX_LEVEL];		//	������ ���� ��.

		EMSTATE_BLOW		emSTATE_BLOW;				//	���� �̻� ���� Ÿ��.
		SKILL::SSTATE_BLOW	sSTATE_BLOW[MAX_LEVEL];		//	���� �̻� ��ġ��.

		SKILL::SIMPACTS_108	sImpacts[MAX_IMPACT];
		SKILL::SSPECS_108	sSpecs[MAX_SPEC];

		SAPPLY_200 (void) :
			emBASIC_TYPE(EMFOR_HP),
			emELEMENT(EMELEMENT_SPIRIT),
			dwCUREFLAG(NULL),
			emSTATE_BLOW(EMBLOW_NONE)
		{
			for ( int i=0; i<MAX_IMPACT; ++i )
				sImpacts[i] = SKILL::SIMPACTS_108();

			for ( int i=0; i<MAX_SPEC; ++i )
					sSpecs[i] = SKILL::SSPECS_108();
		}
	};

	struct SAPPLY
	{
		enum { VERSION = 0x0202, };

		//	�⺻ ���밪 ����.
		SKILL::EMTYPES		emBASIC_TYPE;				//	���밪 Ÿ��.
		EMELEMENT			emELEMENT;					//	( ��, ��, ȭ, ��, ���� ) �Ӽ�.
		SKILL::CDATA_LVL	sDATA_LVL[MAX_LEVEL];		//	������ ���� ��.
		DWORD				dwCUREFLAG;					//	�ص� ����.

		EMSTATE_BLOW		emSTATE_BLOW;				//	���� �̻� ���� Ÿ��.
		SKILL::SSTATE_BLOW	sSTATE_BLOW[MAX_LEVEL];		//	���� �̻� ��ġ��.

		SKILL::SIMPACTS		sImpacts[MAX_IMPACT];
		SKILL::SSPECS		sSpecs[MAX_SPEC];

		DWORD				dwUnknownData;

		SAPPLY (void) :
			emBASIC_TYPE(EMFOR_HP),
			emELEMENT(EMELEMENT_SPIRIT),
			dwCUREFLAG(NULL),
			emSTATE_BLOW(EMBLOW_NONE),
			dwUnknownData(0)
		{
			for ( int i=0; i<MAX_IMPACT; ++i )
				sImpacts[i] = SKILL::SIMPACTS();

			for ( int i=0; i<MAX_SPEC; ++i )
				sSpecs[i] = SKILL::SSPECS();
		}

		void Assign ( SAPPLY_100 &sOldData );
		void Assign ( SAPPLY_101 &sOldData );
		void Assign ( SAPPLY_102 &sOldData );
		void Assign ( SAPPLY_103 &sOldData );
		void Assign ( SAPPLY_200 &sOldData );

		BOOL LOAD_0106 ( basestream &SFile );
		BOOL LOAD_0107 ( basestream &SFile );
		BOOL LOAD_0108 ( basestream &SFile );
		BOOL LOAD_0109 ( basestream &SFile );
		BOOL LOAD_0110 ( basestream &SFile );

		BOOL LOAD_0201 ( basestream &SFile );

		BOOL LOAD ( basestream &SFile );
		BOOL SAVE ( CSerialFile &SFile );

		static VOID SaveCsvHead ( std::fstream &SFile );
		VOID SaveCsv ( std::fstream &SFile );
		VOID LoadCsv ( CStringArray &StrArray, int &iCsvCur );

		BOOL IsImpact( EMIMPACT_ADDON emImpact );
		BOOL IsSpec( EMSPEC_ADDON emSpec );
	};
};

namespace COMMENT
{
	extern std::string SKILL_TYPES[SKILL::FOR_TYPE_SIZE];
	extern float SKILL_TYPES_SCALE[SKILL::FOR_TYPE_SIZE];
	inline bool IsSKILL_PER ( SKILL::EMTYPES emTYPE )			{ return SKILL_TYPES_SCALE[emTYPE]==100.0f; }
};

#endif // GLSKILL_APPLY_H_