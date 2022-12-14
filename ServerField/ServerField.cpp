#include "stdafx.h"
#include "resource.h"
#include "ServerField.h"
#include "s_NetGlobal.h"
#include "gassert.h"
#include "GLogicData.h"
#include "GLogic.h"
#include "ServerControllerMsgDefine.h"
#include "MinBugTrap.h"
#include "StringUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_LOADSTRING 100

CWinApp theApp;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		MessageBox( NULL, "Fatal Error: MFC initialization failed", "ERROR", MB_OK );
		return 1;
	}

	BUG_TRAP::BugTrapInstall( std::string(_T("ServerField")));
	g_hInst = hInstance;
	g_pServer = NULL;
	g_bStopReserve = false;
	SERVER_CONTROLLER::checkCmdParameter(lpCmdLine);

	CString StrCmdLine = lpCmdLine;

	STRUTIL::ClearSeparator ();
	STRUTIL::RegisterSeparator ( "/" );
	STRUTIL::RegisterSeparator ( " " );

	CStringArray strCmdArray;
	STRUTIL::StringSeparate ( StrCmdLine, strCmdArray );

	BOOL bRCC = FALSE;

	for ( int i=0; i<strCmdArray.GetCount(); i++ )
	{
		CString strTemp = strCmdArray.GetAt(i);

		if ( strTemp == "use_rcc" || strTemp == "USE_RCC" )
		{
			bRCC = TRUE;
		}
	}

	//rcc initialize
	GLOGIC::bGLOGIC_PACKFILE = FALSE;
	GLOGIC::bGLOGIC_ZIPFILE = FALSE;
	GLOGIC::bENGLIB_ZIPFILE = FALSE;

	if ( bRCC )
	{
		GLOGIC::bGLOGIC_PACKFILE = FALSE;
		GLOGIC::bGLOGIC_ZIPFILE = TRUE;
		GLOGIC::bENGLIB_ZIPFILE = TRUE;
	}

	DialogBox(g_hInst, MAKEINTRESOURCE(IDD_MAIN_DIALOG), HWND_DESKTOP, MainDlgProc);
	return 0;
}

void executeCmdParameter(HWND hDlg)
{
	if (SERVER_CONTROLLER::bStart) 
	{
		cmdStartOrStop(hDlg);
	}
}

void setFirstFocus(HWND hDlg)
{
	HWND pWnd = GetDlgItem(hDlg, IDC_BTN_EXECUTE);
	SetFocus(pWnd);
}

void initDialog(HWND hDlg)
{
	HWND pWnd = NULL;
	pWnd = GetDlgItem(hDlg, IDC_BTN_STOP);
	EnableWindow(pWnd, TRUE);

	pWnd = GetDlgItem(hDlg, IDC_BTN_PAUSE);
	EnableWindow(pWnd, FALSE);

	setFirstFocus(hDlg);

	::SetTimer(hDlg, 
		SERVER_CONTROLLER_TIMER_ID,
		SERVER_CONTROLLER_TIMER_MILLISECOND,
		NULL);
}

void executeCommand(HWND hDlg)
{
	if (g_pServer != NULL)
	{
		char cExecText[100] = {0};
		GetDlgItemText(hDlg, IDC_EDIT_EXEC, cExecText, 100);
		g_pServer->ExecuteCommand(cExecText);
	}
}

