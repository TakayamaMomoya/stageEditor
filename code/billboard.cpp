//*****************************************************
//
// �RD�|���S���̏���[billboard.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "billboard.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_width = 0.0f;
	m_heigth = 0.0f;
	m_nIdxTexture = -1;
	m_pVtxBuff = nullptr;
	m_bZTest = false;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBillboard::~CBillboard()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CBillboard::Init(void)
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
	pVtx[0].pos = D3DXVECTOR3(-m_width, m_heigth, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_width, m_heigth, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_width, -m_heigth, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_width, -m_heigth, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);

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
void CBillboard::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{// ���_�o�b�t�@�|�C���^�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CBillboard::Update(void)
{
	m_posOld = m_pos;
}

//=====================================================
// ���_�ݒ�
//=====================================================
void CBillboard::SetVtx(void)
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_width, m_heigth, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_width, m_heigth, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_width, -m_heigth, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_width, -m_heigth, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=====================================================
// �e�N�X�`�����W�ݒ菈��
//=====================================================
void CBillboard::SetTex(D3DXVECTOR2 texLeftUp, D3DXVECTOR2 texRightDown)
{
	// ���_���̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W
	pVtx[0].tex = texLeftUp;
	pVtx[1].tex = D3DXVECTOR2(texRightDown.x, texLeftUp.y);
	pVtx[2].tex = D3DXVECTOR2(texLeftUp.x, texRightDown.y);
	pVtx[3].tex = texRightDown;

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=====================================================
// �`�揈��
//=====================================================
void CBillboard::Draw(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CRenderer::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();
	D3DXMATRIX mtxView, mtxTrans;

	//���C�e�B���O������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (m_bZTest)
	{
		//Z�e�X�g�̖�����
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	if (pRenderer->IsFog())
	{
		// �t�H�O�𖳌���
		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

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

	// ���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���ݒ�
	LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(m_nIdxTexture);
	pDevice->SetTexture(0, pTexture);

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���C�e�B���O�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	if (m_bZTest)
	{
		//Z�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	if (pRenderer->IsFog())
	{
		// �t�H�O��L����
		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	}
}

//=====================================================
// �}�g���b�N�X�݂̂̐ݒ�
//=====================================================
void CBillboard::SetMatrix(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();
	D3DXMATRIX mtxView, mtxTrans;

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

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

	// ���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//=====================================================
// ��������
//=====================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos,float width,float height)
{
	CBillboard *pBillboard = nullptr;

	if (pBillboard == nullptr)
	{
		// �C���X�^���X����
		pBillboard = new CBillboard;

		// �T�C�Y�ݒ�
		pBillboard->SetSize(width, height);

		pBillboard->SetPosition(pos);

		// ����������
		pBillboard->Init();
	}

	return pBillboard;
}

//=====================================================
// �ʒu�ݒ菈��
//=====================================================
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;

	D3DXMATRIX mtxTrans;
}

//=====================================================
// �T�C�Y�ݒ菈��
//=====================================================
void CBillboard::SetSize(float width, float height)
{
	m_width = width;
	m_heigth = height;

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_width, m_heigth, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_width, m_heigth, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_width, -m_heigth, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_width, -m_heigth, 0.0f);

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//=====================================================
// �F�ݒ菈��
//=====================================================
void CBillboard::SetColor(D3DXCOLOR col)
{
	m_col = col;

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}
}