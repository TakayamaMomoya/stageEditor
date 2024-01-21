//*****************************************************
//
// �u���b�N�Ǘ�[blockManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "BlockManager.h"
#include <stdio.h>

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const char* FILE_PATH = "data\\TEXT\\map.txt";	// �}�b�v���
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CBlockManager *CBlockManager::m_pBlockManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CBlockManager::CBlockManager()
{
	m_pInfoBlock = nullptr;
	m_nNumInfoBlock = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBlockManager::~CBlockManager()
{

}

//=====================================================
// ��������
//=====================================================
CBlockManager *CBlockManager::Create(void)
{
	if (m_pBlockManager == nullptr)
	{// �C���X�^���X����
		m_pBlockManager = new CBlockManager;

		// ����������
		m_pBlockManager->Init();
	}

	return m_pBlockManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CBlockManager::Init(void)
{
	Load();

	return S_OK;
}

//=====================================================
// �ǂݍ��ݏ���
//=====================================================
void CBlockManager::Load(void)
{
	//�ϐ��錾
	char cTemp[256];
	int nCntBlock= 0;

	//�t�@�C������ǂݍ���
	FILE *pFile = fopen(FILE_PATH, "r");

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ
		while (true)
		{
			//�����ǂݍ���
			(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "NUM_BLOCK") == 0)
			{
				(void)fscanf(pFile, "%s", &cTemp[0]);

				(void)fscanf(pFile, "%d", &m_nNumInfoBlock);

				if (m_pInfoBlock == nullptr)
				{// �u���b�N���̊m��
					m_pInfoBlock = new SInfoBlock[m_nNumInfoBlock];

					ZeroMemory(m_pInfoBlock, sizeof(SInfoBlock) * m_nNumInfoBlock);
				}
			}

			if (strcmp(cTemp, "INFOBLOCK") == 0)
			{
				while (true)
				{
					//�����ǂݍ���
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
// �I������
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
// �X�V����
//=====================================================
void CBlockManager::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CBlockManager::Draw(void)
{
#ifdef _DEBUG

#endif
}