//*****************************************************
//
// ブロック管理[blockManager.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "block.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CModel;

//*****************************************************
// クラスの定義
//*****************************************************
class CBlockManager : public CObject
{
public:
	struct SInfoBlock
	{// ブロックの情報
		char aTag[256];	// タグ
		int nIdxModel;	// モデル番号
		bool bSnag;	// 障害物になるかどうか
	};

	CBlockManager();	// コンストラクタ
	~CBlockManager();	// デストラクタ

	static CBlockManager *Create(void);
	static CBlockManager *GetInstance(void) { return m_pBlockManager; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetNumBlock(void) { return m_nNumInfoBlock; }
	SInfoBlock *GetInfoBlock(void) { return m_pInfoBlock; }

private:
	void Load(void);

	SInfoBlock *m_pInfoBlock;	// ブロック情報のポインタ
	int m_nNumInfoBlock;	// ブロック情報の数
	static CBlockManager *m_pBlockManager;	// 自身のポインタ
};

#endif
