#ifndef GLITEMDEF_EX_H_
#define GLITEMDEF_EX_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//official item type used for loading official item
enum EMEXITEM_TYPE
{
	EXITEM_SUIT					= 0,
	EXITEM_ARROW				= 1,	//	ȭ��.
	EXITEM_CURE					= 2,	//	��ǰ.
	EXITEM_SKILL				= 3,	//	��ų ���� ����.
	EXITEM_RECALL				= 4,	//	��ȯ��.
	EXITEM_KEY					= 5,	//	������ ( ���� ).
	EXITEM_GRINDING				= 6,	//	������
	EXITEM_CHARM				= 7,	//	����.
	EXITEM_TICKET				= 8,	//	������.
	EXITEM_SKP_RESET			= 9,	//	��ų ����Ʈ ����.
	EXITEM_STAT_RESET			= 10,	//	���� ����Ʈ ����.
	EXITEM_SKP_STAT_RESET		= 11,	//	��ų, ���� ����Ʈ ����.
	EXITEM_BOX					= 12,	//	���� ����.
	EXITEM_CLEANSER				= 13,	//	��Ź��.
	EXITEM_LOUDSPEAKER			= 14,	//	Ȯ����.
	EXITEM_FIRECRACKER			= 15,	//	����.
	EXITEM_CHARACTER_CARD		= 16,	//	ĳ���� �߰� ī��.
	EXITEM_INVEN_CARD			= 17,	//	�κ� Ȯ�� ī��.
	EXITEM_STORAGE_CARD			= 18,	//	â�� Ȯ�� ī��.
	EXITEM_STORAGE_CONNECT		= 19,	//	â�� ���� ī��.
	EXITEM_PREMIUMSET			= 20,	//	�����̾� ��Ʈ.
	EXITEM_PRIVATEMARKET		= 21,	//	���λ��� ���� �Ǹ�.
	EXITEM_RANDOMITEM			= 22,	//	���� ������.
	EXITEM_DISJUNCTION			= 23,	//	�ڽ��� �и�.
	EXITEM_HAIR					= 24,	//	��Ÿ�� ����.
	EXITEM_FACE					= 25,	//	�� ����.
	EXITEM_QITEM				= 26,	//	? ������.
	EXITEM_CD					= 27,	//	CD.
	EXITEM_2FRIEND				= 28,	//	ģ������.
	EXITEM_CLUBCALL				= 29,	//	Ŭ��ȣ��.
	EXITEM_HAIRSHOP				= 30,	//	���� �̿��.
	EXITEM_RENAME				= 31,   //  �̸����� ī��.
	EXITEM_HAIR_STYLE			= 32,	//  ��Ÿ��
	EXITEM_HAIR_COLOR			= 33,   //  ����÷�
	EXITEM_REVIVE				= 34,	//  ��ȥ��
	EXITEM_PET_CARD				= 35,	//	�� ī��	// PetData
	EXITEM_PET_FOOD				= 36,	//	�� ����
	EXITEM_PET_RENAME			= 37,	//	�� �̸�����
	EXITEM_PET_COLOR			= 38,	//	�� �÷�����
	EXITEM_PET_STYLE			= 39,	//	�� ��Ÿ�Ϻ���
	EXITEM_PET_SKILL			= 40,	//	�� ��ų
	EXITEM_SMS					= 41,	//	SMS���� �߼�
	EXITEM_PET_REVIVE			= 42,	//	�� ��Ȱī��
	EXITEM_ANTI_DISAPPEAR 		= 43,	//	�ҹ���(�Ҹ����)
	EXITEM_REMODEL				= 44,	//	���� ���
	EXITEM_VEHICLE				= 45,	//	Ż��
	EXITEM_VEHICLE_OIL			= 46,	//  Ż�� �⸧
	EXITEM_VIETNAM_ITEMGET		= 47,	//  ��Ʈ�� Ž�� ���� ������ ȹ��
	EXITEM_VIETNAM_EXPGET		= 48,	//  ��Ʈ�� Ž�� ���� ����ġ ȹ��	
	EXITEM_GENDER_CHANGE		= 49,	//  ���� ���� ī�� 
	EXITEM_GARBAGE_CARD			= 50,	//	������ ī��	
	EXITEM_TELEPORT_CARD		= 51,	//	��ȯ��	
	EXITEM_PET_SKIN_PACK		= 52,	//  �� ��Ų ��
	EXITEM_FACE_STYLE			= 53,	//	�󱼽�Ÿ��
	EXITEM_TAXI_CARD			= 54,	//	�ý�ī��
	EXITEM_MATERIALS			= 55,	//	��������
	EXITEM_NPC_RECALL			= 56,	//	NPC��ȯ ī��
	EXITEM_BULLET				= 57,
	EXITEM_FOOD					= 58,
	EXITEM_CARD_DUALPETSKILL	= 59,
	EXITEM_BEADS_STRENGTHEN		= 60,
	EXITEM_BEADS_RELAXANT		= 61,
	EXITEM_CARD_BIKECOLOR		= 62,
	EXITEM_CARD_BIKEBOOST		= 63,
	EXITEM_OBLIVION_NEW			= 64,
	EXITEM_COSTUME_COLOR		= 65,
	EXITEM_CARD_MAILBOX			= 66,
	EXITEM_POINTCARD_A			= 67,
	EXITEM_POINTCARD_B			= 68,
	EXITEM_CRAFTING_BOOK		= 69,
	EXITEM_RESET_CRAFTING			= 70,
	EXITEM_PERSONAL_STORE_SEARCH	= 71,

	EXITEM_NSIZE				= 72,	//	��������.
};

#endif // GLITEMDEF_EX_H_
