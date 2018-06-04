#include "DxLib.h"
#include "../support/Support.h"
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "player.h"
#include "fade_in.h"
#include "fade_out.h"
#include <string>
#include <random>


// �Q�[���̏������t���O
extern int is_init ;

// �V�[���𐧌䂷��ϐ�
// ���̕ϐ��̒l
// 0 : �^�C�g��
// 1 : �v���C���
// 2 : ���U���g���
extern int scene ;
extern int pre_scene;

//�t�H���g�̃n���h��
extern int title_str;
extern int emp_str;
extern int subtitle_str;
extern int normal_str;
extern int window_str;
extern int window_emp_str;

// ��̉摜
extern int gfx_rock ;
extern int gfx_scissors ;
extern int gfx_paper ;
extern int sword_img[20];
extern int shield_img[20];
extern int hammer_img[20];
extern int small_sword_img[20];
extern int small_shield_img[20];
extern int small_hammer_img[20];

//�w�i�̉摜
extern int field_img;
extern int window_img;
extern int window_all;
extern int heroine_window;
extern int heroine_window3;
extern int hp_gauge;
extern int hp_gauge_edge;
extern int cut_in_img;

//�G�t�F�N�g�̉摜
extern int attack_effect[5];
extern int break_effect[7];
extern int guard_effect[10];
extern int claw_effect[10];
extern int bite_effect[10];
extern int enemy_guard_effect[10];
extern int tale_effect[10];
extern int collide_effect[5];
extern int braver_skill_effect[10];
extern int magician_skill_effect[10];
extern int heal_effect[8];

//���ʉ�
extern int slash_sound;
extern int collide_sound;
extern int damage_sound;
extern int break_sound;
extern int decide_sound;
extern int select_sound;
extern int braver_skill_sound;
extern int magician_attack_sound;
extern int magician_break_sound;
extern int magician_skill_sound;
extern int soldier_skill_sound;
extern int skill_start_sound;
extern int enemy_dead_sound;
extern int level_up_sound;
extern int heal_sound;
extern int escape_sound;

//HP�Q�[�W�̐F���Ǘ�����ϐ�
extern float hp_color_manager;
extern int enemy_hp_width;

// �J�[�\���̉摜
extern int gfx_cursor ;

// �v���C��ʂł̃V�[�P���X�p�ϐ�
// 0 : �v���C���̎�I���V�[�P���X
// 1 : ���ʕ\��
extern int play_sequence ;

// �v���C���[�̎�
// 0 : �O�[
// 1 : �`���L
// 2 : �p�[
extern int play_hand_player ;

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
extern int cut_in_cnt;
extern int heal_cnt;

//�v���C���[�̃L�����̎��
// 0�F�E��
// 1�F���@�g��
// 2�F�R�m
extern int player_character;

//�v���C���[�N���X
extern player hero;
extern player enemy;

//�v���C���[�̉摜
extern int braver_run[10];
extern int braver_walk[15];
extern int braver_attack_ready[10];
extern int braver_attack[10];
extern int braver_break[10];
extern int braver_guard[10];
extern int braver_jump[10];
extern int braver_damage[10];
extern int braver_down;
extern int braver_victory[10];
extern int braver_skill[10];
extern int braver_charge[10];
extern int braver_hp_1;
extern int braver_hp_2;
extern int braver_cut_in;
extern int magician_attack_ready[16];
extern int magician_run[10];
extern int magician_walk[15];
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
extern int magician_charge[10];
extern int magician_cut_in;
extern int soldier_idle[30];
extern int soldier_walk[25];
extern int soldier_hp_1;
extern int soldier_hp_2;
extern int soldier_attack[20];
extern int soldier_damage[20];
extern int soldier_down;
extern int soldier_victory[25];
extern int soldier_charge;
extern int soldier_cut_in;
extern int heroine[12];
extern int heroine_battle[12];

//�G�̉摜
extern int enemy1_img;
extern int enemy2_img;
extern int enemy3_img;

// CPU �̎�
extern int play_hand_cpu ;

// �W�����P����������
extern int turn_count ;

// ��������
extern int play_win_count ;

// ��������
extern int play_lose_count ;

//��������
extern bool is_player_win;

//�t���O�Ǘ�
extern bool is_damage;
extern bool is_init_char;
extern bool is_init_battle;

// ���f�t�H���g�͂������ɂ��Ă���
int win_or_lose_or_drow = 2;
bool is_battle;

//���y
extern int battle1_bgm;
extern int battle_victory_bgm;

//�o���l�l�������ɗp����ϐ�
int exp_counter = 0;
int gain_total_exp = 0;
int gain_exp = 0;
int next_exp = 0;
bool is_levelup = false;
bool is_levelup_sound = false;
extern std::mt19937 machine;
extern std::uniform_int_distribution<int> random_level_up;

//�G�̎�����߂邽�߂̕ϐ�
extern std::uniform_int_distribution<int> random_number;
bool is_enemy_hand_decided = false;

//�q���C������ǂ݂ł��邩�ǂ����̔���
bool is_heroine_see_enemy = false;

//�q���C���̉񕜎����̉�
extern int heroine_heal_cnt;

//�񕜏����ɗp����ϐ�
bool is_healed = false;
int heal_point = 0;

//�q���C���̖��O
extern std::string heroine_name;

