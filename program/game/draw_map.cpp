#include "draw_map.h"
#include "Dxlib.h"


//マップに関する定義
const int MAP_WIDTH = 60;
const int MAP_HEIGHT = 50;
const int MAP_SIZE = 32;

extern int player_pos_x;
extern int player_pos_y;
extern float moving_player_pos_x;
extern float moving_player_pos_y;

extern int map_chip[160];

//キャラの画像(32×32)
extern int braver_idle_map[10];
extern int braver_walk_map[15];
extern int magician_idle_map[16];
extern int magician_walk_map[15];
extern int soldier_idle_map[30];
extern int soldier_walk_map[25];

void draw_map(int scrollx, int scrolly, int* map,int character_number,int animation_control,bool is_right,bool is_move)
{
	int map_draw_posx, map_draw_posy;		// 描画するマップ座標値
	int draw_chip_numx, draw_chip_numy;	// 描画するマップチップの数

											// 描画するマップチップの数をセット
	draw_chip_numx = 1024 / MAP_SIZE + 2;
	draw_chip_numy = 768 / MAP_SIZE + 2;

	// 画面左上に描画するマップ座標をセット
	map_draw_posx = player_pos_x - (draw_chip_numx / 2 - 1);
	map_draw_posy = player_pos_y - (draw_chip_numy / 2 - 1);

	//マップ描画
	for (int i = 0; i < draw_chip_numy; i++){
		for (int j = 0; j < draw_chip_numx; j++) {
			//画面からはみ出たら描画しない
			if (j + map_draw_posx < 0 || i + map_draw_posy < 0 || j + map_draw_posx >= MAP_WIDTH || i + map_draw_posy >= MAP_HEIGHT) {
				DrawGraph(j * MAP_SIZE + scrollx, i * MAP_SIZE + scrolly, map_chip[148], true);
				continue;
			}
			/*
			if (map[(i + map_draw_posy) * 60 + (j + map_draw_posx)] == 0) {
				DrawBox(j * MAP_SIZE, i * MAP_SIZE, j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE, GetColor(255, 0, 0), true);
			}
			else {
				DrawBox(j * MAP_SIZE, i * MAP_SIZE, j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE, GetColor(255, 255, 0), true);
			}
			*/
			DrawGraph(j * MAP_SIZE + scrollx, i * MAP_SIZE + scrolly, map_chip[map[(i + map_draw_posy) * 60 + (j + map_draw_posx)]], true);
		}
	}

	switch(character_number){
	case 0:
		if (is_move) {
			if (is_right) {
				DrawTurnGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, braver_walk_map[animation_control / 5], true);
			}
			else {
				DrawGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, braver_walk_map[animation_control / 5], true);
			}
		}
		else {
			if (is_right) {
				DrawTurnGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, braver_idle_map[animation_control / 10], true);
			}
			else {
				DrawGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, braver_idle_map[animation_control / 10], true);
			}
		}
		break;
	case 1:
		if (is_move) {
			if (is_right) {
				DrawTurnGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, magician_walk_map[animation_control / 5], true);
			}
			else {
				DrawGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, magician_walk_map[animation_control / 5], true);
			}
		}
		else {
			if (is_right) {
				DrawTurnGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, magician_idle_map[animation_control / 5], true);
			}
			else {
				DrawGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, magician_idle_map[animation_control / 5], true);
			}
		}
		break;
	case 2:
		if (is_move) {
			if (is_right) {
				DrawGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, soldier_walk_map[animation_control / 3], true);
			}
			else {
				DrawTurnGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, soldier_walk_map[animation_control / 3], true);
			}
		}
		else {
			if (is_right) {
				DrawGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, soldier_idle_map[animation_control / 3], true);
			}
			else {
				DrawTurnGraph((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, soldier_idle_map[animation_control / 3], true);
			}
		}
		break;
	default:
		break;
	}

	//プレイヤーの描画
	//DrawBox((player_pos_x - map_draw_posx) * MAP_SIZE, (player_pos_y - map_draw_posy) * MAP_SIZE, (player_pos_x - map_draw_posx + 1) * MAP_SIZE, (player_pos_y - map_draw_posy + 1) * MAP_SIZE, GetColor(255, 255, 255), true);

}