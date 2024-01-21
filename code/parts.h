//*****************************************************
//
// �p�[�c�̏���[parts.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _PARTS_H_
#define _PARTS_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "model.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_TEX	(5)	// �e�N�X�`���̐�

//*****************************************************
// �N���X��`
//*****************************************************
class CParts
{
public:
	CParts();	// �R���X�g���N�^
	~CParts();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DrawShadow(void);
	static CParts *Create(D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f }, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });
	float GetWidth(void) { return 0.0f; }	// �T�C�Y�擾
	float GetHeight(void) { return 0.0f; }	// �T�C�Y�擾
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// �ݒ菈��
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �擾����
	void SetMove(D3DXVECTOR3 move) { m_move = move; }	// �ݒ菈��
	D3DXVECTOR3 GetMove(void) { return m_move; }	// �擾����
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	D3DXVECTOR3 GetPosOrg(void) { return m_posOrg; }	// �擾����
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }// �����ݒ菈��
	void SetPosOrg(D3DXVECTOR3 pos) { m_posOrg = pos; }// �����ݒ菈��
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �����擾����
	void BindModel(int nIdx);
	int GetIdxModel(void) { return m_IdxModel; }
	void SetIdxModel(int nIdx) { m_IdxModel = nIdx; }
	void SetRadius(void);
	float GetRadius(void) { return m_fRadius; }
	D3DXMATRIX *GetMatrix(void) { return &m_mtxWorld; }
	void SetMatrix(void);
	CModel::Model *GetModel(void) { return m_pModel; }
	void SetModel(CModel::Model *pModel) { m_pModel = pModel; }
	void SetEmissiveCol(D3DXCOLOR col) { m_col = col; m_bChangeCol = true; }
	D3DXCOLOR GetEmissiveCol(void) { return m_col; }
	void ResetColor(void) { m_bChangeCol = false; }

private:
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_posOrg;								//�ŏ��̈ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_rot;								//����
	D3DXCOLOR m_col;	// �F
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X
	CModel::Model *m_pModel;	// ���f�����
	int m_IdxModel;	// ���f���̔ԍ�
	float m_fRadius;	// ���f���̔��a
	bool m_bChangeCol;	// �F��ς��邩�ǂ���
};

#endif