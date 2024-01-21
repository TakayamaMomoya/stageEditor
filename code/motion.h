//*****************************************************
//
// ���[�V�����̏���[motion.h]
// Author:���R����
//
//*****************************************************

#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "parts.h"
#include "object.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MAX_PARTS	(20)	// �p�[�c�̍ő吔
#define MAX_MOTION	(40)	// ���[�V�����̍ő吔

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CMotion : public CObject
{
public:
	//�L�[�̍\����
	typedef struct
	{
		float fPosX;				//�ʒuX
		float fPosY;				//�ʒuY
		float fPosZ;				//�ʒuZ
		float fRotX;				//����X
		float fRotY;				//����Y
		float fRotZ;				//����Z
	}KEY;

	//�L�[���\����
	typedef struct
	{
		int nFrame;					//�Đ��t���[��
		KEY aKey[MAX_PARTS];			//�e���f���̃L�[�v�f
	}KEY_INFO;

	typedef struct
	{// �p�[�e�B�N�����\����
		int nKey;	//��������L�[
		int nFrame;	//��������t���[��
		D3DXVECTOR3 offset;	// �I�t�Z�b�g�ʒu
		int nIdxParent;	// �e�ƂȂ�p�[�c�̔ԍ�
	}EVENT_INFO;
	
	typedef struct
	{// �����蔻����\����
		int nKey;	//��������L�[
		int nFrame;	//��������t���[��
		D3DXVECTOR3 offset;	// �I�t�Z�b�g�ʒu
		int nIdxParent;	// �e�ƂȂ�p�[�c�̔ԍ�
	}COLLISION_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;						//���[�v���邩�ǂ���
		int nNumKey;					//�L�[�̑���
		KEY_INFO aKeyInfo[MAX_PARTS];	//�L�[���
		int nNumEvent;	// �p�[�e�B�N���̐�
		int nNumCollision;	// �����蔻��̐�
		EVENT_INFO *pEvent;	// �C�x���g���̃|�C���^
		COLLISION_INFO *pCollision;	// �����蔻��̃|�C���^
	}MOTION_INFO;

	// �p�[�c�̍\����
	typedef struct
	{
		int nIdx;
		int nIdxParent;
		CParts *pParts;
	}Parts;

	// �����o�֐�
	CMotion(int nPriority = 5);	// �R���X�g���N�^
	~CMotion();	// �f�X�g���N�^
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(char *pPath);
	void MultiplyMtx(void);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// �ݒ菈��
	void SetPosShadow(D3DXVECTOR3 pos) { m_posShadow = pos; }	// �ݒ菈��
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }	// �ݒ菈��
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �擾����
	D3DXVECTOR3 *GetPosAddress(void) { return &m_pos; }	// �擾����
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	D3DXVECTOR3 GetMtxPos(int nIdx);
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }	// �擾����
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetMotion(int nMotionType);
	int GetMotion(void) { return m_motionType; }
	void SetKeyOld(void);
	static CMotion *Create(char *pPath);
	Parts *GetParts(int nIdx) { return m_apParts[nIdx]; }
	D3DXMATRIX *GetMatrix(void) { return &m_mtxWorld; }
	bool IsFinish(void) { return m_bFinish; }
	void CalcMatrix(void);
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }
	float GetRadiusMax(void);
	void SetAfterImage(D3DXCOLOR col = { 0.0f,0.0f,0.0f,0.0f }, int m_nLife = 10);
	int GetKey(void) { return m_nKey; }
	float GetFrame(void) { return m_fCounterMotion; }
	void SetAllCol(D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }
	void ResetAllCol(void);
	void InitPose(int nMotion);
	void EnableShadow(bool bShadow) { m_bShadow = bShadow; }
	void EnableIndependent(bool bInde) { m_bInde = bInde; }
	bool IsIndependent(void) { return m_bInde; }
	EVENT_INFO *GetInfoEvent(int nMotion) { return m_aMotionInfo[nMotion].pEvent; }
	int GetNumEventInfo(int nMotion) { return m_aMotionInfo[nMotion].nNumEvent; }
	virtual void Event(EVENT_INFO *pEventInfo) {};
	void EnableMotion(int nIdx, bool bMotion);
	void ResetEnableMotion(void);

private:
	Parts *m_apParts[MAX_PARTS];	// �p�[�c�̍\����
	MOTION_INFO m_aMotionInfo[MAX_MOTION];	//���[�V�������̍\����
	KEY m_aKeyOld[MAX_PARTS];	// �O��̃L�[���̍\����
	bool m_abMotion[MAX_PARTS];	// �p�[�c���ƂɃ��[�V���������邩�ǂ���
	int m_nNumMotion;	//���[�V�����̑���
	int m_motionType;	//���[�V�����̎��
	int m_motionTypeOld;	//�O��̃��[�V�����̎��
	int m_nFrame;	// �t���[����
	bool m_bLoopMotion;	//���[�v���邩�ǂ���
	int m_nNumKey;	//�L�[�̑���
	int m_nKey;	//���݂̃L�[
	float m_fCounterMotion;	//���[�V�����J�E���^�[
	int m_nNumParts;	// �p�[�c�̐�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXVECTOR3 m_posShadow;	// �e�̈ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_rot;	//����
	D3DXMATRIX m_mtxWorld;	// �}�g���b�N�X
	D3DXCOLOR m_col;	// �F
	bool m_bFinish;	// ���[�V�������I��������ǂ���
	bool m_bShadow;	// �e��`�悷�邩�ǂ���
	bool m_bInde;	// �������Ă��邩�ǂ���
};

#endif