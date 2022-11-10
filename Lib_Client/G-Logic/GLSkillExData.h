#ifndef GLSKILL_EXDATA_H_
#define GLSKILL_EXDATA_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "../../Lib_Engine/Common/BaseStream.h"
#include "../../Lib_Engine/Common/StringFile.h"
#include "../../Lib_Engine/Common/SerialFile.h"
#include "../../Lib_Engine/Common/STRINGUTILS.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"

#include "../../Lib_Engine/Meshs/DxAniKeys.h"
#include "./GLSkillDefine.h"
#include "./GLCharDefine.h"

namespace SKILL
{
	enum EMEFFECTIME
	{
		EMTIME_FIRST	= 0,		//	��ų ���۰� ���ÿ�.
		EMTIME_IMPACT	= 1,		//	��ų Ÿ�� ����.
		EMTIME_TARG_OVR	= 2,		//	��ų Ÿ�� ����Ʈ�� ������ ����.
		EMTIME_PASSIVE	= 3,		//	Ÿ�ٿ� ������ ��ų��.
		EMTIME_REV01	= 4,
		EMTIME_EFFECT_ACTIVATED	= 5, /*skill activated effect, Juver, 2017/12/29 */
		EMTIME_NSIZE	= 6,
	};

	enum EMEFFECTPOS
	{
		EMPOS_GROUND	= 0,		//	���� ��ġ.
		EMPOS_STRIKE	= 1,		//	��Ʈ����ũ ��ġ. ( ����, �տ� ������ ������(�߻��ϴ�) ��ġ. )

		EMPOS_NSIZE		= 2,
	};

	struct SEXT_DATA_100
	{
		EMANI_MAINTYPE		emANIMTYPE;						//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;						//	��ų ���� ĳ������ ���ϸ��̼� ����.		

		EMEFFECTIME			emTARG;
		char				szTARG[MAX_SZFILE];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		char				szSELFZONE01[MAX_SZFILE];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		char				szTARGZONE01[MAX_SZFILE];		//	��ǥ ��ġ ����Ʈ.
		EMEFFECTIME			emTARGZONE02;
		char				szTARGZONE02[MAX_SZFILE];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		char				szSELFBODY[MAX_SZFILE];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		EMEFFECTIME			emTARGBODY01;
		char				szTARGBODY01[MAX_SZFILE];		//	��ǥ ������ ���� �״� ����Ʈ.
		EMEFFECTIME			emTARGBODY02;
		char				szTARGBODY02[MAX_SZFILE];		//	��ǥ ������ ���� �״� ����Ʈ.

		SNATIVEID			sICONINDEX;						//	������ �ε���.
		char				szICONFILE[MAX_SZFILE];			//	������ �ؽ��� ���� �̸�.

		char				szCOMMENTS[MAX_SZCOMMENT];		//	��ų�� ���� ������ ����.
	};

	struct SEXT_DATA_101
	{
		EMANI_MAINTYPE		emANIMTYPE;						//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;						//	��ų ���� ĳ������ ���ϸ��̼� ����.		

		EMEFFECTIME			emTARG;
		char				szTARG[MAX_SZFILE];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		char				szSELFZONE01[MAX_SZFILE];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE02;
		char				szSELFZONE02[MAX_SZFILE];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		char				szTARGZONE01[MAX_SZFILE];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE02;
		char				szTARGZONE02[MAX_SZFILE];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		char				szSELFBODY[MAX_SZFILE];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		EMEFFECTIME			emTARGBODY01;
		char				szTARGBODY01[MAX_SZFILE];		//	��ǥ ������ ���� �״� ����Ʈ.
		EMEFFECTIME			emTARGBODY02;
		char				szTARGBODY02[MAX_SZFILE];		//	��ǥ ������ ���� �״� ����Ʈ.

		SNATIVEID			sICONINDEX;						//	������ �ε���.
		char				szICONFILE[MAX_SZFILE];			//	������ �ؽ��� ���� �̸�.

		char				szCOMMENTS[MAX_SZCOMMENT];		//	��ų�� ���� ������ ����.
	};

