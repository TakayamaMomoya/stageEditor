//*****************************************************
//
// �����_���[�̏���[renderer.h]
// Author:���R����
//
//*****************************************************

#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRenderer
{
public:
	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^

	static CRenderer *Create(HWND hWnd, BOOL bWindow);
	HRESULT Init(HWND hWnd, BOOL bWindow);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void DrawFPS(void);	//FPS�\������
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// �f�o�C�X�̎擾
	IDirect3DVertexDeclaration9 *GetDecVtxShader(void) { return m_pDecVtx; }
	IDirect3DPixelShader9 *GetHandlerPxShader(void) { return m_pHandlerPxShader; }
	IDirect3DVertexShader9 *GetHandlerVtxShader(void) { return m_pHandlerVtxShader; }
	bool IsFog(void) { return m_fogInfo.bEnable; }
	void EnableFog(bool bFog) { m_fogInfo.bEnable = bFog; }
	static CRenderer *GetInstance(void) { return m_pRenderer; }

private:
	struct SInfoFog
	{// �t�H�O���
		float fStart;	// �J�n����
		float fEnd;	// �I������
		bool bEnable;	// �L�����ǂ���
		D3DXCOLOR col;	// �F
	};

	LPDIRECT3D9 m_pD3D;	// �I�u�W�F�N�g�̐���
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// �f�o�C�X
	IDirect3DPixelShader9 *m_pHandlerPxShader;	// �s�N�Z���V�F�[�_�[�n���h���[
	IDirect3DVertexShader9 *m_pHandlerVtxShader;	// ���_�V�F�[�_�[�n���h���[
	IDirect3DVertexDeclaration9 *m_pDecVtx;	// ���_�錾
	SInfoFog m_fogInfo;	// �t�H�O�̏��

	static CRenderer *m_pRenderer;	// ���g�̃|�C���^
};

#endif