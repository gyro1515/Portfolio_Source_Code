#include "Framework.h"
#include "BaseScene1.h"
#include "Scenes/GameScene/LoadingScene_2.h"

BaseScene1::BaseScene1()
{
	LandScapeManager::Get()->Update();
	{
		initCount++;
		Device::Get()->Clear();
		Environment::Get()->PostSet();
		loadingBar->SetAmount((float)initCount / maxInitCount);
		loadingBar->Update();
		loadingScene->PostRender();
		Device::Get()->Present();
	}
	//Let there be light
	SetLights();
	// 소리 추가
	//SetSound();

	// 그림자용 모델
	SetShadowModel();
	{
		initCount++;
		Device::Get()->Clear();
		Environment::Get()->PostSet();
		loadingBar->SetAmount((float)initCount / maxInitCount);
		loadingBar->Update();
		loadingScene->PostRender();
		Device::Get()->Present();
	}
	FOR(2)
	{
		blendState[i] = new BlendState();
		rasterizer[i] = new RasterizerState();
	}
	blendState[1]->Alpha(true);
	blendState[1]->AlphaToCoverage(true);
	rasterizer[1]->CullMode(D3D11_CULL_NONE);

	shadow = new Shadow(L"BaseScene", 16384, 16384); // 픽셀 깨짐 최소화
	//shadow = new Shadow();


	//terrainF = new Terrain();
	{
		initCount++;
		Device::Get()->Clear();
		Environment::Get()->PostSet();
		loadingBar->SetAmount((float)initCount / maxInitCount);
		loadingBar->Update();
		loadingScene->PostRender();
		Device::Get()->Present();
	}
	skyBox = new SkyBox(L"Textures/Landscape/testsky.dds");
	//
	water = new Water(L"Textures/Landscape/Wave.dds", 500, 500);
	water->Pos() = { 250.0f,11.0f, 250.0f };
	water->Scale() *= 4.0f;
	water->GetRefraction()->GetWaterBuffer()->Get().waveSpeed = 0.01f;
	water->GetRefraction()->GetWaterBuffer()->Get().waveScale = 0.2f;
	{
		initCount++;
		Device::Get()->Clear();
		Environment::Get()->PostSet();
		loadingBar->SetAmount((float)initCount / maxInitCount);
		loadingBar->Update();
		loadingScene->PostRender();
		Device::Get()->Present();
	}

	//PalsManager::Get()->SetTarget(PlayerManager::Get()->GetPlayer());
	PalsManager::Get()->SetPlayer(PlayerManager::Get()->GetPlayer());
	PalsManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());
	{
		initCount++;
		Device::Get()->Clear();
		Environment::Get()->PostSet();
		loadingBar->SetAmount((float)initCount / maxInitCount);
		loadingBar->Update();
		loadingScene->PostRender();
		Device::Get()->Present();
	}
	//PlayerPalsManager::Get()->SetTarget(); // 플레이어에서 플레이어가 타겟한 타겟으로 설정하기
	PlayerPalsManager::Get()->SetPlayer(PlayerManager::Get()->GetPlayer());
	PlayerPalsManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());
	{
		initCount++;
		Device::Get()->Clear();
		Environment::Get()->PostSet();
		loadingBar->SetAmount((float)initCount / maxInitCount);
		loadingBar->Update();
		loadingScene->PostRender();
		Device::Get()->Present();
	}
	PalSpearManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());
	{
		initCount++;
		Device::Get()->Clear();
		Environment::Get()->PostSet();
		loadingBar->SetAmount((float)initCount / maxInitCount);
		loadingBar->Update();
		loadingScene->PostRender();
		Device::Get()->Present();
	}
	FieldPalSkillManager::Get(); // 생성자용
	MyPalSkillManager::Get();	 // 생성자용
	AStarManager::Get();
	LandScapeManager::Get();
	{
		initCount++;
		Device::Get()->Clear();
		Environment::Get()->PostSet();
		loadingBar->SetAmount((float)initCount / maxInitCount);
		loadingBar->Update();
		loadingScene->PostRender();
		Device::Get()->Present();
	}
	//palBoxUi = new PalBoxUi();

	// 스킬 테스트
	//testSkill = new Tornado();

	// UI테스트
	//testUI = new FieldUI();

	// 모델 테스트
	//mam = new ModelAnimator("Mammoth");
	//mam->ReadClip("Idle");
	//mam->ReadClip("Walk");
	//mam->ReadClip("Run");
	//mam->ReadClip("Attack");
	//
	//mam->Scale() *= 0.01f;

	//paTest = new ParticleSystem("TextData/Particles/PalSpear.fx");


	// 소리 실행
	//SOUND->Play("BGM_Battle");
	//SOUND->Play("BGM",0.2f);

}

