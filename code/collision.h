//*****************************************************
//
// �����蔻�菈��[collision.h]
// Author:���R����
//
//*****************************************************

#ifndef _COLLISION_H_
#define _COLLISION_H_

//*****************************************************
// �C���N���[�h
//****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//****************************************************
class CObject2D;
class CBillboard;

//*****************************************************
// �N���X��`
//*****************************************************
class CCollision : public CObject
{
public:
	typedef enum
	{// ���ʃ^�O
		TAG_NONE = 0,	// ���ł��Ȃ�
		TAG_PLAYER,	// �v���C���[
		TAG_ENEMY,	// �G
		TAG_PLAYERBULLET,	// �v���C���[�̒e
		TAG_ENEMYBULLET,	// �G�̒e
		TAG_BLOCK,	// �u���b�N
		TAG_ITEM,	// �A�C�e��
		TAG_GOAL,	// �S�[��
		TAG_ROCKET,	// ���P�b�g
		TAG_BOX,	// ��
		TAG_MAX
	}TAG;

	typedef enum
	{
		TYPE_NONE = 0, // ���ł��Ȃ�
		TYPE_SPHERE,	// ���̓����蔻��
		TYPE_CUBE,	// �����̂̓����蔻��
		TYPE_MAX
	}TYPE;

	CCollision();	// �R���X�g���N�^
	~CCollision();	// �f�X�g���N�^

	static CCollision *Create(TAG tag,TYPE type,CObject *obj);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static void DeleteAll(void);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetPosition(D3DXVECTOR3 pos);
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	CCollision **GetCollision(void) { return &m_apCollision[0]; }
	TAG GetTag(void) { return m_tag; }
	TYPE GetType(void) { return m_type; }
	void SetType(TYPE type) { m_type = type; }
	void SetTag(TAG tag) { m_tag = tag; }
	virtual float GetRadius(void) { return 0.0f; }
	virtual bool SphereCollision(TAG tag) { return false; }
	void SetOwner(CObject *pObj) { m_pObjectOwner = pObj; }
	void SetOther(CObject *pObj) { m_pObjectOther = pObj; }
	CObject *GetOther(void) { return m_pObjectOther; }
	CObject *GetOwner(void) { return m_pObjectOwner; }
	void ReleaseOther(void) { m_pObjectOther = nullptr; }
	virtual D3DXVECTOR3 GetVtxMax(void) { return D3DXVECTOR3(0.0f,0.0f,0.0f); }
	virtual D3DXVECTOR3 GetVtxMin(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	static bool IsCross(D3DXVECTOR3 posTarget, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest, float *fRate, D3DXVECTOR3 move = { 0.0f,0.0f,0.0f });
	static bool IsCrossTrigger(D3DXVECTOR3 posTarget, D3DXVECTOR3 posTargetOld,D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest);
	bool TriggerCube(TAG tag);
	bool ChckObstclBtwn(CObject *pObject,D3DXVECTOR3 vecDiff);
	static int GetNumAll(void) { return m_nNumAll; }

private:
	D3DXVECTOR3 m_pos;	// �ꏊ
	D3DXVECTOR3 m_posOld;	// �O��̏ꏊ
	TAG m_tag;	// ���ʗp�^�O
	TYPE m_type;
	static CCollision *m_apCollision[NUM_OBJECT];
	int m_nID;	// �ԍ�
	static int m_nNumAll;
	CObject *m_pObjectOwner;
	CObject *m_pObjectOther;
};

class CCollisionSphere : public CCollision
{// ���̓����蔻��
public:
	CCollisionSphere();	// �R���X�g���N�^
	~CCollisionSphere();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	bool OnEnter(TAG tag);
	float GetRadius(void) { return m_fRadius; }
	static CCollisionSphere *Create(TAG tag, TYPE type, CObject *obj);
	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	bool IsTriggerExit(TAG tag);
	bool IsTriggerEnter(TAG tag);
	void PushCollision(D3DXVECTOR3 *pPos,TAG tag);
	void DamageAll(TAG tag, float fDamage);

private:
	float m_fRadius;
	CBillboard *m_pBillboard;	// �r���{�[�h
};

class CCollisionCube : public CCollision
{// �����̂̓����蔻��
public:
	CCollisionCube();	// �R���X�g���N�^
	~CCollisionCube();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	bool CubeCollision(TAG tag, D3DXVECTOR3 *pMove,CObject **ppObjOther = nullptr);
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }
	static CCollisionCube *Create(TAG tag, CObject *obj);
	void SetVtx(D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);
	D3DXVECTOR3 CollisionVector(CObject *pObj);

private:
	D3DXVECTOR3 m_vtxMax;	// �ő咸�_
	D3DXVECTOR3 m_vtxMin;	// �ŏ����_
};


#endif