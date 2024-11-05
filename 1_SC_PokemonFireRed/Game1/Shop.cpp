#include "stdafx.h"

void Shop::Init()
{
	LIGHT->light.inColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	shop = new ObTileMap();
	shop->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
	shop->file = "Shop1.txt";
	shop->Load();
	shop->CreateTileCost();

	shopBack = new ObImage(L"shop1.png");
	shopBack->scale = shopBack->imageSize * 5;
	shopBack->pivot = OFFSET_LB;
	shopBack->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
	
	shopFront = new ObImage(L"shop6.png");
	shopFront->scale = shopFront->imageSize * 5;
	shopFront->pivot = OFFSET_LB;
	shopFront->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	shopSel1 = new ObImage(L"shop2.png");
	shopSel1->scale = shopSel1->imageSize * 5;
	shopSel2 = new ObImage(L"shop3.png");
	shopSel2->scale = shopSel2->imageSize * 5;
	shopSel3 = new ObImage(L"shop4.png");
	shopSel3->scale = shopSel3->imageSize * 5;
	shopSel4 = new ObImage(L"shop5.png");
	shopSel4->scale = shopSel4->imageSize * 5;
	shopSel5 = new ObImage(L"shop7.png");
	shopSel5->scale = shopSel5->imageSize * 5;
	shopMenu = new ObImage(L"PokeFullMenu2.png");
	shopMenu->scale = shopMenu->imageSize * 5;
	shopMenu->pivot = OFFSET_LB;
	shopMenuSel = 0;
	buyNum = 1;
	selNum = 1;
	totalNum = 0;
	sel_0 = L"";
	isErase = false;

	player->SetPlayerPos(shop->TileIdxTOTIlePos(Int2(11, 9)));
	player->playerBack->isVisible = true;

	player->Update();
	//이동
	playerGo = false;
	playerTurn = false;
	goWall = false;
	//아이템
	setItem[0] = new PokeBall();
	setItem[1] = new Portion();
	closeImg = new ObImage(L"Bag Screens5.png");
	closeImg->scale = closeImg->imageSize * 5;
	closeImg->SetWorldPos(Vector2(-502.0f, -280.0f));
	//메뉴
	mapMenu = new ObImage(L"PokeFullMenu1.png");
	mapMenu->scale = mapMenu->imageSize * 5;
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
	//상점 메세지
	wstring shopMes = L"";
	int mesNum = 0;
	int mesIndex = 0;
	float mesTime = 0.0f;
	//씬전환
	goTown = false;
	//조명
	lightCol = 0.0f;
	fadeIn = true;
	fadeOut = false;
}

void Shop::Release()
{
	SafeDelete(shop);
	SafeDelete(shopBack);
	SafeDelete(shopFront);
	SafeDelete(setItem[0]);
	SafeDelete(setItem[1]);
	SafeDelete(mapMenu);
	SafeDelete(mapMenuSel);
	SafeDelete(pokeMenu);
	SafeDelete(bag);
}

void Shop::Update()
{
	Int2 test;
	if (shop->WorldPosToTileIdx(player->playerFront->GetWorldPos(), test))
	{
		cout << test.x << " " << test.y << " " << player->inTown << "/" << player->inCave << endl;
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
		case ShopState::SHOP:
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
					SOUND->Stop("SHOPBGM");
					player->SetPlayerPos(shop->TileIdxTOTIlePos(Int2(21, 10)));
					player->Update();
					SOUND->Play("TOWNBGM");
					SCENE->ChangeScene("Town");
					return;
				}

			}
			else
			{
				SHOP();
			}
			break;
		case ShopState::MENU:
			MENU();

			break;
		case ShopState::BUY:
			BUY();

			break;
		case ShopState::SEL:
			SEL();

			break;
		case ShopState::POKEMENU:
			POKEMENU();
			break;
		case ShopState::POKEMON:
			POKEMON();
			break;
		case ShopState::BAG:
			BAG();
			bag->Update();
			if (bag->usedItemName == L"상처약")
			{
				state = ShopState::POKEMON;
				bag->keyOn = false;
				pokeMenu->SetState(PokeMenuState::BAG_ITEM);
				bag->usedItemName = L"";
			}
			break;
		default:
			break;
		}
	}
	
	shop->Update();
	shopBack->Update();
	shopFront->Update();
	player->Update();
	mapMenu->Update();
	mapMenuSel->Update();
	pokeMenu->Update();
	shopSel1->Update();
	shopSel2->Update();
	shopSel3->Update();
	shopSel4->Update();
	shopSel5->Update();

	shopMenu->Update();
	for (int i = 0; i < 2; i++)
	{
		setItem[i]->itemImg->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 502.0f, player->playerFront->GetWorldPos().y - 280.0f));
		setItem[i]->itemImg->Update();
	}
	
	closeImg->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 502.0f, player->playerFront->GetWorldPos().y - 280.0f));
	closeImg->Update();
}

