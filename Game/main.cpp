/*!
 *@brief	main.cpp
 */
#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "Fade.h"
#include "StageSeni.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	srand((unsigned)time(NULL));
	//tkEngine2の初期化パラメータを設定する。
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.frameBufferHeight = 720;
	initParam.screenWidth2D = 1280.0f;
	initParam.screenHeight2D = 720.0f;
	//影の設定。
	initParam.graphicsConfing.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 2048;
	initParam.graphicsConfing.shadowRenderConfig.lightHeight = 150.0f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[0] = 0.00001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[1] = 0.00001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[2] = 0.00002f;
	initParam.graphicsConfing.shadowRenderConfig.offsetTexelWorld = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.softShadowLevel = EnSoftShadowQualityLevel::eSSSS_PCF;
	//アンチ
	initParam.graphicsConfing.aaConfig.isEnable = true;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = true;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = true;
	initParam.graphicsConfing.tonemapConfig.luminance = 0.3f;
	GraphicsEngine().GetShadowMap().SetFar(1000.0f);
	GraphicsEngine().GetShadowMap().SetNear(50.0f);

	srand(time(NULL));
	//エンジンを初期化。
	if (Engine().Init(initParam) == true) {
		//NewGO<Game>(0, nullptr);
		NewGO<Fade>(1, "Fade");
		NewGO<StageSeni>(0,"ss");
		NewGO<Title>(0, nullptr);
		
		//ゲームループを実行。
		Engine().RunGameLoop();
	}
	//エンジンの終了処理。
	Engine().Final();

	return 0;
}

