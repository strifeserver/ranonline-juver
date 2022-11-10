/*!
 * \file StudentRecordButton.h
 *
 * \author Juver
 * \date October 2017
 *
 * 
 */

#pragma	once

#include "UIGroup.h"

class	CNPCShopButton : public CUIGroup
{
private:
	enum
	{
		NPCSHOP_BUTTON = NO_ID + 1,
	};

public:
	CNPCShopButton ();
	virtual	~CNPCShopButton ();

public:
	void	CreateSubControl ();

public:
	CUIControl*			m_pButtonImage;

public:
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
};