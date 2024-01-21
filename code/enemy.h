//*****************************************************
//
// �G�̏���[enemy.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;
class CCollisionCube;
class CBlock;
class CObject2D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemy : public CMotion
{
public:
	enum TYPE
	{// �G�̎��
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_NORMAL,	// �ʏ�G
		TYPE_BOSS,		// �{�X�G
		TYPE_MAX
	};

	enum STATE
	{// ���
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_THROWN,	// ������ꂽ���
		STATE_DAMAGE,	// �_���[�W���
		STATE_DEATH,	// ���S���
		STATE_MAX
	};

	enum MOVESTATE
	{// �ړ����
		MOVESTATE_NONE = 0,	// ���ł��Ȃ����
		MOVESTATE_INTRUSION,	// �N�����悤�Ƃ��Ă���
		MOVESTATE_CHASE,	// �ǐՏ��
		MOVESTATE_MAX
	};

	CEnemy();	// �R���X�g���N�^
	~CEnemy();	// �f�X�g���N�^

	static CEnemy *Create(D3DXVECTOR3 pos,TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetNumAll(void) { return m_nNumAll; }
	void SetLife(float fLife);
	float GetLife(void) { return m_info.fLife; }
	void Hit(float fDamage);
	void SetSpherePosition(D3DXVECTOR3 pos);
	STATE GetState(void) { return m_info.state; }
	void SetState(STATE state) { m_info.state = state; }
	CCollisionSphere *GetClsnSphere(void) { return m_info.pCollisionSphere; }
	CEnemy *GetNext(void) { return m_pNext; }
	int GetCntState(void) { return m_info.nTimerState; }
	void SetCntState(int nCnt) { m_info.nTimerState = nCnt; }
	float GetSpeed(void) { return m_info.fMoveSpeed; }
	void SetMoveSpeed(float fSpeed) { m_info.fMoveSpeed = fSpeed; }
	MOVESTATE GetMoveState(void) { return m_info.moveState; }
	void SetPosDest(D3DXVECTOR3 pos) { m_info.posDest = pos; }
	void CreateCollision(void);
	void DeleteCollision(void);
	void EnableLock(bool bLock);
	void SetPositionCursor(D3DXVECTOR3 pos);

protected:
	void ManageScore(void);
	virtual void ChaseTarget(void);
	virtual void Death(void);
	virtual void TransferChase(void);

private:
	struct SInfo
	{
		float fLife;	// �̗�
		float fMoveSpeed;	// �ړ����x
		int nTimerState;	// ��ԑJ�ڃJ�E���^�[
		CCollisionSphere *pCollisionSphere;	// ���̓����蔻��
		CCollisionCube *pCollisionCube;	// �����̂̓����蔻��
		STATE state;	// ���
		MOVESTATE moveState;	// �ړ����
		D3DXVECTOR3 posDest;	// �ڕW�ʒu
		CObject2D *pCursor;	// �ߑ��\�J�[�\��
	};
	void ManageState(void);
	void ManageMoveState(void);
	void ManageCollision(void);
	bool IsInArea(void);
	void CollisionThrown(void);

	static int m_nNumAll;	// ����
	SInfo m_info;	// ���

	CEnemy *m_pPrev;	// �O�̃A�h���X
	CEnemy *m_pNext;	// ���̃A�h���X
};

#endif
