//*****************************************************
//
// �����蔻�菈��[collision.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "collision.h"
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "manager.h"
#include "debugproc.h"
#include "billboard.h"
#include "texture.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_EDGE	(4)	// �ӂ̐�

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CCollision *CCollision::m_apCollision[NUM_OBJECT] = {};	// �����蔻��Ǘ��p�̔z��
int CCollision::m_nNumAll = 0;

//=====================================================
// �R���X�g���N�^
//=====================================================
CCollision::CCollision()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_tag = TAG_NONE;
	m_pObjectOwner = nullptr;
	m_pObjectOther = nullptr;

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (m_apCollision[nCnt] == nullptr)
		{// �ۊǂ���
			m_apCollision[nCnt] = this;

			// ID�L��
			m_nID = nCnt;

			m_nNumAll++;

			break;
		}
	}
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CCollision::~CCollision()
{
	m_nNumAll--;
}

//=====================================================
// ����������
//=====================================================
HRESULT CCollision::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CCollision::Uninit(void)
{
	if (m_apCollision[m_nID] != nullptr)
	{
		m_apCollision[m_nID] = nullptr;
	}

	if (m_pObjectOwner != nullptr)
	{
		m_pObjectOwner = nullptr;
	}

	if (m_pObjectOther != nullptr)
	{
		m_pObjectOther = nullptr;
	}

	Release();
}

//=====================================================
// �폜����
//=====================================================
void CCollision::DeleteAll(void)
{
	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (m_apCollision[nCnt] != nullptr)
		{// �폜����
			m_apCollision[nCnt]->Uninit();
		}
	}
}

//=====================================================
// �X�V����
//=====================================================
void CCollision::Update(void)
{

}

//=====================================================
// �L���[�u�Ƃ̃g���K�[����
//=====================================================
bool CCollision::TriggerCube(TAG tag)
{
	// �ϐ��錾
	bool bHitOld = false;
	bool bHit = false;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;

	// �����蔻��̎擾
	CCollision **ppCollision = GetCollision();

	pos = GetOwner()->GetPosition();
	posOld = GetOwner()->GetPositionOld();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE)
			{
				if (ppCollision[nCnt]->GetTag() != tag && tag != TAG_NONE)
				{
					continue;
				}

				vtxMax = ppCollision[nCnt]->GetVtxMax() + ppCollision[nCnt]->GetPosition();
				vtxMin = ppCollision[nCnt]->GetVtxMin() + ppCollision[nCnt]->GetPosition();

				if (pos.y > vtxMin.y && pos.y < vtxMax.y &&
					pos.x > vtxMin.x && pos.x < vtxMax.x &&
					pos.z > vtxMin.z && pos.z < vtxMax.z)
				{// ���݃u���b�N�̒��ɂ���
					if (posOld.y < vtxMin.y || posOld.y > vtxMax.y ||
						posOld.x < vtxMin.x || posOld.x > vtxMax.x ||
						posOld.z < vtxMin.z || posOld.z > vtxMax.z)
					{// �O��u���b�N�̒��ɂ��Ȃ�
						SetOther(ppCollision[nCnt]->GetOwner());

						bHit = true;
					}
				}
			}
		}
	}

	return bHit;
}

