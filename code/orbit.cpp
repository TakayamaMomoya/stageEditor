//******************************************
//
// �O�Ղ̏���
// Author : ���R����
//
//******************************************

//******************************************
// �C���N���[�h
//******************************************
#include "orbit.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//******************************************
// �}�N����`
//******************************************
#define DELETE_LENGTH	(4.0f)	// �폜���钷��

//==========================================
// �R���X�g���N�^
//==========================================
COrbit::COrbit(int nPriority) : CObject(nPriority)
{
	ZeroMemory(&m_aColPoint[0], sizeof(m_aColPoint));
	ZeroMemory(&m_aMtxOffset[0], sizeof(m_aMtxOffset));
	ZeroMemory(&m_aPosPoint[0], sizeof(m_aPosPoint));
	ZeroMemory(&m_posOffset[0],sizeof(m_posOffset));
	m_col = { 0.0f,0.0f,0.0f,0.0f };
	m_nIdxTexture = 0;
	m_nNumEdge = 0;
	m_nID = -1;
	m_pVtxBuff = nullptr;
	m_bEnd = false;
}

//==========================================
// �f�X�g���N�^
//==========================================
COrbit::~COrbit()
{

}

//==========================================
// ����������
//==========================================
HRESULT COrbit::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �e�N�X�`���Ǎ�
	m_nIdxTexture = CTexture::GetInstance()->Regist("data\\TEXTURE\\EFFECT\\orbit001.png");

	if (m_pVtxBuff == nullptr)
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer
		(
			sizeof(VERTEX_3D) * MAX_EDGE * NUM_OFFSET,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			nullptr
		);
	}

	VERTEX_3D *pVtx;		//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0;nCntVtx < MAX_EDGE * NUM_OFFSET;nCntVtx++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f * (nCntVtx % NUM_OFFSET));

		pVtx += 1;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==========================================
// �I������
//==========================================
void COrbit::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{//���_���j��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// ���g�̔j��
	Release();
}

//==========================================
// �X�V����
//==========================================
void COrbit::Update(void)
{
	if (m_bEnd)
	{
		//�|���S���X�V����
		UpdatePolygon();
	}
}

//==========================================
// �|���S���X�V����
//==========================================
void COrbit::UpdatePolygon(void)
{
	//�ϐ��錾
	int nCntOffset;
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DXVECTOR3 posTemp[NUM_OFFSET];

	//�ۑ��������W�����炷==========
	for (int nCntVtx = 1; nCntVtx < m_nNumEdge; nCntVtx++)
	{
		for (nCntOffset = 0; nCntOffset < NUM_OFFSET; nCntOffset++)
		{
			//��O�̍��W�ɂ����
			m_aPosPoint[nCntVtx - 1][nCntOffset] = m_aPosPoint[nCntVtx][nCntOffset];
		}
	}

	for (nCntOffset = 0; nCntOffset < NUM_OFFSET; nCntOffset++)
	{
		//���݂̃t���[���̃I�t�Z�b�g�ʒu��ۑ�
		m_aPosPoint[m_nNumEdge - 1][nCntOffset] =
		{
			m_aMtxOffset[nCntOffset]._41,
			m_aMtxOffset[nCntOffset]._42,
			m_aMtxOffset[nCntOffset]._43
		};
	}
	//�ۑ��������W�����炷==========

	VERTEX_3D *pVtx;		//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_nNumEdge; nCntVtx++)
	{//�ӂ��Ƃ̒��_���W�ݒ�

		for (nCntOffset = 0; nCntOffset < NUM_OFFSET; nCntOffset++)
		{//�I�t�Z�b�g�̐����ݒ�

			 //���_���W�̐ݒ�
			pVtx[nCntOffset].pos = m_aPosPoint[nCntVtx][nCntOffset];

			//���_�J���[�̐ݒ�
			pVtx[nCntOffset].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, (float)nCntVtx / m_nNumEdge);
		}

		//�|�C���^��i�߂�
		pVtx += NUM_OFFSET;
	}

	if (m_bEnd)
	{// �؂藣������̎����폜
		D3DXVECTOR3 vecDiff;

		vecDiff = pVtx[0].pos - pVtx[m_nNumEdge * NUM_OFFSET - 1].pos;

		float fLength = D3DXVec3Length(&vecDiff);

		if (fLength < DELETE_LENGTH)
		{
			Uninit();
		}
	}
}

//==========================================
// �`�揈��
//==========================================
void COrbit::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;						// �v�Z�p�}�g���b�N�X
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	// ���C�e�B���O������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �J�����O�𖳌���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���擾
	pTexture = CTexture::GetInstance()->GetAddress(m_nIdxTexture);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
		0,		//�`�悷��ŏ��̃C���f�b�N�X
		m_nNumEdge + (m_nNumEdge - 2)
	);

	// �J�����O��L����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// ���C�e�B���O�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
