#include "stdafx.h"
#include "resource.h"
#include "CharEditTab.h"
#include "GLCharData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharEditTab

IMPLEMENT_DYNAMIC(CCharEditTab, CPropertySheet)

CCharEditTab::CCharEditTab( SCHARDATA2* pData, CRect& rect, LOGFONT logfont, CWnd* pParentWnd /*= NULL*/ )
	 : CPropertySheet("Sheet", pParentWnd),
	m_bNoTabs(FALSE),
	m_pWndParent(NULL),
	m_iDistanceFromTop(0),
	
	m_PageBasic ( logfont, pData ),
	m_PagePutOn ( logfont, pData ),
	m_PageInven ( logfont, pData ),
	m_PageSkills ( logfont, pData ),
	m_PageSlotAction ( logfont, pData ),
	m_PageSlotSkill ( logfont, pData ),
	m_PageQuest ( logfont, pData ),
	m_PageCoolTime ( logfont, pData ),
	m_PageLocker ( logfont, pData ),
	m_PageItemFood ( logfont, pData ),
	m_PageActivity ( logfont, pData ), /*activity system, Juver, 2017/10/23 */

	m_pFont( NULL ),
	m_pData( NULL )
{
	m_pData = pData;
	m_pWndParent = pParentWnd;
	m_Rect = rect;
	//m_bNoTabs = TRUE;
	m_bStacked = FALSE;

	m_PageBasic.SetSheetTab ( this );
	m_PagePutOn.SetSheetTab ( this );
	m_PageInven.SetSheetTab ( this );
	m_PageSkills.SetSheetTab ( this );
	m_PageSlotAction.SetSheetTab ( this );
	m_PageSlotSkill.SetSheetTab ( this );
	m_PageQuest.SetSheetTab ( this );
	m_PageCoolTime.SetSheetTab ( this );
	m_PageLocker.SetSheetTab ( this );
	m_PageItemFood.SetSheetTab ( this );
	m_PageActivity.SetSheetTab ( this ); /*activity system, Juver, 2017/10/23 */

	AddPage ( &m_PageBasic );
	AddPage ( &m_PagePutOn );
	AddPage ( &m_PageInven );
	AddPage ( &m_PageSkills );
	AddPage ( &m_PageSlotAction );
	AddPage ( &m_PageSlotSkill );
	AddPage ( &m_PageQuest );
	AddPage ( &m_PageCoolTime );
	AddPage ( &m_PageLocker );
	AddPage ( &m_PageItemFood );
	AddPage ( &m_PageActivity ); /*activity system, Juver, 2017/10/23 */


	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CCharEditTab::~CCharEditTab()
{
	SAFE_DELETE( m_pFont );
}

static int module_piButtons[] = { IDOK, IDCANCEL, ID_APPLY_NOW, IDHELP };

BOOL CCharEditTab::OnInitDialog() 
{
	HWND hTabWnd;
	CRect rectTabCtrl;

	ChangeDialogFont( this, m_pFont, CDF_NONE );

	if( m_Rect.right )
	{
		hTabWnd = (HWND)::GetDlgItem(m_hWnd, AFX_IDC_TAB_CONTROL);
		ASSERT(hTabWnd != NULL);
		::GetWindowRect(hTabWnd, &rectTabCtrl);  // Tab-control rectangle (screen coordinates)
		ScreenToClient(rectTabCtrl);

		if( !m_bNoTabs && rectTabCtrl.right > (m_Rect.Width() - 3) )
		{
			rectTabCtrl.right = m_Rect.Width() - 3; // Set new right position
		}

		rectTabCtrl.bottom = 32; // Height for tabs

		::MoveWindow( hTabWnd, 0, m_iDistanceFromTop, rectTabCtrl.Width(), rectTabCtrl.bottom, TRUE );
		BOOL bResult = (BOOL)Default();          // Process messages

		if( m_bNoTabs )
		{
			::ShowWindow(hTabWnd, SW_HIDE);
			::EnableWindow(hTabWnd, FALSE);
		}

		if (!m_bStacked)
		{
			hTabWnd = (HWND)SendMessage(PSM_GETTABCONTROL);
			if (hTabWnd != NULL)
			{
				CWnd::ModifyStyle(hTabWnd, TCS_MULTILINE, TCS_SINGLELINE, 0);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			HWND hWnd = ::GetDlgItem(m_hWnd, module_piButtons[i]);
			if (hWnd != NULL)
			{
				::ShowWindow(hWnd, SW_HIDE);
				::EnableWindow(hWnd, FALSE);
			}
		}

		MoveWindow( m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom /*- cyDiff*/ );
		return bResult;
	}
	return CPropertySheet::OnInitDialog();
}

BEGIN_MESSAGE_MAP(CCharEditTab, CPropertySheet)
	//{{AFX_MSG_MAP(CCharEditTab)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

HBRUSH CCharEditTab::CtlColor(CDC* pDc, UINT uCtlColor) 
{
	CWnd*    pwndParent;   // Parent window to property-sheet
	CDC*     pdcParent;    // Parent dc
	COLORREF color;        // color on parent dc           
	pwndParent = GetParent();
	ASSERT( pwndParent->IsKindOf( RUNTIME_CLASS( CWnd ) ) ); 
	pdcParent = pwndParent->GetDC();
	color = pdcParent->GetBkColor();    // Get parent color
	pwndParent->ReleaseDC( pdcParent );
	CBrush brush( color );              // Make a brush
	return (HBRUSH)brush;
}

BOOL CCharEditTab::PreTranslateMessage(MSG* pMsg)
{
	switch ( pMsg->message )
	{
	case WM_KEYDOWN:
		{
			if ( pMsg->wParam == VK_ESCAPE )
			{
			}
		}break;
	}
	return CPropertySheet::PreTranslateMessage(pMsg);
}

void CCharEditTab::ChangeDialogFont(CWnd* pWnd, CFont* pFont, int nFlag)
{
	CRect windowRect;
	TEXTMETRIC tmOld, tmNew;
	CDC * pDC = pWnd->GetDC();
	CFont * pSavedFont = pDC->SelectObject(pWnd->GetFont());
	pDC->GetTextMetrics(&tmOld);
	pDC->SelectObject(pFont);
	pDC->GetTextMetrics(&tmNew);
	pDC->SelectObject(pSavedFont);
	pWnd->ReleaseDC(pDC);

	CRect clientRect, newClientRect, newWindowRect;
	pWnd->GetWindowRect(windowRect);
	pWnd->GetClientRect(clientRect);
	double fHeigth = (double)(m_Rect.bottom-m_Rect.top) / clientRect.bottom;
	double fWidth = (double) (m_Rect.right-m_Rect.left) / clientRect.right;

	if (nFlag != CDF_NONE)
	{
		long xDiff = windowRect.Width() - clientRect.Width();
		long yDiff = windowRect.Height() - clientRect.Height();
	
		newClientRect.left = newClientRect.top = 0;
		newClientRect.right = LONG(clientRect.right * fWidth);
		newClientRect.bottom = LONG(clientRect.bottom * fHeigth);

		if (nFlag == CDF_TOPLEFT)
		{
			newWindowRect.left = windowRect.left;
			newWindowRect.top = windowRect.top;
			newWindowRect.right = windowRect.left + newClientRect.right + xDiff;
			newWindowRect.bottom = windowRect.top + newClientRect.bottom + yDiff;
		}else if (nFlag == CDF_CENTER){
			newWindowRect.left = windowRect.left - 
							(newClientRect.right - clientRect.right)/2;
			newWindowRect.top = windowRect.top -
							(newClientRect.bottom - clientRect.bottom)/2;
			newWindowRect.right = newWindowRect.left + newClientRect.right + xDiff;
			newWindowRect.bottom = newWindowRect.top + newClientRect.bottom + yDiff;
		}
		pWnd->MoveWindow(newWindowRect);
	}

	pWnd->SetFont(pFont);

	CWnd* pChildWnd = pWnd->GetWindow(GW_CHILD);
	while (pChildWnd)
	{
		pChildWnd->SetFont(pFont);
		pChildWnd->GetWindowRect(windowRect);

		CString strClass;
		::GetClassName(pChildWnd->m_hWnd, strClass.GetBufferSetLength(32), 31);
		strClass.MakeUpper();
		if(strClass==_T("COMBOBOX"))
		{
			CRect rect;
			pChildWnd->SendMessage(CB_GETDROPPEDCONTROLRECT,0,(LPARAM) &rect);
			windowRect.right = rect.right;
			windowRect.bottom = rect.bottom;
		}

		pWnd->ScreenToClient(windowRect);
		windowRect.left = LONG(windowRect.left * fWidth);
		windowRect.right = LONG(windowRect.right * fWidth);
		windowRect.top = LONG(windowRect.top * fHeigth);
		windowRect.bottom = LONG(windowRect.bottom *fHeigth);
		pChildWnd->MoveWindow(windowRect);
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
}

void CCharEditTab::InitPages()
{
	int nPAGE = GetPageCount();
	for( int i = 0; i < nPAGE; ++ i )
	{
		SetActivePage( i );
	}

	if ( nPAGE > 0 )
		SetActivePage( 0 );
}

BOOL CCharEditTab::SaveInfo()
{
	BOOL bSAVE = FALSE;

	bSAVE = m_PageBasic.DataSave();
	if ( !bSAVE ){
		return FALSE;
	}

	return TRUE;
}