	struct SEXT_DATA_102
	{
		EMANI_MAINTYPE		emANIMTYPE;						//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;						//	��ų ���� ĳ������ ���ϸ��̼� ����.		

		EMEFFECTIME			emTARG;
		EMEFFECTPOS			emTARG_POSA;
		EMEFFECTPOS			emTARG_POSB;
		char				szTARG[MAX_SZFILE];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		EMEFFECTPOS			emSELFZONE01_POS;
		char				szSELFZONE01[MAX_SZFILE];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE02;
		EMEFFECTPOS			emSELFZONE02_POS;
		char				szSELFZONE02[MAX_SZFILE];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		EMEFFECTPOS			emTARGZONE01_POS;
		char				szTARGZONE01[MAX_SZFILE];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE02;
		EMEFFECTPOS			emTARGZONE02_POS;
		char				szTARGZONE02[MAX_SZFILE];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		char				szSELFBODY[MAX_SZFILE];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.
		EMEFFECTIME			emTARGBODY01;
		char				szTARGBODY01[MAX_SZFILE];		//	��ǥ ������ ���� �״� ����Ʈ.
		EMEFFECTIME			emTARGBODY02;
		char				szTARGBODY02[MAX_SZFILE];		//	��ǥ ������ ���� �״� ����Ʈ.

		SNATIVEID			sICONINDEX;						//	������ �ε���.
		char				szICONFILE[MAX_SZFILE];			//	������ �ؽ��� ���� �̸�.

		char				szCOMMENTS[MAX_SZCOMMENT];		//	��ų�� ���� ������ ����.
	};

	struct SEXT_DATA_103
	{
		EMANI_MAINTYPE		emANIMTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		

		EMEFFECTIME			emTARG;
		EMEFFECTPOS			emTARG_POSA;
		EMEFFECTPOS			emTARG_POSB;
		std::string			strTARG[EMELEMENT_OLDMAX];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		EMEFFECTPOS			emSELFZONE01_POS;
		std::string			strSELFZONE01[EMELEMENT_OLDMAX];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE02;
		EMEFFECTPOS			emSELFZONE02_POS;
		std::string			strSELFZONE02[EMELEMENT_OLDMAX];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		EMEFFECTPOS			emTARGZONE01_POS;
		std::string			strTARGZONE01[EMELEMENT_OLDMAX];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE02;
		EMEFFECTPOS			emTARGZONE02_POS;
		std::string			strTARGZONE02[EMELEMENT_OLDMAX];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		std::string			strSELFBODY[EMELEMENT_OLDMAX];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY01;
		std::string			strTARGBODY01[EMELEMENT_OLDMAX];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY02;
		std::string			strTARGBODY02[EMELEMENT_OLDMAX];		//	��ǥ ������ ���� �״� ����Ʈ.

		std::string			strHOLDOUT;								//	��� ����Ʈ.

		SNATIVEID			sICONINDEX;								//	������ �ε���.
		std::string			strICONFILE;							//	������ �ؽ��� ���� �̸�.

		std::string			strCOMMENTS;							//	��ų�� ���� ������ ����.

		BOOL LOAD ( basestream &SFile );
	};

	struct SEXT_DATA_104
	{
		EMANI_MAINTYPE		emANIMTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		

		float				fDELAY4DAMAGE;							//	����� �߻� ������.
		EMEFFECTIME			emTARG;
		EMEFFECTPOS			emTARG_POSA;
		EMEFFECTPOS			emTARG_POSB;
		std::string			strTARG[EMELEMENT_OLDMAX];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		EMEFFECTPOS			emSELFZONE01_POS;
		std::string			strSELFZONE01[EMELEMENT_OLDMAX];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE02;
		EMEFFECTPOS			emSELFZONE02_POS;
		std::string			strSELFZONE02[EMELEMENT_OLDMAX];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		EMEFFECTPOS			emTARGZONE01_POS;
		std::string			strTARGZONE01[EMELEMENT_OLDMAX];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE02;
		EMEFFECTPOS			emTARGZONE02_POS;
		std::string			strTARGZONE02[EMELEMENT_OLDMAX];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		std::string			strSELFBODY[EMELEMENT_OLDMAX];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY01;
		std::string			strTARGBODY01[EMELEMENT_OLDMAX];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY02;
		std::string			strTARGBODY02[EMELEMENT_OLDMAX];		//	��ǥ ������ ���� �״� ����Ʈ.

