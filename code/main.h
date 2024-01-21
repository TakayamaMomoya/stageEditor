//*****************************************************
//
// ���C������[main.h]
// Author:���R����
//
//*****************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include <windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)						//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"
#include "xaudio2.h"
#include <assert.h>
#include "universal.h"

//*****************************************************
// ���C�u����
//*****************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//*****************************************************
//�}�N����`
//*****************************************************
#define SCREEN_WIDTH			(1280)									// �E�B���h�E�̕�
#define SCREEN_HEIGHT			(720)									// �E�B���h�E�̍���
#define FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���_�t�H�[�}�b�g�ݒ�
#define FVF_VERTEX_3D			(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//���_�t�H�[�}�b�g�ݒ�
#define NUM_PLAYER (4)	// �v���C���[�̍ő吔

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
}

//*****************************************************
// �\���̒�`
//*****************************************************
typedef struct
{// 2D�̒��_���
	D3DXVECTOR3 pos;			//���_���W
	float rhw;					//���W�ϊ��p�W���i�P�D�O���ŌŒ�j
	D3DCOLOR col;				//���_�J���[
	D3DXVECTOR2 tex;			//�e�N�X�`�����W
}VERTEX_2D;

typedef struct
{// �RD�̒��_���
	D3DXVECTOR3 pos;			//���_���W
	D3DXVECTOR3 nor;			//�@���x�N�g��
	D3DCOLOR col;				//���_�J���[
	D3DXVECTOR2 tex;			//�e�N�X�`�����W
}VERTEX_3D;

//*****************************************************
// �v���g�^�C�v�錾
//*****************************************************
int GetFPS(void);

#endif