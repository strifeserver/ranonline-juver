#include "stdafx.h"
#include "./RANPARAM.h"

#include "../Lib_Engine/Common/IniLoader.h"
#include "../Lib_Engine/DxCommon/DxFontMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace RANPARAM
{
	//game features

	/*product item, Juver, 2017/10/18 */
	BOOL bFeatureProduct = TRUE;	

	/*quick slot delay, Juver, 2017/10/29 */
	BOOL bFeatureQuickSlotDelay = FALSE;	
	DWORD dwFeatureQuickSlotDelay = 200;

	/*student record ui, Juver, 2017/10/30 */
	BOOL bFeatureStudentRecord = TRUE;

	/*activity system, Juver, 2017/11/04 */
	BOOL bFeatureActivity = TRUE;

	/*quest ui, Juver, 2017/11/06 */
	BOOL bFeatureModernQuestWindow = TRUE;

	/*charinfoview , Juver, 2017/11/11 */
	BOOL bFeatureViewCharInfo = TRUE;

	/*register page, Juver, 2017/11/18 */
	BOOL bFeatureRegister = TRUE;
	BOOL bFeatureRegisterUseMD5 = FALSE;

	/*character delete, Juver, 2017/11/18 */
	BOOL bFeatureCharacterDelete = FALSE;
	BOOL bFeatureCharacterDeleteMD5 = FALSE;

	/*recovery exp setting, Juver, 2017/11/18 */
	BOOL bFeatureUseRecoveryEXP = FALSE;

	/*hide gm info, Juver, 2017/11/26 */
	BOOL bFeatureHideGMInfo = FALSE;

	/*skill validity check, Juver, 2017/11/27 */
	WORD wFeatureSkillRangeCheckAdd = 50;

	/*pet skill info display, Juver, 2017/12/01 */
	BOOL bFeaturePetSkilDisplay = TRUE;

	/*regional chat, Juver, 2017/12/06 */
	BOOL bFeatureRegionalChatColor = TRUE;
	BYTE nFeatureRegionalChatColorR = 0x00;
	BYTE nFeatureRegionalChatColorG = 0xCE;
	BYTE nFeatureRegionalChatColorB = 0xD1;
	DWORD dwFeatureRegionalChatCost = 1; //region chat cost

	/*block back damage, Juver, 2017/12/12 */
	BOOL bFeatureBlockDamageBack = FALSE;
	float fFeatureBlockDamageBackTimer = 1.0f;

	/*clubwar verify non push or pull, Juver, 2017/12/13 */
	BOOL bFeatureClubWarVerifyDisablePushPull = FALSE;

	/*staff name in chat, Juver, 2017/12/26 */
	BOOL bFeatureChatShowStaffName = TRUE;

	/*change school card, Juver, 2018/01/12 */
	BOOL bFeatureChangeSchoolReqCleanQuest = FALSE;
	BOOL bFeatureChangeSchoolReqCleanGuild = FALSE;
	BOOL bFeatureChangeSchoolReqMaxLevel = FALSE;
	BOOL bFeatureChangeSchoolWipeQuest = FALSE;

	/*item transfer card, Juver, 2018/01/18 */
	DWORD dwFeatureItemTransferCost = 0;

   BOOL bFeatureDisplayCP = FALSE;
	BOOL LOAD_FEATURE( const TCHAR *szRootPath )
	{
		std::string	strfeature_file(szRootPath);
		strfeature_file += "\\Config.ini";

		CIniLoader cFILE;

		if( !cFILE.open( strfeature_file, true) )
		{
			return FALSE;
		}

		// param.ini use not error msg box
		cFILE.SetUseErrorMsgBox( FALSE );

		/*product item, Juver, 2017/10/18 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureProduct", 0, 1, bFeatureProduct );	

		/*quick slot delay, Juver, 2017/10/29 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureQuickSlotDelay", 0, 1, bFeatureQuickSlotDelay ); 
		cFILE.getflag ( "GAME_FEATURE", "dwFeatureQuickSlotDelay", 0, 1, dwFeatureQuickSlotDelay ); 

		/*student record ui, Juver, 2017/10/30 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureStudentRecord", 0, 1, bFeatureStudentRecord );	

		/*activity system, Juver, 2017/11/04 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureActivity", 0, 1, bFeatureActivity );	

		/*quest ui, Juver, 2017/11/06 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureModernQuestWindow", 0, 1, bFeatureModernQuestWindow );	

		/*charinfoview , Juver, 2017/11/11 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureViewCharInfo", 0, 1, bFeatureViewCharInfo );	

		/*register page, Juver, 2017/11/18 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureRegister", 0, 1, bFeatureRegister );	
		cFILE.getflag ( "GAME_FEATURE", "bFeatureRegisterUseMD5", 0, 1, bFeatureRegisterUseMD5 );	

		/*character delete, Juver, 2017/11/18 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureCharacterDelete", 0, 1, bFeatureCharacterDelete );	
		cFILE.getflag ( "GAME_FEATURE", "bFeatureCharacterDeleteMD5", 0, 1, bFeatureCharacterDeleteMD5 );	

		/*recovery exp setting, Juver, 2017/11/18 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureUseRecoveryEXP", 0, 1, bFeatureUseRecoveryEXP );	

		/*hide gm info, Juver, 2017/11/26 */	
		cFILE.getflag ( "GAME_FEATURE", "bFeatureHideGMInfo", 0, 1, bFeatureHideGMInfo );	

		/*skill validity check, Juver, 2017/11/27 */
		cFILE.getflag ( "GAME_FEATURE", "wFeatureSkillRangeCheckAdd", 0, 1, wFeatureSkillRangeCheckAdd );	

		/*pet skill info display, Juver, 2017/12/01 */
		cFILE.getflag ( "GAME_FEATURE", "bFeaturePetSkilDisplay", 0, 1, bFeaturePetSkilDisplay );	

		/*regional chat, Juver, 2017/12/06 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureRegionalChatColor", 0, 1, bFeatureRegionalChatColor );	
		cFILE.getflag ( "GAME_FEATURE", "nFeatureRegionalChatColorR", 0, 1, nFeatureRegionalChatColorR );	
		cFILE.getflag ( "GAME_FEATURE", "nFeatureRegionalChatColorG", 0, 1, nFeatureRegionalChatColorG );	
		cFILE.getflag ( "GAME_FEATURE", "nFeatureRegionalChatColorB", 0, 1, nFeatureRegionalChatColorB );	
		cFILE.getflag ( "GAME_FEATURE", "dwFeatureRegionalChatCost", 0, 1, dwFeatureRegionalChatCost );	

		/*block back damage, Juver, 2017/12/12 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureBlockDamageBack", 0, 1, bFeatureBlockDamageBack );	
		cFILE.getflag ( "GAME_FEATURE", "fFeatureBlockDamageBackTimer", 0, 1, fFeatureBlockDamageBackTimer );	

		/*clubwar verify non push or pull, Juver, 2017/12/13 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureClubWarVerifyDisablePushPull", 0, 1, bFeatureClubWarVerifyDisablePushPull );	

		/*staff name in chat, Juver, 2017/12/26 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureChatShowStaffName", 0, 1, bFeatureChatShowStaffName );	

		/*change school card, Juver, 2018/01/12 */
		cFILE.getflag ( "GAME_FEATURE", "bFeatureChangeSchoolReqCleanQuest", 0, 1, bFeatureChangeSchoolReqCleanQuest );	
		cFILE.getflag ( "GAME_FEATURE", "bFeatureChangeSchoolReqCleanGuild", 0, 1, bFeatureChangeSchoolReqCleanGuild );	
		cFILE.getflag ( "GAME_FEATURE", "bFeatureChangeSchoolReqMaxLevel", 0, 1, bFeatureChangeSchoolReqMaxLevel );	
		cFILE.getflag ( "GAME_FEATURE", "bFeatureChangeSchoolWipeQuest", 0, 1, bFeatureChangeSchoolWipeQuest );	

		/*item transfer card, Juver, 2018/01/18 */
		cFILE.getflag ( "GAME_FEATURE", "dwFeatureItemTransferCost", 0, 1, dwFeatureItemTransferCost );	
        cFILE.getflag ( "GAME_FEATURE", "bFeatureDisplayCP", 0, 1, bFeatureDisplayCP );

		return TRUE;
	}

};

