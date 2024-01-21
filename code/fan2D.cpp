//*****************************************************
//
// 2D�~�̏���[fan2D.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "fan2D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "universal.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const float INITIAL_RADIUS = 50.0f;	// �����̔��a
	const char* TEX_PATH = "data\\TEXTURE\\UI\\gauge.png";	// �e�N�X�`���̃p�X
}

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CFan2D::CFan2D(int nPriority) : CObject(nPriority)
{
	// �ϐ��̃N���A
	m_pVtxBuff = nullptr;
	m_pos = { 0,0,0 };
	m_fRot = 0.0f;
	m_fRadius = 0.0f;
	m_nNumVtx = 0;
	m_fAngleMax = 1.0f;
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_nIdxTexture = -1;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CFan2D::~CFan2D()
{

}

//=====================================================
// ��������
//=====================================================
CFan2D *CFan2D::Create(int nPriority, int nNumVtx)
{
	CFan2D *pFan2D = nullptr;

	// �C���X�^���X����
	pFan2D = new CFan2D(nPriority);

	if (pFan2D != nullptr)
	{
		pFan2D->m_nNumVtx = nNumVtx;

		// ����������
		pFan2D->Init();
	}

	return pFan2D;
}

//=====================================================
// ������
//=====================================================
HRESULT CFan2D::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	if (pDevice != nullptr)
	{
		if (m_pVtxBuff == nullptr)
		{
			// ���_�o�b�t�@�̐���
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (m_nNumVtx + 2),
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&m_pVtxBuff,
				nullptr);
		}
	}

	// �e�N�X�`���ǂݍ���
	int nIdx = CTexture::GetInstance()->Regist(TEX_PATH);
	SetIdxTexture(nIdx);

	m_fRadius = INITIAL_RADIUS;
	m_pos = D3DXVECTOR3{ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f };

	// �F������
	SetCol(m_col);

	// ���_�ݒ�
	SetVtx();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CFan2D::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �������g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CFan2D::Update(void)
{

}

//=====================================================
// ���_�ʒu�ݒ�
//=====================================================
void CFan2D::SetVtx(void)
{
	// ���_���̃|�C���^
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		
		// ���S�̒��_�̐ݒ�
		pVtx[0].pos = pos;
		pVtx[0].tex = D3DXVECTOR2{ 0.5f,0.5f };

		for (int i = 1;i < m_nNumVtx + 2;i++)
		{// �~���̒��_�̐ݒ�
			float fAngle = (6.28f * m_fAngleMax) * ((float)(i - 1) / (float)m_nNumVtx);

			universal::LimitRot(&fAngle);

			pVtx[i].pos =
			{
				pos.x + sinf(fAngle) * m_fRadius,
				pos.y - cosf(fAngle) * m_fRadius,
				0.0f,
			};

			D3DXVECTOR2 tex =
			{
				0.5f + sinf(fAngle) * 0.5f,
				0.5f - cosf(fAngle) * 0.5f,
			};

			pVtx[i].tex = tex;
		}

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//=====================================================
// �`��
//=====================================================
void CFan2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	if (pDevice != nullptr)
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(m_nIdxTexture);

		// �e�N�X�`���ݒ�
		pDevice->SetTexture(0, pTexture);

		// �w�i�̕`��
 		pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, m_nNumVtx);
	}
}

//=====================================================
// �ݒ菈��
//=====================================================
void CFan2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
// �����ݒ菈��
//=====================================================
void CFan2D::SetRot(float fRot)
{
	m_fRot = fRot;
}

//=====================================================
// �F�ݒ菈��
//=====================================================
void CFan2D::SetCol(D3DXCOLOR col)
{
	m_col = col;

	// ���_���̃|�C���^
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < m_nNumVtx + 2; nCnt++)
		{
			pVtx[nCnt].col = (D3DCOLOR)m_col;

			pVtx[nCnt].rhw = 1.0;
		}

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
}