#include "stdafx.h"

BagMenu::BagMenu()
{
	bagImg = new ObImage(L"Bag Screens1.png");
	bagImg->scale = bagImg->imageSize * 5;
	bagImg->pivot = OFFSET_LB;
	bagImg->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	bagSelImg = new ObImage(L"PokeFullMenu2.png");
	bagSelImg->scale = bagSelImg->imageSize * 5;
	bagSelImg->pivot = OFFSET_LB;
	bagSelImg->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	bagMenuImg = new ObImage(L"Bag Screens4.png");
	bagMenuImg->scale = bagMenuImg->imageSize * 5;
	bagMenuImg->pivot = OFFSET_LB;
	bagMenuImg->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	bagMenuSelImg = new ObImage(L"PokeFullMenu2.png");
	bagMenuSelImg->scale = bagMenuSelImg->imageSize * 5;
	bagMenuSelImg->pivot = OFFSET_LB;
	bagMenuSelImg->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	closeImg = new ObImage(L"Bag Screens5.png");
	closeImg->scale = closeImg->imageSize * 5;
	closeImg->SetWorldPos(Vector2(-502.0f, -280.0f));

	bagPlayer = 0;
	itemList[0] = 0;
	itemList[1] = 0;
	usedItemName = L"";
	state = BagMenuState::SEL;

	sel = 0;
	menuSel = 0;

	//키 유예시간
	keyOn = false;
	keyOnTime = 0.0f;
	//이미지 테스트
	imgX = 0;
	imgY = 0;
	
}

BagMenu::~BagMenu()
{
}

void BagMenu::Update()
{
	if (keyOn)
	{
		switch (state)
		{
		case BagMenuState::SEL:
			Sel();
			break;
		case BagMenuState::MENU:
			Menu();
			break;
		case BagMenuState::BATTEL_SEL:
			Battle_Sel();
			break;
		case BagMenuState::BATTEL_MENU:
			Battle_Menu();
			break;
		default:
			break;
		}
	}
	else
	{
		if (TIMER->GetTick(keyOnTime, 0.1f))
		{
			keyOn = true;
		}
	}
	
	switch (sel)
	{
	case 0:
		bagSelImg->SetWorldPos(Vector2(-153.0f, 294.0f));
		break;
	case 1:
		bagSelImg->SetWorldPos(Vector2(-153.0f, 214.0f));
		break;
	case 2:
		bagSelImg->SetWorldPos(Vector2(-153.0f, 134.0f));
		break;
	case 3:
		bagSelImg->SetWorldPos(Vector2(-153.0f, 54.0f));
		break;
	case 4:
		bagSelImg->SetWorldPos(Vector2(-153.0f, -26.0f));
		break;
	case 5:
		bagSelImg->SetWorldPos(Vector2(-153.0f, -106.0f));
		break;
	default:
		break;
	}
	switch (menuSel)
	{
	case 0:
		bagMenuSelImg->SetWorldPos(Vector2(290.0f, -265.0f));
		break;
	case 1:
		bagMenuSelImg->SetWorldPos(Vector2(290.0f, -345.0f));
		break;
	default:
		break;
	}
	if (sel < bagPlayer->myItem.size())
	{
		bagPlayer->myItem[sel]->itemImg->Update();
	}
	bagImg->Update();
	bagSelImg->Update();
	bagMenuImg->Update();
	bagMenuSelImg->Update();
	closeImg->Update();
}

void BagMenu::LateUpdate()
{
}

