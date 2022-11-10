#pragma once

#include "string"
#include "../Lib_ClientUI/Interface/BasicChatRightBody.h"
#include "CList.h"
#include "GLLandManClient.h"
#include "GLogicData.h"
#include "GLogicEx.h" //itemmall
#include "GLCharacter.h"
#include "GLMapList.h"
#include "GLCrowTracer.h"
#include "GLCOPY.h"
#include "GLActiveMap.h"
#include "GLPetClient.h"
#include "GLSummonClient.h"

/*get process command, Juver, 2017/06/08 */
#include "GLProcessInfo.h"

//#define _SYNC_TEST

class GLGaeaClient : public GLMapList , public GLCrowTracer, public GLActiveMap
{
protected:
	char						m_szAppPath[MAX_PATH];
	HWND						m_hWnd;

	float						m_fAge;
	LPDIRECT3DDEVICEQ			m_pd3dDevice;
	PLANDMANCLIENT				m_pLandMClient;

	GLCharacter					m_Character;
	GLPetClient					m_Pet;
	
	DETECTMAP					m_vecDetectID;
	D3DXVECTOR3					m_vCharPos;

	bool						m_bSCHOOL_FREEPK;	// �п��� ���� PK
	bool						m_bBRIGHTEVENT;		// ���� �̺�Ʈ
	
	bool						m_bCLUBBATTLE;		// ������
	float						m_fCLUBBATTLETimer;

	bool						m_bClubDeathMatch;
	float						m_fClubDeathMatchTimer;

	CTime						m_cServerTime;			// ������ ���� �ð�
	char						m_szShopInfoFile[MAX_PATH];

public:
	/*skill summon, Juver, 2017/10/08 */
	GLSummonClient				m_Summon[SKILL_SUMMON_MAX_CLIENT_NUM];

public:
	CDM_RANK_VEC				m_vecCdmRank;
	SCDM_RANK_EX				m_sMyCdmRank;
	PK_HISTORY_VEC				m_vecPKHistory;
		/*get process command, Juver, 2017/06/08 */
	PROCESS_INFO_DATA_MAP_CLIENT	m_mapProcessInfo;

	//pk ranking
	PLAYER_RANKING_STATUS_VEC		m_vecPlayerRank;
	PLAYER_RANKING_EX				m_sMyPKRank;

public:
	bool IsSchoolFreePk ()		{ return m_bSCHOOL_FREEPK; }
	bool IsBRIGHTEVENT ()		{ return m_bBRIGHTEVENT; }
	bool IsClubDeathMatch()		{ return m_bClubDeathMatch; }

public:
	HRESULT OneTimeSceneInit ( const char* szAppPath, HWND hWnd );
	HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RestoreDeviceObjects ();

	HRESULT InvalidateDeviceObjects ();
	HRESULT DeleteDeviceObjects ();

	HRESULT FrameMove ( float fTime, float fElapsedTime );
	
	HRESULT Render ( CLIPVOLUME &CV );
	HRESULT RenderEff ( CLIPVOLUME &CV );
	void	RenderPickAlpha();

protected:
	PLANDMANCLIENT CreateLandMClient ( char* szLandFileName, D3DXVECTOR3 &vBasicPos );
	PLANDMANCLIENT CreateLandMClient ( SNATIVEID sMapID, D3DXVECTOR3 &vBasicPos );
	PLANDMANCLIENT CreateInstantMapClient ( SNATIVEID sBaseMapID, SNATIVEID sInstantMapID, D3DXVECTOR3 &vBasicPos );

protected:
	HRESULT MoveActiveMap ( SNATIVEID sMapID, D3DXVECTOR3 &vPos );
	HRESULT CreateInstantMap ( SNATIVEID sBaseMapID, SNATIVEID sInstantMapID, D3DXVECTOR3 &vBasicPos );

public:
	HRESULT SetActiveMap ( char* szLandFileName, D3DXVECTOR3 &vBasicPos );
	HRESULT SetActiveMap ( SNATIVEID sMapID, D3DXVECTOR3 &vBasicPos );
	PLANDMANCLIENT GetActiveMap ();
	SNATIVEID GetActiveMapID ();

