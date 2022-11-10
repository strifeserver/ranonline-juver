#ifndef GLITEM_GENERATE_H_
#define GLITEM_GENERATE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../Lib_Engine/Common/BaseStream.h"
#include "../../Lib_Engine/Common/StringFile.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/Common/STRINGUTILS.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"


namespace ITEM
{
	struct SGENERATE_100
	{
		DWORD dwSpecID;			//	������ �з� ��.
		DWORD dwLimitTime;		//	���� ���� �ð�.
		DWORD dwLimitTimeGen;	//	�ð��� ���� ���� ����.
	};

	struct SGENERATE_101
	{
		DWORD dwSpecID;			//	������ �з� ��.
		DWORD dwLimitTimeGen;	//	�ð��� ���� ���� ����.
		DWORD dwLimitTime;		//	���� ���� �ð�.
	};

	struct SGENERATE
	{
		enum { VERSION = 0x0200, SPECID_NULL = 0, LIMIT_NOUSE = 0 };

		DWORD dwSpecID;			//	������ �з� ��.
		DWORD dwLimitTimeGen;	//	�ð��� ���� ���� ����.
		DWORD dwLimitTime;		//	���� ���� �ð�.
		BOOL bGenEnable;

		SGENERATE ()
			: dwSpecID(SPECID_NULL)
			, dwLimitTimeGen(LIMIT_NOUSE)
			, dwLimitTime(LIMIT_NOUSE)
			, bGenEnable(TRUE)
		{
		}

		void Assign ( SGENERATE_100 &sOld );
		void Assign ( SGENERATE_101 &sOld );

		static VOID SaveCsvHead ( std::fstream &SFile );
		VOID SaveCsv ( std::fstream &SFile );
		VOID LoadCsv ( CStringArray &StrArray, int &iCsvCur  );
	};
};

#endif // GLITEM_GENERATE_H_