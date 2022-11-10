#include "stdafx.h"
#include "./GLGaeaserver.h"
#include "./stl_func.h"
#include ".\glsummonfield.h"

DWORD GLSummonField::SELECT_SKILLSLOT ( SNATIVEID skill_id )
{
	SKILLREALFACT_SIZE;
	DWORD dwSELECT = UINT_MAX;

	//	Note : ��ų�� �� �⺻ ���� ����.
	//
	for ( DWORD i=0; i<SKILLREALFACT_SIZE; ++i )
	{
		if ( m_sSKILLFACT[i].sNATIVEID==skill_id )
		{
			return dwSELECT = i;
		}
	}

	float fAGE = FLT_MAX;
	for ( DWORD i=0; i<SKILLREALFACT_SIZE; ++i )
	{
		if ( m_sSKILLFACT[i].sNATIVEID==SNATIVEID(false) )
		{
			return dwSELECT = i;
		}

		if ( m_sSKILLFACT[i].fAGE < fAGE )
		{
			fAGE = m_sSKILLFACT[i].fAGE;
			dwSELECT = i;
		}
	}

	return dwSELECT;
}


BOOL GLSummonField::RECEIVE_SKILLFACT ( const SNATIVEID skill_id, const WORD wlevel, DWORD &dwSELECT, WORD _wCasterCrow, DWORD _dwCasterID )
{
	dwSELECT = SKILLFACT_SIZE;

	//	��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )				return FALSE;
	if ( wlevel >= SKILL::MAX_LEVEL )	return FALSE;
	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[wlevel];

	BOOL bHOLD = FALSE;
	SSKILLFACT sSKILLEF;
	sSKILLEF._wCasterCrow = _wCasterCrow;
	sSKILLEF._dwCasterID = _dwCasterID;

	switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
	{
	case SKILL::EMFOR_VARHP:
	case SKILL::EMFOR_VARMP:
	case SKILL::EMFOR_VARSP:
	case SKILL::EMFOR_DEFENSE:
	case SKILL::EMFOR_HITRATE:
	case SKILL::EMFOR_AVOIDRATE:
	case SKILL::EMFOR_VARAP:
	case SKILL::EMFOR_VARDAMAGE:
	case SKILL::EMFOR_VARDEFENSE:
	case SKILL::EMFOR_PA:
	case SKILL::EMFOR_SA:
	case SKILL::EMFOR_MA:
		bHOLD = TRUE;
		sSKILLEF.emTYPE = pSkill->m_sAPPLY.emBASIC_TYPE;
		sSKILLEF.fMVAR = sSKILL_DATA.fBASIC_VAR;
		break;
	};

	for( int nImpact=0; nImpact<SKILL::MAX_IMPACT; ++nImpact )
	{
		if ( pSkill->m_sAPPLY.sImpacts[nImpact].emADDON != EMIMPACTA_NONE )
		{
			bHOLD = TRUE;
			sSKILLEF.sImpacts[nImpact].emADDON = pSkill->m_sAPPLY.sImpacts[nImpact].emADDON;
			sSKILLEF.sImpacts[nImpact].fADDON_VAR = pSkill->m_sAPPLY.sImpacts[nImpact].fADDON_VAR[wlevel];
		}
	}

	for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
	{
		switch ( pSkill->m_sAPPLY.sSpecs[nSpec].emSPEC )
		{
		case EMSPECA_REFDAMAGE:
		case EMSPECA_NONBLOW:
		case EMSPECA_PIERCE:
		case EMSPECA_TARRANGE:
		case EMSPECA_MOVEVELO:
		case EMSPECA_PROHIBIT_POTION:		/*prohibit potion skill logic, Juver, 2017/06/06 */
		case EMSPECA_PROHIBIT_SKILL:		/*prohibit skill logic, Juver, 2017/06/06 */
		case EMSPECA_CHANGE_ATTACK_RANGE:	/*skill range spec logic, Juver, 2017/06/06 */
		case EMSPECA_CHANGE_APPLY_RANGE:	/*skill range spec logic, Juver, 2017/06/06 */
		case EMSPECA_STUN:					/*skill stun logic, Juver, 2017/06/06 */
		case EMSPECA_CONTINUOUS_DAMAGE:		/*continuous damage skill logic, Juver, 2017/06/10 */
		case EMSPECA_CURSE:					/*curse skill logic, Juver, 2017/06/10 */
		case EMSPECA_IGNORE_DAMAGE:			/*ignore damage, Juver, 2017/12/12 */
			bHOLD = TRUE;
			sSKILLEF.sSpecs[nSpec].emSPEC = pSkill->m_sAPPLY.sSpecs[nSpec].emSPEC;
			sSKILLEF.sSpecs[nSpec].fSPECVAR1 = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wlevel].fVAR1;
			sSKILLEF.sSpecs[nSpec].fSPECVAR2 = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wlevel].fVAR2;
			sSKILLEF.sSpecs[nSpec].dwSPECFLAG = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wlevel].dwFLAG;
			break;
		};
	}
	

	//	Note : ������ ��ų�� ��� ���� ������ ã�Ƽ� ��ų ȿ���� �־���.
	//
	if ( bHOLD )
	{
		sSKILLEF.sNATIVEID	= skill_id;
		sSKILLEF.wLEVEL		= wlevel;
		sSKILLEF.fAGE		= sSKILL_DATA.fLIFE;

		dwSELECT = SELECT_SKILLSLOT ( skill_id );
		m_sSKILLFACT[dwSELECT] = sSKILLEF;
	}

	return TRUE;
}

//! ������ �켱���� �ֱ����� ������ �α� ���
void GLSummonField::VAR_BODY_POINT ( const EMCROW emACrow, const DWORD dwAID, const BOOL bPartySkill, int nvar_hp, int nvar_mp, int nvar_sp )
{
	if ( m_dwNowHP==0 )		return;

	DWORD dwDxHP = GLOGICEX::VARIATION ( m_dwNowHP, GETMAXHP(), nvar_hp );
	GLOGICEX::VARIATION ( m_wNowMP, GETMAXMP(), nvar_mp );
	GLOGICEX::VARIATION ( m_wNowSP, GETMAXSP(), nvar_sp );

	BOOL bDamage = nvar_hp<0;

	if ( bDamage )
	{
		//	�ڽ��� ������ ��� ���.
		m_sAssault.emCrow = emACrow;
		m_sAssault.dwID = dwAID;

		STARGETID sTargetID = STARGETID ( emACrow, dwAID );
		if( !IsSTATE ( EM_SUMMONACT_ATTACK ) && GetAttackTarget( sTargetID ) )
		{
			SetAttackTarget( sTargetID );
		}

		//	������ ���.
		/*if ( emACrow == CROW_PC )
		{
			PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar ( dwAID );
			if ( pChar )
			{
				AddDamageLog      ( m_cDamageLog, dwAID, pChar->GetUserID(), dwDxHP );
				AddDamageLogParty ( m_cDamageLogParty, pChar->m_dwPartyID, dwDxHP );
			}
		}*/
	}

	//HRESULT hrESCAPE = S_OK;
	//EMCROWACT_UP emCROWACT = GetActPattern();
	//int nDamageHP = abs(nvar_hp);
	//if ( bDamage )		hrESCAPE = ESCAPE ( STARGETID ( emACrow, dwAID ), nDamageHP );

	//if ( EMCROWACT_UP_ESCAPE != emCROWACT || hrESCAPE!=S_OK )
	//{
	//	//	Note :Ÿ���� �������� ������ �����ڰ� ������ Ÿ������ ��� �õ�.
	//	//
	//	if ( !IsFLAG(EMTARGET) && bDamage )
	//	{
	//		PGLCHAR pTarget = NULL;
	//		if ( emACrow==CROW_PC )		pTarget = GLGaeaServer::GetInstance().GetChar(dwAID);

	//		if ( pTarget )
	//		{
	//			STARGETID sTARID(CROW_PC,pTarget->GetCtrlID(),pTarget->GetPosition());
	//			NewTarget ( sTARID );
	//		}
	//	}
	//}
}

void GLSummonField::CURE_STATEBLOW ( DWORD dwCUREFLAG )
{
	BOOL bChanged = FALSE;

	for ( int i=0; i<EMBLOW_MULTI; ++i )
	{
		if ( m_sSTATEBLOWS[i].emBLOW!=EMBLOW_NONE )		continue;

		bChanged = TRUE;
		if ( STATE_TO_DISORDER(m_sSTATEBLOWS[i].emBLOW)&dwCUREFLAG )	m_sSTATEBLOWS[i].emBLOW = EMBLOW_NONE;
	}

	if ( !bChanged )	return;

	//	Note : ���� �̻� ��ȭ MsgFB.
	//
	GLMSG::SNETPC_CURESTATEBLOW_BRD NetMsgBRD;
	NetMsgBRD.dwCUREFLAG = dwCUREFLAG;

	//	Note : �ֺ� Ŭ���̾�Ʈ�鿡�� �޼��� ����.
	//
	SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgBRD );
}

