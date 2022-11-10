// ItemBox.cpp : implementation file
//

#include "stdafx.h"
#include "EditorItem.h"
#include "ItemBox.h"
#include "EtcFunction.h"

// ItemBox dialog

IMPLEMENT_DYNAMIC(CItemBox, CDialog)

CItemBox::CItemBox(CWnd* pParent /*=NULL*/)
	: CDialog(CItemBox::IDD, pParent)
{
	m_vecData.clear();
	m_vecResult.clear();
}

CItemBox::~CItemBox()
{
}

void CItemBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SELECT, m_listSELECT );
	DDX_Control(pDX, IDC_LIST_SELECTED, m_listSELECTED );
}


BEGIN_MESSAGE_MAP(CItemBox, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnBnClickedButtonInsert)
	ON_LBN_SELCHANGE(IDC_LIST_SELECT, OnLbnSelchangeListSelect)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// ItemBox message handlers
BOOL CItemBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_vecSELECTED.clear();

	ReadData();
	ShowSelected();
	ResetSelection();

	const int nSEARCHSIZE = 4;

	std::string strSEARCH[nSEARCHSIZE] =
	{
		"Search Name",
		"Search MID",
		"Search SID",
		"Search Type",
	};

	SetWin_Combo_Init( this, IDC_COMBO_SEARCH, strSEARCH, nSEARCHSIZE );
	SetWin_Text( this, IDC_EDIT_SEARCH, "" );

	SearchData();

	return TRUE;
}

void CItemBox::ReadData()
{
	m_vecData.clear();
	for ( int MID = 0; MID < GLItemMan::MAX_MID; MID++ )
	{
		for ( int SID = 0; SID < GLItemMan::MAX_SID; SID++ )
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem ( MID, SID );
			if ( !pItem )	continue;

			m_vecData.push_back( pItem->sBasicOp.sNativeID );
		}
	}
}

void CItemBox::ShowSelections()
{
	m_listSELECT.ResetContent();
	m_listSELECT.SetRedraw( FALSE );

	for( int i = 0; i < (int) m_vecResult.size(); ++ i )
	{
		SNATIVEID sID = m_vecResult[i];
		SITEM* pItem = GLItemMan::GetInstance().GetItem ( sID );
		if ( !pItem )	continue;

		CString strNAME;
		strNAME.Format ( "[%03d/%03d] %s", sID.wMainID, sID.wSubID, pItem->GetName() );

		int nIndex = m_listSELECT.AddString ( strNAME );
		m_listSELECT.SetItemData ( nIndex, pItem->sBasicOp.sNativeID.dwID );
	}

	m_listSELECT.SetRedraw( TRUE );
}

void CItemBox::ShowSelected()
{
	m_listSELECTED.ResetContent();
	m_listSELECTED.SetRedraw( FALSE );

	int nTOTAL = (int)m_vecSELECTED.size();
	for ( int i = 0; i < nTOTAL; ++i )
	{
		ITEM::SBOX_ITEM sDATA = m_vecSELECTED[i];

		SITEM* pItem = GLItemMan::GetInstance().GetItem ( sDATA.nidITEM );
		if ( !pItem )	continue;

		CString strNAME;
		strNAME.Format ( "[%03d/%03d] %s [%d]", pItem->sBasicOp.sNativeID.wMainID, pItem->sBasicOp.sNativeID.wSubID, pItem->GetName(), sDATA.dwAMOUNT );

		int nIndex = m_listSELECTED.AddString ( strNAME );
		m_listSELECTED.SetItemData ( nIndex, pItem->sBasicOp.sNativeID.dwID );
	}

	m_listSELECTED.SetRedraw( TRUE );
}

