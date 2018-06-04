#include "Dxlib.h"
#include "fade_out.h"
#include "fade_in.h"
#define _USE_MATH_DEFINES
#include <cmath>

extern int fade_out_img;

const int display_width = 1024;
const int display_height = 768;

void fade_out_circle(){

	int var;
	GetDrawScreenGraph(0, 0, display_width, display_height, fade_out_img);
	var = fade_out_img;

	for (int i = 0; i <= 700; i += 24)
	{
		// ��ʂ�������
		//ClearDrawScreen();

		DrawGraph(0, 0, var, true);
		// �`�悵���O���t�B�b�N�̏�ɔ��]�~��`��
		//DrawReversalCircle(320, 240, Mode == 0 ? 399-i : 399-i, 0);
		draw_reverse_circle(display_width / 2, display_height / 2, 700-i);

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
}

void fade_out_alpha() {

	int var,k;
	GetDrawScreenGraph(0, 0, display_width, display_height, fade_out_img);
	var = fade_out_img;

	for (int i = 0; i < 512 + 128; i += 18)
	{
		// ��ʂ�������
		//ClearDrawScreen();

		//�O���t�B�b�N�P��`�悵�܂�
		DrawGraph(0, 0, var, FALSE);

		// �O���t�B�b�N�Q��`�悵�܂�
		for (int j = 0; j < 128; j++)
		{
			// �`��\�̈�ݒ�p�̒l�Z�b�g
			k = j + i - 128;

			// �`��\�̈���w�肵�܂�
			if (k >= 0)
			{
				// �A���t�@�u�����h�l���Z�b�g
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 254 - 2 * j);

				//���ߕ��������E���璆�S�Ɍ������ĕ`��
				DrawBox(k, 0, k + 1, display_height, GetColor(0, 0, 0), true);
				DrawBox(display_width - (k + 1), 0, display_width - k, display_height, GetColor(0, 0, 0), true);

			}
		}

		// �u�����h���[�h�����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		k = i - 128;
		if (k > 0)
		{
			//����������`��
			DrawBox(0, 0, k, display_height, GetColor(0, 0, 0), true);
			DrawBox(display_width - k, 0, display_width, display_height, GetColor(0, 0, 0), true);

		}

		//����ʂ̕`��
		ScreenFlip();
	}
}

void fade_out_title(int title_img) {
	for (int i = 0; i < 64; i++)
	{
		// ��ʂ�������
		ClearDrawScreen();
		DrawBox(0, 0, display_width, display_height, GetColor(0, 0, 0), true);

		// �A���t�@�u�����h�l���Z�b�g
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 252 - 4 * i);

		//�O���t�B�b�N�P��`�悵�܂�
		DrawRotaGraph(512, 384, 1.0 + (1.0*i / float(64)), 2 * M_PI*(i / float(64)), title_img, true, false);
		// �u�����h���[�h�����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//����ʂ̕`��
		ScreenFlip();
	}
}

void fade_out_place() {
	int var, k;
	GetDrawScreenGraph(0, 0, display_width, display_height, fade_out_img);
	var = fade_out_img;
	//�}�b�v�A���A�_���W����fade_out
	for (int i = 0; i < 80; i += 2) {

		// �t�F�[�h�A�E�g�O�̉摜��`��
		DrawGraph(0, 0, var, true);

		for (int j = 0; j < display_width / 32; j++)
		{
			// �`��\�̈�ݒ�p�̒l�Z�b�g
			k = j + i - 32;
			if (k > 0)
			{
				if (k > 32) {
					k = 32;
				}

				// �`��\�̈���w��
				SetDrawArea((display_width - 32) - j * 32, 0, (display_width - 32) - (j * 32 - k), display_height);

				DrawBox(0, 0, display_width, display_height, GetColor(0, 0, 0), true);
			}
		}
		SetDrawArea(0, 0, display_width, display_height);
		//����ʂ̕`��
		ScreenFlip();

	}
}