void GLSummonField::STATEBLOW ( const SSTATEBLOW &sStateBlow )
{
	int nIndex = 0;

	if ( sStateBlow.emBLOW <= EMBLOW_SINGLE )	nIndex = 0;
	else										nIndex = sStateBlow.emBLOW-EMBLOW_SINGLE;

	m_sSTATEBLOWS[nIndex] = sStateBlow;

	//	�����̻� ( ���� ) �� ������ ���� ���� �ߴ�.
	if ( sStateBlow.emBLOW == EMBLOW_STUN )
	{
		TurnAction ( GLAT_IDLE );
		SetSTATE( EM_SUMMONACT_STOP );		
	}
}


VEC_SK_TAR GLSummonField::DetectTarget ( const D3DXVECTOR3 &vDetectPosA, const D3DXVECTOR3 &vDetectPosB, const DWORD dwMaxFind )
{
	VEC_SK_TAR vecTargetID;

	float fTarLeng(0.0f);
	D3DXVECTOR3 vMax, vMin, vPos;

	for ( DWORD i=0; i<m_dwPC_AMOUNT && i<m_vecPC_VIEW.size(); ++i )
	{
		DWORD dwGAEAID = m_vecPC_VIEW[i];
		GLChar *pChar = GLGaeaServer::GetInstance().GetChar ( dwGAEAID );
		if ( !pChar )				continue;
		if ( pChar->IsSafeTime() )	continue;
		if ( pChar->IsSafeZone() )	continue;

		vPos = pChar->GetPosition();

		vMax = vPos + D3DXVECTOR3(8,20,8);
		vMin = vPos + D3DXVECTOR3(-8,0,-8);

		if ( COLLISION::IsCollisionLineToAABB ( vDetectPosA, vDetectPosB, vMax, vMin ) )
		{
			vecTargetID.push_back( STARGETID(pChar->GetCrow(),  pChar->GetCtrlID(), pChar->GetPosition() ) );
		}

		// ��ȯ���� �����ȿ� ������쿡�� ��ȯ���� ��ų Ÿ�� ����Ʈ�� �߰��Ѵ�.
		/*skill summon, Juver, 2017/10/09 */
		for ( int ii=0; ii<SKILL_SUMMON_MAX_CLIENT_NUM; ++ii )
		{
			PGLSUMMONFIELD pMySummon = GLGaeaServer::GetInstance().GetSummon( pChar->m_dwSummonGUID_FLD[ii] );
			if ( pMySummon && pMySummon->IsValid() && pMySummon->IsTargetReady() )
			{
				vPos = pMySummon->GetPosition();
				vMax = vPos + D3DXVECTOR3(8,20,8);
				vMin = vPos + D3DXVECTOR3(-8,0,-8);

				if ( COLLISION::IsCollisionLineToAABB ( vDetectPosA, vDetectPosB, vMax, vMin ) )
				{
					vecTargetID.push_back( STARGETID(pMySummon->GetCrow(),  pMySummon->GetCtrlID(), pMySummon->GetPosition() ) );
				}
			}
		}
	}

	if ( m_pLandMan )
	{
		for ( DWORD i=0; i<m_dwCROW_AMOUNT && i<m_vecCROW_VIEW.size(); ++i )
		{
			DWORD dwGlobID = m_vecCROW_VIEW[i];
			GLCrow *pCrow = m_pLandMan->GetCrow( dwGlobID );
			if ( !pCrow )				continue;

			vPos = pCrow->GetPosition();

			vMax = vPos + D3DXVECTOR3(8,20,8);
			vMin = vPos + D3DXVECTOR3(-8,0,-8);

			if ( COLLISION::IsCollisionLineToAABB ( vDetectPosA, vDetectPosB, vMax, vMin ) )
			{
				vecTargetID.push_back( STARGETID(pCrow->GetCrow(),  pCrow->GetCtrlID(), pCrow->GetPosition() ) );
			}
		}
	}
	

	if( vecTargetID.empty() ) return vecTargetID;

	std_afunc::CCompareTargetDist Comp(D3DXVECTOR3(0.0f,0.0f,0.0f));
	std::sort ( vecTargetID.begin(), vecTargetID.end(), Comp );
	if( vecTargetID.size() > dwMaxFind )
		vecTargetID.erase( vecTargetID.begin()+dwMaxFind, vecTargetID.end() );

	return vecTargetID;
}


VEC_SK_TAR GLSummonField::DetectTarget ( const D3DXVECTOR3 &vDetectPos, const int nRange, const DWORD dwMaxFind )
{
	VEC_SK_TAR vecTargetID;

	float fTarLeng(0.0f);
	D3DXVECTOR3 vMax, vMin, vPos;

	for ( DWORD i=0; i<m_dwPC_AMOUNT && i<m_vecPC_VIEW.size(); ++i )
	{
		DWORD dwGAEAID = m_vecPC_VIEW[i];
		GLChar *pChar = GLGaeaServer::GetInstance().GetChar ( dwGAEAID );
		if ( !pChar )				continue;
		if ( pChar->IsSafeTime() )	continue;
		if ( pChar->IsSafeZone() )	continue;

		D3DXVECTOR3 vLengA = pChar->GetPosition() - vDetectPos;
		fTarLeng = D3DXVec3Length(&vLengA);
		if ( fTarLeng <= nRange )
		{
			vecTargetID.push_back( STARGETID(pChar->GetCrow(),  pChar->GetCtrlID(), pChar->GetPosition() ) );
		}

		// ��ȯ���� �����ȿ� ������쿡�� ��ȯ���� ��ų Ÿ�� ����Ʈ�� �߰��Ѵ�.
		/*skill summon, Juver, 2017/10/09 */
		for ( int ii=0; ii<SKILL_SUMMON_MAX_CLIENT_NUM; ++ii )
		{
			PGLSUMMONFIELD pMySummon = GLGaeaServer::GetInstance().GetSummon( pChar->m_dwSummonGUID_FLD[ii] );
			if ( pMySummon && pMySummon->IsValid() && pMySummon->IsTargetReady() )
			{
				D3DXVECTOR3 vLengA = pMySummon->GetPosition() - vDetectPos;
				fTarLeng = D3DXVec3Length(&vLengA);
				if ( fTarLeng <= nRange )
				{
					vecTargetID.push_back( STARGETID(pMySummon->GetCrow(),  pMySummon->GetCtrlID(), pMySummon->GetPosition() ) );
				}		
			}
		}
	}

	if ( m_pLandMan )
	{
		for ( DWORD i=0; i<m_dwCROW_AMOUNT && i<m_vecCROW_VIEW.size(); ++i )
		{
			DWORD dwGlobID = m_vecCROW_VIEW[i];
			GLCrow *pCrow = m_pLandMan->GetCrow( dwGlobID );
			if ( !pCrow )				continue;

			D3DXVECTOR3 vLengA = pCrow->GetPosition() - vDetectPos;
			fTarLeng = D3DXVec3Length(&vLengA);
			if ( fTarLeng <= nRange )
			{
				vecTargetID.push_back( STARGETID(pCrow->GetCrow(), pCrow->GetCtrlID(), pCrow->GetPosition() ) );
			}
		}
	}

	if( vecTargetID.empty() ) return vecTargetID;

	std_afunc::CCompareTargetDist Comp(D3DXVECTOR3(0.0f,0.0f,0.0f));
	std::sort ( vecTargetID.begin(), vecTargetID.end(), Comp );
	if( vecTargetID.size() > dwMaxFind )
		vecTargetID.erase( vecTargetID.begin()+dwMaxFind, vecTargetID.end() );

	return vecTargetID;
}


//	�ڱ����� ��ų üũ ( �ڱ� ��ġ�� ���� )
BOOL GLSummonField::SKT_SELFZONEOUR ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	GASSERT(m_pLandMan);

	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_sTARIDS[m_wTARNUM].wCrow = static_cast<WORD>(GetCrow());
	m_sTARIDS[m_wTARNUM].wID = static_cast<WORD>(GetCtrlID());
	++m_wTARNUM;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARNUM )	return TRUE;

	//	Note : ��Ƽ���� �߿� Skill ������ ������ ��� �˻�.
	//
	//PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	//if ( !pLand )	return TRUE;

	TARGETMAP	Targetmap;
	float fDetectRange = GETBODYRADIUS() + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	//DWORD dwIndex = 0;
	//GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	//while ( pMember && dwIndex<MAXPARTY )
	//{
	//	if ( !pMember->ISONESELF() )
	//	{
	//		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );
	//		
	//		D3DXVECTOR3 vMemPos = pMember->m_vPos;
	//		if ( pChar )	 vMemPos = pChar->GetPosition();

	//		float fLength = D3DXVec3Length ( &D3DXVECTOR3(GetPosition()-vMemPos) );
	//		if ( fLength <= fDetectRange )
	//		{
	//			STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
	//			Targetmap.insert ( std::make_pair(fLength,sFindID) );
	//		}
	//	}

	//	pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	//}

	//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	//
	TARGETMAP_ITER iter = Targetmap.begin();
	TARGETMAP_ITER iter_end = Targetmap.end();
	for ( WORD i=m_wTARNUM; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	{
		if ( wTARNUM<=m_wTARNUM )		break;
		if ( EMTARGET_NET<=m_wTARNUM )	break;

		m_sTARIDS[m_wTARNUM].SET ( (*iter).m_sTARGETID );
		++m_wTARNUM;
	}

	return TRUE;
}

