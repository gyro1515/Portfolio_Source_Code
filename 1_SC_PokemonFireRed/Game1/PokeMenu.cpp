#include "stdafx.h"

PokeMenu::PokeMenu()
{
	pokeListBack_Img = new ObImage(L"Pokemon Menu1.png");
	pokeListBack_Img->scale = pokeListBack_Img->imageSize * 5;
	pokeListBack_Img->pivot = OFFSET_LB;
	pokeListBack_Img->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	outUseItem = new ObImage(L"Pokemon Menu13.png");
	outUseItem->scale = outUseItem->imageSize * 5;
	outUseItem->pivot = OFFSET_LB;
	outUseItem->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	pokeListPick1_Img[0] = new ObImage(L"Pokemon Menu2.png");
	pokeListPick1_Img[1] = new ObImage(L"Pokemon Menu3.png");
	pokeListPick1_Img[2] = new ObImage(L"Pokemon Menu12.png");
	pokeListPick2_Img[0] = new ObImage(L"Pokemon Menu4.png");
	pokeListPick2_Img[1] = new ObImage(L"Pokemon Menu5.png");
	pokeListPick2_Img[2] = new ObImage(L"Pokemon Menu11.png");
	pokeListPick3_Img[0] = new ObImage(L"Pokemon Menu4.png");
	pokeListPick3_Img[1] = new ObImage(L"Pokemon Menu5.png");
	pokeListPick3_Img[2] = new ObImage(L"Pokemon Menu11.png");
	pokeListPick4_Img[0] = new ObImage(L"Pokemon Menu4.png");
	pokeListPick4_Img[1] = new ObImage(L"Pokemon Menu5.png");
	pokeListPick4_Img[2] = new ObImage(L"Pokemon Menu11.png");
	pokeListPick5_Img[0] = new ObImage(L"Pokemon Menu4.png");
	pokeListPick5_Img[1] = new ObImage(L"Pokemon Menu5.png");
	pokeListPick5_Img[2] = new ObImage(L"Pokemon Menu11.png");
	pokeListPick6_Img[0] = new ObImage(L"Pokemon Menu4.png");
	pokeListPick6_Img[1] = new ObImage(L"Pokemon Menu5.png");
	pokeListPick6_Img[2] = new ObImage(L"Pokemon Menu11.png");
	pokeListPickC_Img[0] = new ObImage(L"Pokemon Menu9.png");
	pokeListPickC_Img[1] = new ObImage(L"Pokemon Menu10.png");
	for (int i = 0; i < 3; i++)
	{
		pokeListPick1_Img[i]->scale = pokeListPick1_Img[i]->imageSize * 5;
		pokeListPick1_Img[i]->pivot = OFFSET_LB;
		pokeListPick1_Img[i]->SetWorldPos(Vector2(-590.0f, 25.0f));
		pokeListPick2_Img[i]->scale = pokeListPick2_Img[i]->imageSize * 5;
		pokeListPick2_Img[i]->pivot = OFFSET_LB;
		pokeListPick2_Img[i]->SetWorldPos(Vector2(-160.0f, 235.0f));
		pokeListPick3_Img[i]->scale = pokeListPick3_Img[i]->imageSize * 5;
		pokeListPick3_Img[i]->pivot = OFFSET_LB;
		pokeListPick3_Img[i]->SetWorldPos(Vector2(-160.0f, 115.0f));
		pokeListPick4_Img[i]->scale = pokeListPick4_Img[i]->imageSize * 5;
		pokeListPick4_Img[i]->pivot = OFFSET_LB;
		pokeListPick4_Img[i]->SetWorldPos(Vector2(-160.0f, -5.0f));
		pokeListPick5_Img[i]->scale = pokeListPick5_Img[i]->imageSize * 5;
		pokeListPick5_Img[i]->pivot = OFFSET_LB;
		pokeListPick5_Img[i]->SetWorldPos(Vector2(-160.0f, -125.0f));
		pokeListPick6_Img[i]->scale = pokeListPick6_Img[i]->imageSize * 5;
		pokeListPick6_Img[i]->pivot = OFFSET_LB;
		pokeListPick6_Img[i]->SetWorldPos(Vector2(-160.0f, -245.0f));
	}
	for (int i = 0; i < 2; i++)
	{
		pokeListPickC_Img[i]->scale = pokeListPickC_Img[i]->imageSize * 5;
		pokeListPickC_Img[i]->pivot = OFFSET_LB;
		pokeListPickC_Img[i]->SetWorldPos(Vector2(320.0f, -380.0f));
	}
	for (int i = 0; i < 6; i++)
	{
		pokeListHpG_Img[i] = new ObImage(L"Pokemon Menu6.png");
		pokeListHpG_Img[i]->scale = pokeListHpG_Img[i]->imageSize * 5;
		pokeListHpG_Img[i]->pivot = OFFSET_LB;
		pokeListHpY_Img[i] = new ObImage(L"Pokemon Menu7.png");
		pokeListHpY_Img[i]->scale = pokeListHpY_Img[i]->imageSize * 5;
		pokeListHpY_Img[i]->pivot = OFFSET_LB;
		pokeListHpR_Img[i] = new ObImage(L"Pokemon Menu8.png");
		pokeListHpR_Img[i]->scale = pokeListHpR_Img[i]->imageSize * 5;
		pokeListHpR_Img[i]->pivot = OFFSET_LB;
	}
	pokeListHpG_Img[0]->SetWorldPos(Vector2(-440.0f, 90.0f));
	pokeListHpY_Img[0]->SetWorldPos(Vector2(-440.0f, 90.0f));
	pokeListHpR_Img[0]->SetWorldPos(Vector2(-440.0f, 90.0f));
	pokeListHpG_Img[1]->SetWorldPos(Vector2(320.0f, 295.0f));
	pokeListHpY_Img[1]->SetWorldPos(Vector2(320.0f, 295.0f));
	pokeListHpR_Img[1]->SetWorldPos(Vector2(320.0f, 295.0f));
	pokeListHpG_Img[2]->SetWorldPos(Vector2(320.0f, 175.0f));
	pokeListHpY_Img[2]->SetWorldPos(Vector2(320.0f, 175.0f));
	pokeListHpR_Img[2]->SetWorldPos(Vector2(320.0f, 175.0f));
	pokeListHpG_Img[3]->SetWorldPos(Vector2(320.0f, 55.0f));
	pokeListHpY_Img[3]->SetWorldPos(Vector2(320.0f, 55.0f));
	pokeListHpR_Img[3]->SetWorldPos(Vector2(320.0f, 55.0f));
	pokeListHpG_Img[4]->SetWorldPos(Vector2(320.0f, -65.0f));
	pokeListHpY_Img[4]->SetWorldPos(Vector2(320.0f, -65.0f));
	pokeListHpR_Img[4]->SetWorldPos(Vector2(320.0f, -65.0f));
	pokeListHpG_Img[5]->SetWorldPos(Vector2(320.0f, -185.0f));
	pokeListHpY_Img[5]->SetWorldPos(Vector2(320.0f, -185.0f));
	pokeListHpR_Img[5]->SetWorldPos(Vector2(320.0f, -185.0f));
	
	for (int i = 0; i < 6; i++)
	{
		pokeListDie[i] = new ObImage(L"Type Status Icons1.png");
		pokeListDie[i]->scale = pokeListDie[i]->imageSize * 5;
		pokeListDie[i]->pivot = OFFSET_LB;
	}
	pokeListDie[0]->SetWorldPos(Vector2(-515.0f, 40.0f));
	pokeListDie[1]->SetWorldPos(Vector2(245.0f, 245.0f));
	pokeListDie[2]->SetWorldPos(Vector2(245.0f, 125.0f));
	pokeListDie[3]->SetWorldPos(Vector2(245.0f, 5.0f));
	pokeListDie[4]->SetWorldPos(Vector2(245.0f, -115.0f));
	pokeListDie[5]->SetWorldPos(Vector2(245.0f, -235.0f));



	pokeListSize = 1;
	selPokeList = 0;
	lastSelPokeList = 1;
	for (int i = 0; i < 6; i++)
	{
		pokeList[i] = 0;
	}
	pokeMenuPlayer = 0;
	selChangePokeList = 0;
	useItemTime = 0.0f;
	pokemonToBag = false;
	changeHp = 0;
	changeHpFloat = 0.0f;

	state = PokeMenuState::SEL;
	tempS = "";
	tempW = L"";
	tempW2 = L"";

}

