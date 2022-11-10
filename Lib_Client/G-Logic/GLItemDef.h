#ifndef GLITEMDEF_H_
#define GLITEMDEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "../../Lib_Engine/Meshs/DxPieceDefine.h"

#include "GLItemDefEX.h"

/*item color, Juver, 2018/01/04 */
#define ITEMCOLOR_WHITE 32767

namespace glold_102
{
	enum GLITEM_ATT_102
	{
		ITEMATT_NOTHING		= 0,	//	Âø¿ë¹«±â¾øÀ½.

		ITEMATT_SWORD		= 1,	//	°Ë·ù.
		ITEMATT_REV00		= 2,	//	REV00
		ITEMATT_DAGGER		= 3,	//	´Ü°Ë·ù.
		ITEMATT_SPEAR		= 4,	//	Ã¢·ù.
		ITEMATT_BOW			= 5,	//	È°·ù.
		ITEMATT_THROW		= 6,	//	ÅõÃ´·ù.

		ITEMATT_NOCARE		= 7,	//	Å¸ÀÔ »ó°ü ¾ÈÇÔ.	( "GLSKILL" ¿¡¼­ Hand ¹«±â Á¦ÇÑ ¼Ó¼º¿¡¼­ »ç¿ëµÊ. )
		ITEMATT_NSIZE		= 7,	//	Á¾·ù°¹¼ö.

		ITEMATT_NEAR		= 4,	//	±ÙÁ¢ °ø°Ý.
	};
};

namespace glold_103
{
	enum GLITEM_ATT_103
	{
		ITEMATT_NOTHING		= 0,	//	Âø¿ë¹«±â¾øÀ½.

		ITEMATT_SWORD		= 1,	//	°Ë.
		ITEMATT_BLADE		= 2,	//	µµ.
		ITEMATT_DAGGER		= 3,	//	´Ü°Ë.
		ITEMATT_SPEAR		= 4,	//	Ã¢.
		ITEMATT_STICK		= 5,	//	¸ùµÕÀÌ.
		ITEMATT_BOW			= 6,	//	È°.
		ITEMATT_THROW		= 7,	//	ÅõÃ´.

		ITEMATT_NOCARE		= 8,	//	Å¸ÀÔ »ó°ü ¾ÈÇÔ.	( "GLSKILL" ¿¡¼­ Hand ¹«±â Á¦ÇÑ ¼Ó¼º¿¡¼­ »ç¿ëµÊ. )
		ITEMATT_NSIZE		= 8,	//	Á¾·ù°¹¼ö.

		ITEMATT_NEAR		= 5,	//	±ÙÁ¢ °ø°Ý.
	};
};

namespace glold_108
{
	enum GLITEM_ATT_108
	{
		ITEMATT_NOTHING		= 0,	//	Âø¿ë¹«±â¾øÀ½.

		ITEMATT_SWORD		= 1,	//	°Ë.
		ITEMATT_BLADE		= 2,	//	µµ.
		ITEMATT_SWORDBLADE	= 3,	//	°Ë/µµ. "°Ë/µµ" ´Â ½ºÅ³¿¡¼­ »ç¿ë¹«±â È®ÀÎ½Ã¿¡¸¸ »ç¿ëµÊ.

		ITEMATT_DAGGER		= 4,	//	´Ü°Ë.
		ITEMATT_SPEAR		= 5,	//	Ã¢.
		ITEMATT_STICK		= 6,	//	¸ùµÕÀÌ.
		ITEMATT_GAUNT		= 7,	//	±Ç.
		ITEMATT_BOW			= 8,	//	È°.
		ITEMATT_THROW		= 9,	//	ÅõÃ´.

		ITEMATT_NOCARE		= 10,	//	Å¸ÀÔ »ó°ü ¾ÈÇÔ.	( "GLSKILL" ¿¡¼­ Hand ¹«±â Á¦ÇÑ ¼Ó¼º¿¡¼­ »ç¿ëµÊ. )
		ITEMATT_NSIZE		= 10,	//	Á¾·ù°¹¼ö.

		ITEMATT_NEAR		= 7,	//	±ÙÁ¢ °ø°Ý.
	};
};

enum EMITEMLEVEL
{
	LEVEL_NORMAL	= 0,	//	ÀÏ¹Ý
	LEVEL_RARE		= 1,	//	Áø±ÍÇÑ
	LEVEL_UNIQUE	= 2,	//	À¯ÀÏÇÑ
	LEVEL_INFINITY	= 3,	//	¹«ÇÑ
	LEVEL_FERVOR	= 4,	//	¹é¿­
	
	LEVEL_NSIZE		= 5		//	Á¾·ù°¹¼ö.
};

enum EMITEM_FLAG
{
	TRADE_SALE			= 0x01,	//	»óÁ¡¿¡ ÆÇ¸Å °¡´É.
	TRADE_EXCHANGE		= 0x02,	//	°³ÀÎ°£ ±³È¯ °¡´É.
	TRADE_THROW			= 0x04,	//	ÇÊµå¿¡ ¹ö¸®±â °¡´É.

	TRADE_EVENT_SGL		= 0x08,	//	¿©·¯ ÀÌº¥Æ® ¾ÆÀÌÅÛÁß ÇÑ°³ ÀÌ»ó ¸ø ÁÝ°Ô ÇÏ±â À§ÇÑ.

	ITEM_DISGUISE		= 0x10,	//	ÄÚ½ºÅù.
	ITEM_TIMELMT		= 0x20,	//	½ÃÈ¿¼º.
	
