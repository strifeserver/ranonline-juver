#include "stdafx.h"
#include "./RANPARAM.h"

#include "../Lib_Engine/Common/compbyte.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace RANPARAM
{
	EMSERVICE_TYPE		emSERVICE_TYPE		= EMSERVICE_DEFAULT;
	BOOL				bXML_USE			= TRUE;

	BOOL				bSAVE_USERID		= FALSE;
	std::string			strENC_USERID		= "";
	std::string			strENC_CHARID		= "";

	const std::string	strIDNULL			= "(null)";

	BOOL				bDIS_CONFT			= FALSE;		//	'�ڵ�' ��� �ź�.
	BOOL				bDIS_TRADE			= FALSE;		//	'�ڵ�' �ŷ� �ź�.
	BOOL				bDIS_PARTY			= FALSE;		//	'�ڵ�' ��Ƽ �ź�.
	BOOL				bDIS_RIDE			= FALSE;		//	'�ڵ�' ��Ƽ �ź�.
	BOOL				bDIS_FRIEND			= FALSE;		//	'�ڵ�' ģ�� ��û �ź�.
	BOOL				bSHOW_SIMPLEHP		= TRUE;			//	�̴� HP ǥ��
	BOOL				b3D_SOUND			= FALSE;
	BOOL				bSHOW_TIP			= TRUE;			//	�� �����ֱ�
	BOOL				bMOVABLE_ON_CHAT	= FALSE;		//	ä��â ������ �����̱�
	BOOL				bFORCED_ATTACK		= TRUE;			//	���� ����
	BOOL				bNAME_DISPLAY		= TRUE;			//	�̸� �׻� ǥ��
	BOOL				bNON_Rebirth		= FALSE;		//  ��Ȱ ��ų ����
	BOOL				bPrivateStats		= FALSE;		/*charinfoview , Juver, 2017/11/12 */

	BOOL				bCONFT_BOUND		= TRUE;			//	��ý� ���� ���� ����.
	WORD				wCONFT_RECOVER		= 0;			//	��ý� ȸ���� ����.
	float				fCONFT_HP_RATE		= 1.0f;			//	��ý� ü�� Ȯ�� ����.
	float				fCONFT_TAR_HP_RATE	= 1.0f;			//	��ý� ü�� Ȯ�� ���� [ ����(���δ�ýø�) ].

	DWORD				dwPARTY_GET_ITEM	= 3;			//	��Ƽ�ɼ� ������ �й� ��Ģ.(����Ʈ�� ��������)
	DWORD				dwPARTY_GET_MONEY	= 3;			//	��Ƽ�ɼ� �� �й� ��Ģ.(����Ʈ�� �յ�й�)
	
	int					QuickSlot[QUICK_SLOT_NUM]		= { DIK_Q, DIK_W, DIK_E, DIK_A, DIK_S, DIK_D };
	
	int					SkillSlot[QUICK_SKILL_NUM]		= { DIK_1, DIK_2, DIK_3, DIK_4, DIK_5, DIK_6,
															DIK_7, DIK_8, DIK_9, DIK_0};
	
	int					MenuShotcut[QUICK_MENU_NUM]		= { DIK_I, DIK_C, DIK_K, DIK_P, DIK_T, DIK_G, 
															DIK_F, DIK_M, DIK_B, DIK_R, DIK_H, DIK_L,
															DIK_X, DIK_Z ,DIK_U, DIK_J, DIK_O};
	
	int					DefaultShotcutKey[QUICK_ALL_NUM]	= { DIK_Q, DIK_W, DIK_E, DIK_A, DIK_S, DIK_D,
																DIK_1, DIK_2, DIK_3, DIK_4, DIK_5, DIK_6,
																DIK_7, DIK_8, DIK_9, DIK_0,	DIK_I, DIK_C,
																DIK_K, DIK_P, DIK_T, DIK_G, DIK_F, DIK_M, 
																DIK_B, DIK_R, DIK_H, DIK_L, DIK_X, DIK_Z,
																DIK_U, DIK_J, DIK_O };

	// KeySettingWindow ���� ���̺� ����Ű ������ �ٸ��� �����Ǿ� �־ �ʿ�
	int					KeySettingToRanparam[QUICK_MENU_NUM] = { SHOTCUT_INVEN, SHOTCUT_CHAR, SHOTCUT_SKILL, SHOTCUT_PARTY,
																 SHOTCUT_QUEST, SHOTCUT_CLUB, SHOTCUT_FRIEND, SHOTCUT_MAP,
																 SHOTCUT_CHATMACRO, SHOTCUT_ITEMBANK, SHOTCUT_ITEMSHOP, SHOTCUT_RUN,
																 SHOTCUT_HELP, SHOTCUT_PET, SHOTCUT_ATTACKMODE, SHOTCUT_PKMODE, SHOTCUT_SUMMON};

	// BasicMenu ���� ���̺� ����Ű ������ �ٸ��� �����Ǿ� �־ �ʿ�
	int					BasicMenuToRanparam[BASICMENU_NUM] = { SHOTCUT_INVEN, SHOTCUT_CHAR,	SHOTCUT_SKILL, SHOTCUT_PARTY,
															   SHOTCUT_QUEST, SHOTCUT_CLUB, SHOTCUT_FRIEND, SHOTCUT_MAP,
															   SHOTCUT_ITEMBANK, SHOTCUT_RUN, SHOTCUT_ITEMSHOP, SHOTCUT_CHATMACRO};
	
	CString				ChatMacro[CHAT_MACRO_NUM];

	BOOL				bCHECKWHQL			= TRUE;
	DWORD				dwScrWidth			= 1024;
	DWORD				dwScrHeight			= 768;
	EMSCREEN_FORMAT		emScrFormat			= EMSCREEN_F16;
	UINT				uScrRefreshHz		= 60;
	BOOL				bScrWindowed		= FALSE;
	BOOL				bScrWndHalfSize		= TRUE;
	BOOL				bScrWndFullSize		= FALSE;

	bool				bDISP_CONSOLE		= false;
	bool				bDISP_FPS			= false;

	BOOL				bGameCursor			= TRUE;

	LONG				nSndSfx				= 0;
	LONG				nSndMap				= 0;
	LONG				nSndMusic			= 0;
	DWORD				dw3DAlgorithm		= 0;
	DWORD				dwSndBufferSize		= 10;

	BOOL				bSndMuteSfx			= FALSE;
	BOOL				bSndMuteMap			= FALSE;
	BOOL				bSndMuteMusic		= FALSE;
	BOOL				bUsePassiveDN		= FALSE;


	DWORD				dwVideoLevel		= 0;
	DWORD				dwShadowChar		= 4;
	BOOL				bBuff				= TRUE;
	BOOL				bShadowLand			= TRUE;
	BOOL				bRealReflect		= TRUE;
	BOOL				bRefract			= TRUE;
	BOOL				bGlow				= TRUE;
	BOOL				bPost				= TRUE;
	BOOL				bFrameLimit			= FALSE;
	DWORD				dwSkinDetail		= 2;
	DWORD				dwTextureFilter		= 0;

	BOOL				bBUFF_SFX			= TRUE;
	BOOL				bEMOTICON			= TRUE;

	BOOL				bClickEffect		= TRUE;
	BOOL				bTargetEffect		= TRUE;
	BOOL				bMineEffect			= TRUE;

	BOOL				bCharacterSimple	= FALSE;	/*character simple, Juver, 2017/10/01 */
	BOOL				bHideSkillEffect	= FALSE;	/*skill effect setting, Juver, 2017/10/01 */

	DWORD				dwFogRange			= 0;

	TCHAR				LoginAddress[128]	= "211.172.252.50";

	UINT				nLoginPort			= 5001;		/*login port, Juver, 2017/11/16 */

	TCHAR				FtpAddressTable[MAX_FTP][128] =
											{
												"", "", "", "", "",
												"", "", "", "", "",
												"", "", "", "", "",
												"", "", "", "", "",
												"", "", "", "",
											};
	TCHAR				HttpAddressTable[MAX_HTTP][128] =
											{
												"patch.ran-online.co.kr", "", "", "", "",
												"", "", "", "", "",
												"", "", "", "", "",
												"", "", "", "", "",
												"", "", "", "",
											};

	CString				strNewsURL			= "ran-online.co.kr/news/patch_list/list2.aspx";
	CString				strConnectionURL	= "2046.5u56.com";

	UINT				nChinaRegion		= MAX_CHINA_REGION;

	SERVER_SET			China_Region[MAX_CHINA_REGION];
	
	DWORD				dwLangSet			= 0;
	CString				strGDIFont			= "����ü";
	CString				strFontType			= "D3DFONT";
	
	CString				strCountry			= "kr";
	CString				strLauncherText		= "Launcher.xml";
	CString				strGameInText		= "gameintext.xml";
	CString				strGameExText		= "gameextext.xml";
	CString				strGameWord			= "gameword.xml";
	CString				strServerText		= "servertext.xml";

	TCHAR				HelpAddress[STRING_NUM_128] = _T("\\data\\help\\help.htm");
	// �߱� : http://2046.5u56.com/gameshop/gameshop.html
	TCHAR				ItemShopAddress[STRING_NUM_128] = _T("about:blank");
	TCHAR				RPFDataPath[STRING_NUM_128] = _T("\\package\\data.rpf");
	TCHAR				ClientWindowTitle[STRING_NUM_128] = _T("RanOnline GameClient");

	
	BOOL bNPCShopConfirm = TRUE;	/*npc shop, Juver, 2017/07/27 */
	BOOL bItemPreviewStance = TRUE; /*item preview, Juver, 2017/07/28 */
	BOOL bVehicleWindowRun = FALSE; /*vehicle system, Juver, 2017/08/08 */
	
	DWORD dwPotsCount = 0;

	std::string strIDPARAM;
	std::string strIDPARAM2;
	std::string strIDPARAM3;

	std::string strJPUUID;

	/* anti-zoomout cheat fix, SeiferXIII 2020/05/17 */
	float fZoomOutValue;

	/* anti-zoomout cheat fix, SeiferXIII 2020/05/17 */
	float GETZOOMOUTVALUE()						{ return fZoomOutValue; }
	void SETZOOMOUTVALUE ( float m_fZoomOutValue )	{ fZoomOutValue = m_fZoomOutValue; }

	void SETIDPARAM( std::string strPARAM )		{ strIDPARAM = strPARAM; }
	void SETIDPARAM2( std::string strPARAM )	{ strIDPARAM2 = strPARAM; }
	void SETIDPARAM3( std::string strPARAM )	{ strIDPARAM3 = strPARAM; }
	void SETJAPANUUID( std::string strUUID )	{ strJPUUID = strUUID; }

	const TCHAR* GETIDPARAM()					{ return strIDPARAM.c_str(); }
	const TCHAR* GETIDPARAM2()					{ return strIDPARAM2.c_str(); }
	const TCHAR* GETIDPARAM3()					{ return strIDPARAM3.c_str(); }
	const TCHAR* GETJAPANUUID()					{ return strJPUUID.c_str(); }

	bool VALIDIDPARAM ()
	{
		switch ( emSERVICE_TYPE )
		{
//		Japan �α��� ��� ����
//		case EMSERVICE_JAPAN:
//			return !strIDPARAM.empty() && !strIDPARAM2.empty() && !strIDPARAM3.empty();

		default:
			return !strIDPARAM.empty();
		};

		return false;
	}

	enum { emENCKEYLENG = MAX_COMPUTERNAME_LENGTH+32 };
	char szEncryptKEY[emENCKEYLENG] = "unnamed";

	void SETENCRYPT ()
	{
		StringCchCopy ( szEncryptKEY, emENCKEYLENG, "XWeRtSOn32QwRtQs" );
	}

	BOOL SETCHARID( const TCHAR* szCHARID )
	{
		strENC_CHARID = szCHARID;
		
		return TRUE;
	}

	std::string GETCHARID()
	{
		return strENC_CHARID;
	}


	BOOL SETUSERID ( const TCHAR* szUSERID )
	{
		SETENCRYPT ();

		BYTE szENC_USERID[MAX_PATH] = "";

		size_t nKEYLENG = strlen ( szEncryptKEY );
		size_t nIDLENG = strlen ( szUSERID );
		compbyte::encrypt ( (UCHAR*) szEncryptKEY, (DWORD)nKEYLENG, (const UCHAR*) szUSERID, szENC_USERID, (DWORD)nIDLENG );
		compbyte::hex2string( szENC_USERID, (DWORD)nIDLENG, strENC_USERID );
	
		return TRUE;
	}

	std::string GETUSERID_ENC ()
	{
		return strENC_USERID;
	}

	std::string GETUSERID_DEC ()
	{
		SETENCRYPT ();

		const char* szENC_USERID = strENC_USERID.c_str();

		size_t nKEYLENG = strlen ( szEncryptKEY );
		size_t nIDLENG = strlen ( szENC_USERID );
		if ( nIDLENG == 0 )		return "";

		BYTE szHEX_USERID[MAX_PATH] = "";
		char szDEC_USERID[MAX_PATH] = "";

		SecureZeroMemory ( szHEX_USERID, MAX_PATH );
		SecureZeroMemory ( szDEC_USERID, MAX_PATH );

		BOOL bOK = compbyte::string2hex ( (UCHAR*)szENC_USERID, (UCHAR*) szHEX_USERID, (DWORD) nIDLENG );
		size_t nHEXLENG = strlen ( (char*) szHEX_USERID );

		compbyte::decrypt ( (UCHAR*) szEncryptKEY, (DWORD) nKEYLENG, (const UCHAR*) szHEX_USERID, (UCHAR*) szDEC_USERID, (DWORD) nHEXLENG );

		return szDEC_USERID;
	}

	DWORD GetTextureFilter()
	{
		EMTEXTUREFILTER emFILTER = (EMTEXTUREFILTER)dwTextureFilter;

		if ( emFILTER == EMTEXTUREFILTER_ANISOTROPIC_2 || emFILTER == EMTEXTUREFILTER_ANISOTROPIC_4 ||
			emFILTER == EMTEXTUREFILTER_ANISOTROPIC_8 || emFILTER == EMTEXTUREFILTER_ANISOTROPIC_16 )
		{
			return D3DTEXF_ANISOTROPIC;
		}

		return D3DTEXF_LINEAR;
	}

	DWORD GetTextureAF()
	{
		EMTEXTUREFILTER emFILTER = (EMTEXTUREFILTER)dwTextureFilter;

		switch ( emFILTER )
		{
		case EMTEXTUREFILTER_ANISOTROPIC_2:		return 2;	break;
		case EMTEXTUREFILTER_ANISOTROPIC_4:		return 4;	break;
		case EMTEXTUREFILTER_ANISOTROPIC_8:		return 8;	break;
		case EMTEXTUREFILTER_ANISOTROPIC_16:	return 16;	break;
		};
		return 0;
	}
	
};

