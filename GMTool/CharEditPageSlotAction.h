#pragma once

class	CCharEditTab;
struct SCHARDATA2;

// CCharEditPageSlotAction dialog

class CCharEditPageSlotAction : public CPropertyPage
{
	DECLARE_DYNAMIC(CCharEditPageSlotAction)

public:
	CCharEditPageSlotAction(LOGFONT logfont, SCHARDATA2* pData);
	virtual ~CCharEditPageSlotAction();

// Dialog Data
	enum { IDD = IDD_CHAREDIT_PAGE_SLOT_ACTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CCharEditTab*	m_pSheetTab;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	CFont*			m_pFont;
	SCHARDATA2*		m_pData;

public:
	void	SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void	SetSheetTab ( CCharEditTab* pSheetTab ) { m_pSheetTab = pSheetTab; }

private:
	CListCtrl	m_List;

public:
	void DataShow();
	void DataEdit();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChareditActionslotButtonEdit();
	afx_msg void OnBnClickedChareditActionslotButtonDelete();
	afx_msg void OnBnClickedChareditActionslotButtonClear();
	afx_msg void OnNMDblclkChareditActionslotList(NMHDR *pNMHDR, LRESULT *pResult);
};
