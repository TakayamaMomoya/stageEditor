//*****************************************************
//
// �^�C�g������[title.cpp]
// Author:����쏟
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "title.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "manager.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "sound.h"

#include "object3D.h"
#include "objectX.h"
#include "skybox.h"

//*****************************************************
// �}�N����`
//*****************************************************

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const float FIELD_WIDTH = 10000.0f;		// �t�B�[���h�̕�
	const float FIELD_HEIGHT = 10000.0f;	// �t�B�[���h�̍���

	const D3DXVECTOR3 LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0f, 0.0f);	// ���S�̈ʒu
	const float LOGO_WIDTH = 875.0f * 0.35f;	// ���S�̕�
	const float LOGO_HEIGHT = 320.0f * 0.35f;	// ���S�̍���
	const char* LOGO_PATH = "data\\TEXTURE\\UI\\logo000.png";	// ���S�̃p�X

	const D3DXVECTOR3 STATE_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f);	// �X�^�[�g�\���̈ʒu
	const float START_WIDTH = 200.0f;	// �X�^�[�g�\���̕�
	const float START_HEIGHT = 50.0f;	// �X�^�[�g�\���̍���
	const float ADD_WIDTH = 16.0f;		// ���̊g�剻
	const float ADD_HEIGHT = 10.0f;		// �����̊g�剻  
	const char* START_PATH = "data\\TEXTURE\\UI\\gamestart.png";	// �X�^�[�g�\���̃p�X

	const int FADE_COUNT = 120;			// �t�F�[�h�܂ł̎���

	const float ALPHA_UPPER = 1.0f;			// ���l�̏����
	const float ALPHA_LOWER = 0.25f;		// ���l�̉�����
	const float ALPHA_CHANGE = 0.1f;		// ���l�̕ω���
	const float ALPHA_CHANGE_LOGO = 0.01f;	// ���l�̕ω���
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CTitle::CTitle()
{
	m_state = STATE_NONE;
	m_pLogo = nullptr;
	m_pLogoLate = nullptr;
	m_pStart = nullptr;
	m_nFadeCnt = 0;
	m_bIsAlphaChange = false;
	m_fSizeX = LOGO_WIDTH;
	m_fSizeY = LOGO_HEIGHT;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTitle::~CTitle()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CTitle::Init(void)
{
	// ���S�̐���
	m_pLogo = CObject2D::Create(7);

	if (m_pLogo != nullptr)
	{
		m_pLogo->SetSize(LOGO_WIDTH, LOGO_HEIGHT);
		m_pLogo->SetPosition(LOGO_POS);
		int nIdx = CTexture::GetInstance()->Regist(LOGO_PATH);
		m_pLogo->SetIdxTexture(nIdx);
		m_pLogo->SetVtx();
	}
	if (m_pLogo == nullptr)
	{
		return E_FAIL;
	}

	// �X�^�[�g�\���̐���
	m_pStart = CObject2D::Create(7);

	if (m_pStart != nullptr)
	{
		m_pStart->SetSize(START_WIDTH, START_HEIGHT);
		m_pStart->SetPosition(STATE_POS);
		int nIdx = CTexture::GetInstance()->Regist(START_PATH);
		m_pStart->SetIdxTexture(nIdx);
		m_pStart->SetVtx();
	}
	else if (m_pStart == nullptr)
	{
		return E_FAIL;
	}

	// �X�J�C�{�b�N�X�̐���
	CSkybox* pSkyBox = CSkybox::Create();

	if (pSkyBox == nullptr)
	{
		return E_FAIL;
	}

	// �n�ʂ̐���
	CObject3D* pField = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (pField != nullptr)
	{
		pField->SetSize(FIELD_WIDTH, FIELD_HEIGHT);
		int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\field00.jpg");
		pField->SetIdxTexture(nIdx);
		pField->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f));
	}
	else if (pField == nullptr)
	{
		return E_FAIL;
	}

	// �t�H�O��������
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->EnableFog(true);
	}
	else if (pRenderer == nullptr)
	{
		return E_FAIL;
	}

	// �T�E���h�C���X�^���X�̎擾
	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		// BGM�̍Đ�
		pSound->Play(pSound->LABEL_BGM_TITLE);
	}
	else if (pSound == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTitle::Uninit(void)
{
	// �I�u�W�F�N�g�S�j��
	CObject::ReleaseAll();

	// �t�H�O��������
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->EnableFog(false);
	}
}