//  ���鿡�� ��ų üũ ( �ڱ� ��ġ�� ���� )
BOOL GLSummonField::SKT_SELFZONEENERMY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];
	WORD wTARNUM = sSKILL_DATA.wTARNUM;

	//	PC, SUMMON �˻�
	int nApplyRange = int ( GETBODYRADIUS() + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2 );
	VEC_SK_TAR vecTargetID = DetectTarget ( GetPosition(), nApplyRange, DWORD(wTARNUM) );

	if( !vecTargetID.empty() )
	{
		VEC_SK_ITER iter = vecTargetID.begin();;
		for( ; iter != vecTargetID.end(); ++iter )
		{
			if ( wTARNUM<=m_wTARNUM )		break;
			if ( EMTARGET_NET<=m_wTARNUM )	break;

			m_sTARIDS[m_wTARNUM] = STARID(iter->emCrow,iter->dwID);
			++m_wTARNUM;	
		}
	}

	if ( m_wTARNUM==0 )		return FALSE;

	return TRUE;
}

//  ��ο��� ��ų üũ ( �ڱ� ��ġ�� ���� )
BOOL GLSummonField::SKT_SELFZONANYBODY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];
	WORD wTARNUM = sSKILL_DATA.wTARNUM;

	//	CROW �˻�
	int nApplyRange = int ( GETBODYRADIUS() + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2 );
	ARRAY_CROW* pDetectedCROW = m_pLandMan->DetectCROW ( GetPosition(), nApplyRange, DWORD(wTARNUM) );

	if ( pDetectedCROW )
	{
		ARRAY_CROW_ITER iter = pDetectedCROW->begin();
		ARRAY_CROW_ITER iter_end = pDetectedCROW->end();
		for ( ; iter!=iter_end; ++iter )
		{
			if ( wTARNUM<=m_wTARNUM )		break;
			if ( EMTARGET_NET<=m_wTARNUM )	break;

			PGLCROW pCrow = (*iter).pCrow;
			WORD wCrow = (WORD) pCrow->GetCrow();
			WORD wID = (WORD) pCrow->GetCtrlID();

			m_sTARIDS[m_wTARNUM] = STARID(wCrow,wID);
			++m_wTARNUM;
		}
	}

	if ( m_wTARNUM==0 )		return FALSE;

	return TRUE;
}

//	�ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
BOOL GLSummonField::SKT_TARSPECOUR_SELF ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	if ( sTargetID.emCrow != CROW_SUMMON )	return FALSE;

	//GLPARTY_CLIENT* pParty = GLPartyClient::GetInstance().FindMember ( sTargetID.dwID );
	//if ( !pParty )						return FALSE;

	m_sTARIDS[m_wTARNUM].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARIDS[m_wTARNUM].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARNUM;

	return TRUE;
}

//	���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
BOOL GLSummonField::SKT_TARSPECENERMY_SELF ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	if ( sTargetID.emCrow != CROW_PC && sTargetID.emCrow != CROW_SUMMON )	return FALSE;

	m_sTARIDS[m_wTARNUM].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARIDS[m_wTARNUM].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARNUM;
	return TRUE;
}

//	��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� �ڽ� ����
BOOL GLSummonField::SKT_TARSPECANYBODY_SELF ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	if ( sTargetID.emCrow != CROW_SUMMON )	return FALSE;

	m_sTARIDS[m_wTARNUM].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARIDS[m_wTARNUM].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARNUM;
	return TRUE;
}

//	�ڱ����� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
BOOL GLSummonField::SKT_TARSPECOUR ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_sTARIDS[m_wTARNUM].wCrow = static_cast<WORD>(sTargetID.emCrow);
	m_sTARIDS[m_wTARNUM].wID = static_cast<WORD>(sTargetID.dwID);
	++m_wTARNUM;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARNUM )			return TRUE;

	static D3DXVECTOR3 vERROR(FLT_MAX,FLT_MAX,FLT_MAX);
	D3DXVECTOR3 vFindPos = GLGaeaServer::GetInstance().GetTargetPos ( m_pLandMan, sTargetID );
	if ( vFindPos == vERROR )			return FALSE;

	//	Note : ��Ƽ���� �߿� Skill ������ ������ ��� �˻�.
	//
	int nDetectRange = int ( GETBODYRADIUS() + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2 );

	//DWORD dwIndex = 0;
	//GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	//while ( pMember && dwIndex<MAXPARTY )
	//{
	//	if ( !pMember->ISONESELF() )
	//	{
	//		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );
	//		
	//		D3DXVECTOR3 vMemPos = pMember->m_vPos;
	//		if ( pChar )	 vMemPos = vFindPos;

	//		float fLength = D3DXVec3Length ( &D3DXVECTOR3(vFindPos-vMemPos) );
	//		if ( fLength <= fDetectRange )
	//		{
	//			STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
	//			Targetmap.insert ( std::make_pair(fLength,sFindID) );
	//		}
	//	}

	//	pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	//}

	//	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	//
	//TARGETMAP_ITER iter = Targetmap.begin();
	//TARGETMAP_ITER iter_end = Targetmap.end();
	//for ( WORD i=m_wTARNUM; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	//{
	//	if ( wTARNUM<=m_wTARNUM )	break;

	//	m_sTARIDS[m_wTARNUM].wCrow = static_cast<WORD> ( (*iter).second.emCrow );
	//	m_sTARIDS[m_wTARNUM].wID = static_cast<WORD> ( (*iter).second.dwID );
	//	++m_wTARNUM;
	//}

	if ( m_wTARNUM==0 )		return FALSE;

	return TRUE;
}

//	���鿡�� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
BOOL GLSummonField::SKT_TARSPECENERMY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];
	WORD wTARNUM = sSKILL_DATA.wTARNUM;

	static D3DXVECTOR3 vERROR(FLT_MAX,FLT_MAX,FLT_MAX);
	D3DXVECTOR3 vFindPos = GLGaeaServer::GetInstance().GetTargetPos ( m_pLandMan, sTargetID );
	if ( vFindPos == vERROR )			return FALSE;

	//	PC, SUMMON �˻�
	int nApplyRange = int ( GETBODYRADIUS() + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2 );
	VEC_SK_TAR vecTargetID = DetectTarget ( vFindPos, nApplyRange, DWORD(wTARNUM) );

	if( !vecTargetID.empty() )
	{
		VEC_SK_ITER iter = vecTargetID.begin();;
		for( ; iter != vecTargetID.end(); ++iter )
		{
			if ( wTARNUM<=m_wTARNUM )		break;
			if ( EMTARGET_NET<=m_wTARNUM )	break;

			m_sTARIDS[m_wTARNUM] = STARID(iter->emCrow,iter->dwID);
			++m_wTARNUM;	
		}
	}

	if ( m_wTARNUM==0 )		return FALSE;

	return TRUE;
}

//	��ο��� ��ų üũ ( ��� ��ġ�� ���� )�̰� ��ǥ ����
BOOL GLSummonField::SKT_TARSPECANYBODY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];
	WORD wTARNUM = sSKILL_DATA.wTARNUM;

	static D3DXVECTOR3 vERROR(FLT_MAX,FLT_MAX,FLT_MAX);
	D3DXVECTOR3 vFindPos = GLGaeaServer::GetInstance().GetTargetPos ( m_pLandMan, sTargetID );
	if ( vFindPos == vERROR )			return FALSE;

	//	CROW �˻�
	int nApplyRange = int ( GETBODYRADIUS() + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2 );
	ARRAY_CROW* pDetectedCROW = m_pLandMan->DetectCROW ( vFindPos, nApplyRange, DWORD(wTARNUM) );

	if ( pDetectedCROW )
	{
		ARRAY_CROW_ITER iter = pDetectedCROW->begin();
		ARRAY_CROW_ITER iter_end = pDetectedCROW->end();
		for ( ; iter!=iter_end; ++iter )
		{
			if ( wTARNUM<=m_wTARNUM )		break;
			if ( EMTARGET_NET<=m_wTARNUM )	break;

			PGLCROW pCrow = (*iter).pCrow;
			WORD wCrow = (WORD) pCrow->GetCrow();
			WORD wID = (WORD) pCrow->GetCtrlID();

			m_sTARIDS[m_wTARNUM] = STARID(wCrow,wID);
			++m_wTARNUM;
		}
	}

	if ( m_wTARNUM==0 )		return FALSE;

	return TRUE;
}

