#include "StdAfx.h"
#include "GLPetClient.h"
#include "GLGaeaClient.h"

#include "GLContrlMsg.h"
#include "DxGlobalStage.h"

#include "GLItemMan.h"

#include "../Lib_ClientUI/Interface/InnerInterface.h"
#include "../Lib_ClientUI/Interface/UITextcontrol.h"
#include "../Lib_ClientUI/Interface/GameTextcontrol.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::StartSkillProc_A ()
{
	//	��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_sActiveSkillID_A );
	if ( !pSkill )	return;

	// �� ��ų���� �Լ����� �޽����� �߼��ϰ� ȸ���� ������
	// ��ų �ߵ�...
	switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
	{
	case SKILL::EMFOR_PET_GETALLITEMS:		GetAllItems_A ();	break;
	case SKILL::EMFOR_PET_GETRAREITEMS:		GetRareItems_A ();	break;
	case SKILL::EMFOR_PET_GETPOTIONS:		GetPotions_A ();	break;
	case SKILL::EMFOR_PET_GETSTONE:			GetStone_A ();		break;
	case SKILL::EMFOR_PET_GETMONEY:			GetMoney_A ();		break;
	case SKILL::EMFOR_PET_HEAL:
	case SKILL::EMFOR_PET_SUPPROT:
	case SKILL::EMFOR_PET_BACKUP_ATK:
	case SKILL::EMFOR_PET_BACKUP_DEF:
		{
		}
		break;
	case SKILL::EMFOR_PET_AUTOMEDISON:
		break;
	case SKILL::EMFOR_PET_PROTECTITEMS:
		// ������ �������°��� �����ش�.
		break;

	default: break;
	};

	m_bSkillProcessing_A = true;

	//AccountSkill ( m_sActiveSkillID );
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::StartSkillProc_B ()
{
	//	��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_sActiveSkillID_B );
	if ( !pSkill )	return;

	// �� ��ų���� �Լ����� �޽����� �߼��ϰ� ȸ���� ������
	// ��ų �ߵ�...
	switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
	{
	case SKILL::EMFOR_PET_GETALLITEMS:		GetAllItems_B ();	break;
	case SKILL::EMFOR_PET_GETRAREITEMS:		GetRareItems_B ();	break;
	case SKILL::EMFOR_PET_GETPOTIONS:		GetPotions_B ();	break;
	case SKILL::EMFOR_PET_GETSTONE:			GetStone_B ();		break;
	case SKILL::EMFOR_PET_GETMONEY:			GetMoney_B ();		break;
	case SKILL::EMFOR_PET_HEAL:
	case SKILL::EMFOR_PET_SUPPROT:
	case SKILL::EMFOR_PET_BACKUP_ATK:
	case SKILL::EMFOR_PET_BACKUP_DEF:
		{
		}
		break;
	case SKILL::EMFOR_PET_AUTOMEDISON:
		break;
	case SKILL::EMFOR_PET_PROTECTITEMS:
		// ������ �������°��� �����ش�.
		break;

	default: break;
	};

	m_bSkillProcessing_B = true;

	//AccountSkill ( m_sActiveSkillID );
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::ProceedSkill_A ()
{
	// ��ų�� ����������?
	if ( !m_bSkillProcessing_A ) return;

	//	��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_sActiveSkillID_A );
	if ( !pSkill )	return;

	switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
	{
		// �������� �ݴ� ��ų�̸�
	case SKILL::EMFOR_PET_GETALLITEMS:
	case SKILL::EMFOR_PET_GETRAREITEMS:
	case SKILL::EMFOR_PET_GETPOTIONS:
	case SKILL::EMFOR_PET_GETSTONE:
	case SKILL::EMFOR_PET_GETMONEY:
		{
			// �ֺ��� �������� ������ �޷�����.
			if ( !IsSTATE(EM_PETACT_RUN_PICKUP_ITEM) )
			{
				if ( !m_vecDroppedItems_A.empty() )
				{
					// �ϳ� ������
					m_sSkillTARGET = m_vecDroppedItems_A.back();
					m_vecDroppedItems_A.pop_back ();

					// �������� �κ��� ���� �� �ִ��� �˻�
					EM_FIELDITEM_STATE emResult = IsInsertableInven ( m_sSkillTARGET );

					switch ( emResult )
					{
						// ��Ʈ��ũ �����̷� �������� �ʴ� �������� ��� �õ��Ұ��
					case EM_FIELDITEM_STATE_REMOVED:
						break;

						// �κ��丮 ���� ����
					case EM_FIELDITEM_STATE_INSERTFAIL:
						{
							m_sSkillTARGET.RESET ();
							ReqChangeActiveSkill_A ( NATIVEID_NULL() ); // ��ų�� ����ع�����.
							m_vecDroppedItems_A.clear();
							CInnerInterface::GetInstance().PrintConsoleTextDlg( ID2GAMEINTEXT("EMPET_NOTENOUGHINVEN") );
						}
						break;;
						// �κ��丮 ���� ����
					case EM_FIELDITEM_STATE_INSERTOK:
						{
							D3DXVECTOR3 vDist, vDir, vTar;
							vDist = m_sSkillTARGET.vPos - m_vPos;
							D3DXVec3Normalize ( &vDir, &vDist );
							float fDist = D3DXVec3Length ( &vDist ) - 10.0f; // �ݱ� ������ �Ÿ���ŭ �Ÿ� ����
							vTar = vDir * fDist;
							vTar = m_vPos + vTar;
							ReqGoto ( vTar, true );
						}
						break;
						// �Ϲ� ������ ���
					case EM_FIELDITEM_STATE_GENERALFAIL:
						{
						}
						break;
					}
				}
				// ���� ������ ������ ������ ��û�Ѵ�.
				else 
				{
					GetItembySkill_A ( m_sActiveSkillID_A ); 
				}
			}
		}
		break;

		// ������ ��ų���� ������ ���¸� �������ش�.
	case SKILL::EMFOR_PET_HEAL:
	case SKILL::EMFOR_PET_SUPPROT:
	case SKILL::EMFOR_PET_BACKUP_ATK:
	case SKILL::EMFOR_PET_BACKUP_DEF:
		{
		}
		break;

		// ţ���Կ� ������ �Ծ��ش�. (�������ӿ� �ѹ��� ���� �Ծ��ش�!)
	case SKILL::EMFOR_PET_AUTOMEDISON:
		{
			DWORD dwMaxOwnersHP = m_pOwner->GETMAXHP ();
			DWORD dwMaxOwnersMP = m_pOwner->GETMAXMP ();
			DWORD dwMaxOwnersSP = m_pOwner->GETMAXSP ();
			DWORD dwHPVar = dwMaxOwnersHP - m_pOwner->GETHP ();
			int   nMPVar  = dwMaxOwnersMP - m_pOwner->GETMP ();
			int   nSPVar  = dwMaxOwnersSP - m_pOwner->GETSP ();

			// Q, W, E, A, S, D
			for ( WORD wSLOT = 0; wSLOT < EMACTIONQUICK_SIZE; ++wSLOT )
			{
				const SACTION_SLOT &sACTION = m_pOwner->m_sACTIONQUICK[wSLOT];
				if ( !sACTION.VALID() )	continue;

				switch ( sACTION.wACT )
				{
				case EMACT_SLOT_DRUG:
					{
						SINVENITEM* pInvenItem = m_pOwner->m_cInventory.FindItem ( sACTION.sNID );
						if ( !pInvenItem )	continue;

						SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sACTION.sNID );
						if ( !pITEM ) continue;

						if ( pITEM->sBasicOp.emItemType!=ITEM_CURE ) continue;

						if ( m_pOwner->IsCoolTime( pInvenItem->sItemCustom.sNativeID ) ) continue;

						// HP �����̸�
						switch ( pITEM->sDrugOp.emDrug )
						{
						case ITEM_DRUG_HP:
						case ITEM_DRUG_HP_MP:
						case ITEM_DRUG_HP_MP_SP:
						case ITEM_DRUG_HP_CURE:
						case ITEM_DRUG_HP_MP_SP_CURE:
							{
								if ( pITEM->sDrugOp.bRatio )
								{
									if ( pITEM->sDrugOp.wCureVolume/100.0f*dwMaxOwnersHP <= (float)dwHPVar )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}
								else
								{
									if ( pITEM->sDrugOp.wCureVolume <= dwHPVar )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}

								// HP�� 20% ������ �������� ������ �Դ´�.
								if ( (float)(dwMaxOwnersHP-dwHPVar)/dwMaxOwnersHP*100.0f < GLCONST_PET::fMaginotLineHP )
								{
									m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
									return;
								}
							}
						};

						// MP �����̸�
						switch ( pITEM->sDrugOp.emDrug )
						{
						case ITEM_DRUG_MP:
						case ITEM_DRUG_HP_MP:
						case ITEM_DRUG_MP_SP:
						case ITEM_DRUG_HP_MP_SP:
						case ITEM_DRUG_HP_MP_SP_CURE:
							{
								if ( pITEM->sDrugOp.bRatio )
								{
									if ( pITEM->sDrugOp.wCureVolume/100.0f*dwMaxOwnersMP <= float(nMPVar) )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}
								else
								{
									if ( pITEM->sDrugOp.wCureVolume <= nMPVar )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}

								// MP�� 20% ������ ��������
								if ( (float)(dwMaxOwnersMP-nMPVar)/dwMaxOwnersMP*100.0f < GLCONST_PET::fMaginotLineMP )
								{
									m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
									return;
								}
							}
						};

						// SP �����̸�
						switch ( pITEM->sDrugOp.emDrug )
						{
						case ITEM_DRUG_SP:
						case ITEM_DRUG_MP_SP:
						case ITEM_DRUG_HP_MP_SP:
						case ITEM_DRUG_HP_MP_SP_CURE:
							{
								if ( pITEM->sDrugOp.bRatio )
								{
									if ( pITEM->sDrugOp.wCureVolume/100.0f*dwMaxOwnersSP <= (float)nSPVar )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}
								else
								{
									if ( pITEM->sDrugOp.wCureVolume <= nSPVar )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}

								// SP�� 20% ������ ��������
								if ( (float)(dwMaxOwnersSP-nSPVar)/dwMaxOwnersSP*100.0f < GLCONST_PET::fMaginotLineSP )
								{
									m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
									return;
								}
							}
						};

						// �̻�ġ��
						if ( pITEM->sDrugOp.emDrug == ITEM_DRUG_CURE )
						{
							if ( m_pOwner->ISSTATEBLOW() )
							{
								m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
								return;
							}
						}
					}
				};
			} // end of for
		}
		break;

	case SKILL::EMFOR_PET_PROTECTITEMS:
		break;

	default: break;
	};
}

void GLPetClient::ProceedSkill_B ()
{
	// ��ų�� ����������?
	if ( !m_bSkillProcessing_B ) return;

	//	��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_sActiveSkillID_B );
	if ( !pSkill )	return;

	switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
	{
		// �������� �ݴ� ��ų�̸�
	case SKILL::EMFOR_PET_GETALLITEMS:
	case SKILL::EMFOR_PET_GETRAREITEMS:
	case SKILL::EMFOR_PET_GETPOTIONS:
	case SKILL::EMFOR_PET_GETSTONE:
	case SKILL::EMFOR_PET_GETMONEY:
		{
			// �ֺ��� �������� ������ �޷�����.
			if ( !IsSTATE(EM_PETACT_RUN_PICKUP_ITEM) )
			{
				if ( !m_vecDroppedItems_B.empty() )
				{
					// �ϳ� ������
					m_sSkillTARGET = m_vecDroppedItems_B.back();
					m_vecDroppedItems_B.pop_back ();

					// �������� �κ��� ���� �� �ִ��� �˻�
					EM_FIELDITEM_STATE emResult = IsInsertableInven ( m_sSkillTARGET );

					switch ( emResult )
					{
						// ��Ʈ��ũ �����̷� �������� �ʴ� �������� ��� �õ��Ұ��
					case EM_FIELDITEM_STATE_REMOVED:
						break;

						// �κ��丮 ���� ����
					case EM_FIELDITEM_STATE_INSERTFAIL:
						{
							m_sSkillTARGET.RESET ();
							ReqChangeActiveSkill_B ( NATIVEID_NULL() ); // ��ų�� ����ع�����.
							m_vecDroppedItems_B.clear();
							CInnerInterface::GetInstance().PrintConsoleTextDlg( ID2GAMEINTEXT("EMPET_NOTENOUGHINVEN") );
						}
						break;;
						// �κ��丮 ���� ����
					case EM_FIELDITEM_STATE_INSERTOK:
						{
							D3DXVECTOR3 vDist, vDir, vTar;
							vDist = m_sSkillTARGET.vPos - m_vPos;
							D3DXVec3Normalize ( &vDir, &vDist );
							float fDist = D3DXVec3Length ( &vDist ) - 10.0f; // �ݱ� ������ �Ÿ���ŭ �Ÿ� ����
							vTar = vDir * fDist;
							vTar = m_vPos + vTar;
							ReqGoto ( vTar, true );
						}
						break;
						// �Ϲ� ������ ���
					case EM_FIELDITEM_STATE_GENERALFAIL:
						{
						}
						break;
					}
				}
				// ���� ������ ������ ������ ��û�Ѵ�.
				else 
				{
					GetItembySkill_B ( m_sActiveSkillID_B ); 
				}
			}
		}
		break;

		// ������ ��ų���� ������ ���¸� �������ش�.
	case SKILL::EMFOR_PET_HEAL:
	case SKILL::EMFOR_PET_SUPPROT:
	case SKILL::EMFOR_PET_BACKUP_ATK:
	case SKILL::EMFOR_PET_BACKUP_DEF:
		{
		}
		break;

		// ţ���Կ� ������ �Ծ��ش�. (�������ӿ� �ѹ��� ���� �Ծ��ش�!)
	case SKILL::EMFOR_PET_AUTOMEDISON:
		{
			DWORD dwMaxOwnersHP = m_pOwner->GETMAXHP ();
			DWORD dwMaxOwnersMP = m_pOwner->GETMAXMP ();
			DWORD dwMaxOwnersSP = m_pOwner->GETMAXSP ();
			DWORD dwHPVar = dwMaxOwnersHP - m_pOwner->GETHP ();
			int   nMPVar  = dwMaxOwnersMP - m_pOwner->GETMP ();
			int   nSPVar  = dwMaxOwnersSP - m_pOwner->GETSP ();

			// Q, W, E, A, S, D
			for ( WORD wSLOT = 0; wSLOT < EMACTIONQUICK_SIZE; ++wSLOT )
			{
				const SACTION_SLOT &sACTION = m_pOwner->m_sACTIONQUICK[wSLOT];
				if ( !sACTION.VALID() )	continue;

				switch ( sACTION.wACT )
				{
				case EMACT_SLOT_DRUG:
					{
						SINVENITEM* pInvenItem = m_pOwner->m_cInventory.FindItem ( sACTION.sNID );
						if ( !pInvenItem )	continue;

						SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sACTION.sNID );
						if ( !pITEM ) continue;

						if ( pITEM->sBasicOp.emItemType!=ITEM_CURE ) continue;

						if ( m_pOwner->IsCoolTime( pInvenItem->sItemCustom.sNativeID ) ) continue;

						// HP �����̸�
						switch ( pITEM->sDrugOp.emDrug )
						{
						case ITEM_DRUG_HP:
						case ITEM_DRUG_HP_MP:
						case ITEM_DRUG_HP_MP_SP:
						case ITEM_DRUG_HP_CURE:
						case ITEM_DRUG_HP_MP_SP_CURE:
							{
								if ( pITEM->sDrugOp.bRatio )
								{
									if ( pITEM->sDrugOp.wCureVolume/100.0f*dwMaxOwnersHP <= (float)dwHPVar )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}
								else
								{
									if ( pITEM->sDrugOp.wCureVolume <= dwHPVar )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}

								// HP�� 20% ������ �������� ������ �Դ´�.
								if ( (float)(dwMaxOwnersHP-dwHPVar)/dwMaxOwnersHP*100.0f < GLCONST_PET::fMaginotLineHP )
								{
									m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
									return;
								}
							}
						};

						// MP �����̸�
						switch ( pITEM->sDrugOp.emDrug )
						{
						case ITEM_DRUG_MP:
						case ITEM_DRUG_HP_MP:
						case ITEM_DRUG_MP_SP:
						case ITEM_DRUG_HP_MP_SP:
						case ITEM_DRUG_HP_MP_SP_CURE:
							{
								if ( pITEM->sDrugOp.bRatio )
								{
									if ( pITEM->sDrugOp.wCureVolume/100.0f*dwMaxOwnersMP <= float(nMPVar) )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}
								else
								{
									if ( pITEM->sDrugOp.wCureVolume <= nMPVar )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}

								// MP�� 20% ������ ��������
								if ( (float)(dwMaxOwnersMP-nMPVar)/dwMaxOwnersMP*100.0f < GLCONST_PET::fMaginotLineMP )
								{
									m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
									return;
								}
							}
						};

						// SP �����̸�
						switch ( pITEM->sDrugOp.emDrug )
						{
						case ITEM_DRUG_SP:
						case ITEM_DRUG_MP_SP:
						case ITEM_DRUG_HP_MP_SP:
						case ITEM_DRUG_HP_MP_SP_CURE:
							{
								if ( pITEM->sDrugOp.bRatio )
								{
									if ( pITEM->sDrugOp.wCureVolume/100.0f*dwMaxOwnersSP <= (float)nSPVar )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}
								else
								{
									if ( pITEM->sDrugOp.wCureVolume <= nSPVar )
									{
										m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
										return;
									}
								}

								// SP�� 20% ������ ��������
								if ( (float)(dwMaxOwnersSP-nSPVar)/dwMaxOwnersSP*100.0f < GLCONST_PET::fMaginotLineSP )
								{
									m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
									return;
								}
							}
						};

						// �̻�ġ��
						if ( pITEM->sDrugOp.emDrug == ITEM_DRUG_CURE )
						{
							if ( m_pOwner->ISSTATEBLOW() )
							{
								m_pOwner->ReqInvenDrug ( pInvenItem->wPosX, pInvenItem->wPosY );
								return;
							}
						}
					}
				};
			} // end of for
		}
		break;

	case SKILL::EMFOR_PET_PROTECTITEMS:
		break;

	default: break;
	};
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetItembySkill_A ( SNATIVEID sSkillID )
{
	//	��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sSkillID );
	if ( !pSkill )	return;

	switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
	{
		// �������� �ݴ� ��ų�̸�
	case SKILL::EMFOR_PET_GETALLITEMS:  GetAllItems_A ();
		break;
	case SKILL::EMFOR_PET_GETRAREITEMS: GetRareItems_A ();
		break;
	case SKILL::EMFOR_PET_GETPOTIONS:   GetPotions_A ();
		break;
	case SKILL::EMFOR_PET_GETSTONE:		GetStone_A ();
		break;
	case SKILL::EMFOR_PET_GETMONEY:		GetMoney_A ();
		break;
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetItembySkill_B ( SNATIVEID sSkillID )
{
	//	��ų ���� ������.
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sSkillID );
	if ( !pSkill )	return;

	switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
	{
		// �������� �ݴ� ��ų�̸�
	case SKILL::EMFOR_PET_GETALLITEMS:  GetAllItems_B ();
		break;
	case SKILL::EMFOR_PET_GETRAREITEMS: GetRareItems_B ();
		break;
	case SKILL::EMFOR_PET_GETPOTIONS:   GetPotions_B ();
		break;
	case SKILL::EMFOR_PET_GETSTONE:		GetStone_B ();
		break;
	case SKILL::EMFOR_PET_GETMONEY:		GetMoney_B ();
		break;
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetAllItems_A ()
{
	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_ITEM | CROW_EX_MONEY );
	DETECTMAP* pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, m_vPos, MAX_VIEWRANGE/6.0f );
	if ( m_vecDroppedItems_A.empty() && pDetectMap )
	{
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_ITEM, STAR_ORDER() );
		bool bDetectItem = pairRange.first != pairRange.second;
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MONEY, STAR_ORDER() );
		bool bDetectMoney = pairRange.first != pairRange.second;

		// �����۰� ���� ���� ������ ������
		if ( bDetectItem || bDetectMoney )
		{
			m_vecDroppedItems_A.clear();
			GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A NetMsg;
			NetMsg.dwGUID = m_dwGUID;
			NetMsg.emSkill = EMPETSKILL_GETALL;
			NETSENDTOFIELD ( &NetMsg );
		}
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetAllItems_B ()
{
	DETECTMAP_RANGE pairRange;
	DWORD emCrow = ( CROW_EX_ITEM | CROW_EX_MONEY );
	DETECTMAP* pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( emCrow, m_vPos, MAX_VIEWRANGE/6.0f );
	if ( m_vecDroppedItems_B.empty() && pDetectMap )
	{
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_ITEM, STAR_ORDER() );
		bool bDetectItem = pairRange.first != pairRange.second;
		pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MONEY, STAR_ORDER() );
		bool bDetectMoney = pairRange.first != pairRange.second;

		// �����۰� ���� ���� ������ ������
		if ( bDetectItem || bDetectMoney )
		{
			m_vecDroppedItems_B.clear();
			GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B NetMsg;
			NetMsg.dwGUID = m_dwGUID;
			NetMsg.emSkill = EMPETSKILL_GETALL;
			NETSENDTOFIELD ( &NetMsg );
		}
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetRareItems_A ()
{
	PLANDMANCLIENT pLAND = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLAND ) return;

	DETECTMAP* pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_ITEM, m_vPos, MAX_VIEWRANGE/6.0f );
	if ( m_vecDroppedItems_A.empty() && pDetectMap )
	{
		DETECTMAP_RANGE pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_ITEM, STAR_ORDER() );
		if ( pairRange.first != pairRange.second )
		{
			DETECTMAP_ITER iter = pairRange.first;
			for ( ; iter != pairRange.second; ++iter )
			{
				const STARGETID &sTarID = (*iter);
				PITEMCLIENTDROP pDropItem = pLAND->GetItem ( sTarID.dwID );
				if ( !pDropItem ) continue;
				SITEM *pItem = GLItemMan::GetInstance().GetItem(pDropItem->sItemClient.sNativeID);
				if ( !pItem ) continue;

				// ����������� �ϳ��� ���� ������ ������
				if ( pItem->sBasicOp.emLevel == LEVEL_RARE )
				{
					m_vecDroppedItems_A.clear();
					GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A NetMsg;
					NetMsg.dwGUID = m_dwGUID;
					NetMsg.emSkill = EMPETSKILL_GETRARE;
					NETSENDTOFIELD ( &NetMsg );
					break;
				}
			}
		}
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetRareItems_B ()
{
	PLANDMANCLIENT pLAND = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLAND ) return;

	DETECTMAP* pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_ITEM, m_vPos, MAX_VIEWRANGE/6.0f );
	if ( m_vecDroppedItems_B.empty() && pDetectMap )
	{
		DETECTMAP_RANGE pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_ITEM, STAR_ORDER() );
		if ( pairRange.first != pairRange.second )
		{
			DETECTMAP_ITER iter = pairRange.first;
			for ( ; iter != pairRange.second; ++iter )
			{
				const STARGETID &sTarID = (*iter);
				PITEMCLIENTDROP pDropItem = pLAND->GetItem ( sTarID.dwID );
				if ( !pDropItem ) continue;
				SITEM *pItem = GLItemMan::GetInstance().GetItem(pDropItem->sItemClient.sNativeID);
				if ( !pItem ) continue;

				// ����������� �ϳ��� ���� ������ ������
				if ( pItem->sBasicOp.emLevel == LEVEL_RARE )
				{
					m_vecDroppedItems_B.clear();
					GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B NetMsg;
					NetMsg.dwGUID = m_dwGUID;
					NetMsg.emSkill = EMPETSKILL_GETRARE;
					NETSENDTOFIELD ( &NetMsg );
					break;
				}
			}
		}
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetPotions_A ()
{
	PLANDMANCLIENT pLAND = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLAND ) return;

	DETECTMAP* pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_ITEM, m_vPos, MAX_VIEWRANGE/6.0f );
	if ( m_vecDroppedItems_A.empty() && pDetectMap )
	{
		DETECTMAP_RANGE pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_ITEM, STAR_ORDER() );
		if ( pairRange.first != pairRange.second )
		{
			DETECTMAP_ITER iter = pairRange.first;
			for ( ; iter != pairRange.second; ++iter )
			{
				const STARGETID &sTarID = (*iter);
				PITEMCLIENTDROP pDropItem = pLAND->GetItem ( sTarID.dwID );
				if ( !pDropItem ) continue;
				SITEM *pItem = GLItemMan::GetInstance().GetItem(pDropItem->sItemClient.sNativeID);
				if ( !pItem ) continue;

				// ������ �ϳ��� ���� ������ ������
				if ( pItem->sBasicOp.emItemType == ITEM_CURE )
				{
					m_vecDroppedItems_A.clear();
					GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A NetMsg;
					NetMsg.dwGUID = m_dwGUID;
					NetMsg.emSkill = EMPETSKILL_GETPOTIONS;
					NETSENDTOFIELD ( &NetMsg );
					break;
				}
			}
		}
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetPotions_B ()
{
	PLANDMANCLIENT pLAND = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLAND ) return;

	DETECTMAP* pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_ITEM, m_vPos, MAX_VIEWRANGE/6.0f );
	if ( m_vecDroppedItems_B.empty() && pDetectMap )
	{
		DETECTMAP_RANGE pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_ITEM, STAR_ORDER() );
		if ( pairRange.first != pairRange.second )
		{
			DETECTMAP_ITER iter = pairRange.first;
			for ( ; iter != pairRange.second; ++iter )
			{
				const STARGETID &sTarID = (*iter);
				PITEMCLIENTDROP pDropItem = pLAND->GetItem ( sTarID.dwID );
				if ( !pDropItem ) continue;
				SITEM *pItem = GLItemMan::GetInstance().GetItem(pDropItem->sItemClient.sNativeID);
				if ( !pItem ) continue;

				// ������ �ϳ��� ���� ������ ������
				if ( pItem->sBasicOp.emItemType == ITEM_CURE )
				{
					m_vecDroppedItems_B.clear();
					GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B NetMsg;
					NetMsg.dwGUID = m_dwGUID;
					NetMsg.emSkill = EMPETSKILL_GETPOTIONS;
					NETSENDTOFIELD ( &NetMsg );
					break;
				}
			}
		}
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetMoney_A ()
{
	DETECTMAP* pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_MONEY, m_vPos, MAX_VIEWRANGE/6.0f );
	if ( m_vecDroppedItems_A.empty() && pDetectMap )
	{
		DETECTMAP_RANGE pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MONEY, STAR_ORDER() );
		if ( pairRange.first != pairRange.second )
		{
			m_vecDroppedItems_A.clear();
			GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A NetMsg;
			NetMsg.dwGUID = m_dwGUID;
			NetMsg.emSkill = EMPETSKILL_GETMONEY;
			NETSENDTOFIELD ( &NetMsg );
		}
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetMoney_B ()
{
	DETECTMAP* pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_MONEY, m_vPos, MAX_VIEWRANGE/6.0f );
	if ( m_vecDroppedItems_B.empty() && pDetectMap )
	{
		DETECTMAP_RANGE pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_MONEY, STAR_ORDER() );
		if ( pairRange.first != pairRange.second )
		{
			m_vecDroppedItems_B.clear();
			GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B NetMsg;
			NetMsg.dwGUID = m_dwGUID;
			NetMsg.emSkill = EMPETSKILL_GETMONEY;
			NETSENDTOFIELD ( &NetMsg );
		}
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetStone_A ()
{
	PLANDMANCLIENT pLAND = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLAND ) return;

	DETECTMAP* pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_ITEM, m_vPos, MAX_VIEWRANGE/6.0f );
	if ( m_vecDroppedItems_A.empty() && pDetectMap )
	{
		DETECTMAP_RANGE pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_ITEM, STAR_ORDER() );
		if ( pairRange.first != pairRange.second )
		{
			DETECTMAP_ITER iter = pairRange.first;
			for ( ; iter != pairRange.second; ++iter )
			{
				const STARGETID &sTarID = (*iter);
				PITEMCLIENTDROP pDropItem = pLAND->GetItem ( sTarID.dwID );
				if ( !pDropItem ) continue;
				SITEM *pItem = GLItemMan::GetInstance().GetItem(pDropItem->sItemClient.sNativeID);
				if ( !pItem ) continue;

				// �������� �ϳ��� ���� ������ ������
				if ( pItem->sBasicOp.emItemType == ITEM_GRINDING
					|| pItem->sBasicOp.emItemType == ITEM_MATERIALS )
				{
					m_vecDroppedItems_A.clear();
					GLMSG::SNETPET_REQ_GETRIGHTOFITEM_A NetMsg;
					NetMsg.dwGUID = m_dwGUID;
					NetMsg.emSkill = EMPETSKILL_GETSTONE;
					NETSENDTOFIELD ( &NetMsg );
					break;
				}
			}
		}
	}
}

