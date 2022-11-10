#ifndef GLCROWDATA_ACTION_H_
#define GLCROWDATA_ACTION_H_

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


enum EMCROW_NPCACT
{
	EMCROWACT_TARSHORT	= 0x00004,
	EMCROWACT_CDCERTIFY	= 0x00008,

	EMCROWACT_INVISIBLE	= 0x00010,
	EMCROWACT_RECVISIBLE= 0x00020,
	EMCROWACT_BARRIER	= 0x00040,
	EMCROWACT_POSHOLD	= 0x00080,
	EMCROWACT_DIRHOLD	= 0x00100,

	EMCROWACT_KNOCK		= 0x00200,
	EMCROWACT_BOSS		= 0x00400,
	EMCROWACT_BUSUNIT	= 0x01000,

	EMCROWACT_IGNORE_SHOCK	= 0x10000,

	EMCROWACT_AUTODROP	= 0x20000,
};

enum EMCROWACT_UP
{
	EMCROWACT_UP_IDLE			= 0,
	EMCROWACT_UP_FIRSTSTRIKE	= 1,
	EMCROWACT_UP_LOWLEVEL		= 2,
	EMCROWACT_UP_LOWHP			= 3,
	EMCROWACT_UP_BRIGHT			= 4,
	EMCROWACT_UP_DARK			= 5,
	EMCROWACT_UP_BLOW			= 6,
	EMCROWACT_UP_ARMER			= 7,
	EMCROWACT_UP_RUNNER			= 8,
	EMCROWACT_UP_ESCAPE			= 9,

	EMCROWACT_UP_NSIZE			= 10
};

enum EMCROWACT_DN
{
	EMCROWACT_DN_CONTINUE		= 0,
	EMCROWACT_DN_LOWHP			= 1,
	EMCROWACT_DN_ESCAPE			= 2,

	EMCROWACT_DN_NSIZE			= 3,
};

struct SCROWPATTERN
{
	float				m_fPatternDNRate;
	EMCROWACT_UP		m_emActPattern;
	DWORD				m_dwPatternAttackSet;        

	SCROWPATTERN (void) :
	m_fPatternDNRate( 0.0f ),
		m_emActPattern( EMCROWACT_UP_IDLE ),
		m_dwPatternAttackSet( 0 )
	{

	}
};

class CROW_PATTERN_CMP
{
public:
	bool operator () ( const SCROWPATTERN &lvalue, const SCROWPATTERN &rvalue )
	{
		if( lvalue.m_fPatternDNRate > rvalue.m_fPatternDNRate ) return true;
		return false;
	}
};

struct SCROWACTION_100
{
	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	char				m_szSkinObj[ACF_SZNAME];		//	��Ų ����.
	char				m_szTalkFile[ACF_SZNAME];		//	��ȭ ����.

	BOOL				m_bTrade;						//	�ŷ���������.
	char				m_szSaleFile[ACF_SZNAME];		//	Item �Ǹ� ���.

	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	char				m_szFallingEffect[ACF_SZNAME];	//	�״� ������ ������ ȿ��.
	char				m_szBlowEffect[ACF_SZNAME];		//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.

	DWORD				m_dwActionUP;					//	�ൿ ���� HP 50%�̻�.
	DWORD				m_dwActionDN;					//	�ൿ ���� HP 50%����.

	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.

	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.
};

struct SCROWACTION_101
{
	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	char				m_szSkinObj[ACF_SZNAME];		//	��Ų ����.
	char				m_szTalkFile[ACF_SZNAME];		//	��ȭ ����.

	DWORD				m_dwActFlag;					//	���� �ൿ.
	char				m_szSaleFile[ACF_SZNAME];		//	Item �Ǹ� ���.

	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	char				m_szBirthEffect[ACF_SZNAME];	//	ź���� ������ ȿ��.
	char				m_szFallingEffect[ACF_SZNAME];	//	�״� ������ ������ ȿ��.
	char				m_szBlowEffect[ACF_SZNAME];		//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.

	EMCROWACT_UP		m_emActionUP;					//	�ൿ ���� HP 50%�̻�.
	EMCROWACT_DN		m_emActionDN;					//	�ൿ ���� HP 50%����.

	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.

	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.
};

struct SCROWACTION_102
{
	enum { SALENUM = 3 };
	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	char				m_szSkinObj[ACF_SZNAME];		//	��Ų ����.
	char				m_szTalkFile[ACF_SZNAME];		//	��ȭ ����.

