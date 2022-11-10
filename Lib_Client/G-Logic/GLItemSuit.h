#ifndef GLITEM_SUIT_H_
#define GLITEM_SUIT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../Lib_Engine/Common/BaseStream.h"
#include "../../Lib_Engine/Common/StringFile.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/Common/STRINGUTILS.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"

#include "./GLItemDef.h"
#include "./GLCharDefine.h"


namespace ITEM
{
	GLITEM_ATT assign_att ( glold_102::GLITEM_ATT_102 emOld );
	GLITEM_ATT assign_att ( glold_103::GLITEM_ATT_103 emOld );
	GLITEM_ATT assign_att ( glold_108::GLITEM_ATT_108 emOld );

	struct SADDON
	{
		EMITEM_ADDON	emTYPE;		//	���� Ÿ��.
		int				nVALUE;		//	���� ��.

		SADDON ()
			: emTYPE(EMADD_NONE)
			, nVALUE(0)
		{

		}
	};

	struct SVAR
	{
		EMITEM_VAR		emTYPE;		//	���� Ÿ��.
		float			fVariate;	//	���� ��.

		SVAR ()
			: emTYPE(EMVAR_NONE)
			, fVariate(0.0f)
		{
		}
	};

	struct SVOL
	{
		EMITEM_VAR	emTYPE;		//	���� Ÿ��.
		float		fVolume;	//	���� ��.

		SVOL ()
			: emTYPE(EMVAR_NONE)
			, fVolume(0)
		{
		}
	};

	struct SSATE_BLOW_100
	{
		EMSTATE_BLOW	emTYPE;		//	���� Ÿ��.
		float			fRATE;		//	�߻� Ȯ��.
		float			fLIFE;		//	���� �ð�.
		float			fVALUE;		//	���� ��.
	};

	struct SSATE_BLOW
	{
		EMSTATE_BLOW	emTYPE;		//	���� Ÿ��.
		float			fRATE;		//	�߻� Ȯ��.
		float			fLIFE;		//	���� �ð�.
		float			fVAR1;		//	���� �� 1.
		float			fVAR2;		//	���� �� 2.

		SSATE_BLOW ()
			: emTYPE(EMBLOW_NONE)
			, fRATE(0.0f)
			, fLIFE(0.0f)
			, fVAR1(0.0f)
			, fVAR2(0.0f)
		{
		}
	};

	struct SSUIT_100
	{
		enum { ADDON_SIZE = 4 };

		EMSUIT		emSuit;						//	������ ���� Ÿ��.
		BOOL		bBothHand;					//	��� ��� ��������.
		EMITEM_HAND	emHand;						//	���� �� ��ġ.

		glold_102::GLITEM_ATT_102	emAttack;	//	���ݼӼ�.
		WORD		wAttRange;					//	���� ���� �Ÿ�.

		short		nHitRate;					//	������. ( +/- ) (%)
		short		nAvoidRate;					//	ȸ����. ( +/- ) (%)

		GLPADATA	gdDamage;					//	�����. ( +/- )
		short		nDefense;					//	���. ( +/- )

		SRESIST		sResist;					//	���װ�.

		WORD		wReModelNum;				//	���� ���� Ƚ��.		( '0' ���� �Ұ� )

		//	Ư�� �ΰ� ȿ����.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SSATE_BLOW_100	sBLOW;					//	���� �̻� ȿ��.
	};

	struct SSUIT_101
	{
		enum { ADDON_SIZE = 4 };

		EMSUIT		emSuit;						//	������ ���� Ÿ��.
		BOOL		bBothHand;					//	��� ��� ��������.
		EMITEM_HAND	emHand;						//	���� �� ��ġ.

		glold_102::GLITEM_ATT_102	emAttack;	//	���ݼӼ�.
		WORD		wAttRange;					//	���� ���� �Ÿ�.

		short		nHitRate;					//	������. ( +/- ) (%)
		short		nAvoidRate;					//	ȸ����. ( +/- ) (%)

		GLPADATA	gdDamage;					//	�����. ( +/- )
		short		nDefense;					//	���. ( +/- )

		SRESIST		sResist;					//	���װ�.

		WORD		wReModelNum;				//	���� ���� Ƚ��.		( '0' ���� �Ұ� )

		//	Ư�� �ΰ� ȿ����.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SSATE_BLOW	sBLOW;						//	���� �̻� ȿ��.
	};

