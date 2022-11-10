#include "stdafx.h"
#include "./GLGaeaserver.h"

#include ".\glsummonfield.h"

GLSummonField::GLSummonField(void) :
	m_vDir(D3DXVECTOR3(0,0,-1)),
	m_vDirOrig(D3DXVECTOR3(0,0,-1)),
	m_vPos(D3DXVECTOR3(0,0,0)),
	m_pLandMan(NULL),
	m_pLandNode(NULL),
	m_vTarPos(D3DXVECTOR3(0,0,0)),
	m_pOwner(NULL),
	m_Action(GLAT_IDLE),
	m_pQuadNode(NULL),
	m_pCellNode(NULL),
	m_dwActionFlag(0),
	m_fTIMER(0.0f),
	m_bValid(false),
	m_wAniSub(0),
	m_fattTIMER(0.0f),
	m_pAttackProp(NULL),
	m_fIdleTime(0.0f),
	m_dwOwnerCharID(0),
	m_fContinuousDamageCheck(0.0f), /*continuous damage skill logic, Juver, 2017/06/10 */

	/*skill summon, Juver, 2017/10/09 */
	m_fSummonLife(0.0f),
	m_fSummonDelay(0.0f),
	m_fOwnerCheckTime(0.0f),
	m_wTARNUM(0),
	m_vTARPOS(0,0,0)
{

	m_ARoundSlot.SetSummon ( this );
	m_TargetID.RESET();
	m_sHITARRAY.clear();
}

GLSummonField::~GLSummonField(void)
{
}

HRESULT GLSummonField::Create ( GLLandMan* pLandMan, PGLCHAR pOwner, PGLSUMMON pSummonData, D3DXVECTOR3 vtargetpos, SUMMON_DATA_SKILL *psummon_skill )
{
	if ( !pSummonData )		return E_FAIL;
	if ( !pLandMan )		return E_FAIL;
	if ( !pOwner )			return E_FAIL;
	if ( !psummon_skill )	return E_FAIL;

	ASSIGN ( *pSummonData );

	/*skill summon, Juver, 2017/10/09 */
	m_Summon = *psummon_skill;

	m_pSummonCrowData = GLCrowDataMan::GetInstance().GetCrowData ( m_sSummonID );
	if( !m_pSummonCrowData )
	{
		DEBUGMSG_WRITE ( _T("GLSummonField::Create, Mob Create Failed. nativeid [%d/%d]"), m_sSummonID.wMainID, m_sSummonID.wSubID );
		return E_FAIL;
	}

	// ��ȯ �ϰ����� ���¸� �ִ밪����
	m_dwNowHP = GETMAXHP();
	m_wNowMP  = GETMAXMP();

	m_Action = GLAT_IDLE;

	m_pOwner   = pOwner;
	m_pLandMan = pLandMan;

	SetValid ();

	//	Note : �� ���� ������ �ʱ�ȭ.
	GLSUMMON::INIT_DATA ();

	// ���� �ֺ�
	D3DXVECTOR3 vRandPos =  GetRandomPostision ();
	m_vPos = vRandPos + vtargetpos;

	// ����
	m_vDir = m_vPos - vtargetpos;
	D3DXVec3Normalize ( &m_vDir, &m_vDir );

	m_dwOwner = pOwner->m_dwGaeaID;
	m_sMapID  = pOwner->m_sMapID;

	m_dwOwnerCharID = pOwner->m_dwCharID;

	m_actorMove.Create ( m_pLandMan->GetNavi (), m_vPos, -1 );
	m_actorMove.Stop ();

	m_TargetID.RESET();
	m_sHITARRAY.clear();

	m_fattTIMER = 0.0f;

	m_fIdleTime = 0.0f;

	/*skill summon, Juver, 2017/10/09 */
	if ( m_Summon.bSummon )
	{
		m_fSummonLife = 0.0f;
		m_fSummonDelay = 0.0f;

		ReSetAllSTATE();
		SetSTATE( EM_SUMMONACT_WAITING );
		TurnAction( GLAT_IDLE );
	}

	return S_OK;
}

HRESULT GLSummonField::DeleteDeviceObject ()
{
	CleanUp ();
	return S_OK;
}

void GLSummonField::CleanUp ()
{
	m_vPos	   = D3DXVECTOR3(0,0,0);
	m_vDir	   = D3DXVECTOR3(0,0,-1);
	m_vDirOrig = D3DXVECTOR3(0,0,-1);

	m_pLandMan  = NULL;
	m_pLandNode = NULL;
	m_pQuadNode = NULL;
	m_pCellNode = NULL;

	m_wAniSub		= 0;
	m_fTIMER		= 0.0f;
	m_bValid		= false;
	m_dwActionFlag  = 0;
	m_dwOwnerCharID = 0;

	m_sHITARRAY.clear();
	m_actorMove.ResetMovedData();
	m_actorMove.Stop();
	m_actorMove.Release();

	m_fattTIMER = 0.0f;

	m_actorMove.Stop ();
	m_actorMove.Release ();

	m_pOwner	  = NULL;
	m_pAttackProp = NULL;

	m_vDir	     = D3DXVECTOR3 (0,0,-1);
	m_vPos	     = D3DXVECTOR3(0,0,0);
	m_vDirOrig   = D3DXVECTOR3(0,0,-1);

	ReSetAllSTATE ();
	SetSTATE ( EM_SUMMONACT_STOP );
	m_Action = GLAT_IDLE;

	m_TargetID.RESET();

	m_fattTIMER    = 0.0f;
	m_fIdleTime    = 0.0f;

	GLSUMMON::RESET_DATA();

	m_Action = GLAT_IDLE;

	m_ARoundSlot.Reset();

	/*skill summon, Juver, 2017/10/09 */
	m_fSummonLife = 0.0f;
	m_fSummonDelay = 0.0f;
	m_fOwnerCheckTime = 0.0f;

	m_wTARNUM = 0;
	for ( int i=0; i<EMTARGET_NET; ++i )
		m_sTARIDS[i] = STARID(CROW_PC,GAEAID_NULL);

	m_vTARPOS = D3DXVECTOR3(0,0,0);

	RESET ();
}

HRESULT GLSummonField::SetPosition ( GLLandMan* pLandMan )
{
	if ( !pLandMan )	return E_FAIL;

	m_pLandMan = pLandMan;

	SetValid ();

	// ���� �ֺ�
	D3DXVECTOR3 vRandPos, vOwnerPos; 
	vOwnerPos = m_pOwner->GetPosition ();
	vRandPos = GetRandomPostision ();
	m_vPos = vRandPos + vOwnerPos;

	// ����
	m_vDir = m_vPos - vOwnerPos;
	D3DXVec3Normalize ( &m_vDir, &m_vDir );

	m_sMapID  = m_pOwner->m_sMapID;

	m_actorMove.Create ( m_pLandMan->GetNavi (), m_vPos, -1 );
	m_actorMove.Stop ();

	return S_OK;
}

void GLSummonField::SetSTATE( DWORD dwStateFlag )
{ 

	m_dwActionFlag |= dwStateFlag; 
}