BaseScene1::~BaseScene1()
{
	//delete player;
	//delete terrain;
	//delete terrainF;
	delete shadow;
	delete water;
	delete ModelP;
	delete ModelM;
	delete ModelD;

	PalsManager::Get()->Delete();
	PlayerPalsManager::Get()->Delete();
	LandScapeManager::Get()->Delete();
	PlayerManager::Get()->Delete();
	UiManager::Get()->Delete();
	StructureManager::Get()->Delete();
	//delete palBoxUi;
}

void BaseScene1::Update()
{
	LightBuffer::Light* light1 = Environment::Get()->GetLight(1);
	light1->pos = CAM->GlobalPos();

	// 사운드 업데이트
	SOUND->Update();

	StructureManager::Get()->Update();
	UiManager::Get()->Update(); // UI 관련 업데이트가 먼저



	water->Update();
	//player->Jump(terrainF->GetHeight(player->GlobalPos()));
	//if (KEY_DOWN(VK_SPACE)) player->GlobalPos().y = terrain->GetHeight(player->GlobalPos());
	//player->Update();
	ItemManager::Get()->Update();
	PlayerManager::Get()->Update();



	PalsManager::Get()->Update();
	PlayerPalsManager::Get()->Update();
	LandScapeManager::Get()->Update();
	//PlayerManager::Get()->Update();
	FieldPalSkillManager::Get()->Update(); // 벡터 터짐 방지
	MyPalSkillManager::Get()->Update();	   //  -> 맨 마지막에 업데이트

	// UI테스트
	//testUI->Update();
	//mam->Pos() = CAM->ScreenToWorld(mousePos);
	//mam->Update();

	// 
	// 파티클 테스트
	//if (KEY_DOWN('Z'))
	//{
	//	Ray ray;
	//	ray.dir = CAM->Forward();
	//	ray.pos = CAM->GlobalPos();
	//	Vector3 hitP;
	//
	//	if (PalsManager::Get()->IsCollision(ray, hitP)) //마우스 커서가 구체에 닿으면
	//	{
	//		paTest->Play(hitP); //거기서 파티클 재생
	//	}
	//}
	//paTest->Update();
}

void BaseScene1::PreRender()
{
	//PalSpearManager::Get()->PreRender();

	water->SetRefraction();

	// 일렁인 쪽 클래스의 쿼드에 일렁임의 결과 출력
	skyBox->Render();

	// 반사
	water->SetReflection();
	// 반사 출력
	skyBox->Render();

	StructureManager::Get()->PreRender();
	//LandScapeManager::Get()->PreRender();

	// 그림자
	
	//shadow->SetRenderTargetPos(PlayerManager::Get()->GetPlayer()->GlobalPos());
	shadow->SetRenderTargetPos(CAM->GlobalPos());
	LightBuffer::Light* light = Environment::Get()->GetLight(0);
	if (light->active == 0) return;
	PlayerManager::Get()->GetPlayer()->ShadowRender();
	RenderShadowModel();
}

void BaseScene1::Render()
{

	skyBox->Render();
	//terrain->Render();
	water->Render();
	
	//mam->Render();

	StructureManager::Get()->Render();
	PlayerManager::Get()->Render();

	PalsManager::Get()->Render();
	PlayerPalsManager::Get()->Render();

	//PalSpearManager::Get()->Render();
	// 그림자 + 터레인
	shadow->SetRender();
	LandScapeManager::Get()->Render();
	AStarManager::Get()->Render();

	//UiManager::Get()->Render(); 랜더 안함


	//paTest->Render();

}

void BaseScene1::PostRender()
{
	//PalSpearManager::Get()->PostRender();


	PalsManager::Get()->PostRender();
	PlayerPalsManager::Get()->PostRender();
	StructureManager::Get()->PostRender();

	// UI테스트
	//testUI->PostRender();
	UiManager::Get()->PostRender();

}

