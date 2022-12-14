#pragma	once

#include "../UIWindowEx.h"
#include "../BasicLineBoxEx.h"

class	CBasicTextBoxEx;
class	CBasicScrollBarEx;
class	PlayerRankingDisplaySlot;

class PlayerRankingDisplayPage : public CUIGroup
{
protected:
	static	const	int		nSTARTLINE;
	static	const	int		nOUTOFRANGE;

protected:
	enum
	{
		nMAX_ONE_VIEW_SLOT = 10,
		nMAX_RANK_SLOT = 100,
	};

	enum
	{
		CTF_RESULT_SLOT_0 = NO_ID + 1,
		CTF_RESULT_SLOT_1,CTF_RESULT_SLOT_2,CTF_RESULT_SLOT_3,
		CTF_RESULT_SLOT_4,CTF_RESULT_SLOT_5,CTF_RESULT_SLOT_6,
		CTF_RESULT_SLOT_7,CTF_RESULT_SLOT_8,CTF_RESULT_SLOT_9,
		CTF_SLOT_END = CTF_RESULT_SLOT_0 + nMAX_RANK_SLOT,
		CTF_RESULT_MYSLOT,
	};



private:
	CBasicTextBoxEx*			m_pCTFBaseRank;
	CBasicTextBoxEx*			m_pCTFBaseSchool;
	CBasicTextBoxEx*			m_pCTFBaseClass;
	CBasicTextBoxEx*			m_pCTFBaseCharName;
	CBasicTextBoxEx*			m_pCTFBaseKill;
	CBasicTextBoxEx*			m_pCTFBaseDeath;
	CBasicTextBoxEx*			m_pCTFBaseKdr;
	
	CBasicLineBoxEx*			m_pLineBoxMyRankHead;
	CBasicLineBoxEx*			m_pLineBoxMyRankTail;

	CBasicScrollBarEx*			m_pScrollBar;

	PlayerRankingDisplaySlot*			m_pRankSlot[nMAX_RANK_SLOT];

	CUIControl*					m_pRankSlotArrayDummy[nMAX_ONE_VIEW_SLOT];

protected:
	PlayerRankingDisplaySlot*	CreateRankSlot ( CString strKeyword, UIGUID ControlID, int index, D3DCOLOR dwColor );
	CUIControl*	CreateControl ( const char* szControl );

	void	ResetAllRankSlotRender ( int nTotal );
	void	SetRankSlotRender ( int nStartIndex, int nTotal );

public:
	PlayerRankingDisplayPage();
	~PlayerRankingDisplayPage();

	void	CreateSubControl ( int nRankCount, bool bMyRank );
	void	Init();
	void	RefreshRankSlot( bool bMyRank, int wSchool );
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

	void	SetRankCnt(int count)		{ m_nMaxRankCnt = count; }

private:
	int		m_nSlotIndex;
	int		m_nCurPos;
	int		m_nMaxRankCnt;
	std::vector<int> m_vecViewRank;
};