//	'��ǥ'�� ���� ��ä�� ���.
BOOL GLSummonField::SKT_TARSPECFANWIZE ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];
	WORD wTARNUM = sSKILL_DATA.wTARNUM;

	GLACTOR *pTarget = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, sTargetID );
	if ( !pTarget )		return FALSE;

	D3DXVECTOR3 vTarPos = pTarget->GetPosition();

	D3DXVECTOR3 vTarOrgDir = vTarPos - GetPosition();
	const D3DXVECTOR3 &vFindPos = GetPosition ();

	float fApplyAngle = D3DXToRadian(sSKILL_DATA.wAPPLYANGLE) / 2.0f;

	//	ù ǥ�� ����.
	m_sTARIDS[m_wTARNUM].wCrow = static_cast<WORD> ( sTargetID.emCrow );
	m_sTARIDS[m_wTARNUM].wID = static_cast<WORD> ( sTargetID.dwID );
	m_wTARNUM++;

	//	PC, SUMMON �˻�
	int nApplyRange = int ( pTarget->GetBodyRadius() + GETBODYRADIUS() + GETSKILLRANGE_APPLY(sSKILL,wLEVEL) + 2 );
	VEC_SK_TAR vecTargetID = DetectTarget ( vFindPos, nApplyRange, DWORD(wTARNUM) );

	if( !vecTargetID.empty() )
	{
		VEC_SK_ITER iter = vecTargetID.begin();;
		for( ; iter != vecTargetID.end(); ++iter )
		{
			if ( wTARNUM<=m_wTARNUM )		break;
			if ( EMTARGET_NET<=m_wTARNUM )	break;

			if( iter->emCrow == sTargetID.emCrow && sTargetID.dwID == iter->dwID ) continue;
			m_sTARIDS[m_wTARNUM] = STARID(iter->emCrow,iter->dwID);
			++m_wTARNUM;	
		}
	}

	if ( m_wTARNUM==0 )		return FALSE;

	return TRUE;
}

// �����Ը� �ڱ� ��ġ���� ��� ��ġ����. ( ȭ�� ���� )
BOOL GLSummonField::SKT_TARSELFTOSPEC ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];
	WORD wPIERCENUM = sSKILL_DATA.wPIERCENUM + GETSUM_PIERCE();

	GLACTOR *pTarget = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, sTargetID );
	if ( !pTarget )		return FALSE;

	D3DXVECTOR3 vTarget = sTargetID.vPos;	vTarget.y += 12.0f;
	D3DXVECTOR3 vFrom = m_vPos;				vFrom.y += 12.0f;

	D3DXVECTOR3 vDir = vTarget - vFrom;
	D3DXVec3Normalize ( &vDir, &vDir );

	//	Note : ��Ÿ��� ��ų�� ��� GETSUM_TARRANGE() ����.
	float fDetectRange = (float) ( pTarget->GetBodyRadius() + GETBODYRADIUS() + GETSKILLRANGE_APPLY(sSKILL,wLEVEL) + 2 );
	vTarget = vFrom + vDir * fDetectRange;

	VEC_SK_TAR vecTargetID = DetectTarget ( vFrom, vTarget, wPIERCENUM );

	if( !vecTargetID.empty() )
	{
		VEC_SK_ITER iter = vecTargetID.begin();;
		for( ; iter != vecTargetID.end(); ++iter )
		{
			if ( wPIERCENUM<=m_wTARNUM )	break;
			if ( EMTARGET_NET<=m_wTARNUM )	break;

			m_sTARIDS[m_wTARNUM] = STARID(iter->emCrow,iter->dwID);
			++m_wTARNUM;	
		}
	}

	if ( m_wTARNUM==0 )		return FALSE;

	return TRUE;
}

//	�ڱ����� ��ų üũ ( ��ġ�� ���� )
BOOL GLSummonField::SKT_TARZONEOUR ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_vTARPOS = *pvTarPos;
	D3DXVECTOR3 vFindPos = *pvTarPos;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;
	if ( wTARNUM<=m_wTARNUM )	return TRUE;

	//	Note : ��Ƽ���� �߿� Skill ������ ������ ��� �˻�.
	//
	//PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	//if ( !pLand )	return TRUE;

	//TARGETMAP	Targetmap;
	//float fDetectRange = GETBODYRADIUS() + static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2;

	//DWORD dwIndex = 0;
	//GLPARTY_CLIENT* pMember = GLPartyClient::GetInstance().GetMaster ();
	//while ( pMember && dwIndex<MAXPARTY )
	//{
	//	if ( !pMember->ISONESELF() )
	//	{
	//		PGLCHARCLIENT pChar = pLand->GetChar ( pMember->m_dwGaeaID );
	//		
	//		D3DXVECTOR3 vMemPos = pMember->m_vPos;
	//		if ( pChar )	 vMemPos = vFindPos;

	//		float fLength = D3DXVec3Length ( &D3DXVECTOR3(vFindPos-vMemPos) );
	//		if ( fLength <= fDetectRange )
	//		{
	//			STARGETID sFindID ( pChar->GETCROW(), pChar->m_dwGaeaID, vMemPos );
	//			Targetmap.insert ( std::make_pair(fLength,sFindID) );
	//		}
	//	}

	//	pMember = GLPartyClient::GetInstance().GetMember ( dwIndex++ );
	//}

	////	Note : �����ͺ��� ������ ������ŭ �̾Ƴ���.
	////
	//TARGETMAP_ITER iter = Targetmap.begin();
	//TARGETMAP_ITER iter_end = Targetmap.end();
	//for ( WORD i=m_wTARNUM; (iter!=iter_end) && (i<EMTARGET_NET); ++iter, ++i )
	//{
	//	if ( wTARNUM<=m_wTARNUM )	break;

	//	m_sTARIDS[m_wTARNUM].wCrow = static_cast<WORD> ( (*iter).second.emCrow );
	//	m_sTARIDS[m_wTARNUM].wID = static_cast<WORD> ( (*iter).second.dwID );
	//	++m_wTARNUM;
	//}

	return TRUE;
}

//	���鿡�� ��ų üũ ( ��ġ�� ���� )
BOOL GLSummonField::SKT_TARZONEENERMY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_vTARPOS = *pvTarPos;
	D3DXVECTOR3 vFindPos = *pvTarPos;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;

	//	PC, SUMMON �˻�
	int nApplyRange = int ( static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2 );
	VEC_SK_TAR vecTargetID = DetectTarget ( vFindPos, nApplyRange, DWORD(wTARNUM) );

	if( !vecTargetID.empty() )
	{
		VEC_SK_ITER iter = vecTargetID.begin();;
		for( ; iter != vecTargetID.end(); ++iter )
		{
			if ( wTARNUM<=m_wTARNUM )		break;
			if ( EMTARGET_NET<=m_wTARNUM )	break;

			m_sTARIDS[m_wTARNUM] = STARID(iter->emCrow,iter->dwID);
			++m_wTARNUM;	
		}
	}

	if ( m_wTARNUM==0 )		return FALSE;

	return TRUE;
}

//	��ο��� ��ų üũ ( ��ġ�� ���� )
BOOL GLSummonField::SKT_TARZONEANYBODY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL )
{
	const SKILL::CDATA_LVL &sSKILL_DATA = sSKILL.m_sAPPLY.sDATA_LVL[wLEVEL];

	m_vTARPOS = *pvTarPos;
	D3DXVECTOR3 vFindPos = *pvTarPos;

	WORD wTARNUM = sSKILL_DATA.wTARNUM;

	//	CROW �˻�.
	int nApplyRange = int ( static_cast<float>(sSKILL_DATA.wAPPLYRANGE) + 2 );
	ARRAY_CROW* pDetectedCROW = m_pLandMan->DetectCROW ( vFindPos, nApplyRange, DWORD(wTARNUM) );

	if ( pDetectedCROW )
	{
		ARRAY_CROW_ITER iter = pDetectedCROW->begin();
		ARRAY_CROW_ITER iter_end = pDetectedCROW->end();
		for ( ; iter!=iter_end; ++iter )
		{
			if ( wTARNUM<=m_wTARNUM )		break;
			if ( EMTARGET_NET<=m_wTARNUM )	break;

			PGLCROW pCrow = (*iter).pCrow;
			WORD wCrow = (WORD) pCrow->GetCrow();
			WORD wID = (WORD) pCrow->GetCtrlID();

			m_sTARIDS[m_wTARNUM] = STARID(wCrow,wID);
			++m_wTARNUM;
		}
	}

	if ( m_wTARNUM==0 )		return FALSE;

	return TRUE;
}