	DWORD				m_dwActFlag;					//	���� �ൿ.
	char				m_szSaleFile[SALENUM][ACF_SZNAME];		//	Item �Ǹ� ���.

	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	char				m_szBirthEffect[ACF_SZNAME];	//	ź���� ������ ȿ��.
	char				m_szFallingEffect[ACF_SZNAME];	//	�״� ������ ������ ȿ��.
	char				m_szBlowEffect[ACF_SZNAME];		//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.

	EMCROWACT_UP		m_emActionUP;					//	�ൿ ���� HP 50%�̻�.
	EMCROWACT_DN		m_emActionDN;					//	�ൿ ���� HP 50%����.

	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.

	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.
};

struct SCROWACTION_103
{
	enum { VERSION = 0x0103, SALENUM = 3 };

	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	std::string			m_strSkinObj;					//	��Ų ����.
	std::string			m_strTalkFile;					//	��ȭ ����.

	DWORD				m_dwActFlag;					//	���� �ൿ.
	std::string			m_strSaleFile[SALENUM];			//	Item �Ǹ� ���.

	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	std::string			m_strBirthEffect;				//	ź���� ������ ȿ��.
	std::string			m_strFallingEffect;				//	�״� ������ ������ ȿ��.
	std::string			m_strBlowEffect;					//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.

	EMCROWACT_UP		m_emActionUP;					//	�ൿ ���� HP 50%�̻�.
	EMCROWACT_DN		m_emActionDN;					//	�ൿ ���� HP 50%����.

	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.

	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.
};

struct SCROWACTION_104
{
	enum { VERSION = 0x0104, SALENUM = 3 };

	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	std::string			m_strSkinObj;					//	��Ų ����.
	std::string			m_strTalkFile;					//	��ȭ ����.

	DWORD				m_dwActFlag;					//	���� �ൿ.
	std::string			m_strSaleFile[SALENUM];			//	Item �Ǹ� ���.

	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	std::string			m_strBirthEffect;				//	ź���� ������ ȿ��.
	std::string			m_strFallingEffect;				//	�״� ������ ������ ȿ��.
	std::string			m_strBlowEffect;					//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.

	EMCROWACT_UP		m_emActionUP;					//	�ൿ ���� HP 50%�̻�.
	EMCROWACT_DN		m_emActionDN;					//	�ൿ ���� HP 50%����.

	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.

	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.

	float				m_fLiveTime;					//  Ȱ�������� �ð�(EMCROWACT_AUTODROP �÷����� ���)
};

struct SCROWACTION_105
{
	enum { SALENUM = 3 };

	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	std::string			m_strSkinObj;					//	��Ų ����.
	std::string			m_strTalkFile;					//	��ȭ ����.

	DWORD				m_dwActFlag;					//	���� �ൿ.
	std::string			m_strSaleFile[SALENUM];			//	Item �Ǹ� ���.

	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	std::string			m_strBirthEffect;				//	ź���� ������ ȿ��.
	std::string			m_strFallingEffect;				//	�״� ������ ������ ȿ��.
	std::string			m_strBlowEffect;					//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.

	EMCROWACT_UP		m_emActionUP;					//	�ൿ ���� HP 50%�̻�.
	EMCROWACT_DN		m_emActionDN;					//	�ൿ ���� HP 50%����.

	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.

	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.

	float				m_fLiveTime;					//  Ȱ�������� �ð�(EMCROWACT_AUTODROP �÷����� ���)
	float				m_fActionDNRate;				// �ൿ ���� ���� %
};

struct SCROWACTION_106
{
	enum { SALENUM = 3 };

	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	std::string			m_strSkinObj;					//	��Ų ����.
	std::string			m_strTalkFile;					//	��ȭ ����.

	DWORD				m_dwActFlag;					//	���� �ൿ.
	std::string			m_strSaleFile[SALENUM];			//	Item �Ǹ� ���.

	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	std::string			m_strBirthEffect;				//	ź���� ������ ȿ��.
	std::string			m_strFallingEffect;				//	�״� ������ ������ ȿ��.
	std::string			m_strBlowEffect;					//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.

	EMCROWACT_UP		m_emActionUP;					//	�ൿ ���� HP 50%�̻�.
	EMCROWACT_DN		m_emActionDN;					//	�ൿ ���� HP 50%����.

	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.

	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.