void BaseScene1::GUIRender()
{
	//PlayerManager::Get()->GUIRender();

	//water->GUIRender();
	//terrain->GUIRender();
	//palBox->GUIRender();

	//PalsManager::Get()->GUIRender();
	//PlayerPalsManager::Get()->GUIRender();

	//PlayerManager::Get()->GUIRender();
	//PalSpearManager::Get()->GUIRender();

	// UI테스트
	//testUI->GUIRender();
	//UiManager::Get()->GuiRender();
	//LandScapeManager::Get()->GUIRender();
	//ImGui::Text("Wold X : %f", CAM->ScreenToWorld(mousePos).x);
	//ImGui::Text("Wold Y : %f", CAM->ScreenToWorld(mousePos).y);
	//ImGui::Text("Wold Z : %f", CAM->ScreenToWorld(mousePos).z);
	//mam->GUIRender();
}

void BaseScene1::PlayBGM()
{
	SOUND->Play("BGM", 0.2f);
}

void BaseScene1::SetLights()
{
	LightBuffer::Light* light0 = Environment::Get()->GetLight(0);
	light0->type = 0;
	light0->range = 3000.0f;
	//light0->color = { 55.0f / 255.0f,55.0f / 255.0f,55.0f / 255.0f ,0 };
	light0->color = { 1.0f,1.0f,1.0f ,0 };
	//light0->direction = { 0,-1,0 };
	light0->direction = { 0.5f,-1.0f,0.5f };
	light0->pos = { 0.01f,300.0f,0.01f };

	//LightBuffer::Light* light1 = Environment::Get()->AddLight();
	//light1->type = 1;
	//light1->range = 3000.0f;
	//light1->color = { 150.0f / 255.0f,150.0f / 255.0f,150.0f / 255.0f ,0 };
	//light1->direction = { 0,-1,0 };
	//
	//
	LightBuffer::Light* light1 = Environment::Get()->AddLight();
	light1->type = 1;
	light1->range = 0.01f;
	light1->active = 1;
	
	LightBuffer::Light* light2 = Environment::Get()->AddLight();
	light2->type = 1;
	light2->range = 0.01f;
	light2->active = 1;
}

void BaseScene1::SetShadowModel()
{
	ModelP = new ModelAnimatorInstancing("PenGuin");
	ModelP->ReadClip("Idle");
	ModelP->ReadClip("Walk");
	ModelP->ReadClip("Run");
	ModelP->ReadClip("Attack");
	ModelP->ReadClip("Damage");
	ModelP->ReadClip("Work");
	ModelP->SetTag("Penguin");
	ModelP->SetShader(L"Light/DepthMap.hlsl");
	ModelP->Scale() *= 0.01f;
	ModelP->Render();

	ModelM = new ModelAnimatorInstancing("Mammoth");
	ModelM->ReadClip("Idle");
	ModelM->ReadClip("Walk");
	ModelM->ReadClip("Run");
	ModelM->ReadClip("Attack");
	ModelM->ReadClip("Damage");
	ModelM->SetTag("mammoth");
	ModelM->SetShader(L"Light/DepthMap.hlsl");
	ModelM->Scale() *= 0.01f;
	ModelM->Update();
	ModelM->Render();

	ModelD = new ModelAnimatorInstancing("DarkWolf");
	ModelD->ReadClip("Idle");
	ModelD->ReadClip("Walk");
	ModelD->ReadClip("Run");
	ModelD->ReadClip("Attack");
	ModelD->ReadClip("Damage");
	ModelD->SetTag("wolf");
	ModelD->SetShader(L"Light/DepthMap.hlsl");
	ModelD->Scale() *= 0.01f;
	ModelD->Render();


	treeS1 = new Model("Tree1");
	treeS1->Scale() *= 0.01f;
	//treeS1->SetShader(L"Light/DepthMap.hlsl");
	treeS1->SetShader(L"Basic/Texture.hlsl");

	treeS2 = new Model("Tree2");
	//treeS2 = new ModelInstancing("Tree2");
	treeS2->Scale() *= 0.01f;
	//treeS2->SetShader(L"Light/DepthMap.hlsl");
	treeS2->SetShader(L"Basic/Texture.hlsl");

	//rockS  = new Model("Rock1");
	//rockS->Scale() *= 0.01f;
	//rockS->SetShader(L"Light/DepthMap.hlsl");

	//grassS1= new Model("Grass1");
	////grassS1->Scale() *= 0.01f;
	////grassS1->Scale() *= 5.0f;
	//grassS1->SetShader(L"Light/DepthMap.hlsl");
	//
	//grassS2= new Model("Grass2");
	////grassS2->Scale() *= 0.01f;
	////grassS2->Scale().z *= 3.0f;
	//grassS2->SetShader(L"Light/DepthMap.hlsl");


}


