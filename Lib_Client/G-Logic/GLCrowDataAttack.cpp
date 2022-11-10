#include "stdafx.h"
#include "GLCrowDataAttack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

SCROWATTACK& SCROWATTACK::operator= ( const SCROWATTACK_100 &OldData )
{
	bUsed				= OldData.bUsed;
	emAttRgType			= OldData.emAttRgType;
	wRange				= OldData.wRange;

	sDamage				= OldData.sDamage;
	fDelay				= OldData.fDelay;

	wUse_SP				= OldData.wUse_SP;

	strAniFile			= OldData.szAniFile;
	sAniAttack			= OldData.sAniAttack;

	strSelfBodyEffect	= OldData.szSelfBodyEffect;
	strTargBodyEffect	= OldData.szTargBodyEffect;
	strTargetEffect		= OldData.szTargetEffect;

	return *this;
}

SCROWATTACK& SCROWATTACK::operator= ( const SCROWATTACK_101 &OldData )
{
	bUsed				= OldData.bUsed;
	emAttRgType			= OldData.emAttRgType;
	wRange				= OldData.wRange;

	sDamage				= OldData.sDamage;
	fDelay				= OldData.fDelay;

	wUse_SP				= OldData.wUse_SP;

	strAniFile			= OldData.szAniFile;
	sAniAttack			= OldData.sAniAttack;

	strSelfBodyEffect	= OldData.szSelfBodyEffect;
	strTargBodyEffect	= OldData.szTargBodyEffect;
	strTargetEffect		= OldData.szTargetEffect;

	return *this;
}

SCROWATTACK& SCROWATTACK::operator= ( const SCROWATTACK_102 &OldData )
{
	bUsed			= OldData.bUsed;
	emAttRgType		= OldData.emAttRgType;
	wRange			= OldData.wRange;

	sDamage			= OldData.sDamage;
	fDelay			= OldData.fDelay;

	wUse_SP			= OldData.wUse_SP;

	strAniFile		= OldData.szAniFile;
	sAniAttack		= OldData.sAniAttack;

	skill_id		= OldData.skill_id;
	skill_lev		= 0;
	skill_tar		= CROWSKTAR_ENEMY;

	emBLOW_TYPE		= OldData.emBLOW_TYPE;
	fBLOW_RATE		= OldData.fBLOW_RATE;
	fBLOW_LIFE		= OldData.fBLOW_LIFE;
	fBLOW_VAR1		= OldData.fBLOW_VAR1;
	fBLOW_VAR2		= OldData.fBLOW_VAR2;

	strSelfBodyEffect	= OldData.szSelfBodyEffect;
	strTargBodyEffect	= OldData.szTargBodyEffect;
	strTargetEffect		= OldData.szTargetEffect;

	return *this;
}

SCROWATTACK& SCROWATTACK::operator= ( const SCROWATTACK_103 &OldData )
{
	bUsed			= OldData.bUsed;
	emAttRgType		= OldData.emAttRgType;
	wRange			= OldData.wRange;

	sDamage			= OldData.sDamage;
	fDelay			= OldData.fDelay;

	wUse_SP			= OldData.wUse_SP;

	strAniFile		= OldData.szAniFile;
	sAniAttack.Assign ( OldData.sAniAttack );

	skill_id		= OldData.skill_id;
	skill_lev		= OldData.skill_lev;
	skill_tar		= OldData.skill_tar;

	emBLOW_TYPE		= OldData.emBLOW_TYPE;
	fBLOW_RATE		= OldData.fBLOW_RATE;
	fBLOW_LIFE		= OldData.fBLOW_LIFE;
	fBLOW_VAR1		= OldData.fBLOW_VAR1;
	fBLOW_VAR2		= OldData.fBLOW_VAR2;

	strSelfBodyEffect	= OldData.szSelfBodyEffect;
	strTargBodyEffect	= OldData.szTargBodyEffect;
	strTargetEffect		= OldData.szTargetEffect;

	return *this;
}

