#include "StdAfx.h"

#include "SkillTimeUnit.h"
#include "./BasicProgressBar.h"
#include "SkillImage.h"
#include "InnerInterface.h"
#include "UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSkillTimeUnit::CSkillTimeUnit ()
{
}

CSkillTimeUnit::~CSkillTimeUnit ()
{
}

void CSkillTimeUnit::CreateSubControl ()
{
	CSkillImage* pSkillImage = new CSkillImage;
	pSkillImage->CreateSub ( this, "SKILLTIME_IMAGE", UI_FLAG_DEFAULT, TIMEUNIT_IMAGE );	
	pSkillImage->SetUseRender ( TRUE );
	RegisterControl ( pSkillImage );
	m_pSkillImage = pSkillImage;

	CUIControl* pProgressBack = new CUIControl;
	pProgressBack->CreateSub ( this, "SKILLTIME_BACK" );
	RegisterControl ( pProgressBack );

	CBasicProgressBar* pProgressBar = new CBasicProgressBar;
	pProgressBar->CreateSub ( this, "SKILLTIME_PROGRESS", UI_FLAG_DEFAULT, TIMEUNIT_PROGRESS );
	pProgressBar->CreateOverImage ( "SKILLTIME_PROGRESS_OVERIMAGE" );
	pProgressBar->SetType ( CBasicProgressBar::VERTICAL );
	RegisterControl ( pProgressBar );
	m_pProgressBar = pProgressBar;
}

void CSkillTimeUnit::SetLeftTime ( const float& fLeftTime )
{
	m_fLEFT_TIME = fLeftTime;
}

void CSkillTimeUnit::SetSkill ( const DWORD& dwID, const float& fLifeTime, const CString& strSkillName )
{
	m_fLIFE_TIME = fLifeTime;
	m_pSkillImage->SetSkill ( dwID );
	m_pSkillImage->SetVisibleSingle ( TRUE );

	m_strSkillName = strSkillName;
}

void CSkillTimeUnit::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	if ( m_pProgressBar )
	{
		const float fPercent = m_fLEFT_TIME/m_fLIFE_TIME;
		m_pProgressBar->SetPercent ( fPercent );
	}

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CSkillTimeUnit::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case TIMEUNIT_IMAGE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) ){
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( m_strSkillName, NS_UITEXTCOLOR::GREENYELLOW );
			}
		}break;

	case TIMEUNIT_PROGRESS:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) ){
				if ( m_fLEFT_TIME >= 0.0f )
				{
					CTimeSpan timeSpan(0,0,0,(int)m_fLEFT_TIME);

					std::string strRemainTime("");
					if ( timeSpan.GetTotalSeconds() > 0 ){
						if ( timeSpan.GetDays() > 0 && timeSpan.GetTotalHours() > 0 ){
							strRemainTime = timeSpan.Format( _T("%D Days, %H Hours, %M Minutes, %S Seconds") );
						}else if ( timeSpan.GetTotalHours() > 0 && timeSpan.GetTotalMinutes() > 0 ){
							strRemainTime = timeSpan.Format( _T("%H Hours, %M Minutes, %S Seconds") );
						}else if ( timeSpan.GetTotalMinutes() > 0 && timeSpan.GetTotalSeconds() > 0 ){
							strRemainTime = timeSpan.Format( _T("%M Minutes, %S Seconds") );
						}else{
							strRemainTime = timeSpan.Format( _T("%S Seconds") );
						}
					}

					if ( strRemainTime.size() )
						CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strRemainTime.c_str(), NS_UITEXTCOLOR::GREENYELLOW );	
				}
			}
		}break;
	}

	CUIGroup::TranslateUIMessage( ControlID, dwMsg );
}