void GLSummonField::TurnAction ( EMACTIONTYPE toAction )
{
	//	Note : ���� �׼� ���(���������� �������� ����)
	//
	switch ( m_Action )
	{
	case GLAT_IDLE:
		break;

	case GLAT_FALLING:
		if ( toAction==GLAT_FALLING )	return;
		break;

	case GLAT_DIE:
		if ( toAction==GLAT_FALLING || toAction==GLAT_DIE )	return;
		break;

		/*push pull skill logic, Juver, 2017/06/05 */
	case GLAT_SKILLMOVE:
	case GLAT_SKILLDASH: /*dash skill logic, Juver, 2017/06/17 */
		{
			if ( toAction == GLAT_DIE || toAction == GLAT_FALLING ){
				if ( m_actorMove.PathIsActive() )		
					m_actorMove.Stop();
			}
		}break;

	case GLAT_ATTACK:
		{
			//	Note : ���ݼ����� ������ ������ ���.
			if ( m_pAttackProp )
			{
				if ( m_pAttackProp->skill_id != NATIVEID_NULL() )
				{
					//m_idACTIVESKILL = NATIVEID_NULL();
					//m_wTARNUM = 0;

					SNATIVEID sRunSkill = m_pAttackProp->skill_id;
					WORD wLevel = m_pAttackProp->skill_lev;

					//	Note : ��ų ���� ������.
					PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sRunSkill );
					if ( !pSkill )								break;
					if ( wLevel >= SKILL::MAX_LEVEL )			break;

					float fSkillDelay = pSkill->m_sAPPLY.sDATA_LVL[wLevel].fDELAYTIME;
					m_fACTIONDELAY[m_dwAType] = fSkillDelay + 0.1f;
				}
				else
				{	
					m_fACTIONDELAY[m_dwAType] = m_pAttackProp->fDelay + 0.3f;
				}
			}
		}break;

	default:
		break;
	};

	//	Note : �׼� �ʱ�ȭ.
	//
	m_Action = toAction;

	switch ( m_Action )
	{
	case GLAT_IDLE:
		m_fIdleTime = 0.0f;
		break;

	case GLAT_MOVE:
		break;

	case GLAT_ATTACK:
		{
			m_fattTIMER = 0.0f;

			if ( m_pAttackProp && m_pAttackProp->skill_id != NATIVEID_NULL() )
			{
				ACCOUNTSKILL ( 1 );
				PreStrikeProc( TRUE, FALSE );
			}
			else
			{
				PreStrikeProc( FALSE, FALSE );
			}
			
			if ( m_pAttackProp )
			{
				GLMSG::SNET_SUMMON_ATTACK NetMsg;
				NetMsg.dwGUID  = m_dwGUID; /*skill summon, Juver, 2017/10/09 */
				NetMsg.sTarID  = m_TargetID;
				NetMsg.dwAType = m_dwAType;
				NetMsg.sidSkill = m_pAttackProp->skill_id;
				NetMsg.wSkillLevel = m_Summon.wSkillLevel;
				NetMsg.vTARPOS = m_vTARPOS;
				NetMsg.wTARNUM = m_wTARNUM;
				for( int i=0; i<EMTARGET_NET; ++i )
					NetMsg.sTARIDS[i] = m_sTARIDS[i];
				GLGaeaServer::GetInstance().SENDTOCLIENT ( m_pOwner->m_dwClientID, &NetMsg );

				GLMSG::SNET_SUMMON_ATTACK_BRD NetMsgBRD;
				NetMsgBRD.dwGUID  = m_dwGUID;
				NetMsgBRD.dwAType = m_dwAType;
				NetMsgBRD.sTarID  = m_TargetID;
				NetMsgBRD.sidSkill = m_pAttackProp->skill_id;
				NetMsgBRD.wSkillLevel = m_Summon.wSkillLevel;
				NetMsgBRD.vTARPOS = m_vTARPOS;
				NetMsgBRD.wTARNUM = m_wTARNUM;
				for( int i=0; i<EMTARGET_NET; ++i )
					NetMsgBRD.sTARIDS[i] = m_sTARIDS[i];
				SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgBRD );
			}
			
			STARGETID sTargetID = STARGETID ( CROW_SUMMON, m_dwGUID, m_vPos );

			if( m_TargetID.emCrow == CROW_PC )
			{
				PGLCHAR pCHAR = GLGaeaServer::GetInstance().GetChar ( m_TargetID.dwID );
				if ( pCHAR )
				{
					// PET Attack ó��
					PGLPETFIELD pEnemyPet = GLGaeaServer::GetInstance().GetPET ( pCHAR->m_dwPetGUID );
					if ( pEnemyPet && pEnemyPet->IsValid () && !pEnemyPet->IsSTATE ( EM_PETACT_ATTACK ) )
					{
						D3DXVECTOR3 vOwnerPos, vDist;
						float fDist;
						vOwnerPos = pCHAR->GetPosition ();
						vDist = pEnemyPet->m_vPos - vOwnerPos;
						fDist = D3DXVec3Length(&vDist);

						// �����Ÿ� �ȿ� ������ 
						if ( fDist <= GLCONST_PET::fWalkArea )
						{
							pEnemyPet->ReSetAllSTATE ();
							pEnemyPet->SetSTATE ( EM_PETACT_ATTACK );

							GLMSG::SNETPET_ATTACK NetMsg;
							NetMsg.sTarID = sTargetID;
							GLGaeaServer::GetInstance().SENDTOCLIENT ( pCHAR->m_dwClientID, &NetMsg );

							GLMSG::SNETPET_ATTACK_BRD NetMsgBRD;
							NetMsgBRD.dwGUID = pEnemyPet->m_dwGUID;
							NetMsgBRD.sTarID = sTargetID;
							pCHAR->SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );
						}
					}
					// Summon Attack ó��

					/*skill summon, Juver, 2017/10/09 */
					for ( int ii=0; ii<SKILL_SUMMON_MAX_CLIENT_NUM; ++ii )
					{
						PGLSUMMONFIELD pEnemySummon = GLGaeaServer::GetInstance().GetSummon ( pCHAR->m_dwSummonGUID_FLD[ii] );
						if ( pEnemySummon && pEnemySummon->IsValid () && !pEnemySummon->IsSTATE ( EM_SUMMONACT_ATTACK ) && 
							pEnemySummon->GetAttackTarget( sTargetID ) && pEnemySummon->IsTargetReady() )
						{
							/*D3DXVECTOR3 vOwnerPos, vDist;
							float fDist;
							vOwnerPos = pCHAR->GetPosition ();
							vDist = pEnemySummon->m_vPos - vOwnerPos;
							fDist = D3DXVec3Length(&vDist);

							if ( fDist <= pEnemySummon->m_fWalkArea )*/
							{
								pEnemySummon->SetAttackTarget( sTargetID );
							}
						}
					}
				}
			}
		}break;

	case GLAT_FALLING:
		m_fIdleTime = 0.0f;
		break;

	case GLAT_PUSHPULL:
	case GLAT_SKILLMOVE: /*push pull skill logic, Juver, 2017/06/05 */
	case GLAT_SKILLDASH: /*dash skill logic, Juver, 2017/06/17 */
		m_fIdleTime = 0.0f;
		break;

	case GLAT_DIE:
		break;

	case GLAT_SHOCK:
		m_fIdleTime = 0.0f;
		break;

	default:
		GASSERT("GLCharacter::TurnAction() �غ���� ���� ACTION �� ���Խ��ϴ�.");
		break;
	};

	if ( m_actorMove.PathIsActive() )
	{
		/*push pull skill logic, Juver, 2017/06/05 */
		/*dash skill logic, Juver, 2017/06/17 */
		if ( !IsACTION(GLAT_MOVE) && !IsACTION(GLAT_PUSHPULL) && !IsACTION(GLAT_SKILLMOVE) && !IsACTION(GLAT_SKILLDASH) ) m_actorMove.Stop();
	}
}

