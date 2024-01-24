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
	int GetIdx(void) { return m_nIdx; }
	void SetIdx(int nIdx) { m_nIdx = nIdx; }
	CBlock *GetNext(void) { return m_pNext; }
	static int GetNumAll(void) { return m_nNumAll; }
	void SetPosition(D3DXVECTOR3 pos);

private:
	void SwapVtx(void);

	static int m_nNumAll;	// ����
	CCollisionCube *m_pCollisionCube;	// �����̂̓����蔻��
	float m_fLife;	// �̗�
	int m_nIdx;	// ��ނ̃C���f�b�N�X

	CBlock *m_pPrev;	// �O�̃A�h���X
	CBlock *m_pNext;	// ���̃A�h���X
};

#endif
