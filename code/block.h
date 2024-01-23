//*****************************************************
//
// �u���b�N�̏���[block.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "ObjectX.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionCube;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBlock : public CObjectX
{
public:
	typedef enum
	{// ���
		TYPE_WALL = 0,	// ��
		TYPE_MAX
	}TYPE;

	typedef struct
	{// �ۑ�����Ƃ��̏��
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		TYPE type;
	}MemBlock;

	CBlock(int nPriority = 3);	// �R���X�g���N�^
	~CBlock();	// �f�X�g���N�^

	static CBlock *Create(int nIdxModel);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(float fDamage);
	void SetRot(D3DXVECTOR3 rot);
	int GetID(void) { return m_nID; }
	static HRESULT Load(char *pPath);	// �Ǎ�
	static void Save(void);	// �ۑ�
	static void Delete(int nIdx);	// �����폜����
	static void DeleteAll(void);	// �S�폜����
	static int GetNumAll(void) { return m_nNumAll; }
	static CBlock **GetBlock(void) { return &m_apBlock[0]; }
	static float CheckShadow(D3DXVECTOR3 pos);
	static void LoadModel(void);
	static void DeleteIdx(void);

private:
	void SwapVtx(void);

	static CBlock *m_apBlock[NUM_OBJECT];	// �u���b�N�̔z��
	static int m_nNumAll;	// ����
	CCollisionCube *m_pCollisionCube;	// �����̂̓����蔻��
	float m_fLife;	// �̗�
	int m_nID;	// ID
};

#endif
