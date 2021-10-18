#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"
#include "Game.h"
#include "Func.h"
#include "Sound.h"
#include "erslib19.h" //�V���A���ʐM���ȒP�ɂ��Ă����w�b�_�t�@�C��


//�V���A���ʐM�̂��߂ɕK�{�ȕϐ�4��
#define BUFSIZE 5000
static int com = 1;
static char buf[1000];
static int r;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    int MouseInput;

    ChangeWindowMode(FALSE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    r = ERS_Open(com, BUFSIZE, BUFSIZE);    // rs232c�̃|�[�g���I�[�v������
    ERS_Config(com, ERS_9600);		// �ʐM���x��9600bps�ɂ���(�f�t�H���g)
    Game_Initialize(); //�V���A���ʐM�̏���
    Sound_Initialize(); //�T�E���h�ǂݍ��݁i���ł��g�����Ԃɂ��Ă����j
    Opening_Sound();
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        Keyboard_Update();
        SceneMgr_Update();
        SceneMgr_Draw();
        if (ERS_CheckRecv(com) > 0) {  // �V���A���ʐM�̎�M�f�[�^����
            DrawString(200, 100, "��M�f�[�^����", GetColor(254, 247, 240));
            r = ERS_Recv(com, buf, 1);
            DrawFormatString(200, 120, GetColor(255, 255, 255), "r�̒l�F%d", r);
            DrawFormatString(200, 140, GetColor(255, 255, 255), "buf[0]�̒l�F%c", buf[0]);
            DrawFormatString(200, 160, GetColor(255, 255, 255), "buf[1]�̒l�F%c", buf[1]);

            if (buf[0] < 920) {
                DrawString(200, 100, "buf[0]�͐��l�f�[�^�ł�", GetColor(254, 247, 240));
            }
        }

    }

    DxLib_End();
    return 0;
}