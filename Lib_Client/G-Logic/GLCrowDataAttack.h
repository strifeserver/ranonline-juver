#ifndef GLCROWDATA_ATTACK_H_
#define GLCROWDATA_ATTACK_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../Lib_Engine/Common/BaseStream.h"
#include "../../Lib_Engine/Common/StringFile.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/Common/STRINGUTILS.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"


#include "../../Lib_Engine/Meshs/SAnimation.h"
#include "../../Lib_Engine/Meshs/DxSkinAniControl.h"
#include "./GLCharDefine.h"

struct SCROWATTACK_100
{
	enum { VERSION = 0x0100, };

	BOOL			bUsed;						//	��밡��.
	EMATT_RGTYPE	emAttRgType;				//	���ݰ��ɰŸ� ����.
	WORD			wRange;						//	���ݰ��� �Ÿ�.
	WORD			wSphere;					//	���ݿ��� ����.

	//	Skill �� ���� �޴� ��ǥ.
	EMIMPACT_TAR	emImpact_Tar;				//	Ÿ��. ( �ڽ�, ���, ��ġ ) &&
	EMIMPACT_REALM	emImpact_Realm;				//	����. ( Ÿ��, Ÿ�ٰ� �� ����, �� ���� ) &&
	EMIMPACT_SIDE	emImpact_Side;				//	"��" ( �� ������ �ڱ���, �� ������ ����� )

	EMELEMENT		emElement;					//	���� �Ӽ�.
	GLPADATA		sDamage;					//	Ÿ�ݰ�.
	float			fDelay;						//	������.
	float			fLife;						//	���� �ð�.

	WORD			wUse_MP;					//	���� MP ������.
	WORD			wUse_SP;					//	���� SP ������.

	EMSTATE_BLOW	emBlow;						//	�����̻�.
	float			fBlowRATE;					//	�߻� Ȯ��.
	float			fBlowVALUE;					//	���� ��.

	EMIMPACT_ADDON	emImpact;					//	�ΰ�ȿ�� ����.
	int				nImpactVAR;					//	��ȭ ��ġ.

	char			szAniFile[ACF_SZNAME];		//	���ϸ��̼� ���� �̸�.
	SANIATTACK		sAniAttack;					//	���ϸ��̼� ����.

	char			szSelfBodyEffect[ACF_SZNAME];	//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
	char			szTargBodyEffect[ACF_SZNAME];	//	��ǥ ������ ���� �״� ����Ʈ.
	char			szTargetEffect[ACF_SZNAME];		//	��ǥ ���� ����Ʈ.
};

//----------------------------------------------------------------------
struct SCROWATTACK_101
{
	BOOL			bUsed;						//	��밡��.
	EMATT_RGTYPE	emAttRgType;				//	���ݰ��ɰŸ� ����.
	WORD			wRange;						//	���ݰ��� �Ÿ�.

	GLPADATA		sDamage;					//	Ÿ�ݰ�.
	float			fDelay;						//	������.

	WORD			wUse_SP;					//	���� SP ������.

	char			szAniFile[ACF_SZNAME];		//	���ϸ��̼� ���� �̸�.
	SANIATTACK		sAniAttack;					//	���ϸ��̼� ����.

	SNATIVEID		skill_id;					//	������ ��ų ����.

	char			szSelfBodyEffect[ACF_SZNAME];	//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
	char			szTargBodyEffect[ACF_SZNAME];	//	��ǥ ������ ���� �״� ����Ʈ.
	char			szTargetEffect[ACF_SZNAME];		//	��ǥ ���� ����Ʈ.
};

struct SCROWATTACK_102
{
	BOOL			bUsed;						//	��밡��.
	EMATT_RGTYPE	emAttRgType;				//	���ݰ��ɰŸ� ����.
	WORD			wRange;						//	���ݰ��� �Ÿ�.

	GLPADATA		sDamage;					//	Ÿ�ݰ�.
	float			fDelay;						//	������.

	WORD			wUse_SP;					//	���� SP ������.

	char			szAniFile[ACF_SZNAME];		//	���ϸ��̼� ���� �̸�.
	SANIATTACK		sAniAttack;					//	���ϸ��̼� ����.