BOOL GLSummonField::SelectSkillTarget ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const SNATIVEID &sCheckSkill, const WORD wLevel )
{
	m_wTARNUM = 0;

	for ( int i=0; i<EMTARGET_NET; i++ )
		m_sTARIDS[i] = STARID();

	//	Note : ��ų ���� ������.
	//
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sCheckSkill.wMainID, sCheckSkill.wSubID );
	if ( !pSkill )							return FALSE;

	switch ( pSkill->m_sBASIC.emIMPACT_TAR )
	{
	case TAR_SELF:
		switch ( pSkill->m_sBASIC.emIMPACT_REALM )
		{
		case REALM_KEEP_ZONE:	return FALSE;

		case REALM_SELF:
			m_sTARIDS[m_wTARNUM].wCrow = static_cast<WORD>(GETCROW());
			m_sTARIDS[m_wTARNUM].wID = static_cast<WORD>(GetCtrlID());
			++m_wTARNUM;
			return TRUE;

		case REALM_ZONE:
			switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
			{
			case SIDE_OUR:		return SKT_SELFZONEOUR ( sTargetID, pvTarPos, *pSkill, wLevel );
			case SIDE_ENEMY:	return SKT_SELFZONEENERMY ( sTargetID, pvTarPos, *pSkill, wLevel );
			case SIDE_ANYBODY:	return SKT_SELFZONANYBODY ( sTargetID, pvTarPos, *pSkill, wLevel );
			};
			return FALSE;
		};
		return FALSE;

	case TAR_SPEC:
		{
			if ( sTargetID.dwID == EMTARGET_NULL )	return FALSE;

			switch ( pSkill->m_sBASIC.emIMPACT_REALM )
			{
			case REALM_KEEP_ZONE:	return FALSE;

			case REALM_SELF:
				switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
				{
				case SIDE_OUR:		return SKT_TARSPECOUR_SELF ( sTargetID, pvTarPos, *pSkill, wLevel );
				case SIDE_ENEMY:	return SKT_TARSPECENERMY_SELF ( sTargetID, pvTarPos, *pSkill, wLevel );
				case SIDE_ANYBODY:	return SKT_TARSPECANYBODY_SELF ( sTargetID, pvTarPos, *pSkill, wLevel );
				};
				return TRUE;

			case REALM_ZONE:
				switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
				{
				case SIDE_OUR:		return SKT_TARSPECOUR ( sTargetID, pvTarPos, *pSkill, wLevel );
				case SIDE_ENEMY:	return SKT_TARSPECENERMY ( sTargetID, pvTarPos, *pSkill, wLevel );
				case SIDE_ANYBODY:	return SKT_TARSPECANYBODY ( sTargetID, pvTarPos, *pSkill, wLevel );
				};
				return FALSE;

			case REALM_FANWIZE:
				switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
				{
				case SIDE_OUR:		return FALSE;
				case SIDE_ENEMY:	return SKT_TARSPECFANWIZE ( sTargetID, pvTarPos, *pSkill, wLevel );
				case SIDE_ANYBODY:	return FALSE;
				};
				return FALSE;
			};
		}
		break;

	case TAR_SELF_TOSPEC:
		switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
		{
		case SIDE_OUR:		return FALSE;
		case SIDE_ENEMY:	return SKT_TARSELFTOSPEC ( sTargetID, pvTarPos, *pSkill, wLevel );
		case SIDE_ANYBODY:	return FALSE;
		};
		return FALSE;

	case TAR_ZONE:
		if ( !pvTarPos )		return FALSE;
		switch ( pSkill->m_sBASIC.emIMPACT_SIDE )
		{
		case SIDE_OUR:		return SKT_TARZONEOUR ( sTargetID, pvTarPos, *pSkill, wLevel );
		case SIDE_ENEMY:	return SKT_TARZONEENERMY ( sTargetID, pvTarPos, *pSkill, wLevel );
		case SIDE_ANYBODY:	return SKT_TARZONEANYBODY ( sTargetID, pvTarPos, *pSkill, wLevel );
		};
		return FALSE;
	};

	return FALSE;
}


