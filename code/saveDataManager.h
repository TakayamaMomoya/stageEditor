//*****************************************************
//
//�Z�[�u�f�[�^�Ǘ�[saveDataManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _SAVEDATAMANAGER_H_
#define _SAVEDATAMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CSaveDataManager : public CObject
{
public:
	CSaveDataManager();	// �R���X�g���N�^
	~CSaveDataManager();	// �f�X�g���N�^

	static CSaveDataManager *Create(void);
	static CSaveDataManager *GetInstance(void) { return m_pSaveDataManager; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Load(void);
	void Save(void);

	int m_nProgress;	// ���݂̐i�s��

	static CSaveDataManager *m_pSaveDataManager;	// ���g�̃|�C���^
};

#endif