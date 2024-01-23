//*****************************************************
//
// ���̓}�l�[�W���[[inputManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "inputManager.h"
#include "manager.h"
#include "inputjoypad.h"
#include "inputkeyboard.h"
#include "inputmouse.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CInputManager *CInputManager::m_pInputManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CInputManager::CInputManager()
{
	ZeroMemory(&m_info, sizeof(SInfo));
	ZeroMemory(&m_axis, sizeof(SAxis));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CInputManager::~CInputManager()
{

}

//=====================================================
// ��������
//=====================================================
CInputManager *CInputManager::Create(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInputManager == nullptr)
	{// �C���X�^���X����
		m_pInputManager = new CInputManager;

		// ����������
		m_pInputManager->Init(hInstance, hWnd);
	}

	return m_pInputManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CInputManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �W���C�p�b�h����
	CInputJoypad::Create();

	// �L�[�{�[�h����
	CInputKeyboard::Create(hInstance, hWnd);

	// �}�E�X����
	CInputMouse::Create(hInstance, hWnd);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CInputManager::Uninit(void)
{
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->Uninit();
	}

	if (pKeyboard != nullptr)
	{
		pKeyboard->Uninit();
	}

	if (pMouse != nullptr)
	{
		pMouse->Uninit();
	}

	// ���g�̃|�C���^�j��
	m_pInputManager = nullptr;
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CInputManager::Update(void)
{
	// �e���̓f�o�C�X�̍X�V
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->Update();
	}

	if (pKeyboard != nullptr)
	{
		pKeyboard->Update();
	}

	if (pMouse != nullptr)
	{
		pMouse->Update();
	}

	// �G���^�[
	m_info.abTrigger[BUTTON_ENTER] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, 0) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
		pKeyboard->GetTrigger(DIK_RETURN)
	);

	// �߂�{�^��
	m_info.abTrigger[BUTTON_BACK] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_B, 0) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_BACK, 0) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_RMB)
	);

	// �W�����v
	m_info.abTrigger[BUTTON_JUMP] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_LB, 0) ||
		pKeyboard->GetTrigger(DIK_SPACE)
	);
	m_info.abPress[BUTTON_JUMP] =
	(
		pJoypad->GetPress(CInputJoypad::PADBUTTONS_LB, 0) ||
		pKeyboard->GetPress(DIK_SPACE)
	);

	// �ˌ�
	m_info.abTrigger[BUTTON_SHOT] =
	(
		pJoypad->GetTriggerTB(CInputJoypad::TRIGGER_LT, 0) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
		pKeyboard->GetTrigger(DIK_RETURN)
	);

	// �ߐڍU��
	m_info.abTrigger[BUTTON_MELEE] =
	(
		pJoypad->GetTriggerTB(CInputJoypad::TRIGGER_RT, 0) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_RMB)
	);

	// �͂�
	m_info.abTrigger[BUTTON_GRAB] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_RB, 0) ||
		pKeyboard->GetTrigger(DIK_E)
	);

	// ����u�[�X�g
	m_info.abTrigger[BUTTON_DODGE] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_X, 0) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_SIDE01) ||
		pKeyboard->GetTrigger(DIK_LSHIFT)
	);

	// �|�[�Y
	m_info.abTrigger[BUTTON_PAUSE] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, 0) ||
		pKeyboard->GetTrigger(DIK_P)
	);

	// ������L�[
	m_info.abTrigger[BUTTON_AXIS_UP] =
	(
		pJoypad->GetLStickTrigger(CInputJoypad::DIRECTION_UP,0) || 
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_UP,0) ||
		pKeyboard->GetTrigger(DIK_W)
	);

	// �������L�[
	m_info.abTrigger[BUTTON_AXIS_DOWN] =
	(
		pJoypad->GetLStickTrigger(CInputJoypad::DIRECTION_DOWN, 0) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_DOWN, 0) ||
		pKeyboard->GetTrigger(DIK_S)
	);

	// �����̃��Z�b�g
	ZeroMemory(&m_axis, sizeof(SAxis));

	// �ړ������̐ݒ�=============
	// �W���C�p�b�h
	m_axis.axisMove = D3DXVECTOR3(pJoypad->GetJoyStickLX(0), 0.0f, pJoypad->GetJoyStickLY(0));

	// �L�[�{�[�h
	if (pKeyboard->GetPress(DIK_W))
	{
		m_axis.axisMove.z += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		m_axis.axisMove.z -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		m_axis.axisMove.x -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		m_axis.axisMove.x += 1.0f;
	}

	D3DXVec3Normalize(&m_axis.axisMove, &m_axis.axisMove);

	// �J�����̌��������ݒ�=============
	m_axis.axisCamera += D3DXVECTOR3(pJoypad->GetJoyStickRX(0), pJoypad->GetJoyStickRY(0), 0.0f);
	m_axis.axisCamera += D3DXVECTOR3(pMouse->GetMoveIX(), pMouse->GetMoveIY(), 0.0f);

	D3DXVec3Normalize(&m_axis.axisCamera, &m_axis.axisCamera);
}