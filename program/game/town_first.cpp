#include "Dxlib.h"
#include "town_first.h"
#include "fade_in.h"
#include "fade_out.h"
#include "player.h"
#include "../support/Support.h"
#include <random>

//�V�[���J�ڐ���ϐ�
extern int scene;
extern int pre_scene;

//�v���C���[�L����
extern player hero;

//�摜
extern int town_img;
extern int window_img;
extern int window_img2;
extern int heroine_window;
extern int cursor_right[3];
extern int heroine[12];

//�t�H���g�̃n���h��
extern int title_str;
extern int emp_str;
extern int subtitle_str;
extern int normal_str;
extern int window_str;
extern int window_emp_str;

//BGM
extern int char_select_bgm;

//���ʉ�
extern int decide_sound;
extern int select_sound;
extern int player_select_sound;
extern int heal_sound;

//�����֌W
extern std::mt19937 machine;
extern std::uniform_int_distribution<int> random_number;

//�J�[�\������̕ϐ�
extern int cursor_cnt;
int town_scene = 0;
extern int cursor;

//�A�j���[�V��������̕ϐ�
extern int heroine_cnt;
extern bool heroine_walk_flag;
extern int heal_cnt;
bool heal_flag = false;

//�q���C���̉񕜎����̉�
extern int heroine_heal_cnt;


void town_first(){

	//���ɓ���ۂ�fade_in
	if (pre_scene == 100) {
		fade_in_town(town_img);
		pre_scene = scene;
	}

	if (heroine_walk_flag) {
		heroine_cnt++;
	}
	else {
		heroine_cnt--;
	}

	if (heroine_cnt >= 49 || heroine_cnt <= 10) {
		heroine_walk_flag = !heroine_walk_flag;
	}

	switch (town_scene) {
	case 0:
		//����UI
		DrawGraph(0, 0, town_img, true);
		DrawGraph(0, 10, window_img, true);
		DrawGraph(710, 251, window_img2, true);
		DrawGraph(0, 580, heroine_window, true);
		DrawGraph(68, 628, heroine[heroine_cnt / 20], true);

		//���̗l�q��\�����̕\��
		DrawStringToHandle(130, 50, "�`���͑吨�̐l�œ�����Ă���c", 0xffffffff, window_str);
		//�I����e�̕\��
		DrawStringToHandle(780, 290, "�h��", 0xffffffff, window_str);
		DrawStringToHandle(780, 330, "����", 0xffffffff, window_str);
		DrawStringToHandle(780, 370, "�����o��", 0xffffffff, window_str);

		if (IsKeyDownTrigger(KEY_INPUT_UP)) {
			PlaySoundMem(player_select_sound, DX_PLAYTYPE_BACK);
			cursor -= 1;
		}

		if (IsKeyDownTrigger(KEY_INPUT_DOWN)) {
			PlaySoundMem(player_select_sound, DX_PLAYTYPE_BACK);
			cursor += 1;
		}

		if (cursor < 0) {
			cursor = 2;
		}

		if (cursor > 2) {
			cursor = 0;
		}

		if (cursor == 0) {
			DrawStringToHandle(160, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(170, 640, "�u�x�����Ƃ��ĉ񕜂����I", 0xffffffff, window_str);
			DrawStringToHandle(170, 680, "�@��ꂽ���͖������Ȃ��ŋx�����ˁv", 0xffffffff, window_str);
			DrawGraph(740, 290, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 1) {
			DrawStringToHandle(160, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(170, 640, "�u����ɂ���l��������b�𕷂����I", 0xffffffff, window_str);
			DrawStringToHandle(170, 680, "�@���ɗ����Ƃ������邩���c�v", 0xffffffff, window_str);
			DrawGraph(740, 330, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 2) {
			DrawStringToHandle(160, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(170, 640, "�u�`���ɏo�������I", 0xffffffff, window_str);
			DrawStringToHandle(170, 680, "�@�������߂Ċ撣�낤�ˁI�I�v", 0xffffffff, window_str);
			DrawGraph(740, 370, cursor_right[cursor_cnt / 12], true);
		}
		cursor_cnt++;
		if (cursor_cnt == 36) {
			cursor_cnt = 0;
		}

		if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
			town_scene = cursor+1;
			cursor = 0;
			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
		}
		break;
	case 1:
		//�h���ł̉񕜏���
		if (!heal_flag) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 254 - heal_cnt * 4);
			DrawGraph(0, 0, town_img, true);
			DrawGraph(0, 10, window_img, true);
			DrawGraph(710, 251, window_img2, true);
			DrawGraph(0, 580, heroine_window, true);
			DrawGraph(68, 628, heroine[heroine_cnt / 20], true);
			DrawStringToHandle(160, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(170, 640, "�u���₷�݂Ȃ����I�v", 0xffffffff, window_str);
			heal_cnt++;
			if (CheckSoundMem(heal_sound) == 0) {
				PlaySoundMem(heal_sound, DX_PLAYTYPE_BACK);
			}
			// �u�����h���[�h�����ɖ߂�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			if (heal_cnt == 64) {
				heal_cnt = 0;
				heal_flag = true;
			}
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, heal_cnt * 4);
			DrawGraph(0, 0, town_img, true);
			DrawGraph(0, 10, window_img, true);
			DrawGraph(710, 251, window_img2, true);
			DrawGraph(0, 580, heroine_window, true);
			DrawGraph(68, 628, heroine[heroine_cnt / 20], true);
			DrawStringToHandle(160, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(170, 640, "�u���͂悤�I�v", 0xffffffff, window_str);
			heal_cnt++;
			// �u�����h���[�h�����ɖ߂�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			if (heal_cnt == 64) {
				heal_cnt = 0;
				heal_flag = false;
				town_scene = 0;
				hero.hp_heal();
				heroine_heal_cnt = 3;
			}
		}
		break;
	case 2:
		break;
	case 3:
		//����UI
		DrawGraph(0, 0, town_img, true);
		DrawGraph(0, 10, window_img, true);
		DrawGraph(710, 251, window_img2, true);
		DrawGraph(0, 580, heroine_window, true);
		DrawGraph(68, 628, heroine[heroine_cnt / 20], true);
		town_scene = 0;
		//pre_scene = scene;
		fade_out_place();
		StopSoundMem(char_select_bgm);
		scene = 100;
		break;
	default:
		break;
	}
}