	SNATIVEID		skill_id;					//	������ ��ų ����.

	EMSTATE_BLOW	emBLOW_TYPE;				//	'�����̻�' ���� Ÿ��.
	float			fBLOW_RATE;					//	�߻� Ȯ��.
	float			fBLOW_LIFE;					//	���� �ð�.
	float			fBLOW_VAR1;					//	���� �� 1.
	float			fBLOW_VAR2;					//	���� �� 2.

	char			szSelfBodyEffect[ACF_SZNAME];	//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
	char			szTargBodyEffect[ACF_SZNAME];	//	��ǥ ������ ���� �״� ����Ʈ.
	char			szTargetEffect[ACF_SZNAME];		//	��ǥ ���� ����Ʈ.
};

enum EMCROWSKTAR
{
	CROWSKTAR_OUR	= 0,
	CROWSKTAR_ENEMY	= 1,
	CROWSKTAR_SIZE	= 2,
};

struct SCROWATTACK_103
{
	BOOL			bUsed;						//	��밡��.
	EMATT_RGTYPE	emAttRgType;				//	���ݰ��ɰŸ� ����.
	WORD			wRange;						//	���ݰ��� �Ÿ�.

	GLPADATA		sDamage;					//	Ÿ�ݰ�.
	float			fDelay;						//	������.

	WORD			wUse_SP;					//	���� SP ������.

	char			szAniFile[ACF_SZNAME];		//	���ϸ��̼� ���� �̸�.
	SANIATTACK_100	sAniAttack;					//	���ϸ��̼� ����.

	SNATIVEID		skill_id;					//	��ų ����.
	WORD			skill_lev;					//	��ų ����.
	EMCROWSKTAR		skill_tar;					//	��ų Ÿ��.

	EMSTATE_BLOW	emBLOW_TYPE;				//	'�����̻�' ���� Ÿ��.
	float			fBLOW_RATE;					//	�߻� Ȯ��.
	float			fBLOW_LIFE;					//	���� �ð�.
	float			fBLOW_VAR1;					//	���� �� 1.
	float			fBLOW_VAR2;					//	���� �� 2.

	char			szSelfBodyEffect[ACF_SZNAME];	//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
	char			szTargBodyEffect[ACF_SZNAME];	//	��ǥ ������ ���� �״� ����Ʈ.
	char			szTargetEffect[ACF_SZNAME];		//	��ǥ ���� ����Ʈ.
};

struct SCROWATTACK_104
{
	BOOL			bUsed;						//	��밡��.
	EMATT_RGTYPE	emAttRgType;				//	���ݰ��ɰŸ� ����.
	WORD			wRange;						//	���ݰ��� �Ÿ�.

	GLPADATA		sDamage;					//	Ÿ�ݰ�.
	float			fDelay;						//	������.

	WORD			wUse_SP;					//	���� SP ������.

	char			szAniFile[ACF_SZNAME];		//	���ϸ��̼� ���� �̸�.
	SANIATTACK		sAniAttack;					//	���ϸ��̼� ����.

	SNATIVEID		skill_id;					//	��ų ����.
	WORD			skill_lev;					//	��ų ����.
	EMCROWSKTAR		skill_tar;					//	��ų Ÿ��.

	EMSTATE_BLOW	emBLOW_TYPE;				//	'�����̻�' ���� Ÿ��.
	float			fBLOW_RATE;					//	�߻� Ȯ��.
	float			fBLOW_LIFE;					//	���� �ð�.
	float			fBLOW_VAR1;					//	���� �� 1.
	float			fBLOW_VAR2;					//	���� �� 2.

	char			szSelfBodyEffect[ACF_SZNAME];	//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
	char			szTargBodyEffect[ACF_SZNAME];	//	��ǥ ������ ���� �״� ����Ʈ.
	char			szTargetEffect[ACF_SZNAME];		//	��ǥ ���� ����Ʈ.
};

struct SCROWATTACK_105
{
	BOOL			bUsed;						//	��밡��.
	EMATT_RGTYPE	emAttRgType;				//	���ݰ��ɰŸ� ����.
	WORD			wRange;						//	���ݰ��� �Ÿ�.

