//*****************************************
//
// ���낢��ėp�����l�ߍ���
// Author:���R����
//
//*****************************************

//*****************************************
// �C���N���[�h
//*****************************************
#include "manager.h"
#include "renderer.h"
#include "universal.h"
#include "debugproc.h"
#include <stdio.h>

namespace universal
{
//=========================================
// �l�̐���
//=========================================
void LimitValue(float *pValue, float fMax, float fMin)
{
	if (fMax < *pValue)
	{
		*pValue = fMax;
	}

	if (fMin > *pValue)
	{
		*pValue = fMin;
	}
}

//=========================================
// ��]���䏈��
//=========================================
void LimitRot(float *fRot)
{
	if (*fRot > D3DX_PI)
	{
		*fRot -= 6.28f;
	}
	if (*fRot < -D3DX_PI)
	{
		*fRot += 6.28f;
	}
}

//=========================================
// ���x�̐���
//=========================================
void LimitSpeed(D3DXVECTOR3 *pVec, float fSpeedMax)
{
	if (pVec == nullptr)
	{
		return;
	}

	// ���x�̎擾
	float fSpeed = D3DXVec3Length(pVec);

	if (fSpeed > fSpeedMax)
	{// ���x�̐���
		D3DXVECTOR3 vecNew = *pVec;

		D3DXVec3Normalize(&vecNew, &vecNew);

		vecNew *= fSpeedMax;

		*pVec = vecNew;
	}
}

//========================================
// �I�t�Z�b�g�ݒ菈��
//========================================
void SetOffSet(D3DXMATRIX *pMtxWorldOffset, D3DXMATRIX mtxWorldOwner, D3DXVECTOR3 posOffset, D3DXVECTOR3 rot)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pMtxWorldOffset);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, posOffset.x, posOffset.y, posOffset.z);
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxTrans);

	//�}�g���b�N�X���������킹��
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxWorldOwner);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, pMtxWorldOffset);
}

//========================================
// �����␳����
//========================================
void FactingRot(float *pfRot, float fRotDest, float rotateFact)
{
	// �����̊p�x�̕␳
	LimitRot(pfRot);
	LimitRot(&fRotDest);

	//�����p�x���擾
	float fRotDiff = fRotDest - *pfRot;

	//�p�x�̏C��
	LimitRot(&fRotDiff);

	//�p�x�␳
	*pfRot += fRotDiff * rotateFact;

	LimitRot(pfRot);
}

//========================================
// �����̔�r
//========================================
D3DXVECTOR3 VecToRot(D3DXVECTOR3 vec)
{
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };

	rot.y = atan2f(vec.x, vec.z);

	float fLength = sqrtf(vec.x * vec.x + vec.z * vec.z);

	rot.x = atan2f(fLength, -vec.y);

	return rot;
}

//========================================
// �����̔�r
//========================================
bool DistCmp(D3DXVECTOR3 posOwn, D3DXVECTOR3 posTarget, float fLengthMax, float *fDiff)
{
	D3DXVECTOR3 vecDiff = posTarget - posOwn;
	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength < fLengthMax)
	{
		if (fDiff != nullptr)
		{
			*fDiff = fLength;
		}

		return true;
	}
	else
	{
		return false;
	}
}

//========================================
// �O�ς̌v�Z
//========================================
float CrossProduct(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	return pos1.z * pos2.x - pos1.x * pos2.z;
}

//========================================
// �O�ς̓����蔻��v�Z
//========================================
bool IsCross(D3DXVECTOR3 posTarget, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest, float *pRate, D3DXVECTOR3 move)
{
	bool bHit = false;

	D3DXVECTOR3 vecLine = vecDest - vecSorce;
	D3DXVECTOR3 vecToPos = posTarget - vecSorce;
	float fArea = CrossProduct(vecLine, vecToPos);

	if (fArea > 0)
	{
		if (pRate != nullptr)
		{
			D3DXVECTOR3 vecToPos = posTarget - vecSorce;

			// �������Z�o
			float fAreaMax = (vecDest.z * move.x) - (vecDest.x * move.z);
			float fArea = (vecToPos.z * move.x) - (vecToPos.x * move.z);

			*pRate = fArea / fAreaMax;
		}

		bHit = true;
	}

	return bHit;
}

//========================================
// �O�p�`�̒��ɂ��邩�̔���
//========================================
bool IsInTriangle(D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3, D3DXVECTOR3 posTarget)
{
	int nHit = 0;

	if(IsCross(posTarget, vtx1, vtx2, nullptr) == false)
		nHit++;
	if (IsCross(posTarget, vtx2, vtx3, nullptr) == false)
		nHit++;
	if (IsCross(posTarget, vtx3, vtx1, nullptr) == false)
		nHit++;

	if (nHit == 3)
	{
		return true;
	}

	return false;
}

