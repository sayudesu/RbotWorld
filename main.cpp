#include <DxLib.h>
#include "Util/game.h"
#include "Scene/SceneManager.h"
#include "Util/Sound.h"
#include <math.h>


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// ウィンドのサイズを変更できるかどうか
	SetWindowSizeChangeEnableFlag(Game::kWindowSizeChange);
	// Log.txtでログを残すかどうか
	SetOutApplicationLogValidFlag(Game::kLogText);

	// DirectX9を使用するようにする。(DirectX11も可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	// ********** フォントのロード **********
	LPCSTR font_path = "Data/Fonts/851letrogo_007.ttf"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) 
	{
		ChangeFont("851レトロゴ", DX_CHARSET_DEFAULT);
	}
	else
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	//
	// サウンド読み込み
	Sound::load();

	SceneManager* pScene = new SceneManager;

	pScene->Init();
	
	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		pScene->Update();

		pScene->Draw();
		
		// 裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	// ********** フォントのアンロード **********
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
	}
	else {
		MessageBox(NULL, "remove failure", "", MB_OK);
	}

	pScene->End();

	Sound::unload();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();				
	// ソフトの終了 
	return 0;				
}