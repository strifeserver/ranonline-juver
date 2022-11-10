/*!
 * \file EquipmentLockRecoverWindow.h
 *
 * \author Juver
 * \date January 2018
 *
 * 
 */

#pragma once

#include "UIWindowEx.h"

class CBasicTextBox;
class CUIEditBoxMan;
class CBasicTextButton;


class CEquipmentLockRecoverWindow : public CUIWindowEx
{
	enum
	{
		EQUIPMENT_LOCK_RECOVER_WINDOW_EDIT_MAN = ET_CONTROL_NEXT,
		EQUIPMENT_LOCK_RECOVER_WINDOW_EDIT_PIN1,
		EQUIPMENT_LOCK_RECOVER_WINDOW_EDIT_PIN2,
		EQUIPMENT_LOCK_RECOVER_WINDOW_EDIT_CONFIRM,

		EQUIPMENT_LOCK_ENABLE_WINDOW_BUTTON_CHANGE,
		EQUIPMENT_LOCK_ENABLE_WINDOW_BUTTON_DELETE,
		EQUIPMENT_LOCK_ENABLE_WINDOW_BUTTON_CLOSE,
		
	};

public:
	static int nLIMIT_PIN;
	static int nLIMIT_AGREE;

public:
	CEquipmentLockRecoverWindow(void);
	virtual ~CEquipmentLockRecoverWindow(void);

public:
	void CreateSubControl();

public:
	CBasicTextBox*		m_pInfoDesc;
	CBasicTextBox*		m_pInfoPin1;
	CBasicTextBox*		m_pInfoPin2;
	CBasicTextBox*		m_pInfoOrigPin1;
	CBasicTextBox*		m_pInfoOrigPin2;
	CBasicTextBox*		m_pInfoConfirm;

	CUIEditBoxMan*		m_pEditBoxMan;

	CBasicTextButton*	m_pButtonChange;
	CBasicTextButton*	m_pButtonDelete;
	CBasicTextButton*	m_pButtonClose;

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage( UIGUID cID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

	void	ActionChangeKey();
	void	ActionDeleteKey();
	void	ActionCloseWindow();

	void	setCurrentKey( std::string strKey );

};