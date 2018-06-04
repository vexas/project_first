#include "Dxlib.h"
#include "fade_in.h"
#include "draw_map.h"

const int color_black = GetColor(0, 0, 0);
const int display_width = 1024;
const int display_height = 768;
extern int field_img;

//円形のフェードイン
//image_cnt…描画したい画像の数、2つ目以降の引数…画像
//主にバトルシーンのフェードイン用
void fade_in_circle(int background_handle,int enemy_handle) {
	
	for (int i = 0; i <= 700; i += 24)
	{
		// 画面を初期化
		ClearDrawScreen();

		DrawGraph(0, 0, background_handle, true);
		DrawGraph(50, 200, enemy_handle, true);

		// 描画したグラフィックの上に反転円を描画
		//DrawReversalCircle(320, 240, Mode == 0 ? 399-i : 399-i, 0);
		draw_reverse_circle(display_width/2, display_height/2, i);

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}
}

void fade_in_alpha(int scrollx, int scrolly, int *map, int *map2, int character_number, int animation_control, bool is_right, bool is_move) {

	int k;

	for (int i = 512 + 128; i >= 0; i -= 18)
	{
		// 画面を初期化
		ClearDrawScreen();

		//グラフィック１を描画します
		//DrawGraph(0, 0, image1, FALSE);
		draw_map(scrollx, scrolly, map, character_number, animation_control, is_right, is_move);
		draw_map(scrollx, scrolly, map2, character_number, animation_control, is_right, is_move);

		// グラフィック２を描画します
		for (int j = 0; j < 128; j++)
		{
			// 描画可能領域設定用の値セット
			k = j + i - 128;

			// 描画可能領域を指定します
			if (k >= 0)
			{
				// アルファブレンド値をセット
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 254 - 2 * j);

				//透過部分を中心から左右に向かって描画
				DrawBox(k, 0, k + 1, display_height, GetColor(0, 0, 0), true);
				DrawBox(display_width - (k + 1), 0, display_width - k, display_height, GetColor(0, 0, 0), true);

			}
		}

		// ブレンドモードを元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		k = i - 128;
		if (k > 0)
		{
			//黒い部分を描画
			DrawBox(0, 0, k, display_height, GetColor(0, 0, 0), true);
			DrawBox(display_width - k, 0, display_width, display_height, GetColor(0, 0, 0), true);

		}

		//裏画面の描画
		ScreenFlip();
	}
}

void fade_in_dungeon(int scrollx, int scrolly, int *map, int *map2, int character_number, int animation_control, bool is_right, bool is_move) {

	int k;

	for (int i = 0; i < 80; i += 2) {
		ClearDrawScreen();

		// 背面に黒い領域を描画
		DrawBox(0, 0, display_width, display_height, GetColor(0, 0, 0), true);

		for (int j = 0; j < display_width / 32; j++)
		{
			// 描画可能領域設定用の値セット
			k = j + i - 32;
			if (k > 0)
			{
				if (k > 32) {
					k = 32;
				}

				// 描画可能領域を指定
				SetDrawArea((display_width - 32) - j * 32, 0, (display_width - 32) - (j * 32 - k), display_height);

				draw_map(scrollx, scrolly, map, character_number, animation_control, is_right, is_move);
				draw_map(scrollx, scrolly, map2, character_number, animation_control, is_right, is_move);
			}
		}
		SetDrawArea(0, 0, display_width, display_height);
		//裏画面の描画
		ScreenFlip();

	}
}

void fade_in_town(int town_image) {
	int k;

	for (int i = 0; i < 80; i += 2) {
		ClearDrawScreen();

		// 背面に黒い領域を描画
		DrawBox(0, 0, display_width, display_height, GetColor(0, 0, 0), true);

		for (int j = 0; j < display_width / 32; j++)
		{
			// 描画可能領域設定用の値セット
			k = j + i - 32;
			if (k > 0)
			{
				if (k > 32) {
					k = 32;
				}

				// 描画可能領域を指定
				SetDrawArea((display_width - 32) - j * 32, 0, (display_width - 32) - (j * 32 - k), display_height);

				DrawGraph(0, 0, town_image, true);
			}
		}
		SetDrawArea(0, 0, display_width, display_height);
		//裏画面の描画
		ScreenFlip();

	}
}

void draw_reverse_circle(int pos_x,int pos_y,int radius) {
	// 円反転描画領域の外側を描画
	DrawBox(0, 0, display_width, pos_y - radius, color_black, TRUE);
	DrawBox(0, pos_y - radius, pos_x - radius, display_height, color_black, TRUE);
	DrawBox(pos_x - radius, pos_y + radius + 1, display_width, display_height, color_black, TRUE);
	DrawBox(pos_x + radius, pos_y - radius, display_width, pos_y + radius + 1, color_black, TRUE);

	// 描画処理
	int dx, dy, F, j;
	int pos_x1, pos_x2, pos_y1;

	// 初期値セット
	dx = radius; dy = 0; F = -2 * radius + 3;

	j = 0;
	// まず最初に座標データを進める
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

	// 描き切るまでループ
	while (dx >= dy)
	{
		// ラインを描く
		pos_x2 = dx + pos_x; pos_x1 = -dx + pos_x; pos_y1 = dy + pos_y;
		DrawLine(0, pos_y1, pos_x1, pos_y1, color_black);
		DrawLine(pos_x2, pos_y1, display_width, pos_y1, color_black);
		pos_x2 = dx + pos_x; pos_x1 = -dx + pos_x; pos_y1 = -dy + pos_y;
		DrawLine(0, pos_y1, pos_x1, pos_y1, color_black);
		DrawLine(pos_x2, pos_y1, display_width, pos_y1, color_black);

		// 座標データを進める
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