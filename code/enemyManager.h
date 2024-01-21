//*****************************************************
//
// �G�}�l�[�W���[[enemyManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"
#include "enemy.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyManager : public CObject
{
public:
	CEnemyManager();	// �R���X�g���N�^
	~CEnemyManager();	// �f�X�g���N�^

	CEnemy *CreateEnemy(D3DXVECTOR3 pos, CEnemy::TYPE type);
	static CEnemyManager *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CEnemy *Lockon(CEnemy *pEnemyExclusive = nullptr);
	void EnableLockTarget(bool bLock);
	bool IsLockTarget(void) { return m_bLockTarget; }
	void CheckDeathLockon(CEnemy *pEnemy);
	CEnemy *GetLockon(void) { return m_pEnemyLockon; }
	CEnemy *GetHead(void) { return m_pHead; }
	CEnemy *GetTail(void) { return m_pTail; }
	void SetHead(CEnemy *pEnemy) { m_pHead = pEnemy; }
	void SetTail(CEnemy *pEnemy) { m_pTail = pEnemy; }
	static CEnemyManager *GetInstance(void) { return m_pEnemyManager; }

private:
	void Load(void);

	CEnemy *m_pEnemyLockon;	// ���b�N�I�����Ă�G
	bool m_bLockTarget;	// �^�[�Q�b�g�����b�N���Ă��邩�ǂ���
	float m_fTimer;	// �X�|�[���^�C�}�[
	CUI *m_pCursor;	// ���b�N�I���J�[�\��
	CEnemy *m_pHead;	// �擪�̃A�h���X
	CEnemy *m_pTail;	// �Ō���̃A�h���X

	static CEnemyManager *m_pEnemyManager;	// ���g�̃|�C���^
};

#endif