HRESULT GLSummonField::UpdateTurnAction( float fElapsedTime )
{
	HRESULT hr(S_OK);

	/*skill summon, Juver, 2017/10/10 */
	if ( IsSTATE( EM_SUMMONACT_WAITING ) )	return S_OK;

	if( m_TargetID.dwID != EMTARGET_NULL && !( IsACTION( GLAT_DIE ) || IsACTION( GLAT_FALLING ) ) )
	{
		GLACTOR *pTARGET = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, m_TargetID );
		if ( !pTARGET )
		{
			m_TargetID.RESET();
			TurnAction( GLAT_IDLE );
			ReSetAllSTATE();
			SetSTATE( EM_SUMMONACT_STOP );
		}else{

			if( !pTARGET->IsValidBody() )
			{
				m_TargetID.RESET();
				TurnAction( GLAT_IDLE );
				ReSetAllSTATE();
				SetSTATE( EM_SUMMONACT_STOP );
			}else{
				D3DXVECTOR3 vDist = pTARGET->GetPosition () - m_vPos;
				float		fDist = D3DXVec3Length( &vDist );

				WORD wAttackRange = pTARGET->GetBodyRadius() + GETSUMMON_BODYRADIUS() + GETSUMMON_ATTACKRANGE() + 2;
				if ( m_pAttackProp && m_pAttackProp->skill_id != NATIVEID_NULL() )
				{
					PGLSKILL pskill_summon = GLSkillMan::GetInstance().GetData( m_pAttackProp->skill_id );
					if ( pskill_summon )
						wAttackRange += GETSKILLRANGE_APPLY(*pskill_summon,m_wACTIVESKILL_LVL) + 2;
				}

				/*skill summon, Juver, 2017/10/10 */
				if( fDist <= wAttackRange && !IsACTION( GLAT_ATTACK ) )
				{
					if ( IsSTATE(EM_SUMMONACT_TRACING) ) {

						if ( m_pAttackProp && m_pAttackProp->skill_id != NATIVEID_NULL() )
						{
							EMSKILLCHECK emSkillCheck = CHECHSKILL ( m_dwAType );
							if ( emSkillCheck == EMSKILL_OK || emSkillCheck == EMSKILL_NOTSP)
							{
								TurnAction( GLAT_ATTACK );
								ReSetAllSTATE();
								SetSTATE( EM_SUMMONACT_ATTACK );
							}
						}
						else
						{
							TurnAction( GLAT_ATTACK );
							ReSetAllSTATE();
							SetSTATE( EM_SUMMONACT_ATTACK );
						}	
					}
					else {
						SetAttackTarget( m_TargetID );
					}
				}	
			}
		}
	}

	switch ( m_Action )
	{
	case GLAT_IDLE:
		m_fIdleTime += fElapsedTime;
		break;

	case GLAT_TALK:
		break;

	case GLAT_MOVE:
		{
			//	Note : �ɸ��� �̵� ������Ʈ.
			//
			hr = m_actorMove.Update ( fElapsedTime );
			if ( FAILED(hr) )	return E_FAIL;

			if ( !m_actorMove.PathIsActive() ) m_actorMove.Stop ();

			// ���� ������Ʈ
			D3DXVECTOR3 vMovement = m_actorMove.NextPosition();
			if ( vMovement.x != FLT_MAX && vMovement.y != FLT_MAX && vMovement.z != FLT_MAX )
			{
				D3DXVECTOR3 vDirection = vMovement - m_vPos;
				if ( !DxIsMinVector(vDirection,0.2f) )
				{
					D3DXVec3Normalize ( &vDirection, &vDirection );
					m_vDir = vDirection;
				}
			}			
		}
		break;

	case GLAT_ATTACK:
		{
			if ( !AttackProcess ( fElapsedTime ) )
			{
				SetSTATE( EM_SUMMONACT_STOP );
				TurnAction( GLAT_IDLE );
				//				m_TargetID.RESET();
			}

			//	Note : ���� �������� ȸ��.
			//
			GLACTOR* pACTOR = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, m_TargetID );
			if ( pACTOR )
			{
				D3DXVECTOR3 vDirection = pACTOR->GetPosition() - m_vPos;
				D3DXVec3Normalize ( &vDirection, &vDirection );
				m_vDir = vDirection;
			}
		}
		break;

		//case GLAT_SKILL:
		//	{
		//		if ( !SkillProcess ( fElapsedTime ) )
		//		{
		//			TurnAction ( GLAT_IDLE, false );
		//		}
		//	}
		//	break;

	case GLAT_SHOCK:
		if ( !ShockProcess ( fElapsedTime ) )	
		{
			TurnAction( GLAT_IDLE );
			SetSTATE( EM_SUMMONACT_STOP );
		}
		break;

	case GLAT_FALLING:
		m_fIdleTime += fElapsedTime;
		if ( m_fIdleTime > 4.0f )	TurnAction ( GLAT_DIE );
		break;

	case GLAT_PUSHPULL:
	case GLAT_SKILLMOVE: /*push pull skill logic, Juver, 2017/06/05 */
	case GLAT_SKILLDASH: /*dash skill logic, Juver, 2017/06/17 */
		{
			//m_actorMove.SetMaxSpeed ( GLCONST_CHAR::fPUSHPULL_VELO );
			m_actorMove.Update ( fElapsedTime );
			if ( !m_actorMove.PathIsActive() )
			{
				m_actorMove.Stop ();
				TurnAction( GLAT_IDLE );
				SetSTATE( EM_SUMMONACT_STOP );
			}

			//	Note : Mob�� ���� ��ġ ������Ʈ.
			//
			m_vPos = m_actorMove.Position();
		}
		break;

	case GLAT_DIE:
		break;
	case GLAT_GATHERING:
		break;
	};

	return S_OK;
}