	struct SSUIT_102
	{
		enum { ADDON_SIZE = 4 };
		EMSUIT		emSuit;						//	������ ���� Ÿ��.
		bool		bBothHand;					//	��� ��� ��������.
		bool		bBig;						//	����.
		EMITEM_HAND	emHand;						//	���� �� ��ġ.

		glold_102::GLITEM_ATT_102	emAttack;	//	���ݼӼ�.
		WORD		wAttRange;					//	���� ���� �Ÿ�.
		WORD		wReqSP;						//	���ݽ� �ʿ��� SP.

		short		nHitRate;					//	������. ( +/- ) (%)
		short		nAvoidRate;					//	ȸ����. ( +/- ) (%)

		GLPADATA	gdDamage;					//	�����. ( +/- )
		short		nDefense;					//	���. ( +/- )

		SRESIST		sResist;					//	���װ�.

		WORD		wReModelNum;				//	���� ���� Ƚ��.		( '0' ���� �Ұ� )

		//	Ư�� �ΰ� ȿ����.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SSATE_BLOW	sBLOW;						//	���� �̻� ȿ��.
	};

	struct SSUIT_103
	{
		enum { ADDON_SIZE = 4 };

		EMSUIT		emSuit;						//	������ ���� Ÿ��.
		bool		bBothHand;					//	��� ��� ��������.
		bool		bBig;						//	����.
		EMITEM_HAND	emHand;						//	���� �� ��ġ.

		glold_103::GLITEM_ATT_103	emAttack;	//	���ݼӼ�.
		WORD		wAttRange;					//	���� ���� �Ÿ�.
		WORD		wReqSP;						//	���ݽ� �ʿ��� SP.

		short		nHitRate;					//	������. ( +/- ) (%)
		short		nAvoidRate;					//	ȸ����. ( +/- ) (%)

		GLPADATA	gdDamage;					//	�����. ( +/- )
		short		nDefense;					//	���. ( +/- )

		SRESIST		sResist;					//	���װ�.

		WORD		wReModelNum;				//	���� ���� Ƚ��.		( '0' ���� �Ұ� )

		//	Ư�� �ΰ� ȿ����.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SSATE_BLOW	sBLOW;						//	���� �̻� ȿ��.
	};

	struct SSUIT_104
	{
		enum { ADDON_SIZE = 4 };
		EMSUIT		emSuit;
		bool		bBothHand;
		bool		bBig;
		EMITEM_HAND	emHand;

		glold_108::GLITEM_ATT_108	emAttack;
		WORD		wAttRange;
		WORD		wReqSP;

		short		nHitRate;
		short		nAvoidRate;

		GLPADATA	gdDamage;
		short		nDefense;

		SRESIST_101	sResist;

		WORD		wReModelNum;

		SADDON		sADDON[ADDON_SIZE];
		SVAR		sVARIATE;
		SSATE_BLOW	sBLOW;
	};

	struct SSUIT_105
	{
		enum { ADDON_SIZE = 4 };
		EMSUIT		emSuit;
		bool		bBothHand;
		bool		bBig;
		EMITEM_HAND	emHand;

		glold_108::GLITEM_ATT_108	emAttack;
		WORD		wAttRange;
		WORD		wReqSP;

		short		nHitRate;
		short		nAvoidRate;

		GLPADATA	gdDamage;
		short		nDefense;

		SRESIST		sResist;

		WORD		wReModelNum;				//	���� ���� Ƚ��.		( '0' ���� �Ұ� )

		//	Ư�� �ΰ� ȿ����.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SSATE_BLOW	sBLOW;						//	���� �̻� ȿ��.
	};

	struct SSUIT_106
	{
		enum { ADDON_SIZE = 4 };

		EMSUIT		emSuit;						//	������ ���� Ÿ��.
		DWORD		dwHAND;						//	�� ���� �Ӽ�.
		EMITEM_HAND	emHand;						//	���� �� ��ġ.

		glold_108::GLITEM_ATT_108	emAttack;	//	���ݼӼ�.
		WORD		wAttRange;					//	���� ���� �Ÿ�.
		WORD		wReqSP;						//	���ݽ� �ʿ��� SP.

		short		nHitRate;					//	������. ( +/- ) (%)
		short		nAvoidRate;					//	ȸ����. ( +/- ) (%)

		GLPADATA	gdDamage;					//	�����. ( +/- )
		short		nDefense;					//	���. ( +/- )