// ��������
//==========================================
COrbit *COrbit::Create(D3DXMATRIX mtxWorld, D3DXVECTOR3 m_posOffset1, D3DXVECTOR3 m_posOffset2, D3DXCOLOR col,int nNumEdge)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// �ϐ��錾
	int nCounterOrbit = -1;
	COrbit *pOrbit = nullptr;

	if (pOrbit == nullptr)
	{
		pOrbit = new COrbit;

		if (pOrbit != nullptr)
		{
			// ������
			pOrbit->Init();

			// �F�̑��
			pOrbit->m_col = col;

			// �I�t�Z�b�g�̑��
			pOrbit->m_posOffset[0] = m_posOffset1;
			pOrbit->m_posOffset[1] = m_posOffset2;

			// �ӂ̐��̑��
			pOrbit->m_nNumEdge = nNumEdge;

			pOrbit->m_aMtxOffset[0]._41 = m_posOffset1.x + mtxWorld._41;
			pOrbit->m_aMtxOffset[0]._42 = m_posOffset1.y + mtxWorld._42;
			pOrbit->m_aMtxOffset[0]._43 = m_posOffset1.z + mtxWorld._43;
			pOrbit->m_aMtxOffset[1]._41 = m_posOffset2.x + mtxWorld._41;
			pOrbit->m_aMtxOffset[1]._42 = m_posOffset2.y + mtxWorld._42;
			pOrbit->m_aMtxOffset[1]._43 = m_posOffset2.z + mtxWorld._43;

			for (int nCntVtx = 0; nCntVtx < nNumEdge; nCntVtx++)
			{
				pOrbit->m_aPosPoint[nCntVtx][0].x = m_posOffset1.x + mtxWorld._41;
				pOrbit->m_aPosPoint[nCntVtx][0].y = m_posOffset1.y + mtxWorld._42;
				pOrbit->m_aPosPoint[nCntVtx][0].z = m_posOffset1.z + mtxWorld._43;
				pOrbit->m_aPosPoint[nCntVtx][1].x = m_posOffset2.x + mtxWorld._41;
				pOrbit->m_aPosPoint[nCntVtx][1].y = m_posOffset2.y + mtxWorld._42;
				pOrbit->m_aPosPoint[nCntVtx][1].z = m_posOffset2.z + mtxWorld._43;
			}

			pOrbit->UpdatePolygon();
		}
	}

	return pOrbit;
}

//==========================================
// �ʒu�ݒ菈��
//==========================================
void COrbit::SetPositionOffset(D3DXMATRIX mtxWorld,int nIdxOrbit)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntOffset = 0; nCntOffset < NUM_OFFSET; nCntOffset++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_aMtxOffset[nCntOffset]);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_posOffset[nCntOffset].x, m_posOffset[nCntOffset].y, m_posOffset[nCntOffset].z);
		D3DXMatrixMultiply(&m_aMtxOffset[nCntOffset], &m_aMtxOffset[nCntOffset], &mtxTrans);

		//�}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&m_aMtxOffset[nCntOffset], &m_aMtxOffset[nCntOffset], &mtxWorld);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_aMtxOffset[nCntOffset]);
	}

	//�|���S���X�V����
	UpdatePolygon();
}