		std::string			strHOLDOUT;								//	��� ����Ʈ.

		SNATIVEID			sICONINDEX;								//	������ �ε���.
		std::string			strICONFILE;							//	������ �ؽ��� ���� �̸�.

		std::string			strCOMMENTS;							//	��ų�� ���� ������ ����.

		BOOL LOAD ( basestream &SFile );
	};

	struct SEXT_DATA_105
	{
		EMANI_MAINTYPE		emANIMTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		

		float				fDELAY4DAMAGE;							//	����� �߻� ������.
		EMEFFECTIME			emTARG;
		EMEFFECTPOS			emTARG_POSA;
		EMEFFECTPOS			emTARG_POSB;
		bool				bTARG_ONE;								//	��ǥ ���� ����Ʈ ���� ����.
		std::string			strTARG[EMELEMENT_OLDMAX];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		EMEFFECTPOS			emSELFZONE01_POS;
		std::string			strSELFZONE01[EMELEMENT_OLDMAX];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE02;
		EMEFFECTPOS			emSELFZONE02_POS;
		std::string			strSELFZONE02[EMELEMENT_OLDMAX];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		EMEFFECTPOS			emTARGZONE01_POS;
		std::string			strTARGZONE01[EMELEMENT_OLDMAX];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE02;
		EMEFFECTPOS			emTARGZONE02_POS;
		std::string			strTARGZONE02[EMELEMENT_OLDMAX];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		std::string			strSELFBODY[EMELEMENT_OLDMAX];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY01;
		std::string			strTARGBODY01[EMELEMENT_OLDMAX];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY02;
		std::string			strTARGBODY02[EMELEMENT_OLDMAX];		//	��ǥ ������ ���� �״� ����Ʈ.

		std::string			strHOLDOUT;								//	��� ����Ʈ.

		SNATIVEID			sICONINDEX;								//	������ �ε���.
		std::string			strICONFILE;							//	������ �ؽ��� ���� �̸�.

		std::string			strCOMMENTS;							//	��ų�� ���� ������ ����.

		BOOL LOAD ( basestream &SFile );

	};

	struct SEXT_DATA_106
	{
		EMANI_MAINTYPE		emANIMTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		

