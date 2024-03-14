//*****************************************************
//
// ランバートの処理[lambert.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _LAMBERT_H_
#define _LAMBERT_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CLambert
{
public:
	CLambert();
	~CLambert();
	static CLambert *Create(void);
	static CLambert *GetInstance(void) { return m_pLambert; }
	HRESULT Init(void);
	void Uninit(void);
	void Invalidate();
	void Restore();
	void Begin();
	void BeginPass();
	void SetAmbient(float Ambient);
	void SetAmbient(D3DXVECTOR4* pAmbient);
	void SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir);
	void CommitChanges();
	void EndPass();
	void End();
	bool IsOK();
	LPD3DXEFFECT GetEffect() { return m_pEffect; };

private:
	LPD3DXEFFECT m_pEffect;	// エフェクトのポインタ
	D3DXHANDLE m_pTechnique;	// テクニックのハンドラ
	D3DXHANDLE m_pWVP;	// マトリックスのハンドラ
	D3DXHANDLE m_pLightDir;	// ディレクショナルライトのハンドラ
	D3DXHANDLE m_pAmbient;	// 環境光のハンドラ
	D3DXMATRIX m_mtxView;	// ビューマトリックス
	D3DXMATRIX m_mtxProj;	// プロジェクションマトリックス
	D3DXVECTOR4 m_ambient;	// アンビエントの値
	static CLambert *m_pLambert;	// 自身のポインタ
};

#endif