//*****************************************************
//
// 敵マネージャー[enemyManager.h]
// Author:��山桃也
//
//*****************************************************

#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"
#include "enemy.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CUI;

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyManager : public CObject
{
public:
	CEnemyManager();	// コンストラクタ
	~CEnemyManager();	// デストラクタ

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

	CEnemy *m_pEnemyLockon;	// ロックオンしてる敵
	bool m_bLockTarget;	// ターゲットをロックしているかどうか
	float m_fTimer;	// スポーンタイマー
	CUI *m_pCursor;	// ロックオンカーソル
	CEnemy *m_pHead;	// 先頭のアドレス
	CEnemy *m_pTail;	// 最後尾のアドレス

	static CEnemyManager *m_pEnemyManager;	// 自身のポインタ
};

#endif
