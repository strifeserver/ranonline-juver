#include "stdafx.h"
#include "./GLogicEx.h"
#include "./GLItemMan.h"
#include "./GLGaeaServer.h"
#include "./GLChar.h"
#include "./GLQuest.h"
#include "./GLQuestMan.h"
#include "./GLSchoolFreePK.h"
#include "./DxGlobalStage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace GLOGICEX
{
	int CALCKILLEXP ( WORD wMYLEVEL, const STARGETID &cTargetID, const GLLandMan* pLandMan )
	{	
		GLACTOR *pActor = GLGaeaServer::GetInstance().GetTarget ( pLandMan, cTargetID );
		if ( !pActor )	return 0;

		WORD wAttackerLev = wMYLEVEL;
		WORD wDefenserLev = pActor->GetLevel();
		DWORD dwBonusExp = pActor->GetBonusExp();

		//	Note : ����ġ ����	
		return GLOGICEX::GLKILLEXP(wAttackerLev,wDefenserLev,dwBonusExp);
	}

	int CALCATTACKEXP ( WORD wMYLEVEL, const STARGETID &cTargetID, const GLLandMan* pLandMan, DWORD dwDamage )
	{
		GLACTOR *pActor = GLGaeaServer::GetInstance().GetTarget ( pLandMan, cTargetID );
		if ( !pActor )	return 0;

		WORD wTAR_LEVEL = pActor->GetLevel ();
		DWORD dwTAR_MAXHP = pActor->GetMaxHP ();
		DWORD dwBONUSEXP = pActor->GetBonusExp ();

		//	Note : ����ġ ����
		return GLOGICEX::GLATTACKEXP ( wMYLEVEL, wTAR_LEVEL, dwDamage, dwTAR_MAXHP, dwBONUSEXP );
	}
};

void GLCHARLOGIC::RESET_DATA ()
{
	int i=0;

	SCHARDATA2::Assign ( SCHARDATA2() );

	m_CHARINDEX = GLCI_BRAWLER_M;
	m_SKILLDELAY.clear();

	for ( i=0; i<SKILLFACT_SIZE; ++i )
		m_sSKILLFACT[i] = SSKILLFACT();

	m_dwHOLDBLOW = NULL;
	m_bSTATEBLOW = false;

	for ( i=0; i<EMBLOW_MULTI; ++i )
		m_sSTATEBLOWS[i] = SSTATEBLOW();

	m_fSTATE_MOVE = 1.0f;
	m_fSTATE_DELAY = 1.0f;

	m_fSTATE_DAMAGE = 1.0f;

	m_bSTATE_PANT = false;
	m_bSTATE_STUN = false;
	m_bINVISIBLE = false;
	m_bRECVISIBLE = false;

	m_fSKILL_MOVE = 0.0f;
	m_fOPTION_MOVE = 0.0f;

	m_sDefenseSkill.RESET();

	m_sSUMSTATS = SCHARSTATS();

	m_wSUM_AP = 0;
	m_wSUM_DP = 0;
	m_wSUM_PA = 0;
	m_wSUM_SA = 0;
	m_wSUM_MA = 0;

	m_sSUMRESIST = SRESIST();
	m_sSUMRESIST_SKILL = SRESIST();
	m_sSUMITEM = SSUM_ITEM();
	m_sSUM_PASSIVE = SPASSIVE_SKILL_DATA();

	m_nSUM_PIERCE = 0;
	m_fSUM_TARRANGE = 0;

	m_wACCEPTP = 0;
	m_wSUM_DisSP = 0;

	m_nHIT = 0;
	m_nSUM_HIT = 0;
	m_nAVOID = 0;
	m_nSUM_AVOID = 0;

	m_nDEFENSE_BODY = 0;
	m_nDEFENSE = 0;
	m_nDEFENSE_SKILL = 0;

	m_gdDAMAGE = GLPADATA();
	m_gdDAMAGE_SKILL = GLPADATA();
	m_gdDAMAGE_PHYSIC = GLPADATA();

	m_fDamageRate = 1.0f;
	m_fDefenseRate = 1.0f;

	m_fINCR_HP = 0.0f;
	m_fINCR_MP = 0.0f;
	m_fINCR_SP = 0.0f;

	m_fATTVELO = 0.0f;
	m_wATTRANGE = 0;
	m_wSUM_ATTRANGE = 0;
	m_fSKILLDELAY = 0.0f;

	m_emITEM_ATT = ITEMATT_NOTHING;

	m_emANISUBTYPE = AN_SUB_NONE;

	m_idACTIVESKILL = SNATIVEID(false);
	m_emANIMAINSKILL = AN_GUARD_N;
	m_emANISUBSKILL = AN_SUB_NONE;

	m_bUseArmSub = FALSE;

	for ( i=0; i<SLOT_TSIZE; ++i )
		m_pITEMS[i] = NULL;

	m_fIncHP = 0.0f;
	m_fIncMP = 0.0f;

	DEL_PLAYHOSTILE_ALL();	

	m_bVehicle = FALSE;
	m_bPassenger = FALSE;
	m_fVehicleSpeedRate = 0.0f;
	m_fVehicleSpeedVol = 0.0f;

	m_sDamageSpec.RESET();

	m_ExpSkills.clear();

	m_bSafeZone = false;

	/*prohibit potion skill logic, Juver, 2017/06/06 */
	m_bProhibitPotion = false;

	/*prohibit skill logic, Juver, 2017/06/06 */
	m_bProhibitSkill = false; 

	/*skill range spec logic, Juver, 2017/06/06 */
	m_fSUM_SKILL_ATTACKRANGE = 0.0f;
	m_fSUM_SKILL_APPLYRANGE = 0.0f;

	/*continuous damage skill logic, Juver, 2017/06/10 */
	m_mapContinuousDamage.clear();

	/*curse skill logic, Juver, 2017/06/10 */
	m_bCurse = false;
	m_fCurseDamage = 0.0f;

	/*vehicle booster system, Juver, 2017/08/11 */
	m_bBoosterCharge = false;
	m_bBoosterStart = false;
	m_fBoosterTimer = 0.0f;

	m_wAutoPotsAttemptCount = 0;
	m_fAutoPotsAttemptTimer = 0.0f;

	DISABLEALLLANDEFF();
}

void GLCHARLOGIC::INIT_NEW_CHAR ( const EMCHARINDEX _emCIndex, const DWORD dwUserID, const DWORD dwServerID, const char* szCharName,
								 const WORD _wSchool, const WORD wHair, const WORD wFace, const WORD _wHairColor, const WORD _wSex, const float _fScaleRange )
{
	EMCHARINDEX emCIndex = _emCIndex;
	WORD wSchool = _wSchool;

	if ( emCIndex>=GLCI_NUM_8CLASS )			emCIndex = GLCI_BRAWLER_M;
	if ( wSchool>=GLCONST_CHAR::wSCHOOLNUM )	wSchool = 0;

	SCHARDATA2 &CharData2 = GLCONST_CHAR::GET_CHAR_DATA2 ( wSchool, emCIndex );

	SCHARDATA2::Assign ( CharData2 );
	m_cInventory.SetItemGenTime();

	m_dwUserID		= dwUserID;			// ������ȣ.
	m_dwServerID	= dwServerID;		// �����׷�.
	StringCchCopy ( m_szName, CHAR_SZNAME, szCharName );	// ĳ���͸�.

	m_wSchool		= wSchool;
	m_wHair			= wHair;
	m_wFace			= wFace;
	m_wHairColor	= _wHairColor;
	m_wSex			= _wSex;
	m_fScaleRange	= _fScaleRange;

	INIT_DATA ( TRUE, TRUE );

	const GLCONST_CHARCLASS &cCONST = GLCONST_CHAR::cCONSTCLASS[emCIndex];

	if ( cCONST.dwHAIRNUM <= m_wHair )				m_wHair = 0;
	if ( cCONST.dwHEADNUM <= m_wFace )				m_wFace = 0;
	
	//	Note : �ʱ� ���� ��ġ ����. ( �б��� ���� Ʋ��. )
	//
	if ( GLCONST_CHAR::wSCHOOLNUM <= m_wSchool )	m_wSchool = 0;

	GLCONST_CHAR::nidSTARTMAP[m_wSchool];
	GLCONST_CHAR::dwSTARTGATE[m_wSchool];
}

const SCHARSTATS& GLCHARLOGIC::GETSTATS_ADD () const
{
	static SCHARSTATS sSTATS_SUM;
	sSTATS_SUM = m_sStats + m_sSUMITEM.sStats;
	
	return sSTATS_SUM;
}

const SCHARSTATS& GLCHARLOGIC::GETSTATS_ITEM () const
{
	return m_sSUMITEM.sStats;
}

void GLCHARLOGIC::OptionMoveUp()
{
	m_fOPTION_MOVE += 0.1f;

	if( m_fOPTION_MOVE >= 3.0f )
		m_fOPTION_MOVE = 3.0f;
}

void GLCHARLOGIC::OptionMoveDown()
{
	m_fOPTION_MOVE -= 0.1f;

	if( m_fOPTION_MOVE <= 0.0f )
		m_fOPTION_MOVE = 0.0f;
}

void GLCHARLOGIC::SUM_ADDITION ( float fCONFT_POINT_RATE )
{
	int i=0;
	int nLEVEL = GETLEVEL();												//	�ɸ����� ����.
	EMCHARINDEX emCI = GETCHARINDEX ();										//	�ɸ����� ���� �ε���.
	const GLCONST_CHARCLASS &cCHARCONST = GLCONST_CHAR::cCONSTCLASS[emCI];	//	�ɸ����� �����.
	int ZBLEVEL = (nLEVEL-1);												//	Zero base Level.

	//	Note : ��ú� ��ų ���갪 �ջ�.
	//
	SUM_PASSIVE ();

	//	Note : �����ۿ� ���� �ΰ� ȿ���� �ջ�.
	//
	SUM_ITEM ();

	//	Note : �⺻ ���� �� ���.
	//		STATS = �ʱ��ġ + ������ ���� �ڵ�������ġ + ĳ���� ��������Ʈ�� �к��� ��ġ + ������ �ɼ�.
	//
	m_sSUMSTATS.RESET();
	m_sSUMSTATS = cCHARCONST.sBEGIN_STATS + cCHARCONST.sLVLUP_STATS*ZBLEVEL + m_sStats + m_sSUMITEM.sStats;
	
	//	Note : ���, ��� ���.
	m_wSUM_AP = WORD ( ( cCHARCONST.wBEGIN_AP + cCHARCONST.fLVLUP_AP*ZBLEVEL ) * cCHARCONST.fCONV_AP );
	m_wSUM_DP = WORD ( ( cCHARCONST.wBEGIN_DP + cCHARCONST.fLVLUP_DP*ZBLEVEL ) * cCHARCONST.fCONV_DP );
	
	//	Note : ����ġ, ���ġ.
	m_wPA = WORD ( ( cCHARCONST.wBEGIN_PA + cCHARCONST.fLVLUP_PA*ZBLEVEL ) * cCHARCONST.fCONV_PA );
	m_wSA = WORD ( ( cCHARCONST.wBEGIN_SA + cCHARCONST.fLVLUP_SA*ZBLEVEL ) * cCHARCONST.fCONV_SA );

	//	Note : ����ġ, ���ġ, ����ġ�� STATS �� �ݿ�.
	m_wPA += WORD ( m_sSUMSTATS.wPow * cCHARCONST.fPA_POW + m_sSUMSTATS.wDex * cCHARCONST.fPA_DEX );
	m_wSA += WORD ( m_sSUMSTATS.wPow * cCHARCONST.fSA_POW + m_sSUMSTATS.wDex * cCHARCONST.fSA_DEX );
	m_wMA = WORD ( m_sSUMSTATS.wDex * cCHARCONST.fMA_DEX + m_sSUMSTATS.wSpi * cCHARCONST.fMA_SPI + m_sSUMSTATS.wInt * cCHARCONST.fMA_INT );

	//	Note : ����ġ, ���ġ, ����ġ�� SUM_ITEM �� �ݿ�.
	int nSUM_PA = m_sSUMITEM.nPA + m_sSUM_PASSIVE.m_nPA;
	GLOGICEX::VARIATION ( m_wPA, USHRT_MAX, nSUM_PA );	// ��ȭ�Ǵ� ���� 0 <= x < 0xffff ������ ����.

	int nSUM_SA = m_sSUMITEM.nSA + m_sSUM_PASSIVE.m_nSA;
	GLOGICEX::VARIATION ( m_wSA, USHRT_MAX, nSUM_SA );	// ��ȭ�Ǵ� ���� 0 <= x < 0xffff ������ ����.

	int nSUM_MA = m_sSUMITEM.nMA + m_sSUM_PASSIVE.m_nMA;
	GLOGICEX::VARIATION ( m_wMA, USHRT_MAX, nSUM_MA );	// ��ȭ�Ǵ� ���� 0 <= x < 0xffff ������ ����.

	//	Note : �ջ� ��ġ ����.
	//
	m_wSUM_PA = m_wPA;
	m_wSUM_SA = m_wSA;
	m_wSUM_MA = m_wMA;

	//	Note : HP, MP, SP �ѷ� Ȯ��.
	//
	m_sHP.wMax = WORD ( ( m_sSUMSTATS.wStr*cCHARCONST.fHP_STR + m_sSUMITEM.nHP + m_sSUM_PASSIVE.m_nHP ) );
	m_sHP.wMax = WORD ( m_sHP.wMax * (1+m_sSUM_PASSIVE.m_fHP_RATE) * fCONFT_POINT_RATE );
	m_sHP.LIMIT();

	m_sMP.wMax = WORD ( ( m_sSUMSTATS.wSpi*cCHARCONST.fMP_SPI + m_sSUMITEM.nMP + m_sSUM_PASSIVE.m_nMP ) );
	m_sMP.wMax = WORD ( m_sMP.wMax * (1+m_sSUM_PASSIVE.m_fMP_RATE) * fCONFT_POINT_RATE );
	m_sMP.LIMIT();
	
	m_sSP.wMax = WORD ( ( m_sSUMSTATS.wSta*cCHARCONST.fSP_STA + m_sSUMITEM.nSP + m_sSUM_PASSIVE.m_nSP ) );
	m_sSP.wMax = WORD ( m_sSP.wMax * (1+m_sSUM_PASSIVE.m_fSP_RATE) * fCONFT_POINT_RATE );
	m_sSP.LIMIT();

	/*combatpoint logic, Juver, 2017/05/28 */
	m_sCombatPoint.wMax = GLCONST_CHAR::wCombatPoint_MAX;
	m_sCombatPoint.LIMIT();
	
	//	Note : ������, ȸ���� ���.
	m_nHIT = int ( m_sSUMSTATS.wDex*cCHARCONST.fHIT_DEX + m_sSUMITEM.nHitRate + m_sSUM_PASSIVE.m_nHIT );
	m_nAVOID = int ( m_sSUMSTATS.wDex*cCHARCONST.fAVOID_DEX + m_sSUMITEM.nAvoidRate + m_sSUM_PASSIVE.m_nAVOID );

	//part of add directval project
	//multiply here
	m_nHIT = int( m_nHIT * ( 100.0f + m_sSUMITEM.fRateHit_Per )*0.01f );
	m_nAVOID = int ( m_nAVOID * ( 100.0f + m_sSUMITEM.fRateAvoid_Per )*0.01f );
	m_nDEFENSE_BODY = int ( m_wSUM_DP + m_sSUMSTATS.wDex*cCHARCONST.fDEFENSE_DEX );

	//	Note : ���� ( DP + POW*��� + ITEM_DEF ) * �������� ����.
	m_nDEFENSE_SKILL = m_nDEFENSE = int ( m_nDEFENSE_BODY + m_sSUMITEM.nDefense + m_sSUM_PASSIVE.m_nDEFENSE );

	//	Note : ���ݷ�.
	m_gdDAMAGE.wMax = m_gdDAMAGE.wLow = int ( m_wSUM_AP + m_sSUM_PASSIVE.m_nDAMAGE );
	m_gdDAMAGE_SKILL = m_gdDAMAGE;

	m_gdDAMAGE_PHYSIC = m_gdDAMAGE_SKILL;
	m_gdDAMAGE_PHYSIC.wLow += m_sSUMITEM.gdDamage.wLow;
	m_gdDAMAGE_PHYSIC.wMax += m_sSUMITEM.gdDamage.wMax;

	if ( ISLONGRANGE_ARMS() )	m_gdDAMAGE_PHYSIC.VAR_PARAM ( m_wSUM_SA );	//	��Ÿ� ����.
	else						m_gdDAMAGE_PHYSIC.VAR_PARAM ( m_wSUM_PA );	//	���� ����.

	//	Note : ���׷�. ( ������ �����ƿ��� ������ ����. )
	m_sSUMRESIST.RESET();
	m_sSUMRESIST = m_sSUM_PASSIVE.m_sSUMRESIST + m_sSUMITEM.sResist;

	//	Note : HP, MP, SP ȸ���� ����.
	m_fINCR_HP = GLCONST_CHAR::fHP_INC_PER + m_sSUMITEM.fIncR_HP + m_sSUM_PASSIVE.m_fINCR_HP;
	m_fINCR_MP = GLCONST_CHAR::fMP_INC_PER + m_sSUMITEM.fIncR_MP + m_sSUM_PASSIVE.m_fINCR_MP;
	m_fINCR_SP = GLCONST_CHAR::fSP_INC_PER + m_sSUMITEM.fIncR_SP + m_sSUM_PASSIVE.m_fINCR_SP;

	//part of add directval project
	m_nHP_Potion_Rate = m_sSUMITEM.nHP_Potion_Rate;
	m_nMP_Potion_Rate = m_sSUMITEM.nMP_Potion_Rate;
	m_nSP_Potion_Rate = m_sSUMITEM.nSP_Potion_Rate;

	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	if ( m_pITEMS[emRHand] )
	{
		m_emITEM_ATT = m_pITEMS[emRHand]->sSuitOp.emAttack;
		m_wATTRANGE = m_pITEMS[emRHand]->sSuitOp.wAttRange;
	}
	else
	{
		m_emITEM_ATT = ITEMATT_NOTHING;
		m_wATTRANGE = GLCONST_CHAR::wMAXATRANGE_SHORT;
	}

	//	Note : ���ڶ�� ��ġ�� �ջ�. ( STATS, LEVEL )
	//
	m_wACCEPTP = 0;
	m_wACCEPTP += CALC_ACCEPTP ( GET_SLOT_NID(emLHand) );
	m_wACCEPTP += CALC_ACCEPTP ( GET_SLOT_NID(emRHand) );

	//	Note : "SP�Һ�� ���Ǵ� �䱸��ġ" + "������ ���� �Һ� SP �ջ�"
	//
	m_wSUM_DisSP = m_wACCEPTP;

	SITEM* pRHAND = GET_SLOT_ITEMDATA ( emRHand );
	SITEM* pLHAND = GET_SLOT_ITEMDATA ( emLHand );

	if ( pRHAND )	m_wSUM_DisSP += pRHAND->sSuitOp.wReqSP;
	if ( pLHAND )	m_wSUM_DisSP += pLHAND->sSuitOp.wReqSP;

	m_sHP.LIMIT ();
	m_sMP.LIMIT ();
	m_sSP.LIMIT ();
}