		SRESIST		sResist;					//	���װ�.

		//	���� ���� Ƚ��.		( '0' ���� �Ұ� ),
		//	���, �� �����ۿ����� ������ ��ȣ.
		WORD		wReModelNum;

		//	Ư�� �ΰ� ȿ����.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SSATE_BLOW	sBLOW;						//	���� �̻� ȿ��.
	};

	enum	EMHAND
	{
		EMHAND_BOTHHAND		= 0x0001,
		EMHAND_BIG			= 0x0002,
		EMHAND_BROOM		= 0x0004,
	};

	struct SSUIT_107
	{
		enum { ADDON_SIZE = 4 };

		EMSUIT		emSuit;						//	������ ���� Ÿ��.
		DWORD		dwHAND;						//	�� ���� �Ӽ�.
		EMITEM_HAND	emHand;						//	���� �� ��ġ.

		glold_108::GLITEM_ATT_108	emAttack;	//	���ݼӼ�.
		WORD		wAttRange;					//	���� ���� �Ÿ�.
		WORD		wReqSP;						//	���ݽ� �ʿ��� SP.

		short		nHitRate;					//	������. ( +/- ) (%)
		short		nAvoidRate;					//	ȸ����. ( +/- ) (%)

		GLPADATA	gdDamage;					//	�����. ( +/- )
		short		nDefense;					//	���. ( +/- )

		SRESIST		sResist;					//	���װ�.

		//	���� ���� Ƚ��.		( '0' ���� �Ұ� ),
		//	���, �� �����ۿ����� ������ ��ȣ.
		WORD		wReModelNum;

		//	Ư�� �ΰ� ȿ����.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SVOL		sVOLUME;					//  ��ȭ�� ȿ��. By ���
		SSATE_BLOW	sBLOW;						//	���� �̻� ȿ��.
	};

	struct SSUIT_108
	{
		enum { ADDON_SIZE = 4 };

		EMSUIT		emSuit;						//	������ ���� Ÿ��.
		DWORD		dwHAND;						//	�� ���� �Ӽ�.
		EMITEM_HAND	emHand;						//	���� �� ��ġ.
		GLPADATA	gdDamage;					//	�����. ( +/- )
		short		nDefense;					//	���. ( +/- )
		short		nHitRate;					//	������. ( +/- ) (%)
		short		nAvoidRate;					//	ȸ����. ( +/- ) (%)
		SRESIST		sResist;					//	���װ�.
		glold_108::GLITEM_ATT_108	emAttack;	//	���ݼӼ�.
		WORD		wAttRange;					//	���� ���� �Ÿ�.
		WORD		wReqSP;						//	���ݽ� �ʿ��� SP.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SVOL		sVOLUME;					//  ��ȭ�� ȿ��. By ���
		SSATE_BLOW	sBLOW;						//	���� �̻� ȿ��.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		WORD		wReModelNum;
	};

	struct SSUIT_109
	{
		enum { ADDON_SIZE = 4 };

		EMSUIT		emSuit;						//	������ ���� Ÿ��.
		DWORD		dwHAND;						//	�� ���� �Ӽ�.
		EMITEM_HAND	emHand;						//	���� �� ��ġ.
		GLPADATA	gdDamage;					//	�����. ( +/- )
		short		nDefense;					//	���. ( +/- )
		short		nHitRate;					//	������. ( +/- ) (%)
		short		nAvoidRate;					//	ȸ����. ( +/- ) (%)
		SRESIST		sResist;					//	���װ�.
		GLITEM_ATT	emAttack;					//	���ݼӼ�.
		WORD		wAttRange;					//	���� ���� �Ÿ�.
		WORD		wReqSP;						//	���ݽ� �ʿ��� SP.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SVOL		sVOLUME;					//  ��ȭ�� ȿ��. By ���
		SSATE_BLOW	sBLOW;						//	���� �̻� ȿ��.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		WORD		wReModelNum;
	};

	struct SSUIT_110
	{
		enum { ADDON_SIZE = 4 };

