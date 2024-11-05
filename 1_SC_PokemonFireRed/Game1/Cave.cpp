#include "stdafx.h"

void Cave::Init()
{
	if (player->findJam == true)
	{
		LIGHT->light.lights[0].radius = 1000.0f;
		LIGHT->light.select.x = 0.0f;
	}
	else
	{
		LIGHT->light.lights[0].radius = 150.0f;
		LIGHT->light.select.x = 1.0f;
	}
	LIGHT->light.inColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	

	cave = new ObTileMap();
	cave->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
	cave->file = "testCave1.txt";
	cave->Load();
	cave->CreateTileCost();
	//41 6, 8 6, 13 20, 11 26, 10 36, 8 43, 25 43, 41 38, 41 13,
	jam = new ObImage(L"Pokemon143.png");
	jam->scale = jam->imageSize * 5;
	ranJam[0] = Int2(41, 6);
	ranJam[1] = Int2(8, 6);
	ranJam[2] = Int2(13, 20);
	ranJam[3] = Int2(11, 26);
	ranJam[4] = Int2(10, 36);
	ranJam[5] = Int2(8, 43);
	ranJam[6] = Int2(25, 43);
	ranJam[7] = Int2(41, 38);
	ranJam[8] = Int2(41, 13);
	tempRan = RANDOM->Int(0, 8);
	jam->SetWorldPos(cave->TileIdxTOTIlePos(ranJam[tempRan]));
	cave->SetTile(ranJam[tempRan], Int2(6, 3), 1, 1);
	cave->SetTile(Int2(ranJam[tempRan].x + 1, ranJam[tempRan].y), Int2(6, 3), 1, 1);
	cave->SetTile(Int2(ranJam[tempRan].x, ranJam[tempRan].y + 1), Int2(6, 3), 1, 1);
	cave->SetTile(Int2(ranJam[tempRan].x + 1, ranJam[tempRan].y + 1), Int2(6, 3), 1, 1);
	cave->CreateTileCost();

	//LIGHT->light.lights[1].radius = 150.0f;


	//이동
	player->inCave = true;
	if (player->playerFront->isVisible == false && player->playerRight->isVisible == false && player->playerLeft->isVisible == false)
	{
		player->playerBack->isVisible = true;
	}

	if (player->caveToBattle == false)
	{
		player->SetPlayerPos(cave->TileIdxTOTIlePos(Int2(25, 5)));
		player->Update();
	}
	//이동
	playerGo = false;
	playerTurn = false;
	goWall = false;
	playAni = false;
	//포켓몬 -> 잠만보 or 다른 포켓몬으로 변경해야 함
	fieldPoke = new Poke143();
	//전투 시작
	battleStart = false;
	//메뉴
	mapMenu = new ObImage(L"PokeFullMenu1.png");
	mapMenu->scale = mapMenu->imageSize * 5;
	//mapMenu->pivot = OFFSET_LB;
	mapMenuSel = new ObImage(L"PokeFullMenu2.png");
	mapMenuSel->scale = mapMenuSel->imageSize * 5;
	mapMenuSel->pivot = OFFSET_LB;
	menuSel = 0;
	//메뉴 포켓몬
	pokeMenu = new PokeMenu();
	pokeMenu->SetPokeMenu(player, player->myPokemon.size());

	//메뉴 가방
	bag = new BagMenu();
	bag->bagPlayer = player;
	
	goWall = false;
	playerTurn = false;
	//씬전환
	goTown = false;
	//조명
	lightCol = 0.0f;
	lightTime = 0.0f;
	battleLightCount = 0;
	battleLightOn = true;
	fadeIn = true;
	fadeOut = false;

	state = CaveState::CAVE;
}

void Cave::Release()
{
	SafeDelete(cave);
	SafeDelete(fieldPoke);
	SafeDelete(mapMenu);
	SafeDelete(mapMenuSel);
	SafeDelete(pokeMenu);
	SafeDelete(bag);
}

