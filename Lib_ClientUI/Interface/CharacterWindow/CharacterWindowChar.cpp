#include "StdAfx.h"
#include "../Lib_Client/G-Logic/GLGaeaClient.h"
#include "../Lib_Engine/DxCommon/d3dfont.h"
#include "BasicTextBox.h"
#include "BasicButton.h"
#include "BasicButtonRadio.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "InnerInterface.h"
#include "ModalCallerID.h"
#include "ModalWindow.h"
#include "BasicLineBox.h"
#include "CharacterWindowChar.h"
#include "CharacterWindowCharStat.h"
#include "CharacterWindowCharWear.h"
#include "CharacterWindowCharWearEx.h"
#include "CharacterWindowCharRender.h"
#include "DxGlobalStage.h"
#include "../Lib_Client/G-Logic/GLCharacter.h"
#include "GLActivity.h"
#include "./BasicComboBoxRollOver.h"
#include "RANPARAM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCharacterWindowChar::CCharacterWindowChar () :
	m_pStatRegion ( NULL ),
	m_RollOverID(NO_ID)

	, m_pCharWear ( NULL )
	, m_pCharWearEx ( NULL )
	, m_pNameText ( NULL )
	, m_pClubText ( NULL )
	, m_pTitleText ( NULL )
	, m_pAcademy ( NULL )
	, m_pLifeP ( NULL )
	, m_pHelp ( NULL )
	, m_pAbility( NULL )
	, m_pRender( NULL )
	, m_pBadgeText(NULL)

	/*activity system, Juver, 2017/11/05 */
	, m_pButtonTitle ( NULL )
	, m_pComboBoxTitleRollOver ( NULL )
	
{
}

CCharacterWindowChar::~CCharacterWindowChar ()
{
}


CBasicTextBox* CCharacterWindowChar::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword, UI_FLAG_DEFAULT, cID );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );	
	RegisterControl ( pStaticText );

	return pStaticText;
}

CUIControl*	CCharacterWindowChar::CreateControl ( const char* szControl, const UIGUID& cID )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl, UI_FLAG_DEFAULT, cID );
	RegisterControl ( pControl );
	return pControl;
}

CBasicButton* CCharacterWindowChar::CreateFlipButton ( char* szButton, char* szButtonFlip, UIGUID ControlID, WORD wFlipType )
{
	CBasicButton* pButton = new CBasicButton;
	pButton->CreateSub ( this, szButton, UI_FLAG_DEFAULT, ControlID );
	pButton->CreateFlip ( szButtonFlip, wFlipType );
	RegisterControl ( pButton );
	return pButton;
}

