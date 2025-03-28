#include "Framework.h"

PalModeUi::PalModeUi()
{
	baseDonut = new Quad(donutSize);
	baseDonut->GetMaterial()->SetDiffuseMap(L"Textures/UI/DonutGlass50.png");
	baseDonut->Pos() = center;

	selectA = new ClickQuad(selectSize);
	selectA->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/UI/devilIcon1.png");
	selectA->GetQuad()->Pos() = center + Vector3(200.0f * cosf(XM_2PI * (11.0f / 12.0f)), 200.0f * sinf(XM_2PI * (11.0f / 12.0f)), 0.0f);

	selectP = new ClickQuad(selectSize);
	selectP->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/UI/angelIcon1.png");
	selectP->GetQuad()->Pos() = center + Vector3(200.0f * cosf(XM_2PI * (7.0f / 12.0f)), 200.0f * sinf(XM_2PI * (7.0f / 12.0f)), 0.0f);

	selectW = new ClickQuad(selectSize);
	selectW->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_monitoring_button_1.png");
	selectW->GetQuad()->Pos() = center + Vector3(200.0f * cosf(XM_2PI * (3.0f / 12.0f)), 200.0f * sinf(XM_2PI * (3.0f / 12.0f)), 0.0f);

	selectMiddle = new Quad(selectSize);
	selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	selectMiddle->Pos() = center + Vector3(0.0f * cosf(XM_2PI * (0.0f / 6.0f)), 0.0f * sinf(XM_2PI * (0.0f / 6.0f)), 0.0f);

	donutPiece = new Quad(donutSize);
	donutPiece->GetMaterial()->SetDiffuseMap(L"Textures/UI/DonutPiece.png");
	donutPiece->Pos() = center;
	donutPiece->SetActive(false);

}

PalModeUi::~PalModeUi()
{
	delete baseDonut;
	delete selectMiddle;
	delete donutPiece;

	delete selectA;
	delete selectP;
	delete selectW;
}

void PalModeUi::Update()
{
	SetTexture();

	if (selectA->MouseCollision())
	{
		if (!isPlayed)
		{
			isPlayed = true;
			SOUND->Stop("UI_2");
			SOUND->Play("UI_2", 0.7f);
		}
		pieceRot = XM_2PI * (11.0f / 12.0f);
		donutPiece->SetActive(true);
		if (KEY_DOWN(VK_LBUTTON) && UiManager::Get()->palModeUiOn)
		{
			SOUND->Stop("UI_1");
			SOUND->Play("UI_1");
			PlayerPalsManager::Get()->SetMode(PlayerPalsManager::MODE::AGGRESSIVE);
			UiManager::Get()->palModeUiOn = false;
			mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
		}
	}
	else if (selectP->MouseCollision())
	{
		if (!isPlayed)
		{
			isPlayed = true;
			SOUND->Stop("UI_2");
			SOUND->Play("UI_2", 0.7f);
		}
		pieceRot = XM_2PI * (7.0f / 12.0f);
		donutPiece->SetActive(true);
		if (KEY_DOWN(VK_LBUTTON) && UiManager::Get()->palModeUiOn)
		{
			SOUND->Stop("UI_1");
			SOUND->Play("UI_1");
			PlayerPalsManager::Get()->SetMode(PlayerPalsManager::MODE::PASSIVE);
			UiManager::Get()->palModeUiOn = false;
			mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };

		}

	}
	else if (selectW->MouseCollision())
	{
		if (!isPlayed)
		{
			isPlayed = true;
			SOUND->Stop("UI_2");
			SOUND->Play("UI_2", 0.7f);
		}
		pieceRot = XM_2PI * (3.0f / 12.0f);
		donutPiece->SetActive(true);
		if (KEY_DOWN(VK_LBUTTON) && UiManager::Get()->palModeUiOn)
		{
			SOUND->Stop("UI_1");
			SOUND->Play("UI_1");
			PlayerPalsManager::Get()->SetMode(PlayerPalsManager::MODE::WORK);
			UiManager::Get()->palModeUiOn = false;
			mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
		}
	}
	else
	{
		donutPiece->SetActive(false);
		isPlayed = false;
	}
	donutPiece->Rot().z = pieceRot;


	baseDonut->Update();
	selectA->Update();
	selectP->Update();
	selectW->Update();
	selectMiddle->Update();
	donutPiece->Update();

}

void PalModeUi::Render()
{
}

void PalModeUi::PostRender()
{
	baseDonut->Render();
	selectA->Render();
	selectP->Render();
	selectW->Render();
	donutPiece->Render();
	selectMiddle->Render();

}

void PalModeUi::GuiRender()
{

}

void PalModeUi::SetTexture()
{
	if (selectA->MouseCollision())
	{
		selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/UI/devilIcon1.png");
	}
	else if (selectP->MouseCollision())
	{
		selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/UI/angelIcon1.png");
	}
	else if (selectW->MouseCollision())
	{
		selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_monitoring_button_1.png");
	}
	else
	{
		selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	}

}