void Cave::Update()
{
	Int2 test;
	//if (cave->WorldPosToTileIdx(player->playerFront->GetWorldPos(), test))
	//{
	//	cout << test.x << " " << test.y << endl;
	//}
	if(cave->WorldPosToTileIdx(jam->GetWorldPos(), test))
	{
		cout << test.x << " jam " << test.y << endl;
	}
	if (fadeIn == true)
	{

		lightCol += 1.5f * DELTA;
		if (lightCol >= 0.5f)
		{
			lightCol = 0.5f;
			fadeIn = false;
		}
		LIGHT->light.inColor = Color(lightCol, lightCol, lightCol, 0.5f);

	}
	else
	{
		switch (state)
		{
		case CaveState::CAVE:
			if (goTown == true)
			{
				if (LIGHT->light.inColor != Color(0.0f, 0.0f, 0.0f, 0.5f))
				{
					lightCol -= 1.5f * DELTA;
					if (lightCol <= 0.0f)
					{
						lightCol = 0.0f;
					}
					LIGHT->light.inColor = Color(lightCol, lightCol, lightCol, 0.5f);
				}
				else
				{
					goTown = false;
					SOUND->Stop("CAVE");
					
					player->caveToBattle = false;
					player->inCave = false;
					player->SetPlayerPos(cave->TileIdxTOTIlePos(Int2(18, 22)));
					player->Update();
					SOUND->Play("TOWNBGM");
					SCENE->ChangeScene("Town");
					return;
				}

			}
			else if (battleStart == true)
			{
				if (player->findJam == true)
				{
					if (LIGHT->light.lights[0].radius > 250.0f)
					{
						LIGHT->light.lights[0].radius -= 700 * DELTA;
						SOUND->Stop("CAVE");
						SOUND->Play("BATTLE");
					}
					else if (TIMER->GetTick(sceneTime, 0.6f))
					{
						battleStart = false;
						player->caveToBattle = true;
						LIGHT->light.inColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
						SCENE->ChangeScene("Battle");
						lightCol = 0.5f;
						return;
					}
					if (battleLightOn && battleLightCount < 2)
					{
						lightCol -= 1.5f * DELTA;
						if (lightCol <= 0.12f)
						{
							lightCol = 0.12f;
							battleLightOn = false;
						}
						LIGHT->light.inColor = Color(lightCol, lightCol, lightCol, 0.5f);
					}
					else if (battleLightOn == false && battleLightCount < 2)
					{
						lightCol += 1.5f * DELTA;
						if (lightCol >= 0.5f)
						{
							lightCol = 0.5f;
							battleLightOn = true;
							battleLightCount++;
						}
						LIGHT->light.inColor = Color(lightCol, lightCol, lightCol, 0.5f);
					}
				}
				else
				{
					if (LIGHT->light.lights[0].radius < 1000.0f)
					{
						LIGHT->light.lights[0].radius += 700 * DELTA;
						SOUND->Stop("CAVE");
						SOUND->Play("BATTLE");
					}
					else if (TIMER->GetTick(sceneTime, 0.6f))
					{
						player->caveToBattle = true;
						LIGHT->light.inColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
						battleStart = false;
						SCENE->ChangeScene("Battle");
						player->findJam = true;
						return;
					}
					if (battleLightOn && battleLightCount < 2)
					{
						lightCol -= 1.5f * DELTA;
						if (lightCol <= 0.12f)
						{
							lightCol = 0.12f;
							battleLightOn = false;
						}
						LIGHT->light.inColor = Color(lightCol, lightCol, lightCol, 0.5f);
					}
					else if (battleLightOn == false && battleLightCount < 2)
					{
						lightCol += 1.5f * DELTA;
						if (lightCol >= 0.5f)
						{
							lightCol = 0.5f;
							battleLightOn = true;
							battleLightCount++;
						}
						LIGHT->light.inColor = Color(lightCol, lightCol, lightCol, 0.5f);
					}
				}
			}
			else
			{
				CAVE();
			}
			break;
		case CaveState::POKEMENU:
			POKEMENU();
			break;
		case CaveState::POKEMON:
			POKEMON();
			break;
		case CaveState::BAG:
			BAG();
			bag->Update();
			if (bag->usedItemName == L"상처약")
			{
				state = CaveState::POKEMON;
				bag->keyOn = false;
				pokeMenu->SetState(PokeMenuState::BAG_ITEM);
				bag->usedItemName = L"";
			}
			break;
		default:
			break;
		}
	}
	

	cave->Update();
	player->Update();
	mapMenu->Update();
	mapMenuSel->Update();
	pokeMenu->Update();
	jam->Update();
}