void cmdStartOrStop(HWND hDlg)
{
	int nRetCode = 0;

	if (g_bStopReserve == true) {
		return;
	}

	// Server is running
	if (g_pServer != NULL && g_pServer->IsRunning())
	{					
		g_bStopReserve = true;
		g_pServer->Stop();
		SetDlgItemText(hDlg, IDC_BTN_STOP, "Waiting...");
		HWND pWnd = GetDlgItem(hDlg, IDC_BTN_PAUSE);
		EnableWindow(pWnd, FALSE);

		while (g_pServer->GetReservationServerStop() == true)
		{
			Sleep( 1 );
		}
		g_pServer->FinalStop();
		SAFE_DELETE(g_pServer);

		SetDlgItemText(hDlg, IDC_BTN_STOP, "Start");
	}
	// Server is not running
	else
	{				
		g_pServer = new CFieldServer(hDlg, GetDlgItem(hDlg, IDC_EDITCONSOLE), GetDlgItem(hDlg, IDC_EDITCONSOLE_INFO), GetDlgItem(hDlg, IDC_EDITCONSOLE_STATS));
		nRetCode = g_pServer->Start();
		if ( nRetCode == NET_OK )
		{
			SetDlgItemText(hDlg, IDC_BTN_STOP, "Stop");
			HWND pWnd = GetDlgItem(hDlg, IDC_BTN_PAUSE);
			EnableWindow(pWnd, TRUE);
		}
		else if( nRetCode == NET_CFG_LOADERROR )
		{
			SAFE_DELETE(g_pServer);					
			HWND pWnd = GetDlgItem(hDlg, IDC_BTN_PAUSE);
			EnableWindow(pWnd, FALSE);
		}
		else 
		{
			g_pServer->Stop();
			while (g_pServer->GetReservationServerStop() == true)
			{
				Sleep( 1 );
			}
			g_pServer->FinalStop();
			SAFE_DELETE(g_pServer);					
			HWND pWnd = GetDlgItem(hDlg, IDC_BTN_PAUSE);
			EnableWindow(pWnd, FALSE);
		}
	}
}

void cmdPause(HWND hDlg)
{
	if (g_pServer != NULL)
	{
		if (g_pServer->GetStatus() == S_SERVER_RUNING)
		{
			g_pServer->Pause();
			SetDlgItemText(hDlg, IDC_BTN_PAUSE, "Resume");
			
			HWND pWnd = GetDlgItem(hDlg, IDC_BTN_STOP);
			EnableWindow(pWnd, FALSE);
		}
		else if (g_pServer->GetStatus() == S_SERVER_PAUSE)
		{
			g_pServer->Resume();
			SetDlgItemText(hDlg, IDC_BTN_PAUSE, "Pause");

			HWND pWnd = GetDlgItem(hDlg, IDC_BTN_STOP);
			EnableWindow(pWnd, TRUE);
		}
	}
}

void cmdExit(HWND hDlg)
{
	if (g_pServer != NULL)
	{
		g_pServer->Stop();
		while (g_pServer->GetReservationServerStop() == true)
		{
			Sleep( 1 );
		}
		g_pServer->FinalStop();
	}else{
		EndDialog(hDlg,0);
	}
}

void cmdFinalExit(HWND hDlg)
{
	if (g_pServer != NULL)
	{
		g_pServer->FinalStop ();
        SAFE_DELETE(g_pServer);
	}
	if (g_bStopReserve == true)
	{
		// Stop
		g_bStopReserve = false;
	}
	else
	{
		// Exit
		EndDialog(hDlg,0);
	}
}

void cmdShowWindow(HWND hDlg)
{
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.uID = 0;
	nid.hWnd = hDlg;
	Shell_NotifyIcon(NIM_DELETE, &nid);	
	ShowWindow(hDlg, SW_SHOW);

	return;

}

void cmdHideWindow(HWND hDlg)
{
	NOTIFYICONDATA nid;

	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.uID = 0;
	nid.hWnd = hDlg;

	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_FIELDSERVER));
	lstrcpy(nid.szTip, "ServerField");
	nid.uCallbackMessage = WM_TRAY_NOTIFICATION;
	Shell_NotifyIcon(NIM_ADD, &nid);
	ShowWindow(hDlg, SW_HIDE);

	return;

}

void cmdPopupMenu(HWND hDlg)
{
	HMENU hMenu, hPopupMenu;
	POINT pt;

	hMenu = LoadMenu(g_hInst,MAKEINTRESOURCE(IDR_POPMENU));
	hPopupMenu = GetSubMenu(hMenu,0);
	GetCursorPos(&pt);
	SetForegroundWindow(hDlg);
	TrackPopupMenu(hPopupMenu,TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
					pt.x, pt.y, 0, hDlg, NULL);
	SetForegroundWindow(hDlg);
	DestroyMenu(hPopupMenu);
	DestroyMenu(hMenu);

	return;
}