void CCharacterWindowChar::CreateSubControl ()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );
	const EMCHARCLASS emCharClass = DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass;
	const int nClassType = CharClassToIndex ( emCharClass );
	
	const int nAlignTop	= TEXT_ALIGN_TOP;
	const int nAlignLeft = TEXT_ALIGN_LEFT;
	const int nAlignCenter = TEXT_ALIGN_CENTER_X;	
	const DWORD& dwSilver = NS_UITEXTCOLOR::SILVER;


	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxWhite( "CHARACTER_WINDOW_WHITE_LINEBOX" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CHARACTER_WINDOW_SCHOOL_REGION" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CHARACTER_WINDOW_EQUIP_REGION" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CHARACTER_WINDOW_TITLE_NAME_REGION" );
	RegisterControl ( pBasicLineBox );

	CBasicTextBox* pTextBox = NULL;
	pTextBox = CreateStaticControl ( "CHARACTER_WINDOW_BRIGHT_TEXT", pFont, nAlignLeft );
	pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 5) );

	pTextBox = CreateStaticControl ( "CHARACTER_WINDOW_ACTIVITY_POINT_TEXT", pFont, nAlignLeft );
	pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 2) );

	pTextBox = CreateStaticControl ( "CHARACTER_WINDOW_CONTRIB_POINT_TEXT", pFont, nAlignLeft );
	pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 7) );

	pTextBox = CreateStaticControl ( "CHARACTER_WINDOW_EXTRA_ACT_POINT_TEXT", pFont, nAlignLeft );
	pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 8) );

	//pkscore
	pTextBox = CreateStaticControl ( "CHARACTER_WINDOW_PKSCORE_TEXT", pFont, nAlignLeft );
	pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 9) );

	m_pPkscore = CreateStaticControl ( "CHARACTER_WINDOW_PKSCORE_VALUE", pFont, nAlignLeft );
	m_pPkdeath = CreateStaticControl ( "CHARACTER_WINDOW_PKDEATH_VALUE", pFont, nAlignLeft );

	pTextBox = CreateStaticControl ( "CHARACTER_WINDOW_PKDEATH_TEXT", pFont, nAlignLeft );
	pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 10) );

	m_pAcademy = CreateStaticControl ( "CHARACTER_WINDOW_ACADEMY_DEPARTMENT_TEXT", pFont, nAlignLeft );
	m_pLifeP = CreateStaticControl ( "CHARACTER_WINDOW_ACTIVITY_POINT_VALUE", pFont, nAlignLeft );
	m_pContrib = CreateStaticControl ( "CHARACTER_WINDOW_CONTRIB_POINT_VALUE", pFont, nAlignLeft );
	m_pActivity = CreateStaticControl ( "CHARACTER_WINDOW_EXTRA_ACT_POINT_VALUE", pFont, nAlignLeft );
	m_pBadgeText = CreateStaticControl ( "CHARACTER_WINDOW_STAT_BADGE_VALUE", pFont, nAlignTop );

	m_pBrightFrame = CreateControl ( "CHARACTER_WINDOW_BRIGHTBAR" );		
	m_pBrightSlider = CreateControl ( "CHARACTER_WINDOW_BRIGHTBAR_THUMB" , CHARACTER_ACADEMY_BRIGHTBAR );

	m_pHelp = new CBasicButton;
	m_pHelp->CreateSub ( this, "CHARACTER_WINDOW_ACADEMY_QUESTION_BUTTON" , UI_FLAG_DEFAULT, CHARACTER_ACADEMY_HELP );
	m_pHelp->CreateFlip ( "CHARACTER_WINDOW_ACADEMY_QUESTION_BUTTON_OVER", CBasicButton::MOUSEIN_FLIP );
	m_pHelp->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pHelp );

	m_pStatRegion = new CCharacterWindowCharStat;
	m_pStatRegion->CreateSub ( this, "CHARACTER_WINDOW_STAT_REGION", UI_FLAG_YSIZE, CHARACTER_STATS );
	m_pStatRegion->CreateSubControl ();
	RegisterControl ( m_pStatRegion );

	m_pRender = new CCharacterWindowCharRender;
	m_pRender->CreateSub ( this, "CHARACTER_WINDOW_CHARACTER_MESHRENDER" );
	m_pRender->CreateSubControl ();
	RegisterControl ( m_pRender );

	if( nClassType == GLCI_EXTREME_W || nClassType == GLCI_EXTREME_M )
	{
		m_pCharWearEx = new CCharacterWindowCharWearEx;
		m_pCharWearEx->CreateSub ( this, "CHARACTER_WINDOW_WEAR_WINDOW", UI_FLAG_YSIZE, CHARACTER_WEAR_EX );
		m_pCharWearEx->CreateSubControl ();
		RegisterControl ( m_pCharWearEx );
	}else{
		m_pCharWear = new CCharacterWindowCharWear;
		m_pCharWear->CreateSub ( this, "CHARACTER_WINDOW_WEAR_WINDOW", UI_FLAG_YSIZE, CHARACTER_WEAR );
		m_pCharWear->CreateSubControl ();
		RegisterControl ( m_pCharWear );
	}

	m_pNameText = CreateStaticControl ( "CHARACTER_WINDOW_CHARACTER_NAME_TEXT", pFont, nAlignCenter );
	m_pClubText = CreateStaticControl ( "CHARACTER_WINDOW_CLUB_NAME_TEXT", pFont, nAlignCenter );
	m_pTitleText = CreateStaticControl ( "CHARACTER_WINDOW_TITLE_NAME_TEXT", pFont, nAlignCenter );
	
	m_pAbility = new CBasicButtonRadio;
	m_pAbility->CreateSub ( this, "CHARACTER_WINDOW_STAT_RADIO_BUTTON" );
	m_pAbility->CreateRadioWithText ( pFont, CBasicButtonRadio::SIZE_TEXT_50, nAlignLeft );
	m_pAbility->SetVisibleSingle ( TRUE );
	m_pAbility->SetFlip( TRUE );
	m_pAbility->SetOneLineText( ID2GAMEINTEXT("CHARACTER_WINDOW_STAT" ), dwSilver );
	RegisterControl ( m_pAbility );

	/*activity system, Juver, 2017/11/05 */
	if ( RANPARAM::bFeatureActivity )
	{
		m_pButtonTitle = new CBasicButton;
		m_pButtonTitle->CreateSub ( this, "CHARACTER_TITLE_BUTTON", UI_FLAG_DEFAULT, CHARACTER_TITLE_BUTTON );
		m_pButtonTitle->CreateFlip ( "CHARACTER_TITLE_BUTTON_F", CBasicButton::MOUSEIN_FLIP );
		m_pButtonTitle->SetControlNameEx ( "CHARACTER_TITLE_BUTTON" );
		RegisterControl ( m_pButtonTitle );

		m_pComboBoxTitleRollOver = new CBasicComboBoxRollOver;
		m_pComboBoxTitleRollOver->CreateSub ( this, "BASIC_COMBOBOX_ROLLOVER", UI_FLAG_XSIZE | UI_FLAG_YSIZE, CHARACTER_TITLE_COMBO_ROLLOVER );
		m_pComboBoxTitleRollOver->CreateBaseComboBoxRollOver ( "CHARACTER_TITLE_COMBO_ROLLOVER" );			
		m_pComboBoxTitleRollOver->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pComboBoxTitleRollOver );
	}
}