	ITEM_CHANNEL_ALL	= 0x40, //	¸ðµç Ã¼³Î.

	TRADE_GARBAGE		= 0x80, //	ÆÄ¼â °¡´É

	ITEM_FLAG_EX_1		= 0x100,
	ITEM_FLAG_EX_2		= 0x200,
	ITEM_FLAG_EX_3		= 0x400,
	ITEM_FLAG_EX_4		= 0x800,

	TRADE_ALL		= TRADE_SALE|TRADE_EXCHANGE|TRADE_THROW,
};

enum EMITEM_HAND
{
	HAND_RIGHT		= 0x0001,	//	¿À¸¥¼Õ ¿ë.
	HAND_LEFT		= 0x0002,	//	¿Þ¼Õ ¿ë.
	HAND_BOTH		= 0x0003,	//	¿Þ¼Õ, ¿À¸¥¼Õ ¸ðµÎ °¡´É.
};

//	Note : Ä³¸¯ÅÍ ¿¡´Ï¸ÞÀÌ¼Ç Á¦¾î¿Í °ü·ÃÀÌ ÀÖÀ½.
//		Ä³¸¯ÅÍ ¿¡´Ï¸ÞÀÌ¼Ç ¼±ÅÃÇÒ¶§ Âø¿ë ¾ÆÀÌÅÆ¿¡ µû¶ó ¼±ÅÃÀ» ÇÔ.
//
enum GLITEM_ATT
{
	ITEMATT_NOTHING		= 0,	//	Âø¿ë¹«±â¾øÀ½.
	ITEMATT_SWORD		= 1,	//	°Ë.
	ITEMATT_BLADE		= 2,	//	µµ.
	ITEMATT_DAGGER		= 3,	//	´Ü°Ë.
	ITEMATT_SPEAR		= 4,	//	Ã¢.
	ITEMATT_STICK		= 5,	//	¸ùµÕÀÌ.
	ITEMATT_GAUNT		= 6,	//	±Ç.
	ITEMATT_BOW			= 7,	//	È°.
	ITEMATT_THROW		= 8,	//	ÅõÃ´.
	ITEMATT_GUN			= 9,
	ITEMATT_RAILGUN		= 10,
	ITEMATT_PORTALGUN	= 11,
	ITEMATT_SCYTHE		= 12,
	ITEMATT_DUALSPEAR	= 13,
	ITEMATT_SHURIKEN	= 14,

	ITEMATT_NOCARE		= 15,
	ITEMATT_NSIZE		= 15,	//	Á¾·ù°¹¼ö.

	ITEMATT_NEAR		= 6,	//	±ÙÁ¢ °ø°Ý.
};

enum GLITEM_CONST
{
	ITEM_SZNAME		= 65,	//	item ÀÌ¸§ ±æÀÌ Á¦ÇÑ. (NULL) ¹®ÀÚ Æ÷ÇÔ ±æÀÌ.
	ITEM_SZCOMMENT	= 256,	//	item "°£·«¼³¸í" ±æÀÌ Á¦ÇÑ. (NULL) ¹®ÀÚ Æ÷ÇÔ ±æÀÌ.
	ITEM_SKILLS		= 4,	//	"½ºÅ³ Æ÷ÀÎÆ® Áõ°¡Ä¡" °¡ ºÙÀ»¼ö ÀÖ´Â °¹¼ö.
};

enum EMSUIT
{
	SUIT_HEADGEAR		= 0,
	SUIT_UPPER			= 1,
	SUIT_LOWER			= 2,
	SUIT_HAND			= 3,
	SUIT_FOOT			= 4,

	SUIT_HANDHELD		= 5,

	SUIT_NECK			= 6,
	SUIT_WRIST			= 7,

	SUIT_FINGER			= 8,

	SUIT_PET_A			= 9,	// PetData
	SUIT_PET_B			= 10,
	SUIT_VEHICLE		= 11,	// Å»°Í
	
	SUIT_VEHICLE_SKIN		= 12,	// Å»°Í Áß º¸µå ½ºÅ²
	SUIT_VEHICLE_PARTS_A	= 13,	// Å»°Í Áß º¸µå ÆÄÃ÷
	SUIT_VEHICLE_PARTS_B	= 14,
	SUIT_VEHICLE_PARTS_C	= 15,
	SUIT_VEHICLE_PARTS_D	= 16,	// Å»°Í Áß º¸µå ÆÄÃ÷
	SUIT_VEHICLE_PARTS_E	= 17,
	SUIT_VEHICLE_PARTS_F	= 18,
	SUIT_WING				= 19,//add wing
	SUIT_BELT				= 20,//add aura
	SUIT_EARRING			= 21,//add newitem
	SUIT_ACCESSORY			= 22,//add newitem

	SUIT_NSIZE				= 23,
};

//	Note : Âø¿ëÀ§Ä¡.
enum EMSLOT
{
	SLOT_HEADGEAR	= 0,	//	¸Ó¸® ¾µ°Í
	SLOT_UPPER		= 1,	//	»óÃ¼
	SLOT_LOWER		= 2,	//	ÇÏÃ¼
	SLOT_HAND		= 3,	//	¼Õ
	SLOT_FOOT		= 4,	//	¹ß

	SLOT_RHAND		= 5,	//	¿À¸¥¼Õ µµ±¸
	SLOT_LHAND		= 6,	//	¿Þ¼Õ µµ±¸
	
