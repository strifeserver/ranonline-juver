#include "StdAfx.h"
#include "CrowTargetInfoNpc.h"
#include "InnerInterface.h"
#include "BasicLineBox.h"
#include "../Lib_Engine/DxCommon/d3dfont.h"
#include "../Lib_Engine/DxCommon/DxFontMan.h"
#include "BasicLineBox.h"
#include "BasicLineBoxEx.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "BasicTextBox.h"

#include "../Lib_Client/G-Logic/GLGaeaClient.h"
#include "../Lib_Client/G-Logic/GLCrowData.h"
#include "../Lib_Client/G-Logic/GLCrow.h"
#include "../Lib_Client/G-Logic/GLCrowClient.h"
#include "../Lib_Client/G-Logic/GlogicEx.h"
#include "../Lib_Client/NpcTalk/NpcTalk.h"

#include "GLCharData.h"
#include "GLCharacter.h"
#include "GLChar.h"
#include "GLCharClient.h"
#include "GLogicData.h"
#include "GLCharDefine.h"
#include "UIInfoLoader.h"
#include "GLCrowRenList.h"
#include "GLStringTable.h"
#include "../Lib_Client/NpcTalk/NpcTalk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCrowTargetInfoNpc::CCrowTargetInfoNpc () :
	m_pNameBoxDummy ( NULL )
{
}

CCrowTargetInfoNpc::~CCrowTargetInfoNpc ()
{
}

void CCrowTargetInfoNpc::CreateSubControl ()
{
	m_pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );

	/*m_pTargetBox = new CBasicLineBoxEx;
	m_pTargetBox->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pTargetBox->CreateBaseBoxVarTextBoxNew ( "RNCROW_TARGET_INFOBOX_NPC" );
	m_pTargetBox->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pTargetBox );*/

	CBasicLineBoxEx* m_pTargetBox = new CBasicLineBoxEx;
	m_pTargetBox->CreateSub ( this, "RNCROW_TARGET_INFOBOX_NPC", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pTargetBox->CreateBaseBoxVarTextBox ( "BASIC_VAR_LINE_NPC_BOX" );
	m_pTargetBox->SetDiffuse ( D3DCOLOR_ARGB (175,0xC0,0xC0,0xC0) );
	m_pTargetBox->SetNoUpdate ( true );
	RegisterControl ( m_pTargetBox );

	CBasicTextBox* m_pHP = new CBasicTextBox;
	m_pHP->CreateSub ( this, "HP_NAMEBOX_NPC" );
    m_pHP->SetFont ( m_pFont8 );
	m_pHP->SetTextAlign ( TEXT_ALIGN_LEFT );
	m_pHP->SetControlNameEx ( "HP Text" );	
	m_pHP->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	RegisterControl ( m_pHP );
	m_pHPBox = m_pHP;

	CBasicTextBox* pNameBox = new CBasicTextBox;
	pNameBox->CreateSub ( this, "CROW_NAMEBOX_NPC" );
    pNameBox->SetFont ( m_pFont8 );
	pNameBox->SetTextAlign ( TEXT_ALIGN_LEFT );
	pNameBox->SetControlNameEx ( "HP Text" );	
	pNameBox->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	RegisterControl ( pNameBox );
	m_pNameBox = pNameBox;
	
	m_pNameBoxDummy = CreateControl ( "CROW_NAMEBOX_NPC", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
}

CUIControl*	CCrowTargetInfoNpc::CreateControl ( const char* szControl, WORD wAlignFlag )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl, wAlignFlag );
	RegisterControl ( pControl );
	return pControl;
}

void CCrowTargetInfoNpc::SetTargetInfo ( CString strName )
{	
		CString strCombine;
		CString combine;
		strCombine.Format ( "[Npc Type]");
		m_pHPBox->SetOneLineText ( strCombine, NS_UITEXTCOLOR::DODGERBLUE );
		m_pNameBox->ClearText ();
		
		SIZE Size;
		m_pFont8->GetTextExtent ( strName.GetString (), Size );
		
		CString strTemp;
		strTemp.Format ( "%s", strName );
		m_pNameBox->SetOneLineText ( strTemp, NS_UITEXTCOLOR::WHITE );	
		m_strName = strName;
}
