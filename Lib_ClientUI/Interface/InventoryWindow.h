#pragma	once

#include "UIWindowEx.h"

class	CInventoryPage;
class	CItemBankPage;
class	CBasicTextButton;
class	CBasicButtonText;

class	CInventoryWindow : public CUIWindowEx
{
protected:
	enum
	{
		INVENTORY_MONEY_BUTTON = ET_CONTROL_NEXT,
		INVENTORY_PAGE,
		ITEMBANK_PAGE,
		INVENTORY_VNGAINSYS_BUTTON,
		INVENTORY_PAGE_BUTTON0,
		INVENTORY_PAGE_BUTTON1,
		INVENTORY_PAGE_BUTTON2,
		INVENTORY_LOCKER_BUTTON,
		INVENTORY_ZOOM_BUTTON,
		INVENTORY_DELETE_BUTTON,
		INVENTORY_RANK_BUTTON,
		INVENTORY_WINDOW_HELP_BUTTON,
		INVENTORY_WINDOW_HELP_BUTTON_OVER,
	};
public:
	CInventoryPage*		GetInventoryPage()	{ return m_pPage; }
private:
	CInventoryPage*		m_pPage;
	CItemBankPage*		m_pPage2;
	CUIControl*			m_bg_white;
	CBasicTextBox*		m_pMoneyTextBox;
	CBasicTextButton*	m_pPageButton[3];

	WORD	m_wSplitItemPosX;
	WORD	m_wSplitItemPosY;
	BOOL	m_bSplitItem;

	int		m_nONE_VIEW_SLOT;

public:
	CInventoryWindow ();
	virtual	~CInventoryWindow ();

public:
	void	CreateSubControl ();

	LONGLONG Money;

public:
	void	GetSplitPos ( WORD* pwPosX, WORD* pwPosY );
	void	SetSplitPos ( WORD wPosX, WORD wPosY );

	void	SetArmSwapTabButton( BOOL bArmSub );

	CBasicTextButton*	CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText );
	CBasicTextButton*	CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText );
	CBasicTextButton*	CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText );

	void	INVENTORY();
	void	INVENTORY_BANK();
	void	INVENTORY_WANT();

	void	InitItemBank ();
	void	ClearItemBank();
public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

private:
	void	SetMoney ( LONGLONG Money );

public:
	void	SetOneViewSlot ( const int& nONE_VIEW_SLOT );
	const int& GetOneViewSlot () const						{ return m_nONE_VIEW_SLOT; }

	CBasicButtonText*	CreateButtonBlue ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText );
	CBasicButtonText*	m_pButton[4];

public:
	float fSortTimer;
	int nSTATE;
	int GetSTATE() { return nSTATE; }

	void DoFunction(int nIndex);
};