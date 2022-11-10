#ifndef GLSKILL_LEARN_H_
#define GLSKILL_LEARN_H_

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
	//	���� �� ���� ����.
	struct SLEARN_LVL_0100_0101
	{
		DWORD				dwSKP;					//	�䱸 ��ų ����Ʈ.
		DWORD				dwLEVEL;				//	�䱸 Level.
		SCHARSTATS			sSTATS;					//	�䱸 Stats.
		DWORD				dwSKILL_LVL;			//	�䱸 ������ų ����.
	};

	struct SLEARN_LVL
	{
		DWORD				dwLEVEL;				//	�䱸 Level.
		SCHARSTATS			sSTATS;					//	�䱸 Stats.
		DWORD				dwSKP;					//	�䱸 ��ų ����Ʈ.
		DWORD				dwSKILL_LVL;			//	�䱸 ������ų ����.

		SLEARN_LVL (void) :
			dwLEVEL(1),
			dwSKP(1),
			dwSKILL_LVL(0)
		{
		}

		void Assign ( SLEARN_LVL_0100_0101 &OldData )
		{
			dwLEVEL		= OldData.dwLEVEL;
			sSTATS		= OldData.sSTATS;
			dwSKP		= OldData.dwSKP;
			dwSKILL_LVL	= OldData.dwSKILL_LVL;
		}
	};

	struct SLEARN_100
	{
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.
		DWORD				dwCLASS;					//	����.
		SNATIVEID			sSKILL;						//	�䱸 ������ų.
		SLEARN_LVL_0100_0101	sLVL_STEP[MAX_LEVEL];		//	���� �� �䱸 ��ġ.
	};

	struct SLEARN_101
	{
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.
		DWORD				dwCLASS;					//	����.
		SNATIVEID			sSKILL;						//	�䱸 ������ų.
		SLEARN_LVL_0100_0101	sLVL_STEP[MAX_LEVEL];	//	���� �� �䱸 ��ġ.
	};

	struct SLEARN
	{
		enum { VERSION = 0x0102, };

		DWORD				dwCLASS;					//	����.
		EMBRIGHT			emBRIGHT;					//	�Ӽ�.
		SNATIVEID			sSKILL;						//	�䱸 ������ų.

		SLEARN_LVL			sLVL_STEP[MAX_LEVEL];		//	���� �� �䱸 ��ġ.

		SLEARN (void) :
			emBRIGHT(BRIGHT_BOTH),
			dwCLASS(GLCC_NONE),
			sSKILL(NATIVEID_NULL())
		{
		}

		void Assign ( SLEARN_100 &OldData )
		{
			dwCLASS		= OldData.dwCLASS;
			emBRIGHT	= OldData.emBRIGHT;
			sSKILL		= OldData.sSKILL;

			for ( int i=0; i<MAX_LEVEL; ++i )
				sLVL_STEP[i].dwSKP = 1;
		}

		void Assign ( SLEARN_101 &OldData )
		{
			dwCLASS		= OldData.dwCLASS;
			emBRIGHT	= OldData.emBRIGHT;
			sSKILL		= OldData.sSKILL;

			for ( int i=0; i<MAX_LEVEL; ++i )
				sLVL_STEP[i].Assign( OldData.sLVL_STEP[i] );
		}

		static VOID SaveCsvHead ( std::fstream &SFile );
		VOID SaveCsv ( std::fstream &SFile );
		VOID LoadCsv ( CStringArray &StrArray, int &iCsvCur );
	};
};

#endif // GLSKILL_LEARN_H_