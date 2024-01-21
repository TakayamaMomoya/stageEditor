//*****************************************************
//
// ボス敵の処理[enemyBoss.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "enemyBoss.h"
#include "fade.h"

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CEnemyBoss *CEnemyBoss::m_pEnemyBoss = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CEnemyBoss::CEnemyBoss()
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyBoss::~CEnemyBoss()
{

}

//=====================================================
// 生成処理
//=====================================================
CEnemyBoss *CEnemyBoss::Create(void)
{
	if (m_pEnemyBoss == nullptr)
	{
		m_pEnemyBoss = new CEnemyBoss;

		if (m_pEnemyBoss != nullptr)
		{
			m_pEnemyBoss->Init();
		}
	}

	return m_pEnemyBoss;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyBoss::Init(void)
{
	// モーション読込
	Load("data\\MOTION\\motionArms00.txt");

	// 継承クラスの初期化
	CEnemy::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyBoss::Uninit(void)
{
	m_pEnemyBoss = nullptr;

	// 継承クラスの終了
	CEnemy::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyBoss::Update(void)
{
	// 継承クラスの更新
	CEnemy::Update();

	CEnemy::STATE state = GetState();

	if (state == CEnemy::STATE::STATE_DEATH)
	{// 死亡モーション
		int nMotion = GetMotion();

		if (nMotion != MOTION_DEATH)
		{
			SetMotion(MOTION_DEATH);
		}
	}
	else
	{

	}
}

//=====================================================
// 死亡時の処理
//=====================================================
void CEnemyBoss::Death(void)
{
	CFade *pFade = CFade::GetInstance();

	if (pFade != nullptr)
	{
		pFade->SetFade(CScene::MODE_RANKING);
	}

	CEnemy::Death();
}

//=====================================================
// 目標の追跡
//=====================================================
void CEnemyBoss::ChaseTarget(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CEnemyBoss::Draw(void)
{
	// 継承クラスの描画
	CEnemy::Draw();
}