void GLSummonField::SkillProc ( BOOL bLowSP )
{
	if ( !m_pAttackProp )	return;
	if ( !m_pOwner )		return;

	SANIATTACK &sAniAttack = m_pAttackProp->sAniAttack;

	//	��ų ���� ������.
	SNATIVEID skill_id = m_idACTIVESKILL;
	WORD wSKILL_LVL = m_wACTIVESKILL_LVL;

	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id );
	if ( !pSkill )	return;

	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[wSKILL_LVL];

	int nEXP_NUM = 0;
	int nALL_LVL = 0;
	int nALL_VARHP = 0, nALL_FULLHP = 0;
	int nALL_VARMP = 0, nALL_FULLMP = 0;
	int nALL_VARSP = 0, nALL_FULLSP = 0;

	WORD wMAX_TAR = 0;
	if ( pSkill->m_sBASIC.emIMPACT_TAR == TAR_SELF_TOSPEC )			wMAX_TAR = sSKILL_DATA.wPIERCENUM + GETSUM_PIERCE() + 1;
	else if ( pSkill->m_sBASIC.emIMPACT_REALM == REALM_FANWIZE )	wMAX_TAR = sSKILL_DATA.wTARNUM * ( sSKILL_DATA.wPIERCENUM + GETSUM_PIERCE() + 1 );
	else															wMAX_TAR = sSKILL_DATA.wTARNUM;

	if ( m_wTARNUM > wMAX_TAR )		m_wTARNUM = wMAX_TAR;

	/*dash skill logic, Juver, 2017/06/17 */
	BOOL bACTDASH = FALSE;

	//	Note : ��ų�� ����Ǵ� Ÿ�� �˻�.
	//
	STARGETID sTARID;
	for ( WORD i=0; i<m_wTARNUM; ++i )
	{
		const STARID &_sTARID = m_sTARIDS[i];

		sTARID.emCrow = _sTARID.GETCROW();
		sTARID.dwID = _sTARID.GETID();
		GLACTOR* pACTOR = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, sTARID );
		if ( !pACTOR )					continue;

		for ( WORD j=0; j<sSKILL_DATA.wAPPLYNUM; ++j )
		{
			if ( pACTOR->GetNowHP()==0 )	continue;

			//	Note : ���� ������ �߻�.
			//
			DWORD dwDamageFlag = DAMAGE_TYPE_NONE;
			int nVAR_HP(0), nVAR_MP(0), nVAR_SP(0);

			//	����ġ.
			short nRESIST = pACTOR->GETRESIST().GetElement(pSkill->m_sAPPLY.emELEMENT);
			if ( nRESIST>699 )	nRESIST = 699;

			//	SKILL �⺻ ����.
			//
			switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
			{
			case SKILL::EMFOR_HP:
				if ( sSKILL_DATA.fBASIC_VAR < 0.0f )		//	��󿡰� ���ظ� �ִ� ��ų.
				{
					//					bCRITICAL = CALCDAMAGE ( nVAR_HP, bShock, sTARID, m_pLandMan, pSkill, wSKILL_LVL, GLPeriod::GetInstance().GetWeather(), sAniAttack.m_wDivCount );
					DWORD dwWeather = GLPeriod::GetInstance().GetMapWeather( m_pLandMan->GetMapID().wMainID, m_pLandMan->GetMapID().wSubID );
					dwDamageFlag = CALCDAMAGE_SKILL ( nVAR_HP, m_dwGUID, sTARID, m_pLandMan, pSkill, wSKILL_LVL, dwWeather, sAniAttack.m_wDivCount );
					nVAR_HP = - nVAR_HP;
				}
				else										//	����� ȸ������ �ִ� ��ų.
				{
					nVAR_HP += (int) ( sSKILL_DATA.fBASIC_VAR );
				}
				break;

			case SKILL::EMFOR_MP:
				if ( sSKILL_DATA.fBASIC_VAR < 0.0f )		//	��󿡰� ���ظ� �ִ� ��ų.
				{
					int nVAR = int(-sSKILL_DATA.fBASIC_VAR);
					nVAR_MP -= (int) ( nVAR - (nVAR*nRESIST*0.01f*GLCONST_CHAR::fRESIST_G ) );
				}
				else										//	����� ȸ������ �ִ� ��ų.
				{
					nVAR_MP += (int) ( sSKILL_DATA.fBASIC_VAR );
				}
				break;

			case SKILL::EMFOR_SP:
				if ( sSKILL_DATA.fBASIC_VAR < 0.0f )		//	��󿡰� ���ظ� �ִ� ��ų.
				{
					int nVAR = int(-sSKILL_DATA.fBASIC_VAR);
					nVAR_SP -= (int) ( nVAR - (nVAR*nRESIST*0.01f*GLCONST_CHAR::fRESIST_G ) );
				}
				else										//	����� ȸ������ �ִ� ��ų.
				{
					nVAR_SP += (int) ( sSKILL_DATA.fBASIC_VAR );
				}
				break;
			};

			//	Note : SP �����ÿ��� ��ȭ ���� ������ ����.
			//
			if ( bLowSP )
			{
				nVAR_HP /= 2;
				nVAR_MP /= 2;
				nVAR_SP /= 2;
			}

			//	Note : ��ų Ư�� ���.
			//
			int nGATHER_HP(0), nGATHER_MP(0), nGATHER_SP(0);

			for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
			{
				const SKILL::SSPEC &sSKILL_SPEC = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wSKILL_LVL];

				switch ( pSkill->m_sAPPLY.sSpecs[nSpec].emSPEC )
				{
				case EMSPECA_HP_GATHER:
					nGATHER_HP += int ( abs(nVAR_HP) * sSKILL_SPEC.fVAR1 );
					break;

				case EMSPECA_MP_GATHER:
					nGATHER_MP += int ( abs(nVAR_MP) * sSKILL_SPEC.fVAR1 );
					break;

				case EMSPECA_SP_GATHER:
					nGATHER_SP += int ( abs(nVAR_SP) * sSKILL_SPEC.fVAR1 );
					break;
				};
			}



			//	Note : ��ų �⺻ ����.
			//
			SSKILLACT sSKILLACT;
			sSKILLACT.sID = STARGETID(CROW_SUMMON,GetCtrlID());
			sSKILLACT.sID_TAR = STARGETID(_sTARID.GETCROW(),_sTARID.GETID());
			sSKILLACT.fDELAY = pSkill->m_sEXT_DATA.fDELAY4DAMAGE;
			sSKILLACT.emAPPLY = pSkill->m_sBASIC.emAPPLY;
			sSKILLACT.dwDamageFlag = dwDamageFlag;

			//	Note : ü�� ��ȭ ����.
			//
			sSKILLACT.nVAR_HP = nVAR_HP;
			sSKILLACT.nVAR_MP = nVAR_MP;
			sSKILLACT.nVAR_SP = nVAR_SP;

			//	Note : ü�� ��� ����.
			//
			sSKILLACT.nGATHER_HP = nGATHER_HP;
			sSKILLACT.nGATHER_MP = nGATHER_MP;
			sSKILLACT.nGATHER_SP = nGATHER_SP;

			if ( sSKILLACT.VALID() )
			{
				m_pLandMan->RegSkillAct ( sSKILLACT );
			}
		}

		//	Note : ��ų ���� ����.
		//
		SSKILLACTEX sSKILLACTEX;
		sSKILLACTEX.sID = STARGETID(CROW_SUMMON,GetCtrlID());
		sSKILLACTEX.sID_TAR = STARGETID(_sTARID.GETCROW(),_sTARID.GETID());
		sSKILLACTEX.fDELAY = pSkill->m_sEXT_DATA.fDELAY4DAMAGE;

		sSKILLACTEX.idSKILL = skill_id;
		sSKILLACTEX.wSKILL_LVL = wSKILL_LVL;

		//	Note : ���� �̻� ����.
		//
		ITEM::SSATE_BLOW sBLOW;
		sBLOW.emTYPE = EMBLOW_NONE;

		const SKILL::SSTATE_BLOW &sSKILL_BLOW = pSkill->m_sAPPLY.sSTATE_BLOW[wSKILL_LVL];

		sBLOW.emTYPE = pSkill->m_sAPPLY.emSTATE_BLOW;
		sBLOW.fRATE = sBLOW.fRATE;
		sBLOW.fLIFE = pSkill->m_sAPPLY.sDATA_LVL[wSKILL_LVL].fLIFE;
		sBLOW.fVAR1 = sBLOW.fVAR1;
		sBLOW.fVAR2 = sBLOW.fVAR2;

		if ( sBLOW.emTYPE!=EMBLOW_NONE )
		{
			//	Note : �߻� Ȯ�� ���.
			//
			short nBLOWRESIST = pACTOR->GETRESIST().GetElement ( STATE_TO_ELEMENT(sBLOW.emTYPE) );
			if ( nBLOWRESIST>99 )	nBLOWRESIST = 99;

			//			float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( sBLOW.emTYPE, GLPeriod::GetInstance().GetWeather(), m_pLandMan->IsWeatherActive() );
			DWORD dwWeather = GLPeriod::GetInstance().GetMapWeather( m_pLandMan->GetMapID().wMainID, m_pLandMan->GetMapID().wSubID );
			float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( sBLOW.emTYPE, dwWeather, m_pLandMan->IsWeatherActive() );

			BOOL bBLOW(FALSE);
			if ( !(pACTOR->GETHOLDBLOW()&STATE_TO_DISORDER(sBLOW.emTYPE)) )
			{
				bBLOW = GLOGICEX::CHECKSTATEBLOW ( sBLOW.fRATE * fPOWER, GETLEVEL(), pACTOR->GetLevel(), nBLOWRESIST );
			}

			if ( bBLOW )
			{
				//	Note : �����̻� �߻�.
				//	
				SSTATEBLOW sSTATEBLOW;
				float fLIFE = sBLOW.fLIFE * fPOWER;
				fLIFE = ( fLIFE - (fLIFE*nBLOWRESIST*0.01f*GLCONST_CHAR::fRESIST_G ) );

				sSTATEBLOW.emBLOW = sBLOW.emTYPE;
				sSTATEBLOW.fAGE = fLIFE;
				sSTATEBLOW.fSTATE_VAR1 = sBLOW.fVAR1;
				sSTATEBLOW.fSTATE_VAR2 = sBLOW.fVAR2;

				//	Note : ���� �̻� �߻� ����.
				//
				sSKILLACTEX.sSTATEBLOW = sSTATEBLOW;
			}
		}

		//	Note : ��ų Ư�� ���.
		//
		BOOL bActionMovement = FALSE;
		BOOL bCUREFLAG = FALSE;
		BOOL bREMOVEFLAG = FALSE;

		//if ( bCrushBlowOne )	bActionMovement = TRUE;
		if ( bACTDASH )			bActionMovement = TRUE;

		for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
		{
			const SKILL::SSPEC &sSKILL_SPEC = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wSKILL_LVL];
			switch ( pSkill->m_sAPPLY.sSpecs[nSpec].emSPEC )
			{
			case EMSPECA_PUSHPULL:
				{
					if ( bActionMovement )	break;
					if ( !pACTOR->IsValidBody() )				break;
					if ( RANDOM_POS > sSKILL_SPEC.fVAR2 )		break;	//	Note : �߻�Ȯ�� ����.
					sSKILLACTEX.fPUSH_PULL = sSKILL_SPEC.fVAR1;
					bActionMovement = TRUE;
				}break;

				/*push pull skill logic, Juver, 2017/06/04 */
			case EMSPECA_PUSH:
				{
					if ( bActionMovement )			break;
					if ( !pACTOR->IsValidBody() )	break;
					if ( RANDOM_POS > sSKILL_SPEC.fVAR1 )		break;
					sSKILLACTEX.fPUSH_PULL = sSKILL_SPEC.fVAR2; //distance
					sSKILLACTEX.bPush = true;
					bActionMovement = TRUE;
				}break;

				/*push pull skill logic, Juver, 2017/06/04 */
			case EMSPECA_PULL:
				{
					if ( bActionMovement )			break;
					if ( !pACTOR->IsValidBody() )	break;
					if ( RANDOM_POS > sSKILL_SPEC.fVAR1 )		break;
					sSKILLACTEX.fPUSH_PULL = sSKILL_SPEC.fVAR2; //pull speed
					sSKILLACTEX.bPull = true;
					bActionMovement = TRUE;
				}break;

				/*dash skill logic, Juver, 2017/06/17 */
			case EMSPECA_ONWARD:
				{
					if ( bActionMovement )			break;
					if ( bACTDASH )					break;
					if ( !pACTOR->IsValidBody() )	break;
					if ( RANDOM_POS > sSKILL_SPEC.fVAR1 )		break;
					sSKILLACTEX.fPUSH_PULL = sSKILL_SPEC.fVAR2; //dash speed
					sSKILLACTEX.wActionAnim = (WORD)sSKILL_SPEC.dwFLAG; //animation
					sSKILLACTEX.bDash = true;
					bACTDASH = TRUE;
					bActionMovement = TRUE;
				}break;

			case EMSPECA_HP_DIV:
			case EMSPECA_MP_DIV:
			case EMSPECA_SP_DIV:
				break;

			case EMSPECA_RECBLOW:
				{
					//	Note : ���� �̻� ġ��.
					//
					if ( bCUREFLAG )	break;
					sSKILLACTEX.dwCUREFLAG |= pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wSKILL_LVL].dwFLAG;
					bCUREFLAG = TRUE;
				}break;

				/*debuff skill logic, Juver, 2017/06/10 */
			case EMSPECA_BUFF_REMOVE:
				{
					if ( bREMOVEFLAG )	break;
					if ( sSKILLACTEX.bDebuff )	break;
					sSKILLACTEX.dwRemoveFlag = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[wSKILL_LVL].dwFLAG;
					sSKILLACTEX.bDebuff = true;
					bREMOVEFLAG = TRUE;
				}break;
			};
		}


		switch (pSkill->m_sAPPLY.emBASIC_TYPE)
		{
		case SKILL::EMFOR_CURE:
			//	Note : ���� �̻� ġ��.
			//
			sSKILLACTEX.dwCUREFLAG |= pSkill->m_sAPPLY.dwCUREFLAG;
			break;
		};

		if ( sSKILLACTEX.VALID() )
		{
			m_pLandMan->RegSkillActEx ( sSKILLACTEX );
		}
	}

	//	Note : ����ġ ȹ�� ����.
	//
	int nSUM_EXP = 0;
	if ( nEXP_NUM!=0 )
	{
		//	Note : ȸ���� �⿩���� ���� ����ġ �߻�.	( ���ݽô� ���� )
		//
		if ( nALL_VARHP>0 && nALL_VARMP>0 && nALL_VARSP>0 )
		{
			nALL_LVL /= nEXP_NUM;

			nALL_VARHP = abs(nALL_VARHP) / nEXP_NUM;
			nALL_VARMP = abs(nALL_VARMP) / nEXP_NUM;
			nALL_VARSP = abs(nALL_VARSP) / nEXP_NUM;

			nALL_FULLHP /= nEXP_NUM;
			nALL_FULLMP /= nEXP_NUM;
			nALL_FULLSP /= nEXP_NUM;

			//	���� ��ȭ���� ���� ���� ����ġ�� ����.
			if ( nALL_VARHP!=0 )	nSUM_EXP += GLOGICEX::GLATTACKEXP(GETLEVEL(),nALL_LVL,nALL_VARHP,nALL_FULLHP);
			if ( nALL_VARMP!=0 )	nSUM_EXP += GLOGICEX::GLATTACKEXP(GETLEVEL(),nALL_LVL,nALL_VARMP,nALL_FULLMP);
			if ( nALL_VARSP!=0 )	nSUM_EXP += GLOGICEX::GLATTACKEXP(GETLEVEL(),nALL_LVL,nALL_VARSP,nALL_FULLSP);
		}
		//	Note : ���� ��ų ���� ����ġ.
		//
		else
		{
			nSUM_EXP = (pSkill->m_sBASIC.dwGRADE*(wSKILL_LVL+1)*100) / GETLEVEL();
			if ( nSUM_EXP < 1 )		nSUM_EXP = 1;
			if ( nSUM_EXP > 5 )		nSUM_EXP = 5;
		}
	}
}

