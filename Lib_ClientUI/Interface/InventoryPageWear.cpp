#include "StdAfx.h"
#include "InventoryPageWear.h"
#include "ItemImage.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "InnerInterface.h"
#include "ItemMove.h"
#include "BasicButton.h"
#include "GameTextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CInventoryPageWear::nOUTOFRANGE = -1;

CInventoryPageWear::CInventoryPageWear () 
	: m_pMouseOver ( NULL )

	/*equipment lock, Juver, 2018/01/16 */
	, m_pButtonLock(NULL)
	, m_pButtonUnlock(NULL)
{
}

CInventoryPageWear::~CInventoryPageWear ()
{
}

void CInventoryPageWear::CreateSubControl ( int nClassType )
{
	CString	strInvenWearBack[GLCI_NUM_8CLASS] = 
	{
		"INVENTORY_PAGE_WEAR_FIGHTER_M",
		"INVENTORY_PAGE_WEAR_ARMS_M",
		"INVENTORY_PAGE_WEAR_ARCHER_W",
		"INVENTORY_PAGE_WEAR_SPIRIT_W",
		"INVENTORY_PAGE_WEAR_EXTREME_M",
		"INVENTORY_PAGE_WEAR_EXTREME_W",
		"INVENTORY_PAGE_WEAR_FIGHTER_W",
		"INVENTORY_PAGE_WEAR_ARMS_W",
		"INVENTORY_PAGE_WEAR_ARCHER_M",
		"INVENTORY_PAGE_WEAR_SPIRIT_M",
		"INVENTORY_PAGE_WEAR_SCIENTIST_M",
		"INVENTORY_PAGE_WEAR_SCIENTIST_W",
		"INVENTORY_PAGE_WEAR_ASSASSIN_M",
		"INVENTORY_PAGE_WEAR_ASSASSIN_W",
		"INVENTORY_PAGE_WEAR_TRICKER_M",
		"INVENTORY_PAGE_WEAR_TRICKER_W",
	};

	CreateControl ( strInvenWearBack[nClassType].GetString () );
	
	{
		CString strInvenWearItem[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOT_HEAD",			//À—«
			"CHARACTER_WINDOW_WEAR_SLOT_NECK",			// √ÈÕ¬
			"CHARACTER_WINDOW_WEAR_SLOT_UPPER",			//‡ ◊ÈÕ
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_WEAPON",	//¬—π °√– ÿπ
			"CHARACTER_WINDOW_WEAR_SLOT_WRIST",			//µË“ßÀŸ
			"CHARACTER_WINDOW_WEAR_SLOT_HAND",			//∂ÿß¡◊Õ
			"CHARACTER_WINDOW_WEAR_SLOT_LOWER",			//°“ß‡°ß
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_EARRING",	//·À«π1
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_WEAPON",	//Õ“«ÿ∏
			"CHARACTER_WINDOW_WEAR_SLOT_FOOT",			//√Õß‡∑È“
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_EARRING",//·À«π2
			"CHARACTER_WINDOW_WEAR_SLOT_VEHICLE",		//√∂
		};

		CString strInvenWearOver[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOT_HEAD_OVER",			//À—«
			"CHARACTER_WINDOW_WEAR_SLOT_NECK_OVER",			// √ÈÕ¬
			"CHARACTER_WINDOW_WEAR_SLOT_UPPER_OVER",		//‡ ◊ÈÕ
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_WEAPON_OVER",	//¬—π °√– ÿπ
			"CHARACTER_WINDOW_WEAR_SLOT_WRIST_OVER",		//µË“ßÀŸ
			"CHARACTER_WINDOW_WEAR_SLOT_HAND_OVER",			//∂ÿß¡◊Õ
			"CHARACTER_WINDOW_WEAR_SLOT_LOWER_OVER",		//°“ß‡°ß
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_EARRING_OVER",	//·À«π1
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_WEAPON_OVER",	//Õ“«ÿ∏
			"CHARACTER_WINDOW_WEAR_SLOT_FOOT_OVER",			//√Õß‡∑È“
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_EARRING_OVER",//·À«π2
			"CHARACTER_WINDOW_WEAR_SLOT_VEHICLE_OVER",		//√∂
		};

		for ( int i = 0; i < ITEM_IMAGE_SIZE; i++ )
		{
			m_pItemImage[i] = CreateItemImage ( strInvenWearItem[i].GetString (), ITEM_IMAGE0 + i );
			m_pSlotDisplay[i] = CreateControl ( strInvenWearOver[i].GetString () );
			m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );
		}
	}

	m_pMouseOver = CreateControl ( "ITEM_MOUSE_OVER" );
//	m_pSlotDisplay = CreateControl ( "TRADE_INVENTORY_OVER_0" );
//	m_pSlotBlockDisplay = CreateControl ( "TRADE_OVER_0" );


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

CUIControl*	CInventoryPageWear::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

CItemImage*	CInventoryPageWear::CreateItemImage ( const char* szControl, UIGUID ControlID )
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, szControl, UI_FLAG_DEFAULT, ControlID );
	pItemImage->CreateSubControl ();
	RegisterControl ( pItemImage );

	return pItemImage;
}

