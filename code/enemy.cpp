//*****************************************************
//
// �G�̏���[enemy.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemy.h"
#include "manager.h"
#include "collision.h"
#include "debugproc.h"
#include "particle.h"
#include <stdio.h>
#include "player.h"
#include "game.h"
#include "enemyManager.h"
#include "enemyNormal.h"
#include "motion.h"
#include "universal.h"
#include "animEffect3D.h"
#include "sound.h"
#include "particle.h"
#include "texture.h"
#include "object2D.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float INITIAL_LIFE = 10.0f;	// �����̗�
const float INITIAL_SPEED = 1.0f;	// �������x
const float LINE_CHASE = 470;	// �ǐՏ�ԂɈڍs����G���A
const int DAMAGE_FRAME = 10;	// �_���[�W��Ԃ̃t���[����
const int TIME_DEATH = 60;	// ���S�܂ł̎���
const float DAMAGE_THROWN = 10.0f;	// �����ł̃_���[�W
const float SIZE_CURSOR = 30.0f;	// �J�[�\���T�C�Y
const char* CURSOR_PATH = "data\\TEXTURE\\UI\\lockon00.png";	// �J�[�\���̃e�N�X�`��
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CEnemy::m_nNumAll = 0;	// ����

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemy::CEnemy()
{
	// �����J�E���g�A�b�v
	m_nNumAll++;

	// �擪�A�Ō���A�h���X�擾
	CEnemyManager *pManager = CEnemyManager::GetInstance();
	CEnemy *pHead = nullptr;
	CEnemy *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	ZeroMemory(&m_info, sizeof(SInfo));

	// �l�̃N���A
	m_pPrev = nullptr;
	m_pNext = nullptr;

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
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemy::~CEnemy()
{
	// �擪�A�Ō���A�h���X�擾
	CEnemyManager *pManager = CEnemyManager::GetInstance();
	CEnemy *pHead = nullptr;
	CEnemy *pTail = nullptr;

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
}

//=====================================================
// ��������
//=====================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{// �C���X�^���X����
		switch (type)
		{
		case TYPE_NORMAL:

			pEnemy = new CEnemyNormal;

			pEnemy->Load("data\\Character\\robot00.txt");

			break;
		default:
			break;
		}

		// �ʒu�ݒ�
		pEnemy->SetPosition(pos);

		// ����������
		pEnemy->Init();
	}

	return pEnemy;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemy::Init(void)
{
	// �p���N���X�̏�����
	CMotion::Init();

	// �^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	// �����蔻�萶��
	CreateCollision();

	// �p�����[�^�[�����ݒ�
	m_info.fLife = INITIAL_LIFE;
	SetMoveSpeed(INITIAL_SPEED);

	// �ʏ��Ԃɂ���
	m_info.state = STATE_NORMAL;
	m_info.moveState = MOVESTATE_INTRUSION;

	SetPositionOld(GetPosition());

	// �e�̗L����
	EnableShadow(true);
	SetPosShadow(D3DXVECTOR3(0.0f, 0.5f, 0.0f));

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemy::Uninit(void)
{
	CEnemyManager *pEnemyManager = CEnemyManager::GetInstance();

	if (pEnemyManager != nullptr)
		pEnemyManager->CheckDeathLockon(this);

	if (m_info.pCursor != nullptr)
	{
		m_info.pCursor->Uninit();
		m_info.pCursor = nullptr;
	}

	// �����蔻��폜
	DeleteCollision();

	// �p���N���X�̏I��
	CMotion::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemy::Update(void)
{
	// �p���N���X�̍X�V
	CMotion::Update();

	// ��ԊǗ�
	ManageState();

	// �����蔻��̊Ǘ�
	ManageCollision();

	// �ړ��ʂ𔽉f
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();

	SetPositionOld(pos);

	pos += move;
	SetPosition(pos);

	// �ړ��ʂ̌���
	move *= 0.95f;
	SetMove(move);
}

//=====================================================
// �����蔻��̊Ǘ�
//=====================================================
void CEnemy::ManageCollision(void)
{
	if (m_info.pCollisionSphere != nullptr)
	{// ���̓����蔻��̊Ǘ�
		D3DXVECTOR3 posWaist = GetMtxPos(0);

		D3DXVECTOR3 pos = GetPosition();

		m_info.pCollisionSphere->SetPosition(pos);

		if (m_info.state != STATE_THROWN)
		{
			m_info.pCollisionSphere->PushCollision(&pos, CCollision::TAG_PLAYER);
			m_info.pCollisionSphere->PushCollision(&pos, CCollision::TAG_ENEMY);

			SetPosition(pos);
		}

		m_info.pCollisionSphere->SetPositionOld(m_info.pCollisionSphere->GetPosition());

		m_info.pCollisionSphere->SetPosition(posWaist);
	}

	if (m_info.pCollisionCube != nullptr)
	{// �����̂̓����蔻��̊Ǘ�
		// �����蔻��̈ʒu�ݒ�
		m_info.pCollisionCube->SetPositionOld(m_info.pCollisionCube->GetPosition());
		m_info.pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 move = GetMove();

		// �����o���̓����蔻��
		m_info.pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);
		SetMove(move);
	}
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CEnemy::ManageState(void)
{
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	switch (m_info.state)
	{
	case STATE_NORMAL:
		break;
	case STATE_THROWN:

		CollisionThrown();

		break;
	case STATE_DAMAGE:
		if (m_info.nTimerState > DAMAGE_FRAME)
		{// �ʏ��Ԃɖ߂�
			m_info.nTimerState = 0;
			m_info.state = STATE_NORMAL;

			ResetAllCol();
		}
		else
		{// �J�E���g�A�b�v
			m_info.nTimerState++;
		}

		break;
	case STATE_DEATH:

		m_info.nTimerState++;

		// �����ɂȂ�Ȃ��������
		col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);

		col.a = 1.0f - (float)((float)(m_info.nTimerState) / (TIME_DEATH));

		SetAllCol(col);

		if (m_info.nTimerState >= TIME_DEATH)
		{// ���S
			Uninit();
		}

		break;
	default:
		break;
	}
}

//=====================================================
// �ړ���ԊǗ�
//=====================================================
void CEnemy::ManageMoveState(void)
{
	switch (m_info.moveState)
	{
	case MOVESTATE_INTRUSION:
		// �N�����悤�Ƃ��Ă�����
		if (IsInArea())
		{// �G���A���ɓ�������A�ǐՂֈڍs
			TransferChase();
		}

		break;
	case MOVESTATE_CHASE:
		// �Ώۂ�ǐՂ��Ă�����
		

		break;
	}
}

//=====================================================
// �ǐՂɈڍs����
//=====================================================
void CEnemy::TransferChase(void)
{
	m_info.moveState = MOVESTATE_CHASE;
}

//=====================================================
// �G���A�ɓ���������
//=====================================================
bool CEnemy::IsInArea(void)
{
	D3DXVECTOR3 pos = GetPosition();

	if (pos.x <= LINE_CHASE && pos.x >= -LINE_CHASE && pos.z <= LINE_CHASE && pos.z >= -LINE_CHASE)
	{
		return true;
	}

	return false;
}

//=====================================================
// �������Ă鎞�̔���
//=====================================================
void CEnemy::CollisionThrown(void)
{
	if (m_info.pCollisionSphere != nullptr)
	{
		m_info.pCollisionSphere->SetRadius(200.0f);

		if (m_info.pCollisionSphere->OnEnter(CCollision::TAG_ENEMY))
		{
			// ���������G�Ƀ_���[�W��^����
			m_info.pCollisionSphere->DamageAll(CCollision::TAG_ENEMY, DAMAGE_THROWN);
		}

		if (m_info.pCollisionSphere != nullptr)
		{
			m_info.pCollisionSphere->SetRadius(90.0f);
		}
	}
}

//=====================================================
// �ڕW�̒ǐ�
//=====================================================
void CEnemy::ChaseTarget(void)
{
	// ��Ԃɂ���ĒǐՂ����Ȃ�
	CGame *pGame = CGame::GetInstance();
	CEnemy::STATE state = GetState();

	if (state == CEnemy::STATE::STATE_DEATH)
	{
		return;
	}

	if (pGame != nullptr)
	{
		CGame::STATE state = pGame->GetState();

		if (state != CGame::STATE::STATE_NORMAL)
		{
			return;
		}
	}

	// �ړ��ʂ̐ݒ�
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 vecDiff = m_info.posDest - pos;
	D3DXVECTOR3 move = GetMove();

	D3DXVec3Normalize(&vecDiff, &vecDiff);

	vecDiff *= m_info.fMoveSpeed;

	move += vecDiff;

	SetMove(move);

	// ������ڕW�����ɕ␳
	float fAngleDist = atan2f(vecDiff.x, vecDiff.z);
	D3DXVECTOR3 rot = GetRot();

	fAngleDist += D3DX_PI;

	universal::FactingRot(&rot.y, fAngleDist, 0.1f);

	SetRot(rot);
}

//=====================================================
// �̗͐ݒ�
//=====================================================
void CEnemy::SetLife(float fLife)
{
	m_info.fLife = fLife;

	if (m_info.fLife < 0)
	{
		m_info.fLife = 0;
	}
}

//=====================================================
// �q�b�g����
//=====================================================
void CEnemy::Hit(float fDamage)
{
	if (m_info.state != STATE_DEATH)
	{
		m_info.fLife -= fDamage;

		// �_���[�W�G�t�F�N�g�̐���
		CAnimEffect3D *pAnim3D = CAnimEffect3D::GetInstance();

		CSound* pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(pSound->LABEL_SE_HIT);
		}

		if (pAnim3D != nullptr)
		{
			D3DXVECTOR3 pos = GetPosition();

			pAnim3D->CreateEffect(pos,CAnimEffect3D::TYPE::TYPE_BLOOD);
		}

		if (m_info.fLife <= 0.0f)
		{// ���S���
			m_info.fLife = 0.0f;

			m_info.state = STATE_DEATH;

			// �X�R�A�Ǘ�
			ManageScore();

			if (pAnim3D != nullptr)
			{
				D3DXVECTOR3 pos = GetPosition();

				pAnim3D->CreateEffect(pos, CAnimEffect3D::TYPE::TYPE_BLOOD1);
			}

			// �g�}�g�`
			CParticle::Create(GetPosition(), CParticle::TYPE::TYPE_TOMATO_JUICE);

			// �����蔻��폜
			DeleteCollision();

			// ���S����
			Death();
		}
		else
		{
			m_info.state = STATE_DAMAGE;

			// �q�b�g�F
			D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			SetAllCol(col);
		}
	}
}