HRESULT GLSummonField::FrameMove( float fTime, float fElapsedTime )
{
	HRESULT hr(S_OK);
	static float fTimer(0.0f);

	if ( m_dwAType < SCROWDATA::EMMAXATTACK )
		m_pAttackProp = &(m_pSummonCrowData->m_sCrowAttack[m_dwAType]);
	
	for ( int i=0; i<SCROWDATA::EMMAXATTACK; ++i )
	{
		if ( m_fACTIONDELAY[i] > 0.0f )
			m_fACTIONDELAY[i] -= fElapsedTime;
	}

	/*continuous damage skill logic, Juver, 2017/06/10 */
	if ( m_pLandMan )
	{
		for( CONTINUOUS_DAMAGE_DATA_MAP_ITER iterdamage = m_mapContinuousDamage.begin();
			iterdamage != m_mapContinuousDamage.end(); ++iterdamage )
		{
			SCONTINUOUS_DAMAGE_DATA& sContinuousDamageData = (*iterdamage).second;
			sContinuousDamageData.fAge += fElapsedTime;

			if ( sContinuousDamageData.fAge >= sContinuousDamageData.fInterval )
			{
				SSKILLACT sSKILLACTCD;
				sSKILLACTCD.sID.dwID = sContinuousDamageData.dwCrowID;
				sSKILLACTCD.sID.emCrow = (EMCROW)sContinuousDamageData.wCrow;
				sSKILLACTCD.sID.vPos = m_vPos;
				sSKILLACTCD.sID_TAR.dwID = m_dwGUID;
				sSKILLACTCD.sID_TAR.emCrow = GETCROW();
				sSKILLACTCD.sID_TAR.vPos = m_vPos;

				sSKILLACTCD.fDELAY = 0.0f;
				sSKILLACTCD.emAPPLY = SKILL::EMAPPLY_PHY_LONG;
				sSKILLACTCD.nVAR_HP = (int)-sContinuousDamageData.fVar;
				sSKILLACTCD.dwDamageFlag = DAMAGE_TYPE_NONE;		

				if ( sSKILLACTCD.VALID() )
				{
					m_pLandMan->RegSkillAct ( sSKILLACTCD );
				}

				sContinuousDamageData.fAge = 0.0f;
			}
		}

		m_fContinuousDamageCheck += fElapsedTime;
		if ( m_fContinuousDamageCheck >= 1.0f )
		{
			for( CONTINUOUS_DAMAGE_DATA_MAP_ITER iterdamage = m_mapContinuousDamage.begin();
				iterdamage != m_mapContinuousDamage.end(); ++iterdamage )
			{
				SCONTINUOUS_DAMAGE_DATA sContinuousDamageData = (*iterdamage).second;
				
				BOOL _bFIND = FALSE;
				for( int _sf=0; _sf<SKILLFACT_SIZE; ++_sf )
				{
					if ( m_sSKILLFACT[_sf].sNATIVEID != NATIVEID_NULL() &&
						m_sSKILLFACT[_sf].sNATIVEID == sContinuousDamageData.sidSkill )
						_bFIND  = TRUE;
				}

				if ( !_bFIND )
					CONTINUOUSDAMAGE_DELETE( sContinuousDamageData.sidSkill );
			}

			m_fContinuousDamageCheck = 0.0f;
		}
	}
	
	/*block back damage, Juver, 2017/12/12 */
	if ( m_bBlockBackDamage && RANPARAM::bFeatureBlockDamageBack )
	{
		m_fBlockBackDamageTime += fElapsedTime;
		if ( m_fBlockBackDamageTime >= RANPARAM::fFeatureBlockDamageBackTimer )
		{
			m_bBlockBackDamage = false;
			m_fBlockBackDamageTime = 0.0f;
		}
	}

	if ( IsValidBody () )
	{
		/*skill summon, Juver, 2017/10/09 */
		if ( IsSTATE( EM_SUMMONACT_WAITING ) )
		{
			m_fSummonDelay += fElapsedTime;
			if ( m_fSummonDelay >= m_Summon.fDelay )
			{
				ReSetAllSTATE();
				SetSTATE( EM_SUMMONACT_STOP );
				TurnAction( GLAT_IDLE );


				m_fSummonDelay = 0.0f;
				m_fSummonLife = 0.0f;

				if ( m_pOwner )
				{
					GLMSG::SNET_SUMMON_END_REST NetMsg;
					NetMsg.dwGUID  = m_dwGUID;
					GLGaeaServer::GetInstance().SENDTOCLIENT ( m_pOwner->m_dwClientID, &NetMsg );

					GLMSG::SNET_SUMMON_END_REST_BRD NetMsgBRD;
					NetMsgBRD.dwGUID  = m_dwGUID;
					SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgBRD );
				}

				STARGETID starget_id;
				starget_id.emCrow  = m_Summon.sTarget.GETCROW();
				starget_id.dwID = m_Summon.sTarget.GETID();
				SetAttackTarget( starget_id );
			}
		}
		
		/*skill summon, Juver, 2017/10/09 */
		if ( !IsSTATE( EM_SUMMONACT_WAITING ) && m_dwNowHP != 0 )
		{	
			m_fSummonLife += fElapsedTime;
			if ( m_fSummonLife >= m_Summon.fLife )
			{
				m_dwNowHP = 0;

				if ( m_pOwner )
				{
					GLMSG::SNET_SUMMON_END_LIFE NetMsg;
					NetMsg.dwGUID  = m_dwGUID; 
					GLGaeaServer::GetInstance().SENDTOCLIENT ( m_pOwner->m_dwClientID, &NetMsg );

					GLMSG::SNET_SUMMON_END_LIFE_BRD NetMsgBRD;
					NetMsgBRD.dwGUID  = m_dwGUID;
					SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgBRD );
				}
			}
		}

		if ( m_dwNowHP!=0 )
		{
			m_ARoundSlot.Update ( m_pLandMan );

			// Summon �� ���� ���°����� Update �Ѵ�
			GLSUMMON::UPDATE_DATA ( fTime, fElapsedTime );
		}else{

			//	���� ��ȭ.

			TurnAction ( GLAT_FALLING );
		}
	}

	/*skill summon, Juver, 2017/10/10 */
	m_fOwnerCheckTime += fElapsedTime;
	if ( m_fOwnerCheckTime >= SUMMON_VALID_CHECK_TIME )
	{
		m_fOwnerCheckTime = 0.0f;

		if ( m_pOwner )
		{
			if ( !m_pOwner->isMySummon( m_dwGUID ) )
			{
				CDebugSet::ToFileWithTime( "_summon.txt", "summon stuck no longer connected to owner id:%d owner:%d", m_dwGUID, m_dwOwnerCharID );
				m_dwNowHP = 0;
				TurnAction ( GLAT_FALLING );
			}
		}
		else
		{
			CDebugSet::ToFileWithTime( "_summon.txt", "summon stuck no longer have owner id:%d owner:%d", m_dwGUID, m_dwOwnerCharID );
			m_dwNowHP = 0;
			TurnAction ( GLAT_FALLING );
		}
	}

	UpdateTurnAction( fElapsedTime );

	// ���� ��ġ ������Ʈ
	m_vPos = m_actorMove.Position();

	return S_OK;
}

BOOL GLSummonField::AttackProcess ( float fElapsedTime )
{
	GASSERT(m_pAttackProp);
	m_fattTIMER += fElapsedTime/* * GETATTVELO()*/;

	SANIATTACK &sAniAttack = m_pAttackProp->sAniAttack;
	int wTotalKeys = int(sAniAttack.m_dwETime) - int(sAniAttack.m_dwSTime);
	int wThisKey = int(m_fattTIMER*UNITANIKEY_PERSEC);

	if ( GetAttackRangeType()==EMATT_SHORT )
	{
		GLACTOR *pTARGET = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, m_TargetID );
		if ( !pTARGET )
		{
			TurnAction ( GLAT_IDLE );
			SetSTATE( EM_SUMMONACT_STOP );
			m_TargetID.RESET();
			return FALSE;
		}

		D3DXVECTOR3 vDist = m_vPos - pTARGET->GetPosition();
		float fTarLength = D3DXVec3Length(&vDist);

		WORD wAttackRange = pTARGET->GetBodyRadius() + GETSUMMON_BODYRADIUS() + GETSUMMON_ATTACKRANGE() + 2;

		if ( m_pAttackProp && m_pAttackProp->skill_id != NATIVEID_NULL() )
		{
			PGLSKILL pskill_summon = GLSkillMan::GetInstance().GetData( m_pAttackProp->skill_id );
			if ( pskill_summon )
				wAttackRange += GETSKILLRANGE_APPLY(*pskill_summon,m_wACTIVESKILL_LVL) + 2;
		}

		if ( wAttackRange*GLCONST_CHAR::fREACT_VALID_SCALE < (WORD)(fTarLength) )
		{
			TurnAction ( GLAT_IDLE );
			SetSTATE( EM_SUMMONACT_STOP );
			return FALSE;
		}
	}

	if ( !m_sHITARRAY.empty() )
	{
		SSTRIKE sStrike = *m_sHITARRAY.begin();

		if ( wThisKey >= sStrike.wDivKey )
		{
			if ( sStrike.bHit )
			{
				if ( m_pAttackProp && m_pAttackProp->skill_id != NATIVEID_NULL() )
				{
					SkillProc();
				}
				else
				{
					int nDamage = 0;
					DWORD dwDamageFlag = DAMAGE_TYPE_NONE;
					dwDamageFlag = GLSUMMON::CALCDAMAGE ( nDamage, m_dwGUID, m_TargetID, m_pLandMan, NULL, 0, NULL, sAniAttack.m_wDivCount );
					DamageProc ( nDamage, dwDamageFlag );
				}
				
			}
			else					AvoidProc ();

			//	ť ����Ÿ�� ó���� ��� �����Ѵ�.
			m_sHITARRAY.pop_front ();
		}	
	}

	//	�̻����� ���� ����Ÿ�� ���� ó������ �������,
	//	�������� �Ѳ����� ó���ϰ�, FALSE�� �����Ѵ�.
	if ( wThisKey >= wTotalKeys )
	{
		if ( !m_sHITARRAY.empty() )
		{
			while ( !m_sHITARRAY.empty() )
			{
				SSTRIKE sStrike = *m_sHITARRAY.begin();

				if ( sStrike.bHit )
				{
					if ( m_pAttackProp && m_pAttackProp->skill_id != NATIVEID_NULL() )
					{
						SkillProc();
					}
					else
					{
						int nDamage = 0;
						DWORD dwDamageFlag = DAMAGE_TYPE_NONE;
						dwDamageFlag = GLSUMMON::CALCDAMAGE ( nDamage, m_dwGUID, m_TargetID, m_pLandMan, NULL, 0, NULL, sAniAttack.m_wDivCount );
						DamageProc ( nDamage, dwDamageFlag );
					}
				}
				else					AvoidProc ();

				//	ť ����Ÿ�� ó���� ��� �����Ѵ�.
				m_sHITARRAY.pop_front ();
			}
		}

		return FALSE;
	}

	return TRUE;
}



