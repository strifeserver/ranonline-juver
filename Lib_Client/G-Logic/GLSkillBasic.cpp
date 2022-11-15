#include "stdafx.h"
#include "GLSkillBasic.h"
#include "./GLItemSuit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


namespace SKILL
{
	GLSKILL_ATT assign_att ( gloldskill_102::GLSKILL_ATT_102 emOld )
	{
		GLSKILL_ATT emAttack;
		switch ( emOld )
		{
		case gloldskill_102::SKILLATT_NOTHING:	emAttack = SKILLATT_NOTHING;	break;
		case gloldskill_102::SKILLATT_SWORD:	emAttack = SKILLATT_SWORD;	break;
		case gloldskill_102::SKILLATT_REV00:	emAttack = SKILLATT_SWORD;	break;
		case gloldskill_102::SKILLATT_DAGGER:	emAttack = SKILLATT_DAGGER;	break;
		case gloldskill_102::SKILLATT_SPEAR:	emAttack = SKILLATT_SPEAR;	break;
		case gloldskill_102::SKILLATT_BOW:		emAttack = SKILLATT_BOW;	break;
		case gloldskill_102::SKILLATT_THROW:	emAttack = SKILLATT_THROW;	break;
		case gloldskill_102::SKILLATT_NOCARE:	emAttack = SKILLATT_NOCARE;	break;
		default:	emAttack = SKILLATT_NOTHING;	break;
		};

		return emAttack;
	}

	GLSKILL_ATT assign_att ( gloldskill_103::GLSKILL_ATT_103 emOld )
	{
		GLSKILL_ATT emAttack;
		switch ( emOld )
		{
		case gloldskill_103::SKILLATT_NOTHING:	emAttack = SKILLATT_NOTHING;	break;
		case gloldskill_103::SKILLATT_SWORD:	emAttack = SKILLATT_SWORD;	break;
		case gloldskill_103::SKILLATT_BLADE:	emAttack = SKILLATT_BLADE;	break;
		case gloldskill_103::SKILLATT_DAGGER:	emAttack = SKILLATT_DAGGER;	break;
		case gloldskill_103::SKILLATT_SPEAR:	emAttack = SKILLATT_SPEAR;	break;
		case gloldskill_103::SKILLATT_STICK:	emAttack = SKILLATT_STICK;	break;
		case gloldskill_103::SKILLATT_BOW:		emAttack = SKILLATT_BOW;	break;
		case gloldskill_103::SKILLATT_THROW:	emAttack = SKILLATT_THROW;	break;
		case gloldskill_103::SKILLATT_NOCARE:	emAttack = SKILLATT_NOCARE;	break;
		default:	emAttack = SKILLATT_NOTHING;		break;
		};

		return emAttack;
	}

	GLSKILL_ATT assign_att ( gloldskill_108::GLSKILL_ATT_108 emOld )
	{
		GLSKILL_ATT emAttack;
		switch ( emOld )
		{
		case gloldskill_108::SKILLATT_NOTHING:	emAttack = SKILLATT_NOTHING;	break;
		case gloldskill_108::SKILLATT_SWORD:	emAttack = SKILLATT_SWORD;	break;
		case gloldskill_108::SKILLATT_BLADE:	emAttack = SKILLATT_BLADE;	break;
		case gloldskill_108::SKILLATT_SWORDBLADE:	emAttack = SKILLATT_SWORDBLADE;	break;
		case gloldskill_108::SKILLATT_DAGGER:	emAttack = SKILLATT_DAGGER;	break;
		case gloldskill_108::SKILLATT_SPEAR:	emAttack = SKILLATT_SPEAR;	break;
		case gloldskill_108::SKILLATT_STICK:	emAttack = SKILLATT_STICK;	break;
		case gloldskill_108::SKILLATT_GAUNT:	emAttack = SKILLATT_GAUNT;	break;
		case gloldskill_108::SKILLATT_BOW:		emAttack = SKILLATT_BOW;	break;
		case gloldskill_108::SKILLATT_THROW:	emAttack = SKILLATT_THROW;	break;
		case gloldskill_108::SKILLATT_NOCARE:	emAttack = SKILLATT_NOCARE;	break;
		default:	emAttack = SKILLATT_NOTHING;		break;
		};

		return emAttack;
	}

