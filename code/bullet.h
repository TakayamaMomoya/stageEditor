//*****************************************************
//
// �e����[bullet.h]
// Author:���R����
//
//*****************************************************

#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "collision.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MAX_HIT	(54)	// �ő�Ŋo�����閽�������I�u�W�F�N�g

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;
class CObject3D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBullet : public CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_PLAYER,	// �v���C���[�̒e
		TYPE_ENEMY,	// �G�̒e
		TYPE_MAX
	}TYPE;

	CBullet(int nPriority = 6);	// �R���X�g���N�^
	~CBullet();	// �f�X�g���N�^

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fLife, TYPE type, bool bPierce = false, float fRadius = 2.0f, float fDamage = 5.0f, D3DXCOLOR col = { 1.0f,1.0f,1.0f,1.0f });
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetNumAll(void) { return m_nNumAll; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	void SetIdxPlayer(int nIdx) { m_nIdxPlayer = nIdx; }

private:
	bool BulletHit(CCollision::TAG tag);
	void Death(void);

	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	float m_fLife;	// ����
	TYPE m_type;	// ���
	static int m_nNumAll;	// ����
	bool m_bPierce;	// �ђʂ��邩�ǂ���
	CCollisionSphere *m_pCollisionSphere;	// ���̓����蔻��
	CObject3D *m_pObject3D;	// �����ڂ̃|�C���^
	D3DXCOLOR m_col;	// �F
	float m_fDamage;	// �^�_���[�W
	float m_fSize;	// �e�̃T�C�Y
	int m_nIdxPlayer;	// �v���C���[�ԍ�
};

#endif