inline DWORD GLSummonField::ToDamage ( const STARGETID &sTargetID, const int nDAMAGE, const BOOL bShock )
{
	GLACTOR* pACTOR_TAR = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, sTargetID );
	if ( !pACTOR_TAR )	return 0;

	//	Note : Ÿ���� ���� ������ ��쿡 damage �ټ� ����.
	//
	if ( CROW_PC==sTargetID.emCrow && !pACTOR_TAR->IsValidBody() )	return 0;

	return pACTOR_TAR->ReceiveDamage ( GLSUMMON::GETCROW(), m_dwGUID, nDAMAGE, bShock );
}

void GLSummonField::AvoidProc ( )
{
	//	Note : �ֺ� Ŭ���̾�Ʈ�鿡�� �޼��� ����.
	//
	//	Note : �ڽſ���.
	GLMSG::SNET_SUMMON_ATTACK_AVOID NetMsg;
	NetMsg.emTarCrow	= m_TargetID.emCrow;
	NetMsg.dwTarID		= m_TargetID.dwID;

	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_pOwner->m_dwClientID, (NET_MSG_GENERIC*) &NetMsg );

	SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsg );
}

void GLSummonField::DamageProc ( const int nDAMAGE, DWORD dwDamageFlag )
{
	//	Note : ����ڿ��� ������� ����.
	bool bShock = ( dwDamageFlag & DAMAGE_TYPE_SHOCK );
	DWORD dwNowHP = ToDamage ( m_TargetID, nDAMAGE, bShock );

	//	Note : �ֺ� Ŭ���̾�Ʈ�鿡�� �޼��� ����.
	//
	//	Note : �ڽſ���.
	GLMSG::SNET_SUMMON_ATTACK_DAMAGE NetMsg;
	NetMsg.emTarCrow		= m_TargetID.emCrow;
	NetMsg.dwTarID			= m_TargetID.dwID;
	NetMsg.nDamage			= nDAMAGE;
	NetMsg.dwDamageFlag		= dwDamageFlag;
	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_pOwner->m_dwClientID, (NET_MSG_GENERIC*) &NetMsg );

	//	Note : �ֺ� Ŭ���̾�Ʈ�鿡�� �޼��� ����.
	//
	SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsg );

	GLACTOR* pACTOR = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, m_TargetID );

	//	Note : ���� �̻� ����.
	//
	if ( pACTOR && m_pAttackProp->emBLOW_TYPE!=EMBLOW_NONE )
	{
		//	Note : �߻� Ȯ�� ���.
		//
		short nBLOWRESIST = pACTOR->GETRESIST().GetElement ( STATE_TO_ELEMENT(m_pAttackProp->emBLOW_TYPE) );
		if ( nBLOWRESIST>99 )	nBLOWRESIST = 99;

		//		float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( m_pAttackProp->emBLOW_TYPE, GLPeriod::GetInstance().GetWeather(), m_pLandMan->IsWeatherActive() );
		DWORD dwWeather = GLPeriod::GetInstance().GetMapWeather( m_pLandMan->GetMapID().wMainID, m_pLandMan->GetMapID().wSubID );
		float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( m_pAttackProp->emBLOW_TYPE, dwWeather, m_pLandMan->IsWeatherActive() );

		BOOL bBLOW = FALSE;
		if ( !(pACTOR->GETHOLDBLOW()&STATE_TO_DISORDER(m_pAttackProp->emBLOW_TYPE)) )
		{
			bBLOW = GLOGICEX::CHECKSTATEBLOW ( m_pAttackProp->fBLOW_RATE*fPOWER, GLSUMMON::GETLEVEL(), pACTOR->GetLevel(), nBLOWRESIST );
		}

		if ( bBLOW )
		{
			//	Note : �����̻� �߻�.
			//	
			SSTATEBLOW sSTATEBLOW;
			float fLIFE = m_pAttackProp->fBLOW_LIFE * fPOWER;
			fLIFE = ( fLIFE - (fLIFE*nBLOWRESIST*0.01f*GLCONST_CHAR::fRESIST_G ) );

			sSTATEBLOW.emBLOW = m_pAttackProp->emBLOW_TYPE;
			sSTATEBLOW.fAGE = fLIFE;
			sSTATEBLOW.fSTATE_VAR1 = m_pAttackProp->fBLOW_VAR1;
			sSTATEBLOW.fSTATE_VAR2 = m_pAttackProp->fBLOW_VAR2;

			pACTOR->STATEBLOW ( sSTATEBLOW );

			//	Note : �����̻� �߻� Msg.
			//
			GLMSG::SNETPC_STATEBLOW_BRD NetMsgState;
			NetMsgState.emCrow = m_TargetID.emCrow;
			NetMsgState.dwID = m_TargetID.dwID;
			NetMsgState.emBLOW = sSTATEBLOW.emBLOW;
			NetMsgState.fAGE = fLIFE;
			NetMsgState.fSTATE_VAR1 = sSTATEBLOW.fSTATE_VAR1;
			NetMsgState.fSTATE_VAR2 = sSTATEBLOW.fSTATE_VAR2;

			//	Note : '��ų���'�� �ֺ� Ŭ���̾�Ʈ�鿡�� �޼��� ����.
			//
			pACTOR->SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgState );

			//	Note : ��ų ��󿡰� �޼��� ����.
			if ( m_TargetID.emCrow==CROW_PC )	GLGaeaServer::GetInstance().SENDTOCLIENT ( pACTOR->GETCLIENTID (), &NetMsgState );
		}
	}

	/*curse skill logic, Juver, 2017/06/11 */
	if ( pACTOR )
	{
		if ( m_pLandMan && m_bCurse && m_fCurseDamage != 0.0f )
		{
			int _nCurseDamage = int(nDAMAGE*m_fCurseDamage);

			SSKILLACT sSKILLACTCURSE;
			sSKILLACTCURSE.sID = m_TargetID;
			sSKILLACTCURSE.sID_TAR = STARGETID(CROW_SUMMON,m_dwGUID);
			sSKILLACTCURSE.fDELAY = 0.2f;
			sSKILLACTCURSE.emAPPLY = SKILL::EMAPPLY_PHY_LONG;
			sSKILLACTCURSE.nVAR_HP = -_nCurseDamage;
			sSKILLACTCURSE.dwDamageFlag = DAMAGE_TYPE_NONE;		

			if ( sSKILLACTCURSE.VALID() )
			{
				m_pLandMan->RegSkillAct ( sSKILLACTCURSE );
			}
		}
	}
}

BOOL GLSummonField::IsValidBody () const
{
	return ( m_Action < GLAT_FALLING );
}

BOOL GLSummonField::IsDie () const
{
	if ( m_Action==GLAT_DIE )		
		return TRUE;

	return FALSE;
}


void GLSummonField::PreAttackProc ()
{
	SANIATTACK &sAniAttack = m_pAttackProp->sAniAttack;

	m_sHITARRAY.clear ();

	for ( int i = 0; i < sAniAttack.m_wDivCount; i++ )
	{
		bool bhit = GLSUMMON::CHECKHIT(m_TargetID,m_pLandMan) ? true : false;
		m_sHITARRAY.push_back ( SSTRIKE(sAniAttack.m_wDivFrame[i],bhit) );
	}
}