//=====================================================
// �X�V����
//=====================================================
void CTitle::Update(void)
{
	// ���擾
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	// �V�[���̍X�V
	CScene::Update();

	if (m_state == STATE_NONE)
	{
		if (pKeyboard != nullptr && pMouse != nullptr && pJoypad != nullptr)
		{
			if (pKeyboard->GetTrigger(DIK_RETURN) ||
				pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
				pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
			{// �t�F�[�h�J�n

				// �T�E���h�C���X�^���X�̎擾
				CSound* pSound = CSound::GetInstance();

				if (pSound != nullptr)
				{
					pSound->Play(pSound->LABEL_SE_START_GAME);
				}

				// �t�F�[�h�ݒ�
				SetFadeIn();
			}
		}
	}
	else if (m_state == STATE_OUT)
	{
		// �t�F�[�h�X�V����
		UpdateFade();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CTitle::Draw(void)
{

}

//=====================================================
// �X�^�[�g�\���̊Ǘ�
//=====================================================
void CTitle::ManageStart(void)
{
	// �F�̏��擾
	D3DXCOLOR colStart = m_pStart->GetCol();
	D3DXCOLOR colLogo = m_pLogo->GetCol();
	D3DXCOLOR colLogoLate = m_pLogoLate->GetCol();

	if (m_pStart != nullptr && m_pLogo != nullptr)
	{
		if (m_bIsAlphaChange == false)
		{
			colStart.a -= ALPHA_CHANGE;
		}
		else if (m_bIsAlphaChange == true)
		{
			colStart.a += ALPHA_CHANGE;
		}

		if (colStart.a <= ALPHA_LOWER)
		{
			m_bIsAlphaChange = true;
		}
		else if (colStart.a >= ALPHA_UPPER)
		{
			m_bIsAlphaChange = false;
		}

		if (colLogo.a >= 0.0f)
		{
			// ���S�̃��l������
			colLogo.a -= ALPHA_CHANGE_LOGO;
		}

		if (colLogoLate.a >= 0.0f)
		{
			// ���S�̃��l������
			colLogoLate.a -= 0.06f;
		}

		// �T�C�Y�̔�剻
		m_fSizeX += ADD_WIDTH;
		m_fSizeY += ADD_HEIGHT;

		// �ݒ菈��
		m_pStart->SetCol(colStart);
		m_pStart->SetVtx();
		m_pLogo->SetCol(colLogo);
		m_pLogo->SetVtx();
		m_pLogoLate->SetSize(m_fSizeX, m_fSizeY);
		m_pLogoLate->SetCol(colLogoLate);
		m_pLogoLate->SetVtx();
	}
}

//=====================================================
// �t�F�[�h�̍X�V����
//=====================================================
void CTitle::UpdateFade(void)
{
	// �X�^�[�g�\���̊Ǘ�
	ManageStart();

	// �t�F�[�h�J�E���g�i�߂�
	m_nFadeCnt++;

	if (m_nFadeCnt == FADE_COUNT)
	{
		// �t�F�[�h�̎擾
		CFade* pFade = CFade::GetInstance();

		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_GAME);
		}
	}
}

//=====================================================
// �t�F�[�h�ݒ�
//=====================================================
void CTitle::SetFadeIn(void)
{
	// ���擾
	CCamera* pCamera = CManager::GetCamera();
	
	if (m_pLogoLate == nullptr)
	{
		m_pLogoLate = CObject2D::Create(7);

		if (m_pLogoLate != nullptr)
		{
			m_pLogoLate->SetSize(LOGO_WIDTH, LOGO_HEIGHT);
			m_pLogoLate->SetPosition(LOGO_POS);
			int nIdx = CTexture::GetInstance()->Regist(LOGO_PATH);
			m_pLogoLate->SetIdxTexture(nIdx);
			m_pLogoLate->SetVtx();
		}
	}

	// �t�F�[�h�A�E�g�ɐݒ�
	m_state = STATE_OUT;
}