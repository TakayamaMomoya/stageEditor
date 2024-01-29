//*****************************************************
//
// レンダラーの処理[renderer.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CRenderer
{
public:
	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ

	static CRenderer *Create(HWND hWnd, BOOL bWindow);
	HRESULT Init(HWND hWnd, BOOL bWindow);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void DrawFPS(void);	//FPS表示処理
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// デバイスの取得
	IDirect3DVertexDeclaration9 *GetDecVtxShader(void) { return m_pDecVtx; }
	IDirect3DPixelShader9 *GetHandlerPxShader(void) { return m_pHandlerPxShader; }
	IDirect3DVertexShader9 *GetHandlerVtxShader(void) { return m_pHandlerVtxShader; }
	bool IsFog(void) { return m_fogInfo.bEnable; }
	void EnableFog(bool bFog) { m_fogInfo.bEnable = bFog; }
	static CRenderer *GetInstance(void) { return m_pRenderer; }

private:
	struct SInfoFog
	{// フォグ情報
		float fStart;	// 開始距離
		float fEnd;	// 終了距離
		bool bEnable;	// 有効かどうか
		D3DXCOLOR col;	// 色
	};

	LPDIRECT3D9 m_pD3D;	// オブジェクトの生成
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// デバイス
	IDirect3DPixelShader9 *m_pHandlerPxShader;	// ピクセルシェーダーハンドラー
	IDirect3DVertexShader9 *m_pHandlerVtxShader;	// 頂点シェーダーハンドラー
	IDirect3DVertexDeclaration9 *m_pDecVtx;	// 頂点宣言
	SInfoFog m_fogInfo;	// フォグの情報

	static CRenderer *m_pRenderer;	// 自身のポインタ
};

#endif