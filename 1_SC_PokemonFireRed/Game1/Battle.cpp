#include "stdafx.h"

void Battle::Init()
{
	LIGHT->light.inColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	LIGHT->light.lights[0].radius = 1000.0f;
	LIGHT->light.select.x = 0.0f;


	CAM->position = Vector2(0.0f, 0.0f);

	battleGround[0] = new ObImage(L"Battle Backgrounds2-1.png");
	battleGround[0]->scale = battleGround[0]->imageSize * 5;
	battleGround[1] = new ObImage(L"Battle Backgrounds2-2.png");
	battleGround[1]->scale = battleGround[1]->imageSize * 5;
	battleGround[2] = new ObImage(L"Battle Backgrounds2-3.png");
	battleGround[2]->scale = battleGround[2]->imageSize * 5;

	battleHp[0] = new ObImage(L"HP Bars & In-battle Menu1.png");
	battleHp[0]->scale = battleHp[0]->imageSize * 5;
	battleHp[1] = new ObImage(L"HP Bars & In-battle Menu2.png");
	battleHp[1]->scale = battleHp[1]->imageSize * 5;

	battleHpBar[0] = new ObImage(L"HP Bars & In-battle Menu17.png");
	battleHpBar[0]->scale = battleHpBar[0]->imageSize * 5;
	battleHpBar[1] = new ObImage(L"HP Bars & In-battle Menu15.png");
	battleHpBar[1]->scale = battleHpBar[1]->imageSize * 5;
	battleHpBar[2] = new ObImage(L"HP Bars & In-battle Menu16.png");
	battleHpBar[2]->scale = battleHpBar[2]->imageSize * 5;
	battleHpBar[3] = new ObImage(L"HP Bars & In-battle Menu14.png");
	battleHpBar[3]->scale = battleHpBar[3]->imageSize * 5;
	battleHpBar[4] = new ObImage(L"HP Bars & In-battle Menu17.png");
	battleHpBar[4]->scale = battleHpBar[4]->imageSize * 5;
	battleHpBar[5] = new ObImage(L"HP Bars & In-battle Menu15.png");
	battleHpBar[5]->scale = battleHpBar[5]->imageSize * 5;
	battleHpBar[6] = new ObImage(L"HP Bars & In-battle Menu16.png");
	battleHpBar[6]->scale = battleHpBar[6]->imageSize * 5;
	battleHpBar[7] = new ObImage(L"HP Bars & In-battle Menu14.png");
	battleHpBar[7]->scale = battleHpBar[7]->imageSize * 5;
	battleHpBar[8] = new ObImage(L"HP Bars & In-battle Menu18.png");
	battleHpBar[8]->scale = battleHpBar[8]->imageSize * 5;

	battleUi[0] = new ObImage(L"HP Bars & In-battle Menu6.png");
	battleUi[0]->scale = battleUi[0]->imageSize * 5;
	battleUi[1] = new ObImage(L"HP Bars & In-battle Menu3.png");
	battleUi[1]->scale = battleUi[1]->imageSize * 5;
	battleUi[2] = new ObImage(L"HP Bars & In-battle Menu5.png");
	battleUi[2]->scale = battleUi[2]->imageSize * 5;
	battleUi[3] = new ObImage(L"HP Bars & In-battle Menu4.png");
	battleUi[3]->scale = battleUi[3]->imageSize * 5;

	for (int i = 0; i < 3; i++)
	{
		battleGround[i]->pivot = OFFSET_LB;
		//battleGround[i]->SetWorldPosX(-app.GetHalfWidth());
		battleGround[i]->SetWorldPosY(app.GetHalfHeight() - battleGround[i]->imageSize.y * 5);
	}
	battleGround[0]->SetWorldPosX(-app.GetHalfWidth());
	battleGround[1]->SetWorldPosX(-app.GetHalfWidth() - battleGround[1]->imageSize.x * 5);
	battleGround[2]->SetWorldPosX(app.GetHalfWidth());
	battleGround[2]->Update(); // 업데이트 미리 해야 씬전환하자마자 트레이너 중간에 안나타남 -> 업데이트가 값 세팅하고 그 다음에 이뤄지기 때문
	for (int i = 0; i < 3; i++)
	{
		battleGround[i]->Update();
	}
	for (int i = 0; i < 2; i++)
	{
		battleHp[i]->pivot = OFFSET_LB;
	}
	//battleHp[0]->SetWorldPosX(-app.GetHalfWidth() + 60);
	//battleHp[0]->SetWorldPosY(app.GetHalfHeight() - battleHp[0]->imageSize.y * 5 - 80);
	//battleHp[1]->SetWorldPosX(-app.GetHalfWidth() + 650);
	//battleHp[1]->SetWorldPosY(app.GetHalfHeight() - battleGround[0]->imageSize.y * 5);

	battleHp[0]->SetWorldPosX(-app.GetHalfWidth() - battleHp[0]->imageSize.x * 5);
	battleHp[0]->SetWorldPosY(app.GetHalfHeight() - battleHp[0]->imageSize.y * 5 - 80);
	battleHp[1]->SetWorldPosX(app.GetHalfWidth());
	battleHp[1]->SetWorldPosY(app.GetHalfHeight() - battleGround[0]->imageSize.y * 5);

	for (int i = 0; i < 9; i++)
	{
		battleHpBar[i]->pivot = OFFSET_LB;
		if (i <= 3)
		{
			//battleHpBar[i]->SetWorldPosX(-345.0f);
			battleHpBar[i]->SetWorldPosX(-345.0f - 60.0f - battleHp[0]->imageSize.x * 5);
			battleHpBar[i]->SetWorldPosY(220.0f);
			battleHpBar[i]->scale.x = 241.0f;
		}
		else if (i <= 7)
		{
			//battleHpBar[i]->SetWorldPosX(289.0f);
			battleHpBar[i]->SetWorldPosX(289.0f + 550.0f);
			battleHpBar[i]->SetWorldPosY(-75.0f);
			battleHpBar[i]->scale.x = 241.0f;
		}
		else if (i == 8)
		{
			//battleHpBar[i]->SetWorldPosX(210.0f);
			battleHpBar[i]->SetWorldPosX(210.0f + 550.0f);
			battleHpBar[i]->SetWorldPosY(-150.0f);
			battleHpBar[i]->scale.x = 320.0f;
		}
	}
	//battleHpBar[0]->scale.x = 241.0f;
	//battleHpBar[4]->scale.x = 241.0f;
	//battleHpBar[8]->scale.x = 320.0f;

	for (int i = 0; i < 4; i++)
	{
		battleUi[i]->pivot = OFFSET_LB;
		battleUi[i]->SetWorldPosX(-app.GetHalfWidth());
		battleUi[i]->SetWorldPosY(app.GetHalfHeight() - battleUi[i]->imageSize.y * 5 - battleGround[0]->imageSize.y * 5);
	}
	battleUi[1]->SetWorldPosX(app.GetHalfWidth() - battleUi[1]->imageSize.x * 5);
	battleUi[3]->SetWorldPosX(app.GetHalfWidth());


	


	playerImg = new ObImage(L"Pokemon_throw_man.png");
	playerImg->scale.x = playerImg->imageSize.x;
	playerImg->scale.y = playerImg->imageSize.y * 5;
	playerImg->maxFrame.x = 5;
	playerImg->pivot = OFFSET_LB;
	playerImg->SetLocalPosX(app.GetHalfWidth());
	playerImg->SetLocalPosY(app.GetHalfHeight() - battleGround[0]->imageSize.y * 5);

	ballAni = new ObImage(L"Pokemon_Item_MonsterBall2.png");
	ballAni->scale.x = ballAni->imageSize.x / 4 * 5;
	ballAni->scale.y = ballAni->imageSize.y * 5;
	ballAni->maxFrame.x = 4;
	ballAni->pivot = OFFSET_LB;
	ballAni->SetLocalPosX(-400.0f);
	ballAni->SetLocalPosY(20.0f);
	ballAni->isVisible = false;
	ballThrowTime = 0.0f;
	ballAniTime = 0.0f;
	ballGravi = -200.0f;
	ballOutScale = 0.1f;
	ballInScale = 1.0f;

	//씬으로 바꾸면서 필요없어짐, main 업데이트에서 Batte->Init()가 실행되기 때문에 메인에 있는 것들은 다시 초기화 x
	//playerPoke = nullptr;
	//enermyPoke = nullptr;
	//포켓몬 세팅
	for (int i = 0; i < player->myPokemon.size(); i++)
	{
		if (player->myPokemon[i]->pokeDie == false)
		{
			SetPokemon(player->myPokemon[i], player->enemyPokemon[0]);
			player->myPokemonNum = i;
			break;
		}
	}

	playerPoke->pokeBack->SetWorldPos(Vector2(1400.0f, 800.0f));
	enermyPoke->pokeFront->SetWorldPos(Vector2(1400.0f, 800.0f));
	//playerPoke->pokeAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	//playerPoke->pokeAni->SetWorldPos(Vector2(-475.0f, 190.0f));
	//playerPoke->pokeAni->isAxis = true;
	//1위치 -475,190  2위치 35, 295, .. 175 55 -65 -185

	intro2State = 0;
	selMenu = 0;

	//메뉴 가방
	bag = new BagMenu();
	bag->bagPlayer = player;
	
	pokeMenu = new PokeMenu();
	pokeMenu->SetPokeMenu(player,(int)(player->myPokemon.size()));
	//몬스터볼
	catchPokeBall = new ObImage(L"Pokemon_Item_MonsterBall.png");
	catchPokeBall->scale.x = catchPokeBall->imageSize.x / 3 * 5;
	catchPokeBall->scale.y = catchPokeBall->imageSize.y * 5;
	catchPokeBall->maxFrame.x = 3;
	catchPokeBall->SetLocalPosX(-600.0f);
	catchPokeBall->SetLocalPosY(0.0f); // 300에서 모션온
	catchPokeBall->isVisible = false;
	catchPokeBallTime = 0.0f;
	catchPokeBallGravi = 800.0f;
	ballBounce = 0;
	ballTime = 0.0f;
	ballCol = 0.5f;

	//배틀 메세지
	battleMes = L"";
	mesNum = 0;
	mesIndex = 0;
	mesTime = 0.0f;
	battelClick = new ObImage(L"HP Bars & In-battle Menu9.png");
	battelClick->scale = battelClick->imageSize * 5;
	battelClick->pivot = OFFSET_L;

	//전투
	playerAttack = false;
	enermyAttack = false;
	changeHp = 0;;
	changeHpFloat = 0.0f;
	fightNum = 0;
	enermySkillNum = 0;
	skillTime = 0.0f;
	enermyPokeDie = false;
	changeExp = 0;
	changeExpFloat = 0.0f;
	leftchangeExp = 0;
	leveUP = false;
	hitTime = 0.0f;
	//플레이어 포켓몬 죽음 수
	pokeDieCount = 0;
	//조명
	lightCol = 0.0f;
	lightTime = 0.0f;
	fadeIn = true;
	fadeOut = false;

	//시작 상태
	state = battleState::INTRO1;
}

