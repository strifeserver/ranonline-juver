#include "StdAfx.h"
#include "InventoryWindow.h"
#include "InventoryPage.h"
#include "ItemBankPage.h"
#include "UITextControl.h"
#include "GLGaeaClient.h"
#include "ModalWindow.h"
#include "ModalCallerID.h"
#include "GameTextControl.h"
#include "InnerInterface.h"
#include "MarketWindow.h"
#include "d3dfont.h"
#include "DxGlobalStage.h"
#include "BasicTextButton.h"
#include "BasicButtonText.h"
#include "BasicLineBox.h"
#include "BasicTextBox.h"
#include "BasicButton.h"
#include "DxFontMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CInventoryWindow::CInventoryWindow ()
	: m_pPage( NULL )
	, m_pPage2( NULL )
	, m_pMoneyTextBox( NULL )
	, m_nONE_VIEW_SLOT( 4 )
	, nSTATE(0)
	, fSortTimer(0.0f)

{
	memset ( m_pPageButton, 0, sizeof ( CBasicTextButton* ) * 3 );
}

CInventoryWindow::~CInventoryWindow ()
{
	nSTATE = 0;
	fSortTimer = GLCONST_CHAR::fSORTTIME;
}

void CInventoryWindow::CreateSubControl ()
{

	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );
	const int nAlignCenterBoth = TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y;

	const EMCHARCLASS emCharClass = DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass;
	const int nClassType = CharClassToIndex ( emCharClass );

	CString strButtonKeyword[3] = 
	{
		"INVENTORY_PAGE_INVEN",
		"INVENTORY_PAGE_BANK",
		"INVENTORY_PAGE_WANT"
	};

	for ( int i = 0; i < 3; i++ )
	{	
		m_pPageButton[i] = CreateTextButton23 ( strButtonKeyword[i].GetString (), INVENTORY_PAGE_BUTTON0 + i, (char*)ID2GAMEWORD ( "NEW_INVENTORY_BUTTON", i ) );
	}

	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxWhite( "INVENTORY_WINDOW_WHITE_LINEBOX" );
	RegisterControl ( pBasicLineBox );

	CBasicButton * pButtonInv = new CBasicButton;
	pButtonInv->CreateSub( this, "INVENTORY_WINDOW_HELP_BUTTON", UI_FLAG_BOTTOM, INVENTORY_WINDOW_HELP_BUTTON );
	pButtonInv->CreateFlip( "INVENTORY_WINDOW_HELP_BUTTON_OVER", CBasicButton::MOUSEIN_FLIP );
	pButtonInv->SetUseGlobalAction ( TRUE );	
	RegisterControl( pButtonInv );

	CUIControl* pControl = CreateControl ( "INVENTORY_MONEY_BACK" );
	pControl->SetAlignFlag ( UI_FLAG_DEFAULT );
	
	m_pPage = new CInventoryPage;
	m_pPage->CreateSub ( this, "INVENTORY_PAGE", UI_FLAG_YSIZE, INVENTORY_PAGE );
	m_pPage->CreateSubControl ();
	m_pPage->SetVisibleSingle(TRUE);
	RegisterControl ( m_pPage );

	m_pPage2 = new CItemBankPage;
	m_pPage2->CreateSub ( this, "ITEMBANK_PAGE", UI_FLAG_YSIZE, ITEMBANK_PAGE );
	m_pPage2->CreateSubControl ();
	m_pPage2->SetVisibleSingle(FALSE);
	RegisterControl ( m_pPage2 );

	CBasicButton* pButton = NULL;
	pButton = CreateFlipButton ( "INVENTORY_MONEY_BUTTON", "INVENTORY_MONEY_BUTTON_F", INVENTORY_MONEY_BUTTON, CBasicButton::CLICK_FLIP );
	pButton->CreateMouseOver ( "INVENTORY_MONEY_BUTTON_F" );
	pButton->SetAlignFlag ( UI_FLAG_DEFAULT );
	pButton->SetUseDynamic ( TRUE );

