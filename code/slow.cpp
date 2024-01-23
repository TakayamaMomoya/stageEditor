//*****************************************************
//
// �X���[�̏���[slow.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "slow.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{

}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CSlow *CSlow::m_pSlow = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CSlow::CSlow()
{
	m_pSlow = this;

	m_fScale = 0.0f;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CSlow::~CSlow()
{

}

//=====================================================
// ��������
//=====================================================
CSlow *CSlow::Create(void)
{
	if (m_pSlow == nullptr)
	{
		m_pSlow = new CSlow;

		if (m_pSlow != nullptr)
		{
			m_pSlow->Init();
		}
	}

	return m_pSlow;
}

//=====================================================
// ����������
//=====================================================
HRESULT CSlow::Init(void)
{
	m_fScale = 1.0f;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CSlow::Uninit(void)
{
	m_pSlow = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CSlow::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CSlow::Draw(void)
{
#ifdef _DEBUG
	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc != nullptr)
	{
		pDebugProc->Print("\n�X���[�{��[%f]",m_fScale);
	}
#endif
}

//=====================================================
// �X�P�[���̐ݒ�
//=====================================================
void CSlow::SetScale(float fScale)
{
	if (fScale >= 0.0f)
	{
		m_fScale = fScale;
	}
}