void Battle::Release()
{
	for (int i = 0; i < 3; i++)
	{
		SafeDelete(battleGround[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		SafeDelete(battleHp[i]);
	}
	for (int i = 0; i < 9; i++)
	{
		SafeDelete(battleHpBar[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		SafeDelete(battleUi[i]);
	}
	SafeDelete(playerImg);
	SafeDelete(ballAni);
	
	SafeDelete(bag);
	player->enemyPokemon.clear();
}

void Battle::Update()
{
	cout << player->myPokemonNum << endl;
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
		case battleState::INTRO1:
			Intro1();
			break;
		case battleState::INTRO2:
			Intro2();
			break;
		case battleState::TRAINER_INTRO1:
			break;
		case battleState::TRAINER_INTRO2:
			break;
		case battleState::MENU:
			Menu();
			break;
		case battleState::FIGHT: // 선 후공 결정
			Fight();
			break;
		case battleState::FIGHT_FIRST: // 플레이어 공격 -> 플레이어 공격피니시 트루 -> 적 공격피니시도 트루일시 메뉴로  / 아니라면 적 공격
			FightFirst();
			break;
		case battleState::FIGHT_SECEND: // 적 공격 -> 적 공격피니시 트루 -> 플레이어 공격피니시도 트루일시 메뉴로  / 아니라면 적 공격
			FightSecend();
			break;
		case battleState::BAG:
			Bag();
			bag->Update();
			if (bag->usedItemName == L"상처약")
			{
				state = battleState::POKEMON;
				bag->keyOn = false;
				pokeMenu->SetState(PokeMenuState::BAG_ITEM);
				bag->usedItemName = L"";
			}
			else if (bag->usedItemName == L"몬스터볼")
			{
				state = battleState::CATCH_POKE;
				bag->keyOn = false;
				bag->usedItemName = L"";
			}
			break;
		case battleState::POKEMON:
			PokemonList();
			pokeMenu->Update();
			break;
		case battleState::CHANGE_POKE:
			PokemonListChange();
			pokeMenu->Update();
			break;
		case battleState::RUN:
			Run();
			if (player->inCave == true)
			{
				player->inCave = false;
				SOUND->Stop("BATTLE");
				SOUND->Play("CAVE");
				SCENE->ChangeScene("Cave");
				return;
			}
			else if (player->inTown == true)
			{
				player->inTown = false;
				SOUND->Stop("BATTLE");
				SCENE->ChangeScene("Town");
				return;
			}
			break;
		case battleState::CATCH_POKE:
			CatchPokemon();
			if (mesNum == 8)
			{
				if (player->inCave == true)
				{
					player->inCave = false;
					SOUND->Stop("BATTLE");
					SOUND->Play("CAVE");
					SCENE->ChangeScene("Cave");
					return;
				}
				else if (player->inTown == true)
				{
					player->inTown = false;
					SOUND->Stop("BATTLE");
					SCENE->ChangeScene("Town");
					return;
				}
			}
			break;
		case battleState::PLAYER_WIN:
			PlayerWIn();
			if (mesNum == 7)
			{
				if (TIMER->GetTick(mesTime, 0.5))
				{
					mesNum = 0;
					mesIndex = 0;
					enermyPoke->pokeFront->isVisible = true;
					playerPoke->pokeBack->isVisible = false;
					battleHp[0]->isVisible = true;
					for (int i = 0; i < 4; i++)
					{
						battleHpBar[i]->isVisible = true;
					}
					if (playerPoke->evol == false)
					{
						SOUND->Stop("WIN");
						if (player->inCave == true)
						{
							player->inCave = false;
							SOUND->Play("CAVE");
							SCENE->ChangeScene("Cave");
							return;
						}
						else if (player->inTown == true)
						{
							player->inTown = false;
							SCENE->ChangeScene("Town");
							return;
						}
					}
					else
					{
						SOUND->Stop("WIN");
						SOUND->Play("EVO1");
						SCENE->ChangeScene("Evolution");
						return;

					}
				}
			}
			break;
		case battleState::PLAYER_LOSE:
			PlayerLose();
			if (mesNum == 10)
			{
				SOUND->Stop("BATTLE");
				mesNum = 0;
				mesIndex = 0;
				if (player->inCave == true)
				{
					SOUND->Play("CAVE");
					SCENE->ChangeScene("Cave");
					return;
				}
				else if (player->inTown == true)
				{
					SCENE->ChangeScene("Town");
					return;
				}
			}
			break;
		default:
			break;
		}
	}
	
	for (int i = 0; i < player->myPokemon.size(); i++)
	{
		if (player->myPokemon[i]->hp > 0)
		{
			player->myPokemon[i]->pokeDie = false;
		}
	}
	for (int i = 1; i < 9; i++)
	{
		if (i > 0 && i < 4)
		{
			float temp = (float)(enermyPoke->hp) / enermyPoke->maxHP;
			battleHpBar[i]->scale.x = 241.0f * temp;
		}
		else if (i > 4 && i < 8)
		{
			float temp = (float)(playerPoke->hp) / playerPoke->maxHP;
			battleHpBar[i]->scale.x = 241.0f * temp;
		}
		else if (i == 8)
		{
			float temp = (float)(playerPoke->exp) / playerPoke->maxExp;
			battleHpBar[i]->scale.x = 320.0f * temp;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		battleGround[i]->Update();
	}
	for (int i = 0; i < 2; i++)
	{
		battleHp[i]->Update();
	}
	for (int i = 0; i < 9; i++)
	{
		battleHpBar[i]->Update();
	}
	for (int i = 0; i < 4; i++)
	{
		battleUi[i]->Update();
	}
	playerImg->Update();
	ballAni->Update();
	playerPoke->pokeBack->Update();
	enermyPoke->pokeFront->Update();
	
	if (playerPoke->skill[selMenu] != 0)
	{
		playerPoke->skill[selMenu]->skillImg->Update();
	}
	if (enermyPoke->skill[enermySkillNum] != 0)
	{
		enermyPoke->skill[enermySkillNum]->skillImg->Update();
	}
	catchPokeBall->Update();
}

void Battle::LateUpdate()
{
}

void Battle::Render()
{
	if (state != battleState::BAG && state != battleState::POKEMON && state != battleState::EVOLUTION)
	{
		//적
		long leftR = (long)battleHp[0]->GetWorldPos().x + (long)app.GetHalfWidth() + 40;
		long topR = (long)app.GetHalfHeight() - (long)battleHp[0]->GetWorldPos().y - 136;
		long rightR = leftR + 1200;
		long botR = topR + 100;
		wstring tempW = to_wstring(enermyPoke->lv);

		if (battleHp[0]->isVisible == true)
		{
			//이름
			DWRITE->RenderText(enermyPoke->name, RECT{ leftR + 5, topR, rightR + 5, botR }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
			DWRITE->RenderText(enermyPoke->name, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
			DWRITE->RenderText(enermyPoke->name, RECT{ leftR, topR + 5, rightR + 1200, botR + 5 }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
			DWRITE->RenderText(enermyPoke->name, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
			DWRITE->RenderText(enermyPoke->name, RECT{ leftR + 2, topR, rightR + 2, botR }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
			DWRITE->RenderText(enermyPoke->name, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
			DWRITE->RenderText(enermyPoke->name, RECT{ leftR, topR + 2, rightR, botR + 2 }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
			DWRITE->RenderText(enermyPoke->name, RECT{ leftR, topR, rightR, botR }, 48.0f, L"Galmuri11", Color(64.0f / 255.0f, 64.0f / 255.0f, 64.0f / 255.0f, 1.0f));
			//레벨
			//wstring tempW = L"99";

			leftR = (long)battleHp[0]->GetWorldPos().x + (long)app.GetHalfWidth() + 405;
			topR = (long)app.GetHalfHeight() - (long)battleHp[0]->GetWorldPos().y - 132;
			rightR = leftR + 1200;
			botR = topR + 100;

			DWRITE->RenderText(tempW, RECT{ leftR + 5, topR, rightR + 5, botR }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
			DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
			DWRITE->RenderText(tempW, RECT{ leftR, topR + 5, rightR + 1200, botR + 5 }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
			DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
			DWRITE->RenderText(tempW, RECT{ leftR + 2, topR, rightR + 2, botR }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
			DWRITE->RenderText(tempW, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
			DWRITE->RenderText(tempW, RECT{ leftR, topR + 2, rightR, botR + 2 }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
			DWRITE->RenderText(tempW, RECT{ leftR, topR, rightR, botR }, 44.0f, L"Galmuri11", Color(64.0f / 255.0f, 64.0f / 255.0f, 64.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
		}
		
		//나
		//이름
		leftR = (long)battleHp[1]->GetWorldPos().x + (long)app.GetHalfWidth() + 85;
		topR = (long)app.GetHalfHeight() - (long)battleHp[1]->GetWorldPos().y - 176;
		rightR = leftR + 1200;
		botR = topR + 100;
		//cout << leftR << " " << topR << endl;
		DWRITE->RenderText(playerPoke->name, RECT{ leftR + 5, topR, rightR + 5, botR }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(playerPoke->name, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(playerPoke->name, RECT{ leftR, topR + 5, rightR + 1200, botR + 5 }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(playerPoke->name, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(playerPoke->name, RECT{ leftR + 2, topR, rightR + 2, botR }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(playerPoke->name, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(playerPoke->name, RECT{ leftR, topR + 2, rightR, botR + 2 }, 48.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(playerPoke->name, RECT{ leftR, topR, rightR, botR }, 48.0f, L"Galmuri11", Color(64.0f / 255.0f, 64.0f / 255.0f, 64.0f / 255.0f, 1.0f));
		//레벨
		tempW = to_wstring(playerPoke->lv);
		//wstring tempW = L"99";
		leftR = (long)battleHp[1]->GetWorldPos().x + (long)app.GetHalfWidth() + 450;
		topR = (long)app.GetHalfHeight() - (long)battleHp[1]->GetWorldPos().y - 172;
		rightR = leftR + 1200;
		botR = topR + 100;

		DWRITE->RenderText(tempW, RECT{ leftR + 5, topR, rightR + 5, botR }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
		DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
		DWRITE->RenderText(tempW, RECT{ leftR, topR + 5, rightR + 1200, botR + 5 }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
		DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
		DWRITE->RenderText(tempW, RECT{ leftR + 2, topR, rightR + 2, botR }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
		DWRITE->RenderText(tempW, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
		DWRITE->RenderText(tempW, RECT{ leftR, topR + 2, rightR, botR + 2 }, 44.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
		DWRITE->RenderText(tempW, RECT{ leftR, topR, rightR, botR }, 44.0f, L"Galmuri11", Color(64.0f / 255.0f, 64.0f / 255.0f, 64.0f / 255.0f, 1.0f), DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED);
		//체력
		leftR = (long)battleHp[1]->GetWorldPos().x + (long)app.GetHalfWidth() + 300;
		topR = (long)app.GetHalfHeight() - (long)battleHp[1]->GetWorldPos().y - 81;
		rightR = leftR + 1200;
		botR = topR + 100;
		tempW = to_wstring(playerPoke->hp) + L" / " + to_wstring(playerPoke->maxHP);
		DWRITE->RenderText(tempW, RECT{ leftR + 5, topR, rightR + 5, botR }, 35.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 35.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(tempW, RECT{ leftR, topR + 5, rightR + 1200, botR + 5 }, 35.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(tempW, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 35.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(tempW, RECT{ leftR + 2, topR, rightR + 2, botR }, 35.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(tempW, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 35.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(tempW, RECT{ leftR, topR + 2, rightR, botR + 2 }, 35.0f, L"Galmuri11", Color(216.0f / 255.0f, 208.0f / 255.0f, 176.0f / 255.0f, 1.0f));
		DWRITE->RenderText(tempW, RECT{ leftR, topR, rightR, botR }, 35.0f, L"Galmuri11", Color(64.0f / 255.0f, 64.0f / 255.0f, 64.0f / 255.0f, 1.0f));
		
	}
	

	for (int i = 0; i < 3; i++)
	{
		battleGround[i]->Render();
	}
	enermyPoke->pokeFront->Render();
	catchPokeBall->Render();

	for (int i = 0; i < 2; i++)
	{
		battleHp[i]->Render();
	}
	for (int i = 0; i < 9; i++)
	{
		if (i > 0 && i <4)
		{
			if ((float)(enermyPoke->hp) / enermyPoke->maxHP > 0.5f)
			{
				battleHpBar[3]->Render();
			}
			else if ((float)(enermyPoke->hp) / enermyPoke->maxHP > 0.1f)
			{
				battleHpBar[2]->Render();
			}
			else
			{
				battleHpBar[1]->Render();
			}
		}
		else if (i > 4 && i < 8)
		{
			if ((float)(playerPoke->hp) / playerPoke->maxHP > 0.5f)
			{
				battleHpBar[7]->Render();
			}
			else if ((float)(playerPoke->hp) / playerPoke->maxHP > 0.1f)
			{
				battleHpBar[6]->Render();
			}
			else
			{
				battleHpBar[5]->Render();
			}
		}
		else
		{
			battleHpBar[i]->Render();

		}
	}
	playerPoke->pokeBack->Render();
	playerImg->Render();
	ballAni->Render();
	battleUi[0]->Render();
	switch (state)
	{
	case battleState::INTRO2:
	case battleState::INTRO1:
		if (mesNum == 1)
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;

			battleMes = L"앗!  야생의\n" + enermyPoke->name + L"(이)가";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1f))
				{
					mesIndex++;
				}
			}
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f,L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f,L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f,L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f,L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f,L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f,L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f,L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f,L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
			battelClick->SetLocalPos(Vector2(-app.GetHalfWidth() +70.0f + 80.0f * (enermyPoke->name.size() + 1.5f), -330.0f)); //x: -130
			battelClick->Update();
			if (mesIndex == battleMes.size())
			{
				battelClick->Render();
				if (INPUT->KeyDown('Z'))
				{
					SOUND->Stop("SEL");
					SOUND->Play("SEL");
					mesNum++;
					mesIndex = (int)(enermyPoke->name.size()) + 5;
				}
			}

		}
		else if (mesNum == 2)
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = enermyPoke->name + L"(이)가\n튀어나왔다!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1f))
				{
					mesIndex++;
				}
			}
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
			battelClick->SetLocalPos(Vector2(-app.GetHalfWidth() + 70.0f + 80.0f * (4), -330.0f)); //x: -130
			battelClick->Update();
			if (mesIndex == battleMes.size())
			{
				battelClick->Render();
				if (INPUT->KeyDown('Z'))
				{
					SOUND->Stop("SEL");
					SOUND->Play("SEL");
					mesNum++;
					mesIndex = 0;
				}
			}
		}
		else if (mesNum == 3)
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = L"가랏!  " + playerPoke->name + L"!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1f))
				{
					mesIndex++;

				}
			}
			
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
			battelClick->SetLocalPos(Vector2(-app.GetHalfWidth() + 70.0f + 80.0f * (battleMes.size() - 11), -330.0f)); //x: -130
			battelClick->Update();
			
		}
		break;
	case battleState::MENU:
		battleUi[1]->Render();
		battleUi[3]->Render();
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = playerPoke->name + L"(은)는\n무엇을  할까?";
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
		}
		break;
	case battleState::FIGHT:
		battleUi[2]->Render();
		battleUi[3]->Render();
		{
			long leftR = 80;
			long topR = 620;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			float sizeR = 38.0f;
			// 위: 80 400 / 620 아래: 80 400 / 700
			for (int i = 0; i < 4; i++)
			{
				if (playerPoke->skill[i] != 0)
				{
					leftR = 80 + ((i % 2) * 320);
					topR = 620 + ((i / 2) * 80);
					rightR = leftR + 1200;
					botR = topR + 100;
					sizeR = 38.0f;
					battleMes = playerPoke->skill[i]->name;
					DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(72.0f / 255.0f, 72.0f / 255.0f, 72.0f / 255.0f, 1.0f));
				}
				else
				{
					leftR = 80 + ((i % 2) * 320);
					topR = 620 + ((i / 2) * 80);
					rightR = leftR + 1200;
					botR = topR + 100;
					sizeR = 38.0f;
					battleMes = L"­-";
					DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
					DWRITE->RenderText(battleMes, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(72.0f / 255.0f, 72.0f / 255.0f, 72.0f / 255.0f, 1.0f));
				}
			}
			leftR = 955;
			topR = 701;
			rightR = leftR + 1200;
			botR = topR + 100;
			sizeR = 38.0f;
			battleMes = playerPoke->skill[selMenu]->skillType;
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(72.0f / 255.0f, 72.0f / 255.0f, 72.0f / 255.0f, 1.0f));
			leftR = 1001;
			topR = 594;
			rightR = leftR + 1200;
			botR = topR + 100;
			sizeR = 70.0f;
			battleMes = L"­∞";
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f));
			leftR = 1101;
			topR = 594;
			rightR = leftR + 1200;
			botR = topR + 100;
			sizeR = 70.0f;
			battleMes = L"­∞";
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(208.0f / 255.0f, 208.0f / 255.0f, 200.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes, RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f));
		}
		break;
	case battleState::BAG:
		bag->Render();
		break;
	case battleState::POKEMON:
		pokeMenu->Render();
		break;
	case battleState::CHANGE_POKE:
		switch (mesNum)
		{
		case 1:
			
		case 0:
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = playerPoke->name + L"  이젠  됐어\n돌아와!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1f))
				{
					mesIndex++;
				}
			}

			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
			battelClick->SetLocalPos(Vector2(-app.GetHalfWidth() + 70.0f + 80.0f * (battleMes.size() - 11), -330.0f)); //x: -130
			battelClick->Update();
		}
			break;
		case 4:
		case 3:
		case 2:
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = L"가랏!  " + playerPoke->name + L"!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1f))
				{
					mesIndex++;
				}
			}

			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
			battelClick->SetLocalPos(Vector2(-app.GetHalfWidth() + 70.0f + 80.0f * (battleMes.size() - 11), -330.0f)); //x: -130
			battelClick->Update();
		}
			break;
		}
		
		break;
	case battleState::RUN:
		break;
	case battleState::FIGHT_FIRST:
	{
		long leftR = 65;
		long topR = 595;
		long rightR = leftR + 1200;
		long botR = topR + 100;
		battleMes = playerPoke->name + L"의\n" + playerPoke->skill[selMenu]->name + L"　공격!    ";
		if (mesIndex < battleMes.size())
		{
			if (TIMER->GetTick(mesTime, 0.1f))
			{
				mesIndex++;
			}
		}
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
	}
	    switch (fightNum)
	    {
		case 2:
	    	playerPoke->skill[selMenu]->skillImg->Render();
	    	break;
	    default:
	    	break;
	    }
		break;
	case battleState::FIGHT_SECEND:
	{
		long leftR = 65;
		long topR = 595;
		long rightR = leftR + 1200;
		long botR = topR + 100;
		battleMes = enermyPoke->name + L"의\n" + enermyPoke->skill[enermySkillNum]->name + L"　공격!    ";
		if (mesIndex < battleMes.size())
		{
			if (TIMER->GetTick(mesTime, 0.1f))
			{
				mesIndex++;
			}
		}
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
	}
	    switch (fightNum)
	    {
	    case 2:
	    	enermyPoke->skill[enermySkillNum]->skillImg->Render();
	    	break;
	    default:
	    	break;
	    }
	    break;
	    	break;
	case battleState::CATCH_POKE:
		CatchPokemonRander();
		break;
	case battleState::PLAYER_WIN:
		if (mesNum == 1)
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;

			battleMes = L"야생  " + enermyPoke->name + L"(은)는\n쓰러졌다!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1f))
				{
					mesIndex++;
				}
			}
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
			battelClick->SetLocalPos(Vector2(-app.GetHalfWidth() + 70.0f + 80.0f * (3.5f), -330.0f)); //x: -130
			battelClick->Update();
			if (mesIndex == battleMes.size())
			{
				battelClick->Render();
				if (INPUT->KeyDown('Z'))
				{
					SOUND->Stop("SEL");
					SOUND->Play("SEL");
					SOUND->Stop("BATTLE");
					SOUND->Stop("WIN");
					SOUND->Play("WIN");
					mesNum++;
					mesIndex = 0;
				}
			}
		}
		else if (mesNum == 2)
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			wstring tempW = to_wstring(enermyPoke->lv * 50);
			battleMes = playerPoke->name + L"(은)는\n" + tempW + L"  경험치를  얻었다!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1f))
				{
					mesIndex++;
				}
			}
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
			battelClick->SetLocalPos(Vector2(-app.GetHalfWidth() + 70.0f + 80.0f * (tempW.size() + 6), -330.0f)); //x: -130
			battelClick->Update();
			if (mesIndex == battleMes.size())
			{
				battelClick->Render();
				if (INPUT->KeyDown('Z'))
				{
					SOUND->Stop("SEL");
					SOUND->Play("SEL");
					mesNum++;
					//mesIndex = 0;
				}
			}
		}
		else if (mesNum == 4 && leveUP == true)//mesNum =4
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			long sizeR = 60;

			wstring tempW = to_wstring(playerPoke->lv);
			battleMes = playerPoke->name + L"(은)는\n레벨" + tempW + L"(으)로  올랐다!      ";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1f))
				{
					mesIndex++;
				}
			}
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, sizeR, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, sizeR, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, sizeR, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, sizeR, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, sizeR, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
			if (mesIndex == battleMes.size())
			{
				mesNum = 5;
				//mesIndex = 0;
			}
		}
		break;
	case battleState::PLAYER_LOSE:
		PlayerLoseRander();
		break;
	default:
		break;
	}
}

void Battle::ResizeScreen()
{
}

void Battle::Intro1()
{
	if (battleGround[1]->GetWorldPos().x < -app.GetHalfWidth() || battleGround[2]->GetWorldPos().x > -app.GetHalfWidth())
	{
		battleGround[1]->MoveWorldPos(RIGHT * 600.0f * DELTA);
		battleGround[2]->MoveWorldPos(LEFT * 600.0f * DELTA);
		for (int i = 0; i < 3; i++)
		{
			battleGround[i]->Update();
		}
		playerImg->SetLocalPosX(battleGround[2]->GetWorldPos().x + 280);
		enermyPoke->pokeFront->SetLocalPos(Vector2(battleGround[1]->GetWorldPos().x + 875, battleGround[2]->GetWorldPos().y + 200));
		if (battleGround[1]->GetWorldPos().x >= -app.GetHalfWidth() && battleGround[2]->GetWorldPos().x <= -app.GetHalfWidth())
		{
			battleGround[1]->SetWorldPosX(-app.GetHalfWidth());
			battleGround[2]->SetWorldPosX(-app.GetHalfWidth());
			for (int i = 1; i < 3; i++)
			{
				battleGround[i]->Update();
			}
			enermyPoke->pokeFront->SetLocalPos(Vector2(battleGround[1]->GetWorldPos().x + 875, battleGround[2]->GetWorldPos().y + 200));
			enermyPoke->OutSound();
			mesNum = 1;
		}

	}
	else if (battleHp[0]->GetWorldPos().x < -app.GetHalfWidth() + 60.0f)
	{
		battleHp[0]->MoveWorldPos(RIGHT * 1000.0f * DELTA);
		for (int i = 0; i < 4; i++)
		{
			battleHpBar[i]->MoveWorldPos(RIGHT * 1000.0f * DELTA);
		}
		if (battleHp[0]->GetWorldPos().x >= -app.GetHalfWidth() + 60.0f)
		{
			battleHp[0]->SetWorldPosX(-app.GetHalfWidth() + 60.0f);
			for (int i = 0; i < 4; i++)
			{
				battleHpBar[i]->SetWorldPosX(-345.0f);
			}
		}
	}
	else
	{
		//울음소리 추가 필요
		if (mesNum == 3 && mesIndex == battleMes.size())
		{
			state = battleState::INTRO2;
			playerImg->frame.x = 0;
			//mesNum = 0;
		}
		
	}
}

void Battle::Intro2()
{
	switch (intro2State)
	{
	case 0:
		if (playerImg->frame.x == 0)
		{
			//mesNum = 1;
			playerImg->ChangeAnim(ANIMSTATE::ONCE, 0.15f);
			intro2State++;
		}
		break;
	case 1:
		if (playerImg->GetWorldPos().x > -app.GetHalfWidth() - playerImg->imageSize.x)
		{
			playerImg->MoveWorldPos(LEFT * 700.0f * DELTA);
			if (TIMER->GetTick(ballThrowTime, 0.5))
			{
				ballAni->isVisible = true;
			}
		}
		else
		{
			playerImg->isVisible = false;
		}
		if (ballAni->isVisible == true)
		{
			if (TIMER->GetTick(ballAniTime, 0.1f))
			{
				ballAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			}
			ballAni->MoveWorldPos(RIGHT * 100.0f * DELTA + DOWN * ballGravi * DELTA);
			ballGravi += 1000.0f * DELTA;
		}
		if (ballAni->GetWorldPos().y < -300.0f && ballAni->isVisible == true)
		{
			SOUND->Stop("BALLSWAP");
			SOUND->Play("BALLSWAP");
			ballAni->isVisible = false;
			ballAni->SetLocalPosX(-400.0f);
			ballAni->SetLocalPosY(20.0f);
			ballGravi = -200.0f;
			ballAni->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			ballAni->frame.x = 0;
			playerPoke->pokeBack->scale *= 0.1f;
			playerPoke->pokeBack->SetWorldPos(Vector2(-260.0f, -160.0f));
			intro2State++;
		}
		break;
	case 2:
		if (BallOutPoke(playerPoke, ballOutScale))
		{
			intro2State++;
			playerPoke->OutSound();
		}
		break;
	case 3:
		if (battleHp[1]->GetWorldPos().x > -app.GetHalfWidth() + 650)
		{
			battleHp[1]->MoveWorldPos(LEFT * 1000.0f * DELTA);
			for (int i = 4; i < 9; i++)
			{
				battleHpBar[i]->MoveWorldPos(LEFT * 1000.0f * DELTA);
			}
		}
		else
		{
			battleHp[1]->SetWorldPosX(-app.GetHalfWidth() + 650);
			for (int i = 4; i < 8; i++)
			{
				battleHpBar[i]->SetWorldPosX(289.0f);
			}
			battleHpBar[8]->SetWorldPosX(210.0f);

			intro2State = 4;
		}
		
		break;
	case 4:
		playerPoke->pokeBack->scale = playerPoke->pokeBack->imageSize * 5;
		state = battleState::MENU;
		intro2State = 0;
		mesNum = 0;
		mesIndex = 0;
		break;
	default:
		break;
	}
}

void Battle::Menu()
{
	if (INPUT->KeyDown(VK_UP))
	{
		switch (selMenu)
		{
		case 2:
			selMenu = 0;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		case 3:
			selMenu = 1;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		default:
			//효과음만
			break;
		}
	}
	else if (INPUT->KeyDown(VK_DOWN))
	{
		switch (selMenu)
		{
		case 0:
			selMenu = 2;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		case 1:
			selMenu = 3;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		default:
			//효과음만
			break;
		}
	}
	else if (INPUT->KeyDown(VK_LEFT))
	{
		switch (selMenu)
		{
		case 1:
			selMenu = 0;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		case 3:
			selMenu = 2;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		default:
			//효과음만
			break;
		}
	}
	else if (INPUT->KeyDown(VK_RIGHT))
	{
		switch (selMenu)
		{
		case 0:
			selMenu = 1;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		case 2:
			selMenu = 3;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		default:
			//효과음만
			break;
		}
	}
	else if (INPUT->KeyDown('Z'))
	{
		switch (selMenu)
		{
		case 0:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = battleState::FIGHT;
			break;
		case 1:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = battleState::BAG;
			bag->state = BagMenuState::BATTEL_SEL;
			bag->sel = 0;
			
			break;
		case 2:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = battleState::POKEMON;
			pokeMenu->SetState(PokeMenuState::BATTEL_SEL);
			break;
		case 3:
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = battleState::RUN;
			break;
		default:
			break;
		}
	}
	switch (selMenu)
	{
	case 0:
		battleUi[3]->SetWorldPos(Vector2(45.0f, -274.0f));
		break;
	case 1:
		battleUi[3]->SetWorldPos(Vector2(323.0f, -274.0f));
		break;
	case 2:
		battleUi[3]->SetWorldPos(Vector2(45.0f, -354.0f));
		break;
	case 3:
		battleUi[3]->SetWorldPos(Vector2(323.0f, -354.0f));
		break;
	default:
		break;
	}
}

void Battle::Fight()
{
	if (INPUT->KeyDown(VK_UP))
	{
		switch (selMenu)
		{
		case 2:
			selMenu = 0;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		case 3:
			selMenu = 1;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		default:
			//효과음만
			break;
		}
	}
	else if (INPUT->KeyDown(VK_DOWN))
	{
		switch (selMenu)
		{
		case 0:
			if (playerPoke->skill[2] != 0)
			{
				selMenu = 2;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
			}
			break;
		case 1:
			if (playerPoke->skill[3] != 0)
			{
				selMenu = 3;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
			}
			break;
		default:
			//효과음만
			break;
		}
	}
	else if (INPUT->KeyDown(VK_LEFT))
	{
		switch (selMenu)
		{
		case 1:
			selMenu = 0;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		case 3:
			selMenu = 2;
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			break;
		default:
			//효과음만
			break;
		}
	}
	else if (INPUT->KeyDown(VK_RIGHT))
	{
		switch (selMenu)
		{
		case 0:
			if (playerPoke->skill[1] != 0)
			{
				selMenu = 1;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
			}
			break;
		case 2:
			if (playerPoke->skill[3] != 0)
			{
				selMenu = 3;
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
			}
			break;
		default:
			//효과음만
			break;
		}
	}
	else if (INPUT->KeyDown('X'))
	{
		state = battleState::MENU;
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		selMenu = 0;
	}
	else if (INPUT->KeyDown('Z'))
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		enermySkillNum = 0;
		for (int i = 0; i < 4; i++)
		{
			if (enermyPoke->skill[i] != 0)
			{
				enermySkillNum++;
			}
		}
		enermySkillNum = RANDOM->Int(0, enermySkillNum - 1);
		if (playerPoke->spd >= enermyPoke->spd)
		{
			state = battleState::FIGHT_FIRST;

		}
		else
		{
			state = battleState::FIGHT_SECEND;
		}

		//selMenu = 0;
	}
	switch (selMenu)
	{
	case 0:
		battleUi[3]->SetWorldPos(Vector2(-555.0f, -274.0f));
		break;
	case 1:
		battleUi[3]->SetWorldPos(Vector2(-235.0f, -274.0f));
		break;
	case 2:
		battleUi[3]->SetWorldPos(Vector2(-555.0f, -354.0f));
		break;
	case 3:
		battleUi[3]->SetWorldPos(Vector2(-235.0f, -354.0f));
		break;
	default:
		break;
	}
}

void Battle::FightFirst()
{
	switch (fightNum)
	{
	case 0:
		if (mesIndex == battleMes.size())
		{
			fightNum = 1;
		}
		break;
	case 1:
		playerPoke->skill[selMenu]->skillImg->SetWorldPos(enermyPoke->pokeFront->GetWorldPos());
		playerPoke->skill[selMenu]->skillImg->Update();
		playerPoke->skill[selMenu]->skillImg->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		playerPoke->skill[selMenu]->OutSound();
		fightNum = 2;
		break;
	case 2:
		if (playerPoke->skill[selMenu]->skillImg->animState == ANIMSTATE::STOP)
		{
			fightNum = 3;
		}
		break;
	case 3:
	{
		int temp = enermyPoke->def - playerPoke->atk - playerPoke->skill[selMenu]->dam;
		if (temp >= 0)
		{
			temp = -1;
		}
		enermyPoke->changeHp += temp;//플레이어 공격: 적 방어력 - ( 플레이어 공격력 + 스킬 데미지);
		if (enermyPoke->changeHp <= 0)
		{
			enermyPoke->changeHp = 0;
		}
		changeHp = (enermyPoke->hp - enermyPoke->changeHp);
		changeHpFloat = (float)(enermyPoke->hp);

		fightNum = 4;
		SOUND->Stop("ATTACK");
		SOUND->Play("ATTACK");
	}
		break;
	case 4:
		if (enermyPoke->hp > enermyPoke->changeHp)
		{
			changeHpFloat -= changeHp * DELTA;
			enermyPoke->hp = (int)changeHpFloat;
			if (TIMER->GetTick(hitTime,0.08))
			{
				if (enermyPoke->pokeFront->color == Color(0.5f, 0.5f, 0.5f, 0.5f))
				{
					enermyPoke->pokeFront->color = Color(0.5f, 0.5f, 0.5f, 0.0f);
				}
				else
				{
					enermyPoke->pokeFront->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
				}
			}
		}
		else
		{
			enermyPoke->hp = enermyPoke->changeHp;
			enermyPoke->pokeFront->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			if (enermyPoke->hp > 0)
			{
				playerAttack = true;
				if (playerAttack == true && enermyAttack == true)
				{
					if (TIMER->GetTick(mesTime, 0.4f))
					{
						playerAttack = false;
						enermyAttack = false;
						state = battleState::MENU;
						fightNum = 0;
						selMenu = 0;
						mesIndex = 0;
					}
					
				}
				else
				{
					if (TIMER->GetTick(mesTime, 0.4f))
					{
						fightNum = 0;
						mesIndex = 0;
						state = battleState::FIGHT_SECEND;
					}
					
				}
			}
			else
			{
				if (TIMER->GetTick(mesTime, 0.4f))
				{
					playerAttack = false;
					enermyAttack = false;
					fightNum = 0;
					selMenu = 0;
					mesIndex = 0;
					state = battleState::PLAYER_WIN;
				}
				
			}
		}
		break;
	
	default:
		break;
	}
}

void Battle::FightSecend()
{
	switch (fightNum)
	{
	case 0:
		if (mesIndex == battleMes.size())
		{
			fightNum = 1;
		}
		break;
	case 1:
		enermyPoke->skill[enermySkillNum]->skillImg->SetWorldPos(playerPoke->pokeBack->GetWorldPos());
		enermyPoke->skill[enermySkillNum]->skillImg->Update();
		enermyPoke->skill[enermySkillNum]->skillImg->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		enermyPoke->skill[enermySkillNum]->OutSound();
		fightNum = 2;
		break;
	case 2:
		if (enermyPoke->skill[enermySkillNum]->skillImg->animState == ANIMSTATE::STOP)
		{
			fightNum = 3;
		}
		break;
	case 3:
	{
		int temp = playerPoke->def - enermyPoke->atk - enermyPoke->skill[enermySkillNum]->dam;
		if (temp > 0)
		{
			temp = -1;
		}
		playerPoke->changeHp += temp;//플레이어 공격: 적 방어력 - ( 플레이어 공격력 + 스킬 데미지);
		if (playerPoke->changeHp <= 0)
		{
			playerPoke->changeHp = 0;
		}
		changeHp = (playerPoke->hp - playerPoke->changeHp);
		changeHpFloat = (float)(playerPoke->hp);
		//cout << DELTA * changeHp << " " << (int)changeHpFloat << endl;

		fightNum = 4;
		SOUND->Stop("ATTACK");
		SOUND->Play("ATTACK");
	}
	break;
	case 4:
		if (playerPoke->hp > playerPoke->changeHp)
		{
			changeHpFloat -= changeHp * DELTA;
			playerPoke->hp = (int)changeHpFloat;
			if (TIMER->GetTick(hitTime, 0.08))
			{
				if (playerPoke->pokeBack->color == Color(0.5f, 0.5f, 0.5f, 0.5f))
				{
					playerPoke->pokeBack->color = Color(0.5f, 0.5f, 0.5f, 0.0f);
				}
				else
				{
					playerPoke->pokeBack->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
				}
			}
		}
		else
		{
			playerPoke->hp = playerPoke->changeHp;
			playerPoke->pokeBack->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			if (playerPoke->hp > 0)
			{
				enermyAttack = true;
				if (playerAttack == true && enermyAttack == true)
				{
					if (TIMER->GetTick(mesTime, 0.4f))
					{
						playerAttack = false;
						enermyAttack = false;
						state = battleState::MENU;
						fightNum = 0;
						selMenu = 0;
						mesIndex = 0;
					}
				}
				else
				{
					if (TIMER->GetTick(mesTime, 0.4f))
					{
						fightNum = 0;
						mesIndex = 0;
						state = battleState::FIGHT_FIRST;
					}
				}
			}
			else
			{
				if (TIMER->GetTick(mesTime, 0.4f))
				{
					playerAttack = false;
					enermyAttack = false;
					fightNum = 0;
					selMenu = 0;
					mesIndex = 0;
					state = battleState::PLAYER_LOSE;
				}
			}
		}
		break;
	
	default:
		break;
	}
	
}

void Battle::Bag()
{
	if (INPUT->KeyDown('X') && bag->state == BagMenuState::BATTEL_SEL)
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		state = battleState::MENU;		
		bag->sel = 0;
		bag->keyOn = false;
	}
	else if (INPUT->KeyDown('Z') && bag->state == BagMenuState::BATTEL_SEL && bag->sel == player->myItem.size())
	{
		SOUND->Stop("SEL");
		SOUND->Play("SEL");
		state = battleState::MENU;		
		bag->sel = 0;
		bag->keyOn = false;
	}
}

void Battle::PokemonList()
{
	switch (pokeMenu->state)
	{
	case PokeMenuState::BATTEL_SEL:
		if (INPUT->KeyDown('X'))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = battleState::MENU;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;
		}
		else if (INPUT->KeyDown('Z') && pokeMenu->selPokeList == 6)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = battleState::MENU;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;

		}
		else if (INPUT->KeyDown('Z') && pokeMenu->selPokeList != 6 && player->myPokemon[pokeMenu->selPokeList]->pokeDie == false)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			if (playerPoke != player->myPokemon[pokeMenu->selPokeList])
			{
				state = battleState::CHANGE_POKE;
			}
		}
		break;
	case PokeMenuState::BATTEL_LOSE_SEL:
		if (INPUT->KeyDown('Z') && pokeMenu->selPokeList != 6)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			if (playerPoke != player->myPokemon[pokeMenu->selPokeList] && player->myPokemon[pokeMenu->selPokeList]->pokeDie == false)
			{
				playerPoke = player->myPokemon[pokeMenu->selPokeList];
				player->myPokemonNum = pokeMenu->selPokeList;
				playerPoke->pokeBack->isVisible = false;
				pokeMenu->selPokeList = 0;
				pokeMenu->lastSelPokeList = 1;
				//battleHp[1]->SetWorldPosX(app.GetHalfWidth());
				//battleHpBar[4]->SetWorldPosX(289.0f + 550.0f);
				//battleHpBar[5]->SetWorldPosX(289.0f + 550.0f);
				//battleHpBar[6]->SetWorldPosX(289.0f + 550.0f);
				//battleHpBar[7]->SetWorldPosX(289.0f + 550.0f);
				//battleHpBar[8]->SetWorldPosX(210.0f + 550.0f);
				state = battleState::PLAYER_LOSE;
			}
		}
		break;
	case PokeMenuState::BAG_ITEM:
		if (INPUT->KeyDown('X'))
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = battleState::BAG;
			pokeMenu->state = PokeMenuState::SEL;
			pokeMenu->lastSelPokeList = 1;
			pokeMenu->selPokeList = 0;
		}
		else if (INPUT->KeyDown('Z') && pokeMenu->selPokeList == 6)
		{
			SOUND->Stop("SEL");
			SOUND->Play("SEL");
			state = battleState::BAG;
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
				playerAttack = true;

				state = battleState::FIGHT_SECEND;// 적 공격으로

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

void Battle::PokemonListChange()
{
	switch (mesNum)
	{
	case 0:
		if (mesIndex == battleMes.size())
		{
			mesNum++;
			SOUND->Stop("BALLSWAP");
			SOUND->Play("BALLSWAP");
		}
		break;
	case 1:
		if (BallInPoke(playerPoke, ballInScale))
		{
			playerPoke = player->myPokemon[pokeMenu->selPokeList];
			player->myPokemonNum = pokeMenu->selPokeList;
			mesNum++;
			mesIndex = 0;
			pokeMenu->selPokeList = 0;
			pokeMenu->lastSelPokeList = 1;
			battleHp[1]->SetWorldPosX(app.GetHalfWidth());
			battleHpBar[4]->SetWorldPosX(289.0f + 550.0f);
			battleHpBar[5]->SetWorldPosX(289.0f + 550.0f);
			battleHpBar[6]->SetWorldPosX(289.0f + 550.0f);
			battleHpBar[7]->SetWorldPosX(289.0f + 550.0f);
			battleHpBar[8]->SetWorldPosX(210.0f + 550.0f);
		}
		break;
	case 2: // 포켓몬 볼 던지기
		if (mesIndex == battleMes.size())
		{
			ballAni->isVisible = true;
		}
		if (ballAni->isVisible == true)
		{
			if (TIMER->GetTick(ballAniTime, 0.1f))
			{
				ballAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			}
			ballAni->MoveWorldPos(RIGHT * 100.0f * DELTA + DOWN * ballGravi * DELTA);
			ballGravi += 1000.0f * DELTA;
		}
		if (ballAni->GetWorldPos().y < -300.0f && ballAni->isVisible == true)
		{
			SOUND->Stop("BALLSWAP");
			SOUND->Play("BALLSWAP");
			ballAni->isVisible = false;
			ballAni->SetLocalPosX(-400.0f);
			ballAni->SetLocalPosY(20.0f);
			ballGravi = -200.0f;
			ballAni->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			ballAni->frame.x = 0;
			playerPoke->pokeBack->scale *= 0.1f;
			playerPoke->pokeBack->SetWorldPos(Vector2(-260.0f, -160.0f));
			mesNum++;
		}
		break;
	case 3: //포켓몬 볼아웃
		if (BallOutPoke(playerPoke, ballOutScale))
		{
			mesNum++;
			playerPoke->pokeBack->scale = playerPoke->pokeBack->imageSize * 5;
			playerPoke->OutSound();
		}
		break;
	case 4: //포켓몬 체력바 움직이기 -> 상대턴으로 전환
		if (battleHp[1]->GetWorldPos().x > -app.GetHalfWidth() + 650)
		{
			battleHp[1]->MoveWorldPos(LEFT * 1000.0f * DELTA);
			for (int i = 4; i < 9; i++)
			{
				battleHpBar[i]->MoveWorldPos(LEFT * 1000.0f * DELTA);
			}
		}
		else
		{
			battleHp[1]->SetWorldPosX(-app.GetHalfWidth() + 650);
			for (int i = 4; i < 8; i++)
			{
				battleHpBar[i]->SetWorldPosX(289.0f);
			}
			battleHpBar[8]->SetWorldPosX(210.0f);
			mesNum = 0;
			mesIndex = 0;
			state = battleState::FIGHT_SECEND;
			playerAttack = true;
			selMenu = 0;
		}
		break;
	}
	
}

void Battle::Run()
{
	//임시
	//if (INPUT->KeyDown('X')) 
	//{
	//	state = battleState::MENU;
	//}
	playerPoke->pokeBack->isVisible = false;
	SOUND->Stop("RUN");
	SOUND->Play("RUN");
}

void Battle::PlayerWIn()
{
	if (mesNum == 0)
	{
		if (enermyPoke->pokeFront->GetWorldPos().y > battleGround[2]->GetWorldPos().y + 200 - enermyPoke->pokeFront->imageSize.y * 5)
		{
			if (enermyPokeDie == false)
			{
				enermyPokeDie = true;
				SOUND->Stop("DIE");
				SOUND->Play("DIE");
			}
			enermyPoke->pokeFront->MoveWorldPos(DOWN * 1000.0f * DELTA);
			enermyPoke->pokeFront->Update();
			if (enermyPoke->pokeFront->GetWorldPos().y <= battleGround[2]->GetWorldPos().y + 200 - enermyPoke->pokeFront->imageSize.y * 5)
			{
				enermyPoke->pokeFront->SetLocalPos(Vector2(battleGround[1]->GetWorldPos().x + 875, battleGround[2]->GetWorldPos().y + 200));//원위치
				enermyPoke->pokeFront->isVisible = false;
				player->money += enermyPoke->lv * 100;
				battleHp[0]->isVisible = false;
				for (int i = 0; i < 4; i++)
				{
					battleHpBar[i]->isVisible = false;
				}
				enermyPokeDie = false;
				mesNum = 1;
				playerPoke->evol = false;
				playerPoke->changeExp += enermyPoke->lv * 50;
				if (playerPoke->changeExp > playerPoke->maxExp)
				{
					leftchangeExp = playerPoke->changeExp - playerPoke->maxExp;
					playerPoke->changeExp = playerPoke->maxExp;
				}
				changeExp = (playerPoke->changeExp - playerPoke->exp);
				changeExpFloat = (float)(playerPoke->exp);
			}
		}
	}
	else if (mesNum == 3)//경험치 증가
	{
		if (playerPoke->exp < playerPoke->changeExp)
		{
			//SOUND->Stop("EXP");
			SOUND->Play("EXP");
			changeExpFloat += changeExp * DELTA;
			playerPoke->exp = (int)changeExpFloat;
			
		}
		else if (playerPoke->exp >= playerPoke->maxExp)
		{
			SOUND->Stop("EXP");
			SOUND->Stop("LEVUP");
			SOUND->Play("LEVUP");
			playerPoke->exp = 0;
			playerPoke->changeExp = 0;
			playerPoke->lv += 1;
			playerPoke->SetPokemon();
			leveUP = true;
			mesNum = 4;
			mesIndex = 0;
			playerPoke->changeExp += leftchangeExp;
			leftchangeExp = 0;
			if (playerPoke->changeExp > playerPoke->maxExp)
			{
				leftchangeExp = playerPoke->changeExp - playerPoke->maxExp;
				playerPoke->changeExp = playerPoke->maxExp;
			}
			changeExp = (playerPoke->changeExp - playerPoke->exp);
			changeExpFloat = (float)(playerPoke->exp);
		}
		else
		{
			SOUND->Stop("EXP");
			mesIndex = battleMes.size();
			mesNum = 7;
		}
	}
	else if (mesNum == 5) //경험치 증가2
	{
		if (playerPoke->exp < playerPoke->changeExp)
		{
			//SOUND->Stop("EXP");
			SOUND->Play("EXP");
			changeExpFloat += changeExp * DELTA;
			playerPoke->exp = (int)changeExpFloat;

		}
		else if (playerPoke->exp >= playerPoke->maxExp)
		{
			SOUND->Stop("EXP");
			SOUND->Stop("LEVUP");
			SOUND->Play("LEVUP");
			playerPoke->exp = 0;
			playerPoke->changeExp = 0;
			playerPoke->lv += 1;
			playerPoke->SetPokemon();
			leveUP = true;
			mesNum = 4;
			mesIndex = 0;
			playerPoke->changeExp += leftchangeExp;
			leftchangeExp = 0;
			if (playerPoke->changeExp > playerPoke->maxExp)
			{
				leftchangeExp = playerPoke->changeExp - playerPoke->maxExp;
				playerPoke->changeExp = playerPoke->maxExp;
			}
			changeExp = (playerPoke->changeExp - playerPoke->exp);
			changeExpFloat = (float)(playerPoke->exp);
		}
		else
		{
			SOUND->Stop("EXP");
			mesIndex = battleMes.size();
			mesNum = 7;
		}
	}
}

void Battle::PlayerLose()
{
	if (mesNum == 0) // 포켓몬, 체력바 사라지기
	{
		if (playerPoke->pokeBack->GetWorldPos().y >  -160.0f - playerPoke->pokeBack->imageSize.y * 5)
		{
			if (playerPoke->pokeDie == false)
			{
				playerPoke->pokeDie = true;
				SOUND->Stop("DIE");
				SOUND->Play("DIE");
			}
			playerPoke->pokeBack->MoveWorldPos(DOWN * 1000.0f * DELTA);
			playerPoke->pokeBack->Update();
			if (playerPoke->pokeBack->GetWorldPos().y <= -160.0f - playerPoke->pokeBack->imageSize.y * 5)
			{
				playerPoke->pokeBack->SetLocalPos(Vector2(-260.0f, -160.0f));//원위치
				playerPoke->pokeBack->isVisible = false;
				battleHp[1]->SetWorldPosX(app.GetHalfWidth());
				battleHpBar[4]->SetWorldPosX(289.0f + 550.0f);
				battleHpBar[5]->SetWorldPosX(289.0f + 550.0f);
				battleHpBar[6]->SetWorldPosX(289.0f + 550.0f);
				battleHpBar[7]->SetWorldPosX(289.0f + 550.0f);
				battleHpBar[8]->SetWorldPosX(210.0f + 550.0f);
				pokeDieCount = 0;
				for (int i = 0; i < player->myPokemon.size(); i++)
				{
					if (player->myPokemon[i]->pokeDie == true)
					{
						pokeDieCount++;
					}
				}
				cout << pokeDieCount << "die" << endl;

				mesNum = 1;
			}
		}
	}
	else if (mesNum == 2) //포켓몬 교환으로 전환
	{
		state = battleState::POKEMON;
		pokeMenu->SetState(PokeMenuState::BATTEL_LOSE_SEL);
		mesNum = 3;
		
	}
	else if (mesNum == 3)
	{
		if (mesIndex == battleMes.size())
		{
			ballAni->isVisible = true;
			mesNum = 4;
		}
	}
	else if (mesNum == 4) //포켓볼 던지기
	{
		if (ballAni->isVisible == true)
		{
			if (TIMER->GetTick(ballAniTime, 0.1f))
			{
				ballAni->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			}
			ballAni->MoveWorldPos(RIGHT * 100.0f * DELTA + DOWN * ballGravi * DELTA);
			ballGravi += 1000.0f * DELTA;
			ballAni->Update();
			if (ballAni->GetWorldPos().y < -300.0f && ballAni->isVisible == true)
			{
				SOUND->Stop("BALLSWAP");
				SOUND->Play("BALLSWAP");
				ballAni->isVisible = false;
				ballAni->SetLocalPosX(-400.0f);
				ballAni->SetLocalPosY(20.0f);
				ballGravi = -200.0f;
				ballAni->ChangeAnim(ANIMSTATE::STOP, 0.1f);
				ballAni->frame.x = 0;
				playerPoke->pokeBack->scale *= 0.1f;
				playerPoke->pokeBack->SetWorldPos(Vector2(-260.0f, -160.0f));
				mesNum = 5;
			}
		}
	}
	else if (mesNum == 5)// 볼 아웃
	{
		if (BallOutPoke(playerPoke, ballOutScale))
		{
			mesNum = 6;
			playerPoke->pokeBack->scale = playerPoke->pokeBack->imageSize * 5;
			playerPoke->OutSound();
		}
	}
	else if (mesNum == 6) // 체력바 움직이기-> 배틀 메뉴로
	{
		if (battleHp[1]->GetWorldPos().x > -app.GetHalfWidth() + 650)
		{
			battleHp[1]->MoveWorldPos(LEFT * 1000.0f * DELTA);
			for (int i = 4; i < 9; i++)
			{
				battleHpBar[i]->MoveWorldPos(LEFT * 1000.0f * DELTA);
			}
		}
		else
		{
			battleHp[1]->SetWorldPosX(-app.GetHalfWidth() + 650);
			for (int i = 4; i < 8; i++)
			{
				battleHpBar[i]->SetWorldPosX(289.0f);
			}
			battleHpBar[8]->SetWorldPosX(210.0f);
			mesNum = 0;
			mesIndex = 0;
			state = battleState::MENU;
			selMenu = 0;
		}
	}
	else if (mesNum == 9)
	{
	    for (int i = 0; i < player->myPokemon.size(); i++)
	    {
			player->myPokemon[i]->lv = 1;
			player->myPokemon[i]->hp = player->myPokemon[i]->maxHP;
			player->myPokemon[i]->SetPokemon();
			player->myPokemon[i]->pokeDie = false;

	    }
		mesNum = 10;
	}
	
	
}

void Battle::PlayerLoseRander()
{
	if (mesNum == 1)
	{
		long leftR = 65;
		long topR = 595;
		long rightR = leftR + 1200;
		long botR = topR + 100;

		battleMes = playerPoke->name + L"(은)는\n쓰러졌다!";
		if (mesIndex < battleMes.size())
		{
			if (TIMER->GetTick(mesTime, 0.1))
			{
				mesIndex++;
			}
		}
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
		DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
		battelClick->SetLocalPos(Vector2(-app.GetHalfWidth() + 70.0f + 80.0f * (3.5), -330.0f)); //x: -130
		battelClick->Update();
		if (mesIndex == battleMes.size())
		{
			battelClick->Render();
			if (INPUT->KeyDown('Z'))
			{
				SOUND->Stop("SEL");
				SOUND->Play("SEL");
				if (pokeDieCount == player->myPokemon.size())
				{
					mesNum = 7;
				}
				else
				{
					mesNum++;
				}
				mesIndex = 0;
			}
		}
	}
	else if (mesNum == 3 || mesNum == 4 || mesNum == 5 || mesNum == 6) // 가라 외치고 포켓볼 던지기
	{
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = L"가랏!  " + playerPoke->name + L"!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1))
				{
					mesIndex++;
				}
			}

			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
		}
	}
	else if (mesNum == 7)
	{
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = L"원진의　곁에는　더이상\n싸울　수　있는　포켓몬이　없다!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1))
				{
					mesIndex++;
				}
			}

			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
			battelClick->SetLocalPos(Vector2(-app.GetHalfWidth() + 70.0f + 80.0f * (11.5), -330.0f)); //x: -130
			battelClick->Update();
			if (mesIndex == battleMes.size())
			{
				battelClick->Render();

				if (INPUT->KeyDown('Z'))
				{
					SOUND->Stop("SEL");
					SOUND->Play("SEL");
					mesNum = 8;
					mesIndex = 0;
				}
			}
			
		}
	}
	else if (mesNum == 8)
	{
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = L"원진의　모든　포켓몬　레벨이\n1로　초기화된다.";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1))
				{
					mesIndex++;
				}
			}

			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
			battelClick->SetLocalPos(Vector2(-app.GetHalfWidth() + 70.0f + 80.0f * (6), -330.0f)); //x: -130
			battelClick->Update();
			if (mesIndex == battleMes.size())
			{
				battelClick->Render();

				if (INPUT->KeyDown('Z'))
				{
					SOUND->Stop("SEL");
					SOUND->Play("SEL");
					mesNum = 9;
					mesIndex = 0;
				}
			}
			
		}
	}
}

