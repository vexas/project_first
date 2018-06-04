#include "DxLib.h"
#include "game_main.h"
#include "scene_play.h"
#include "main_map.h"
#include "draw_map.h"
#include "town_first.h"
#include "player.h"
#include "fade_out.h"
#include "../support/Support.h"
#include <time.h>
#include <math.h>
#include <string>
#include <random>

//-----------------------------------------------------------------------------
//
//  ゲーム全体で使用する変数
//

// ゲームの初期化フラグ
int is_init = false ;

//タイトル画面での点滅を制御する変数
int title_counter = 0;
bool is_print = true;

//文字の色
int color_blue = 0;
int color_red = 0;

//フォントのハンドル
int title_str = 0;
int emp_str = 0;
int subtitle_str = 0;
int normal_str = 0;
int window_str = 0;
int window_emp_str = 0;


// シーンを制御する変数
// この変数の値
// 0 : タイトル
// 1 : バトル画面
// 2 : リザルト画面
//100: メインマップ
//110: 始まりの町
int scene = 0 ;
int pre_scene = 0;

//HPゲージの色を管理する変数
float hp_color_manager;
int enemy_hp_width = 200;


// 手の画像
int gfx_rock = 0 ;
int gfx_scissors = 0 ;
int gfx_paper = 0 ;
int sword_img[20];
int shield_img[20];
int hammer_img[20];
int small_sword_img[20];
int small_shield_img[20];
int small_hammer_img[20];

//タイトル画面、ゲームオーバー画面、背景の画像
int title_img = 0;
int fade_out_title_img = 0;
int gameover_img = 0;
int town_img = 0;
int field_img = 0;
int window_img = 0;
int window_img2 = 0;
int window_all = 0;
int window_menu = 0;
int heroine_window = 0;
int heroine_window2 = 0;
int heroine_window3 = 0;
int title_dot1 = 0;
int title_dot2 = 0;
int title_dot3 = 0;
int hp_gauge = 0;
int hp_gauge_edge = 0;
int crystal[40];
int cut_in_img = 0;
int fade_out_img = MakeGraph(1024, 768);

//キャラの画像
int braver_idle[10];
int braver_idle_map[10];
int braver_run[10];
int braver_walk[15];
int braver_walk_map[15];
int braver_hp_1;
int braver_hp_2;
int braver_attack_ready[10];
int braver_attack[10];
int braver_break[10];
int braver_guard[10];
int braver_jump[10];
int braver_damage[10];
int braver_down;
int braver_victory[10];
int braver_cut_in;
int braver_skill[10];
int braver_skill_effect[10];
int braver_charge[10];
int magician_idle[16];
int magician_idle_map[16];
int magician_run[10];
int magician_walk[15];
int magician_walk_map[15];
int magician_hp_1;
int magician_hp_2;
int magician_attack_ready[16];
int magician_attack[20];
int magician_break[25];
int magician_guard[15];
int magician_jump[20];
int magician_damage[15];
int magician_down;
int magician_victory[20];
int magician_magic[10];
int magician_cut_in;
int magician_skill[10];
int magician_skill_effect[10];
int magician_charge[10];
int soldier_idle[30];
int soldier_idle_map[30];
int soldier_walk[25];
int soldier_walk_map[25];
int soldier_attack[20];
int soldier_damage[20];
int soldier_down;
int soldier_victory[25];
int soldier_charge;
int soldier_hp_1;
int soldier_hp_2;
int soldier_cut_in;
int archer_idle[16];
int heroine[12];
int heroine_battle[12];
int cursor_up[3];
int cursor_down[3];
int cursor_right[3];

//敵の画像
int enemy1_img = 0;
int enemy2_img = 0;
int enemy3_img = 0;

//エフェクトの画像
int attack_effect[5];
int break_effect[7];
int guard_effect[10];
int claw_effect[10];
int bite_effect[10];
int enemy_guard_effect[10];
int tale_effect[10];
int collide_effect[5];
int heal_effect[8];

