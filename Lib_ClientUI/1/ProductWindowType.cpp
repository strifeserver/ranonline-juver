#include "StdAfx.h"
#include "ProductWindowType.h"
#include "ProductWindowTypeBase.h"
#include "BasicButton.h"

#include "InnerInterface.h"
#include "UITextControl.h"
#include "GameTextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CProductWindowType::CProductWindowType ()
	: m_nSelect(0)
{
	for( int i=0; i<PRODUCT_WINDOW_TYPE_SIZE; ++i )
		m_pIconType[i] = NULL;
}

CProductWindowType::~CProductWindowType ()
{
}

void CProductWindowType::CreateSubControl ()
{
	std::string stricon[PRODUCT_WINDOW_TYPE_SIZE] = 
	{
		"RAN_PRODUCT_WINDOW_TYPE_ALL_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_HEAD_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_UPPER_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_UNDER_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_GLOVES_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_SHOES_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_WEAPON_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_NECKLACE_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_BRACELET_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_RING_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_VEHICLE_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_ETC_BASE",
		"RAN_PRODUCT_WINDOW_TYPE_COSTUME_BASE",
	};

	std::string stricon_base[PRODUCT_WINDOW_TYPE_SIZE] = 
	{
		"RAN_PRODUCT_WINDOW_TYPE_ALL_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_HEAD_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_UPPER_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_UNDER_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_GLOVES_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_SHOES_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_WEAPON_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_NECKLACE_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_BRACELET_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_RING_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_VEHICLE_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_ETC_INACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_COSTUME_INACTIVE",
	};

	std::string stricon_select[PRODUCT_WINDOW_TYPE_SIZE] = 
	{
		"RAN_PRODUCT_WINDOW_TYPE_ALL_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_HEAD_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_UPPER_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_UNDER_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_GLOVES_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_SHOES_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_WEAPON_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_NECKLACE_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_BRACELET_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_RING_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_VEHICLE_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_ETC_ACTIVE",
		"RAN_PRODUCT_WINDOW_TYPE_COSTUME_ACTIVE",
	};

	std::string stricon_over[PRODUCT_WINDOW_TYPE_SIZE] = 
	{
		"RAN_PRODUCT_WINDOW_TYPE_ALL_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_HEAD_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_UPPER_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_UNDER_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_GLOVES_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_SHOES_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_WEAPON_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_NECKLACE_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_BRACELET_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_RING_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_VEHICLE_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_ETC_OVER",
		"RAN_PRODUCT_WINDOW_TYPE_COSTUME_OVER",
	};

	for( int i=0; i<PRODUCT_WINDOW_TYPE_SIZE; ++i )
	{
		m_pIconType[i] = new CProductWindowTypeBase;
		m_pIconType[i]->CreateSub ( this, stricon[i].c_str(), UI_FLAG_DEFAULT, PRODUCT_WINDOW_TYPE_ALL + i );
		m_pIconType[i]->CreateSubControl ( stricon_base[i].c_str(), stricon_select[i].c_str(), stricon_over[i].c_str() );
		RegisterControl ( m_pIconType[i] );
	}

	DefaultSelect();
}

void CProductWindowType::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case PRODUCT_WINDOW_TYPE_ALL:
	case PRODUCT_WINDOW_TYPE_HATS:
	case PRODUCT_WINDOW_TYPE_UPPER:
	case PRODUCT_WINDOW_TYPE_LOWER:
	case PRODUCT_WINDOW_TYPE_GLOVES:
	case PRODUCT_WINDOW_TYPE_SHOES:
	case PRODUCT_WINDOW_TYPE_WEAPONS:
	case PRODUCT_WINDOW_TYPE_NECK:
	case PRODUCT_WINDOW_TYPE_BRACELET:
	case PRODUCT_WINDOW_TYPE_RING:
	case PRODUCT_WINDOW_TYPE_ETC:
	case PRODUCT_WINDOW_TYPE_BOX:
	case PRODUCT_WINDOW_TYPE_COSTUME:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nSelect = ControlID - PRODUCT_WINDOW_TYPE_ALL;
			
				if ( nSelect >= 0 && nSelect < PRODUCT_WINDOW_TYPE_SIZE )
				{
					if ( CHECK_LB_UP_LIKE ( dwMsg ) )	
					{
						m_nSelect = nSelect;
						
						AddMessageEx ( UIMSG_PRODUCT_WINDOW_TYPE_SELECT );

						for ( int i=0; i<PRODUCT_WINDOW_TYPE_SIZE; ++i )
						{
							if ( m_pIconType[i] )
								m_pIconType[i]->SetSelect( i == nSelect );
						}
					}

					CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( ID2GAMEWORD( "RAN_PRODUCT_TYPE_STRING", nSelect ), NS_UITEXTCOLOR::WHITE );
				}
			}
		}break;
	};
}

void CProductWindowType::DefaultSelect()
{
	for ( int i=0; i<PRODUCT_WINDOW_TYPE_SIZE; ++i )
	{
		if ( m_pIconType[i] )
			m_pIconType[i]->SetSelect( i == 0 );
	}
}

