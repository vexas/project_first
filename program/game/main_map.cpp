#include "DxLib.h"
#include "main_map.h"
#include "draw_map.h"
#include "fade_in.h"
#include "fade_out.h"
#include "../support/Support.h"
#include <time.h>
#define _USE_MATH_DEFINES
#define MOVE_FRAME 10
#include <math.h>
#include "player.h"
#include <string.h>
#include <random>


// �Q�[���̏������t���O
extern int is_init;

// �V�[���𐧌䂷��ϐ�
// ���̕ϐ��̒l
// 0 : �^�C�g��
// 1 : �v���C���
// 2 : ���U���g���
extern int scene;
extern int pre_scene;

//�t�H���g�̃n���h��
extern int title_str;
extern int emp_str;
extern int subtitle_str;
extern int normal_str;
extern int window_str;
extern int window_emp_str;

// ��̉摜
extern int cursor_right[3];
extern int sword_img[20];
extern int shield_img[20];
extern int hammer_img[20];
extern int small_sword_img[20];
extern int small_shield_img[20];
extern int small_hammer_img[20];

//�w�i�̉摜
extern int field_img;
extern int window_img;
extern int hp_gauge;
extern int hp_gauge_edge;
extern int window_all;
extern int window_menu;
extern int heroine_window2;

//�G�t�F�N�g�̉摜
extern int attack_effect[5];
extern int break_effect[7];
extern int guard_effect[10];
extern int claw_effect[10];
extern int bite_effect[10];
extern int enemy_guard_effect[10];
extern int tale_effect[10];
extern int collide_effect[5];

//�}�b�v�ł̉��y
extern int main_map_bgm;

//���ʉ�
extern int slash_sound;
extern int collide_sound;
extern int damage_sound;
extern int break_sound;
extern int decide_sound;
extern int select_sound;
extern int encount_sound;
extern int player_select_sound;
extern int heal_sound;
extern int cancel_sound;

//HP�Q�[�W�̐F���Ǘ�����ϐ�
extern float hp_color_manager;
extern int enemy_hp_width;

// �J�[�\���̉摜
extern int gfx_cursor;

// �v���C��ʂł̃V�[�P���X�p�ϐ�
// 0 : �v���C���̎�I���V�[�P���X
// 1 : ���ʕ\��
extern int play_sequence;

// �v���C���[�̎�
// 0 : �O�[
// 1 : �`���L
// 2 : �p�[
extern int play_hand_player;

//�A�j���[�V��������̕ϐ�
extern int braver_idle_cnt;
extern int braver_attack_cnt;
extern int magician_idle_cnt;
extern int soldier_idle_cnt;
extern int archer_idle_cnt;
extern int cursor_cnt;
extern int attack_cnt;
extern int guard_cnt;
extern int break_cnt;
extern int effect_cnt;
extern int death_cnt;

//�v���C���[�̃L�����̎��
// 0�F�E��
// 1�F���@�g��
// 2�F�R�m
extern int player_character;

//�G�L�����̎��
// -1�F�{���ۂ���
// -2�F��p�t���ۂ���
// -3�F�h���S��
// -4�F����
// -5�F�������`��
extern int enemy_character;

//�v���C���[�N���X
extern player hero;
extern player enemy;

//�v���C���[�̉摜
extern int braver_attack_ready[10];
extern int braver_attack[10];
extern int braver_break[10];
extern int braver_guard[10];
extern int braver_jump[10];
extern int braver_damage[10];
extern int braver_down;
extern int braver_victory[10];
extern int braver_skill[10];
extern int braver_hp_1;
extern int braver_hp_2;
extern int magician_attack_ready[16];
extern int magician_hp_1;
extern int magician_hp_2;
extern int magician_attack[20];
extern int magician_break[25];
extern int magician_guard[15];
extern int magician_jump[20];
extern int magician_damage[15];
extern int magician_down;
extern int magician_victory[20];
extern int magician_magic[10];
extern int magician_skill[10];
extern int soldier_idle[30];
extern int soldier_hp_1;
extern int soldier_hp_2;
extern int soldier_attack[20];
extern int soldier_damage[20];
extern int soldier_down;
extern int soldier_victory[25];
extern int heroine[12];

