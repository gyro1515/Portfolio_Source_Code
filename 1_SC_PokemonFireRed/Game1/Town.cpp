#include "stdafx.h"

void Town::Init()
{
	//LIGHT->light.inColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	LIGHT->light.select.x = 0.0f;
	LIGHT->light.lights[1].radius = 0.0f;
	LIGHT->light.lights[0].radius = 1000.0f;



	town = new ObTileMap();
	town->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
	town->file = "Town1.txt";
	town->Load();
	town->CreateTileCost();

	townBack = new ObImage(L"town2-2.png");
	townBack->scale = townBack->imageSize * 5;
	townBack->pivot = OFFSET_LB;
	townBack->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	building1 = new ObImage(L"Buildings1.png");
	building1->scale = building1->imageSize * 5;
	building1->pivot = OFFSET_LB;
	building1->SetWorldPos(Vector2(-app.GetHalfWidth() + 80.0f * 10, -app.GetHalfHeight() + 80.0f * 16));

	pokeCenter = new ObImage(L"Buildings3.png");
	pokeCenter->scale = pokeCenter->imageSize * 5;
	pokeCenter->pivot = OFFSET_LB;
	pokeCenter->SetWorldPos(Vector2(-app.GetHalfWidth() + 80.0f * 18, -app.GetHalfHeight() + 80.0f * 16));

	shop = new ObImage(L"Buildings2.png");
	shop->scale = shop->imageSize * 5;
	shop->pivot = OFFSET_LB;
	shop->SetWorldPos(Vector2(-app.GetHalfWidth() + 80.0f * 19, -app.GetHalfHeight() + 80.0f * 10));

	building1Roof = new ObImage(L"BuildingsRoof1.png");
	building1Roof->scale = building1Roof->imageSize * 5;
	building1Roof->pivot = OFFSET_LB;
	building1Roof->SetWorldPos(Vector2(-app.GetHalfWidth() + 80.0f * 10, -app.GetHalfHeight() + 80.0f * 16));

	pokeCenterRoof = new ObImage(L"BuildingsRoof3.png");
	pokeCenterRoof->scale = pokeCenterRoof->imageSize * 5;
	pokeCenterRoof->pivot = OFFSET_LB;
	pokeCenterRoof->SetWorldPos(Vector2(-app.GetHalfWidth() + 80.0f * 18, -app.GetHalfHeight() + 80.0f * 16));

	shopRoof = new ObImage(L"BuildingsRoof2.png");
	shopRoof->scale = shopRoof->imageSize * 5;
	shopRoof->pivot = OFFSET_LB;
	shopRoof->SetWorldPos(Vector2(-app.GetHalfWidth() + 80.0f * 19, -app.GetHalfHeight() + 80.0f * 10));

	for (int i = 0; i < 3; i++)
	{
		door[i] = new ObImage(L"Tileset_door3.png");
		door[i]->scale = door[i]->imageSize * 5;
		door[i]->pivot = OFFSET_LB;
	}
	
	door[0]->SetWorldPos(Vector2(-app.GetHalfWidth() + 80.0f * 11, -app.GetHalfHeight() + 80.0f * 16));
	door[1]->SetWorldPos(Vector2(-app.GetHalfWidth() + 80.0f * 20, -app.GetHalfHeight() + 80.0f * 16));
	door[2]->SetWorldPos(Vector2(-app.GetHalfWidth() + 80.0f * 21, -app.GetHalfHeight() + 80.0f * 10));
	
	//필드 포켓몬
	fieldPoke[0] = new Poke1();
	fieldPoke[1] = new Poke4();
	fieldPoke[2] = new Poke7();

	fieldPoke[3] = new Poke2();
	fieldPoke[4] = new Poke5();
	fieldPoke[5] = new Poke8();

	fieldPoke[6] = new Poke3();
	fieldPoke[7] = new Poke6();
	fieldPoke[8] = new Poke9();

	fieldPoke[9] = new Poke143();

	testPoke = new Poke3();
	//아이템
	setItem[0] = new PokeBall();
	setItem[1] = new Portion();

	//전투 시작
	battleStart = false;
	//필드 포켓몬 초기화 후 플레이어 및 플레이어 포켓몬 세팅
	player->inTown = true;
	if (player->firstSet)
	{
		//player->money = 999999;
		player->SetPlayerPos(town->TileIdxTOTIlePos(Int2(11, 15)));
		player->playerBack->isVisible = false;
		player->playerFront->isVisible = true;
		player->playerLeft->isVisible = false;
		player->playerRight->isVisible = false;

		player->myPokemon.push_back(fieldPoke[6]->Create(fieldPoke[6]));
		player->myPokemon[0]->lv = 7;
		player->myPokemon[0]->SetPokemon();
		/*player->myPokemon[0]->hp = 10;
		player->myPokemon[0]->changeHp = 10;*/

		player->myPokemon.push_back(fieldPoke[7]->Create(fieldPoke[7]));
		player->myPokemon.push_back(fieldPoke[8]->Create(fieldPoke[8]));
		player->myPokemon[1]->lv = 8;
		player->myPokemon[1]->SetPokemon();
		player->myPokemon[2]->lv = 9;
		player->myPokemon[2]->SetPokemon(); 
		/*player->myPokemon[1]->hp = 10;
		player->myPokemon[1]->changeHp = 10;
		player->myPokemon[2]->hp = 10;
		player->myPokemon[2]->changeHp = 10;*/

		player->myPokemon.push_back(fieldPoke[9]->Create(fieldPoke[9]));
		player->myPokemon[3]->lv = 8;
		player->myPokemon[3]->SetPokemon();
		/*player->myPokemon.push_back(fieldPoke[9]->Create(fieldPoke[9]));
		player->myPokemon[4]->lv = 5;
		player->myPokemon[4]->SetPokemon();
		player->myPokemon.push_back(fieldPoke[8]->Create(fieldPoke[8]));
		player->myPokemon[5]->lv = 8;
		player->myPokemon[5]->SetPokemon();*/


		
		//player->myPokemon.push_back(fieldPoke[6]->Create(fieldPoke[6]));
		//player->myPokemon.push_back(fieldPoke[7]->Create(fieldPoke[7]));
		//player->myPokemon.push_back(fieldPoke[8]->Create(fieldPoke[8]));
		player->enemyPokemon.push_back(fieldPoke[8]->Create(fieldPoke[8]));
		player->enemyPokemon[0]->hp = 10;
		player->enemyPokemon[0]->changeHp = 10;

		player->firstSet = false;

		//아이템 세팅
		player->myItem.push_back(setItem[0]->Create());
		player->myItem[0]->num = 5;
		player->myItem.push_back(setItem[1]->Create());
		player->myItem[1]->num = 5;
		//player->myItem.push_back(setItem[1]->Create());
		//player->myItem.push_back(setItem[1]->Create());
		//player->myItem.push_back(setItem[1]->Create());
	}
	
	onGrassImg = new ObImage(L"Tileset_GrassAni5.png");
	onGrassImg->scale = onGrassImg->imageSize * 5;
	onGrassImg->SetWorldPos(player->playerFront->GetWorldPos());

	Int2 destest;
	if (town->WorldPosToTileIdx(player->playerFront->GetWorldPos(), destest) && town->GetTileState(destest) == TileState::TILE_TRAP)
	{
		onGrassImg->isVisible = true;
	}
	else
	{
		onGrassImg->isVisible = false;
	}

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
	//소리 세팅
	SetSound();
	SOUND->Play("TOWNBGM");
	//씬체인지용 타임
	sceneTime = 0.0f;
	//조명
	lightCol = 0.0f;
	lightTime = 0.0f;
	battleLightCount = 0;
	battleLightOn = true;
	fadeIn = true;
	fadeOut = false;

	goWall = false;
	playerTurn = false;
	goShop = false;
	goCave = false;
	state = TownState::TOWN;

}

