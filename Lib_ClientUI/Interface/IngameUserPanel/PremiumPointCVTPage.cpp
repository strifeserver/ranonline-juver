#include "StdAfx.h"
#include "../Lib_ClientUI/Interface/IngameUserPanel/PremiumPointCVTPage.h"
#include "BasicTextButton.h"
#include "GameTextControl.h"
#include "BasicTextBoxEx.h"
#include "UITextControl.h"
#include "BasicLineBox.h"
#include "OuterInterface.h"
#include "ModalWindow.h"
#include "s_NetClient.h"
#include "RANPARAM.h"
#include "../Lib_Client/G-Logic/GlogicData.h"
#include "DxGlobalStage.h"
#include "DxInputString.h"
#include "DebugSet.h"

#include "../Lib_Engine/Common/StringUtils.h"
#include "../Lib_Engine/DxCommon/DxFontMan.h"
#include "UIEditBoxMan.h"
#include "../Lib_Engine/GUInterface/UIKeyCheck.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int	CPremiumPointCVTPage::nLIMIT_CP = 7;

CPremiumPointCVTPage::CPremiumPointCVTPage ()
	: m_pRandTextBox(NULL)
	, m_nRandPassNumber(0)
	, m_nRPUpdateCnt(0)
{
	memset( m_szRandomString, 0, sizeof( m_szRandomString ) );
}

CPremiumPointCVTPage::~CPremiumPointCVTPage ()
{
}

void CPremiumPointCVTPage::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_FLAG );

	const int nBUTTONSIZE = CBasicTextButton::SIZE18;

	const DWORD dwPremiumPoint = COuterInterface::GetInstance().GetUserPoint();
	CBasicTextBox* pTextBox = NULL;
	CString strText,strText2;
	pTextBox = CreateStaticControl ( "PPCVT_PAGE_STATIC", pFont9, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_LEFT );
	pTextBox->SetOneLineText ( (char*)ID2GAMEWORD ( "PPCVT_PAGE_INFO", 0 ) );
	pTextBox = CreateStaticControl ( "PPCVT_PAGE_STATIC1", pFont9, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_LEFT );
	if ( dwPremiumPoint == 0 )
	{
		strText.Format("You don't have Premium Points yet");
	}
	else
	{
		strText.Format((char*)ID2GAMEWORD ( "PPCVT_PAGE_INFO", 1 ) ,dwPremiumPoint);
	}
	pTextBox->SetOneLineText ( strText );
	m_pStaticText2Box = pTextBox;
	pTextBox = CreateStaticControl ( "PPCVT_PAGE_STATIC2", pFont9, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_LEFT );
	strText.Format((char*)ID2GAMEWORD ( "PPCVT_PAGE_INFO", 2 ));
	pTextBox->SetOneLineText ( strText );
	m_pStaticText3Box = pTextBox;
	pTextBox = CreateStaticControl ( "PPCVT_PAGE_STATIC3", pFont9, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_LEFT );
	strText.Format( "Convert PP:");
	pTextBox->SetOneLineText ( strText );
	m_pStaticText4Box = pTextBox;
	m_pRandTextBox = CreateStaticControl ( "PPCVT_PAGE_CP", pFont9, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_LEFT );

	
	{
		CBasicLineBox* pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxOuter ( "PPCVT_PAGE_CP_BACK" );
		RegisterControl ( pBasicLineBox );

	}

	{
		CBasicLineBox* pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxOuter ( "PPCVT_PAGE_PP_BACK" );
		RegisterControl ( pBasicLineBox );

	}

	{
		CUIEditBoxMan* pEditBoxMan = new CUIEditBoxMan;
		pEditBoxMan->CreateSub ( this, "PPCVT_EDITMAN", UI_FLAG_DEFAULT, PPCVT_EDIT_MAN );
		pEditBoxMan->CreateEditBox ( PPCVT_PP_EDIT_CP, "PPCVT_PP_EDIT_RP", "PPCVT_CARRAT", TRUE, UINT_MAX, pFont9, nLIMIT_CP );
		pEditBoxMan->CreateEditBox ( PPCVT_EDIT_CP, "PPCVT_EDIT_RP", "PPCVT_CARRAT", TRUE, UINT_MAX, pFont9, nLIMIT_CP );
		RegisterControl( pEditBoxMan );
		m_pEditBoxMan = pEditBoxMan;
	}

	CBasicTextButton* pOKButton = new CBasicTextButton;
	pOKButton->CreateSub ( this, "BASIC_TEXT_BUTTON18", UI_FLAG_XSIZE, PPCVT_OK );
	pOKButton->CreateBaseButton ( "PPCVT_PAGE_OK", nBUTTONSIZE, CBasicButton::CLICK_FLIP, (char*)ID2GAMEWORD ( "PPCVT_PAGE_OKCANCEL", 0 ) );
	pOKButton->SetShortcutKey ( DIK_RETURN, DIK_NUMPADENTER );
	RegisterControl ( pOKButton );

	CBasicTextButton* pQuitButton = new CBasicTextButton;
	pQuitButton->CreateSub ( this, "BASIC_TEXT_BUTTON18", UI_FLAG_XSIZE, PPCVT_CANCEL );
	pQuitButton->CreateBaseButton ( "PPCVT_PAGE_CANCEL", nBUTTONSIZE, CBasicButton::CLICK_FLIP, (char*)ID2GAMEWORD ( "GTCVT_PAGE_OKCANCEL", 1 ) );
	pQuitButton->SetShortcutKey ( DIK_ESCAPE );
	RegisterControl ( pQuitButton );

}	