//�G�̉摜
extern int bird_img;

// CPU �̎�
extern int play_hand_cpu;

// �W�����P����������
extern int turn_count;

// ��������
extern int play_win_count;

// ��������
extern int play_lose_count;

//��������
extern bool is_player_win;

//�t���O�Ǘ�
extern bool is_damage;
extern bool is_init_char;

//�}�b�v
extern int main_map_chip_number[3000];
extern int main_map_chip_above_number[3000];

//�}�b�v�`�b�v
extern int map_chip[160];

//�L�����N�^�[�̈ʒu
extern int player_pos_x;
extern int player_pos_y;

//�L�����N�^�[�̈ړ���
extern int scroll_x;
extern int scroll_y;

// �ړ����Ă��邩�ǂ����̃t���O( 0:��~��  1:�ړ��� )
extern bool is_move;
extern bool is_right;
extern bool is_walk;
int walk_cnt = 0;

// �e�����Ɉړ������
extern int move_x, move_y;

// �ړ����n�߂Ă��牽�t���[���o�߂�������ێ�����ϐ�
extern int move_cnt_frame;

//�v���C���[�̈ړ��O�̈ʒu���i�[����ϐ�
extern float moving_player_pos_x;
extern float moving_player_pos_y;

//�}�b�v�̓����蔻��
extern bool is_penetrate[160];

//�����֌W
extern std::mt19937 machine;
extern std::uniform_int_distribution<int> random_number;

//�G���J�E���g�̃t���O
bool is_encount = false;

//�q���C���̃A�j���[�V��������ϐ�
extern int heroine_cnt;
extern bool heroine_walk_flag;

//���j���[��ʂ̃J�[�\��
extern int cursor;

//�}�b�v���V�[���J�ڊǗ��ϐ�
int map_scene = 0;
bool is_heal = false;

//�q���C���̉񕜎����̉�
extern int heroine_heal_cnt;


