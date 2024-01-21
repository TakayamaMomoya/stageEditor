//*****************************************************
//
// �ʏ�G�̏���[enemyNormal.h]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMYNORMAL_H_
#define _ENEMYNORMAL_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "enemy.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyNormal : public CEnemy
{
public:
	CEnemyNormal();	// �R���X�g���N�^
	~CEnemyNormal();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChaseTarget(void);

private:
	enum MOTION
	{
		MOTION_NEUTRAL = 0,	// �ҋ@���[�V����
		MOTION_WALK,	// �������[�V����
		MOTION_ATTACK,	// �U�����[�V����
		MOTION_DEATH,	// ���S���[�V����
		MOTION_MAX
	};
};

#endif