	SLOT_NECK		= 7,	//	¸ñ°ÉÀÌ
	SLOT_WRIST		= 8,	//	¼Õ?E
	SLOT_RFINGER	= 9,	//	¿À¸¥¼Õ ¼Õ°¡?E
	SLOT_LFINGER	= 10,	//	¿Þ¼Õ ¼Õ°¡?E
	SLOT_RHAND_S	= 11,	//	¿À¸¥¼Õ µµ±¸, ±Ø°­ºÎ
	SLOT_LHAND_S	= 12,	//	¿Þ¼Õ µµ±¸, ±Ø°­ºÎ

	SLOT_VEHICLE	= 13,	//  Å»°Í 
	SLOT_WING		= 14,
	SLOT_BELT		= 15,	
	SLOT_REARRING	= 16,
	SLOT_LEARRING	= 17,	
	SLOT_ACCESSORY	= 18,

	SLOT_NSIZE		= 11,   
	SLOT_NSIZE_S	= 13,	
	SLOT_NSIZE_2	= 17,   // Normal Class
	SLOT_NSIZE_S_2	= 19,	// Extreme Class

	SLOT_HOLD		= 19,	// I dont know what the fuck is this 
	SLOT_TSIZE		= 20,   //Max Slot Size
	
	SLOT_WEAR_SIMPLE = 5,	/*character simple, Juver, 2017/10/01 */
};

inline EMSUIT SLOT_2_SUIT ( EMSLOT emSlot )
{
	switch( emSlot )
	{
	case SLOT_HEADGEAR: return SUIT_HEADGEAR;
	case SLOT_UPPER:	return SUIT_UPPER;
	case SLOT_LOWER:	return SUIT_LOWER;
	case SLOT_HAND:		return SUIT_HAND;
	case SLOT_FOOT:		return SUIT_FOOT;

	case SLOT_RHAND:	
	case SLOT_RHAND_S:
	case SLOT_LHAND:	
	case SLOT_LHAND_S:	return SUIT_HANDHELD;

	case SLOT_NECK:		return SUIT_NECK;
	case SLOT_WRIST:	return SUIT_WRIST;
	case SLOT_RFINGER:
	case SLOT_LFINGER:	return SUIT_FINGER;
	
	case SLOT_VEHICLE:	return SUIT_VEHICLE;
	case SLOT_WING:		return SUIT_WING;
	case SLOT_BELT:		return SUIT_BELT;
	case SLOT_REARRING:
	case SLOT_LEARRING:	return SUIT_EARRING;
	case SLOT_ACCESSORY:return SUIT_ACCESSORY;
	
	default:			return SUIT_NSIZE;
	}
}

inline EMPIECECHAR SLOT_2_PIECE ( EMSLOT emSlot )
{
	switch( emSlot )
	{
	case SLOT_HEADGEAR: return PIECE_HEADGEAR;
	case SLOT_UPPER:	return PIECE_UPBODY;
	case SLOT_LOWER:	return PIECE_LOBODY;
	case SLOT_HAND:		return PIECE_GLOVE;
	case SLOT_FOOT:		return PIECE_FOOT;

	case SLOT_RHAND:	
	case SLOT_RHAND_S:	return PIECE_RHAND;
	case SLOT_LHAND:	
	case SLOT_LHAND_S:	return PIECE_LHAND;
	case SLOT_VEHICLE:	return PIECE_VEHICLE;

	case SLOT_NECK:		return PIECE_NECK;
	case SLOT_WRIST:	return PIECE_WRIST;
	case SLOT_RFINGER:
	case SLOT_LFINGER:	return PIECE_RING;
	case SLOT_WING:		return PIECE_WING;
	case SLOT_BELT:		return PIECE_BELT;
	case SLOT_REARRING:	
	case SLOT_LEARRING:	return PIECE_EAR_RING;
	case SLOT_ACCESSORY:return PIECE_ACCESSORY;
	

	default:			return PIECE_SIZE;
	}
}

/*upgrade effect, Juver, 2017/09/01 */
inline EMPIECECHAR SLOT_2_UPGRADEPIECE ( EMSLOT emSlot )
{
	switch( emSlot )
	{
	case SLOT_UPPER:	return PIECE_ENCHANT_UPBODY;
	case SLOT_LOWER:	return PIECE_ENCHANT_LOBODY;
	case SLOT_HAND:		return PIECE_ENCHANT_GLOVE;
	case SLOT_FOOT:		return PIECE_ENCHANT_FOOT;
	default:			return PIECE_SIZE;
	};
}

inline EMSLOT PIECE_2_SLOT ( EMPIECECHAR emPiece )
{
	switch( emPiece )
	{
	case PIECE_HEAD:		return SLOT_HEADGEAR;
	case PIECE_UPBODY:		return SLOT_UPPER;
	case PIECE_LOBODY:		return SLOT_LOWER;
	case PIECE_GLOVE:		return SLOT_HAND;
	case PIECE_RHAND:		return SLOT_RHAND;
	case PIECE_LHAND:		return SLOT_LHAND;
	case PIECE_FOOT:		return SLOT_FOOT;
	case PIECE_VEHICLE:		return SLOT_VEHICLE;
	case PIECE_HAIR:
	case PIECE_HEADGEAR:	return SLOT_TSIZE;

	case PIECE_REV01:
	case PIECE_REV02:
	case PIECE_REV03:
	case PIECE_SIZE:		return SLOT_TSIZE;

	case PIECE_WING:		return SLOT_WING;
	case PIECE_BELT:		return SLOT_BELT;
	case PIECE_ACCESSORY:	return SLOT_ACCESSORY;

	case PIECE_EAR_RING:	return SLOT_REARRING;
	
	default:				return SLOT_TSIZE;
	}
}