void CItemBox::OnBnClickedButtonInsert()
{
	WORD wMID = GetWin_Num_int( this, IDC_EDIT_SEL_MID );
	WORD wSID = GetWin_Num_int( this, IDC_EDIT_SEL_SID );
	WORD wNUM = GetWin_Num_int( this, IDC_EDIT_SEL_NUM );

	SITEM* pItem = GLItemMan::GetInstance().GetItem ( wMID, wSID );
	if ( pItem )
	{
		ITEM::SBOX_ITEM sBOXITEM;
		sBOXITEM.nidITEM = pItem->sBasicOp.sNativeID;
		sBOXITEM.dwAMOUNT = wNUM;
		m_vecSELECTED.push_back( sBOXITEM );

		ShowSelected();
	}
}

void CItemBox::OnLbnSelchangeListSelect()
{
	int nSel = m_listSELECT.GetCurSel();

	if ( nSel < 0 ) return;

	DWORD dwData = (DWORD) m_listSELECT.GetItemData ( nSel );
	SITEM* pItem = GLItemMan::GetInstance().GetItem ( dwData );
	if ( pItem )
	{
		SetWin_Num_int( this, IDC_EDIT_SEL_MID, pItem->sBasicOp.sNativeID.wMainID );
		SetWin_Num_int( this, IDC_EDIT_SEL_SID, pItem->sBasicOp.sNativeID.wSubID );
		SetWin_Text( this, IDC_EDIT_SEL_NAME, pItem->GetName() );
	}
	else
	{
		ResetSelection();
	}
}

void CItemBox::ResetSelection()
{
	SetWin_Num_int( this, IDC_EDIT_SEL_MID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_SEL_SID, 65535 );
	SetWin_Text( this, IDC_EDIT_SEL_NAME, "" );
	SetWin_Num_int( this, IDC_EDIT_SEL_NUM, 1 );
}

void CItemBox::OnBnClickedButtonRemove()
{
	int nSel = m_listSELECTED.GetCurSel();

	if ( nSel < 0 ) return;
	if ( nSel >= (int)m_vecSELECTED.size() )	return;
	DWORD dwData = (DWORD) m_listSELECTED.GetItemData ( nSel );

	VEC_ITER iter = m_vecSELECTED.begin();
	for( int nITER = 0; iter!=m_vecSELECTED.end(); ++iter, ++nITER )
	{
		if( nITER==nSel && (*iter).nidITEM.dwID == dwData )
		{
			m_vecSELECTED.erase( iter );
			ShowSelected();
			break;
		}
	}
}

void CItemBox::OnBnClickedButtonSearch()
{
	SearchData();
}

void CItemBox::SearchData()
{
	int nSEARCH =  GetWin_Combo_Sel( this, IDC_COMBO_SEARCH );
	std::string strSEARCH = GetWin_Text( this, IDC_EDIT_SEARCH );

	m_vecResult.clear();

	if ( strSEARCH.size() <= 0 )
	{
		m_vecResult = m_vecData;
	}
	else
	{
		for( int i = 0; i < (int)m_vecData.size(); ++ i )
		{
			SNATIVEID sID = m_vecData[i];
			SITEM* pItem = GLItemMan::GetInstance().GetItem ( sID );
			if ( !pItem )	continue;

			CString strFIND;
			switch( nSEARCH )
			{
			case 0:
				{
					strFIND.Format( "%s", pItem->GetName() );
				}break;
			case 1:
				{
					strFIND.Format( "%d", pItem->sBasicOp.sNativeID.wMainID );
				}break;
			case 2:
				{
					strFIND.Format( "%d", pItem->sBasicOp.sNativeID.wSubID );
				}break;
			case 3:
				{
					strFIND.Format( "%d", pItem->sBasicOp.emItemType );
				}break;
			};

			if ( strFIND.GetLength() <= 0 )	continue;

			std::string strSEARCH1 = strSEARCH.c_str();
			std::string strSEARCH2 = strFIND.GetString();
			std::transform ( strSEARCH1.begin(), strSEARCH1.end(), strSEARCH1.begin(), tolower );
			std::transform ( strSEARCH2.begin(), strSEARCH2.end(), strSEARCH2.begin(), tolower );

			unsigned found = strSEARCH2.find(strSEARCH1.c_str());
			if (found!=std::string::npos)
			{
				m_vecResult.push_back( sID );
			}
		}
	}

	ShowSelections();
}
