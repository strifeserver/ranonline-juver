#pragma	once

#include "../Lib_Engine/GUInterface/UIGroup.h"

class CBasicTextBox;

const DWORD	MAX_QUEST_DISPLAY = 5;

class CQuestHelper : public CUIGroup
{
private:
	CBasicTextBox*	m_pQuestText;

public:
	DWORD			m_dwQuestID[MAX_QUEST_DISPLAY];


public:
	CQuestHelper();
	~CQuestHelper();

	void	CreateSubControl ();
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:	
	void	SetQuestID( DWORD dwQuestID );
	void	ReSetQuestID ( DWORD dwQuestID );

	bool	UpdateQuestInfo ( DWORD dwQuestID );

	bool	IsQuestPrint();
	bool	IsSameQuest( DWORD dwQuestID );
};