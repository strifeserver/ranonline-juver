#include "StdAfx.h"
#include "BasicLineBoxEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBasicLineBoxEx::CBasicLineBoxEx ()
{
}

CBasicLineBoxEx::~CBasicLineBoxEx ()
{
}

void CBasicLineBoxEx::CreateBaseBoxStorageCard ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_STORAGE_CARD" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_STORAGE_CARD", "BASIC_LINE_BOX_EX_RIGHT_STORAGE_CARD", "BASIC_LINE_BOX_EX_TOP_STORAGE_CARD", "BASIC_LINE_BOX_EX_BOTTOM_STORAGE_CARD" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_STORAGE_CARD", "BASIC_LINE_BOX_EX_LEFTBOTTOM_STORAGE_CARD", "BASIC_LINE_BOX_EX_RIGHTTOP_STORAGE_CARD", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_STORAGE_CARD" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxESCMenu ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_ESC" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_ESC", "BASIC_LINE_BOX_EX_RIGHT_ESC", "BASIC_LINE_BOX_EX_TOP_ESC", "BASIC_LINE_BOX_EX_BOTTOM_ESC" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_ESC", "BASIC_LINE_BOX_EX_LEFTBOTTOM_ESC", "BASIC_LINE_BOX_EX_RIGHTTOP_ESC", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_ESC" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxVarTextBox ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_VARTEXT" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_VARTEXT", "BASIC_LINE_BOX_EX_RIGHT_VARTEXT", "BASIC_LINE_BOX_EX_TOP_VARTEXT", "BASIC_LINE_BOX_EX_BOTTOM_VARTEXT" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_VARTEXT", "BASIC_LINE_BOX_EX_LEFTBOTTOM_VARTEXT", "BASIC_LINE_BOX_EX_RIGHTTOP_VARTEXT", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_VARTEXT" );
	ResizeControl ( szBoxControl );	
}
void CBasicLineBoxEx::CreateBaseBoxVarTextBoxGrayish ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_VARTEXT_LINK" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_VARTEXT_LINK", "BASIC_LINE_BOX_EX_RIGHT_VARTEXT_LINK", "BASIC_LINE_BOX_EX_TOP_VARTEXT_LINK", "BASIC_LINE_BOX_EX_BOTTOM_VARTEXT_LINK" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_VARTEXT_LINK", "BASIC_LINE_BOX_EX_LEFTBOTTOM_VARTEXT_LINK", "BASIC_LINE_BOX_EX_RIGHTTOP_VARTEXT_LINK", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_VARTEXT_LINK" );
	ResizeControl ( szBoxControl );	
}
void CBasicLineBoxEx::CreateBaseBoxLoiBox ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_VARTEXT_IS" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_VARTEXT_IS", "BASIC_LINE_BOX_EX_RIGHT_VARTEXT_IS", "BASIC_LINE_BOX_EX_TOP_VARTEXT_IS", "BASIC_LINE_BOX_EX_BOTTOM_VARTEXT_IS" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_VARTEXT_IS", "BASIC_LINE_BOX_EX_LEFTBOTTOM_VARTEXT_IS", "BASIC_LINE_BOX_EX_RIGHTTOP_VARTEXT_IS", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_VARTEXT_IS" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxBangBox ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_BANG" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_BANG", "BASIC_LINE_BOX_EX_RIGHT_BANG", "BASIC_LINE_BOX_EX_TOP_BANG", "BASIC_LINE_BOX_EX_BOTTOM_BANG" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_BANG", "BASIC_LINE_BOX_EX_LEFTBOTTOM_BANG", "BASIC_LINE_BOX_EX_RIGHTTOP_BANG", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_BANG" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxLomBox ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_LOM" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_LOM", "BASIC_LINE_BOX_EX_RIGHT_LOM", "BASIC_LINE_BOX_EX_TOP_LOM", "BASIC_LINE_BOX_EX_BOTTOM_LOM" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_LOM", "BASIC_LINE_BOX_EX_LEFTBOTTOM_LOM", "BASIC_LINE_BOX_EX_RIGHTTOP_LOM", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_LOM" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxBlueBox ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_BLUE" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_BLUE", "BASIC_LINE_BOX_EX_RIGHT_BLUE", "BASIC_LINE_BOX_EX_TOP_BLUE", "BASIC_LINE_BOX_EX_BOTTOM_BLUE" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_BLUE", "BASIC_LINE_BOX_EX_LEFTBOTTOM_BLUE", "BASIC_LINE_BOX_EX_RIGHTTOP_BLUE", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_BLUE" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxDenXamBox ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_DENXAM" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_DENXAM", "BASIC_LINE_BOX_EX_RIGHT_DENXAM", "BASIC_LINE_BOX_EX_TOP_DENXAM", "BASIC_LINE_BOX_EX_BOTTOM_DENXAM" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_DENXAM", "BASIC_LINE_BOX_EX_LEFTBOTTOM_DENXAM", "BASIC_LINE_BOX_EX_RIGHTTOP_DENXAM", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DENXAM" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxMapBox ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_MAP" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_MAP", "BASIC_LINE_BOX_EX_RIGHT_MAP", "BASIC_LINE_BOX_EX_TOP_MAP", "BASIC_LINE_BOX_EX_BOTTOM_MAP" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_MAP", "BASIC_LINE_BOX_EX_LEFTBOTTOM_MAP", "BASIC_LINE_BOX_EX_RIGHTTOP_MAP", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_MAP" );
	ResizeControl ( szBoxControl );	
}
void CBasicLineBoxEx::CreateBaseBoxNewBox ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_NEW" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_NEW", "BASIC_LINE_BOX_EX_RIGHT_NEW", "BASIC_LINE_BOX_EX_TOP_NEW", "BASIC_LINE_BOX_EX_BOTTOM_NEW" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_NEW", "BASIC_LINE_BOX_EX_LEFTBOTTOM_NEW", "BASIC_LINE_BOX_EX_RIGHTTOP_NEW", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_NEW" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxVarTextBoxNew ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_VARTEXT_NEW" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_VARTEXT_NEW", "BASIC_LINE_BOX_EX_RIGHT_VARTEXT_NEW", "BASIC_LINE_BOX_EX_TOP_VARTEXT_NEW", "BASIC_LINE_BOX_EX_BOTTOM_VARTEXT_NEW" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_VARTEXT_NEW", "BASIC_LINE_BOX_EX_LEFTBOTTOM_VARTEXT_NEW", "BASIC_LINE_BOX_EX_RIGHTTOP_VARTEXT_NEW", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_VARTEXT_NEW" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxTargetInfo ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_TARGETINFO" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_TARGETINFO", "BASIC_LINE_BOX_EX_RIGHT_TARGETINFO", "BASIC_LINE_BOX_EX_TOP_TARGETINFO", "BASIC_LINE_BOX_EX_BOTTOM_TARGETINFO" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_TARGETINFO", "BASIC_LINE_BOX_EX_LEFTBOTTOM_TARGETINFO", "BASIC_LINE_BOX_EX_RIGHTTOP_TARGETINFO", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_TARGETINFO" );
	ResizeControl ( szBoxControl );	
}

