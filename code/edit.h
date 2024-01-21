//*****************************************************
//
// �G�f�B�^�[�̏���[edit.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "block.h"

//*****************************************************
// �O���錾
//*****************************************************
class CObjectX;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEdit : public CObject
{
public:
	CEdit();	// �R���X�g���N�^
	~CEdit();	// �f�X�g���N�^

	static CEdit *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CEdit *GetInstatnce(void) { return m_pEdit; }

private:
	enum MODE
	{
		MODE_CREATE_BLOCK = 0,	// �u���b�N����
		MODE_DELTE_BLOCK,	// �u���b�N�폜
		MODE_CREATE_GIMICK,	// �M�~�b�N����
		MODE_DELTE_GIMICK,	// �M�~�b�N�폜
		MODE_MAX
	};

	int CheckDelete(void);

	MODE m_mode;	// ���[�h
	CObjectX *m_pObjectCursor;	// �J�[�\���̃I�u�W�F�N�gX�ւ̃|�C���^
	int m_nIdxObject;
	CBlock::TYPE m_type;
	static CEdit *m_pEdit;	// ���g�̃|�C���^
};