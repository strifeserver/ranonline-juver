#pragma	once

#include "../Lib_Engine/GUInterface/UIGroup.h"

class	CD3DFontPar;
class	CBasicTextBox;
class CBasicLineBoxEx;
class	CBasicProgressBar;

class	CTargetInfoDisplay : public CUIGroup
{
//public:
//	enum
//	{
//		nSCHOOLMARK = 3,
//		nPARTYMARK = 5,
//		NODATA = UINT_MAX
//	};

public:
	CTargetInfoDisplay ();
	virtual	~CTargetInfoDisplay ();

public:
	void	CreateSubControl ();
	CUIControl*	CreateControl ( const char* szControl, WORD wAlignFlag );
	CUIControl*	CreateControlEx ( const char* szControl );

public:
	void	SetTargetInfo ( float fPercent, CString strName, D3DCOLOR dwColor ); /*, int nSchoolMark = NODATA, int nPartyMark = NODATA );*/
	const CString& GetTargetName () const			{ return m_strName; }

private:
	CBasicTextBox*		m_pNameBox;
	CBasicProgressBar*	m_pHP;
	CBasicLineBoxEx*	m_pNameLineBox;
	CUIControl*			m_pNameBoxDummy;

private:
	CString		m_strName;

private:
	CD3DFontPar*	m_pFont8;

//private:
//	CUIControl*		m_pSchoolMark[nSCHOOLMARK];
//	CUIControl*		m_pPartyMark[nPARTYMARK];
};