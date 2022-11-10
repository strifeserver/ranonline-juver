#pragma once

class	CsheetWithTab;
// CPageABF dialog

class CPageABF : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageABF)

public:
	CPageABF(LOGFONT logfont);
	virtual ~CPageABF();

// Dialog Data
	enum { IDD = IDD_PAGE_ABF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CsheetWithTab*	m_pSheetTab;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	CFont*			m_pFont;

public:
	void	SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void	SetSheetTab ( CsheetWithTab* pSheetTab ) { m_pSheetTab = pSheetTab; }

public:
	CListCtrl		m_List_Anim;
	CListCtrl		m_List_Piece;

public:
	void	DataReset();
	void	DataShow();
	void	DataShowAnim();
	void	DataShowPiece();
	void	PlayAnim();

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonAbfLoad();
	afx_msg void OnBnClickedButtonPieceReset();
	afx_msg void OnBnClickedButtonPieceCps();
	afx_msg void OnBnClickedButtonPieceEffskin();
	afx_msg void OnBnClickedButtonAnimPlay();
	afx_msg void OnNMDblclkListAnim(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonPieceEffskinAbf();
};