//========================================
// ��`�̒��ɂ��邩�ǂ����̌v�Z
//========================================
bool CubeCrossProduct(D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3, D3DXVECTOR3 vtx4, D3DXVECTOR3 pos)
{
	bool bHit = false;
	int nHit = 0;

	D3DXVECTOR3 aVec[4] =
	{// �z��Ɋi�[
		vtx1,
		vtx2,
		vtx3,
		vtx4,
	};

	// �S�ӂ̂Ȃ��ɂ��邩�̃`�F�b�N
	for (int i = 0; i < 4; i++)
	{
		int nNext = (i + 1) % 4;

		// �����̌������ɂ��邩�̔���
		bool bCross = IsCross(pos, aVec[i], aVec[nNext], nullptr);

		if (bCross)
		{
			nHit++;
		}
	}

	if (nHit >= 4)
	{
		bHit = true;
	}

	return bHit;
}

//========================================
// ��ʓ�����
//========================================
bool IsInScreen(const D3DXVECTOR3 pos, D3DXMATRIX mtx, D3DXVECTOR3 *pPos)
{
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer == nullptr)
	{
		return false;
	}

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DVIEWPORT9 viewport;
	pDevice->GetViewport(&viewport);

	D3DXMATRIX projectionMatrix;
	pDevice->GetTransform(D3DTS_PROJECTION, &projectionMatrix);

	D3DXMATRIX viewMatrix;
	pDevice->GetTransform(D3DTS_VIEW, &viewMatrix);

	D3DXVECTOR3 screenPosition;
	D3DXVec3Project(&screenPosition, &pos, &viewport, &projectionMatrix, &viewMatrix, D3DXMatrixIdentity(&mtx));

	if (pPos != nullptr)
	{
		*pPos = screenPosition;
	}

	if (screenPosition.x >= viewport.X && 
		screenPosition.x <= viewport.X + viewport.Width &&
		screenPosition.y >= viewport.Y && 
		screenPosition.y <= viewport.Y + viewport.Height &&
		screenPosition.z >= 0.0f && screenPosition.z <= 1.0f)
	{
		return true;
	}

	return false;
}

//=====================================================
// �΍������̏���
//=====================================================
D3DXVECTOR3 LinePridiction(D3DXVECTOR3 pos, float fSpeedBullet, D3DXVECTOR3 posTarget, D3DXVECTOR3 moveTarget)
{
	// �ϐ��錾
	D3DXVECTOR3 vecDiff;
	float fSpeedTarget;
	float fDataA, fDataB, fDataC, fDataD;
	int nFrame1, nFrame2;

	// �ڕW�̑��x���v�Z
	fSpeedTarget = D3DXVec3Length(&moveTarget);

	// �ڕW�Ƃ̈ʒu�̍������擾
	vecDiff = posTarget - pos;

	fDataA = (moveTarget.x * moveTarget.x + moveTarget.y * moveTarget.y + moveTarget.z * moveTarget.z) - fSpeedBullet * fSpeedBullet;

	fDataB = 2 * (posTarget.x * moveTarget.x + posTarget.y * moveTarget.y + posTarget.z * moveTarget.z);

	fDataC = (posTarget.x * posTarget.x + posTarget.y * posTarget.y + posTarget.z * posTarget.z);

	if (fDataA == 0)
	{// 0����h�~
		if (fDataB == 0)
		{
			return posTarget;
		}
		else
		{
			return posTarget + moveTarget * (-fDataC / fDataB);
		}
	}

	//�񎟕������̉��̌����̔��ʎ��ŕ���
	fDataD = fDataB * fDataB - 4 * fDataA * fDataC;

	if (fDataD > 0)
	{
		float fDataE = (float)sqrt(fDataD);
		nFrame1 = (int)((-fDataB - fDataE) / (2 * fDataA));
		nFrame2 = (int)((-fDataB + fDataE) / (2 * fDataA));
		//����2�Ȃ̂Ő��̐��̍ŏ��l���g��
		nFrame1 = (int)PlusMin((float)nFrame1, (float)nFrame2);
	}
	else
	{
		//������
		//������Ȃ��̂ō��̈ʒu��_��
		nFrame1 = 0;
	}

	//�\�z�ʒu��Ԃ�
	return posTarget + moveTarget * (float)nFrame1;
}

//=====================================================
// �v���X�̍ŏ��l��Ԃ�����
//=====================================================
float PlusMin(float fData1, float fData2)
{
	if (fData1 < 0 && fData2 < 0)
	{// �ǂ�������̒l�Ȃ�O��Ԃ�
		return 0;
	}
	else if (fData1 < 0)
	{
		return fData2;
	}
	else if (fData2 < 0)
	{
		return fData1;
	}

	return fData1 < fData2 ? fData1 : fData2;
}

//========================================
// �͈͓��̃����_�����l��Ԃ�����
//========================================
int RandRange(int nMax, int nMin)
{
	int nRange = nMax - nMin;
	int nRand = rand() % nRange + nMin;

	return nRand;
}
}	// namespace universal