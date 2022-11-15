#ifndef GLSKILL_BASIC_H_
#define GLSKILL_BASIC_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../Lib_Engine/Common/BaseStream.h"
#include "../../Lib_Engine/Common/StringFile.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/Common/STRINGUTILS.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"

#include "./GLCharDefine.h"
#include "./GLSkillDefine.h"

namespace gloldskill_102
{
	enum GLSKILL_ATT_102
	{
		SKILLATT_NOTHING	= 0,	//	���빫�����.
		SKILLATT_SWORD		= 1,	//	�˷�.
		SKILLATT_REV00		= 2,	//	REV00
		SKILLATT_DAGGER		= 3,	//	�ܰ˷�.
		SKILLATT_SPEAR		= 4,	//	â��.
		SKILLATT_BOW		= 5,	//	Ȱ��.
		SKILLATT_THROW		= 6,	//	��ô��.
		SKILLATT_NOCARE		= 7,	//	Ÿ�� ��� ����.	( "GLSKILL" ���� Hand ���� ���� �Ӽ����� ����. )
		SKILLATT_NSIZE		= 7,	//	��������.
		SKILLATT_NEAR		= 4,	//	���� ����.
	};
};

namespace gloldskill_103
{
	enum GLSKILL_ATT_103
	{
		SKILLATT_NOTHING	= 0,	//	���빫�����.
		SKILLATT_SWORD		= 1,	//	��.
		SKILLATT_BLADE		= 2,	//	��.
		SKILLATT_DAGGER		= 3,	//	�ܰ�.
		SKILLATT_SPEAR		= 4,	//	â.
		SKILLATT_STICK		= 5,	//	������.
		SKILLATT_BOW		= 6,	//	Ȱ.
		SKILLATT_THROW		= 7,	//	��ô.
		SKILLATT_NOCARE		= 8,	//	Ÿ�� ��� ����.	( "GLSKILL" ���� Hand ���� ���� �Ӽ����� ����. )
		SKILLATT_NSIZE		= 8,	//	��������.
		SKILLATT_NEAR		= 5,	//	���� ����.
	};
};

namespace gloldskill_108
{
	enum GLSKILL_ATT_108
	{
		SKILLATT_NOTHING	= 0,	//
		SKILLATT_SWORD		= 1,	//
		SKILLATT_BLADE		= 2,	//
		SKILLATT_SWORDBLADE	= 3,	//
		SKILLATT_DAGGER		= 4,	//
		SKILLATT_SPEAR		= 5,	//
		SKILLATT_STICK		= 6,	//
		SKILLATT_GAUNT		= 7,	//
		SKILLATT_BOW		= 8,	//
		SKILLATT_THROW		= 9,	//
		SKILLATT_NOCARE		= 10,	//
		SKILLATT_NSIZE		= 10,	//
		SKILLATT_NEAR		= 7,	//
	};
};

namespace gloldskill_110
{
	enum GLSKILL_ATT_110
	{
		SKILLATT_NOTHING	= 0,
		SKILLATT_SWORD		= 1,
		SKILLATT_BLADE		= 2,
		SKILLATT_SWORDBLADE	= 3,
		SKILLATT_DAGGER		= 4,
		SKILLATT_SPEAR		= 5,
		SKILLATT_STICK		= 6,
		SKILLATT_GAUNT		= 7,
		SKILLATT_BOW		= 8,
		SKILLATT_THROW		= 9,

		SKILLATT_GUN		= 10,
		SKILLATT_RAILGUN	= 11,
		SKILLATT_PORTALGUN	= 12,

		SKILLATT_SHOTGUN		= 13,
		SKILLATT_RAILPORTALGUN	= 14,

		SKILLATT_SCYTHE		= 15,
		SKILLATT_DUALSPEAR	= 16,
		SKILLATT_SHURIKEN	= 17,

		SKILLATT_FIST	= 18,
		SKILLATT_WAND	= 19,
		SKILLATT_CUBE	= 20,
		SKILLATT_WHIP	= 21,