//=====================================================
// �L���[�u����_�Ԃɂ��邩����
//=====================================================
bool CCollision::ChckObstclBtwn(CObject *pObj, D3DXVECTOR3 vecDiff)
{
	D3DXVECTOR3 pos,posTarget;
	D3DXVECTOR3 vtxMax, vtxMin;
	D3DXVECTOR3 vtxMaxOwn, vtxMinOwn;
	D3DXVECTOR3 aVector[NUM_EDGE];
	int nIdx;
	float fRate;

	if (pObj == nullptr)
	{
		return false;
	}

	// �󂯎�����I�u�W�F�N�g�̈ʒu���擾
	pos = pObj->GetPosition();
	posTarget = pos + vecDiff;

	// �����蔻��̎擾
	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE && ppCollision[nCnt] != this)
			{
				if (ppCollision[nCnt]->GetTag() != TAG_BLOCK)
				{// �^�O�ɍ���Ȃ���ΌJ��Ԃ�
					continue;
				}

				// �ő�E�ŏ����_�̎擾
				vtxMax = ppCollision[nCnt]->GetVtxMax() + ppCollision[nCnt]->GetPosition();
				vtxMin = ppCollision[nCnt]->GetVtxMin() + ppCollision[nCnt]->GetPosition();
				vtxMaxOwn = GetVtxMax();
				vtxMinOwn = GetVtxMin();

				// �l�_�̈ʒu��ݒ�
				aVector[0] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);
				aVector[1] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
				aVector[2] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
				aVector[3] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);
				
				// �ǂ̃x�N�g���Ƀg���K�[���肪�������̂��m�F
				for (int nCntEdge = 0; nCntEdge < NUM_EDGE; nCntEdge++)
				{
					nIdx = (nCntEdge + 1) % NUM_EDGE;

					if (IsCross(pos, aVector[nCntEdge], aVector[nIdx], &fRate, vecDiff) &&
						IsCross(posTarget, aVector[nCntEdge], aVector[nIdx], &fRate, vecDiff) == false)
					{
						fRate *= 1;

						if (fRate < 1.0f && fRate > 0.0f)
						{// �������ӂɐڐG���Ă�����

							if (pos.y < vtxMax.y)
							{
								return true;
							}
						}
					}

				}
			}
		}
	}

	return false;
}

//=====================================================
// �O�ς̓����蔻��v�Z
//=====================================================
bool CCollision::IsCross(D3DXVECTOR3 posTarget, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest, float *pRate,D3DXVECTOR3 move)
{
	bool bHit = false;

	D3DXVECTOR3 vec1 = vecDest - vecSorce;

	if (vec1.z * (posTarget.x - vecSorce.x) - vec1.x * (posTarget.z - vecSorce.z) < 0)
	{
		D3DXVECTOR3 vecToPos = posTarget - vecSorce;

		if (pRate != nullptr)
		{
			// �������Z�o
			float fAreaMax = (vecDest.z * move.x) - (vecDest.x * move.z);
			float fArea = (vecToPos.z * move.x) - (vecToPos.x * move.z);
			*pRate = fArea / fAreaMax;
		}

		bHit = true;
	}

	return bHit;
}

//=====================================================
// �O�ς̃g���K�[����v�Z
//=====================================================
bool CCollision::IsCrossTrigger(D3DXVECTOR3 posTarget, D3DXVECTOR3 posTargetOld, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest)
{
	bool bHit = false;

	D3DXVECTOR3 vec = vecDest - vecSorce;

	if (vec.z * (posTarget.x - vecSorce.x) - vec.x * (posTarget.z - vecSorce.z) > 0 &&
		vec.z * (posTargetOld.x - vecSorce.x) - vec.x * (posTargetOld.z - vecSorce.z) < 0)
	{
		bHit = true;
	}

	return bHit;
}