void GLCHARLOGIC::SUM_ITEM ()
{
	m_sSUMITEM.RESET();

	for ( int i=0; i<SLOT_NSIZE_S_2; i++ )
	{
		EMSLOT emSLOT = static_cast<EMSLOT>(i);
		if ( !VALID_SLOT_ITEM(emSLOT) )					continue;

		const SITEMCUSTOM& sItemCustom = GET_SLOT_ITEM ( emSLOT );

		SITEM &sItem = *m_pITEMS[emSLOT];

		//	������ ���� ���ݿ��� ������ ���� ����.
		if ( sItem.sBasicOp.emItemType==ITEM_CHARM )	continue;

		for ( DWORD addon=0; addon<ITEM::SSUIT::ADDON_SIZE; ++addon )
		{
			switch ( sItem.sSuitOp.sADDON[addon].emTYPE )
			{
			case EMADD_NONE:
				break;
			case EMADD_HITRATE:
				m_sSUMITEM.nHitRate		+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;
			case EMADD_AVOIDRATE:
				m_sSUMITEM.nAvoidRate	+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;

			case EMADD_DAMAGE:
				m_sSUMITEM.gdDamage.wLow+= sItem.sSuitOp.sADDON[addon].nVALUE;
				m_sSUMITEM.gdDamage.wMax+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;

			case EMADD_DEFENSE:
				m_sSUMITEM.nDefense		+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;

			case EMADD_HP:
				m_sSUMITEM.nHP			+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;
			case EMADD_MP:
				m_sSUMITEM.nMP			+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;
			case EMADD_SP:
				m_sSUMITEM.nSP			+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;

			case EMADD_STATS_POW:
				m_sSUMITEM.sStats.wPow	+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;
			case EMADD_STATS_STR:
				m_sSUMITEM.sStats.wStr	+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;
			case EMADD_STATS_SPI:
				m_sSUMITEM.sStats.wSpi	+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;
			case EMADD_STATS_DEX:
				m_sSUMITEM.sStats.wDex	+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;
			case EMADD_STATS_INT:
				m_sSUMITEM.sStats.wInt	+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;
			case EMADD_STATS_STA:
				m_sSUMITEM.sStats.wSta	+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;

			case EMADD_PA:
				m_sSUMITEM.nPA	+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;
			case EMADD_SA:
				m_sSUMITEM.nSA	+= sItem.sSuitOp.sADDON[addon].nVALUE;
				break;
			//case EMADD_MA:	//	�� �ɼ��� GETMaDAMAGE() ���� ������ ���ѵ� ó��.
			//	m_sSUMITEM.nMA	+= sItem.sSuitOp.sADDON[addon].nVALUE;
			//	break;
			};
		}

		m_sSUMITEM.nHP += (int) sItemCustom.GETOptVALUE(EMR_OPT_HP);
		m_sSUMITEM.nMP += (int) sItemCustom.GETOptVALUE(EMR_OPT_MP);
		m_sSUMITEM.nSP += (int) sItemCustom.GETOptVALUE(EMR_OPT_SP);

		//	Note : ��ȭ�� ȿ��.
		switch ( sItem.sSuitOp.sVARIATE.emTYPE )
		{
		case EMVAR_HP:
			m_sSUMITEM.fIncR_HP += sItem.sSuitOp.sVARIATE.fVariate;
			break;
		case EMVAR_MP:
			m_sSUMITEM.fIncR_MP += sItem.sSuitOp.sVARIATE.fVariate;
			break;
		case EMVAR_SP:
			m_sSUMITEM.fIncR_SP += sItem.sSuitOp.sVARIATE.fVariate;
			break;

		case EMVAR_AP:
			m_sSUMITEM.fIncR_HP += sItem.sSuitOp.sVARIATE.fVariate;
			m_sSUMITEM.fIncR_MP += sItem.sSuitOp.sVARIATE.fVariate;
			m_sSUMITEM.fIncR_SP += sItem.sSuitOp.sVARIATE.fVariate;
			break;
		case EMVAR_MOVE_SPEED:
			// ���߿� �ջ����� ����
			if ( emSLOT != SLOT_VEHICLE ) m_sSUMITEM.fIncR_MoveSpeed += sItemCustom.GETMOVESPEEDR();
			else if ( m_bVehicle ) m_sSUMITEM.fIncR_MoveSpeed += m_fVehicleSpeedRate + sItemCustom.GETMOVESPEEDR();;
			break;
		case EMVAR_ATTACK_SPEED:
			m_sSUMITEM.fIncR_AtkSpeed	+= sItem.sSuitOp.sVARIATE.fVariate;	
			break;
		case EMVAR_CRITICAL_RATE:
			m_sSUMITEM.fIncR_Critical += sItem.sSuitOp.sVARIATE.fVariate;
			break;
		case EMVAR_CRUSHING_BLOW:
			m_sSUMITEM.fIncR_CrushingBlow += sItem.sSuitOp.sVARIATE.fVariate;
			break;
		};

		m_sSUMITEM.fIncR_HP += sItemCustom.GETOptVALUE(EMR_OPT_HP_INC) + sItemCustom.GETOptVALUE(EMR_OPT_HMS_INC);
		m_sSUMITEM.fIncR_MP += sItemCustom.GETOptVALUE(EMR_OPT_MP_INC) + sItemCustom.GETOptVALUE(EMR_OPT_HMS_INC);
		m_sSUMITEM.fIncR_SP += sItemCustom.GETOptVALUE(EMR_OPT_SP_INC) + sItemCustom.GETOptVALUE(EMR_OPT_HMS_INC);

		//	Note : ��ȭ�� ȿ��.
		switch ( sItem.sSuitOp.sVOLUME.emTYPE )
		{
		case EMVAR_HP:
			m_sSUMITEM.fInc_HP += sItem.sSuitOp.sVOLUME.fVolume;
			break;
		case EMVAR_MP:
			m_sSUMITEM.fInc_MP += sItem.sSuitOp.sVOLUME.fVolume;
			break;
		case EMVAR_SP:
			m_sSUMITEM.fInc_SP += sItem.sSuitOp.sVOLUME.fVolume;
			break;

		case EMVAR_AP:
			m_sSUMITEM.fInc_HP += sItem.sSuitOp.sVOLUME.fVolume;
			m_sSUMITEM.fInc_MP += sItem.sSuitOp.sVOLUME.fVolume;
			m_sSUMITEM.fInc_SP += sItem.sSuitOp.sVOLUME.fVolume;
			break;
		case EMVAR_MOVE_SPEED:
			// ���߿� �ջ����� ����
			if ( emSLOT != SLOT_VEHICLE ) m_sSUMITEM.fInc_MoveSpeed += sItemCustom.GETMOVESPEED();
			else if	( m_bVehicle ) m_sSUMITEM.fInc_MoveSpeed += m_fVehicleSpeedVol + sItemCustom.GETMOVESPEED();
			break;
		case EMVAR_ATTACK_SPEED:
			m_sSUMITEM.fInc_AtkSpeed	+= sItem.sSuitOp.sVOLUME.fVolume;
			break;
		case EMVAR_CRITICAL_RATE:
			m_sSUMITEM.fInc_Critical += sItem.sSuitOp.sVOLUME.fVolume;
			break;
		case EMVAR_CRUSHING_BLOW:
			m_sSUMITEM.fInc_CrushingBlow += sItem.sSuitOp.sVOLUME.fVolume;
			break;
		};

		// �̵��ӵ� �����ɼ� ����( ������ ������ ���� m_fVehicleSpeedVol ) 
//		if ( emSLOT != SLOT_VEHICLE ) m_sSUMITEM.fInc_MoveSpeed += sItemCustom.GETOptVALUE( EMR_OPT_MOVE_SPEED );
//		else if ( m_bVehicle ) m_sSUMITEM.fInc_MoveSpeed += sItemCustom.GETOptVALUE( EMR_OPT_MOVE_SPEED );

		//	Note : ������ �⺻ �ɷ� ADD ��ġ.
		//

		// Add latest Random Values
		m_sSUMITEM.nPA += sItemCustom.GETADDPA(); // add melee
		m_sSUMITEM.nSA += sItemCustom.GETADDSA(); // add missile
		m_sSUMITEM.nMA += sItemCustom.GETADDENERGY(); // add energy

		m_sSUMITEM.gdDamage			+= sItemCustom.GETDAMAGE();
		m_sSUMITEM.nDefense			+= sItemCustom.GETDEFENSE();

		m_sSUMITEM.nAvoidRate		+= sItemCustom.GETAVOIDRATE();
		m_sSUMITEM.nHitRate			+= sItemCustom.GETHITRATE();


		//	 Note : ������ ���� [+] ��ġ �ջ�.
		//
		m_sSUMITEM.sResist.nElectric	+= sItemCustom.GETRESIST_ELEC();
		m_sSUMITEM.sResist.nFire		+= sItemCustom.GETRESIST_FIRE();
		m_sSUMITEM.sResist.nIce			+= sItemCustom.GETRESIST_ICE();
		m_sSUMITEM.sResist.nPoison		+= sItemCustom.GETRESIST_POISON();
		m_sSUMITEM.sResist.nSpirit		+= sItemCustom.GETRESIST_SPIRIT();

		m_sSUMITEM.sStats.wPow += sItemCustom.GET_STAT_POW();
		m_sSUMITEM.sStats.wSpi += sItemCustom.GET_STAT_INT();
		m_sSUMITEM.sStats.wDex += sItemCustom.GET_STAT_DEX();
		m_sSUMITEM.sStats.wSta += sItemCustom.GET_STAT_STM();
		m_sSUMITEM.sStats.wStr += sItemCustom.GET_STAT_VIT();
		m_sSUMITEM.nHP_Potion_Rate += sItemCustom.GET_HP_POTION(); //add directval hppotion
		m_sSUMITEM.nMP_Potion_Rate += sItemCustom.GET_MP_POTION(); //add directval mppotion
		m_sSUMITEM.nSP_Potion_Rate += sItemCustom.GET_SP_POTION(); //add directval sppotion

		//this is part of add directval project
		//this will work as multiplier for overall hitrate
		m_sSUMITEM.fRateAvoid_Per += sItemCustom.GETAVOIDRATE_PER();
		m_sSUMITEM.fRateHit_Per += sItemCustom.GETHITRATE_PER();

		//	Note : ���ġ�� ���ݷ� ����.
		//
		m_sSUMITEM.nMA	+= sItemCustom.GETMaDAMAGE();



		/*costume combine stats, Juver, 2017/09/01 */
		SITEM*	pItemDisguiseCombine = GLItemMan::GetInstance().GetItem( sItemCustom.nidDISGUISE );
		if ( pItemDisguiseCombine && pItemDisguiseCombine->sBasicOp.IsDISGUISE() )
		{
			for ( DWORD addon=0; addon<ITEM::SSUIT::ADDON_SIZE; ++addon )
			{
				switch ( pItemDisguiseCombine->sSuitOp.sADDON[addon].emTYPE )
				{
				case EMADD_NONE:
					break;
				case EMADD_HITRATE:
					m_sSUMITEM.nHitRate		+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_AVOIDRATE:
					m_sSUMITEM.nAvoidRate	+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_DAMAGE:
					m_sSUMITEM.gdDamage.wLow+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					m_sSUMITEM.gdDamage.wMax+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_DEFENSE:
					m_sSUMITEM.nDefense		+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_HP:
					m_sSUMITEM.nHP			+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_MP:
					m_sSUMITEM.nMP			+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_SP:
					m_sSUMITEM.nSP			+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_STATS_POW:
					m_sSUMITEM.sStats.wPow	+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_STATS_STR:
					m_sSUMITEM.sStats.wStr	+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_STATS_SPI:
					m_sSUMITEM.sStats.wSpi	+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_STATS_DEX:
					m_sSUMITEM.sStats.wDex	+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_STATS_INT:
					m_sSUMITEM.sStats.wInt	+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_STATS_STA:
					m_sSUMITEM.sStats.wSta	+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_PA:
					m_sSUMITEM.nPA	+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
				case EMADD_SA:
					m_sSUMITEM.nSA	+= pItemDisguiseCombine->sSuitOp.sADDON[addon].nVALUE;
					break;
					//case EMADD_MA:
					//	m_sSUMITEM.nMA	+= pCostume->sSuitOp.sADDON[addon].nVALUE;
					//	break;
				};
			}

			switch ( pItemDisguiseCombine->sSuitOp.sVARIATE.emTYPE )
			{
			case EMVAR_HP:
				m_sSUMITEM.fIncR_HP += pItemDisguiseCombine->sSuitOp.sVARIATE.fVariate;
				break;
			case EMVAR_MP:
				m_sSUMITEM.fIncR_MP += pItemDisguiseCombine->sSuitOp.sVARIATE.fVariate;
				break;
			case EMVAR_SP:
				m_sSUMITEM.fIncR_SP += pItemDisguiseCombine->sSuitOp.sVARIATE.fVariate;
				break;
			case EMVAR_AP:
				m_sSUMITEM.fIncR_HP += pItemDisguiseCombine->sSuitOp.sVARIATE.fVariate;
				m_sSUMITEM.fIncR_MP += pItemDisguiseCombine->sSuitOp.sVARIATE.fVariate;
				m_sSUMITEM.fIncR_SP += pItemDisguiseCombine->sSuitOp.sVARIATE.fVariate;
				break;
			case EMVAR_MOVE_SPEED:
				m_sSUMITEM.fIncR_MoveSpeed += pItemDisguiseCombine->sSuitOp.sVARIATE.fVariate;
				break;
			case EMVAR_ATTACK_SPEED:
				m_sSUMITEM.fIncR_AtkSpeed	+= pItemDisguiseCombine->sSuitOp.sVARIATE.fVariate;	
				break;
			case EMVAR_CRITICAL_RATE:
				m_sSUMITEM.fIncR_Critical += pItemDisguiseCombine->sSuitOp.sVARIATE.fVariate;
				break;
			case EMVAR_CRUSHING_BLOW:
				m_sSUMITEM.fIncR_CrushingBlow += pItemDisguiseCombine->sSuitOp.sVARIATE.fVariate;
				break;
			};

			switch ( pItemDisguiseCombine->sSuitOp.sVOLUME.emTYPE )
			{
			case EMVAR_HP:
				m_sSUMITEM.fInc_HP += pItemDisguiseCombine->sSuitOp.sVOLUME.fVolume;
				break;
			case EMVAR_MP:
				m_sSUMITEM.fInc_MP += pItemDisguiseCombine->sSuitOp.sVOLUME.fVolume;
				break;
			case EMVAR_SP:
				m_sSUMITEM.fInc_SP += pItemDisguiseCombine->sSuitOp.sVOLUME.fVolume;
				break;
			case EMVAR_AP:
				m_sSUMITEM.fInc_HP += pItemDisguiseCombine->sSuitOp.sVOLUME.fVolume;
				m_sSUMITEM.fInc_MP += pItemDisguiseCombine->sSuitOp.sVOLUME.fVolume;
				m_sSUMITEM.fInc_SP += pItemDisguiseCombine->sSuitOp.sVOLUME.fVolume;
				break;
			case EMVAR_MOVE_SPEED:
				m_sSUMITEM.fInc_MoveSpeed += pItemDisguiseCombine->sSuitOp.sVOLUME.fVolume;
				break;
			case EMVAR_ATTACK_SPEED:
				m_sSUMITEM.fInc_AtkSpeed	+= pItemDisguiseCombine->sSuitOp.sVOLUME.fVolume;
				break;
			case EMVAR_CRITICAL_RATE:
				m_sSUMITEM.fInc_Critical += pItemDisguiseCombine->sSuitOp.sVOLUME.fVolume;
				break;
			case EMVAR_CRUSHING_BLOW:
				m_sSUMITEM.fInc_CrushingBlow += pItemDisguiseCombine->sSuitOp.sVOLUME.fVolume;
				break;
			};
		}


	}
}

void GLCHARLOGIC::SUM_PASSIVE ()
{
	m_sSUM_PASSIVE = SPASSIVE_SKILL_DATA();
	
	if ( m_bVehicle ) return;

	if ( m_ExpSkills.empty() ) return;

	SKILL_MAP_ITER iter = m_ExpSkills.begin ();
	SKILL_MAP_ITER iter_end = m_ExpSkills.end ();
	for ( ; iter!=iter_end; ++iter )
	{
		const SCHARSKILL &sCharSkill = (*iter).second;
		PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sCharSkill.sNativeID.wMainID, sCharSkill.sNativeID.wSubID );
		if ( !pSkill )											continue;
		if ( pSkill->m_sBASIC.emROLE != SKILL::EMROLE_PASSIVE )	continue;

		//	Note : ������ ���� ���� �˻�.
		//
		bool bvalid_left(true), bvalid_right(true);
		GLITEM_ATT emITEM_LEFT = ITEMATT_NOTHING;
		GLITEM_ATT emITEM_RIGHT = ITEMATT_NOTHING;
		GLSKILL_ATT emSKILL_LEFT = pSkill->m_sBASIC.emUSE_LITEM;
		GLSKILL_ATT emSKILL_RIGHT = pSkill->m_sBASIC.emUSE_RITEM;

		EMSLOT emRHand = GetCurRHand();
		EMSLOT emLHand = GetCurLHand();

		if ( emSKILL_LEFT!=SKILLATT_NOCARE )
		{
			bvalid_left = false;
			SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
			if ( pItem )
			{
				emITEM_LEFT = pItem->sSuitOp.emAttack;
				bvalid_left = CHECHSKILL_ITEM(emSKILL_LEFT,emITEM_LEFT);
			}
		}

		if ( emSKILL_RIGHT!=SKILLATT_NOCARE )
		{
			bvalid_right = false;
			SITEM* pItem = GET_SLOT_ITEMDATA(emRHand);
			if ( pItem )
			{
				emITEM_RIGHT = pItem->sSuitOp.emAttack;
				bvalid_right = CHECHSKILL_ITEM(emSKILL_RIGHT,emITEM_RIGHT);
			}
		}

		if ( !(bvalid_left&&bvalid_right) )						continue;

		const SKILL::CDATA_LVL &sDATA_LVL = pSkill->m_sAPPLY.sDATA_LVL[sCharSkill.wLevel];
		
		

		switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
		{
		case SKILL::EMFOR_HP:
			m_sSUM_PASSIVE.m_nHP += WORD ( sDATA_LVL.fBASIC_VAR );
			break;

		case SKILL::EMFOR_MP:
			m_sSUM_PASSIVE.m_nMP += WORD ( sDATA_LVL.fBASIC_VAR );
			break;

		case SKILL::EMFOR_SP:
			m_sSUM_PASSIVE.m_nSP += WORD ( sDATA_LVL.fBASIC_VAR );
			break;

		case SKILL::EMFOR_VARHP:
			m_sSUM_PASSIVE.m_fINCR_HP += sDATA_LVL.fBASIC_VAR;
			break;

		case SKILL::EMFOR_VARMP:
			m_sSUM_PASSIVE.m_fINCR_MP += sDATA_LVL.fBASIC_VAR;
			break;

		case SKILL::EMFOR_VARSP:
			m_sSUM_PASSIVE.m_fINCR_SP += sDATA_LVL.fBASIC_VAR;
			break;

		case SKILL::EMFOR_DEFENSE:
			m_sSUM_PASSIVE.m_nDEFENSE += int ( sDATA_LVL.fBASIC_VAR );
			break;

		case SKILL::EMFOR_HITRATE:
			m_sSUM_PASSIVE.m_nHIT += int ( sDATA_LVL.fBASIC_VAR );
			break;

		case SKILL::EMFOR_AVOIDRATE:
			m_sSUM_PASSIVE.m_nAVOID += int ( sDATA_LVL.fBASIC_VAR );
			break;

		case SKILL::EMFOR_VARAP:
			m_sSUM_PASSIVE.m_fINCR_HP += sDATA_LVL.fBASIC_VAR;
			m_sSUM_PASSIVE.m_fINCR_MP += sDATA_LVL.fBASIC_VAR;
			m_sSUM_PASSIVE.m_fINCR_SP += sDATA_LVL.fBASIC_VAR;
			break;

		case SKILL::EMFOR_VARDAMAGE:
			m_sSUM_PASSIVE.m_nDAMAGE += int(sDATA_LVL.fBASIC_VAR);
			break;

		case SKILL::EMFOR_VARDEFENSE:
			m_sSUM_PASSIVE.m_nDEFENSE += int(sDATA_LVL.fBASIC_VAR);
			break;

		case SKILL::EMFOR_PA:
			m_sSUM_PASSIVE.m_nPA += int(sDATA_LVL.fBASIC_VAR);
			break;

		case SKILL::EMFOR_SA:
			m_sSUM_PASSIVE.m_nSA += int(sDATA_LVL.fBASIC_VAR);
			break;

		case SKILL::EMFOR_MA:
			m_sSUM_PASSIVE.m_nMA += int(sDATA_LVL.fBASIC_VAR);
			break;

		case SKILL::EMFOR_HP_RATE:
			m_sSUM_PASSIVE.m_fHP_RATE += sDATA_LVL.fBASIC_VAR;
			break;

		case SKILL::EMFOR_MP_RATE:
			m_sSUM_PASSIVE.m_fMP_RATE += sDATA_LVL.fBASIC_VAR;
			break;

		case SKILL::EMFOR_SP_RATE:
			m_sSUM_PASSIVE.m_fSP_RATE += sDATA_LVL.fBASIC_VAR;
			break;

		case SKILL::EMFOR_RESIST:
			m_sSUM_PASSIVE.m_sSUMRESIST += (int)(sDATA_LVL.fBASIC_VAR);
			break;

			/*summon time, Juver, 2017/12/12 */
		case SKILL::EMFOR_SUMMONTIME:
			m_sSUM_PASSIVE.m_nSummonTime += int ( sDATA_LVL.fBASIC_VAR );
			break;
		};

		for( int nImpact=0; nImpact<SKILL::MAX_IMPACT; ++nImpact )
		{
			const float &fADDON = pSkill->m_sAPPLY.sImpacts[nImpact].fADDON_VAR[sCharSkill.wLevel];

			switch ( pSkill->m_sAPPLY.sImpacts[nImpact].emADDON )
			{
			case EMIMPACTA_HITRATE:
				m_sSUM_PASSIVE.m_nHIT += int ( fADDON );
				break;
			case EMIMPACTA_AVOIDRATE:
				m_sSUM_PASSIVE.m_nAVOID += int ( fADDON );
				break;

			case EMIMPACTA_DAMAGE:
				m_sSUM_PASSIVE.m_nDAMAGE += int ( fADDON );
				break;

			case EMIMPACTA_DEFENSE:
				m_sSUM_PASSIVE.m_nDEFENSE += int ( fADDON );
				break;

			case EMIMPACTA_VARHP:
				m_sSUM_PASSIVE.m_fINCR_HP += fADDON;
				break;
			case EMIMPACTA_VARMP:
				m_sSUM_PASSIVE.m_fINCR_MP += fADDON;
				break;
			case EMIMPACTA_VARSP:
				m_sSUM_PASSIVE.m_fINCR_SP += fADDON;
				break;

			case EMIMPACTA_VARAP:
				m_sSUM_PASSIVE.m_fINCR_HP += fADDON;
				m_sSUM_PASSIVE.m_fINCR_MP += fADDON;
				m_sSUM_PASSIVE.m_fINCR_SP += fADDON;
				break;

			case EMIMPACTA_DAMAGE_RATE:
				m_sSUM_PASSIVE.m_fDAMAGE_RATE += fADDON;
				break;

			case EMIMPACTA_DEFENSE_RATE:
				m_sSUM_PASSIVE.m_fDEFENSE_RATE += fADDON;
				break;

			case EMIMPACTA_PA:
				m_sSUM_PASSIVE.m_nPA += int(fADDON);
				break;

			case EMIMPACTA_SA:
				m_sSUM_PASSIVE.m_nSA += int(fADDON);
				break;

			case EMIMPACTA_MA:
				m_sSUM_PASSIVE.m_nMA += int(fADDON);
				break;

			case EMIMPACTA_HP_RATE:
				m_sSUM_PASSIVE.m_fHP_RATE += fADDON;
				break;

			case EMIMPACTA_MP_RATE:
				m_sSUM_PASSIVE.m_fMP_RATE += fADDON;
				break;

			case EMIMPACTA_SP_RATE:
				m_sSUM_PASSIVE.m_fSP_RATE += fADDON;
				break;

			case EMIMPACTA_RESIST:
				m_sSUM_PASSIVE.m_sSUMRESIST += (int)fADDON;
				break;


			};
		}
		

		for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
		{
			const SKILL::SSPEC &sSPEC = pSkill->m_sAPPLY.sSpecs[nSpec].sSPEC[sCharSkill.wLevel];

			switch ( pSkill->m_sAPPLY.sSpecs[nSpec].emSPEC )
			{
			case EMSPECA_PIERCE:
				m_sSUM_PASSIVE.m_nPIERCE += int ( sSPEC.fVAR1 );
				break;

			case EMSPECA_TARRANGE:
				m_sSUM_PASSIVE.m_fTARRANGE += sSPEC.fVAR1;
				break;

			case EMSPECA_MOVEVELO:
				m_sSUM_PASSIVE.m_fMOVEVELO += sSPEC.fVAR1;
				break;

			case EMSPECA_ATTACKVELO:
				//	���� �ӵ� ����̹Ƿ� ( ���� �ð��� -0.1 (-10%) ���� ��Ű�� ���ؼ��� ��ȣ ������ �Ͽ�����. )
				m_sSUM_PASSIVE.m_fATTVELO -= sSPEC.fVAR1;
				break;

			case EMSPECA_SKILLDELAY:
				m_sSUM_PASSIVE.m_fSKILLDELAY += sSPEC.fVAR1;
				break;

			case EMSPECA_PSY_DAMAGE_REDUCE:
				if ( m_sSUM_PASSIVE.m_sDamageSpec.m_fPsyDamageReduce < sSPEC.fVAR1 )
					m_sSUM_PASSIVE.m_sDamageSpec.m_fPsyDamageReduce = sSPEC.fVAR1;
				break;

			case EMSPECA_MAGIC_DAMAGE_REDUCE:
				if ( m_sSUM_PASSIVE.m_sDamageSpec.m_fMagicDamageReduce < sSPEC.fVAR1 )
					m_sSUM_PASSIVE.m_sDamageSpec.m_fMagicDamageReduce = sSPEC.fVAR1;
				break;

			case EMSPECA_PSY_DAMAGE_REFLECTION:
				if ( m_sSUM_PASSIVE.m_sDamageSpec.m_fPsyDamageReflection < sSPEC.fVAR1 )
				{
					m_sSUM_PASSIVE.m_sDamageSpec.m_fPsyDamageReflection = sSPEC.fVAR1;
					m_sSUM_PASSIVE.m_sDamageSpec.m_fPsyDamageReflectionRate = sSPEC.fVAR2;
				}
				break;

			case EMSPECA_MAGIC_DAMAGE_REFLECTION:
				if ( m_sSUM_PASSIVE.m_sDamageSpec.m_fMagicDamageReflection < sSPEC.fVAR1 )
				{
					m_sSUM_PASSIVE.m_sDamageSpec.m_fMagicDamageReflection = sSPEC.fVAR1;
					m_sSUM_PASSIVE.m_sDamageSpec.m_fMagicDamageReflectionRate = sSPEC.fVAR2;
				}
				break;
			case EMSPECA_DEFENSE_SKILL_ACTIVE:
				{				
				}
				break;

				/*skill range spec logic, Juver, 2017/06/06 */
			case EMSPECA_CHANGE_ATTACK_RANGE:	
				{
					m_sSUM_PASSIVE.m_fSUM_SKILL_ATTACKRANGE += sSPEC.fVAR1;	
				}break;

			case EMSPECA_CHANGE_APPLY_RANGE:	
				{
					m_sSUM_PASSIVE.m_fSUM_SKILL_APPLYRANGE += sSPEC.fVAR1;	
				}break;
			};
		}

		
	}
}

void GLCHARLOGIC::INIT_RECOVER ( int nRECOVER )
{
	m_sHP.CHECKMIN ( (m_sHP.wMax*nRECOVER)/100 + 1 );
	m_sMP.CHECKMIN ( (m_sMP.wMax*nRECOVER)/100 + 1 );
	m_sSP.CHECKMIN ( (m_sSP.wMax*nRECOVER)/100 + 1 );

	for ( int i=0; i<EMBLOW_MULTI; ++i )		DISABLEBLOW ( i );
	for ( int i=0; i<SKILLFACT_SIZE; ++i )		DISABLESKEFF ( i );

	/*dual pet skill, Juver, 2017/12/27 */
	m_sPETSKILLFACT_A.RESET ();
	m_sPETSKILLFACT_B.RESET ();

	DISABLEALLLANDEFF();
}