#if defined(VN_PARAM) //vietnamtest%%%
	pButton = CreateFlipButton ( "VNGAINSYS_INVEN_BUTTON", "VNGAINSYS_INVEN_BUTTON_F", INVENTORY_VNGAINSYS_BUTTON, CBasicButton::CLICK_FLIP );
	pButton->CreateMouseOver ( "VNGAINSYS_INVEN_BUTTON_F" );
	pButton->SetAlignFlag ( UI_FLAG_DEFAULT );
	pButton->SetUseDynamic ( TRUE );	
#endif

	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_FLAG );
	const int nAlignCenteredLeft = TEXT_ALIGN_LEFT;

	m_pMoneyTextBox = CreateStaticControl ( "INVENTORY_MONEY_TEXT", pFont8, NS_UITEXTCOLOR::DEFAULT, TEXT_ALIGN_LEFT );
	m_pMoneyTextBox->SetAlignFlag ( UI_FLAG_DEFAULT );

	char* szButton[4] =
	{
		"INVENTORY_BUTTON00",
		"INVENTORY_BUTTON01",
		"INVENTORY_BUTTON02",
		"INVENTORY_BUTTON03",
	};

	for ( int i = 0; i < 4; i++)
	{
		m_pButton[i] = CreateButtonBlue ( szButton[i], szButton[i], pFont9, nAlignCenteredLeft, INVENTORY_LOCKER_BUTTON + i, "" );
	}

	CreateControl( "IVENTORY_ICON00" );
	CreateControl( "IVENTORY_ICON01" );
	CreateControl( "IVENTORY_ICON02" );
	CreateControl( "IVENTORY_ICON03" );

	INVENTORY();
	fSortTimer = GLCONST_CHAR::fSORTTIME;

}
CBasicTextButton*  CInventoryWindow::CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText, _DEFAULT_FONT_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}
CBasicTextButton*  CInventoryWindow::CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButtonEx ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText, _DEFAULT_FONT_SHADOW_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}
CBasicTextButton*  CInventoryWindow::CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE24;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON24", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText );
	RegisterControl ( pTextButton );
	return pTextButton;
}
void CInventoryWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	GLCHARLOGIC& ref_CharData = GLGaeaClient::GetInstance().GetCharacterLogic ();
	SetMoney ( ref_CharData.m_lnMoney );

	GLInventory& ref_Inventory = ref_CharData.m_cInventory;	
	m_pPage->LoadItemPage ( ref_Inventory );
	fSortTimer += fElapsedTime;
}

void CInventoryWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{

			}
		}
		break;
	case INVENTORY_PAGE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nPosX, nPosY;
				m_pPage->GetItemIndex ( &nPosX, &nPosY );

				if ( nPosX < 0 || nPosY < 0 ) return;

				BOOL bMarketOpen = CInnerInterface::GetInstance().IsMarketWindowOpen ();
				{
					SINVENITEM sInvenItem = m_pPage->GetItem ( nPosX, nPosY );
					if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
					{						
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sInvenItem.sItemCustom, bMarketOpen, FALSE, FALSE, sInvenItem.wPosX, sInvenItem.wPosY );
					}

					/*item preview, Juver, 2017/07/27 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().PreviewItem( sInvenItem.sItemCustom );
							return;
						}
					}

					/*box contents, Juver, 2017/08/30 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_RB_UP )
						{
							CInnerInterface::GetInstance().ShowBoxContents( sInvenItem.sItemCustom.sNativeID );
							return;
						}
					}

					/*item link, Juver, 2017/07/31 */
					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_RB_UP )
						{
							CInnerInterface::GetInstance().LinkItem( &sInvenItem.sItemCustom );
							return;
						}
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					if ( m_bSplitItem )
					{
						m_bSplitItem = FALSE;

						WORD wSplitPosX, wSplitPosY;
						GetSplitPos ( &wSplitPosX, &wSplitPosY );
						BOOL bDiffPos = !( nPosX == wSplitPosX && nPosY == wSplitPosY );
						BOOL bSplitable = GLGaeaClient::GetInstance().GetCharacter()->IsInvenSplitItem ( wSplitPosX, wSplitPosY );
                        if ( bDiffPos && bSplitable )
						{
							DoModal ( ID2GAMEINTEXT ( "SPLIT_ITEM" ), MODAL_QUESTION, EDITBOX_NUMBER, MODAL_SPLIT_ITEM );
						}
						else
						{
							GLGaeaClient::GetInstance().GetCharacter()->ReqInvenTo ( nPosX, nPosY );
						}
					}
					return ;
				}

				if ( dwMsg & UIMSG_RB_UP )
				{
					/*rightclick wear/unwear, Juver, 2017/06/24 */
					HRESULT hrWear = GLGaeaClient::GetInstance().GetCharacter()->ReqInvenToWear( nPosX, nPosY );
					if ( hrWear != S_OK )
						GLGaeaClient::GetInstance().GetCharacter()->ReqInvenDrug ( nPosX, nPosY );

					return ;
				}

				if ( dwMsg & UIMSG_LB_DOWN )
				{
					SetSplitPos ( nPosX, nPosY );
					m_bSplitItem = TRUE;
					return ;
				}
			}
		}
		break;
		
	case ITEMBANK_PAGE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nPosX, nPosY;
				m_pPage2->GetItemIndex ( &nPosX, &nPosY );

				if ( nPosX < 0 || nPosY < 0 ) return ;

				SINVENITEM sInvenItem = m_pPage2->GetItem ( nPosX, nPosY );
				if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
				{
					CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sInvenItem.sItemCustom, FALSE, FALSE, FALSE, sInvenItem.wPosX, sInvenItem.wPosY );

					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().PreviewItem( sInvenItem.sItemCustom );
							return;
						}
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					GLGaeaClient::GetInstance().GetCharacter()->ReqChargedItemTo ( static_cast<WORD>(nPosX), static_cast<WORD>(nPosY) );
					return ;
				}
			}
		}
		break;

	case INVENTORY_MONEY_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				if ( CInnerInterface::GetInstance().IsStorageWindowOpen () )
				{
					DoModal ( ID2GAMEINTEXT("PLAYINTERFACE_31"), MODAL_INPUT, EDITBOX_MONEY, MODAL_SAVEMONEY );
				}
				else if ( CInnerInterface::GetInstance().IsClubStorageWindowOpen () )
				{
					DoModal ( ID2GAMEINTEXT("PLAYINTERFACE_31"), MODAL_INPUT, EDITBOX_MONEY, MODAL_CLUB_SAVEMONEY );
				}
				else
				{
					if ( GLCONST_CHAR::bMONEY_DROP2FIELD )
					{
						DoModal ( ID2GAMEINTEXT("MONEYTO_FIELD"), MODAL_INPUT, EDITBOX_MONEY, MODAL_INVENTORY_MONEY_TO_FIELD );
					}
				}
			}
		}
		break;
#if defined(VN_PARAM) //vietnamtest%%%
	case INVENTORY_VNGAINSYS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{

				if ( dwMsg & UIMSG_LB_UP )
				{
					if ( !CInnerInterface::GetInstance().IsVisibleGroup ( VNGAINSYS_WINDOW ) )
					{
						CInnerInterface::GetInstance().ShowGroupFocus ( VNGAINSYS_WINDOW );
					}
					else
					{
						CInnerInterface::GetInstance().HideGroup ( VNGAINSYS_WINDOW );
					}
				}
			}
		}
		break;