void GLSummonField::PreStrikeProc ( BOOL bSkill, BOOL bLowSP )
{
	SANIATTACK &sAniAttack = m_pAttackProp->sAniAttack;

	m_sHITARRAY.clear ();

	STARGETID sTargetID;
	BOOL bCheckHit = FALSE;

	if ( !bSkill )
	{
		sTargetID = m_TargetID;
		bCheckHit = TRUE;
	}
	else
	{
		//	Note : ��ų ���� ������.
		//
		PGLSKILL pSkill = NULL;
		pSkill = GLSkillMan::GetInstance().GetData ( m_idACTIVESKILL.wMainID, m_idACTIVESKILL.wSubID );
		if ( pSkill && pSkill->m_sBASIC.emAPPLY != SKILL::EMAPPLY_MAGIC )
		{
			//	Note : ��ų Ÿ���� �ϳ��� ��ȿ�ϰ� Ȯ���� �ϰ� ����.
			//	NEED : ���� Ÿ���� ��� �ٽ� Ȯ���ؾ���.
			sTargetID = STARGETID(static_cast<EMCROW>(m_sTARIDS[0].wCrow),static_cast<DWORD>(m_sTARIDS[0].wID));
			bCheckHit = TRUE;
		}
		else
		{
			sTargetID.dwID = EMTARGET_NULL;
		}
	}

	//	ť �ʱ�ȭ
	m_sHITARRAY.clear ();

	for ( int i = 0; i < sAniAttack.m_wDivCount; i++ )
	{
		bool bhit = true;
		if ( bCheckHit && (sTargetID.dwID!=EMTARGET_NULL) )
		{
			if ( !GLSUMMON::CHECKHIT(sTargetID,m_pLandMan) )		bhit = false;
		}

		m_sHITARRAY.push_back ( SSTRIKE(sAniAttack.m_wDivFrame[i],bhit) );
	}
}

bool GLSummonField::GetAttackTarget( STARGETID sTargetID ) 
{ 
	if( m_TargetID.dwID != EMTARGET_NULL ) 
	{
		if( GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, m_TargetID ) == NULL )
		{
			m_TargetID.RESET();
			return TRUE;
		}

		if( m_TargetID == sTargetID ) return TRUE;
		else						  return FALSE;
	}

	return TRUE; 
}

void GLSummonField::ResetAttackTarget()
{ 
	m_TargetID.RESET();
	TurnAction( GLAT_IDLE );
	ReSetAllSTATE();
	SetSTATE( EM_SUMMONACT_STOP );

	if ( m_pOwner )
	{
		GLMSG::SNET_SUMMON_RESET_TARGET NetMsg;
		NetMsg.dwGUID  = m_dwGUID;
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_pOwner->m_dwClientID, &NetMsg );

		GLMSG::SNET_SUMMON_RESET_TARGET_BRD NetMsgBRD;
		NetMsgBRD.dwGUID  = m_dwGUID;
		SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgBRD );
	}
}

DWORD GLSummonField::ReceiveDamage ( const EMCROW emACrow, const DWORD dwAID, const DWORD dwDamage, const BOOL bShock )
{
	if ( !IsValid() )		return m_dwNowHP;
	if ( m_dwNowHP == 0 )	return m_dwNowHP;

	//	Note : ���� ������ ���� ����?
	//		( emACrow, dwAID )
	WORD wDxHP = GLSUMMON::RECEIVE_DAMAGE ( (WORD) dwDamage );

	//	Note : ��� ����.
	//
	//TurnAction ( GLAT_SHOCK );

	//	Note : ��� ����.
	if( !m_pSummonCrowData->IsIgnoreShock() )
	{
		if ( bShock )	
		{
			//			SetSTATE ( EM_SUMMONACT_SHOCK );
			TurnAction( GLAT_SHOCK );
		}
	}

	m_sAssault.emCrow = emACrow;
	m_sAssault.dwID = dwAID;

	STARGETID sTargetID = STARGETID ( emACrow, dwAID );
	if( !IsSTATE ( EM_SUMMONACT_ATTACK ) && GetAttackTarget( sTargetID ) )
	{
		SetAttackTarget( sTargetID );
	}

	return m_dwNowHP;
}

BOOL GLSummonField::ShockProcess ( float fElapsedTime )
{
	VECANIATTACK &vecShock = m_pSummonCrowData->GetAnimation(AN_SHOCK,AN_SUB_NONE);
	if ( vecShock.empty() )	return FALSE;

	m_fIdleTime += fElapsedTime * GETATTVELO();

	SANIATTACK &sAniShock = vecShock[0];

	int wTotalKeys = int(sAniShock.m_dwETime) - int(sAniShock.m_dwSTime);
	int wThisKey = int(m_fIdleTime*UNITANIKEY_PERSEC);

	if ( wThisKey >= wTotalKeys )	return FALSE;

	return TRUE;
}

BOOL GLSummonField::IsOwnerShortDistance( D3DXVECTOR3 vCheckPos )
{

	D3DXVECTOR3 vLeng = m_pOwner->GetPosition() - vCheckPos;
	float fTarLeng1 = D3DXVec3Length(&vLeng);

	vLeng			  = m_vPos - vCheckPos;
	float fTarLeng2 = D3DXVec3Length(&vLeng);

	if( fTarLeng1 > fTarLeng2 )
	{
		return TRUE;
	}

	return FALSE;
}

/*push pull skill logic, Juver, 2017/06/04 */
/*dash skill logic, Juver, 2017/06/17 */
void GLSummonField::ReceivePushPull ( const D3DXVECTOR3 &vMovePos, float fSpeed, bool bSkillMove, bool bReverseDir, bool bSkillDash, WORD wActionAnim )
{
	if ( !IsValidBody () )		return;

	/*skill summon, Juver, 2017/10/09 */
	if ( IsSTATE( EM_SUMMONACT_WAITING ) )	return;

	//	Note : �з��� ��ġ�� �̵� �õ�.
	//
	BOOL bSucceed = m_actorMove.GotoLocation
	(
		D3DXVECTOR3(vMovePos.x,vMovePos.y+5,vMovePos.z),
		D3DXVECTOR3(vMovePos.x,vMovePos.y-5,vMovePos.z)
	);

	if ( bSucceed )
	{
		//	Note : �з����� ���� ����.
		//
		m_TargetID.vPos = vMovePos;

		if ( bSkillDash )
		{
			/*dash skill logic, Juver, 2017/06/17 */
			TurnAction( GLAT_SKILLDASH );
		}
		else if ( bSkillMove )
		{
			/*push pull skill logic, Juver, 2017/06/05 */
			TurnAction ( GLAT_SKILLMOVE );
		}else{
			TurnAction ( GLAT_PUSHPULL );
		}

		/*push pull skill logic, Juver, 2017/06/05 */
		if ( bSkillMove && vMovePos.x != FLT_MAX && vMovePos.y != FLT_MAX && vMovePos.z != FLT_MAX )
		{
			D3DXVECTOR3 vNewDirection = m_vPos - vMovePos;
			if ( bReverseDir )	vNewDirection = vMovePos - m_vPos;
			if ( !DxIsMinVector(vNewDirection,0.2f) )
			{
				D3DXVec3Normalize ( &vNewDirection, &vNewDirection );
				m_vDir = vNewDirection;
			}
		}

		//	Note : �и��� �ӵ� ����.
		//
		m_actorMove.SetMaxSpeed ( fSpeed );

		//	Note : �޽��� ���� ����.
		//
		GLMSG::SNET_PUSHPULL_BRD NetMsgBRD;
		NetMsgBRD.emCrow = GETCROW();
		NetMsgBRD.dwID = m_dwGUID;
		NetMsgBRD.vMovePos = vMovePos;
		
		/*push pull skill logic, Juver, 2017/06/04 */
		NetMsgBRD.fSpeed = fSpeed; 
		NetMsgBRD.bSkillMove = bSkillMove;
		NetMsgBRD.bReverseDir = bReverseDir;
		
		/*dash skill logic, Juver, 2017/06/17 */
		NetMsgBRD.bSkillDash = bSkillDash; 
		NetMsgBRD.wActionAnim = wActionAnim;

		//	Note : [�ڽ��� �ֺ� Char] ���� Msg�� ����.
		//
		GLGaeaServer::GetInstance().SENDTOCLIENT ( m_pOwner->m_dwClientID, &NetMsgBRD );
		SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgBRD );
	}
}