void GLCHARLOGIC::RELEASE_SLOT_ITEM ( EMSLOT _slot )
{
	m_PutOnItems[_slot] = SITEMCUSTOM ( SNATIVEID(false) );
	
	//	Note : ������ ������ �ʱ�ȭ.
	//
	m_pITEMS[_slot] = NULL;
}

void GLCHARLOGIC::SLOT_ITEM ( const SITEMCUSTOM &sItemCustom, EMSLOT _slot )
{
	m_PutOnItems[_slot] = sItemCustom;

	//	Note : ������ ������ �ʱ�ȭ.
	//
	if ( VALID_SLOT_ITEM(_slot) )
		m_pITEMS[_slot] =  GLItemMan::GetInstance().GetItem ( m_PutOnItems[_slot].sNativeID );
}

void GLCHARLOGIC::HOLD_ITEM ( const SITEMCUSTOM &sItemCustom )
{
	m_PutOnItems[SLOT_HOLD] = sItemCustom;

	//	Note : ������ ������ �ʱ�ȭ.
	//
	if ( VALID_SLOT_ITEM(SLOT_HOLD) )
		m_pITEMS[SLOT_HOLD] =  GLItemMan::GetInstance().GetItem ( m_PutOnItems[SLOT_HOLD].sNativeID );
}

void GLCHARLOGIC::HOLD_ARRAY( const SITEMCUSTOM &sItemCustom, int nIndex )
{
	m_pHoldArray[nIndex] = sItemCustom;
}

void GLCHARLOGIC::RELEASE_HOLDARRAY_ITEM (int nIndex)
{
	m_pHoldArray[nIndex] = SITEMCUSTOM (SNATIVEID(false));
}

void GLCHARLOGIC::RELEASE_HOLD_ITEM ()
{
	m_PutOnItems[SLOT_HOLD] = SITEMCUSTOM ( SNATIVEID(false) );

	//	Note : ������ ������ �ʱ�ȭ.
	//
	m_pITEMS[SLOT_HOLD] = NULL;
}


//	�޼�, ������ �������߿��� 'BLOW' �Ӽ��� �ִ� �������� ��ȯ.
SITEM* GLCHARLOGIC::GET_ELMT_ITEM ()
{
	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	SITEM* pRHandItem = GET_SLOT_ITEMDATA(emRHand);
	SITEM* pLHandItem = GET_SLOT_ITEMDATA(emLHand);

	if ( pRHandItem && pRHandItem->sSuitOp.sBLOW.emTYPE!=EMBLOW_NONE )
	{
		return pRHandItem;
	}
	else if ( pLHandItem && pLHandItem->sSuitOp.sBLOW.emTYPE!=EMBLOW_NONE )
	{
		return pLHandItem;
	}

	return NULL;
}

BOOL GLCHARLOGIC::INIT_DATA ( BOOL bNEW, BOOL bReGen, float fCONFT_POINT_RATE, bool bInitNowExp )
{
	int i = 0;
	m_CHARINDEX = GETCHARINDEX ();
	const GLCONST_CHARCLASS &cCHARCONST = GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX];

	//	Note : ������ ������ ��������.
	//
	memset ( m_pITEMS, 0x00, sizeof(SITEM*)*SLOT_TSIZE );
	for ( int i=0; i<SLOT_TSIZE; i++ )
	{
		if ( m_PutOnItems[i].sNativeID != NATIVEID_NULL() )
		{
			m_pITEMS[i] = GLItemMan::GetInstance().GetItem ( m_PutOnItems[i].sNativeID );

			//	������ ���̺��� ���� �������� ����.
			if ( !m_pITEMS[i] )		RELEASE_SLOT_ITEM ( EMSLOT(i) );
		}
	}

	//	Note : ADD �� ���.
	SUM_ADDITION( fCONFT_POINT_RATE );

	if ( bNEW )
	{
		m_bServerStorage = TRUE;

		//m_wStatsPoint = GLCONST_CHAR::wLVL_STATS_P;

		m_sHP.TO_FULL ();
		m_sMP.TO_FULL ();
		m_sSP.TO_FULL ();
	}
	else if ( bReGen )
	{
		INIT_RECOVER ();
	}

	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	m_emANISUBTYPE = CHECK_ANISUB ( m_pITEMS[emRHand], m_pITEMS[emLHand]  );

	GLITEM_ATT emRHAtt = ITEMATT_NOTHING;
	GLITEM_ATT emLHAtt = ITEMATT_NOTHING;

	if ( m_pITEMS[emRHand] )		emRHAtt = m_pITEMS[emRHand]->sSuitOp.emAttack;
	if ( m_pITEMS[emLHand] )		emLHAtt = m_pITEMS[emLHand]->sSuitOp.emAttack;

	if ( emRHAtt==ITEMATT_NOTHING )		m_wATTRANGE = GLCONST_CHAR::wMAXATRANGE_SHORT;
	else								m_wATTRANGE = m_pITEMS[emRHand]->sSuitOp.wAttRange;

	//	���� �������� ���������� �ִ� ����ġ ���.
	m_sExperience.lnMax = GET_LEVELUP_EXP();
	if( bInitNowExp ) m_sExperience.LIMIT();
	
	return TRUE;
}

BOOL GLCHARLOGIC::CHECKHIT ( const STARGETID &cTargetID, const GLLandMan* pLandMan, const BOOL bLowSP )
{
	int nAVOID = 0;
	EMBRIGHT emBright;

	if ( cTargetID.dwID == EMTARGET_NULL )	return FALSE;

	GLACTOR *pActor = GLGaeaServer::GetInstance().GetTarget ( pLandMan, cTargetID );
	if ( !pActor )						return FALSE;
	
	nAVOID = pActor->GetAvoid ();
	emBright = pActor->GetBright ();

	EM_BRIGHT_FB bFB = GLOGICEX::GLSPACEGAP ( GETBRIGHT(), emBright, pLandMan->GETBRIGHT() );	
	int nHitRate = GLOGICEX::GLHITRATE ( GETHIT(), nAVOID, bFB );
	if ( bLowSP )		nHitRate = int(nHitRate*(1.0f-GLCONST_CHAR::fLOWSP_HIT_DROP));

	return ( nHitRate >= (RANDOM_POS*100) );
}

DWORD GLCHARLOGIC::CALCDAMAGE(
	int &rResultDAMAGE,
	const DWORD dwGaeaID,
	const STARGETID &cTargetID,
	const GLLandMan* pLandMan,
	const GLSKILL* pSkill,
	const DWORD dwskill_lev,
	const DWORD dwWeatherFlag,
	const int dwDivCount)
{
#if defined(KRT_PARAM) || defined(KR_PARAM) || defined(CH_PARAM) || defined(TH_PARAM) || defined(ID_PARAM) || defined(JP_PARAM) || defined(MY_PARAM) || defined(MYE_PARAM) || defined(PH_PARAM) || defined ( GS_PARAM ) || defined(_RELEASED)
	return CALCDAMAGE_20060328(
		rResultDAMAGE,
		dwGaeaID,
		cTargetID,
		pLandMan,
		pSkill,
		dwskill_lev,
		dwWeatherFlag,
		dwDivCount);
#else
	return CALCDAMAGE_2004(
		rResultDAMAGE,
		dwGaeaID,
		cTargetID,
		pLandMan,
		pSkill,
		dwskill_lev,
		dwWeatherFlag,
		dwDivCount);
#endif
}