		float				fDELAY4DAMAGE;							//	����� �߻� ������.
		EMEFFECTIME			emTARG;
		EMEFFECTPOS			emTARG_POSA;
		EMEFFECTPOS			emTARG_POSB;
		bool				bTARG_ONE;								//	��ǥ ���� ����Ʈ ���� ����.
		std::string			strTARG[EMELEMENT_MAXNUM];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		EMEFFECTPOS			emSELFZONE01_POS;
		std::string			strSELFZONE01[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE02;
		EMEFFECTPOS			emSELFZONE02_POS;
		std::string			strSELFZONE02[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		EMEFFECTPOS			emTARGZONE01_POS;
		std::string			strTARGZONE01[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE02;
		EMEFFECTPOS			emTARGZONE02_POS;
		std::string			strTARGZONE02[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		std::string			strSELFBODY[EMELEMENT_MAXNUM];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY01;
		std::string			strTARGBODY01[EMELEMENT_MAXNUM];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY02;
		std::string			strTARGBODY02[EMELEMENT_MAXNUM];		//	��ǥ ������ ���� �״� ����Ʈ.

		std::string			strHOLDOUT;								//	��� ����Ʈ.

		SNATIVEID			sICONINDEX;								//	������ �ε���.
		std::string			strICONFILE;							//	������ �ؽ��� ���� �̸�.

		std::string			strCOMMENTS;							//	��ų�� ���� ������ ����.

		BOOL LOAD ( basestream &SFile );
	};

	struct SEXT_DATA_107
	{
		EMANI_MAINTYPE		emANIMTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		

		SNATIVEID			sICONINDEX;								//	������ �ε���.
		std::string			strICONFILE;							//	������ �ؽ��� ���� �̸�.

		std::string			strCOMMENTS;							//	��ų�� ���� ������ ����.

		EMEFFECTIME			emTARG;
		EMEFFECTPOS			emTARG_POSA;
		EMEFFECTPOS			emTARG_POSB;

		float				fDELAY4DAMAGE;							//	����� �߻� ������.

		std::string			strHOLDOUT;								//	��� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		EMEFFECTPOS			emSELFZONE01_POS;
		std::string			strSELFZONE01[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE02;
		EMEFFECTPOS			emSELFZONE02_POS;
		std::string			strSELFZONE02[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		bool				bTARG_ONE;								//	��ǥ ���� ����Ʈ ���� ����.
		std::string			strTARG[EMELEMENT_MAXNUM];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		EMEFFECTPOS			emTARGZONE01_POS;
		std::string			strTARGZONE01[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE02;
		EMEFFECTPOS			emTARGZONE02_POS;
		std::string			strTARGZONE02[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGBODY01;
		std::string			strTARGBODY01[EMELEMENT_MAXNUM];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY02;
		std::string			strTARGBODY02[EMELEMENT_MAXNUM];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		std::string			strSELFBODY[EMELEMENT_MAXNUM];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.

		BOOL LOAD ( basestream &SFile );
	};

	struct SEXT_DATA_108
	{
		EMANI_MAINTYPE		emANIMTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.	
		DWORD				dwVal;		//official unknown data

		SNATIVEID			sICONINDEX;								//	������ �ε���.
		std::string			strICONFILE;							//	������ �ؽ��� ���� �̸�.

		std::string			strCOMMENTS;							//	��ų�� ���� ������ ����.

		EMEFFECTIME			emTARG;
		EMEFFECTPOS			emTARG_POSA;
		EMEFFECTPOS			emTARG_POSB;

		float				fDELAY4DAMAGE;							//	����� �߻� ������.

		std::string			strHOLDOUT;								//	��� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		EMEFFECTPOS			emSELFZONE01_POS;
		std::string			strSELFZONE01[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE02;
		EMEFFECTPOS			emSELFZONE02_POS;
		std::string			strSELFZONE02[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		bool				bTARG_ONE;								//	��ǥ ���� ����Ʈ ���� ����.
		std::string			strTARG[EMELEMENT_MAXNUM];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		EMEFFECTPOS			emTARGZONE01_POS;
		std::string			strTARGZONE01[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE02;
		EMEFFECTPOS			emTARGZONE02_POS;
		std::string			strTARGZONE02[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGBODY01;
		std::string			strTARGBODY01[EMELEMENT_MAXNUM];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY02;
		std::string			strTARGBODY02[EMELEMENT_MAXNUM];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		std::string			strSELFBODY[EMELEMENT_MAXNUM];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.

		BOOL LOAD ( basestream &SFile );
	};

	struct SEXT_DATA_109
	{
		EMANI_MAINTYPE		emANIMTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.	
		DWORD				dwVal;		//official unknown data

		SNATIVEID			sICONINDEX;								//	������ �ε���.
		std::string			strICONFILE;							//	������ �ؽ��� ���� �̸�.

		std::string			strCOMMENTS;							//	��ų�� ���� ������ ����.

		EMEFFECTIME			emTARG;
		EMEFFECTPOS			emTARG_POSA;
		EMEFFECTPOS			emTARG_POSB;

		float				fDELAY4DAMAGE;							//	����� �߻� ������.

		std::string			strHOLDOUT;								//	��� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		EMEFFECTPOS			emSELFZONE01_POS;
		std::string			strSELFZONE01[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE02;
		EMEFFECTPOS			emSELFZONE02_POS;
		std::string			strSELFZONE02[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE03;
		EMEFFECTPOS			emSELFZONE03_POS;
		std::string			strSELFZONE03[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		bool				bTARG_ONE;								//	��ǥ ���� ����Ʈ ���� ����.
		std::string			strTARG[EMELEMENT_MAXNUM];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		EMEFFECTPOS			emTARGZONE01_POS;
		std::string			strTARGZONE01[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE02;
		EMEFFECTPOS			emTARGZONE02_POS;
		std::string			strTARGZONE02[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE03;
		EMEFFECTPOS			emTARGZONE03_POS;
		std::string			strTARGZONE03[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGBODY01;
		std::string			strTARGBODY01[EMELEMENT_MAXNUM];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY02;
		std::string			strTARGBODY02[EMELEMENT_MAXNUM];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		std::string			strSELFBODY[EMELEMENT_MAXNUM];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.

		SNATIVEID			sADDSKILL;
		DWORD				dwADDSKILLLEVEL;

		BOOL LOAD ( basestream &SFile );
	};

	struct SEXT_DATA
	{
		enum { VERSION = 0x0110, };

		EMANI_MAINTYPE		emANIMTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.		
		EMANI_SUBTYPE		emANISTYPE;								//	��ų ���� ĳ������ ���ϸ��̼� ����.	
		DWORD				dwVal;		//official unknown data

		SNATIVEID			sICONINDEX;								//	������ �ε���.
		std::string			strICONFILE;							//	������ �ؽ��� ���� �̸�.

		std::string			strCOMMENTS;							//	��ų�� ���� ������ ����.

		EMEFFECTIME			emTARG;
		EMEFFECTPOS			emTARG_POSA;
		EMEFFECTPOS			emTARG_POSB;

		float				fDELAY4DAMAGE;							//	����� �߻� ������.

		std::string			strHOLDOUT;								//	��� ����Ʈ.

		EMEFFECTIME			emSELFZONE01;
		EMEFFECTPOS			emSELFZONE01_POS;
		std::string			strSELFZONE01[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE02;
		EMEFFECTPOS			emSELFZONE02_POS;
		std::string			strSELFZONE02[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		EMEFFECTIME			emSELFZONE03;
		EMEFFECTPOS			emSELFZONE03_POS;
		std::string			strSELFZONE03[EMELEMENT_MAXNUM];		//	�ڱ� ��ġ ����Ʈ.

		bool				bTARG_ONE;								//	��ǥ ���� ����Ʈ ���� ����.
		std::string			strTARG[EMELEMENT_MAXNUM];				//	��ǥ ���� ����Ʈ.

		EMEFFECTIME			emTARGZONE01;
		EMEFFECTPOS			emTARGZONE01_POS;
		std::string			strTARGZONE01[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE02;
		EMEFFECTPOS			emTARGZONE02_POS;
		std::string			strTARGZONE02[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGZONE03;
		EMEFFECTPOS			emTARGZONE03_POS;
		std::string			strTARGZONE03[EMELEMENT_MAXNUM];		//	��ǥ ��ġ ����Ʈ.

		EMEFFECTIME			emTARGBODY01;
		std::string			strTARGBODY01[EMELEMENT_MAXNUM];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emTARGBODY02;
		std::string			strTARGBODY02[EMELEMENT_MAXNUM];		//	��ǥ ������ ���� �״� ����Ʈ.

		EMEFFECTIME			emSELFBODY;
		std::string			strSELFBODY[EMELEMENT_MAXNUM];			//	�ڱ� �ڽ��� ���� �״� ����Ʈ.

		SNATIVEID			sADDSKILL;
		DWORD				dwADDSKILLLEVEL;

		inline void LIMIT ( EMELEMENT &emElement )
		{
			GASSERT(emElement<EMELEMENT_MAXNUM2);
			if (emElement==EMELEMENT_MAXNUM) emElement=EMELEMENT_SPIRIT;
		}

		bool VALIDTARG ( EMELEMENT emElement )					{  LIMIT(emElement); return strTARG[emElement].length()!=0; }

		const char* GETTARG ( EMELEMENT emElement )				{  LIMIT(emElement); return strTARG[emElement].c_str(); }
		const char* GETSELFZONE01 ( EMELEMENT emElement )		{  LIMIT(emElement); return strSELFZONE01[emElement].c_str(); }
		const char* GETSELFZONE02 ( EMELEMENT emElement )		{  LIMIT(emElement); return strSELFZONE02[emElement].c_str(); }
		const char* GETSELFZONE03 ( EMELEMENT emElement )		{  LIMIT(emElement); return strSELFZONE03[emElement].c_str(); }

		const char* GETTARGZONE01 ( EMELEMENT emElement )		{  LIMIT(emElement); return strTARGZONE01[emElement].c_str(); }
		const char* GETTARGZONE02 ( EMELEMENT emElement )		{  LIMIT(emElement); return strTARGZONE02[emElement].c_str(); }
		const char* GETTARGZONE03 ( EMELEMENT emElement )		{  LIMIT(emElement); return strTARGZONE03[emElement].c_str(); }

		const char* GETSELFBODY ( EMELEMENT emElement )			{  LIMIT(emElement); return strSELFBODY[emElement].c_str(); }

		const char* GETTARGBODY01 ( EMELEMENT emElement )		{  LIMIT(emElement); return strTARGBODY01[emElement].c_str(); }
		const char* GETTARGBODY02 ( EMELEMENT emElement )		{  LIMIT(emElement); return strTARGBODY02[emElement].c_str(); }

		SEXT_DATA (void) :
			emANIMTYPE(AN_SKILL_A),
			emANISTYPE(AN_SUB_00),
			dwVal(7), //default val from official
			sICONINDEX(0,0),
			emTARG_POSA(EMPOS_GROUND),
			emTARG_POSB(EMPOS_GROUND),
			fDELAY4DAMAGE(0.0f),
			emSELFZONE01_POS(EMPOS_GROUND),
			emSELFZONE02_POS(EMPOS_GROUND),
			emSELFZONE03_POS(EMPOS_GROUND),
			emTARGZONE01_POS(EMPOS_GROUND),
			emTARGZONE02_POS(EMPOS_GROUND),
			emTARGZONE03_POS(EMPOS_GROUND),
			bTARG_ONE(false),
			emTARG(EMTIME_IMPACT),
			emSELFZONE01(EMTIME_FIRST),
			emSELFZONE02(EMTIME_IMPACT),
			emSELFZONE03(EMTIME_IMPACT),
			emTARGZONE01(EMTIME_TARG_OVR),
			emTARGZONE02(EMTIME_PASSIVE),
			emTARGZONE03(EMTIME_PASSIVE),
			emTARGBODY01(EMTIME_TARG_OVR),
			emTARGBODY02(EMTIME_PASSIVE),
			emSELFBODY(EMTIME_FIRST),
			sADDSKILL(NATIVEID_NULL()),
			dwADDSKILLLEVEL(0)
		{
		}

		void Assign ( const SEXT_DATA_100 &OldData );
		void Assign ( const SEXT_DATA_101 &OldData );
		void Assign ( const SEXT_DATA_102 &OldData );
		void Assign ( const SEXT_DATA_103 &OldData );
		void Assign ( const SEXT_DATA_104 &OldData );
		void Assign ( const SEXT_DATA_105 &OldData );
		void Assign ( const SEXT_DATA_106 &OldData );
		void Assign ( const SEXT_DATA_107 &OldData );
		void Assign ( const SEXT_DATA_108 &OldData );
		void Assign ( const SEXT_DATA_109 &OldData );

		BOOL SAVE ( CSerialFile &SFile );
		BOOL LOAD ( basestream &SFile );

		static VOID SaveCsvHead ( std::fstream &SFile );
		VOID SaveCsv ( std::fstream &SFile );
		VOID LoadCsv ( CStringArray &StrArray, int &iCsvCur );

		SEXT_DATA& operator= ( const SEXT_DATA &value );
	};
};

namespace COMMENT
{
	extern std::string SKILL_EFFTIME[SKILL::EMTIME_NSIZE];
	extern std::string SKILL_EFFPOS[SKILL::EMPOS_NSIZE];
};

#endif // GLSKILL_EXDATA_H_