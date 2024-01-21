//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���R����
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	typedef enum
	{
		LABEL_BGM000 = 0,				// �^�C�g��BGM
		LABEL_SE_GET_WEAPON,			// ����擾
		LABEL_SE_GUNSHOT_00,			// ���C��00
		LABEL_SE_GUNSHOT_01,			// ���C��01
		LABEL_SE_OPEN_BOX,				// �����J��
		LABEL_SE_APPEARE,				// �o��
		LABEL_BGM_SELECT,				// �I�����bgm
		LABEL_BGM_GAME,					// �Q�[��bgm
		LABEL_SE_REPAIR,				// �C�U
		LABEL_SE_GUNSHOT_02,			// ���C��02
		LABEL_SE_START_GAME,			// �Q�[���X�^�[�g
		LABEL_BGM_TITLE,				// �^�C�g��
		LABEL_SE_LUNCH,					// ���P�b�g����
		LABEL_SE_GUNSHOT_03,			// ���C��03

		LABEL_SE_GET_MAGNUM,			// �}�O�i���擾��
		LABEL_SE_GET_MACHINEGUN,		// �}�V���K���擾��
		LABEL_SE_GET_SHOTGUN,			// �V���b�g�K���擾��
		LABEL_SE_GET_RAILGUN,			// ���[���K���擾��

		LABEL_SE_SWING,					// �X�E�B���O
		LABEL_SE_DAMAGE,				// �_���[�W
		LABEL_SE_HIT,					// �q�b�g

		LABEL_SE_DOOR_TOUCH,			// �h�A�̃C���^���N�g
		LABEL_SE_BOX_BROKEN,			// ����j��

		LABEL_SE_RIFT,					// �Z���N�g���t�g
		LABEL_SE_RIFTING,				// ���������グ��
		LABEL_SE_DOOR_OPEN,				// �h�A���J��

		LABEL_SE_PAUSE_MENU,			// �|�[�Y
		LABEL_SE_PAUSE_ARROW,			// �|�[�Y�ړ�
		LABEL_SE_PAUSE_ENTER,			// �|�[�Y�I��

		LABEL_SE_GET_MINIGUN,			// �~�j�K���擾
		LABEL_SE_GET_LUNCHER,			// ���P�����擾
		LABEL_SE_GUNSHOT_04,			// ���P�����ˌ�
		LABEL_SE_WEAPON_LOST,			// ���������
		LABEL_SE_STAMP,					// �X�^���v
		LABEL_SE_GAMEOVER,				// �Q�[���I�[�o�[

		LABEL_SE_EMOTE_UP,				// �G���[�g�\���L�[ ��
		LABEL_SE_EMOTE_DOWN,			// �G���[�g�\���L�[ ��
		LABEL_SE_EMOTE_LEFT,			// �G���[�g�\���L�[ ��
		LABEL_SE_EMOTE_RIGHT,			// �G���[�g�\���L�[ ��

		LABEL_SE_EXPLOSION,				// ����
		LABEL_BGM_RANKING,				// �����L���O
		LABEL_SE_SIREN,					// �T�C����
		LABEL_SE_COUNT_DOWN,			// �J�E���g�_�E��

		LABEL_MAX
	} LABEL;

	typedef enum
	{
		FADESTATE_NONE = 0,	//�������Ă��Ȃ����
		FADESTATE_IN,	//�t�F�[�h�C�����
		FADESTATE_OUT,	//�t�F�[�h�A�E�g���
		FADESTATE_MAX
	}FADESTATE;

	CSound();	// �R���X�g���N�^
	~CSound();	// �f�X�g���N�^

	static CSound *Create(HWND hWnd);
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);

	void SetVolume(LABEL label, float fVolume);
	void SetFade(LABEL LabelNow, LABEL LabelNext, float fSpeed);

	static CSound *GetInstance(void) { return m_pSound; }

private:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];	// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];	// �I�[�f�B�I�f�[�^�T�C�Y
	FADESTATE m_fadeSound;	// �t�F�[�h���
	LABEL m_SoundLabelNow;	// ���݂̃T�E���h���x��
	LABEL m_SoundLabelNext;	// ���̃T�E���h���x��
	float m_fSpeedFadeSound;	// �T�E���h���t�F�[�h����X�s�[�h
	float m_fVolumeSound;	// �T�E���h�̃{�����[��

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[LABEL_MAX] =
	{
		{ "data/SOUND/BGM/title.wav", -1 },				// �^�C�g��	
		{ "data/SOUND/SE/get_weapon_00.wav",0 },		// �G������擾
		{ "data/SOUND/SE/gunshot_sound_00.wav",0 },		// �}�O�i�����C
		{ "data/SOUND/SE/gunshot_sound_01.wav",0 },		// �}�V���K�����C
		{ "data/SOUND/SE/open_weaponbox.wav",0 },		// ����̔��J��
		{ "data/SOUND/SE/Appearance.wav",0 },			// �o��
		{ "data/SOUND/BGM/select.wav",-1 },				// �I��
		{ "data/SOUND/BGM/game.wav",-1 },				// �Q�[��
		{ "data/SOUND/SE/repair.wav",0 },				// �C�U
		{ "data/SOUND/SE/gunshot_sound_03.wav",0 },		// �V���b�g�K�����C
		{ "data/SOUND/SE/start_game.wav",0 },			// �Q�[���X�^�[�g
		{ "data/SOUND/BGM/title_BGM.wav",-1 },			// �^�C�g���T�E���h	
		{ "data/SOUND/SE/rocket_lunch.wav",0 },			// ���P�b�g����
		{ "data/SOUND/SE/gunshot_sound_04.wav",0 },		// ���[���K�����C

		{ "data/SOUND/SE/get_magnum.wav",0 },			// �}�O�i���{�C�X
		{ "data/SOUND/SE/get_submachinegun.wav",0 },	// �}�V���K���{�C�X
		{ "data/SOUND/SE/get_shotgun.wav",0 },			// �V���b�g�K���{�C�X
		{ "data/SOUND/SE/get_railgun.wav",0 },			// ���[���K���{�C�X

		{ "data/SOUND/SE/swing.wav",0 },				// �X�E�B���O
		{ "data/SOUND/SE/damage.wav",0 },				// �_���[�W
		{ "data/SOUND/SE/hit.wav",0 },					// �q�b�g

		{ "data/SOUND/SE/door_open.wav",0 },			// �h�A�̃C���^���N�g
		{ "data/SOUND/SE/box_broken.wav",0 },			// ���j��

		{ "data/SOUND/SE/rift.wav",0 },					// ���t�g
		{ "data/SOUND/SE/lifting.wav",0 },				// �����グ��
		{ "data/SOUND/SE/door_enter.wav",0 },			// �h�A���J��

		{ "data/SOUND/SE/pause.wav",0 },				// �|�[�Y
		{ "data/SOUND/SE/pause_arrow.wav",0 },			// �I��
		{ "data/SOUND/SE/pause_enter.wav",0 },			// ����

		{ "data/SOUND/SE/get_minigun.wav",0 },			// �~�j�K���擾
		{ "data/SOUND/SE/get_luncher.wav",0 },			// ���P�����擾
		{ "data/SOUND/SE/gunshot_sound_05.wav",0 },		// ���P�����擾
		{ "data/SOUND/SE/weapon_lost.wav",0 },			// ���편��
		{ "data/SOUND/SE/stamp.wav",0 },				// �X�^���v
		{ "data/SOUND/SE/fail.wav",0 },					// �Q�[���I�[�o�[

		{ "data/SOUND/SE/up.wav",0 },					// �G���[�g�\���L�[ �� 
		{ "data/SOUND/SE/down.wav",0 },					// �G���[�g�\���L�[ �� 
		{ "data/SOUND/SE/left.wav",0 },					// �G���[�g�\���L�[ �� 	
		{ "data/SOUND/SE/right.wav",0 },				// �G���[�g�\���L�[ �� 

		{ "data/SOUND/SE/explosion.wav",0 },			// ����
		{ "data/SOUND/BGM/ranking.wav",0 },				// �����L���O
		{ "data/SOUND/SE/siren.wav",0 },				// �T�C����
		{ "data/SOUND/SE/counter.wav",0 }				// �J�E���g�_�E��
	};

	static CSound *m_pSound;	// ���g�̃|�C���^
};

#endif