	GLSKILL_ATT assign_att ( gloldskill_110::GLSKILL_ATT_110 emOld )
	{
		GLSKILL_ATT emAttack;
		switch ( emOld )
		{
		case gloldskill_110::SKILLATT_SWORD:	emAttack = SKILLATT_SWORD;	break;
		case gloldskill_110::SKILLATT_BLADE:	emAttack = SKILLATT_BLADE;	break;
		case gloldskill_110::SKILLATT_SWORDBLADE:	emAttack = SKILLATT_SWORDBLADE;	break;
		case gloldskill_110::SKILLATT_DAGGER:	emAttack = SKILLATT_DAGGER;	break;
		case gloldskill_110::SKILLATT_SPEAR:	emAttack = SKILLATT_SPEAR;	break;
		case gloldskill_110::SKILLATT_STICK:	emAttack = SKILLATT_STICK;	break;
		case gloldskill_110::SKILLATT_GAUNT:	emAttack = SKILLATT_GAUNT;	break;
		case gloldskill_110::SKILLATT_BOW:	emAttack = SKILLATT_BOW;	break;
		case gloldskill_110::SKILLATT_THROW:	emAttack = SKILLATT_THROW;	break;
		case gloldskill_110::SKILLATT_GUN:	emAttack = SKILLATT_GUN;	break;
		case gloldskill_110::SKILLATT_RAILGUN:	emAttack = SKILLATT_RAILGUN;	break;
		case gloldskill_110::SKILLATT_PORTALGUN:	emAttack = SKILLATT_PORTALGUN;	break;
		case gloldskill_110::SKILLATT_SHOTGUN:	emAttack = SKILLATT_SHOTGUN;	break;
		case gloldskill_110::SKILLATT_RAILPORTALGUN:	emAttack = SKILLATT_RAILPORTALGUN;	break;
		case gloldskill_110::SKILLATT_SCYTHE:	emAttack = SKILLATT_SCYTHE;	break;
		case gloldskill_110::SKILLATT_DUALSPEAR:	emAttack = SKILLATT_DUALSPEAR;	break;
		case gloldskill_110::SKILLATT_SHURIKEN:	emAttack = SKILLATT_SHURIKEN;	break;
		case gloldskill_110::SKILLATT_FIST:	emAttack = SKILLATT_FIST;	break;
		case gloldskill_110::SKILLATT_WAND:	emAttack = SKILLATT_WAND;	break;
		case gloldskill_110::SKILLATT_CUBE:	emAttack = SKILLATT_CUBE;	break;
		case gloldskill_110::SKILLATT_WHIP:	emAttack = SKILLATT_WHIP;	break;
		case gloldskill_110::SKILLATT_NOCARE:	emAttack = SKILLATT_NOCARE;	break;

		default:	emAttack = SKILLATT_NOTHING;		break;
		};

		return emAttack;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_100 &sOldData )
	{
		sNATIVEID				= sOldData.sNATIVEID;

		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );
		dwGRADE					= sOldData.dwGRADE;

		emROLE					= sOldData.emROLE;
		emAPPLY					= sOldData.emAPPLY;

		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;
		
		wTARRANGE				= sOldData.wTARRANGE;