void Cave::LateUpdate()
{
	switch (state)
	{
	case CaveState::CAVE:
		CAM->position = player->playerFront->GetWorldPos(); // 원본
		//CAM->position.x = (cave->GetTileSize().x - 15) * 40.0f; // 동굴 길찾기 테스트용
		//CAM->position.y = (cave->GetTileSize().y - 10) * 40.0f; // 동굴 길찾기 테스트용
		//LIGHT->light.select.x = 1.0f;
		//LIGHT->light.lights[1].screenPos = Vector2(jam->GetWorldPos().x + app.GetHalfWidth(), app.GetHalfHeight() - jam->GetWorldPos().y);
		break;
	case CaveState::POKEMENU:
		CAM->position = player->playerFront->GetWorldPos();
		//LIGHT->light.select.x = 0.0f;
		//LIGHT->light.lights[1].screenPos = Vector2(jam->GetWorldPos().x + app.GetHalfWidth(), app.GetHalfHeight() - jam->GetWorldPos().y);
		break;
	case CaveState::POKEMON:
		//LIGHT->light.select.x = 0.0f;
		CAM->position = Vector2(0.0f, 0.0f);
		break;
	case CaveState::BAG:
		//LIGHT->light.select.x = 0.0f;
		CAM->position = Vector2(0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void Cave::Render()
{
	switch (state)
	{
	case CaveState::CAVE:
		cave->Render();
		jam->Render();
		player->Render();

		break;
	case CaveState::POKEMENU:
		cave->Render();
		jam->Render();

		player->Render();

		mapMenu->Render();
		mapMenuSel->Render();
		DWRITE->RenderText(L"원진", RECT{ 915, 250, 1115, 250 + 100 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"원진", RECT{ 915, 250 + 5, 1115, 250 + 105 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"원진", RECT{ 910, 250 + 5, 1110, 250 + 105 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"원진", RECT{ 910, 250, 1110, 250 + 100 }, 60.0F,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
		switch (menuSel)
		{
		case 0:
			DWRITE->RenderText(L"도감에  기록된  포켓몬의\n상세  정보를  확인합니다.", RECT{ 25 + 5, 610, 25 + 1200 + 5, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"도감에  기록된  포켓몬의\n상세  정보를  확인합니다.", RECT{ 25 + 5, 610 + 5, 1200 + 5, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"도감에  기록된  포켓몬의\n상세  정보를  확인합니다.", RECT{ 25, 610 + 5, 1200, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"도감에  기록된  포켓몬의\n상세  정보를  확인합니다.", RECT{ 25, 610, 1200, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 1:
			DWRITE->RenderText(L"같이  있는  포켓몬의  상태를\n확인하고  관리합니다.", RECT{ 25 + 5, 610, 25 + 1200 + 5, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"같이  있는  포켓몬의  상태를\n확인하고  관리합니다.", RECT{ 25 + 5, 610 + 5, 1200 + 5, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"같이  있는  포켓몬의  상태를\n확인하고  관리합니다.", RECT{ 25, 610 + 5, 1200, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"같이  있는  포켓몬의  상태를\n확인하고  관리합니다.", RECT{ 25, 610, 1200, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 2:
			DWRITE->RenderText(L"도구를  확인하고\n사용할  수  있습니다.", RECT{ 25 + 5, 610, 25 + 1200 + 5, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"도구를  확인하고\n사용할  수  있습니다.", RECT{ 25 + 5, 610 + 5, 1200 + 5, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"도구를  확인하고\n사용할  수  있습니다.", RECT{ 25, 610 + 5, 1200, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"도구를  확인하고\n사용할  수  있습니다.", RECT{ 25, 610, 1200, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 3:
			DWRITE->RenderText(L"당신의  트레이너  카드를\n확인합니다.", RECT{ 25 + 5, 610, 25 + 1200 + 5, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"당신의  트레이너  카드를\n확인합니다.", RECT{ 25 + 5, 610 + 5, 1200 + 5, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"당신의  트레이너  카드를\n확인합니다.", RECT{ 25, 610 + 5, 1200, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"당신의  트레이너  카드를\n확인합니다.", RECT{ 25, 610, 1200, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 4:
			DWRITE->RenderText(L"지금까지의  모험을\n리포트로  기록합니다.", RECT{ 25 + 5, 610, 25 + 1200 + 5, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"지금까지의  모험을\n리포트로  기록합니다.", RECT{ 25 + 5, 610 + 5, 1200 + 5, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"지금까지의  모험을\n리포트로  기록합니다.", RECT{ 25, 610 + 5, 1200, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"지금까지의  모험을\n리포트로  기록합니다.", RECT{ 25, 610, 1200, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 5:
			DWRITE->RenderText(L"사운드,  속도  등의  설정을\n변경합니다.", RECT{ 25 + 5, 610, 25 + 1200 + 5, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"사운드,  속도  등의  설정을\n변경합니다.", RECT{ 25 + 5, 610 + 5, 1200 + 5, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"사운드,  속도  등의  설정을\n변경합니다.", RECT{ 25, 610 + 5, 1200, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"사운드,  속도  등의  설정을\n변경합니다.", RECT{ 25, 610, 1200, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case 6:
			DWRITE->RenderText(L"이  메뉴를  닫고\n게임을  계속합니다.", RECT{ 25 + 5, 610, 25 + 1200 + 5, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"이  메뉴를  닫고\n게임을  계속합니다.", RECT{ 25 + 5, 610 + 5, 1200 + 5, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"이  메뉴를  닫고\n게임을  계속합니다.", RECT{ 25, 610 + 5, 1200, 610 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"이  메뉴를  닫고\n게임을  계속합니다.", RECT{ 25, 610, 1200, 610 + 100 }, 60.0F,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		default:
			break;
		}
		break;
	case CaveState::POKEMON:
		pokeMenu->Render();

		break;
	case CaveState::BAG:
		bag->Render();

		break;
	default:
		break;
	}
}

void Cave::ResizeScreen()
{
}

void Cave::CAVE()
{
	if (INPUT->KeyDown(VK_UP) && player->playerBack->isVisible == false && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = true;
		player->playerBack->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.05);
		player->playerFront->isVisible = false;
		player->playerLeft->isVisible = false;
		player->playerRight->isVisible = false;
		playerTurn = true;

	}
	else if (INPUT->KeyPress(VK_UP) && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = true;
		player->playerFront->isVisible = false;
		player->playerLeft->isVisible = false;
		player->playerRight->isVisible = false;

		Int2 sour, dest;
		if (cave->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x, player->playerBack->GetWorldPos().y + cave->scale.y), dest) &&
			cave->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (cave->GetTileState(sour) != TileState::TILE_WALL && cave->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerBack->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);
				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = cave->TileIdxTOTIlePos(dest);
				playerGo = true;
				goWall = false;
				wallTime = 0.0f;

			}
			else
			{
				player->playerBack->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.3f);
				goWall = true;
				playerGo = true;
			}
		}
	}
	else if (INPUT->KeyDown(VK_DOWN) && player->playerFront->isVisible == false && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = false;
		player->playerFront->isVisible = true;
		player->playerFront->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.05f);
		player->playerLeft->isVisible = false;
		player->playerRight->isVisible = false;
		playerTurn = true;

	}
	else if (INPUT->KeyPress(VK_DOWN) && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = false;
		player->playerFront->isVisible = true;
		player->playerLeft->isVisible = false;
		player->playerRight->isVisible = false;
		Int2 sour, dest;
		if (cave->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x, player->playerBack->GetWorldPos().y - cave->scale.y), dest) && cave->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (sour.x == 25 && sour.y == 5)
			{
				goTown = true;
				SOUND->Stop("DOUT");
				SOUND->Play("DOUT");
				return;
			}
			if (cave->GetTileState(sour) != TileState::TILE_WALL && cave->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerFront->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);

				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = cave->TileIdxTOTIlePos(dest);
				playerGo = true;
				goWall = false;
				wallTime = 0.0f;
			}
			else
			{
				player->playerFront->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.3f);
				goWall = true;
				playerGo = true;
			}
		}
	}
	else if (INPUT->KeyDown(VK_RIGHT) && player->playerRight->isVisible == false && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = false;
		player->playerFront->isVisible = false;
		player->playerLeft->isVisible = false;
		player->playerRight->isVisible = true;
		player->playerRight->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.05f);

		playerTurn = true;

	}
	else if (INPUT->KeyPress(VK_RIGHT) && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = false;
		player->playerFront->isVisible = false;
		player->playerLeft->isVisible = false;
		player->playerRight->isVisible = true;
		Int2 sour, dest;
		if (cave->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x + cave->scale.x, player->playerBack->GetWorldPos().y), dest) && cave->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (cave->GetTileState(sour) != TileState::TILE_WALL && cave->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerRight->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);
				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = cave->TileIdxTOTIlePos(dest);
				playerGo = true;
				goWall = false;
				wallTime = 0.0f;
			}
			else
			{
				player->playerRight->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.3f);
				goWall = true;
				playerGo = true;
			}
		}
	}
	else if (INPUT->KeyDown(VK_LEFT) && player->playerLeft->isVisible == false && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = false;
		player->playerFront->isVisible = false;
		player->playerLeft->isVisible = true;
		player->playerLeft->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.05f);
		player->playerRight->isVisible = false;

		playerTurn = true;

	}
	else if (INPUT->KeyPress(VK_LEFT) && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = false;
		player->playerFront->isVisible = false;
		player->playerLeft->isVisible = true;
		player->playerRight->isVisible = false;
		Int2 sour, dest;
		if (cave->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x - cave->scale.x, player->playerBack->GetWorldPos().y), dest) && cave->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (cave->GetTileState(sour) != TileState::TILE_WALL && cave->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerLeft->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);

				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = cave->TileIdxTOTIlePos(dest);
				playerGo = true;
				goWall = false;
				wallTime = 0.0f;
			}
			else
			{
				playerGo = true;
				player->playerLeft->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.3f);
				goWall = true;
			}
		}
	}
	else if (INPUT->KeyDown(VK_RETURN) && playerGo == false && playerTurn == false && player->findJam == true)
	{
		mapMenu->SetWorldPos(player->playerFront->GetWorldPos());
		mapMenuSel->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x + 280.0f, player->playerFront->GetWorldPos().y + 305.0f)); // -35씩
		SOUND->Stop("MENUOPEN");
		SOUND->Play("MENUOPEN");
		state = CaveState::POKEMENU;
	}
	else if (INPUT->KeyDown('A') && playerGo == false && playerTurn == false && player->findJam == true)
	{
	    //   출발점, 도착점
	    Int2 sour, dest;
	    //찾았는가?
	    bool isFind;
	    isFind = cave->WorldPosToTileIdx(player->playerFront->GetWorldPos(), sour);
		if (ranJam[tempRan].x < sour.x)
		{
			isFind &= cave->WorldPosToTileIdx(cave->TileIdxTOTIlePos(Int2(ranJam[tempRan].x + 1, ranJam[tempRan].y - 1)), dest);
		}
		else
		{
			isFind &= cave->WorldPosToTileIdx(cave->TileIdxTOTIlePos(Int2(ranJam[tempRan].x, ranJam[tempRan].y - 1)), dest);
		}
	    
	    if (isFind)
	    {
	    	if (cave->PathFinding(sour, dest, PlWay))
	    	{
	    		g = 0.0f;
	    		plSour = player->playerFront->GetWorldPos();
				SOUND->Play("FIND");

				// 241010 테스트
				TmpPlWay.clear();
				for (Tile* tmpT : PlWay)
				{
					TmpPlWay.push_back(tmpT);
					cave->SetTileColor(tmpT->idx);
				}

	    		PlWay.pop_back(); //출발지 빼기
	    		plDest = PlWay.back()->Pos;
				playerGo = true;
				goWall = false;
	    	}
	    }
	}

	//가야될 길이 존재할 때
	if (!PlWay.empty())
	{
		player->SetPlayerPos(Utility::Lerp(plSour, plDest, g));
		g += DELTA * 3.3f;
		//플레이어 이동 모션 실행
		if (playAni == false)
		{
			if (plSour.x == plDest.x && plSour.y < plDest.y) //상
			{
				player->playerBack->isVisible = true;
				player->playerFront->isVisible = false;
				player->playerLeft->isVisible = false;
				player->playerRight->isVisible = false;
				player->playerBack->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);

			}
			else if (plSour.x == plDest.x && plSour.y > plDest.y) //하
			{
				player->playerBack->isVisible = false;
				player->playerFront->isVisible = true;
				player->playerLeft->isVisible = false;
				player->playerRight->isVisible = false;
				player->playerFront->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);
			}
			else if (plSour.x > plDest.x && plSour.y == plDest.y) //좌
			{
				player->playerBack->isVisible = false;
				player->playerFront->isVisible = false;
				player->playerLeft->isVisible = true;
				player->playerRight->isVisible = false;
				player->playerLeft->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);

			}
			else if (plSour.x < plDest.x && plSour.y == plDest.y) //우
			{
				player->playerBack->isVisible = false;
				player->playerFront->isVisible = false;
				player->playerLeft->isVisible = false;
				player->playerRight->isVisible = true;
				player->playerRight->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);
			}
			playAni = true;
		}
		//도착지를 지났을때
		if (g >= 1.0f)
		{
			g = 0.0f;
			player->SetPlayerPos(plDest);
			plSour = plDest;
			PlWay.pop_back(); //맨뒷길 빼기
			playAni = false;

			if (!PlWay.empty())
			{
				plDest = PlWay.back()->Pos;
			}
			else
			{
				playerGo = false;
				for (Tile* tmpT : TmpPlWay)
				{
					cave->ResetTileColor(tmpT->idx);
				}
			}
		}
	}
	else if (playerGo && goWall == false)
	{
		player->SetPlayerPos(Utility::Lerp(plSour, plDest, g));
		g += DELTA * 3.3f;

		//도착지를 지났을때

		if (g >= 1.0f)
		{
			g = 0.0f;
			player->SetPlayerPos(plDest);
			playerGo = false;
			player->SetPlayerAni(ANIMSTATE::STOP, 0.1f);
			if ((plDest.x == cave->TileIdxTOTIlePos(Int2(ranJam[tempRan].x, ranJam[tempRan].y - 1)).x && plDest.y == cave->TileIdxTOTIlePos(Int2(ranJam[tempRan].x, ranJam[tempRan].y - 1)).y) ||
				(plDest.x == cave->TileIdxTOTIlePos(Int2(ranJam[tempRan].x + 1, ranJam[tempRan].y - 1)).x && plDest.y == cave->TileIdxTOTIlePos(Int2(ranJam[tempRan].x + 1, ranJam[tempRan].y - 1)).y))
			{
				player->enemyPokemon.push_front(fieldPoke->Create(fieldPoke));
				player->enemyPokemon[0]->lv = player->myPokemon[0]->lv + 2;
				player->enemyPokemon[0]->SetPokemon();
				//player->enemyPokemon[0]->hp = 10;
				//player->enemyPokemon[0]->changeHp = 10;
				battleStart = true;
			}
		}
	}
	else if (goWall)
	{
		if (TIMER->GetTick(wallTime, 0.7f))
		{
			SOUND->Stop("WALL");
			SOUND->Play("WALL");
			goWall = false;
			playerGo = false;
		}
	}
	else if (playerTurn)
	{
		if (TIMER->GetTick(wallTime, 0.1f))
		{
			playerTurn = false;
		}
	}
}

void Cave::POKEMENU()
{
	if (INPUT->KeyDown(VK_UP))
	{
		if (menuSel > 0)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			menuSel--;
		}
	}
	else if (INPUT->KeyDown(VK_DOWN))
	{
		if (menuSel < 6)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			menuSel++;
		}
	}
	else if (INPUT->KeyDown('Z'))
	{
		switch (menuSel)
		{
		case 1:
			state = CaveState::POKEMON;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		case 2:
			state = CaveState::BAG;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			bag->sel = 0;
			break;
		case 6:
			state = CaveState::CAVE;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			menuSel = 0;
			break;
		}
	}
	else if (INPUT->KeyDown('X'))
	{
		state = CaveState::CAVE;
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		menuSel = 0;
	}

	switch (menuSel)
	{
	case 0:
		mapMenuSel->SetWorldPosY(player->playerFront->GetWorldPos().y + 305.0f);
		break;
	case 1:
		mapMenuSel->SetWorldPosY(player->playerFront->GetWorldPos().y + 230.0f);
		break;
	case 2:
		mapMenuSel->SetWorldPosY(player->playerFront->GetWorldPos().y + 155.0f);
		break;
	case 3:
		mapMenuSel->SetWorldPosY(player->playerFront->GetWorldPos().y + 80.0f);
		break;
	case 4:
		mapMenuSel->SetWorldPosY(player->playerFront->GetWorldPos().y + 5.0f);
		break;
	case 5:
		mapMenuSel->SetWorldPosY(player->playerFront->GetWorldPos().y - 70.0f);
		break;
	case 6:
		mapMenuSel->SetWorldPosY(player->playerFront->GetWorldPos().y - 145.0f);
		break;
	default:
		break;
	}
}

void Cave::POKEMON()
{
	switch (pokeMenu->state)
	{
	case PokeMenuState::SEL:
		if (INPUT->KeyDown('X') && pokeMenu->state == PokeMenuState::SEL)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = CaveState::POKEMENU;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;
		}
		else if (INPUT->KeyDown('Z') && pokeMenu->selPokeList == 6 && pokeMenu->state == PokeMenuState::SEL)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = CaveState::POKEMENU;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;

		}
		break;
	case PokeMenuState::BAG_ITEM:
		if (INPUT->KeyDown('X') && pokeMenu->state == PokeMenuState::BAG_ITEM)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = CaveState::BAG;
			pokeMenu->state = PokeMenuState::SEL;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;
		}
		else if (INPUT->KeyDown('Z') && pokeMenu->selPokeList == 6 && pokeMenu->state == PokeMenuState::BAG_ITEM)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = CaveState::BAG;
			pokeMenu->state = PokeMenuState::SEL;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;
		}
		break;
	case PokeMenuState::USE_BAG_ITEM:
		if (INPUT->KeyDown('Z') || INPUT->KeyDown('X'))
		{
			if (pokeMenu->pokemonToBag)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				state = CaveState::BAG;
				pokeMenu->state = PokeMenuState::SEL;
				pokeMenu->lastSelPokeList = 1;
				pokeMenu->selPokeList = 0;
				pokeMenu->pokemonToBag = false;
				if (player->myItem[bag->sel]->num == 1)
				{
					auto iter = player->myItem.begin() + bag->sel;
					player->myItem.erase(iter);
				}
				else
				{
					player->myItem[bag->sel]->num--;
				}
			}
		}
		break;
	default:
		break;
	}
	pokeMenu->ContrlPokeMenu();
}

void Cave::BAG()
{
	if (INPUT->KeyDown('X') && bag->state == BagMenuState::SEL)
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		state = CaveState::POKEMENU;
		bag->sel = 0;
		bag->keyOn = false;
	}
	else if (INPUT->KeyDown('Z') && bag->state == BagMenuState::SEL && bag->sel == player->myItem.size())
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		state = CaveState::POKEMENU;
		bag->sel = 0;
		bag->keyOn = false;

	}
}