enum EMITEM_TYPE
{
	ITEM_SUIT				= 0,

	ITEM_ARROW				= 1,	//	È­»ì.

	ITEM_CURE				= 2,	//	¾àÇ°.
	ITEM_SKILL				= 3,	//	½ºÅ³ ½Àµæ ¼­Àû.
	ITEM_RECALL				= 4,	//	±ÍÈ¯¼­.
	ITEM_KEY				= 5,	//	ÀÎÁõ¼­ ( ¿­¼è ).
	ITEM_GRINDING			= 6,	//	¿¬¸¶Á¦
	ITEM_CHARM				= 7,	//	ºÎÀû.
	ITEM_TICKET				= 8,	//	½ÂÂ÷±Ç.
	ITEM_SKP_RESET			= 9,	//	½ºÅ³ Æ÷ÀÎÆ® ¸®¼Â.
	ITEM_STAT_RESET			= 10,	//	½ºÅÝ Æ÷ÀÎÆ® ¸®¼Â.
	ITEM_SKP_STAT_RESET		= 11,	//	½ºÅ³, ½ºÅÝ Æ÷ÀÎÆ® ¸®¼Â.

	ITEM_BOX				= 12,	//	¼±¹° »óÀÚ.
	ITEM_CLEANSER			= 13,	//	¼¼Å¹Á¦.
	ITEM_LOUDSPEAKER		= 14,	//	È®¼º±â.
	ITEM_FIRECRACKER		= 15,	//	ÆøÁ×.
	ITEM_CHARACTER_CARD		= 16,	//	Ä³¸¯ÅÍ Ãß°¡ Ä«µå.
	ITEM_INVEN_CARD			= 17,	//	ÀÎº¥ È®Àå Ä«µå.
	ITEM_STORAGE_CARD		= 18,	//	Ã¢°í È®Àå Ä«µå.
	ITEM_STORAGE_CONNECT	= 19,	//	Ã¢°í ¿¬°á Ä«µå.
	ITEM_PREMIUMSET			= 20,	//	ÇÁ¸®¹Ì¾ö ¼¼Æ®.
	ITEM_PRIVATEMARKET		= 21,	//	°³ÀÎ»óÁ¡ °³¼³ ±Ç¸®.
	ITEM_RANDOMITEM			= 22,	//	·£´ý ¾ÆÀÌÅÆ.
	ITEM_DISJUNCTION		= 23,	//	ÄÚ½ºÅù ºÐ¸®.
	ITEM_HAIR				= 24,	//	Çì¾î½ºÅ¸ÀÏ º¯°æ.
	ITEM_FACE				= 25,	//	¾ó±¼ º¯°æ.
	ITEM_QITEM				= 26,	//	? ¾ÆÀÌÅÛ.
	ITEM_CD					= 27,	//	CD.
	ITEM_2FRIEND			= 28,	//	Ä£±¸¿¡°Ô.
	ITEM_CLUBCALL			= 29,	//	Å¬·´È£Ãâ.
	ITEM_HAIRSHOP			= 30,	//	Çì¾î˜?ÀÌ¿ë±Ç.
	ITEM_RENAME				= 31,   //  ÀÌ¸§º¯°æ Ä«µå.
	ITEM_HAIR_STYLE			= 32,	//  Çì¾î½ºÅ¸ÀÏ
	ITEM_HAIR_COLOR			= 33,   //  Çì¾îÄÃ·¯
	ITEM_REVIVE				= 34,	//  ±ÍÈ¥ÁÖ
	ITEM_PET_CARD			= 35,	//	Æê Ä«µå	// PetData
	ITEM_PET_FOOD			= 36,	//	Æê ¸ÔÀÌ
	ITEM_PET_RENAME			= 37,	//	ÆÖ ÀÌ¸§º¯°æ
	ITEM_PET_COLOR			= 38,	//	ÆÖ ÄÃ·¯º¯°æ
	ITEM_PET_STYLE			= 39,	//	ÆÖ ½ºÅ¸ÀÏº¯°æ
	ITEM_PET_SKILL			= 40,	//	ÆÖ ½ºÅ³
	ITEM_SMS				= 41,	//	SMS¹®ÀÚ ¹ß¼Û
	ITEM_PET_REVIVE			= 42,	//	ÆÖ ºÎÈ°Ä«µå
	ITEM_ANTI_DISAPPEAR 	= 43,	//	¼Ò¹æÁÖ(¼Ò¸ê¹æÁö)
	ITEM_REMODEL			= 44,	//	°³Á¶ ±â´É
	ITEM_VEHICLE			= 45,	//	Å»°Í
	ITEM_VEHICLE_OIL		= 46,	//  Å»°Í ±â¸§
	ITEM_VIETNAM_ITEMGET	= 47,	//  º£Æ®³² Å½´Ð ¹æÁö ¾ÆÀÌÅÛ È¹µæ
	ITEM_VIETNAM_EXPGET		= 48,	//  º£Æ®³² Å½´Ð ¹æÁö °æÇèÄ¡ È¹µæ	
	ITEM_GENDER_CHANGE		= 49,	//  ¼ºº° º¯°æ Ä«µå 
	ITEM_GARBAGE_CARD		= 50,	//	ÈÞÁöÅë Ä«µå	
	ITEM_TELEPORT_CARD		= 51,	//	¼ÒÈ¯¼­	
	ITEM_PET_SKIN_PACK  	= 52,	//  Æê ½ºÅ² ÆÑ
	ITEM_FACE_STYLE			= 53,	//	¾ó±¼½ºÅ¸ÀÏ
	ITEM_TAXI_CARD			= 54,	//	ÅÃ½ÃÄ«µå
	ITEM_MATERIALS			= 55,	//	Àç·á¾ÆÀÌÅÛ
	ITEM_NPC_RECALL			= 56,	//	NPC¼ÒÈ¯ Ä«µå
	ITEM_BULLET				= 57,	/*gun-bullet logic, Juver, 2017/05/27 */
	ITEM_FOOD				= 58,	/*itemfood system, Juver, 2017/05/26 */
	ITEM_CARD_DUALPETSKILL	= 59,	/*dual pet skill, Juver, 2017/12/29 */
	ITEM_BEADS_STRENGTHEN	= 60,
	ITEM_BEADS_RELAXANT		= 61,
	ITEM_CARD_BIKECOLOR		= 62,	/*bike color , Juver, 2017/11/12 */
	ITEM_CARD_BIKEBOOST		= 63,	/*vehicle booster system, Juver, 2017/08/10 */
	ITEM_OBLIVION_NEW		= 64,
	ITEM_COSTUME_COLOR		= 65,	/*item color, Juver, 2018/01/10 */
	ITEM_CARD_MAILBOX		= 66,
	ITEM_CARD_FOODUNLOCK	= 67,	/*itemfood system, Juver, 2017/05/26 */
	ITEM_POINTCARD_A		= 68,
	ITEM_POINTCARD_B		= 69,
	ITEM_CRAFTING_BOOK		= 70,
	ITEM_RANDOM_OPTION_CARD	= 71,	/*rv card, Juver, 2017/11/25 */
	ITEM_NONDROP_CARD		= 72,	/*nondrop card, Juver, 2017/11/26 */
	ITEM_RESET_CRAFTING			= 73,
	ITEM_PERSONAL_STORE_SEARCH	= 74,
	ITEM_CHANGE_SCALE_CARD	= 75,	/*change scale card, Juver, 2018/01/03 */
	ITEM_WRAPPER			= 76,	/*item wrapper, Juver, 2018/01/11 */
	ITEM_WRAPPER_BOX		= 77,	/*item wrapper, Juver, 2018/01/11 */
	ITEM_CHANGE_SCHOOL		= 78,	/*change school card, Juver, 2018/01/12 */
	ITEM_EQUIPMENT_LOCK_ENABLE	= 79,	/*equipment lock, Juver, 2018/01/13 */
	ITEM_EQUIPMENT_LOCK_RECOVER	= 80,	/*equipment lock, Juver, 2018/01/13 */
	ITEM_TRANSFER_CARD		= 81,	/*item transfer card, Juver, 2018/01/18 */
	ITEM_CARD_CAR_COLOR		= 82,	/* car, cart color, Juver, 2018/02/14 */
	ITEM_CARD_VEHICLE_BOOST	= 83,	/* booster all vehicle, Juver, 2018/02/14 */
	