PokeMenu::~PokeMenu()
{
}

void PokeMenu::Update()
{
	switch (state)
	{
	case PokeMenuState::SEL:
		pokeListPick1_Img[1]->isVisible = true;
		pokeListPick2_Img[1]->isVisible = true;
		pokeListPick3_Img[1]->isVisible = true;
		pokeListPick4_Img[1]->isVisible = true;
		pokeListPick5_Img[1]->isVisible = true;
		pokeListPick6_Img[1]->isVisible = true;
		pokeListPickC_Img[1]->isVisible = true;
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[1]->isVisible = false;
			break;
		case 1:
			pokeListPick2_Img[1]->isVisible = false;

			break;
		case 2:
			pokeListPick3_Img[1]->isVisible = false;

			break;
		case 3:
			pokeListPick4_Img[1]->isVisible = false;

			break;
		case 4:
			pokeListPick5_Img[1]->isVisible = false;

			break;
		case 5:
			pokeListPick6_Img[1]->isVisible = false;

			break;
		case 6:
			pokeListPickC_Img[1]->isVisible = false;

			break;
		default:
			break;
		}
		break;
	case PokeMenuState::MENU:
		break;
	case PokeMenuState::CHANGE_SEL:
		pokeListPick1_Img[1]->isVisible = true;
		pokeListPick2_Img[1]->isVisible = true;
		pokeListPick3_Img[1]->isVisible = true;
		pokeListPick4_Img[1]->isVisible = true;
		pokeListPick5_Img[1]->isVisible = true;
		pokeListPick6_Img[1]->isVisible = true;
		pokeListPickC_Img[1]->isVisible = true;
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[1]->isVisible = false;
			break;
		case 1:
			pokeListPick2_Img[1]->isVisible = false;

			break;
		case 2:
			pokeListPick3_Img[1]->isVisible = false;

			break;
		case 3:
			pokeListPick4_Img[1]->isVisible = false;

			break;
		case 4:
			pokeListPick5_Img[1]->isVisible = false;

			break;
		case 5:
			pokeListPick6_Img[1]->isVisible = false;

			break;
		case 6:
			pokeListPickC_Img[1]->isVisible = false;

			break;
		default:
			break;
		}
		switch (selChangePokeList)
		{
		case 0:
			pokeListPick1_Img[1]->isVisible = false;
			break;
		case 1:
			pokeListPick2_Img[1]->isVisible = false;

			break;
		case 2:
			pokeListPick3_Img[1]->isVisible = false;

			break;
		case 3:
			pokeListPick4_Img[1]->isVisible = false;

			break;
		case 4:
			pokeListPick5_Img[1]->isVisible = false;

			break;
		case 5:
			pokeListPick6_Img[1]->isVisible = false;

			break;
		case 6:
			pokeListPickC_Img[1]->isVisible = false;

			break;
		default:
			break;
		}
		if (INPUT->KeyDown('X'))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = PokeMenuState::SEL;
		}
		break;
	case PokeMenuState::BATTEL_SEL:
		pokeListPick1_Img[1]->isVisible = true;
		pokeListPick2_Img[1]->isVisible = true;
		pokeListPick3_Img[1]->isVisible = true;
		pokeListPick4_Img[1]->isVisible = true;
		pokeListPick5_Img[1]->isVisible = true;
		pokeListPick6_Img[1]->isVisible = true;
		pokeListPickC_Img[1]->isVisible = true;
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[1]->isVisible = false;
			break;
		case 1:
			pokeListPick2_Img[1]->isVisible = false;

			break;
		case 2:
			pokeListPick3_Img[1]->isVisible = false;

			break;
		case 3:
			pokeListPick4_Img[1]->isVisible = false;

			break;
		case 4:
			pokeListPick5_Img[1]->isVisible = false;

			break;
		case 5:
			pokeListPick6_Img[1]->isVisible = false;

			break;
		case 6:
			pokeListPickC_Img[1]->isVisible = false;

			break;
		default:
			break;
		}
		break;
	case PokeMenuState::BATTEL_LOSE_SEL:
		pokeListPick1_Img[1]->isVisible = true;
		pokeListPick2_Img[1]->isVisible = true;
		pokeListPick3_Img[1]->isVisible = true;
		pokeListPick4_Img[1]->isVisible = true;
		pokeListPick5_Img[1]->isVisible = true;
		pokeListPick6_Img[1]->isVisible = true;
		pokeListPickC_Img[1]->isVisible = true;
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[1]->isVisible = false;
			break;
		case 1:
			pokeListPick2_Img[1]->isVisible = false;

			break;
		case 2:
			pokeListPick3_Img[1]->isVisible = false;

			break;
		case 3:
			pokeListPick4_Img[1]->isVisible = false;

			break;
		case 4:
			pokeListPick5_Img[1]->isVisible = false;

			break;
		case 5:
			pokeListPick6_Img[1]->isVisible = false;

			break;
		case 6:
			pokeListPickC_Img[1]->isVisible = false;

			break;
		default:
			break;
		}
		break;
	case PokeMenuState::BAG_ITEM:
		pokeListPick1_Img[1]->isVisible = true;
		pokeListPick2_Img[1]->isVisible = true;
		pokeListPick3_Img[1]->isVisible = true;
		pokeListPick4_Img[1]->isVisible = true;
		pokeListPick5_Img[1]->isVisible = true;
		pokeListPick6_Img[1]->isVisible = true;
		pokeListPickC_Img[1]->isVisible = true;
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[1]->isVisible = false;
			break;
		case 1:
			pokeListPick2_Img[1]->isVisible = false;

			break;
		case 2:
			pokeListPick3_Img[1]->isVisible = false;

			break;
		case 3:
			pokeListPick4_Img[1]->isVisible = false;

			break;
		case 4:
			pokeListPick5_Img[1]->isVisible = false;

			break;
		case 5:
			pokeListPick6_Img[1]->isVisible = false;

			break;
		case 6:
			pokeListPickC_Img[1]->isVisible = false;

			break;
		
		default:
			break;
		}
		break;
	case PokeMenuState::USE_BAG_ITEM:
		if (pokeMenuPlayer->myPokemon[selPokeList]->hp < pokeMenuPlayer->myPokemon[selPokeList]->changeHp)
		{
			changeHpFloat += changeHp * DELTA;
			pokeMenuPlayer->myPokemon[selPokeList]->hp = (int)changeHpFloat;
			//cout << DELTA * changeHp << " " << (int)changeHpFloat << endl;
		}
		else
		{
			pokeMenuPlayer->myPokemon[selPokeList]->hp = pokeMenuPlayer->myPokemon[selPokeList]->changeHp;
			pokemonToBag = true;
		}
		pokeListPick1_Img[1]->isVisible = true;
		pokeListPick2_Img[1]->isVisible = true;
		pokeListPick3_Img[1]->isVisible = true;
		pokeListPick4_Img[1]->isVisible = true;
		pokeListPick5_Img[1]->isVisible = true;
		pokeListPick6_Img[1]->isVisible = true;
		pokeListPickC_Img[1]->isVisible = true;
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[1]->isVisible = false;
			break;
		case 1:
			pokeListPick2_Img[1]->isVisible = false;

			break;
		case 2:
			pokeListPick3_Img[1]->isVisible = false;

			break;
		case 3:
			pokeListPick4_Img[1]->isVisible = false;

			break;
		case 4:
			pokeListPick5_Img[1]->isVisible = false;

			break;
		case 5:
			pokeListPick6_Img[1]->isVisible = false;

			break;
		case 6:
			pokeListPickC_Img[1]->isVisible = false;

			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
	for (int i = 0; i < pokeListSize; i++)
	{
		float temp = (float)(pokeMenuPlayer->myPokemon[i]->hp) / pokeMenuPlayer->myPokemon[i]->maxHP;
		//cout << temp << endl;
		pokeListHpG_Img[i]->scale.x = pokeListHpG_Img[i]->imageSize.x * 5.0f * temp;
		pokeListHpY_Img[i]->scale.x = pokeListHpG_Img[i]->imageSize.x * 5.0f * temp;
		pokeListHpR_Img[i]->scale.x = pokeListHpG_Img[i]->imageSize.x * 5.0f * temp;

	}
	pokeListBack_Img->Update();
	outUseItem->Update();

	for (int i = 0; i < 3; i++)
	{
		pokeListPick1_Img[i]->Update();
		pokeListPick2_Img[i]->Update();
		pokeListPick3_Img[i]->Update();
		pokeListPick4_Img[i]->Update();
		pokeListPick5_Img[i]->Update();
		pokeListPick6_Img[i]->Update();
	}
	for (int i = 0; i < 2; i++)
	{
		pokeListPickC_Img[i]->Update();
	}
	for (int i = 0; i < 6; i++)
	{
		pokeListHpG_Img[i]->Update();
		pokeListHpY_Img[i]->Update();
		pokeListHpR_Img[i]->Update();
	}
	for (int i = 0; i < pokeListSize; i++)
	{
		pokeList[i]->pokeAni->Update();
	}
	for (int i = 0; i < 6; i++)
	{
		pokeListDie[i]->Update();
	}
	for (int i = 0; i < pokeListSize; i++)
	{
		if (pokeList[i]->hp > 0)
		{
			pokeList[i]->pokeAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			pokeList[i]->pokeDie = false;
		}
		else
		{
			pokeList[i]->pokeDie = true;
			pokeList[i]->pokeAni->ChangeAnim(ANIMSTATE::STOP, 0.1f);

		}
		
	}
}

