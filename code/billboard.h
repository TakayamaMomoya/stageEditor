//*****************************************************
//
// �r���{�[�h�̏���[billboard.h]
// Author:���R����
//
//*****************************************************

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBillboard : public CObject
{
public:
	CBillboard(int nPriority = 5);	// �R���X�g���N�^
	~CBillboard();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboard *Create(D3DXVECTOR3 pos, float width, float height);
	float GetWidth(void) { return m_width; }	// �T�C�Y�擾
	float GetHeight(void) { return m_heigth; }	// �T�C�Y�擾
	void SetSize(float width, float height);
	void SetPosition(D3DXVECTOR3 pos);	// �ݒ菈��
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �擾����
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetTex(D3DXVECTOR2 texLeftUp, D3DXVECTOR2 texRightDown);
	void SetColor(D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }
	int GetIdxTexture(void) { return m_nIdxTexture; }
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }
	void SetMatrix(void);
	void SetZTest(bool bZTest) { m_bZTest = bZTest; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	void SetVtx(void);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR m_col;	// �F
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	float m_width;	// ��
	float m_heigth;	// ����
	int m_nIdxTexture;	// �e�N�X�`���̔ԍ�
	bool m_bZTest;	// Z�e�X�g���邩�ǂ���
};

#endif