SCROWATTACK& SCROWATTACK::operator= ( const SCROWATTACK_104 &OldData )
{
	bUsed			= OldData.bUsed;
	emAttRgType		= OldData.emAttRgType;
	wRange			= OldData.wRange;

	sDamage			= OldData.sDamage;
	fDelay			= OldData.fDelay;

	wUse_SP			= OldData.wUse_SP;

	strAniFile		= OldData.szAniFile;
	sAniAttack		= OldData.sAniAttack;

	skill_id		= OldData.skill_id;
	skill_lev		= OldData.skill_lev;
	skill_tar		= OldData.skill_tar;

	emBLOW_TYPE		= OldData.emBLOW_TYPE;
	fBLOW_RATE		= OldData.fBLOW_RATE;
	fBLOW_LIFE		= OldData.fBLOW_LIFE;
	fBLOW_VAR1		= OldData.fBLOW_VAR1;
	fBLOW_VAR2		= OldData.fBLOW_VAR2;

	strSelfBodyEffect	= OldData.szSelfBodyEffect;
	strTargBodyEffect	= OldData.szTargBodyEffect;
	strTargetEffect		= OldData.szTargetEffect;

	return *this;
}

SCROWATTACK& SCROWATTACK::operator= ( const SCROWATTACK &value )
{
	bUsed			= value.bUsed;
	emAttRgType		= value.emAttRgType;
	wRange			= value.wRange;

	sDamage			= value.sDamage;
	fDelay			= value.fDelay;

	wUse_SP			= value.wUse_SP;

	strAniFile		= value.strAniFile;
	sAniAttack		= value.sAniAttack;

	skill_id		= value.skill_id;
	skill_lev		= value.skill_lev;
	skill_tar		= value.skill_tar;

	emBLOW_TYPE		= value.emBLOW_TYPE;
	fBLOW_RATE		= value.fBLOW_RATE;
	fBLOW_LIFE		= value.fBLOW_LIFE;
	fBLOW_VAR1		= value.fBLOW_VAR1;
	fBLOW_VAR2		= value.fBLOW_VAR2;

	strSelfBodyEffect	= value.strSelfBodyEffect;
	strTargBodyEffect	= value.strTargBodyEffect;
	strTargetEffect		= value.strTargetEffect;

	return *this;
}

bool SCROWATTACK::LOAD_0105 ( basestream &SFile )
{
	DWORD dwDATA(0);

	SFile >> bUsed;
	SFile >> dwDATA; emAttRgType = (EMATT_RGTYPE) dwDATA;
	SFile >> wRange;

	SFile >> sDamage.dwData;
	SFile >> fDelay;

	SFile >> wUse_SP;

	SFile >> strAniFile;
	SFile.ReadBuffer ( &sAniAttack, sizeof(sAniAttack) );

	SFile >> skill_id.dwID;
	SFile >> skill_lev;
	SFile >> dwDATA; skill_tar = (EMCROWSKTAR) dwDATA;

	SFile >> dwDATA; emBLOW_TYPE = (EMSTATE_BLOW) dwDATA;
	SFile >> fBLOW_RATE;
	SFile >> fBLOW_LIFE;
	SFile >> fBLOW_VAR1;
	SFile >> fBLOW_VAR2;

	SFile >> strSelfBodyEffect;
	SFile >> strTargBodyEffect;
	SFile >> strTargetEffect;

	return true;
}

bool SCROWATTACK::LOAD_0107 ( basestream &SFile )
{
	DWORD dwDATA(0);

	SFile >> bUsed;
	SFile >> dwDATA; emAttRgType = (EMATT_RGTYPE) dwDATA;
	SFile >> wRange;
	SFile >> wUse_SP;
	SFile >> sDamage.dwData;
	SFile >> fDelay;
	SFile >> skill_id.dwID;
	SFile >> skill_lev;
	SFile >> dwDATA; skill_tar = (EMCROWSKTAR) dwDATA;
	SFile >> dwDATA; emBLOW_TYPE = (EMSTATE_BLOW) dwDATA;
	SFile >> fBLOW_RATE;
	SFile >> fBLOW_LIFE;
	SFile >> fBLOW_VAR1;
	SFile >> fBLOW_VAR2;

	std::string strAni;
	SFile >> strAni;

	CString strTEMP = strAni.c_str();
	int nIndex = strTEMP.ReverseFind ( '.' );
	if ( nIndex >= 0 )
	{
		CString strCfgFile = strTEMP.Left(nIndex) + ".x";
		strAniFile = strCfgFile.GetString();
	}

	SFile.ReadBuffer ( &sAniAttack, sizeof(sAniAttack) );

	SFile >> strSelfBodyEffect;
	SFile >> strTargBodyEffect;
	SFile >> strTargetEffect;

	return true;
}

