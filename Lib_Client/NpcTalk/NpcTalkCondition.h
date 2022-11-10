///////////////////////////////////////////////////////////////////////
//	SNpcTalkCondition
//
//	���� �ۼ��� : ���⿱
//	���� ������ : 
//	�α�
//
//
///////////////////////////////////////////////////////////////////////

#pragma	once

#include "GLCharDefine.h"
#include <vector>
#include <string>

#include "NpcTalkData.h"

class basestream;
class CSerialFile;
struct GLCHARLOGIC;

//	�������� x��. 20 < x
enum EM_CONDITIONSIGN
{
	CONDITIONSIGN_NONE	=	0,	//	EMPTY
	CONDITIONSIGN_SAME,			//	=
	CONDITIONSIGN_HIGHER,		//	<
	CONDITIONSIGN_LOWER,		//	>
	CONDITIONSIGN_SAMEHIGHER,	//	<=
	CONDITIONSIGN_SAMELOWER,	//	>=

    CONDITIONSIGN_SIZE
};
extern	std::string	strCONDITIONSIGN[CONDITIONSIGN_SIZE];


template<class TYPE>
BOOL NumericCompare ( TYPE A, TYPE B, EM_CONDITIONSIGN sign )
{
	switch ( sign )
	{
	case CONDITIONSIGN_NONE:		return TRUE;

	case CONDITIONSIGN_SAME:		return A == B;
	case CONDITIONSIGN_HIGHER:		return A < B;
	case CONDITIONSIGN_LOWER:		return A > B;
	case CONDITIONSIGN_SAMEHIGHER:	return A <= B;
	case CONDITIONSIGN_SAMELOWER:	return A >= B;
	};

	return FALSE;
}



struct SNpcTalkCondition
{
	enum { VERSION = 0x0010, };

	typedef std::vector<SSkillCondition>	LEARNSKILL;
	typedef LEARNSKILL::iterator			LEARNSKILL_ITER;

	typedef std::vector<SNPC_ITEM>			HAVEITEM;
	typedef HAVEITEM::iterator				HAVEITEM_ITER;

	/*npc talk buff condition, Juver, 2017/10/02 */
	typedef std::vector<SNPC_BUFF>			HAVEBUFF;
	typedef HAVEBUFF::iterator				HAVEBUFF_ITER;

	typedef std::vector<DWORD>				PROCQUEST;
	typedef PROCQUEST::iterator				PROCQUEST_ITER;

	typedef std::vector<DWORD>				PROCSKILL;
	typedef PROCSKILL::iterator				PROCSKILL_ITER;

	bool				m_bEnable;			// unknown official data
	EM_CONDITIONSIGN	m_signLevel;		//	���� ����.
	WORD				m_wLevel;
	DWORD				m_dwClass;			//	Ŭ���� ����.
	WORD				m_wSchool;			//	�Ҽ��б�.
	EM_CONDITIONSIGN	m_signElemental;	//	ELEMENTAL
	int					m_nElemental;
	EM_CONDITIONSIGN	m_signActionPoint;	//	��Ȱ����.
	int					m_nActionPoint;
	BOOL				m_bTime;			//	�ð� ����.
	DWORD				m_dwTimeBegin;
	DWORD				m_dwTimeEnd;
	DWORD				m_dwMONEY;			//	�ʿ� ���� �ݾ�.
	DWORD				m_dwPARTYMEN_NUM;	//	�ʿ� ��Ƽ �ο�.
	DWORD				m_dwQUEST_NID;		//	�������� ����Ʈ ID.
	DWORD				m_dwQUEST_STEP;		//	�������� ����Ʈ STEP.
	PROCQUEST			m_vecCompleteQuest;	//	�Ϸ��ؾ߸� �ϴ� ����Ʈ.
	HAVEITEM			m_vecHaveItem;		//	���� ������.
	LEARNSKILL			m_vecLearnSkill;	//	���� ��ų.
	PROCQUEST			m_vecDisQuest;		//	�� ����Ʈ�� �ޱ� ���ؼ��� �������� �ʾƾ��� ����Ʈ.
	PROCSKILL			m_vecDisSkill;		//	�� ����Ʈ�� �ޱ� ���ؼ��� �������� �ʾƾ��� ��ų.
	HAVEBUFF			m_vecBuff;			/*npc talk buff condition, Juver, 2017/10/02 */

public:
	SNpcTalkCondition ();

public:
	void Reset ();
	SNpcTalkCondition& operator= ( const SNpcTalkCondition& rNpcTalkCondition );

public:
	BOOL IsTERM_LEVEL ()		{ return m_signLevel!=CONDITIONSIGN_NONE; }
	BOOL IsTERM_CLASS ()		{ return m_dwClass!=GLCC_NONE; }
	BOOL IsTERM_ELEMENTAL ()	{ return m_signElemental!=CONDITIONSIGN_NONE; }
	BOOL IsTERM_ACTIONP ()		{ return m_signActionPoint!=CONDITIONSIGN_NONE; }
	BOOL IsTERM_TIME ()			{ return m_bTime; }

	BOOL IsTERM_QUEST ()		{ return m_dwQUEST_NID!=UINT_MAX; }

	BOOL IsTERM_ITEM ()			{ return !m_vecHaveItem.empty(); }
	BOOL IsTERM_SKILL ()		{ return !m_vecLearnSkill.empty(); }

	/*npc talk buff condition, Juver, 2017/10/02 */
	BOOL IsTERM_NPCBUFF()		{ return !m_vecBuff.empty(); }

public:
	BOOL DoTEST ( GLCHARLOGIC *pCHARLOGIC );
	BOOL EmptyCondition();

	std::string GetBoolString ( BOOL bVALUE );
public:
	void GetConditionText( std::string& strName );

protected:
	BOOL LOAD_0001 ( basestream& SFile );
	BOOL LOAD_0002 ( basestream& SFile );
	BOOL LOAD_0003 ( basestream& SFile );
	BOOL LOAD_0004 ( basestream& SFile );
	BOOL LOAD_0005 ( basestream& SFile );
	BOOL LOAD_0006 ( basestream& SFile );
	BOOL LOAD_0007 ( basestream& SFile );
	BOOL LOAD_0008 ( basestream& SFile );
	BOOL LOAD_0009 ( basestream& SFile );
	BOOL LOAD_0010 ( basestream& SFile );

public:
	BOOL SAVE ( CSerialFile& SFile );
	BOOL LOAD ( basestream& SFile );

public:
	BOOL ADDHAVEITEM ( const SNPC_ITEM &sNpcItem );
	BOOL DELHAVEITEM ( DWORD dwNID );

	BOOL ADDLEARNSKILL ( const SSkillCondition &sSkillCondition );
	BOOL DELLEARNSKILL ( DWORD NativeID );

	BOOL ADDDISSKILL ( DWORD dwNID );
	BOOL DELDISSKILL ( DWORD dwNID );

	BOOL ADDDISQUEST ( DWORD dwNID );
	BOOL DELDISQUEST ( DWORD dwNID );

	BOOL ADDCOMQUEST ( DWORD dwNID );
	BOOL DELCOMQUEST ( DWORD dwNID );

	/*npc talk buff condition, Juver, 2017/10/02 */
	BOOL ADDBUFF ( const SNPC_BUFF &sNpcBuff );
	BOOL DELBUFF ( DWORD dwNID );

public:
	void RESET_QUEST ()
	{
		m_dwQUEST_NID = UINT_MAX;
		m_dwQUEST_STEP = 0;
	}
};