void Town::Release()
{
	SafeDelete(town);
	SafeDelete(townBack);
	SafeDelete(building1);
	SafeDelete(pokeCenter);
	SafeDelete(shop);
	//SafeDelete(player);
	for (int i = 0; i < 3; i++)
	{
		SafeDelete(door[i]);
	}
	for (int i = 0; i < 9; i++)
	{
		SafeDelete(fieldPoke[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		SafeDelete(setItem[i]);
	}
	SafeDelete(onGrassImg);
	SafeDelete(mapMenu);
	SafeDelete(mapMenuSel);
	SafeDelete(pokeMenu);
	SafeDelete(bag);


}

void Town::Update()
{

	//Int2 test;
	//if (town->WorldPosToTileIdx(player->playerFront->GetWorldPos(), test))
	//{
	//	cout << test.x << " " << test.y << " " << player->inTown << "/" << player->inCave << endl;
	//}
	//if (ImGui::SliderInt("imgPositon.x", &imgX, -600, 600))
	//{
	//	mapMenuSel->SetWorldPosX(imgX);
	//}
	//if (ImGui::SliderInt("imgPositon.y", &imgY, -400, 400))
	//{
	//	mapMenuSel->SetWorldPosY(imgY);
	//}
	//cout << mapMenuSel->GetWorldPos().y << endl;

	if (fadeIn == true)
	{
		FAIDEIN();
	}
	else if ((plSour == town->TileIdxTOTIlePos(Int2(21, 10)) && goShop == false) || (plSour == town->TileIdxTOTIlePos(Int2(18, 22)) && goCave == false))
	{
		SCENE_TO_TOWN();// 상점이나 동굴에서 나온뒤 한 칸 이동
	}
	else
	{
		switch (state)
		{
		case TownState::TOWN:
			if (goCave == true)
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
					goCave = false;
					player->inTown = false;
					SOUND->Stop("TOWNBGM");
					SOUND->Play("CAVE");
					SCENE->ChangeScene("Cave");
					return;
				}
			}
			else if (goShop == true)
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
					goShop = false;
					SOUND->Stop("TOWNBGM");
					SOUND->Play("SHOPBGM");
					SCENE->ChangeScene("Shop");
					lightCol = 0.5f;
					return;
				}

			}
			else if (battleStart == true)
			{
				if (LIGHT->light.lights[0].radius > 80.0f)
				{
					LIGHT->light.lights[0].radius -= 700 * DELTA;
					SOUND->Stop("TOWNBGM");
					SOUND->Play("BATTLE");
				}
				else if (TIMER->GetTick(sceneTime, 0.6f))
				{
					battleStart = false;
					LIGHT->light.inColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
					SOUND->Play("BATTLE");
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
				TOWN();
			}
			break;
		case TownState::POKEMENU:
			POKEMENU();
			break;
		case TownState::POKEMON:
			POKEMON();
			break;
		case TownState::BAG:
			BAG();
			bag->Update();
			if (bag->usedItemName == L"상처약")
			{
				state = TownState::POKEMON;
				bag->keyOn = false;
				pokeMenu->SetState(PokeMenuState::BAG_ITEM);
				bag->usedItemName = L"";
				//if (player->myItem[bag->sel]->num == 1)
				//{
				//	auto iter = player->myItem.begin() + bag->sel;
				//	player->myItem.erase(iter);
				//}
				//else
				//{
				//	player->myItem[bag->sel]->num--;
				//}
			}
			break;
		default:
			break;
		}
	}
	
	
	town->Update();
	townBack->Update();
	building1->Update();
	pokeCenter->Update();
	shop->Update();
	for (int i = 0; i < 3; i++)
	{
		door[i]->Update();
	}
	player->Update();
	onGrassImg->Update();
	building1Roof->Update();
	pokeCenterRoof->Update();
	shopRoof->Update();
	mapMenu->Update();
	mapMenuSel->Update();
	pokeMenu->Update();
	//bag->Update();
	
}