//音声
int title_bgm = 0;
int char_select_bgm = 0;
int battle1_bgm = 0;
int battle2_bgm = 0;
int battle_victory_bgm = 0;
int clear_bgm = 0;
int gameover_bgm = 0;
int main_map_bgm = 0;

//効果音
int slash_sound = 0;
int collide_sound = 0;
int damage_sound = 0;
int decide_sound = 0;
int select_sound = 0;
int start_sound = 0;
int player_select_sound = 0;
int break_sound = 0;
int braver_skill_sound = 0;
int magician_attack_sound = 0;
int magician_break_sound = 0;
int magician_skill_sound = 0;
int soldier_skill_sound = 0;
int skill_start_sound = 0;
int enemy_dead_sound = 0;
int encount_sound = 0;
int level_up_sound = 0;
int heal_sound = 0;
int cancel_sound = 0;
int escape_sound = 0;


//アニメーション制御の変数
int title_alpha_cnt = 0;
int crystal_cnt = 0;
int braver_idle_cnt = 0;
int braver_attack_cnt = 0;
int magician_idle_cnt = 0;
int soldier_idle_cnt = 0;
int archer_idle_cnt = 0;
int cursor_cnt = 0;
int attack_cnt = 0;
int guard_cnt = 0;
int break_cnt = 0;
int effect_cnt = 0;
int death_cnt = 0;
int cut_in_cnt = 0;
int heroine_cnt = 10;
bool heroine_walk_flag = true;
int heal_cnt = 0;

// カーソルの画像
int gfx_cursor = 0 ;
int cursor = 0;

//キャラクターのクラス
player hero;
player enemy;

//ヒロインの名前
std::string heroine_name = "ヒロイン";


//-----------------------------------------------------------------------------
//
//  プレイ画面に関する変数
//

// プレイ画面でのシーケンス用変数
// 0 : プレイヤの手選択シーケンス
// 1 : 結果表示
int play_sequence = 0 ;

// プレイヤーの手
// 0 : グー
// 1 : チョキ
// 2 : パー
int play_hand_player = 0 ;

//コンティニューするかタイトル画面に戻るか
bool is_continue = true;

//プレイヤーのキャラ
// 0 : 勇者
// 1 : 魔法使い
// 2 : 戦士
int player_character = 0;

//敵キャラの種類
// -1：鶏っぽいの
// -2：呪術師っぽいの
// -3：ドラゴン
// -4：魔王
// -5：魔王第二形態
int enemy_character;

// CPU の手
int play_hand_cpu = 0 ;

// ジャンケンをした回数
int turn_count = 0 ;

// 勝った回数
int play_win_count = 0 ;

// 負けた回数
int play_lose_count = 0 ;

//勝利判定
bool is_player_win;

//フラグ
bool is_damage = false;
bool is_init_char = false;
bool is_init_battle = false;

//キャラクターのマップ上での位置
int player_pos_x = 7;
int player_pos_y = 12;
float moving_player_pos_x = 7;
float moving_player_pos_y = 12;

//画面のスクロール量
int scroll_x;
int scroll_y;

// 移動しているかどうかのフラグ( 0:停止中  1:移動中 )
bool is_move = false;
bool is_right = true;
bool is_walk = false;

// 各方向に移動する量
int move_x = 0;
int move_y = 0;

// 移動し始めてから何フレーム経過したかを保持する変数
int move_cnt_frame;

//マップ（マップチップの番号を保存）
int main_map_chip_number[3000];
int main_map_chip_above_number[3000];

//マップチップの当たり判定を格納する配列
bool is_penetrate[160] = {true,true,true,true,true,true,true,true,
						  false,false,false,false,false,false,false,false,
						  true,true,true,true,false,true,true,true,
						  true,true,true,true,true,true,true,true,
						  false,false,false,false,false,false,false,false,
						  false,false,false,false,false,false,true,true,
					      true,true,true,true,true,true,true,true, 
						  true,true,true,true,true,true,true,true,
						  true,true,true,true,false,false,false,false, 
						  true,true,true,true,true,true,true,true, 
						  true,true,true,true,true,true,true,true, 
						  true,true,true,true,true,true,true,true, 
						  true,true,true,true,true,true,true,true, 
						  true,true,true,true,true,true,true,true, 
						  true,true,true,true,true,true,true,true, 
						  true,true,true,true,true,true,true,true, 
						  true,true,true,true,true,true,true,true, 
						  false,false,false,false,false,false,false,false, 
						  false,false,false,false,false,false,false,false, 
						  false,false,false,false,false,false,false,false, };

