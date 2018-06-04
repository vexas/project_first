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


// ゲームの初期化フラグ
extern int is_init ;

// シーンを制御する変数
// この変数の値
// 0 : タイトル
// 1 : プレイ画面
// 2 : リザルト画面
extern int scene ;
extern int pre_scene;

//フォントのハンドル
extern int title_str;
extern int emp_str;
extern int subtitle_str;
extern int normal_str;
extern int window_str;
extern int window_emp_str;

// 手の画像
extern int gfx_rock ;
extern int gfx_scissors ;
extern int gfx_paper ;
extern int sword_img[20];
extern int shield_img[20];
extern int hammer_img[20];
extern int small_sword_img[20];
extern int small_shield_img[20];
extern int small_hammer_img[20];

//背景の画像
extern int field_img;
extern int window_img;
extern int window_all;
extern int heroine_window;
extern int heroine_window3;
extern int hp_gauge;
extern int hp_gauge_edge;
extern int cut_in_img;

//エフェクトの画像
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

//効果音
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

//HPゲージの色を管理する変数
extern float hp_color_manager;
extern int enemy_hp_width;

// カーソルの画像
extern int gfx_cursor ;

// プレイ画面でのシーケンス用変数
// 0 : プレイヤの手選択シーケンス
// 1 : 結果表示
extern int play_sequence ;

// プレイヤーの手
// 0 : グー
// 1 : チョキ
// 2 : パー
extern int play_hand_player ;

//アニメーション制御の変数
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

//プレイヤーのキャラの種類
// 0：勇者
// 1：魔法使い
// 2：騎士
extern int player_character;

//プレイヤークラス
extern player hero;
extern player enemy;

//プレイヤーの画像
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

//敵の画像
extern int enemy1_img;
extern int enemy2_img;
extern int enemy3_img;

// CPU の手
extern int play_hand_cpu ;

// ジャンケンをした回数
extern int turn_count ;

// 勝った回数
extern int play_win_count ;

// 負けた回数
extern int play_lose_count ;

//勝利判定
extern bool is_player_win;

//フラグ管理
extern bool is_damage;
extern bool is_init_char;
extern bool is_init_battle;

// ※デフォルトはあいこにしておく
int win_or_lose_or_drow = 2;
bool is_battle;

//音楽
extern int battle1_bgm;
extern int battle_victory_bgm;

//経験値獲得処理に用いる変数
int exp_counter = 0;
int gain_total_exp = 0;
int gain_exp = 0;
int next_exp = 0;
bool is_levelup = false;
bool is_levelup_sound = false;
extern std::mt19937 machine;
extern std::uniform_int_distribution<int> random_level_up;

//敵の手を決めるための変数
extern std::uniform_int_distribution<int> random_number;
bool is_enemy_hand_decided = false;

//ヒロインが先読みできるかどうかの判定
bool is_heroine_see_enemy = false;

//ヒロインの回復呪文の回数
extern int heroine_heal_cnt;

//回復処理に用いる変数
bool is_healed = false;
int heal_point = 0;

