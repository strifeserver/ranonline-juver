#include "StdAfx.h"
#include "OuterInterface.h"
#include "ModalWindow.h"
#include "GameTextControl.h"
#include "DxGlobalStage.h"
#include "RanParam.h"

#include "SelectServerPage.h"
#include "LoginPage.h"
#include "CharacterCreatePage.h"
#include "CharacterCreateInfo.h"
#include "CharacterCreateRotate.h"
#include "SelectCharacterPage.h"
#include "WaitDialogue.h"
#include "SecPassCheckPage.h"
#include "SecPassSetPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void COuterInterface::ModalMsgProcess ( UIGUID nCallerID, DWORD dwMsg )
{
	switch ( nCallerID )
	{
	case OUTER_MODAL_CLOSEGAME:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
                DxGlobalStage::GetInstance().CloseGame();
			}
			else if ( dwMsg & UIMSG_MODAL_CANCEL )
			{
				/*login port, Juver, 2017/11/16 */
				if ( DxGlobalStage::GetInstance().GetNetClient()->ConnectLoginServer(RANPARAM::LoginAddress, RANPARAM::nLoginPort) > NET_ERROR )
				{
 					// ���� ����
					DxGlobalStage::GetInstance().GetNetClient()->SndReqServerInfo();				
				}
				else
				{
					//���� ����
					DoModalOuter ( ID2GAMEEXTEXT ( "SERVERSTAGE_3" ), MODAL_INFOMATION, OKCANCEL, OUTER_MODAL_CLOSEGAME );
				}
			}
		}
		break;

	case OUTER_MODAL_WAITSERVERINFO:
		{
			CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
			if ( pNetClient->IsOnline() )		//��Ʈ��ũ ������ ������ ���
			{
				if ( pNetClient->IsGameSvrInfoEnd() )
				{
					HideGroup ( MODAL_WINDOW_OUTER );
					return ;
				}
			}

			if ( dwMsg & UIMSG_MODAL_CANCEL )
			{
				DoModalOuter ( ID2GAMEEXTEXT ( "SERVERSTAGE_3" ), MODAL_INFOMATION, OKCANCEL, OUTER_MODAL_CLOSEGAME );				
			}
		}
		break;

	case OUTER_MODAL_RECONNECT:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				ToSelectServerPage( GetModalCallWindowID() );
			}
		}
		break;

	case OUTER_MODAL_WAITCONFIRM:
		{
			if ( dwMsg & UIMSG_MODAL_CANCEL )
			{
				DxGlobalStage::GetInstance().GetNetClient()->CloseConnect();
				ToSelectServerPage( GetModalCallWindowID() );
			}
		}	
		break;

	case OUTER_MODAL_ALREADYCONNECT:
	case OUTER_MODAL_CREATEFAILED:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				DxGlobalStage::GetInstance().CloseGame();
			}
		}
		break;

	case OUTER_MODAL_NON_PK_CHANNEL:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				if ( IsVisibleGroup ( SELECT_CHARACTER_PAGE ) )			HideGroup ( SELECT_CHARACTER_PAGE );
				if ( IsVisibleGroup ( SELECT_CHARACTER_USERPANEL ) )	HideGroup ( SELECT_CHARACTER_USERPANEL );//userpanel
				if ( IsVisibleGroup ( CHARACTER_CREATE_PAGE ) )			HideGroup ( CHARACTER_CREATE_PAGE );
				if ( IsVisibleGroup ( CHARACTER_CREATE_INFO ) )			HideGroup ( CHARACTER_CREATE_INFO );
				if ( IsVisibleGroup ( CHARACTER_CREATE_ROTATE ) )		HideGroup ( CHARACTER_CREATE_ROTATE );

				//	Note : ��ſ� �������
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
				if ( pNetClient->IsOnline() == true )
					pNetClient->CloseConnect ();

				COuterInterface::GetInstance().ToSelectServerPage ( SELECT_SERVER_PAGE );
			}
		}
		break;

	case OUTER_MODAL_SECONDPASSWORD:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				WAITSERVER_DIALOGUE_OPEN ( ID2GAMEEXTEXT("WAITSERVER_DEL_CHARACTER"), WAITSERVER_DEL_CHARACTER, 10.0f );
			}
		}
		break;

	case OUTER_MODAL_LOGOUT:
	case OUTER_MODAL_CONNECTCLOSED:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				//	Note : ��ſ� �������
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
				if ( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect ();
					COuterInterface::GetInstance().SetCancelToLogin();
				}

				//				if ( pNetClient->ConnectLoginServer(RANPARAM::LoginAddress) <= NET_ERROR )
				//					CDebugSet::ToListView ( "CCharacterStage::Logout ConnectLoginServer NET_ERROR" );
				//				else
				//					CDebugSet::ToListView ( "CCharacterStage::Logout ConnectLoginServer NET_OK" );				

				if ( IsVisibleGroup ( SELECT_CHARACTER_PAGE ) )			HideGroup ( SELECT_CHARACTER_PAGE );
				if ( IsVisibleGroup ( SELECT_CHARACTER_USERPANEL ) )	HideGroup ( SELECT_CHARACTER_USERPANEL ); //userpanel
				if ( IsVisibleGroup ( CHARACTER_CREATE_PAGE ) )			HideGroup ( CHARACTER_CREATE_PAGE );
				if ( IsVisibleGroup ( CHARACTER_CREATE_INFO ) )			HideGroup ( CHARACTER_CREATE_INFO );
				if ( IsVisibleGroup ( CHARACTER_CREATE_ROTATE ) )		HideGroup ( CHARACTER_CREATE_ROTATE );

				if( IsVisibleGroup( SELECT_CHINA_AREA_PAGE ) )			
				{
					ToChinaAreaPage( SELECT_CHINA_AREA_PAGE );
				}
				else
				{
					ToSelectServerPage ( SELECT_CHARACTER_PAGE );
				}
			}
		}
		break;

	

	case OUTER_MODAL_CREATESUCCEED:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				ToSelectCharacterPage ( CHARACTER_CREATE_PAGE );
			}
		}
		break;

	//userpanel
		case OUTER_MODAL_CHANGEPIN:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				if ( IsVisibleGroup ( CHANGEPIN_PAGE ) )			HideGroup ( CHANGEPIN_PAGE );
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
				if( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect();
					COuterInterface::GetInstance().SetCancelToLogin();
				}

				COuterInterface::GetInstance().ToSelectServerPage ( CHANGEPIN_PAGE );
			}
		}break;

	case OUTER_MODAL_CHANGEPASS:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				if ( IsVisibleGroup ( CHANGEPASS_PAGE ) )			HideGroup ( CHANGEPASS_PAGE );
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
				if( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect();
					COuterInterface::GetInstance().SetCancelToLogin();
				}

				COuterInterface::GetInstance().ToSelectServerPage ( CHANGEPASS_PAGE );
			}
		}break;

	case OUTER_MODAL_CHANGEEMAIL:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				if ( IsVisibleGroup ( CHANGEEMAIL_PAGE ) )			HideGroup ( CHANGEEMAIL_PAGE );
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
				if( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect();
					COuterInterface::GetInstance().SetCancelToLogin();
				}

				COuterInterface::GetInstance().ToSelectServerPage ( CHANGEEMAIL_PAGE );
			}
		}break;
	case OUTER_MODAL_RESETPIN:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				if ( IsVisibleGroup ( RESETPIN_PAGE ) )			HideGroup ( RESETPIN_PAGE );
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
				if( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect();
					COuterInterface::GetInstance().SetCancelToLogin();
				}
				COuterInterface::GetInstance().ToSelectServerPage ( RESETPIN_PAGE );

			}
		}break;
	case OUTER_MODAL_RESETPASS:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				if ( IsVisibleGroup ( RESETPASS_PAGE ) )			HideGroup ( RESETPASS_PAGE );
				COuterInterface::GetInstance().ToRPSPage2 ( RESETPASS_PAGE );

			}
		}break;
	
	case OUTER_MODAL_RESETPASS2:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				if ( IsVisibleGroup ( RESETPASS_PAGE2 ) )			HideGroup ( RESETPASS_PAGE2 );
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
				if( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect();
					COuterInterface::GetInstance().SetCancelToLogin();
				}
				
				COuterInterface::GetInstance().ToSelectServerPage ( RESETPASS_PAGE2 );
			}
		}break;

	case OUTER_MODAL_TOPUP:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				if ( IsVisibleGroup ( TOPUP_PAGE ) )			HideGroup ( TOPUP_PAGE );
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
				if( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect();
					COuterInterface::GetInstance().SetCancelToLogin();
				}

				COuterInterface::GetInstance().ToSelectServerPage ( TOPUP_PAGE );
			}
		}break;

	case OUTER_MODAL_GAMETIMECVT:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				if ( IsVisibleGroup ( GAMETIMECVT_PAGE ) )			HideGroup ( GAMETIMECVT_PAGE );
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
				if( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect();
					COuterInterface::GetInstance().SetCancelToLogin();
				}

				COuterInterface::GetInstance().ToSelectServerPage ( GAMETIMECVT_PAGE );
			}
		}break;

	case OUTER_MODAL_PREMIUMPOINTCVT:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				if ( IsVisibleGroup ( PREMIUMPOINTCVT_PAGE ) )			HideGroup ( PREMIUMPOINTCVT_PAGE );
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
				if( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect();
					COuterInterface::GetInstance().SetCancelToLogin();
				}

				COuterInterface::GetInstance().ToSelectServerPage ( PREMIUMPOINTCVT_PAGE );
			}
		}break;
	//userpanel end

	case OUTER_MODAL_GENERAL_LOGINFAIL:
		{
			if( dwMsg & UIMSG_MODAL_OK )
			{
				if( RANPARAM::VALIDIDPARAM () )
				{
					UIGUID uiGUID = GetModalCallWindowID();

					if( uiGUID == SECPASS_SETPAGE )
						COuterInterface::GetInstance().GetSecPassSetPage()->ResetAll();
					else if( uiGUID == SECPASS_CHECKPAGE )
						COuterInterface::GetInstance().GetSecPassCheckPage()->ResetAll();
					else
						COuterInterface::GetInstance().ToSelectServerPage ( SELECT_SERVER_PAGE );
				}
				else
				{
					//COuterInterface::GetInstance().ToLoginPage ( LOGIN_PAGE );
					COuterInterface::GetInstance().GetLoginPage()->ResetAll();
				}
			}
		}
		break;

	case OUTER_MODAL_LOGIN_WAIT_DAUM:
		{
			//	NOTE
			//		���� ������ ��ȣ Ű�� ���� ������ ����Ѵ�.
			//		
			CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
			if ( pNetClient->IsKeyReceived () )
			{
				CString strTemp;

				//	��Ʈ�ѷ� ���� ���̵�� ��ȣ�� ������ ������ ����
				switch ( RANPARAM::emSERVICE_TYPE )
				{
				case EMSERVICE_KOREA:
					pNetClient->DaumSndLogin ( RANPARAM::GETIDPARAM(), m_nServerChannel );
					break;

				//case EMSERVICE_GSP:
				//	pNetClient->GspSndLogin ( RANPARAM::GETIDPARAM(), m_nServerChannel );
				//	break;

				case EMSERVICE_MALAYSIA_CN:
				case EMSERVICE_MALAYSIA_EN:
				case EMSERVICE_PHILIPPINES:
				case EMSERVICE_VIETNAM:
					pNetClient->TerraSndLogin ( RANPARAM::GETIDPARAM(), m_nServerChannel );
					break;

//		Japan �α��� ��� ����
//				case EMSERVICE_JAPAN:
//					pNetClient->ExciteSndLogin ( RANPARAM::GETIDPARAM(), RANPARAM::GETIDPARAM2(), RANPARAM::GETIDPARAM3(), m_nServerChannel );
//					break;

				default:
					CString strTemp;
					strTemp.Format( "OUTER_MODAL_LOGIN_WAIT_DAUM::default:ServiceType:%d", RANPARAM::emSERVICE_TYPE );
					AfxMessageBox( strTemp.GetString() );
					break;
				};

                START_WAIT_TIME ( 10.0f );
				DoModalOuter ( ID2GAMEEXTEXT ("DAUM_LOGIN_WAIT"), MODAL_INFOMATION, CANCEL, OUTER_MODAL_LOGIN_WAIT_DAUM_AFTER_KEYRECEIVED );
			}
			else			
			{
				//	NOTE
				//		�ð��� �ʰ��� ���
				//		�Ʒ��� ó������ �ٷ� ������ �� á�ٴ� �޽����� �Ѹ���.
				if ( GET_WAIT_TIME() < 0.0f )
				{
					DoModalOuter ( ID2GAMEEXTEXT ("DAUM_LOGIN_WAIT_SERVERFULL"), MODAL_INFOMATION, YESNO, OUTER_MODAL_LOGIN_WAIT_DAUM_SERVERFULL );
				}
			}
		}
		break;

	case OUTER_MODAL_LOGIN_WAIT_DAUM_AFTER_KEYRECEIVED:
		{
			//	NOTE
			//		�ð��� �ʰ��� ���
			//		�Ʒ��� ó������ �ٷ� ������ �� á�ٴ� �޽����� �Ѹ���.
			if ( GET_WAIT_TIME() < 0.0f )
			{
				DoModalOuter ( ID2GAMEEXTEXT ("DAUM_LOGIN_WAIT_SERVERFULL"), MODAL_INFOMATION, YESNO, OUTER_MODAL_LOGIN_WAIT_DAUM_SERVERFULL );
			}
		}
		break;

	case OUTER_MODAL_LOGIN_WAIT_DAUM_SERVERFULL:
		{
			//	NOTE
			//		�ٽ� �õ��غ���
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				GetSelectServerPage()->Login ();
			}
		}
		break;

	case OUTER_MODAL_CHARACTERSTAGE_GAME_JOIN_WAIT:
		{
			if( dwMsg & UIMSG_MODAL_CANCEL )
			{
				DxGlobalStage::GetInstance().SetGameJoin( FALSE );
				//	Note : ��ſ� �������
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
				if ( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect ();
					COuterInterface::GetInstance().SetCancelToLogin();
				}

				//				if ( pNetClient->ConnectLoginServer(RANPARAM::LoginAddress) <= NET_ERROR )
				//					CDebugSet::ToListView ( "CCharacterStage::Logout ConnectLoginServer NET_ERROR" );
				//				else
				//					CDebugSet::ToListView ( "CCharacterStage::Logout ConnectLoginServer NET_OK" );				

				if ( IsVisibleGroup ( SELECT_CHARACTER_PAGE ) )			HideGroup ( SELECT_CHARACTER_PAGE );
				if ( IsVisibleGroup ( SELECT_CHARACTER_USERPANEL ) )	HideGroup ( SELECT_CHARACTER_USERPANEL ); //userpanel
				if ( IsVisibleGroup ( CHARACTER_CREATE_PAGE ) )			HideGroup ( CHARACTER_CREATE_PAGE );
				if ( IsVisibleGroup ( CHARACTER_CREATE_INFO ) )			HideGroup ( CHARACTER_CREATE_INFO );
				if ( IsVisibleGroup ( CHARACTER_CREATE_ROTATE ) )		HideGroup ( CHARACTER_CREATE_ROTATE );

				if( IsVisibleGroup( SELECT_CHINA_AREA_PAGE ) )			
				{
					ToChinaAreaPage( SELECT_CHINA_AREA_PAGE );
				}
				else
				{
					ToSelectServerPage ( SELECT_CHARACTER_PAGE );
				}
			}
			else if ( GET_WAIT_TIME() < 0.0f )
			{
				//	NOTE
				//		�ð��� �ʰ��� ���
				//		�Ʒ��� ó������ �ٷ� ������ �� á�ٴ� �޽����� �Ѹ���.
				DoModalOuter ( ID2GAMEEXTEXT ("CHARACTERSTAGE_DAUM_GAME_JOIN_FAIL"), MODAL_INFOMATION, OK, OUTER_MODAL_CONNECTCLOSED );
			}
		}
		break;

	case OUTER_MODAL_NAME_ERROR:
	case OUTER_MODAL_THAI_CHECK_STRING_ERROR:
		{
			if ( dwMsg & UIMSG_MODAL_OK )
			{
				GetCharacterCreatePage()->ResetNameEdit ();
			}
		}
		break;
	}
}