void main_map() {

	switch (map_scene) {
	case 0:
		//�o�g����ʂ���J�ڂ��Ă����ꍇ��fade_in
		if (pre_scene == 1) {
			switch (player_character) {
			case 0:
				fade_in_alpha(scroll_x, scroll_y, main_map_chip_number, main_map_chip_above_number, player_character, braver_idle_cnt, is_right, is_walk);
				break;
			case 1:
				fade_in_alpha(scroll_x, scroll_y, main_map_chip_number, main_map_chip_above_number, player_character, magician_idle_cnt, is_right, is_walk);
				break;
			case 2:
				fade_in_alpha(scroll_x, scroll_y, main_map_chip_number, main_map_chip_above_number, player_character, soldier_idle_cnt, is_right, is_walk);
				break;
			default:
				break;
			}

			pre_scene = scene;
		}

		//���܂��̓_���W��������J�ڂ��Ă����ꍇ��fade_in
		//�n�܂�̒�����
		if (pre_scene == 110) {
			player_pos_x = 7;
			player_pos_y = 12;
			switch (player_character) {
			case 0:
				fade_in_dungeon(scroll_x, scroll_y, main_map_chip_number, main_map_chip_above_number, player_character, braver_idle_cnt, is_right, is_walk);
				break;
			case 1:
				fade_in_dungeon(scroll_x, scroll_y, main_map_chip_number, main_map_chip_above_number, player_character, magician_idle_cnt, is_right, is_walk);
				break;
			case 2:
				fade_in_dungeon(scroll_x, scroll_y, main_map_chip_number, main_map_chip_above_number, player_character, soldier_idle_cnt, is_right, is_walk);
				break;
			default:
				break;
			}

			pre_scene = scene;
		}

		// �ړ����ł͂Ȃ��ꍇ�L�[���͂��󂯕t����
		if (!is_move)
		{
			if (walk_cnt < 10) {
				walk_cnt++;
			}
			// �L�[���͂ɉ����ăv���C���[�̍��W���ړ�
			if (CheckHitKey(KEY_INPUT_LEFT))
			{
				is_move = true;
				move_x -= 1;
				if (move_x < -1) {
					move_x = -1;
				}
			}
			if (CheckHitKey(KEY_INPUT_RIGHT))
			{
				is_move = true;
				move_x += 1;
				if (move_x > 1) {
					move_x = 1;
				}
			}
			if (CheckHitKey(KEY_INPUT_UP))
			{
				is_move = true;
				move_y -= 1;
				if (move_y < -1) {
					move_y = -1;
				}
			}
			if (CheckHitKey(KEY_INPUT_DOWN))
			{
				is_move = true;
				move_y += 1;
				if (move_y > 1) {
					move_y = 1;
				}
			}

			if (is_move) {

				if (player_pos_x + move_x < 0 || player_pos_x + move_x > 59 ||
					player_pos_y + move_y < 0 || player_pos_y + move_y > 49) {
					is_move = false;
					move_x = 0;
					move_y = 0;
				}
				else if (main_map_chip_above_number[(player_pos_y + move_y) * 60 + (player_pos_x + move_x)] == -1) {
					if (!is_penetrate[main_map_chip_number[(player_pos_y + move_y) * 60 + (player_pos_x + move_x)]]) {
						is_move = false;
						move_x = 0;
						move_y = 0;
					}
					else {
						move_cnt_frame = 0;
					}
				}
				else if ((!is_penetrate[main_map_chip_above_number[(player_pos_y + move_y) * 60 + (player_pos_x + move_x)]] &&
					!is_penetrate[main_map_chip_number[(player_pos_y + move_y) * 60 + (player_pos_x + move_x)]]) ||
					!is_penetrate[main_map_chip_above_number[(player_pos_y + move_y) * 60 + (player_pos_x + move_x)]]) {
					is_move = false;
					move_x = 0;
					move_y = 0;
				}
				else {
					move_cnt_frame = 0;
				}
			}

			// ��~���͉�ʂ̃X�N���[���͍s��Ȃ�
			scroll_x = 0;
			scroll_y = 0;
		}

		// �ړ����̏ꍇ�͈ړ��������s��
		if (is_move)
		{
			is_walk = true;
			walk_cnt = 0;
			move_cnt_frame++;

			if (move_x == 1) {
				is_right = true;
			}
			else if (move_x == -1) {
				is_right = false;
			}

			// �ړ��������I���������~���ɂ���
			if (move_cnt_frame == MOVE_FRAME)
			{
				is_move = false;

				// �v���C���[�̈ʒu��ύX����
				player_pos_x += move_x;
				player_pos_y += move_y;
				move_x = 0;
				move_y = 0;

				//�����_���G���J�E���g�̔���
				if (random_number(machine) <= 5) {
					is_encount = true;
				}

				// ��~���͉�ʂ̃X�N���[���͍s��Ȃ�
				scroll_x = 0;
				scroll_y = 0;
			}
			else
			{
				// �o�ߎ��Ԃ���X�N���[���ʂ��Z�o����
				scroll_x = -(move_x * 32 * float(move_cnt_frame) / MOVE_FRAME);
				scroll_y = -(move_y * 32 * float(move_cnt_frame) / MOVE_FRAME);
			}
		}

		//�`�悳��Ȃ��̈�̕`��i�C�j
		//for (int i = 0; i < 32; i++) {
		//	for (int j = 0; j < 24; j++) {
		//		DrawGraph(i * 32, j * 32, map_chip[148], true);
		//	}
		//}

		if (walk_cnt == 10) {
			is_walk = false;
		}

		//draw_map(scroll_x, scroll_y, main_map_chip_number,0,braver_idle_cnt,is_right,is_walk);
		//draw_map(scroll_x, scroll_y, main_map_chip_above_number,0,braver_idle_cnt,is_right,is_walk);
		//�L�����N�^�[�ƃ}�b�v�̕`��
		switch (player_character) {
		case 0:
			draw_map(scroll_x, scroll_y, main_map_chip_number, player_character, braver_idle_cnt, is_right, is_walk);
			draw_map(scroll_x, scroll_y, main_map_chip_above_number, player_character, braver_idle_cnt, is_right, is_walk);
			braver_idle_cnt++;
			if (braver_idle_cnt == 70) {
				braver_idle_cnt = 0;
			}
			break;
		case 1:
			draw_map(scroll_x, scroll_y, main_map_chip_number, player_character, magician_idle_cnt, is_right, is_walk);
			draw_map(scroll_x, scroll_y, main_map_chip_above_number, player_character, magician_idle_cnt, is_right, is_walk);
			magician_idle_cnt++;
			if (magician_idle_cnt == 70) {
				magician_idle_cnt = 0;
			}
			break;
		case 2:
			draw_map(scroll_x, scroll_y, main_map_chip_number, player_character, soldier_idle_cnt, is_right, is_walk);
			draw_map(scroll_x, scroll_y, main_map_chip_above_number, player_character, soldier_idle_cnt, is_right, is_walk);
			soldier_idle_cnt++;
			if (soldier_idle_cnt == 72) {
				soldier_idle_cnt = 0;
			}
			break;
		default:
			break;
		}

		//���܂��̓_���W�����ɓ�������G���J�E���g�������s�킸�V�[���J��

		//�n�܂�̒�
		if ((player_pos_x == 6 && player_pos_y == 11) || (player_pos_x == 7 && player_pos_y == 11)) {
			pre_scene = scene;
			StopSoundMem(main_map_bgm);
			scene = 110;
			is_encount = false;
			switch (player_character) {
			case 0:
				braver_idle_cnt = 0;
				break;
			case 1:
				magician_idle_cnt = 0;
				break;
			case 2:
				soldier_idle_cnt = 0;
				break;
			default:
				break;
			}
			fade_out_place();
		}

		if (is_encount) {
			pre_scene = scene;
			scene = 1;
			is_encount = false;
			StopSoundMem(main_map_bgm);
			enemy_character = -((random_number(machine) % 3) + 1);
			PlaySoundMem(encount_sound, DX_PLAYTYPE_BACK);
			fade_out_alpha();
			switch (player_character) {
			case 0:
				braver_idle_cnt = 0;
				break;
			case 1:
				magician_idle_cnt = 0;
				break;
			case 2:
				soldier_idle_cnt = 0;
				break;
			default:
				break;
			}
		}


		//X�������ꂽ�烁�j���[��ʁi�G���J�E���g���Ă��炸���ȂǂɃV�[���J�ڂ��Ă��Ȃ���ԁj
		if (!is_encount && scene != 110 && IsKeyDownTrigger(KEY_INPUT_X)) {
			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
			map_scene = 1;
		}

		break;
	case 1:

		//�w�i�̕`��
		DrawGraph(0, 0, field_img, true);
		DrawGraph(0, -15, window_all, true);

		//�q���C���̕`��i�������j
		DrawGraph(50, 580, heroine_window2, true);
		DrawGraph(108, 628, heroine[heroine_cnt / 20], true);

		if (heroine_walk_flag) {
			heroine_cnt++;
		}
		else {
			heroine_cnt--;
		}

		if (heroine_cnt >= 49 || heroine_cnt <= 10) {
			heroine_walk_flag = !heroine_walk_flag;
		}

		//X�������ꂽ�烁�j���[��ʂ����
		if (IsKeyDownTrigger(KEY_INPUT_X)) {
			PlaySoundMem(cancel_sound, DX_PLAYTYPE_BACK);
			map_scene = 0;
		}

		DrawGraph(670, 50, window_menu, true);

		//�I����e�̕\��
		DrawStringToHandle(740, 90, "�b��", 0xffffffff, window_str);
		DrawStringToHandle(740, 150, "��", 0xffffffff, window_str);
		DrawStringToHandle(740, 210, "����", 0xffffffff, window_str);
		DrawStringToHandle(740, 270, "�Z�[�u", 0xffffffff, window_str);
		DrawStringToHandle(740, 330, "���[�h", 0xffffffff, window_str);
		DrawStringToHandle(740, 390, "�^�C�g��", 0xffffffff, window_str);

		switch (player_character) {
		case 0:
			DrawGraph(200, 150, braver_skill[9], true);
			break;
		case 1:
			DrawGraph(200, 150, magician_skill[9], true);
			break;
		case 2:
			DrawTurnGraph(200, 150, soldier_attack[1], true);
			break;
		default:
			break;
		}
		DrawFormatStringToHandle(200, 130, 0xffffffff, window_emp_str, "%s", hero.player_name().c_str());
		DrawFormatStringToHandle(250, 410, 0xffffffff, window_emp_str, "Level %d", hero.player_level());
		DrawFormatStringToHandle(250, 460, 0xffffffff, window_emp_str, "Hp %d/%d", hero.player_hp(), hero.player_hp_max());

		if (IsKeyDownTrigger(KEY_INPUT_UP)) {
			PlaySoundMem(player_select_sound, DX_PLAYTYPE_BACK);
			cursor -= 1;
		}

		if (IsKeyDownTrigger(KEY_INPUT_DOWN)) {
			PlaySoundMem(player_select_sound, DX_PLAYTYPE_BACK);
			cursor += 1;
		}

		if (cursor < 0) {
			cursor = 5;
		}

		if (cursor > 5) {
			cursor = 0;
		}

		if (cursor == 0) {
			DrawStringToHandle(210, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "�u���ƎG�k���悤�I�v", 0xffffffff, window_str);
			DrawGraph(700, 90, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 1) {
			DrawStringToHandle(210, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "�u���̎����ŉ񕜂����I�v", 0xffffffff, window_str);
			DrawGraph(700, 150, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 2) {
			DrawStringToHandle(210, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "�u���Ȃ��̋������m�F�����I�v", 0xffffffff, window_str);
			DrawGraph(700, 210, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 3) {
			DrawStringToHandle(210, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "�u�`�����L�^�����I�v", 0xffffffff, window_str);
			DrawGraph(700, 270, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 4) {
			DrawStringToHandle(210, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "�u�`���̋L�^��ǂݍ��ނ�I�v", 0xffffffff, window_str);
			DrawGraph(700, 330, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 5) {
			DrawStringToHandle(210, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "�u�`�����I�������I", 0xffffffff, window_str);
			DrawStringToHandle(220, 680, "�@�Z�[�u��Y��Ȃ��łˁI�v", 0xffffffff, window_str);
			DrawGraph(700, 390, cursor_right[cursor_cnt / 12], true);
		}


		cursor_cnt++;
		if (cursor_cnt == 36) {
			cursor_cnt = 0;
		}

		if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
			map_scene = cursor + 2;
			cursor = 0;
			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
		}

		break;
	case 2:
		//�b���R�}���h

		//�w�i�̕`��
		DrawGraph(0, 0, field_img, true);
		DrawGraph(0, -15, window_all, true);

		//�q���C���̕`��i�������j
		DrawGraph(50, 580, heroine_window2, true);
		DrawGraph(108, 628, heroine[heroine_cnt / 20], true);

		if (heroine_walk_flag) {
			heroine_cnt++;
		}
		else {
			heroine_cnt--;
		}

		if (heroine_cnt >= 49 || heroine_cnt <= 10) {
			heroine_walk_flag = !heroine_walk_flag;
		}

		DrawStringToHandle(210, 600, "�q���C��", 0xffffffff, window_str);
		DrawStringToHandle(220, 640, "�u�Ă��ƁI�v", 0xffffffff, window_str);

		if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
			map_scene = 1;
		}
		break;
	case 3:
		//�񕜃R�}���h
		//�w�i�̕`��
		DrawGraph(0, 0, field_img, true);
		DrawGraph(0, -15, window_all, true);

		//�q���C���̕`��i�������j
		DrawGraph(50, 580, heroine_window2, true);
		DrawGraph(108, 628, heroine[heroine_cnt / 20], true);

		if (heroine_walk_flag) {
			heroine_cnt++;
		}
		else {
			heroine_cnt--;
		}

		if (heroine_cnt >= 49 || heroine_cnt <= 10) {
			heroine_walk_flag = !heroine_walk_flag;
		}

		if (!is_heal) {

			if (heroine_heal_cnt > 0) {

				DrawGraph(670, 50, window_menu, true);

				//�I����e�̕\��
				DrawStringToHandle(740, 90, "�͂�", 0xffffffff, window_str);
				DrawStringToHandle(740, 150, "������", 0xffffffff, window_str);

				if (IsKeyDownTrigger(KEY_INPUT_UP)) {
					PlaySoundMem(player_select_sound, DX_PLAYTYPE_BACK);
					cursor -= 1;
				}

				if (IsKeyDownTrigger(KEY_INPUT_DOWN)) {
					PlaySoundMem(player_select_sound, DX_PLAYTYPE_BACK);
					cursor += 1;
				}

				if (cursor < 0) {
					cursor = 1;
				}

				if (cursor > 1) {
					cursor = 0;
				}

				DrawStringToHandle(210, 600, "�q���C��", 0xffffffff, window_str);
				DrawFormatStringToHandle(220, 640, 0xffffffff, window_str, "�u��%d�񏥂����邯��", heroine_heal_cnt);
				DrawStringToHandle(220, 680, "�@�񕜂���H�v", 0xffffffff, window_str);

				if (cursor == 0) {
					DrawGraph(700, 90, cursor_right[cursor_cnt / 12], true);
				}
				if (cursor == 1) {
					DrawGraph(700, 150, cursor_right[cursor_cnt / 12], true);
				}

				cursor_cnt++;
				if (cursor_cnt == 36) {
					cursor_cnt = 0;
				}

				if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
					if (cursor == 0) {
						hero.hp_heal();
						heroine_heal_cnt--;
						is_heal = true;
						PlaySoundMem(heal_sound, DX_PLAYTYPE_BACK);
					}
					else {
						PlaySoundMem(cancel_sound, DX_PLAYTYPE_BACK);
						cursor = 0;
						map_scene = 1;
					}
				}
			}
			else {
				DrawStringToHandle(210, 600, "�q���C��", 0xffffffff, window_str);
				DrawFormatStringToHandle(220, 640, 0xffffffff, window_str, "�u�������͂��c���ĂȂ���", heroine_heal_cnt);
				DrawStringToHandle(220, 680, "�@���߂�ˁc�v", 0xffffffff, window_str);

				if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
					map_scene = 1;
				}

			}
		}
		else {
			DrawStringToHandle(210, 600, "�q���C��", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "�u�񕜂�����I�I�v", 0xffffffff, window_str);

			if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
				is_heal = false;
				map_scene = 1;
			}

		}

		break;
	case 4:
		//�����R�}���h
		DrawGraph(0, 0, field_img, true);
		DrawGraph(0, -15, window_all, true);

		DrawStringToHandle(170, 50, "Status", 0x00000000, emp_str);

		DrawFormatStringToHandle(550, 200, 0xffffffff, window_emp_str, "Level %d", hero.player_level());
		DrawFormatStringToHandle(550, 280, 0xffffffff, window_emp_str, "Hp %d/%d", hero.player_hp(), hero.player_hp_max());
		DrawFormatStringToHandle(550, 330, 0xffffffff, window_emp_str, "Bre %d", hero.break_attack());
		DrawFormatStringToHandle(550, 380, 0xffffffff, window_emp_str, "Spd %d", hero.speed_attack());
		DrawFormatStringToHandle(550, 430, 0xffffffff, window_emp_str, "Def %d", hero.guard_attack());

		DrawFormatStringToHandle(200, 200, 0xffffffff, window_emp_str, "%s", hero.player_name().c_str());
		DrawFormatStringToHandle(150, 530, 0xffffffff, window_emp_str, "EXP %d", hero.player_exp());
		DrawFormatStringToHandle(150, 580, 0xffffffff, window_emp_str, "���̃��x���܂� %d", hero.player_next_exp());

		switch (player_character) {
		case 0:
			DrawGraph(150, 190, braver_skill[9], true);
			break;
		case 1:
			DrawGraph(150, 190, magician_skill[9], true);
			break;
		case 2:
			DrawTurnGraph(150, 190, soldier_attack[1], true);
			break;
		default:
			break;
		}

		if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
			map_scene = 1;
		}

		break;
	case 5:
		//�Z�[�u�R�}���h
		break;
	case 6:
		//���[�h�R�}���h
		break;
	case 7:
		//�^�C�g���R�}���h
		break;
	default:
		break;
	}
}