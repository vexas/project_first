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


// ゲームの初期化フラグ
extern int is_init;

// シーンを制御する変数
// この変数の値
// 0 : タイトル
// 1 : プレイ画面
// 2 : リザルト画面
extern int scene;
extern int pre_scene;

//フォントのハンドル
extern int title_str;
extern int emp_str;
extern int subtitle_str;
extern int normal_str;
extern int window_str;
extern int window_emp_str;

// 手の画像
extern int cursor_right[3];
extern int sword_img[20];
extern int shield_img[20];
extern int hammer_img[20];
extern int small_sword_img[20];
extern int small_shield_img[20];
extern int small_hammer_img[20];

//背景の画像
extern int field_img;
extern int window_img;
extern int hp_gauge;
extern int hp_gauge_edge;
extern int window_all;
extern int window_menu;
extern int heroine_window2;

//エフェクトの画像
extern int attack_effect[5];
extern int break_effect[7];
extern int guard_effect[10];
extern int claw_effect[10];
extern int bite_effect[10];
extern int enemy_guard_effect[10];
extern int tale_effect[10];
extern int collide_effect[5];

//マップでの音楽
extern int main_map_bgm;

//効果音
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

//HPゲージの色を管理する変数
extern float hp_color_manager;
extern int enemy_hp_width;

// カーソルの画像
extern int gfx_cursor;

// プレイ画面でのシーケンス用変数
// 0 : プレイヤの手選択シーケンス
// 1 : 結果表示
extern int play_sequence;

// プレイヤーの手
// 0 : グー
// 1 : チョキ
// 2 : パー
extern int play_hand_player;

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

//プレイヤーのキャラの種類
// 0：勇者
// 1：魔法使い
// 2：騎士
extern int player_character;

//敵キャラの種類
// -1：鶏っぽいの
// -2：呪術師っぽいの
// -3：ドラゴン
// -4：魔王
// -5：魔王第二形態
extern int enemy_character;

//プレイヤークラス
extern player hero;
extern player enemy;

//プレイヤーの画像
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

//敵の画像
extern int bird_img;

// CPU の手
extern int play_hand_cpu;

// ジャンケンをした回数
extern int turn_count;

// 勝った回数
extern int play_win_count;

// 負けた回数
extern int play_lose_count;

//勝利判定
extern bool is_player_win;

//フラグ管理
extern bool is_damage;
extern bool is_init_char;

//マップ
extern int main_map_chip_number[3000];
extern int main_map_chip_above_number[3000];

//マップチップ
extern int map_chip[160];

//キャラクターの位置
extern int player_pos_x;
extern int player_pos_y;

//キャラクターの移動量
extern int scroll_x;
extern int scroll_y;

// 移動しているかどうかのフラグ( 0:停止中  1:移動中 )
extern bool is_move;
extern bool is_right;
extern bool is_walk;
int walk_cnt = 0;

// 各方向に移動する量
extern int move_x, move_y;

// 移動し始めてから何フレーム経過したかを保持する変数
extern int move_cnt_frame;

//プレイヤーの移動前の位置を格納する変数
extern float moving_player_pos_x;
extern float moving_player_pos_y;

//マップの当たり判定
extern bool is_penetrate[160];

//乱数関係
extern std::mt19937 machine;
extern std::uniform_int_distribution<int> random_number;

//エンカウントのフラグ
bool is_encount = false;

//ヒロインのアニメーション制御変数
extern int heroine_cnt;
extern bool heroine_walk_flag;

//メニュー画面のカーソル
extern int cursor;

//マップ内シーン遷移管理変数
int map_scene = 0;
bool is_heal = false;

//ヒロインの回復呪文の回数
extern int heroine_heal_cnt;