void CCharacterWindowChar::SetData ( const GLCHARLOGIC& sCharData )
{
	m_pAcademy->ClearText();
	m_pLifeP->ClearText();
	m_pNameText->ClearText();
	m_pContrib->ClearText();
	m_pActivity->ClearText();
	m_pBadgeText->ClearText();

	//pkscore
	m_pPkscore->ClearText();
	m_pPkdeath->ClearText();

	CString strTemp;

	if ( m_pBadgeText )
	{
		if ( strlen( sCharData.m_szBadge ) )
		{
			m_pBadgeText->SetText( sCharData.m_szBadge, NS_UITEXTCOLOR::DODGERBLUE ); 
		}else{
			m_pBadgeText->SetText( "No Badge" );
		}
	}

	if ( m_pNameText )
	{
		CString strTemp;
		strTemp.Format("[ID:%d] [Name:%s]",sCharData.m_dwCharID,sCharData.m_szName);
		m_pNameText->SetOneLineText ( strTemp.GetString() , NS_UITEXTCOLOR::WHITE);
	}

	CString strCombine;
	strCombine.Format ( "%s,%s", GLCONST_CHAR::strSCHOOLNAME[sCharData.m_wSchool].c_str() , COMMENT::CHARCLASS[CharClassToIndex( sCharData.m_emClass )].c_str() );
	m_pAcademy->AddText ( strCombine, NS_UITEXTCOLOR::WHITE );
	
	strCombine.Format ( "%d", sCharData.m_nLiving );
	m_pLifeP->SetOneLineText ( strCombine, NS_UITEXTCOLOR::WHITE );

	strCombine.Format ( "%I64d", sCharData.m_llContributionPoint );
	m_pContrib->SetOneLineText ( strCombine, NS_UITEXTCOLOR::WHITESMOKE );

	strCombine.Format ( "%d", sCharData.m_dwActivityPoint );
	m_pActivity->SetOneLineText ( strCombine, NS_UITEXTCOLOR::WHITESMOKE );

	strCombine.Format ( "%d", sCharData.m_dwPKScore );
	m_pPkscore->SetOneLineText ( strCombine, NS_UITEXTCOLOR::GREEN_WOW );

	strCombine.Format ( "%d", sCharData.m_dwPKDeath );
	m_pPkdeath->SetOneLineText ( strCombine, NS_UITEXTCOLOR::DISABLE );


	{
		const int nMIN = -100;
		const int nMAX = 100;
		const int nRANGE = nMAX - nMIN;
		int nPercent = sCharData.GETBRIGHTPER ();
		nPercent = -(nPercent);
		if ( nPercent < nMIN ) nPercent = nMIN;
		if ( nPercent > nMAX ) nPercent = nMAX;
		nPercent += nMAX;
		float fPercent = static_cast<float>(nPercent) / static_cast<float>(nRANGE);
		const UIRECT& rcFramePos = m_pBrightFrame->GetGlobalPos ();
		const UIRECT& rcThumbPos = m_pBrightSlider->GetGlobalPos ();
		float fMOVE = (rcFramePos.sizeX - rcThumbPos.sizeX) * fPercent;
		float fLeft = rcFramePos.left + fMOVE;
		m_pBrightSlider->SetGlobalPos ( D3DXVECTOR2 ( fLeft, rcThumbPos.top ) );
	}

	{
		GLCLUB& sCLUB = GLGaeaClient::GetInstance().GetCharacter ()->m_sCLUB;
		CString strTemp;
		if ( sCLUB.IsMember( sCharData.m_dwCharID ) )
		{
			strTemp.Format("[ID:%d][Name:%s]",sCLUB.m_dwID,sCLUB.m_szName);
		}else{
			strTemp.Format("[%s]",ID2GAMEINTEXT("CHARACTER_WINDOW_EMPTY_CLUB") );
		}
		if ( m_pClubText )	m_pClubText->SetOneLineText ( strTemp.GetString(), NS_UITEXTCOLOR::YELLOW );
	}
}

