#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	ATTACK->Init();

	player = new Player();
	player->SetWorldPos(Vector2(-200.f, -20.f));
	playerHpBar = new HpBar(player);
	playerHpBar->SetBarScale(Vector2(300.f, 20.f));
	playerHpBar->SetWorldPos(Vector2(CAM->position.x - 150.f, CAM->position.y - 300.f));

	will = new Will();
	will->player = player;
	willHpBar = new HpBar(will);
	willHpBar->SetBarScale(Vector2(app.GetWidth() - 50.f, 20.f));
	willHpBar->SetWorldPos(Vector2(CAM->position.x - app.GetHalfWidth() + 25.f, CAM->position.y + app.GetHalfHeight() - 10.f));
	player->snailObject.enemy = will;
	will->ball.player = player;

	phase2 = new Phase2();

	for (auto& _beholderBody : beholderBodys)
	{
		_beholderBody = new BeholderBody();
		_beholderBody->player = player;

		for (auto& _bullet : _beholderBody->_bulletPool)
		{
			_bullet.player = player;
		}
	}
	beholderBodys[0]->SetWorldPos(Vector2(-300.f, 200.f));
	beholderBodys[1]->SetWorldPos(Vector2(300.f, 200.f));

	for (auto& _spiderLeg : spiderLegs)
	{
		_spiderLeg = new SpiderLeg();
		_spiderLeg->player = player;
	}
	spiderLegs[0]->SetWorldPos(Vector2(400.f, -52.f));
	spiderLegs[1]->SetWorldPos(Vector2(-200.f, -52.f));

	for (auto& _spiderLegMirror : spiderLegMirrors)
	{
		_spiderLegMirror = new SpiderLegMirror();
		_spiderLegMirror->player = player;
	}
	spiderLegMirrors[0]->SetWorldPos(Vector2(200.f, -52.f));
	spiderLegMirrors[1]->SetWorldPos(Vector2(-400.f, -52.f));

	for (auto& _spiderLeg : spiderLegs2)
	{
		_spiderLeg = new SpiderLeg();
		_spiderLeg->player = player;
		_spiderLeg->_playRate += 2.f;
	}
	spiderLegs2[0]->SetWorldPos(Vector2(100.f, -52.f));
	spiderLegs2[1]->SetWorldPos(Vector2(-300.f, -52.f));

	for (auto& _spiderLegMirror : spiderLegMirrors2)
	{
		_spiderLegMirror = new SpiderLegMirror();
		_spiderLegMirror->player = player;
		_spiderLegMirror->_playRate += 2.f;
	}
	spiderLegMirrors2[0]->SetWorldPos(Vector2(300.f, -52.f));
	spiderLegMirrors2[1]->SetWorldPos(Vector2(-100.f, -52.f));

	for (auto& _spiderLeg : spiderLegs3)
	{
		_spiderLeg = new SpiderLeg();
		_spiderLeg->player = player;
		_spiderLeg->_playRate += 4.f;
	}
	spiderLegs3[0]->SetWorldPos(Vector2(0.f, -52.f));
	spiderLegs3[1]->SetWorldPos(Vector2(400.f, -52.f));
	spiderLegs3[2]->SetWorldPos(Vector2(-400.f, -52.f));

	for (auto& _spiderLegMirror : spiderLegMirrors3)
	{
		_spiderLegMirror = new SpiderLegMirror();
		_spiderLegMirror->player = player;
		_spiderLegMirror->_playRate += 4.f;
	}
	spiderLegMirrors3[0]->SetWorldPos(Vector2(200.f, -52.f));
	spiderLegMirrors3[1]->SetWorldPos(Vector2(-200.f, -52.f));

	for (auto& _darkEnforcer : darkEnforcers)
	{
		_darkEnforcer = new DarkEnforcer();
		_darkEnforcer->player = player;
	}
	darkEnforcers[0]->SetWorldPos(Vector2(0.f, 200.f));
	darkEnforcers[1]->SetWorldPos(Vector2(-500.f, 200.f));
	darkEnforcers[2]->SetWorldPos(Vector2(500.f, 200.f));

	SOUND->AddSound("MirrorCage.mp3", "BGM", true);
	SOUND->AddSound("2phase.mp3", "Phase2");
	SOUND->AddSound("intro3.mp3", "Phase3");

	phase = 0;
	soundCount = 0;
}

