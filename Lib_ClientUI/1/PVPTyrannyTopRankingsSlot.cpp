#include "StdAfx.h"
#include "PVPTyrannyTopRankingsSlot.h"

#include "../Lib_Engine/DxCommon/DxFontMan.h"
#include "BasicLineBox.h"
#include "BasicTextBox.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "GLPVPTyrannyDefine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPVPTyrannyTopRankingsSlot::CPVPTyrannyTopRankingsSlot ()
	: m_pTextRank(NULL)
	, m_pTextName(NULL)
{
	for( int i=0; i<TYRANNY_SCHOOL_SIZE; ++i )
		m_pSchoolImage[i] = NULL;

	for( int i=0; i<GLCI_NUM_8CLASS; ++i )
		m_pClassImage[i] = NULL;
}

CPVPTyrannyTopRankingsSlot::~CPVPTyrannyTopRankingsSlot ()
{
}

void CPVPTyrannyTopRankingsSlot::CreateSubControl ()
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, _DEFAULT_FONT_FLAG );

	m_pTextRank = new CBasicTextBox;
	m_pTextRank->CreateSub ( this, "CTF_RESULT_TEXT_BASE_RANK" );
	m_pTextRank->SetFont ( pFont8 );
	m_pTextRank->SetTextAlign ( TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	m_pTextRank->SetText( "--", NS_UITEXTCOLOR::WHITE );
	RegisterControl ( m_pTextRank );

	m_pTextName = new CBasicTextBox;
	m_pTextName->CreateSub ( this, "CTF_RESULT_TEXT_BASE_NAME" );
	m_pTextName->SetFont ( pFont8 );
	m_pTextName->SetTextAlign ( TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	m_pTextName->SetText( "--", NS_UITEXTCOLOR::WHITE );
	RegisterControl ( m_pTextName );

	std::string strschool_image[TYRANNY_SCHOOL_SIZE] = 
	{
		"CTF_RESULT_RANKSLOT_IMAGE_SCHOOL0",
		"CTF_RESULT_RANKSLOT_IMAGE_SCHOOL1",
		"CTF_RESULT_RANKSLOT_IMAGE_SCHOOL2",
	};

	std::string strclass_image[GLCI_NUM_8CLASS] = 
	{
		"CTF_RESULT_RANKSLOT_IMAGE_BRAWLER_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SWORDMAN_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_ARCHER_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SHAMAN_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_EXTREME_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_EXTREME_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_BRAWLER_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SWORDMAN_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_ARCHER_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SHAMAN_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SCIENTIST_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SCIENTIST_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_ASSASSIN_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_ASSASSIN_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_TRICKER_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_TRICKER_FEMALE",
	};

	for( int i=0; i<TYRANNY_SCHOOL_SIZE; ++i )
	{
		m_pSchoolImage[i] = new CUIControl;
		m_pSchoolImage[i]->CreateSub ( this, strschool_image[i].c_str(), UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pSchoolImage[i]->SetVisibleSingle( FALSE );
		RegisterControl ( m_pSchoolImage[i] );
	}

	for( int i=0; i<GLCI_NUM_8CLASS; ++i )
	{
		m_pClassImage[i] = new CUIControl;
		m_pClassImage[i]->CreateSub ( this, strclass_image[i].c_str(), UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pClassImage[i]->SetVisibleSingle( FALSE );
		RegisterControl ( m_pClassImage[i] );
	}
}

void CPVPTyrannyTopRankingsSlot::ResetData()
{
	if ( m_pTextRank )		m_pTextRank->ClearText();
	if ( m_pTextName )		m_pTextName->ClearText();

	for( int i=0; i<TYRANNY_SCHOOL_SIZE; ++i )
	{
		if ( m_pSchoolImage[i] )
			m_pSchoolImage[i]->SetVisibleSingle( FALSE );
	}

	for( int i=0; i<GLCI_NUM_8CLASS; ++i )
	{
		if ( m_pClassImage[i] )
			m_pClassImage[i]->SetVisibleSingle( FALSE );
	}
}

void CPVPTyrannyTopRankingsSlot::SetData( TYRANNY_PLAYER_DATA* pData )
{
	ResetData();

	if ( !pData )	return;
	CString strText;

	if ( m_pTextRank )
	{
		strText.Format( "%u", pData->wRankAll );
		m_pTextRank->AddText( strText.GetString(), NS_UITEXTCOLOR::WHITE );
	}

	if ( m_pTextName )
	{
		strText.Format( "%s", pData->szInfoCharName );
		m_pTextName->AddText( strText.GetString(), NS_UITEXTCOLOR::WHITE );
	}

	if ( pData->wInfoSchool < TYRANNY_SCHOOL_SIZE )
	{
		if ( m_pSchoolImage[pData->wInfoSchool] )
			m_pSchoolImage[pData->wInfoSchool]->SetVisibleSingle( TRUE );
	}

	if ( pData->wInfoClass < GLCI_NUM_8CLASS )
	{
		if ( m_pClassImage[pData->wInfoClass] )
			m_pClassImage[pData->wInfoClass]->SetVisibleSingle( TRUE );
	}
}