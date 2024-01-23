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

					if (strcmp(cTemp, "TAG") == 0)
					{
						(void)fscanf(pFile, "%s", &cTemp[0]);

						(void)fscanf(pFile, "%s", &m_pInfoBlock[nCntBlock].aTag[0]);
					}

					if (strcmp(cTemp, "MODEL") == 0)
					{
						(void)fscanf(pFile, "%s", &cTemp[0]);
						(void)fscanf(pFile, "%s", &cTemp[0]);

						m_pInfoBlock[nCntBlock].nIdxModel = CModel::Load(&cTemp[0]);
					}

					if (strcmp(cTemp, "SNAG") == 0)
					{
						int nBool;

						(void)fscanf(pFile, "%s", &cTemp[0]);

						(void)fscanf(pFile, "%d", &nBool);

						if (nBool == 1)
						{
							m_pInfoBlock[nCntBlock].bSnag = true;
						}
						else
						{
							m_pInfoBlock[nCntBlock].bSnag = false;
						}
					}

					if (strcmp(cTemp, "END_INFOBLOCK") == 0)
					{
						nCntBlock++;

						break;
					}
				}
			}

			// ���[�h���̓ǂݍ���
			LoadMap(pFile, &cTemp[0]);

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
}

//=====================================================
// �}�b�v�z�u�̓ǂݍ���
//=====================================================
void CBlockManager::LoadMap(FILE *pFile, char *pTemp)
{
	if (strcmp(pTemp, "SETBLOCK") == 0)
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		int nIdx;

		while (true)
		{
			//�����ǂݍ���
			(void)fscanf(pFile, "%s", pTemp);

			if (strcmp(pTemp, "IDX") == 0)
			{// �C���f�b�N�X
				(void)fscanf(pFile, "%s", pTemp);

				(void)fscanf(pFile, "%d", &nIdx);
			}

			if (strcmp(pTemp, "POS") == 0)
			{// �ʒu
				(void)fscanf(pFile, "%s", pTemp);

				(void)fscanf(pFile, "%f", &pos.x);
				(void)fscanf(pFile, "%f", &pos.y);
				(void)fscanf(pFile, "%f", &pos.z);
			}

			if (strcmp(pTemp, "ROT") == 0)
			{// ����
				(void)fscanf(pFile, "%s", pTemp);

				(void)fscanf(pFile, "%f", &rot.x);
				(void)fscanf(pFile, "%f", &rot.y);
				(void)fscanf(pFile, "%f", &rot.z);
			}

			if (strcmp(pTemp, "END_SETBLOCK") == 0)
			{
				// �u���b�N����
				CBlock *pBlock = CBlock::Create(m_pInfoBlock[nIdx].nIdxModel);

				if (pBlock != nullptr)
				{
					pBlock->SetPosition(pos);
					pBlock->SetRot(rot);
				}

				break;
			}
		}
	}
}

//=====================================================
// �}�b�v���ۑ�
//=====================================================
void CBlockManager::Save(char *pPath)
{
	FILE *pFile = nullptr;

	pFile = fopen(pPath, "w");

	if (pFile != nullptr)
	{
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# �}�b�v�̃u���b�N�z�u���[map.txt]\n");
		fprintf(pFile, "# Author�FMomoya Takayama\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "SCRIPT\n\n");
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "# ���f����\n");
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "NUM_BLOCK = %d\n\n", m_nNumInfoBlock);

		for (int i = 0;i < m_nNumInfoBlock;i++)
		{
			char *pPathBlock = CModel::GetPath(m_pInfoBlock[i].nIdxModel);

			fprintf(pFile, "#%d�Ԗڂ̃u���b�N\n", i);
			fprintf(pFile, " TAG = %s\n", &m_pInfoBlock[i].aTag[0]);
			fprintf(pFile, " MODEL = %s\n", pPathBlock);
			fprintf(pFile, " SNAG = %d\n\n", m_pInfoBlock[i].bSnag);
		}

		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "# �z�u���\n");
		fprintf(pFile, "#====================================================================\n");

		CBlock::GetNumAll();



		fprintf(pFile, "END_SCRIPT\n");

		fclose(pFile);
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