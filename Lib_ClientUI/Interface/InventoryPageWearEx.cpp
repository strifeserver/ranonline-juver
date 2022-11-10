#include "StdAfx.h"
#include "./InventoryPageWearEx.h"
#include "ItemImage.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "InnerInterface.h"
#include "ItemMove.h"
#include "BasicTextButton.h"
#include "../Lib_ClientUI/Interface/BasicTextBox.h"
#include "./BasicVarTextBox.h"
#include "GameTextControl.h"
#include "d3dfont.h"
#include "UITextControl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CInventoryPageWearEx::nOUTOFRANGE = -1;

CInventoryPageWearEx::CInventoryPageWearEx () 
	: m_pMouseOver(NULL)
	, m_pAButton(NULL)
	, m_pBButton(NULL)
	, m_pARHandSlot(NULL)
	, m_pALHandSlot(NULL)
	, m_pBRHandSlot(NULL)
	, m_pBLHandSlot(NULL)

	/*equipment lock, Juver, 2018/01/16 */
	, m_pButtonLock(NULL)
	, m_pButtonUnlock(NULL)
{
	memset ( m_Button, 0, sizeof ( CUIControl* ) * 2 );	
	memset ( m_ButtonSet, 0, sizeof ( CUIControl* ) * 2 );
}

CInventoryPageWearEx::~CInventoryPageWearEx ()
{
}

void CInventoryPageWearEx::CreateSubControl ( int nClassType )
{
	CString	strInvenWearBack[GLCI_NUM_5CLASS-GLCI_NUM_4CLASS] = 
	{
		"INVENTORY_PAGE_WEAR_EXTREME_M",
		"INVENTORY_PAGE_WEAR_EXTREME_W",
	};

	CreateControl ( strInvenWearBack[nClassType-GLCI_NUM_4CLASS].GetString () );

	{	//	아이템 이미지 ( 0 - 11 )
		CString strInvenWearItem[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOT_HEAD",
			"CHARACTER_WINDOW_WEAR_SLOT_NECK",
			"CHARACTER_WINDOW_WEAR_SLOT_UPPER",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_FIRST_LEFT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOT_BRACELET",
			"CHARACTER_WINDOW_WEAR_SLOT_HAND",
			"CHARACTER_WINDOW_WEAR_SLOT_LOWER",
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_RING",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_FIRST_RIGHT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOT_FOOT",
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_RING",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_SECOND_RIGHT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_SECOND_LEFT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOT_VEHICLE",
		};

		CString strInvenWearOver[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOT_HEAD_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_NECK_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_UPPER_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_FIRST_LEFT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_BRACELET_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_HAND_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_LOWER_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_RING_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_FIRST_RIGHT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_FOOT_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_RING_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_SECOND_RIGHT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_SECOND_LEFT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_VEHICLE_OVER",
		};


		for ( int i = 0; i < ITEM_IMAGE_SIZE; i++ )
		{
			m_pItemImage[i] = CreateItemImage ( strInvenWearItem[i].GetString (), ITEM_IMAGE0 + i );
			m_pSlotDisplay[i] = CreateControl ( strInvenWearOver[i].GetString () );
			m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );
		}
	}

	m_pMouseOver = CreateControl ( "ITEM_MOUSE_OVER" );

	CString strButton[2] =
	{
		"SWITCH_BUTTONA",
		"SWITCH_BUTTONB"
	};

	CString strButtonSet[2] =
	{
		"SWITCH_BUTTONA_F",
		"SWITCH_BUTTONB_F"
	};

	for ( int i = 0; i < 2 ; i++ )
	{
		m_Button[i] = new CUIControl;
		m_Button[i]->CreateSub ( this, strButton[i].GetString (), UI_FLAG_DEFAULT, SWITCH_BUTTONA + i );
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_Button[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_Button[i] );

		m_ButtonSet[i] = new CUIControl;
		m_ButtonSet[i]->CreateSub ( this, strButtonSet[i].GetString (), UI_FLAG_DEFAULT );	
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
		m_ButtonSet[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_ButtonSet[i] );
	}

	m_pARHandSlot = CreateControl("INVENTORY_USE_SLOT_RHAND_A");
	m_pALHandSlot = CreateControl("INVENTORY_USE_SLOT_LHAND_A");
	m_pBRHandSlot = CreateControl("INVENTORY_USE_SLOT_RHAND_B");
	m_pBLHandSlot = CreateControl("INVENTORY_USE_SLOT_LHAND_B");

	/*equipment lock, Juver, 2018/01/16 */
	m_pButtonLock = new CBasicButton;
	m_pButtonLock->CreateSub ( this, "INVEN_BUTTON_LOCK", UI_FLAG_DEFAULT, BUTTON_KEY_LOCK );
	m_pButtonLock->CreateFlip ( "INVEN_BUTTON_LOCK_F", CBasicButton::CLICK_FLIP );
	m_pButtonLock->SetFlip(false);
	m_pButtonLock->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pButtonLock );

	m_pButtonUnlock = new CBasicButton;
	m_pButtonUnlock->CreateSub ( this, "INVEN_BUTTON_UNLOCK", UI_FLAG_DEFAULT, BUTTON_KEY_UNLOCK );
	m_pButtonUnlock->CreateFlip ( "INVEN_BUTTON_UNLOCK_F", CBasicButton::CLICK_FLIP );
	m_pButtonUnlock->SetFlip(false);
	m_pButtonUnlock->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pButtonUnlock );
}