void	CBasicLineBoxEx::CreateBaseBoxSimpleHP ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_SIMPLEHP" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_SIMPLEHP", "BASIC_LINE_BOX_EX_RIGHT_SIMPLEHP", "BASIC_LINE_BOX_EX_TOP_SIMPLEHP", "BASIC_LINE_BOX_EX_BOTTOM_SIMPLEHP" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_SIMPLEHP", "BASIC_LINE_BOX_EX_LEFTBOTTOM_SIMPLEHP", "BASIC_LINE_BOX_EX_RIGHTTOP_SIMPLEHP", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_SIMPLEHP" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxName ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_NAME" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_NAME", "BASIC_LINE_BOX_EX_RIGHT_NAME", "BASIC_LINE_BOX_EX_TOP_NAME", "BASIC_LINE_BOX_EX_BOTTOM_NAME" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_NAME", "BASIC_LINE_BOX_EX_LEFTBOTTOM_NAME", "BASIC_LINE_BOX_EX_RIGHTTOP_NAME", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_NAME" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxNameCD ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_NAME_CD" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_NAME", "BASIC_LINE_BOX_EX_RIGHT_NAME", "BASIC_LINE_BOX_EX_TOP_NAME", "BASIC_LINE_BOX_EX_BOTTOM_NAME" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_NAME", "BASIC_LINE_BOX_EX_LEFTBOTTOM_NAME", "BASIC_LINE_BOX_EX_RIGHTTOP_NAME", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_NAME" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxChat ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_CHAT" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_CHAT", "BASIC_LINE_BOX_EX_RIGHT_CHAT", "BASIC_LINE_BOX_EX_TOP_CHAT", "BASIC_LINE_BOX_EX_BOTTOM_CHAT" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_CHAT", "BASIC_LINE_BOX_EX_LEFTBOTTOM_CHAT", "BASIC_LINE_BOX_EX_RIGHTTOP_CHAT", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_CHAT" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateLineImageEx ( char* szLeftTop, char* szLeftBottom, char* szRightTop, char* szRIghtBottom )
{
	m_pLeftTop = CreateControl ( szLeftTop, UI_FLAG_DEFAULT );
	m_pLeftBottom = CreateControl ( szLeftBottom, UI_FLAG_BOTTOM );
	m_pRIghtTop = CreateControl ( szRightTop, UI_FLAG_RIGHT );
	m_pRightBottom = CreateControl ( szRIghtBottom, UI_FLAG_BOTTOM | UI_FLAG_RIGHT );
}