void Battle::CatchPokemon()
{
	
	if (mesNum == 0)
	{
		if (player->myItem[bag->sel]->num == 1)
		{
			auto iter = player->myItem.begin() + bag->sel;
			player->myItem.erase(iter);
		}
		else
		{
			player->myItem[bag->sel]->num--;
		}
		mesNum = 1;
	}
	else if (mesNum == 1)
	{
		if (mesIndex == battleMes.size())
		{
			if (catchPokeBall->GetWorldPos().x < enermyPoke->pokeFront->GetWorldPos().x)
			{
				if (catchPokeBall->isVisible == false)
				{
					catchPokeBall->isVisible = true;
					SOUND->Play("BALL");
				}
				catchPokeBall->MoveWorldPos((RIGHT * 1000.0f + UP * catchPokeBallGravi) * DELTA);
				catchPokeBallGravi -= DELTA * 1100.0f;
				catchPokeBall->Update();
				if (catchPokeBall->GetWorldPos().x >= enermyPoke->pokeFront->GetWorldPos().x)
				{
					catchPokeBall->SetWorldPosX(enermyPoke->pokeFront->GetWorldPos().x);
				}
			}
			else if (catchPokeBall->GetWorldPos().x == enermyPoke->pokeFront->GetWorldPos().x)
			{
				if (TIMER->GetTick(mesTime, 0.1f))
				{
					catchPokeBall->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
					mesNum = 2;
					catchPokeBallGravi = 600.0f;//메스넘 4에서 사용 후 원래 값으로 되돌리기
				}
			}
		}
	}
	else if (mesNum == 2)
	{
		if (catchPokeBall->animState == ANIMSTATE::STOP)
		{
			SOUND->Play("BALL_CATCH");
			SOUND->Play("BALLSWAP");
			mesNum = 3;
		}
	}
	else if (mesNum == 3)
	{
		enermyPoke->pokeFront->MoveWorldPos(UP * DELTA * 800);
		if (BallInPoke(enermyPoke, ballInScale))
		{
			if (TIMER->GetTick(mesTime, 0.1f))
			{
				enermyPoke->pokeFront->SetLocalPos(Vector2(battleGround[1]->GetWorldPos().x + 875, battleGround[2]->GetWorldPos().y + 200));
				catchPokeBall->ChangeAnim(ANIMSTATE::REVERSE_ONCE, 0.1f);
				mesNum = 4;
			}
		}
	}
	else if (mesNum == 4)
	{
		catchPokeBallGravi -= DELTA * 280;
		if (ballBounce == 0)
		{
			catchPokeBall->MoveWorldPos(DOWN * DELTA * catchPokeBallGravi);
			catchPokeBall->Update();
			if (catchPokeBall->GetWorldPos().y <= enermyPoke->pokeFront->GetWorldPos().y + 30.0f)
			{
				catchPokeBall->SetWorldPosY(enermyPoke->pokeFront->GetWorldPos().y + 30.0f);
				ballBounce = 1;
				SOUND->Play("BALL_BOUNCE1");
			}
		}
		else if (ballBounce == 1)
		{
			catchPokeBall->MoveWorldPos(UP * DELTA * catchPokeBallGravi);
			catchPokeBall->Update();
			if (catchPokeBall->GetWorldPos().y >= enermyPoke->pokeFront->GetWorldPos().y + 30.0f + 120.0f)
			{
				catchPokeBall->SetWorldPosY(enermyPoke->pokeFront->GetWorldPos().y + 30.0f + 120.0f);
				ballBounce = 2;
			}
		}
		else if (ballBounce == 2)
		{
			catchPokeBall->MoveWorldPos(DOWN * DELTA * catchPokeBallGravi);
			catchPokeBall->Update();
			if (catchPokeBall->GetWorldPos().y <= enermyPoke->pokeFront->GetWorldPos().y + 30.0f)
			{
				catchPokeBall->SetWorldPosY(enermyPoke->pokeFront->GetWorldPos().y + 30.0f);
				ballBounce = 3;
				SOUND->Play("BALL_BOUNCE2");
			}
		}
		else if (ballBounce == 3)
		{
			catchPokeBall->MoveWorldPos(UP * DELTA * catchPokeBallGravi);
			catchPokeBall->Update();
			if (catchPokeBall->GetWorldPos().y >= enermyPoke->pokeFront->GetWorldPos().y + 30.0f + 60.0f)
			{
				catchPokeBall->SetWorldPosY(enermyPoke->pokeFront->GetWorldPos().y + 30.0f + 60.0f);
				ballBounce = 4;
			}
		}
		else if (ballBounce == 4)
		{
			catchPokeBall->MoveWorldPos(DOWN * DELTA * catchPokeBallGravi);
			catchPokeBall->Update();
			if (catchPokeBall->GetWorldPos().y <= enermyPoke->pokeFront->GetWorldPos().y + 30.0f)
			{
				catchPokeBall->SetWorldPosY(enermyPoke->pokeFront->GetWorldPos().y + 30.0f);
				ballBounce = 0;
				mesNum = 5;
				catchPokeBallGravi = 800.0f;
				SOUND->Play("BALL_BOUNCE3");
			}
		}
	}
	else if (mesNum == 5)//실패 성공 여부
	{
	    if (TIMER->GetTick(ballTime, 1.0f))
	    {
	    	int temp = RANDOM->Int(0, 2);//확률
	    	if (temp == 0) //성공
	    	{
				mesNum = 6;
				mesIndex = 0;
				SOUND->Stop("BATTLE");
				SOUND->Play("BALL_CAUGHT");
	    	}
	    	else // 실패
	    	{
	    		mesNum = 7;
	    		mesIndex = 0;
				catchPokeBall->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	    	}
	    }
    }
	else if (mesNum == 6) //성공
	{
	    if (catchPokeBall->color != Color(0.5f, 0.5f, 0.5f, 0.0f))
	    {
	    	ballCol -= DELTA;
	    	catchPokeBall->color = Color(0.5f, 0.5f, 0.5f, ballCol);
	    }
	    else
	    {
	    	catchPokeBall->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
	    	ballCol = 0.5f;
	    }
		if (mesIndex == battleMes.size())
		{
			if (TIMER->GetTick(ballTime, 2.0f))
			{
				mesNum = 8;
				mesIndex = 0;
				if (player->myPokemon.size() < 6)
				{
					player->myPokemon.push_back(enermyPoke->Create(enermyPoke));
				}
				else
				{
					player->myPokemon.pop_back();
					player->myPokemon.push_back(enermyPoke->Create(enermyPoke));
				}
			}
		}
    }
	else if (mesNum == 7) // 실패
	{
	    if (catchPokeBall->frame.x == 1)
	    {
			SOUND->Play("BALLSWAP");
	    }
	    if (catchPokeBall->frame.x >= 1)
	    {
			BallOutPoke(enermyPoke, ballOutScale);
		}
	    if (mesIndex == battleMes.size())
	    {
			if (TIMER->GetTick(ballTime, 1.0f))
			{
				catchPokeBall->frame.x = 0;
				mesIndex = 0;
				mesNum = 0;
				playerAttack = true;
				state = battleState::FIGHT_SECEND;
		    }
	    }
		if (catchPokeBall->animState == ANIMSTATE::STOP)
		{
			catchPokeBall->isVisible = false;
			catchPokeBall->SetLocalPosX(-600.0f);
			catchPokeBall->SetLocalPosY(0.0f); // 300에서 모션온
		}
    }
}