DWORD GLSummonField::CALCDAMAGE_SKILL( int& rResultDAMAGE, const DWORD dwGaeaID, const STARGETID &cTargetID, 
						   const GLLandMan* pLandMan, const GLSKILL* pSkill/* =NULL */, DWORD dwskill_lev/* =0 */, 
						   DWORD dwWeatherFlag/* =NULL */, DWORD dwDivCount/* =0 */ )
{
	GLACTOR *pActor = GLGaeaServer::GetInstance().GetTarget ( pLandMan, cTargetID );
	if ( !pActor )		return FALSE;
	if ( !m_pOwner )	return FALSE;
	if ( pActor->GetMaxHP() == 0 )	return FALSE;
	if ( pActor->GetNowHP() == 0 )	return FALSE;

	/*ignore damage, Juver, 2017/12/12 */
	if ( pActor->IsIgnoreDamage() )
	{
		rResultDAMAGE = 1;
		return DAMAGE_TYPE_NONE;
	}

	int nDEFENSE = pActor->GetDefense ();
	int nDEFAULT_DEFENSE = pActor->GetBodyDefense ();
	int nITEM_DEFENSE = pActor->GetItemDefense ();

	int nLEVEL = pActor->GetLevel ();
	float fSTATE_DAMAGE = pActor->GETSTATE_DAMAGE ();
	const SRESIST &sRESIST = pActor->GETRESIST ();

	EMSLOT emRHand = m_pOwner->GetCurRHand();
	EMSLOT emLHand = m_pOwner->GetCurLHand();

	WORD wGRADE = 0;
	const SITEMCUSTOM &sRHAND = m_pOwner->GET_SLOT_ITEM(emRHand);
	if ( sRHAND.sNativeID != SNATIVEID(false) )
		wGRADE = sRHAND.GETGRADE(EMGRINDING_DAMAGE);

	int nCrushingBlow = (int)( m_pOwner->m_sSUMITEM.fIncR_CrushingBlow * 100 );

	DWORD dwDamageFlag = DAMAGE_TYPE_NONE;
	bool bShock = false;
	bool bCrushingBlow = false;
	bool bCritical = false; 
	bool bPsyDamage = true;

	DAMAGE_SPEC	sDamageSpec = pActor->GetDamageSpec();
	float fDamageReduce = sDamageSpec.m_fPsyDamageReduce;
	float fDamageReflection = sDamageSpec.m_fPsyDamageReflection;
	float fDamageReflectionRate = sDamageSpec.m_fPsyDamageReflectionRate;

	DEFENSE_SKILL sDefenseSkill = pActor->GetDefenseSkill();

	GLPADATA gdDamage = m_pOwner->m_gdDAMAGE_SKILL;
	gdDamage.wLow += GETFORCE_LOW();
	gdDamage.wHigh += GETFORCE_HIGH();

	if ( pSkill )
	{
		const SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[dwskill_lev];

		//	Note : ��ų ���� ������ �Ҹ�Ǹ�, ������ ����ġ ����.
		//
		if ( sSKILL_DATA.wUSE_CHARMNUM > 0 )
		{
			SITEM* pItem = m_pOwner->GET_SLOT_ITEMDATA(emLHand);
			if ( pItem )
			{
				GLPADATA &sDATA = pItem->sSuitOp.gdDamage;
				gdDamage.wLow += sDATA.wLow;
				gdDamage.wHigh += sDATA.wHigh;
			}
		}


		float fRESIST_G = 0;
		switch ( pSkill->m_sBASIC.emAPPLY )
		{
			//	���� ����.
		case SKILL::EMAPPLY_PHY_SHORT:
			gdDamage.wLow += m_pOwner->m_sSUMITEM.gdDamage.wLow;
			gdDamage.wMax += m_pOwner->m_sSUMITEM.gdDamage.wMax;

			gdDamage.VAR_PARAM ( m_pOwner->m_wSUM_PA );
			// ���� ���ݽ� �Ӽ� ����ġ ���� ����
			// default.charset ���� ������
			// fRESIST_PHYSIC_G �� ��
			fRESIST_G = GLCONST_CHAR::fRESIST_PHYSIC_G;
			break;

			//	��Ÿ� ����.
		case SKILL::EMAPPLY_PHY_LONG:
			gdDamage.wLow += m_pOwner->m_sSUMITEM.gdDamage.wLow;
			gdDamage.wMax += m_pOwner->m_sSUMITEM.gdDamage.wMax;

			gdDamage.VAR_PARAM ( m_pOwner->m_wSUM_SA );
			// ���� ���ݽ� �Ӽ� ����ġ ���� ����
			// default.charset ���� ������
			// fRESIST_PHYSIC_G �� ��
			fRESIST_G = GLCONST_CHAR::fRESIST_PHYSIC_G;
			fDamageReflection = 0.0f;
			fDamageReflectionRate = 0.0f;			
			break;

			//	���� ����.
		case SKILL::EMAPPLY_MAGIC:
			nDEFENSE = 0;						//	���� �����϶��� �Ϲ� ���� ���õ�.
			nDEFAULT_DEFENSE = 0;				//	���� �����϶��� �Ϲ� ���� ���õ�.
			nITEM_DEFENSE = 0;					//	���� �����϶��� �Ϲ� ���� ���õ�.

			gdDamage.VAR_PARAM ( m_pOwner->m_wSUM_MA );
			// ���� ���ݽ� �Ӽ� ����ġ ���� ����
			// default.charset ���� ������
			// fRESIST_G �� ��
			fRESIST_G = GLCONST_CHAR::fRESIST_G;
			fDamageReduce = sDamageSpec.m_fMagicDamageReduce;
			fDamageReflection = sDamageSpec.m_fMagicDamageReflection;
			fDamageReflectionRate = sDamageSpec.m_fMagicDamageReflectionRate;
			bPsyDamage = false;

			break;

		default:
			GASSERT(0&&"CALCDAMAGE() ���� �������� ������� �ʴ� ��ų.");
			break;
		};

		for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
		{
			if ( pSkill->m_sAPPLY.sSpecs[nSpec].emSPEC == EMSPECA_CRUSHING_BLOW )	
			{
				const SKILL::SSPEC &sSKILL_SPEC = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[dwskill_lev];
				nCrushingBlow += (int) ( sSKILL_SPEC.fVAR2 * 100 ) ;
			}
		}


		EMELEMENT emELMT(EMELEMENT_SPIRIT);
		if ( pSkill->m_sAPPLY.emELEMENT==EMELEMENT_ARM )
		{
			SITEM *pITEM = m_pOwner->GET_ELMT_ITEM ();
			if ( pITEM )	emELMT = STATE_TO_ELEMENT(pITEM->sSuitOp.sBLOW.emTYPE);
		}
		else
		{
			emELMT = pSkill->m_sAPPLY.emELEMENT;
		}

		if ( pLandMan )
		{
			short nRESIST = sRESIST.GetElement ( emELMT );
			if ( nRESIST>699 )	nRESIST = 699;
			float fPOWER = GLOGICEX::WEATHER_ELEMENT_POW ( emELMT, dwWeatherFlag, pLandMan->IsWeatherActive() );

			//	��ų�� ������ ��꿡 ������ �ִ� ���� �⺻���� Ư������ �˻�.
			float fSKILL_VAR = sSKILL_DATA.fBASIC_VAR;

			// 2006-03-28 Jgkim��ȹ�� ��û���� �ּ�ó��, ������ ���ĺ����
			// int nVAR = abs ( int(fSKILL_VAR*fPOWER) );
			// nVAR = nVAR - (int) ( nVAR*nRESIST/100.0f*fRESIST_G );
			// if ( nVAR<0 )	nVAR = 0;

			// //	Note : ������� ����ȴ�, ����� �ݿ���.
			// gdDamage.wLow += WORD ( nVAR + (gdDamage.wLow*wGRADE)/GLCONST_CHAR::fDAMAGE_GRADE_K );
			// gdDamage.wHigh += WORD ( nVAR + (gdDamage.wHigh*wGRADE)/GLCONST_CHAR::fDAMAGE_GRADE_K );


			// ��ų������ = �⺻��ų������*������ ���� �������ݿ���
			int nVAR = abs ( int(fSKILL_VAR*fPOWER) );

			// �ݿ���
			float fGrade = (float) wGRADE / GLCONST_CHAR::fDAMAGE_GRADE_K;

			// �ּ�/�ִ� ������ =  ��ų������ + (�ּ�/�ִ� ������) * �ݿ���
			gdDamage.wLow  += WORD (nVAR + ((float) gdDamage.wLow  * fGrade));
			gdDamage.wHigh += WORD (nVAR + ((float) gdDamage.wHigh * fGrade));

			// ��ü���װ� = ����� ���װ� / 100 * �Ӽ�����ġ �������
			float fResistTotal = (float) ((float) nRESIST * 0.01f * fRESIST_G);

			// �ּ�/�ִ� ������ = ������-(������*��ü���װ�)
			gdDamage.wLow  -= (WORD) ((float) gdDamage.wLow  * fResistTotal);
			gdDamage.wHigh -= (WORD) ((float) gdDamage.wHigh * fResistTotal);

			// �������� 0 ���� ������ 0 ���� �����Ѵ�.
			if (gdDamage.wLow <0) gdDamage.wLow  = 0;
			if (gdDamage.wHigh<0) gdDamage.wHigh = 0;
		}
	}
	else
	{
		gdDamage.wLow += m_pOwner->m_sSUMITEM.gdDamage.wLow;
		gdDamage.wMax += m_pOwner->m_sSUMITEM.gdDamage.wMax;

		if ( m_pOwner->ISLONGRANGE_ARMS() )	gdDamage.VAR_PARAM ( m_pOwner->m_wSUM_SA );	//	��Ÿ� ����.
		else						gdDamage.VAR_PARAM ( m_pOwner->m_wSUM_PA );	//	���� ����.
	}

	//	���ݷ�. ��ȭ�� �ݿ�.
	gdDamage.wLow = int ( gdDamage.wLow * m_pOwner->m_fDamageRate );
	gdDamage.wHigh = int ( gdDamage.wHigh * m_pOwner->m_fDamageRate );

	//	Note : �߰� ����ġ ����.
	int nExtFORCE = 0;
	int ndxLvl = nLEVEL - GETLEVEL();
	if ( ndxLvl > 0 )		nExtFORCE = int(RANDOM_POS*ndxLvl*0.1f);


	if ( ndxLvl > 5 )		ndxLvl = 5;
	if ( ndxLvl < -5 )		ndxLvl = -5;

	//	Note : Critical �߻� Ȯ��.
	int nPerHP = ((GETHP()*100)/GETMAXHP());
	if ( nPerHP <= 10 )	nPerHP = 10;
	int nPercentCri = 1000 / nPerHP - 10 + ndxLvl;
	nPercentCri += (int)( m_pOwner->m_sSUMITEM.fIncR_Critical * 100 );

	if ( nPercentCri > (int)GLCONST_CHAR::dwCRITICAL_MAX )		nPercentCri = GLCONST_CHAR::dwCRITICAL_MAX;
	if ( nPercentCri < 0 )	nPercentCri = 0;

	//	ũ��Ƽ�� �߻� ���� �Ǵ�.
	if ( nPercentCri > (RANDOM_POS*100) )	bCritical = true;

	//	����Ÿ�� �߻� ���� �Ǵ�
	if ( nCrushingBlow > GLCONST_CHAR::dwCRUSHING_BLOW_MAX )		nCrushingBlow = GLCONST_CHAR::dwCRUSHING_BLOW_MAX;	
	if ( nCrushingBlow > (RANDOM_POS*100) )	bCrushingBlow = true;

	//	����� �ִ� �ּҰ� ������ ���� ����� ����.
	int  nDAMAGE_NOW = 0;
	nDAMAGE_NOW = int ( gdDamage.wLow + (gdDamage.wHigh-gdDamage.wLow)*RANDOM_POS );
	int nDAMAGE_OLD = ( nDAMAGE_NOW + nExtFORCE );

	//	���� ���� ����� ����.
	int nNetDAMAGE = int ( nDAMAGE_OLD*(1.0f-GLCONST_CHAR::fLOW_SEED_DAMAGE) - nDEFENSE );
	if ( nNetDAMAGE < 0 )	nNetDAMAGE = 0;
	if ( nNetDAMAGE > 0 )	rResultDAMAGE = int ( nDAMAGE_OLD - nDEFENSE );
	else					rResultDAMAGE = int ( nNetDAMAGE + (nDAMAGE_OLD*GLCONST_CHAR::fLOW_SEED_DAMAGE)*RANDOM_POS );
	rResultDAMAGE = int(rResultDAMAGE*fSTATE_DAMAGE);

	//	�� ����� ����� �ݿ�.
	float fRATE = ( 1.0f - nDEFAULT_DEFENSE*nITEM_DEFENSE / GLCONST_CHAR::fDAMAGE_DEC_RATE );
	if ( fRATE > 1.0f )		fRATE = 1.0f;
	if ( fRATE < 0.0f )		fRATE = 0.0f;
	rResultDAMAGE = int(rResultDAMAGE*fRATE);

	if ( bCritical && bCrushingBlow )
	{
		rResultDAMAGE = int ( rResultDAMAGE* GLCONST_CHAR::dwCRUSHING_BLOW_DAMAGE / 100 );
	}else{
		if ( bCritical )	rResultDAMAGE = int ( rResultDAMAGE* GLCONST_CHAR::dwCRITICAL_DAMAGE / 100 );
		if ( bCrushingBlow ) rResultDAMAGE = int ( rResultDAMAGE* GLCONST_CHAR::dwCRUSHING_BLOW_DAMAGE / 100 );
	}

	//	������ ���
	if ( fDamageReduce > 0.0f ) 
	{
		int nDamageReduce = (int) ( ( (rResultDAMAGE * fDamageReduce) * nLEVEL ) / GLCONST_CHAR::wMAX_LEVEL );
		rResultDAMAGE -= nDamageReduce;

		if ( bPsyDamage ) dwDamageFlag += DAMAGE_TYPE_PSY_REDUCE;
		else dwDamageFlag += DAMAGE_TYPE_MAGIC_REDUCE;
	}


	//	������ �ݻ� ���
	if ( fDamageReflectionRate > 0.0f )
	{
		if ( fDamageReflectionRate > (RANDOM_POS*1) )
		{
			int nDamageReflection = (int) ( ( (rResultDAMAGE * fDamageReflection) * nLEVEL ) / GLCONST_CHAR::wMAX_LEVEL );

			if ( nDamageReflection > 0 ) 
			{
				if ( bPsyDamage ) dwDamageFlag += DAMAGE_TYPE_PSY_REFLECTION;
				else dwDamageFlag += DAMAGE_TYPE_MAGIC_REFLECTION;

				// �ǰ��� ���忡�� �������� �ٽ� ������.
				STARGETID sActor(GETCROW(),dwGaeaID);
				pActor->DamageReflectionProc( nDamageReflection, sActor );
			}
		}
	}

	//	�ߵ� ��ų
	if ( sDefenseSkill.m_dwSkillID != NATIVEID_NULL() )
	{
		if ( sDefenseSkill.m_fRate > (RANDOM_POS*1) )
		{
			STARGETID sActor(GETCROW(),dwGaeaID);
			pActor->DefenseSkill( sDefenseSkill.m_dwSkillID, 
				sDefenseSkill.m_wLevel, 
				sActor );
		}
	}

	if ( rResultDAMAGE <= 1 )
	{
		bCritical = false;
		rResultDAMAGE = 1;
	}

	if ( dwDivCount>1 )
	{
		rResultDAMAGE /= dwDivCount;
	}

	bShock = GLOGICEX::CHECKSHOCK ( GETLEVEL(), nLEVEL, rResultDAMAGE, bCritical );

	if ( bShock )			dwDamageFlag += DAMAGE_TYPE_SHOCK;
	if ( bCritical )		dwDamageFlag += DAMAGE_TYPE_CRITICAL;
	if ( bCrushingBlow )	dwDamageFlag += DAMAGE_TYPE_CRUSHING_BLOW;

	return dwDamageFlag;
}