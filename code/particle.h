//*****************************************************
//
// �p�[�e�B�N������[particle.h]
// Author:���R����
//
//*****************************************************

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CParticle : public CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_EXPLOSION,	// ����
		TYPE_INJECTION_FIRE,	// ����(��)
		TYPE_INJECTION_SMOKE,	// ����(��)
		TYPE_SMOKE,	// ��
		TYPE_TOMATO_JUICE,	// �g�}�g�`
		TYPE_MISSILE_SMOKE,	// �~�T�C���̉�
		TYPE_MISSILE_SPARK,	// �~�T�C���̉Ή�
		TYPE_BREAK_WEAPON,	// ����̔j��
		TYPE_MAX
	}TYPE;

	CParticle(int nPriority = 3);	// �R���X�g���N�^
	~CParticle();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};
	static CParticle *Create(D3DXVECTOR3 pos, TYPE type, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f },D3DXVECTOR3 *pPosOwner = nullptr, int nPriorityEffect = 5);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); }	// �擾����
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };	// �����ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �����擾
	float GetWidth(void) { return 0.0f; }	// �T�C�Y�擾
	float GetHeight(void) { return 0.0f; }	// �T�C�Y�擾
	static void Load(void);	// �Ǎ�����
	static void Unload(void);	// �j������

private:
	typedef struct
	{// �p�[�e�B�N�����
		char acTexPath[256];
		int nLife;	// ����
		int nLifeEffect;	// �G�t�F�N�g�̎���
		float fRadiusEffect;	// �G�t�F�N�g�̔��a
		int nNumEffect;	// �G�t�F�N�g�̐�
		float fSpeed;	// �G�t�F�N�g�̊�X�s�[�h
		D3DXCOLOR col;	// �F
		int nAdd;	// ���Z���������邩�ǂ���
		float fGravity;	// �d��
		float fDecrease;	// ���a������
		float fRangeRot;	// �����̃����_���͈�
		int nRot;	// �����𔽉f���邩�ǂ���
		bool bTurn;	// ���]���邩�ǂ���
	}PARTICLE_INFO;

	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 *m_pPosOwner;	// ������̈ʒu
	D3DXVECTOR3 m_rot;	// ����
	int m_nLife;	// ����
	static PARTICLE_INFO *m_apParticleInfo[TYPE_MAX + 1];
	TYPE m_type; // ���
	int m_nPriorityEffect;
};

#endif