	ITEM_SEALED_CARD		= 84,		// add sealed card

	ITEM_NSIZE				= 85,	//	Á¾·ù°¹¼ö.
};

EMITEM_TYPE EXITEM_TO_ITEM( EMEXITEM_TYPE _emTYPE );

enum EMITEM_DRUG
{
	ITEM_DRUG_NONE			= 0,
	ITEM_DRUG_HP			= 1,	//	Ã¤·Â
	ITEM_DRUG_MP			= 2,	//	±â·Â
	ITEM_DRUG_SP			= 3,	//	È°·Â

	ITEM_DRUG_HP_MP			= 4,	//	Ã¼·Â+±â·Â
	ITEM_DRUG_MP_SP			= 5,	//	Ã¼·Â+È°·Â
	ITEM_DRUG_HP_MP_SP		= 6,	//	Ã¼·Â+±â·Â+È°·Â
	
	ITEM_DRUG_CURE			= 7,	//	»óÅÂ ÀÌ»ó Ä¡·á.

	ITEM_DRUG_CALL_SCHOOL	= 8,	//	ÇÐ±³±ÍÈ¯.
	ITEM_DRUG_CALL_REGEN	= 9,	//	½ÃÀÛ±ÍÈ¯.
	ITEM_DRUG_CALL_LASTCALL	= 10,	//	Á÷Àü±ÍÈ¯.
	ITEM_DRUG_CALL_REVIVE	= 11,	//	ºÎÈ°±â´É.

	ITEM_DRUG_HP_CURE		= 12,	// Ã¼·Â+ÀÌ»óÄ¡·á
	ITEM_DRUG_HP_MP_SP_CURE	= 13,	// Ã¼·Â+±â·Â+È°·Â+ÀÌ»óÄ¡·á
	ITEM_DRUG_CALL_TELEPORT	= 14,	// Æ¯Á¤°ø°£ÀÌµ¿

	ITEM_DRUG_CP			= 15,	/*combatpoint logic, Juver, 2017/05/27 */

	ITEM_DRUG_SIZE			= 16
};

enum EMITEM_ADDON
{
	EMADD_NONE		= 0,
	EMADD_HITRATE	= 1,	//	¸íÁßÀ²
	EMADD_AVOIDRATE	= 2,	//	È¸ÇÇÀ².
	
	EMADD_DAMAGE	= 3,	//	°ø°Ý·Â.
	EMADD_DEFENSE	= 4,	//	¹æ¾î·Â.

