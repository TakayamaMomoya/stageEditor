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
#include "blockManager.h"
#include <assert.h>

//*****************************************************
// �}�N����`
//*****************************************************
#define SPEED_MOVE	(0.2f)	// �ړ����x
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
	m_pos = { 0.0f,0.0f,0.0f };
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
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager != nullptr)
	{
		CBlockManager::SInfoBlock *pInfoBlock = pBlockManager->GetInfoBlock();

		if (pInfoBlock == nullptr)
		{
			nullptr;
		}

		m_pObjectCursor = nullptr;

		m_pObjectCursor = CObjectX::Create();

		// �^�C�v�̏����ݒ�
		m_type = CBlock::TYPE_WALL;

		// ���f���ԍ��̐ݒ�
		m_pObjectCursor->BindModel(pInfoBlock[0].nIdxModel);

		m_pObjectCursor->SetEmissiveCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

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
	// ���擾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };
	float fSpeed = SPEED_MOVE;

	// �J�[�\���̃��[�v
	LoopCursor();

	if (m_pObjectCursor != nullptr && pKeyboard != nullptr && pMouse != nullptr && pBlockManager != nullptr)
	{
		// �u���b�N�ړ�
		ImGui::DragFloat("POS.X", &m_pos.x, SPEED_MOVE, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat("POS.Y", &m_pos.y, SPEED_MOVE, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat("POS.Z", &m_pos.z, SPEED_MOVE, -FLT_MAX, FLT_MAX);

		int nNumBlock = pBlockManager->GetNumBlock();
		CBlockManager::SInfoBlock *pInfoBlock = pBlockManager->GetInfoBlock();
		
		for (int i = 0;i < nNumBlock;i++)
		{// �u���b�N�I��
			if (ImGui::Button(&pInfoBlock[i].aTag[0], ImVec2(50.0f, 20.0f)))
			{
				m_nIdxObject = i;

				m_pObjectCursor->BindModel(pInfoBlock[i].nIdxModel);
			}
		}

		if (ImGui::Button("Create", ImVec2(50.0f, 20.0f)))
		{// �u���b�N����
			CreateBlock(m_pObjectCursor->GetPosition());
		}
		
		if (ImGui::Button("Save", ImVec2(50.0f, 20.0f)))
		{// �ۑ�
			CBlockManager *pBlockManager = CBlockManager::GetInstance();

			if (pBlockManager != nullptr)
			{
				pBlockManager->Save("data\\map.txt");
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

		// �폜�u���b�N�I��
		CBlock *pBlock = CheckDelete();

		if (pKeyboard->GetTrigger(DIK_BACKSPACE) && pBlock != nullptr)
		{
			pBlock->Uninit();
		}

		if (m_pObjectCursor != nullptr)
		{// �J�[�\���̃g�����X�t�H�[��
			m_pObjectCursor->SetPosition(m_pos);
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
// �J�[�\���̃��[�v
//=====================================================
void CEdit::LoopCursor(void)
{

}

//=====================================================
// �u���b�N�̐���
//=====================================================
void CEdit::CreateBlock(D3DXVECTOR3 pos)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
	{
		return;
	}

	CBlockManager::SInfoBlock *pInfoBlock = pBlockManager->GetInfoBlock();

	CBlock *pBlock = CBlock::Create(pInfoBlock[m_nIdxObject].nIdxModel);

	if (pBlock != nullptr)
	{
		pBlock->SetPosition(pos);
	}
}

//=====================================================
// �폜�u���b�N�̃`�F�b�N
//=====================================================
CBlock *CEdit::CheckDelete(void)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
	{
		return nullptr;
	}

	CBlock *pBlock = pBlockManager->GetHead();

	while (pBlock != nullptr)
	{
		CBlock *pBlockNext = pBlock->GetNext();

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

				return pBlock;
			}
		}

		pBlock = pBlockNext;
	}

	return nullptr;
}