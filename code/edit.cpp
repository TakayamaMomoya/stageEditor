//*****************************************************
//
// エディターの処理[edit.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "edit.h"
#include "objectX.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "manager.h"
#include "debugproc.h"
#include "block.h"
#include "enemy.h"
#include "enemyManager.h"
#include "blockManager.h"
#include <assert.h>

//*****************************************************
// マクロ定義
//*****************************************************
#define SPEED_MOVE	(1.0f)	// 移動速度
#define SPEED_ROTATION	(0.01f)	// 回転

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CEdit *CEdit::m_pEdit = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CEdit::CEdit()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_pObjectCursor = nullptr;
	m_nIdxObject = 0;
	m_type = CBlock::TYPE_WALL;
	m_mode = MODE_CREATE_BLOCK;
	ZeroMemory(&m_aPath[0], sizeof(m_aPath));
}

//=====================================================
// デストラクタ
//=====================================================
CEdit::~CEdit()
{

}

//=====================================================
// 生成処理
//=====================================================
CEdit *CEdit::Create(void)
{
	if (m_pEdit == nullptr)
	{// インスタンス生成
		m_pEdit = new CEdit;

		// 初期化処理
		m_pEdit->Init();
	}

	return m_pEdit;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEdit::Init(void)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager != nullptr)
	{
		CBlockManager::SInfoBlock *pInfoBlock = pBlockManager->GetInfoBlock();

		if (pInfoBlock == nullptr)
		{
			nullptr;
		}

		m_pObjectCursor = nullptr;

		m_pObjectCursor = CObjectX::Create();

		// タイプの初期設定
		m_type = CBlock::TYPE_WALL;

		// モデル番号の設定
		m_pObjectCursor->BindModel(pInfoBlock[0].nIdxModel);

		m_pObjectCursor->SetEmissiveCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEdit::Uninit(void)
{
	if (m_pObjectCursor != nullptr)
	{
		m_pObjectCursor->Uninit();
		m_pObjectCursor = nullptr;
	}

	m_pEdit = nullptr;

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CEdit::Update(void)
{
	// 情報取得
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };
	float fSpeed = SPEED_MOVE;

	// カーソルのループ
	LoopCursor();

	if (m_pObjectCursor != nullptr && pKeyboard != nullptr && pMouse != nullptr && pBlockManager != nullptr)
	{
		if (ImGui::TreeNode("POS"))
		{
			// ブロック移動
			ImGui::DragFloat("POS.X", &m_pos.x, SPEED_MOVE, -FLT_MAX, FLT_MAX);
			ImGui::DragFloat("POS.Y", &m_pos.y, SPEED_MOVE, -FLT_MAX, FLT_MAX);
			ImGui::DragFloat("POS.Z", &m_pos.z, SPEED_MOVE, -FLT_MAX, FLT_MAX);

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("ROT"))
		{
			// ブロック向き
			ImGui::DragFloat("ROT.X", &m_rot.x, 0.01f, -D3DX_PI, D3DX_PI);
			ImGui::DragFloat("ROT.Y", &m_rot.y, 0.01f, -D3DX_PI, D3DX_PI);
			ImGui::DragFloat("ROT.Z", &m_rot.z, 0.01f, -D3DX_PI, D3DX_PI);

			ImGui::TreePop();
		}

		int nNumBlock = pBlockManager->GetNumBlock();
		CBlockManager::SInfoBlock *pInfoBlock = pBlockManager->GetInfoBlock();

		if (ImGui::TreeNode("SelectBlock"))
		{
			for (int i = 0; i < nNumBlock; i++)
			{// ブロック選択
				if (ImGui::Button(&pInfoBlock[i].aTag[0], ImVec2(50.0f, 20.0f)))
				{
					m_nIdxObject = i;

					m_pObjectCursor->BindModel(pInfoBlock[i].nIdxModel);
				}
			}

			ImGui::TreePop();
		}

		if (ImGui::Button("Create", ImVec2(50.0f, 20.0f)))
		{// ブロック生成
			CreateBlock(m_pObjectCursor->GetPosition());
		}

		// 削除ブロック選択
		CBlock *pBlock = CheckDelete();

		if (ImGui::Button("Delete", ImVec2(60.0f, 20.0f)))
		{// 削除
			pBlock->Uninit();
		}

		ImGui::InputText("SavePath", &m_aPath[0], 256);

		if (ImGui::Button("Save", ImVec2(50.0f, 20.0f)))
		{// 保存
			CBlockManager *pBlockManager = CBlockManager::GetInstance();

			if (pBlockManager != nullptr)
			{
				pBlockManager->Save(&m_aPath[0]);
			}
		}

		if (ImGui::Button("DeleteAll", ImVec2(80.0f, 20.0f)))
		{// 全削除
			CBlockManager *pBlockManager = CBlockManager::GetInstance();

			if (pBlockManager != nullptr)
			{
				pBlockManager->DeleteAll();
			}
		}

		// 回転
		if (pKeyboard->GetTrigger(DIK_Z))
		{
			rot.y = 0.0f;

			m_pObjectCursor->SetRot(rot);
		}
		if (pKeyboard->GetTrigger(DIK_C))
		{
			rot.y = D3DX_PI * 0.5f;

			m_pObjectCursor->SetRot(rot);
		}

		if (m_pObjectCursor != nullptr)
		{// カーソルのトランスフォーム
			m_pObjectCursor->SetPosition(m_pos);
			m_pObjectCursor->SetRot(m_rot);
		}
	}
}

//=====================================================
// カーソルのループ
//=====================================================
void CEdit::LoopCursor(void)
{

}

//=====================================================
// ブロックの生成
//=====================================================
void CEdit::CreateBlock(D3DXVECTOR3 pos)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
	{
		return;
	}

	CBlockManager::SInfoBlock *pInfoBlock = pBlockManager->GetInfoBlock();

	CBlock *pBlock = CBlock::Create(pInfoBlock[m_nIdxObject].nIdxModel);

	if (pBlock != nullptr)
	{
		pBlock->SetPosition(pos);
		pBlock->SetRot(m_pObjectCursor->GetRot());
		pBlock->SetIdx(m_nIdxObject);

		if (pInfoBlock[m_nIdxObject].bSnag == false)
		{
			pBlock->DeleteCollision();
		}
	}
}

//=====================================================
// 削除ブロックのチェック
//=====================================================
CBlock *CEdit::CheckDelete(void)
{
	CBlockManager *pBlockManager = CBlockManager::GetInstance();

	if (pBlockManager == nullptr)
	{
		return nullptr;
	}

	CBlock *pBlock = pBlockManager->GetHead();

	while (pBlock != nullptr)
	{
		CBlock *pBlockNext = pBlock->GetNext();

		if (pBlock != nullptr)
		{
			pBlock->ResetColor();

			D3DXVECTOR3 posBlock = pBlock->GetPosition();
			D3DXVECTOR3 pos = m_pObjectCursor->GetPosition();
			D3DXVECTOR3 vtxMax = pBlock->GetVtxMax();
			D3DXVECTOR3 vtxMin = pBlock->GetVtxMin();

			if (pos.x >= posBlock.x + vtxMin.x &&
				pos.x <= posBlock.x + vtxMax.x &&
				pos.z >= posBlock.z + vtxMin.z &&
				pos.z <= posBlock.z + vtxMax.z &&
				pos.y >= posBlock.y + vtxMin.y &&
				pos.y <= posBlock.y + vtxMax.y)
			{// ブロック内にいるとき
				pBlock->SetEmissiveCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

				return pBlock;
			}
		}

		pBlock = pBlockNext;
	}

	return nullptr;
}