		SKILLATT_NOCARE		= 22,
		SKILLATT_NSIZE		= 22,
	};
};


enum GLSKILL_ATT
{
	SKILLATT_NOTHING	= 0,
	SKILLATT_SWORD		= 1,
	SKILLATT_BLADE		= 2,
	SKILLATT_SWORDBLADE	= 3,
	SKILLATT_DAGGER		= 4,
	SKILLATT_SPEAR		= 5,
	SKILLATT_STICK		= 6,
	SKILLATT_GAUNT		= 7,
	SKILLATT_BOW		= 8,
	SKILLATT_THROW		= 9,

	SKILLATT_GUN		= 10,
	SKILLATT_RAILGUN	= 11,
	SKILLATT_PORTALGUN	= 12,

	SKILLATT_SHOTGUN		= 13,
	SKILLATT_RAILPORTALGUN	= 14,

	SKILLATT_SCYTHE		= 15,
	SKILLATT_DUALSPEAR	= 16,
	SKILLATT_SHURIKEN	= 17,

	SKILLATT_FIST	= 18,
	SKILLATT_WAND	= 19,
	SKILLATT_CUBE	= 20,
	SKILLATT_WHIP	= 21,

	SKILLATT_NOCARE		= 22,
	SKILLATT_NSIZE		= 22,

};

namespace SKILL
{
	enum EMROLE
	{
		EMROLE_NORMAL	= 0,		//	���.
		EMROLE_PASSIVE	= 1,		//	��ú� �迭. ( ����ϴ� ���� �ƴϰ� ������� �ٸ� ���� ���� )
		EMROLE_NSIZE	= 2,
	};

	enum EMAPPLY	//	������ ����� ȿ��.
	{
		EMAPPLY_PHY_SHORT	= 0,	//	���� Ÿ����.
		EMAPPLY_PHY_LONG	= 1,	//	���� �����.
		EMAPPLY_MAGIC		= 2,	//	���� �ۿ���.

		EMAPPLY_NSIZE		= 3
	};

	enum EMACTION
	{
		EMACTION_NORMAL		= 0,
		EMACTION_BUFF		= 1,
		EMACTION_DEBUFF		= 2,
		EMACTION_LIMIT		= 3,
		EMACTION_NSIZE		= 4,
	};

	GLSKILL_ATT assign_att ( gloldskill_102::GLSKILL_ATT_102 emOld );
	GLSKILL_ATT assign_att ( gloldskill_103::GLSKILL_ATT_103 emOld );
	GLSKILL_ATT assign_att ( gloldskill_108::GLSKILL_ATT_108 emOld );
	GLSKILL_ATT assign_att ( gloldskill_110::GLSKILL_ATT_110 emOld );

