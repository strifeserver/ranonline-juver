#pragma once

#include "../Lib_Engine/GUInterface/UIGroup.h"
#include "../Lib_ClientUI/Interface/BasicButton.h"

class	CEscMenuOpen : public CUIGroup
{
protected:
	enum
	{
		ESCMENU_OPEN_BUTTON = NO_ID + 1,
	};

public:
	CEscMenuOpen ();
	virtual	~CEscMenuOpen ();

public:
	void	CreateSubControl ();

public:
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
};