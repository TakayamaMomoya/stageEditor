//*****************************************************
//
// �e����[bullet.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "effect3D.h"
#include "particle.h"
#include "sound.h"
#include "collision.h"
#include "orbit.h"
#include "universal.h"
#include "object3D.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const int EDGE_ORBIT = 20;	// �O�Ղ̕ӂ̐�
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CBullet::m_nNumAll = 0;	// ����

//=====================================================
// �R���X�g���N�^
//=====================================================
CBullet::CBullet(int nPriority) : CObject(nPriority)
{
	m_fLife = 0.0f;
	m_fDamage = 0.0f;
	m_fSize = 0.0f;
	m_type = TYPE_NONE;
	m_bPierce = false;
	m_move = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_col = { 0.0f,0.0f,0.0f,0.0f };
	m_pCollisionSphere = nullptr;
	m_pObject3D = nullptr;
	m_nIdxPlayer = -1;

	// �����J�E���g�A�b�v
	m_nNumAll++;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBullet::~CBullet()
{
	m_nNumAll--;
}

//=====================================================
// ����������
//=====================================================
HRESULT CBullet::Init(void)
{
	m_rot.y = atan2f(m_move.x, m_move.z);
	float fLengthMove = sqrtf(m_move.x * m_move.x + m_move.z * m_move.z);

	m_rot.x = atan2f(fLengthMove,m_move.y) - D3DX_PI * 0.5f;

	universal::LimitRot(&m_rot.x);

	// �^�C�v�̐ݒ�
	SetType(TYPE_BULLET);

	// �����ڂ̐���
	if (m_pObject3D == nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRot();

		m_pObject3D = CObject3D::Create(pos, rot);

		if (m_pObject3D != nullptr)
		{
			m_pObject3D->SetSize(m_fSize, m_fSize * 5.0f);
			m_pObject3D->SetMode(CObject3D::MODE::MODE_STRETCHBILLBOARD);
			m_pObject3D->SetVtx();

			int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\EFFECT\\bullet000.png");
			m_pObject3D->SetIdxTexture(nIdx);
			m_pObject3D->SetColor(m_col);
			m_pObject3D->EnableAdd(true);
		}
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CBullet::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}

	if (m_pObject3D != nullptr)
	{
		m_pObject3D->Uninit();
		m_pObject3D = nullptr;
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CBullet::Update(void)
{
	// �ϐ��錾
	bool bHit = false;

	// ��������
	float fDeltaTime = CManager::GetDeltaTime();

	m_fLife -= fDeltaTime;

	m_posOld = m_pos;

	// �ʒu�̍X�V
	m_pos += m_move;

	if (m_pCollisionSphere != nullptr)
	{// �����蔻��̊Ǘ�
		// �^�O
		CCollision::TAG tag = CCollision::TAG_PLAYER;

		// �����蔻��̈ʒu�ݒ�
		m_pCollisionSphere->SetPositionOld(m_pCollisionSphere->GetPosition());
		m_pCollisionSphere->SetPosition(m_pos);

		switch (m_type)
		{
		case TYPE_PLAYER:
			tag = CCollision::TAG_ENEMY;

			// �ؔ��Ƃ̓����蔻��
			bHit = BulletHit(CCollision::TAG_BOX);
			break;
		case TYPE_ENEMY:
			tag = CCollision::TAG_PLAYER;
			break;
		default:
			break;
		}

		// �L�����N�^�[�Ƃ̓����蔻��
		bHit = BulletHit(tag);

		if (m_pCollisionSphere->TriggerCube(CCollision::TAG_BLOCK))
		{// �u���b�N�Ƃ̓����蔻��
			Death();
		}
	}

	if (bHit == false)
	{
		if (m_fLife < 0)
		{// �����̍폜
			Death();
		}
	}
	else
	{
		if (m_bPierce == false)
		{// �ђʂ��Ȃ��e�͏�����
			Death();
		}
	}

	if (m_pObject3D != nullptr)
	{// �����ڂ̒Ǐ]
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRot();

		m_pObject3D->SetPosition(pos);
		m_pObject3D->SetRot(rot);
		m_pObject3D->SetVtx();
	}
}

//=====================================================
// �����������m�F���鏈��
//=====================================================
bool CBullet::BulletHit(CCollision::TAG tag)
{
	bool bHit = false;

	if (m_pCollisionSphere->OnEnter(tag))
	{// �ΏۂƂ̓����蔻��
		CObject *pObj = m_pCollisionSphere->GetOther();

		if (pObj != nullptr)
		{
			bHit = true;

			// ���������I�u�W�F�N�g�̃q�b�g����
			pObj->Hit(m_fDamage);
		}
	}

	return bHit;
}

//=====================================================
// ���S����
//=====================================================
void CBullet::Death(void)
{
	// �I������
	Uninit();
}

//=====================================================
// �`�揈��
//=====================================================
void CBullet::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//=====================================================
// ��������
//=====================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, float fLife,TYPE type, bool bPierce, float fRadius, float fDamage, D3DXCOLOR col)
{
	CBullet *pBullet = nullptr;

	if (pBullet == nullptr)
	{// �C���X�^���X����
		pBullet = new CBullet;

		if (pBullet != nullptr)
		{
			pBullet->m_move = move;
			pBullet->m_pos = pos;
			pBullet->m_posOld = pos;
			pBullet->m_fLife = fLife;
			pBullet->m_type = type;
			pBullet->m_bPierce = bPierce;
			pBullet->m_fDamage = fDamage;
			pBullet->m_col = col;
			pBullet->m_fSize = fRadius;

			if (pBullet->m_pCollisionSphere == nullptr)
			{// �����蔻�萶��
				switch (type)
				{// ��ނ��ƂɃ^�O�̐ݒ�
				case TYPE_PLAYER:
					pBullet->m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_PLAYERBULLET, CCollision::TYPE_SPHERE, pBullet);
					break;
				case TYPE_ENEMY:
					pBullet->m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ENEMYBULLET, CCollision::TYPE_SPHERE, pBullet);
					break;
				default:
					break;
				}
			}

			if (pBullet->m_pCollisionSphere != nullptr)
			{
				pBullet->m_pCollisionSphere->SetPosition(pBullet->m_pos);

				pBullet->m_pCollisionSphere->SetRadius(fRadius);
			}

			// ����������
			pBullet->Init();
		}
	}

	return pBullet;
}