//*****************************************************
//
// �����o�[�g�̏���[Lambert.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "Lambert.h"
#include "renderer.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CLambert *CLambert::m_pLambert = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CLambert::CLambert()
{
	m_pEffect = nullptr;
	m_pTechnique = nullptr;
	m_pAmbient = nullptr;
	m_pLightDir = nullptr;
	m_pWVP = nullptr;
	m_ambient = { 1.0f,1.0f,1.0f,1.0f };
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CLambert::~CLambert()
{

}

//=====================================================
// ��������
//=====================================================
CLambert *CLambert::Create(void)
{
	if (m_pLambert == nullptr)
	{
		m_pLambert = new CLambert;

		if (m_pLambert != nullptr)
		{
			m_pLambert->Init();
		}
	}

	return m_pLambert;
}

//=====================================================
// ������
//=====================================================
HRESULT CLambert::Init(void)
{
	HRESULT hr;
	D3DCAPS9 caps;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	pDevice->GetDeviceCaps(&caps);
	DWORD vVs = caps.VertexShaderVersion;
	DWORD vPs = caps.PixelShaderVersion;

	// �o�[�W�����̃`�F�b�N
	if (vVs < D3DVS_VERSION(1, 1) || vVs > D3DVS_VERSION(3, 0) ||
		vPs < D3DPS_VERSION(1, 1) || vPs > D3DPS_VERSION(3, 0))
	{
		assert(("�V�F�[�_�[�̃o�[�W�������g�p�ł��Ȃ����̂ł�", false));

		return E_FAIL;
	}

	LPD3DXBUFFER pErr = nullptr;

	// fx�t�@�C���̃��[�h
	hr = D3DXCreateEffectFromFile(pDevice, "data\\EFFECT\\Empty.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, &pErr);

	if (SUCCEEDED(hr))
	{
		//fx�t�@�C�����Ő錾���Ă���ϐ��̃n���h�����擾����
		m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
		m_pWVP = m_pEffect->GetParameterByName(NULL, "m_WVP");
		m_pLightDir = m_pEffect->GetParameterByName(NULL, "m_LightDir");
		m_pAmbient = m_pEffect->GetParameterByName(NULL, "m_Ambient");
		SetAmbient(0.8f);

		m_pEffect->SetTechnique(m_pTechnique);
	}

	return S_OK;
}

//=====================================================
// �I��
//=====================================================
void CLambert::Uninit(void)
{
	if (m_pEffect != nullptr)
	{
		m_pEffect->Release();
		m_pEffect = nullptr;
	}
}

//=====================================================
// �J��
//=====================================================
void CLambert::Invalidate(void)
{
	if (m_pEffect != nullptr)
		m_pEffect->OnLostDevice();
}

//=====================================================
// ���X�g�A
//=====================================================
void CLambert::Restore(void)
{
	if (m_pEffect != nullptr)
		m_pEffect->OnResetDevice();
}

//=====================================================
// �V�F�[�_�[�����̊J�n
//=====================================================
void CLambert::Begin(void)
{
	if (m_pEffect != nullptr)
	{
		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

		pDevice->GetTransform(D3DTS_VIEW, &m_mtxView);
		pDevice->GetTransform(D3DTS_PROJECTION, &m_mtxProj);

		m_pEffect->Begin(nullptr, 0);
	}
}

//=====================================================
// �p�X�O�̊J�n
//=====================================================
void CLambert::BeginPass(void)
{
	if (m_pEffect)
	{
		m_pEffect->BeginPass(0);
	}
}

//=====================================================
// �����̐ݒ�(float)
//=====================================================
void CLambert::SetAmbient(float fAmbient)
{
	m_ambient = { fAmbient ,fAmbient ,fAmbient ,1.0f };

	if (m_pEffect)
	{//�V�F�[�_�[���g�p�ł���Ƃ�
		D3DXVECTOR4 ambient;
		ambient = D3DXVECTOR4(fAmbient, fAmbient, fAmbient, 1.0f);
		m_pEffect->SetVector(m_pAmbient, &ambient);
	}
	else
	{//�V�F�[�_�[���g�p�ł��Ȃ��Ƃ��́A�Œ�@�\�p�C�v���C���̃}�e���A����ݒ肷��B(���ӂR)
		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

		D3DMATERIAL9 old_material;
		pDevice->GetMaterial(&old_material);
		old_material.Ambient.r = fAmbient;
		old_material.Ambient.g = fAmbient;
		old_material.Ambient.b = fAmbient;
		old_material.Ambient.a = 1.0f;
		pDevice->SetMaterial(&old_material);
	}
}

//=====================================================
// �����̐ݒ�(Vector4)
//=====================================================
void CLambert::SetAmbient(D3DXVECTOR4* pAmbient)
{
	m_ambient = { pAmbient->x ,pAmbient->y ,pAmbient->z ,1.0f };

	if (m_pEffect)
	{//�V�F�[�_�[���g�p�ł���Ƃ�
		D3DXVECTOR4 ambient;
		ambient = *pAmbient;
		m_pEffect->SetVector(m_pAmbient, &ambient);
	}
	else
	{//�V�F�[�_�[���g�p�ł��Ȃ��Ƃ��́A�Œ�@�\�p�C�v���C���̃}�e���A����ݒ肷��B(���ӂR)
		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

		D3DMATERIAL9 old_material;
		pDevice->GetMaterial(&old_material);
		old_material.Ambient.r = pAmbient->x;
		old_material.Ambient.g = pAmbient->y;
		old_material.Ambient.b = pAmbient->z;
		old_material.Ambient.a = 1.0f;
		pDevice->SetMaterial(&old_material);
	}
}

//=====================================================
// ���[���h�}�g���b�N�X�̐ݒ�
//=====================================================
void CLambert::SetMatrix(D3DXMATRIX *pMtxWorld, D3DXVECTOR4 *pLightDir)
{
	if (pMtxWorld == nullptr || pLightDir == nullptr)
		return;

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	if (m_pEffect != nullptr)
	{
		// �r���[�Ǝˉe�}�g���b�N�X����A���[���h�}�g���b�N�X��ݒ�
		D3DXMATRIX mtxWorld;
		mtxWorld = *pMtxWorld * m_mtxView * m_mtxProj;

		m_pEffect->SetMatrix(m_pWVP, &mtxWorld);

		// ���s�����̕����x�N�g����ݒ肷��
		D3DXMATRIX mtxLight;
		D3DXVECTOR4 vecLight = *pLightDir;
		D3DXVECTOR4 vector;

		D3DXMatrixInverse(&mtxLight, nullptr, pMtxWorld);
		D3DXVec4Transform(&vector, &vecLight, &mtxLight);

		// ���K������
		D3DXVec3Normalize((D3DXVECTOR3*)&vector, (D3DXVECTOR3*)&vector);
		m_pEffect->SetVector(m_pLightDir, &vector);
	}
	else
	{// �V�F�[�_�[���g�p�ł��Ȃ��Ƃ��͌Œ�p�C�v���C�����g�p����
		pDevice->SetTransform(D3DTS_WORLD, pMtxWorld);
	}
}

//=====================================================
// �X�e�[�g�̕ύX���f�o�C�X�ɒʒm
//=====================================================
void CLambert::CommitChanges(void)
{
	if (m_pEffect)
		m_pEffect->CommitChanges();
}

//=====================================================
// �p�X�̏I��
//=====================================================
void CLambert::EndPass(void)
{
	if (m_pEffect)
		m_pEffect->EndPass();
}

//=====================================================
// �V�F�[�_�[�����̏I��
//=====================================================
void CLambert::End(void)
{
	if (m_pEffect)
		m_pEffect->End();
}

//=====================================================
// �V�F�[�_�[���g�p�ł��邩�ǂ���
//=====================================================
bool CLambert::IsOK(void)
{
	return m_pEffect != nullptr;
}