void Battle::CatchPokemonRander()
{
	if (mesNum == 1 || mesNum == 2 || mesNum == 3 || mesNum == 4 || mesNum == 5)
	{
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = L"원진은\n몬스터볼을　사용했다!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1))
				{
					mesIndex++;
				}
			}

			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
		}
	}
	else if (mesNum == 6 || mesNum == 8)
	{
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = L"신난다!\n"+ enermyPoke->name + L"(을)를　잡았다!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1))
				{
					mesIndex++;
				}
			}

			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
		}
	}
	else if (mesNum == 7)
	{
		{
			long leftR = 65;
			long topR = 595;
			long rightR = leftR + 1200;
			long botR = topR + 100;
			battleMes = L"으으!\n잡았다고　생각했는데!";
			if (mesIndex < battleMes.size())
			{
				if (TIMER->GetTick(mesTime, 0.1))
				{
					mesIndex++;
				}
			}

			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR, rightR + 5, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 5, rightR + 5, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 5, rightR, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 5, topR + 2, rightR + 5, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR, rightR + 2, botR }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR + 2, topR + 5, rightR + 2, botR + 5 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR + 2, rightR, botR + 2 }, 60.0f, L"Galmuri11", Color(104.0f / 255.0f, 88.0f / 255.0f, 112.0f / 255.0f, 1.0f));
			DWRITE->RenderText(battleMes.substr(0, mesIndex), RECT{ leftR, topR, rightR, botR }, 60.0f, L"Galmuri11", Color(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
		}
	}
}