	GLPADATA		sDamage;					//	Ÿ�ݰ�.
	float			fDelay;						//	������.

	WORD			wUse_SP;					//	���� SP ������.

	std::string		strAniFile;					//	���ϸ��̼� ���� �̸�.
	SANIATTACK		sAniAttack;					//	���ϸ��̼� ����.

	SNATIVEID		skill_id;					//	��ų ����.
	WORD			skill_lev;					//	��ų ����.
	EMCROWSKTAR		skill_tar;					//	��ų Ÿ��.

	EMSTATE_BLOW	emBLOW_TYPE;				//	'�����̻�' ���� Ÿ��.
	float			fBLOW_RATE;					//	�߻� Ȯ��.
	float			fBLOW_LIFE;					//	���� �ð�.
	float			fBLOW_VAR1;					//	���� �� 1.
	float			fBLOW_VAR2;					//	���� �� 2.

	std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
	std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
	std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.
};

//----------------------------------------------------------------------
struct SCROWATTACK
{
	enum { VERSION = 0x0200, };

	BOOL			bUsed;						//	��밡��.
	EMATT_RGTYPE	emAttRgType;				//	���ݰ��ɰŸ� ����.
	WORD			wRange;						//	���ݰ��� �Ÿ�.
	WORD			wUse_SP;					//	���� SP ������.
	GLPADATA		sDamage;					//	Ÿ�ݰ�.
	float			fDelay;						//	������.
	SNATIVEID		skill_id;					//	��ų ����.
	WORD			skill_lev;					//	��ų ����.
	EMCROWSKTAR		skill_tar;					//	��ų Ÿ��.
	EMSTATE_BLOW	emBLOW_TYPE;				//	'�����̻�' ���� Ÿ��.
	float			fBLOW_RATE;					//	�߻� Ȯ��.
	float			fBLOW_LIFE;					//	���� �ð�.
	float			fBLOW_VAR1;					//	���� �� 1.
	float			fBLOW_VAR2;					//	���� �� 2.
	std::string		strAniFile;					//	���ϸ��̼� ���� �̸�.
	SANIATTACK		sAniAttack;					//	���ϸ��̼� ����.
	std::string		strSelfBodyEffect;			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
	std::string		strTargBodyEffect;			//	��ǥ ������ ���� �״� ����Ʈ.
	std::string		strTargetEffect;			//	��ǥ ���� ����Ʈ.

	SCROWATTACK () :
		bUsed(FALSE),
		emAttRgType(EMATT_SHORT),
		wRange(4),
		wUse_SP(0),
		sDamage(4,6),
		fDelay(0.2f),
		skill_id(NATIVEID_NULL()),
		skill_lev(0),
		skill_tar(CROWSKTAR_ENEMY),
		emBLOW_TYPE(EMBLOW_NONE),
		fBLOW_RATE(0.0f),
		fBLOW_LIFE(0.0f),
		fBLOW_VAR1(0.0f),
		fBLOW_VAR2(0.0f)
	{
	}

	SCROWATTACK (const SCROWATTACK& value )
	{
		operator= ( value );
	}

	SCROWATTACK& operator= ( const SCROWATTACK_100 &OldData );
	SCROWATTACK& operator= ( const SCROWATTACK_101 &OldData );
	SCROWATTACK& operator= ( const SCROWATTACK_102 &OldData );
	SCROWATTACK& operator= ( const SCROWATTACK_103 &OldData );
	SCROWATTACK& operator= ( const SCROWATTACK_104 &OldData );
	SCROWATTACK& operator= ( const SCROWATTACK &value );

	bool LOAD_0105 ( basestream &SFile );
	bool LOAD_0107 ( basestream &SFile );
	bool LOAD ( basestream &SFile );
	bool SAVE ( CSerialFile &SFile );

	static VOID SaveCsvHead ( std::fstream &SFile, int iIndex );
	VOID SaveCsv ( std::fstream &SFile );
	VOID LoadCsv ( CStringArray &StrArray, int& iCsvCur );
};

namespace COMMENT
{
	extern std::string CROWSKTAR[CROWSKTAR_SIZE];
};

#endif // GLCROWDATA_ATTACK_H_