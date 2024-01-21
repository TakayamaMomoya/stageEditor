//*****************************************************
//
// 2D�~�̏���[fan2D.h]
// Author:���R����
//
//*****************************************************

#ifndef _FAN2D_H_
#define _FAN2D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CFan2D	: public CObject
{
public:
	CFan2D(int nPriority = 7);
	~CFan2D();	//	�f�X�g���N�^

	static CFan2D *Create(int nPriority = 3,int nNumVtx = 16);	// ��������
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetPosition(D3DXVECTOR3 pos);	// �ݒ菈��
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �擾����
	void SetRot(float fRot);// �����ݒ菈��
	float GetRot(void) { return m_fRot; }	// �����擾����
	D3DXCOLOR GetCol(void) { return m_col; }
	void SetCol(D3DXCOLOR col);
	void SetVtx(void);
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }
	int GetIdxTexture(void) { return m_nIdxTexture; }
	void SetMaxAngle(float fAngle) { m_fAngleMax = fAngle; }
	float GetMaxAngle(void) { return m_fAngleMax; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXCOLOR m_col;	// �F
	float m_fRot;	// ����
	float m_fRadius;	// ���a
	float m_fAngleMax;	// �ő�̊p�x
	int m_nNumVtx;	// �O���̒��_��
	int m_nIdxTexture;	// �e�N�X�`���̔ԍ�
};

#endif