//ただの入れ物
int var1,var2;

//マップを構成するチップ番号格納しているテキストファイルを読み込む
FILE *fp;
FILE *gp;

//マップチップ
int map_chip[160];

//乱数関係（一様分布）
std::mt19937 machine{ std::random_device{}() };
std::uniform_int_distribution<int> random_number(1, 100);
std::uniform_int_distribution<int> random_level_up(-3, 3);

//ヒロインの呪文回数
int heroine_heal_cnt = 3;

//=============================================================================
// name... game_main
// work... ゲームのメインループ
// arg.... none
// ret.... [ 正常終了 : 0 ]
//=============================================================================
int game_main()
{

	//----------------------------------------------------------------------------------------------------
	// ゲーム起動時の初期化処理
	if( false == is_init ) {

		// 乱数シードの設定
		srand( time(NULL) ) ;

		// 画像のロード
		gfx_rock = LoadGraph( "rock.png", true ) ;
		gfx_scissors = LoadGraph( "scissors.png", true ) ;
		gfx_paper = LoadGraph( "paper.png", true ) ;
		gfx_cursor = LoadGraph( "cursor.png", true ) ;

		LoadDivGraph("graphics/sword.png", 20, 5, 4, 200, 200, sword_img);
		LoadDivGraph("graphics/shield.png", 20, 5, 4, 200, 200, shield_img);
		LoadDivGraph("graphics/hammer.png", 20, 5, 4, 200, 200, hammer_img);
		LoadDivGraph("graphics/sword_small.png", 20, 5, 4, 100, 100, small_sword_img);
		LoadDivGraph("graphics/shield_small.png", 20, 5, 4, 100, 100, small_shield_img);
		LoadDivGraph("graphics/hammer_small.png", 20, 5, 4, 100, 100, small_hammer_img);

		title_img = LoadGraph("graphics/title.png", true);
		fade_out_title_img = LoadGraph("graphics/fade_out_title_img.png", true);
		LoadDivGraph("graphics/crystal.png", 40, 8, 5, 400, 400,crystal);
		gameover_img = LoadGraph("graphics/gameover.png", true);
		town_img = LoadGraph("graphics/town.jpg", true);
		field_img = LoadGraph("graphics/field.jpg", true);
		window_img = LoadGraph("graphics/window_fantasy.png", true);
		window_img2 = LoadGraph("graphics/window_talking.png", true);
		window_all = LoadGraph("graphics/window_all.png", true);
		window_menu = LoadGraph("graphics/window_menu.png", true);
		heroine_window = LoadGraph("graphics/heroine_window.png", true);
		heroine_window2 = LoadGraph("graphics/heroine_window_second.png", true);
		heroine_window3 = LoadGraph("graphics/heroine_window_third.png", true);
		title_dot1 = LoadGraph("graphics/title_dot1.png", true);
		title_dot2 = LoadGraph("graphics/title_dot2.png", true);
		title_dot3 = LoadGraph("graphics/title_dot3.png", true);
		hp_gauge = LoadGraph("graphics/hp_gauge.png", true);
		hp_gauge_edge = LoadGraph("graphics/hp_gauge_edge.png", true);
		braver_hp_1 = LoadGraph("graphics/P01/braver_hp_1.png", true);
		braver_hp_2 = LoadGraph("graphics/P01/braver_hp_2.png", true);
		braver_cut_in = LoadGraph("graphics/P01/braver_cut_in_img.png", true);
		magician_hp_1 = LoadGraph("graphics/P02/magician_hp_1.png", true);
		magician_hp_2 = LoadGraph("graphics/P02/magician_hp_2.png", true);
		magician_cut_in = LoadGraph("graphics/P02/magician_cut_in_img.png", true);
		soldier_hp_1 = LoadGraph("graphics/P03/soldier_hp_1.png", true);
		soldier_hp_2 = LoadGraph("graphics/P03/soldier_hp_2.png", true);
		soldier_cut_in = LoadGraph("graphics/P03/soldier_cut_in_img.png", true);
		soldier_charge = LoadGraph("graphics/P03/soldier_charge.png", true);
		braver_down = LoadGraph("graphics/P01/braver_down.png", true);
		magician_down = LoadGraph("graphics/P02/magician_down.png", true);
		soldier_down = LoadGraph("graphics/P03/soldier_down.png", true);
		cut_in_img = LoadGraph("graphics/cut_in.png", true);
		

		//音声のロード
		title_bgm = LoadSoundMem("sound/title.mp3");
		char_select_bgm = LoadSoundMem("sound/town.mp3");
		battle1_bgm = LoadSoundMem("sound/battle1.mp3");
		main_map_bgm = LoadSoundMem("sound/main_map.mp3");
		battle_victory_bgm = LoadSoundMem("sound/battle_victory.mp3");
		gameover_bgm = LoadSoundMem("sound/gameover.mp3");

		//効果音のロード
		slash_sound = LoadSoundMem("sound/slash.mp3");
		collide_sound = LoadSoundMem("sound/collide.mp3");
		damage_sound = LoadSoundMem("sound/damage.mp3");
		break_sound = LoadSoundMem("sound/break.mp3");
		decide_sound = LoadSoundMem("sound/decide.mp3");
		select_sound = LoadSoundMem("sound/select.mp3");
		start_sound = LoadSoundMem("sound/start.mp3");
		skill_start_sound = LoadSoundMem("sound/skill_start.mp3");
		player_select_sound = LoadSoundMem("sound/player_select.mp3");
		braver_skill_sound = LoadSoundMem("sound/braver_skill.mp3");
		magician_skill_sound = LoadSoundMem("sound/magician_skill.mp3");
		soldier_skill_sound = LoadSoundMem("sound/soldier_skill.mp3");
		magician_attack_sound = LoadSoundMem("sound/magician_attack.mp3");
		magician_break_sound = LoadSoundMem("sound/magician_break.mp3");
		enemy_dead_sound = LoadSoundMem("sound/enemy_dead.mp3");
		encount_sound = LoadSoundMem("sound/encount.mp3");
		level_up_sound = LoadSoundMem("sound/level_up.mp3");
		heal_sound = LoadSoundMem("sound/heal.mp3");
		cancel_sound = LoadSoundMem("sound/cancel.mp3");
		escape_sound = LoadSoundMem("sound/escape.mp3");
		

		//色
		color_blue = GetColor(0, 0, 255);
		color_red = GetColor(255, 0, 0);

		//フォント
		title_str = CreateFontToHandle("MS　ゴシック", 128, 8,DX_FONTTYPE_ANTIALIASING);
		emp_str = CreateFontToHandle("MS　ゴシック", 60, 8, DX_FONTTYPE_ANTIALIASING);
		subtitle_str = CreateFontToHandle("MS　ゴシック", 84, 8, DX_FONTTYPE_ANTIALIASING);
		normal_str = CreateFontToHandle("MS ゴシック", 32, 4, DX_FONTTYPE_ANTIALIASING);
		window_str = CreateFontToHandle("MS　明朝", 32, 4, DX_FONTTYPE_ANTIALIASING);
		window_emp_str = CreateFontToHandle("MS ゴシック", 44, 6, DX_FONTTYPE_ANTIALIASING);

		LoadDivGraph("graphics/P01/braver_idle.png",10, 5, 2, 320, 320, braver_idle);
		LoadDivGraph("graphics/P01/braver_walk.png", 15, 5, 3, 320, 320, braver_walk);
		LoadDivGraph("graphics/P01/braver_idle_map.png", 10, 5, 2, 32, 32, braver_idle_map);
		LoadDivGraph("graphics/P01/braver_walk_map.png", 15, 5, 3, 32, 32, braver_walk_map);
		LoadDivGraph("graphics/P01/braver_run.png", 10, 5, 2, 320, 320, braver_run);
		LoadDivGraph("graphics/P01/braver_attack_ready.png", 10, 5, 2, 320, 320, braver_attack_ready);
		LoadDivGraph("graphics/P01/braver_attack.png", 10, 5, 2, 320, 320, braver_attack);
		LoadDivGraph("graphics/P01/braver_break.png", 10, 5, 2, 320, 320, braver_break);
		LoadDivGraph("graphics/P01/braver_guard.png", 10, 5, 2, 320, 320, braver_guard);
		LoadDivGraph("graphics/P01/braver_jump.png", 10, 5, 2, 320, 320, braver_jump);
		LoadDivGraph("graphics/P01/braver_damage.png", 10, 5, 2, 320, 320, braver_damage);
		LoadDivGraph("graphics/P01/braver_victory.png", 10, 5, 2, 320, 320, braver_victory);
		LoadDivGraph("graphics/P01/braver_skill.png", 10, 5, 2, 320, 320, braver_skill);
		LoadDivGraph("graphics/braver_skill_effect.png", 10, 5, 2, 400, 400, braver_skill_effect);
		LoadDivGraph("graphics/P01/braver_charge.png", 10, 5, 2, 320, 320, braver_charge);
		//LoadDivGraph("graphics/P02/magician_idle.png", 10, 5, 2, 320, 320, magician_idle);
		LoadDivGraph("graphics/P02/magician_idle.png", 16, 4, 4, 320, 320, magician_idle);
		LoadDivGraph("graphics/P02/magician_idle_map.png", 16, 4, 4, 32, 32, magician_idle_map);
		LoadDivGraph("graphics/P02/magician_walk.png", 15, 5, 3, 320, 320, magician_walk);
		LoadDivGraph("graphics/P02/magician_walk_map.png", 15, 5, 3, 32, 32, magician_walk_map);
		LoadDivGraph("graphics/P02/magician_run.png", 10, 5, 2, 320, 320,magician_run);
		LoadDivGraph("graphics/P02/magician_attack_ready.png", 16, 4, 4, 320, 320, magician_attack_ready);
		LoadDivGraph("graphics/P02/magician_attack.png", 20, 5, 4, 320, 320, magician_attack);
		LoadDivGraph("graphics/P02/magician_break.png", 25, 5, 5, 320, 320, magician_break);
		LoadDivGraph("graphics/P02/magician_guard.png", 15, 5, 3, 320, 320, magician_guard);
		LoadDivGraph("graphics/P02/magician_jump.png", 20, 5, 4, 320, 320, magician_jump);
		LoadDivGraph("graphics/P02/magician_damage.png", 15, 5, 3, 320, 320, magician_damage);
		LoadDivGraph("graphics/P02/magician_victory.png", 20, 5, 4, 320, 320, magician_victory);
		LoadDivGraph("graphics/magician_magic.png", 10, 5, 2, 320, 320, magician_magic);
		LoadDivGraph("graphics/P02/magician_skill.png", 10, 5, 2, 320, 320, magician_skill);
		LoadDivGraph("graphics/magician_skill_effect.png", 10, 5, 2, 400, 400, magician_skill_effect);
		LoadDivGraph("graphics/P02/magician_charge.png", 10, 5, 2, 320, 320, magician_charge);
		LoadDivGraph("graphics/P03/soldier_idle.png", 30, 6, 5, 320, 320, soldier_idle);
		LoadDivGraph("graphics/P03/soldier_idle_map.png", 30, 6, 5, 32, 32, soldier_idle_map);
		LoadDivGraph("graphics/P03/soldier_walk.png", 25, 5, 5, 320, 320, soldier_walk);
		LoadDivGraph("graphics/P03/soldier_walk_map.png", 25, 5, 5, 32, 32, soldier_walk_map);
		LoadDivGraph("graphics/P03/soldier_attack.png", 20, 5, 4, 320, 320, soldier_attack);
		LoadDivGraph("graphics/P03/soldier_damage.png", 20, 5, 4, 320, 320, soldier_damage);
		LoadDivGraph("graphics/P03/soldier_victory.png", 25, 5, 5, 320, 320, soldier_victory);
		//LoadDivGraph("graphics/P04/archer_idle2.png", 16, 4, 4, 320, 320, archer_idle);
		LoadDivGraph("graphics/heroine.png", 12, 3, 4, 96, 96, heroine);
		LoadDivGraph("graphics/heroine_battle.png", 12, 3, 4, 64, 64, heroine_battle);

		//マップ関連のロード
		fp = fopen("map/map_array_number_above.txt", "r+");
		gp = fopen("map/map_array_number.txt", "r+");

		// 画像のロード
		LoadDivGraph("graphics/map_origin_first.png", 160, 8, 20, 32, 32, map_chip);
		for (int i = 0; i < 3000; i++) {
			if (fscanf(gp, "%d", &var1) != EOF) {
				if (var1 != -1) {
					main_map_chip_number[i] = var1;
				}
				else {
					main_map_chip_number[i] = -1;
				}
			}
			else {
				main_map_chip_number[i] = -1;
			}

			if (fscanf(fp, "%d", &var2) != EOF) {
				if (var2 != -1) {
					main_map_chip_above_number[i] = var2;
				}
				else {
					main_map_chip_above_number[i] = -1;
				}
			}
			else {
				main_map_chip_above_number[i] = -1;
			}
		}
		fclose(fp);
		fclose(gp);

		enemy1_img = LoadGraph("graphics/Enemy/enemy1.png", true);
		enemy2_img = LoadGraph("graphics/Enemy/enemy2.png", true);
		enemy3_img = LoadGraph("graphics/Enemy/enemy3.png", true);

		LoadDivGraph("graphics/cursor.png", 3, 3, 1, 64, 64, cursor_up);
		LoadDivGraph("graphics/cursor2.png", 3, 3, 1, 64, 64, cursor_down);
		LoadDivGraph("graphics/cursor3.png",3, 3, 1, 32, 32, cursor_right);

		//エフェクトのロード
		LoadDivGraph("graphics/slash.png", 5, 5, 1, 240, 240, attack_effect);
		LoadDivGraph("graphics/break.png", 7, 7, 1, 240, 240, break_effect);
		LoadDivGraph("graphics/player_guard.png", 10, 5, 2, 240, 240, guard_effect);
		LoadDivGraph("graphics/Enemy/enemy_guard.png", 10, 5, 2, 240, 240, enemy_guard_effect);
		LoadDivGraph("graphics/Enemy/claw.png", 10, 5, 2, 240, 240, claw_effect);
		LoadDivGraph("graphics/Enemy/bite.png", 10, 5, 2, 240, 240, bite_effect);
		LoadDivGraph("graphics/collide.png", 5, 5, 1, 240, 240, collide_effect);
		LoadDivGraph("graphics/heal_effect.png", 8, 8, 1, 240, 240, heal_effect);


		is_init = true ;
	}


	//----------------------------------------------------------------------------------------------------
	// 全体のシーン制御
	switch( scene ) {
	// タイトル画面での処理
	case 0 :
		//タイトル画面を徐々に出現させる
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_alpha_cnt * 2 + 1);
		if (title_alpha_cnt != 127) {
			title_alpha_cnt++;
		}

		if (CheckSoundMem(title_bgm) == 0) {
			PlaySoundMem(title_bgm, DX_PLAYTYPE_LOOP);
		}

		//タイトル画像を描画する
		DrawGraph(0, 0, title_img, true);


		/*カットイン　テスト
		DrawGraph(30*cut_in_cnt, 284, cut_in_img, true);
		if (cut_in_cnt > -65) {
			cut_in_cnt--;
		}
		//勇者DrawGraph(272, 200, braver_cut_in, true);
		//魔法使いDrawGraph(272, 184, magician_cut_in, true);
		//騎士DrawTurnGraph(302, 239, soldier_cut_in, true);


		//1976
		/*
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 60; j++) {
				DrawGraph(j*32, i*32, map_center[i*60 + j], true);
			}
		}
		*/
		
		//クリスタルのアニメーション
		DrawGraph(175, 10, crystal[crystal_cnt / 3], true);
		crystal_cnt++;
		if (crystal_cnt == 120) {
			crystal_cnt = 0;
		}

		// タイトルを描画する
		DrawStringToHandle(150, 150, "RPC FANTASY", color_red,title_str);

		//キャラを表示
		DrawGraph(375, 300, title_dot1,true);
		DrawGraph(100, 300, title_dot2, true);
		DrawTurnGraph(650, 285, title_dot3, true);

		//指示を点滅させる
		if (is_print) {
			DrawStringToHandle(100, 650, "Please Press Enter Button!!", color_blue, emp_str);
		}
		
		title_counter++;

		if (title_counter == 45) {
			title_counter = 0;
			is_print = !is_print;
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// エンターキーでプレイ画面へ移行
		if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
			PlaySoundMem(start_sound, DX_PLAYTYPE_BACK);
			title_alpha_cnt = 0;
			title_counter = 0;
			crystal_cnt = 0;
			is_print = true;
			StopSoundMem(title_bgm);
			scene = 3;
			fade_out_title(fade_out_title_img);
		}


		//デバッグ用
		if (IsKeyDownTrigger(KEY_INPUT_ESCAPE)) {
			scene = 110;
		}

		break ;


	//----------------------------------------------------------------------------------------------------
	// プレイ画面での処理
	case 1:
		scene_play(enemy_character);

		break ;

	//----------------------------------------------------------------------------------------------------
	// リザルト画面での処理
	case 2:
		StopSoundMem(battle1_bgm);

		// エンターキーでタイトル画面へ移行
		if( IsKeyDownTrigger(KEY_INPUT_RETURN) == true ) {
			scene = 0 ;
			play_win_count = 0 ;
			play_lose_count = 0 ;
			is_player_win = false;
		}

		if (is_player_win) {
			DrawStringToHandle(250, 250,"You Win!!",0xffffffff, title_str);
		}
		else {
			DrawStringToHandle(250, 250,"You Lose...",0xffffffff, title_str);
		}

		// リザルトの文字を描画する
		DrawStringEx(300, 600, 0xFFFFFFFF, "リザルト画面です　エンターキーでタイトルへ戻ります") ;

		player_character = 0;

		break ;

	case 3:
		DrawGraph(0, 0, town_img, true);
		if (CheckSoundMem(char_select_bgm) == 0) {
			PlaySoundMem(char_select_bgm, DX_PLAYTYPE_LOOP);
		}

		DrawStringToHandle(90, 100, "†Character Select†", 0x00000000, subtitle_str);

		DrawGraph(100, 400, braver_idle[braver_idle_cnt / 6], true);
		braver_idle_cnt++;
		if (braver_idle_cnt == 42) {
			braver_idle_cnt = 0;
		}

		DrawGraph(350, 400, magician_idle[magician_idle_cnt / 5], true);
		magician_idle_cnt++;
		if (magician_idle_cnt == 70) {
			magician_idle_cnt = 0;
		}

		DrawTurnGraph(600, 385, soldier_idle[soldier_idle_cnt / 5], true);
		soldier_idle_cnt++;
		if (soldier_idle_cnt == 145) {
			soldier_idle_cnt = 0;
		}

		/*
		DrawGraph(700, 300, archer_idle[archer_idle_cnt / 5], true);
		archer_idle_cnt++;
		if (archer_idle_cnt == 70) {
			archer_idle_cnt = 0;
		}
		*/

		if (IsKeyDownTrigger(KEY_INPUT_LEFT)) {
			PlaySoundMem(player_select_sound, DX_PLAYTYPE_BACK);
			player_character -= 1;
		}

		if (IsKeyDownTrigger(KEY_INPUT_RIGHT)) {
			PlaySoundMem(player_select_sound, DX_PLAYTYPE_BACK);
			player_character += 1;
		}

		if (player_character < 0) {
			player_character = 2;
		}

		if (player_character > 2) {
			player_character = 0;
		}

		if (player_character == 0) {
			DrawStringToHandle(230, 270, "勇者", 0x00000000, normal_str);
			DrawStringToHandle(180, 310, "体力:普通", 0x00000000, normal_str);
			DrawStringToHandle(180, 350, "攻撃力:普通", 0x00000000, normal_str);
			DrawGraph(230, 400, cursor_down[cursor_cnt / 6], true);
		}
		if (player_character == 1) {
			DrawStringToHandle(450, 270, "魔法使い", 0x00000000, normal_str);
			DrawStringToHandle(430, 310, "体力:低い", 0x00000000, normal_str);
			DrawStringToHandle(430, 350, "攻撃力:高い", 0x00000000, normal_str);
			DrawGraph(480, 400, cursor_down[cursor_cnt / 6], true);
		}
		if (player_character == 2) {
			DrawStringToHandle(730, 270, "騎士", 0x00000000, normal_str);
			DrawStringToHandle(680, 310, "体力:高い", 0x00000000, normal_str);
			DrawStringToHandle(680, 350, "攻撃力:低い", 0x00000000, normal_str);
			DrawGraph(730, 400, cursor_down[cursor_cnt / 6], true);
		}
		cursor_cnt++;
		if (cursor_cnt == 18) {
			cursor_cnt = 0;
		}

		if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
			PlaySoundMem(start_sound, DX_PLAYTYPE_BACK);
			//シーン遷移
			//scene = 1;
			scene = 100;
			hero.set_parameter(player_character);
			cursor_cnt = 0;
			braver_idle_cnt = 0;
			magician_idle_cnt = 0;
			soldier_idle_cnt = 0;
			StopSoundMem(char_select_bgm);
		}
		break;
	case 4:
		StopSoundMem(battle1_bgm);
		if (CheckSoundMem(gameover_bgm) == 0) {
			PlaySoundMem(gameover_bgm, DX_PLAYTYPE_LOOP);
		}

		//ゲームオーバー画像を描画する
		DrawGraph(0, 0, gameover_img, true);

		if (is_continue) {
			DrawStringToHandle(100, 300, "Retry Battle", color_red, emp_str);
			DrawStringToHandle(100, 400, "Back to Title", 0xffffffff, normal_str);
		}
		else {
			DrawStringToHandle(100, 300, "Retry Battle", 0xffffffff, normal_str);
			DrawStringToHandle(100, 400, "Back to Title", color_red, emp_str);
		}

		//キャラクターを描画する
		switch (player_character) {
		case 0:
			DrawGraph(580, 400, braver_down, true);
			break;
		case 1:
			DrawGraph(580, 400, magician_down, true);
			break;
		case 2:
			DrawTurnGraph(580, 385, soldier_down, true);
			break;
		default:
			break;
		}

		if (IsKeyDownTrigger(KEY_INPUT_UP) || IsKeyDownTrigger(KEY_INPUT_DOWN)) {
			is_continue = !is_continue;
		}


		if (IsKeyDownTrigger(KEY_INPUT_RETURN)) {
			if (is_continue) {
				hero.hp_heal();
				scene = 1;
				is_init_char = false;
				is_init_battle = false;
				StopSoundMem(gameover_bgm);
				fade_out_circle();
			}
			else {
				is_continue = true;
				scene = 0;
				play_win_count = 0;
				play_lose_count = 0;
				is_player_win = false;
				player_character = 0;
				StopSoundMem(gameover_bgm);
				fade_out_circle();
			}
		}

		break;
	case 100:
		if (CheckSoundMem(main_map_bgm) == 0) {
			PlaySoundMem(main_map_bgm, DX_PLAYTYPE_LOOP);
		}
		main_map();
		break;
	case 110:
		if (CheckSoundMem(char_select_bgm) == 0) {
			PlaySoundMem(char_select_bgm, DX_PLAYTYPE_LOOP);
		}
		town_first();
		break;
	default:
		break;


	}



	return 0 ;
}