		EMSUIT		emSuit;						//	������ ���� Ÿ��.
		DWORD		dwHAND;						//	�� ���� �Ӽ�.
		EMITEM_HAND	emHand;						//	���� �� ��ġ.
		GLPADATA	gdDamage;					//	�����. ( +/- )
		short		nDefense;					//	���. ( +/- )
		short		nHitRate;					//	������. ( +/- ) (%)
		short		nAvoidRate;					//	ȸ����. ( +/- ) (%)
		SRESIST		sResist;					//	���װ�.
		GLITEM_ATT	emAttack;					//	���ݼӼ�.
		WORD		wAttRange;					//	���� ���� �Ÿ�.
		WORD		wReqSP;						//	���ݽ� �ʿ��� SP.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SVOL		sVOLUME;					//  ��ȭ�� ȿ��. By ���
		SSATE_BLOW	sBLOW;						//	���� �̻� ȿ��.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		WORD		wReModelNum;
	};

	//	���� ������, ���� ������.
	struct SSUIT
	{
		enum { ADDON_SIZE = 4, VERSION = 0x0112 };

		EMSUIT		emSuit;						//	������ ���� Ÿ��.
		DWORD		dwHAND;						//	�� ���� �Ӽ�.
		EMITEM_HAND	emHand;						//	���� �� ��ġ.
		GLPADATA	gdDamage;					//	�����. ( +/- )
		short		nDefense;					//	���. ( +/- )
		short		nHitRate;					//	������. ( +/- ) (%)
		short		nAvoidRate;					//	ȸ����. ( +/- ) (%)
		SRESIST		sResist;					//	���װ�.
		GLITEM_ATT	emAttack;					//	���ݼӼ�.
		WORD		wAttRange;					//	���� ���� �Ÿ�.
		WORD		wReqSP;						//	���ݽ� �ʿ��� SP.
		SVAR		sVARIATE;					//	��ȭ�� ȿ��.
		SVOL		sVOLUME;					//  ��ȭ�� ȿ��. By ���
		SSATE_BLOW	sBLOW;						//	���� �̻� ȿ��.
		SADDON		sADDON[ADDON_SIZE];			//	���� ȿ��.
		WORD		wReModelNum;

		DWORD		dummy_var_0;
		WORD		dummy_var_1;
		DWORD		dummy_var_2;

		SSUIT ()
			: emSuit(SUIT_HEADGEAR)
			, dwHAND(NULL)
			, emHand(HAND_RIGHT)
			, gdDamage(0,0)
			, nDefense(0)
			, nHitRate(0)
			, nAvoidRate(0)
			, emAttack(ITEMATT_NOTHING)
			, wAttRange(4)
			, wReqSP(0)
			, wReModelNum(0)

			, dummy_var_0(0)
			, dummy_var_1(0)
			, dummy_var_2(0)
		{
		}

		void Assign ( SSUIT_100 &Suit100 );
		void Assign ( SSUIT_101 &Suit101 );
		void Assign ( SSUIT_102 &Suit102 );
		void Assign ( SSUIT_103 &Suit103 );
		void Assign ( SSUIT_104 &Suit104 );
		void Assign ( SSUIT_105 &Suit105 );
		void Assign ( SSUIT_106 &Suit106 );
		void Assign ( SSUIT_107 &Suit107 );
		void Assign ( SSUIT_108 &Suit108 );
		void Assign ( SSUIT_109 &Suit109 );
		void Assign ( SSUIT_110 &Suit109 );

		static VOID SaveCsvHead ( std::fstream &SFile );
		VOID SaveCsv ( std::fstream &SFile );
		VOID LoadCsv ( CStringArray &StrArray, int &iCsvCur );

		void SETBOTHHAND ( bool bBOTH )		{ (bBOTH) ? (dwHAND|=EMHAND_BOTHHAND) : (dwHAND&=~EMHAND_BOTHHAND); }
		void SETBIG ( bool bBIG )			{ (bBIG) ? (dwHAND|=EMHAND_BIG) : (dwHAND&=~EMHAND_BIG); }
		void SETBROOM ( bool bBROOM )		{ (bBROOM) ? (dwHAND|=EMHAND_BROOM) : (dwHAND&=~EMHAND_BROOM); }

		bool IsBOTHHAND () const			{ return NULL!=(dwHAND&EMHAND_BOTHHAND); }
		bool IsBIG () const					{ return NULL!=(dwHAND&EMHAND_BIG); }
		bool IsBROOM () const				{ return NULL!=(dwHAND&EMHAND_BROOM); }
	};
};

namespace COMMENT
{
	extern std::string ADDON_NO[ITEM::SSUIT::ADDON_SIZE];
};

#endif // GLITEM_SUIT_H_