void CCharacterWindowChar::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
		case CHARACTER_TITLE_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_DOWN )
				{
					m_pComboBoxTitleRollOver->SetVisibleSingle( TRUE );
					m_pComboBoxTitleRollOver->SetScrollPercent ( 0.0f );

					m_RollOverID = CHARACTER_TITLE_COMBO_ROLLOVER;
					m_bFirstLBUP = TRUE;
				}
			}
		}break;

		/*activity system, Juver, 2017/11/05 */
	case CHARACTER_TITLE_COMBO_ROLLOVER:
		{
			if ( dwMsg & UI_MSG_COMBOBOX_ROLLOVER_SCROLL )
			{				
				DWORD dwMsg = GetMessageEx ();
				dwMsg &= ~UI_MSG_COMBOBOX_ROLLOVER_SCROLL;
				ResetMessageEx ();
				AddMessageEx ( dwMsg );

				break;
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{				
				int nIndex = m_pComboBoxTitleRollOver->GetSelectIndex ();
				if ( nIndex < 0 ) return ;

				DWORD dwSelected = m_pComboBoxTitleRollOver->GetTextData( nIndex );
				GLGaeaClient::GetInstance().GetCharacter()->ReqChangeBadge( dwSelected );
			}
		}
		break;
	case CHARACTER_ACADEMY_BRIGHTBAR:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter ();

				CString strTemp;				
				strTemp.Format ( "%d", pCharacter->m_nBright );

				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strTemp, NS_UITEXTCOLOR::WHITE );
			}
		}
		break;

	case CHARACTER_ACADEMY_HELP:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CString strTemp;
				strTemp.Format( "%s %s %s %s %s %s", 
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_1_TEXT" ),
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_1" ),
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_2_TEXT" ),
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_2" ),
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_3_TEXT" ),
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_3" ) );
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO_SPLIT( strTemp.GetString(), NS_UITEXTCOLOR::DARKLBUE );
			}
		}
		break;

	case CHARACTER_WEAR:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pCharWear->GetItemIndex ();
				if ( nIndex < 0 ) return ;				

				//if ( CUIMan::GetFocusControl () == this )
				{
					SITEMCUSTOM sItemCustom = m_pCharWear->GetItem ( nIndex );
					if ( sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItemCustom, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
					}

					/*item preview, Juver, 2017/07/27 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().PreviewItem( sItemCustom );
							return;
						}
					}

					/*item link, Juver, 2017/07/31 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_RB_UP )
						{
							CInnerInterface::GetInstance().LinkItem( &sItemCustom );
							return;
						}
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					EMSLOT emSlot = m_pCharWear->GetItemSlot ();
					GLGaeaClient::GetInstance().GetCharacter()->ReqSlotTo ( emSlot );
				}

				/*rightclick wear/unwear, Juver, 2017/06/24 */
				if ( dwMsg & UIMSG_RB_UP )
				{
					EMSLOT emSlot = m_pCharWear->GetItemSlot ();

					SNATIVEID sid_item_hold = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM().sNativeID;
					if ( sid_item_hold != NATIVEID_NULL () )
					{
						BOOL bUse = GLGaeaClient::GetInstance().GetCharacter()->InvenUseToPutOn ( emSlot );
						if ( bUse )	return;
					}

					GLGaeaClient::GetInstance().GetCharacter()->ReqWearToInven ( emSlot );
					return;
				}
			}
		}
		break;

	case CHARACTER_WEAR_EX:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pCharWearEx->GetItemIndex ();
				if ( nIndex < 0 ) return ;				

				//if ( CUIMan::GetFocusControl () == this )
				{
					SITEMCUSTOM sItemCustom = m_pCharWearEx->GetItem ( nIndex );
					if ( sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItemCustom, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
					}

					/*item preview, Juver, 2017/07/27 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().PreviewItem( sItemCustom );
							return;
						}
					}

					/*item link, Juver, 2017/07/31 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_RB_UP )
						{
							CInnerInterface::GetInstance().LinkItem( &sItemCustom );
							return;
						}
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					EMSLOT emSlot = m_pCharWearEx->GetItemSlot ();
					GLGaeaClient::GetInstance().GetCharacter()->ReqSlotTo ( emSlot );
				}

				/*rightclick wear/unwear, Juver, 2017/06/24 */
				if ( dwMsg & UIMSG_RB_UP )
				{
					EMSLOT emSlot = m_pCharWearEx->GetItemSlot ();

					SNATIVEID sid_item_hold = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM().sNativeID;
					if ( sid_item_hold != NATIVEID_NULL () )
					{
						BOOL bUse = GLGaeaClient::GetInstance().GetCharacter()->InvenUseToPutOn ( emSlot );
						if ( bUse )	return;
					}

					GLGaeaClient::GetInstance().GetCharacter()->ReqWearToInven ( emSlot );
					return;
				}
			}
		}
		break;
	};
}