void Shop::LateUpdate()
{
	switch (state)
	{
	case ShopState::SHOP:
		CAM->position = player->playerFront->GetWorldPos();
		break;
	case ShopState::MENU:
		break;
	case ShopState::BUY:
		break;
	case ShopState::SEL:
		break;
	case ShopState::POKEMENU:
		CAM->position = player->playerFront->GetWorldPos();
		break;
	case ShopState::POKEMON:
		CAM->position = Vector2(0.0f, 0.0f);
		break;
	case ShopState::BAG:
		CAM->position = Vector2(0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void Shop::Render()
{
	switch (state)
	{
	case ShopState::SHOP:
		shopBack->Render();
		shop->Render();
		player->Render();
		shopFront->Render();
		break;
	case ShopState::MENU:

		shopBack->Render();
		shop->Render();
		player->Render();
		shopFront->Render();
		shopSel1->Render();
		switch (mesNum)
		{
		case 1:
			shopSel5->Render();
			shopMenu->Render();
		case 0:
		{
			long leftR = 100;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			long sizeR = 60.0f;

			wstring tempW;
			//shopMes = L"어서　오세요!\n무엇을　도와　드릴까요?";
			if (mesIndex < shopMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.05))
				{
					mesIndex++;
				}
			}
			DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			if (mesIndex == shopMes.size())
			{
				mesNum = 1;
				//mesIndex = 0;
			}
		}
			break;
		default:
			break;
		}

		break;
	case ShopState::BUY:
		
		shopBack->Render();
		shop->Render();
		player->Render();
		shopFront->Render();
		shopSel2->Render();
		shopMenu->Render();
		//플레이어 돈
		{
			long leftR = 0;
			long topR = 93;
			long rightR = leftR + 363;
			long botR = topR + 100;
			float sizeR = 60.0f;
			wstring wordR = to_wstring(player->money) + L"원";
			DWRITE->RenderText(wordR, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR, topR, rightR, botR }, sizeR,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
		}
		//아이템 이름
		{
			long leftR = 490;
			long topR = 35;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 60.0f;
			wstring wordR = L"";
			for (int i = 0; i < 2; i++)
			{
				leftR = 490;
				topR = 35 + 80 * i;
				rightR = leftR + 1200;
				botR = topR + 100;
				wordR = setItem[i]->name;
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR, topR, rightR, botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				leftR = 940;
				topR = 35 + 80 * i;
				rightR = leftR + 180;
				botR = topR + 100;
				sizeR = 57.0f;
				wordR = to_wstring(setItem[i]->price) + L"원";
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR, topR, rightR, botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			}
			leftR = 490;
			topR = 35 + 80 * 2;
			rightR = leftR + 1200;
			botR = topR + 100;
			DWRITE->RenderText(L"그만둔다", RECT{ leftR + 5, topR, rightR + 5,  botR }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR, topR, rightR, botR }, 60.0f,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		}
		
		switch (mesNum)
		{
		case 0:
			//아이템 설명
		{
			long leftR = 210;
			long topR = 560;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 57.0f;
			wstring word;
			if (shopMenuSel < 2)
			{
				DWRITE->RenderText(setItem[shopMenuSel]->explanation, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(setItem[shopMenuSel]->explanation, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(setItem[shopMenuSel]->explanation, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(setItem[shopMenuSel]->explanation, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(setItem[shopMenuSel]->explanation, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(setItem[shopMenuSel]->explanation, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(setItem[shopMenuSel]->explanation, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(setItem[shopMenuSel]->explanation, RECT{ leftR, topR, rightR, botR }, sizeR,
					L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			}
		}
		    if (shopMenuSel < 2)
		    {
		    	setItem[shopMenuSel]->itemImg->Render();
		    }
		    else
		    {
		    	closeImg->Render();
		    }
			break;
		case 2:
			shopSel3->Render();
			{
				long leftR = 0;
				long topR = 435;
				long rightR = leftR + 570;
				long botR = topR + 100;
				long sizeR = 60.0f;

				wstring tempW = to_wstring(totalNum) + L"개　갖고　있음";
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				leftR = 0;
				topR = 395;
				rightR = leftR + 1160;
				botR = topR + 100;
				sizeR = 60.0f;
				int temp = buyNum * setItem[shopMenuSel]->price;
				tempW = to_wstring(temp) + L"원";
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				leftR = 0;
				topR = 403;
				rightR = leftR + 793;
				botR = topR + 100;
				sizeR = 50.0f;
				tempW = to_wstring(buyNum);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			}
		case 1:
			shopSel1->Render();
			{
				long leftR = 100;
				long topR = 595;
				long rightR = leftR + 1200;
				long botR = topR + 100;
				long sizeR = 60.0f;

				wstring tempW;
				shopMes = setItem[shopMenuSel]->name + L"을(를)\n몇　개　구입하시겠습니까?";
				if (mesIndex < shopMes.size())
				{
					if (TIMER->GetTick(mesTime, 0.05))
					{
						mesIndex++;
					}
				}
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
				if (mesIndex == shopMes.size())
				{
					mesNum = 2;
					//mesIndex = 0;
				}
			}
			break;
		case 3:
			shopSel1->Render();
			{
				long leftR = 100;
				long topR = 595;
				long rightR = leftR + 1200;
				long botR = topR + 100;
				long sizeR = 60.0f;

				//wstring tempW = L"네　여기　있습니다.\n감사합니다";
				shopMes = L"네　여기　있습니다.\n감사합니다.";
				if (mesIndex < shopMes.size())
				{
					if (TIMER->GetTick(mesTime, 0.05))
					{
						mesIndex++;
						if (mesIndex == shopMes.size())
						{
							SOUND->Stop("ITEM");
							SOUND->Play("ITEM");
							player->money -= setItem[shopMenuSel]->price * buyNum;

						}
					}
				}
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			}
			break;
		case 4:
			shopSel1->Render();
			{
				long leftR = 100;
				long topR = 595;
				long rightR = leftR + 1200;
				long botR = topR + 100;
				long sizeR = 60.0f;

				//wstring tempW = L"네　여기　있습니다.\n감사합니다";
				shopMes = L"가방이 가득 찼습니다.";
				if (mesIndex < shopMes.size())
				{
					if (TIMER->GetTick(mesTime, 0.05))
					{
						mesIndex++;
					}
				}
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			}
		default:
			break;
		}
		
		break;
	case ShopState::SEL:
		shopBack->Render();
		shop->Render();
		player->Render();
		shopFront->Render();
		shopSel2->Render();
		shopMenu->Render();
		//플레이어 돈
		{
			long leftR = 0;
			long topR = 93;
			long rightR = leftR + 363;
			long botR = topR + 100;
			float sizeR = 60.0f;
			wstring wordR = to_wstring(player->money) + L"원";
			DWRITE->RenderText(wordR, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			DWRITE->RenderText(wordR, RECT{ leftR, topR, rightR, botR }, sizeR,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
		}
		//아이템 이름
		{

			long leftR = 490;
			long topR = 35;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 60.0f;
			wstring wordR = L"";
			for (int i = 0; i < player->myItem.size(); i++)
			{
				leftR = 490;
				topR = 35 + 80 * i;
				rightR = leftR + 1200;
				botR = topR + 100;
				wordR = player->myItem[i]->name;
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(wordR, RECT{ leftR, topR, rightR, botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				leftR = 940;
				topR = 35 + 80 * i;
				rightR = leftR + 180;
				botR = topR + 100;
				sizeR = 57.0f;
				wordR = to_wstring(player->myItem[i]->num)+ L"개";
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
					L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(wordR, RECT{ leftR, topR, rightR, botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
			}
			leftR = 490;
			topR = 35 + 80 * player->myItem.size();
			rightR = leftR + 1200;
			botR = topR + 100;
			DWRITE->RenderText(L"그만둔다", RECT{ leftR + 5, topR, rightR + 5,  botR }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->RenderText(L"그만둔다", RECT{ leftR, topR, rightR, botR }, 60.0f,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			DWRITE->GetDC()->EndDraw();
			DWRITE->GetDC()->BeginDraw();

		}
		switch (mesNum)
		{
		case 0:
			//아이템 설명
		{
			long leftR = 210;
			long topR = 560;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 57.0f;
			wstring word;
			if (shopMenuSel < player->myItem.size())
			{
				DWRITE->RenderText(player->myItem[shopMenuSel]->explanation, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(player->myItem[shopMenuSel]->explanation, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(player->myItem[shopMenuSel]->explanation, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(player->myItem[shopMenuSel]->explanation, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(player->myItem[shopMenuSel]->explanation, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(player->myItem[shopMenuSel]->explanation, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(player->myItem[shopMenuSel]->explanation, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(player->myItem[shopMenuSel]->explanation, RECT{ leftR, topR, rightR, botR }, sizeR,
					L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			}

		}
		if (shopMenuSel < player->myItem.size())
		{
			player->myItem[shopMenuSel]->itemImg->Render();
		}
		else
		{
			closeImg->Render();
		}
			break;
		case 2:
			shopSel4->Render();
			{
				long leftR = 0;
				long topR = 435;
				long rightR = leftR + 570;
				long botR = topR + 100;
				long sizeR = 60.0f;
				wstring tempW;

				leftR = 0;
				topR = 395;
				rightR = leftR + 1160;
				botR = topR + 100;
				sizeR = 60.0f;
				int temp = selNum * (player->myItem[shopMenuSel]->price / 2);
				tempW = to_wstring(temp) + L"원";
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				leftR = 0;
				topR = 403;
				rightR = leftR + 793;
				botR = topR + 100;
				sizeR = 50.0f;
				tempW = to_wstring(selNum);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);
				DWRITE->RenderText(tempW, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING);

			}
		case 1:
			shopSel1->Render();
			{
				long leftR = 100;
				long topR = 595;
				long rightR = leftR + 1200;
				long botR = topR + 100;
				long sizeR = 60.0f;

				wstring tempW;
				shopMes = player->myItem[shopMenuSel]->name + L"을(를)\n몇　개　파시겠습니까?";
				if (mesIndex < shopMes.size())
				{
					if (TIMER->GetTick(mesTime, 0.05))
					{
						mesIndex++;
					}
				}
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
				if (mesIndex == shopMes.size())
				{
					mesNum = 2;
					//mesIndex = 0;
				}
			}
			break;
		case 3:
			shopSel1->Render();
			{
				long leftR = 100;
				long topR = 595;
				long rightR = leftR + 1200;
				long botR = topR + 100;
				long sizeR = 60.0f;

				//wstring tempW = L"네　여기　있습니다.\n감사합니다";
				if (isErase == false)
				{
					sel_0 = player->myItem[shopMenuSel]->name;
					shopMes = sel_0 + L"　" + to_wstring(selNum) + L"개를　팔아\n" + to_wstring(player->myItem[shopMenuSel]->price / 2 * selNum) + L"원을 얻었습니다!";
				}
				if (mesIndex < shopMes.size())
				{
					if (TIMER->GetTick(mesTime, 0.05))
					{
						mesIndex++;
						if (mesIndex == shopMes.size())
						{
							SOUND->Stop("ITEM");
							SOUND->Play("ITEM");
							player->myItem[shopMenuSel]->num -= selNum;
							player->money += player->myItem[shopMenuSel]->price / 2 * selNum;
							if (player->myItem[shopMenuSel]->num == 0)
							{
								player->myItem.erase(player->myItem.begin() + shopMenuSel);
								isErase = true;
							}
						}
					}
				}
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
				DWRITE->RenderText(shopMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
			}
			break;
		default:
			break;
		}
		
		
		break;
	case ShopState::POKEMENU:
		shopBack->Render();
		shop->Render();
		player->Render();
		shopFront->Render();
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
	case ShopState::POKEMON:
		pokeMenu->Render();
		break;
	case ShopState::BAG:
		bag->Render();
		break;
	default:
		break;
	}
}

void Shop::ResizeScreen()
{
}

void Shop::SHOP()
{
	if (INPUT->KeyDown(VK_UP) && player->playerBack->isVisible == false && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = true;
		player->playerBack->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.03);
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
		if (shop->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x, player->playerBack->GetWorldPos().y + shop->scale.y), dest) &&
			shop->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (shop->GetTileState(sour) != TileState::TILE_WALL && shop->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerBack->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);
				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = shop->TileIdxTOTIlePos(dest);
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
		player->playerFront->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.03);
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
		if (shop->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x, player->playerBack->GetWorldPos().y - shop->scale.y), dest) && shop->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (sour.x == 11 && sour.y == 9)
			{
				goTown = true;
				SOUND->Stop("DOUT");
				SOUND->Play("DOUT");
				return;
			}
			if (shop->GetTileState(sour) != TileState::TILE_WALL && shop->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerFront->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);

				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = shop->TileIdxTOTIlePos(dest);
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
		player->playerRight->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.03);

		playerTurn = true;

	}
	else if (INPUT->KeyPress(VK_RIGHT) && playerGo == false && playerTurn == false)
	{
		player->playerBack->isVisible = false;
		player->playerFront->isVisible = false;
		player->playerLeft->isVisible = false;
		player->playerRight->isVisible = true;
		Int2 sour, dest;
		if (shop->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x + shop->scale.x, player->playerBack->GetWorldPos().y), dest) && shop->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (shop->GetTileState(sour) != TileState::TILE_WALL && shop->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerRight->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);
				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = shop->TileIdxTOTIlePos(dest);
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
	player->playerLeft->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.03);
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
		if (shop->WorldPosToTileIdx(Vector2(player->playerBack->GetWorldPos().x - shop->scale.x, player->playerBack->GetWorldPos().y), dest) && shop->WorldPosToTileIdx(player->playerBack->GetWorldPos(), sour))
		{
			if (shop->GetTileState(sour) != TileState::TILE_WALL && shop->GetTileState(dest) != TileState::TILE_WALL)
			{
				player->playerLeft->ChangeAnim(ANIMSTATE::HALF_ONCE, 0.13f);

				g = 0.0f;
				plSour = player->playerBack->GetWorldPos();
				plDest = shop->TileIdxTOTIlePos(dest);
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
	else if (INPUT->KeyDown(VK_RETURN) && playerGo == false && playerTurn == false)
	{
		mapMenu->SetWorldPos(player->playerFront->GetWorldPos());
		mapMenuSel->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x + 280.0f, player->playerFront->GetWorldPos().y + 305.0f)); // -35씩
		SOUND->Stop("MENUOPEN");
		SOUND->Play("MENUOPEN");
		state = ShopState::POKEMENU;
	}
	else if (INPUT->KeyDown('Z') && playerGo == false && playerTurn == false && player->playerLeft->isVisible == true && player->playerFront->GetWorldPivot() == shop->TileIdxTOTIlePos(Int2(11, 13)))
	{
	    SOUND->Stop("SEL");
	    SOUND->Play("SEL");
		shopSel1->SetWorldPos(player->playerFront->GetWorldPos());
		shopSel2->SetWorldPos(player->playerFront->GetWorldPos());
		shopSel3->SetWorldPos(player->playerFront->GetWorldPos());
		shopSel4->SetWorldPos(player->playerFront->GetWorldPos());
		shopSel5->SetWorldPos(player->playerFront->GetWorldPos());
	    mapMenuSel->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x + 280.0f, player->playerFront->GetWorldPos().y + 305.0f)); // -35씩
		shopMenuSel = 0;
	    state = ShopState::MENU;
		shopMes = L"어서　오세요!\n무엇을　도와　드릴까요?";

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
		}
	}
	else if (goWall)
	{
		if (TIMER->GetTick(wallTime, 0.6))
		{
			SOUND->Stop("WALL");
			SOUND->Play("WALL");
			goWall = false;
			playerGo = false;
		}
	}
	else if (playerTurn)
	{
		if (TIMER->GetTick(wallTime, 0.06))
		{
			playerTurn = false;
		}
	}
}

void Shop::MENU()
{
	for (int i = 0; i < player->myItem.size(); i++)
	{
		player->myItem[i]->itemImg->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 502.0f, player->playerFront->GetWorldPos().y - 280.0f));
		player->myItem[i]->itemImg->Update();
	}
	switch (mesNum)
	{
	case 1:
		if (INPUT->KeyDown(VK_UP))
		{
			if (shopMenuSel > 0)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				shopMenuSel--;
			}
		}
		else if (INPUT->KeyDown(VK_DOWN))
		{
			if (shopMenuSel < 2)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				shopMenuSel++;
			}
		}
		else if (INPUT->KeyDown('Z'))
		{
			switch (shopMenuSel)
			{
			case 0:
				state = ShopState::BUY;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				mesNum = 0;
				mesIndex = 0;
				shopMenuSel = 0;
				break;
			case 1:
				state = ShopState::SEL;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				mesNum = 0;
				mesIndex = 0;
				shopMenuSel = 0;

				break;
			case 2:
				state = ShopState::SHOP;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				mesNum = 0;
				mesIndex = 0;
				shopMenuSel = 0;
				shopMes = L"어서　오세요!\n무엇을　도와　드릴까요?";
				for (int i = 0; i < player->myItem.size(); i++)
				{
					player->myItem[i]->itemImg->SetWorldPos(Vector2(-502.0f, -280.0f));
					player->myItem[i]->itemImg->Update();
				}
				
				break;
			}
		}
		else if (INPUT->KeyDown('X'))
		{
			state = ShopState::SHOP;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			mesNum = 0;
			mesIndex = 0;
			shopMenuSel = 0;
			shopMes = L"어서　오세요!\n무엇을　도와　드릴까요?";
			for (int i = 0; i < player->myItem.size(); i++)
			{
				player->myItem[i]->itemImg->SetWorldPos(Vector2(-502.0f, -280.0f));
				player->myItem[i]->itemImg->Update();
			}

		}
		switch (shopMenuSel)
		{
		case 0:
			shopMenu->SetWorldPosX(player->playerFront->GetWorldPos().x - 525.0f);
			shopMenu->SetWorldPosY(player->playerFront->GetWorldPos().y + 295.0f);
			break;
		case 1:
			shopMenu->SetWorldPosX(player->playerFront->GetWorldPos().x - 525.0f);
			shopMenu->SetWorldPosY(player->playerFront->GetWorldPos().y + 215.0f);
			break;
		case 2:
			shopMenu->SetWorldPosX(player->playerFront->GetWorldPos().x - 525.0f);
			shopMenu->SetWorldPosY(player->playerFront->GetWorldPos().y + 135.0f);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
}

void Shop::BUY()
{
	switch (mesNum)
	{
	case 0:
		if (INPUT->KeyDown(VK_UP))
		{
			if (shopMenuSel > 0)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				shopMenuSel--;
			}
		}
		else if (INPUT->KeyDown(VK_DOWN))
		{
			if (shopMenuSel < 3)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				shopMenuSel++;
			}
		}
		else if (INPUT->KeyDown('Z'))
		{
			switch (shopMenuSel)
			{
			case 0:
				mesNum++;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				for (int i = 0; i < player->myItem.size(); i++)
				{
					if (player->myItem[i]->name == setItem[shopMenuSel]->name)
					{
						totalNum += player->myItem[i]->num;
					}
					
				}
				break;
			case 1:
				mesNum++;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				for (int i = 0; i < player->myItem.size(); i++)
				{
					if (player->myItem[i]->name == setItem[shopMenuSel]->name)
					{
						totalNum += player->myItem[i]->num;
					}
				}
				break;
			case 2:
				state = ShopState::MENU;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				mesNum = 0;
				mesIndex = 0;
				shopMenuSel = 0;
				shopMes = L"그　밖에　저희가\n뭐　도와드릴　건　없습니까?";
				break;
			}
		}
		else if (INPUT->KeyDown('X'))
		{
			state = ShopState::MENU;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			mesNum = 0;
			mesIndex = 0;
			shopMenuSel = 0;
			shopMes = L"그　밖에　저희가\n뭐　도와드릴　건　없습니까?";
		}
		switch (shopMenuSel)
		{
		case 0:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y + 294.0f));
			break;
		case 1:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y + 214.0f));
			break;
		case 2:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y + 134.0f));
			break;
		case 3:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y + 54.0f));
			break;
		case 4:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y - 26.0f));
			break;
		case 5:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y - 106.0f));
			break;
		default:
			break;
		}
		break;
	case 1:
		break;
	case 2:
		if (INPUT->KeyDown(VK_UP))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			buyNum++;
			if (player->money < buyNum * setItem[shopMenuSel]->price)
			{
				buyNum = 1;
			}
			else if (buyNum > 99)
			{
				buyNum = 1;
			}
			keyDownTime = 0.0f;

		}
		else if (INPUT->KeyPress(VK_UP))
		{
			if (TIMER->GetTick(keyDownTime, 0.2))
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				buyNum++;
				if (player->money < buyNum * setItem[shopMenuSel]->price)
				{
					buyNum = 1;
				}
				else if (buyNum > 99)
				{
					buyNum = 1;
				}
			}
			
		}
		else if (INPUT->KeyDown(VK_DOWN))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			if (buyNum == 1)
			{
				if (player->money / setItem[shopMenuSel]->price > 99)
				{
					buyNum = 99;
				}
				else
				{
					buyNum = player->money / setItem[shopMenuSel]->price;
				}
				
			}
			else
			{
				buyNum--;
			}
			keyDownTime = 0.0f;
		}
		else if (INPUT->KeyPress(VK_DOWN))
		{
			if (TIMER->GetTick(keyDownTime, 0.2))
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				if (buyNum == 1)
				{
					if (player->money / setItem[shopMenuSel]->price > 99)
					{
						buyNum = 99;
					}
					else
					{
						buyNum = player->money / setItem[shopMenuSel]->price;
					}
				}
				else
				{
					buyNum--;
				}
			}

		}
		else if (INPUT->KeyDown('Z'))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			bool isCheck = false;
			int index = 0;
			for (index = 0; index < player->myItem.size(); index++)
			{
				if (player->myItem[index]->name == setItem[shopMenuSel]->name)
				{
					if (player->myItem[index]->num + buyNum > 99)
					{
						continue;
					}
					else
					{
						isCheck = true;
						
						break;
					}
				}
				
			}
			mesNum = 3;
			if (isCheck)
			{
				player->myItem[index]->num += buyNum;
				//player->money -= setItem[shopMenuSel]->price * buyNum;
			}
			else if (player->myItem.size() < 5)
			{
				player->myItem.push_back(setItem[shopMenuSel]->Create());
				player->myItem.back()->num = buyNum;
				//player->money -= setItem[shopMenuSel]->price * buyNum;
			}
			else
			{
				mesNum = 4;
			}
			mesIndex = 0;
			totalNum = 0;
		}
		else if (INPUT->KeyDown('X'))
		{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
			mesNum = 0;
			mesIndex = 0;
			totalNum = 0;
			buyNum = 1;
		}
		break;
	case 3:
		if (mesIndex == shopMes.size())
		{
			
			if (INPUT->KeyDown('X') || INPUT->KeyDown('Z'))
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				mesNum = 0;
				mesIndex = 0;
				buyNum = 1;

			}
		}
		
		break;
	case 4:
		if (mesIndex == shopMes.size())
		{

			if (INPUT->KeyDown('X') || INPUT->KeyDown('Z'))
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				mesNum = 0;
				mesIndex = 0;
				buyNum = 1;

			}
		}
		break;
	default:
		break;
	}
	
}

