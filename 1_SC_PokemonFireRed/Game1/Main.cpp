#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	LIGHT->light.lights[0].radius = 1000.0f;

	//시작
	player = new Player();
	//{ //익명스코프
	//	Battle* temp = new Battle();
	//	temp->SetPokemon(_001[0], _001[1]);
	//	SCENE->AddScene("Battle", temp);
	//}
	townScene = new Town();
	townScene->player = player;
	SCENE->AddScene("Town", townScene);

	battleScene = new Battle();
	battleScene->player = player;
	SCENE->AddScene("Battle", battleScene);

	shopScene = new Shop();
	shopScene->player = player;
	SCENE->AddScene("Shop", shopScene);

	caveScene = new Cave();
	caveScene->player = player;
	SCENE->AddScene("Cave", caveScene);

	evoScene = new Evolution();
	evoScene->player = player;
	SCENE->AddScene("Evolution", evoScene);

	SCENE->ChangeScene("Town");

	//글자 테스트 910 100 200 100 60
	lefT = 65;
	toP = 595; //515
	righT = lefT + 1200;
	boT = toP + 100;
	sizE = 60;
	testTIme = 0.0f;
	testIndex = 0;
	testStart = 0;

	leftR = 155;
	topR = 35;
	rightR = leftR +1200;
	botR = topR + 100;
	sizeR = 60.0f;
	numR = 1;
	//이미지 테스트
	imgX = 0;
	imgY = 0;
	scaleX = 0;
	scaleY = 0;
	test_gravi = 500.0f;
	testImg = new ObImage(L"Pokemon_Item_MonsterBall.png");
	//testImg->pivot = OFFSET_LB;
	testImg->scale.x = testImg->imageSize.x / 3 * 5;
	testImg->scale.y = testImg->imageSize.y * 5;
	testImg->maxFrame.x = 3;
}

void Main::Release()
{
	SCENE->Release();
}

void Main::Update()
{

	ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());
	//if (ImGui::SliderInt("imgPositon.l", &leftR, 0, 1200))
	//{
	//	rectT = { lefT , toP , lefT + righT , toP + boT };
	//}
	//if (ImGui::SliderInt("imgPositon.t", &topR, 0, 1200))
	//{
	//	rectT = { lefT , toP , lefT + righT , toP + boT };
	//}
	//if (ImGui::SliderInt("imgPositon.r", &rightR, 0, 3000))
	//{
	//	rectT = { lefT , toP , lefT + righT , toP + boT };
	//}
	//if (ImGui::SliderInt("imgPositon.b", &botR, 0, 3000))
	//{
	//	rectT = { lefT , toP , lefT + righT , toP + boT };
	//}
	//if (ImGui::SliderInt("sizE", &sizeR, 0, 100))
	//{
	//
	//}
	//if (ImGui::SliderInt("numR", &numR, 0, 99))
	//{
	//
	//}
	//
	testImg->MoveWorldPos((RIGHT * 800.0f + UP * test_gravi) * DELTA);
	test_gravi -= DELTA * 800.0f;
	//if (ImGui::SliderInt("imgPositon.x", &imgX, -600, 600))
	//{
	//	//testImg->SetWorldPosX(player->playerFront->GetWorldPos().x + imgX);
	//	testImg->SetWorldPosX(imgX);
	//}
	//if (ImGui::SliderInt("imgPositon.y", &imgY, -400, 400))
	//{
	//	//testImg->SetWorldPosY(player->playerFront->GetWorldPos().y + imgY);
	//	//testImg->SetWorldPosY(imgY);
	//	test_gravi = imgY;
	//}
	//cout << testImg->GetWorldPos().x - player->playerFront->GetWorldPos().x << " " << testImg->GetWorldPos().y - player->playerFront->GetWorldPos().y << endl;
	//if (ImGui::SliderInt("imgScale.x", &scaleX, 0.0f, 400.0f))
	//{
	//	battleHpBar[3]->scale.x = scaleX;
	//}
	//if (ImGui::SliderInt("imgScale.y", &scaleY, 0.0f, 400.0f))
	//{
	//	battleHpBar[0]->scale.y = scaleY;
	//}
	SCENE->Update();
	testImg->Update();
}

//모든 객체가 움직이고 난 후
void Main::LateUpdate()
{
	LIGHT->light.lights[0].screenPos = Vector2(app.GetHalfWidth(), app.GetHalfHeight());
	SCENE->LateUpdate();
}

void Main::Render()
{
	string tsetsdg = "안녕하세요";
	//cout << tsetsdg.size() << endl;
	wstring testWW = L"잠만보";
	
	//테스트
	testInt = to_wstring(sizeR);
	//wcout << testInt.length() << endl;;
	//if (TIMER->GetTick(testTIme, 0.1))
	//{
	//	testIndex++;
	//	if (testIndex == 15)
	//	{
	//		toP -= 80;
	//		//testStart = 15;
	//	}
	//	else if (testIndex > testInt.size())
	//	{
	//		testIndex = testInt.size();
	//	}
	//}
	//cout << testIndex << endl;
	//leftR = 155;
	//topR = 35;
	//rightR = leftR + 1200;
	//botR = topR + 100;
	//sizeR = 60.0f;
	wstring wordR = L"99999원";
	wordR = to_wstring(numR);
	//DWRITE->RenderText(wordR, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
	//DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
	//DWRITE->RenderText(wordR, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
	//DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
	//DWRITE->RenderText(wordR, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
	//DWRITE->RenderText(wordR, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
	//DWRITE->RenderText(wordR, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
	//DWRITE->RenderText(wordR, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(72.0f / 255.0f, 72.0f / 255.0f, 72.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
	


	SCENE->Render();
	testImg->Render();
}

void Main::ResizeScreen()
{
	SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1200.0f , 800.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}