void scene_play(int enemy_number) {

	if (!is_init_battle) {
		switch (enemy_number) {
		case -1:
			fade_in_circle(field_img, enemy1_img);
			break;
		case -2:
			fade_in_circle(field_img, enemy2_img);
			break;
		case -3:
			fade_in_circle(field_img, enemy3_img);
			break;
		default:
			break;
		}
		play_sequence = 2;
		is_battle = true;
		is_init_battle = true;
		//�A�j���[�V�����Ǘ��ϐ��̏�����
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

	DrawGraph(0, 0, field_img, true);

	if (!is_init_char) {
		enemy.set_parameter(enemy_number);
		is_init_char = true;
	}

	if (CheckSoundMem(battle1_bgm) == 0 && death_cnt < 64) {
		PlaySoundMem(battle1_bgm, DX_PLAYTYPE_LOOP);
	}



	//----------------------------------------------------------------------------------------------------
	// �v���C��ʂł̃V�[�P���X����
	switch (play_sequence) {

		// ��I�����
	case 0:

		DrawGraph(0, 10, window_img, true);

		// �� �����������̏���
		if (IsKeyDownTrigger(KEY_INPUT_LEFT)) {
			play_hand_player -= 1;
			PlaySoundMem(select_sound, DX_PLAYTYPE_BACK);
		}

		// �� �����������̏���
		if (IsKeyDownTrigger(KEY_INPUT_RIGHT)) {
			play_hand_player += 1;
			PlaySoundMem(select_sound, DX_PLAYTYPE_BACK);
		}

		// ������ 0 ��菬�����Ȃ��Ă��܂����� 0 �ɂ���
		if (play_hand_player < 0) {
			play_hand_player = 2;
		}

		// ������ 2 ���傫���Ȃ��Ă��܂����� 2 �ɂ���
		if (play_hand_player > 2) {
			play_hand_player = 0;
		}


		// �G���^�[�����������̏���
		if (IsKeyDownTrigger(KEY_INPUT_RETURN) && is_enemy_hand_decided) {

			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);

			// �W�����P���������񐔂𑝂₷
			turn_count++;

			// ���s��������ď������񐔂ƕ������񐔂��J�E���g����
			// CPU �̎肪�O�[�̎�
			if (0 == play_hand_cpu) {
				if (1 == play_hand_player) {
					play_lose_count += 1;
				}
				if (2 == play_hand_player) {
					play_win_count += 1;
				}
			}

			// CPU �̎肪�`���L�̎�
			if (1 == play_hand_cpu) {
				if (2 == play_hand_player) {
					play_lose_count += 1;
				}
				if (0 == play_hand_player) {
					play_win_count += 1;
				}
			}

			// CPU �̎肪�p�[�̎�
			if (2 == play_hand_cpu) {
				if (0 == play_hand_player) {
					play_lose_count += 1;
				}
				if (1 == play_hand_player) {
					play_win_count += 1;
				}
			}

			//�A�j���[�V�����Ǘ��ϐ��̏�����
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

			//�e��̃J�E���g
			switch (play_hand_player) {
			case 0:
				hero.break_increment();
				break;
			case 1:
				hero.attack_increment();
				break;
			case 2:
				hero.guard_increment();
				break;
			default:
				break;
			}

			// �^�[���̌��ʂւƐi�߂�
			play_sequence = 1;

		}

		if (IsKeyDownTrigger(KEY_INPUT_LSHIFT)) {
			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
			play_sequence = 6;
		}

		if (IsKeyDownTrigger(KEY_INPUT_S) && hero.is_skill()) {
			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
			turn_count++;
			play_hand_player = 4;
			play_sequence = 1;
		}

		if (IsKeyDownTrigger(KEY_INPUT_A)) {
			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
			play_sequence = 4;
		}

		if (IsKeyDownTrigger(KEY_INPUT_D)) {
			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
			if (random_number(machine) <= 50) {
				//�A�j���[�V�����Ǘ��ϐ��̏�����
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
				PlaySoundMem(escape_sound, DX_PLAYTYPE_BACK);
				play_sequence = 5;
				play_hand_player = 0;
			}
			else {
				turn_count++;
				play_hand_player = 5;
				play_sequence = 1;
			}
		}

		//�v���C���[�L�����̕`��
		switch (player_character) {
		case 0:
			if (hero.is_skill()) {
				DrawGraph(580, 400, braver_charge[braver_idle_cnt / 6], true);
				braver_idle_cnt++;
				if (braver_idle_cnt == 42) {
					braver_idle_cnt = 0;
				}
			}
			else {
				DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
				braver_idle_cnt++;
				if (braver_idle_cnt == 42) {
					braver_idle_cnt = 0;
				}
			}
			break;

		case 1:
			if (hero.is_skill()) {
				if (magician_idle_cnt >= 42) {
					magician_idle_cnt = 0;
				}
				DrawGraph(580, 400, magician_charge[magician_idle_cnt / 6], true);
				magician_idle_cnt++;
				if (magician_idle_cnt == 42) {
					magician_idle_cnt = 0;
				}
			}
			else {
				DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
				magician_idle_cnt++;
				if (magician_idle_cnt == 70) {
					magician_idle_cnt = 0;
				}
			}
			break;

		case 2:
			if (hero.is_skill()) {
				DrawGraph(580, 385, soldier_charge, true);
				DrawTurnGraph(580, 385, soldier_attack[0], true);
			}
			else {
				DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
				soldier_idle_cnt++;
				if (soldier_idle_cnt == 145) {
					soldier_idle_cnt = 0;
				}
			}
			break;
		default:
			break;
		}

		//�v���C���[��HP�Q�[�W
		if (hero.player_hp_percentage() > 30) {
			switch (player_character) {
			case 0:
				DrawGraph(770, 480, braver_hp_1, true);
				break;
			case 1:
				DrawGraph(770, 480, magician_hp_1, true);
				break;
			case 2:
				DrawTurnGraph(770, 480, soldier_hp_1, true);
				break;
			default:
				break;
			}
		}
		else {
			switch (player_character) {
			case 0:
				DrawGraph(785, 475, braver_hp_2, true);
				break;
			case 1:
				DrawGraph(785, 475, magician_hp_2, true);
				break;
			case 2:
				DrawTurnGraph(760, 470, soldier_hp_2, true);
				break;
			default:
				break;
			}
		}

		DrawCircleGauge(890, 575, 100, hp_gauge_edge, 0);
		hp_color_manager = hero.player_hp_percentage() * 1.2f;
		GraphFilter(hp_gauge, DX_GRAPH_FILTER_HSB, 1, int(hp_color_manager), 0, 0);
		DrawCircleGauge(890, 575, hero.player_hp_percentage(), hp_gauge, 0);
		//�v���C���[��HP�̊�����\���iDebug�p�j
		//DrawStringEx(100, 100, 0x00000000, "%d", hero.player_hp_percentage());

		//�G�L�����̕`��
		switch (enemy_number) {
		case -1:
			DrawGraph(50, 200, enemy1_img, true);
			DrawBox(180, 360, 390, 400, GetColor(0, 0, 0), true);
			if (enemy.player_hp_percentage() <= 50) {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
			}
			else {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
			}
			break;
		case -2:
			DrawGraph(50, 200, enemy2_img, true);
			DrawBox(180, 360, 390, 400, GetColor(0, 0, 0), true);
			if (enemy.player_hp_percentage() <= 50) {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
			}
			else {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
			}
			break;
		case -3:
			DrawGraph(50, 200, enemy3_img, true);
			DrawBox(180, 240, 390, 280, GetColor(0, 0, 0), true);
			if (enemy.player_hp_percentage() <= 50) {
				DrawBox(185, 245, 185 + enemy.player_hp_percentage() * 2, 275, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
			}
			else {
				DrawBox(185, 245, 185 + enemy.player_hp_percentage() * 2, 275, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
			}
			break;
		default:
			break;
		}

		// CPU �̎������I�ɑI������
		// 0 ���� 2 �܂ł̗������擾
		//play_hand_cpu = rand() % 3;
		if (!is_enemy_hand_decided) {
			play_hand_cpu = enemy.enemy_hand_decided(random_number(machine));
			is_enemy_hand_decided = true;
			if (random_number(machine) <= 15) {
				is_heroine_see_enemy = true;
			}
		}

		//�q���C���Ɋւ���`��
		DrawGraph(607, 186, heroine_window3, true);
		DrawGraph(627, 216, heroine_battle[1], true);
		if (is_heroine_see_enemy) {
			if (play_hand_cpu == 0) {
				DrawGraph(760, 195, small_hammer_img[0], true);
			}
			else if (play_hand_cpu == 1) {
				DrawGraph(760, 195, small_sword_img[0], true);
			}
			else {
				DrawGraph(760, 195, small_shield_img[0], true);
			}
			DrawStringToHandle(710, 230, "���́@�@����I�I", 0xffffffff, window_str);
		}
		else {
			DrawStringToHandle(680, 210, "(�G�̗l�q��", 0xffffffff, window_str);
			DrawStringToHandle(680, 250, " ���������Ă���c)", 0xffffffff, window_str);
		}

		// �n���}�[�A���A���̕`��
		if (play_hand_player == 0) {
			DrawGraph(635, 300, hammer_img[break_cnt / 5], true);
			DrawGraph(790, 400, small_sword_img[0], true);
			attack_cnt = -1;
			DrawGraph(580, 400, small_shield_img[0], true);
			guard_cnt = -1;
			DrawStringToHandle(150, 40, "Break", 0xffffffff, window_emp_str);
			DrawStringToHandle(250, 90, "Guard��ł��j��{���̈ꌂ�I�I", 0xffffffff, window_str);
			DrawStringToHandle(250, 130, "Speed Attack�ɂ��j�~����Ă��܂��c", 0xffffffff, window_str);
		}
		else if (play_hand_player == 1) {
			DrawGraph(635, 300, sword_img[attack_cnt / 5], true);
			DrawGraph(580, 400, small_hammer_img[0], true);
			break_cnt = -1;
			DrawGraph(790, 400, small_shield_img[0], true);
			guard_cnt = -1;
			DrawStringToHandle(150, 40, "Speed", 0xffffffff, window_emp_str);
			DrawStringToHandle(250, 90, "Power Attack��j�~���鎾���̈ꌂ�I�I", 0xffffffff, window_str);
			DrawStringToHandle(250, 130, "Guard�ɂ�蔽������Ă��܂��c", 0xffffffff, window_str);
		}
		else if (play_hand_player == 2) {
			DrawGraph(635, 300, shield_img[guard_cnt / 5], true);
			DrawGraph(790, 400, small_hammer_img[0], true);
			break_cnt = -1;
			DrawGraph(580, 400, small_sword_img[0], true);
			attack_cnt = -1;
			DrawStringToHandle(150, 40, "Guard", 0xffffffff, window_emp_str);
			DrawStringToHandle(250, 90, "Speed Attack���󂯎~�ߔ����I�I", 0xffffffff, window_str);
			DrawStringToHandle(250, 130, "Power Attack�̑O�ɂ͖��́c", 0xffffffff, window_str);
		}
		break_cnt++;
		attack_cnt++;
		guard_cnt++;

		if (attack_cnt == 100) {
			attack_cnt = 0;
		}
		if (break_cnt == 100) {
			break_cnt = 0;
		}
		if (guard_cnt == 100) {
			guard_cnt = 0;
		}

		// �����̕`��
		DrawFormatStringToHandle(30, 200, 0x00000000, window_emp_str,"%d Turn",turn_count + 1);
		DrawFormatStringToHandle(540, 660, 0x00000000, normal_str, "���L�[�����L�[�ōs����I���I�I", turn_count + 1);
		DrawStringToHandle(590, 710, "Enter�L�[�ōs��������I�I", 0x00000000, normal_str);

		//�萔�̕`��
		DrawRotaGraph(40, 730, 0.5, 0, hammer_img[0], true, false);
		DrawFormatStringToHandle(70, 710, 0x00000000, emp_str, "�~%d", hero.break_count());
		DrawRotaGraph(200, 730, 0.5, 0, sword_img[0], true, false);
		DrawFormatStringToHandle(230, 710, 0x00000000, emp_str, "�~%d", hero.attack_count());
		DrawRotaGraph(360, 730, 0.5, 0, shield_img[0], true, false);
		DrawFormatStringToHandle(390, 710, 0x00000000, emp_str, "�~%d", hero.guard_count());

		break;

		//----------------------------------------------------------------------------------------------------
		// ���ʕ\�����
	case 1:

		// �P��P�ʂł̏������������������������̕ϐ�
		// 0 : ����
		// 1 : ����
		// 2 : ������
		DrawGraph(0, 10, window_img, true);

		//�G�L�����̕`��
		if (enemy.player_hp() <= 0) {
			if (death_cnt == 0) {
				PlaySoundMem(enemy_dead_sound, DX_PLAYTYPE_BACK);
			}
			if (death_cnt == 60) {
				StopSoundMem(enemy_dead_sound);
			}
			if (death_cnt % 2 == 0) {
				switch (enemy_number) {
				case -1:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 4 * death_cnt);
					DrawGraph(55, 200, enemy1_img, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				case -2:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 4 * death_cnt);
					DrawGraph(55, 200, enemy2_img, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				case -3:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 4 * death_cnt);
					DrawGraph(55, 200, enemy3_img, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				default:
					break;
				}
			}
			else {
				switch (enemy_number) {
				case -1:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 4 * death_cnt);
					DrawGraph(45, 200, enemy1_img, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				case -2:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 4 * death_cnt);
					DrawGraph(45, 200, enemy2_img, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				case -3:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 4 * death_cnt);
					DrawGraph(45, 200, enemy3_img, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				default:
					break;
				}
			}
			death_cnt ++;
		}
		else{
			switch (enemy_number) {
			case -1:
				DrawGraph(50, 200, enemy1_img, true);
				break;
			case -2:
				DrawGraph(50, 200, enemy2_img, true);
				break;
			case -3:
				DrawGraph(50, 200, enemy3_img, true);
				break;
			default:
				break;
			}
		}
		if (enemy.player_hp() > 0) {
			switch (enemy_number) {
			case -1:
				DrawBox(180, 360, 390, 400, GetColor(0, 0, 0), true);
				if (enemy.player_hp_percentage() <= 50) {
					if (enemy.player_hp() > 0) {
						DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
					}
				}
				else {
					DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
				}
				break;
			case -2:
				DrawBox(180, 360, 390, 400, GetColor(0, 0, 0), true);
				if (enemy.player_hp_percentage() <= 50) {
					if (enemy.player_hp() > 0) {
						DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
					}
				}
				else {
					DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
				}
				break;
			case -3:
				DrawBox(180, 240, 390, 280, GetColor(0, 0, 0), true);
				if (enemy.player_hp_percentage() <= 50) {
					DrawBox(185, 245, 185 + enemy.player_hp_percentage() * 2, 275, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
				}
				else {
					DrawBox(185, 245, 185 + enemy.player_hp_percentage() * 2, 275, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
				}
				break;
			}
		}


		// CPU �̎肪�n���}�[�̎�
		if (0 == play_hand_cpu) {

			if (1 == play_hand_player) {
				/*if (!is_damage) {
					enemy.damage(hero.player_attack());
					is_damage = true;

				}
				*/

				switch (player_character) {
				case 0:
					//�E��speed attack --> �Gpower attack
					if (braver_attack_cnt < 18) {
						DrawGraph(580 - int(braver_attack_cnt / 18.0f * 300), 400, braver_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 18 && braver_attack_cnt < 53) {
						if (!is_damage) {
							enemy.damage(hero.speed_attack());
							is_damage = true;

						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(),hero.speed_attack());
						DrawGraph(280 + int((braver_attack_cnt - 18) / 35.0f * 225), 400, braver_jump[(braver_attack_cnt - 18) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.speed_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							is_battle = false;
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 95) {
								death_cnt = 64;
							}
						}
					}

					//�E��speed attack --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 35 && braver_attack_cnt > 8) {
						if (braver_attack_cnt == 12) {
							PlaySoundMem(slash_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(170, 410, attack_effect[effect_cnt / 7], true);
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g��speed attack --> �Gpower attack
					if (braver_attack_cnt < 32) {
						DrawGraph(580 - int(braver_attack_cnt / 32.0f * 300), 400 - int(100 * sin(braver_attack_cnt / 32.0f * M_PI)), magician_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 32 && braver_attack_cnt < 58) {
						if (!is_damage) {
							enemy.damage(hero.speed_attack());
							is_damage = true;

						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.speed_attack());
						DrawGraph(280 + int((braver_attack_cnt - 32) / 26.0f * 225), 400, magician_jump[(braver_attack_cnt - 32) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.speed_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}

					//���@�g��speed attack --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 35 && braver_attack_cnt > 15) {
						if (braver_attack_cnt == 20) {
							PlaySoundMem(magician_attack_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(170, 410, attack_effect[effect_cnt / 7], true);
						effect_cnt++;
					}
					break;
				case 2:
					//�R�mspeed attack --> �Gpower attack
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580 - int(braver_attack_cnt / 20.0f * 300), 385, soldier_attack[braver_attack_cnt], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						if (!is_damage) {
							enemy.damage(hero.speed_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.speed_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 20) / 40.0f * 300), 385 - int(50 * sin((braver_attack_cnt - 20) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 12) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.speed_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//�R�mspeed attack --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 35 && braver_attack_cnt > 15) {
						if (braver_attack_cnt == 20) {
							PlaySoundMem(slash_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(170, 410, attack_effect[effect_cnt / 7], true);
						effect_cnt++;
					}
					break;
				default:
					break;
				}

				win_or_lose_or_drow = 0;
			}

			if (2 == play_hand_player) {
				/*if (!is_damage) {
					hero.damage(enemy.player_attack());
					is_damage = true;
				}
				*/
				switch (player_character) {
				case 0:
					//�E��guard --> �Gpower attack
					if (braver_attack_cnt < 21) {
						DrawGraph(580, 400, braver_guard[braver_attack_cnt / 3], true);
						DrawGraph(580, 450, guard_effect[braver_attack_cnt / 6], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 21 && braver_attack_cnt < 49) {
						if (!is_damage) {
							hero.damage(enemy.break_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						DrawGraph(580, 400, braver_damage[(braver_attack_cnt - 21) / 4], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawGraph(580, 400, braver_down, true);
						}
					}

					//�E��guard --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 56 && braver_attack_cnt > 15) {
						DrawGraph(620, 440, bite_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 25) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g��guard --> �Gpower attack
					if (braver_attack_cnt < 28) {
						DrawGraph(580, 400, magician_guard[braver_attack_cnt / 2], true);
						DrawGraph(580, 450, guard_effect[braver_attack_cnt / 6], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 28 && braver_attack_cnt < 64) {
						if (!is_damage) {
							hero.damage(enemy.break_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						DrawGraph(580, 400, magician_damage[(braver_attack_cnt - 28) / 3], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawGraph(580, 400, magician_down, true);
						}
					}

					//���@�g��guard --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 56 && braver_attack_cnt > 21) {
						DrawGraph(620, 440, bite_effect[effect_cnt / 7], true);
						if (effect_cnt < 45 && effect_cnt > 9) {
							if (braver_attack_cnt == 42) {
								PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
							}
						}
						effect_cnt++;
					}
					break;
				case 2:
					//�R�mguard --> �Gpower attack
					if (braver_attack_cnt < 28) {
						DrawTurnGraph(580, 385, soldier_attack[0], true);
						DrawGraph(580, 450, guard_effect[braver_attack_cnt / 6], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 28 && braver_attack_cnt < 68) {
						if (!is_damage) {
							hero.damage(enemy.break_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						DrawTurnGraph(580, 385, soldier_damage[(braver_attack_cnt - 28) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawTurnGraph(580, 385, soldier_down, true);
						}
					}

					//�R�mguard --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 56 && braver_attack_cnt > 21) {
						DrawGraph(620, 440, bite_effect[effect_cnt / 7], true);
						if (effect_cnt < 45 && effect_cnt > 9) {
							if (braver_attack_cnt == 42) {
								PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
							}
						}
						effect_cnt++;
					}
					break;
				default:
					break;
				}
				win_or_lose_or_drow = 1;
			}

			if (play_hand_cpu == play_hand_player) {
				switch (player_character) {
				case 0:
					//�E��power attack --> �Gpower attack
					if (braver_attack_cnt < 18) {
						DrawGraph(580 - int(braver_attack_cnt / 18.0f * 200), 400, braver_break[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 18 && braver_attack_cnt < 53) {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						DrawGraph(380 + int((braver_attack_cnt - 18) / 35.0f * 125), 400, braver_jump[(braver_attack_cnt - 18) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						is_battle = false;
						DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
						braver_idle_cnt++;
						if (braver_idle_cnt == 42) {
							braver_idle_cnt = 0;
						}
					}

					//�E��power attack --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 56) {
						DrawGraph(400, 410, bite_effect[effect_cnt / 7], true);
						if (effect_cnt < 45 && effect_cnt > 9) {
							if (braver_attack_cnt == 15) {
								PlaySoundMem(collide_sound, DX_PLAYTYPE_BACK);
							}
							DrawGraph(400, 410, collide_effect[(effect_cnt - 10) / 7], true);
						}
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g��power attack --> �Gpower attack
					if (braver_attack_cnt < 50) {
						DrawGraph(580, 400, magician_break[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						is_battle = false;
						DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
						magician_idle_cnt++;
						if (magician_idle_cnt == 70) {
							magician_idle_cnt = 0;
						}
					}

					//���@�g��power attack --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 56) {
						DrawGraph(400, 410, bite_effect[effect_cnt / 7], true);
						if (effect_cnt < 45 && effect_cnt > 9) {
							if (braver_attack_cnt == 30) {
								PlaySoundMem(collide_sound, DX_PLAYTYPE_BACK);
							}
							DrawGraph(360, 380, magician_magic[(effect_cnt - 10) / 4], true);
							DrawGraph(400, 410, collide_effect[(effect_cnt - 10) / 7], true);
						}
						effect_cnt++;
					}
					break;
				case 2:
					//�R�mpower attack --> �Gpower attack
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580 - int(braver_attack_cnt / 20.0f * 200), 385, soldier_attack[braver_attack_cnt], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						DrawTurnGraph(380 + int((braver_attack_cnt - 20) / 40.0f * 200), 385 - int(50 * sin((braver_attack_cnt - 20) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 12) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						is_battle = false;
						DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
						soldier_idle_cnt++;
						if (soldier_idle_cnt == 145) {
							soldier_idle_cnt = 0;
						}
					}

					//�R�mpower attack --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 56) {
						DrawGraph(400, 410, bite_effect[effect_cnt / 7], true);
						if (effect_cnt < 45 && effect_cnt > 9) {
							if (braver_attack_cnt == 20) {
								PlaySoundMem(collide_sound, DX_PLAYTYPE_BACK);
							}
							DrawGraph(400, 410, collide_effect[(effect_cnt - 10) / 7], true);
						}
						effect_cnt++;
					}
					break;
				default:
					break;
				}
				win_or_lose_or_drow = 2;
			}

			if (play_hand_player == 4) {
				/*if (!is_damage) {
					enemy.damage(hero.skill_attack());
					hero.break_decrement();
					hero.attack_decrement();
					hero.guard_decrement();
					is_damage = true;
				}
				*/
				switch (player_character) {
				case 0:
					//�E��skill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͗͂���������I�I", hero.player_name().c_str());
						DrawGraph(580, 400, braver_skill[braver_attack_cnt/5], true);
						if (cut_in_cnt <= -65) {
							braver_attack_cnt++;
						}
					}else if (braver_attack_cnt >= 50 && braver_attack_cnt < 77) {
						DrawRotaGraph(740 - int((braver_attack_cnt - 50) / 27.0f * 280), 560 - int(200 * sin((braver_attack_cnt - 50) / 27.0f * M_PI)), 1.0, -((braver_attack_cnt - 50) / 27.0f) * M_PI * 2.0f, braver_break[(braver_attack_cnt - 50) / 3], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 77 && braver_attack_cnt < 119) {
						if (!is_damage) {
							enemy.damage(hero.skill_attack());
							hero.break_decrement();
							hero.attack_decrement();
							hero.guard_decrement();
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃}�[�x���u���[�h�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^���A%d�����͂�D�����I", enemy.player_name().c_str(), 2 * hero.speed_attack(), hero.speed_attack());
						DrawGraph(280 + int((braver_attack_cnt - 77) / 35.0f * 225), 400, braver_jump[(braver_attack_cnt - 77) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃}�[�x���u���[�h�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^���A%d�����͂�D�����I", enemy.player_name().c_str(), 2 * hero.speed_attack(),hero.speed_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 91) {
								death_cnt = 64;
							}
						}
					}
					//�E��skill�@�G�t�F�N�g
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 70) {
							PlaySoundMem(braver_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//�E��skill�@�J�b�g�C��
					if (cut_in_cnt > -65) {
						if (cut_in_cnt == -5) {
							PlaySoundMem(skill_start_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(30 * cut_in_cnt, 284, cut_in_img, true);
						cut_in_cnt--;
						DrawGraph(272, 200, braver_cut_in, true);
					}
					break;
				case 1:
					//���@�g��skill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͗͂���������I�I", hero.player_name().c_str());
						DrawGraph(580, 400, magician_skill[braver_attack_cnt / 5], true);
						if (cut_in_cnt <= -65) {
							braver_attack_cnt++;
						}
					}
					else if (braver_attack_cnt < 100) {
						if (!is_damage) {
							enemy.damage(hero.skill_attack());
							hero.break_decrement();
							hero.attack_decrement();
							hero.guard_decrement();
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃T���_�[�{���g�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						DrawGraph(580, 400, magician_break[(braver_attack_cnt-50) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃T���_�[�{���g�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}
					//���@�g��skill�@�G�t�F�N�g
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 80) {
							PlaySoundMem(magician_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, magician_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//���@�g��skill�@�J�b�g�C��
					if (cut_in_cnt > -65) {
						if (cut_in_cnt == -5) {
							PlaySoundMem(skill_start_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(30 * cut_in_cnt, 284, cut_in_img, true);
						cut_in_cnt--;
						DrawGraph(272, 184, magician_cut_in, true);
					}
					break;
				case 2:
					//�R�mskill
					if (braver_attack_cnt < 30) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͗͂���������I�I", hero.player_name().c_str());
						DrawTurnGraph(580, 385, soldier_attack[0], true);
						if (cut_in_cnt <= -65) {
							braver_attack_cnt++;
						}
					}
					else if (braver_attack_cnt < 50) {
						DrawRotaGraph(740 - int((braver_attack_cnt - 30) / 20.0f * 280), 545 - int(200 * sin((braver_attack_cnt - 30) / 20.0f * M_PI)), 1.0, -((braver_attack_cnt - 30) / 20.0f) * M_PI * 2.0f, soldier_attack[braver_attack_cnt - 30], true, true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 50 && braver_attack_cnt < 90) {
						if (!is_damage) {
							enemy.damage(hero.skill_attack());
							hero.break_decrement();
							hero.attack_decrement();
							hero.guard_decrement();
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃��x���W�X���b�V���I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 50) / 40.0f * 300), 385 - int(50 * sin((braver_attack_cnt - 50) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 42) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃��x���W�X���b�V���I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//�R�mskill�@�G�t�F�N�g
					if (effect_cnt < 70 && braver_attack_cnt > 25) {
						if (braver_attack_cnt == 35) {
							PlaySoundMem(soldier_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//�R�mskill�@�J�b�g�C��
					if (cut_in_cnt > -65) {
						if (cut_in_cnt == -5) {
							PlaySoundMem(skill_start_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(30 * cut_in_cnt, 284, cut_in_img, true);
						cut_in_cnt--;
						DrawTurnGraph(302, 239, soldier_cut_in, true);
					}

					break;
				default:
					break;
				}
			}

			if (play_hand_player == 5) {
				switch (player_character) {
				case 0:
					//�E�ғ��� --> �Gpower attack
					if (braver_attack_cnt < 42) {
						DrawGraph(580, 400, braver_attack_ready[braver_attack_cnt / 6], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�����͓����o�����I", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "��������荞�܂�Ă��܂����I�I", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 42 && braver_attack_cnt < 70) {
						if (!is_damage) {
							hero.damage(enemy.break_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						DrawGraph(580, 400, braver_damage[(braver_attack_cnt - 42) / 4], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawGraph(580, 400, braver_down, true);
						}
					}

					//�E�ғ��� --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 56 && braver_attack_cnt > 35) {
						DrawGraph(620, 440, bite_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 45) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g������ --> �Gpower attack
					if (braver_attack_cnt < 44) {
						DrawGraph(580, 400, magician_attack_ready[braver_attack_cnt / 4], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�����͓����o�����I", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "��������荞�܂�Ă��܂����I�I", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 44 && braver_attack_cnt < 80) {
						if (!is_damage) {
							hero.damage(enemy.break_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						DrawGraph(580, 400, magician_damage[(braver_attack_cnt - 44) / 3], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawGraph(580, 400, magician_down, true);
						}
					}

					//���@�g������ --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 56 && braver_attack_cnt > 35) {
						DrawGraph(620, 440, bite_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 50) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 2:
					//�R�m���� --> �Gpower attack
					if (braver_attack_cnt < 42) {
						DrawTurnGraph(580, 385, soldier_idle[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�����͓����o�����I", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "��������荞�܂�Ă��܂����I�I", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 42 && braver_attack_cnt < 82) {
						if (!is_damage) {
							hero.damage(enemy.break_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						DrawTurnGraph(580, 385, soldier_damage[(braver_attack_cnt - 42) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawTurnGraph(580, 385, soldier_down, true);
						}
					}

					//�R�mguard --> �Gpower attack�@�G�t�F�N�g
					if (effect_cnt < 56 && braver_attack_cnt > 35) {
						DrawGraph(620, 440, bite_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 50) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				default:
					break;
				}
			}

		}

		// CPU �̎肪���̎�
		if (1 == play_hand_cpu) {

			if (2 == play_hand_player) {
				/*if (!is_damage) {
					enemy.damage(hero.player_attack());
					is_damage = true;
				}
				*/
				switch (player_character) {
				case 0:
					//�E��guard --> �Gspeed attack
					if (braver_attack_cnt < 21) {
						DrawGraph(580, 400, braver_guard[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 21 && braver_attack_cnt < 39) {
						if (!is_damage) {
							enemy.damage(hero.guard_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s��%s�̍U�����󂯗������������I", hero.player_name().c_str(),enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.guard_attack());
						DrawGraph(580, 400, braver_break[(braver_attack_cnt - 21) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s��%s�̍U�����󂯗������������I", hero.player_name().c_str(), enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.guard_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 95) {
								death_cnt = 64;
							}
						}
					}

					//�E��guard --> �Gspeed attack�@�G�t�F�N�g
					if (braver_attack_cnt < 21) {
						DrawGraph(580, 450, guard_effect[braver_attack_cnt / 6], true);
					}
					if (effect_cnt < 39 && braver_attack_cnt > 3) {
						DrawGraph(600, 440, claw_effect[effect_cnt / 7], true);
						if (effect_cnt < 39 && effect_cnt > 9) {
							if (braver_attack_cnt == 20) {
								PlaySoundMem(collide_sound, DX_PLAYTYPE_BACK);
							}
						}
						effect_cnt++;
					}

					if (braver_attack_cnt >= 21 && braver_attack_cnt < 56) {
						if (braver_attack_cnt == 31) {
							PlaySoundMem(slash_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(170, 410, attack_effect[(braver_attack_cnt - 21) / 7], true);
						if (braver_attack_cnt >= 39) {
							braver_attack_cnt++;
						}
					}

					break;
				case 1:
					//���@�g��guard --> �Gspeed attack
					if (braver_attack_cnt < 28) {
						DrawGraph(580, 400, magician_guard[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 28 && braver_attack_cnt < 78) {
						if (!is_damage) {
							enemy.damage(hero.guard_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s��%s�̍U�����󂯗������������I", hero.player_name().c_str(), enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.guard_attack());
						DrawGraph(580, 400, magician_break[(braver_attack_cnt - 28) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s��%s�̍U�����󂯗������������I", hero.player_name().c_str(), enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.guard_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}

					//���@�g��guard --> �Gspeed attack�@�G�t�F�N�g
					if (braver_attack_cnt < 21) {
						DrawGraph(580, 450, guard_effect[braver_attack_cnt / 6], true);
					}
					if (effect_cnt < 39 && braver_attack_cnt > 3) {
						DrawGraph(600, 440, claw_effect[effect_cnt / 7], true);
						if (effect_cnt < 39 && effect_cnt > 9) {
							if (braver_attack_cnt == 20) {
								PlaySoundMem(collide_sound, DX_PLAYTYPE_BACK);
							}
						}
						effect_cnt++;
					}

					if (braver_attack_cnt >= 28 && braver_attack_cnt < 78) {
						if (braver_attack_cnt == 43) {
							PlaySoundMem(magician_break_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(140, 370, magician_magic[(braver_attack_cnt - 28) / 5], true);
					}
					break;
				case 2:
					//�R�mguard --> �Gspeed attack
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580, 385, soldier_attack[0], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 40) {
						if (!is_damage) {
							enemy.damage(hero.guard_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s��%s�̍U�����󂯗������������I", hero.player_name().c_str(), enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.guard_attack());
						DrawTurnGraph(580, 385, soldier_attack[braver_attack_cnt - 20], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s��%s�̍U�����󂯗������������I", hero.player_name().c_str(), enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.guard_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//�R�mguard --> �Gspeed attack�@�G�t�F�N�g
					if (braver_attack_cnt < 20) {
						DrawGraph(580, 450, guard_effect[braver_attack_cnt / 6], true);
					}
					if (effect_cnt < 39 && braver_attack_cnt > 3) {
						DrawGraph(600, 440, claw_effect[effect_cnt / 7], true);
						if (effect_cnt < 39 && effect_cnt > 9) {
							if (braver_attack_cnt == 20) {
								PlaySoundMem(collide_sound, DX_PLAYTYPE_BACK);
							}
						}
						effect_cnt++;
					}

					if (braver_attack_cnt >= 20 && braver_attack_cnt < 56) {
						if (braver_attack_cnt == 30) {
							PlaySoundMem(slash_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(170, 410, attack_effect[(braver_attack_cnt - 20) / 7], true);
						if (braver_attack_cnt >= 40) {
							braver_attack_cnt++;
						}
					}
					break;
				default:
					break;
				}
				win_or_lose_or_drow = 0;
			}

			if (0 == play_hand_player) {
				/*if (!is_damage) {
					hero.damage(enemy.player_attack());
					is_damage = true;
				}
				*/
				switch (player_character) {
				case 0:
					//�E��power attack --> �Gspeed attack
					if (braver_attack_cnt < 15) {
						DrawGraph(580, 400, braver_break[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 15 && braver_attack_cnt < 43) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						DrawGraph(580, 400, braver_damage[(braver_attack_cnt - 15) / 4], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawGraph(580, 400, braver_down, true);
						}
					}

					//�E��power attack --> �Gspeed attack�@�G�t�F�N�g
					if (effect_cnt < 56) {
						DrawGraph(620, 440, claw_effect[effect_cnt / 7], true);
						if (effect_cnt < 45 && effect_cnt > 9) {
							if (braver_attack_cnt == 20) {
								PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
							}
						}
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g��power attack --> �Gspeed attack
					if (braver_attack_cnt < 30) {
						DrawGraph(580, 400, magician_break[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 30 && braver_attack_cnt < 66) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						DrawGraph(580, 400, magician_damage[(braver_attack_cnt - 30) / 3], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawGraph(580, 400, magician_down, true);
						}
					}

					//���@�g��power attack --> �Gspeed attack�@�G�t�F�N�g
					if (effect_cnt < 56 && braver_attack_cnt > 16) {
						DrawGraph(620, 440, claw_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 20) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 2:
					//�R�mpower attack --> �Gspeed attack
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580, 385, soldier_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						DrawTurnGraph(580, 385, soldier_damage[(braver_attack_cnt - 20) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawTurnGraph(580, 385, soldier_down, true);
						}
					}

					//�R�mpower attack --> �Gspeed attack�@�G�t�F�N�g
					if (effect_cnt < 56) {
						DrawGraph(620, 440, claw_effect[effect_cnt / 7], true);
						if (effect_cnt < 45 && effect_cnt > 9) {
							if (braver_attack_cnt == 20) {
								PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
							}
						}
						effect_cnt++;
					}
					break;
				default:
					break;
				}
				win_or_lose_or_drow = 1;
			}

			if (play_hand_cpu == play_hand_player) {
				switch (player_character) {
				case 0:
					//�E��speed attack --> �Gspeed attack 
					if (braver_attack_cnt < 18) {
						DrawGraph(580 - int(braver_attack_cnt / 18.0f * 200), 400, braver_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 18 && braver_attack_cnt < 53) {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						DrawGraph(380 + int((braver_attack_cnt - 18) / 35.0f * 125), 400, braver_jump[(braver_attack_cnt - 18) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						is_battle = false;
						DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
						braver_idle_cnt++;
						if (braver_idle_cnt == 42) {
							braver_idle_cnt = 0;
						}
					}

					//�E��speed attack --> �Gspeed attack�@�G�t�F�N�g
					if (effect_cnt < 56) {
						DrawGraph(400, 410, claw_effect[effect_cnt / 7], true);
						if (effect_cnt < 45 && effect_cnt > 9) {
							if (braver_attack_cnt == 15) {
								PlaySoundMem(collide_sound, DX_PLAYTYPE_BACK);
							}
							DrawGraph(400, 410, collide_effect[(effect_cnt - 10) / 7], true);
						}
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g��speed attack --> �Gspeed attack 
					if (braver_attack_cnt < 32) {
						DrawGraph(580 - int(braver_attack_cnt / 32.0f * 200), 400, magician_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 32 && braver_attack_cnt < 58) {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						DrawGraph(380 + int((braver_attack_cnt - 32) / 26.0f * 125), 400, magician_jump[(braver_attack_cnt - 32) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						is_battle = false;
						DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
						magician_idle_cnt++;
						if (magician_idle_cnt == 70) {
							magician_idle_cnt = 0;
						}
					}

					//���@�g��speed attack --> �Gspeed attack�@�G�t�F�N�g
					if (effect_cnt < 56) {
						DrawGraph(400, 410, claw_effect[effect_cnt / 7], true);
						if (effect_cnt < 45 && effect_cnt > 9) {
							if (braver_attack_cnt == 20) {
								PlaySoundMem(collide_sound, DX_PLAYTYPE_BACK);
							}
							DrawGraph(400, 410, collide_effect[(effect_cnt - 10) / 7], true);
						}
						effect_cnt++;
					}
					break;
				case 2:
					//�R�mspeed attack --> �Gspeed attack 
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580 - int(braver_attack_cnt / 20.0f * 200), 385, soldier_attack[braver_attack_cnt], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						DrawTurnGraph(380 + int((braver_attack_cnt - 20) / 40.0f * 200), 385 - int(50 * sin((braver_attack_cnt - 20) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 12) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��̋���Ȉꌂ���Ԃ��荇���I");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "�U�������E���ꂽ�I");
						is_battle = false;
						DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
						soldier_idle_cnt++;
						if (soldier_idle_cnt == 145) {
							soldier_idle_cnt = 0;
						}
					}

					//�R�mspeed attack --> �Gspeed attack�@�G�t�F�N�g
					if (effect_cnt < 56) {
						DrawGraph(400, 410, claw_effect[effect_cnt / 7], true);
						if (effect_cnt < 45 && effect_cnt > 9) {
							if (braver_attack_cnt == 20) {
								PlaySoundMem(collide_sound, DX_PLAYTYPE_BACK);
							}
							DrawGraph(400, 410, collide_effect[(effect_cnt - 10) / 7], true);
						}
						effect_cnt++;
					}
					break;
				default:
					break;
				}
				win_or_lose_or_drow = 2;
			}

			if (play_hand_player == 4) {
				/*if (!is_damage) {
				enemy.damage(hero.skill_attack());
				hero.break_decrement();
				hero.attack_decrement();
				hero.guard_decrement();
				is_damage = true;
				}
				*/
				switch (player_character) {
				case 0:
					//�E��skill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͗͂���������I�I", hero.player_name().c_str());
						DrawGraph(580, 400, braver_skill[braver_attack_cnt / 5], true);
						if (cut_in_cnt <= -65) {
							braver_attack_cnt++;
						}
					}
					else if (braver_attack_cnt >= 50 && braver_attack_cnt < 77) {
						DrawRotaGraph(740 - int((braver_attack_cnt - 50) / 27.0f * 280), 560 - int(200 * sin((braver_attack_cnt - 50) / 27.0f * M_PI)), 1.0, -((braver_attack_cnt - 50) / 27.0f) * M_PI * 2.0f, braver_break[(braver_attack_cnt - 50) / 3], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 77 && braver_attack_cnt < 119) {
						if (!is_damage) {
							enemy.damage(hero.skill_attack());
							hero.break_decrement();
							hero.attack_decrement();
							hero.guard_decrement();
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃}�[�x���u���[�h�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^���A%d�����͂�D�����I", enemy.player_name().c_str(), 2 * hero.speed_attack(), hero.speed_attack());
						DrawGraph(280 + int((braver_attack_cnt - 77) / 35.0f * 225), 400, braver_jump[(braver_attack_cnt - 77) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃}�[�x���u���[�h�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^���A%d�����͂�D�����I", enemy.player_name().c_str(), 2 * hero.speed_attack(), hero.speed_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 91) {
								death_cnt = 64;
							}
						}
					}
					//�E��skill�@�G�t�F�N�g
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 70) {
							PlaySoundMem(braver_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//�E��skill�@�J�b�g�C��
					if (cut_in_cnt > -65) {
						if (cut_in_cnt == -5) {
							PlaySoundMem(skill_start_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(30 * cut_in_cnt, 284, cut_in_img, true);
						cut_in_cnt--;
						DrawGraph(272, 200, braver_cut_in, true);
					}
					break;
				case 1:
					//���@�g��skill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͗͂���������I�I", hero.player_name().c_str());
						DrawGraph(580, 400, magician_skill[braver_attack_cnt / 5], true);
						if (cut_in_cnt <= -65) {
							braver_attack_cnt++;
						}
					}
					else if (braver_attack_cnt < 100) {
						if (!is_damage) {
							enemy.damage(hero.skill_attack());
							hero.break_decrement();
							hero.attack_decrement();
							hero.guard_decrement();
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃T���_�[�{���g�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						DrawGraph(580, 400, magician_break[(braver_attack_cnt - 50) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃T���_�[�{���g�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}
					//���@�g��skill�@�G�t�F�N�g
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 80) {
							PlaySoundMem(magician_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, magician_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//���@�g��skill�@�J�b�g�C��
					if (cut_in_cnt > -65) {
						if (cut_in_cnt == -5) {
							PlaySoundMem(skill_start_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(30 * cut_in_cnt, 284, cut_in_img, true);
						cut_in_cnt--;
						DrawGraph(272, 184, magician_cut_in, true);
					}
					break;
				case 2:
					//�R�mskill
					if (braver_attack_cnt < 30) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͗͂���������I�I", hero.player_name().c_str());
						DrawTurnGraph(580, 385, soldier_attack[0], true);
						if (cut_in_cnt <= -65) {
							braver_attack_cnt++;
						}
					}
					else if (braver_attack_cnt < 50) {
						DrawRotaGraph(740 - int((braver_attack_cnt - 30) / 20.0f * 280), 545 - int(200 * sin((braver_attack_cnt - 30) / 20.0f * M_PI)), 1.0, -((braver_attack_cnt - 30) / 20.0f) * M_PI * 2.0f, soldier_attack[braver_attack_cnt - 30], true, true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 50 && braver_attack_cnt < 90) {
						if (!is_damage) {
							enemy.damage(hero.skill_attack());
							hero.break_decrement();
							hero.attack_decrement();
							hero.guard_decrement();
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃��x���W�X���b�V���I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 50) / 40.0f * 300), 385 - int(50 * sin((braver_attack_cnt - 50) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 42) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃��x���W�X���b�V���I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//�R�mskill�@�G�t�F�N�g
					if (effect_cnt < 70 && braver_attack_cnt > 25) {
						if (braver_attack_cnt == 35) {
							PlaySoundMem(soldier_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//�R�mskill�@�J�b�g�C��
					if (cut_in_cnt > -65) {
						if (cut_in_cnt == -5) {
							PlaySoundMem(skill_start_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(30 * cut_in_cnt, 284, cut_in_img, true);
						cut_in_cnt--;
						DrawTurnGraph(302, 239, soldier_cut_in, true);
					}

					break;
				default:
					break;
				}
			}

			if (play_hand_player == 5) {
				switch (player_character) {
				case 0:
					//�E�ғ��� --> �Gspeed attack
					if (braver_attack_cnt < 42) {
						DrawGraph(580, 400, braver_attack_ready[braver_attack_cnt / 6], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�����͓����o�����I", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "��������荞�܂�Ă��܂����I�I", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 42 && braver_attack_cnt < 70) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						DrawGraph(580, 400, braver_damage[(braver_attack_cnt - 42) / 4], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawGraph(580, 400, braver_down, true);
						}
					}

					//�E�ғ��� --> �Gspeed attack�@�G�t�F�N�g
					if (effect_cnt < 56 && braver_attack_cnt > 35) {
						DrawGraph(620, 440, claw_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 45) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g������ --> �Gspeed attack
					if (braver_attack_cnt < 44) {
						DrawGraph(580, 400, magician_attack_ready[braver_attack_cnt / 4], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�����͓����o�����I", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "��������荞�܂�Ă��܂����I�I", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 44 && braver_attack_cnt < 80) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						DrawGraph(580, 400, magician_damage[(braver_attack_cnt - 44) / 3], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawGraph(580, 400, magician_down, true);
						}
					}

					//���@�g������ --> �Gspeed attack�@�G�t�F�N�g
					if (effect_cnt < 56 && braver_attack_cnt > 35) {
						DrawGraph(620, 440, claw_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 45) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 2:
					//�R�m���� --> �Gspeed attack
					if (braver_attack_cnt < 42) {
						DrawTurnGraph(580, 385, soldier_idle[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�����͓����o�����I", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "��������荞�܂�Ă��܂����I�I", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 42 && braver_attack_cnt < 82) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						DrawTurnGraph(580, 385, soldier_damage[(braver_attack_cnt - 42) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̑f�����ꌂ�I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawTurnGraph(580, 385, soldier_down, true);
						}
					}

					//�R�m���� --> �Gspeed attack�@�G�t�F�N�g
					if (effect_cnt < 56 && braver_attack_cnt > 35) {
						DrawGraph(620, 440, claw_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 45) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				default:
					break;
				}
			}

		}

		// CPU �̎肪���̎�
		if (2 == play_hand_cpu) {

			if (0 == play_hand_player) {
				/*if (!is_damage) {
					enemy.damage(hero.player_attack());
					is_damage = true;
				}
				*/
				switch (player_character) {
				case 0:
					//�E��power attack --> �Gguard
					if (braver_attack_cnt < 27) {
						//DrawRotaGraph(580 - int(braver_attack_cnt / 27.0f * 280), 400 - int(50 * sin(braver_attack_cnt / 27.0f * M_PI)), 1.0, -(braver_attack_cnt / 26.0f) * M_PI * 2.0f, braver_break[braver_attack_cnt / 3], true);
						//DrawRotaGraph(580 - int(braver_attack_cnt / 27.0f * 280), 400, 1.0, -(braver_attack_cnt / 26.0f) * M_PI * 2.0f, braver_break[braver_attack_cnt / 3], true);
						DrawGraph(580 - int(braver_attack_cnt / 27.0f * 300), 400 - int(150 * sin(braver_attack_cnt / 27.0f * M_PI)), braver_break[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 27 && braver_attack_cnt < 62) {
						if (!is_damage) {
							enemy.damage(hero.break_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.break_attack());
						DrawGraph(280 + int((braver_attack_cnt - 27) / 35.0f * 225), 400, braver_jump[(braver_attack_cnt - 27) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.break_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 91) {
								death_cnt = 64;
							}
						}
					}

					//�E��power attack --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 49 && braver_attack_cnt > 15) {
						if (braver_attack_cnt == 20) {
							PlaySoundMem(break_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(170, 410, break_effect[effect_cnt / 7], true);
						effect_cnt++;
					}
					else if(effect_cnt < 49){
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g��power attack --> �Gguard
					if (braver_attack_cnt < 50) {
						DrawGraph(580, 400, magician_break[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.break_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}

					//���@�g��power attack --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 50 && braver_attack_cnt > 15) {
						if (braver_attack_cnt == 20) {
							if (!is_damage) {
								enemy.damage(hero.break_attack());
								is_damage = true;
							}
							PlaySoundMem(magician_break_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(140, 370, magician_magic[effect_cnt / 5], true);
						effect_cnt++;
					}
					else if (effect_cnt < 49) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}

					break;
				case 2:
					//�R�mpower attack --> �Gguard
					if (braver_attack_cnt < 20) {
						//DrawRotaGraph(580 - int(braver_attack_cnt / 27.0f * 280), 400 - int(50 * sin(braver_attack_cnt / 27.0f * M_PI)), 1.0, -(braver_attack_cnt / 26.0f) * M_PI * 2.0f, braver_break[braver_attack_cnt / 3], true);
						//DrawRotaGraph(580 - int(braver_attack_cnt / 27.0f * 280), 400, 1.0, -(braver_attack_cnt / 26.0f) * M_PI * 2.0f, braver_break[braver_attack_cnt / 3], true);
						DrawTurnGraph(580 - int(braver_attack_cnt / 20.0f * 300), 385 - int(150 * sin(braver_attack_cnt / 20.0f * M_PI)), soldier_attack[braver_attack_cnt], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						if (!is_damage) {
							enemy.damage(hero.break_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.break_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 20) / 40.0f * 300), 385 - int(50 * sin((braver_attack_cnt - 20) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 12) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̋���Ȉꌂ�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.break_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//�R�mpower attack --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 49 && braver_attack_cnt > 15) {
						if (braver_attack_cnt == 20) {
							PlaySoundMem(break_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(170, 410, break_effect[effect_cnt / 7], true);
						effect_cnt++;
					}
					else if (effect_cnt < 49) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				default:
					break;
				}
				win_or_lose_or_drow = 0;
			}

			if (1 == play_hand_player) {
				/*if (!is_damage) {
					hero.damage(enemy.player_attack());
					is_damage = true;
				}
				*/
				switch (player_character) {
				case 0:
					//�E��speed attack --> �Gguard
					if (braver_attack_cnt < 27) {
						DrawGraph(580 - int(braver_attack_cnt / 27.0f * 300), 400, braver_attack[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 27 && braver_attack_cnt < 55) {
						if (!is_damage) {
							hero.damage(enemy.guard_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͔������Ă����I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.guard_attack());
						DrawGraph(280 + int((braver_attack_cnt - 27) / 28.0f * 300), 400, braver_damage[(braver_attack_cnt - 27) / 4], true);
						braver_attack_cnt++;
					}
					else {						
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͔������Ă����I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.guard_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawGraph(580, 400, braver_down, true);
						}
					}

					//�E��speed attack --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						if (braver_attack_cnt == 20) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g��speed attack --> �Gguard
					if (braver_attack_cnt < 32) {
						DrawGraph(580 - int(braver_attack_cnt / 32.0f * 300), 400 - int(100 * sin(braver_attack_cnt / 32.0f * M_PI)), magician_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 32 && braver_attack_cnt < 68) {
						if (!is_damage) {
							hero.damage(enemy.guard_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͔������Ă����I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.guard_attack());
						DrawGraph(280 + int((braver_attack_cnt - 32) / 36.0f * 300), 400, magician_damage[(braver_attack_cnt - 32) / 3], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͔������Ă����I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.guard_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawGraph(580, 400, magician_down, true);
						}
					}

					//���@�g��speed attack --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						if (braver_attack_cnt == 20) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 2:
					//�R�mspeed attack --> �Gguard
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580 - int(braver_attack_cnt / 20.0f * 300), 385, soldier_attack[braver_attack_cnt], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						if (!is_damage) {
							hero.damage(enemy.guard_attack());
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͔������Ă����I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.guard_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 20) / 40.0f * 310), 385, soldier_damage[(braver_attack_cnt - 20) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͔������Ă����I", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W���󂯂��I", hero.player_name().c_str(), enemy.guard_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�s�k�\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͓|�ꂽ�c", hero.player_name().c_str());
							DrawTurnGraph(580, 385, soldier_down, true);
						}
					}

					//�R�mspeed attack --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						if (braver_attack_cnt == 20) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
				default:
					break;
				}
				win_or_lose_or_drow = 1;
			}

			if (play_hand_cpu == play_hand_player) {
				switch (player_character) {
				case 0:
					//�E��guard --> �Gguard
					if (braver_attack_cnt < 49) {
						DrawGraph(580, 400, braver_guard[braver_attack_cnt / 7], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��ɔ����̋@������������Ă���I");
						is_battle = false;
						DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
						braver_idle_cnt++;
						if (braver_idle_cnt == 42) {
							braver_idle_cnt = 0;
						}
					}

					//�E��guard --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						DrawGraph(580, 440, guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g��guard --> �Gguard
					if (braver_attack_cnt < 70) {
						DrawGraph(580, 400, magician_guard[braver_attack_cnt / 5], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��ɔ����̋@������������Ă���I");
						is_battle = false;
						DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
						magician_idle_cnt++;
						if (magician_idle_cnt == 70) {
							magician_idle_cnt = 0;
						}
					}

					//���@�g��guard --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						DrawGraph(580, 440, guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				case 2:
					//�R�mguard --> �Gguard
					if (braver_attack_cnt < 49) {
						DrawTurnGraph(580, 385, soldier_attack[0], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "�݂��ɔ����̋@������������Ă���I");
						is_battle = false;
						DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
						soldier_idle_cnt++;
						if (soldier_idle_cnt == 145) {
							soldier_idle_cnt = 0;
						}
					}

					//�R�mguard --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						DrawGraph(580, 440, guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				default:
					break;
				}
				win_or_lose_or_drow = 2;
			}

			if (play_hand_player == 4) {
				/*if (!is_damage) {
				enemy.damage(hero.skill_attack());
				hero.break_decrement();
				hero.attack_decrement();
				hero.guard_decrement();
				is_damage = true;
				}
				*/
				switch (player_character) {
				case 0:
					//�E��skill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͗͂���������I�I", hero.player_name().c_str());
						DrawGraph(580, 400, braver_skill[braver_attack_cnt / 5], true);
						if (cut_in_cnt <= -65) {
							braver_attack_cnt++;
						}
					}
					else if (braver_attack_cnt >= 50 && braver_attack_cnt < 77) {
						DrawRotaGraph(740 - int((braver_attack_cnt - 50) / 27.0f * 280), 560 - int(200 * sin((braver_attack_cnt - 50) / 27.0f * M_PI)), 1.0, -((braver_attack_cnt - 50) / 27.0f) * M_PI * 2.0f, braver_break[(braver_attack_cnt - 50) / 3], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 77 && braver_attack_cnt < 119) {
						if (!is_damage) {
							enemy.damage(hero.skill_attack());
							hero.break_decrement();
							hero.attack_decrement();
							hero.guard_decrement();
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃}�[�x���u���[�h�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^���A%d�����͂�D�����I", enemy.player_name().c_str(), 2 * hero.speed_attack(), hero.speed_attack());
						DrawGraph(280 + int((braver_attack_cnt - 77) / 35.0f * 225), 400, braver_jump[(braver_attack_cnt - 77) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃}�[�x���u���[�h�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^���A%d�����͂�D�����I", enemy.player_name().c_str(), 2 * hero.speed_attack(), hero.speed_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 91) {
								death_cnt = 64;
							}
						}
					}
					//�E��skill�@�G�t�F�N�g
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 70) {
							PlaySoundMem(braver_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//�E��skill�@�J�b�g�C��
					if (cut_in_cnt > -65) {
						if (cut_in_cnt == -5) {
							PlaySoundMem(skill_start_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(30 * cut_in_cnt, 284, cut_in_img, true);
						cut_in_cnt--;
						DrawGraph(272, 200, braver_cut_in, true);
					}
					break;
				case 1:
					//���@�g��skill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͗͂���������I�I", hero.player_name().c_str());
						DrawGraph(580, 400, magician_skill[braver_attack_cnt / 5], true);
						if (cut_in_cnt <= -65) {
							braver_attack_cnt++;
						}
					}
					else if (braver_attack_cnt < 100) {
						if (!is_damage) {
							enemy.damage(hero.skill_attack());
							hero.break_decrement();
							hero.attack_decrement();
							hero.guard_decrement();
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃T���_�[�{���g�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						DrawGraph(580, 400, magician_break[(braver_attack_cnt - 50) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃T���_�[�{���g�I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}
					//���@�g��skill�@�G�t�F�N�g
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 80) {
							PlaySoundMem(magician_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, magician_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//���@�g��skill�@�J�b�g�C��
					if (cut_in_cnt > -65) {
						if (cut_in_cnt == -5) {
							PlaySoundMem(skill_start_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(30 * cut_in_cnt, 284, cut_in_img, true);
						cut_in_cnt--;
						DrawGraph(272, 184, magician_cut_in, true);
					}
					break;
				case 2:
					//�R�mskill
					if (braver_attack_cnt < 30) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�͗͂���������I�I", hero.player_name().c_str());
						DrawTurnGraph(580, 385, soldier_attack[0], true);
						if (cut_in_cnt <= -65) {
							braver_attack_cnt++;
						}
					}
					else if (braver_attack_cnt < 50) {
						DrawRotaGraph(740 - int((braver_attack_cnt - 30) / 20.0f * 280), 545 - int(200 * sin((braver_attack_cnt - 30) / 20.0f * M_PI)), 1.0, -((braver_attack_cnt - 30) / 20.0f) * M_PI * 2.0f, soldier_attack[braver_attack_cnt - 30], true, true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 50 && braver_attack_cnt < 90) {
						if (!is_damage) {
							enemy.damage(hero.skill_attack());
							hero.break_decrement();
							hero.attack_decrement();
							hero.guard_decrement();
							is_damage = true;
						}
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃��x���W�X���b�V���I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 50) / 40.0f * 300), 385 - int(50 * sin((braver_attack_cnt - 50) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 42) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//�퓬�̕��͕`��
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�̃��x���W�X���b�V���I�I", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�̃_���[�W��^�����I", enemy.player_name().c_str(), hero.skill_attack());
						if (enemy.player_hp() > 0) {
							is_battle = false;
						}
						if (death_cnt < 64) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//�����\�L�̕`��
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s��|�����I�I", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//�R�mskill�@�G�t�F�N�g
					if (effect_cnt < 70 && braver_attack_cnt > 25) {
						if (braver_attack_cnt == 35) {
							PlaySoundMem(soldier_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//�R�mskill�@�J�b�g�C��
					if (cut_in_cnt > -65) {
						if (cut_in_cnt == -5) {
							PlaySoundMem(skill_start_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(30 * cut_in_cnt, 284, cut_in_img, true);
						cut_in_cnt--;
						DrawTurnGraph(302, 239, soldier_cut_in, true);
					}

					break;
				default:
					break;
				}
			}

			if (play_hand_player == 5) {
				switch (player_character) {
				case 0:
					//�E�ғ��� --> �Gguard
					//�퓬�̕��͕`��
					DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�����͓����o�����I", hero.player_name().c_str());
					DrawStringToHandle(70, 90, "��������荞�܂�Ă��܂����I�I", 0xffffffff, normal_str);
					DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͂�����̗l�q�����������Ă���I", enemy.player_name().c_str());
					is_battle = false;
					DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
					braver_idle_cnt++;
					if (braver_idle_cnt == 42) {
						braver_idle_cnt = 0;
					}
					
					//�E�ғ��� --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				case 1:
					//���@�g������ --> �Gguard
					//�퓬�̕��͕`��
					DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�����͓����o�����I", hero.player_name().c_str());
					DrawStringToHandle(70, 90, "��������荞�܂�Ă��܂����I�I", 0xffffffff, normal_str);
					DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͂�����̗l�q�����������Ă���I", enemy.player_name().c_str());
					is_battle = false;
					DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
					magician_idle_cnt++;
					if (magician_idle_cnt == 70) {
						magician_idle_cnt = 0;
					}

					//���@�g������ --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				case 2:
					//�R�m���� --> �Gguard
					//�퓬�̕��͕`��
					DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%s�����͓����o�����I", hero.player_name().c_str());
					DrawStringToHandle(70, 90, "��������荞�܂�Ă��܂����I�I", 0xffffffff, normal_str);
					DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%s�͂�����̗l�q�����������Ă���I", enemy.player_name().c_str());
					is_battle = false;
					DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
					soldier_idle_cnt++;
					if (soldier_idle_cnt == 145) {
						soldier_idle_cnt = 0;
					}

					//�R�m���� --> �Gguard�@�G�t�F�N�g
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				default:
					break;
				}
			}

		}

		//�v���C���[��HP�Q�[�W
		if (hero.player_hp_percentage() > 30) {
			switch (player_character) {
			case 0:
				DrawGraph(770, 480, braver_hp_1, true);
				break;
			case 1:
				DrawGraph(770, 480, magician_hp_1, true);
				break;
			case 2:
				DrawTurnGraph(770, 480, soldier_hp_1, true);
				break;
			default:
				break;
			}
		}
		else {
			switch (player_character) {
			case 0:
				DrawGraph(785, 475, braver_hp_2, true);
				break;
			case 1:
				DrawGraph(785, 475, magician_hp_2, true);
				break;
			case 2:
				DrawTurnGraph(760, 470, soldier_hp_2, true);
				break;
			default:
				break;
			}
		}

		DrawCircleGauge(890, 575, 100, hp_gauge_edge, 0);
		hp_color_manager = hero.player_hp_percentage() * 1.2f;
		GraphFilter(hp_gauge, DX_GRAPH_FILTER_HSB, 1, int(hp_color_manager), 0, 0);
		DrawCircleGauge(890, 575, hero.player_hp_percentage(), hp_gauge, 0);
		//�v���C���[��HP�̊�����\���iDebug�p�j
		//DrawStringEx(100, 100, 0x00000000, "%d", hero.player_hp_percentage());

		//�萔�̕`��
		DrawRotaGraph(40, 730, 0.5, 0, hammer_img[0], true, false);
		DrawFormatStringToHandle(70, 710, 0x00000000, emp_str, "�~%d", hero.break_count());
		DrawRotaGraph(200, 730, 0.5, 0, sword_img[0], true, false);
		DrawFormatStringToHandle(230, 710, 0x00000000, emp_str, "�~%d", hero.attack_count());
		DrawRotaGraph(360, 730, 0.5, 0, shield_img[0], true, false);
		DrawFormatStringToHandle(390, 710, 0x00000000, emp_str, "�~%d", hero.guard_count());

		//�G���������珟��BGM�𗬂�
		if (CheckSoundMem(battle_victory_bgm) == 0 && death_cnt >= 64) {
			StopSoundMem(battle1_bgm);
			PlaySoundMem(battle_victory_bgm, DX_PLAYTYPE_LOOP);
		}

		/*�@�f�o�b�O�p
		if (0 == win_or_lose_or_drow) {
			DrawStringEx(460, 340, 0xffffffff, "���Ȃ��̏���");
		}
		if (1 == win_or_lose_or_drow) {
			DrawStringEx(460, 340, 0xffffffff, "CPU �̏���");
		}
		if (2 == win_or_lose_or_drow) {
			DrawStringEx(480, 340, 0xffffffff, "������");
		}

		DrawFormatStringToHandle(0, 0, 0x00000000, normal_str, "��l���̗̑́F%d", hero.player_hp());
		DrawFormatStringToHandle(10, 10, 0x00000000, normal_str, "%s�̗̑́F%d", enemy.player_name().c_str(),enemy.player_hp());
		DrawFormatStringToHandle(20, 20, 0x00000000, normal_str, "��l���̍U���́F%d", hero.player_attack());
		DrawFormatStringToHandle(60, 50, 0x00000000, normal_str, "�G�̍U���́F%d", enemy.player_attack());

		DrawFormatStringToHandle(100, 350, 0x00000000, normal_str, "break_cnt�F%d", hero.break_count());
		DrawFormatStringToHandle(100, 400, 0x00000000, normal_str, "attack_cnt�F%d", hero.attack_count());
		DrawFormatStringToHandle(100, 450, 0x00000000, normal_str, "guard_cnt�F%d", hero.guard_count());

		//DrawStringEx(450, 560, 0xffffffff, "���Ȃ� �̎�");

		DrawStringEx(390, 630, 0xffffffff, "�G���^�[�L�[�������Ă�������");
		*/

		// �v���C���[�܂��͓G��HP��0�ɂȂ�����Q�[���I�[�o�[��ʂ܂��̓}�b�v�ɖ߂�
		// �܂��Ȃ��I����
		if (IsKeyDownTrigger(KEY_INPUT_RETURN) == true && !is_battle) {
			is_enemy_hand_decided = false;
			is_heroine_see_enemy = false;
			braver_attack_cnt = 0;
			play_sequence = 0;
			effect_cnt = 0;
			cut_in_cnt = 0;
			play_hand_player = 0;
			is_battle = true;
			if (hero.player_hp() <= 0) {
				fade_out_circle();
				scene = 4;
				turn_count = 0;
				is_player_win = false;
				is_damage = false;
				is_init_char = false;
				is_init_battle = false;
				death_cnt = 0;
				StopSoundMem(battle1_bgm);
			}
			else if(enemy.player_hp() <= 0){
				//fade_out_circle();
				//scene = pre_scene;
				//pre_scene = 1;
				turn_count = 0;
				is_player_win = true;
				is_damage = false;
				//is_init_char = false;
				//is_init_battle = false;
				//StopSoundMem(battle_victory_bgm);
				play_sequence = 3;
				gain_total_exp = enemy.player_exp();
				gain_exp = gain_total_exp;
				next_exp = hero.player_next_exp();
			}
			else {
				is_damage = false;
			}
		}

		break;
	case 2:
		//�퓬�J�n���̃A�j���[�V����
		//�G�̕`��
		switch (enemy_number) {
		case -1:
			DrawGraph(50, 200, enemy1_img, true);
			break;
		case -2:
			DrawGraph(50, 200, enemy2_img, true);
			break;
		case -3:
			DrawGraph(50, 200, enemy3_img, true);
			break;
		default:
			break;
		}
		switch (player_character) {
		case 0:
			DrawGraph(1024 - braver_idle_cnt / 32.0f * 444, 400, braver_run[braver_idle_cnt / 4], true);
			braver_idle_cnt++;
			if (braver_idle_cnt == 32) {
				braver_idle_cnt = 0;
				play_sequence = 0;
			}
			break;

		case 1:
			DrawGraph(1024 - magician_idle_cnt / 32.0f * 444, 400, magician_run[magician_idle_cnt / 4], true);
			magician_idle_cnt++;
			if (magician_idle_cnt == 32) {
				magician_idle_cnt = 0;
				play_sequence = 0;
			}
			break;

		case 2:
			DrawTurnGraph(1024 - soldier_idle_cnt /32.0f * 444, 385, soldier_walk[soldier_idle_cnt / 2], true);
			soldier_idle_cnt++;
			if (soldier_idle_cnt == 32) {
				soldier_idle_cnt = 0;
				play_sequence = 0;
			}
			break;
		default:
			break;
		}
		break;
	case 3:
		DrawGraph(0, -15, window_all, true);

		//�o���l�l������
		if (exp_counter < gain_total_exp) {
			hero.exp_gain();
			exp_counter++;
			gain_exp--;
		}

		if (hero.is_level_up()) {
			hero.level_up(random_level_up(machine), random_level_up(machine), random_level_up(machine), random_level_up(machine));
			PlaySoundMem(level_up_sound, DX_PLAYTYPE_BACK);
			is_levelup = true;
		}

		DrawStringToHandle(150, 90, "Battle Result", 0x00000000, emp_str);
		DrawFormatStringToHandle(550, 200, 0xffffffff, window_emp_str, "Level %d",hero.player_level());
		DrawFormatStringToHandle(550, 280, 0xffffffff, window_emp_str, "Hp %d/%d", hero.player_hp(),hero.player_hp_max());
		DrawFormatStringToHandle(550, 330, 0xffffffff, window_emp_str, "Bre %d", hero.break_attack());
		DrawFormatStringToHandle(550, 380, 0xffffffff, window_emp_str, "Spd %d", hero.speed_attack());
		DrawFormatStringToHandle(550, 430, 0xffffffff, window_emp_str, "Def %d", hero.guard_attack());

		DrawFormatStringToHandle(150, 530, 0xffffffff, window_emp_str, "EXP %d", hero.player_exp());
		DrawFormatStringToHandle(150, 580, 0xffffffff, window_emp_str, "���̃��x���܂� %d", hero.player_next_exp());
		DrawFormatStringToHandle(150, 630, 0xffffffff, window_emp_str, "�l���o���l %d", enemy.player_exp());


		DrawFormatStringToHandle(200, 200, 0xffffffff, window_emp_str, "%s", hero.player_name().c_str());
		switch (player_character) {
		case 0:
			if (is_levelup) {
				if (braver_idle_cnt >= 32) {
					braver_idle_cnt = 0;
				}
				DrawGraph(150, 190, braver_victory[braver_idle_cnt / 4], true);
				DrawStringToHandle(180, 450, "Level Up !!", GetColor(255, 0, 0), window_emp_str);
				braver_idle_cnt++;
			}
			else {
				DrawGraph(150, 190, braver_attack_ready[braver_idle_cnt / 6], true);
				braver_idle_cnt++;
				if (braver_idle_cnt == 42) {
					braver_idle_cnt = 0;
				}
			}
			break;
		case 1:
			if (is_levelup) {
				if (magician_idle_cnt >= 68) {
					magician_idle_cnt = 0;
				}
				DrawGraph(150, 190, magician_victory[magician_idle_cnt / 4], true);
				DrawStringToHandle(180, 450, "Level Up !!", GetColor(255, 0, 0), window_emp_str);
				magician_idle_cnt++;
			}
			else {
				DrawGraph(150, 190, magician_attack_ready[magician_idle_cnt / 5], true);
				magician_idle_cnt++;
				if (magician_idle_cnt == 70) {
					magician_idle_cnt = 0;
				}
			}
			break;
		case 2:
			if (is_levelup) {
				if (soldier_idle_cnt >= 75) {
					soldier_idle_cnt = 0;
				}
				DrawTurnGraph(150, 190, soldier_victory[soldier_idle_cnt / 3], true);
				DrawStringToHandle(180, 450, "Level Up !!", GetColor(255, 0, 0), window_emp_str);
				soldier_idle_cnt++;
			}
			else {
				DrawTurnGraph(150, 190, soldier_idle[soldier_idle_cnt / 5], true);
				soldier_idle_cnt++;
				if (soldier_idle_cnt == 145) {
					soldier_idle_cnt = 0;
				}
			}
			break;
		default:
			break;
		}

		if (IsKeyDownTrigger(KEY_INPUT_RETURN) && exp_counter >= gain_total_exp) {
			fade_out_circle();
			scene = pre_scene;
			pre_scene = 1;
			turn_count = 0;
			is_player_win = true;
			is_damage = false;
			is_init_char = false;
			is_init_battle = false;
			death_cnt = 0;
			exp_counter = 0;
			gain_total_exp = 0;
			gain_exp = 0;
			next_exp = 0;
			is_levelup = false;
			is_levelup_sound = false;
			death_cnt = 0;
			StopSoundMem(battle_victory_bgm);
			play_sequence = 0;
		}
		break;
	case 4:
		//�q���C���̉񕜎���
		DrawGraph(0, 10, window_img, true);

		//�v���C���[�L�����̕`��
		switch (player_character) {
		case 0:
			if (hero.is_skill()) {
				DrawGraph(580, 400, braver_charge[braver_idle_cnt / 6], true);
				braver_idle_cnt++;
				if (braver_idle_cnt == 42) {
					braver_idle_cnt = 0;
				}
			}
			else {
				DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
				braver_idle_cnt++;
				if (braver_idle_cnt == 42) {
					braver_idle_cnt = 0;
				}
			}
			break;

		case 1:
			if (hero.is_skill()) {
				if (magician_idle_cnt >= 42) {
					magician_idle_cnt = 0;
				}
				DrawGraph(580, 400, magician_charge[magician_idle_cnt / 6], true);
				magician_idle_cnt++;
				if (magician_idle_cnt == 42) {
					magician_idle_cnt = 0;
				}
			}
			else {
				DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
				magician_idle_cnt++;
				if (magician_idle_cnt == 70) {
					magician_idle_cnt = 0;
				}
			}
			break;

		case 2:
			if (hero.is_skill()) {
				DrawGraph(580, 385, soldier_charge, true);
				DrawTurnGraph(580, 385, soldier_attack[0], true);
			}
			else {
				DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
				soldier_idle_cnt++;
				if (soldier_idle_cnt == 145) {
					soldier_idle_cnt = 0;
				}
			}
			break;
		default:
			break;
		}

		//�v���C���[��HP�Q�[�W
		if (hero.player_hp_percentage() > 30) {
			switch (player_character) {
			case 0:
				DrawGraph(770, 480, braver_hp_1, true);
				break;
			case 1:
				DrawGraph(770, 480, magician_hp_1, true);
				break;
			case 2:
				DrawTurnGraph(770, 480, soldier_hp_1, true);
				break;
			default:
				break;
			}
		}
		else {
			switch (player_character) {
			case 0:
				DrawGraph(785, 475, braver_hp_2, true);
				break;
			case 1:
				DrawGraph(785, 475, magician_hp_2, true);
				break;
			case 2:
				DrawTurnGraph(760, 470, soldier_hp_2, true);
				break;
			default:
				break;
			}
		}

		DrawCircleGauge(890, 575, 100, hp_gauge_edge, 0);
		hp_color_manager = hero.player_hp_percentage() * 1.2f;
		GraphFilter(hp_gauge, DX_GRAPH_FILTER_HSB, 1, int(hp_color_manager), 0, 0);
		DrawCircleGauge(890, 575, hero.player_hp_percentage(), hp_gauge, 0);
		//�v���C���[��HP�̊�����\���iDebug�p�j
		//DrawStringEx(100, 100, 0x00000000, "%d", hero.player_hp_percentage());

		//�G�L�����̕`��
		switch (enemy_number) {
		case -1:
			DrawGraph(50, 200, enemy1_img, true);
			DrawBox(180, 360, 390, 400, GetColor(0, 0, 0), true);
			if (enemy.player_hp_percentage() <= 50) {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
			}
			else {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
			}
			break;
		case -2:
			DrawGraph(50, 200, enemy2_img, true);
			DrawBox(180, 360, 390, 400, GetColor(0, 0, 0), true);
			if (enemy.player_hp_percentage() <= 50) {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
			}
			else {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
			}
			break;
		case -3:
			DrawGraph(50, 200, enemy3_img, true);
			DrawBox(180, 240, 390, 280, GetColor(0, 0, 0), true);
			if (enemy.player_hp_percentage() <= 50) {
				DrawBox(185, 245, 185 + enemy.player_hp_percentage() * 2, 275, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
			}
			else {
				DrawBox(185, 245, 185 + enemy.player_hp_percentage() * 2, 275, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
			}
			break;
		default:
			break;
		}

		//�q���C���Ɋւ���`��
		DrawGraph(607, 186, heroine_window3, true);
		DrawGraph(627, 216, heroine_battle[1], true);

		if (heroine_heal_cnt != 0 || is_healed) {
			//�񕜏������A�j���[�V����
			if (heal_cnt < 64) {
				DrawGraph(615, 425, heal_effect[heal_cnt / 8], true);
				heal_cnt++;
			}

			if (heal_cnt == 64 && !is_healed) {
				PlaySoundMem(heal_sound, DX_PLAYTYPE_BACK);
				heal_point = hero.player_hp_max() - hero.player_hp();
				hero.hp_heal();
				heroine_heal_cnt--;
				is_healed = true;

			}

			DrawStringToHandle(710, 230, "�񕜂����I�I", 0xffffffff, window_str);

			DrawFormatStringToHandle(70, 50, 0xffffffff, window_str,"%s�̓q�[�����������I�I",heroine_name.c_str());
			if (heal_cnt == 64) {
				DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%s��%d�񕜂����I�I", hero.player_name().c_str(), heal_point);
			}

			if (IsKeyDownTrigger(KEY_INPUT_RETURN) && heal_cnt >= 64) {
				PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
				is_healed = false;
				heal_point = 0;
				heal_cnt = 0;
				play_sequence = 0;
			}
		}
		else {
			DrawFormatStringToHandle(70, 50, 0xffffffff, window_str, "%s�̓q�[���������悤�Ƃ����I", heroine_name.c_str());
			DrawStringToHandle(70, 90, "���������͂�����Ȃ��c", 0xffffffff, window_str);
			DrawStringToHandle(710, 230, "���������݂����c", 0xffffffff, window_str);

			if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
				PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
				heal_cnt = 0;
				play_sequence = 0;
			}
		}

		break;
	case 5:
		//��������
		switch (enemy_number) {
		case -1:
			DrawGraph(50, 200, enemy1_img, true);
			break;
		case -2:
			DrawGraph(50, 200, enemy2_img, true);
			break;
		case -3:
			DrawGraph(50, 200, enemy3_img, true);
			break;
		default:
			break;
		}

		DrawGraph(0, 10, window_img, true);
		DrawFormatStringToHandle(70, 50, 0xffffffff, window_str, "%s�����͓����o�����I�I", hero.player_name().c_str());

		switch (player_character) {
		case 0:
			DrawTurnGraph(580 + braver_idle_cnt / 32.0f * 444, 400, braver_run[braver_idle_cnt / 4], true);
			braver_idle_cnt++;
			if (braver_idle_cnt == 32) {
				braver_idle_cnt = 0;
				play_sequence = 0;
				fade_out_circle();
				scene = pre_scene;
				pre_scene = 1;
				turn_count = 0;
				is_damage = false;
				is_init_char = false;
				is_init_battle = false;
				death_cnt = 0;
				death_cnt = 0;
				StopSoundMem(battle1_bgm);
			}
			break;

		case 1:
			DrawTurnGraph(580 + magician_idle_cnt / 32.0f * 444, 400, magician_run[magician_idle_cnt / 4], true);
			magician_idle_cnt++;
			if (magician_idle_cnt == 32) {
				magician_idle_cnt = 0;
				play_sequence = 0;
				fade_out_circle();
				scene = pre_scene;
				pre_scene = 1;
				turn_count = 0;
				is_damage = false;
				is_init_char = false;
				is_init_battle = false;
				death_cnt = 0;
				death_cnt = 0;
				StopSoundMem(battle1_bgm);
			}
			break;

		case 2:
			DrawGraph(580 + soldier_idle_cnt / 32.0f * 444, 385, soldier_walk[soldier_idle_cnt / 2], true);
			soldier_idle_cnt++;
			if (soldier_idle_cnt == 32) {
				soldier_idle_cnt = 0;
				play_sequence = 0;
				fade_out_circle();
				scene = pre_scene;
				pre_scene = 1;
				turn_count = 0;
				is_damage = false;
				is_init_char = false;
				is_init_battle = false;
				death_cnt = 0;
				death_cnt = 0;
				StopSoundMem(battle1_bgm);
			}
			break;
		default:
			break;
		}
		break;
	case 6:
		//�q���C���̃��C�u������

		DrawGraph(0, 10, heroine_window, true);
		DrawGraph(58, 68, heroine[1], true);

		DrawFormatStringToHandle(158, 40, 0xffffffff, window_str, "��%s��", enemy.player_name().c_str());
		switch (enemy_number) {
		case -1:
			DrawStringToHandle(158, 80, "�j���g���̖�����", 0xffffffff, window_str);
			DrawStringToHandle(158, 120, "�͔C���̍U���������݂�����", 0xffffffff, window_str);
			break;
		case -2:
			DrawStringToHandle(158, 80, "�I�I�J�~�̖�����", 0xffffffff, window_str);
			DrawStringToHandle(158, 120, "�f�����U���������݂�����", 0xffffffff, window_str);
			break;
		case -3:
			DrawStringToHandle(158, 80, "���[���C�̖�����", 0xffffffff, window_str);
			DrawStringToHandle(158, 120, "�g������Ă��邱�Ƃ������݂�����", 0xffffffff, window_str);
			break;
		default:
			break;
		}

		if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
			play_sequence = 0;
		}

		//�v���C���[�L�����̕`��
		switch (player_character) {
		case 0:
			if (hero.is_skill()) {
				DrawGraph(580, 400, braver_charge[braver_idle_cnt / 6], true);
				braver_idle_cnt++;
				if (braver_idle_cnt == 42) {
					braver_idle_cnt = 0;
				}
			}
			else {
				DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
				braver_idle_cnt++;
				if (braver_idle_cnt == 42) {
					braver_idle_cnt = 0;
				}
			}
			break;

		case 1:
			if (hero.is_skill()) {
				if (magician_idle_cnt >= 42) {
					magician_idle_cnt = 0;
				}
				DrawGraph(580, 400, magician_charge[magician_idle_cnt / 6], true);
				magician_idle_cnt++;
				if (magician_idle_cnt == 42) {
					magician_idle_cnt = 0;
				}
			}
			else {
				DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
				magician_idle_cnt++;
				if (magician_idle_cnt == 70) {
					magician_idle_cnt = 0;
				}
			}
			break;

		case 2:
			if (hero.is_skill()) {
				DrawGraph(580, 385, soldier_charge, true);
				DrawTurnGraph(580, 385, soldier_attack[0], true);
			}
			else {
				DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
				soldier_idle_cnt++;
				if (soldier_idle_cnt == 145) {
					soldier_idle_cnt = 0;
				}
			}
			break;
		default:
			break;
		}

		//�v���C���[��HP�Q�[�W
		if (hero.player_hp_percentage() > 30) {
			switch (player_character) {
			case 0:
				DrawGraph(770, 480, braver_hp_1, true);
				break;
			case 1:
				DrawGraph(770, 480, magician_hp_1, true);
				break;
			case 2:
				DrawTurnGraph(770, 480, soldier_hp_1, true);
				break;
			default:
				break;
			}
		}
		else {
			switch (player_character) {
			case 0:
				DrawGraph(785, 475, braver_hp_2, true);
				break;
			case 1:
				DrawGraph(785, 475, magician_hp_2, true);
				break;
			case 2:
				DrawTurnGraph(760, 470, soldier_hp_2, true);
				break;
			default:
				break;
			}
		}

		DrawCircleGauge(890, 575, 100, hp_gauge_edge, 0);
		hp_color_manager = hero.player_hp_percentage() * 1.2f;
		GraphFilter(hp_gauge, DX_GRAPH_FILTER_HSB, 1, int(hp_color_manager), 0, 0);
		DrawCircleGauge(890, 575, hero.player_hp_percentage(), hp_gauge, 0);
		//�v���C���[��HP�̊�����\���iDebug�p�j
		//DrawStringEx(100, 100, 0x00000000, "%d", hero.player_hp_percentage());

		//�G�L�����̕`��
		switch (enemy_number) {
		case -1:
			DrawGraph(50, 200, enemy1_img, true);
			DrawBox(180, 360, 390, 400, GetColor(0, 0, 0), true);
			if (enemy.player_hp_percentage() <= 50) {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
			}
			else {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
			}
			break;
		case -2:
			DrawGraph(50, 200, enemy2_img, true);
			DrawBox(180, 360, 390, 400, GetColor(0, 0, 0), true);
			if (enemy.player_hp_percentage() <= 50) {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
			}
			else {
				DrawBox(185, 365, 185 + enemy.player_hp_percentage() * 2, 395, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
			}
			break;
		case -3:
			DrawGraph(50, 200, enemy3_img, true);
			DrawBox(180, 240, 390, 280, GetColor(0, 0, 0), true);
			if (enemy.player_hp_percentage() <= 50) {
				DrawBox(185, 245, 185 + enemy.player_hp_percentage() * 2, 275, GetColor(255, int(enemy.player_hp_percentage() * 5.1), 0), true);
			}
			else {
				DrawBox(185, 245, 185 + enemy.player_hp_percentage() * 2, 275, GetColor(int((100 - enemy.player_hp_percentage()) * 5.1), 255, 0), true);
			}
			break;
		default:
			break;
		}

		break;
	default:
		break;
	}


}