void PokeMenu::LateUpdate()
{
}

void PokeMenu::Render()
{
	pokeListBack_Img->Render();

	switch (state)
	{
	case PokeMenuState::SEL:
		DWRITE->RenderText(L"포켓몬을  선택해  주십시오.", RECT{ 50 + 5, 675, 50 + 1200 + 5, 675 + 100 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"포켓몬을  선택해  주십시오.", RECT{ 50 + 5, 675 + 5, 50 + 1200 + 5, 675 + 100 + 5 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"포켓몬을  선택해  주십시오.", RECT{ 50, 675 + 5, 50 + 1200, 675 + 100 + 5 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"포켓몬을  선택해  주십시오.", RECT{ 50, 675, 50 + 1200, 675 + 100 }, 60.0F,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
		switch (pokeListSize)
		{
		case 1:
			switch (selPokeList)
			{
			case 0:
				pokeListPick1_Img[0]->Render();
				break;
			default:
				pokeListPick1_Img[1]->Render();
				break;
			}
			break;
		case 2:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			break;
		case 3:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			break;
		case 4:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			
			break;
		case 5:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			break;

		case 6:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			pokeListPick6_Img[1]->Render();
			
			break;
		default:
			break;
		}
		pokeListPickC_Img[1]->Render();
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[0]->Render();
			break;
		case 1:
			pokeListPick2_Img[0]->Render();
			break;
		case 2:
			pokeListPick3_Img[0]->Render();
			break;
		case 3:
			pokeListPick4_Img[0]->Render();
			break;
		case 4:
			pokeListPick5_Img[0]->Render();
			break;
		case 5:
			pokeListPick6_Img[0]->Render();
			break;
		case 6:
			pokeListPickC_Img[0]->Render();
			break;
		default:
			break;
		}
		
		break;
	case PokeMenuState::MENU:
		break;
	case PokeMenuState::CHANGE_SEL:
		DWRITE->RenderText(L"어디로  이동할까?", RECT{ 50 + 5, 675, 50 + 1200 + 5, 675 + 100 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"어디로  이동할까?", RECT{ 50 + 5, 675 + 5, 50 + 1200 + 5, 675 + 100 + 5 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"어디로  이동할까?", RECT{ 50, 675 + 5, 50 + 1200, 675 + 100 + 5 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"어디로  이동할까?", RECT{ 50, 675, 50 + 1200, 675 + 100 }, 60.0F,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
		switch (pokeListSize)
		{
		case 1:
			switch (selPokeList)
			{
			case 0:
				pokeListPick1_Img[0]->Render();
				break;
			default:
				pokeListPick1_Img[1]->Render();
				break;
			}
			break;
		case 2:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			break;
		case 3:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			break;
		case 4:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();

			break;
		case 5:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			break;
		case 6:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			pokeListPick6_Img[1]->Render();

			break;
		default:
			break;
		}
		pokeListPickC_Img[1]->Render();
		switch (selChangePokeList)
		{
		case 0:
			pokeListPick1_Img[2]->Render();
			break;
		case 1:
			pokeListPick2_Img[2]->Render();
			break;
		case 2:
			pokeListPick3_Img[2]->Render();
			break;
		case 3:
			pokeListPick4_Img[2]->Render();
			break;
		case 4:
			pokeListPick5_Img[2]->Render();
			break;
		case 5:
			pokeListPick6_Img[2]->Render();
			break;
		default:
			break;
		}
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[0]->Render();
			break;
		case 1:
			pokeListPick2_Img[0]->Render();
			break;
		case 2:
			pokeListPick3_Img[0]->Render();
			break;
		case 3:
			pokeListPick4_Img[0]->Render();
			break;
		case 4:
			pokeListPick5_Img[0]->Render();
			break;
		case 5:
			pokeListPick6_Img[0]->Render();
			break;
		case 6:
			pokeListPickC_Img[0]->Render();
			break;
		default:
			break;
		}
		break;
	case PokeMenuState::BATTEL_SEL:
		
		if (selPokeList != 6)
		{
			DWRITE->RenderText(pokeMenuPlayer->myPokemon[selPokeList]->name + L"(으)로  바꾼다.", RECT{50 + 5, 675, 50 + 1200 + 5, 675 + 100}, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(pokeMenuPlayer->myPokemon[selPokeList]->name + L"(으)로  바꾼다.", RECT{ 50 + 5, 675 + 5, 50 + 1200 + 5, 675 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(pokeMenuPlayer->myPokemon[selPokeList]->name + L"(으)로  바꾼다.", RECT{ 50, 675 + 5, 50 + 1200, 675 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(pokeMenuPlayer->myPokemon[selPokeList]->name + L"(으)로  바꾼다.", RECT{ 50, 675, 50 + 1200, 675 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
		}
		else
		{
			DWRITE->RenderText(L"배틀로  돌아간다.", RECT{ 50 + 5, 675, 50 + 1200 + 5, 675 + 100 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"배틀로  돌아간다.", RECT{ 50 + 5, 675 + 5, 50 + 1200 + 5, 675 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"배틀로  돌아간다.", RECT{ 50, 675 + 5, 50 + 1200, 675 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"배틀로  돌아간다.", RECT{ 50, 675, 50 + 1200, 675 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
		}
		switch (pokeListSize)
		{
		case 1:
			switch (selPokeList)
			{
			case 0:
				pokeListPick1_Img[0]->Render();
				break;
			default:
				pokeListPick1_Img[1]->Render();
				break;
			}
			break;
		case 2:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			break;
		case 3:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			break;
		case 4:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();

			break;
		case 5:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			break;
		case 6:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			pokeListPick6_Img[1]->Render();

			break;
		default:
			break;
		}
		pokeListPickC_Img[1]->Render();
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[0]->Render();
			break;
		case 1:
			pokeListPick2_Img[0]->Render();
			break;
		case 2:
			pokeListPick3_Img[0]->Render();
			break;
		case 3:
			pokeListPick4_Img[0]->Render();
			break;
		case 4:
			pokeListPick5_Img[0]->Render();
			break;
		case 5:
			pokeListPick6_Img[0]->Render();
			break;
		case 6:
			pokeListPickC_Img[0]->Render();
			break;
		default:
			break;
		}
		break;
	case PokeMenuState::BATTEL_LOSE_SEL:
		if (selPokeList != 6)
		{
			DWRITE->RenderText(pokeMenuPlayer->myPokemon[selPokeList]->name + L"(으)로  바꾼다.", RECT{ 50 + 5, 675, 50 + 1200 + 5, 675 + 100 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(pokeMenuPlayer->myPokemon[selPokeList]->name + L"(으)로  바꾼다.", RECT{ 50 + 5, 675 + 5, 50 + 1200 + 5, 675 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(pokeMenuPlayer->myPokemon[selPokeList]->name + L"(으)로  바꾼다.", RECT{ 50, 675 + 5, 50 + 1200, 675 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(pokeMenuPlayer->myPokemon[selPokeList]->name + L"(으)로  바꾼다.", RECT{ 50, 675, 50 + 1200, 675 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
		}
		else
		{
			DWRITE->RenderText(L"선택할  수  없다.", RECT{ 50 + 5, 675, 50 + 1200 + 5, 675 + 100 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"선택할  수  없다.", RECT{ 50 + 5, 675 + 5, 50 + 1200 + 5, 675 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"선택할  수  없다.", RECT{ 50, 675 + 5, 50 + 1200, 675 + 100 + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(L"선택할  수  없다.", RECT{ 50, 675, 50 + 1200, 675 + 100 }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
		}
		switch (pokeListSize)
		{
		case 1:
			switch (selPokeList)
			{
			case 0:
				pokeListPick1_Img[0]->Render();
				break;
			default:
				pokeListPick1_Img[1]->Render();
				break;
			}
			break;
		case 2:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			break;
		case 3:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			break;
		case 4:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();

			break;
		case 5:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			break;
		case 6:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			pokeListPick6_Img[1]->Render();

			break;
		default:
			break;
		}
		pokeListPickC_Img[1]->Render();
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[0]->Render();
			break;
		case 1:
			pokeListPick2_Img[0]->Render();
			break;
		case 2:
			pokeListPick3_Img[0]->Render();
			break;
		case 3:
			pokeListPick4_Img[0]->Render();
			break;
		case 4:
			pokeListPick5_Img[0]->Render();
			break;
		case 5:
			pokeListPick6_Img[0]->Render();
			break;
		case 6:
			pokeListPickC_Img[0]->Render();
			break;
		default:
			break;
		}
		break;
	case PokeMenuState::BAG_ITEM:
		DWRITE->RenderText(L"누구에게 사용할까요?", RECT{ 50 + 5, 675, 50 + 1200 + 5, 675 + 100 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"누구에게 사용할까요?", RECT{ 50 + 5, 675 + 5, 50 + 1200 + 5, 675 + 100 + 5 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"누구에게 사용할까요?", RECT{ 50, 675 + 5, 50 + 1200, 675 + 100 + 5 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"누구에게 사용할까요?", RECT{ 50, 675, 50 + 1200, 675 + 100 }, 60.0F,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
		switch (pokeListSize)
		{
		case 1:
			switch (selPokeList)
			{
			case 0:
				pokeListPick1_Img[0]->Render();
				break;
			default:
				pokeListPick1_Img[1]->Render();
				break;
			}
			break;
		case 2:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			break;
		case 3:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			break;
		case 4:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();

			break;
		case 5:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			break;
		case 6:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			pokeListPick6_Img[1]->Render();

			break;

		default:
			break;
		}
		pokeListPickC_Img[1]->Render();
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[0]->Render();
			break;
		case 1:
			pokeListPick2_Img[0]->Render();
			break;
		case 2:
			pokeListPick3_Img[0]->Render();
			break;
		case 3:
			pokeListPick4_Img[0]->Render();
			break;
		case 4:
			pokeListPick5_Img[0]->Render();
			break;
		case 5:
			pokeListPick6_Img[0]->Render();
			break;
		case 6:
			pokeListPickC_Img[0]->Render();
			break;
		default:
			break;
		}
		break;
	case PokeMenuState::USE_BAG_ITEM:
		switch (pokeListSize)
		{
		case 1:
			switch (selPokeList)
			{
			case 0:
				pokeListPick1_Img[0]->Render();
				break;
			default:
				pokeListPick1_Img[1]->Render();
				break;
			}
			break;
		case 2:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			break;
		case 3:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			break;
		case 4:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();

			break;
		case 5:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			break;
		case 6:
			pokeListPick1_Img[1]->Render();
			pokeListPick2_Img[1]->Render();
			pokeListPick3_Img[1]->Render();
			pokeListPick4_Img[1]->Render();
			pokeListPick5_Img[1]->Render();
			pokeListPick6_Img[1]->Render();

			break;

		default:
			break;
		}
		pokeListPickC_Img[1]->Render();
		switch (selPokeList)
		{
		case 0:
			pokeListPick1_Img[0]->Render();
			break;
		case 1:
			pokeListPick2_Img[0]->Render();
			break;
		case 2:
			pokeListPick3_Img[0]->Render();
			break;
		case 3:
			pokeListPick4_Img[0]->Render();
			break;
		case 4:
			pokeListPick5_Img[0]->Render();
			break;
		case 5:
			pokeListPick6_Img[0]->Render();
			break;
		case 6:
			pokeListPickC_Img[0]->Render();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	switch (pokeListSize)
	{
	case 6:
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[5]->name, RECT{ 640 + 5, 535, 640 + 1200 + 5, 535 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[5]->name, RECT{ 640 + 5, 535 + 5, 640 + 1200 + 5, 535 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[5]->name, RECT{ 640, 535 + 5, 640 + 1200, 535 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[5]->name, RECT{ 640 + 5, 535 + 2, 640 + 1200 + 5, 535 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[5]->name, RECT{ 640 + 2, 535, 640 + 1200 + 2, 535 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[5]->name, RECT{ 640 + 2, 535 + 5, 640 + 1200 + 2, 535 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[5]->name, RECT{ 640, 535 + 2, 640 + 1200, 535 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[5]->name, RECT{ 640, 535, 640 + 1200, 535 + 100 }, 38.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		tempW = to_wstring(pokeMenuPlayer->myPokemon[5]->lv);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 577, 690 + 1200 + 5, 577 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 577 + 5, 690 + 1200 + 5, 577 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 577 + 5, 690 + 1200, 577 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 577 + 2, 690 + 1200 + 5, 577 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 2, 577, 690 + 1200 + 2, 577 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 2, 577 + 5, 690 + 1200 + 2, 577 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 577 + 2, 690 + 1200, 577 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 577, 690 + 1200, 577 + 100 }, 50.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);

		
	case 5:
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[4]->name, RECT{ 640 + 5, 415, 640 + 1200 + 5, 415 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[4]->name, RECT{ 640 + 5, 415 + 5, 640 + 1200 + 5, 415 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[4]->name, RECT{ 640, 415 + 5, 640 + 1200, 415 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[4]->name, RECT{ 640 + 5, 415 + 2, 640 + 1200 + 5, 415 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[4]->name, RECT{ 640 + 2, 415, 640 + 1200 + 2, 415 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[4]->name, RECT{ 640 + 2, 415 + 5, 640 + 1200 + 2, 415 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[4]->name, RECT{ 640, 415 + 2, 640 + 1200, 415 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[4]->name, RECT{ 640, 415, 640 + 1200, 415 + 100 }, 38.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		tempW = to_wstring(pokeMenuPlayer->myPokemon[4]->lv);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 457, 690 + 1200 + 5, 457 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 457 + 5, 690 + 1200 + 5, 457 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 457 + 5, 690 + 1200, 457 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 457 + 2, 690 + 1200 + 5, 457 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 2, 457, 690 + 1200 + 2, 457 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 2, 457 + 5, 690 + 1200 + 2, 457 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 457 + 2, 690 + 1200, 457 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 457, 690 + 1200, 457 + 100 }, 50.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		
	case 4:
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[3]->name, RECT{ 640 + 5, 295, 640 + 1200 + 5, 295 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[3]->name, RECT{ 640 + 5, 295 + 5, 640 + 1200 + 5, 295 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[3]->name, RECT{ 640, 295 + 5, 640 + 1200, 295 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[3]->name, RECT{ 640 + 5, 295 + 2, 640 + 1200 + 5, 295 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[3]->name, RECT{ 640 + 2, 295, 640 + 1200 + 2, 295 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[3]->name, RECT{ 640 + 2, 295 + 5, 640 + 1200 + 2, 295 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[3]->name, RECT{ 640, 295 + 2, 640 + 1200, 295 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[3]->name, RECT{ 640, 295, 640 + 1200, 295 + 100 }, 38.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		tempW = to_wstring(pokeMenuPlayer->myPokemon[3]->lv);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 337, 690 + 1200 + 5, 337 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 337 + 5, 690 + 1200 + 5, 337 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 337 + 5, 690 + 1200, 337 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 337 + 2, 690 + 1200 + 5, 337 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 2, 337, 690 + 1200 + 2, 337 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 2, 337 + 5, 690 + 1200 + 2, 337 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 337 + 2, 690 + 1200, 337 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 337, 690 + 1200, 337 + 100 }, 50.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
	case 3:
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[2]->name, RECT{ 640 + 5, 175, 640 + 1200 + 5, 175 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[2]->name, RECT{ 640 + 5, 175 + 5, 640 + 1200 + 5, 175 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[2]->name, RECT{ 640, 175 + 5, 640 + 1200, 175 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[2]->name, RECT{ 640 + 5, 175 + 2, 640 + 1200 + 5, 175 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[2]->name, RECT{ 640 + 2, 175, 640 + 1200 + 2, 175 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[2]->name, RECT{ 640 + 2, 175 + 5, 640 + 1200 + 2, 175 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[2]->name, RECT{ 640, 175 + 2, 640 + 1200, 175 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[2]->name, RECT{ 640, 175, 640 + 1200, 175 + 100 }, 38.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		tempW = to_wstring(pokeMenuPlayer->myPokemon[2]->lv);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 217, 690 + 1200 + 5, 217 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 217 + 5, 690 + 1200 + 5, 217 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 217 + 5, 690 + 1200, 217 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 217 + 2, 690 + 1200 + 5, 217 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 2, 217, 690 + 1200 + 2, 217 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 2, 217 + 5, 690 + 1200 + 2, 217 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 217 + 2, 690 + 1200, 217 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 217, 690 + 1200, 217 + 100 }, 50.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
	case 2:
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[1]->name, RECT{ 640 + 5, 55, 640 + 1200 + 5, 55 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[1]->name, RECT{ 640 + 5, 55 + 5, 640 + 1200 + 5, 55 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[1]->name, RECT{ 640, 55 + 5, 640 + 1200, 55 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[1]->name, RECT{ 640 + 5, 55 + 2, 640 + 1200 + 5, 55 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[1]->name, RECT{ 640 + 2, 55, 640 + 1200 + 2, 55 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[1]->name, RECT{ 640 + 2, 55 + 5, 640 + 1200 + 2, 55 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[1]->name, RECT{ 640, 55 + 2, 640 + 1200, 55 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[1]->name, RECT{ 640, 55, 640 + 1200, 55 + 100 }, 38.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		tempW = to_wstring(pokeMenuPlayer->myPokemon[1]->lv);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 97, 690 + 1200 + 5, 97 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 97 + 5, 690 + 1200 + 5, 97 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 97 + 5, 690 + 1200, 97 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 5, 97 + 2, 690 + 1200 + 5, 97 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 2, 97, 690 + 1200 + 2, 97 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690 + 2, 97 + 5, 690 + 1200 + 2, 97 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 97 + 2, 690 + 1200, 97 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 690, 97, 690 + 1200, 97 + 100 }, 50.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
	case 1:
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[0]->name, RECT{ 200 + 5, 165, 200 + 1200 + 5, 165 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[0]->name, RECT{ 200 + 5, 165 + 5, 200 + 1200 + 5, 165 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[0]->name, RECT{ 200, 165 + 5, 200 + 1200, 165 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[0]->name, RECT{ 200 + 5, 165 + 2, 200 + 1200 + 5, 165 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[0]->name, RECT{ 200 + 2, 165, 200 + 1200 + 2, 165 + 100 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[0]->name, RECT{ 200 + 2, 165 + 5, 200 + 1200 + 2, 165 + 100 + 5 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[0]->name, RECT{ 200, 165 + 2, 200 + 1200, 165 + 100 + 2 }, 38.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(pokeMenuPlayer->myPokemon[0]->name, RECT{ 200, 165, 200 + 1200, 165 + 100 }, 38.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		tempW = to_wstring(pokeMenuPlayer->myPokemon[0]->lv);
		DWRITE->RenderText(tempW, RECT{ 250 + 5, 217, 250 + 1200 + 5, 217 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 250 + 5, 217 + 5, 250 + 1200 + 5, 217 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 250, 217 + 5, 250 + 1200, 217 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 250 + 5, 217 + 2, 250 + 1200 + 5, 217 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 250 + 2, 217, 250 + 1200 + 2, 217 + 100 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 250 + 2, 217 + 5, 250 + 1200 + 2, 217 + 100 + 5 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 250, 217 + 2, 250 + 1200, 217 + 100 + 2 }, 50.0f,
			L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		DWRITE->RenderText(tempW, RECT{ 250, 217, 250 + 1200, 217 + 100 }, 50.0f,
			L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		break;
	default:
		break;
	}

	for (int i = 0; i < pokeListSize; i++)
	{
		if (i == 0)
		{
			//tempW2 = to_wstring(pokeMenuPlayer->myPokemon[i]->hp);
			tempW = to_wstring(pokeMenuPlayer->myPokemon[i]->maxHP);
			DWRITE->RenderText(tempW, RECT{ 336 + 5, 311, 336 + 1200 + 5, 311 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 336 + 5, 311 + 5, 336 + 1200 + 5, 311 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 336, 311 + 5, 336 + 1200, 311 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 336 + 5, 311 + 2, 336 + 1200 + 5, 311 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 336 + 2, 311, 336 + 1200 + 2, 311 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 336 + 2, 311 + 5, 336 + 1200 + 2, 311 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 336, 311 + 2, 336 + 1200, 311 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 336, 311, 336 + 1200, 311 + 100 }, 38.0f,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			tempW = to_wstring(pokeMenuPlayer->myPokemon[i]->hp);
			DWRITE->RenderText(tempW, RECT{ 230 + 5, 311, 230 + 1200 + 5, 311 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 230 + 5, 311 + 5, 230 + 1200 + 5, 311 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 230, 311 + 5, 230 + 1200, 311 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 230 + 5, 311 + 2, 230 + 1200 + 5, 311 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 230 + 2, 311, 230 + 1200 + 2, 311 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 230 + 2, 311 + 5, 230 + 1200 + 2, 311 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 230, 311 + 2, 230 + 1200, 311 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 230, 311, 230 + 1200, 311 + 100 }, 38.0f,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		}
		else if (i == 1)
		{
			tempW = to_wstring(pokeMenuPlayer->myPokemon[i]->maxHP);
			DWRITE->RenderText(tempW, RECT{ 1096 + 5, 111, 1096 + 1200 + 5, 111 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096 + 5, 111 + 5, 1096 + 1200 + 5, 111 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096, 111 + 5, 1096 + 1200, 111 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096 + 5, 111 + 2, 1096 + 1200 + 5, 111 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096 + 2, 111, 1096 + 1200 + 2, 111 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096 + 2, 111 + 5, 1096 + 1200 + 2, 111 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096, 111 + 2, 1096 + 1200, 111 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096, 111, 1096 + 1200, 111 + 100 }, 38.0f,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			tempW = to_wstring(pokeMenuPlayer->myPokemon[i]->hp);
			DWRITE->RenderText(tempW, RECT{ 990 + 5, 111, 990 + 1200 + 5, 111 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990 + 5, 111 + 5, 990 + 1200 + 5, 111 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990, 111 + 5, 990 + 1200, 111 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990 + 5, 111 + 2, 990 + 1200 + 5, 111 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990 + 2, 111, 990 + 1200 + 2, 111 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990 + 2, 111 + 5, 990 + 1200 + 2, 111 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990, 111 + 2, 990 + 1200, 111 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990, 111, 990 + 1200, 111 + 100 }, 38.0f,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		}
		else
		{
			tempW = to_wstring(pokeMenuPlayer->myPokemon[i]->maxHP);
			DWRITE->RenderText(tempW, RECT{ 1096 + 5, 111 + (i - 1) * 120, 1096 + 1200 + 5, 111 + (i - 1) * 120 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096 + 5, 111 + (i - 1) * 120 + 5, 1096 + 1200 + 5, 111 + (i - 1) * 120 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096, 111 + (i - 1) * 120 + 5, 1096 + 1200, 111 * (i - 1) + 120 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096 + 5, 111 + (i - 1) * 120 + 2, 1096 + 1200 + 5, 111 + (i - 1) * 120 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096 + 2, 111 + (i - 1) * 120, 1096 + 1200 + 2, 111 + (i - 1) * 120 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096 + 2, 111 + (i - 1) * 120 + 5, 1096 + 1200 + 2, 111 + (i - 1) * 120 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096, 111 + (i - 1) * 120 + 2, 1096 + 1200, 111 + (i - 1) * 120 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 1096, 111 + (i - 1) * 120, 1096 + 1200, 111 + (i - 1) * 120 + 100 }, 38.0f,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			tempW = to_wstring(pokeMenuPlayer->myPokemon[i]->hp);
			DWRITE->RenderText(tempW, RECT{ 990 + 5, 111 + (i - 1) * 120, 990 + 1200 + 5, 111 + (i - 1) * 120 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990 + 5, 111 + (i - 1) * 120 + 5, 990 + 1200 + 5, 111 + (i - 1) * 120 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990, 111 + (i - 1) * 120 + 5, 990 + 1200, 111 + (i - 1) * 120 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990 + 5, 111 + (i - 1) * 120 + 2, 990 + 1200 + 5, 111 + (i - 1) * 120 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990 + 2, 111 + (i - 1) * 120, 990 + 1200 + 2, 111 + (i - 1) * 120 + 100 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990 + 2, 111 + (i - 1) * 120 + 5, 990 + 1200 + 2, 111 + (i - 1) * 120 + 100 + 5 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990, 111 + (i - 1) * 120 + 2, 990 + 1200, 111 + (i - 1) * 120 + 100 + 2 }, 38.0f,
				L"Galmuri11", Color(112.0f / 255.0f, 112.0f / 255.0f, 112.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
			DWRITE->RenderText(tempW, RECT{ 990, 111 + (i - 1) * 120, 990 + 1200, 111 + (i - 1) * 120 + 100 }, 38.0f,
				L"Galmuri11", Color(1.0f, 1.0f, 1.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL);
		}
	}

	for (int i = 0; i < pokeListSize; i++)
	{
		pokeList[i]->pokeAni->Render();

	}
	for (int i = 0; i < pokeListSize; i++)
	{
		if ((float)(pokeMenuPlayer->myPokemon[i]->hp) / pokeMenuPlayer->myPokemon[i]->maxHP > 0.5f)
		{
			pokeListHpG_Img[i]->Render();
		}
		else if ((float)(pokeMenuPlayer->myPokemon[i]->hp) / pokeMenuPlayer->myPokemon[i]->maxHP > 0.1f)
		{
			pokeListHpY_Img[i]->Render();
		}
		else
		{
			pokeListHpR_Img[i]->Render();
		}
	}
	for (int i = 0; i < pokeListSize; i++)
	{
		if (pokeList[i]->pokeDie == true)
		{
			pokeListDie[i]->Render();
		}
	}
	if (state == PokeMenuState::USE_BAG_ITEM && pokemonToBag == true)
	{
		{
			long leftR = 270;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 60.0f;
			wstring wordR = L"상처약을    \n" + pokeMenuPlayer->myPokemon[selPokeList]->name + L"에게  사용했다.";
			DWRITE->RenderText(wordR, RECT{ 50 + 5, topR, 50 + 1200 + 5, botR }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(wordR, RECT{ 50 + 5, topR + 5, 50 + 1200 + 5, botR + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(wordR, RECT{ 50, topR + 5, 50 + 1200, botR + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(wordR, RECT{ 50, topR, 50 + 1200, botR }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
		}
		outUseItem->Render();
		{
			long leftR = 270;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 60.0f;
			wstring wordR = L"상처약을    \n" + pokeMenuPlayer->myPokemon[selPokeList]->name + L"에게  사용했다.";
			DWRITE->RenderText(wordR, RECT{ 50 + 5, topR, 50 + 1200 + 5, botR }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(wordR, RECT{ 50 + 5, topR + 5, 50 + 1200 + 5, botR + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(wordR, RECT{ 50, topR + 5, 50 + 1200, botR + 5 }, 60.0F,
				L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(wordR, RECT{ 50, topR, 50 + 1200, botR }, 60.0F,
				L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
		}
	}
	else if (state == PokeMenuState::USE_BAG_ITEM)
	{
		DWRITE->RenderText(L"누구에게 사용할까요?", RECT{ 50 + 5, 675, 50 + 1200 + 5, 675 + 100 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"누구에게 사용할까요?", RECT{ 50 + 5, 675 + 5, 50 + 1200 + 5, 675 + 100 + 5 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"누구에게 사용할까요?", RECT{ 50, 675 + 5, 50 + 1200, 675 + 100 + 5 }, 60.0F,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
		DWRITE->RenderText(L"누구에게 사용할까요?", RECT{ 50, 675, 50 + 1200, 675 + 100 }, 60.0F,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f));
	}
}

void PokeMenu::SetPokeMenu(Player* _player, int _myPokeSize)
{
	pokeListSize = _myPokeSize;
	pokeMenuPlayer = _player;
	for (int i = 0; i < pokeListSize; i++)
	{
		pokeList[i] = pokeMenuPlayer->myPokemon[i];
	}
	for (int i = 0; i < 6; i++)
	{
		if (pokeList[i] != 0)
		{
			switch (i)
			{
			case 0:
				pokeList[i]->pokeAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
				pokeList[i]->pokeAni->SetWorldPos(Vector2(-475.0f, 190.0f));
				break;
			case 1:
				pokeList[i]->pokeAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
				pokeList[i]->pokeAni->SetWorldPos(Vector2(-35.0f, 295.0f));
				break;
			case 2:
				pokeList[i]->pokeAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
				pokeList[i]->pokeAni->SetWorldPos(Vector2(-35.0f, 175.0f));
				break;
			case 3:
				pokeList[i]->pokeAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
				pokeList[i]->pokeAni->SetWorldPos(Vector2(-35.0f, 55.0f));
				break;
			case 4:
				pokeList[i]->pokeAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
				pokeList[i]->pokeAni->SetWorldPos(Vector2(-35.0f, -65.0f));
				break;
			case 5:
				pokeList[i]->pokeAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
				pokeList[i]->pokeAni->SetWorldPos(Vector2(-35.0f, -185.0f));
				break;
			default:
				break;
			}
		}
		
	}
}

void PokeMenu::ContrlPokeMenu()
{
	if (state != PokeMenuState::USE_BAG_ITEM)
	{
		if (INPUT->KeyDown(VK_UP))
		{
			if (selPokeList > 0)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				switch (pokeListSize)
				{
				case 1:
					selPokeList = 0;
					break;
				case 2:
					if (selPokeList == 6)
					{
						selPokeList = 1;
					}
					else
					{
						selPokeList--;
					}
					break;
				case 3:
					if (selPokeList == 6)
					{
						selPokeList = 2;
					}
					else
					{
						selPokeList--;
					}
					break;
				case 4:
					if (selPokeList == 6)
					{
						selPokeList = 3;
					}
					else
					{
						selPokeList--;
					}
					break;
				case 5:
					if (selPokeList == 6)
					{
						selPokeList = 4;
					}
					else
					{
						selPokeList--;
					}
					break;
				case 6:
					selPokeList--;
					break;
				default:
					break;
				}
			}
			else if (selPokeList == 0)
			{
				selPokeList = 6;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
			}
		}
		else if (INPUT->KeyDown(VK_DOWN))
		{
			if (selPokeList < 6)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				switch (pokeListSize)
				{
				case 1:
					selPokeList = 6;
					break;
				case 2:
					if (selPokeList == pokeListSize - 1)
					{
						selPokeList = 6;
					}
					else
					{
						selPokeList++;
					}
					break;
				case 3:
					if (selPokeList == pokeListSize - 1)
					{
						selPokeList = 6;
					}
					else
					{
						selPokeList++;
					}
					break;
				case 4:
					if (selPokeList == pokeListSize - 1)
					{
						selPokeList = 6;
					}
					else
					{
						selPokeList++;
					}
					break;
				case 5:
					if (selPokeList == pokeListSize - 1)
					{
						selPokeList = 6;
					}
					else
					{
						selPokeList++;
					}
					break;
				case 6:
					selPokeList++;
					break;
				default:
					break;
				}
			}
			else if (selPokeList == 6)
			{
				selPokeList = 0;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
			}
		}
		else if (INPUT->KeyDown(VK_LEFT) && selPokeList != 6 && selPokeList != 0)
		{
			lastSelPokeList = selPokeList;
			selPokeList = 0;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");

		}
		else if (INPUT->KeyDown(VK_RIGHT) && selPokeList == 0)
		{
			if (pokeListSize > 1)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				selPokeList = lastSelPokeList;
			}
		}
		
		switch (state)
		{
		case PokeMenuState::SEL:
			if (INPUT->KeyDown('Z') && selPokeList != 6 && state == PokeMenuState::SEL)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				state = PokeMenuState::CHANGE_SEL;
				selChangePokeList = selPokeList;
			}
			break;
		case PokeMenuState::CHANGE_SEL:
			if (INPUT->KeyDown('Z') && selPokeList == 6 && state == PokeMenuState::CHANGE_SEL)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				state = PokeMenuState::SEL;
			}
			else if (INPUT->KeyDown('Z') && selPokeList != 6 && state == PokeMenuState::CHANGE_SEL)
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				Pokemon* temp = pokeMenuPlayer->myPokemon[selPokeList];
				pokeMenuPlayer->myPokemon[selPokeList] = pokeMenuPlayer->myPokemon[selChangePokeList];
				pokeMenuPlayer->myPokemon[selChangePokeList] = temp;
				SetPokeMenu(pokeMenuPlayer, pokeMenuPlayer->myPokemon.size());
				state = PokeMenuState::SEL;
			}
			break;
		case PokeMenuState::BATTEL_SEL:
			break;
		case PokeMenuState::BATTEL_LOSE_SEL:
			break;
		case PokeMenuState::BAG_ITEM:
			if (INPUT->KeyDown('Z'))
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				if (selPokeList != 6 && pokeMenuPlayer->myPokemon[selPokeList]->hp < pokeMenuPlayer->myPokemon[selPokeList]->maxHP)
				{
					SOUND->Stop("POTION");
					SOUND->Play("POTION");
					state = PokeMenuState::USE_BAG_ITEM;
					pokeMenuPlayer->myPokemon[selPokeList]->changeHp += 50;//상처약 피 회복 50;
					if (pokeMenuPlayer->myPokemon[selPokeList]->changeHp > pokeMenuPlayer->myPokemon[selPokeList]->maxHP)
					{
						pokeMenuPlayer->myPokemon[selPokeList]->changeHp = pokeMenuPlayer->myPokemon[selPokeList]->maxHP;
					}
					changeHp = (pokeMenuPlayer->myPokemon[selPokeList]->changeHp - pokeMenuPlayer->myPokemon[selPokeList]->hp);
					changeHpFloat = (float)(pokeMenuPlayer->myPokemon[selPokeList]->hp);
					
				}
			}
			break;
		case PokeMenuState::USE_BAG_ITEM:

			break;
		default:
			break;
		}

	}
	
	
}

void PokeMenu::SetState(PokeMenuState _state)
{
	state = _state;
}