void CBasicLineBoxEx::CreateBaseBoxSkillGreen ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_SKILL_GREEN" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_SKILL_GREEN", "BASIC_LINE_BOX_EX_RIGHT_SKILL_GREEN", "BASIC_LINE_BOX_EX_TOP_SKILL_GREEN", "BASIC_LINE_BOX_EX_BOTTOM_SKILL_GREEN" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_SKILL_GREEN", "BASIC_LINE_BOX_EX_LEFTBOTTOM_SKILL_GREEN", "BASIC_LINE_BOX_EX_RIGHTTOP_SKILL_GREEN", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_SKILL_GREEN" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxSkillBlue ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_SKILL_BLUE" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_SKILL_BLUE", "BASIC_LINE_BOX_EX_RIGHT_SKILL_BLUE", "BASIC_LINE_BOX_EX_TOP_SKILL_BLUE", "BASIC_LINE_BOX_EX_BOTTOM_SKILL_BLUE" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_SKILL_BLUE", "BASIC_LINE_BOX_EX_LEFTBOTTOM_SKILL_BLUE", "BASIC_LINE_BOX_EX_RIGHTTOP_SKILL_BLUE", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_SKILL_BLUE" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxSkillYellow ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_SKILL_YELLOW" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_SKILL_YELLOW", "BASIC_LINE_BOX_EX_RIGHT_SKILL_YELLOW", "BASIC_LINE_BOX_EX_TOP_SKILL_YELLOW", "BASIC_LINE_BOX_EX_BOTTOM_SKILL_YELLOW" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_SKILL_YELLOW", "BASIC_LINE_BOX_EX_LEFTBOTTOM_SKILL_YELLOW", "BASIC_LINE_BOX_EX_RIGHTTOP_SKILL_YELLOW", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_SKILL_YELLOW" );
	ResizeControl ( szBoxControl );	
}

//void CBasicLineBoxEx::CreateBaseBoxDialogueWhite ( char* szBoxControl )
//{
//	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_DIALOGUE_WHITE" );
//	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_RIGHT_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_TOP_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_BOTTOM_DIALOGUE_WHITE" );
//	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_LEFTBOTTOM_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_RIGHTTOP_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DIALOGUE_WHITE" );
//	ResizeControl ( szBoxControl );	
//}
//
//void CBasicLineBoxEx::CreateBaseBoxDialogueWhiteBack ( char* szBoxControl )
//{
//	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_DIALOGUE_WHITE_BACK" );
//	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_RIGHT_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_TOP_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_BOTTOM_DIALOGUE_WHITE_BACK" );
//	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_LEFTBOTTOM_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_RIGHTTOP_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DIALOGUE_WHITE_BACK" );
//	ResizeControl ( szBoxControl );	
//}
//itemmall
void CBasicLineBoxEx::CreateBaseBoxDialogueWhite ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_DIALOGUE_WHITE" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_RIGHT_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_TOP_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_BOTTOM_DIALOGUE_WHITE" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_LEFTBOTTOM_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_RIGHTTOP_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DIALOGUE_WHITE" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxDialogueWhiteBack ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_DIALOGUE_WHITE_BACK" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_RIGHT_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_TOP_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_BOTTOM_DIALOGUE_WHITE_BACK" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_LEFTBOTTOM_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_RIGHTTOP_DIALOGUE_WHITE_BACK", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DIALOGUE_WHITE_BACK" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxWhiteOuter ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_WHITE_OUTER" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_WHITE_OUTER", "BASIC_LINE_BOX_EX_RIGHT_WHITE_OUTER", "BASIC_LINE_BOX_EX_TOP_WHITE_OUTER", "BASIC_LINE_BOX_EX_BOTTOM_WHITE_OUTER" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_WHITE_OUTER", "BASIC_LINE_BOX_EX_LEFTBOTTOM_WHITE_OUTER", "BASIC_LINE_BOX_EX_RIGHTTOP_WHITE_OUTER", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DIALOGUE_WHITE" );
	ResizeControl ( szBoxControl );	
}