		emUSE_LITEM				= assign_att ( sOldData.emUSE_LITEM );
		emUSE_RITEM				= assign_att ( sOldData.emUSE_RITEM );
		dwData = 0;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_101 &sOldData )
	{
		sNATIVEID				= sOldData.sNATIVEID;

		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );
		dwGRADE					= sOldData.dwGRADE;

		emROLE					= sOldData.emROLE;
		emAPPLY					= sOldData.emAPPLY;

		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;
		
		wTARRANGE				= sOldData.wTARRANGE;

		emUSE_LITEM				= assign_att ( sOldData.emUSE_LITEM );
		emUSE_RITEM				= assign_att ( sOldData.emUSE_RITEM );
		dwData = 0;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_102 &sOldData )
	{
		sNATIVEID				= sOldData.sNATIVEID;

		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );
		dwGRADE					= sOldData.dwGRADE;

		emROLE					= sOldData.emROLE;
		emAPPLY					= sOldData.emAPPLY;

		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;
		
		wTARRANGE				= sOldData.wTARRANGE;

		emUSE_LITEM				= assign_att ( sOldData.emUSE_LITEM );
		emUSE_RITEM				= assign_att ( sOldData.emUSE_RITEM );

		dwData = 0;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_103 &sOldData )
	{
		sNATIVEID				= sOldData.sNATIVEID;

		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );
		dwGRADE					= sOldData.dwGRADE;

		emROLE					= sOldData.emROLE;
		emAPPLY					= sOldData.emAPPLY;

		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;
		
		wTARRANGE				= sOldData.wTARRANGE;

		emUSE_LITEM				= assign_att( sOldData.emUSE_LITEM );
		emUSE_RITEM				= assign_att( sOldData.emUSE_RITEM );

		dwData = 0;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_105 &sOldData )
	{
		sNATIVEID				= sOldData.sNATIVEID;

		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );
		dwGRADE					= sOldData.dwGRADE;
		dwMAXLEVEL				= sOldData.dwMAXLEVEL;

		emROLE					= sOldData.emROLE;
		emAPPLY					= sOldData.emAPPLY;

		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;

		wTARRANGE				= sOldData.wTARRANGE;

		emUSE_LITEM				= assign_att( sOldData.emUSE_LITEM );
		emUSE_RITEM				= assign_att( sOldData.emUSE_RITEM );

		dwData = 0;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_106 &sOldData )
	{
		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );

		sNATIVEID				= sOldData.sNATIVEID;
		bLearnView				= sOldData.bLearnView;
		dwMAXLEVEL				= sOldData.dwMAXLEVEL;
		dwGRADE					= sOldData.dwGRADE;
		emAPPLY					= sOldData.emAPPLY;
		emROLE					= sOldData.emROLE;
		wTARRANGE				= sOldData.wTARRANGE;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;
		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emUSE_LITEM				= assign_att( sOldData.emUSE_LITEM );
		emUSE_RITEM				= assign_att( sOldData.emUSE_RITEM );

		dwData = 0;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_107 &sOldData )
	{
		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );

		sNATIVEID				= sOldData.sNATIVEID;
		bLearnView				= sOldData.bLearnView;
		dwMAXLEVEL				= sOldData.dwMAXLEVEL;
		dwGRADE					= sOldData.dwGRADE;
		emAPPLY					= sOldData.emAPPLY;
		emROLE					= sOldData.emROLE;
		wTARRANGE				= sOldData.wTARRANGE;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;
		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emUSE_LITEM				= assign_att( sOldData.emUSE_LITEM );
		emUSE_RITEM				= assign_att( sOldData.emUSE_RITEM );

		dwData = 0;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_108 &sOldData )
	{
		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );

		sNATIVEID				= sOldData.sNATIVEID;
		bLearnView				= sOldData.bLearnView;
		dwMAXLEVEL				= sOldData.dwMAXLEVEL;
		dwGRADE					= sOldData.dwGRADE;
		emAPPLY					= sOldData.emAPPLY;
		emROLE					= sOldData.emROLE;
		emACTION				= sOldData.emACTION;
		wTARRANGE				= sOldData.wTARRANGE;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;
		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emUSE_LITEM				= assign_att( sOldData.emUSE_LITEM );
		emUSE_RITEM				= assign_att( sOldData.emUSE_RITEM );

		dwData = 0;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_109 &sOldData )
	{
		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );

		sNATIVEID				= sOldData.sNATIVEID;
		wData					= sOldData.wData;
		bLearnView				= sOldData.bLearnView;
		dwMAXLEVEL				= sOldData.dwMAXLEVEL;
		dwGRADE					= sOldData.dwGRADE;
		emAPPLY					= sOldData.emAPPLY;
		emROLE					= sOldData.emROLE;
		emACTION				= sOldData.emACTION;
		wTARRANGE				= sOldData.wTARRANGE;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;
		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emUSE_LITEM				= assign_att( sOldData.emUSE_LITEM );
		emUSE_RITEM				= assign_att( sOldData.emUSE_RITEM );

		dwData = 0;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_110 &sOldData )
	{
		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );

		sNATIVEID				= sOldData.sNATIVEID;
		wData					= sOldData.wData;
		bLearnView				= sOldData.bLearnView;
		dwMAXLEVEL				= sOldData.dwMAXLEVEL;
		dwGRADE					= sOldData.dwGRADE;
		emAPPLY					= sOldData.emAPPLY;
		emROLE					= sOldData.emROLE;
		emACTION				= sOldData.emACTION;
		wTARRANGE				= sOldData.wTARRANGE;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;
		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emUSE_LITEM				= assign_att( sOldData.emUSE_LITEM );
		emUSE_RITEM				= assign_att( sOldData.emUSE_RITEM );

		dwData = 0;
	}

	void SSKILLBASIC::Assign ( SSKILLBASIC_111 &sOldData )
	{
		StringCchCopy ( szNAME, MAX_SZNAME, sOldData.szNAME );

		sNATIVEID				= sOldData.sNATIVEID;
		wData					= sOldData.wData;
		bLearnView				= sOldData.bLearnView;
		dwMAXLEVEL				= sOldData.dwMAXLEVEL;
		dwGRADE					= sOldData.dwGRADE;
		emAPPLY					= sOldData.emAPPLY;
		emROLE					= sOldData.emROLE;
		emACTION				= sOldData.emACTION;
		wTARRANGE				= sOldData.wTARRANGE;
		emIMPACT_SIDE			= sOldData.emIMPACT_SIDE;
		emIMPACT_TAR			= sOldData.emIMPACT_TAR;
		emIMPACT_REALM			= sOldData.emIMPACT_REALM;
		emUSE_LITEM				= sOldData.emUSE_LITEM;
		emUSE_RITEM				= sOldData.emUSE_RITEM;

		dwData = 0;
	}

	VOID SSKILLBASIC::SaveCsvHead ( std::fstream &SFile )
	{
		SFile << "sNATIVEID wMainID" << ",";
		SFile << "sNATIVEID wSubID" << ",";

		SFile << "szNAME" << ",";

//		��ȹ�� ��û���� ������
//		SFile << "szNAME" << ",";

		SFile << "dwGRADE" << ",";
		SFile << "dwMAXLEVEL" << ",";

		SFile << "emROLE" << ",";
		SFile << "emAPPLY" << ",";
		SFile << "emACTION" << ",";


		SFile << "emIMPACT_TAR" << ",";
		SFile << "emIMPACT_REALM" << ",";
		SFile << "emIMPACT_SIDE" << ",";

		SFile << "wTARRANGE" << ",";

		SFile << "emUSE_LITEM" << ",";
		SFile << "emUSE_RITEM" << ",";

		SFile << "bLearnView" << ",";
		SFile << "wData" << ",";
		SFile << "dwData" << ",";
	}

	VOID SSKILLBASIC::SaveCsv ( std::fstream &SFile )
	{
		SFile << sNATIVEID.wMainID << ",";
		SFile << sNATIVEID.wSubID << ",";

		std::string str = szNAME;
		STRUTIL::OutputStrCsv( SFile, str );

//		��ȹ�� ��û���� ������
/*
		if( szNAME )
		{
			const char* szpLongName = GLStringTable::GetInstance().GetString( szNAME, GLStringTable::SKILL );
			if( szpLongName )
				str = szpLongName;
		}
		STRUTIL::OutputStrCsv( SFile, str );
*/

		SFile << dwGRADE << ",";
		SFile << dwMAXLEVEL << ",";

		SFile << emROLE << ",";
		SFile << emAPPLY << ",";
		SFile << emACTION << ",";

		SFile << emIMPACT_TAR << ",";
		SFile << emIMPACT_REALM << ",";
		SFile << emIMPACT_SIDE << ",";

		SFile << wTARRANGE << ",";

		SFile << emUSE_LITEM << ",";
		SFile << emUSE_RITEM << ",";

		SFile << bLearnView << ",";
		SFile << wData << ",";
		SFile << dwData << ",";
	}

	VOID SSKILLBASIC::LoadCsv ( CStringArray &StrArray, int &iCsvCur )
	{
		sNATIVEID.wMainID = (WORD)atoi( StrArray[ iCsvCur++ ] );
		sNATIVEID.wSubID = (WORD)atoi( StrArray[ iCsvCur++ ] );

		std::string str;
		STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], str );
		memset( szNAME, 0, sizeof(char) * MAX_SZNAME );
		StringCchCopy( szNAME, MAX_SZNAME, str.c_str() );