void Main::Release()
{
	for (int i = 0; i < 31; i++)
	{
		SafeDelete(img[i]);
	}
}

void Main::Update()
{
	//ImGui::ColorEdit3("Color", (float*)&pet.color, ImGuiColorEditFlags_PickerHueBar);
	////%d 서식문자 int , %f 실수 , %.3f
	ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());
	if (ImGui::SliderFloat("MasterVolume", &app.soundScale,
		0.0f, 5.0f))
	{
		SOUND->SetMasterVolume();
	}
	//cout << phase2->animation->GetAnimCount() << endl;
	switch (phase)
	{
	case 0:
		phase2->Update();
		SOUND->Play("Phase2");

		break;
	case 1:
		player->Update();
		will->Update();
		SOUND->Play("BGM");
		for (auto& _beholderBody : beholderBodys)
		{
			_beholderBody->Update();
		}

		for (auto& _spiderLeg : spiderLegs)
		{
			_spiderLeg->Update();
		}

		for (auto& _spiderLegMirror : spiderLegMirrors)
		{
			_spiderLegMirror->Update();
		}

		for (auto& _spiderLeg : spiderLegs2)
		{
			_spiderLeg->Update();
		}

		for (auto& _spiderLegMirror : spiderLegMirrors2)
		{
			_spiderLegMirror->Update();
		}

		for (auto& _spiderLeg : spiderLegs3)
		{
			_spiderLeg->Update();
		}

		for (auto& _spiderLegMirror : spiderLegMirrors3)
		{
			_spiderLegMirror->Update();
		}

		for (auto& _darkEnforcer : darkEnforcers)
		{
			_darkEnforcer->Update();
		}
		break;
	case 2:
		SOUND->Stop("BGM");
		if (soundCount == 0)
		{
			SOUND->Play("Phase3");
			soundCount++;
		}
		phase2->Update();
		break;
	}
}

//모든 객체가 움직이고 난 후
void Main::LateUpdate()
{
	switch (phase)
	{
	case 0:
		//if (phase2->animation->GetAnimCount() > 112)
		//{
		//	phase2->animState = AnimState::Phase3;
		//	phase = 1;
		//}
		//phase2->Update();

		if (phase2->animation->GetAnimCount() == 112)
		{
			phase2->SetState(AnimState::Phase3);
			phase = 1;
		}
		phase2->Update();
		break;
	case 1:
		ATTACK->Update();
		EFFECT->Update();

		playerHpBar->Update();
		willHpBar->Update();
		if (willHpBar->GetCurrentHp() <= 0.0f)
		{
			will->SetState(AnimState::Die1);
			if (will->animation->IsOver())
			{
				phase = 2;
			}
			will->Update();
		}
		break;
	case 2:
		//phase2->Update();
		break;
	}
}

void Main::Render()
{
	switch (phase)
	{
	case 0:
		phase2->Render();
		break;
	case 1:
		will->Render();
		player->Render();
		for (auto& _beholderBody : beholderBodys)
		{
			_beholderBody->Render();
		}

		for (auto& _spiderLeg : spiderLegs)
		{
			_spiderLeg->Render();
		}

		for (auto& _spiderLegMirror : spiderLegMirrors)
		{
			_spiderLegMirror->Render();
		}

		for (auto& _spiderLeg : spiderLegs2)
		{
			_spiderLeg->Render();
		}

		for (auto& _spiderLegMirror : spiderLegMirrors2)
		{
			_spiderLegMirror->Render();
		}

		for (auto& _spiderLeg : spiderLegs3)
		{
			_spiderLeg->Render();
		}

		for (auto& _spiderLegMirror : spiderLegMirrors3)
		{
			_spiderLegMirror->Render();
		}

		for (auto& _darkEnforcer : darkEnforcers)
		{
			_darkEnforcer->Render();
		}

		ATTACK->Render();
		EFFECT->Render();

		playerHpBar->Render();
		willHpBar->Render();
		break;
	case 2:
		phase2->Render();
		break;
	}
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game1");
	app.SetInstance(instance);
	app.InitWidthHeight(1400.0f, 800.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}