void CPremiumPointCVTPage::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	CUIWindow::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
	if ( !pNetClient->IsOnline() )		//��Ʈ��ũ ������ ������ ���
	{
		if ( !COuterInterface::GetInstance().IsVisibleGroup ( MODAL_WINDOW_OUTER ) )
		{
			if( !COuterInterface::GetInstance().IsLoginCancel() )
			{
				DoModalOuter ( ID2GAMEEXTEXT ("TOPUPSTAGE_1"), MODAL_INFOMATION, OK, OUTER_MODAL_RECONNECT );
			}
		}
	}
	else
	{
		const DWORD dwPremiumPoint = COuterInterface::GetInstance().GetUserPoint();
		CString strText,strText2;
		if ( dwPremiumPoint == 0 )
		{
			strText.Format("You don't have Premium Points yet");
		}
		else{
		strText.Format((char*)ID2GAMEWORD ( "PPCVT_PAGE_INFO", 1 ) ,dwPremiumPoint);
		}
		m_pStaticText2Box->SetOneLineText ( strText );
		strText.Format((char*)ID2GAMEWORD ( "PPCVT_PAGE_INFO", 2 ));
		m_pStaticText3Box->SetOneLineText ( strText );
		strText.Format( "Convert PP:" );
		m_pStaticText4Box->SetOneLineText ( strText );
		if (m_nRandPassNumber == -1 )
		{
			CString strTemp;
			StringCchCopy( m_szRandomString, 7, pNetClient->GetRandomString()  );
			strTemp.Format( "Captcha %s", m_szRandomString  );
			m_nRandPassNumber = 1;
			if( m_pRandTextBox ) m_pRandTextBox->SetOneLineText( strTemp );	
		}
		else
		{
			if( m_nRPUpdateCnt++ > 5 && m_nRandPassNumber == 0 )
			{
				pNetClient->SndRequestRandomKey();
				m_nRandPassNumber = -1;
				m_nRPUpdateCnt = 0;
			}
		}
	}

	if ( m_pEditBoxMan )
	{
		CUIControl* pParent = m_pEditBoxMan->GetTopParent ();
		if ( !pParent )	pParent = this;	//	���� ��Ŭ������ �ֻ��� ��Ʈ���� ���
		BOOL bFocus = ( pParent->IsFocusControl() );

		if ( bFocus )
		{
			if ( UIKeyCheck::GetInstance()->Check ( DIK_TAB, DXKEY_DOWN ) )
			{
				m_pEditBoxMan->GoNextTab ();
			}
		}
	}
}

