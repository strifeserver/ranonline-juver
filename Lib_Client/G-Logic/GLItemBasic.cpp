#include "stdafx.h"
#include "GLItemBasic.h"
#include "./GLStringTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace ITEM
{
	void SITEMBASIC::Assign ( SITEMBASIC_100 &sOld )
	{
		sNativeID		= sOld.sNativeID;

		strName			= sOld.szName;
		emLevel			= sOld.emLevel;

		dwFlags			= sOld.dwFlags;
		dwBuyPrice		= sOld.dwPrice;
		dwSellPrice		= dwBuyPrice/3;

		emItemType = EXITEM_TO_ITEM(sOld.emItemType);

		//	���� ����.
		emReqBright		= sOld.emReqBright;
		dwReqCharClass	= sOld.dwReqCharClass;
		wReqLevelDW		= sOld.wReqLevel;
		wReqPA			= sOld.wReqPA;
		wReqSA			= sOld.wReqSA;
		sReqStats		= sOld.sReqStats;

		wInvenSizeX		= sOld.wInvenSizeX;
		wInvenSizeY		= sOld.wInvenSizeY;

		strFieldFile	= sOld.szFieldFile;
		strInventoryFile = sOld.szInventoryFile;

		for ( int i=0; i<GLCI_NUM_6CLASS; i++ )
			strWearingFileRight[i] = sOld.szWearingFIle[i];

		strComment = sOld.szComment;
	}

	void SITEMBASIC::Assign ( SITEMBASIC_101 &sOld )
	{
		sNativeID		= sOld.sNativeID;

		strName			= sOld.szName;
		emLevel			= sOld.emLevel;

		dwFlags			= sOld.dwFlags;
		dwBuyPrice		= sOld.dwPrice;
		dwSellPrice		= dwBuyPrice/3;

		emItemType = EXITEM_TO_ITEM(sOld.emItemType);

		//	���� ����.
		emReqBright		= sOld.emReqBright;
		dwReqCharClass	= sOld.dwReqCharClass;
		wReqLevelDW		= sOld.wReqLevel;
		wReqPA			= 0;
		wReqSA			= 0;
		sReqStats		= sOld.sReqStats;

		wInvenSizeX		= sOld.wInvenSizeX;
		wInvenSizeY		= sOld.wInvenSizeY;

		strSelfBodyEffect = sOld.szSelfBodyEffect;
		strTargBodyEffect = sOld.szTargBodyEffect;
		strTargetEffect = sOld.szTargetEffect;

		strFieldFile	= sOld.szFieldFile;
		strInventoryFile = sOld.szInventoryFile;

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			strWearingFileRight[i] = sOld.szWearingFIle[i];

		strComment = sOld.szComment;
	}

	void SITEMBASIC::Assign ( SITEMBASIC_102 &sOld )
	{
		sNativeID = sOld.sNativeID;					//	���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )

		strName = sOld.szName;						//	�������� �̸�.	
		emLevel = sOld.emLevel;						//	������ ��ġ ���.

		dwFlags		= sOld.dwFlags;						//	Trade �Ӽ�.
		dwBuyPrice	= sOld.dwPrice;						//	������ ���԰���.
		dwSellPrice	= dwBuyPrice/3;				//  ������ �ǸŰ���

		emItemType = EXITEM_TO_ITEM(sOld.emItemType);

		//	���� ����.
		emReqBright = sOld.emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		dwReqCharClass = sOld.dwReqCharClass;		//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		wReqLevelDW = sOld.wReqLevel;					//	�䱸 Level.
		wReqPA = sOld.wReqPA;						//	�䱸 ����ġ.
		wReqSA = sOld.wReqSA;						//	�䱸 ���ġ.
		sReqStats = sOld.sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.

		wInvenSizeX = sOld.wInvenSizeX;				//	�κ��丮 ������.
		wInvenSizeY = sOld.wInvenSizeY;				//	�κ��丮 ������.

		sICONID = sOld.sICONID;						//	������ �ε���.

		strSelfBodyEffect = sOld.szSelfBodyEffect;	//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		strTargBodyEffect = sOld.szTargBodyEffect;	//	��ǥ ������ ���� �״� ����Ʈ.
		strTargetEffect = sOld.szTargetEffect;		//	��ǥ ���� ����Ʈ.

		strFieldFile = sOld.szFieldFile;			//	�ٴ� ���� ����.
		strInventoryFile = sOld.szInventoryFile;	//	�κ��丮 ���� ����.

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )	
			strWearingFileRight[i] = sOld.szWearingFIle[i];	//	���� ����.

		strComment = sOld.szComment;			//	�����ۿ� ���� ������ ����.
	}

	bool SITEMBASIC::LOAD_103 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		dwSellPrice		= dwBuyPrice/3;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> wReqLevelDW;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		return true;
	}

	bool SITEMBASIC::LOAD_104 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		dwSellPrice		= dwBuyPrice/3;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		return true;
	}

	bool SITEMBASIC::LOAD_105 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> wGradeAttack;
		SFile >> wGradeDefense;

		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		dwSellPrice		= dwBuyPrice/3;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		return true;
	}

	bool SITEMBASIC::LOAD_106 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> wGradeAttack;
		SFile >> wGradeDefense;

		SFile >> fExpMultiple;

		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		dwSellPrice		= dwBuyPrice/3;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		return true;
	}

	bool SITEMBASIC::LOAD_107 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> wGradeAttack;
		SFile >> wGradeDefense;

		SFile >> fExpMultiple;

		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		dwSellPrice		= dwBuyPrice/3;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		// PET
		SFile >> strPetWearingFile;

		return true;
	}

	bool SITEMBASIC::LOAD_108 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> wGradeAttack;
		SFile >> wGradeDefense;

		SFile >> fExpMultiple;

		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		dwSellPrice		= dwBuyPrice/3;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_5CLASS; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		// PET
		SFile >> strPetWearingFile;

		return true;
	}

	bool SITEMBASIC::LOAD_109 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> wGradeAttack;
		SFile >> wGradeDefense;

		SFile >> fExpMultiple;

		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		dwSellPrice		= dwBuyPrice/3;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_5CLASS; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		// PET
		SFile >> strPetWearingFile;

		return true;
	}

	bool SITEMBASIC::LOAD_110 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> wGradeAttack;
		SFile >> wGradeDefense;

		SFile >> fExpMultiple;

		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		dwSellPrice		= dwBuyPrice/3;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;

		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_5CLASS_EX; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		// PET
		SFile >> strPetWearingFile;

		return true;
	}

	bool SITEMBASIC::LOAD_111 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> wGradeAttack;
		SFile >> wGradeDefense;

		SFile >> fExpMultiple;

		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		dwSellPrice		= dwBuyPrice/3;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_5CLASS_EX; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		// PET
		SFile >> strPetWearingFile;

		return true;
	}

	bool SITEMBASIC::LOAD_112 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> wGradeAttack;
		SFile >> wGradeDefense;

		SFile >> fExpMultiple;

		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		dwSellPrice		= dwBuyPrice/3;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_5CLASS_EX; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		// PET
		SFile >> strPetWearingFile;

		SFile >> sSubID.dwID;

		SFile >> wPosX;
		SFile >> wPosY;

		return true;
	}

	bool SITEMBASIC::LOAD_113 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> wGradeAttack;
		SFile >> wGradeDefense;

		SFile >> fExpMultiple;

		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;

		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_5CLASS_EX; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		// PET
		SFile >> strPetWearingFile;

		SFile >> sSubID.dwID;

		SFile >> wPosX;
		SFile >> wPosY;

		return true;
	}

	bool SITEMBASIC::LOAD_114 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;

		SFile >> strName;
		SFile >> dwData;
		emLevel = (EMITEMLEVEL)dwData;

		SFile >> wGradeAttack;
		SFile >> wGradeDefense;

		SFile >> fExpMultiple;

		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;

		SFile >> dwFlags;

		if ( IsTHROW() )
		{
			dwFlags |= 7;
		}

		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;

		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		//	���� ����.
		SFile >> dwData;
		emReqBright = (EMBRIGHT) dwData;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;

		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );

		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;

		SFile >> sICONID.dwID;

		SFile >> strSelfBodyEffect;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;

		SFile >> strFieldFile;
		SFile >> strInventoryFile;

		for ( int i=0; i<GLCI_NUM_5CLASS_EX; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strComment;

		// PET
		SFile >> strPetWearingFile;

		SFile >> sSubID.dwID;

		SFile >> wPosX;
		SFile >> wPosY;

		SFile >> dwCoolTime;

		SFile >> dwData;
		emCoolType = (EMCOOL_TYPE) dwData;		

		return true;
	}

	bool SITEMBASIC::LOAD_115 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;
	
		for ( int i=0; i<GLCI_NUM_5CLASS_EX; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;

		return true;
	}

	bool SITEMBASIC::LOAD_116 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			SFile >> strWearingFileRight[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;

		return true;
	}

	bool SITEMBASIC::LOAD_117 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;

		return true;
	}

	bool SITEMBASIC::LOAD_118 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);

		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_6CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;
		SFile >> bEnable;

		return true;
	}

	bool SITEMBASIC::LOAD_119 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;
		SFile >> bEnable;

		return true;
	}

	bool SITEMBASIC::LOAD_121 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;	
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;

		if ( dwReqCharClass == GLCC_ALL_6CLASS )
			dwReqCharClass = GLCC_ALL_8CLASS;
		else if ( dwReqCharClass == GLCC_MAN_6CLASS )
			dwReqCharClass = GLCC_MAN_8CLASS;
		else if ( dwReqCharClass == GLCC_WOMAN_6CLASS )
			dwReqCharClass = GLCC_WOMAN_8CLASS;

		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;
		SFile >> bEnable;

		/*activity point, Juver, 2017/08/23 */
		DWORD dwActivityReqType;
		SFile >> dwActivityReqType;
		SFile >> dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		SFile >> dwReqContributionPoint;

		/*activity point, Juver, 2017/08/23 */
		if ( dwActivityReqType == 1 )
			dwReqActivityPoint = dwReqActivityPoint * 2;
		else if ( dwActivityReqType == 2 )
			dwReqActivityPoint = dwReqActivityPoint * 3;


		return true;
	}


	bool SITEMBASIC::LOAD_122 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;	
		EMEXITEM_TYPE exemItemType = (EMEXITEM_TYPE) dwData;
		emItemType = EXITEM_TO_ITEM(exemItemType);
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;

		if ( dwReqCharClass == GLCC_ALL_7CLASS )
			dwReqCharClass = GLCC_ALL_8CLASS;
		else if ( dwReqCharClass == GLCC_MAN_7CLASS )
			dwReqCharClass = GLCC_MAN_8CLASS;
		else if ( dwReqCharClass == GLCC_WOMAN_7CLASS )
			dwReqCharClass = GLCC_WOMAN_8CLASS;

		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		//SFile >> wInvenSizeX;
		//SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;
		SFile >> bEnable;

		/*activity point, Juver, 2017/08/23 */
		DWORD dwActivityReqType;
		SFile >> dwActivityReqType;
		SFile >> dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		SFile >> dwReqContributionPoint;

		/*activity point, Juver, 2017/08/23 */
		if ( dwActivityReqType == 1 )
			dwReqActivityPoint = dwReqActivityPoint * 2;
		else if ( dwActivityReqType == 2 )
			dwReqActivityPoint = dwReqActivityPoint * 3;

		return true;
	}

	bool SITEMBASIC::LOAD_200 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;	emItemType = (EMITEM_TYPE) dwData;
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;
		SFile >> bEnable;

		/*activity point, Juver, 2017/08/23 */
		DWORD dwActivityReqType;
		SFile >> dwActivityReqType;
		SFile >> dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		SFile >> dwReqContributionPoint;

		/*activity point, Juver, 2017/08/23 */
		if ( dwActivityReqType == 1 )
			dwReqActivityPoint = dwReqActivityPoint * 2;
		else if ( dwActivityReqType == 2 )
			dwReqActivityPoint = dwReqActivityPoint * 3;

		return true;
	}

	bool SITEMBASIC::LOAD_201 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;	emItemType = (EMITEM_TYPE) dwData;
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;
		SFile >> bEnable;

		/*activity point, Juver, 2017/08/23 */
		DWORD dwActivityReqType;
		SFile >> dwActivityReqType;
		SFile >> dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		SFile >> dwReqContributionPoint;

		/*activity point, Juver, 2017/08/23 */
		if ( dwActivityReqType == 1 )
			dwReqActivityPoint = dwReqActivityPoint * 2;
		else if ( dwActivityReqType == 2 )
			dwReqActivityPoint = dwReqActivityPoint * 3;

		/*UserNum ItemReq, Juver, 2017/06/27 */
		SFile >> dwReqUserNum;

		return true;
	}

	bool SITEMBASIC::LOAD_202 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;	emItemType = (EMITEM_TYPE) dwData;
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;
		SFile >> bEnable;

		/*activity point, Juver, 2017/08/23 */
		SFile >> dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		SFile >> dwReqContributionPoint;

		/*UserNum ItemReq, Juver, 2017/06/27 */
		SFile >> dwReqUserNum;

		return true;
	}

	bool SITEMBASIC::LOAD_203 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;	emItemType = (EMITEM_TYPE) dwData;
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;
		SFile >> bEnable;

		/*activity point, Juver, 2017/08/23 */
		SFile >> dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		SFile >> dwReqContributionPoint;

		/*UserNum ItemReq, Juver, 2017/06/27 */
		SFile >> dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		SFile >> bItemColor;
		SFile >> wItemColor1;
		SFile >> wItemColor2;

		return true;
	}


	bool SITEMBASIC::LOAD_204 ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;	emItemType = (EMITEM_TYPE) dwData;
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;
		SFile >> bEnable;

		/*activity point, Juver, 2017/08/23 */
		SFile >> dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		SFile >> dwReqContributionPoint;

		/*UserNum ItemReq, Juver, 2017/06/27 */
		SFile >> dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		SFile >> bItemColor;
		SFile >> wItemColor1;
		SFile >> wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SFile >> sidWrapperBox.dwID;

		return true;
	}

	bool SITEMBASIC::LOAD ( basestream &SFile )
	{
		DWORD dwData(0);

		SFile >> sNativeID.dwID;
		SFile >> sGroupID.dwID;
		SFile >> dwData;	emLevel = (EMITEMLEVEL)dwData;
		SFile >> dwData;	emItemType = (EMITEM_TYPE) dwData;
		SFile >> strName;
		SFile >> fExpMultiple;
		SFile >> wGradeAttack;
		SFile >> wGradeDefense;
		SFile >> dwFlags;
		SFile >> dwBuyPrice;
		SFile >> dwSellPrice;
		SFile >> wReserved1;
		SFile >> wReserved2;
		SFile >> wReserved3;
		SFile >> wReserved4;
		SFile >> wReserved5;
		SFile >> dwReqCharClass;
		SFile >> dwReqSchool;
		SFile.ReadBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile >> wReqLevelDW;
		SFile >> wReqLevelUP;
		SFile >> wReqPA;
		SFile >> wReqSA;
		SFile >> dwData;	emReqBright = (EMBRIGHT) dwData;
		SFile >> dwCoolTime;
		SFile >> dwData;	emCoolType = (EMCOOL_TYPE) dwData;		
		SFile >> wInvenSizeX;
		SFile >> wInvenSizeY;
		SFile >> sICONID.dwID;
		SFile >> strFieldFile;
		SFile >> strInventoryFile;
		SFile >> strTargBodyEffect;
		SFile >> strTargetEffect;
		SFile >> strSelfBodyEffect;

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile >> strWearingFileLeft[i];

		SFile >> strPetWearingFile;
		SFile >> strComment;
		SFile >> sSubID.dwID;
		SFile >> wPosX;
		SFile >> wPosY;
		SFile >> bEnable;

		/*activity point, Juver, 2017/08/23 */
		SFile >> dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		SFile >> dwReqContributionPoint;

		/*UserNum ItemReq, Juver, 2017/06/27 */
		SFile >> dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		SFile >> bItemColor;
		SFile >> wItemColor1;
		SFile >> wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SFile >> sidWrapperBox.dwID;

		/*item transfer card, Juver, 2018/01/18 */
		SFile >> bItemTransfer;

		return true;
	}

	bool SITEMBASIC::SAVE ( CSerialFile &SFile )
	{
		CString cstrName;
		cstrName.Format( _T("IN_%03d_%03d"), sNativeID.wMainID , sNativeID.wSubID ); // by ���
		strName = cstrName.GetString();

		cstrName.Format( _T("ID_%03d_%03d"), sNativeID.wMainID , sNativeID.wSubID ); // by ���
		strComment = cstrName.GetString();

		SFile << sNativeID.dwID;
		SFile << sGroupID.dwID;
		SFile << (DWORD)emLevel;
		SFile << (DWORD)emItemType;
		SFile << strName;
		SFile << fExpMultiple;
		SFile << wGradeAttack;
		SFile << wGradeDefense;
		SFile << dwFlags;
		SFile << dwBuyPrice;
		SFile << dwSellPrice;
		SFile << wReserved1;
		SFile << wReserved2;
		SFile << wReserved3;
		SFile << wReserved4;
		SFile << wReserved5;
		SFile << dwReqCharClass;
		SFile << dwReqSchool;
		SFile.WriteBuffer ( &sReqStats, sizeof(sReqStats) );
		SFile << wReqLevelDW;
		SFile << wReqLevelUP;
		SFile << wReqPA;
		SFile << wReqSA;
		SFile << (DWORD)emReqBright;
		SFile << dwCoolTime;
		SFile << (DWORD)emCoolType;
		SFile << wInvenSizeX;
		SFile << wInvenSizeY;
		SFile << sICONID.dwID;
		SFile << strFieldFile;
		SFile << strInventoryFile;
		SFile << strTargBodyEffect;
		SFile << strTargetEffect;
		SFile << strSelfBodyEffect;
		
		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile << strWearingFileRight[i];

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile << strWearingFileLeft[i];

		SFile << strPetWearingFile;
		SFile << strComment;
		SFile << sSubID.dwID;
		SFile << wPosX;
		SFile << wPosY;
		SFile << bEnable;

		/*activity point, Juver, 2017/08/23 */
		SFile << dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		SFile << dwReqContributionPoint;

		/*UserNum ItemReq, Juver, 2017/06/27 */
		SFile << dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		SFile << bItemColor;
		SFile << wItemColor1;
		SFile << wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		SFile << sidWrapperBox.dwID;

		/*item transfer card, Juver, 2018/01/18 */
		SFile << bItemTransfer;

		return true;
	}

	VOID SITEMBASIC::SaveCsvHead ( std::fstream &SFile )
	{
		SFile << "sNativeID wMainID" << ",";
		SFile << "sNativeID wSubID" << ",";
		SFile << "sGroupID wMainID" << ",";
		SFile << "sGroupID wSubID" << ",";

		SFile << "strName" << ",";

	//		��ȹ�� ��û���� ������
		SFile << "strName" << ",";

		SFile << "emLevel" << ",";

		SFile << "wGradeAttack" << ",";
		SFile << "wGradeDefense" << ",";

		SFile << "fExpMultiple" << ",";

		SFile << "wReserved1" << ",";
		SFile << "wReserved2" << ",";
		SFile << "wReserved3" << ",";
		SFile << "wReserved4" << ",";
		SFile << "wReserved5" << ",";

		SFile << "dwFlags" << ",";
		SFile << "dwBuyPrice" << ",";
		SFile << "dwSellPrices" << ",";

		SFile << "emItemType" << ",";

		SFile << "emReqBright" << ",";
		SFile << "dwReqCharClass" << ",";
		SFile << "dwReqSchool" << ",";
		SFile << "wReqLevelDW" << ",";
		SFile << "wReqLevelUP" << ",";
		SFile << "wReqPA" << ",";
		SFile << "wReqSA" << ",";
		SFile << "sReqStats wPow" << ",";
		SFile << "sReqStats wStr" << ",";
		SFile << "sReqStats wSpi" << ",";
		SFile << "sReqStats wDex" << ",";
		SFile << "sReqStats wInt" << ",";
		SFile << "sReqStats wSta" << ",";

		SFile << "wInvenSizeX" << ",";
		SFile << "wInvenSizeY" << ",";

		SFile << "sICONID wMainID" << ",";
		SFile << "sICONID wSubID" << ",";

		SFile << "strSelfBodyEffect" << ",";
		SFile << "strTargBodyEffect" << ",";
		SFile << "strTargetEffect" << ",";

		SFile << "strFieldFile" << ",";
		SFile << "strInventoryFile" << ",";

		for( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile << "strWearingFileRight " << i << ",";

		for( int i=0; i<GLCI_NUM_8CLASS; ++i )
			SFile << "strWearingFileLeft " << i << ",";

		SFile << "strComment" << ",";

		// PET
		SFile << "strPetWearingFile" << ",";

		SFile << "sMapID wMainID" << ",";
		SFile << "sMapID wSubID" << ",";

		SFile << "wPosX" << ",";
		SFile << "wPosY" << ",";

		SFile << "dwCoolTime" << ",";
		SFile << "emCoolType" << ",";
		SFile << "bEnable" << ",";

		/*activity point, Juver, 2017/08/23 */
		SFile << "dwReqActivityPoint" << ",";

		/*contribution point, Juver, 2017/08/23 */
		SFile << "dwReqContributionPoint" << ",";

		/*UserNum ItemReq, Juver, 2017/06/27 */
		SFile << "dwReqUserNum" << ",";

		/*item color, Juver, 2018/01/05 */
		SFile << "bItemColor" << ",";
		SFile << "wItemColor1" << ",";
		SFile << "wItemColor2" << ",";

		/*item wrapper, Juver, 2018/01/11 */
		SFile << "sidWrapperBox wMainID" << ",";
		SFile << "sidWrapperBox wSubID" << ",";

		/*item transfer card, Juver, 2018/01/18 */
		SFile << "bItemTransfer" << ",";
	}

	VOID SITEMBASIC::SaveCsv ( std::fstream &SFile )
	{
		SFile << sNativeID.wMainID << ",";
		SFile << sNativeID.wSubID << ",";
		SFile << sGroupID.wMainID << ",";
		SFile << sGroupID.wSubID << ",";

		STRUTIL::OutputStrCsv( SFile, strName );

	//		��ȹ�� ��û���� ������

		std::string str = strName;
		const char* szpName = str.c_str();
		if( szpName )
		{
			const char* szpLongName = GLStringTable::GetInstance().GetString( szpName, GLStringTable::ITEM );
			if( szpLongName )
				str = szpLongName;
		}
		STRUTIL::OutputStrCsv( SFile, str );

		SFile << emLevel << ",";

		SFile << wGradeAttack << ",";
		SFile << wGradeDefense << ",";

		SFile << fExpMultiple << ",";

		SFile << wReserved1 << ",";
		SFile << wReserved2 << ",";
		SFile << wReserved3 << ",";
		SFile << wReserved4 << ",";
		SFile << wReserved5 << ",";

		SFile << dwFlags << ",";
		SFile << dwBuyPrice << ",";
		SFile << dwSellPrice << ",";

		SFile << emItemType << ",";

		SFile << emReqBright << ",";
		SFile << dwReqCharClass << ",";
		SFile << dwReqSchool << ",";
		SFile << wReqLevelDW << ",";
		SFile << wReqLevelUP << ",";
		SFile << wReqPA << ",";
		SFile << wReqSA << ",";
		SFile << sReqStats.wPow << ",";
		SFile << sReqStats.wStr << ",";
		SFile << sReqStats.wSpi << ",";
		SFile << sReqStats.wDex << ",";
		SFile << sReqStats.wInt << ",";
		SFile << sReqStats.wSta << ",";

		SFile << wInvenSizeX << ",";
		SFile << wInvenSizeY << ",";

		SFile << sICONID.wMainID << ",";
		SFile << sICONID.wSubID << ",";

		STRUTIL::OutputStrCsv( SFile, strSelfBodyEffect );
		STRUTIL::OutputStrCsv( SFile, strTargBodyEffect );
		STRUTIL::OutputStrCsv( SFile, strTargetEffect );

		STRUTIL::OutputStrCsv( SFile, strFieldFile );
		STRUTIL::OutputStrCsv( SFile, strInventoryFile );

		for( int i=0; i<GLCI_NUM_8CLASS; ++i )
			STRUTIL::OutputStrCsv( SFile, strWearingFileRight[i] );

		for( int i=0; i<GLCI_NUM_8CLASS; ++i )
			STRUTIL::OutputStrCsv( SFile, strWearingFileLeft[i] );

		STRUTIL::OutputStrCsv( SFile, strComment );

		// PET
		STRUTIL::OutputStrCsv ( SFile, strPetWearingFile );

		SFile << sSubID.wMainID << ",";
		SFile << sSubID.wSubID << ",";
		
		SFile << wPosX << ",";
		SFile << wPosY << ",";

		SFile << dwCoolTime << ",";
		SFile << emCoolType << ",";

		SFile << bEnable << ",";

		/*activity point, Juver, 2017/08/23 */
		SFile << dwReqActivityPoint << ",";

		/*contribution point, Juver, 2017/08/23 */
		SFile << dwReqContributionPoint << ",";

		/*UserNum ItemReq, Juver, 2017/06/27 */
		SFile << dwReqUserNum << ",";

		/*item color, Juver, 2018/01/05 */
		SFile << bItemColor << ",";
		SFile << wItemColor1 << ",";
		SFile << wItemColor2 << ",";

		/*item wrapper, Juver, 2018/01/11 */
		SFile << sidWrapperBox.wMainID << ",";
		SFile << sidWrapperBox.wSubID << ",";

		/*item transfer card, Juver, 2018/01/18 */
		SFile << bItemTransfer << ",";
	}

	VOID SITEMBASIC::LoadCsv ( CStringArray &StrArray, int &iCsvCur  )
	{
		sNativeID.wMainID = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sNativeID.wSubID = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sGroupID.wMainID = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sGroupID.wSubID = (WORD)atoi( StrArray[ iCsvCur++ ] );

		STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strName );

	//		��ȹ�� ��û���� ������
		++iCsvCur;	// Item Name

		emLevel = (EMITEMLEVEL)atoi( StrArray[ iCsvCur++ ] );

		wGradeAttack = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wGradeDefense = (WORD)atoi( StrArray[ iCsvCur++ ] );

		fExpMultiple = (float)atof( StrArray[ iCsvCur++ ] );

		wReserved1 = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wReserved2 = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wReserved3 = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wReserved4 = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wReserved5 = (WORD)atoi( StrArray[ iCsvCur++ ] );

		dwFlags = (DWORD)atol( StrArray[ iCsvCur++ ] );
		dwBuyPrice  = (DWORD)atol( StrArray[ iCsvCur++ ] );
		dwSellPrice = (DWORD)atol( StrArray[ iCsvCur++ ] );

		emItemType = (EMITEM_TYPE)atoi( StrArray[ iCsvCur++ ] );

		emReqBright = (EMBRIGHT)atoi( StrArray[ iCsvCur++ ] );
		dwReqCharClass = (DWORD)atol( StrArray[ iCsvCur++ ] );
		dwReqSchool = (DWORD)atol( StrArray[ iCsvCur++ ] );
		wReqLevelDW = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wReqLevelUP = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wReqPA = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wReqSA = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sReqStats.wPow = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sReqStats.wStr = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sReqStats.wSpi = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sReqStats.wDex = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sReqStats.wInt = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sReqStats.wSta = (WORD)atoi( StrArray[ iCsvCur++ ] );

		wInvenSizeX = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wInvenSizeY = (WORD)atoi( StrArray[ iCsvCur++ ] );

		sICONID.wMainID = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sICONID.wSubID = (WORD)atoi( StrArray[ iCsvCur++ ] );

		STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strSelfBodyEffect );
		STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strTargBodyEffect );
		STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strTargetEffect );

		STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strFieldFile );
		STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strInventoryFile );

		for( int i=0; i<GLCI_NUM_8CLASS; ++i )
			STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strWearingFileRight[i] );

		for( int i=0; i<GLCI_NUM_8CLASS; ++i )
			STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strWearingFileLeft[i] );

		STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strComment );

		// PET
		STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strPetWearingFile );

		sSubID.wMainID = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sSubID.wSubID = (WORD)atoi( StrArray[ iCsvCur++ ] );
		
		wPosX = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wPosY = (WORD)atoi( StrArray[ iCsvCur++ ] );

		dwCoolTime = (DWORD)atoi( StrArray[ iCsvCur++ ] );
		emCoolType = (EMCOOL_TYPE)atoi( StrArray[ iCsvCur++ ] );

		bEnable = (bool)atoi( StrArray[ iCsvCur++ ] );

		/*activity point, Juver, 2017/08/23 */
		dwReqActivityPoint = (DWORD)atoi( StrArray[ iCsvCur++ ] );

		/*contribution point, Juver, 2017/08/23 */
		dwReqContributionPoint = (DWORD)atoi( StrArray[ iCsvCur++ ] );

		/*UserNum ItemReq, Juver, 2017/06/27 */
		dwReqUserNum = (DWORD)atoi( StrArray[ iCsvCur++ ] );

		/*item color, Juver, 2018/01/05 */
		bItemColor = (bool)atoi( StrArray[ iCsvCur++ ] );
		wItemColor1 = (WORD)atoi( StrArray[ iCsvCur++ ] );
		wItemColor2 = (WORD)atoi( StrArray[ iCsvCur++ ] );

		/*item wrapper, Juver, 2018/01/11 */
		sidWrapperBox.wMainID = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sidWrapperBox.wSubID = (WORD)atoi( StrArray[ iCsvCur++ ] );

		/*item transfer card, Juver, 2018/01/18 */
		bItemTransfer = (bool)atoi( StrArray[ iCsvCur++ ] );
	}

	SITEMBASIC& SITEMBASIC::operator = ( const SITEMBASIC& rvalue )
	{
		sNativeID = rvalue.sNativeID;					//	���� ID. ( ������ ���� ���� �����ÿ� �ο��Ǵ� ���� ID )
		sGroupID = rvalue.sGroupID;
		emLevel = rvalue.emLevel;						//	������ ��ġ ���.
		emItemType = rvalue.emItemType;					//	������ ����.
		strName = rvalue.strName;						//	�������� �̸�.	
		fExpMultiple = rvalue.fExpMultiple;				// ����ġ ���� ���
		wGradeAttack = rvalue.wGradeAttack;				// ���� ���� ���
		wGradeDefense = rvalue.wGradeDefense;			// ��� ���� ���
		dwFlags = rvalue.dwFlags;						//	Trade �Ӽ�.
		dwBuyPrice	= rvalue.dwBuyPrice;				//	������ ���� ����.
		dwSellPrice = rvalue.dwSellPrice;				//	������ �Ǹ� ����.
		wReserved1 = rvalue.wReserved1;					// ��� ����
		wReserved2 = rvalue.wReserved2;					// ��� ����
		wReserved3 = rvalue.wReserved3;					// ��� ����
		wReserved4 = rvalue.wReserved4;					// ��� ����
		wReserved5 = rvalue.wReserved4;					// ��� ����
		dwReqCharClass = rvalue.dwReqCharClass;			//	������ �� �ִ� ������. ( EMCHARCLASS Flags )
		dwReqSchool = rvalue.dwReqSchool;				//	������ �� �ִ� �п�.
		sReqStats = rvalue.sReqStats;					//	�䱸 �ɸ��� Stats ��ġ.
		wReqLevelDW = rvalue.wReqLevelDW;				//	�䱸 Level.
		wReqLevelUP = rvalue.wReqLevelUP;				//	�䱸 Level.
		wReqPA = rvalue.wReqPA;							//	�䱸 ����ġ.
		wReqSA = rvalue.wReqSA;							//	�䱸 ���ġ.
		emReqBright = rvalue.emReqBright;				//	ĳ�� �Ӽ�. ( ��/�� )
		dwCoolTime = rvalue.dwCoolTime;
		emCoolType = rvalue.emCoolType;
		wInvenSizeX = rvalue.wInvenSizeX;				//	�κ��丮 ������. 
		wInvenSizeY = rvalue.wInvenSizeY;				//	�κ��丮 ������.
		sICONID = rvalue.sICONID;						//	������ �ε���.
		strFieldFile = rvalue.strFieldFile;				//	�ٴ� ���� ����.
		strInventoryFile = rvalue.strInventoryFile;		//	�κ��丮 ���� ����.
		strTargBodyEffect = rvalue.strTargBodyEffect;	//	��ǥ ������ ���� �״� ����Ʈ.
		strTargetEffect = rvalue.strTargetEffect;		//	��ǥ ���� ����Ʈ.
		strSelfBodyEffect = rvalue.strSelfBodyEffect;	//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
	
		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )	
			strWearingFileRight[i] = rvalue.strWearingFileRight[i];	//	���� ����.

		for ( int i=0; i<GLCI_NUM_8CLASS; ++i )	
			strWearingFileLeft[i] = rvalue.strWearingFileLeft[i];	//	���� ����.

		strPetWearingFile = rvalue.strPetWearingFile;
		strComment = rvalue.strComment;
		sSubID = rvalue.sSubID;
		wPosX = rvalue.wPosX;
		wPosY = rvalue.wPosY;

		bEnable = rvalue.bEnable;

		/*activity point, Juver, 2017/08/23 */
		dwReqActivityPoint = rvalue.dwReqActivityPoint;

		/*contribution point, Juver, 2017/08/23 */
		dwReqContributionPoint = rvalue.dwReqContributionPoint;

		/*UserNum ItemReq, Juver, 2017/06/27 */
		dwReqUserNum = rvalue.dwReqUserNum;

		/*item color, Juver, 2018/01/05 */
		bItemColor	= rvalue.bItemColor;
		wItemColor1 = rvalue.wItemColor1;
		wItemColor2 = rvalue.wItemColor2;

		/*item wrapper, Juver, 2018/01/11 */
		sidWrapperBox = rvalue.sidWrapperBox;

		/*item transfer card, Juver, 2018/01/18 */
		bItemTransfer = rvalue.bItemTransfer;

		return *this;
	}

};