/*debuff skill logic, Juver, 2017/06/10 */
void GLSummonField::BUFF_REMOVE( DWORD dwBuffFlag )
{
	GLMSG::SNETPC_SKILLHOLD_RS_BRD NetMsgSkillBrd;
	for ( int i=0; i<SKILLFACT_SIZE; ++i )
	{
		if ( m_sSKILLFACT[i].sNATIVEID == NATIVEID_NULL() ) continue;

		PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_sSKILLFACT[i].sNATIVEID );
		if ( !pSkill ) continue;
		if ( pSkill->m_sBASIC.emACTION != (SKILL::EMACTION)dwBuffFlag ) continue;
		
		DISABLESKEFF( i );
		NetMsgSkillBrd.bRESET[i] = true;
	}

	NetMsgSkillBrd.dwID = m_dwGUID;
	NetMsgSkillBrd.emCrow = CROW_SUMMON;

	SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgSkillBrd );
	GLGaeaServer::GetInstance().SENDTOCLIENT ( m_pOwner->m_dwClientID, &NetMsgSkillBrd );
}

void GLSummonField::DamageReflectionProc ( int nDAMAGE, STARGETID sACTOR )
{
	/*block back damage, Juver, 2017/12/12 */
	if ( RANPARAM::bFeatureBlockDamageBack && m_pLandMan )
	{
		GLACTOR* pactor_target = GLGaeaServer::GetInstance().GetTarget( m_pLandMan, sACTOR );
		if ( pactor_target )
		{
			if ( pactor_target->IsBlockDamageBack() )	return;
			pactor_target->SetBlockDamageBack( true );
		}
	}

	//	Note : ����ڿ��� ������� ����.
	DWORD dwNowHP = ToDamage ( sACTOR, nDAMAGE, FALSE );

	//	Note : �ֺ� Ŭ���̾�Ʈ�鿡�� �޼��� ����.
	//
	GLMSG::SNETCROW_DAMAGE NetMsg;
	NetMsg.dwGlobID		= m_dwGUID;
	NetMsg.emTarCrow	= sACTOR.emCrow;
	NetMsg.dwTarID		= sACTOR.dwID;
	NetMsg.nDamage		= nDAMAGE;
	NetMsg.dwNowHP		= dwNowHP;
	NetMsg.dwDamageFlag	= DAMAGE_TYPE_NONE;

	SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsg );
}


namespace
{
	typedef std::pair<int,int> PRIOR_PAIR;
	class prior_sort
	{
	public:
		bool operator () ( const PRIOR_PAIR &lvalue, const PRIOR_PAIR &rvalue ) const
		{
			return lvalue.first > rvalue.first;
		}
	};

	// float g_fMINNEAR(15.0f);
	float g_fMINNEAR(21.0f);
	float g_fMAXNEAR(35.0f);
};

bool GLSummonField::SetAttackTarget( STARGETID sAttackTargetID )
{
	if( !IsValidBody() ) return FALSE;

	if( !IsTargetReady() ) return FALSE;

	if ( IsACTION( GLAT_FALLING ) || IsACTION( GLAT_DIE ) || IsACTION( GLAT_ATTACK ) || IsACTION( GLAT_SKILL ) ) return FALSE;

	GLACTOR *pTARGET = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, sAttackTargetID );
	if( !pTARGET ) return FALSE;	

	D3DXVECTOR3 vDist = pTARGET->GetPosition () - m_vPos;
	float		fDist = D3DXVec3Length( &vDist );
	vDist			  = m_pOwner->GetPosition() - pTARGET->GetPosition();
	float  fOnwerDist = D3DXVec3Length( &vDist );

	// ���ΰ� ���� �Ÿ��� �ʹ� �ָ� ���� �ߴ�
	//if( fOnwerDist > m_fRunArea ) return FALSE;

	PGLSKILL pskill_base = GLSkillMan::GetInstance().GetData( m_Summon.sidSkill );
	if ( pskill_base && m_pOwner )
	{
		bool benemy = ( SIDE_ENEMY==pskill_base->m_sBASIC.emIMPACT_SIDE );

		if ( !m_pOwner->IsReActionable( pTARGET, benemy ) )
			return FALSE;

		if ( benemy && sAttackTargetID.emCrow == CROW_PC && sAttackTargetID.dwID == m_pOwner->m_dwGaeaID )
			return FALSE;
	}


	DWORD dwFoundAType = FindOptAType ( sAttackTargetID, false );
	if ( dwFoundAType >= SCROWDATA::EMMAXATTACK )	return FALSE;

	m_TargetID = sAttackTargetID;

	m_dwAType = dwFoundAType;
	m_pAttackProp = &(m_pSummonCrowData->m_sCrowAttack[m_dwAType]);

	m_idACTIVESKILL = m_pAttackProp->skill_id;
	m_wACTIVESKILL_LVL = m_Summon.wSkillLevel;

	PGLSKILL pskill_use = GLSkillMan::GetInstance().GetData( m_idACTIVESKILL );
	if ( pskill_use && m_pOwner )
	{
		EMSKILLCHECK emSkillCheck = CHECHSKILL ( m_dwAType );
		if ( emSkillCheck!=EMSKILL_OK && emSkillCheck!=EMSKILL_NOTSP)	return FALSE;

		UpdateViewAround();

		D3DXVECTOR3 vTarPos(0,0,0);
		BOOL bOK = SelectSkillTarget ( m_TargetID, &vTarPos, m_idACTIVESKILL, m_wACTIVESKILL_LVL);
		if ( !bOK )		return FALSE;

		bool benemy = ( SIDE_ENEMY==pskill_use->m_sBASIC.emIMPACT_SIDE );

		std::vector<STARID> vectargets;
		vectargets.reserve( EMTARGET_NET );

		for( int i=0; i<EMTARGET_NET; ++i )
		{
			if ( m_sTARIDS[i].GETID() == EMTARGET_NULL ) continue;

			GLACTOR *pskill_target = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, STARGETID( m_sTARIDS[i].GETCROW(), m_sTARIDS[i].GETID() ) );
			if( !pskill_target ) continue;

			if ( pskill_use->m_sBASIC.emIMPACT_SIDE != SIDE_OUR )
			{
				if ( m_sTARIDS[i].GETCROW() == CROW_PC && m_sTARIDS[i].GETID() == m_pOwner->m_dwGaeaID )	continue;

				if ( m_sTARIDS[i].GETCROW() == CROW_SUMMON )
				{
					PGLSUMMONFIELD psummon_target = GLGaeaServer::GetInstance().GetSummon( m_sTARIDS[i].GETID() );
					if ( psummon_target && psummon_target->m_pOwner && psummon_target->m_pOwner->m_dwGaeaID == m_pOwner->m_dwGaeaID )	continue;
					if ( psummon_target && !psummon_target->IsTargetReady() )	continue;
				}
			}

			if ( !m_pOwner->IsReActionable( pskill_target, benemy ) )	continue;

			vectargets.push_back ( m_sTARIDS[i] );
		}

		if ( vectargets.empty() )	return FALSE;

		m_wTARNUM = (WORD)vectargets.size();
		for( int n=0; n<EMTARGET_NET; ++n )
		{
			m_sTARIDS[n].wCrow = 0;
			m_sTARIDS[n].wID = USHRT_MAX;
		}

		for( int n=0; n<(int)vectargets.size(); ++n )
		{
			if ( n >= EMTARGET_NET )	continue;
			m_sTARIDS[n] = vectargets[n];
		}
	}


	ReSetAllSTATE ();
	SetSTATE ( EM_SUMMONACT_ATTACK );
	TurnAction( GLAT_ATTACK );		

	return TRUE;
}


