#pragma once

#include "../Lib_Engine/GUInterface/UIGroup.h"

////////////////////////////////////////////////////////////////////
//	����� �޽��� ����
const DWORD UIMSG_MOUSEIN_LEFTBAR_DRAG	= UIMSG_USER1;
const DWORD UIMSG_MOUSEIN_NORMAL_CHAT	= UIMSG_USER2;
const DWORD UIMSG_MOUSEIN_PRIVATE_CHAT	= UIMSG_USER3;
const DWORD UIMSG_MOUSEIN_PARTY_CHAT	= UIMSG_USER4;
const DWORD UIMSG_MOUSEIN_TOALL_CHAT	= UIMSG_USER5;
const DWORD UIMSG_MOUSEIN_GUILD_CHAT	= UIMSG_USER6;
const DWORD UIMSG_MOUSEIN_ALLIANCE_CHAT	= UIMSG_USER7;
const DWORD UIMSG_MOUSEIN_REGIONAL_CHAT	= UIMSG_USER8;	/*regional chat, Juver, 2017/12/06 */
////////////////////////////////////////////////////////////////////

class CBasicChatLeftBar : public CUIGroup
{
public:
	enum
	{
		CHAT_LEFT_BAR_TOP = 1,
		CHAT_NORMAL_STATE,
		CHAT_PRIVATE_STATE,
		CHAT_PARTY_STATE,		
		CHAT_TOALL_STATE,
		CHAT_GUILD_STATE,
		CHAT_ALLIANCE_STATE,
		CHAT_REGIONAL_STATE,			/*regional chat, Juver, 2017/12/06 */

		TOTAL_CHAT_STATE = 7
	};

public:
	CBasicChatLeftBar ();
	virtual	~CBasicChatLeftBar ();

public:
	void	CreateSubControl ();

public:
	void	DO_CHAT_STATE ( int nSTATE );

public:
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

private:
	CUIControl*	m_pCHATSTATE[TOTAL_CHAT_STATE];
};