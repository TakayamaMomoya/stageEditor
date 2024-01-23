//*****************************************************
//
// �u���b�N�Ǘ�[blockManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "block.h"

//*****************************************************
// �O���錾
//*****************************************************
class CModel;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBlockManager : public CObject
{
public:
	struct SInfoBlock
	{// �u���b�N�̏��
		char aTag[256];	// �^�O
		int nIdxModel;	// ���f���ԍ�
		bool bSnag;	// ��Q���ɂȂ邩�ǂ���
	};

	CBlockManager();	// �R���X�g���N�^
	~CBlockManager();	// �f�X�g���N�^

	static CBlockManager *Create(void);
	static CBlockManager *GetInstance(void) { return m_pBlockManager; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetNumBlock(void) { return m_nNumInfoBlock; }
	SInfoBlock *GetInfoBlock(void) { return m_pInfoBlock; }

private:
	void Load(void);

	SInfoBlock *m_pInfoBlock;	// �u���b�N���̃|�C���^
	int m_nNumInfoBlock;	// �u���b�N���̐�
	static CBlockManager *m_pBlockManager;	// ���g�̃|�C���^
};

#endif