EMSLOT CInventoryPageWear::IMAGE2EMSLOT ( int nIndex )
{
	switch ( nIndex )
	{	
	case ITEM_IMAGE0:	return SLOT_HEADGEAR;	//	∏”∏Æ
	case ITEM_IMAGE1:	return SLOT_NECK;		//	∏Ò∞…¿Ã
	case ITEM_IMAGE2:	return SLOT_UPPER;		//	ªÛ¿«
	case ITEM_IMAGE3:	return SLOT_LHAND;		//	øﬁº’µµ±∏
	case ITEM_IMAGE4:	return SLOT_WRIST;		//	º’∏Ò
	case ITEM_IMAGE5:	return SLOT_HAND;		//	¿Â∞©
	case ITEM_IMAGE6:	return SLOT_LOWER;		//	«œ¿«
	case ITEM_IMAGE7:	return SLOT_LFINGER;	//	øﬁº’ º’∞°∂Ù
	case ITEM_IMAGE8:	return SLOT_RHAND;		//	ø¿∏•º’µµ±∏
	case ITEM_IMAGE9:	return SLOT_FOOT;		//	Ω≈πﬂ
	case ITEM_IMAGE10:	return SLOT_RFINGER;	//	ø¿∏•º’ º’∞°∂Ù	
	case ITEM_IMAGE11:	return SLOT_VEHICLE;	
	}

	GASSERT ( 0 && "π¸¿ß∏¶ π˛æÓ≥≥¥œ¥Ÿ." );
	return SLOT_TSIZE;
}

void CInventoryPageWear::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE );
	if ( m_pMouseOver ) m_pMouseOver->SetVisibleSingle ( FALSE );
//	if ( m_pSlotDisplay ) m_pSlotDisplay->SetVisibleSingle ( FALSE );
//	if ( m_pSlotBlockDisplay ) m_pSlotBlockDisplay->SetVisibleSingle ( FALSE );

	//	Ω∫≥¿, Ω∫≈≥ ¿ÃπÃ¡ˆ ∫Ÿ¿Ã±‚
	CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
	SNATIVEID sHOLD_ITEM_ID(false);
//	bool bFOUND_TOWEAR = false;
	if ( pItemMove ) sHOLD_ITEM_ID = pItemMove->GetItem();

	for ( int i = 0; i < SLOT_NSIZE_2; i++ )
	{
		const SITEMCUSTOM& sItemCustomOld = GetItem ( i );

		EMSLOT emSlot = IMAGE2EMSLOT ( i + ITEM_IMAGE0 );
		SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_SLOT_ITEM ( emSlot );

		//	NOTE
		//		¿Ã¿¸ «¡∑π¿”∞˙ ∫Ò±≥«œø©,
		//		µ•¿Ã≈∏∞° ¥ﬁ∂Û¡¯ ∞ÊøÏø°∏∏,
		//		∑ŒµÂ/æ∑ŒµÂ ¿€æ˜¿ª ¡¯«‡«—¥Ÿ.
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
		//		¿Â¬¯µ… ¿ßƒ° «•Ω√
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

void CInventoryPageWear::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
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
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = ControlID - ITEM_IMAGE0;
				SetItemIndex ( nIndex );

				if ( !CInnerInterface::GetInstance().IsFirstItemSlot () ) return ;

				//	Ω∫≥¿, Ω∫≈≥ ¿ÃπÃ¡ˆ ∫Ÿ¿Ã±‚
				CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
				if ( !pItemMove )
				{
					GASSERT ( 0 && "CItemMove∞° ≥Œ¿‘¥œ¥Ÿ." );
					return ;
				}

				if ( pItemMove->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcSlotPos = m_pItemImage[nIndex]->GetGlobalPos ();
					pItemMove->SetGlobalPos ( rcSlotPos );						

					AddMessageEx ( UIMSG_MOUSEIN_WEARSLOT | UIMSG_TOTOPPARENT );
				}				

				//	∏∂øÏΩ∫ «•Ω√ ≈◊µŒ∏Æ
				if ( pItemMove->GetItem () == NATIVEID_NULL () && m_pItemImage[m_nIndex]->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcImagePos = m_pItemImage[nIndex]->GetGlobalPos ();
					m_pMouseOver->SetGlobalPos ( rcImagePos );
					m_pMouseOver->SetVisibleSingle ( TRUE );
				}
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

EMSLOT CInventoryPageWear::GetItemSlot ()
{
	return IMAGE2EMSLOT ( GetItemIndex () + ITEM_IMAGE0 );
}

void CInventoryPageWear::LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom )
{
	m_ItemCustomArray[nIndex] = ref_sItemCustom;

	SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_sItemCustom.sNativeID );
	m_pItemImage[nIndex]->SetItem ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), pItemData->sBasicOp.sNativeID );
}

SITEMCUSTOM& CInventoryPageWear::GetItem ( int nIndex )
{
	return m_ItemCustomArray[nIndex];
}

void CInventoryPageWear::UnLoadItem ( int nIndex )
{
	m_ItemCustomArray[nIndex].sNativeID = NATIVEID_NULL ();
	m_pItemImage[nIndex]->ResetItem ();
}