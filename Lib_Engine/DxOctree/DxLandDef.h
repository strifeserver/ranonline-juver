#ifndef DXLANDDEF_H_
#define DXLANDDEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Common/SerialFile.h"
//class CSerialFile;

enum  EMLANDMAN
{
//	MAXLANDSID		= 32, 
	MAXLANDMID		= 256,	
	MAXLANDSID		= 256, // �δ� ������ ���� SID�� �÷ȴ�.
	MAXLANDNAME		= 128,
};

struct SLAND_FILEMARK_000
{
	DWORD	dwNAVI_MARK;	//	�׺���̼� �޽�.
	DWORD	dwGATE_MARK;	//	���Ա�.
	DWORD	dwCOLL_MARK;	//	�浹��.
};

struct SLAND_FILEMARK_100
{
	DWORD	dwNAVI_MARK;	//	�׺���̼� �޽�.
	DWORD	dwGATE_MARK;	//	���Ա�.
	DWORD	dwCOLL_MARK;	//	�浹��.
	DWORD	dwWEATHER_MARK;	//	����.
};

struct SLAND_FILEMARK
{
	enum { VERSION = 0x0101, };

	DWORD	dwNAVI_MARK;	//	�׺���̼� �޽�.
	DWORD	dwWEATHER_MARK;	//	����.
	DWORD	dwGATE_MARK;	//	���Ա�.
	DWORD	dwCOLL_MARK;	//	�浹��.
	
	SLAND_FILEMARK()
		: dwNAVI_MARK(0)
		, dwWEATHER_MARK(0)
		, dwGATE_MARK(0)
		, dwCOLL_MARK(0)
	{
	}

	void Assign( SLAND_FILEMARK_000 &sOldMark );
	void Assign( SLAND_FILEMARK_100 &sOldMark );

	BOOL LoadSet( CSerialFile &SFile );
	BOOL SaveSet( CSerialFile &SFile );
};

#endif // DXLANDDEF_H_