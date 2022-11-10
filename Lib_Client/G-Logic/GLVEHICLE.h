#ifndef GLVEHICLE_H_
#define GLCEHICLE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./GLItem.h"
#include "../../Lib_Engine/G-Logic/GLDefine.h"

#include <hash_map>

class GLChar;

/*bike color , Juver, 2017/11/13 */
struct SVEHICLE_COLOR_EDIT
{
	WORD	m_wColor[BIKE_COLOR_SLOT_PART_SIZE];

	SVEHICLE_COLOR_EDIT()
	{
		for( int i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
			m_wColor[i] = 0;
	}
};

struct SVEHICLEITEMINFO
{
	VEHICLE_TYPE	m_emTYPE;
	int				m_nFull;
	SITEMCUSTOM		m_PutOnItems[VEHICLE_ACCETYPE_SIZE];
	bool			m_bBooster; /*vehicle booster system, Juver, 2017/08/10 */
	WORD			m_wColor[BIKE_COLOR_SLOT_PART_SIZE];	/*bike color , Juver, 2017/11/13 */

	SVEHICLEITEMINFO () :
		m_emTYPE(VEHICLE_TYPE_NONE),
		m_nFull(0),
		m_bBooster(false) /*vehicle booster system, Juver, 2017/08/10 */
	{
		/*bike color , Juver, 2017/11/13 */
		for( int i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
			m_wColor[i] = 0;
	}

	SVEHICLEITEMINFO ( const SVEHICLEITEMINFO& value ) { operator=( value ); }
	SVEHICLEITEMINFO& operator= ( const SVEHICLEITEMINFO& rvalue );

};

typedef stdext::hash_map<DWORD,SVEHICLEITEMINFO>	VEHICLEITEMINFO_MAP;
typedef VEHICLEITEMINFO_MAP::iterator				VEHICLEITEMINFO_MAP_ITER;

struct CLIENT_VEHICLE
{
	VEHICLE_TYPE	m_emTYPE;
	DWORD			m_dwGUID;						// Ż���� GUID
	SNATIVEID		m_sVehicleID;					// ��ȯ�� ��û�� Ż�� �������� Mid/Sid
	SITEMCLIENT		m_PutOnItems[VEHICLE_ACCETYPE_SIZE];
	WORD			m_wColor[BIKE_COLOR_SLOT_PART_SIZE];	/*bike color , Juver, 2017/11/13 */
	
	DWORD			m_dwDriverID;
	CLIENT_VEHICLE() 
		: m_emTYPE ( VEHICLE_TYPE_NONE )
		, m_dwGUID ( 0 )
		, m_sVehicleID ( NATIVEID_NULL() )
		, m_dwDriverID( 0 )
	{
		/*bike color , Juver, 2017/11/13 */
		for( int i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
			m_wColor[i] = 0;
	}
};


struct GLVEHICLE
{
	enum
	{	
		COLOR_VERSION = 0x0001,		/*bike color , Juver, 2017/11/13 */
	};

	VEHICLE_TYPE	m_emTYPE;
	DWORD			m_dwGUID;						// Ż���� GUID
	DWORD			m_dwOwner;						// ������ charID
	SNATIVEID		m_sVehicleID;					// ��ȯ�� ��û�� Ż�� �������� Mid/Sid
	int				m_nFull;
	SITEMCUSTOM		m_PutOnItems[VEHICLE_ACCETYPE_SIZE];
	float			m_fSpeedRate;					// Ż���� �ӵ� ����( ���� �κ��� ��ģ�� )
	float			m_fSpeedVol;					// Ż���� �ӵ� ���밪( ���� �κ��� ��ģ�� )
	SNATIVEID		m_sSkinID;						// Ż���� ��Ų ������ Item ID
	bool			m_bActiveValue;					// ���� Ż���� �������� Ȯ��
	bool			m_bBooster;						/*vehicle booster system, Juver, 2017/08/10 */
	WORD			m_wColor[BIKE_COLOR_SLOT_PART_SIZE];	/*bike color , Juver, 2017/11/13 */
	DWORD			m_dwDriverID;
	// constructor & operator
	GLVEHICLE () :
		m_emTYPE(VEHICLE_TYPE_NONE),
		m_dwGUID(UINT_MAX),
		m_dwOwner(0),
		m_nFull(0),
		m_sVehicleID(NATIVEID_NULL()),
		m_fSpeedRate( 0.0f ),
		m_fSpeedVol( 0.0f ),
		m_sSkinID ( NATIVEID_NULL() ),
		m_bActiveValue ( false ),
		m_dwDriverID(0),
		m_bBooster(false) /*vehicle booster system, Juver, 2017/08/10 */
	{
		/*bike color , Juver, 2017/11/13 */
		for( int i=0; i<BIKE_COLOR_SLOT_PART_SIZE; ++i )
			m_wColor[i] = 0;
	}

	GLVEHICLE ( const GLVEHICLE& value ) { operator=( value ); }
	GLVEHICLE& operator= ( const GLVEHICLE& rvalue );

	BOOL GETPUTONITEMS_BYBUF ( CByteStream &ByteStream ) const;

	/*bike color , Juver, 2017/11/13 */
	BOOL GETCOLORS_BYBUF ( CByteStream &ByteStream ) const;
	BOOL SETCOLORS_BYBUF ( CByteStream &ByteStream );

	void ASSIGN ( const GLVEHICLE& sVehicleData );
	void RESET ();
	bool IncreaseFull ( const WORD volume, const BOOL bRatio = TRUE );

	BOOL IsNotEnoughFull () { return m_nFull < 10; }

	BOOL IsActiveValue() { return m_bActiveValue; }
	VOID SetActiveValue( bool bActiveValue ) { m_bActiveValue = bActiveValue; }
	SNATIVEID GetSkinID()	{ return m_sSkinID; }


	SITEMCUSTOM GetSlotitembySuittype ( EMSUIT emSuit );
	void		SetSlotItem ( EMSUIT emType, SITEMCUSTOM sCustomItem);
	void		ReSetSlotItem ( EMSUIT emType);
	BOOL		CheckSlotItem ( SNATIVEID sNativeID, EMSUIT emSUIT );
//    EMPIECECHAR GetPieceFromSlot ( VEHICLE_ACCESSORYTYPE emType );

	// access
	BOOL		LoadFile ( const char* szFileName, VEHICLE_TYPE emType );

	void		UpdateTimeLmtItem ( GLChar* pChar );
	void		ITEM_UPDATE();

	float		GetSpeedRate()	{ return m_fSpeedRate; }
	float		GetSpeedVol()	{ return m_fSpeedVol; }

	/*vehicle booster system, Juver, 2017/08/10 */
	void		SetBooster( bool bEnable ){	m_bBooster = bEnable; }
	bool		IsBooster()	{ return m_bBooster; }
};

typedef GLVEHICLE* PGLVEHICLE;

namespace COMMENT
{
	extern std::string VEHICLE_TYPE[VEHICLE_TYPE_SIZE];
	extern std::string VEHICLE_SUBTYPE_HOVER[VEHICLE_SUBTYPE_SIZE];
	extern std::string VEHICLE_SUBTYPE_BIKE[VEHICLE_SUBTYPE_SIZE];

	/* vehicle car, cart, Juver, 2018/02/13 */
	extern std::string VEHICLE_SUBTYPE_CAR[VEHICLE_SUBTYPE_SIZE];
	extern std::string VEHICLE_SUBTYPE_CART[VEHICLE_SUBTYPE_SIZE];
};

#endif // GLVEHICLE_H_