#endif
	case INVENTORY_WINDOW_HELP_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( GetSTATE() == 0 )
				{
					CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( "Display all items in your inventory" , NS_UITEXTCOLOR::AQUA );				
				}
				else if ( GetSTATE() == 1 ) 
				{
					CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( "Display all items in your bank.", NS_UITEXTCOLOR::AQUA );
				}
				else
				{
					CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( "Wish List is currently unavailable.", NS_UITEXTCOLOR::AQUA );
				}
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
			}
		}
		break;

	case INVENTORY_LOCKER_BUTTON:
	case INVENTORY_ZOOM_BUTTON:
	case INVENTORY_DELETE_BUTTON:
	case INVENTORY_RANK_BUTTON:
		{
			int nIndex = ControlID - INVENTORY_LOCKER_BUTTON;
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( ID2GAMEWORD("INVENTORY_BUTTON_TEXT",nIndex), NS_UITEXTCOLOR::WHITE );
			}

			if( CHECK_MOUSEIN_LBUPLIKE( dwMsg ))
			{
				DoFunction(nIndex);
			}
		}
		break;
	case ET_CONTROL_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().HideGroup ( MARKET_WINDOW );
				CInnerInterface::GetInstance().HideGroup ( STORAGE_WINDOW );
				CInnerInterface::GetInstance().HideGroup ( CLUB_STORAGE_WINDOW );
			}
		}
		break;
	}

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case INVENTORY_PAGE_BUTTON0:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				INVENTORY();
			}
		}
		break;
	case INVENTORY_PAGE_BUTTON1:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				INVENTORY_BANK();

				GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter ();
				if ( pCharacter )
				{
				pCharacter->ReqItemBankInfo ();
				}
			}
		}
		break;
	case INVENTORY_PAGE_BUTTON2:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().PrintConsoleText( "Not Available", NS_UITEXTCOLOR::AQUA );
				return;
			}
		}
		break;
	}
}
void CInventoryWindow::InitItemBank ()
{
	m_pPage2->UnLoadItemPage ();

	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
	m_pPage2->LoadItemPage ( pCharacter->m_cInvenCharged );
}

void CInventoryWindow::ClearItemBank()
{ 
	m_pPage2->UnLoadItemPage ();
}
void CInventoryWindow::INVENTORY()
{
	for ( int i = 0; i < 3 ; i++ )
	{
		m_pPageButton[i]->SetFlip ( FALSE );
	}

	m_pPageButton[0]->SetFlip ( TRUE );
	m_pPage->SetVisibleSingle(TRUE);
	m_pPage2->SetVisibleSingle(FALSE);
	nSTATE = 0;
}
void CInventoryWindow::INVENTORY_BANK()
{
	for ( int i = 0; i < 3 ; i++ )
	{
		m_pPageButton[i]->SetFlip ( FALSE );
	}

	m_pPageButton[1]->SetFlip ( TRUE );
	m_pPage2->SetVisibleSingle(TRUE);
	m_pPage->SetVisibleSingle(FALSE);
	nSTATE = 1;
}
void CInventoryWindow::INVENTORY_WANT()
{
	for ( int i = 0; i < 3 ; i++ )
	{
		m_pPageButton[i]->SetFlip ( FALSE );
	}
	m_pPageButton[2]->SetFlip ( TRUE );
	m_pPage2->SetVisibleSingle(FALSE);
	m_pPage->SetVisibleSingle(FALSE);
}
void CInventoryWindow::SetMoney ( LONGLONG Money )
{
	//	µ·ÀÚ¸®¼ö
	CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( Money, 3, "," );
	m_pMoneyTextBox->SetOneLineText ( strTemp );
}

void CInventoryWindow::GetSplitPos ( WORD* pwPosX, WORD* pwPosY )
{
	*pwPosX = m_wSplitItemPosX;
	*pwPosY = m_wSplitItemPosY;
}

void CInventoryWindow::SetSplitPos ( WORD wPosX, WORD wPosY )
{
	m_wSplitItemPosX = wPosX;
	m_wSplitItemPosY = wPosY;
}