	EMADD_HP		= 5,	//	Ã¤·Â Áõ°¡.
	EMADD_MP		= 6,	//	¸¶³ª Áõ°¡.
	EMADD_SP		= 7,	//	½ºÅ×¹Ì³ª Áõ°¡.

	EMADD_STATS_POW	= 8,	//	Èû.
	EMADD_STATS_STR	= 9,	//	Ã¼·Â.
	EMADD_STATS_SPI	= 10,	//	Á¤½Å.
	EMADD_STATS_DEX	= 11,	//	¹ÎÃ¸.
	EMADD_STATS_INT	= 12,	//	Áö¼º.
	EMADD_STATS_STA	= 13,	//	±Ù·Â.

	EMADD_PA		= 14,	//	°ÝÅõÄ¡.
	EMADD_SA		= 15,	//	»ç°ÝÄ¡.
	EMADD_MA		= 16,	//	¸¶·ÂÄ¡.

	EMADD_SIZE		= 17,
};

enum EMITEM_VAR
{
	EMVAR_NONE			= 0,
	EMVAR_HP			= 1,
	EMVAR_MP			= 2,
	EMVAR_SP			= 3,
	EMVAR_AP			= 4,
	EMVAR_MOVE_SPEED	= 5,
	EMVAR_ATTACK_SPEED	= 6,
	EMVAR_CRITICAL_RATE	= 7,
	EMVAR_CRUSHING_BLOW	= 8, 

	EMVAR_SIZE			= 9,
};

enum EMITEM_QUESTION
{
	QUESTION_NONE			= 0,
	QUESTION_SPEED_UP		= 1,
	QUESTION_CRAZY			= 2,
	QUESTION_ATTACK_UP		= 3,
	QUESTION_EXP_UP			= 4,
	QUESTION_EXP_GET		= 5,
	QUESTION_LUCKY			= 6,
	QUESTION_BOMB			= 7,
	QUESTION_MOBGEN			= 8,

	QUESTION_SPEED_UP_M		= 9,
	QUESTION_MADNESS		= 10,
	QUESTION_ATTACK_UP_M	= 11,
	QUESTION_HEAL			= 12,

	QUESTION_SIZE			= 13
};

enum EMRANDOM_OPT
{
	EMR_OPT_NULL			= 0,
	EMR_OPT_DAMAGE			= 1,	//	°ø°Ý·Â.
	EMR_OPT_DEFENSE			= 2,	//	¹æ¾ûÓÂ.

	EMR_OPT_HITRATE			= 3,	//	¸úÝßÀ².
	EMR_OPT_AVOIDRATE		= 4,	//	È¸ÇÇÀ².

	EMR_OPT_HP				= 5,	//	hp Áõ°¡.
	EMR_OPT_MP				= 6,	//	mp Áõ°¡.
	EMR_OPT_SP				= 7,	//	sp Áõ°¡.

	EMR_OPT_HP_INC			= 8,	//	hp Áõ°¡À².
	EMR_OPT_MP_INC			= 9,	//	mp Áõ°¡À².
	EMR_OPT_SP_INC			= 10,	//	sp Áõ°¡À².
	EMR_OPT_HMS_INC			= 11,	//	hp, mp, sp Áõ°¡À².

	EMR_OPT_GRIND_DAMAGE	= 12,	//	°ø°Ý·Â ¿¬¸¶.
	EMR_OPT_GRIND_DEFENSE	= 13,	//	¹æ¾ûÓÂ ¿¬¸¶.

	EMR_OPT_RANGE			= 14,	//	°ø°Ý ¿µ¿ª.
	EMR_OPT_DIS_SP			= 15,	//	sp ¼Ò¸ð·®.
	EMR_OPT_RESIST			= 16,	//	ÀúÇ×.

	EMR_OPT_MOVE_SPEED		= 17,	// ÀÌµ¿¼Óµµ Áõ°¡
	
	// Add latest Random Values
	// Latest RVs'
	EMR_OPT_ATTACK_VOL		= 18,	// Attack
	EMR_OPT_DEFENSE_VOL		= 19,	// Defense
	EMR_OPT_HIT_VOL			= 20,	// Hit Rate
	EMR_OPT_AVOID_VOL		= 21,	// Avoid Rate
	EMR_OPT_POWER			= 22,	// Power
	EMR_OPT_VITALITY		= 23,	// Vitality
	EMR_OPT_SPIRIT			= 24,	// Spirit
	EMR_OPT_DEXTERITY		= 25,	// Dexterity
	EMR_OPT_STAMINA			= 26,	// Stamina
	EMR_OPT_MELEE			= 27,	// Melee
	EMR_OPT_SHOOTING		= 28,	// Missile
	EMR_OPT_ENERGY			= 29,	// Energy
	EMR_OPT_HP_REC			= 30,	// HP Potion Recover Increase Amount
	EMR_OPT_MP_REC			= 31,	// MP Potion Recover Increase Amount
	EMR_OPT_SP_REC			= 32,	// SP Potion Recover Increase Amount

	EMR_OPT_SIZE			= 33
};

enum EMCOOL_TYPE
{
	EMCOOL_ITEMID	= 0,	// MID/SID
	EMCOOL_ITEMTYPE	= 1,	// ¾ÆÀÌÅÛ Å¸ÀÔ
	EMCOOL_SIZE		= 2,	// »çÀÌÁî
};

struct SRANDOM_OPT
{
	WORD	wTYPE;
	short	nVALUE;

	SRANDOM_OPT()
		: wTYPE( EMR_OPT_NULL )
		, nVALUE( 0 )
	{
	}

