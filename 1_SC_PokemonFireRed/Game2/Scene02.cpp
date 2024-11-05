#include "stdafx.h"

void Scene02::Init()
{
	map = new ObTileMap();
	map->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
	map->file = "TileMap02.txt";
	map->Load();
	map->CreateTileCost();

	//player = new ObImage(L"bono3.png");
	player->scale = Vector2(100.0f, 70.0f);
	//player->SetWorldPosX(-50.0f);



	LIGHT->light.lights[0].radius = 1000.0f;
	LIGHT->light.inColor.x = 1.0f;
	LIGHT->light.inColor.y = 1.0f;
	LIGHT->light.inColor.z = 1.0f;

	whiteOut = false;
	whiteIn = 1.0f;
}

void Scene02::Release()
{
	SafeDelete(map);
	//SafeDelete(player);
}

void Scene02::Update()
{
	if (ImGui::Button("Scene01"))
	{
		whiteOut = true;
		SCENE->ChangeScene("Scene01", 1.0f);
		//return;
	}

	if (whiteOut)
	{
		LIGHT->light.inColor.x += 0.5f * DELTA;
		LIGHT->light.inColor.y += 0.5f * DELTA;
		LIGHT->light.inColor.z += 0.5f * DELTA;
	}

	if (whiteIn > 0.0f)
	{
		whiteIn -= DELTA;

		LIGHT->light.inColor.x -= 0.5f * DELTA;
		LIGHT->light.inColor.y -= 0.5f * DELTA;
		LIGHT->light.inColor.z -= 0.5f * DELTA;
	}

	if (ImGui::Button("Color"))
	{
		player->color.x = 0.2f;
		player->color.y = 0.2f;
		player->color.z = 0.2f;
	}
	ImGui::SliderFloat("AlPha", &player->color.w, 0.0f, 1.0f);

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


	map->Update();
	player->Update();
}

void Scene02::LateUpdate()
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

void Scene02::Render()
{
	map->Render();
	player->Render();
}

void Scene02::ResizeScreen()
{
}

