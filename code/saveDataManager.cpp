//*****************************************************
//
//�Z�[�u�f�[�^�Ǘ�[saveDataManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "saveDataManager.h"
#include <stdio.h>

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const char* SAVE_PATH = "data\\TEXT\\save.txt";	// �Z�[�u�f�[�^�̃p�X
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CSaveDataManager *CSaveDataManager::m_pSaveDataManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CSaveDataManager::CSaveDataManager()
{
	m_nProgress = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CSaveDataManager::~CSaveDataManager()
{

}

//=====================================================
// ��������
//=====================================================
CSaveDataManager *CSaveDataManager::Create(void)
{
	if (m_pSaveDataManager == nullptr)
	{
		m_pSaveDataManager = new CSaveDataManager;

		if (m_pSaveDataManager != nullptr)
		{
			m_pSaveDataManager->Init();
		}
	}

	return m_pSaveDataManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CSaveDataManager::Init(void)
{
	Load();

	return S_OK;
}

//=====================================================
// �Ǎ�
//=====================================================
void CSaveDataManager::Load(void)
{
	// �ϐ��錾
	char cTemp[256];
	int nCntPos = 0;

	// �t�@�C������ǂݍ���
	FILE *pFile = fopen(SAVE_PATH, "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "PROGRESS") == 0)
			{// �i�s�󋵓Ǎ�
				(void)fscanf(pFile, "%s", &cTemp[0]);

				(void)fscanf(pFile, "%d", &m_nProgress);
			}
		}
	}
}

//=====================================================
// �I������
//=====================================================
void CSaveDataManager::Uninit(void)
{
	m_pSaveDataManager = nullptr;

	Release();
}

//=====================================================
// �ۑ�
//=====================================================
void CSaveDataManager::Save(void)
{
	FILE *pFile = NULL;

	pFile = fopen(SAVE_PATH, "w");

	if (pFile != NULL)
	{
		// �i�s��
		fprintf(pFile, "PROGRESS = %d\n", m_nProgress);

		fprintf(pFile, "END_SCRIPT\n");

		fclose(pFile);
	}
}

//=====================================================
// �X�V����
//=====================================================
void CSaveDataManager::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CSaveDataManager::Draw(void)
{

}