//=====================================================
// �ʒu�ݒ�
//=====================================================
void CCollision::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
// ��������
//=====================================================
CCollision *CCollision::Create(TAG tag, TYPE type, CObject *obj)
{
	CCollision *pCollision = nullptr;

	if (pCollision == nullptr)
	{
		// �C���X�^���X����
		switch (type)
		{
		case TYPE_SPHERE:
			pCollision = new CCollisionSphere;
			break;
		default:
			break;
		}

		if (pCollision != nullptr)
		{
			// ����������
			pCollision->Init();

			// �^�O�󂯎��
			pCollision->m_tag = tag;

			// ������̃|�C���^
			pCollision->m_pObjectOwner = obj;
		}
	}

	return pCollision;
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CCollisionSphere::CCollisionSphere()
{
	m_fRadius = 0.0f;

	SetType(TYPE_SPHERE);

	m_pBillboard = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CCollisionSphere::~CCollisionSphere()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CCollisionSphere::Init(void)
{
#ifdef _DEBUG
	if (m_pBillboard == nullptr)
	{// �r���{�[�h�̐���
		m_pBillboard = CBillboard::Create(GetPosition(),m_fRadius,m_fRadius);

		if (m_pBillboard != nullptr)
		{
			int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\EFFECT\\collision.png");
			m_pBillboard->SetIdxTexture(nIdx);
		}
	}
#endif

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CCollisionSphere::Uninit(void)
{
	if (m_pBillboard != nullptr)
	{// �r���{�[�h�̍폜
		m_pBillboard->Uninit();
		m_pBillboard = nullptr;
	}

	CCollision::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CCollisionSphere::Update(void)
{
	if (m_pBillboard != nullptr)
	{// �r���{�[�h�̒Ǐ]
		D3DXVECTOR3 pos = GetPosition();

		m_pBillboard->SetPosition(pos);

		m_pBillboard->SetSize(m_fRadius, m_fRadius);
	}
}

//=====================================================
// ���̓����蔻��
//=====================================================
bool CCollisionSphere::OnEnter(TAG tag)
{
	bool bHit = false;

	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag || ppCollision[nCnt] == this)
				{
					continue;
				}

				// �����擾
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - GetPosition();

				float fLength = D3DXVec3Length(&vecDiff);

				if (fLength < ppCollision[nCnt]->GetRadius() + GetRadius())
				{
					// �Ԃ���������̎�����𔻕�
					SetOther(ppCollision[nCnt]->GetOwner());

					return true;
				}
			}
		}
	}

	return bHit;
}

//=====================================================
// ���������I�u�W�F�N�g���ׂĂɃ_���[�W��^���鏈��
//=====================================================
void CCollisionSphere::DamageAll(TAG tag,float fDamage)
{
	bool bHit = false;

	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag)
				{
					continue;
				}

				// �����擾
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - GetPosition();

				float fLength = D3DXVec3Length(&vecDiff);

				if (fLength < ppCollision[nCnt]->GetRadius() + GetRadius())
				{
					ppCollision[nCnt]->GetOwner()->Hit(fDamage);
				}
			}
		}
	}
}


//=====================================================
// ����ʂ蔲��������
//=====================================================
bool CCollisionSphere::IsTriggerExit(TAG tag)
{
	bool bExit = false;

	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag)
				{
					continue;
				}

				// �����擾
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - GetPosition();

				// �����̒���
				float fLengthDiff = D3DXVec3Length(&vecDiff);

				// �O��̈ʒu�Ƃ̍���
				vecDiff = ppCollision[nCnt]->GetOwner()->GetPositionOld() - GetPositionOld();

				float fLengthOld = D3DXVec3Length(&vecDiff);

				// �Ԃ��鎞�̋���
				float fLength = ppCollision[nCnt]->GetRadius() + GetRadius();

				if (fLengthDiff >= fLength && fLengthOld < fLength)
				{
					// �Ԃ���������̎�����𔻕�
					SetOther(ppCollision[nCnt]->GetOwner());

					return true;
				}
			}
		}
	}

	return bExit;
}

//=====================================================
// �����Ԃ������u�Ԃ̔���
//=====================================================
bool CCollisionSphere::IsTriggerEnter(TAG tag)
{
	bool bExit = false;

	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag)
				{
					continue;
				}

				// �����擾
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - GetPosition();

				// �����̒���
				float fLengthDiff = D3DXVec3Length(&vecDiff);

				// �O��̈ʒu�Ƃ̍���
				vecDiff = ppCollision[nCnt]->GetOwner()->GetPositionOld() - GetPositionOld();

				float fLengthOld = D3DXVec3Length(&vecDiff);

				// �Ԃ��鎞�̋���
				float fLength = ppCollision[nCnt]->GetRadius() + GetRadius();

				if (fLengthDiff <= fLength && fLengthOld > fLength)
				{
					// �Ԃ���������̎�����𔻕�
					SetOther(ppCollision[nCnt]->GetOwner());

					return true;
				}
			}
		}
	}

	return bExit;
}

