#include "Framework.h"
#include "WorkBench.h"

WorkBench::WorkBench()
{
	FOR(3)
	{
		blendState[i] = new BlendState();
	}

	blendState[1]->Alpha(true);
	blendState[1]->AlphaToCoverage(true);
	blendState[2]->Alpha(true);

	building = new Model("WorkBenchF");
	finished = new Model("WorkBench");
	cube = new Model("CubeModel");

	building->Rot().x = XM_PIDIV2;
	//finished->Rot().x = XM_PIDIV2;
	finished->SetParent(building);

	//Place();

	//light = Environment::Get()->GetLight(1);
	light = Environment::Get()->GetLight(2);
	light->type = 1;
	light->range = 0.01f;


	shadow = new FakeShadow();

	cube->Scale() *= 10;
	cube->Rot().y = XM_PIDIV4;

	range = new SphereCollider(5.0f);
	mouseHit = new SphereCollider(2.5f);

	produceBar = new ProgressBar(
		L"Textures/UI/gauge_bar.png",
		L"Textures/UI/hp_bar_BG.png"
	);
	WorkItem = nullptr;
	WorkImage = new Quad(Vector2(0.3, 0.3));
}

WorkBench::~WorkBench()
{
	FOR(2) delete blendState[i];

	delete building;
	delete finished;
	delete center;
	delete cube;
	delete shadow;
	delete light;
	delete produceBar;
	delete WorkItem;
	delete WorkImage;
}

void WorkBench::Update()
{
	//Place(PlayerManager::Get()->GetPlayer()->GetFrontPoint()->Pos().x, PlayerManager::Get()->GetPlayer()->GetFrontPoint()->Pos().y);

	cube->Pos().x = building->Pos().x;
	cube->Pos().z = building->Pos().z;
	cube->Pos().y = building->Pos().y + off2;

	range->Pos() = building->Pos();
	mouseHit->Pos() = building->Pos();


	light->pos = building->Pos() + off;


	if (Progressing && isPlaced)
	{
		off2 += 0.5f * DELTA;
		
	}
	
	

	if (KEY_PRESS('F') && PlayerManager::Get()->GetPlayer()->GetPlayerCol()->IsCollision(mouseHit)
		&& !Done && UiManager::Get()->buildWorkBench)
	{
		Progressing = true;
		if (!PlayerManager::Get()->GetPlayer()->isBuild) PlayerManager::Get()->GetPlayer()->isBuild = true;
	}
	else if(KEY_UP('F'))
	{
		Progressing = false;
		if (PlayerManager::Get()->GetPlayer()->isBuild) PlayerManager::Get()->GetPlayer()->isBuild = false;
		
	}

	if (off2 > 12.0f)
	{
		Done = true;
		if (PlayerManager::Get()->GetPlayer()->isBuild && UiManager::Get()->buildWorkBench) PlayerManager::Get()->GetPlayer()->isBuild = false;
		UiManager::Get()->buildWorkBench = false;
		
	}


	if (UiManager::Get()->buildWorkBench)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			isPlaced = true;
		}
	}
	//상호작용 함수
	Interaction();

	cube->UpdateWorld();
	building->UpdateWorld();
	finished->UpdateWorld();
	range->UpdateWorld();
	mouseHit->UpdateWorld();
}

void WorkBench::PreRender()
{
	if (!isPlaced) return;
	if (Done) return;

	shadow->SetRenderTarget(2);

	cube->SetShader(L"Light/DepthMap.hlsl");
	//cube->SetShader(L"Basic/Texture.hlsl");

	cube->Render();

}

void WorkBench::Render()
{
	WorkImage->SetRender();
	blendState[1]->SetState();
	if (WorkItem != nullptr)
	{
		WorkImage->Render();
	}
	blendState[0]->SetState();
	blendState[2]->SetState();

	if (!Done)
	{
		shadow->SetRender();
		building->SetShader(L"Light/Shadow.hlsl");
	}

	if (UiManager::Get()->buildWorkBench)
	{
		//shadow->SetRender();
		//building->SetShader(L"Light/Shadow.hlsl");
		building->Render();

	}

	if (Done)
	{
		finished->Render();
	}

	blendState[0]->SetState();

	range->Render();
	mouseHit->Render();
	
}

void WorkBench::PostRender()
{
	if (WorkItem != nullptr) produceBar->Render();
}

void WorkBench::GUIRender()
{
}

void WorkBench::Place(float x, float z)
{
	if (isPlaced) return;

	building->Pos() = { x,LandScapeManager::Get()->GetTerrain()->GetHeight({x, 0, z}), z };
}

void WorkBench::Interaction()
{
	if (PlayerManager::Get()->GetPlayer()->GetPlayerCol()->IsCollision(range) && Done)
	{
		Ray ray = CAM->ScreenPointToRay(mousePos);
		Contact contact;

		if (mouseHit->IsRayCollision(ray, &contact) && KEY_DOWN('F') && !UiManager::Get()->GetUiOn())
		{
			UiManager::Get()->WorkBenchUiOn = true;
		}

	}

	if (WorkItem != nullptr)
	{

		if (!CAM->ContainPoint(gaugePos) || abs((building->Pos() - PlayerManager::Get()->GetPlayer()->GlobalPos())
			.Length()) > 20)
		{
			WorkImage->SetActive(false);
			produceBar->SetActive(false);
		}
		else
		{
			WorkImage->SetActive(true);
			produceBar->SetActive(true);
		}

		WorkImage->GetMaterial()->SetDiffuseMap(WorkItem->icon);

		gaugePos = building->Pos() + Vector3(0, 1.2f, 0);
		WorkImage->Pos() = building->Pos() + Vector3(0, 1.4f, 0);

		produceBar->SetAmount(time / CompleteTime);
		produceBar->Pos() = CAM->WorldToScreen(gaugePos);
		produceBar->Scale() = { 1.0f,0.5f,0.3f };

		Vector3 tmp = WorkImage->GlobalPos() - CAM->GlobalPos();
		tmp = tmp.GetNormalized();
		WorkImage->Rot().y = atan2(tmp.x, tmp.z);
		WorkImage->Rot().x = asinf(-tmp.y);
		WorkImage->Update();
		produceBar->UpdateWorld();
		if (PlayerManager::Get()->GetPlayer()->GetPlayerCol()->IsCollision(mouseHit) && KEY_PRESS('Y'))
		{
			BarUpdate();
			PlayerManager::Get()->GetPlayer()->isWork = true;
		}
		else if ((KEY_UP('Y'))) PlayerManager::Get()->GetPlayer()->isWork = false;


	}
	else PlayerManager::Get()->GetPlayer()->isWork = false;


}

bool WorkBench::PalWorkCheck()
{
	if (isPlaced && !Done) return true;
	else	return false;
}

void WorkBench::SetItem(Item* item)
{
	if (WorkItem == nullptr)
	{
		time = 1;
		WorkItem = item;
		CompleteTime = WorkItem->MakeTime;
	}
}

void WorkBench::BarUpdate()
{
	if (time > CompleteTime)
	{
		produceBar->SetActive(false);

		time = 10;
		CompleteTime = 20;

		FOR(Count)
		{
			ItemManager::Get()->Mining(WorkItem);
		}
		WorkItem = nullptr;

		PlayerManager::Get()->GetPlayer()->isWork = false;
	}
	else
	{
		
		time += 10 * DELTA;
	}

}
