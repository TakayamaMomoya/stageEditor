//*****************************************************
//
// 2D�I�u�W�F�N�g�̏���[object2D.h]
// Author:���R����
//
//*****************************************************

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CObject2D	: public CObject
{
public:
	CObject2D(int nPriority = 7);
	~CObject2D();	//	�f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	static CObject2D *Create(int nPriority = 3,float fCenterHeight = 0.5f);	// ��������

	void SetSize(float width, float height);
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2(m_width, m_heigth); }
	void SetAnim(int nAnim, int nNumAnim, int nNumV);
	void SetTex(D3DXVECTOR2 texLeftUp, D3DXVECTOR2 texRightDown);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	void SetPosition(D3DXVECTOR3 pos);	// �ݒ菈��
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �擾����
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetMove(D3DXVECTOR3 move);	// �ړ��ʐݒ菈��
	void AddMove(D3DXVECTOR3 move);	// �ړ��ʉ��Z����
	void DicMove(float fDicrease);	// �ړ��ʌ�������
	D3DXVECTOR3 GetMove(void) { return m_move; }	// �ړ��ʎ擾����
	void SetRot(float fRot);// �����ݒ菈��
	float GetRot(void) { return m_fRot; }	// �����擾����
	void LimitPos(void);	// �ړ�����
	D3DXCOLOR GetCol(void) { return m_col; }
	void SetCol(D3DXCOLOR col);
	float GetWidth(void) { return m_width; }	// �T�C�Y�擾
	float GetHeight(void) { return m_heigth; }	// �T�C�Y�擾
	void SetVtx(void);
	void SetCenterHeight(float fHeight);
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }
	int GetIdxTexture(void) { return m_nIdxTexture; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXCOLOR m_col;	// �F
	float m_fRot;	// ����
	float m_width;	// ��
	float m_heigth;	// ����
	float m_fCenterHeight;	// ���S�̍���
	int m_nIdxTexture;	// �e�N�X�`���̔ԍ�
};

#endif