//=====================================================
// ���̉����o���̔���
//=====================================================
void CCollisionSphere::PushCollision(D3DXVECTOR3* pPos, TAG tag)
{

	CCollision** ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag || ppCollision[nCnt] == this)
				{
					continue;
				}

				D3DXVECTOR3 pos = { pPos->x,pPos->y,pPos->z };
				D3DXVECTOR3 posTarget = { ppCollision[nCnt]->GetPosition().x,ppCollision[nCnt]->GetPosition().y, ppCollision[nCnt]->GetPosition().z };

				// �����擾
				D3DXVECTOR3 vecDiff = posTarget - pos;

				// �����̒���
				float fLengthDiff = D3DXVec3Length(&vecDiff);

				// �Ԃ��鎞�̋���
				float fLength = ppCollision[nCnt]->GetRadius() + GetRadius();

				if (fLengthDiff < fLength)
				{
					D3DXVECTOR3 posAfter;	// �����o����̍��W

					// �����x�N�g�����牟���o����̈ʒu���v�Z
					D3DXVec3Normalize(&posAfter,&vecDiff);

					posAfter *= -fLength;

					posAfter += posTarget;

					*pPos = posAfter;
				}
			}
		}
	}
}

//=====================================================
// ��������
//=====================================================
CCollisionSphere *CCollisionSphere::Create(TAG tag, TYPE type, CObject *obj)
{
	CCollisionSphere *pCollision = nullptr;

	if (pCollision == nullptr)
	{
		// �C���X�^���X����
		pCollision = new CCollisionSphere;

		if (pCollision != nullptr)
		{
			// ����������
			pCollision->Init();

			// �^�O�󂯎��
			pCollision->SetTag(tag);

			// ������̃|�C���^
			pCollision->SetOwner(obj);
		}
	}

	return pCollision;
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CCollisionCube::CCollisionCube()
{
	m_vtxMax = { 0.0f,0.0f,0.0f };
	m_vtxMin = { 0.0f,0.0f,0.0f };

	SetType(TYPE_CUBE);
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CCollisionCube::~CCollisionCube()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CCollisionCube::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CCollisionCube::Uninit(void)
{
	CCollision::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CCollisionCube::Update(void)
{

}

//=====================================================
// �����̂̓����蔻��
//=====================================================
bool CCollisionCube::CubeCollision(TAG tag, D3DXVECTOR3 *pMove, CObject **ppObjOther)
{
	bool bLand = false;
	D3DXVECTOR3 pos;
	CCollision **ppCollision = GetCollision();

	// �v�Z�p�ϐ�
	D3DXVECTOR3 posOwn;
	D3DXVECTOR3 posOwnOld;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMaxOwn;
	D3DXVECTOR3 vtxMinOwn;

	if (GetOwner() != nullptr)
	{// �����̐ݒ�
		posOwn = GetOwner()->GetPosition();
		posOwnOld = GetOwner()->GetPositionOld();
		vtxMaxOwn = GetVtxMax();
		vtxMinOwn = GetVtxMin();
	}

	if (ppObjOther != nullptr)
	{
		*ppObjOther = nullptr;
	}

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE)
			{
				if (ppCollision[nCnt]->GetTag() != tag && tag != TAG_NONE)
				{// �^�O�ɍ���Ȃ���ΌJ��Ԃ�
					continue;
				}

				// ����̈ʒu���擾
				pos = ppCollision[nCnt]->GetPosition();

				// ����̍ő咸�_���擾
				vtxMax = ppCollision[nCnt]->GetVtxMax() + ppCollision[nCnt]->GetPosition();
				vtxMin = ppCollision[nCnt]->GetVtxMin() + ppCollision[nCnt]->GetPosition();

				if (posOwn.y >= vtxMin.y - vtxMaxOwn.y &&
					posOwn.y <= vtxMax.y)
				{//�㉺�œ����Ă���ꍇ
					if (posOwn.z >= vtxMin.z - vtxMaxOwn.z &&
						posOwn.z <= vtxMax.z + vtxMaxOwn.z)
					{//������̓����蔻��
						if (posOwnOld.x >= vtxMax.x - vtxMinOwn.x &&
							posOwn.x < vtxMax.x - vtxMinOwn.x)
						{//�E���瓖�������ꍇ
							//�E�ɖ߂�
							posOwn.x = vtxMax.x - vtxMinOwn.x + 0.2f;

							//�ړ��ʂ��Ȃ���
							pMove->x = 0;

							if (ppObjOther != nullptr)
							{
								*ppObjOther = ppCollision[nCnt]->GetOwner();
							}
						}

						if (posOwnOld.x <= vtxMin.x - vtxMaxOwn.x &&
							posOwn.x > vtxMin.x - vtxMaxOwn.x)
						{//�����瓖�������ꍇ
							//���ɖ߂�
							posOwn.x = vtxMin.x - vtxMaxOwn.x - 0.2f;

							//�ړ��ʂ��Ȃ���
							pMove->x = 0;

							if (ppObjOther != nullptr)
							{
								*ppObjOther = ppCollision[nCnt]->GetOwner();
							}
						}
					}

					if (posOwn.x >= vtxMin.x - vtxMaxOwn.x &&
						posOwn.x <= vtxMax.x - vtxMinOwn.x)
					{//���s���̓����蔻��

						if (posOwnOld.z <= vtxMin.z - vtxMaxOwn.z &&
							posOwn.z > vtxMin.z - vtxMaxOwn.z)
						{//��O���瓖�������ꍇ
							//��O�ɖ߂�
							posOwn.z = vtxMin.z - vtxMaxOwn.z - 0.2f;

							//�ړ��ʂ��Ȃ���
							pMove->z = 0;

							if (ppObjOther != nullptr)
							{
								*ppObjOther = ppCollision[nCnt]->GetOwner();
							}
						}

						if (posOwnOld.z >= vtxMax.z - vtxMinOwn.z &&
							posOwn.z < vtxMax.z - vtxMinOwn.z)
						{//��O���瓖�������ꍇ
						 //��O�ɖ߂�
							posOwn.z = vtxMax.z - vtxMinOwn.z + 0.2f;

							//�ړ��ʂ��Ȃ���
							pMove->z = 0;

							if (ppObjOther != nullptr)
							{
								*ppObjOther = ppCollision[nCnt]->GetOwner();
							}
						}
					}

					if (posOwn.z >= vtxMin.z - vtxMaxOwn.z &&
						posOwn.z <= vtxMax.z + vtxMaxOwn.z &&
						posOwn.x >= vtxMin.x - vtxMaxOwn.x &&
						posOwn.x <= vtxMax.x - vtxMinOwn.x)
					{// XZ���ʂ̒��ɂ���ꍇ
						if (posOwnOld.y <= vtxMin.y - vtxMaxOwn.y)
						{// �����瓖�������ꍇ
							posOwn.y = vtxMin.y - vtxMaxOwn.y;
						}
						else if (posOwnOld.y >= vtxMax.y)
						{// �ォ�瓖�������ꍇ
							posOwn.y = vtxMax.y;

							// �ړ��ʂ��Ȃ���
							pMove->y = 0.0f;

							bLand = true;

							if (ppObjOther != nullptr)
							{
								*ppObjOther = ppCollision[nCnt]->GetOwner();
							}
						}
					}
				}

				GetOwner()->SetPosition(posOwn);
			}
		}
	}

	return bLand;
}

