//*****************************************************
//
// �RD�|���S���̏���[object3D.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "debugproc.h"
#include "camera.h"
#include "lambert.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_width = 0.0f;
	m_heigth = 0.0f;
	m_pVtxBuff = nullptr;
	m_nIdxTexture = -1;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CObject3D::~CObject3D()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CObject3D::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	if (m_pVtxBuff == nullptr)
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			nullptr);
	}

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_width, 0.0f, m_heigth);
	pVtx[1].pos = D3DXVECTOR3(m_width, 0.0f, m_heigth);
	pVtx[2].pos = D3DXVECTOR3(-m_width, 0.0f, -m_heigth);
	pVtx[3].pos = D3DXVECTOR3(m_width, 0.0f, -m_heigth);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f, 1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CObject3D::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{//���_�o�b�t�@�|�C���^�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CObject3D::Update(void)
{

}

//=====================================================
// ���_�ݒ�
//=====================================================
void CObject3D::SetVtx(void)
{
	switch (m_mode)
	{
	case CObject3D::MODE_NORMAL:

		SetVtxNormal();

		break;
	case CObject3D::MODE_BILLBOARD:

		SetVtxNormal();

		break;
	case CObject3D::MODE_STRETCHBILLBOARD:

		SetVtxStretchBillboard();

		break;
	default:
		break;
	}
}

//=====================================================
// �ʏ풸�_�ݒ�
//=====================================================
void CObject3D::SetVtxNormal(void)
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_mode == MODE_BILLBOARD)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_width, m_heigth, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_width, m_heigth, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_width, -m_heigth, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_width, -m_heigth, 0.0f);
	}
	else
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_width, 0.0f, m_heigth);
		pVtx[1].pos = D3DXVECTOR3(m_width, 0.0f, m_heigth);
		pVtx[2].pos = D3DXVECTOR3(-m_width, 0.0f, -m_heigth);
		pVtx[3].pos = D3DXVECTOR3(m_width, 0.0f, -m_heigth);
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=====================================================
// �X�g���b�`�r���{�[�h���_�ݒ�
//=====================================================
void CObject3D::SetVtxStretchBillboard(void)
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 pos = m_pos;
	D3DXVECTOR3 vecFront;
	D3DXVECTOR3 vecRear;

	vecFront =
	{// �O���x�N�g��
		sinf(m_rot.x + D3DX_PI * 0.5f) * sinf(m_rot.y) * m_heigth,
		cosf(m_rot.x + D3DX_PI * 0.5f) * m_heigth,
		sinf(m_rot.x + D3DX_PI * 0.5f) * cosf(m_rot.y) * m_heigth
	};

	// ����x�N�g��
	vecRear = -vecFront;

	vecFront += pos;
	vecRear += pos;

	// �J��������̃x�N�g���擾
	D3DXVECTOR3 vecEye = pInfoCamera->posV - vecFront;
	D3DXVECTOR3 nor;
	D3DXVECTOR3 vecPolygon = vecFront - vecRear;

	// �@���̎Z�o
	D3DXVec3Cross(&nor, &vecEye, &vecPolygon);

	// �@�����K��
	D3DXVec3Normalize(&nor, &nor);

	//���_���W�̐ݒ�
	pVtx[1].pos = vecFront + nor * m_width;
	pVtx[3].pos = vecFront - nor * m_width;
	pVtx[0].pos = vecRear + nor * m_width;
	pVtx[2].pos = vecRear - nor * m_width;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=====================================================
// �`�揈��
//=====================================================
void CObject3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_mode == MODE_BILLBOARD)
	{
		SetMtxBillboard();
	}
	else
	{
		SetMtx();
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���ݒ�
	LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(m_nIdxTexture);
	pDevice->SetTexture(0, pTexture);

	if (m_mode == MODE_STRETCHBILLBOARD)
	{
		// �J�����O�𖳌���
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	CLambert *pLambert = CLambert::GetInstance();

	if (pLambert != nullptr)
	{
		pLambert->Begin();
		pLambert->SetMatrix(&m_mtxWorld, &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
		pLambert->BeginPass();
	}

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	if (pLambert != nullptr)
	{
		pLambert->End();
		pLambert->EndPass();
	}

	if (m_mode == MODE_STRETCHBILLBOARD)
	{
		// �J�����O��L����
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
}

//=====================================================
// �}�g���b�N�X�̐ݒ�
//=====================================================
void CObject3D::SetMtx(void)
{
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXVECTOR3 pos = m_pos;
	D3DXVECTOR3 rot = m_rot;

	if (m_mode == MODE_STRETCHBILLBOARD)
	{
		pos = { 0.0f,0.0f,0.0f };
		rot = { 0.0f,0.0f,0.0f };
	}

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//=====================================================
// �r���{�[�h�ł̃}�g���b�N�X�̐ݒ�
//=====================================================
void CObject3D::SetMtxBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();
	D3DXMATRIX mtxView, mtxTrans;

	//�r���[�}�g���b�N�X�擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����Ɍ�����
	D3DXMatrixInverse(&m_mtxWorld, nullptr, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//=====================================================
// ��������
//=====================================================
CObject3D *CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObject3D *pObject3D = nullptr;

	if (pObject3D == nullptr)
	{
		// �C���X�^���X����
		pObject3D = new CObject3D;

		// ����������
		pObject3D->Init();

		// �T�C�Y�ݒ�
		pObject3D->SetSize(500.0f, 500.0f);
	}

	return pObject3D;
}

//=====================================================
// ���[�h�̐ݒ�
//=====================================================
void CObject3D::SetMode(MODE mode)
{
	if (mode < MODE_MAX &&
		mode >= 0)
	{
		m_mode = mode;
	}
}

//=====================================================
// �T�C�Y�ݒ菈��
//=====================================================
void CObject3D::SetSize(float width, float height)
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	m_width = width;
	m_heigth = height;

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_mode == MODE_BILLBOARD)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_width, m_heigth, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_width, m_heigth, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_width, -m_heigth, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_width, -m_heigth, 0.0f);
	}
	else
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_width, 0.0f, m_heigth);
		pVtx[1].pos = D3DXVECTOR3(m_width, 0.0f, m_heigth);
		pVtx[2].pos = D3DXVECTOR3(-m_width, 0.0f, -m_heigth);
		pVtx[3].pos = D3DXVECTOR3(m_width, 0.0f, -m_heigth);
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=====================================================
// �F�ݒ菈��
//=====================================================
void CObject3D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=====================================================
// �e�N�X�`�����W�ݒ�
//=====================================================
void CObject3D::SetTex(D3DXVECTOR2 rd, D3DXVECTOR2 lu)
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(lu.x, lu.y);
	pVtx[1].tex = D3DXVECTOR2(rd.x, lu.y);
	pVtx[2].tex = D3DXVECTOR2(lu.x, rd.y);
	pVtx[3].tex = D3DXVECTOR2(rd.x, rd.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}