void main_map() {

	switch (map_scene) {
	case 0:
		//バトル画面から遷移してきた場合のfade_in
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

		//町またはダンジョンから遷移してきた場合のfade_in
		//始まりの町から
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

		// 移動中ではない場合キー入力を受け付ける
		if (!is_move)
		{
			if (walk_cnt < 10) {
				walk_cnt++;
			}
			// キー入力に応じてプレイヤーの座標を移動
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

			// 停止中は画面のスクロールは行わない
			scroll_x = 0;
			scroll_y = 0;
		}

		// 移動中の場合は移動処理を行う
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

			// 移動処理が終了したら停止中にする
			if (move_cnt_frame == MOVE_FRAME)
			{
				is_move = false;

				// プレイヤーの位置を変更する
				player_pos_x += move_x;
				player_pos_y += move_y;
				move_x = 0;
				move_y = 0;

				//ランダムエンカウントの判定
				if (random_number(machine) <= 5) {
					is_encount = true;
				}

				// 停止中は画面のスクロールは行わない
				scroll_x = 0;
				scroll_y = 0;
			}
			else
			{
				// 経過時間からスクロール量を算出する
				scroll_x = -(move_x * 32 * float(move_cnt_frame) / MOVE_FRAME);
				scroll_y = -(move_y * 32 * float(move_cnt_frame) / MOVE_FRAME);
			}
		}

		//描画されない領域の描画（海）
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
		//キャラクターとマップの描画
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

		//町またはダンジョンに入ったらエンカウント処理を行わずシーン遷移

		//始まりの町
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


		//Xが押されたらメニュー画面（エンカウントしておらず町などにシーン遷移していない状態）
		if (!is_encount && scene != 110 && IsKeyDownTrigger(KEY_INPUT_X)) {
			PlaySoundMem(decide_sound, DX_PLAYTYPE_BACK);
			map_scene = 1;
		}

		break;
	case 1:

		//背景の描画
		DrawGraph(0, 0, field_img, true);
		DrawGraph(0, -15, window_all, true);

		//ヒロインの描画（説明役）
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

		//Xが押されたらメニュー画面を閉じる
		if (IsKeyDownTrigger(KEY_INPUT_X)) {
			PlaySoundMem(cancel_sound, DX_PLAYTYPE_BACK);
			map_scene = 0;
		}

		DrawGraph(670, 50, window_menu, true);

		//選択内容の表示
		DrawStringToHandle(740, 90, "話す", 0xffffffff, window_str);
		DrawStringToHandle(740, 150, "回復", 0xffffffff, window_str);
		DrawStringToHandle(740, 210, "強さ", 0xffffffff, window_str);
		DrawStringToHandle(740, 270, "セーブ", 0xffffffff, window_str);
		DrawStringToHandle(740, 330, "ロード", 0xffffffff, window_str);
		DrawStringToHandle(740, 390, "タイトル", 0xffffffff, window_str);

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
			DrawStringToHandle(210, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "「私と雑談しよう！」", 0xffffffff, window_str);
			DrawGraph(700, 90, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 1) {
			DrawStringToHandle(210, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "「私の呪文で回復するよ！」", 0xffffffff, window_str);
			DrawGraph(700, 150, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 2) {
			DrawStringToHandle(210, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "「あなたの強さを確認するよ！」", 0xffffffff, window_str);
			DrawGraph(700, 210, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 3) {
			DrawStringToHandle(210, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "「冒険を記録するよ！」", 0xffffffff, window_str);
			DrawGraph(700, 270, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 4) {
			DrawStringToHandle(210, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "「冒険の記録を読み込むよ！」", 0xffffffff, window_str);
			DrawGraph(700, 330, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 5) {
			DrawStringToHandle(210, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "「冒険を終了するよ！", 0xffffffff, window_str);
			DrawStringToHandle(220, 680, "　セーブを忘れないでね！」", 0xffffffff, window_str);
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
		//話すコマンド

		//背景の描画
		DrawGraph(0, 0, field_img, true);
		DrawGraph(0, -15, window_all, true);

		//ヒロインの描画（説明役）
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

		DrawStringToHandle(210, 600, "ヒロイン", 0xffffffff, window_str);
		DrawStringToHandle(220, 640, "「てすと！」", 0xffffffff, window_str);

		if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
			map_scene = 1;
		}
		break;
	case 3:
		//回復コマンド
		//背景の描画
		DrawGraph(0, 0, field_img, true);
		DrawGraph(0, -15, window_all, true);

		//ヒロインの描画（説明役）
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

				//選択内容の表示
				DrawStringToHandle(740, 90, "はい", 0xffffffff, window_str);
				DrawStringToHandle(740, 150, "いいえ", 0xffffffff, window_str);

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

				DrawStringToHandle(210, 600, "ヒロイン", 0xffffffff, window_str);
				DrawFormatStringToHandle(220, 640, 0xffffffff, window_str, "「後%d回唱えられるけど", heroine_heal_cnt);
				DrawStringToHandle(220, 680, "　回復する？」", 0xffffffff, window_str);

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
				DrawStringToHandle(210, 600, "ヒロイン", 0xffffffff, window_str);
				DrawFormatStringToHandle(220, 640, 0xffffffff, window_str, "「もう魔力が残ってないの", heroine_heal_cnt);
				DrawStringToHandle(220, 680, "　ごめんね…」", 0xffffffff, window_str);

				if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
					map_scene = 1;
				}

			}
		}
		else {
			DrawStringToHandle(210, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(220, 640, "「回復したよ！！」", 0xffffffff, window_str);

			if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
				is_heal = false;
				map_scene = 1;
			}

		}

		break;
	case 4:
		//強さコマンド
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
		DrawFormatStringToHandle(150, 580, 0xffffffff, window_emp_str, "次のレベルまで %d", hero.player_next_exp());

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
		//セーブコマンド
		break;
	case 6:
		//ロードコマンド
		break;
	case 7:
		//タイトルコマンド
		break;
	default:
		break;
	}
}