DWORD GLSummonField::FindOptAType ( const STARGETID &sTargetID, bool branvar )
{
	GLACTOR *pTarget = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, sTargetID );
	if ( !pTarget )		return SCROWDATA::EMMAXATTACK;

	bool bTarStateRun = (pTarget->IsRunning()==TRUE);

	D3DXVECTOR3 vDX = m_vPos - pTarget->GetPosition();
	float fLength = D3DXVec3Length ( &vDX );

	//	Note : ������ �켱���� ����.
	bool bprior_near(false);
	if ( g_fMAXNEAR>fLength && !bTarStateRun )	bprior_near = true;

	static std::vector<PRIOR_PAIR> vecPRIOR;
	vecPRIOR.clear ();

	for ( int i=0; i<SCROWDATA::EMMAXATTACK; ++i )
	{
		const SCROWATTACK &sATTACK = m_pSummonCrowData->m_sCrowAttack[i];
		if ( !sATTACK.bUsed )							continue;

		if ( m_fACTIONDELAY[i] > 0.0f )					continue;

		bool bskill(false);
		bool bnear(false);
		if ( sATTACK.skill_id!=SNATIVEID(false) )
		{
			PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sATTACK.skill_id );
			if ( !pSkill )								continue;
			if ( sATTACK.skill_tar == CROWSKTAR_OUR )	continue;

			//	������ �ð�, ���Ǽ�ġ�� Ȯ���Ͽ� ��� �������� ����.
			EMSKILLCHECK emcheck = CHECHSKILL ( DWORD(i) );
			if ( emcheck!=EMSKILL_OK && emcheck!=EMSKILL_NOTSP )	continue;

			bskill = true;

			if ( pSkill->m_sBASIC.wTARRANGE < g_fMAXNEAR )		bnear = true;
			else												bnear = false;
		}
		else
		{
			if ( sATTACK.emAttRgType == EMATT_SHORT )	bnear = true;
			else										bnear = false;
		}

		//	�켱���� ���.
		int nprior(0);

		//	�켱������ ������ ��ġ�� �ణ �ο�. ( ���� ���� )
		if ( branvar )					nprior += int ( (RANDOM_POS) * SCROWDATA::EMMAXATTACK );

		//	��ų�� ��� ������.
		if ( bskill )					nprior += 11;

		//	���� ������ �����Ѱ� ��Ÿ��� �����Ѱ��� ���� �켱 ���� ����.
		if ( bprior_near )
		{
			//	���� �켱.
			if ( bnear )				nprior += 10;
			else						nprior += 5;
		}
		else
		{
			//	��Ÿ� �켱.
			if ( bnear )				nprior += 5;
			else						nprior += 10;
		}

		vecPRIOR.push_back ( std::make_pair(nprior,i) );
	}

	if ( vecPRIOR.empty() )		return SCROWDATA::EMMAXATTACK;

	std::sort ( vecPRIOR.begin(), vecPRIOR.end(), prior_sort() );

	const PRIOR_PAIR &sPRIOR = *vecPRIOR.begin();

	GASSERT ( sPRIOR.second < SCROWDATA::EMMAXATTACK );
	if ( sPRIOR.second >= SCROWDATA::EMMAXATTACK )	return SCROWDATA::EMMAXATTACK;

	return sPRIOR.second;
}

HRESULT GLSummonField::UpdateViewAround ()
{
	int nX, nZ;

	m_dwPC_AMOUNT = 0;
	m_dwCROW_AMOUNT = 0;
	m_dwSUMMON_AMOUNT = 0;

	if ( !m_pLandMan )	return E_FAIL;

	//DWORD dwStartTime = GetTickCount();

	nX = int ( m_vPos.x );
	nZ = int ( m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+MAX_SUMMON_VIEWRANGE,nZ+MAX_SUMMON_VIEWRANGE,nX-MAX_SUMMON_VIEWRANGE,nZ-MAX_SUMMON_VIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
		GLLandNode *pLandNode = pQuadNode->pData;
		if( !pLandNode ) continue;

		//char
		GLCHARNODE *pchar_node = pQuadNode->pData->m_PCList.m_pHead;
		for ( ; pchar_node; pchar_node = pchar_node->pNext )
		{
			GLChar *pchar = pchar_node->Data;
			if( !pchar ) continue;
			if( !pchar ) continue;

			if ( !glGaeaServer.GetChar ( pchar->m_dwGaeaID ) )	continue;
			if ( bRect.IsWithIn(nX,nZ) )
			{
				if ( m_vecPC_VIEW.size() < m_dwPC_AMOUNT+16 )
					m_vecPC_VIEW.resize(m_dwPC_AMOUNT+16);

				m_vecPC_VIEW[m_dwPC_AMOUNT++] = pchar->m_dwGaeaID;
			}
		}

		//crow
		GLCROWNODE *pcrow_node = pQuadNode->pData->m_CROWList.m_pHead;
		for ( ; pcrow_node; pcrow_node = pcrow_node->pNext )
		{
			GLCrow *pcrow = pcrow_node->Data;
			if( !pcrow ) continue;
			if( !pcrow ) continue;

			if ( !m_pLandMan->GetCrow ( pcrow->m_dwGlobID ) )	continue;
			if ( bRect.IsWithIn(nX,nZ) )
			{
				if ( m_vecCROW_VIEW.size() < m_dwCROW_AMOUNT+16 )
					m_vecCROW_VIEW.resize(m_dwCROW_AMOUNT+16);

				m_vecCROW_VIEW[m_dwCROW_AMOUNT++] = pcrow->m_dwGlobID;
			}
		}

		//summon
		/*GLSUMMONNODE *psummon_node = pQuadNode->pData->m_SummonList.m_pHead;
		for ( ; psummon_node; psummon_node = psummon_node->pNext )
		{
			GLSummonField* psummon = psummon_node->Data;
			if( !psummon ) continue;
			if( !psummon ) continue;

			if ( !glGaeaServer.GetSummon ( psummon->m_dwGUID ) ) continue;

			if ( bRect.IsWithIn(nX,nZ) )
			{
				if ( m_vecSUMMON_VIEW.size() < m_dwSUMMON_AMOUNT+16 )
					m_vecSUMMON_VIEW.resize(m_dwSUMMON_AMOUNT+16);

				m_vecSUMMON_VIEW[m_dwSUMMON_AMOUNT++] = psummon->m_dwGUID;
			}
		}*/
	}

	//DWORD dwEndTime = GetTickCount();
	//DWORD dwTime = dwEndTime - dwStartTime;

	//if ( dwTime > 0 )
	//	CDebugSet::ToFileWithTime( "_summonscan.txt", "time %d pcsize:%d crowsize:%d summonsize:%d", dwTime, m_dwPC_AMOUNT, m_dwCROW_AMOUNT, m_dwSUMMON_AMOUNT );

	return S_OK;
}



BOOL GLSummonField::IsTargetReady ()
{
	if ( IsSTATE( EM_SUMMONACT_WAITING ) )	return FALSE;
	if ( IsACTION( GLAT_FALLING ) )			return FALSE;
	if ( IsACTION( GLAT_DIE ) )				return FALSE;

	if ( m_dwNowHP == 0 )					return FALSE;

	return TRUE;
}

/*block back damage, Juver, 2017/12/12 */
void GLSummonField::SetBlockDamageBack( bool bSet )
{
	m_bBlockBackDamage = bSet;
	m_fBlockBackDamageTime = 0.0f;
}