	float get_float()	{ return nVALUE * 0.01f; }
	float get_int()		{ return nVALUE; }
};

#define USAGE_RANDOM_OPT_SE
#ifdef USAGE_RANDOM_OPT_SE
//#ifdef DAUMTESTPARAM	// ÇÑ±¹ Å×¼·¿¡¼­¸¸ 2Â÷ ·£´ý ¿É¼Ç ÆÄÀÏ »ç¿ë ( ÁØÇõ )
	struct SRANDOM_OPT_SECTION
	{
		float	fRATE;	// ±¸°£º° ¹ß»ý È®·ü
		float	fHIGH;	// °ª ÃÖ´ë
		float	fLOW;	// °ª ÃÖ¼Ò

		SRANDOM_OPT_SECTION()
			: fRATE( 0.0f )
			, fHIGH( 0.0f )
			, fLOW( 0.0f )
		{
		}
	};

	struct SRANDOM_OPT_SET
	{
		float					fRATE;	// ¼³Á¤µÈ ¿É¼Ç´ç ¹ß»ý È®·ü
		WORD					wTYPE;	// ¿É¼Ç Á¾·ù
		WORD					wSECT;	// ±¸°£ ¼ö
		SRANDOM_OPT_SECTION*	pSECT;	// ±¸°£

		SRANDOM_OPT_SET()
			: fRATE( 0.0f )
			, wTYPE( EMR_OPT_NULL )
			, wSECT( 0 )
			, pSECT( NULL )
		{
		}

		~SRANDOM_OPT_SET()
		{
			SAFE_DELETE_ARRAY( pSECT );
		}
	};

	struct SRANDOM_GEN
	{
		enum { MAX_SET = 10, MAX_OPT = 4 };

		float			fRATE;				// ·£´ý ¿É¼Ç ¹ß»ý È®·ü
		DWORD			dwSET_NUM;			// ¼³Á¤µÈ ·£´ý ¿É¼Ç °¹¼ö
		float			fD_point;			// °³Á¶ ½Ã ¼Ò¸êÇÒ ¼ö ÀÖ´Â È®·ü
		float			fS_value;			// °³Á¶ ½Ã ÇÊ¿äÇÑ ±Ý¾× ¹èÀ² ( ¾ÆÀÌÅÛ °¡°Ý¿¡ °öÇÔ )
		SRANDOM_OPT_SET	sSET[ MAX_SET ];	// ¼³Á¤µÈ ¿É¼Ç ( Ã³À½ »ý¼º ½Ã »ç¿ë )
		SRANDOM_OPT_SET	sSETR[ MAX_SET ];	// ¼³Á¤µÈ ¿É¼Ç ( ÀÌÈÄ °³Á¶ ½Ã »ç¿ë )

		SRANDOM_GEN()
			: fRATE( 0.0f )
			, dwSET_NUM( 0 )
			, fD_point( 0.0f )
			, fS_value( 1.0f )
		{
		}
	};
	#undef USAGE_RANDOM_OPT_SE
#else
	struct SRANDOM_OPT_SET
	{
		float	fRATE;	// ¼³Á¤µÈ ¿É¼Ç´ç ¹ß»ý È®À²
		WORD	wTYPE;	// ¿É¼Ç Á¾·ù
		float	fLOW;	// °ª ÃÖ´ë
		float	fHIGH;	// °ª ÃÖ¼Ò

		SRANDOM_OPT_SET()
            : fRATE( 0 )
            , wTYPE( EMR_OPT_NULL )
			, fLOW( 0 )
			, fHIGH( 0 )
		{
		}
	};

	struct SRANDOM_GEN
	{
		enum { MAX_SET = 10, MAX_OPT = 4 };

		float			fRATE;			// ·£´ý ¿É¼Ç ¹ß»ý È®À²
		DWORD			dwSET_NUM;		// ¼³Á¤µÈ ·£´ý ¿É¼Ç °¹¼ö
		SRANDOM_OPT_SET	sSET[MAX_SET];	// ¼³Á¤µÈ ¿É¼Ç

		float			fD_point;		// DAUMTESTPARAM ¾Æ´Ï¸é ¾²ÀÌÁö ¾ÊÀ½
		float			fS_value;		// DAUMTESTPARAM ¾Æ´Ï¸é ¾²ÀÌÁö ¾ÊÀ½

		SRANDOM_GEN()
			: fRATE( 0 )
			, dwSET_NUM( 0 )

			, fD_point( 0.0f )			// DAUMTESTPARAM ¾Æ´Ï¸é ¾²ÀÌÁö ¾ÊÀ½
			, fS_value( 1.0f )			// DAUMTESTPARAM ¾Æ´Ï¸é ¾²ÀÌÁö ¾ÊÀ½
		{
		}
	};
#endif

struct SRANDOM_DATA
{
	enum { NAME_LEN = 64 };
	char			szNAME[ NAME_LEN ];
	SRANDOM_GEN*	pSET;

	SRANDOM_DATA()
		: pSET( NULL )
	{
		memset( szNAME, 0, sizeof(char) * NAME_LEN );
	}
};

struct SRANDOM_DATA_OPER
{
	bool operator() ( const SRANDOM_DATA &lvalue, const SRANDOM_DATA &rvalue )
	{
		return strcmp(lvalue.szNAME,rvalue.szNAME)<0;
	}

	bool operator() ( const SRANDOM_DATA &lvalue, const char *szNAME )
	{
		return strcmp(lvalue.szNAME,szNAME)<0;
	}

