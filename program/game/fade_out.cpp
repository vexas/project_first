#include "Dxlib.h"
#include "fade_out.h"
#include "fade_in.h"
#define _USE_MATH_DEFINES
#include <cmath>

extern int fade_out_img;

const int display_width = 1024;
const int display_height = 768;

void fade_out_circle(){

	int var;
	GetDrawScreenGraph(0, 0, display_width, display_height, fade_out_img);
	var = fade_out_img;

	for (int i = 0; i <= 700; i += 24)
	{
		// 画面を初期化
		//ClearDrawScreen();

		DrawGraph(0, 0, var, true);
		// 描画したグラフィックの上に反転円を描画
		//DrawReversalCircle(320, 240, Mode == 0 ? 399-i : 399-i, 0);
		draw_reverse_circle(display_width / 2, display_height / 2, 700-i);

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}
}

void fade_out_alpha() {

	int var,k;
	GetDrawScreenGraph(0, 0, display_width, display_height, fade_out_img);
	var = fade_out_img;

	for (int i = 0; i < 512 + 128; i += 18)
	{
		// 画面を初期化
		//ClearDrawScreen();

		//グラフィック１を描画します
		DrawGraph(0, 0, var, FALSE);

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

				//透過部分を左右から中心に向かって描画
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

void fade_out_title(int title_img) {
	for (int i = 0; i < 64; i++)
	{
		// 画面を初期化
		ClearDrawScreen();
		DrawBox(0, 0, display_width, display_height, GetColor(0, 0, 0), true);

		// アルファブレンド値をセット
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 252 - 4 * i);

		//グラフィック１を描画します
		DrawRotaGraph(512, 384, 1.0 + (1.0*i / float(64)), 2 * M_PI*(i / float(64)), title_img, true, false);
		// ブレンドモードを元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//裏画面の描画
		ScreenFlip();
	}
}

void fade_out_place() {
	int var, k;
	GetDrawScreenGraph(0, 0, display_width, display_height, fade_out_img);
	var = fade_out_img;
	//マップ、町、ダンジョンfade_out
	for (int i = 0; i < 80; i += 2) {

		// フェードアウト前の画像を描画
		DrawGraph(0, 0, var, true);

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

				DrawBox(0, 0, display_width, display_height, GetColor(0, 0, 0), true);
			}
		}
		SetDrawArea(0, 0, display_width, display_height);
		//裏画面の描画
		ScreenFlip();

	}
}