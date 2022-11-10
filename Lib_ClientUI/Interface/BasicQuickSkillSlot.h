//	��ų Ʈ����
//
//	���� �ۼ��� : ���⿱
//	���� ������ : 
//	�α�
//		[2003.12.5]
//			@ ��ų �̹���(CSkillImage) Ŭ���� �ۼ���, ��� �и�
//		[2003.11.21]
//			@ �ۼ�

#pragma	once

#include "../Lib_Engine/GUInterface/UIGroup.h"
#include "GLDefine.h"

class	CSkillImage;

class CBasicQuickSkillSlot : public CUIGroup
{
protected:
	enum
	{
		QUICK_SKILL_MOUSE_OVER = NO_ID + 1,
		QUICK_SKILL_BLOCK, /*prohibit skill logic, Juver, 2017/06/06 */
	};

public:
	CBasicQuickSkillSlot ();
	virtual	~CBasicQuickSkillSlot ();

public:
	virtual	void	CreateSubControl ();

public:
	UIRECT GetAbsPosSkillImage ();
	void SetUseSkillImageTwinkle( bool bUse );

protected:	
	void	CreateSkillImage ();
	void	CreateMouseOver ();
	void	CreateSkillBlock (); /*prohibit skill logic, Juver, 2017/06/06 */

protected:
    void	UpdateSlot ( SNATIVEID sNativeID );

public:
	virtual void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	CSkillImage*		m_pSkillImage;

protected:
	CUIControl*			m_pSkillMouseOver;
	CUIControl*			m_pSkillBlock; /*prohibit skill logic, Juver, 2017/06/06 */

private:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;
};