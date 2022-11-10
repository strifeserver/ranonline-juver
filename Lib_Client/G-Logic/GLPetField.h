#pragma once

#include "./GLPet.h"
#include "./GLChar.h"

#include "../../Lib_Engine/G-Logic/GLList.h"

class GLPetField : public GLPET
{
public:
	Actor				m_actorMove;

	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vDirOrig;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_matTrans;

	PGLCHAR				m_pOwner;

	D3DXVECTOR3			m_vTarPos;

	DWORD				m_dwActionFlag;
	float				m_fTIMER;

	DWORD				m_dwOwnerCharID; // ������ ����(OnLine/OffLine) ������ ���� ���

protected:
	bool				m_bValid;
	PETDELAY_MAP		m_SKILLDELAY;
	WORD				m_wAniSub;

public:
	GLLandMan*				m_pLandMan;
	SGLNODE<GLPetField*>*	m_pLandNode;

	LANDQUADNODE*			m_pQuadNode;			//	���� Ʈ�� ���. ( ���� ������ ���� �����ϱ� ������. )
	SGLNODE<GLPetField*>*	m_pCellNode;			//	�� ����Ʈ ���.

	HMODULE m_hCheckStrDLL;
	BOOL (_stdcall *m_pCheckString)(CString);


public:
	GLPetField(void);
	~GLPetField(void);

	HRESULT Create ( GLLandMan* pLandMan, PGLCHAR pOwner, PGLPET pPetData );
	HRESULT SetPosition ( GLLandMan* pLandMan );

	HRESULT FrameMove( float fTime, float fElapsedTime );
	HRESULT DeleteDeviceObject ();

	HRESULT UpdateClientState ( float fElapsedTime );

	BOOL  IsSTATE ( DWORD dwStateFlag )		 			{ return m_dwActionFlag&dwStateFlag; }
	void  SetSTATE ( DWORD dwStateFlag )				{ m_dwActionFlag |= dwStateFlag; }
	void  ReSetSTATE ( DWORD dwStateFlag )				{ m_dwActionFlag &= ~dwStateFlag; }
	void  ReSetAllSTATE ()								{ m_dwActionFlag = 0; }

	void  SetPetID ( DWORD dwPetID )					{ m_dwPetID = dwPetID; }
	DWORD GetPetID ()									{ return m_dwPetID; }

	void	SetValid ()									{ m_bValid = true; }
	void	ReSetValid ()								{ m_bValid = false; }
	bool	IsValid ()									{ return m_bValid; }

	bool IsUsePetSkinPack() { return m_sPetSkinPackData.bUsePetSkinPack; }

	void	CleanUp ();

	bool	CheckSkill ( SNATIVEID sSkillID );
	void	AccountSkill ( SNATIVEID sSkillID );
	void	UpdateSkillDelay ( float fElapsedTime );

	/*dual pet skill, Juver, 2017/12/27 */
	void	UpdateSkillState_A ( float fElapsedTime );
	void	UpdateSkillState_B ( float fElapsedTime );

	void	ReSetSkillDelay ()							{ m_SKILLDELAY.clear(); }

	void	MsgProcess ( NET_MSG_GENERIC* nmg );

	// Access
	void	SetPosition ( D3DXVECTOR3 vPos ) { m_vPos = vPos; }

public:
	NET_MSG_GENERIC* ReqNetMsg_Drop ();

	HRESULT	MsgGoto ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgStop ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgUpdateMoveState ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgUpdateVelocity ( NET_MSG_GENERIC* nmg );
	HRESULT MsgUpdateState ( NET_MSG_GENERIC* nmg );
	HRESULT MsgChangeSkill ( NET_MSG_GENERIC* nmg );
	HRESULT MsgUpdateSkillState ( NET_MSG_GENERIC* nmg );

	HRESULT MsgRename ( NET_MSG_GENERIC* nmg );
	HRESULT RenameFeedBack ( NET_MSG_GENERIC* nmg );

	HRESULT	MsgChangeColor ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgChangeStyle ( NET_MSG_GENERIC* nmg );

	/*dual pet skill, Juver, 2017/12/27 */
	HRESULT	MsgChangeActiveSkill_A ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgChangeActiveSkill_B ( NET_MSG_GENERIC* nmg );

	HRESULT	MsgAccHoldExSlot ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgAccHoldToSlot ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgAccSlotToHold ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgLearnSkill ( NET_MSG_GENERIC* nmg );
	HRESULT	MsgRemoveSlotItem ( NET_MSG_GENERIC* nmg );
	HRESULT MsgPetSkinPackItem ( NET_MSG_GENERIC* nmg );

	/*enable pet skill at pet creation, Juver, 2017/12/13 */
	/*dual pet skill, Juver, 2017/12/27 */
	void	ChangePetSKill_A( SNATIVEID sidSkill );
	void	ChangePetSKill_B( SNATIVEID sidSkill );
};

typedef GLPetField* PGLPETFIELD;

typedef CGLLIST<PGLPETFIELD>	GLPETLIST;
typedef SGLNODE<PGLPETFIELD>	GLPETNODE;