void	CInventoryWindow::SetOneViewSlot ( const int& nONE_VIEW_SLOT )
{
	CUIControl TempControl;
	TempControl.Create ( 1, "INVENTORY_ITEM_SLOT0" );

	CUIControl TempControl2;
	TempControl2.Create ( 2, "INVENTORY_ITEM_SLOT1" );

	const UIRECT& rcTempGlobalPos = TempControl.GetGlobalPos ();
	D3DXVECTOR2 vONE_SLOT_SIZE ( rcTempGlobalPos.sizeX, rcTempGlobalPos.sizeY );

	const UIRECT& rcTempGlobalPos2 = TempControl2.GetGlobalPos ();

	const float fSlotGap = rcTempGlobalPos2.top - rcTempGlobalPos.bottom;

	const float fOldSizeY = (vONE_SLOT_SIZE.y+fSlotGap) * m_nONE_VIEW_SLOT;
	const float fNewSizeY = (vONE_SLOT_SIZE.y+fSlotGap) * nONE_VIEW_SLOT;
    const float fDIFF_SIZE_Y = fNewSizeY - fOldSizeY;

	const UIRECT& rcGlobalPos = GetGlobalPos ();
	UIRECT rcNewGlobalPos ( rcGlobalPos.left, rcGlobalPos.top,
		rcGlobalPos.sizeX, rcGlobalPos.sizeY + fDIFF_SIZE_Y );

	WORD wFlagAlignBACK = GetAlignFlag ();
	SetAlignFlag ( UI_FLAG_YSIZE );
	
	//AlignSubControl ( rcGlobalPos, rcNewGlobalPos );
	//SetGlobalPos ( rcNewGlobalPos );
	
	SetAlignFlag ( wFlagAlignBACK );

	m_pPage->SetOneViewSlot ( nONE_VIEW_SLOT );
	m_nONE_VIEW_SLOT = nONE_VIEW_SLOT;
}

CBasicButtonText* CInventoryWindow::CreateButtonBlue ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText )
{
	CBasicButtonText* pButton = new CBasicButtonText;
	pButton->CreateRanButtonBlue ( this, szButton, ControlID );
	pButton->CreateTextBox ( szTextBox, pFont, nAlign );
	pButton->SetOneLineText( strText.GetString() );
	RegisterControl ( pButton );

	return pButton;
}

void CInventoryWindow::DoFunction(int nIndex)
{
	if ( nIndex == 0 )
	{
		for ( WORD y = 0; y < EM_INVENSIZE_Y; y++ )
		{
			for ( WORD x = 0; x < EM_INVENSIZE_X; x++ )
			{
				SINVENITEM& ref_InvenItem = m_pPage->GetItem ( x, y );
				if ( ref_InvenItem.sItemCustom.sNativeID != NATIVEID_NULL() )
				{
					SITEM* pItem = GLItemMan::GetInstance().GetItem ( ref_InvenItem.sItemCustom.sNativeID );
					if ( pItem->sBasicOp.emItemType == ITEM_STORAGE_CONNECT )
					{
						GLGaeaClient::GetInstance().GetCharacter()->ReqInvenDrug ( x, y );
						return;
					}
				}
			}
		}
	}
	else if ( nIndex == 1 )
	{
		for ( WORD y = 0; y < EM_INVENSIZE_Y; y++ )
		{
			for ( WORD x = 0; x < EM_INVENSIZE_X; x++ )
			{
				SINVENITEM& ref_InvenItem = m_pPage->GetItem ( x, y );
				if ( ref_InvenItem.sItemCustom.sNativeID != NATIVEID_NULL() )
				{
					SITEM* pItem = GLItemMan::GetInstance().GetItem ( ref_InvenItem.sItemCustom.sNativeID );
					if ( pItem->sBasicOp.emItemType == ITEM_INVEN_CARD )
					{
						GLGaeaClient::GetInstance().GetCharacter()->ReqInvenDrug ( x, y );
						return;
					}
				}
			}
		}
	}
	else if ( nIndex == 2 ) CInnerInterface::GetInstance().PrintConsoleText( "Disable Function", NS_UITEXTCOLOR::AQUA );
	else if ( nIndex == 3 ) 
	{
		if ( fSortTimer < GLCONST_CHAR::fSORTTIME ) 
		{
			CInnerInterface::GetInstance().PrintConsoleText( "Please Wait.." );
			return;
		}

		fSortTimer = 0.0f;
		GLGaeaClient::GetInstance().GetCharacter()->ReqSortItem();
	}
}

//void CInventoryWindow::SetArmSwapTabButton( BOOL bArmSub )
//{
///*	if( m_pPageWearEx )
//	{
//		m_pPageWearEx->SetTabButton( bArmSub );
//	}*/
//}