bool SCROWATTACK::LOAD ( basestream &SFile )
{
	DWORD dwDATA(0);

	SFile >> bUsed;
	SFile >> dwDATA; emAttRgType = (EMATT_RGTYPE) dwDATA;
	SFile >> wRange;
	SFile >> wUse_SP;
	SFile >> sDamage.dwData;
	SFile >> fDelay;
	SFile >> skill_id.dwID;
	SFile >> skill_lev;
	SFile >> dwDATA; skill_tar = (EMCROWSKTAR) dwDATA;
	SFile >> dwDATA; emBLOW_TYPE = (EMSTATE_BLOW) dwDATA;
	SFile >> fBLOW_RATE;
	SFile >> fBLOW_LIFE;
	SFile >> fBLOW_VAR1;
	SFile >> fBLOW_VAR2;
	SFile >> strAniFile;
	SFile.ReadBuffer ( &sAniAttack, sizeof(sAniAttack) );
	SFile >> strSelfBodyEffect;
	SFile >> strTargBodyEffect;
	SFile >> strTargetEffect;

	return true;
}

bool SCROWATTACK::SAVE ( CSerialFile &SFile )
{
	SFile << bUsed;
	SFile << (DWORD) emAttRgType;
	SFile << wRange;
	SFile << wUse_SP;
	SFile << sDamage.dwData;
	SFile << fDelay;
	SFile << skill_id.dwID;
	SFile << skill_lev;
	SFile << (DWORD) skill_tar;
	SFile << (DWORD) emBLOW_TYPE;
	SFile << fBLOW_RATE;
	SFile << fBLOW_LIFE;
	SFile << fBLOW_VAR1;
	SFile << fBLOW_VAR2;
	SFile << strAniFile;
	SFile.WriteBuffer ( &sAniAttack, sizeof(sAniAttack) );
	SFile << strSelfBodyEffect;
	SFile << strTargBodyEffect;
	SFile << strTargetEffect;

	return true;
}

VOID SCROWATTACK::SaveCsvHead ( std::fstream &SFile, int iIndex )
{
	SFile << iIndex << " bUsed" << ",";
	SFile << iIndex << " emAttRgType" << ",";
	SFile << iIndex << " wRange" << ",";

	SFile << iIndex << " sDamage wLow" << ",";
	SFile << iIndex << " sDamage wHigh" << ",";
	SFile << iIndex << " fDelay" << ",";

	SFile << iIndex << " wUse_SP" << ",";

	SFile << iIndex << " strAniFile" << ",";

	SFile << iIndex << " sAniAttack dwSTime" << ",";
	SFile << iIndex << " sAniAttack dwETime" << ",";
	SFile << iIndex << " sAniAttack UNITTIME" << ",";
	SFile << iIndex << " sAniAttack dwFlags" << ",";
	SFile << iIndex << " sAniAttack MainType" << ",";
	SFile << iIndex << " sAniAttack SubType" << ",";
	SFile << iIndex << " sAniAttack wDivCount" << ",";
	for( int i=0; i<ACF_DIV; ++i )
		SFile << iIndex << " sAniAttack wDivFrame " << i << ",";

	SFile << iIndex << " skill_id wMainID" << ",";
	SFile << iIndex << " skill_id wSubID" << ",";
	SFile << iIndex << " skill_lev" << ",";
	SFile << iIndex << " skill_tar" << ",";

	SFile << iIndex << " emBLOW_TYPE" << ",";
	SFile << iIndex << " fBLOW_RATE" << ",";
	SFile << iIndex << " fBLOW_LIFE" << ",";
	SFile << iIndex << " fBLOW_VAR1" << ",";
	SFile << iIndex << " fBLOW_VAR2" << ",";

	SFile << iIndex << " strSelfBodyEffect" << ",";
	SFile << iIndex << " strTargBodyEffect" << ",";
	SFile << iIndex << " strTargetEffect" << ",";
}