void BaseScene1::RenderShadowModel()
{
	// 필드 팰즈 매니저
	for (int i = 0; i < PalsManager::Get()->GetPalsInstancing().size(); i++)
	{
		int tmpIII = 0;
		for (Transform* pal : PalsManager::Get()->GetPalsInstancing()[i]->GetInstancingTransform())
		{
			if (pal->Active())
			{
				if (PalsManager::Get()->GetPalsInstancing()[i]->ModelName == "PenGuin")
				{
					ModelP->Pos() = pal->Pos();
					ModelP->Rot() = pal->Rot();
					//ModelP->GetFrameB()->Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelP->GetFrameB().Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB().Get().motions[tmpIII].cur;

					ModelP->UpdateWorld();
					ModelP->Render();
				}
				else if (PalsManager::Get()->GetPalsInstancing()[i]->ModelName == "Mammoth")
				{
					ModelM->Pos() = pal->Pos();
					ModelM->Rot() = pal->Rot();
					//ModelM->GetFrameB()->Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelM->GetFrameB().Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB().Get().motions[tmpIII].cur;

					ModelM->UpdateWorld();
					ModelM->Render();
				}
				else if (PalsManager::Get()->GetPalsInstancing()[i]->ModelName == "DarkWolf")
				{
					ModelD->Pos() = pal->Pos();
					ModelD->Rot() = pal->Rot();
					//ModelD->GetFrameB()->Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelD->GetFrameB().Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB().Get().motions[tmpIII].cur;

					ModelD->UpdateWorld();
					ModelD->Render();
				}
			}
			tmpIII++;
		}
	}

	// 플레이어 팰즈 매니저
	for (auto iter = PlayerPalsManager::Get()->GetPalsMAI().begin(); iter != PlayerPalsManager::Get()->GetPalsMAI().end(); iter++)
	{
		int tmpIII = 0;
		for (Transform* pal : iter->second->GetInstancingTransform())
		{
			if (pal->Active())
			{
				if (iter->second->ModelName == "PenGuin")
				{
					ModelP->Pos() = pal->Pos();
					ModelP->Rot() = pal->Rot();
					//ModelP->GetFrameB()->Get().cur = iter->second->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelP->GetFrameB().Get().cur = iter->second->GetFrameIB().Get().motions[tmpIII].cur;

					ModelP->UpdateWorld();
					ModelP->Render();
				}
				else if (iter->second->ModelName == "Mammoth")
				{
					ModelM->Pos() = pal->Pos();
					ModelM->Rot() = pal->Rot();
					//ModelM->GetFrameB()->Get().cur = iter->second->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelM->GetFrameB().Get().cur = iter->second->GetFrameIB().Get().motions[tmpIII].cur;

					ModelM->UpdateWorld();
					ModelM->Render();
				}
				else if (iter->second->ModelName == "DarkWolf")
				{
					ModelD->Pos() = pal->Pos();
					ModelD->Rot() = pal->Rot();
					//ModelD->GetFrameB()->Get().cur = iter->second->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelD->GetFrameB().Get().cur = iter->second->GetFrameIB().Get().motions[tmpIII].cur;

					ModelD->UpdateWorld();
					ModelD->Render();
				}
			}
			tmpIII++;
		}
	}
	blendState[1]->SetState();
	rasterizer[1]->SetState();
	/*
	// 나무1
	for (Transform* tree1 : LandScapeManager::Get()->GetTree1Instancing()->GetTransforms())
	{
		if (tree1->Active())
		{
			treeS1->Pos() = tree1->GlobalPos();
			treeS1->Rot() = tree1->Rot();
			treeS1->UpdateWorld();
			treeS1->Render();
		}
		
	}
	*/
	// 나무2
	for (Transform* tree2 : LandScapeManager::Get()->GetTree2Instancing()->GetTransforms())
	{
		if (tree2->Active() && Distance(PlayerManager::Get()->GetPlayer()->GlobalPos(), tree2->GlobalPos()) < 100.0f)
			//&& CAM->ContainPoint(tree2->GlobalPos(), 7.0f // 넣으면 어색해짐, 프레임은 잘 나옴
		{
			treeS2->Pos() = tree2->GlobalPos();
			treeS2->Rot() = tree2->Rot();
			treeS2->UpdateWorld();
			treeS2->Render();
		}
		
	}
	// 250311 테스트:
	//LandScapeManager::Get()->GetTree2Instancing()->Render();

	// 돌
	//for (Transform* rock : LandScapeManager::Get()->GetRock1Instancing()->GetTransforms())
	//{
	//	rockS->Pos() = rock->GlobalPos();
	//	rockS->Rot() = rock->Rot();
	//	rockS->UpdateWorld();
	//	rockS->Render();
	//}
	// 풀1
	//for (Transform* grass1 : LandScapeManager::Get()->GetGrass1Instancing()->GetTransforms())
	//{
	//	grassS1->Pos() = grass1->GlobalPos();
	//	grassS1->Rot() = grass1->Rot();
	//	grassS1->Scale() = grass1->Scale();
	//	grassS1->UpdateWorld();
	//	grassS1->Render();
	//}
	//// 풀2
	//for (Transform* grass2 : LandScapeManager::Get()->GetGrass2Instancing()->GetTransforms())
	//{
	//	grassS2->Pos() = grass2->GlobalPos();
	//	grassS2->Rot() = grass2->Rot();
	//	grassS2->Scale() = grass2->Scale();
	//	grassS2->UpdateWorld();
	//	grassS2->Render();
	//}
	blendState[0]->SetState();
	rasterizer[0]->SetState();
}

