#include "stdafx.h"

#include "../DxCommon/Collision.h"
#include "../DxCommon/DxLightMan.h"
#include "../DxCommon/DxEnvironment.h"

#include "./DxStaticMesh.h"
#include "./DxPieceEff.h"
#include "./DxPieceStaticAni.h"
#include "./DxPieceContainer.h"
#include "./DxPieceTexEff.h"

#include "./DxPiece.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void DxPiece::Load_EP9( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, DxPieceEdit* pSrc )
{
	DWORD dwVER(0);
	DWORD dwSIZE(0);

	SFile >> dwVER;
	SFile >> dwSIZE;

	if ( dwVER == 0x0100 )
	{
		SFile >> m_vMax;
		SFile >> m_vMin;

		SFile.ReadBuffer( &m_matWorld, sizeof(D3DXMATRIX) );

		//lightmaps data!
		BOOL b(FALSE);
		std::string str;

		SFile >> b;
		SFile >> b;
		SFile >> str;
		SFile >> str;
		SFile >> str;
		SFile >> str;

		// Note : ������ ���� ��� ���
		if( !pSrc )
		{
			m_vStaticMax = m_vMax;
			m_vStaticMin = m_vMin;

			// Note : �ڽſ� �µ��� StaticAABB�� Center, Length�� �ٲ۴�.
			D3DXMatrixAABBTransform( m_vStaticMax, m_vStaticMin, m_matWorld );
			m_vCenter = (m_vStaticMax+m_vStaticMin)*0.5f;
			m_fLength = m_fLength*m_fLength;

			// Note : �ڽŰ� �´�� �ִ� ���� üũ�� �Ѵ�.
			CheckPointLight();

			return;
		}

		// Note : ���´�.
		m_vStaticMax = pSrc->GetStaticMax();
		m_vStaticMin = pSrc->GetStaticMin();
		m_fLength = pSrc->GetLength();

		// Note : �ڽſ� �µ��� StaticAABB�� Center, Length�� �ٲ۴�.
		D3DXMatrixAABBTransform( m_vStaticMax, m_vStaticMin, m_matWorld );
		m_vCenter = (m_vStaticMax+m_vStaticMin)*0.5f;
		m_fLength = m_fLength*m_fLength;

		// Note : �ڽŰ� �´�� �ִ� ���� üũ�� �Ѵ�.
		CheckPointLight();

		// Note : �����͸� ����.
		m_pStaticAniFrame = pSrc->m_pStaticAniFrame;

		m_pPieceEff = new DxPieceEff;
		m_pPieceEff->Clone( pd3dDevice, pSrc->m_pPieceEff );

		m_pAniTexEff = new DxPieceTexEff;
		m_pAniTexEff->Clone( pd3dDevice, pSrc->m_pAniTexEff );
	}
	else
	{
		CDebugSet::ErrorVersion( "DxPiece::Load_EP9", SFile.GetFileName(), dwVER );
		DWORD dwCur = SFile.GetfTell ();
		SFile.SetOffSet ( dwCur+dwSIZE );
	}
}

void DxPieceNode::Load_EP9( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile, DxPieceEdit* pSrc )
{
	DWORD dwVER(0);
	DWORD dwSIZE(0);

	SFile >> dwVER;

	if ( dwVER == 0x0100 )
		SFile >> dwSIZE;

	SFile >> m_vMax;
	SFile >> m_vMin;

	int nCount = 0;
	SFile >> nCount;
	for( int i=0; i<nCount; ++i )
	{
		DxPiece* pNew = new DxPiece;
		pNew->Load_EP9( pd3dDevice, SFile, pSrc );

		// Tree List ����
		pNew->m_pTreeNext = m_pPiece;
		m_pPiece = pNew;
	}

	BOOL bExist = FALSE;
	SFile >> bExist;
	if( bExist )
	{
		m_pLeftChild = new DxPieceNode;
		m_pLeftChild->Load_EP9( pd3dDevice, SFile, pSrc );
	}

	SFile >> bExist;
	if( bExist )
	{
		m_pRightChild = new DxPieceNode;
		m_pRightChild->Load_EP9( pd3dDevice, SFile, pSrc );
	}
}

namespace NSPIECETREE
{
	void Load_EP9( LPDIRECT3DDEVICEQ pd3dDevice, PDXPIECENODE& pNode, CSerialFile& SFile, DxPieceEdit* pSrc )
	{
		BOOL bExist = FALSE;
		SFile >> bExist;
		if( !bExist )	return;

		pNode = new DxPieceNode;
		pNode->Load_EP9( pd3dDevice, SFile, pSrc );
	}
};