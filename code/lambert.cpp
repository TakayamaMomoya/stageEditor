//*****************************************************
//
// ランバートの処理[Lambert.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "Lambert.h"
#include "renderer.h"

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CLambert *CLambert::m_pLambert = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CLambert::CLambert()
{
	m_pEffect = nullptr;
	m_pTechnique = nullptr;
	m_pAmbient = nullptr;
	m_pLightDir = nullptr;
	m_pWVP = nullptr;
	m_ambient = { 1.0f,1.0f,1.0f,1.0f };
}

//=====================================================
// デストラクタ
//=====================================================
CLambert::~CLambert()
{

}

//=====================================================
// 生成処理
//=====================================================
CLambert *CLambert::Create(void)
{
	if (m_pLambert == nullptr)
	{
		m_pLambert = new CLambert;

		if (m_pLambert != nullptr)
		{
			m_pLambert->Init();
		}
	}

	return m_pLambert;
}

//=====================================================
// 初期化
//=====================================================
HRESULT CLambert::Init(void)
{
	HRESULT hr;
	D3DCAPS9 caps;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	pDevice->GetDeviceCaps(&caps);
	DWORD vVs = caps.VertexShaderVersion;
	DWORD vPs = caps.PixelShaderVersion;

	// バージョンのチェック
	if (vVs < D3DVS_VERSION(1, 1) || vVs > D3DVS_VERSION(3, 0) ||
		vPs < D3DPS_VERSION(1, 1) || vPs > D3DPS_VERSION(3, 0))
	{
		assert(("シェーダーのバージョンが使用できないものです", false));

		return E_FAIL;
	}

	LPD3DXBUFFER pErr = nullptr;

	// fxファイルのロード
	hr = D3DXCreateEffectFromFile(pDevice, "data\\EFFECT\\Empty.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, &pErr);

	if (SUCCEEDED(hr))
	{
		//fxファイル内で宣言している変数のハンドルを取得する
		m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
		m_pWVP = m_pEffect->GetParameterByName(NULL, "m_WVP");
		m_pLightDir = m_pEffect->GetParameterByName(NULL, "m_LightDir");
		m_pAmbient = m_pEffect->GetParameterByName(NULL, "m_Ambient");
		SetAmbient(0.8f);

		m_pEffect->SetTechnique(m_pTechnique);
	}

	return S_OK;
}

//=====================================================
// 終了
//=====================================================
void CLambert::Uninit(void)
{
	if (m_pEffect != nullptr)
	{
		m_pEffect->Release();
		m_pEffect = nullptr;
	}
}

//=====================================================
// 開放
//=====================================================
void CLambert::Invalidate(void)
{
	if (m_pEffect != nullptr)
		m_pEffect->OnLostDevice();
}

//=====================================================
// レストア
//=====================================================
void CLambert::Restore(void)
{
	if (m_pEffect != nullptr)
		m_pEffect->OnResetDevice();
}

//=====================================================
// シェーダー処理の開始
//=====================================================
void CLambert::Begin(void)
{
	if (m_pEffect != nullptr)
	{
		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

		pDevice->GetTransform(D3DTS_VIEW, &m_mtxView);
		pDevice->GetTransform(D3DTS_PROJECTION, &m_mtxProj);

		m_pEffect->Begin(nullptr, 0);
	}
}

//=====================================================
// パス０の開始
//=====================================================
void CLambert::BeginPass(void)
{
	if (m_pEffect)
	{
		m_pEffect->BeginPass(0);
	}
}

//=====================================================
// 環境光の設定(float)
//=====================================================
void CLambert::SetAmbient(float fAmbient)
{
	m_ambient = { fAmbient ,fAmbient ,fAmbient ,1.0f };

	if (m_pEffect)
	{//シェーダーが使用できるとき
		D3DXVECTOR4 ambient;
		ambient = D3DXVECTOR4(fAmbient, fAmbient, fAmbient, 1.0f);
		m_pEffect->SetVector(m_pAmbient, &ambient);
	}
	else
	{//シェーダーが使用できないときは、固定機能パイプラインのマテリアルを設定する。(注意３)
		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

		D3DMATERIAL9 old_material;
		pDevice->GetMaterial(&old_material);
		old_material.Ambient.r = fAmbient;
		old_material.Ambient.g = fAmbient;
		old_material.Ambient.b = fAmbient;
		old_material.Ambient.a = 1.0f;
		pDevice->SetMaterial(&old_material);
	}
}

//=====================================================
// 環境光の設定(Vector4)
//=====================================================
void CLambert::SetAmbient(D3DXVECTOR4* pAmbient)
{
	m_ambient = { pAmbient->x ,pAmbient->y ,pAmbient->z ,1.0f };

	if (m_pEffect)
	{//シェーダーが使用できるとき
		D3DXVECTOR4 ambient;
		ambient = *pAmbient;
		m_pEffect->SetVector(m_pAmbient, &ambient);
	}
	else
	{//シェーダーが使用できないときは、固定機能パイプラインのマテリアルを設定する。(注意３)
		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

		D3DMATERIAL9 old_material;
		pDevice->GetMaterial(&old_material);
		old_material.Ambient.r = pAmbient->x;
		old_material.Ambient.g = pAmbient->y;
		old_material.Ambient.b = pAmbient->z;
		old_material.Ambient.a = 1.0f;
		pDevice->SetMaterial(&old_material);
	}
}

//=====================================================
// ワールドマトリックスの設定
//=====================================================
void CLambert::SetMatrix(D3DXMATRIX *pMtxWorld, D3DXVECTOR4 *pLightDir)
{
	if (pMtxWorld == nullptr || pLightDir == nullptr)
		return;

	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	if (m_pEffect != nullptr)
	{
		// ビューと射影マトリックスから、ワールドマトリックスを設定
		D3DXMATRIX mtxWorld;
		mtxWorld = *pMtxWorld * m_mtxView * m_mtxProj;

		m_pEffect->SetMatrix(m_pWVP, &mtxWorld);

		// 平行光源の方向ベクトルを設定する
		D3DXMATRIX mtxLight;
		D3DXVECTOR4 vecLight = *pLightDir;
		D3DXVECTOR4 vector;

		D3DXMatrixInverse(&mtxLight, nullptr, pMtxWorld);
		D3DXVec4Transform(&vector, &vecLight, &mtxLight);

		// 正規化する
		D3DXVec3Normalize((D3DXVECTOR3*)&vector, (D3DXVECTOR3*)&vector);
		m_pEffect->SetVector(m_pLightDir, &vector);
	}
	else
	{// シェーダーが使用できないときは固定パイプラインを使用する
		pDevice->SetTransform(D3DTS_WORLD, pMtxWorld);
	}
}

//=====================================================
// ステートの変更をデバイスに通知
//=====================================================
void CLambert::CommitChanges(void)
{
	if (m_pEffect)
		m_pEffect->CommitChanges();
}

//=====================================================
// パスの終了
//=====================================================
void CLambert::EndPass(void)
{
	if (m_pEffect)
		m_pEffect->EndPass();
}

//=====================================================
// シェーダー処理の終了
//=====================================================
void CLambert::End(void)
{
	if (m_pEffect)
		m_pEffect->End();
}

//=====================================================
// シェーダーが使用できるかどうか
//=====================================================
bool CLambert::IsOK(void)
{
	return m_pEffect != nullptr;
}