BOOL CALLBACK MainDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	g_hWindow = hDlg;
	HWND pWnd = NULL;
	
	switch(iMessage)
	{
	case WM_INITDIALOG :
		initDialog(hDlg);
		break;
	
	case RAN_MSG_START:
		cmdStartOrStop(hDlg);
		break;

	case RAN_MSG_STOP:
		cmdStartOrStop(hDlg);
		break;

	case RAN_MSG_EXIT:
		pWnd = GetDlgItem(hDlg, IDC_CLOSE);
		EnableWindow(pWnd, FALSE);
		cmdExit(hDlg);
		break;

	case WM_FINALCLEANUPFINISH :
		cmdFinalExit(hDlg);
		return true;

	case WM_TIMER :
		if (SERVER_CONTROLLER::bInit == false)
		{
			if (wParam == SERVER_CONTROLLER_TIMER_ID)
			{
				::KillTimer(hDlg, SERVER_CONTROLLER_TIMER_ID);
				executeCmdParameter(hDlg);
			}
			SERVER_CONTROLLER::bInit = true;
		}
		break;
	case WM_INITMENUPOPUP:
		if (g_pServer != NULL && g_pServer->IsRunning()){
			ModifyMenu(HMENU(wParam),IDC_BTN_STOP,MF_BYCOMMAND | MF_STRING, IDC_BTN_STOP, "Stop");
			ModifyMenu(HMENU(wParam),IDC_BTN_PAUSE,MF_BYCOMMAND | MF_ENABLED, IDC_BTN_PAUSE, "Pause");
		}else{
			ModifyMenu(HMENU(wParam),IDC_BTN_STOP,MF_BYCOMMAND | MF_STRING, IDC_BTN_STOP, "Start");
			ModifyMenu(HMENU(wParam),IDC_BTN_PAUSE,MF_BYCOMMAND | MF_GRAYED, IDC_BTN_PAUSE, "Pause");
		}
		break;
	case WM_SYSCOMMAND:
		switch(LOWORD(wParam))
		{
		case SC_CLOSE:
			cmdHideWindow(hDlg);
			return TRUE;
		}
		break;
	case WM_TRAY_NOTIFICATION:
		switch(lParam)
		{
		case WM_LBUTTONUP:
			cmdShowWindow(hDlg);						
			return TRUE;
		case WM_RBUTTONUP:
			cmdPopupMenu(hDlg);
			return TRUE;
		}
		return FALSE;		
	case WM_COMMAND :
		switch (LOWORD(wParam))
		{		
		case IDC_BTN_EXECUTE :
			executeCommand(hDlg);
			return TRUE;

		case IDC_BTN_STOP :
			cmdStartOrStop(hDlg);
			setFirstFocus(hDlg);
			return TRUE;
			
		case IDC_BTN_PAUSE :
			cmdPause(hDlg);
			setFirstFocus(hDlg);
			return TRUE;
			
		case IDC_CLOSE :			
			if( MessageBox(hDlg,"Do you really want to exit?", "Warning", MB_YESNO | MB_ICONWARNING ) == IDYES){
				pWnd = GetDlgItem(hDlg, IDC_CLOSE);
				EnableWindow(pWnd, FALSE);
				cmdExit(hDlg);			
			}
			return TRUE;
		
		case IDC_OPEN :
			cmdShowWindow(hDlg);
			return TRUE;

		case IDC_BTN_CONNECT_SESSION:
			if (g_pServer != NULL && g_pServer->IsRunning())
			{
				g_pServer->SessionConnectSndSvrInfo();
			}			
			return TRUE;
			
		case IDC_EDITCONSOLE :
			switch (HIWORD(wParam))
			{			
			case EN_MAXTEXT:			
				SetWindowText((HWND)lParam, "");
				break;
			}
			return TRUE;
			break;
			
        case IDC_EDITCONSOLE_INFO :
            switch (HIWORD(wParam))
			{			
			case EN_MAXTEXT:			
				SetWindowText((HWND)lParam, "");
				break;
			}
			return TRUE;
			break;

		case IDC_EDITCONSOLE_STATS :
			switch (HIWORD(wParam))
			{			
			case EN_MAXTEXT:			
				SetWindowText((HWND)lParam, "");
				break;
			}
			return TRUE;
			break;
		}
		return FALSE;
	}
	return FALSE;
}