void Town::LateUpdate()
{
	switch (state)
	{
	case TownState::TOWN:
		CAM->position = player->playerFront->GetWorldPos();
		//LIGHT->light.lights[1].screenPos = Vector2(CAM->position);
		break;
	case TownState::POKEMENU:
		CAM->position = player->playerFront->GetWorldPos();

		break;
	case TownState::POKEMON:
		CAM->position = Vector2(0.0f, 0.0f);

		break;
	case TownState::BAG:
		CAM->position = Vector2(0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void Town::Render()
{
	switch (state)
	{
	case TownState::TOWN:
		townBack->Render();
		town->Render();
		building1->Render();
		pokeCenter->Render();
		shop->Render();
		for (int i = 0; i < 3; i++)
		{
			door[i]->Render();
		}
		player->Render();
		onGrassImg->Render();
		building1Roof->Render();
		pokeCenterRoof->Render();
		shopRoof->Render();
		break;
	case TownState::POKEMENU:
		townBack->Render();
		town->Render();
		building1->Render();
		pokeCenter->Render();
		shop->Render();
		for (int i = 0; i < 3; i++)
		{
			door[i]->Render();
		}
		player->Render();
		onGrassImg->Render();
		building1Roof->Render();
		pokeCenterRoof->Render();
		shopRoof->Render();
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
	case TownState::POKEMON:
		pokeMenu->Render();
		break;
	case TownState::BAG:
		bag->Render();

		break;
	default:
		break;
	}

	
}

void Town::ResizeScreen()
{
}

void Town::FAIDEIN()
{
	lightCol += 1.5f * DELTA;
	if (lightCol >= 0.5f)
	{
		lightCol = 0.5f;
		fadeIn = false;
	}
	LIGHT->light.inColor = Color(lightCol, lightCol, lightCol, 0.5f);
	if (player->playerFront->GetWorldPivot() == town->TileIdxTOTIlePos(Int2(21, 10)))
	{
		plSour = player->playerFront->GetWorldPivot();
		plDest = town->TileIdxTOTIlePos(Int2(21, 9));
		g = 0.0f;
		player->SetPlayerVisible(false);
	}
	else if (player->playerFront->GetWorldPivot() == town->TileIdxTOTIlePos(Int2(18, 22)))
	{
		plSour = player->playerFront->GetWorldPivot();
		plDest = town->TileIdxTOTIlePos(Int2(18, 21));
		g = 0.0f;
		player->SetPlayerVisible(false);
	}
}

void Town::SCENE_TO_TOWN()
{
	if (g == 0.0f)
	{
		player->SetPlayerAni(ANIMSTATE::HALF_ONCE, 0.1f);
	}
	player->SetPlayerPos(Utility::Lerp(plSour, plDest, g));
	g += DELTA * 3.3f;

	//도착지를 지났을때

	if (g > 1.0f)
	{
		plSour = town->TileIdxTOTIlePos(Int2(21, 9));
		g = 0.0f;
		player->SetPlayerPos(plDest);
		playerGo = false;
	}
	else if (g > 0.3f)
	{
		player->playerFront->isVisible = true;
	}
}

void Town::TOWN()
{
	
		// 간소화
    if (INPUT->KeyDown(VK_UP) && player->playerBack->isVisible == false && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = true;
		player->playerBack->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.05f);
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
		if (town->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x, player->playerBack->GetWorldPos().y + town->scale.y), dest) &&
			town->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (town->GetTileState(sour) != TileState::TILE_WALL && town->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerBack->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);
				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = town->TileIdxTOTIlePos(dest);
				playerGo = true;
				onGrassImg->isVisible = false;
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
		if (town->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x, player->playerBack->GetWorldPos().y - town->scale.y), dest) && town->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (town->GetTileState(sour) != TileState::TILE_WALL && town->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerFront->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);

				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = town->TileIdxTOTIlePos(dest);
				playerGo = true;
				onGrassImg->isVisible = false;
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
		if (town->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x + town->scale.x, player->playerBack->GetWorldPos().y), dest) && town->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (town->GetTileState(sour) != TileState::TILE_WALL && town->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerRight->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);
				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = town->TileIdxTOTIlePos(dest);
				playerGo = true;
				onGrassImg->isVisible = false;
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
		if (town->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x - town->scale.x, player->playerBack->GetWorldPos().y), dest) && town->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (town->GetTileState(sour) != TileState::TILE_WALL && town->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerLeft->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);

				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = town->TileIdxTOTIlePos(dest);
				playerGo = true;
				onGrassImg->isVisible = false;
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
	else if (INPUT->KeyDown(VK_RETURN) && playerGo == false)
	{
		mapMenu->SetWorldPos(player->playerFront->GetWorldPos());
		mapMenuSel->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x + 280.0f, player->playerFront->GetWorldPos().y + 305.0f)); // -35씩
		SOUND->Stop("MENUOPEN");
		SOUND->Play("MENUOPEN");
		state = TownState::POKEMENU;
	}
	


	
	if (playerGo && goWall == false)
	{
		player->SetPlayerPos(Utility::Lerp(plSour, plDest, g));
		g += DELTA * 3.3f;

		//도착지를 지났을때

		if (g > 1.0f)
		{
			g = 0.0f;
			player->SetPlayerPos(plDest);
			playerGo = false;
			player->SetPlayerAni(ANIMSTATE::STOP, 0.1f);
			if (onGrassImg->isVisible == true)
			{
				int temp = RANDOM->Int(0, 4);
				if (temp == 0)
				{
					temp = RANDOM->Int(0, 2);
					player->enemyPokemon.push_front(fieldPoke[temp]->Create(fieldPoke[temp]));
					player->enemyPokemon[0]->lv = RANDOM->Int(player->myPokemon[0]->lv - 2, player->myPokemon[0]->lv);
					if (player->enemyPokemon[0]->lv <= 0)
					{
						player->enemyPokemon[0]->lv = 1;
					}
					player->enemyPokemon[0]->SetPokemon();
					battleStart = true;
				}
			}
			else if (plDest.x == town->TileIdxTOTIlePos(Int2(21, 10)).x && plDest.y == town->TileIdxTOTIlePos(Int2(21, 10)).y)
			{
				goShop = true;
				player->SetPlayerVisible(false);
				SOUND->Stop("DOPEN");
				SOUND->Play("DOPEN");

			}
			else if (plDest.x == town->TileIdxTOTIlePos(Int2(18, 22)).x && plDest.y == town->TileIdxTOTIlePos(Int2(18, 22)).y)
			{
				goCave = true;
				player->SetPlayerVisible(false);
				SOUND->Stop("DOPEN");
				SOUND->Play("DOPEN");

			}
		}
		else if (g > 0.7f)
		{
			Int2 dest;
			if (town->WorldPosToTileIdx(plDest, dest) && town->GetTileState(dest) == TileState::TILE_TRAP)
			{
				onGrassImg->isVisible = true;
				onGrassImg->SetWorldPos(plDest);
			}
			else
			{
				onGrassImg->isVisible = false;
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

void Town::POKEMENU()
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
			state = TownState::POKEMON;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		case 2:
			state = TownState::BAG;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			bag->sel = 0;
			break;
		case 6:
			state = TownState::TOWN;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			menuSel = 0;
			break;
		}
	}
	else if (INPUT->KeyDown('X'))
	{
		state = TownState::TOWN;
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

void Town::POKEMON()
{
	switch (pokeMenu->state)
	{
	case PokeMenuState::SEL:
		if (INPUT->KeyDown('X') && pokeMenu->state == PokeMenuState::SEL)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = TownState::POKEMENU;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;
		}
		else if (INPUT->KeyDown('Z') && pokeMenu->selPokeList == 6 && pokeMenu->state == PokeMenuState::SEL)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = TownState::POKEMENU;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;

		}
		break;
	case PokeMenuState::BAG_ITEM:
		if (INPUT->KeyDown('X') && pokeMenu->state == PokeMenuState::BAG_ITEM)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = TownState::BAG;
			pokeMenu->state = PokeMenuState::SEL;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;
		}
		else if (INPUT->KeyDown('Z') && pokeMenu->selPokeList == 6 && pokeMenu->state == PokeMenuState::BAG_ITEM)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = TownState::BAG;
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
				state = TownState::BAG;
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

void Town::BAG()
{
	if (INPUT->KeyDown('X') && bag->state == BagMenuState::SEL)
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		state = TownState::POKEMENU;
		bag->sel = 0;
		bag->keyOn = false;
	}
	else if (INPUT->KeyDown('Z') && bag->state == BagMenuState::SEL && bag->sel == player->myItem.size())
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		state = TownState::POKEMENU;
		bag->sel = 0;
		bag->keyOn = false;

	}
	
	//bag->ContrlBagMenu();
}