void Shop::SEL()
{
	switch (mesNum)
	{
	case 0:
		if (INPUT->KeyDown(VK_UP))
		{
			if (shopMenuSel > 0)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				shopMenuSel--;
			}
		}
		else if (INPUT->KeyDown(VK_DOWN))
		{
			if (shopMenuSel < player->myItem.size())
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				shopMenuSel++;
			}
		}
		else if (INPUT->KeyDown('Z'))
		{
			if (shopMenuSel == player->myItem.size())
			{
				state = ShopState::MENU;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				mesNum = 0;
				mesIndex = 0;
				shopMenuSel = 0;
				shopMes = L"그　밖에　저희가\n뭐　도와드릴　건　없습니까?";
			}
			else
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				mesNum = 1;
			}

		}
		else if (INPUT->KeyDown('X'))
		{
			state = ShopState::MENU;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			mesNum = 0;
			mesIndex = 0;
			shopMenuSel = 0;
			shopMes = L"그　밖에　저희가\n뭐　도와드릴　건　없습니까?";
		}
		switch (shopMenuSel)
		{
		case 0:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y + 294.0f));
			break;
		case 1:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y + 214.0f));
			break;
		case 2:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y + 134.0f));
			break;
		case 3:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y + 54.0f));
			break;
		case 4:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y - 26.0f));
			break;
		case 5:
			shopMenu->SetWorldPos(Vector2(player->playerFront->GetWorldPos().x - 153.0f, player->playerFront->GetWorldPos().y - 106.0f));
			break;
		default:
			break;
		}
		break;
	case 2:
		if (INPUT->KeyDown(VK_UP))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			selNum++;
			if (selNum > player->myItem[shopMenuSel]->num)
			{
				selNum = 1;
			}
			
			keyDownTime = 0.0f;

		}
		else if (INPUT->KeyPress(VK_UP))
		{
			if (TIMER->GetTick(keyDownTime, 0.2))
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				selNum++;
				if (selNum > player->myItem[shopMenuSel]->num)
				{
					selNum = 1;
				}
			}

		}
		else if (INPUT->KeyDown(VK_DOWN))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			if (selNum == 1)
			{
				selNum = player->myItem[shopMenuSel]->num;
			}
			else
			{
				selNum--;
			}
			keyDownTime = 0.0f;
		}
		else if (INPUT->KeyPress(VK_DOWN))
		{
			if (TIMER->GetTick(keyDownTime, 0.2))
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				if (selNum == 1)
				{
					selNum = player->myItem[shopMenuSel]->num;
				}
				else
				{
					selNum--;
				}
			}

		}
		else if (INPUT->KeyDown('Z'))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			
			mesNum = 3;
			mesIndex = 0;
			totalNum = 0;
		}
		else if (INPUT->KeyDown('X'))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			mesNum = 0;
			mesIndex = 0;
			totalNum = 0;
		}
		break;
	case 3:
		if (mesIndex == shopMes.size())
		{

			if (INPUT->KeyDown('X') || INPUT->KeyDown('Z'))
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				mesNum = 0;
				mesIndex = 0;
				selNum = 1;
				isErase = false;
			}
		}
		break;
	default:
		break;
	}
	
}