void Battle::SetPokemon(Pokemon* _playerPoke, Pokemon* _enermyPoke)
{
	playerPoke = _playerPoke;
	enermyPoke = _enermyPoke;
}

bool Battle::BallOutPoke(Pokemon* _Poke, float& _ballOutScale)
{
	//_Poke->pokeBack->color = Color(1.0, 0.0f, 1.0, 0.5);
	//_Poke->pokeFront->color = Color(1.0, 0.0f, 1.0, 0.5);
	if (_Poke->pokeBack->scale.x < _Poke->pokeBack->imageSize.x * 5.0)
	{
		_Poke->pokeBack->isVisible = true;
		_Poke->pokeFront->isVisible = true;

		_ballOutScale += 3.0f * DELTA;
		_Poke->pokeBack->scale = _Poke->pokeBack->imageSize * 5.0 * _ballOutScale;
		_Poke->pokeFront->scale = _Poke->pokeBack->imageSize * 5.0 * _ballOutScale;
	}
	else
	{
		_Poke->pokeFront->scale = _Poke->pokeFront->imageSize * 5.0;
		_Poke->pokeBack->scale = _Poke->pokeBack->imageSize * 5.0;
		_ballOutScale = 0.1f;
		return true;
	}
	
	return false;
}

bool Battle::BallInPoke(Pokemon* _Poke, float& _ballInScale)
{
	if (_Poke->pokeBack->scale.x > _Poke->pokeBack->imageSize.x * 0.5f)
	{
		_ballInScale -= 3.0f * DELTA;
		_Poke->pokeBack->scale = _Poke->pokeBack->imageSize * 5.0 * _ballInScale;
		_Poke->pokeFront->scale = _Poke->pokeBack->imageSize * 5.0 * _ballInScale;

	}
	else
	{
		_Poke->pokeFront->scale = _Poke->pokeFront->imageSize * 0.5f;
		_Poke->pokeBack->scale = _Poke->pokeBack->imageSize * 0.5f;
		_Poke->pokeFront->isVisible = false;
		_Poke->pokeBack->isVisible = false;
		_ballInScale = 1.0f;
		return true;
	}
	return false;
}
