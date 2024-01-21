//*****************************************************
//
// �X���[�̏���[slow.h]
// Author:���R����
//
//*****************************************************

#ifndef _SLOW_H_
#define _SLOW_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CSlow : public CObject
{
public:
	CSlow();	// �R���X�g���N�^
	~CSlow();	// �f�X�g���N�^

	static CSlow *Create(void);
	static CSlow *GetInstance(void) { return m_pSlow; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	float GetScale(void) { return m_fScale; }
	void SetScale(float fScale);

private:
	float m_fScale;

	static CSlow *m_pSlow;	// ���g�̃|�C���^
};

#endif