void Shop::POKEMENU()
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
			state = ShopState::POKEMON;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		case 2:
			state = ShopState::BAG;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			bag->sel = 0;
			break;
		case 6:
			state = ShopState::SHOP;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			menuSel = 0;
			break;
		}
	}
	else if (INPUT->KeyDown('X'))
	{
		state = ShopState::SHOP;
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

void Shop::POKEMON()
{
	switch (pokeMenu->state)
	{
	case PokeMenuState::SEL:
		if (INPUT->KeyDown('X') && pokeMenu->state == PokeMenuState::SEL)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = ShopState::POKEMENU;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;
		}
		else if (INPUT->KeyDown('Z') && pokeMenu->selPokeList == 6 && pokeMenu->state == PokeMenuState::SEL)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = ShopState::POKEMENU;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;

		}
		break;
	case PokeMenuState::BAG_ITEM:
		if (INPUT->KeyDown('X') && pokeMenu->state == PokeMenuState::BAG_ITEM)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = ShopState::BAG;
			pokeMenu->state = PokeMenuState::SEL;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;
		}
		else if (INPUT->KeyDown('Z') && pokeMenu->selPokeList == 6 && pokeMenu->state == PokeMenuState::BAG_ITEM)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = ShopState::BAG;
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
				state = ShopState::BAG;
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

void Shop::BAG()
{
	if (INPUT->KeyDown('X') && bag->state == BagMenuState::SEL)
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		state = ShopState::POKEMENU;
		bag->sel = 0;
		bag->keyOn = false;
	}
	else if (INPUT->KeyDown('Z') && bag->state == BagMenuState::SEL && bag->sel == player->myItem.size())
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		state = ShopState::POKEMENU;
		bag->sel = 0;
		bag->keyOn = false;

	}
}

