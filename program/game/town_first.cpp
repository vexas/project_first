#include "Dxlib.h"
#include "town_first.h"
#include "fade_in.h"
#include "fade_out.h"
#include "player.h"
#include "../support/Support.h"
#include <random>

//シーン遷移制御変数
extern int scene;
extern int pre_scene;

//プレイヤーキャラ
extern player hero;

//画像
extern int town_img;
extern int window_img;
extern int window_img2;
extern int heroine_window;
extern int cursor_right[3];
extern int heroine[12];

//フォントのハンドル
extern int title_str;
extern int emp_str;
extern int subtitle_str;
extern int normal_str;
extern int window_str;
extern int window_emp_str;

//BGM
extern int char_select_bgm;

//効果音
extern int decide_sound;
extern int select_sound;
extern int player_select_sound;
extern int heal_sound;

//乱数関係
extern std::mt19937 machine;
extern std::uniform_int_distribution<int> random_number;

//カーソル制御の変数
extern int cursor_cnt;
int town_scene = 0;
extern int cursor;

//アニメーション制御の変数
extern int heroine_cnt;
extern bool heroine_walk_flag;
extern int heal_cnt;
bool heal_flag = false;

//ヒロインの回復呪文の回数
extern int heroine_heal_cnt;


void town_first(){

	//町に入る際のfade_in
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
		//町のUI
		DrawGraph(0, 0, town_img, true);
		DrawGraph(0, 10, window_img, true);
		DrawGraph(710, 251, window_img2, true);
		DrawGraph(0, 580, heroine_window, true);
		DrawGraph(68, 628, heroine[heroine_cnt / 20], true);

		//町の様子を表す文の表示
		DrawStringToHandle(130, 50, "港町は大勢の人で賑わっている…", 0xffffffff, window_str);
		//選択内容の表示
		DrawStringToHandle(780, 290, "宿屋", 0xffffffff, window_str);
		DrawStringToHandle(780, 330, "酒場", 0xffffffff, window_str);
		DrawStringToHandle(780, 370, "町を出る", 0xffffffff, window_str);

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
			DrawStringToHandle(160, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(170, 640, "「休息をとって回復するよ！", 0xffffffff, window_str);
			DrawStringToHandle(170, 680, "　疲れた時は無理しないで休もうね」", 0xffffffff, window_str);
			DrawGraph(740, 290, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 1) {
			DrawStringToHandle(160, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(170, 640, "「酒場にいる人たちから話を聞けるよ！", 0xffffffff, window_str);
			DrawStringToHandle(170, 680, "　役に立つことが聞けるかも…」", 0xffffffff, window_str);
			DrawGraph(740, 330, cursor_right[cursor_cnt / 12], true);
		}
		if (cursor == 2) {
			DrawStringToHandle(160, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(170, 640, "「冒険に出発するよ！", 0xffffffff, window_str);
			DrawStringToHandle(170, 680, "　秘薬を求めて頑張ろうね！！」", 0xffffffff, window_str);
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
		//宿屋での回復処理
		if (!heal_flag) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 254 - heal_cnt * 4);
			DrawGraph(0, 0, town_img, true);
			DrawGraph(0, 10, window_img, true);
			DrawGraph(710, 251, window_img2, true);
			DrawGraph(0, 580, heroine_window, true);
			DrawGraph(68, 628, heroine[heroine_cnt / 20], true);
			DrawStringToHandle(160, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(170, 640, "「おやすみなさい！」", 0xffffffff, window_str);
			heal_cnt++;
			if (CheckSoundMem(heal_sound) == 0) {
				PlaySoundMem(heal_sound, DX_PLAYTYPE_BACK);
			}
			// ブレンドモードを元に戻す
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
			DrawStringToHandle(160, 600, "ヒロイン", 0xffffffff, window_str);
			DrawStringToHandle(170, 640, "「おはよう！」", 0xffffffff, window_str);
			heal_cnt++;
			// ブレンドモードを元に戻す
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
		//町のUI
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