// 2006-03-28 Jgkim ��ȹ�� ��û���� ������ ���� ������
DWORD GLCHARLOGIC::CALCDAMAGE_20060328(
	int& rResultDAMAGE,
	const DWORD dwGaeaID,
	const STARGETID &cTargetID,
	const GLLandMan* pLandMan,
	const GLSKILL* pSkill,
	const DWORD dwskill_lev,
	const DWORD dwWeatherFlag,
	const int dwDivCount)
{
	GLACTOR *pActor = GLGaeaServer::GetInstance().GetTarget ( pLandMan, cTargetID );
	if ( !pActor )	return DAMAGE_TYPE_NONE;

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
	const SRESIST &sRESIST = pActor->GETRESIST (); // ����� �� ���װ�

	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	WORD wGRADE = 0;
	const SITEMCUSTOM &sRHAND = GET_SLOT_ITEM(emRHand);
	if ( sRHAND.sNativeID != SNATIVEID(false) )
		wGRADE = sRHAND.GETGRADE(EMGRINDING_DAMAGE);

	int nCrushingBlow = (int)( m_sSUMITEM.fIncR_CrushingBlow * 100 );


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
	
	GLPADATA gdDamage = m_gdDAMAGE_SKILL;
	if ( pSkill )
	{
		const SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[dwskill_lev];
		

		//	Note : ��ų ���� ������ �Ҹ�Ǹ�, ������ ����ġ ����.
		//
		if ( sSKILL_DATA.wUSE_CHARMNUM > 0 )
		{
			SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
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
			gdDamage.wLow += m_sSUMITEM.gdDamage.wLow;
			gdDamage.wMax += m_sSUMITEM.gdDamage.wMax;
			
			gdDamage.VAR_PARAM ( m_wSUM_PA );
			// ���� ���ݽ� �Ӽ� ����ġ ���� ����
			// default.charset ���� ������
			// fRESIST_PHYSIC_G �� ��
			fRESIST_G = GLCONST_CHAR::fRESIST_PHYSIC_G;
			break;

			//	��Ÿ� ����.
		case SKILL::EMAPPLY_PHY_LONG:
			gdDamage.wLow += m_sSUMITEM.gdDamage.wLow;
			gdDamage.wMax += m_sSUMITEM.gdDamage.wMax;

			gdDamage.VAR_PARAM ( m_wSUM_SA );
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
			gdDamage.VAR_PARAM ( m_wSUM_MA );
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
			SITEM *pITEM = GET_ELMT_ITEM ();
			if ( pITEM )	emELMT = STATE_TO_ELEMENT(pITEM->sSuitOp.sBLOW.emTYPE);
		}
		else
		{
			emELMT = pSkill->m_sAPPLY.emELEMENT;
		}

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
	else
	{
		gdDamage.wLow += m_sSUMITEM.gdDamage.wLow;
		gdDamage.wMax += m_sSUMITEM.gdDamage.wMax;

		if ( ISLONGRANGE_ARMS() )	gdDamage.VAR_PARAM ( m_wSUM_SA );	//	��Ÿ� ����.
		else						gdDamage.VAR_PARAM ( m_wSUM_PA );	//	���� ����.
	}

	//	���ݷ�. ��ȭ�� �ݿ�.
	gdDamage.wLow  = WORD ( gdDamage.wLow  * m_fDamageRate );
	gdDamage.wHigh = WORD ( gdDamage.wHigh * m_fDamageRate );

	//	Note : �߰� ����ġ ����.
	int nExtFORCE = 0;
	int ndxLvl = nLEVEL - GETLEVEL();
	if ( ndxLvl > 0 )			nExtFORCE = int(RANDOM_POS*ndxLvl/10);

	//	Note : Critical �߻� Ȯ��.
	if ( ndxLvl > 5 )		ndxLvl = 5;
	if ( ndxLvl < -5 )		ndxLvl = -5;

	//	Note : Critical �߻� Ȯ��.
	int nPerHP = ((GETHP()*100)/GETMAXHP());
	if ( nPerHP <= 10 )	nPerHP = 10;
	int nPercentCri = 1000 / nPerHP - 10 + ndxLvl;
	nPercentCri += (int)( m_sSUMITEM.fIncR_Critical * 100 );

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
	int nDAMAGE_OLD = ( nDAMAGE_NOW + nExtFORCE );	//	����ġ �ջ�.

	//	���� ���� ����� ����.
	int nNetDAMAGE = int ( nDAMAGE_OLD*(1.0f-GLCONST_CHAR::fLOW_SEED_DAMAGE) - nDEFENSE );

	if ( nNetDAMAGE > 0 )	rResultDAMAGE = int ( nDAMAGE_OLD - nDEFENSE );
	else					rResultDAMAGE = int ( (nDAMAGE_OLD*GLCONST_CHAR::fLOW_SEED_DAMAGE)*RANDOM_POS );
	rResultDAMAGE = int(rResultDAMAGE*fSTATE_DAMAGE);

	//	�� ����� ������ �ݿ�.
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
	
	//	������ ����
	if ( fDamageReduce > 0.0f ) 
	{
		int nDamageReduce = (int) ( ( (rResultDAMAGE * fDamageReduce) * nLEVEL ) / GLCONST_CHAR::wMAX_LEVEL );
		rResultDAMAGE -= nDamageReduce;
		
		if ( bPsyDamage ) dwDamageFlag += DAMAGE_TYPE_PSY_REDUCE;
		else dwDamageFlag += DAMAGE_TYPE_PSY_REDUCE;
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
				STARGETID sActor(CROW_PC,dwGaeaID);
				pActor->DamageReflectionProc( nDamageReflection, sActor );
			}
		}
	}

	//	�ߵ� ��ų
	if ( sDefenseSkill.m_dwSkillID != NATIVEID_NULL() )
	{
		if ( sDefenseSkill.m_fRate > (RANDOM_POS*1) )
		{
			STARGETID sActor(CROW_PC,dwGaeaID);
			pActor->DefenseSkill( sDefenseSkill.m_dwSkillID, 
								  sDefenseSkill.m_wLevel, 
								  sActor );
		}
	}

	if ( rResultDAMAGE <= 1 )
	{
		bCritical = false;
		bCrushingBlow = false;
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

// ������ ������ ����
DWORD GLCHARLOGIC::CALCDAMAGE_2004(
	int& rResultDAMAGE,
	const DWORD dwGaeaID,
	const STARGETID &cTargetID,
	const GLLandMan* pLandMan,
	const GLSKILL* pSkill,
	const DWORD dwskill_lev,
	const DWORD dwWeatherFlag,
	const int dwDivCount)
{
	GLACTOR *pActor = GLGaeaServer::GetInstance().GetTarget ( pLandMan, cTargetID );
	if ( !pActor )	return DAMAGE_TYPE_NONE;

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

	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	WORD wGRADE = 0;
	const SITEMCUSTOM &sRHAND = GET_SLOT_ITEM(emRHand);
	if ( sRHAND.sNativeID != SNATIVEID(false) )
		wGRADE = sRHAND.GETGRADE(EMGRINDING_DAMAGE);

	int nCrushingBlow = (int)( m_sSUMITEM.fIncR_CrushingBlow * 100 );

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

	GLPADATA gdDamage = m_gdDAMAGE_SKILL;
	if ( pSkill )
	{
		const SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[dwskill_lev];
		

		//	Note : ��ų ���� ������ �Ҹ�Ǹ�, ������ ����ġ ����.
		//
		if ( sSKILL_DATA.wUSE_CHARMNUM > 0 )
		{
			SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
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
			gdDamage.wLow += m_sSUMITEM.gdDamage.wLow;
			gdDamage.wMax += m_sSUMITEM.gdDamage.wMax;
			
			gdDamage.VAR_PARAM ( m_wSUM_PA );
			fRESIST_G = GLCONST_CHAR::fRESIST_PHYSIC_G;
			break;

			//	��Ÿ� ����.
		case SKILL::EMAPPLY_PHY_LONG:
			gdDamage.wLow += m_sSUMITEM.gdDamage.wLow;
			gdDamage.wMax += m_sSUMITEM.gdDamage.wMax;

			gdDamage.VAR_PARAM ( m_wSUM_SA );
			fRESIST_G = GLCONST_CHAR::fRESIST_PHYSIC_G;
			
			fDamageReflection = 0.0f;
			fDamageReflectionRate = 0.0f;

			break;

			//	���� ����.
    	case SKILL::EMAPPLY_MAGIC:
			nDEFENSE = 0;						//	���� �����϶��� �Ϲ� ���� ���õ�.
			nDEFAULT_DEFENSE = 0;				//	���� �����϶��� �Ϲ� ���� ���õ�.
			nITEM_DEFENSE = 0;					//	���� �����϶��� �Ϲ� ���� ���õ�.
			gdDamage.VAR_PARAM ( m_wSUM_MA );
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
			SITEM *pITEM = GET_ELMT_ITEM ();
			if ( pITEM )	emELMT = STATE_TO_ELEMENT(pITEM->sSuitOp.sBLOW.emTYPE);
		}
		else
		{
			emELMT = pSkill->m_sAPPLY.emELEMENT;
		}

		short nRESIST = sRESIST.GetElement ( emELMT );
		if ( nRESIST>699 )	nRESIST = 699;
		float fPOWER = GLOGICEX::WEATHER_ELEMENT_POW ( emELMT, dwWeatherFlag, pLandMan->IsWeatherActive() );

		//	��ų�� ������ ��꿡 ������ �ִ� ���� �⺻���� Ư������ �˻�.
		float fSKILL_VAR = sSKILL_DATA.fBASIC_VAR;

		int nVAR = abs ( int(fSKILL_VAR*fPOWER) );
		nVAR = nVAR - (int) ( nVAR*nRESIST*0.01f*fRESIST_G );
		if ( nVAR<0 )	nVAR = 0;

		//	Note : ������� ����ȴ�, ����� �ݿ���.
		gdDamage.wLow += WORD ( nVAR + (gdDamage.wLow*wGRADE)/GLCONST_CHAR::fDAMAGE_GRADE_K );
		gdDamage.wHigh += WORD ( nVAR + (gdDamage.wHigh*wGRADE)/GLCONST_CHAR::fDAMAGE_GRADE_K );
	}
	else
	{
		gdDamage.wLow += m_sSUMITEM.gdDamage.wLow;
		gdDamage.wMax += m_sSUMITEM.gdDamage.wMax;

		if ( ISLONGRANGE_ARMS() )	gdDamage.VAR_PARAM ( m_wSUM_SA );	//	��Ÿ� ����.
		else						gdDamage.VAR_PARAM ( m_wSUM_PA );	//	���� ����.
	}

	//	���ݷ�. ��ȭ�� �ݿ�.
	gdDamage.wLow = WORD ( gdDamage.wLow * m_fDamageRate );
	gdDamage.wHigh = WORD ( gdDamage.wHigh * m_fDamageRate );

	//	Note : �߰� ����ġ ����.
	int nExtFORCE = 0;
	int ndxLvl = nLEVEL - GETLEVEL();
	if ( ndxLvl > 0 )			nExtFORCE = int(RANDOM_POS*ndxLvl*0.1f);

	//	Note : Critical �߻� Ȯ��.
	if ( ndxLvl > 5 )		ndxLvl = 5;
	if ( ndxLvl < -5 )		ndxLvl = -5;

	//	Note : Critical �߻� Ȯ��.
	int nPerHP = ((GETHP()*100)/GETMAXHP());
	if ( nPerHP <= 10 )	nPerHP = 10;
	int nPercentCri = 1000 / nPerHP - 10 + ndxLvl;
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
	int nDAMAGE_OLD = ( nDAMAGE_NOW + nExtFORCE );	//	����ġ �ջ�.

	//	���� ���� ����� ����.
	int nNetDAMAGE = int ( nDAMAGE_OLD*(1.0f-GLCONST_CHAR::fLOW_SEED_DAMAGE) - nDEFENSE );

	if ( nNetDAMAGE > 0 )	rResultDAMAGE = int ( nDAMAGE_OLD - nDEFENSE );
	else					rResultDAMAGE = int ( (nDAMAGE_OLD*GLCONST_CHAR::fLOW_SEED_DAMAGE)*RANDOM_POS );
	rResultDAMAGE = int(rResultDAMAGE*fSTATE_DAMAGE);

	//	�� ����� ������ �ݿ�.
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

	//	������ ����
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
				STARGETID sActor(CROW_PC,dwGaeaID);
				pActor->DamageReflectionProc( nDamageReflection, sActor );
			}
		}
	}

	//	�ߵ� ��ų
	if ( sDefenseSkill.m_dwSkillID != NATIVEID_NULL() )
	{
		if ( sDefenseSkill.m_fRate > (RANDOM_POS*1) )
		{
			STARGETID sActor(CROW_PC,dwGaeaID);
			pActor->DefenseSkill( sDefenseSkill.m_dwSkillID, 
								  sDefenseSkill.m_wLevel, 
								  sActor );
		}
	}

	if ( rResultDAMAGE <= 1 )
	{
		bCritical = false;
		bCrushingBlow = false;
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

WORD GLCHARLOGIC::RECEIVE_DAMAGE ( const WORD wDamage )
{
	WORD wOLD = m_sHP.wNow;
	m_sHP.DECREASE ( wDamage );

	return (wOLD>m_sHP.wNow) ? (wOLD-m_sHP.wNow) : 0;
}

/*qbox check, Juver, 2017/12/05 */
BOOL GLCHARLOGIC::RECEIVE_QITEMFACT ( const SNATIVEID &nidITEM, BOOL bMobGen )
{
	SITEM *pITEM = GLItemMan::GetInstance().GetItem ( nidITEM );
	if ( !pITEM )										return FALSE;
	if ( pITEM->sBasicOp.emItemType!=ITEM_QITEM )		return FALSE;
	if ( pITEM->sQuestionItem.emType==QUESTION_NONE )	return FALSE;

	ITEM::SQUESTIONITEM &sQUESTIONITEM = pITEM->sQuestionItem;

	switch ( sQUESTIONITEM.emType )
	{
	case QUESTION_SPEED_UP:
	case QUESTION_CRAZY:
	case QUESTION_ATTACK_UP:
	case QUESTION_EXP_UP:
	case QUESTION_LUCKY:
	case QUESTION_SPEED_UP_M:
	case QUESTION_MADNESS:
	case QUESTION_ATTACK_UP_M:
		m_sQITEMFACT.emType = sQUESTIONITEM.emType;
		m_sQITEMFACT.fTime = sQUESTIONITEM.fTime;
		m_sQITEMFACT.wParam1 = sQUESTIONITEM.wParam1;
		m_sQITEMFACT.wParam2 = sQUESTIONITEM.wParam2;
		m_sQITEMFACT.bMobGen = bMobGen; /*qbox check, Juver, 2017/12/05 */
		break;
	};

	return TRUE;
}

void GLCHARLOGIC::RECEIVE_EVENTFACT_BEGIN ( const EMGM_EVENT_TYPE emType, const WORD wValue )
{
	m_sEVENTFACT.SetEVENT( emType, wValue );
}

void GLCHARLOGIC::RECEIVE_EVENTFACT_END ( const EMGM_EVENT_TYPE emType )
{
	m_sEVENTFACT.ResetEVENT( emType );
}

//	Note : ? �������� ��ȿ �ð��� ���Ž�Ų��.
//			���� �ڵ�� ��������� false, �׿� ���׿� true
//
bool GLCHARLOGIC::UPDATE_QITEMFACT ( float fElapsedTime )
{
	if( !m_sQITEMFACT.IsACTIVE() )		return true;

	m_sQITEMFACT.fTime -= fElapsedTime;
	if ( m_sQITEMFACT.fTime <= 0 )
	{
		m_sQITEMFACT.RESET();
		return false;
	}

	return true;
}

void GLCHARLOGIC::UPDATE_MAX_POINT ( float fCONFT_POINT_RATE )
{
	EMCHARINDEX emCI = GETCHARINDEX ();										//	�ɸ����� ���� �ε���.
	const GLCONST_CHARCLASS &cCHARCONST = GLCONST_CHAR::cCONSTCLASS[emCI];	//	�ɸ����� �����.

	m_sHP.wMax = WORD ( m_sSUMSTATS.wStr*cCHARCONST.fHP_STR + m_sSUMITEM.nHP + m_sSUM_PASSIVE.m_nHP );
	m_sHP.wMax = WORD ( m_sHP.wMax * (1+m_sSUM_PASSIVE.m_fHP_RATE+m_fHP_RATE ) * fCONFT_POINT_RATE );
    m_sHP.LIMIT();

	m_sMP.wMax = WORD ( m_sSUMSTATS.wSpi*cCHARCONST.fMP_SPI + m_sSUMITEM.nMP + m_sSUM_PASSIVE.m_nMP );
	m_sMP.wMax = WORD ( m_sMP.wMax * (1+m_sSUM_PASSIVE.m_fMP_RATE+m_fMP_RATE ) * fCONFT_POINT_RATE );
	m_sMP.LIMIT();

	m_sSP.wMax = WORD ( m_sSUMSTATS.wSta*cCHARCONST.fSP_STA + m_sSUMITEM.nSP + m_sSUM_PASSIVE.m_nSP );
	m_sSP.wMax = WORD ( m_sSP.wMax * (1+m_sSUM_PASSIVE.m_fSP_RATE+m_fSP_RATE ) * fCONFT_POINT_RATE );
	m_sSP.LIMIT();
	
}

void GLCHARLOGIC::UPDATE_DATA ( float fTime, float fElapsedTime, BOOL bClient, float fCONFT_POINT_RATE )
{
	//m_fAutoPotsAttemptTimer += fElapsedTime;

	//if( m_fAutoPotsAttemptTimer >= 5.0f ){
	//	m_wAutoPotsAttemptCount = 0;
	//	m_fAutoPotsAttemptTimer = 0.0f;
	//}

	//	���� ��ų ������ ����.
	UPDATESKILLDELAY ( fElapsedTime );

	m_nDEFENSE_SKILL = m_nDEFENSE;
	m_gdDAMAGE_SKILL = m_gdDAMAGE;

	m_nSUM_HIT = m_nHIT;
	m_nSUM_AVOID = m_nAVOID;

	m_nSUM_PIERCE = m_sSUM_PASSIVE.m_nPIERCE;
	m_fSUM_TARRANGE = m_sSUM_PASSIVE.m_fTARRANGE;

	m_bSTATEBLOW = FALSE;
	m_fSTATE_MOVE = 1.0f;

	m_fSTATE_DELAY = 1.0f;

	m_fSTATE_DAMAGE = 1.0f;
	m_fSKILL_MOVE = 0.0f + m_sSUM_PASSIVE.m_fMOVEVELO;

	m_bSTATE_PANT = false;
	m_bSTATE_STUN = false;
	m_bINVISIBLE = false;
	m_bRECVISIBLE = false;

	m_dwHOLDBLOW = NULL;

	m_fDamageRate = 1.0f + m_sSUM_PASSIVE.m_fDAMAGE_RATE;
	m_fDefenseRate = 1.0f + m_sSUM_PASSIVE.m_fDEFENSE_RATE;

	m_sSUMRESIST_SKILL = m_sSUMRESIST;

	m_sDamageSpec.RESET();
	m_sDamageSpec = m_sSUM_PASSIVE.m_sDamageSpec;
	m_sDefenseSkill.RESET();

	m_fATTVELO = 0.0f;

	m_fSKILLDELAY = 0.0f;

	m_fEXP_RATE = 1;
	m_fGEN_RATE = 1;

	float fINCR_HP(m_fINCR_HP), fINCR_MP(m_fINCR_MP), fINCR_SP(m_fINCR_SP);

	int nSUM_PA(0), nSUM_SA(0), nSUM_MA(0);

	m_fHP_RATE = 0;
	m_fMP_RATE = 0;
	m_fSP_RATE = 0;

	m_bSafeZone = false;

	/*prohibit potion skill logic, Juver, 2017/06/06 */
	m_bProhibitPotion = false;

	/*prohibit skill logic, Juver, 2017/06/06 */
	m_bProhibitSkill = false; 

	/*skill range spec logic, Juver, 2017/06/06 */
	m_fSUM_SKILL_ATTACKRANGE = 0.0f;
	m_fSUM_SKILL_APPLYRANGE = 0.0f;

	/*curse skill logic, Juver, 2017/06/10 */
	m_bCurse = false;
	m_fCurseDamage = 0.0f;

	/*summon time, Juver, 2017/12/12 */
	m_nSummonTime = 0;

	/*ignore damage, Juver, 2017/12/12 */
	m_bIgnoreDamage = false;

	for ( int i=0; i<SKILLFACT_SIZE; ++i )
	{
		SSKILLFACT &sSKEFF = m_sSKILLFACT[i];
		if ( sSKEFF.sNATIVEID==NATIVEID_NULL() )	continue;

		sSKEFF.fAGE -= fElapsedTime;

		//	Ŭ���̾�Ʈ�� �ƴ� ��� ���⼭ ��ų ����Ʈ�� ��Ȱ��ȭ, Ŭ���̾�Ʈ�� UpdateSkillEffect()���� ��.
		if ( !bClient && sSKEFF.fAGE <= 0.0f )		DISABLESKEFF(i);

		switch ( sSKEFF.emTYPE )
		{
		case SKILL::EMFOR_VARHP:	fINCR_HP += sSKEFF.fMVAR;	break;
		case SKILL::EMFOR_VARMP:	fINCR_MP += sSKEFF.fMVAR;	break;
		case SKILL::EMFOR_VARSP:	fINCR_SP += sSKEFF.fMVAR;	break;
		case SKILL::EMFOR_VARAP:
			fINCR_HP += sSKEFF.fMVAR;
			fINCR_MP += sSKEFF.fMVAR;
			fINCR_SP += sSKEFF.fMVAR;
			break;

		case SKILL::EMFOR_DEFENSE:		m_nDEFENSE_SKILL += (int) sSKEFF.fMVAR;				break;
		case SKILL::EMFOR_HITRATE:		m_nSUM_HIT += int(sSKEFF.fMVAR);					break;
		case SKILL::EMFOR_AVOIDRATE:	m_nSUM_AVOID += int(sSKEFF.fMVAR);					break;
		case SKILL::EMFOR_VARDAMAGE:	m_gdDAMAGE_SKILL.VAR_PARAM ( int(sSKEFF.fMVAR) );	break;
		case SKILL::EMFOR_VARDEFENSE:	m_nDEFENSE_SKILL += int(sSKEFF.fMVAR);				break;
		case SKILL::EMFOR_PA:			nSUM_PA += int(sSKEFF.fMVAR);						break;
		case SKILL::EMFOR_SA:			nSUM_SA += int(sSKEFF.fMVAR);						break;
		case SKILL::EMFOR_MA:			nSUM_MA += int(sSKEFF.fMVAR);						break;
		case SKILL::EMFOR_HP_RATE:		m_fHP_RATE += sSKEFF.fMVAR;							break;
		case SKILL::EMFOR_MP_RATE:		m_fMP_RATE += sSKEFF.fMVAR;							break;
		case SKILL::EMFOR_SP_RATE:		m_fSP_RATE += sSKEFF.fMVAR;							break;
		case SKILL::EMFOR_RESIST:		m_sSUMRESIST_SKILL += int(sSKEFF.fMVAR);			break;
		case SKILL::EMFOR_SUMMONTIME:	m_nSummonTime += (int) sSKEFF.fMVAR;				break;	/*summon time, Juver, 2017/12/12 */
		};

		for( int nImpact=0; nImpact<SKILL::MAX_IMPACT; ++nImpact )
		{
			switch ( sSKEFF.sImpacts[nImpact].emADDON )
			{
			case EMIMPACTA_HITRATE:			m_nSUM_HIT += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);					break;
			case EMIMPACTA_AVOIDRATE:		m_nSUM_AVOID += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_DAMAGE:			m_gdDAMAGE_SKILL.VAR_PARAM ( int(sSKEFF.sImpacts[nImpact].fADDON_VAR) );	break;
			case EMIMPACTA_DEFENSE:			m_nDEFENSE_SKILL += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);			break;
			case EMIMPACTA_VARHP:			fINCR_HP += sSKEFF.sImpacts[nImpact].fADDON_VAR;						break;
			case EMIMPACTA_VARMP:			fINCR_MP += sSKEFF.sImpacts[nImpact].fADDON_VAR;						break;
			case EMIMPACTA_VARSP:			fINCR_SP += sSKEFF.sImpacts[nImpact].fADDON_VAR;						break;
			case EMIMPACTA_VARAP:
				fINCR_HP += sSKEFF.sImpacts[nImpact].fADDON_VAR;
				fINCR_MP += sSKEFF.sImpacts[nImpact].fADDON_VAR;
				fINCR_SP += sSKEFF.sImpacts[nImpact].fADDON_VAR;
				break;

			case EMIMPACTA_DAMAGE_RATE:		m_fDamageRate += sSKEFF.sImpacts[nImpact].fADDON_VAR;				break;
			case EMIMPACTA_DEFENSE_RATE:	m_fDefenseRate += sSKEFF.sImpacts[nImpact].fADDON_VAR;				break;		

			case EMIMPACTA_PA:				nSUM_PA += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_SA:				nSUM_SA += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_MA:				nSUM_MA += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_HP_RATE:			m_fHP_RATE += sSKEFF.sImpacts[nImpact].fADDON_VAR;					break;
			case EMIMPACTA_MP_RATE:			m_fMP_RATE += sSKEFF.sImpacts[nImpact].fADDON_VAR;					break;
			case EMIMPACTA_SP_RATE:			m_fSP_RATE += sSKEFF.sImpacts[nImpact].fADDON_VAR;					break;
			case EMIMPACTA_RESIST:			m_sSUMRESIST_SKILL += int(sSKEFF.sImpacts[nImpact].fADDON_VAR);		break;
			};
		}

		for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
		{
			switch ( sSKEFF.sSpecs[nSpec].emSPEC )
			{
			case EMSPECA_NONBLOW:		m_dwHOLDBLOW = sSKEFF.sSpecs[nSpec].dwSPECFLAG;			break;
			case EMSPECA_PIERCE:		m_nSUM_PIERCE += int ( sSKEFF.sSpecs[nSpec].fSPECVAR1 );	break;
			case EMSPECA_TARRANGE:		m_fSUM_TARRANGE += sSKEFF.sSpecs[nSpec].fSPECVAR1;		break;
			case EMSPECA_MOVEVELO:		m_fSKILL_MOVE += sSKEFF.sSpecs[nSpec].fSPECVAR1;		break;
			case EMSPECA_INVISIBLE:		m_bINVISIBLE = true;						break;
			case EMSPECA_RECVISIBLE:	m_bRECVISIBLE = true;						break;
				//	���� �ӵ� ����̹Ƿ� ( ���� �ð��� -0.1 (-10%) ���� ��Ű�� ���ؼ��� ��ȣ ������ �Ͽ�����. )
			case EMSPECA_ATTACKVELO:	m_fATTVELO -= sSKEFF.sSpecs[nSpec].fSPECVAR1;			break;
			case EMSPECA_SKILLDELAY:	m_fSKILLDELAY += sSKEFF.sSpecs[nSpec].fSPECVAR1;		break;

				/*prohibit potion skill logic, Juver, 2017/06/06 */
			case EMSPECA_PROHIBIT_POTION:	m_bProhibitPotion = true;			break;

				/*prohibit skill logic, Juver, 2017/06/06 */
			case EMSPECA_PROHIBIT_SKILL:	m_bProhibitSkill = true;			break;

			case EMSPECA_PSY_DAMAGE_REDUCE:
				if ( m_sDamageSpec.m_fPsyDamageReduce < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
					m_sDamageSpec.m_fPsyDamageReduce = sSKEFF.sSpecs[nSpec].fSPECVAR1;
				break;

			case EMSPECA_MAGIC_DAMAGE_REDUCE:	
				if ( m_sDamageSpec.m_fMagicDamageReduce < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
					m_sDamageSpec.m_fMagicDamageReduce = sSKEFF.sSpecs[nSpec].fSPECVAR1;		
				break;

			case EMSPECA_PSY_DAMAGE_REFLECTION:	
				if ( m_sDamageSpec.m_fPsyDamageReflection < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
				{
					m_sDamageSpec.m_fPsyDamageReflection = sSKEFF.sSpecs[nSpec].fSPECVAR1;		
					m_sDamageSpec.m_fPsyDamageReflectionRate = sSKEFF.sSpecs[nSpec].fSPECVAR2;		
				}break;

			case EMSPECA_MAGIC_DAMAGE_REFLECTION:
				if ( m_sDamageSpec.m_fMagicDamageReflection < sSKEFF.sSpecs[nSpec].fSPECVAR1 )
				{
					m_sDamageSpec.m_fMagicDamageReflection = sSKEFF.sSpecs[nSpec].fSPECVAR1;	
					m_sDamageSpec.m_fMagicDamageReflectionRate = sSKEFF.sSpecs[nSpec].fSPECVAR2;
				}break;

			case EMSPECA_DEFENSE_SKILL_ACTIVE:
				{
					m_sDefenseSkill.m_dwSkillID = sSKEFF.sSpecs[nSpec].dwNativeID;
					m_sDefenseSkill.m_wLevel = sSKEFF.sSpecs[nSpec].dwSPECFLAG;
					m_sDefenseSkill.m_fRate = sSKEFF.sSpecs[nSpec].fSPECVAR1;
				}break;

				/*skill range spec logic, Juver, 2017/06/06 */
			case EMSPECA_CHANGE_ATTACK_RANGE:
				{
					m_fSUM_SKILL_ATTACKRANGE += sSKEFF.sSpecs[nSpec].fSPECVAR1;		
				}break;
			case EMSPECA_CHANGE_APPLY_RANGE:
				{
					m_fSUM_SKILL_APPLYRANGE += sSKEFF.sSpecs[nSpec].fSPECVAR1;		
				}break;

				/*skill stun logic, Juver, 2017/06/06 */
			case EMSPECA_STUN:
				{
					m_fSTATE_MOVE = 0.0f;
					m_bSTATE_STUN = true;
				}break;

				/*continuous damage skill logic, Juver, 2017/06/10 */
			case EMSPECA_CONTINUOUS_DAMAGE:
				{
					if ( !CONTINUOUSDAMAGE_EXIST(sSKEFF.sNATIVEID) )
					{
						SCONTINUOUS_DAMAGE_DATA _sDATA;
						_sDATA.sidSkill = sSKEFF.sNATIVEID;
						_sDATA.fInterval = sSKEFF.sSpecs[nSpec].fSPECVAR1;
						_sDATA.fVar = sSKEFF.sSpecs[nSpec].fSPECVAR2;
						_sDATA.wCrow = sSKEFF._wCasterCrow;
						_sDATA.dwCrowID = sSKEFF._dwCasterID;
						_sDATA.fAge = 0.0f;

						CONTINUOUSDAMAGE_INSERT( _sDATA );
					}
				}break;

				/*curse skill logic, Juver, 2017/06/10 */
			case EMSPECA_CURSE:
				{
					m_bCurse = true;
					m_fCurseDamage += sSKEFF.sSpecs[nSpec].fSPECVAR1;
				}break;

				/*ignore damage, Juver, 2017/12/12 */
			case EMSPECA_IGNORE_DAMAGE:
				{
					m_bIgnoreDamage = true;
				}break;
			};
		}
		
	}

	for ( int i=0; i<EMBLOW_MULTI; ++i )
	{
		SSTATEBLOW &sSTATEBLOW = m_sSTATEBLOWS[i];
		if ( sSTATEBLOW.emBLOW == EMBLOW_NONE )		continue;

		m_bSTATEBLOW = TRUE;
		sSTATEBLOW.fAGE -= fElapsedTime;
		if ( !bClient && sSTATEBLOW.fAGE <= 0.0f )	DISABLEBLOW(i);

		switch ( sSTATEBLOW.emBLOW )
		{
		case EMBLOW_NUMB:
			m_fSTATE_MOVE += sSTATEBLOW.fSTATE_VAR1;			//	�̵��ӵ� ����.
			m_fSTATE_DELAY += sSTATEBLOW.fSTATE_VAR2;			//	������ ����.
			break;

		case EMBLOW_STUN:
			m_fSTATE_MOVE = 0.0f;								//	����.
			m_bSTATE_PANT = true;
			m_bSTATE_STUN = true;
			break;

		case EMBLOW_STONE:
			m_fSTATE_MOVE += sSTATEBLOW.fSTATE_VAR1;			//	�̵��ӵ� ����.
			m_fIncHP += sSTATEBLOW.fSTATE_VAR2*fElapsedTime;
			break;

		case EMBLOW_BURN:
			m_fIncHP += sSTATEBLOW.fSTATE_VAR2*fElapsedTime;
			break;

		case EMBLOW_FROZEN:
			m_fSTATE_MOVE += sSTATEBLOW.fSTATE_VAR1;			//	�̵��ӵ� ����.
			m_fSTATE_DAMAGE += sSTATEBLOW.fSTATE_VAR2;			//	����� ����.
			break;

		case EMBLOW_MAD:
			m_nSUM_HIT = 30;
			m_nSUM_AVOID = 30;
			m_bSTATE_PANT = true;
			break;

		case EMBLOW_POISON:
			m_fIncHP += sSTATEBLOW.fSTATE_VAR2*fElapsedTime;
			break;

		case EMBLOW_CURSE:
			m_fIncHP += sSTATEBLOW.fSTATE_VAR2*fElapsedTime;
			m_fINCR_MP = 0.0f;
			break;
		};
	}

	if ( m_sQITEMFACT.IsACTIVE() )
	{
 		switch ( m_sQITEMFACT.emType )
		{
		case QUESTION_SPEED_UP:		m_fSKILL_MOVE += (m_sQITEMFACT.wParam1/100.0f);		break;
		case QUESTION_CRAZY:
			m_fSKILL_MOVE += (m_sQITEMFACT.wParam1/100.0f);
			m_fATTVELO += (m_sQITEMFACT.wParam2/100.0f);
			break;
		case QUESTION_ATTACK_UP:	m_fDamageRate += (m_sQITEMFACT.wParam1/100.0f);		break;
		case QUESTION_EXP_UP:		m_fEXP_RATE += (m_sQITEMFACT.wParam1/100.0f);		break;
		case QUESTION_LUCKY:		m_fGEN_RATE += (m_sQITEMFACT.wParam1/100.0f);		break;
		case QUESTION_SPEED_UP_M:	m_fSKILL_MOVE += (m_sQITEMFACT.wParam1/100.0f);		break;
		case QUESTION_MADNESS:
			m_fSKILL_MOVE += (m_sQITEMFACT.wParam1/100.0f);
			m_fATTVELO += (m_sQITEMFACT.wParam2/100.0f);
			break;
		case QUESTION_ATTACK_UP_M:	m_fDamageRate += (m_sQITEMFACT.wParam1/100.0f);		break;
		};
	}

	//	Memo :	? ������ �̺�Ʈ ����
	if( m_sEVENTFACT.IsACTIVE( EMGM_EVENT_SPEED ) )		m_fSKILL_MOVE += (m_sEVENTFACT.wSpeed/100.0f);
	if( m_sEVENTFACT.IsACTIVE( EMGM_EVENT_ASPEED ) )	m_fATTVELO += (m_sEVENTFACT.wASpeed/100.0f);
	if( m_sEVENTFACT.IsACTIVE( EMGM_EVENT_ATTACK ) )	m_fDamageRate += (m_sEVENTFACT.wAttack/100.0f);

	// ���� ������ų ó��
	/*dual pet skill, Juver, 2017/12/27 */
	if ( m_sPETSKILLFACT_A.sNATIVEID !=NATIVEID_NULL() )
	{
		switch ( m_sPETSKILLFACT_A.emTYPE )
		{
		case SKILL::EMFOR_PET_HEAL:				//	������ HP ȸ�� �ӵ� ���
			fINCR_HP += m_sPETSKILLFACT_A.fMVAR;
			break;
		case SKILL::EMFOR_PET_SUPPROT:			//	������ HP, MP, SP ȸ���� ���
			fINCR_HP += m_sPETSKILLFACT_A.fMVAR;
			fINCR_MP += m_sPETSKILLFACT_A.fMVAR;
			fINCR_SP += m_sPETSKILLFACT_A.fMVAR;
			break;
		case SKILL::EMFOR_PET_BACKUP_ATK:		//	������ ���ݷ�(��) ���
			m_fDamageRate += m_sPETSKILLFACT_A.fMVAR/100.0f;
			break;
		case SKILL::EMFOR_PET_BACKUP_DEF:		//	������ ����(��) ���
			m_fDefenseRate += m_sPETSKILLFACT_A.fMVAR/100.0f;
			break;
		};

		// ��ų ������Ÿ�� ����
		m_sPETSKILLFACT_A.fAGE -= fElapsedTime;
	}

	// ���� ������ų ó��
	/*dual pet skill, Juver, 2017/12/27 */
	if ( m_sPETSKILLFACT_B.sNATIVEID !=NATIVEID_NULL() )
	{
		switch ( m_sPETSKILLFACT_B.emTYPE )
		{
		case SKILL::EMFOR_PET_HEAL:				//	������ HP ȸ�� �ӵ� ���
			fINCR_HP += m_sPETSKILLFACT_B.fMVAR;
			break;
		case SKILL::EMFOR_PET_SUPPROT:			//	������ HP, MP, SP ȸ���� ���
			fINCR_HP += m_sPETSKILLFACT_B.fMVAR;
			fINCR_MP += m_sPETSKILLFACT_B.fMVAR;
			fINCR_SP += m_sPETSKILLFACT_B.fMVAR;
			break;
		case SKILL::EMFOR_PET_BACKUP_ATK:		//	������ ���ݷ�(��) ���
			m_fDamageRate += m_sPETSKILLFACT_B.fMVAR/100.0f;
			break;
		case SKILL::EMFOR_PET_BACKUP_DEF:		//	������ ����(��) ���
			m_fDefenseRate += m_sPETSKILLFACT_B.fMVAR/100.0f;
			break;
		};

		// ��ų ������Ÿ�� ����
		m_sPETSKILLFACT_B.fAGE -= fElapsedTime;
	}



	// ���� ȿ�� ó��
	for( int i = 0; i < EMLANDEFFECT_MULTI; i++ )
	{
		SLANDEFFECT landEffect = m_sLandEffect[i];
		if( !landEffect.IsUse() ) continue;

		switch( landEffect.emLandEffectType ) 
		{
		case EMLANDEFFECT_ATK_SPEED: // ���ݼӵ�
			m_fATTVELO	  += landEffect.fValue;
			break;
		case EMLANDEFFECT_MOVE_SPEED: // �̵��ӵ�
			m_fSKILL_MOVE += landEffect.fValue;
			break;
		case EMLANDEFFECT_MP_RATE:	  // HP ��ȭ��
			m_fHP_RATE    += landEffect.fValue;
			break;
		case EMLANDEFFECT_HP_RATE:    // MP ��ȭ��
			m_fMP_RATE    += landEffect.fValue;
			break;
		case EMLANDEFFECT_RECOVER_RATE: // ȸ����
			fINCR_HP	  += landEffect.fValue;
			fINCR_MP	  += landEffect.fValue;
			fINCR_SP	  += landEffect.fValue;
			break;
		case EMLANDEFFECT_DAMAGE_RATE:	// ����ġ ��ȭ��
			m_fDamageRate += landEffect.fValue;
			break;
		case EMLANDEFFECT_DEFENSE_RATE:	// ���ġ ��ȭ��
			m_fDefenseRate += landEffect.fValue;
			break;
		case EMLANDEFFECT_RESIST_RATE:	// ���� ��ġ			
			m_sSUM_PASSIVE.m_sSUMRESIST.nFire += landEffect.fValue;
			m_sSUM_PASSIVE.m_sSUMRESIST.nIce += landEffect.fValue;
			m_sSUM_PASSIVE.m_sSUMRESIST.nElectric += landEffect.fValue;
			m_sSUM_PASSIVE.m_sSUMRESIST.nPoison += landEffect.fValue;
			m_sSUM_PASSIVE.m_sSUMRESIST.nSpirit += landEffect.fValue;
			break;
		case EMLANDEFFECT_CANCEL_ALLBUFF: // ��� ���� ���
//			for ( i=0; i<EMBLOW_MULTI; ++i )		DISABLEBLOW ( i );
//			for ( i=0; i<SKILLFACT_SIZE; ++i )		DISABLESKEFF ( i );
			break;
		case EMLANDEFFECT_SAFE_ZONE:
			{
				int fValue = landEffect.fValue;
				switch (fValue)
				{
					case 1:
						{
							if(m_wSchool == 0) m_bSafeZone = true;
						}
						break;
		
					case 2:
						{
							if(m_wSchool == 1) m_bSafeZone = true;
						}
						break;
		
					case 3:
						{
							if(m_wSchool == 2) m_bSafeZone = true;
						}
						break;
		
					case 4:
						{
							if(m_wCaptureTheFlagTeam == 0) m_bSafeZone = true;
						}
						break;
		
					case 5:
						{
							if(m_wCaptureTheFlagTeam == 1) m_bSafeZone = true;
						}
					default:
						m_bSafeZone = true;
						break;
				}
			}
			break;
		}
	}

	/*itemfood system, Juver, 2017/05/24 */
	for ( int i=0; i<FITEMFACT_SIZE; ++i )
	{
		SFITEMFACT &sFITEMEFF = m_sFITEMFACT[i];
		if ( sFITEMEFF.sNATIVEID==NATIVEID_NULL() )	continue;

		sFITEMEFF.fAGE -= fElapsedTime;

		if ( sFITEMEFF.fAGE <= 0.0f )
		{
			 m_sFITEMFACT[i].RESET();
		}

		switch ( sFITEMEFF.emTYPE )
		{
		case SKILL::EMFOR_VARHP:	fINCR_HP += sFITEMEFF.fMVAR;	break;
		case SKILL::EMFOR_VARMP:	fINCR_MP += sFITEMEFF.fMVAR;	break;
		case SKILL::EMFOR_VARSP:	fINCR_SP += sFITEMEFF.fMVAR;	break;
		case SKILL::EMFOR_VARAP:
			fINCR_HP += sFITEMEFF.fMVAR;
			fINCR_MP += sFITEMEFF.fMVAR;
			fINCR_SP += sFITEMEFF.fMVAR;
			break;

		case SKILL::EMFOR_DEFENSE:		m_nDEFENSE_SKILL += (int) sFITEMEFF.fMVAR;			break;
		case SKILL::EMFOR_HITRATE:		m_nSUM_HIT += int(sFITEMEFF.fMVAR);					break;
		case SKILL::EMFOR_AVOIDRATE:	m_nSUM_AVOID += int(sFITEMEFF.fMVAR);				break;
		case SKILL::EMFOR_VARDAMAGE:	m_gdDAMAGE_SKILL.VAR_PARAM ( int(sFITEMEFF.fMVAR) );	break;
		case SKILL::EMFOR_VARDEFENSE:	m_nDEFENSE_SKILL += int(sFITEMEFF.fMVAR);			break;
		case SKILL::EMFOR_PA:			nSUM_PA += int(sFITEMEFF.fMVAR);					break;
		case SKILL::EMFOR_SA:			nSUM_SA += int(sFITEMEFF.fMVAR);					break;
		case SKILL::EMFOR_MA:			nSUM_MA += int(sFITEMEFF.fMVAR);					break;
		case SKILL::EMFOR_HP_RATE:		m_fHP_RATE += sFITEMEFF.fMVAR;						break;
		case SKILL::EMFOR_MP_RATE:		m_fMP_RATE += sFITEMEFF.fMVAR;						break;
		case SKILL::EMFOR_SP_RATE:		m_fSP_RATE += sFITEMEFF.fMVAR;						break;
		case SKILL::EMFOR_RESIST:		m_sSUMRESIST_SKILL += int(sFITEMEFF.fMVAR);			break;	
		case SKILL::EMFOR_SUMMONTIME:	m_nSummonTime += (int) sFITEMEFF.fMVAR;				break;	/*summon time, Juver, 2017/12/12 */
		};

		for( int nImpact=0; nImpact<SKILL::MAX_IMPACT; ++nImpact )
		{
			switch ( sFITEMEFF.sImpacts[nImpact].emADDON )
			{
			case EMIMPACTA_HITRATE:			m_nSUM_HIT += int(sFITEMEFF.sImpacts[nImpact].fADDON_VAR);					break;
			case EMIMPACTA_AVOIDRATE:		m_nSUM_AVOID += int(sFITEMEFF.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_DAMAGE:			m_gdDAMAGE_SKILL.VAR_PARAM ( int(sFITEMEFF.sImpacts[nImpact].fADDON_VAR) );	break;
			case EMIMPACTA_DEFENSE:			m_nDEFENSE_SKILL += int(sFITEMEFF.sImpacts[nImpact].fADDON_VAR);			break;
			case EMIMPACTA_VARHP:			fINCR_HP += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;						break;
			case EMIMPACTA_VARMP:			fINCR_MP += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;						break;
			case EMIMPACTA_VARSP:			fINCR_SP += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;						break;
			case EMIMPACTA_VARAP:
				fINCR_HP += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;
				fINCR_MP += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;
				fINCR_SP += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;
				break;

			case EMIMPACTA_DAMAGE_RATE:		m_fDamageRate += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;				break;
			case EMIMPACTA_DEFENSE_RATE:	m_fDefenseRate += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;				break;		

			case EMIMPACTA_PA:				nSUM_PA += int(sFITEMEFF.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_SA:				nSUM_SA += int(sFITEMEFF.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_MA:				nSUM_MA += int(sFITEMEFF.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_HP_RATE:			m_fHP_RATE += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;					break;
			case EMIMPACTA_MP_RATE:			m_fMP_RATE += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;					break;
			case EMIMPACTA_SP_RATE:			m_fSP_RATE += sFITEMEFF.sImpacts[nImpact].fADDON_VAR;					break;
			case EMIMPACTA_RESIST:			m_sSUMRESIST_SKILL += int(sFITEMEFF.sImpacts[nImpact].fADDON_VAR);		break;
			};
		}

		for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
		{
			switch ( sFITEMEFF.sSpecs[nSpec].emSPEC )
			{
			case EMSPECA_NONBLOW:		m_dwHOLDBLOW = sFITEMEFF.sSpecs[nSpec].dwSPECFLAG;			break;
			case EMSPECA_PIERCE:		m_nSUM_PIERCE += int ( sFITEMEFF.sSpecs[nSpec].fSPECVAR1 );	break;
			case EMSPECA_TARRANGE:		m_fSUM_TARRANGE += sFITEMEFF.sSpecs[nSpec].fSPECVAR1;		break;
			case EMSPECA_MOVEVELO:		m_fSKILL_MOVE += sFITEMEFF.sSpecs[nSpec].fSPECVAR1;		break;
			case EMSPECA_INVISIBLE:		m_bINVISIBLE = true;						break;
			case EMSPECA_RECVISIBLE:	m_bRECVISIBLE = true;						break;
				//	���� �ӵ� ����̹Ƿ� ( ���� �ð��� -0.1 (-10%) ���� ��Ű�� ���ؼ��� ��ȣ ������ �Ͽ�����. )
			case EMSPECA_ATTACKVELO:	m_fATTVELO -= sFITEMEFF.sSpecs[nSpec].fSPECVAR1;			break;
			case EMSPECA_SKILLDELAY:	m_fSKILLDELAY += sFITEMEFF.sSpecs[nSpec].fSPECVAR1;		break;

			case EMSPECA_PSY_DAMAGE_REDUCE:
				if ( m_sDamageSpec.m_fPsyDamageReduce < sFITEMEFF.sSpecs[nSpec].fSPECVAR1 )
					m_sDamageSpec.m_fPsyDamageReduce = sFITEMEFF.sSpecs[nSpec].fSPECVAR1;
				break;

			case EMSPECA_MAGIC_DAMAGE_REDUCE:	
				if ( m_sDamageSpec.m_fMagicDamageReduce < sFITEMEFF.sSpecs[nSpec].fSPECVAR1 )
					m_sDamageSpec.m_fMagicDamageReduce = sFITEMEFF.sSpecs[nSpec].fSPECVAR1;		
				break;

			case EMSPECA_PSY_DAMAGE_REFLECTION:	
				if ( m_sDamageSpec.m_fPsyDamageReflection < sFITEMEFF.sSpecs[nSpec].fSPECVAR1 )
				{
					m_sDamageSpec.m_fPsyDamageReflection = sFITEMEFF.sSpecs[nSpec].fSPECVAR1;		
					m_sDamageSpec.m_fPsyDamageReflectionRate = sFITEMEFF.sSpecs[nSpec].fSPECVAR2;		
				}break;

			case EMSPECA_MAGIC_DAMAGE_REFLECTION:
				if ( m_sDamageSpec.m_fMagicDamageReflection < sFITEMEFF.sSpecs[nSpec].fSPECVAR1 )
				{
					m_sDamageSpec.m_fMagicDamageReflection = sFITEMEFF.sSpecs[nSpec].fSPECVAR1;	
					m_sDamageSpec.m_fMagicDamageReflectionRate = sFITEMEFF.sSpecs[nSpec].fSPECVAR2;
				}break;

			case EMSPECA_DEFENSE_SKILL_ACTIVE:
				{
					m_sDefenseSkill.m_dwSkillID = sFITEMEFF.sSpecs[nSpec].dwNativeID;
					m_sDefenseSkill.m_wLevel = sFITEMEFF.sSpecs[nSpec].dwSPECFLAG;
					m_sDefenseSkill.m_fRate = sFITEMEFF.sSpecs[nSpec].fSPECVAR1;
				}break;

				/*skill range spec logic, Juver, 2017/06/06 */
			case EMSPECA_CHANGE_ATTACK_RANGE:
				{
					m_fSUM_SKILL_ATTACKRANGE += sFITEMEFF.sSpecs[nSpec].fSPECVAR1;		
				}break;
			case EMSPECA_CHANGE_APPLY_RANGE:
				{
					m_fSUM_SKILL_APPLYRANGE += sFITEMEFF.sSpecs[nSpec].fSPECVAR1;		
				}break;
			};
		}
	}

	/*system buffs, Juver, 2017/09/04 */
	for ( int i=0; i<SYSTEM_BUFF_SIZE; ++i )
	{
		SSYSTEM_BUFF &ssystem_buff = m_sSYSTEM_BUFF[i];
		if ( ssystem_buff.sNATIVEID==NATIVEID_NULL() )	continue;

		switch ( ssystem_buff.emTYPE )
		{
		case SKILL::EMFOR_VARHP:	fINCR_HP += ssystem_buff.fMVAR;	break;
		case SKILL::EMFOR_VARMP:	fINCR_MP += ssystem_buff.fMVAR;	break;
		case SKILL::EMFOR_VARSP:	fINCR_SP += ssystem_buff.fMVAR;	break;
		case SKILL::EMFOR_VARAP:
			fINCR_HP += ssystem_buff.fMVAR;
			fINCR_MP += ssystem_buff.fMVAR;
			fINCR_SP += ssystem_buff.fMVAR;
			break;

		case SKILL::EMFOR_DEFENSE:		m_nDEFENSE_SKILL += (int) ssystem_buff.fMVAR;			break;
		case SKILL::EMFOR_HITRATE:		m_nSUM_HIT += int(ssystem_buff.fMVAR);					break;
		case SKILL::EMFOR_AVOIDRATE:	m_nSUM_AVOID += int(ssystem_buff.fMVAR);				break;
		case SKILL::EMFOR_VARDAMAGE:	m_gdDAMAGE_SKILL.VAR_PARAM ( int(ssystem_buff.fMVAR) );	break;
		case SKILL::EMFOR_VARDEFENSE:	m_nDEFENSE_SKILL += int(ssystem_buff.fMVAR);			break;
		case SKILL::EMFOR_PA:			nSUM_PA += int(ssystem_buff.fMVAR);						break;
		case SKILL::EMFOR_SA:			nSUM_SA += int(ssystem_buff.fMVAR);						break;
		case SKILL::EMFOR_MA:			nSUM_MA += int(ssystem_buff.fMVAR);						break;
		case SKILL::EMFOR_HP_RATE:		m_fHP_RATE += ssystem_buff.fMVAR;						break;
		case SKILL::EMFOR_MP_RATE:		m_fMP_RATE += ssystem_buff.fMVAR;						break;
		case SKILL::EMFOR_SP_RATE:		m_fSP_RATE += ssystem_buff.fMVAR;						break;
		case SKILL::EMFOR_RESIST:		m_sSUMRESIST_SKILL += int(ssystem_buff.fMVAR);			break;
		case SKILL::EMFOR_SUMMONTIME:	m_nSummonTime += (int) ssystem_buff.fMVAR;				break;	/*summon time, Juver, 2017/12/12 */
		};

		for( int nImpact=0; nImpact<SKILL::MAX_IMPACT; ++nImpact )
		{
			switch ( ssystem_buff.sImpacts[nImpact].emADDON )
			{
			case EMIMPACTA_HITRATE:			m_nSUM_HIT += int(ssystem_buff.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_AVOIDRATE:		m_nSUM_AVOID += int(ssystem_buff.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_DAMAGE:			m_gdDAMAGE_SKILL.VAR_PARAM ( int(ssystem_buff.sImpacts[nImpact].fADDON_VAR) );	break;
			case EMIMPACTA_DEFENSE:			m_nDEFENSE_SKILL += int(ssystem_buff.sImpacts[nImpact].fADDON_VAR);			break;
			case EMIMPACTA_VARHP:			fINCR_HP += ssystem_buff.sImpacts[nImpact].fADDON_VAR;						break;
			case EMIMPACTA_VARMP:			fINCR_MP += ssystem_buff.sImpacts[nImpact].fADDON_VAR;						break;
			case EMIMPACTA_VARSP:			fINCR_SP += ssystem_buff.sImpacts[nImpact].fADDON_VAR;						break;
			case EMIMPACTA_VARAP:
				fINCR_HP += ssystem_buff.sImpacts[nImpact].fADDON_VAR;
				fINCR_MP += ssystem_buff.sImpacts[nImpact].fADDON_VAR;
				fINCR_SP += ssystem_buff.sImpacts[nImpact].fADDON_VAR;
				break;

			case EMIMPACTA_DAMAGE_RATE:		m_fDamageRate += ssystem_buff.sImpacts[nImpact].fADDON_VAR;				break;
			case EMIMPACTA_DEFENSE_RATE:	m_fDefenseRate += ssystem_buff.sImpacts[nImpact].fADDON_VAR;				break;		

			case EMIMPACTA_PA:				nSUM_PA += int(ssystem_buff.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_SA:				nSUM_SA += int(ssystem_buff.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_MA:				nSUM_MA += int(ssystem_buff.sImpacts[nImpact].fADDON_VAR);				break;
			case EMIMPACTA_HP_RATE:			m_fHP_RATE += ssystem_buff.sImpacts[nImpact].fADDON_VAR;					break;
			case EMIMPACTA_MP_RATE:			m_fMP_RATE += ssystem_buff.sImpacts[nImpact].fADDON_VAR;					break;
			case EMIMPACTA_SP_RATE:			m_fSP_RATE += ssystem_buff.sImpacts[nImpact].fADDON_VAR;					break;
			case EMIMPACTA_RESIST:			m_sSUMRESIST_SKILL += int(ssystem_buff.sImpacts[nImpact].fADDON_VAR);		break;
			};
		}

		for( int nSpec=0; nSpec<SKILL::MAX_SPEC; ++nSpec )
		{
			switch ( ssystem_buff.sSpecs[nSpec].emSPEC )
			{
			case EMSPECA_NONBLOW:		m_dwHOLDBLOW = ssystem_buff.sSpecs[nSpec].dwSPECFLAG;			break;
			case EMSPECA_PIERCE:		m_nSUM_PIERCE += int ( ssystem_buff.sSpecs[nSpec].fSPECVAR1 );	break;
			case EMSPECA_TARRANGE:		m_fSUM_TARRANGE += ssystem_buff.sSpecs[nSpec].fSPECVAR1;		break;
			case EMSPECA_MOVEVELO:		m_fSKILL_MOVE += ssystem_buff.sSpecs[nSpec].fSPECVAR1;		break;
			case EMSPECA_INVISIBLE:		m_bINVISIBLE = true;						break;
			case EMSPECA_RECVISIBLE:	m_bRECVISIBLE = true;						break;
				//	���� �ӵ� ����̹Ƿ� ( ���� �ð��� -0.1 (-10%) ���� ��Ű�� ���ؼ��� ��ȣ ������ �Ͽ�����. )
			case EMSPECA_ATTACKVELO:	m_fATTVELO -= ssystem_buff.sSpecs[nSpec].fSPECVAR1;			break;
			case EMSPECA_SKILLDELAY:	m_fSKILLDELAY += ssystem_buff.sSpecs[nSpec].fSPECVAR1;		break;

			case EMSPECA_PSY_DAMAGE_REDUCE:
				if ( m_sDamageSpec.m_fPsyDamageReduce < ssystem_buff.sSpecs[nSpec].fSPECVAR1 )
					m_sDamageSpec.m_fPsyDamageReduce = ssystem_buff.sSpecs[nSpec].fSPECVAR1;
				break;

			case EMSPECA_MAGIC_DAMAGE_REDUCE:	
				if ( m_sDamageSpec.m_fMagicDamageReduce < ssystem_buff.sSpecs[nSpec].fSPECVAR1 )
					m_sDamageSpec.m_fMagicDamageReduce = ssystem_buff.sSpecs[nSpec].fSPECVAR1;		
				break;

			case EMSPECA_PSY_DAMAGE_REFLECTION:	
				if ( m_sDamageSpec.m_fPsyDamageReflection < ssystem_buff.sSpecs[nSpec].fSPECVAR1 )
				{
					m_sDamageSpec.m_fPsyDamageReflection = ssystem_buff.sSpecs[nSpec].fSPECVAR1;		
					m_sDamageSpec.m_fPsyDamageReflectionRate = ssystem_buff.sSpecs[nSpec].fSPECVAR2;		
				}break;

			case EMSPECA_MAGIC_DAMAGE_REFLECTION:
				if ( m_sDamageSpec.m_fMagicDamageReflection < ssystem_buff.sSpecs[nSpec].fSPECVAR1 )
				{
					m_sDamageSpec.m_fMagicDamageReflection = ssystem_buff.sSpecs[nSpec].fSPECVAR1;	
					m_sDamageSpec.m_fMagicDamageReflectionRate = ssystem_buff.sSpecs[nSpec].fSPECVAR2;
				}break;

			case EMSPECA_DEFENSE_SKILL_ACTIVE:
				{
					m_sDefenseSkill.m_dwSkillID = ssystem_buff.sSpecs[nSpec].dwNativeID;
					m_sDefenseSkill.m_wLevel = ssystem_buff.sSpecs[nSpec].dwSPECFLAG;
					m_sDefenseSkill.m_fRate = ssystem_buff.sSpecs[nSpec].fSPECVAR1;
				}break;

				/*skill range spec logic, Juver, 2017/06/06 */
			case EMSPECA_CHANGE_ATTACK_RANGE:
				{
					m_fSUM_SKILL_ATTACKRANGE += ssystem_buff.sSpecs[nSpec].fSPECVAR1;		
				}break;
			case EMSPECA_CHANGE_APPLY_RANGE:
				{
					m_fSUM_SKILL_APPLYRANGE += ssystem_buff.sSpecs[nSpec].fSPECVAR1;		
				}break;
			};
		}
	}

	/*vehicle booster system, Juver, 2017/08/11 */
	if ( m_bBoosterStart )	m_fSKILL_MOVE += ( GLCONST_CHAR::fVehicleBoosterAddSpeed /100.0f );

	//	Note : HP, MP, SP �ѷ� Ȯ��.
	//
	UPDATE_MAX_POINT ( fCONFT_POINT_RATE );

	//	����ġ ���ġ ����ġ ����.
	m_wSUM_PA = m_wPA + nSUM_PA;
	m_wSUM_SA = m_wSA + nSUM_SA;
	m_wSUM_MA = m_wMA + nSUM_MA;

	//	����. ��ȭ�� �ݿ�.
	m_nDEFENSE_SKILL = int ( m_nDEFENSE_SKILL * m_fDefenseRate );
	if ( m_nDEFENSE_SKILL < 0 )			m_nDEFENSE_SKILL = 1;

	m_sSUMRESIST_SKILL.LIMIT();

	//	���� �ӵ�. ( ���� skill �Ӽ� ����� �κп� state, passive skill �Ӽ� ����. )
	m_fATTVELO += m_fSTATE_MOVE + m_sSUM_PASSIVE.m_fATTVELO;

	m_fSTATE_DELAY += m_fSKILLDELAY + m_sSUM_PASSIVE.m_fSKILLDELAY;

	//	���� ���ɰŸ�.
	m_wSUM_ATTRANGE = m_wATTRANGE;

	//	MP �������� ������.
	if ( (m_fINCR_MP==0.0f) && (m_fIncMP>0) )		m_fIncMP = 0;





	//	��ų ȿ���� ����� ������ ����.
	m_gdDAMAGE_PHYSIC = m_gdDAMAGE_SKILL;
	m_gdDAMAGE_PHYSIC.wLow += m_sSUMITEM.gdDamage.wLow;
	m_gdDAMAGE_PHYSIC.wMax += m_sSUMITEM.gdDamage.wMax;

	if ( ISLONGRANGE_ARMS() )	m_gdDAMAGE_PHYSIC.VAR_PARAM ( m_wSUM_SA );	//	��Ÿ� ����.
	else						m_gdDAMAGE_PHYSIC.VAR_PARAM ( m_wSUM_PA );	//	���� ����.

	//	���ݷ�. ��ȭ�� �ݿ�.
	m_gdDAMAGE_PHYSIC.wLow = WORD ( m_gdDAMAGE_PHYSIC.wLow * m_fDamageRate );
	m_gdDAMAGE_PHYSIC.wHigh = WORD ( m_gdDAMAGE_PHYSIC.wHigh * m_fDamageRate );

	//	Note : ü�� ��ȭ.
	//
	float fElap = (fElapsedTime/GLCONST_CHAR::fUNIT_TIME);
	float fINC_HP = fElap* ( m_sHP.wMax*fINCR_HP + GLCONST_CHAR::fHP_INC + m_sSUMITEM.fInc_HP );
	float fINC_MP = fElap* ( m_sMP.wMax*fINCR_MP + GLCONST_CHAR::fMP_INC + m_sSUMITEM.fInc_MP );
	float fINC_SP = fElap* ( m_sSP.wMax*fINCR_SP + GLCONST_CHAR::fSP_INC + m_sSUMITEM.fInc_SP );

	GLOGICEX::UPDATE_POINT ( m_sHP, m_fIncHP, fINC_HP, 1 );
	GLOGICEX::UPDATE_POINT ( m_sMP, m_fIncMP, fINC_MP, 0 );
	GLOGICEX::UPDATE_POINT ( m_sSP, m_fIncSP, fINC_SP, 0 );


}
float GLCHARLOGIC::GETATTVELO ()
{
	//	return m_fATTVELO<0.0f?0.0f:m_fATTVELO;
	float fATTVELO = m_fATTVELO + m_sSUMITEM.fIncR_AtkSpeed;
	return fATTVELO<0.0f?0.0f:fATTVELO;
}

void GLCHARLOGIC::LEARN_SKILL_NONSCROLL ( SNATIVEID skill_id )
{
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )	return;

	SKILL::SLEARN_LVL &sSKILL_LEARN_LVL = pSkill->m_sLEARN.sLVL_STEP[0];
	if ( m_dwSkillPoint < sSKILL_LEARN_LVL.dwSKP )	return;

	SCHARSKILL* pCharSkill = GETLEARNED_SKILL( skill_id );
	
	/*if ( !pCharSkill ) 
	{
		if ( m_lnMoney < sSKILL_LEARN_LVL.dwMoneyReq )	return;
	}

	m_dwSkillPoint -= sSKILL_LEARN_LVL.dwSKP;

	if ( !pCharSkill ) 
	{
		m_lnMoney -= sSKILL_LEARN_LVL.dwMoneyReq;
	}*/

	m_ExpSkills.insert ( std::make_pair(skill_id.dwID,SCHARSKILL(skill_id,0)) );

	if ( pSkill->m_sBASIC.emROLE == SKILL::EMROLE_PASSIVE )
	{
		INIT_DATA ( FALSE, FALSE );
	}
}
float GLCHARLOGIC::GETMOVEVELO ()
{
	float fMOVE = m_fSTATE_MOVE + m_fSKILL_MOVE + m_fOPTION_MOVE + m_sSUMITEM.fIncR_MoveSpeed;
	return fMOVE<0.0f?0.0f:fMOVE;
}

float GLCHARLOGIC::GETATT_ITEM ()
{
	float fATTVELO = m_sSUMITEM.fInc_AtkSpeed / 100;
	return fATTVELO;
}
float GLCHARLOGIC::GETMOVE_ITEM ()
{
	float fMOVE = ( m_sSUMITEM.fInc_MoveSpeed / GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX].fRUNVELO);
	return fMOVE<0.0f?0.0f:fMOVE;
}

//	�ܼ��� ������ġ ������ �˻�.
BOOL GLCHARLOGIC::CHECKSLOT_ITEM ( SNATIVEID sNativeID, EMSLOT emSlot )
{
	if ( sNativeID==NATIVEID_NULL() )		return FALSE;

	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sNativeID );
	if ( pItem==NULL )	return FALSE;

	const SITEM &sItem = *pItem;

	if( sItem.sBasicOp.emItemType!=ITEM_SUIT && 
		sItem.sBasicOp.emItemType!=ITEM_ARROW && 
		sItem.sBasicOp.emItemType!=ITEM_CHARM && 
		sItem.sBasicOp.emItemType!=ITEM_BULLET &&  /*gun-bullet logic, Juver, 2017/05/27 */
		sItem.sBasicOp.emItemType!=ITEM_ANTI_DISAPPEAR &&
		sItem.sBasicOp.emItemType!=ITEM_REVIVE && 
		sItem.sBasicOp.emItemType!=ITEM_VEHICLE )
		return FALSE;

	//	�ش� ���Կ� ���������� SUIT����.
	EMSUIT emSuit= SLOT_2_SUIT ( emSlot );
	if ( sItem.sSuitOp.emSuit != emSuit )	return FALSE;

	if ( sItem.sBasicOp.emItemType == ITEM_REVIVE ||
		 sItem.sBasicOp.emItemType == ITEM_ANTI_DISAPPEAR )
	{
		if ( emSlot != SLOT_NECK )
			return FALSE;
	}

	if ( sItem.sBasicOp.emItemType == ITEM_VEHICLE )
	{
		if ( emSlot != SLOT_VEHICLE ) return FALSE;
	}

	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();
	
	if ( sItem.sBasicOp.emItemType==ITEM_ARROW || 
		sItem.sBasicOp.emItemType==ITEM_CHARM ||

		/*gun-bullet logic, Juver, 2017/05/27 */
		sItem.sBasicOp.emItemType==ITEM_BULLET )
	{
		if ( emSlot!=emLHand )
			return FALSE;
	}

	//	�տ� ��� ������ �Ѽտ��϶�.
	if ( emSuit==SUIT_HANDHELD )
	{
		//	��� �����.
		//
		if ( sItem.sSuitOp.IsBOTHHAND() )
		{
			if ( emSlot!=emRHand )											
				return FALSE;
		}
		//	�Ѽ� �����.
		//
		else
		{
			if ( sItem.sSuitOp.emHand!=HAND_BOTH )	//	��� ��� �����ϸ� ���� ����.
			{
				if ( sItem.sSuitOp.emHand==HAND_RIGHT && emSlot!=emRHand )	return FALSE;
				if ( sItem.sSuitOp.emHand==HAND_LEFT && emSlot!=emLHand )	return FALSE;
			}

			if ( sItem.sBasicOp.emItemType==ITEM_ARROW )
			{
				//	ȭ�� ����ÿ��� �����տ� Ȱ�� ������ ���� �ʴٸ� ���� �Ұ���.
				if ( !m_pITEMS[emRHand] || m_pITEMS[emRHand]->sSuitOp.emAttack!=ITEMATT_BOW )	
					return FALSE;
			}
			else if ( sItem.sBasicOp.emItemType==ITEM_CHARM )
			{
				//	���� ����ÿ��� �����տ� â�� ������ ���� �ʴٸ� ���� �Ұ���.
				if ( !m_pITEMS[emRHand] || m_pITEMS[emRHand]->sSuitOp.emAttack!=ITEMATT_SPEAR )	
					return FALSE;
			}
			/*gun-bullet logic, Juver, 2017/05/27 */
			else if ( sItem.sBasicOp.emItemType==ITEM_BULLET )
			{
				if ( !m_pITEMS[emRHand] || !( m_pITEMS[emRHand]->sSuitOp.emAttack==ITEMATT_GUN ||
											m_pITEMS[emRHand]->sSuitOp.emAttack==ITEMATT_RAIL_GUN ||
											m_pITEMS[emRHand]->sSuitOp.emAttack==ITEMATT_PORTAL_GUN ) )	
					return FALSE;
			}
		}
	}

	return TRUE;
}

//	�������� ������ �񿴴��� �˻��Ѵ�.
//	��, Ȱ�� ��� ���������� �޼տ� ȭ���� �����Ҽ� �ִ�.
BOOL GLCHARLOGIC::ISEMPTY_SLOT ( SNATIVEID sNativeID, EMSLOT emSlot )
{
	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sNativeID );
	if ( pItem==NULL )	return FALSE;

	EMSUIT emSuit= SLOT_2_SUIT ( emSlot );

	BOOL bEmptySlot = TRUE;
	if ( pItem->sSuitOp.emSuit==SUIT_HANDHELD )
	{
		EMSLOT emRHand = GetCurRHand();
		EMSLOT emLHand = GetCurLHand();

		//	�������� �ϴ� �������� ��յ����� ��.
		if ( pItem->sSuitOp.IsBOTHHAND() )
		{
			if ( m_pITEMS[emRHand] || m_pITEMS[emLHand] )
			{
				bEmptySlot = FALSE;
			}

			//	���� �������°� Ȱ�̶��. �޼տ� ȭ���� �־ ��. �� �������� ��� �־��.
			if ( pItem->sSuitOp.emAttack==ITEMATT_BOW )
			{
				if ( !m_pITEMS[emRHand] && m_pITEMS[emLHand] )
				{
					if ( m_pITEMS[emLHand]->sBasicOp.emItemType==ITEM_ARROW )
					{
						bEmptySlot = TRUE;
					}
				}
			}

			//	�������� ���� â �����϶� �޼տ� ������ �־ ��.
			if ( pItem->sSuitOp.emAttack==ITEMATT_SPEAR )
			{
				if ( !m_pITEMS[emRHand] && m_pITEMS[emLHand] )
				{
					if ( m_pITEMS[emLHand]->sBasicOp.emItemType==ITEM_CHARM )
					{
						bEmptySlot = TRUE;
					}
				}
			}

			/*gun-bullet logic, Juver, 2017/05/27 */
			if ( pItem->sSuitOp.emAttack==ITEMATT_GUN ||
				pItem->sSuitOp.emAttack==ITEMATT_RAIL_GUN ||
				 pItem->sSuitOp.emAttack==ITEMATT_PORTAL_GUN )
			{
				if ( !m_pITEMS[emRHand] && m_pITEMS[emLHand] )
				{
					if ( m_pITEMS[emLHand]->sBasicOp.emItemType==ITEM_BULLET )
					{
						bEmptySlot = TRUE;
					}
				}
			}
		}
		//	�������� �������� �Ѽյ����� ��.
		else
		{
			//	���� ���Ⱑ ����϶�.
			if ( m_pITEMS[emRHand] && m_pITEMS[emRHand]->sSuitOp.IsBOTHHAND() )
			{
				bEmptySlot = FALSE;
			}
			//	���� ���Ⱑ �Ѽ��϶�.
			else
			{
				if ( m_pITEMS[emSlot] )		bEmptySlot = FALSE;
			}

			//	�������� �������� ȭ���϶�.
			if ( pItem->sBasicOp.emItemType==ITEM_ARROW )
			{
				bEmptySlot = FALSE;
				if ( m_pITEMS[emRHand] && !m_pITEMS[emLHand] )
				{
					if ( m_pITEMS[emRHand]->sSuitOp.emAttack==ITEMATT_BOW )			bEmptySlot = TRUE;
				}
			}

			//	�������� �������� �����϶�.
			if ( pItem->sBasicOp.emItemType==ITEM_CHARM )
			{
				bEmptySlot = FALSE;
				if ( m_pITEMS[emRHand] && !m_pITEMS[emLHand] )
				{
					if ( m_pITEMS[emRHand]->sSuitOp.emAttack==ITEMATT_SPEAR )		bEmptySlot = TRUE;
				}
			}

			/*gun-bullet logic, Juver, 2017/05/27 */
			if ( pItem->sBasicOp.emItemType==ITEM_BULLET )
			{
				bEmptySlot = FALSE;
				if ( m_pITEMS[emRHand] && !m_pITEMS[emLHand] )
				{
					if ( m_pITEMS[emRHand]->sSuitOp.emAttack==ITEMATT_GUN ||
						m_pITEMS[emRHand]->sSuitOp.emAttack==ITEMATT_RAIL_GUN ||
						m_pITEMS[emRHand]->sSuitOp.emAttack==ITEMATT_PORTAL_GUN )		
						bEmptySlot = TRUE;
				}
			}
		}
	}
	else if ( m_pITEMS[emSlot] )			bEmptySlot = FALSE;

	return bEmptySlot;
}

BOOL GLCHARLOGIC::ACCEPT_ITEM ( SNATIVEID sNativeID )
{
	if ( sNativeID==NATIVEID_NULL() )							return FALSE;

	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sNativeID );
	if ( pItem==NULL )											return FALSE;

	const SITEM &sItem = *pItem;
	BOOL bArmor = (( sItem.sSuitOp.emSuit==SUIT_HANDHELD )&&sItem.sBasicOp.emItemType==ITEM_SUIT);
	WORD wAPT = bArmor ? (WORD) GLCONST_CHAR::dwACCEPT_LOWERSTATS : 0;

	if ( !(sItem.sBasicOp.dwReqCharClass&m_emClass) )			return FALSE;
	if ( !(sItem.sBasicOp.dwReqSchool&index2school(m_wSchool)) ) return FALSE;

	if ( sItem.sBasicOp.emReqBright!=BRIGHT_BOTH )
	{
		if ( GETBRIGHT()!=sItem.sBasicOp.emReqBright )			return FALSE;
	}

	if ( m_wSUM_PA < sItem.sBasicOp.wReqPA )					return FALSE;
	if ( m_wSUM_SA < sItem.sBasicOp.wReqSA )					return FALSE;

	/*UserNum ItemReq, Juver, 2017/06/27 */
	if ( sItem.sBasicOp.dwReqUserNum != 0 )
	{
		if ( GetUserID() != sItem.sBasicOp.dwReqUserNum )		return FALSE;
	}

	/*contribution point, Juver, 2017/08/23 */
	if ( sItem.sBasicOp.dwReqContributionPoint != 0 )
	{
		if ( m_llContributionPoint < sItem.sBasicOp.dwReqContributionPoint )	return FALSE;
	}

	/*activity point, Juver, 2017/08/23 */
	if( sItem.sBasicOp.dwReqActivityPoint != 0 )
	{
		if( m_dwActivityPoint < sItem.sBasicOp.dwReqActivityPoint )				return FALSE;
	}

	if ( m_wLevel+wAPT < sItem.sBasicOp.wReqLevelDW )			return FALSE;
	if ( sItem.sBasicOp.wReqLevelUP && m_wLevel > sItem.sBasicOp.wReqLevelUP )	return FALSE;
	if ( !m_sSUMSTATS.CHECK_REQ ( sItem.sBasicOp.sReqStats, wAPT ) )		return FALSE;
	
	if ( pItem->sSkillBookOp.sSkill_ID!=NATIVEID_NULL() &&
		pItem->sBasicOp.emItemType != ITEM_FOOD ) /*itemfood system, Juver, 2017/05/25 */
	{
		if ( CHECKLEARNABLE_SKILL ( pItem->sSkillBookOp.sSkill_ID )!=EMSKILL_LEARN_OK )		return FALSE;
	}

	return TRUE;
}


BOOL GLCHARLOGIC::SIMPLE_CHECK_ITEM ( SNATIVEID sNativeID )
{
	if ( sNativeID==NATIVEID_NULL() )							return FALSE;

	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sNativeID );
	if ( pItem==NULL )											return FALSE;

	const SITEM &sItem = *pItem;
	BOOL bArmor = (( sItem.sSuitOp.emSuit==SUIT_HANDHELD )&&sItem.sBasicOp.emItemType==ITEM_SUIT);
	WORD wAPT = bArmor ? (WORD) GLCONST_CHAR::dwACCEPT_LOWERSTATS : 0;    

	if ( !(sItem.sBasicOp.dwReqCharClass&m_emClass) )			return FALSE;
	if ( !(sItem.sBasicOp.dwReqSchool&index2school(m_wSchool)) ) return FALSE;

	if ( m_wLevel+wAPT < sItem.sBasicOp.wReqLevelDW )			return FALSE;
	if ( sItem.sBasicOp.wReqLevelUP && m_wLevel > sItem.sBasicOp.wReqLevelUP )	return FALSE;	

	return TRUE;
}

BOOL GLCHARLOGIC::SIMPLE_CHECK_ITEM ( SNATIVEID sNativeID, SNATIVEID sDisguiseID )
{
	if ( sNativeID==NATIVEID_NULL() )							return FALSE;
	if ( sDisguiseID==NATIVEID_NULL() )							return FALSE;

	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sNativeID );
	if ( pItem==NULL )											return FALSE;

	SITEM* pItemDisguise = GLItemMan::GetInstance().GetItem ( sDisguiseID );
	if ( pItem==NULL )											return FALSE;

	const SITEM &sItem = *pItem;
	const SITEM &sItemDisguise = *pItemDisguise;
	BOOL bArmor = (( sItem.sSuitOp.emSuit==SUIT_HANDHELD )&&sItem.sBasicOp.emItemType==ITEM_SUIT);
	WORD wAPT = bArmor ? (WORD) GLCONST_CHAR::dwACCEPT_LOWERSTATS : 0;

	//	Memo : �ڽ�Ƭ�� ���� �ڰݿ���� üũ�Ѵ�.
	//		�� ���� �������� ���밡�� �����̴�.
	if( !(sItem.sBasicOp.dwReqCharClass&m_emClass) ||
		!(sItemDisguise.sBasicOp.dwReqCharClass&m_emClass) )	return FALSE;
	if ( !(sItem.sBasicOp.dwReqSchool&index2school(m_wSchool)) ) return FALSE;

	if ( m_wLevel+wAPT < sItem.sBasicOp.wReqLevelDW )				return FALSE;
	if ( sItem.sBasicOp.wReqLevelUP && m_wLevel > sItem.sBasicOp.wReqLevelUP )					return FALSE;

	return TRUE;
}

BOOL GLCHARLOGIC::ACCEPT_ITEM ( SNATIVEID sNativeID, SNATIVEID sDisguiseID )
{
	if ( sNativeID==NATIVEID_NULL() )							return FALSE;
	if ( sDisguiseID==NATIVEID_NULL() )							return FALSE;

	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sNativeID );
	if ( pItem==NULL )											return FALSE;

	SITEM* pItemDisguise = GLItemMan::GetInstance().GetItem ( sDisguiseID );
	if ( pItem==NULL )											return FALSE;

	const SITEM &sItem = *pItem;
	const SITEM &sItemDisguise = *pItemDisguise;
	BOOL bArmor = (( sItem.sSuitOp.emSuit==SUIT_HANDHELD )&&sItem.sBasicOp.emItemType==ITEM_SUIT);
	WORD wAPT = bArmor ? (WORD) GLCONST_CHAR::dwACCEPT_LOWERSTATS : 0;

	//	Memo : �ڽ�Ƭ�� ���� �ڰݿ���� üũ�Ѵ�.
	//		�� ���� �������� ���밡�� �����̴�.
	if( !(sItem.sBasicOp.dwReqCharClass&m_emClass) ||
		!(sItemDisguise.sBasicOp.dwReqCharClass&m_emClass) )	return FALSE;
	if ( !(sItem.sBasicOp.dwReqSchool&index2school(m_wSchool)) ) return FALSE;

	if ( sItem.sBasicOp.emReqBright!=BRIGHT_BOTH )
	{
		if ( GETBRIGHT()!=sItem.sBasicOp.emReqBright )			return FALSE;
	}

	if ( m_wSUM_PA < sItem.sBasicOp.wReqPA )					return FALSE;
	if ( m_wSUM_SA < sItem.sBasicOp.wReqSA )					return FALSE;

	/*UserNum ItemReq, Juver, 2017/06/27 */
	if ( sItem.sBasicOp.dwReqUserNum != 0 )
	{
		if ( GetUserID() != sItem.sBasicOp.dwReqUserNum )		return FALSE;
	}

	/*contribution point, Juver, 2017/08/23 */
	if ( sItem.sBasicOp.dwReqContributionPoint != 0 )
	{
		if ( m_llContributionPoint < sItem.sBasicOp.dwReqContributionPoint )	return FALSE;
	}

	/*activity point, Juver, 2017/08/23 */
	if( sItem.sBasicOp.dwReqActivityPoint != 0 )
	{
		if( m_dwActivityPoint < sItem.sBasicOp.dwReqActivityPoint )				return FALSE;
	}

	if ( m_wLevel+wAPT < sItem.sBasicOp.wReqLevelDW )				return FALSE;
	if ( sItem.sBasicOp.wReqLevelUP && m_wLevel > sItem.sBasicOp.wReqLevelUP )					return FALSE;
	if ( !m_sSUMSTATS.CHECK_REQ ( sItem.sBasicOp.sReqStats, wAPT ) )		
		return FALSE;

	if ( pItem->sSkillBookOp.sSkill_ID!=NATIVEID_NULL() &&
		pItem->sBasicOp.emItemType != ITEM_FOOD ) /*itemfood system, Juver, 2017/05/25 */
	{
		if ( CHECKLEARNABLE_SKILL ( pItem->sSkillBookOp.sSkill_ID )!=EMSKILL_LEARN_OK )		
			return FALSE;
	}

	return TRUE;
}

WORD GLCHARLOGIC::CALC_ACCEPTP ( SNATIVEID sNativeID )
{
	WORD wATP = 0;
	if ( sNativeID==NATIVEID_NULL() )							return wATP;
	SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sNativeID );
	if ( pITEM==NULL )											return wATP;

	if ( m_sSUMSTATS.wPow < pITEM->sBasicOp.sReqStats.wPow )		wATP += pITEM->sBasicOp.sReqStats.wPow - m_sSUMSTATS.wPow;
	if ( m_sSUMSTATS.wStr < pITEM->sBasicOp.sReqStats.wStr )		wATP += pITEM->sBasicOp.sReqStats.wStr - m_sSUMSTATS.wStr;
	if ( m_sSUMSTATS.wSpi < pITEM->sBasicOp.sReqStats.wSpi )		wATP += pITEM->sBasicOp.sReqStats.wSpi - m_sSUMSTATS.wSpi;
	if ( m_sSUMSTATS.wDex < pITEM->sBasicOp.sReqStats.wDex )		wATP += pITEM->sBasicOp.sReqStats.wDex - m_sSUMSTATS.wDex;
	if ( m_sSUMSTATS.wInt < pITEM->sBasicOp.sReqStats.wInt )		wATP += pITEM->sBasicOp.sReqStats.wInt - m_sSUMSTATS.wInt;
	if ( m_sSUMSTATS.wSta < pITEM->sBasicOp.sReqStats.wSta )		wATP += pITEM->sBasicOp.sReqStats.wSta - m_sSUMSTATS.wSta;

	if ( m_wLevel < pITEM->sBasicOp.wReqLevelDW )					wATP += pITEM->sBasicOp.wReqLevelDW - m_wLevel;

	return wATP;
}

EMBEGINATTACK_FB GLCHARLOGIC::BEGIN_ATTACK ( WORD wStrikeNum )
{
	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	SITEM* pRHAND = GET_SLOT_ITEMDATA ( emRHand );
	SITEM* pLHAND = GET_SLOT_ITEMDATA ( emLHand );

	if ( pRHAND && pRHAND->sSuitOp.emAttack==ITEMATT_BOW )
	{
		if ( !pLHAND || pLHAND->sBasicOp.emItemType != ITEM_ARROW )			return EMBEGINA_ARROW;

		//	��밡�ɼ� ���� ��Ŵ.
		WORD &wTurnNum = m_PutOnItems[emLHand].wTurnNum;
		if ( wTurnNum >= wStrikeNum )	wTurnNum -= wStrikeNum;
		else							wTurnNum = 0;
	}

	/*gun-bullet logic, Juver, 2017/05/27 */
	if ( pRHAND && ( pRHAND->sSuitOp.emAttack==ITEMATT_GUN || 
		pRHAND->sSuitOp.emAttack==ITEMATT_RAIL_GUN || 
		pRHAND->sSuitOp.emAttack==ITEMATT_PORTAL_GUN ) )
	{
		if ( !pLHAND || pLHAND->sBasicOp.emItemType != ITEM_BULLET )			return EMBEGINA_BULLET;

		WORD &wTurnNum = m_PutOnItems[emLHand].wTurnNum;
		if ( wTurnNum >= wStrikeNum )	wTurnNum -= wStrikeNum;
		else							wTurnNum = 0;
	}

	WORD wDisSP = GLCONST_CHAR::wBASIC_DIS_SP;
	if ( pRHAND )	wDisSP += pRHAND->sSuitOp.wReqSP;
	if ( pLHAND )	wDisSP += pLHAND->sSuitOp.wReqSP;

	//	SP ���� äũ.
	if ( m_sSP.wNow < (wDisSP*wStrikeNum) )	return EMBEGINA_SP;

	return EMBEGINA_OK;
}

BOOL GLCHARLOGIC::VALID_LEVELUP () const
{
	// �ذ��δ� �ִ� ���� üũ�� �ٸ��� �Ѵ�.
	if( m_CHARINDEX == GLCI_EXTREME_M || m_CHARINDEX == GLCI_EXTREME_W )
	{
		if ( m_wLevel >= GLCONST_CHAR::wMAX_EXTREME_LEVEL )	return FALSE;
	}else{
		if ( m_wLevel >= GLCONST_CHAR::wMAX_LEVEL )	return FALSE;
	}
	return m_sExperience.lnNow >= GET_LEVELUP_EXP();
}

LONGLONG GLCHARLOGIC::GET_LEVELUP_EXP () const
{
	if( m_CHARINDEX == GLCI_EXTREME_M || m_CHARINDEX == GLCI_EXTREME_W )
	{
		return GLOGICEX::GLNEEDEXP2(GETLEVEL());
	}
	else
	{
		return GLOGICEX::GLNEEDEXP(GETLEVEL());
	}
}

void GLCHARLOGIC::LEVLEUP ( bool bInitNowExp )
{
	bool bMaxLevel = FALSE;
	if( m_CHARINDEX == GLCI_EXTREME_M || m_CHARINDEX == GLCI_EXTREME_W )
	{
		if( m_wLevel < GLCONST_CHAR::wMAX_EXTREME_LEVEL ) bMaxLevel = TRUE;
	}else{
		if( m_wLevel < GLCONST_CHAR::wMAX_LEVEL ) bMaxLevel = TRUE;
	}


	if ( /*m_wLevel < GLCONST_CHAR::wMAX_LEVEL*/bMaxLevel )
	{
		//	���� ����ġ ����.
		//GASSERT(m_sExperience.lnNow>=GET_LEVELUP_EXP());
		m_sExperience.lnNow -= GET_LEVELUP_EXP();

		//	������.
		++m_wLevel;

		//	������ ���ʽ� ����Ʈ
		if( m_CHARINDEX == GLCI_EXTREME_M || m_CHARINDEX == GLCI_EXTREME_W )
		{
			m_wStatsPoint += GLCONST_CHAR::wLVL_2ndSTATS_P;
			m_dwSkillPoint += GLCONST_CHAR::wLVL_2ndSKILL_P;
		}
		else
		{
			m_wStatsPoint += GLCONST_CHAR::wLVL_STATS_P;
			m_dwSkillPoint += GLCONST_CHAR::wLVL_SKILL_P;
		}

		//	��� ��ġ�� �ٽ� �ʱ�ȭ �Ѵ�.
		INIT_DATA(FALSE,FALSE,1.0f,bInitNowExp);

		//	ä���� ��� ȸ�� �����ش�.
		m_sHP.TO_FULL ();
		m_sMP.TO_FULL ();
		m_sSP.TO_FULL ();	
	}
}

void GLCHARLOGIC::STATSUP ( EMSTATS emStats )
{
	switch ( emStats )
	{
	case EMPOW:
		{
			if ( m_sStats.wPow >= GLCONST_CHAR::dwPowMax )
			{}else{
				++m_sStats.wPow;
				--m_wStatsPoint;	}
		}
		break;

	case EMSTR:
		{
			if ( m_sStats.wStr >= GLCONST_CHAR::dwStrMax )
			{}else{
				++m_sStats.wStr;
				--m_wStatsPoint;	}
		}
		break;

	case EMSPI: 
		{
			if ( m_sStats.wSpi >= GLCONST_CHAR::dwSpiMax )
			{}else{
				++m_sStats.wSpi; 
				--m_wStatsPoint;	}
		}
		break;

	case EMDEX: 
		{
			if ( m_sStats.wDex >= GLCONST_CHAR::dwDexMax )
			{}else{
				++m_sStats.wDex; 
				--m_wStatsPoint;	}
		}
		break;

	case EMINT:
		{
			if ( m_sStats.wInt >= GLCONST_CHAR::dwIntMax )
			{}else{
				++m_sStats.wInt; 
				--m_wStatsPoint;	}
		}
		break;

	case EMSTA: 
		{
			if ( m_sStats.wSta >= GLCONST_CHAR::dwStaMax )
			{}else{
				++m_sStats.wSta;
				--m_wStatsPoint;
			}
		}
		break;
	};

	INIT_DATA(FALSE,FALSE);
}


void GLCHARLOGIC::STATSUP ( SCHARSTATS sStats )
{
	m_sStats.wPow += sStats.wPow;
	m_sStats.wStr += sStats.wStr;
	m_sStats.wSpi += sStats.wSpi;
	m_sStats.wDex += sStats.wDex;
	m_sStats.wInt += sStats.wInt;
	m_sStats.wSta += sStats.wSta;

	m_wStatsPoint -= sStats.GetTotal();

	INIT_DATA(FALSE,FALSE);
}
// *****************************************************
// Desc: ��ų���� ����
// *****************************************************
bool GLCHARLOGIC::RESET_SKILL ()
{
	EMCHARINDEX emINDEX = CharClassToIndex(m_emClass);
	const SCHARDATA2& sCHARDATA = GLCONST_CHAR::GET_CHAR_DATA2(m_wSchool,emINDEX);

	//	Note : ����Ʈ���� ȹ���� ��ų ����Ʈ.
	//
	DWORD dwGiftSkill(0);

	GLQuestPlay::MAPQUEST& sQuestEnd = m_cQuestPlay.GetQuestEnd();
	GLQuestPlay::MAPQUEST_ITER pos = sQuestEnd.begin();
	GLQuestPlay::MAPQUEST_ITER end = sQuestEnd.end();
	for ( ; pos!=end; ++pos )
	{
		GLQUESTPROG *pPROG = (*pos).second;
		GLQUEST *pQUEST = GLQuestMan::GetInstance().Find ( pPROG->m_sNID.dwID );
		if ( !pQUEST )	continue;

		dwGiftSkill += pQUEST->m_dwGiftSKILLPOINT;
	}

	//	Note : ��ų ����Ʈ �ʱ�ȭ.
	//
	if( m_CHARINDEX == GLCI_EXTREME_M || m_CHARINDEX == GLCI_EXTREME_W )
	{
		m_dwSkillPoint = sCHARDATA.m_dwSkillPoint + (m_wLevel-1)*GLCONST_CHAR::wLVL_2ndSKILL_P + dwGiftSkill;
	}
	else
	{
		m_dwSkillPoint = sCHARDATA.m_dwSkillPoint + (m_wLevel-1)*GLCONST_CHAR::wLVL_SKILL_P + dwGiftSkill;
	}

	//	Note : ��ų�� ����� ���� ���� ����.
	//
	m_wSKILLQUICK_ACT = 0;
	for ( int i=0; i<EMSKILLQUICK_SIZE; ++i )
	{
		m_sSKILLQUICK[i] = SNATIVEID(false);
	}


	//	Note : ������ ��ų �ʱ�ȭ.
	//

	m_ExpSkills.clear();
//	m_ExpSkills = sCHARDATA.m_ExpSkills;

	//	Note : ��� ��ġ�� �ٽ� �ʱ�ȭ �Ѵ�.
	//
	INIT_DATA(FALSE,FALSE);

	return true;
}

// *****************************************************
// Desc: �������� ����
// *****************************************************
bool GLCHARLOGIC::RESET_STATS ( const WORD wDIS )
{
	EMCHARINDEX emINDEX = CharClassToIndex(m_emClass);
	const SCHARDATA2& sCHARDATA = GLCONST_CHAR::GET_CHAR_DATA2(m_wSchool,emINDEX);

	// ��ü ���� ����Ʈ �ʱ�ȭ
	if ( wDIS==USHRT_MAX )
	{
		//	Note : ����Ʈ���� ȹ���� ���� ����Ʈ.
		//
		WORD wGiftStats(0);

		GLQuestPlay::MAPQUEST& sQuestEnd = m_cQuestPlay.GetQuestEnd();
		GLQuestPlay::MAPQUEST_ITER pos = sQuestEnd.begin();
		GLQuestPlay::MAPQUEST_ITER end = sQuestEnd.end();
		for ( ; pos!=end; ++pos )
		{
			GLQUESTPROG *pPROG = (*pos).second;
			GLQUEST *pQUEST = GLQuestMan::GetInstance().Find ( pPROG->m_sNID.dwID );
			if ( !pQUEST )	continue;

			wGiftStats += (WORD) pQUEST->m_dwGiftSTATSPOINT;
		}

		if( m_CHARINDEX == GLCI_EXTREME_M || m_CHARINDEX == GLCI_EXTREME_W )
		{
			m_wStatsPoint = sCHARDATA.m_wStatsPoint + (m_wLevel-1)*GLCONST_CHAR::wLVL_2ndSTATS_P + wGiftStats;
		}
		else
		{
			m_wStatsPoint = sCHARDATA.m_wStatsPoint + (m_wLevel-1)*GLCONST_CHAR::wLVL_STATS_P + wGiftStats;
		}

		m_sStats.RESET();

		return true;
	}

	// ������ ��޿� ���� �ʱ�ȭ
	WORD wNOW_DIS(0);
	while(1)
	{
		if ( wNOW_DIS>=wDIS )		break;
		if ( m_sStats.IsZERO() )	break;

		// �� ���ݺ��� �ϳ��� ����
		for ( int i=0; i<EMSIZE; ++i )
		{
			if ( wNOW_DIS>=wDIS )		break;
			if ( m_sStats.IsZERO() )	break;

			WORD &wSTAT = m_sStats.GET((EMSTATS)i);
			if ( wSTAT == 0 )			continue;

			--wSTAT;
			++wNOW_DIS;
		}
	}

	//	Note : ���� �ܿ� ���� ����Ʈ�� ����.
	m_wStatsPoint += wNOW_DIS;

	//	Note : ��� ��ġ�� �ٽ� �ʱ�ȭ �Ѵ�.
	//
	INIT_DATA(FALSE,FALSE);

	return true;
}

bool GLCHARLOGIC::RESET_STATS_SKILL ( const WORD wDIS_STAT )
{
	//	Note : ���� ȣ�� ������ stats, skill���̿��� �Ѵ�.
	RESET_STATS ( wDIS_STAT );
	RESET_SKILL();

	return true;
}

void GLCHARLOGIC::UPDATESKILLDELAY ( float fElapsedTime )
{
	DELAY_MAP_ITER iter_del;

	DELAY_MAP_ITER iter = m_SKILLDELAY.begin ();
	DELAY_MAP_ITER iter_end = m_SKILLDELAY.end ();

	for ( ; iter!=iter_end; )
	{
		float &fDelay = (*iter).second;
		iter_del = iter++;

		fDelay -= fElapsedTime;
		if ( fDelay <= 0.0f )	m_SKILLDELAY.erase ( iter_del );
	}
}

void GLCHARLOGIC::LEARN_SKILL ( SNATIVEID skill_id )
{
	//	Note : ��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )											return;

	//	Note : ����ġ ���ҽ�Ŵ.
	//
	SKILL::SLEARN_LVL &sSKILL_LEARN_LVL = pSkill->m_sLEARN.sLVL_STEP[0];
	if ( m_dwSkillPoint < sSKILL_LEARN_LVL.dwSKP )			return;

	//if ( m_lnMoney < sSKILL_LEARN_LVL.dwMoneyReq )			return;
	m_dwSkillPoint -= sSKILL_LEARN_LVL.dwSKP;

	//m_lnMoney -= sSKILL_LEARN_LVL.dwMoneyReq;
	//	Note : ��� ��ų�� �����.
	//
	m_ExpSkills.insert ( std::make_pair(skill_id.dwID,SCHARSKILL(skill_id,0)) );

	//	Note : ��ú� ��ų�� ��ȭ �Ҷ� �ʱ� ��ġ���� ��� �� ����Ѵ�.
	//
	if ( pSkill->m_sBASIC.emROLE == SKILL::EMROLE_PASSIVE )
	{
		INIT_DATA ( FALSE, FALSE );
	}
}

bool GLCHARLOGIC::LEARN_SKILL_QUEST ( SNATIVEID skill_id )
{
	//	Note : ��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )	return false;

	//	Note : ��� ��ų�� �����.
	//
	
	m_ExpSkills.insert ( std::make_pair(skill_id.dwID,SCHARSKILL(skill_id,0)) );
	//	Note : ��ú� ��ų�� ��ȭ �Ҷ� �ʱ� ��ġ���� ��� �� ����Ѵ�.
	//
	if ( pSkill->m_sBASIC.emROLE == SKILL::EMROLE_PASSIVE )
	{
		INIT_DATA ( FALSE, FALSE );
	}
	return true;
}

VOID GLCHARLOGIC::LVLUP_SKILL ( SNATIVEID skill_id, WORD wToLevel )
{
	//	Note : ��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )											return;

	SKILL_MAP_ITER learniter = m_ExpSkills.find ( skill_id.dwID );
	if ( learniter==m_ExpSkills.end() )						return;

	SCHARSKILL &sSkill = (*learniter).second;

	//	Note : ����ġ ���ҽ�Ŵ.
	//
	SKILL::SLEARN_LVL &sSKILL_LEARN_LVL = pSkill->m_sLEARN.sLVL_STEP[wToLevel];
	if ( m_dwSkillPoint < sSKILL_LEARN_LVL.dwSKP )			return;

//	if ( m_lnMoney < sSKILL_LEARN_LVL.dwMoneyReq )			return;
	m_dwSkillPoint -= sSKILL_LEARN_LVL.dwSKP;

//	m_lnMoney -= sSKILL_LEARN_LVL.dwMoneyReq;
	//	Note : ��ų ���� ��.
	//
	++sSkill.wLevel;

	//	Note : ��ú� ��ų�� ��ȭ �Ҷ� �ʱ� ��ġ���� ��� �� ����Ѵ�.
	//
	if ( pSkill->m_sBASIC.emROLE == SKILL::EMROLE_PASSIVE )
	{
		INIT_DATA ( FALSE, FALSE );
	}
}

BOOL GLCHARLOGIC::ISLEARNED_SKILL ( SNATIVEID skill_id, WORD wLEVEL )
{
	//	Note : ��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )											return FALSE;

	//	Note : ���� ��ų���� �˻�.
	//
	SKILL_MAP_ITER learniter = m_ExpSkills.find ( skill_id.dwID );
	if ( learniter==m_ExpSkills.end() )			return FALSE;

	SCHARSKILL &sSkill = (*learniter).second;
	if ( sSkill.wLevel <  wLEVEL )				return FALSE;

	return TRUE;
}

BOOL GLCHARLOGIC::ISMASTER_SKILL ( SNATIVEID skill_id )
{
	//	Note : ��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )												return FALSE;

	//	Note : ���� ��ų���� �˻�.
	//
	SKILL_MAP_ITER learniter = m_ExpSkills.find ( skill_id.dwID );
	if ( learniter==m_ExpSkills.end() )							return FALSE;

	SCHARSKILL &sSkill = (*learniter).second;

	if ( DWORD(sSkill.wLevel+1)>=SKILL::MAX_LEVEL )				return TRUE;
	if ( DWORD(sSkill.wLevel+1)>=pSkill->m_sBASIC.dwMAXLEVEL )	return TRUE;

	return FALSE;
}

SCHARSKILL* GLCHARLOGIC::GETLEARNED_SKILL ( SNATIVEID skill_id )
{
	//	Note : ���� ��ų���� �˻�.
	//
	SKILL_MAP_ITER learniter = m_ExpSkills.find ( skill_id.dwID );
	if ( learniter==m_ExpSkills.end() )			return NULL;

	return &((*learniter).second);
}

EMSKILL_LEARNCHECK GLCHARLOGIC::CHECKLEARNABLE_SKILL ( SNATIVEID skill_id )
{
	WORD wSKILL_LEVEL = 0;

	//	Note : ��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )								return EMSKILL_LEARN_UNKNOWN;

	//	Note : ���� ��ų���� �˻�.
	//
	SKILL_MAP_ITER learniter = m_ExpSkills.find ( skill_id.dwID );
	if ( learniter!=m_ExpSkills.end() )
	{
		SCHARSKILL &sSkill = (*learniter).second;
		wSKILL_LEVEL = sSkill.wLevel + 1;			//	���� ��ų LEVEL

		if ( wSKILL_LEVEL == SKILL::MAX_LEVEL )				return EMSKILL_LEARN_MAX;
		if ( wSKILL_LEVEL == pSkill->m_sBASIC.dwMAXLEVEL )	return EMSKILL_LEARN_MAX;
	}
	
	SKILL::SLEARN &sSKILL_LEARN = pSkill->m_sLEARN;
	SKILL::SLEARN_LVL &sSKILL_LEARN_LVL = pSkill->m_sLEARN.sLVL_STEP[wSKILL_LEVEL];

	//	Note : ��ų �������� �˻�.
	//
	if ( !(m_emClass&sSKILL_LEARN.dwCLASS) )					return EMSKILL_LEARN_NOTCLASS;
	
	if ( sSKILL_LEARN.emBRIGHT!=BRIGHT_BOTH )
	{
		if ( GETBRIGHT()!=sSKILL_LEARN.emBRIGHT )				return EMSKILL_LEARN_NOTBRIGHT;
	}

	if ( m_dwSkillPoint < sSKILL_LEARN_LVL.dwSKP )				return EMSKILL_LEARN_NOTTERM;
	if ( WORD(GETLEVEL()) < sSKILL_LEARN_LVL.dwLEVEL )			return EMSKILL_LEARN_NOTTERM;
	if ( !m_sSUMSTATS.CHECK_REQ ( sSKILL_LEARN_LVL.sSTATS ) )	return EMSKILL_LEARN_NOTTERM;

	//if ( m_lnMoney < sSKILL_LEARN_LVL.dwMoneyReq )				return EMSKILL_LEARN_NOTTERM;
	//	�䱸��ų ���� �˻�.
	if ( NATIVEID_NULL()!=sSKILL_LEARN.sSKILL )
	{
		if ( !ISLEARNED_SKILL(sSKILL_LEARN.sSKILL,WORD(sSKILL_LEARN_LVL.dwSKILL_LVL)) )	return EMSKILL_LEARN_NOTTERM;
	}

	return EMSKILL_LEARN_OK;
}

void GLCHARLOGIC::SETACTIVESKILL ( SNATIVEID skill_id )
{
	m_idACTIVESKILL = skill_id;
}

EMSKILLCHECK GLCHARLOGIC::CHECHSKILL ( SNATIVEID skill_id, WORD wStrikeNum, bool bNotLearn )
{
	/*prohibit skill logic, Juver, 2017/06/06 */
	/*pvp capture the flag, Juver, 2018/02/08 */
	if ( m_bProhibitSkill || m_bCaptureTheFlagHoldFlag )	return EMSKILL_PROHIBIT;

	//	Note : ���� ��ų���� �˻�.
	//
	SCHARSKILL sSkill;
	if ( bNotLearn )
	{
		if ( skill_id != m_sDefenseSkill.m_dwSkillID ) return EMSKILL_NOTLEARN;
		sSkill.sNativeID = skill_id;
		sSkill.wLevel = m_sDefenseSkill.m_wLevel;
	}
	else
	{
		SKILL_MAP_ITER learniter = m_ExpSkills.find ( skill_id.dwID );
		if ( learniter==m_ExpSkills.end() )										return EMSKILL_NOTLEARN; // ��� ��ų�� �ƴ� ���.
		sSkill = (*learniter).second;

		//	Note : ��ų ������ Ÿ���� �������� ����.
		//
		DELAY_MAP_ITER delayiter = m_SKILLDELAY.find ( skill_id.dwID );
		if ( delayiter!=m_SKILLDELAY.end() )									return EMSKILL_DELAYTIME; // ��ų ������ �ð��� ������ ����.
	}

	//	Note : ��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id );
	if ( !pSkill )															return EMSKILL_UNKNOWN;
	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[sSkill.wLevel];
	

	//	Note : ����� �� �ִ� ��ų�������� �˻�.
	if ( pSkill->m_sBASIC.emROLE!=SKILL::EMROLE_NORMAL )					return EMSKILL_UNKNOWN;

	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	//	Note : ��ų ���� �����ؾ� �ϴ� ������ ���� �˻�.
	//
	GLSKILL_ATT emSKILL_LITEM = pSkill->m_sBASIC.emUSE_LITEM;
	GLSKILL_ATT emSKILL_RITEM = pSkill->m_sBASIC.emUSE_RITEM;
	if ( emSKILL_LITEM!=SKILLATT_NOCARE )
	{
		SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
		if ( !pItem )														return EMSKILL_NOTITEM;

		if ( !CHECHSKILL_ITEM(emSKILL_LITEM,pItem->sSuitOp.emAttack) )		return EMSKILL_NOTITEM;
	}

	if ( emSKILL_RITEM!=SKILLATT_NOCARE )
	{
		SITEM* pItem = GET_SLOT_ITEMDATA(emRHand);
		if ( !pItem )														return EMSKILL_NOTITEM;
		
		if ( !CHECHSKILL_ITEM(emSKILL_RITEM,pItem->sSuitOp.emAttack) )		return EMSKILL_NOTITEM;
	}

	//	Note : ȭ�� �Ҹ�� �Ҹ� ���� üũ.
	//		--> �Ҹ��� 2 ���δ� �Ѱ��� �����ִ� ��Ȳ? ���� ���� ���ڸ� �����ϰ� ��ų�� �ߵ��ǰ� ����.
	//
	if ( sSKILL_DATA.wUSE_ARROWNUM!=0 )
	{
		SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
		if ( !pItem )														return EMSKILL_NOTARROW;

		if ( pItem->sBasicOp.emItemType != ITEM_ARROW )						return EMSKILL_NOTARROW;

		//	������ �������� �ʴ´�. ���ڶ� ��� �ִ°� �ѵ������� �Ҹ��Ŵ.
	}

	//	Note : ���� �Ҹ�� �Ҹ� ���� üũ.
	//		--> �Ҹ��� 2 ���δ� �Ѱ��� �����ִ� ��Ȳ? ���� ���� ���ڸ� �����ϰ� ��ų�� �ߵ��ǰ� ����.
	//
	if ( sSKILL_DATA.wUSE_CHARMNUM!=0 )
	{
		SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
		if ( !pItem )														return EMSKILL_NOTCHARM;

		if ( pItem->sBasicOp.emItemType != ITEM_CHARM )						return EMSKILL_NOTCHARM;

		//	������ �������� �ʴ´�. ���ڶ� ��� �ִ°� �ѵ������� �Ҹ��Ŵ.
	}

	/*gun-bullet logic, Juver, 2017/05/27 */
	if ( sSKILL_DATA.wUSE_BULLETNUM!=0 )
	{
		SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
		if ( !pItem )														return EMSKILL_NOTBULLET;

		if ( pItem->sBasicOp.emItemType != ITEM_BULLET )					return EMSKILL_NOTBULLET;
	}

	//	Note : ���� ü�� �Ҹ� ����.
	if ( m_sHP.wNow <= sSKILL_DATA.wUSE_HP*wStrikeNum )						return EMSKILL_NOTHP;
	if ( m_sMP.wNow < sSKILL_DATA.wUSE_MP*wStrikeNum )						return EMSKILL_NOTMP;

	//if ( m_sExperience.lnNow < sSKILL_DATA.wUSE_EXP*wStrikeNum )			return EMSKILL_NOTEXP;

	//	NEED : ���� ��Ƽ��ų�� �����Ǿ�����.
	//
	//sSKILL_DATA.wUSE_HP_PTY;
	//sSKILL_DATA.wUSE_MP_PTY;


	SITEM* pRHAND = GET_SLOT_ITEMDATA ( emRHand );
	SITEM* pLHAND = GET_SLOT_ITEMDATA ( emLHand );

	WORD wDisSP = sSKILL_DATA.wUSE_SP;
	if ( pRHAND )	wDisSP += pRHAND->sSuitOp.wReqSP;
	if ( pLHAND )	wDisSP += pLHAND->sSuitOp.wReqSP;

	if ( m_sSP.wNow < wDisSP*wStrikeNum )									return EMSKILL_NOTSP;

	/*combatpoint logic, Juver, 2017/05/28 */
	if ( m_sCombatPoint.wNow < sSKILL_DATA.wUSE_CP*wStrikeNum )				return EMSKILL_NOTCP;

	//	NEED : ���� ��Ƽ��ų�� �����Ǿ�����.
	//
	//sSKILL_DATA.wUSE_SP_PTY;

	return EMSKILL_OK;
}

void GLCHARLOGIC::ACCOUNTSKILL ( SNATIVEID skill_id, WORD wStrikeNum, bool bServer )
{
	//	Note : ĳ���Ͱ� ��� ��ų ���� ������.
	// �ߵ���ų�� ��ų ��Ͽ� ����
	SCHARSKILL sSkill;

	if ( IsDefenseSkill() )
	{
		if ( skill_id != m_sDefenseSkill.m_dwSkillID ) return;
		sSkill.sNativeID = skill_id;
		sSkill.wLevel = m_sDefenseSkill.m_wLevel;
	}
	else
	{
		SKILL_MAP_ITER learniter = m_ExpSkills.find ( skill_id.dwID );
		if( learniter==m_ExpSkills.end() )										return;	// ��� ��ų�� �ƴ� ���.
		sSkill = (*learniter).second;
	}

	//	��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )															return;
	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[sSkill.wLevel];


	//	��ų ������ ���.
	float fDelayTime = GLOGICEX::SKILLDELAY(pSkill->m_sBASIC.dwGRADE,sSkill.wLevel,GETLEVEL(),sSKILL_DATA.fDELAYTIME);
	
	//	Note : �����̻��� ������ ����.
	fDelayTime = fDelayTime * m_fSTATE_DELAY;

	//	Note : ���������� �޽��� ������ ��ŭ ���ҽ��� �ش�.
	if ( bServer )		APPLY_MSGDELAY ( fDelayTime );

	m_SKILLDELAY.insert ( std::make_pair(skill_id.dwID,fDelayTime) );

	EMSLOT emLHand = GetCurLHand();

	//	ȭ�� �Ҹ�.
	if ( sSKILL_DATA.wUSE_ARROWNUM!= 0 )
	{
		SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
		if ( pItem )
		{
			//	ȭ�� �Ҹ��ϴ� ��ų������ ȭ������ �ݵ�� �־�� ������ ������ �������� ���� ������ ����.
			//	ȭ�� ���� ������ �������� �ʴ´�.
			WORD &wTurnNum = m_PutOnItems[emLHand].wTurnNum;
			if ( wTurnNum >= sSKILL_DATA.wUSE_ARROWNUM )	wTurnNum -= sSKILL_DATA.wUSE_ARROWNUM;
			else											wTurnNum = 0;
		}
	}

	//	���� �Ҹ�.
	if ( sSKILL_DATA.wUSE_CHARMNUM!= 0 )
	{
		SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
		if ( pItem )
		{
			//	���� �Ҹ��ϴ� ��ų������ ȭ������ �ݵ�� �־�� ������ ������ �������� ���� ������ ����.
			//	���� ���� ������ �������� �ʴ´�.
			WORD &wTurnNum = m_PutOnItems[emLHand].wTurnNum;
			if ( wTurnNum >= sSKILL_DATA.wUSE_CHARMNUM )	wTurnNum -= sSKILL_DATA.wUSE_CHARMNUM;
			else											wTurnNum = 0;
		}
	}

	/*gun-bullet logic, Juver, 2017/05/27 */
	if ( sSKILL_DATA.wUSE_BULLETNUM!= 0 )
	{
		SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
		if ( pItem )
		{
			WORD &wTurnNum = m_PutOnItems[emLHand].wTurnNum;
			if ( wTurnNum >= sSKILL_DATA.wUSE_BULLETNUM )	wTurnNum -= sSKILL_DATA.wUSE_BULLETNUM;
			else											wTurnNum = 0;
		}
	}

	//	���� ü�� �Ҹ�.
	m_sHP.DECREASE ( sSKILL_DATA.wUSE_HP*wStrikeNum );
	m_sMP.DECREASE ( sSKILL_DATA.wUSE_MP*wStrikeNum );

	/*combatpoint logic, Juver, 2017/05/28 */
	m_sCombatPoint.DECREASE ( sSKILL_DATA.wUSE_CP*wStrikeNum );

	//m_sExperience.DECREASE ( sSKILL_DATA.wUSE_EXP*wStrikeNum );
}


BOOL GLCHARLOGIC::DOGRINDING(	SITEMCUSTOM &sCusItem, 
								const SITEM *pHold, 
								bool &_bRESET, 
								bool &_bTERMINATE, 
								EMANTIDISAPPEAR &emANTIDISAPPEAR )
{
	bool bSUCCEED(false);
	_bRESET = false;
	_bTERMINATE = false;

	const EMGRINDING_TYPE emGRINDING = pHold->sGrindingOp.emTYPE;

	BYTE cGRADE = sCusItem.GETGRADE ( emGRINDING );
	
	if ( emGRINDING == EMGRINDING_DAMAGE || emGRINDING == EMGRINDING_DEFENSE )
	{
		if ( cGRADE >= GLCONST_CHAR::wGRADE_MAX )	return FALSE;
	}
	else
	{
		if ( cGRADE >= GLCONST_CHAR::wGRADE_MAX_REGI )	return FALSE;
	}
	
	
	/*no fail upgrade, Juver, 2017/11/26 */
	if ( pHold->sGrindingOp.bNoFail )
	{
		_bRESET = false;
		_bTERMINATE = false;
		emANTIDISAPPEAR = EMANTIDISAPPEAR_OFF;
	}
	else
	{
		//	4�ܰ� �̻���� ���� Ȯ�� ����.
		if ( cGRADE >= GRADE_NORMAL )
		{
			//	���� Ȯ��.
			float fRATE = GLCONST_CHAR::fGRADE_RATE[cGRADE];
			BOOL bOK = RANDOM_GEN ( fRATE );
			if ( !bOK )
			{
				//	���� Ȯ��.
				float fRESET = GLCONST_CHAR::fGRADE_RESET_RATE[cGRADE];
				bOK = RANDOM_GEN ( fRESET );
				if ( bOK )
				{
					_bRESET = true;
					sCusItem.ResetGrind(emGRINDING);

					//	�ļ� Ȯ��.
					bool bTER = GLCONST_CHAR::bENCHANT_TERMINATE_ITEM && ( emGRINDING==EMGRINDING_DAMAGE || emGRINDING==EMGRINDING_DEFENSE );
					if ( bTER )
					{
						float fTERMINATE = GLCONST_CHAR::fGRADE_TERMINATE_RATE[cGRADE];
						bOK = RANDOM_GEN ( fTERMINATE );
						if ( bOK )
						{
							// �ҹ��ָ� ������ �ִٸ�
							if( emANTIDISAPPEAR == EMANTIDISAPPEAR_ON )
							{
								emANTIDISAPPEAR = EMANTIDISAPPEAR_USE; // �ҹ��ָ� ����ߴ�.
							}
							else
							{
								_bTERMINATE = true;		// �������� �Ҹ�Ǿ���.
							}
						}
					}
				}

				return FALSE;
			}
		}
	}

	

	//	Note : ������ ����.
	//
	switch ( pHold->sGrindingOp.emTYPE )
	{
	case EMGRINDING_DAMAGE:			sCusItem.cDAMAGE++;			break;
	case EMGRINDING_DEFENSE:		sCusItem.cDEFENSE++;		break;
	case EMGRINDING_RESIST_FIRE:	sCusItem.cRESIST_FIRE++;	break;
	case EMGRINDING_RESIST_ICE:		sCusItem.cRESIST_ICE++;		break;
	case EMGRINDING_RESIST_ELEC:	sCusItem.cRESIST_ELEC++;	break;
	case EMGRINDING_RESIST_POISON:	sCusItem.cRESIST_POISON++;	break;
	case EMGRINDING_RESIST_SPIRIT:	sCusItem.cRESIST_SPIRIT++;	break;
	};

	return TRUE;
}

//	Note : �ɸ��Ͱ� �������� �����ϰ� �ִ��� �˻�.
//		���뺹��, �κ��丮���� �˻�.
//		��ħ���� �������� ��� full �� ���� ��츸 ������ ������ �Ǵ�.
//
BOOL GLCHARLOGIC::ISHAVEITEM ( SNATIVEID &sNID, DWORD *pNum )
{
	DWORD dwNum = 0;
	for ( int i=0; i<SLOT_TSIZE; ++i )
	{
		const SITEM* pITEM = GET_SLOT_ITEMDATA ( EMSLOT(i) );
		if ( !pITEM )								continue;

		const SITEMCUSTOM &sCUSTOM = GET_SLOT_ITEM ( EMSLOT(i) );
		if ( sCUSTOM.sNativeID==SNATIVEID(false) )	continue;

		if ( pITEM->sBasicOp.sNativeID==sNID )
		{
			if ( pITEM->sDrugOp.wPileNum == 1 )						dwNum++;
			else if ( pITEM->sDrugOp.wPileNum == sCUSTOM.wTurnNum )	dwNum++;
		}
	}

	dwNum += m_cInventory.CountPileItem ( sNID );

	if ( pNum )		*pNum = dwNum;
	return ( dwNum > 0 );
}

BOOL GLCHARLOGIC::ISREVIVE ()
{
	SITEM* pITEM = GET_SLOT_ITEMDATA(SLOT_NECK);
	if ( !pITEM )											return FALSE;
	if ( pITEM->sDrugOp.emDrug!=ITEM_DRUG_CALL_REVIVE )		return FALSE;

	return TRUE;
}

/*skill range spec logic, Juver, 2017/06/06 */
WORD GLCHARLOGIC::GETSKILLRANGE_TAR ( const GLSKILL &sSKILL ) const
{
	int nRANGE = sSKILL.m_sBASIC.wTARRANGE;
	if ( sSKILL.m_sBASIC.emAPPLY==SKILL::EMAPPLY_PHY_LONG )		nRANGE += (int) GETSUM_TARRANGE();

	if ( sSKILL.m_sBASIC.emIMPACT_SIDE == SIDE_ENEMY )	
		nRANGE += (int) ( m_fSUM_SKILL_ATTACKRANGE + m_sSUM_PASSIVE.m_fSUM_SKILL_ATTACKRANGE );

	if ( nRANGE <= 0 ) nRANGE = 1;

	return (WORD)nRANGE;
}

/*skill range spec logic, Juver, 2017/06/06 */
WORD GLCHARLOGIC::GETSKILLRANGE_APPLY ( const GLSKILL &sSKILL, const WORD dwLEVEL ) const
{
	const SKILL::CDATA_LVL &sDATA_LVL = sSKILL.m_sAPPLY.sDATA_LVL[dwLEVEL];

	int nRANGE = sDATA_LVL.wAPPLYRANGE;
	if ( sSKILL.m_sBASIC.emAPPLY==SKILL::EMAPPLY_PHY_LONG )		nRANGE += (int) GETSUM_TARRANGE();

	if ( sSKILL.m_sBASIC.emIMPACT_SIDE == SIDE_ENEMY )	
		nRANGE += (int) ( m_fSUM_SKILL_APPLYRANGE + m_sSUM_PASSIVE.m_fSUM_SKILL_APPLYRANGE );

	if ( nRANGE <= 0 ) nRANGE = 1;

	return (WORD)nRANGE;
}

//	Note : ���� pk ������ �˾ƺ���. ( UINT_MAX �ϰ�� pk �ش���� ����. )
DWORD GLCHARLOGIC::GET_PK_LEVEL ()
{
	if ( m_nBright >= 0 )	return UINT_MAX;

	DWORD dwLEVEL = 0;
	for ( dwLEVEL=0; dwLEVEL<GLCONST_CHAR::EMPK_STATE_LEVEL; ++dwLEVEL )
	{
		if ( GLCONST_CHAR::sPK_STATE[dwLEVEL].nPKPOINT <= m_nBright )		break;
	}

	if ( dwLEVEL>=GLCONST_CHAR::EMPK_STATE_LEVEL )	dwLEVEL = GLCONST_CHAR::EMPK_STATE_LEVEL-1;

	return dwLEVEL;
}


float GLCHARLOGIC::GET_PK_DECEXP_RATE ()
{
	DWORD dwLEVEL = GET_PK_LEVEL();
	if ( dwLEVEL==UINT_MAX )	return 100.0f;

	return GLCONST_CHAR::sPK_STATE[dwLEVEL].fPK_EXP_RATE;
}

std::string GLCHARLOGIC::GET_PK_NAME ()
{
	DWORD dwLEVEL = GET_PK_LEVEL();
	if ( dwLEVEL==UINT_MAX )	return GLCONST_CHAR::sPK_STATE[0].strNAME;

	return GLCONST_CHAR::sPK_STATE[dwLEVEL].strNAME;
}

DWORD GLCHARLOGIC::GET_PK_COLOR ()
{
	DWORD dwLEVEL = GET_PK_LEVEL();
	if ( dwLEVEL==UINT_MAX )	return GLCONST_CHAR::dwPK_NORMAL_NAME_COLOR;

	return GLCONST_CHAR::sPK_STATE[dwLEVEL].dwNAME_COLOR;
}

float GLCHARLOGIC::GET_PK_SHOP2BUY ()
{
	DWORD dwLEVEL = GET_PK_LEVEL();
	if ( dwLEVEL==UINT_MAX )	return 100.0f;

	return GLCONST_CHAR::sPK_STATE[dwLEVEL].fSHOP_2BUY_RATE;
}

float GLCHARLOGIC::GET_PK_SHOP2SALE ()
{
	DWORD dwLEVEL = GET_PK_LEVEL();
	if ( dwLEVEL==UINT_MAX )	return 100.0f;

	return GLCONST_CHAR::sPK_STATE[dwLEVEL].fSHOP_2SALE_RATE;
}

DWORD GLCHARLOGIC::GET_PK_ITEMDROP_NUM ()
{
	DWORD dwLEVEL = GET_PK_LEVEL();
	if ( dwLEVEL==UINT_MAX )
	{
		if ( GLCONST_CHAR::fPK_ITEM_DROP==0 )	return 0;
		return 1;
	}

	return GLCONST_CHAR::sPK_STATE[dwLEVEL].dwITEM_DROP_NUM;
}

float GLCHARLOGIC::GET_PK_ITEMDROP_RATE ()
{
	DWORD dwLEVEL = GET_PK_LEVEL();
	float fRATE = 0;

	if ( dwLEVEL==UINT_MAX )						fRATE = GLCONST_CHAR::fPK_ITEM_DROP;
	else											fRATE = GLCONST_CHAR::sPK_STATE[dwLEVEL].fITEM_DROP_RATE;

	if ( GLSchoolFreePK::GetInstance().IsON() )		fRATE += GLCONST_CHAR::fSCHOOL_FREE_PK_ITEM_DROP;

	return fRATE;
}

bool GLCHARLOGIC::ISPLAYKILLING ()
{
	return !m_mapPlayHostile.empty();
}

//	Note : �ڽ��� �������ΰ�?
bool GLCHARLOGIC::ISOFFENDER ()
{
	return ( m_nBright < GLCONST_CHAR::sPK_STATE[0].nPKPOINT );
}

bool GLCHARLOGIC::IS_HOSTILE_ACTOR ( DWORD dwCHARID )
{
	MAPPLAYHOSTILE_ITER pos = m_mapPlayHostile.find ( dwCHARID );
	if ( pos!=m_mapPlayHostile.end() )
	{
		if( pos->second )
			return ( pos->second->bBAD == TRUE );
		else
			CDebugSet::ToLogFile( "GLCHARLOGIC::IS_HOSTILE_ACTOR, pos->second = NULL" );
	}

	return false;
}

//	Note : ������ ���. ( pk ���� ),	true : �ű� ��Ͻ�, false : ���� ��� ���Ž�.
bool GLCHARLOGIC::ADD_PLAYHOSTILE ( DWORD dwCHARID, BOOL bBAD )
{
	if ( m_dwCharID == dwCHARID )
	{
		CDebugSet::ToLogFile( "GLCHARLOGIC::ADD_PLAYHOSTILE, m_dwCharID == dwCHARID" );
		return false;
	}

	bool bResult = true;

	MAPPLAYHOSTILE_ITER pos = m_mapPlayHostile.find ( dwCHARID );
	// �̹� ��ϵǾ� ������...
	if ( pos!=m_mapPlayHostile.end() )
	{
		bResult = false;

		//	Note : �ð��� ����. ���� bBAD�� �������� ����. ( ó�� �������� �� ����. )
		if( pos->second )
		{
			pos->second->fTIME = GLCONST_CHAR::fPK_JUSTNESS_TIME;
			return false;
		}
		else
		{
			// �̹� ��ϵǾ� �־����� ���� ��ȿ���� �ʾƼ� �����Ѵ�.
			CDebugSet::ToLogFile ("GLCHARLOGIC::ADD_PLAYHOSTILE, pos->second = NULL");
			m_mapPlayHostile.erase (pos);
		}
	}

	// ��ϵǾ� ���� �ʰų� ��ȿ���� ���� ���̾��� ������
	// �űԷ� ����Ѵ�.
	SPLAYHOSTILE* pHOSTILE = new SPLAYHOSTILE;
	pHOSTILE->bBAD = bBAD;
	pHOSTILE->fTIME = GLCONST_CHAR::fPK_JUSTNESS_TIME;
	m_mapPlayHostile.insert ( std::make_pair( dwCHARID, pHOSTILE ) );

	return bResult;
}

bool GLCHARLOGIC::DEL_PLAYHOSTILE ( DWORD dwCHARID )
{
	MAPPLAYHOSTILE_ITER pos = m_mapPlayHostile.find ( dwCHARID );
	if ( pos!=m_mapPlayHostile.end() )
	{
		SAFE_DELETE( pos->second );
		m_mapPlayHostile.erase ( pos );
		return true;
	}
	else
	{	
		return false;
	}
}

void GLCHARLOGIC::DEL_PLAYHOSTILE_ALL ()
{
	for( MAPPLAYHOSTILE_ITER ci = m_mapPlayHostile.begin(); ci != m_mapPlayHostile.end(); ++ci )
		SAFE_DELETE( ci->second );
	m_mapPlayHostile.clear();
}

bool GLCHARLOGIC::IS_PLAYHOSTILE ( DWORD dwCHARID )
{
	MAPPLAYHOSTILE_ITER pos = m_mapPlayHostile.find ( dwCHARID );
	return ( pos != m_mapPlayHostile.end() );
}

EMSLOT GLCHARLOGIC::GetCurRHand()
{
	if( IsUseArmSub() ) return SLOT_RHAND_S;
	else				return SLOT_RHAND;
}

EMSLOT GLCHARLOGIC::GetCurLHand()
{
	if( IsUseArmSub() ) return SLOT_LHAND_S;
	else				return SLOT_LHAND;
}

BOOL GLCHARLOGIC::VALID_SLOT_ITEM ( EMSLOT _slot )							
{ 
	if( m_PutOnItems[_slot].sNativeID==NATIVEID_NULL() ) return FALSE;

	if( IsUseArmSub() )
	{
		if( _slot == SLOT_RHAND || _slot == SLOT_LHAND ) return FALSE;
	}
	else
	{
		if( _slot == SLOT_RHAND_S || _slot == SLOT_LHAND_S ) return FALSE;
	}

	return TRUE;
}

BOOL GLCHARLOGIC::ISLONGRANGE_ARMS ()							
{
	EMSLOT emRHand = GetCurRHand();
	return m_pITEMS[emRHand] && ( m_pITEMS[emRHand]->sSuitOp.emAttack>ITEMATT_NEAR ); 
}

BOOL GLCHARLOGIC::IsCurUseArm( EMSLOT emSlot )
{
	if( IsUseArmSub() )
	{
		if( emSlot == SLOT_RHAND || emSlot == SLOT_LHAND ) return FALSE;
	}
	else
	{
		if( emSlot == SLOT_RHAND_S || emSlot == SLOT_LHAND_S ) return FALSE;
	}

	return TRUE;
}


void GLCHARLOGIC::DISABLEALLLANDEFF()
{
	for( int i = 0; i < EMLANDEFFECT_MULTI; i++ )
	{
		m_sLandEffect[i].Init();
	}
}

void GLCHARLOGIC::ADDLANDEFF( SLANDEFFECT landEffect, int iNum )
{
	if( iNum >= EMLANDEFFECT_MULTI ) return;
	m_sLandEffect[iNum] = landEffect;
}

/*continuous damage skill logic, Juver, 2017/06/10 */
BOOL GLCHARLOGIC::CONTINUOUSDAMAGE_EXIST( SNATIVEID _sID )
{
	if( m_mapContinuousDamage.empty() )	return FALSE;
	if( _sID == NATIVEID_NULL() )		return FALSE;

	CONTINUOUS_DAMAGE_DATA_MAP_ITER iter = m_mapContinuousDamage.find(_sID.dwID);
	if ( iter != m_mapContinuousDamage.end() )	return TRUE;
	
	return FALSE;
}

/*continuous damage skill logic, Juver, 2017/06/10 */
void GLCHARLOGIC::CONTINUOUSDAMAGE_INSERT( SCONTINUOUS_DAMAGE_DATA _sDATA )
{
	if ( !_sDATA.Valid() )	return;

	m_mapContinuousDamage.insert( std::make_pair( _sDATA.sidSkill.dwID, _sDATA ) );
}

/*continuous damage skill logic, Juver, 2017/06/10 */
void GLCHARLOGIC::CONTINUOUSDAMAGE_DELETE( SNATIVEID _sID )
{
	if( m_mapContinuousDamage.empty() )	return;
	if( _sID == NATIVEID_NULL() )		return;

	CONTINUOUS_DAMAGE_DATA_MAP_ITER iter = m_mapContinuousDamage.find(_sID.dwID);
	if ( iter != m_mapContinuousDamage.end() )
		m_mapContinuousDamage.erase( iter );
}

BOOL GLCHARLOGIC::RECEIVE_PKCOMBO ( int nCount )
{
	m_sPKCOMBOCOUNT.bShow = true;
	m_sPKCOMBOCOUNT.fTime = GLCONST_CHAR::fPKCOMBO_RANGE_TIME;
	m_sPKCOMBOCOUNT.nCount += nCount;

	return TRUE;
}

bool GLCHARLOGIC::UPDATE_PKCOMBO ( float fElapsedTime )
{
	if ( !m_sPKCOMBOCOUNT.IsACTIVE() )		return true;

	m_sPKCOMBOCOUNT.fTime -= fElapsedTime;
	if ( m_sPKCOMBOCOUNT.fTime <= 0 )
	{
		m_sPKCOMBOCOUNT.RESET();
		return false;
	}

	return true;
}
/*npc talk buff condition, Juver, 2017/10/03 */
BOOL GLCHARLOGIC::ISHAVE_BUFF( SNATIVEID skill_id, WORD wLEVEL/*=1*/ )
{
	//level range 1~9
	if ( wLEVEL == 0 )	return FALSE;
	if ( wLEVEL > SKILL::MAX_LEVEL )	return FALSE;

	//range in buff data 0~8
	WORD wLevel = wLEVEL -1;

	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )	return FALSE;

	//check buffs
	for( int i=0; i<SKILLFACT_SIZE; ++i )
	{
		const SSKILLFACT& skill_fact = m_sSKILLFACT[i];
		if ( skill_fact.sNATIVEID == NATIVEID_NULL() ) 
			continue;

		if ( skill_fact.sNATIVEID == skill_id && skill_fact.wLEVEL >= wLevel )	
			return TRUE;
	}

	//check item food
	for( int i=0; i<FITEMFACT_SIZE; ++i )
	{
		const SFITEMFACT& fitem_fact = m_sFITEMFACT[i];
		if ( fitem_fact.sNATIVEID == NATIVEID_NULL() ) 
			continue;

		/*if ( !fitem_fact.bENABLE ) 
			continue;*/

		if ( fitem_fact.sNATIVEID == skill_id && fitem_fact.wLEVEL >= wLevel )	
			return TRUE;
	}

	//check system buffs
	for( int i=0; i<SYSTEM_BUFF_SIZE; ++i )
	{
		const SSYSTEM_BUFF& system_buff = m_sSYSTEM_BUFF[i];
		if ( system_buff.sNATIVEID == NATIVEID_NULL() ) 
			continue;

		if ( system_buff.sNATIVEID == skill_id && system_buff.wLEVEL >= wLevel )	
			return TRUE;
	}

	return FALSE;
}