	bool operator() ( const char *szNAME, const SRANDOM_DATA &rvalue )
	{
		return strcmp(szNAME,rvalue.szNAME)<0;
	}
};

enum EMGRINDING_CLASS
{
	EMGRINDING_CLASS_ARM	= 0,
	EMGRINDING_CLASS_CLOTH	= 1,

	EMGRINDING_CLASS_SIZE	= 2,
};

enum EMGRINDING_TYPE
{
	EMGRINDING_NONE				= 0,

	EMGRINDING_DAMAGE			= 1,
	EMGRINDING_DEFENSE			= 2,

	EMGRINDING_RESIST_FIRE		= 3,
	EMGRINDING_RESIST_ICE		= 4,
	EMGRINDING_RESIST_ELEC		= 5,
	EMGRINDING_RESIST_POISON	= 6,
	EMGRINDING_RESIST_SPIRIT	= 7,
	
	EMGRINDING_NSIZE			= 8
};

enum EMGRINDING_LEVEL
{
	EMGRINDING_LEVEL_NORMAL		= 0,
	EMGRINDING_LEVEL_HIGH		= 1,
	EMGRINDING_LEVEL_TOP		= 2,

	EMGRINDING_LEVEL_SIZE		= 3,
};

enum EMGRINDING_RS_FLAGS
{
	EMGRINDING_RS_FIRE		= 0x01,
	EMGRINDING_RS_ICE		= 0x02,
	EMGRINDING_RS_ELECTRIC	= 0x04,
	EMGRINDING_RS_POISON	= 0x08,
	EMGRINDING_RS_SPIRIT	= 0x10,

	EMGRINDING_RS_NSIZE		= 5,
	EMGRINDING_NO			= 2,
	EMGRINDING_RS_ALL		= (EMGRINDING_RS_FIRE|EMGRINDING_RS_ICE|EMGRINDING_RS_ELECTRIC|EMGRINDING_RS_POISON|EMGRINDING_RS_SPIRIT)
};

enum EMGRINDING_RS_INDEX
{
	EMGRINDING_RS_FIRE_INDEX		= 0,
	EMGRINDING_RS_ICE_INDEX			= 1,
	EMGRINDING_RS_ELECTRIC_INDEX	= 2,
	EMGRINDING_RS_POISON_INDEX		= 3,
	EMGRINDING_RS_SPIRIT_INDEX		= 4,

	EMGRINDING_RS_INDEX_NSIZE		= 5
};

EMGRINDING_RS_INDEX	GrindRsClassToIndex ( const EMGRINDING_RS_FLAGS emClass );
EMGRINDING_RS_FLAGS	GrindIndexToRsClass ( const EMGRINDING_RS_INDEX	emIndex );

struct SGRIND
{
	EMGRINDING_TYPE	emTYPE;

	DWORD			dwRESIST;
	int				nMin;
	int				nMax;

	SGRIND () :
		emTYPE(EMGRINDING_NONE),

		dwRESIST(NULL),
		nMin(0),
		nMax(0)
	{
	}
};

struct ITEM_COOLTIME
{
	enum { VERSION = 0x0001 };

	DWORD		dwID;		//	»ç¿ëÇÑ ¾ÆÀÌÅÛ ID
	DWORD		dwCoolID;	//	ÄðÅ¸ÀÓ ID ( Å¸ÀÔ¿¡ µû¶ó ´Ù¸§ ) 
	__time64_t	tUseTime;	//	»ç¿ë½Ã°£
	__time64_t	tCoolTime;	//	»ç¿ë°¡´ÉÇÑ ½Ã°£

	ITEM_COOLTIME()
		: dwID( 0 )
		, dwCoolID ( 0 )
		, tUseTime ( 0 )
		, tCoolTime ( 0 )
	{
	}
};


namespace COMMENT
{
	extern std::string ITEMLEVEL[LEVEL_NSIZE];
	extern std::string ITEMTYPE[ITEM_NSIZE];

	extern std::string ITEMSUIT[SUIT_NSIZE];
	extern std::string ITEMATTACK[ITEMATT_NSIZE+1];

	extern std::string ITEMDRUG[ITEM_DRUG_SIZE];

	extern std::string ITEMADDON[EMADD_SIZE];
	
	extern std::string ITEMVAR[EMVAR_SIZE];

	extern std::string ITEMVOL[EMVAR_SIZE]; // by °æ´ë
	extern std::string ITEM_QUE_TYPE[QUESTION_SIZE]; // Question Item
	extern std::string ITEM_QUE_VAR1[QUESTION_SIZE];
	extern std::string ITEM_QUE_VAR2[QUESTION_SIZE];

	extern float ITEMVAR_SCALE[EMVAR_SIZE];
	bool IsITEMVAR_SCALE ( EMITEM_VAR emITEM_VAR );

	extern std::string GRINDING_TYPE[EMGRINDING_NSIZE];
	extern std::string GRINDING_RESIST[EMGRINDING_RS_NSIZE];
	extern std::string GRINDING_LEVEL[EMGRINDING_LEVEL_SIZE];
	extern std::string GRINDING_CLASS[EMGRINDING_CLASS_SIZE];

	extern std::string ITEM_RANDOM_OPT[EMR_OPT_SIZE];

	extern DWORD	ITEMCOLOR[LEVEL_NSIZE];

	extern std::string COOLTYPE[EMCOOL_SIZE];

	extern std::string ITEMSLOT_CHAR[SLOT_NSIZE_S_2];
};

#endif // GLITEMDEF_H_
