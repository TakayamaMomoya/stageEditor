//*****************************************************
//
// �����o�[�g�̏���[lambert.h]
// Author:���R����
//
//*****************************************************

#ifndef _LAMBERT_H_
#define _LAMBERT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CLambert
{
public:
	CLambert();
	~CLambert();
	static CLambert *Create(void);
	static CLambert *GetInstance(void) { return m_pLambert; }
	HRESULT Init(void);
	void Uninit(void);
	void Invalidate();
	void Restore();
	void Begin();
	void BeginPass();
	void SetAmbient(float Ambient);
	void SetAmbient(D3DXVECTOR4* pAmbient);
	void SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir);
	void CommitChanges();
	void EndPass();
	void End();
	bool IsOK();
	LPD3DXEFFECT GetEffect() { return m_pEffect; };

private:
	LPD3DXEFFECT m_pEffect;	// �G�t�F�N�g�̃|�C���^
	D3DXHANDLE m_pTechnique;	// �e�N�j�b�N�̃n���h��
	D3DXHANDLE m_pWVP;	// �}�g���b�N�X�̃n���h��
	D3DXHANDLE m_pLightDir;	// �f�B���N�V���i�����C�g�̃n���h��
	D3DXHANDLE m_pAmbient;	// �����̃n���h��
	D3DXMATRIX m_mtxView;	// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProj;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR4 m_ambient;	// �A���r�G���g�̒l
	static CLambert *m_pLambert;	// ���g�̃|�C���^
};

#endif