/*activity system, Juver, 2017/10/30 */
SACTIVITY_CHAR_DATA* GLCHARLOGIC::GetActivityProg( DWORD dwActivityID )
{
	if ( dwActivityID == UINT_MAX )	return NULL;

	SACTIVITY_CHAR_DATA_MAP_ITER iter = m_mapActivityProg.find( dwActivityID );
	if ( iter != m_mapActivityProg.end() )
	{
		return &(*iter).second;
	}

	return NULL;
}

/*activity system, Juver, 2017/10/30 */
SACTIVITY_CHAR_DATA* GLCHARLOGIC::GetActivityDone( DWORD dwActivityID )
{
	if ( dwActivityID == UINT_MAX )	return NULL;

	SACTIVITY_CHAR_DATA_MAP_ITER iter = m_mapActivityDone.find( dwActivityID );
	if ( iter != m_mapActivityDone.end() )
	{
		return &(*iter).second;
	}

	return NULL;
}

/*activity system, Juver, 2017/10/30 */
DWORD GLCHARLOGIC::GetActivityProgNum()
{
	return DWORD( m_mapActivityProg.size() );
}

/*activity system, Juver, 2017/10/30 */
DWORD GLCHARLOGIC::GetActivityDoneNum()
{
	return DWORD( m_mapActivityDone.size() );
}