/*dual pet skill, Juver, 2017/12/28 */
void GLPetClient::GetStone_B ()
{
	PLANDMANCLIENT pLAND = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLAND ) return;

	DETECTMAP* pDetectMap = GLGaeaClient::GetInstance().DetectCrow ( CROW_EX_ITEM, m_vPos, MAX_VIEWRANGE/6.0f );
	if ( m_vecDroppedItems_B.empty() && pDetectMap )
	{
		DETECTMAP_RANGE pairRange = std::equal_range ( pDetectMap->begin(), pDetectMap->end(), CROW_ITEM, STAR_ORDER() );
		if ( pairRange.first != pairRange.second )
		{
			DETECTMAP_ITER iter = pairRange.first;
			for ( ; iter != pairRange.second; ++iter )
			{
				const STARGETID &sTarID = (*iter);
				PITEMCLIENTDROP pDropItem = pLAND->GetItem ( sTarID.dwID );
				if ( !pDropItem ) continue;
				SITEM *pItem = GLItemMan::GetInstance().GetItem(pDropItem->sItemClient.sNativeID);
				if ( !pItem ) continue;

				// �������� �ϳ��� ���� ������ ������
				if ( pItem->sBasicOp.emItemType == ITEM_GRINDING
					|| pItem->sBasicOp.emItemType == ITEM_MATERIALS )
				{
					m_vecDroppedItems_B.clear();
					GLMSG::SNETPET_REQ_GETRIGHTOFITEM_B NetMsg;
					NetMsg.dwGUID = m_dwGUID;
					NetMsg.emSkill = EMPETSKILL_GETSTONE;
					NETSENDTOFIELD ( &NetMsg );
					break;
				}
			}
		}
	}
}