void BagMenu::Render()
{
	{
		long leftR = 155;
		long topR = 35;
		long rightR = leftR + 1200;
		long botR = topR + 100;
		float sizeR = 60.0f;
		wstring wordR = L"가방";
		DWRITE->RenderText(wordR, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(wordR, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(wordR, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(wordR, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(wordR, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(wordR, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(wordR, RECT{ leftR, topR, rightR, botR }, sizeR,
			L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
	}
	switch (state)
	{
	case BagMenuState::SEL:
		bagImg->Render();
		bagSelImg->Render();

		{
			long leftR = 210;
			long topR = 560;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 57.0f;
			wstring word;
			if (sel < bagPlayer->myItem.size())
			{
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR, topR, rightR, botR }, sizeR,
					L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			}
			else
			{
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{leftR + 5, topR, rightR + 5,  botR}, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR, topR, rightR, botR }, sizeR,
					L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			}
		}
		break;
	case BagMenuState::MENU:
		bagImg->Render();
		bagMenuImg->Render();
		bagSelImg->Render();
		bagMenuSelImg->Render();
		{
			long leftR = 270;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 60.0f;
			wstring wordR = bagPlayer->myItem[sel]->name + L"\n어떻게 할까요?";
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
			leftR = 930;
			topR = 595;
			rightR = leftR + 1200;
			botR = topR + 100;
			sizeR = 60.0f;
			if (bagPlayer->myItem[sel]->name == L"상처약")
			{
				wordR = L"쓴다\n그만둠";
			}
			else
			{
				wordR = L"그만둠";
			}
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
		}
		
		break;
	case BagMenuState::BATTEL_SEL:
		bagImg->Render();
		bagSelImg->Render();
		{
			long leftR = 210;
			long topR = 560;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 57.0f;
			wstring word;
			if (sel < bagPlayer->myItem.size())
			{
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(bagPlayer->myItem[sel]->explanation, RECT{ leftR, topR, rightR, botR }, sizeR,
					L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			}
			else
			{
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR + 5, topR, rightR + 5,  botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR,
					L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
				DWRITE->RenderText(L"가방을  닫습니다.", RECT{ leftR, topR, rightR, botR }, sizeR,
					L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
			}
		}
		break;
	case BagMenuState::BATTEL_MENU:
		bagImg->Render();
		bagMenuImg->Render();
		bagSelImg->Render();
		bagMenuSelImg->Render();
		{
			long leftR = 270;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 60.0f;
			wstring wordR = bagPlayer->myItem[sel]->name + L"\n어떻게 할까요?";
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
			leftR = 930;
			topR = 595;
			rightR = leftR + 1200;
			botR = topR + 100;
			sizeR = 60.0f;
			wordR = L"쓴다\n그만둠";
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
		}
		break;
	default:
		break;
	}
	//글자
	{
		long leftR = 490;
		long topR = 35;
		long rightR = leftR + 1200;
		long botR = topR + 100;
		float sizeR = 60.0f;
		wstring wordR = L"";
		for (int i = 0; i < bagPlayer->myItem.size(); i++)
		{
			leftR = 490;
			topR = 35 + 80 * i;
			rightR = leftR + 1200;
			botR = topR + 100;
			wordR = bagPlayer->myItem[i]->name;
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
			wordR = to_wstring(bagPlayer->myItem[i]->num) + L"개";
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
		topR = 35 + 80 * bagPlayer->myItem.size();
		rightR = leftR + 1200;
		botR = topR + 100;
		DWRITE->RenderText(L"닫기", RECT{ leftR + 5, topR, rightR + 5,  botR }, 60.0f,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(L"닫기", RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(L"닫기", RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(L"닫기", RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(L"닫기", RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(L"닫기", RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(L"닫기", RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f,
			L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
		DWRITE->RenderText(L"닫기", RECT{ leftR, topR, rightR, botR }, 60.0f,
			L"Galmuri11", Color(96.0f / 255.0f, 96.0f / 255.0f, 96.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
	}
	if (sel < bagPlayer->myItem.size())
	{
		bagPlayer->myItem[sel]->itemImg->Render();
	}
	else
	{
		closeImg->Render();
	}


}

void BagMenu::Sel()
{
	if (INPUT->KeyDown(VK_UP))
	{
		if (sel > 0)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			sel--;
		}
	
	}
	else if (INPUT->KeyDown(VK_DOWN))
	{
		if (sel < bagPlayer->myItem.size())
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			sel++;
		}
	}
	else if (INPUT->KeyDown('Z'))
	{
		switch (sel)
		{
		case 0:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::MENU;
			break;
		case 1:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::MENU;
			break;
		case 2:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::MENU;
			break;
		case 3:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::MENU;
			break;
		case 4:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::MENU;
			break;
		case 5:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::MENU;
			break;
		default:
			break;
		}
	}
}

void BagMenu::Menu()
{
	usedItemName = L"";

	if (bagPlayer->myItem[sel]->name == L"상처약")
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
			if (menuSel < 1)
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
			case 0:
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				// 마을에서 상처회복 쓰기
				usedItemName = bagPlayer->myItem[sel]->name;
				//cout << "1" << endl;
				state = BagMenuState::SEL;
				menuSel = 0;
				break;
			case 1:
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				state = BagMenuState::SEL;
				menuSel = 0;
				break;
			default:
				break;
			}
			
		}
		else if (INPUT->KeyDown('X'))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::SEL;
			menuSel = 0;
		}
	}
	else
	{
		if (INPUT->KeyDown('Z'))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::SEL;
			menuSel = 0;
		}
		else if (INPUT->KeyDown('X'))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::SEL;
			menuSel = 0;
		}
	}
	
}

void BagMenu::Battle_Sel()
{
	if (INPUT->KeyDown(VK_UP))
	{
		if (sel > 0)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			sel--;
		}

	}
	else if (INPUT->KeyDown(VK_DOWN))
	{
		if (sel < bagPlayer->myItem.size())
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			sel++;
		}
	}
	else if (INPUT->KeyDown('Z'))
	{
		switch (sel)
		{
		case 0:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::BATTEL_MENU;
			break;
		case 1:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::BATTEL_MENU;
			break;
		case 2:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::BATTEL_MENU;
			break;
		case 3:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::BATTEL_MENU;
			break;
		case 4:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::BATTEL_MENU;
			break;
		case 5:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = BagMenuState::BATTEL_MENU;
			break;
		default:
			break;
		}
	}
}

void BagMenu::Battle_Menu()
{
	usedItemName = L"";
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
		if (menuSel < 1)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			menuSel++;
		}
	}
	else if (INPUT->KeyDown('Z'))
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		//배틀 중 아이템 사용
		if (menuSel == 0)
		{
			usedItemName = bagPlayer->myItem[sel]->name;
			state = BagMenuState::BATTEL_SEL;
			menuSel = 0;
		}
		else
		{
			state = BagMenuState::BATTEL_SEL;
			menuSel = 0;
		}
		
		

	}
	else if (INPUT->KeyDown('X'))
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		state = BagMenuState::BATTEL_SEL;
		menuSel = 0;

	}
}

void BagMenu::ContrlBagMenu()
{

	
	
}