void CCharacterWindowChar::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();	
	SetData ( sCharData );

	if ( m_RollOverID == NO_ID )
	{
		CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	}else{
		ResetMessageEx ();

		CUIControl::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

		CUIControl* pControl = m_ControlContainer.FindControl ( m_RollOverID );
		if ( !pControl )
		{
			return ;
		}

		pControl->Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

		DWORD dwControlMsg = pControl->GetMessageEx ();
		NS_UIDEBUGSET::BlockBegin ();
		if ( dwControlMsg ) TranslateUIMessage ( m_RollOverID, dwControlMsg );
		NS_UIDEBUGSET::BlockEnd ();

		//	��ũ�ѹٿ� ����� �~�A���� �ƴϰ�		
		if ( !(dwControlMsg & UI_MSG_COMBOBOX_ROLLOVER_SCROLL) )
		{
			DWORD dwMsg = GetMessageEx ();
			if ( dwMsg & UIMSG_LB_UP )
			{
				if ( !m_bFirstLBUP )
				{
					m_RollOverID = NO_ID;
					pControl->SetVisibleSingle ( FALSE );					
				}
				m_bFirstLBUP = FALSE;
			}
		}
	}
}

void CCharacterWindowChar::LoadBadge( const GLCHARLOGIC& sCharData )
{
	if ( !RANPARAM::bFeatureActivity )	return;

	if ( !m_pComboBoxTitleRollOver )	return;

	m_pComboBoxTitleRollOver->ClearText();

	int nIndex = m_pComboBoxTitleRollOver->AddText( ID2GAMEWORD("CHARWINDOW_TITLE",0) );
	m_pComboBoxTitleRollOver->SetTextData( nIndex, UINT_MAX );

	SACTIVITY_CHAR_DATA_MAP mapCharActivity = sCharData.m_mapActivityDone;

	SACTIVITY_CHAR_DATA_MAP_ITER pos = mapCharActivity.begin();
	SACTIVITY_CHAR_DATA_MAP_ITER end = mapCharActivity.end();
	for ( ; pos!=end; ++pos )
	{
		SACTIVITY_CHAR_DATA sactivity_data( (*pos).second );

		SACTIVITY_FILE_DATA* pactivity = GLActivity::GetInstance().GetActivity( sactivity_data.dwActivityID );
		if( !pactivity ) continue;
		if( !pactivity->bRewardBadge ) continue;
		if( !pactivity->strBadgeString.size() ) continue;

		int nIndex = m_pComboBoxTitleRollOver->AddText( pactivity->strBadgeString.c_str() );
		m_pComboBoxTitleRollOver->SetTextData( nIndex, pactivity->dwActivityID );
	}
}
void CCharacterWindowChar::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );

	if( bVisible )
	{
		const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();
		/*activity system, Juver, 2017/11/05 */
		LoadBadge( sCharData );
	}
	else
	{
		/*activity system, Juver, 2017/11/05 */
		if ( m_pComboBoxTitleRollOver )
			m_pComboBoxTitleRollOver->SetVisibleSingle( FALSE );

		m_RollOverID = NO_ID;
		m_bFirstLBUP = FALSE;
		ClearRender();
	}

	//if( bVisible )
	//{
	//	if( m_pCharWearEx )
	//	{
	//		if( GLGaeaClient::GetInstance().GetCharacter()->IsUseArmSub() )
	//		{
	//			m_pCharWearEx->SetTabButton( FALSE );
	//		}else{
	//			m_pCharWearEx->SetTabButton( TRUE );
	//		}
	//	}
	//}else{
	//	ClearRender();
	//}
}

void CCharacterWindowChar::SetArmSwapTabButton( BOOL bArmSub )
{
	if( m_pCharWearEx )
	{
		m_pCharWearEx->SetTabButton( bArmSub );
	}
}
void CCharacterWindowChar::ClearRender()
{
	if( m_pRender )
	{
		m_pRender->ClearRender();
	}
}