	struct SSKILLBASIC_100
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )

		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwGRADE;					//	���.

		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )

		//	Skill �� ���� �޴� ��ǥ.
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )

		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.

		gloldskill_102::GLSKILL_ATT_102	emUSE_LITEM;			//	��밡�� �޼� ���� �Ӽ�.
		gloldskill_102::GLSKILL_ATT_102	emUSE_RITEM;			//	��밡�� ������ ���� �Ӽ�.
	};

	struct SSKILLBASIC_101
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )

		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwGRADE;					//	���.

		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )

		//	Skill �� ���� �޴� ��ǥ.
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )

		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.

		gloldskill_102::GLSKILL_ATT_102	emUSE_LITEM;			//	��밡�� �޼� ���� �Ӽ�.
		gloldskill_102::GLSKILL_ATT_102	emUSE_RITEM;			//	��밡�� ������ ���� �Ӽ�.
	};

	struct SSKILLBASIC_102
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )

		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwGRADE;					//	���.

		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )

		//	Skill �� ���� �޴� ��ǥ.
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )

		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.

		gloldskill_103::GLSKILL_ATT_103	emUSE_LITEM;			//	��밡�� �޼� ���� �Ӽ�.
		gloldskill_103::GLSKILL_ATT_103	emUSE_RITEM;			//	��밡�� ������ ���� �Ӽ�.
	};

	struct SSKILLBASIC_103
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )

		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwGRADE;					//	���.

		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )

		//	Skill �� ���� �޴� ��ǥ.
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )

		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.

		gloldskill_108::GLSKILL_ATT_108	emUSE_LITEM;				//	��밡�� �޼� ���� �Ӽ�.
		gloldskill_108::GLSKILL_ATT_108	emUSE_RITEM;				//	��밡�� ������ ���� �Ӽ�.
	};

	struct SSKILLBASIC_105
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )

		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwGRADE;					//	���.
		DWORD				dwMAXLEVEL;					//	�ִ� ����.

		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )

		//	Skill �� ���� �޴� ��ǥ.
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )

		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.

		gloldskill_108::GLSKILL_ATT_108	emUSE_LITEM;				//	��밡�� �޼� ���� �Ӽ�.
		gloldskill_108::GLSKILL_ATT_108	emUSE_RITEM;				//	��밡�� ������ ���� �Ӽ�.
	};

	struct SSKILLBASIC_106
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )

		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwGRADE;					//	���.
		DWORD				dwMAXLEVEL;					//	�ִ� ����.

		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )

		//	Skill �� ���� �޴� ��ǥ.
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )

		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.

		gloldskill_108::GLSKILL_ATT_108	emUSE_LITEM;				//	��밡�� �޼� ���� �Ӽ�.
		gloldskill_108::GLSKILL_ATT_108	emUSE_RITEM;				//	��밡�� ������ ���� �Ӽ�.

		bool				bLearnView;					//  GM�� ���̴� ��ų
	};

	struct SSKILLBASIC_107
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )
		bool				bLearnView;					//  GM�� ���̴� ��ų
		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwMAXLEVEL;					//	�ִ� ����.
		DWORD				dwGRADE;					//	���.
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )
		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		gloldskill_108::GLSKILL_ATT_108	emUSE_LITEM;	//	��밡�� �޼� ���� �Ӽ�.
		gloldskill_108::GLSKILL_ATT_108	emUSE_RITEM;	//	��밡�� ������ ���� �Ӽ�.
	};

	struct SSKILLBASIC_108
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )
		bool				bLearnView;					//  GM�� ���̴� ��ų
		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwMAXLEVEL;					//	�ִ� ����.
		DWORD				dwGRADE;					//	���.
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )
		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMACTION			emACTION;
		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		gloldskill_108::GLSKILL_ATT_108	emUSE_LITEM;	//	��밡�� �޼� ���� �Ӽ�.
		gloldskill_108::GLSKILL_ATT_108	emUSE_RITEM;	//	��밡�� ������ ���� �Ӽ�.
	};

	struct SSKILLBASIC_109
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )
		WORD				wData;						// official unknown data
		bool				bLearnView;					//  GM�� ���̴� ��ų
		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwMAXLEVEL;					//	�ִ� ����.
		DWORD				dwGRADE;					//	���.
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )
		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMACTION			emACTION;
		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		gloldskill_110::GLSKILL_ATT_110		emUSE_LITEM;				//	��밡�� �޼� ���� �Ӽ�.
		gloldskill_110::GLSKILL_ATT_110		emUSE_RITEM;				//	��밡�� ������ ���� �Ӽ�.
	};

	struct SSKILLBASIC_110
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )
		WORD				wData;						// official unknown data
		bool				bLearnView;					//  GM�� ���̴� ��ų
		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwMAXLEVEL;					//	�ִ� ����.
		DWORD				dwGRADE;					//	���.
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )
		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMACTION			emACTION;
		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		gloldskill_110::GLSKILL_ATT_110		emUSE_LITEM;				//	��밡�� �޼� ���� �Ӽ�.
		gloldskill_110::GLSKILL_ATT_110		emUSE_RITEM;				//	��밡�� ������ ���� �Ӽ�.
	};

	struct SSKILLBASIC_111
	{
		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )
		WORD				wData;						// official unknown data
		bool				bLearnView;					//  GM�� ���̴� ��ų
		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwMAXLEVEL;					//	�ִ� ����.
		DWORD				dwGRADE;					//	���.
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )
		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMACTION			emACTION;
		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		GLSKILL_ATT			emUSE_LITEM;				//	��밡�� �޼� ���� �Ӽ�.
		GLSKILL_ATT			emUSE_RITEM;				//	��밡�� ������ ���� �Ӽ�.
	};

	struct SSKILLBASIC
	{
		enum { VERSION = 0x0112, };

		SNATIVEID			sNATIVEID;					//	���� ID. ( ���� �����ÿ� �ο��Ǵ� ���� ID )
		WORD				wData;						// official unknown data
		bool				bLearnView;					//  GM�� ���̴� ��ų
		char				szNAME[MAX_SZNAME];			//	��ų�� �̸�.
		DWORD				dwMAXLEVEL;					//	�ִ� ����.
		DWORD				dwGRADE;					//	���.
		EMAPPLY				emAPPLY;					//	��ų ����. ( ��������, ��������, ���� ���� )
		EMROLE				emROLE;						//	��ų ���� Ư��. ( ���, ����, ��ú� )
		EMACTION			emACTION;
		WORD				wTARRANGE;					//	��ǥ ���� �Ÿ�.
		EMIMPACT_SIDE		emIMPACT_SIDE;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )
		EMIMPACT_TAR		emIMPACT_TAR;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
		EMIMPACT_REALM		emIMPACT_REALM;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
		GLSKILL_ATT			emUSE_LITEM;				//	��밡�� �޼� ���� �Ӽ�.
		GLSKILL_ATT			emUSE_RITEM;				//	��밡�� ������ ���� �Ӽ�.
		DWORD				dwData;

		SSKILLBASIC (void) :
			bLearnView(FALSE),
			wData(0),
			dwMAXLEVEL(9),
			dwGRADE(0),
			emAPPLY(EMAPPLY_MAGIC),
			emROLE(EMROLE_NORMAL),
			emACTION(EMACTION_NORMAL),
			wTARRANGE(50),
			emIMPACT_SIDE(SIDE_ENEMY),
			emIMPACT_TAR(TAR_SPEC),
			emIMPACT_REALM(REALM_SELF),
			emUSE_LITEM(SKILLATT_NOCARE),
			emUSE_RITEM(SKILLATT_NOCARE),
			dwData(0)
		{
			SecureZeroMemory ( szNAME, sizeof(char)*MAX_SZNAME );
		}

		void Assign ( SSKILLBASIC_100 &sOldData );
		void Assign ( SSKILLBASIC_101 &sOldData );
		void Assign ( SSKILLBASIC_102 &sOldData );
		void Assign ( SSKILLBASIC_103 &sOldData );
		void Assign ( SSKILLBASIC_105 &sOldData );
		void Assign ( SSKILLBASIC_106 &sOldData );
		void Assign ( SSKILLBASIC_107 &sOldData );
		void Assign ( SSKILLBASIC_108 &sOldData );
		void Assign ( SSKILLBASIC_109 &sOldData );
		void Assign ( SSKILLBASIC_110 &sOldData );
		void Assign ( SSKILLBASIC_111 &sOldData );

		static VOID SaveCsvHead ( std::fstream &SFile );
		VOID SaveCsv ( std::fstream &SFile );
		VOID LoadCsv ( CStringArray &StrArray, int &iCsvCur );
	};
};

namespace COMMENT
{
	extern std::string SKILL_ROLE[SKILL::EMROLE_NSIZE];
	extern std::string SKILL_APPLY[SKILL::EMAPPLY_NSIZE];
	extern std::string SKILLATTACK[SKILLATT_NSIZE+1];
	extern std::string SKILL_ACTION_TYPE[SKILL::EMACTION_NSIZE];
};

#endif // GLSKILL_BASIC_H_