//ヒロインの名前
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
		//アニメーション管理変数の初期化
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
	// プレイ画面でのシーケンス制御
	switch (play_sequence) {

		// 手選択画面
	case 0:

		DrawGraph(0, 10, window_img, true);

		// ← を押した時の処理
		if (IsKeyDownTrigger(KEY_INPUT_LEFT)) {
			play_hand_player -= 1;
			PlaySoundMem(select_sound, DX_PLAYTYPE_BACK);
		}

		// → を押した時の処理
		if (IsKeyDownTrigger(KEY_INPUT_RIGHT)) {
			play_hand_player += 1;
			PlaySoundMem(select_sound, DX_PLAYTYPE_BACK);
		}

		// もしも 0 より小さくなってしまったら 0 にする
		if (play_hand_player < 0) {
			play_hand_player = 2;
		}

		// もしも 2 より大きくなってしまったら 2 にする
		if (play_hand_player > 2) {
			play_hand_player = 0;
		}


		// エンターを押した時の処理
		if (IsKeyDownTrigger(KEY_INPUT_RETURN) && is_enemy_hand_decided) {

			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);

			// ジャンケンをした回数を増やす
			turn_count++;

			// 勝敗判定をして勝った回数と負けた回数をカウントする
			// CPU の手がグーの時
			if (0 == play_hand_cpu) {
				if (1 == play_hand_player) {
					play_lose_count += 1;
				}
				if (2 == play_hand_player) {
					play_win_count += 1;
				}
			}

			// CPU の手がチョキの時
			if (1 == play_hand_cpu) {
				if (2 == play_hand_player) {
					play_lose_count += 1;
				}
				if (0 == play_hand_player) {
					play_win_count += 1;
				}
			}

			// CPU の手がパーの時
			if (2 == play_hand_cpu) {
				if (0 == play_hand_player) {
					play_lose_count += 1;
				}
				if (1 == play_hand_player) {
					play_win_count += 1;
				}
			}

			//アニメーション管理変数の初期化
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

			//各手のカウント
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

			// ターンの結果へと進める
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
				//アニメーション管理変数の初期化
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

		//プレイヤーキャラの描画
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

		//プレイヤーのHPゲージ
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
		//プレイヤーのHPの割合を表示（Debug用）
		//DrawStringEx(100, 100, 0x00000000, "%d", hero.player_hp_percentage());

		//敵キャラの描画
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

		// CPU の手を内部的に選択する
		// 0 から 2 までの乱数を取得
		//play_hand_cpu = rand() % 3;
		if (!is_enemy_hand_decided) {
			play_hand_cpu = enemy.enemy_hand_decided(random_number(machine));
			is_enemy_hand_decided = true;
			if (random_number(machine) <= 15) {
				is_heroine_see_enemy = true;
			}
		}

		//ヒロインに関する描画
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
			DrawStringToHandle(710, 230, "次は　　だよ！！", 0xffffffff, window_str);
		}
		else {
			DrawStringToHandle(680, 210, "(敵の様子を", 0xffffffff, window_str);
			DrawStringToHandle(680, 250, " うかがっている…)", 0xffffffff, window_str);
		}

		// ハンマー、剣、盾の描画
		if (play_hand_player == 0) {
			DrawGraph(635, 300, hammer_img[break_cnt / 5], true);
			DrawGraph(790, 400, small_sword_img[0], true);
			attack_cnt = -1;
			DrawGraph(580, 400, small_shield_img[0], true);
			guard_cnt = -1;
			DrawStringToHandle(150, 40, "Break", 0xffffffff, window_emp_str);
			DrawStringToHandle(250, 90, "Guardを打ち破る怒涛の一撃！！", 0xffffffff, window_str);
			DrawStringToHandle(250, 130, "Speed Attackにより阻止されてしまう…", 0xffffffff, window_str);
		}
		else if (play_hand_player == 1) {
			DrawGraph(635, 300, sword_img[attack_cnt / 5], true);
			DrawGraph(580, 400, small_hammer_img[0], true);
			break_cnt = -1;
			DrawGraph(790, 400, small_shield_img[0], true);
			guard_cnt = -1;
			DrawStringToHandle(150, 40, "Speed", 0xffffffff, window_emp_str);
			DrawStringToHandle(250, 90, "Power Attackを阻止する疾風の一撃！！", 0xffffffff, window_str);
			DrawStringToHandle(250, 130, "Guardにより反撃されてしまう…", 0xffffffff, window_str);
		}
		else if (play_hand_player == 2) {
			DrawGraph(635, 300, shield_img[guard_cnt / 5], true);
			DrawGraph(790, 400, small_hammer_img[0], true);
			break_cnt = -1;
			DrawGraph(580, 400, small_sword_img[0], true);
			attack_cnt = -1;
			DrawStringToHandle(150, 40, "Guard", 0xffffffff, window_emp_str);
			DrawStringToHandle(250, 90, "Speed Attackを受け止め反撃！！", 0xffffffff, window_str);
			DrawStringToHandle(250, 130, "Power Attackの前には無力…", 0xffffffff, window_str);
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

		// 文字の描画
		DrawFormatStringToHandle(30, 200, 0x00000000, window_emp_str,"%d Turn",turn_count + 1);
		DrawFormatStringToHandle(540, 660, 0x00000000, normal_str, "←キー＆→キーで行動を選択！！", turn_count + 1);
		DrawStringToHandle(590, 710, "Enterキーで行動を決定！！", 0x00000000, normal_str);

		//手数の描画
		DrawRotaGraph(40, 730, 0.5, 0, hammer_img[0], true, false);
		DrawFormatStringToHandle(70, 710, 0x00000000, emp_str, "×%d", hero.break_count());
		DrawRotaGraph(200, 730, 0.5, 0, sword_img[0], true, false);
		DrawFormatStringToHandle(230, 710, 0x00000000, emp_str, "×%d", hero.attack_count());
		DrawRotaGraph(360, 730, 0.5, 0, shield_img[0], true, false);
		DrawFormatStringToHandle(390, 710, 0x00000000, emp_str, "×%d", hero.guard_count());

		break;

		//----------------------------------------------------------------------------------------------------
		// 結果表示画面
	case 1:

		// １回単位での勝ったか負けたかあいこかの変数
		// 0 : 勝ち
		// 1 : 負け
		// 2 : あいこ
		DrawGraph(0, 10, window_img, true);

		//敵キャラの描画
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


		// CPU の手がハンマーの時
		if (0 == play_hand_cpu) {

			if (1 == play_hand_player) {
				/*if (!is_damage) {
					enemy.damage(hero.player_attack());
					is_damage = true;

				}
				*/

				switch (player_character) {
				case 0:
					//勇者speed attack --> 敵power attack
					if (braver_attack_cnt < 18) {
						DrawGraph(580 - int(braver_attack_cnt / 18.0f * 300), 400, braver_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 18 && braver_attack_cnt < 53) {
						if (!is_damage) {
							enemy.damage(hero.speed_attack());
							is_damage = true;

						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(),hero.speed_attack());
						DrawGraph(280 + int((braver_attack_cnt - 18) / 35.0f * 225), 400, braver_jump[(braver_attack_cnt - 18) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.speed_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 95) {
								death_cnt = 64;
							}
						}
					}

					//勇者speed attack --> 敵power attack　エフェクト
					if (effect_cnt < 35 && braver_attack_cnt > 8) {
						if (braver_attack_cnt == 12) {
							PlaySoundMem(slash_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(170, 410, attack_effect[effect_cnt / 7], true);
						effect_cnt++;
					}
					break;
				case 1:
					//魔法使いspeed attack --> 敵power attack
					if (braver_attack_cnt < 32) {
						DrawGraph(580 - int(braver_attack_cnt / 32.0f * 300), 400 - int(100 * sin(braver_attack_cnt / 32.0f * M_PI)), magician_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 32 && braver_attack_cnt < 58) {
						if (!is_damage) {
							enemy.damage(hero.speed_attack());
							is_damage = true;

						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.speed_attack());
						DrawGraph(280 + int((braver_attack_cnt - 32) / 26.0f * 225), 400, magician_jump[(braver_attack_cnt - 32) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.speed_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}

					//魔法使いspeed attack --> 敵power attack　エフェクト
					if (effect_cnt < 35 && braver_attack_cnt > 15) {
						if (braver_attack_cnt == 20) {
							PlaySoundMem(magician_attack_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(170, 410, attack_effect[effect_cnt / 7], true);
						effect_cnt++;
					}
					break;
				case 2:
					//騎士speed attack --> 敵power attack
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580 - int(braver_attack_cnt / 20.0f * 300), 385, soldier_attack[braver_attack_cnt], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						if (!is_damage) {
							enemy.damage(hero.speed_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.speed_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 20) / 40.0f * 300), 385 - int(50 * sin((braver_attack_cnt - 20) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 12) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.speed_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//騎士speed attack --> 敵power attack　エフェクト
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
					//勇者guard --> 敵power attack
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						DrawGraph(580, 400, braver_damage[(braver_attack_cnt - 21) / 4], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawGraph(580, 400, braver_down, true);
						}
					}

					//勇者guard --> 敵power attack　エフェクト
					if (effect_cnt < 56 && braver_attack_cnt > 15) {
						DrawGraph(620, 440, bite_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 25) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 1:
					//魔法使いguard --> 敵power attack
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						DrawGraph(580, 400, magician_damage[(braver_attack_cnt - 28) / 3], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawGraph(580, 400, magician_down, true);
						}
					}

					//魔法使いguard --> 敵power attack　エフェクト
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
					//騎士guard --> 敵power attack
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						DrawTurnGraph(580, 385, soldier_damage[(braver_attack_cnt - 28) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawTurnGraph(580, 385, soldier_down, true);
						}
					}

					//騎士guard --> 敵power attack　エフェクト
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
					//勇者power attack --> 敵power attack
					if (braver_attack_cnt < 18) {
						DrawGraph(580 - int(braver_attack_cnt / 18.0f * 200), 400, braver_break[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 18 && braver_attack_cnt < 53) {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						DrawGraph(380 + int((braver_attack_cnt - 18) / 35.0f * 125), 400, braver_jump[(braver_attack_cnt - 18) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						is_battle = false;
						DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
						braver_idle_cnt++;
						if (braver_idle_cnt == 42) {
							braver_idle_cnt = 0;
						}
					}

					//勇者power attack --> 敵power attack　エフェクト
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
					//魔法使いpower attack --> 敵power attack
					if (braver_attack_cnt < 50) {
						DrawGraph(580, 400, magician_break[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						is_battle = false;
						DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
						magician_idle_cnt++;
						if (magician_idle_cnt == 70) {
							magician_idle_cnt = 0;
						}
					}

					//魔法使いpower attack --> 敵power attack　エフェクト
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
					//騎士power attack --> 敵power attack
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580 - int(braver_attack_cnt / 20.0f * 200), 385, soldier_attack[braver_attack_cnt], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						DrawTurnGraph(380 + int((braver_attack_cnt - 20) / 40.0f * 200), 385 - int(50 * sin((braver_attack_cnt - 20) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 12) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						is_battle = false;
						DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
						soldier_idle_cnt++;
						if (soldier_idle_cnt == 145) {
							soldier_idle_cnt = 0;
						}
					}

					//騎士power attack --> 敵power attack　エフェクト
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
					//勇者skill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは力を解放した！！", hero.player_name().c_str());
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのマーベルブレード！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与え、%d生命力を奪った！", enemy.player_name().c_str(), 2 * hero.speed_attack(), hero.speed_attack());
						DrawGraph(280 + int((braver_attack_cnt - 77) / 35.0f * 225), 400, braver_jump[(braver_attack_cnt - 77) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのマーベルブレード！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与え、%d生命力を奪った！", enemy.player_name().c_str(), 2 * hero.speed_attack(),hero.speed_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 91) {
								death_cnt = 64;
							}
						}
					}
					//勇者skill　エフェクト
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 70) {
							PlaySoundMem(braver_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//勇者skill　カットイン
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
					//魔法使いskill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは力を解放した！！", hero.player_name().c_str());
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのサンダーボルト！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
						DrawGraph(580, 400, magician_break[(braver_attack_cnt-50) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのサンダーボルト！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}
					//魔法使いskill　エフェクト
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 80) {
							PlaySoundMem(magician_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, magician_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//魔法使いskill　カットイン
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
					//騎士skill
					if (braver_attack_cnt < 30) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは力を解放した！！", hero.player_name().c_str());
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのリベンジスラッシュ！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 50) / 40.0f * 300), 385 - int(50 * sin((braver_attack_cnt - 50) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 42) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのリベンジスラッシュ！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//騎士skill　エフェクト
					if (effect_cnt < 70 && braver_attack_cnt > 25) {
						if (braver_attack_cnt == 35) {
							PlaySoundMem(soldier_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//騎士skill　カットイン
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
					//勇者逃走 --> 敵power attack
					if (braver_attack_cnt < 42) {
						DrawGraph(580, 400, braver_attack_ready[braver_attack_cnt / 6], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sたちは逃げ出した！", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "しかし回り込まれてしまった！！", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 42 && braver_attack_cnt < 70) {
						if (!is_damage) {
							hero.damage(enemy.break_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						DrawGraph(580, 400, braver_damage[(braver_attack_cnt - 42) / 4], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawGraph(580, 400, braver_down, true);
						}
					}

					//勇者逃走 --> 敵power attack　エフェクト
					if (effect_cnt < 56 && braver_attack_cnt > 35) {
						DrawGraph(620, 440, bite_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 45) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 1:
					//魔法使い逃走 --> 敵power attack
					if (braver_attack_cnt < 44) {
						DrawGraph(580, 400, magician_attack_ready[braver_attack_cnt / 4], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sたちは逃げ出した！", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "しかし回り込まれてしまった！！", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 44 && braver_attack_cnt < 80) {
						if (!is_damage) {
							hero.damage(enemy.break_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						DrawGraph(580, 400, magician_damage[(braver_attack_cnt - 44) / 3], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawGraph(580, 400, magician_down, true);
						}
					}

					//魔法使い逃走 --> 敵power attack　エフェクト
					if (effect_cnt < 56 && braver_attack_cnt > 35) {
						DrawGraph(620, 440, bite_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 50) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 2:
					//騎士逃走 --> 敵power attack
					if (braver_attack_cnt < 42) {
						DrawTurnGraph(580, 385, soldier_idle[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sたちは逃げ出した！", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "しかし回り込まれてしまった！！", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 42 && braver_attack_cnt < 82) {
						if (!is_damage) {
							hero.damage(enemy.break_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						DrawTurnGraph(580, 385, soldier_damage[(braver_attack_cnt - 42) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.break_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawTurnGraph(580, 385, soldier_down, true);
						}
					}

					//騎士guard --> 敵power attack　エフェクト
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

		// CPU の手が剣の時
		if (1 == play_hand_cpu) {

			if (2 == play_hand_player) {
				/*if (!is_damage) {
					enemy.damage(hero.player_attack());
					is_damage = true;
				}
				*/
				switch (player_character) {
				case 0:
					//勇者guard --> 敵speed attack
					if (braver_attack_cnt < 21) {
						DrawGraph(580, 400, braver_guard[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 21 && braver_attack_cnt < 39) {
						if (!is_damage) {
							enemy.damage(hero.guard_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは%sの攻撃を受け流し反撃した！", hero.player_name().c_str(),enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.guard_attack());
						DrawGraph(580, 400, braver_break[(braver_attack_cnt - 21) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは%sの攻撃を受け流し反撃した！", hero.player_name().c_str(), enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.guard_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 95) {
								death_cnt = 64;
							}
						}
					}

					//勇者guard --> 敵speed attack　エフェクト
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
					//魔法使いguard --> 敵speed attack
					if (braver_attack_cnt < 28) {
						DrawGraph(580, 400, magician_guard[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 28 && braver_attack_cnt < 78) {
						if (!is_damage) {
							enemy.damage(hero.guard_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは%sの攻撃を受け流し反撃した！", hero.player_name().c_str(), enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.guard_attack());
						DrawGraph(580, 400, magician_break[(braver_attack_cnt - 28) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは%sの攻撃を受け流し反撃した！", hero.player_name().c_str(), enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.guard_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}

					//魔法使いguard --> 敵speed attack　エフェクト
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
					//騎士guard --> 敵speed attack
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580, 385, soldier_attack[0], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 40) {
						if (!is_damage) {
							enemy.damage(hero.guard_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは%sの攻撃を受け流し反撃した！", hero.player_name().c_str(), enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.guard_attack());
						DrawTurnGraph(580, 385, soldier_attack[braver_attack_cnt - 20], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは%sの攻撃を受け流し反撃した！", hero.player_name().c_str(), enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.guard_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//騎士guard --> 敵speed attack　エフェクト
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
					//勇者power attack --> 敵speed attack
					if (braver_attack_cnt < 15) {
						DrawGraph(580, 400, braver_break[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 15 && braver_attack_cnt < 43) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						DrawGraph(580, 400, braver_damage[(braver_attack_cnt - 15) / 4], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawGraph(580, 400, braver_down, true);
						}
					}

					//勇者power attack --> 敵speed attack　エフェクト
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
					//魔法使いpower attack --> 敵speed attack
					if (braver_attack_cnt < 30) {
						DrawGraph(580, 400, magician_break[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 30 && braver_attack_cnt < 66) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						DrawGraph(580, 400, magician_damage[(braver_attack_cnt - 30) / 3], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawGraph(580, 400, magician_down, true);
						}
					}

					//魔法使いpower attack --> 敵speed attack　エフェクト
					if (effect_cnt < 56 && braver_attack_cnt > 16) {
						DrawGraph(620, 440, claw_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 20) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 2:
					//騎士power attack --> 敵speed attack
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580, 385, soldier_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						DrawTurnGraph(580, 385, soldier_damage[(braver_attack_cnt - 20) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawTurnGraph(580, 385, soldier_down, true);
						}
					}

					//騎士power attack --> 敵speed attack　エフェクト
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
					//勇者speed attack --> 敵speed attack 
					if (braver_attack_cnt < 18) {
						DrawGraph(580 - int(braver_attack_cnt / 18.0f * 200), 400, braver_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 18 && braver_attack_cnt < 53) {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						DrawGraph(380 + int((braver_attack_cnt - 18) / 35.0f * 125), 400, braver_jump[(braver_attack_cnt - 18) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						is_battle = false;
						DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
						braver_idle_cnt++;
						if (braver_idle_cnt == 42) {
							braver_idle_cnt = 0;
						}
					}

					//勇者speed attack --> 敵speed attack　エフェクト
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
					//魔法使いspeed attack --> 敵speed attack 
					if (braver_attack_cnt < 32) {
						DrawGraph(580 - int(braver_attack_cnt / 32.0f * 200), 400, magician_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 32 && braver_attack_cnt < 58) {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						DrawGraph(380 + int((braver_attack_cnt - 32) / 26.0f * 125), 400, magician_jump[(braver_attack_cnt - 32) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						is_battle = false;
						DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
						magician_idle_cnt++;
						if (magician_idle_cnt == 70) {
							magician_idle_cnt = 0;
						}
					}

					//魔法使いspeed attack --> 敵speed attack　エフェクト
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
					//騎士speed attack --> 敵speed attack 
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580 - int(braver_attack_cnt / 20.0f * 200), 385, soldier_attack[braver_attack_cnt], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						DrawTurnGraph(380 + int((braver_attack_cnt - 20) / 40.0f * 200), 385 - int(50 * sin((braver_attack_cnt - 20) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 12) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いの強烈な一撃がぶつかり合う！");
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "攻撃が相殺された！");
						is_battle = false;
						DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
						soldier_idle_cnt++;
						if (soldier_idle_cnt == 145) {
							soldier_idle_cnt = 0;
						}
					}

					//騎士speed attack --> 敵speed attack　エフェクト
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
					//勇者skill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは力を解放した！！", hero.player_name().c_str());
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのマーベルブレード！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与え、%d生命力を奪った！", enemy.player_name().c_str(), 2 * hero.speed_attack(), hero.speed_attack());
						DrawGraph(280 + int((braver_attack_cnt - 77) / 35.0f * 225), 400, braver_jump[(braver_attack_cnt - 77) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのマーベルブレード！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与え、%d生命力を奪った！", enemy.player_name().c_str(), 2 * hero.speed_attack(), hero.speed_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 91) {
								death_cnt = 64;
							}
						}
					}
					//勇者skill　エフェクト
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 70) {
							PlaySoundMem(braver_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//勇者skill　カットイン
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
					//魔法使いskill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは力を解放した！！", hero.player_name().c_str());
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのサンダーボルト！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
						DrawGraph(580, 400, magician_break[(braver_attack_cnt - 50) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのサンダーボルト！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}
					//魔法使いskill　エフェクト
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 80) {
							PlaySoundMem(magician_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, magician_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//魔法使いskill　カットイン
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
					//騎士skill
					if (braver_attack_cnt < 30) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは力を解放した！！", hero.player_name().c_str());
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのリベンジスラッシュ！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 50) / 40.0f * 300), 385 - int(50 * sin((braver_attack_cnt - 50) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 42) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのリベンジスラッシュ！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//騎士skill　エフェクト
					if (effect_cnt < 70 && braver_attack_cnt > 25) {
						if (braver_attack_cnt == 35) {
							PlaySoundMem(soldier_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//騎士skill　カットイン
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
					//勇者逃走 --> 敵speed attack
					if (braver_attack_cnt < 42) {
						DrawGraph(580, 400, braver_attack_ready[braver_attack_cnt / 6], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sたちは逃げ出した！", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "しかし回り込まれてしまった！！", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 42 && braver_attack_cnt < 70) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						DrawGraph(580, 400, braver_damage[(braver_attack_cnt - 42) / 4], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawGraph(580, 400, braver_down, true);
						}
					}

					//勇者逃走 --> 敵speed attack　エフェクト
					if (effect_cnt < 56 && braver_attack_cnt > 35) {
						DrawGraph(620, 440, claw_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 45) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 1:
					//魔法使い逃走 --> 敵speed attack
					if (braver_attack_cnt < 44) {
						DrawGraph(580, 400, magician_attack_ready[braver_attack_cnt / 4], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sたちは逃げ出した！", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "しかし回り込まれてしまった！！", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 44 && braver_attack_cnt < 80) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						DrawGraph(580, 400, magician_damage[(braver_attack_cnt - 44) / 3], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawGraph(580, 400, magician_down, true);
						}
					}

					//魔法使い逃走 --> 敵speed attack　エフェクト
					if (effect_cnt < 56 && braver_attack_cnt > 35) {
						DrawGraph(620, 440, claw_effect[effect_cnt / 7], true);
						if (braver_attack_cnt == 45) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 2:
					//騎士逃走 --> 敵speed attack
					if (braver_attack_cnt < 42) {
						DrawTurnGraph(580, 385, soldier_idle[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sたちは逃げ出した！", hero.player_name().c_str());
						DrawStringToHandle(70, 90, "しかし回り込まれてしまった！！", 0xffffffff, normal_str);
					}
					else if (braver_attack_cnt >= 42 && braver_attack_cnt < 82) {
						if (!is_damage) {
							hero.damage(enemy.speed_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						DrawTurnGraph(580, 385, soldier_damage[(braver_attack_cnt - 42) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの素早い一撃！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.speed_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawTurnGraph(580, 385, soldier_down, true);
						}
					}

					//騎士逃走 --> 敵speed attack　エフェクト
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

		// CPU の手が盾の時
		if (2 == play_hand_cpu) {

			if (0 == play_hand_player) {
				/*if (!is_damage) {
					enemy.damage(hero.player_attack());
					is_damage = true;
				}
				*/
				switch (player_character) {
				case 0:
					//勇者power attack --> 敵guard
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.break_attack());
						DrawGraph(280 + int((braver_attack_cnt - 27) / 35.0f * 225), 400, braver_jump[(braver_attack_cnt - 27) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.break_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 91) {
								death_cnt = 64;
							}
						}
					}

					//勇者power attack --> 敵guard　エフェクト
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
					//魔法使いpower attack --> 敵guard
					if (braver_attack_cnt < 50) {
						DrawGraph(580, 400, magician_break[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.break_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}

					//魔法使いpower attack --> 敵guard　エフェクト
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
					//騎士power attack --> 敵guard
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.break_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 20) / 40.0f * 300), 385 - int(50 * sin((braver_attack_cnt - 20) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 12) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sの強烈な一撃！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.break_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//騎士power attack --> 敵guard　エフェクト
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
					//勇者speed attack --> 敵guard
					if (braver_attack_cnt < 27) {
						DrawGraph(580 - int(braver_attack_cnt / 27.0f * 300), 400, braver_attack[braver_attack_cnt / 3], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 27 && braver_attack_cnt < 55) {
						if (!is_damage) {
							hero.damage(enemy.guard_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは反撃してきた！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.guard_attack());
						DrawGraph(280 + int((braver_attack_cnt - 27) / 28.0f * 300), 400, braver_damage[(braver_attack_cnt - 27) / 4], true);
						braver_attack_cnt++;
					}
					else {						
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは反撃してきた！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.guard_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
							braver_idle_cnt++;
							if (braver_idle_cnt == 42) {
								braver_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawGraph(580, 400, braver_down, true);
						}
					}

					//勇者speed attack --> 敵guard　エフェクト
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						if (braver_attack_cnt == 20) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 1:
					//魔法使いspeed attack --> 敵guard
					if (braver_attack_cnt < 32) {
						DrawGraph(580 - int(braver_attack_cnt / 32.0f * 300), 400 - int(100 * sin(braver_attack_cnt / 32.0f * M_PI)), magician_attack[braver_attack_cnt / 2], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 32 && braver_attack_cnt < 68) {
						if (!is_damage) {
							hero.damage(enemy.guard_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは反撃してきた！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.guard_attack());
						DrawGraph(280 + int((braver_attack_cnt - 32) / 36.0f * 300), 400, magician_damage[(braver_attack_cnt - 32) / 3], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは反撃してきた！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.guard_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
							magician_idle_cnt++;
							if (magician_idle_cnt == 70) {
								magician_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawGraph(580, 400, magician_down, true);
						}
					}

					//魔法使いspeed attack --> 敵guard　エフェクト
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						if (braver_attack_cnt == 20) {
							PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
						}
						effect_cnt++;
					}
					break;
				case 2:
					//騎士speed attack --> 敵guard
					if (braver_attack_cnt < 20) {
						DrawTurnGraph(580 - int(braver_attack_cnt / 20.0f * 300), 385, soldier_attack[braver_attack_cnt], true);
						braver_attack_cnt++;
					}
					else if (braver_attack_cnt >= 20 && braver_attack_cnt < 60) {
						if (!is_damage) {
							hero.damage(enemy.guard_attack());
							is_damage = true;
						}
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは反撃してきた！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.guard_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 20) / 40.0f * 310), 385, soldier_damage[(braver_attack_cnt - 20) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは反撃してきた！", enemy.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%dのダメージを受けた！", hero.player_name().c_str(), enemy.guard_attack());
						is_battle = false;
						if (hero.player_hp() > 0) {
							DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
							soldier_idle_cnt++;
							if (soldier_idle_cnt == 145) {
								soldier_idle_cnt = 0;
							}
						}
						else {
							//敗北表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sは倒れた…", hero.player_name().c_str());
							DrawTurnGraph(580, 385, soldier_down, true);
						}
					}

					//騎士speed attack --> 敵guard　エフェクト
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
					//勇者guard --> 敵guard
					if (braver_attack_cnt < 49) {
						DrawGraph(580, 400, braver_guard[braver_attack_cnt / 7], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いに反撃の機会をうかがっている！");
						is_battle = false;
						DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
						braver_idle_cnt++;
						if (braver_idle_cnt == 42) {
							braver_idle_cnt = 0;
						}
					}

					//勇者guard --> 敵guard　エフェクト
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						DrawGraph(580, 440, guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				case 1:
					//魔法使いguard --> 敵guard
					if (braver_attack_cnt < 70) {
						DrawGraph(580, 400, magician_guard[braver_attack_cnt / 5], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いに反撃の機会をうかがっている！");
						is_battle = false;
						DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
						magician_idle_cnt++;
						if (magician_idle_cnt == 70) {
							magician_idle_cnt = 0;
						}
					}

					//魔法使いguard --> 敵guard　エフェクト
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						DrawGraph(580, 440, guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				case 2:
					//騎士guard --> 敵guard
					if (braver_attack_cnt < 49) {
						DrawTurnGraph(580, 385, soldier_attack[0], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "互いに反撃の機会をうかがっている！");
						is_battle = false;
						DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
						soldier_idle_cnt++;
						if (soldier_idle_cnt == 145) {
							soldier_idle_cnt = 0;
						}
					}

					//騎士guard --> 敵guard　エフェクト
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
					//勇者skill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは力を解放した！！", hero.player_name().c_str());
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのマーベルブレード！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与え、%d生命力を奪った！", enemy.player_name().c_str(), 2 * hero.speed_attack(), hero.speed_attack());
						DrawGraph(280 + int((braver_attack_cnt - 77) / 35.0f * 225), 400, braver_jump[(braver_attack_cnt - 77) / 5], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのマーベルブレード！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与え、%d生命力を奪った！", enemy.player_name().c_str(), 2 * hero.speed_attack(), hero.speed_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, braver_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 91) {
								death_cnt = 64;
							}
						}
					}
					//勇者skill　エフェクト
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 70) {
							PlaySoundMem(braver_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//勇者skill　カットイン
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
					//魔法使いskill
					if (braver_attack_cnt < 50) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは力を解放した！！", hero.player_name().c_str());
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのサンダーボルト！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
						DrawGraph(580, 400, magician_break[(braver_attack_cnt - 50) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのサンダーボルト！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawGraph(580, 400, magician_victory[(death_cnt - 64) / 4], true);
							if (death_cnt == 131) {
								death_cnt = 64;
							}
						}
					}
					//魔法使いskill　エフェクト
					if (effect_cnt < 70 && braver_attack_cnt > 60) {
						if (braver_attack_cnt == 80) {
							PlaySoundMem(magician_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, magician_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//魔法使いskill　カットイン
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
					//騎士skill
					if (braver_attack_cnt < 30) {
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sは力を解放した！！", hero.player_name().c_str());
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
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのリベンジスラッシュ！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
						DrawTurnGraph(280 + int((braver_attack_cnt - 50) / 40.0f * 300), 385 - int(50 * sin((braver_attack_cnt - 50) / 40.0f * M_PI)), soldier_victory[(braver_attack_cnt - 42) / 2], true);
						braver_attack_cnt++;
					}
					else {
						//戦闘の文章描画
						DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sのリベンジスラッシュ！！", hero.player_name().c_str());
						DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sに%dのダメージを与えた！", enemy.player_name().c_str(), hero.skill_attack());
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
							//勝利表記の描画
							DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sを倒した！！", enemy.player_name().c_str());
							is_battle = false;
							DrawTurnGraph(580, 385, soldier_victory[(death_cnt - 64) / 3], true);
							if (death_cnt == 138) {
								death_cnt = 64;
							}
						}
					}

					//騎士skill　エフェクト
					if (effect_cnt < 70 && braver_attack_cnt > 25) {
						if (braver_attack_cnt == 35) {
							PlaySoundMem(soldier_skill_sound, DX_PLAYTYPE_BACK);
						}
						DrawGraph(90, 320, braver_skill_effect[effect_cnt / 7], true);
						effect_cnt++;
					}

					//騎士skill　カットイン
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
					//勇者逃走 --> 敵guard
					//戦闘の文章描画
					DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sたちは逃げ出した！", hero.player_name().c_str());
					DrawStringToHandle(70, 90, "しかし回り込まれてしまった！！", 0xffffffff, normal_str);
					DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sはこちらの様子をうかがっている！", enemy.player_name().c_str());
					is_battle = false;
					DrawGraph(580, 400, braver_attack_ready[braver_idle_cnt / 6], true);
					braver_idle_cnt++;
					if (braver_idle_cnt == 42) {
						braver_idle_cnt = 0;
					}
					
					//勇者逃走 --> 敵guard　エフェクト
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				case 1:
					//魔法使い逃走 --> 敵guard
					//戦闘の文章描画
					DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sたちは逃げ出した！", hero.player_name().c_str());
					DrawStringToHandle(70, 90, "しかし回り込まれてしまった！！", 0xffffffff, normal_str);
					DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sはこちらの様子をうかがっている！", enemy.player_name().c_str());
					is_battle = false;
					DrawGraph(580, 400, magician_attack_ready[magician_idle_cnt / 5], true);
					magician_idle_cnt++;
					if (magician_idle_cnt == 70) {
						magician_idle_cnt = 0;
					}

					//魔法使い逃走 --> 敵guard　エフェクト
					if (effect_cnt < 60) {
						DrawGraph(200, 410, enemy_guard_effect[effect_cnt / 6], true);
						effect_cnt++;
					}
					break;
				case 2:
					//騎士逃走 --> 敵guard
					//戦闘の文章描画
					DrawFormatStringToHandle(70, 50, 0xffffffff, normal_str, "%sたちは逃げ出した！", hero.player_name().c_str());
					DrawStringToHandle(70, 90, "しかし回り込まれてしまった！！", 0xffffffff, normal_str);
					DrawFormatStringToHandle(70, 130, 0xffffffff, normal_str, "%sはこちらの様子をうかがっている！", enemy.player_name().c_str());
					is_battle = false;
					DrawTurnGraph(580, 385, soldier_idle[soldier_idle_cnt / 5], true);
					soldier_idle_cnt++;
					if (soldier_idle_cnt == 145) {
						soldier_idle_cnt = 0;
					}

					//騎士逃走 --> 敵guard　エフェクト
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

		//プレイヤーのHPゲージ
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
		//プレイヤーのHPの割合を表示（Debug用）
		//DrawStringEx(100, 100, 0x00000000, "%d", hero.player_hp_percentage());

		//手数の描画
		DrawRotaGraph(40, 730, 0.5, 0, hammer_img[0], true, false);
		DrawFormatStringToHandle(70, 710, 0x00000000, emp_str, "×%d", hero.break_count());
		DrawRotaGraph(200, 730, 0.5, 0, sword_img[0], true, false);
		DrawFormatStringToHandle(230, 710, 0x00000000, emp_str, "×%d", hero.attack_count());
		DrawRotaGraph(360, 730, 0.5, 0, shield_img[0], true, false);
		DrawFormatStringToHandle(390, 710, 0x00000000, emp_str, "×%d", hero.guard_count());

		//敵が消えたら勝利BGMを流す
		if (CheckSoundMem(battle_victory_bgm) == 0 && death_cnt >= 64) {
			StopSoundMem(battle1_bgm);
			PlaySoundMem(battle_victory_bgm, DX_PLAYTYPE_LOOP);
		}

		/*　デバッグ用
		if (0 == win_or_lose_or_drow) {
			DrawStringEx(460, 340, 0xffffffff, "あなたの勝ち");
		}
		if (1 == win_or_lose_or_drow) {
			DrawStringEx(460, 340, 0xffffffff, "CPU の勝ち");
		}
		if (2 == win_or_lose_or_drow) {
			DrawStringEx(480, 340, 0xffffffff, "あいこ");
		}

		DrawFormatStringToHandle(0, 0, 0x00000000, normal_str, "主人公の体力：%d", hero.player_hp());
		DrawFormatStringToHandle(10, 10, 0x00000000, normal_str, "%sの体力：%d", enemy.player_name().c_str(),enemy.player_hp());
		DrawFormatStringToHandle(20, 20, 0x00000000, normal_str, "主人公の攻撃力：%d", hero.player_attack());
		DrawFormatStringToHandle(60, 50, 0x00000000, normal_str, "敵の攻撃力：%d", enemy.player_attack());

		DrawFormatStringToHandle(100, 350, 0x00000000, normal_str, "break_cnt：%d", hero.break_count());
		DrawFormatStringToHandle(100, 400, 0x00000000, normal_str, "attack_cnt：%d", hero.attack_count());
		DrawFormatStringToHandle(100, 450, 0x00000000, normal_str, "guard_cnt：%d", hero.guard_count());

		//DrawStringEx(450, 560, 0xffffffff, "あなた の手");

		DrawStringEx(390, 630, 0xffffffff, "エンターキーを押してください");
		*/

		// プレイヤーまたは敵のHPが0になったらゲームオーバー画面またはマップに戻る
		// まだなら手選択へ
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
		//戦闘開始時のアニメーション
		//敵の描画
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

		//経験値獲得処理
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
		DrawFormatStringToHandle(150, 580, 0xffffffff, window_emp_str, "次のレベルまで %d", hero.player_next_exp());
		DrawFormatStringToHandle(150, 630, 0xffffffff, window_emp_str, "獲得経験値 %d", enemy.player_exp());


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
		//ヒロインの回復呪文
		DrawGraph(0, 10, window_img, true);

		//プレイヤーキャラの描画
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

		//プレイヤーのHPゲージ
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
		//プレイヤーのHPの割合を表示（Debug用）
		//DrawStringEx(100, 100, 0x00000000, "%d", hero.player_hp_percentage());

		//敵キャラの描画
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

		//ヒロインに関する描画
		DrawGraph(607, 186, heroine_window3, true);
		DrawGraph(627, 216, heroine_battle[1], true);

		if (heroine_heal_cnt != 0 || is_healed) {
			//回復処理＆アニメーション
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

			DrawStringToHandle(710, 230, "回復するよ！！", 0xffffffff, window_str);

			DrawFormatStringToHandle(70, 50, 0xffffffff, window_str,"%sはヒールを唱えた！！",heroine_name.c_str());
			if (heal_cnt == 64) {
				DrawFormatStringToHandle(70, 90, 0xffffffff, normal_str, "%sは%d回復した！！", hero.player_name().c_str(), heal_point);
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
			DrawFormatStringToHandle(70, 50, 0xffffffff, window_str, "%sはヒールを唱えようとした！", heroine_name.c_str());
			DrawStringToHandle(70, 90, "しかし魔力が足りない…", 0xffffffff, window_str);
			DrawStringToHandle(710, 230, "もう無理みたい…", 0xffffffff, window_str);

			if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
				PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
				heal_cnt = 0;
				play_sequence = 0;
			}
		}

		break;
	case 5:
		//逃走成功
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
		DrawFormatStringToHandle(70, 50, 0xffffffff, window_str, "%sたちは逃げ出した！！", hero.player_name().c_str());

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
		//ヒロインのライブラ処理

		DrawGraph(0, 10, heroine_window, true);
		DrawGraph(58, 68, heroine[1], true);

		DrawFormatStringToHandle(158, 40, 0xffffffff, window_str, "＜%s＞", enemy.player_name().c_str());
		switch (enemy_number) {
		case -1:
			DrawStringToHandle(158, 80, "ニワトリの魔物よ", 0xffffffff, window_str);
			DrawStringToHandle(158, 120, "力任せの攻撃が多いみたいね", 0xffffffff, window_str);
			break;
		case -2:
			DrawStringToHandle(158, 80, "オオカミの魔物よ", 0xffffffff, window_str);
			DrawStringToHandle(158, 120, "素早い攻撃が多いみたいね", 0xffffffff, window_str);
			break;
		case -3:
			DrawStringToHandle(158, 80, "ユーレイの魔物よ", 0xffffffff, window_str);
			DrawStringToHandle(158, 120, "身を守っていることが多いみたいね", 0xffffffff, window_str);
			break;
		default:
			break;
		}

		if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
			play_sequence = 0;
		}

		//プレイヤーキャラの描画
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

		//プレイヤーのHPゲージ
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
		//プレイヤーのHPの割合を表示（Debug用）
		//DrawStringEx(100, 100, 0x00000000, "%d", hero.player_hp_percentage());

		//敵キャラの描画
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

