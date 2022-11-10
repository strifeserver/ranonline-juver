#include "StdAfx.h"
#include "CharacterWindow.h"
#include "GLGaeaClient.h"
#include "./BasicButton.h"
#include "./BasicTextBox.h"
#include "./BasicComboBoxRollOver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CCharacterWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	if( m_RollOverID == NO_ID )
	{
		const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();	
		BOOL bPointUsable = (sCharData.m_wStatsPoint)?TRUE:FALSE;

	//	���� ��Ʈ��
		SetPointControl ( bPointUsable );

	//	�̸�,Ŭ����	
		SetName ( sCharData );

	//	����ġ
		SetEXP ( sCharData );

	//	Stat	
		SetPow ( sCharData );
		SetDex ( sCharData );
		SetSpi ( sCharData );
		//SetInt ( sCharData );
		SetStr ( sCharData );
		SetSta ( sCharData );
		SetPoint ( sCharData );

	//	Status
		SetLevel ( sCharData );
		SetDamage ( sCharData );
		SetDefense ( sCharData );
		SetReqPa ( sCharData );
		SetReqSa ( sCharData );	
		SetReqMa ( sCharData );	
		SetHP ( sCharData );
		SetMP ( sCharData );
		SetSP ( sCharData );
		SetHitRate ( sCharData );
		SetAvoidRate ( sCharData );
		SetPremium ();

		/*combatpoint logic, Juver, 2017/05/29 */
		SetCP ( sCharData );

	//	���׷�
		SetFireResi ( sCharData );
		SetColdResi ( sCharData );
		SetElectricResi ( sCharData );
		SetPoisonResi ( sCharData );
		SetSpiritResi ( sCharData );

	//	��ȸ ����
		SetAcademy ( sCharData );
		SetActivityPoint ( sCharData );
		SetPKState ( sCharData );
		SetDepartment ( sCharData );
		SetBright ( sCharData );
		SetGrade ( sCharData );

		/*contribution point, Juver, 2017/08/23 */
		SetContributionPoint ( sCharData );	

		/*activity point, Juver, 2017/08/23 */
		SetActivitySystemPoint ( sCharData );

		/*pk info, Juver, 2017/11/17 */
		LoadPKInfo ( sCharData );

		{	//	�� �ڸ� ã�ư���
			const UIRECT& rcPowPos = m_pPowDiaableButton->GetGlobalPos ();
			m_pPowButton->SetGlobalPos ( D3DXVECTOR2 ( rcPowPos.left, rcPowPos.top ) );

			const UIRECT& rcDexPos = m_pDexDiaableButton->GetGlobalPos ();
			m_pDexButton->SetGlobalPos ( D3DXVECTOR2 ( rcDexPos.left, rcDexPos.top ) );

			const UIRECT& rcSpiPos = m_pSpiDiaableButton->GetGlobalPos ();
			m_pSpiButton->SetGlobalPos ( D3DXVECTOR2 ( rcSpiPos.left, rcSpiPos.top ) );

			//const UIRECT& rcIntPos = m_pIntDiaableButton->GetGlobalPos ();
			//m_pIntButton->SetGlobalPos ( D3DXVECTOR2 ( rcIntPos.left, rcIntPos.top ) );

			const UIRECT& rcStaPos = m_pStaDiaableButton->GetGlobalPos ();
			m_pStaButton->SetGlobalPos ( D3DXVECTOR2 ( rcStaPos.left, rcStaPos.top ) );

			const UIRECT& rcStrPos = m_pStrDiaableButton->GetGlobalPos ();
			m_pStrButton->SetGlobalPos ( D3DXVECTOR2 ( rcStrPos.left, rcStrPos.top ) );
		}

		{
			m_pPowText->SetUseTextColor ( 0, FALSE );
			m_pPowTextStatic->SetUseTextColor ( 0, FALSE );

			m_pDexText->SetUseTextColor ( 0, FALSE );
			m_pDexTextStatic->SetUseTextColor ( 0, FALSE );

			m_pSpiText->SetUseTextColor ( 0, FALSE );
			m_pSpiTextStatic->SetUseTextColor ( 0, FALSE );

			//m_pIntText->SetUseTextColor ( 0, FALSE );
			//m_pIntTextStatic->SetUseTextColor ( 0, FALSE );

			m_pStrText->SetUseTextColor ( 0, FALSE );
			m_pStrTextStatic->SetUseTextColor ( 0, FALSE );

			m_pStaText->SetUseTextColor ( 0, FALSE );
			m_pStaTextStatic->SetUseTextColor ( 0, FALSE );
		}

		CUIWindow::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	}
	else
	{
		/*activity system, Juver, 2017/11/05 */
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

void CCharacterWindow::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindow::SetVisibleSingle( bVisible );

	if( bVisible )
	{
		const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();
		SetPhoneNumber( sCharData.m_szPhoneNumber );

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
	}
}