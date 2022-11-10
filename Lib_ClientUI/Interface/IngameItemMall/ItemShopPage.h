#pragma	once

#include "../Lib_Engine/GUInterface/UIGroup.h"
#include "GLDefine.h"
#include "GLCharDefine.h"
#include "./GLogicEx.h"

class	CItemSlot;
class	CBasicScrollBarEx;
class	GLInventory;
class	CBasicTextBox;
class	CBasicTextBoxEx;
struct	SINVENITEM;

class	CItemShopPage : public GLCHARLOGIC, public CUIGroup
{
static	const	int	nSTARTLINE;
static	const	int	nOUTOFRANGE;

protected:
	enum
	{
		ITEMSHOP_INVEN_X = 1,
		ITEMSHOP_INVEN_Y = 200,
		nMAX_ONE_VIEW_SLOT = 10
	};

	enum
	{
		ITEM_SLOT0 = NO_ID + 1,
		ITEM_SLOT1,
		ITEM_SLOT2,
		ITEM_SLOT3,
		ITEM_SLOT4,
		ITEM_SLOT5,
		ITEM_SLOT6,
		ITEM_SLOT7,
		ITEM_SLOT8,
		ITEM_SLOT9,
		ITEM_SLOT10,
		ITEM_SLOT11,
		ITEM_SLOT_END = ITEM_SLOT0 + ITEMSHOP_INVEN_Y
	};

public:
	CItemShopPage ();
	virtual	~CItemShopPage ();

public:
	void CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

public:
	void	SetItemIndex ( int nPosX, int nPosY );
	void	GetItemIndex ( int* pnPosX, int* pnPosY );

public:
	void	LoadItemPage ( WORD wType ,WORD wCur );
	void	LoadItem ( SINVENITEM& ref_InvenItem );
	SINVENITEM&	GetItem ( int nPosX, int nPosY );

public:
	void	UnLoadItemPage ();
	void	UnLoadItem ( int nPosX, int nPosY );

private:
	void	ResetAllItemSlotRender ( int nTotal );
	void	SetItemSlotRender ( int nStartIndex, int nTotal );
private:
	CItemSlot*	CreateItemSlot ( CString strKeyword, UIGUID ControlID );
	CUIControl*	CreateControl ( const char* szControl );
	CBasicTextBox*	  CreateStaticControl ( const char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID = NO_ID );
private:
	CItemSlot*	m_pItemSlotArray[ITEMSHOP_INVEN_Y];
	CUIControl*	m_pItemSlotArrayDummy[nMAX_ONE_VIEW_SLOT];

	CBasicScrollBarEx*	m_pScrollBar;

private:
	int		m_nPosX;
	int		m_nPosY;
	int		m_nCurPos;
};