void CPremiumPointCVTPage::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindow::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case PPCVT_OK:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				SetMessageEx( dwMsg &= ~UIMSG_KEY_FOCUSED ); // Focus ������ �޼��� ����
				CString strRP, strValue;
				strValue = m_pEditBoxMan->GetEditString ( PPCVT_PP_EDIT_CP );
				strRP = m_pEditBoxMan->GetEditString ( PPCVT_EDIT_CP );


				if( !strRP.GetLength () )
				{
					DoModalOuter ( ID2GAMEEXTEXT ( "GTCVTSTAGE_6" ) );
					return ;
				}

				if ( !CheckString ( strRP ) )
				{
					DoModalOuter ( ID2GAMEEXTEXT ( "GTCVT_PAGE_CP_ERROR" ) );
					return ;
				}
				
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
				
				CString strCheck;
				strCheck.Format("%s",m_szRandomString);
				if ( strCheck == strRP )
				{
					 pNetClient->SndPremiumPointCVT( strValue, strRP );									
					 DoModalOuter ( ID2GAMEEXTEXT ("GTCVTSTAGE_7") );
				}
				else
				{
					DoModalOuter ( ID2GAMEEXTEXT ("GTCVT_PAGE_CP_ERROR"), MODAL_INFOMATION, OK, OUTER_MODAL_TOPUPTOLOGIN );
				}
			}
		}
		break;

	case PPCVT_CANCEL:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
				if( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect();
					COuterInterface::GetInstance().SetCancelToLogin();
				}

				COuterInterface::GetInstance().ToSelectServerPage ( GetWndID () );
			}
		}
		break;
	};
}

BOOL CPremiumPointCVTPage::CheckString( CString strTemp )
{	
	strTemp = strTemp.Trim();

	// ���ڿ� üũ - ���� �ȵǴ� Ư������ : ~!@#$%^&*+|":?><\=`',.;[]{}()
	if( STRUTIL::CheckString( strTemp ) )
	{
		DoModalOuter ( ID2GAMEEXTEXT ( "TOPUPSTAGE_4" ), MODAL_INFOMATION, OK );		
		return FALSE;
	}

    return TRUE;
}

void CPremiumPointCVTPage::ResetAll ()
{
	m_pEditBoxMan->EndEdit ();

	m_pEditBoxMan->ClearEdit ( PPCVT_PP_EDIT_CP );
	m_pEditBoxMan->ClearEdit ( PPCVT_EDIT_CP );

	m_nRandPassNumber = 0;
	m_szRandomString[7] = 0;
	m_nRPUpdateCnt = 0;

	m_pEditBoxMan->Init();
	m_pEditBoxMan->BeginEdit();

	if( m_pEditBoxMan->IsMODE_NATIVE() )
	{
		m_pEditBoxMan->DoMODE_TOGGLE();
	}
}

void CPremiumPointCVTPage::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );

	if ( bVisible )
	{

		ResetAll();

		if( m_pRandTextBox ) m_pRandTextBox->ClearText();
	}
	else
	{
		m_pEditBoxMan->EndEdit ();

		CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
		pNetClient->ResetRandomPassNumber();
	}
}

CBasicButton* CPremiumPointCVTPage::CreateFlipButton ( char* szButton, char* szButtonFlip, UIGUID ControlID )
{
	CBasicButton* pButton = new CBasicButton;
	pButton->CreateSub ( this, szButton, UI_FLAG_DEFAULT, ControlID );
	pButton->CreateFlip ( szButtonFlip, CBasicButton::RADIO_FLIP );
	pButton->SetControlNameEx ( szButton );
	RegisterControl ( pButton );

	return pButton;
}

void CPremiumPointCVTPage::SetCharToEditBox( TCHAR cKey )
{
	if( !m_pEditBoxMan ) return;
	
	CString strTemp;
	UIGUID nID = m_pEditBoxMan->GetBeginEditBox();

	strTemp = m_pEditBoxMan->GetEditString( nID );
	strTemp += cKey;

	m_pEditBoxMan->SetEditString( nID, strTemp );
}

void CPremiumPointCVTPage::DelCharToEditBox()
{
	if( !m_pEditBoxMan ) return;

	CString strTemp;

	UIGUID nID = m_pEditBoxMan->GetBeginEditBox();

	strTemp = m_pEditBoxMan->GetEditString( nID );

	INT nLenth = strTemp.GetLength();
	strTemp = strTemp.Left( nLenth - 1 );

	m_pEditBoxMan->SetEditString( nID, strTemp );
}

void CPremiumPointCVTPage::GoNextTab()
{
	if( m_pEditBoxMan )
		m_pEditBoxMan->GoNextTab();
}