	float				m_fLiveTime;					//  Ȱ�������� �ð�(EMCROWACT_AUTODROP �÷����� ���)
	float				m_fActionDNRate;				// �ൿ ���� ���� %

	BOOL				m_bMobLink;						// �ش���Ͱ� ������ ����Ǿ��ִ� ���͸� ȣ������ ����.
	SNATIVEID			m_sMobLinkID;					// ����� ������ ID
};

struct SCROWACTION_107
{
	enum { SALENUM = 3, PATTERNNUM = 10 };

	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	std::string			m_strSkinObj;					//	��Ų ����.
	std::string			m_strTalkFile;					//	��ȭ ����.

	DWORD				m_dwActFlag;					//	���� �ൿ.
	std::string			m_strSaleFile[SALENUM];			//	Item �Ǹ� ���.

	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	std::string			m_strBirthEffect;				//	ź���� ������ ȿ��.
	std::string			m_strFallingEffect;				//	�״� ������ ������ ȿ��.
	std::string			m_strBlowEffect;					//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.

	EMCROWACT_UP		m_emActionUP;					//	�ൿ ���� HP 50%�̻�.
	EMCROWACT_DN		m_emActionDN;					//	�ൿ ���� HP 50%����.

	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.

	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.

	float				m_fLiveTime;					//  Ȱ�������� �ð�(EMCROWACT_AUTODROP �÷����� ���)
	float				m_fActionDNRate;				// �ൿ ���� ���� %

	BOOL				m_bMobLink;						// �ش���Ͱ� ������ ����Ǿ��ִ� ���͸� ȣ������ ����.
	SNATIVEID			m_sMobLinkID;					// ����� ������ ID

	SCROWPATTERN		m_Pattern;						
	std::vector< SCROWPATTERN >	m_vecPatternList;
};

struct SCROWACTION_108
{
	enum { SALENUM = 3, PATTERNNUM = 10 };

	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	std::string			m_strSkinObj;					//	��Ų ����.
	std::string			m_strTalkFile;					//	��ȭ ����.

	DWORD				m_dwActFlag;					//	���� �ൿ.
	std::string			m_strSaleFile[SALENUM];			//	Item �Ǹ� ���.

	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	std::string			m_strBirthEffect;				//	ź���� ������ ȿ��.
	std::string			m_strFallingEffect;				//	�״� ������ ������ ȿ��.
	std::string			m_strBlowEffect;					//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.

	EMCROWACT_UP		m_emActionUP;					//	�ൿ ���� HP 50%�̻�.
	EMCROWACT_DN		m_emActionDN;					//	�ൿ ���� HP 50%����.

	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.

	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.

	float				m_fLiveTime;					//  Ȱ�������� �ð�(EMCROWACT_AUTODROP �÷����� ���)
	float				m_fActionDNRate;				// �ൿ ���� ���� %

	BOOL				m_bMobLink;						// �ش���Ͱ� ������ ����Ǿ��ִ� ���͸� ȣ������ ����.
	SNATIVEID			m_sMobLinkID;					// ����� ������ ID
	float				m_fMobLinkScale;				// ����� ���� ��ü ũ��
	float				m_fMobLinkDelay;				// ����� ���� ���� ������

	SCROWPATTERN		m_Pattern;						
	std::vector< SCROWPATTERN >	m_vecPatternList;
};

struct SCROWACTION_200
{
	enum { SALENUM = 3, PATTERNNUM = 10 };

	DWORD				m_dwActFlag;					//	���� �ൿ.
	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.
	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.
	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	std::string			m_strSkinObj;					//	��Ų ����.
	std::string			m_strTalkFile;					//	��ȭ ����.
	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	std::string			m_strBirthEffect;				//	ź���� ������ ȿ��.
	std::string			m_strFallingEffect;				//	�״� ������ ������ ȿ��.
	std::string			m_strBlowEffect;				//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.
	std::string			m_strSaleFile[SALENUM];			//	Item �Ǹ� ���.
	std::string			m_strShopFile;					/*npc shop, Juver, 2017/07/25 */
	float				m_fLiveTime;					//  Ȱ�������� �ð�(EMCROWACT_AUTODROP �÷����� ���)
	BOOL				m_bMobLink;						// �ش���Ͱ� ������ ����Ǿ��ִ� ���͸� ȣ������ ����.
	SNATIVEID			m_sMobLinkID;					// ����� ������ ID
	float				m_fMobLinkScale;				// ����� ���� ��ü ũ��
	float				m_fMobLinkDelay;				// ����� ���� ���� ������

	std::vector< SCROWPATTERN >	m_vecPatternList;
};

struct SCROWACTION
{
	enum { VERSION = 0x0201, SALENUM = 3, PATTERNNUM = 10, ACTION_MAXATTACK = 10 };

	DWORD				m_dwActFlag;					//	���� �ൿ.
	EMMOVETYPE			m_emMoveType;					//	�̵� Ÿ��.
	float				m_fDriftHeight;					//	�ξ� ����.
	float				m_fWalkVelo;					//	�̵� �ӵ�.
	BOOL				m_bRun;							//	�ٱ� ����.
	float				m_fRunVelo;						//	�ٱ� �ӵ�.
	WORD				m_wBodyRadius;					//	��ü���� �ݰ�.
	std::string			m_strSkinObj;					//	��Ų ����.
	std::string			m_strTalkFile;					//	��ȭ ����.
	BOOL				m_bAfterFall_NoBody;			//	�״� ������ ����ü �����. ( ȿ���� ��ä�ÿ� ���� )
	std::string			m_strBirthEffect;				//	ź���� ������ ȿ��.
	std::string			m_strFallingEffect;				//	�״� ������ ������ ȿ��.
	std::string			m_strBlowEffect;				//	Ÿ�ݽ� ����Ʈ, CROW �������� ������ �� �ְ�.
	std::string			m_strSaleFile[SALENUM];			//	Item �Ǹ� ���.
	std::string			m_strShopFile;					/*npc shop, Juver, 2017/07/25 */
	float				m_fLiveTime;					//  Ȱ�������� �ð�(EMCROWACT_AUTODROP �÷����� ���)
	BOOL				m_bMobLink;						// �ش���Ͱ� ������ ����Ǿ��ִ� ���͸� ȣ������ ����.
	SNATIVEID			m_sMobLinkID;					// ����� ������ ID
	float				m_fMobLinkScale;				// ����� ���� ��ü ũ��
	float				m_fMobLinkDelay;				// ����� ���� ���� ������
	
	std::vector< SCROWPATTERN >	m_vecPatternList;

	std::string			m_strItemExchangeFile;			/*item exchange, Juver, 2017/10/11 */

	SCROWACTION ( void ) :
		m_dwActFlag( NULL ),
		m_emMoveType( MOVE_LAND ),
		m_fDriftHeight( 0.0f ),
		m_fWalkVelo( 12.0f ),
		m_bRun( FALSE ),
		m_fRunVelo( 34.0f ),
		m_wBodyRadius( 4 ),
		m_bAfterFall_NoBody( FALSE ),
		m_fLiveTime( 0.0f ),
		m_bMobLink( FALSE ),
		m_sMobLinkID( NATIVEID_NULL() ),
		m_fMobLinkScale( 0.0f ),
		m_fMobLinkDelay( 0.0f )
	{
	}

	SCROWACTION ( const SCROWACTION &value )
	{
		operator = ( value );
	}

	SCROWACTION& operator= ( const SCROWACTION_100 &OldData );
	SCROWACTION& operator= ( const SCROWACTION_101 &OldData );
	SCROWACTION& operator= ( const SCROWACTION_102 &OldData );
	SCROWACTION& operator= ( const SCROWACTION &value );

	bool LOAD103 ( basestream &SFile );
	bool LOAD104 ( basestream &SFile );
	bool LOAD105 ( basestream &SFile );
	bool LOAD106 ( basestream &SFile );
	bool LOAD107 ( basestream &SFile );
	bool LOAD108 ( basestream &SFile );
	bool LOAD110 ( basestream &SFile );
	bool LOAD200 ( basestream &SFile );

	bool LOAD ( basestream &SFile );
	bool SAVE ( CSerialFile &SFile );

	static VOID SaveCsvHead ( std::fstream &SFile );
	VOID SaveCsv ( std::fstream &SFile );
	VOID LoadCsv ( CStringArray &StrArray, int& iCsvCur );
};

namespace COMMENT
{
	extern std::string szCROWACT_UP[EMCROWACT_UP_NSIZE];
	extern std::string szCROWACT_DN[EMCROWACT_DN_NSIZE];
};

#endif // GLCROWDATA_ACTION_H_