//*****************************************************
//
// ブロック管理[blockManager.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "BlockManager.h"
#include <stdio.h>

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const char* FILE_PATH = "data\\TEXT\\map.txt";	// マップ情報
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CBlockManager *CBlockManager::m_pBlockManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CBlockManager::CBlockManager()
{
	m_pInfoBlock = nullptr;
	m_nNumInfoBlock = 0;
}

//=====================================================
// デストラクタ
//=====================================================
CBlockManager::~CBlockManager()
{

}

//=====================================================
// 生成処理
//=====================================================
CBlockManager *CBlockManager::Create(void)
{
	if (m_pBlockManager == nullptr)
	{// インスタンス生成
		m_pBlockManager = new CBlockManager;

		// 初期化処理
		m_pBlockManager->Init();
	}

	return m_pBlockManager;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CBlockManager::Init(void)
{
	Load();

	return S_OK;
}

//=====================================================
// 読み込み処理
//=====================================================
void CBlockManager::Load(void)
{
	//変数宣言
	char cTemp[256];
	int nCntBlock= 0;

	//ファイルから読み込む
	FILE *pFile = fopen(FILE_PATH, "r");

	if (pFile != nullptr)
	{//ファイルが開けた場合
		while (true)
		{
			//文字読み込み
			(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "NUM_BLOCK") == 0)
			{
				(void)fscanf(pFile, "%s", &cTemp[0]);

				(void)fscanf(pFile, "%d", &m_nNumInfoBlock);

				if (m_pInfoBlock == nullptr)
				{// ブロック情報の確保
					m_pInfoBlock = new SInfoBlock[m_nNumInfoBlock];

					ZeroMemory(m_pInfoBlock, sizeof(SInfoBlock) * m_nNumInfoBlock);
				}
			}

			if (strcmp(cTemp, "INFOBLOCK") == 0)
			{
				while (true)
				{
					//文字読み込み
					(void)fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "Tag") == 0)
					{
						(void)fscanf(pFile, "%s", &cTemp[0]);

						(void)fscanf(pFile, "%s", m_pInfoBlock[nCntBlock].pTag);
					}

					if (strcmp(cTemp, "END_INFOBLOCK") == 0)
					{
						nCntBlock++;

						break;
					}
				}
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
}

//=====================================================
// 終了処理
//=====================================================
void CBlockManager::Uninit(void)
{
	m_pBlockManager = nullptr;

	if (m_pInfoBlock != nullptr)
	{
		delete[] m_pInfoBlock;
		m_pInfoBlock = nullptr;
	}

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CBlockManager::Update(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CBlockManager::Draw(void)
{
#ifdef _DEBUG

#endif
}