//*****************************************************
//
// �{�X�G�̏���[enemyBoss.h]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMYBOSS_H_
#define _ENEMYBOSS_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "enemy.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyBoss : public CEnemy
{
public:
	CEnemyBoss();	// �R���X�g���N�^
	~CEnemyBoss();	// �f�X�g���N�^

	static CEnemyBoss *Create(void);
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

	void Death(void);
	
	static CEnemyBoss *m_pEnemyBoss;	// ���g�̃|�C���^
};

#endif
