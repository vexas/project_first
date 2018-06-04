#include "Dxlib.h"
#include "fade_in.h"
#include "draw_map.h"

const int color_black = GetColor(0, 0, 0);
const int display_width = 1024;
const int display_height = 768;
extern int field_img;

//�~�`�̃t�F�[�h�C��
//image_cnt�c�`�悵�����摜�̐��A2�ڈȍ~�̈����c�摜
//��Ƀo�g���V�[���̃t�F�[�h�C���p
void fade_in_circle(int background_handle,int enemy_handle) {
	
	for (int i = 0; i <= 700; i += 24)
	{
		// ��ʂ�������
		ClearDrawScreen();

		DrawGraph(0, 0, background_handle, true);
		DrawGraph(50, 200, enemy_handle, true);

		// �`�悵���O���t�B�b�N�̏�ɔ��]�~��`��
		//DrawReversalCircle(320, 240, Mode == 0 ? 399-i : 399-i, 0);
		draw_reverse_circle(display_width/2, display_height/2, i);

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
}

void fade_in_alpha(int scrollx, int scrolly, int *map, int *map2, int character_number, int animation_control, bool is_right, bool is_move) {

	int k;

	for (int i = 512 + 128; i >= 0; i -= 18)
	{
		// ��ʂ�������
		ClearDrawScreen();

		//�O���t�B�b�N�P��`�悵�܂�
		//DrawGraph(0, 0, image1, FALSE);
		draw_map(scrollx, scrolly, map, character_number, animation_control, is_right, is_move);
		draw_map(scrollx, scrolly, map2, character_number, animation_control, is_right, is_move);

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

				//���ߕ����𒆐S���獶�E�Ɍ������ĕ`��
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

void fade_in_dungeon(int scrollx, int scrolly, int *map, int *map2, int character_number, int animation_control, bool is_right, bool is_move) {

	int k;

	for (int i = 0; i < 80; i += 2) {
		ClearDrawScreen();

		// �w�ʂɍ����̈��`��
		DrawBox(0, 0, display_width, display_height, GetColor(0, 0, 0), true);

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

				draw_map(scrollx, scrolly, map, character_number, animation_control, is_right, is_move);
				draw_map(scrollx, scrolly, map2, character_number, animation_control, is_right, is_move);
			}
		}
		SetDrawArea(0, 0, display_width, display_height);
		//����ʂ̕`��
		ScreenFlip();

	}
}

void fade_in_town(int town_image) {
	int k;

	for (int i = 0; i < 80; i += 2) {
		ClearDrawScreen();

		// �w�ʂɍ����̈��`��
		DrawBox(0, 0, display_width, display_height, GetColor(0, 0, 0), true);

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

				DrawGraph(0, 0, town_image, true);
			}
		}
		SetDrawArea(0, 0, display_width, display_height);
		//����ʂ̕`��
		ScreenFlip();

	}
}

void draw_reverse_circle(int pos_x,int pos_y,int radius) {
	// �~���]�`��̈�̊O����`��
	DrawBox(0, 0, display_width, pos_y - radius, color_black, TRUE);
	DrawBox(0, pos_y - radius, pos_x - radius, display_height, color_black, TRUE);
	DrawBox(pos_x - radius, pos_y + radius + 1, display_width, display_height, color_black, TRUE);
	DrawBox(pos_x + radius, pos_y - radius, display_width, pos_y + radius + 1, color_black, TRUE);

	// �`�揈��
	int dx, dy, F, j;
	int pos_x1, pos_x2, pos_y1;

	// �����l�Z�b�g
	dx = radius; dy = 0; F = -2 * radius + 3;

	j = 0;
	// �܂��ŏ��ɍ��W�f�[�^��i�߂�
	if (F >= 0)
	{
		pos_x2 = dy + pos_x; pos_x1 = -dy + pos_x; pos_y1 = dx + pos_y;
		DrawLine(0, pos_y1, pos_x1, pos_y1, color_black);
		DrawLine(pos_x2, pos_y1, display_width, pos_y1, color_black);
		pos_x2 = dy + pos_x; pos_x1 = -dy + pos_x; pos_y1 = -dx + pos_y;
		DrawLine(0, pos_y1, pos_x1, pos_y1, color_black);
		DrawLine(pos_x2, pos_y1, display_width, pos_y1, color_black);

		dx--;
		F -= 4 * dx;
	}

	dy++;
	F += 4 * dy + 2;

	// �`���؂�܂Ń��[�v
	while (dx >= dy)
	{
		// ���C����`��
		pos_x2 = dx + pos_x; pos_x1 = -dx + pos_x; pos_y1 = dy + pos_y;
		DrawLine(0, pos_y1, pos_x1, pos_y1, color_black);
		DrawLine(pos_x2, pos_y1, display_width, pos_y1, color_black);
		pos_x2 = dx + pos_x; pos_x1 = -dx + pos_x; pos_y1 = -dy + pos_y;
		DrawLine(0, pos_y1, pos_x1, pos_y1, color_black);
		DrawLine(pos_x2, pos_y1, display_width, pos_y1, color_black);

		// ���W�f�[�^��i�߂�
		if (F >= 0)
		{
			pos_x2 = dy + pos_x; pos_x1 = -dy + pos_x; pos_y1 = dx + pos_y;
			DrawLine(0, pos_y1, pos_x1, pos_y1, color_black);
			DrawLine(pos_x2, pos_y1, display_width, pos_y1, color_black);
			pos_x2 = dy + pos_x; pos_x1 = -dy + pos_x; pos_y1 = -dx + pos_y;
			DrawLine(0, pos_y1, pos_x1, pos_y1, color_black);
			DrawLine(pos_x2, pos_y1, display_width, pos_y1, color_black);

			dx--;
			F -= 4 * dx;
		}

		dy++;
		F += 4 * dy + 2;
	}
}