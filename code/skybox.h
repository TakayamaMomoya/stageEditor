//*****************************************************
//
// �X�J�C�{�b�N�X�̏���[skybox.h]
// Author:���R����
//
//*****************************************************

#ifndef _SKYBOX_H_
#define _SKYBOX_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CSkybox : public CObjectX
{
public:
	CSkybox(int nPriority = 3);	// �R���X�g���N�^
	~CSkybox();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSkybox *Create();

private:
};

#endif

