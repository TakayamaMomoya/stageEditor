//*****************************************************
//
// �r�[���̏���[beam.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "beam.h"
#include "anim3D.h"
#include "animEffect3D.h"
#include "universal.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int NUM_VTX = 4;	// �����蔻��̒��_��
const float INITIAL_WIDTH_ANIM = 50.0f;	// �A�j���[�V�����̕�
const float INITIAL_WIDTH_LENGTH = 300.0f;	// �A�j���[�V�����̒���
const float INITIAL_SPEED_EXPAND = 40.f;	// �c��ޑ��x
const float INITIAL_SPEED_SHRINK = 5.0f;	// �k�ޑ��x
const float INITIAL_SPEED_EXTEND = 200.0f;	// �L�т鑬�x
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CBeam::CBeam(int nPriority) : CObject(nPriority)
{
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBeam::~CBeam()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CBeam::Init(void)
{
	if (m_info.pAnim == nullptr)
	{// �A�j���[�V�����G�t�F�N�g�̐���
		CAnimEffect3D *pAnimEffect = CAnimEffect3D::GetInstance();

		if (pAnimEffect != nullptr)
		{
			m_info.pAnim = pAnimEffect->CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CAnimEffect3D::TYPE::TYPE_BEAM);

			if (m_info.pAnim != nullptr)
			{
				m_info.pAnim->EnableZtest(false);
			}
		}
	}

	// �l�̏�����
	m_info.fWidthAnimDest = INITIAL_WIDTH_ANIM;
	m_info.fLengthAnimDest = INITIAL_WIDTH_LENGTH;
	m_info.fSpeedExpand = INITIAL_SPEED_EXPAND;
	m_info.fSpeedShrink = INITIAL_SPEED_SHRINK;
	m_info.fSpeedExtend = INITIAL_SPEED_EXTEND;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CBeam::Uninit(void)
{
	if (m_info.pAnim != nullptr)
	{
		m_info.pAnim->Uninit();
		m_info.pAnim = nullptr;
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CBeam::Update(void)
{
	// �T�C�Y�̊Ǘ�
	ManageSize();

	// �A�j���[�V�����̒��_�ʒu�ݒ�
	SetAnimVtx();
}

//=====================================================
// �T�C�Y�̊Ǘ�
//=====================================================
void CBeam::ManageSize(void)
{
	if (m_info.fLengthAnimDest > m_info.fLengthAnim)
	{
		// �L�т鏈��
		m_info.fLengthAnim += m_info.fSpeedExtend;

		if (m_info.fLengthAnimDest <= m_info.fLengthAnim)
		{// ��������
			m_info.fLengthAnim = m_info.fLengthAnimDest;
		}
	}

	if (m_info.bFinish == false)
	{
		if (m_info.fWidthAnimDest > m_info.fWidthAnim)
		{
			// �c��ޏ���
			m_info.fWidthAnim += m_info.fSpeedExpand;

			if (m_info.fWidthAnimDest <= m_info.fWidthAnim)
			{// ���̐���
				m_info.fWidthAnim = m_info.fWidthAnimDest;

				m_info.bFinish = true;
			}
		}
	}
	else
	{
		// �k�ޏ���
		m_info.fWidthAnim -= m_info.fSpeedShrink;
		
		if (m_info.fWidthAnim <= 0.0f)
		{// �k�݂�������I��
			m_info.fWidthAnim = 0.0f;

			Uninit();
		}
	}
}

//=====================================================
// �A�j���[�V�����̒��_�ʒu�ݒ�
//=====================================================
void CBeam::SetAnimVtx(void)
{
	if (m_info.pAnim == nullptr)
	{
		return;
	}

	// ���_�o�b�t�@�̎擾
	CAnim3D *pAnim = m_info.pAnim;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = pAnim->GetVtxBuff();

	if (pVtxBuff == nullptr)
	{
		return;
	}

	// ���_���̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̐ݒ�
	D3DXVECTOR3 aPosVtx[NUM_VTX];
	D3DXMATRIX aMtxVtx[NUM_VTX];
	D3DXVECTOR3 aOffset[NUM_VTX] =
	{
		{ -m_info.fLengthAnim,0.0f,m_info.fWidthAnim },
		{ 0.0f,0.0f,m_info.fWidthAnim },
		{ -m_info.fLengthAnim,0.0f,-m_info.fWidthAnim },
		{ 0.0f,0.0f,-m_info.fWidthAnim },
	};

	for (int i = 0; i < NUM_VTX; i++)
	{
		universal::SetOffSet(&aMtxVtx[i], m_info.mtxWorld, aOffset[i]);

		aPosVtx[i] =
		{
			aMtxVtx[i]._41,
			aMtxVtx[i]._42,
			aMtxVtx[i]._43,
		};

		pVtx[i].pos = aPosVtx[i];
	}

	//���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//=====================================================
// �`�揈��
//=====================================================
void CBeam::Draw(void)
{

}

//=====================================================
// ��������
//=====================================================
CBeam *CBeam::Create(void)
{
	CBeam *pBeam = nullptr;

	if (pBeam == nullptr)
	{
		pBeam = new CBeam;

		if (pBeam != nullptr)
		{
			// ������
			pBeam->Init();
		}
	}

	return pBeam;
}