//*****************************************************
//
// �u���b�N�̏���[block.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "block.h"
#include "blockManager.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "collision.h"
#include "debrisSpawner.h"
#include <stdio.h>

//*****************************************************
// �}�N����`
//*****************************************************
namespace
{
	const float SPEED_MOVE(1.0f);	// �ړ����x
	const char* MAP_FILE = "data\\MAP\\map01.bin";	// �}�b�v�̃t�@�C���p�X
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CBlock::m_nNumAll = 0;	// ����

//=====================================================
// �R���X�g���N�^
//=====================================================
CBlock::CBlock(int nPriority)
{
	m_pCollisionCube = nullptr;
	m_fLife = 0.0f;
	m_pPrev = nullptr;
	m_pNext = nullptr;
	m_nIdx = -1;

	// �擪�A�Ō���A�h���X�擾
	CBlockManager *pManager = CBlockManager::GetInstance();
	CBlock *pHead = nullptr;
	CBlock *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	if (pHead == nullptr)
	{// �擪�ƍŌ���A�h���X�̑��
		pManager->SetHead(this);
		pManager->SetTail(this);

		return;
	}

	// �O�̃A�h���X�ɍŌ���̃A�h���X��������
	m_pPrev = pTail;

	// �Ō���̃A�h���X�������ɂ���
	pManager->SetTail(this);

	if (m_pPrev != nullptr)
	{
		// �O�̃I�u�W�F�N�g�̎��̃A�h���X�������ɂ���
		m_pPrev->m_pNext = this;
	}

	m_nNumAll++;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBlock::~CBlock()
{
	// �擪�A�Ō���A�h���X�擾
	CBlockManager *pManager = CBlockManager::GetInstance();
	CBlock *pHead = nullptr;
	CBlock *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	m_nNumAll--;

	if (pTail != this && pHead != this)
	{// �^�񒆂̃A�h���X�̔j��
		if (m_pPrev != nullptr)
		{
			// �O�̃A�h���X���玟�̃A�h���X���Ȃ�
			m_pPrev->m_pNext = m_pNext;
		}

		if (m_pNext != nullptr)
		{
			// ���̃A�h���X����O�̃A�h���X���Ȃ�
			m_pNext->m_pPrev = m_pPrev;
		}
	}

	if (pHead == this)
	{// �擪�A�h���X�̔j��
		//if (m_pNext != nullptr)
		{// �擪�A�h���X�����̃A�h���X�Ɉ����p��
			pManager->SetHead(m_pNext);

			if (m_pNext != nullptr)
			{
				m_pNext->m_pPrev = nullptr;
			}
		}
	}

	if (pTail == this)
	{// �Ō���A�h���X�̔j��
		if (m_pPrev != nullptr)
		{// �Ō���A�h���X��O�̃A�h���X�Ɉ����p��
			pManager->SetTail(m_pPrev);

			m_pPrev->m_pNext = nullptr;
		}
	}

	m_nNumAll--;
}

//=====================================================
// ��������
//=====================================================
CBlock *CBlock::Create(int nIdxModel)
{
	CBlock *pBlock = nullptr;

	if (pBlock == nullptr)
	{// �C���X�^���X����
		pBlock = new CBlock;

		// ����������
		pBlock->Init();

		// ��ނ��Ƃ̃��f���Ǎ�
		pBlock->BindModel(nIdxModel);

		if (pBlock->m_pCollisionCube == nullptr)
		{// �����蔻�萶��
			pBlock->m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_BLOCK, pBlock);

			if (pBlock->m_pCollisionCube != nullptr)
			{
				pBlock->m_pCollisionCube->SetPosition(pBlock->GetPosition());

				pBlock->m_pCollisionCube->SetVtx(pBlock->GetVtxMax(), pBlock->GetVtxMin());
			}
		}
	}

	return pBlock;
}

//=====================================================
// ����������
//=====================================================
HRESULT CBlock::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �p���N���X�̏�����
	CObjectX::Init();

	// �^�C�v�̐ݒ�
	SetType(TYPE_BLOCK);

	m_fLife = 300.0f;

	// �e�̗L����
	EnableShadow(true);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CBlock::Uninit(void)
{
	// �����蔻��폜
	DeleteCollision();

	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �����蔻��̍폜
//=====================================================
void CBlock::DeleteCollision(void)
{
	if (m_pCollisionCube != nullptr)
	{// �����蔻��̏���
		m_pCollisionCube->Uninit();

		m_pCollisionCube = nullptr;
	}
}

//=====================================================
// �X�V����
//=====================================================
void CBlock::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();
}

//=====================================================
// �ʒu�ݒ�
//=====================================================
void CBlock::SetPosition(D3DXVECTOR3 pos)
{
	if (m_pCollisionCube != nullptr)
	{
		m_pCollisionCube->SetPosition(pos);
	}

	CObjectX::SetPosition(pos);
}

//=====================================================
// �`�揈��
//=====================================================
void CBlock::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// �q�b�g����
//=====================================================
void CBlock::Hit(float fDamage)
{
	//if (m_type == TYPE_IRONWALL)
	{
		//return;
	}

	m_fLife -= fDamage;

	if (m_fLife <= 0.0f)
	{// �j�󔻒�

		float fRotY = (rand() % 628 - 314) / 100.0f;
		
		// ���I�̐���
		CObjectX* pObjX = CObjectX::Create(GetPosition(), D3DXVECTOR3(GetRot().x, fRotY, GetRot().z));
		if (pObjX != nullptr)
		{
			int nRand = rand() % 2;
			
			if (nRand == 0)
			{
				pObjX->BindModel(CModel::Load("data\\MODEL\\block\\woodRubble00.x"));
			}
			else
			{
				pObjX->BindModel(CModel::Load("data\\MODEL\\block\\woodRubble01.x"));
			}
		}

		// �j�Ђ̐���
		CDebrisSpawner::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y + 50.0f, GetPosition().z), CDebrisSpawner::TYPE::TYPE_WALL, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		Uninit();
	}
}

//=====================================================
// ���_�����ւ��鏈��
//=====================================================
void CBlock::SetRot(D3DXVECTOR3 rot)
{
	if (rot.y != 0)
	{// �p�x�ɂ���čő咸�_�A�ŏ����_��ς��鏈��
		SwapVtx();
	}

	CObjectX::SetRot(rot);
}

//=====================================================
// ���_�����ւ��鏈��
//=====================================================
void CBlock::SwapVtx(void)
{
	D3DXVECTOR3 vtxMax = GetVtxMax();
	D3DXVECTOR3 vtxMin = GetVtxMin();
	D3DXVECTOR3 vtxTemp = vtxMin;
	
	vtxMin = { -vtxMax.z,vtxMin.y,-vtxMax.x };
	vtxMax = { -vtxTemp.z,vtxMax.y,-vtxTemp.x };

	SetVtxMax(vtxMax);
	SetVtxMin(vtxMin);
}