CUIControl*	CInventoryPageWearEx::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

CItemImage*	CInventoryPageWearEx::CreateItemImage ( const char* szControl, UIGUID ControlID )
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, szControl, UI_FLAG_DEFAULT, ControlID );
	pItemImage->CreateSubControl ();
	RegisterControl ( pItemImage );

	return pItemImage;
}

EMSLOT CInventoryPageWearEx::IMAGE2EMSLOT ( int nIndex )
{
	switch ( nIndex )
	{	
	case ITEM_IMAGE0:	return SLOT_HEADGEAR;	//	머리
	case ITEM_IMAGE1:	return SLOT_NECK;		//	목걸이
	case ITEM_IMAGE2:	return SLOT_UPPER;		//	상의
	case ITEM_IMAGE3:	return SLOT_LHAND;		//	왼손도구
	case ITEM_IMAGE4:	return SLOT_WRIST;		//	손목
	case ITEM_IMAGE5:	return SLOT_HAND;		//	장갑
	case ITEM_IMAGE6:	return SLOT_LOWER;		//	하의
	case ITEM_IMAGE7:	return SLOT_LFINGER;	//	왼손 손가락
	case ITEM_IMAGE8:	return SLOT_RHAND;		//	오른손도구
	case ITEM_IMAGE9:	return SLOT_FOOT;		//	신발
	case ITEM_IMAGE10:	return SLOT_RFINGER;	//	오른손 손가락	
	case ITEM_IMAGE11:	return SLOT_RHAND_S;	//	오른손도구, 극강부
	case ITEM_IMAGE12:	return SLOT_LHAND_S;	//	왼손도구, 극강부
	case ITEM_IMAGE13:	return SLOT_VEHICLE;	//  탈것
	}

	GASSERT ( 0 && "범위를 벗어납니다." );
	return SLOT_TSIZE;
}

void CInventoryPageWearEx::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE );
	if ( m_pMouseOver ) m_pMouseOver->SetVisibleSingle ( FALSE );

	//	스냅, 스킬 이미지 붙이기
	CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
	SNATIVEID sHOLD_ITEM_ID(false);
	if ( pItemMove ) sHOLD_ITEM_ID = pItemMove->GetItem();

	for ( int i = 0; i < SLOT_NSIZE_S_2; i++ )
	{
		const SITEMCUSTOM& sItemCustomOld = GetItem ( i );

		EMSLOT emSlot = IMAGE2EMSLOT ( i + ITEM_IMAGE0 );
		SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_SLOT_ITEM ( emSlot );

		//	NOTE
		//		이전 프레임과 비교하여,
		//		데이타가 달라진 경우에만,
		//		로드/언로드 작업을 진행한다.
		if ( sItemCustom != sItemCustomOld )
		{		
			if ( sItemCustom.sNativeID != NATIVEID_NULL () )
			{
				LoadItem ( i, sItemCustom );
			}
			else
			{
				UnLoadItem ( i );
			}
		}

		m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );

		//	NOTE
		//		장착될 위치 표시
		if ( sHOLD_ITEM_ID != NATIVEID_NULL () /*&& !bFOUND_TOWEAR*/ )
		{
			if ( GLGaeaClient::GetInstance().GetCharacter()->CHECKSLOT_ITEM ( sHOLD_ITEM_ID, emSlot ) )
			{
				const UIRECT& rcImagePos = m_pItemImage[i]->GetGlobalPos ();
				D3DXVECTOR2 vPos ( rcImagePos.left, rcImagePos.top );

				if ( GLGaeaClient::GetInstance().GetCharacter()->ACCEPT_ITEM ( sHOLD_ITEM_ID ) )
				{
					m_pSlotDisplay[i]->SetVisibleSingle ( TRUE );
				}

//				bFOUND_TOWEAR = true;
			}
		}
	}

	/*puton lock, Juver, 2018/01/13 */
	BOOL bEnabled = GLGaeaClient::GetInstance().GetCharacter()->m_bEnableEquipmentLock;
	BOOL bLocked = GLGaeaClient::GetInstance().GetCharacter()->m_bEquipmentLockStatus;
	if ( m_pButtonLock )	m_pButtonLock->SetVisibleSingle( bEnabled && bLocked );
	if ( m_pButtonUnlock )	m_pButtonUnlock->SetVisibleSingle( bEnabled && !bLocked );

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CInventoryPageWearEx::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ITEM_IMAGE0:
	case ITEM_IMAGE1:
	case ITEM_IMAGE2:
	case ITEM_IMAGE3:
	case ITEM_IMAGE4:
	case ITEM_IMAGE5:
	case ITEM_IMAGE6:
	case ITEM_IMAGE7:
	case ITEM_IMAGE8:
	case ITEM_IMAGE9:
	case ITEM_IMAGE10:	
	case ITEM_IMAGE11:	
	case ITEM_IMAGE12:	
	case ITEM_IMAGE13:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = ControlID - ITEM_IMAGE0;
				SetItemIndex ( nIndex );

				if ( !CInnerInterface::GetInstance().IsFirstItemSlot () ) return ;

				//	스냅, 스킬 이미지 붙이기
				CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
				if ( !pItemMove )
				{
					GASSERT ( 0 && "CItemMove가 널입니다." );
					return ;
				}

				if ( pItemMove->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcSlotPos = m_pItemImage[nIndex]->GetGlobalPos ();
					pItemMove->SetGlobalPos ( rcSlotPos );						

					AddMessageEx ( UIMSG_MOUSEIN_WEARSLOTEX | UIMSG_TOTOPPARENT );
				}				

				//	마우스 표시 테두리
				if ( pItemMove->GetItem () == NATIVEID_NULL () && m_pItemImage[m_nIndex]->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcImagePos = m_pItemImage[nIndex]->GetGlobalPos ();
					m_pMouseOver->SetGlobalPos ( rcImagePos );
					m_pMouseOver->SetVisibleSingle ( TRUE );
				}
			}
		}
		break;

	case SWITCH_BUTTONA:
		{
			if( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				SWITCH1();
				GLGaeaClient::GetInstance().GetCharacter()->ReqSlotChange();
			}
		}
		break;
		
	case SWITCH_BUTTONB:
		{
			if( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				SWITCH2();
				GLGaeaClient::GetInstance().GetCharacter()->ReqSlotChange();
			}
		}
		break;
		/*puton lock, Juver, 2018/01/13 */
	case BUTTON_KEY_LOCK:
	case BUTTON_KEY_UNLOCK:
		{
			if( CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
				CInnerInterface::GetInstance().OpenEquipmentLockInput();
		}break;
	}
}

