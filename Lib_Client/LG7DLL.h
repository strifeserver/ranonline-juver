/////////////////////////////////////////////////////////////////////////////
//	FileName	: LG7DLL.h
//	Project		: RanClientLib
//	Coder		: LG-7

#pragma once

class CLG7_DLL
{
public:
	virtual HRESULT		OneTimeSceneInitServer() = 0;

	/////////////////////////////////////////////////////////////////////////////
	// LG-7 AntiFlood
	virtual BOOL		SetAntiFlood(DWORD dwMax, DWORD dwCur)	= 0;
	virtual BOOL		IsAntiFloodContinue()					= 0;
	virtual DWORD		GetClientCheckTime()					= 0;
	virtual BOOL		IsClientCHECK()							= 0;
	virtual BOOL		SetClientCHECK(BOOL bCheck)				= 0;
	virtual BOOL		SetClientCheckTime(DWORD dwTime)		= 0;
	/////////////////////////////////////////////////////////////////////////////
};