void Town::SetSound()
{
	SOUND->AddSound("sel.wav", "SEL");
	SOUND->AddSound("Attack.wav", "ATTACK");
	SOUND->AddSound("doorOpen.wav", "DOPEN");
	SOUND->AddSound("doorOut.wav", "DOUT");
	SOUND->AddSound("expGain.wav", "EXP");
	SOUND->AddSound("goWall.wav", "WALL");
	SOUND->AddSound("levelUP.wav", "LEVUP");
	SOUND->AddSound("menuOpen.wav", "MENUOPEN");
	SOUND->AddSound("pokeballSwap.wav", "BALLSWAP");
	SOUND->AddSound("pokeCenterMachine.wav", "MACHINE");
	SOUND->AddSound("potion.wav", "POTION");
	SOUND->AddSound("run.wav", "RUN");
	SOUND->AddSound("slideDoorOpen.wav", "SDOPEN");
	SOUND->AddSound("throwBall.wav", "BALL");
	SOUND->AddSound("ballBounce (1).wav", "BALL_BOUNCE1");
	SOUND->AddSound("ballBounce (2).wav", "BALL_BOUNCE2");
	SOUND->AddSound("ballBounce (3).wav", "BALL_BOUNCE3");
	SOUND->AddSound("pokeballCatch.wav", "BALL_CATCH");
	SOUND->AddSound("Pokemon_Caught.mp3", "BALL_CAUGHT");
	SOUND->AddSound("die.wav", "DIE");
	SOUND->AddSound("gainItem.wav", "ITEM");
	SOUND->AddSound("findMap.wav", "FIND");

	SOUND->AddSound("battle.mp3", "BATTLE", true);
	SOUND->AddSound("Cave.mp3", "CAVE", true);
	SOUND->AddSound("Fanfare- Evolution.mp3", "EVO2");
	SOUND->AddSound("Evolution.mp3", "EVO1",true);
	SOUND->AddSound("Pallet Town.mp3", "TOWNBGM", true);
	SOUND->AddSound("Shop.mp3", "SHOPBGM", true);
	SOUND->SetVolume("SHOPBGM", 0.5f);
	SOUND->AddSound("Pokémon Healed.mp3", "HEALED");
	SOUND->AddSound("Victory.mp3", "WIN", true);

	SOUND->AddSound("001 - Bulbasaur.wav", "001");
	SOUND->AddSound("002 - Ivysaur.wav", "002");
	SOUND->AddSound("003 - Venusaur.wav", "003");
	SOUND->AddSound("004 - Charmander.wav", "004");
	SOUND->AddSound("005 - Charmeleon.wav", "005");
	SOUND->AddSound("006 - Charizard.wav", "006");
	SOUND->AddSound("007 - Squirtle.wav", "007");
	SOUND->AddSound("008 - Wartortle.wav", "008");
	SOUND->AddSound("009 - Blastoise.wav", "009");
	SOUND->AddSound("143 - Snorlax.wav", "143");

	SOUND->AddSound("Tackle.mp3", "NORMAL");
	SOUND->AddSound("Fire Spin.mp3", "FIRE");
	SOUND->AddSound("Hydro Pump.mp3", "WATER");
	SOUND->AddSound("Vine Whip.mp3", "GRASS");





}
