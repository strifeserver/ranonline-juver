#include "stdafx.h"
#include "./GLAGLandMan.h"
#include "./GLAgentServer.h"
#include "../Lib_Engine/DxOctree/DxLandMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GLAGLandMan::GLAGLandMan(void) :
	m_dwClubMapID(UINT_MAX),
	m_bGuidBattleMap(false),
	m_bClubDeathMatchMap(false),
	m_bClubWarLock(false),			/*clubwar map lock, Juver, 2017/06/27 */
	m_bPVPTyrannyMap(false),		/*pvp tyranny, Juver, 2017/08/24 */
	m_bPVPSchoolWarsMap(false),		/*school wars, Juver, 2018/01/19 */
	m_bPVPCaptureTheFlagMap(false)	/*pvp capture the flag, Juver, 2018/01/24 */
{
}

GLAGLandMan::~GLAGLandMan(void)
{
	CleanUp ();
}

BOOL GLAGLandMan::LoadWldFile ( const char* szWldFile, bool bLandGateLoad )
{
	HRESULT hr;

	m_sLevelHead.m_strWldFile = szWldFile;

	char szPathName[MAX_PATH] = {0};
	StringCchCopy ( szPathName, MAX_PATH, DxLandMan::GetPath() );
	StringCchCat ( szPathName, MAX_PATH, m_sLevelHead.m_strWldFile.c_str() );

	char szFileType[FILETYPESIZE];
	DWORD dwVersion;

	CSerialFile SFile;
	if ( hr = SFile.OpenFile ( FOT_READ, szPathName ) )
	{
		//	Note : ���� ���� ����Ȯ��.
		//
		SFile.GetFileType( szFileType, FILETYPESIZE, dwVersion );

		if ( strcmp(DxLandMan::FILEMARK,szFileType) )
		{
			CDebugSet::ErrorCode( "GLAGLandMan::LoadWldFile", "Incorrect file: %s head expected:%s~result%s", m_sLevelHead.m_strWldFile.c_str(), DxLandMan::FILEMARK, szFileType );
			return FALSE;
		}

		//update NSLANDMAN_SUPPORT for new file support
		if ( !NSLANDMAN_SUPPORT::IsLandManSupported( dwVersion ))
		{
			CDebugSet::ErrorVersion( "GLAGLandMan::LoadWldFile", SFile.GetFileName(), dwVersion );
			return FALSE;
		}

		if ( dwVersion >= DxLandMan::VERSION_ENCODE )
			SFile.SetEncodeType( EMBYTECRYPT_WLD );

		SLAND_FILEMARK sLandMark;

		//	Note : .wld ������ ��ID�� ������� ����.
		SNATIVEID sMapID;
		SFile >> sMapID.dwID;

		char szMapName[MAXLANDNAME];
		SFile.ReadBuffer ( szMapName, sizeof(char)*MAXLANDNAME );

		sLandMark.LoadSet ( SFile );

		//	Note : ���Ա� ���� �б�.
		//
		if ( sLandMark.dwGATE_MARK && bLandGateLoad )
		{
			SFile.SetOffSet ( sLandMark.dwGATE_MARK );
			m_cLandGateMan.Load ( SFile );
		}
	}

	return TRUE;
}

BOOL GLAGLandMan::LoadFile ( const char *szFile )
{
	GASSERT(szFile);

	BOOL bOk(FALSE);
	bOk = GLLevelFile::LoadFile ( szFile, TRUE, NULL );
	if ( !bOk )			return FALSE;

	bOk = LoadWldFile ( m_sLevelHead.m_strWldFile.c_str(), GLLevelFile::GetFileVer()<=VERSION_BEFORE_GATE );
	if ( !bOk )			return FALSE;

	return TRUE;
}

void GLAGLandMan::CleanUp ()
{
	m_setPC.clear();
	m_dwClubMapID			= UINT_MAX;
	m_bGuidBattleMap		= false;
	m_bClubDeathMatchMap	= false;

	m_bClubWarLock			= false;	/*clubwar map lock, Juver, 2017/06/27 */
	m_bPVPTyrannyMap		= false;	/*pvp tyranny, Juver, 2017/08/24 */
	m_bPVPSchoolWarsMap		= false;	/*school wars, Juver, 2018/01/19 */
	m_bPVPCaptureTheFlagMap	= false;	/*pvp capture the flag, Juver, 2018/01/24 */

	m_cLandGateMan.CleanUp ();
}

bool GLAGLandMan::DropPC ( DWORD dwID )
{
	m_setPC.insert ( dwID );

	return true;
}

bool GLAGLandMan::DropOutPC ( DWORD dwID )
{
	SETPC_ITER pos = m_setPC.find ( dwID );
	if ( pos==m_setPC.end() )	return false;

	m_setPC.erase ( pos );

	return true;
}

void GLAGLandMan::SENDTOALLCLIENT ( LPVOID nmg )
{
	PGLCHARAG pCHAR = NULL;
	SETPC_ITER pos = m_setPC.begin();
	SETPC_ITER end = m_setPC.end();
	for ( ; pos!=end; ++pos )
	{
		pCHAR = GLAgentServer::GetInstance().GetChar ( (*pos) );
		if ( !pCHAR )	
		{
			continue;
		}
		else
		{
			GLAgentServer::GetInstance().SENDTOCLIENT ( pCHAR->m_dwClientID, nmg );
		}
	}
}