//		��ȹ�� ��û���� ������
//		++iCsvCur;	// Item Name

		dwGRADE = (DWORD)atol( StrArray[ iCsvCur++ ] );
		dwMAXLEVEL = (DWORD)atol( StrArray[ iCsvCur++ ] );

		emROLE = (EMROLE)atoi( StrArray[ iCsvCur++ ] );
		emAPPLY = (EMAPPLY)atoi( StrArray[ iCsvCur++ ] );
		emACTION = (EMACTION)atoi( StrArray[ iCsvCur++ ] );

		emIMPACT_TAR = (EMIMPACT_TAR)atoi( StrArray[ iCsvCur++ ] );
		emIMPACT_REALM = (EMIMPACT_REALM)atoi( StrArray[ iCsvCur++ ] );
		emIMPACT_SIDE = (EMIMPACT_SIDE)atoi( StrArray[ iCsvCur++ ] );

		wTARRANGE = (WORD)atoi( StrArray[ iCsvCur++ ] );

		emUSE_LITEM = (GLSKILL_ATT)atoi( StrArray[ iCsvCur++ ] );
		emUSE_RITEM = (GLSKILL_ATT)atoi( StrArray[ iCsvCur++ ] );

		bLearnView = (bool)atoi( StrArray[ iCsvCur++ ] );
		wData = (WORD)atoi( StrArray[ iCsvCur++ ] );
		dwData = (DWORD)atoi( StrArray[ iCsvCur++ ] );
	}
};

namespace COMMENT
{
	std::string SKILL_ROLE[SKILL::EMROLE_NSIZE] =
	{
		"Active",
		"Passive"
	};

	std::string SKILL_APPLY[SKILL::EMAPPLY_NSIZE] =
	{
		"Melee",
		"Missile",
		"Magic"
	};

	std::string SKILLATTACK[SKILLATT_NSIZE+1] =
	{
		"Don't Install",
		"Sword",
		"Blade",
		"Dagger",
		"Spear",
		"Club",
		"Gauntlet",
		"Bow",
		"Throw",
		"Dual Gun",
		"Rail Gun",
		"Portal Gun",
		"Scythe",
		"Dual Spear",
		"Shuriken",
		"Fist",
		"Wand",
		"Cube",
		"Whip",
		"Hammer",
		"Shield",
		"Umbrella",
		"No Type Check",
	};

	std::string SKILL_ACTION_TYPE[SKILL::EMACTION_NSIZE] = 
	{
		"Normal Type",
		"Buff Type",
		"Debuff Type",
		"Limit Type",
	};
};