	HRESULT MoveActiveMap ( NET_MSG_GENERIC *nmg );
	HRESULT CreateInstantMap ( NET_MSG_GENERIC *nmg );
	HRESULT DropOutCrow ( NET_MSG_GENERIC *nmg );
	HRESULT ReBirthFB ( NET_MSG_GENERIC* nmg );
	HRESULT ReCallFB ( NET_MSG_GENERIC* nmg );
	HRESULT ReLvMustLeaveFB ( NET_MSG_GENERIC* nmg );
	HRESULT ReqBusFB ( NET_MSG_GENERIC* nmg );
	HRESULT ReqTaxiFB ( NET_MSG_GENERIC* nmg );
	HRESULT TeleportFB ( NET_MSG_GENERIC* nmg );

public:
	HRESULT ReqClubDeathMatchInfo();

	//dmk14 | 11-4-16 | pk ranking
	HRESULT ReqPlayerRankingInfo ();

public:
	DWORD GetMobNameColor ( DWORD dwGlobID );
	BOOL IsMapCollsion( D3DXVECTOR3& vTargetPt, D3DXVECTOR3& vFromPt );

public:
	GLCOPY* GetCopyActor ( const STARGETID &sTARID )	{ return GetCopyActor ( sTARID.emCrow, sTARID.dwID ); }
	GLCOPY* GetCopyActor ( const EMCROW emCrow, const DWORD dwID );
	GLCOPY* GetCopyActor ( const std::string &strName );
	GLCharacter* GetCharacter ()						{ return &m_Character; }
	const D3DXVECTOR3 &GetCharacterPos ()				{ return m_Character.GetPosition(); }
	SCHARDATA2& GetCharacterData ()						{ return m_Character.GetCharData(); }
	GLCHARLOGIC& GetCharacterLogic ()					{ return m_Character.GetCharLogic(); }

	PGLCHARCLIENT GetChar ( DWORD dwID );

	BOOL ValidCheckTarget ( const STARGETID & sTargetID );
	DETECTMAP* DetectCrowDie ( const D3DXVECTOR3 &vFrom, const D3DXVECTOR3 &vTarget );
	DETECTMAP* DetectCrow ( DWORD emCrow, const D3DXVECTOR3 &vFrom, const D3DXVECTOR3 &vTarget );
	DETECTMAP* DetectCrow ( DWORD emCrow, const D3DXVECTOR3 &vTarPos, const float fLength );
	BOOL IsCollisionMobToPoint ( const D3DXVECTOR3 &vPoint, const WORD wBodyRadius );

	D3DXVECTOR3* FindCharPos ( std::string strName );
	D3DXVECTOR3* FindCharHeadPos ( std::string strName );
	D3DXVECTOR3* FindCharHeadPos ( DWORD dwGaeaID );
	D3DXVECTOR3* FindMaterialHeadPos ( DWORD dwGaeaID );

	CTime		 GetCurrentTime () { return m_cServerTime; }
	void		 SetCurrentTime ( CTime cServerTime ) { m_cServerTime = cServerTime; }

	// PET
	GLPetClient* GetPetClient () { return &m_Pet; }
	HRESULT		 CreatePET ( NET_MSG_GENERIC* nmg );
	void		 PetSkinPackApplyEffect();

	// SUMMON
	/*skill summon, Juver, 2017/10/08 */
	GLSummonClient* GetSummonClient( DWORD dwguid );// { return &m_Summon; }
	HRESULT			CreateSummon( NET_MSG_GENERIC* nmg );
	PGLANYSUMMON	GetSummon ( DWORD dwID );

public:
	void	SetCharacterSimple( BOOL bCharacterSimple ); /*character simple, Juver, 2017/10/01 */
	
public:
	void MsgProcess ( NET_MSG_GENERIC* nmg );

public:
	virtual DxLandMan* getactivemap()
	{
		PLANDMANCLIENT pMapClient = GetActiveMap ();
		if ( !pMapClient )	return NULL;

		return pMapClient->GetLandMan();
	}

public:
	virtual BOOL IsVisibleCV ( const STARGETID & sTargetID );
	virtual D3DXVECTOR3 GetTargetPos ( const STARGETID &sTargetID );
	virtual DxSkinChar* GetSkinChar ( const STARGETID &sTargetID );
	virtual float GetCrowDir ( const STARGETID &sTargetID );

protected:
	GLGaeaClient(void);

public:
	~GLGaeaClient(void);

public:
	static GLGaeaClient& GetInstance();
};