VOID SCROWATTACK::SaveCsv ( std::fstream &SFile )
{
	SFile << bUsed << ",";
	SFile << emAttRgType << ",";
	SFile << wRange << ",";

	SFile << sDamage.wLow << ",";
	SFile << sDamage.wHigh << ",";
	SFile << fDelay << ",";

	SFile << wUse_SP << ",";

	STRUTIL::OutputStrCsv( SFile, strAniFile );

	SFile << sAniAttack.m_dwSTime << ",";
	SFile << sAniAttack.m_dwETime << ",";
	SFile << sAniAttack.m_UNITTIME << ",";
	SFile << sAniAttack.m_dwFlags << ",";
	SFile << sAniAttack.m_MainType << ",";
	SFile << sAniAttack.m_SubType << ",";
	SFile << sAniAttack.m_wDivCount << ",";
	for( int i=0; i<ACF_DIV; ++i )
		SFile << sAniAttack.m_wDivFrame[i] << ",";

	SFile << skill_id.wMainID << ",";
	SFile << skill_id.wSubID << ",";
	SFile << skill_lev << ",";
	SFile << skill_tar << ",";

	SFile << emBLOW_TYPE << ",";
	SFile << fBLOW_RATE << ",";
	SFile << fBLOW_LIFE << ",";
	SFile << fBLOW_VAR1 << ",";
	SFile << fBLOW_VAR2 << ",";

	STRUTIL::OutputStrCsv( SFile, strSelfBodyEffect );
	STRUTIL::OutputStrCsv( SFile, strTargBodyEffect );
	STRUTIL::OutputStrCsv( SFile, strTargetEffect );
}

VOID SCROWATTACK::LoadCsv ( CStringArray &StrArray, int& iCsvCur )
{
	bUsed = (BOOL)atol( StrArray[ iCsvCur++ ] );
	emAttRgType = (EMATT_RGTYPE)atoi( StrArray[ iCsvCur++ ] );
	wRange = (WORD)atoi( StrArray[ iCsvCur++ ] );

	sDamage.wLow = (WORD)atoi( StrArray[ iCsvCur++ ] );
	sDamage.wHigh = (WORD)atoi( StrArray[ iCsvCur++ ] );
	fDelay = (float)atof( StrArray[ iCsvCur++ ] );

	wUse_SP = (WORD)atol( StrArray[ iCsvCur++ ] );

	STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strAniFile );

	sAniAttack.m_dwSTime = (DWORD)atol( StrArray[ iCsvCur++ ] );
	sAniAttack.m_dwETime = (DWORD)atol( StrArray[ iCsvCur++ ] );
	sAniAttack.m_UNITTIME = (DWORD)atol( StrArray[ iCsvCur++ ] );
	sAniAttack.m_dwFlags = (DWORD)atol( StrArray[ iCsvCur++ ] );
	sAniAttack.m_MainType = (EMANI_MAINTYPE)atoi( StrArray[ iCsvCur++ ] );
	sAniAttack.m_SubType = (EMANI_SUBTYPE)atoi( StrArray[ iCsvCur++ ] );
	sAniAttack.m_wDivCount = (WORD)atoi( StrArray[ iCsvCur++ ] );
	for( int i=0; i<ACF_DIV; ++i )
		sAniAttack.m_wDivFrame[i] = (WORD)atoi( StrArray[ iCsvCur++ ] );

	skill_id.wMainID = (WORD)atoi( StrArray[ iCsvCur++ ] );
	skill_id.wSubID = (WORD)atoi( StrArray[ iCsvCur++ ] );
	skill_lev = (WORD)atoi( StrArray[ iCsvCur++ ] );
	skill_tar = (EMCROWSKTAR)atoi( StrArray[ iCsvCur++ ] );

	emBLOW_TYPE = (EMSTATE_BLOW)atoi( StrArray[ iCsvCur++ ] );
	fBLOW_RATE = (float)atof( StrArray[ iCsvCur++ ] );
	fBLOW_LIFE = (float)atof( StrArray[ iCsvCur++ ] );
	fBLOW_VAR1 = (float)atof( StrArray[ iCsvCur++ ] );
	fBLOW_VAR2 = (float)atof( StrArray[ iCsvCur++ ] );

	STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strSelfBodyEffect );
	STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strTargBodyEffect );
	STRUTIL::InputStrCsv( StrArray[ iCsvCur++ ], strTargetEffect );
}

namespace COMMENT
{
	std::string CROWSKTAR[CROWSKTAR_SIZE] =
	{
		"SkillTarget Our",
		"SkillTarget Enemy",
	};
};