#include "stdafx.h"

void Scene01::Init()
{
	map = new ObTileMap();
	map->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
	map->file = "TileMap01.txt";
	map->Load();
	map->CreateTileCost();

	player->scale = Vector2(100.0f, 70.0f);
	//player->SetWorldPosX(-50.0f);

	LIGHT->light.lights[0].radius = 0.0f;
	LIGHT->light.inColor.x = 0.5f;
	LIGHT->light.inColor.y = 0.5f;
	LIGHT->light.inColor.z = 0.5f;

	fadeOut = false;
	fadeIn = 1.0f;


	lefT = 0;
	toP = 0;
	righT = 0;
	boT = 0;
	sizE = 0;
}

void Scene01::Release()
{
	SafeDelete(map);
	
}

void Scene01::Update()
{
	if (ImGui::Button("Scene02"))
	{
		fadeOut = true;
		SCENE->ChangeScene("Scene02", 1.0f);
		//return;
	}

	if (fadeOut)
	{
		LIGHT->light.lights[0].radius -= 1000.0f * DELTA;
	}

	if (fadeIn > 0.0f)
	{
		fadeIn -= DELTA;
		LIGHT->light.lights[0].radius += 1000.0f * DELTA;
	}


	lastPos = player->GetWorldPos();

	if (INPUT->KeyPress(VK_UP))
	{
		player->MoveWorldPos(UP * 400.0f * DELTA);
	}
	else if (INPUT->KeyPress(VK_DOWN))
	{
		player->MoveWorldPos(DOWN * 400.0f * DELTA);
	}
	if (INPUT->KeyPress(VK_RIGHT))
	{
		player->MoveWorldPos(RIGHT * 400.0f * DELTA);
	}
	else if (INPUT->KeyPress(VK_LEFT))
	{
		player->MoveWorldPos(LEFT * 400.0f * DELTA);
	}

	if (INPUT->KeyDown(VK_RBUTTON))
	{
		//   출발점, 도착점
		Int2 sour, dest;
		//찾았는가?
		bool isFind;
		isFind = map->WorldPosToTileIdx(player->GetWorldPos(), sour);
		isFind &= map->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), dest);

		if (isFind)
		{
			if (map->PathFinding(sour, dest, PlWay))
			{
				//길 사이즈만큼 반복
				for (int i = 0; i < PlWay.size(); i++)
				{
					cout << "Way" << i << ":" << PlWay[i]->idx.x <<
						"," << PlWay[i]->idx.y << endl;
				}

				g = 0.0f;
				plSour = player->GetWorldPos();
				PlWay.pop_back(); //출발지 빼기
				plDest = PlWay.back()->Pos;
			}
		}
	}

	//가야될 길이 존재할 때
	if (!PlWay.empty())
	{
		player->SetWorldPos(Utility::Lerp(plSour, plDest, g));
		g += DELTA * 3.0f;

		//도착지를 지났을때
		if (g > 1.0f)
		{
			g = 0.0f;
			plSour = plDest;
			PlWay.pop_back(); //맨뒷길 빼기

			if (!PlWay.empty())
				plDest = PlWay.back()->Pos;
		}
	}
	if (ImGui::SliderInt("imgPositon.l", &lefT, 0, 1200))
	{
		rectT = { lefT , toP , lefT + righT , toP + boT };
	}
	if (ImGui::SliderInt("imgPositon.t", &toP, 0, 1200))
	{
		rectT = { lefT , toP , lefT + righT , toP + boT };
	}
	if (ImGui::SliderInt("imgPositon.r", &righT, 0, 1200))
	{
		rectT = { lefT , toP , lefT + righT , toP + boT };
	}
	if (ImGui::SliderInt("imgPositon.b", &boT, 0, 1200))
	{
		rectT = { lefT , toP , lefT + righT , toP + boT };
	}
	if (ImGui::SliderInt("sizE", &sizE, 0, 1200))
	{
		
	}


	map->Update();
	player->Update();
}

void Scene01::LateUpdate()
{
	vector<Vector2> foot;
	foot.resize(4);

	foot[0] = player->GetWorldPos() + Vector2(-20.0f, 0.0f);
	foot[1] = player->GetWorldPos() + Vector2(-20.0f, -30.0f);
	foot[2] = player->GetWorldPos() + Vector2(20.0f, -30.0f);
	foot[3] = player->GetWorldPos() + Vector2(20.0f, 0.0f);

	Int2 idx;
	for (int i = 0; i < 4; i++)
	{
		if (map->WorldPosToTileIdx(foot[i], idx))
		{
			if (map->GetTileState(idx) == TileState::TILE_WALL)
			{
				player->SetWorldPos(lastPos);
				break;
			}
		}
	}


	player->Update();

	CAM->position = player->GetWorldPos();
}

void Scene01::Render()
{
	DWRITE->RenderText(L"포켓몬", RECT{ 103, 103, 303, 303 }, 60.0f,
		L"Galmuri11", Color(0.6, 0.6, 0.6, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
	DWRITE->RenderText(L"포켓몬", RECT{ 103, 100, 303, 300 }, 60.0f,
		L"Galmuri11", Color(0.6, 0.6, 0.6, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
	DWRITE->RenderText(L"포켓몬", RECT{ 100, 103, 300, 303 }, 60.0f,
		L"Galmuri11", Color(0.6, 0.6, 0.6, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);

	//DWRITE->GetDC()->BeginDraw();
	DWRITE->RenderText(L"포켓몬", RECT{ 100, 100, 300, 300 }, 60.0f,
		L"Galmuri11", Color(0.9f, 0.9f, 0.9f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
	//DWRITE->GetDC()->EndDraw();

	DWRITE->RenderText(L"포켓몬", rectT, sizE,
		L"Galmuri11", Color(0.9f, 0.9f, 0.9f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);

	map->Render();
	player->Render();

	

}

void Scene01::ResizeScreen()
{
}

