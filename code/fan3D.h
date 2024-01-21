//*****************************************************
//
// 3D�~�̏���[fan2D.h]
// Author:���R����
//
//*****************************************************

#ifndef _FAN3D_H_
#define _FAN3D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CFan3D	: public CObject
{
public:
	CFan3D(int nPriority = 6);
	~CFan3D();	//	�f�X�g���N�^

	static CFan3D *Create(int nPriority = 3,int nNumVtx = 16);	// ��������
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void DrawNormal(void);	// �ʏ�`��
	void DrawBillboard(void);	// �r���{�[�h�`��

	void SetPosition(D3DXVECTOR3 pos);	// �ݒ菈��
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �擾����
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }// �����ݒ菈��
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �����擾����
	D3DXCOLOR GetCol(void) { return m_col; }
	void SetCol(D3DXCOLOR col);
	void SetVtx(void);
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }
	int GetIdxTexture(void) { return m_nIdxTexture; }
	void SetMaxAngle(float fAngle) { m_fAngleMax = fAngle; }
	float GetMaxAngle(void) { return m_fAngleMax; }
	void EnableBillboard(bool bEnable) { m_bBillboard = bEnable; }
	void SetAngleMax(float fAngle) { m_fAngleMax = fAngle; }
	float GetAngleMax(void) { return m_fAngleMax; }
	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	float GetRadius(void) { return m_fRadius; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXCOLOR m_col;	// �F
	D3DXMATRIX m_mtxWorld;	// �}�g���b�N�X
	float m_fRadius;	// ���a
	float m_fAngleMax;	// �ő�̊p�x
	int m_nNumVtx;	// �O���̒��_��
	int m_nIdxTexture;	// �e�N�X�`���̔ԍ�
	bool m_bBillboard;	// �r���{�[�h���ǂ���
};

#endif