#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	player = new ObImage(L"bono3.png");

	{ //익명스코프
		Scene01* temp = new Scene01;
		temp->player = player;
		SCENE->AddScene("Scene01", temp);
	}

	{ 
		Scene02* temp = new Scene02;
		temp->player = player;
		SCENE->AddScene("Scene02", temp);
	}
	
	SCENE->ChangeScene("Scene01");
}

void Main::Release()
{
	SafeDelete(player);

	SCENE->Release();
}

void Main::Update()
{

	SCENE->Update();
}

void Main::LateUpdate()
{
	SCENE->LateUpdate();
}

void Main::Render()
{
	SCENE->Render();
}

void Main::ResizeScreen()
{
	SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1400.0f, 800.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	//delete main;
	//delete main;
	SafeDelete(main);
	//SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}