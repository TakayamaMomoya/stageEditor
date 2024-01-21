//*****************************************************
//
// �G�f�B�^�[�̏���[edit.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "edit.h"
#include "objectX.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "manager.h"
#include "debugproc.h"
#include "block.h"
#include "enemy.h"
#include "enemyManager.h"
#include <assert.h>

//*****************************************************
// �}�N����`
//*****************************************************
#define SPEED_MOVE	(6.0f)	// �ړ����x
#define SPEED_ROTATION	(0.01f)	// ��]

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CEdit *CEdit::m_pEdit = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CEdit::CEdit()
{
	m_pObjectCursor = nullptr;
	m_nIdxObject = 0;
	m_type = CBlock::TYPE_WALL;
	m_mode = MODE_CREATE_BLOCK;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEdit::~CEdit()
{

}

//=====================================================
// ��������
//=====================================================
CEdit *CEdit::Create(void)
{
	if (m_pEdit == nullptr)
	{// �C���X�^���X����
		m_pEdit = new CEdit;

		// ����������
		m_pEdit->Init();
	}

	return m_pEdit;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEdit::Init(void)
{
	// �ԍ��擾
	int *pIdx = CBlock::GetIndex();

	m_pObjectCursor = nullptr;

	m_pObjectCursor = CObjectX::Create();

	// �^�C�v�̏����ݒ�
	m_type = CBlock::TYPE_WALL;

	// ���f���ԍ��̐ݒ�
	m_pObjectCursor->SetIdxModel(pIdx[m_type]);
	m_pObjectCursor->BindModel(pIdx[m_type]);

	m_pObjectCursor->SetEmissiveCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEdit::Uninit(void)
{
	if (m_pObjectCursor != nullptr)
	{
		m_pObjectCursor->Uninit();
		m_pObjectCursor = nullptr;
	}

	m_pEdit = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CEdit::Update(void)
{
	// �ԍ��擾
	int *pIdx = CBlock::GetIndex();

	// ���擾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();

	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };
	float fSpeed = SPEED_MOVE;
	CBlock **pBlock = CBlock::GetBlock();

	if (m_pObjectCursor != nullptr && pKeyboard != nullptr && pMouse != nullptr)
	{
		if (pMouse->GetPress(CInputMouse::BUTTON_RMB) == false)
		{
			if (pKeyboard->GetPress(DIK_RSHIFT))
			{
				fSpeed *= 5.0f;
			}

			if (pKeyboard->GetTrigger(DIK_A))
			{
				pos.x -= fSpeed;
			}
			if (pKeyboard->GetTrigger(DIK_D))
			{
				pos.x += fSpeed;
			}
			if (pKeyboard->GetTrigger(DIK_W))
			{
				pos.z += fSpeed;
			}
			if (pKeyboard->GetTrigger(DIK_S))
			{
				pos.z -= fSpeed;
			}
			if (pKeyboard->GetTrigger(DIK_E))
			{
				pos.y += fSpeed;
			}
			if (pKeyboard->GetTrigger(DIK_Q))
			{
				pos.y -= fSpeed;
			}
		}

		// ��]
		if (pKeyboard->GetTrigger(DIK_Z))
		{
			rot.y = 0.0f;

			m_pObjectCursor->SetRot(rot);
		}
		if (pKeyboard->GetTrigger(DIK_C))
		{
			rot.y = D3DX_PI * 0.5f;

			m_pObjectCursor->SetRot(rot);
		}

		if (pKeyboard->GetTrigger(DIK_RETURN) || pMouse->GetTrigger(CInputMouse::BUTTON_LMB))
		{// �u���b�N�̐���
			//CBlock::Create(m_pObjectCursor->GetPosition(), m_pObjectCursor->GetRot(),m_type);
		}

		// �폜�u���b�N�I��
		int nIdxDelete = CheckDelete();

		if (pKeyboard->GetTrigger(DIK_BACKSPACE) && nIdxDelete != -1)
		{
			CBlock::Delete(nIdxDelete);
		}

		if (pKeyboard->GetTrigger(DIK_1))
		{
			m_type = (CBlock::TYPE)((m_type + CBlock::TYPE_MAX - 1) % CBlock::TYPE_MAX);

			// ���f���ԍ��̐ݒ�
			m_pObjectCursor->SetIdxModel(pIdx[m_type]);
			m_pObjectCursor->BindModel(pIdx[m_type]);
		}

		if (pKeyboard->GetTrigger(DIK_2) || pMouse->GetMoveIZ() > 0.0f)
		{// �u���b�N�^�C�v�؂�ւ�
			m_type = (CBlock::TYPE)((m_type + 1) % CBlock::TYPE_MAX);

			// ���f���ԍ��̐ݒ�
			m_pObjectCursor->SetIdxModel(pIdx[m_type]);
			m_pObjectCursor->BindModel(pIdx[m_type]);
		}

		if (pKeyboard->GetTrigger(DIK_F2))
		{// �u���b�N�̕ۑ�
			CBlock::Save();
		}

		if (m_pObjectCursor != nullptr)
		{// �J�[�\���̃g�����X�t�H�[��
			m_pObjectCursor->SetPosition(m_pObjectCursor->GetPosition() + pos);
		}

		CDebugProc::GetInstance()->Print("\n//=======================\n");
		CDebugProc::GetInstance()->Print("// �G�f�B�^�[\n");
		CDebugProc::GetInstance()->Print("//=======================\n");
		CDebugProc::GetInstance()->Print("�G�f�B�^�[�̈ʒu�F[%f,%f,%f]\n", m_pObjectCursor->GetPosition().x, m_pObjectCursor->GetPosition().y, m_pObjectCursor->GetPosition().z);
		CDebugProc::GetInstance()->Print("�G�f�B�^�[�̌����F[%f,%f,%f]\n", m_pObjectCursor->GetRot().x, m_pObjectCursor->GetRot().y, m_pObjectCursor->GetRot().z);
		CDebugProc::GetInstance()->Print("�ړ�[WASD]\n");
		CDebugProc::GetInstance()->Print("�㉺�ړ�[QE]\n");
		CDebugProc::GetInstance()->Print("��][ZC]\n");
		CDebugProc::GetInstance()->Print("�ݒu[ENTER]\n");
		CDebugProc::GetInstance()->Print("�ۑ�[F2]\n");
		CDebugProc::GetInstance()->Print("�I�𒆂̃u���b�N�F[%d]\n", m_nIdxObject);
		CDebugProc::GetInstance()->Print("�I���u���b�N�폜[BACK SPACE]\n");
		CDebugProc::GetInstance()->Print("�ݒu����^�C�v�F[%d]:[1,2]\n", m_type);
		CDebugProc::GetInstance()->Print("//=======================\n");
	}
}

//=====================================================
// �폜�u���b�N�̃`�F�b�N
//=====================================================
int CEdit::CheckDelete(void)
{
	CBlock** ppBlock = CBlock::GetBlock();
	int nNumBlock = CBlock::GetNumAll();

	if (ppBlock == nullptr)
	{
		return -1;
	}

	for (int i = 0; i < nNumBlock; i++)
	{
		CBlock* pBlock = ppBlock[i];

		if (pBlock != nullptr)
		{
			pBlock->ResetColor();

			D3DXVECTOR3 posBlock = pBlock->GetPosition();
			D3DXVECTOR3 pos = m_pObjectCursor->GetPosition();
			D3DXVECTOR3 vtxMax = pBlock->GetVtxMax();
			D3DXVECTOR3 vtxMin = pBlock->GetVtxMin();

			if (pos.x >= posBlock.x + vtxMin.x && 
				pos.x <= posBlock.x + vtxMax.x &&
				pos.z >= posBlock.z + vtxMin.z &&
				pos.z <= posBlock.z + vtxMax.z &&
				pos.y >= posBlock.y + vtxMin.y &&
				pos.y <= posBlock.y + vtxMax.y)
			{// �u���b�N���ɂ���Ƃ�
				pBlock->SetEmissiveCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

				return i;
			}
		}
	}

	return -1;
}