//void BaseScene1::SetSound()
//{
//	// action
//	//SOUND->Add("Walk", "Sounds/Action/WalkGrass.wav", false, true);
//	//SOUND->Add("Run", "Sounds/Action/RunGrass.wav", false, true);
//	SOUND->Add("Walk", "Sounds/Action/WalkGrass.wav");
//	SOUND->Add("Run", "Sounds/Action/RunGrass.wav");
//	SOUND->Add("JumpLanding", "Sounds/Action/JumpLanding.wav");
//	SOUND->Add("Work", "Sounds/Action/WorkBenchWork.wav", false, true);
//	SOUND->Add("Build", "Sounds/Action/Hammer.wav", false, true);
//	SOUND->Add("Gun_Aim", "Sounds/Action/Gun_Aim.wav");
//	SOUND->Add("Gun_Draw", "Sounds/Action/Gun_Draw.wav");
//	SOUND->Add("Gun_Fire", "Sounds/Action/Gun_Fire.wav");
//	SOUND->Add("Gun_Reload", "Sounds/Action/Gun_Reload.wav");
//	SOUND->Add("Pick_Attack", "Sounds/Action/Pick_Attack.wav",false,true);
//	//SOUND->Add("Pickdraw", "Sounds/Action/pickdraw.wav");
//	SOUND->Add("Pick_HitWood", "Sounds/Action/pickhit1.wav");
//	//SOUND->Add("Pickhit2", "Sounds/Action/pickhit2.wav");
//	SOUND->Add("Pick_HitRock", "Sounds/Action/pickhit3.wav");
//
//
//	// skill
//	SOUND->Add("IceMissileHit_1", "Sounds/Skill/IceMissileHit_1.wav");
//	SOUND->Add("IceMissileHit_2", "Sounds/Skill/IceMissileHit_2.wav");
//	SOUND->Add("IceMissileShoot", "Sounds/Skill/IceMissileShoot.wav");
//	SOUND->Add("WindCutterHit", "Sounds/pal/WindCutterHit.mp3");
//	//SOUND->Add("WindCutterHit", "Sounds/Skill/WindCutterHit.wav");
//	SOUND->Add("WindCutterShoot", "Sounds/Skill/WindCutterShoot.wav");
//	SOUND->Add("EarthQuakeHit", "Sounds/pal/EarthQuakeHit.wav");
//	SOUND->Add("EarthQuaSet", "Sounds/pal/earthQuaSet.wav");
//
//	// ui
//	//SOUND->Add("BGM_Battle", "Sounds/UI/BGM_Battle.wav", true, true);
//	SOUND->Add("BGM", "Sounds/UI/BGM.wav", true, true);
//	SOUND->Add("LevelUp", "Sounds/UI/LevelUp.wav");
//	SOUND->Add("UI_1", "Sounds/UI/UI_1.wav");
//	SOUND->Add("UI_2", "Sounds/UI/UI_2.wav");
//	SOUND->Add("UI_3", "Sounds/UI/UI_3.wav");
//
//	
//	// sphere
//	SOUND->Add("Sphere_Flash", "Sounds/pal/Sphere_Flash.wav",false, false, true);
//	SOUND->Add("Sphere_Hit", "Sounds/pal/Sphere_Hit.wav", false, false, true);
//	SOUND->Add("Sphere_Shake", "Sounds/pal/Sphere_Shake.wav", false, false, true);
//	SOUND->Add("Sphere_Success", "Sounds/pal/Sphere_Success.wav", false, false, true);
//
//
//}
