#pragma once

#include <map>
#include <list>
#include <string>
#include <algorithm>

#include "DxSkinMesh9.h"
#include "CFileFind.h"

class DxSkinMeshMan
{
public:
	typedef std::map<std::string,DxSkinMesh9*>				SKINMESHMAP;
	typedef std::map<std::string,DxSkinMesh9*>::iterator	SKINMESHMAP_ITER;

	typedef std::list<DxSkinMesh9*>							SKINMESHLIST;
	typedef std::list<DxSkinMesh9*>::iterator				SKINMESHLIST_ITER;

protected:
	char			m_szPath[MAX_PATH];
	SKINMESHMAP		m_SkinMeshMap;
	SKINMESHMAP		m_PreLoadSkinMeshMap;
	CFileFindTree	m_FileTree;

public:
	DxSkinMesh9* FindSkinMesh ( const char* szSkinMesh );
	char*		GetPath () { return m_szPath; } 

public:
	DxSkinMesh9* LoadSkinMesh( const char* szSkinMesh, const char* szSkeleton, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread );
	BOOL PreLoad ( const char* szSkinList, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread );
	CFileFindTree*	GetFileTree()	{	return &m_FileTree; }

public:
	void OneTimeSceneInit ( char* szPath );
	HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT InvalidateDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT DeleteDeviceObjects();

public:
	HRESULT CleanUp ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT DoInterimClean ( LPDIRECT3DDEVICEQ pd3dDevice );

protected:
	DxSkinMeshMan(void);

public:
	~DxSkinMeshMan(void);

public:
	static DxSkinMeshMan& GetInstance();
};