EMSLOT CInventoryPageWearEx::GetItemSlot ()
{
	return IMAGE2EMSLOT ( GetItemIndex () + ITEM_IMAGE0 );
}

void CInventoryPageWearEx::LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom )
{
	m_ItemCustomArray[nIndex] = ref_sItemCustom;

	SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_sItemCustom.sNativeID );
	m_pItemImage[nIndex]->SetItem ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), pItemData->sBasicOp.sNativeID );
}

SITEMCUSTOM& CInventoryPageWearEx::GetItem ( int nIndex )
{
	return m_ItemCustomArray[nIndex];
}

void CInventoryPageWearEx::UnLoadItem ( int nIndex )
{
	m_ItemCustomArray[nIndex].sNativeID = NATIVEID_NULL ();
	m_pItemImage[nIndex]->ResetItem ();
}

void CInventoryPageWearEx::SWITCH1()
{
	for ( int i = 0; i < 2; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[0]->SetVisibleSingle ( TRUE );
	m_Button[0]->SetVisibleSingle ( FALSE );

	m_pARHandSlot->SetVisibleSingle( FALSE );
	m_pALHandSlot->SetVisibleSingle( FALSE );
	m_pBRHandSlot->SetVisibleSingle( TRUE );
	m_pBLHandSlot->SetVisibleSingle( TRUE );
}
void CInventoryPageWearEx::SWITCH2()
{
	for ( int i = 0; i < 2; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[1]->SetVisibleSingle ( TRUE );
	m_Button[1]->SetVisibleSingle ( FALSE );

	m_pARHandSlot->SetVisibleSingle( TRUE );
	m_pALHandSlot->SetVisibleSingle( TRUE );
	m_pBRHandSlot->SetVisibleSingle( FALSE );
	m_pBLHandSlot->SetVisibleSingle( FALSE );
}

void CInventoryPageWearEx::SetTabButton( BOOL bMain )
{
	if( bMain )
	{
		for ( int i = 0; i < 2; i++ )
		{
			m_Button[i]->SetVisibleSingle ( TRUE );
			m_ButtonSet[i]->SetVisibleSingle ( FALSE );
		}
		m_ButtonSet[0]->SetVisibleSingle ( TRUE );
		m_Button[0]->SetVisibleSingle ( FALSE );

		m_pARHandSlot->SetVisibleSingle( FALSE );
		m_pALHandSlot->SetVisibleSingle( FALSE );
		m_pBRHandSlot->SetVisibleSingle( TRUE );
		m_pBLHandSlot->SetVisibleSingle( TRUE );
	}
	else
	{
		for ( int i = 0; i < 2; i++ )
		{
			m_Button[i]->SetVisibleSingle ( TRUE );
			m_ButtonSet[i]->SetVisibleSingle ( FALSE );
		}
		m_ButtonSet[1]->SetVisibleSingle ( TRUE );
		m_Button[1]->SetVisibleSingle ( FALSE );

		m_pARHandSlot->SetVisibleSingle( TRUE );
		m_pALHandSlot->SetVisibleSingle( TRUE );
		m_pBRHandSlot->SetVisibleSingle( FALSE );
		m_pBLHandSlot->SetVisibleSingle( FALSE );
	}
}