//=====================================================
// ���_�ݒ�
//=====================================================
void CCollisionCube::SetVtx(D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	m_vtxMax = vtxMax; 
	m_vtxMin = vtxMin;
}

//=====================================================
// ���������x�N�g���̎擾
//=====================================================
D3DXVECTOR3 CCollisionCube::CollisionVector(CObject *pObj)
{
	D3DXVECTOR3 vecDest = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 vecDiff;
	D3DXVECTOR3 pos, posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 vecToPos;
	D3DXVECTOR3 vtxMax, vtxMin;
	D3DXVECTOR3 vtxMaxOwn, vtxMinOwn;
	D3DXVECTOR3 aVector[NUM_EDGE];
	int nIdx;
	float fLengthSorce;
	float fLengthDest;

	if (pObj == nullptr)
	{
		return vecDest;
	}

	// �󂯎�����I�u�W�F�N�g�̈ʒu���擾
	pos = pObj->GetPosition();
	posOld = pObj->GetPositionOld();

	move = pos - posOld;

	// �����蔻��̎擾
	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE && ppCollision[nCnt] != this)
			{
				if (ppCollision[nCnt]->GetTag() != TAG_BLOCK)
				{// �^�O�ɍ���Ȃ���ΌJ��Ԃ�
					continue;
				}

				vtxMax = ppCollision[nCnt]->GetVtxMax() + ppCollision[nCnt]->GetPosition();
				vtxMin = ppCollision[nCnt]->GetVtxMin() + ppCollision[nCnt]->GetPosition();
				vtxMaxOwn = GetVtxMax();
				vtxMinOwn = GetVtxMin();

				if (pos.z >= vtxMin.z - vtxMaxOwn.z &&
					pos.z <= vtxMax.z - vtxMinOwn.z &&
					pos.x >= vtxMin.x - vtxMaxOwn.x &&
					pos.x <= vtxMax.x - vtxMinOwn.x &&
					pos.y >= vtxMin.y - vtxMaxOwn.y &&
					pos.y <= vtxMax.y - vtxMinOwn.y)
				{// ���݃u���b�N�̒��ɂ���
					aVector[0] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);
					aVector[1] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
					aVector[2] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
					aVector[3] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);

					// �ǂ̃x�N�g���Ƀg���K�[���肪�������̂��m�F
					for (int nCntEdge = 0; nCntEdge < NUM_EDGE; nCntEdge++)
					{
						nIdx = (nCntEdge + 1) % NUM_EDGE;

						if (IsCrossTrigger(pos, posOld, aVector[nCntEdge], aVector[nIdx]))
						{
							vecDest = aVector[nIdx] - aVector[nCntEdge];

							vecToPos = pos - aVector[nIdx];

							// �������Z�o
							float fAreaMax = (vecDest.z * move.x) - (vecDest.x * move.z);
							float fArea = (vecToPos.z * move.x) - (vecToPos.x * move.z);
							float fRate = fArea / fAreaMax;

							fLengthDest = D3DXVec3Length(&aVector[nIdx]);
							fLengthSorce = D3DXVec3Length(&aVector[nCntEdge]);

							// �ŒZ�����ɂ���ĖڕW�x�N�g�����]
							if (fLengthSorce < fLengthDest)
							{
								vecDest *= -1.0f - fRate;
							}
							else
							{
								vecDest *= -fRate;
							}
						}
					}
				}
			}
		}
	}

	return vecDest;
}

//=====================================================
// ��������
//=====================================================
CCollisionCube *CCollisionCube::Create(TAG tag, CObject *obj)
{
	CCollisionCube *pCollision = nullptr;

	if (pCollision == nullptr)
	{
		// �C���X�^���X����
		pCollision = new CCollisionCube;

		if (pCollision != nullptr)
		{
			// ����������
			pCollision->Init();

			// �^�O�󂯎��
			pCollision->SetTag(tag);

			// ������̃|�C���^
			pCollision->SetOwner(obj);
		}
	}

	return pCollision;
}