//void CBasicLineBoxEx::CreateBaseBoxDialogueBlackBack ( char* szBoxControl )
//{
//	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_DIALOGUE_GREY_BASE" );
//	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_DIALOGUE_GREY_BASE", "BASIC_LINE_BOX_EX_RIGHT_DIALOGUE_GREY_BASE", "BASIC_LINE_BOX_EX_TOP_DIALOGUE_GREY_BASE", "BASIC_LINE_BOX_EX_BOTTOM_DIALOGUE_GREY_BASE" );
//	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_DIALOGUE_GREY_BASE", "BASIC_LINE_BOX_EX_LEFTBOTTOM_DIALOGUE_GREY_BASE", "BASIC_LINE_BOX_EX_RIGHTTOP_DIALOGUE_GREY_BASE", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DIALOGUE_GREY_BASE" );
//	ResizeControl ( szBoxControl );	
//}
void CBasicLineBoxEx::CreateBaseBoxDialogueBlackBack ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_DIALOGUE_BLACK_BACK" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_DIALOGUE_BLACK_BACK", "BASIC_LINE_BOX_EX_RIGHT_DIALOGUE_BLACK_BACK", "BASIC_LINE_BOX_EX_TOP_DIALOGUE_BLACK_BACK", "BASIC_LINE_BOX_EX_BOTTOM_DIALOGUE_BLACK_BACK" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_DIALOGUE_BLACK_BACK", "BASIC_LINE_BOX_EX_LEFTBOTTOM_DIALOGUE_BLACK_BACK", "BASIC_LINE_BOX_EX_RIGHTTOP_DIALOGUE_BLACK_BACK", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DIALOGUE_BLACK_BACK" );
	ResizeControl ( szBoxControl );	
}

void CBasicLineBoxEx::CreateBaseBoxDialogueGrayBack ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_DIALOGUE_DRAK_BASE" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_DIALOGUE_DRAK_BASE", "BASIC_LINE_BOX_EX_RIGHT_DIALOGUE_DRAK_BASE", "BASIC_LINE_BOX_EX_TOP_DIALOGUE_DRAK_BASE", "BASIC_LINE_BOX_EX_BOTTOM_DIALOGUE_DRAK_BASE" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_DIALOGUE_DRAK_BASE", "BASIC_LINE_BOX_EX_LEFTBOTTOM_DIALOGUE_DRAK_BASE", "BASIC_LINE_BOX_EX_RIGHTTOP_DIALOGUE_DRAK_BASE", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DIALOGUE_DRAK_BASE" );
	ResizeControl ( szBoxControl );	
}
void CBasicLineBoxEx::CreateBaseBoxDialogueLightGray ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_DIALOGUE_WHITE" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_RIGHT_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_TOP_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_BOTTOM_DIALOGUE_WHITE" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_LEFTBOTTOM_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_RIGHTTOP_DIALOGUE_WHITE", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DIALOGUE_WHITE" );
	ResizeControl ( szBoxControl );	
}
void CBasicLineBoxEx::CreateBaseBoxDialogueDarkGray( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_SLOT_GRAY" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_SLOT_GRAY", "BASIC_LINE_BOX_EX_RIGHT_SLOT_GRAY", "BASIC_LINE_BOX_EX_TOP_SLOT_GRAY", "BASIC_LINE_BOX_EX_BOTTOM_SLOT_GRAY" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_SLOT_GRAY", "BASIC_LINE_BOX_EX_LEFTBOTTOM_SLOT_GRAY", "BASIC_LINE_BOX_EX_RIGHTTOP_SLOT_GRAY", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_SLOT_GRAY" );
	ResizeControl ( szBoxControl );	
}
void CBasicLineBoxEx::CreateBaseBoxDialogueNewBase ( char* szBoxControl )
{
	CreateBodyImage ( "BASIC_LINE_BOX_EX_BODY_DIALOGUE_NEW_BASE" );
	CreateLineImage ( "BASIC_LINE_BOX_EX_LEFT_DIALOGUE_NEW_BASE", "BASIC_LINE_BOX_EX_RIGHT_DIALOGUE_NEW_BASE", "BASIC_LINE_BOX_EX_TOP_DIALOGUE_NEW_BASE", "BASIC_LINE_BOX_EX_BOTTOM_DIALOGUE_NEW_BASE" );
	CreateLineImageEx ( "BASIC_LINE_BOX_EX_LEFTTOP_DIALOGUE_NEW_BASE", "BASIC_LINE_BOX_EX_LEFTBOTTOM_DIALOGUE_NEW_BASE", "BASIC_LINE_BOX_EX_RIGHTTOP_DIALOGUE_NEW_BASE", "BASIC_LINE_BOX_EX_RIGHTBOTTOM_DIALOGUE_NEW_BASE" );
	ResizeControl ( szBoxControl );	
}