//=====================================================
// ���S����
//=====================================================
void CEnemy::Death(void)
{
	m_info.state = STATE_DEATH;
}

//=====================================================
// �X�R�A�Ǘ�
//=====================================================
void CEnemy::ManageScore(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CEnemy::Draw(void)
{
	// �p���N���X�̕`��
	CMotion::Draw();

#ifdef _DEBUG
	CDebugProc::GetInstance()->Print("\n�G�̈ړ��ʁF[%f,%f,%f]", GetMove().x, GetMove().y, GetMove().z);
#endif
}

//=====================================================
// ���̓����蔻��̈ʒu�ݒ�
//=====================================================
void CEnemy::SetSpherePosition(D3DXVECTOR3 pos)
{
	if (m_info.pCollisionSphere != nullptr)
	{// �ʒu�ݒ�
		m_info.pCollisionSphere->SetPosition(pos);
	}
}

//=====================================================
// �����蔻�萶��
//=====================================================
void CEnemy::CreateCollision(void)
{
	if (m_info.pCollisionSphere == nullptr)
	{// ���̓����蔻�萶��
		m_info.pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ENEMY, CCollision::TYPE_SPHERE, this);

		if (m_info.pCollisionSphere != nullptr)
		{// ���̐ݒ�
			m_info.pCollisionSphere->SetPosition(GetPosition());
			m_info.pCollisionSphere->SetRadius(90.0f);
		}
	}

	if (m_info.pCollisionCube == nullptr)
	{// �����̂̓����蔻��
		m_info.pCollisionCube = CCollisionCube::Create(CCollision::TAG_ENEMY, this);

		D3DXVECTOR3 vtxMax = { 20,20,20 };
		D3DXVECTOR3 vtxMin = { -20,0.0f,-20 };

		if (m_info.pCollisionCube != nullptr)
		{
			m_info.pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}
}

//=====================================================
// �����蔻��폜
//=====================================================
void CEnemy::DeleteCollision(void)
{
	if (m_info.pCollisionSphere != nullptr)
	{// �����蔻��̏���
		m_info.pCollisionSphere->Uninit();

		m_info.pCollisionSphere = nullptr;
	}

	if (m_info.pCollisionCube != nullptr)
	{// �����蔻��̏���
		m_info.pCollisionCube->Uninit();

		m_info.pCollisionCube = nullptr;
	}
}

//=====================================================
// ���b�N�ł��邩�ǂ����̐ݒ�
//=====================================================
void CEnemy::EnableLock(bool bLock)
{
	if (bLock)
	{
		if (m_info.pCursor == nullptr)
		{// �J�[�\������
			m_info.pCursor = CObject2D::Create(7);

			if (m_info.pCursor != nullptr)
			{
				m_info.pCursor->SetSize(SIZE_CURSOR, SIZE_CURSOR);
				int nIdx = CTexture::GetInstance()->Regist(CURSOR_PATH);
				m_info.pCursor->SetIdxTexture(nIdx);
				m_info.pCursor->SetVtx();
			}
		}
	}
	else
	{
		if (m_info.pCursor != nullptr)
		{
			m_info.pCursor->Uninit();
			m_info.pCursor = nullptr;
		}
	}
}

//=====================================================
// �J�[�\���ʒu�ݒ�
//=====================================================
void CEnemy::SetPositionCursor(D3DXVECTOR3 pos)
{
	if (m_info.pCursor != nullptr)
	{
		m_info.pCursor->SetPosition(pos);
		m_info.pCursor->SetVtx();
	}
}