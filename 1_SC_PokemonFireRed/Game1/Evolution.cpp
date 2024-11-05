#include "stdafx.h"

void Evolution::Init()
{
	LIGHT->light.select.x = 0.0f;
	LIGHT->light.lights[1].radius = 0.0f;
	LIGHT->light.lights[0].radius = 1000.0f;
	CAM->position = Vector2(0.0f, 0.0f);
	battleGround[0] = new ObImage(L"Battle Backgrounds2-1.png");
	battleGround[0]->scale = battleGround[0]->imageSize * 5;
	battleGround[1] = new ObImage(L"HP Bars & In-battle Menu6.png");
	battleGround[1]->scale = battleGround[1]->imageSize * 5;
	backCol = 0.5f;
	pokeCol = 0.5f;
	bsCount = 1;
	bsScale1 = 0.0f; //0부터
	bsScale2 = 1.0f;; // 1부터
	for (int i = 0; i < 2; i++)
	{
		battleGround[i]->pivot = OFFSET_LB;
	}
	battleGround[0]->SetWorldPosX(-app.GetHalfWidth());
	battleGround[0]->SetWorldPosY(app.GetHalfHeight() - battleGround[0]->imageSize.y * 5);
	battleGround[1]->SetWorldPosX(-app.GetHalfWidth());
	battleGround[1]->SetWorldPosY(app.GetHalfHeight() - battleGround[1]->imageSize.y * 5 - battleGround[0]->imageSize.y * 5);

	//배틀 메세지
	battleMes = L"";
	mesNum = -1;
	mesIndex = 0;
	mesTime = 0.0f;
	//조명
	lightCol = 0.0f;
	lightTime = 0.0f;
	fadeIn = true;
	fadeOut = false;

	//포켓몬 세팅
	player->myPokemon[player->myPokemonNum]->pokeFront->isVisible = true;
	player->myPokemon[player->myPokemonNum]->pokeFront->pivot = OFFSET_N;
	player->myPokemon[player->myPokemonNum]->pokeFront->SetLocalPos(Vector2(0.0f, 90.0f));
	
	if (player->myPokemon[player->myPokemonNum]->name == L"이상해씨")
	{
		evolPoke = new Poke2();
		evolPoke->lv = player->myPokemon[player->myPokemonNum]->lv;
		evolPoke->SetPokemon();
		evolPoke->hp = player->myPokemon[player->myPokemonNum]->hp;
		evolPoke->changeHp = player->myPokemon[player->myPokemonNum]->changeHp;
		evolPoke->exp = player->myPokemon[player->myPokemonNum]->exp;
		evolPoke->changeExp = player->myPokemon[player->myPokemonNum]->changeExp;
	}
	else if (player->myPokemon[player->myPokemonNum]->name == L"이상해풀")
	{
		evolPoke = new Poke3();
		evolPoke->lv = player->myPokemon[player->myPokemonNum]->lv;
		evolPoke->SetPokemon();
		evolPoke->hp = player->myPokemon[player->myPokemonNum]->hp;
		evolPoke->changeHp = player->myPokemon[player->myPokemonNum]->changeHp;
		evolPoke->exp = player->myPokemon[player->myPokemonNum]->exp;
		evolPoke->changeExp = player->myPokemon[player->myPokemonNum]->changeExp;
	}
	else if (player->myPokemon[player->myPokemonNum]->name == L"파이리")
	{
		evolPoke = new Poke5();
		evolPoke->lv = player->myPokemon[player->myPokemonNum]->lv;
		evolPoke->SetPokemon();
		evolPoke->hp = player->myPokemon[player->myPokemonNum]->hp;
		evolPoke->changeHp = player->myPokemon[player->myPokemonNum]->changeHp;
		evolPoke->exp = player->myPokemon[player->myPokemonNum]->exp;
		evolPoke->changeExp = player->myPokemon[player->myPokemonNum]->changeExp;
	}
	else if (player->myPokemon[player->myPokemonNum]->name == L"리자드")
	{
		evolPoke = new Poke6();
		evolPoke->lv = player->myPokemon[player->myPokemonNum]->lv;
		evolPoke->SetPokemon();
		evolPoke->hp = player->myPokemon[player->myPokemonNum]->hp;
		evolPoke->changeHp = player->myPokemon[player->myPokemonNum]->changeHp;
		evolPoke->exp = player->myPokemon[player->myPokemonNum]->exp;
		evolPoke->changeExp = player->myPokemon[player->myPokemonNum]->changeExp;
	}
	else if (player->myPokemon[player->myPokemonNum]->name == L"꼬부기")
	{
		evolPoke = new Poke8();
		evolPoke->lv = player->myPokemon[player->myPokemonNum]->lv;
		evolPoke->SetPokemon();
		evolPoke->hp = player->myPokemon[player->myPokemonNum]->hp;
		evolPoke->changeHp = player->myPokemon[player->myPokemonNum]->changeHp;
		evolPoke->exp = player->myPokemon[player->myPokemonNum]->exp;
		evolPoke->changeExp = player->myPokemon[player->myPokemonNum]->changeExp;
	}
	else if (player->myPokemon[player->myPokemonNum]->name == L"어니부기")
	{
		evolPoke = new Poke9();
		evolPoke->lv = player->myPokemon[player->myPokemonNum]->lv;
		evolPoke->SetPokemon();
		evolPoke->hp = player->myPokemon[player->myPokemonNum]->hp;
		evolPoke->changeHp = player->myPokemon[player->myPokemonNum]->changeHp;
		evolPoke->exp = player->myPokemon[player->myPokemonNum]->exp;
		evolPoke->changeExp = player->myPokemon[player->myPokemonNum]->changeExp;
	}
	evolPoke->pokeFront->isVisible = false;
	evolPoke->pokeFront->pivot = OFFSET_N;
	evolPoke->pokeFront->scale = Vector2(0.0f, 0.0f);
	evolPoke->pokeFront->SetLocalPos(Vector2(0.0f, 90.0f));
}

void Evolution::Release()
{
	for (int i = 0; i < 2; i++)
	{
		SafeDelete(battleGround[i]);
	}
}

void Evolution::Update()
{
	if (fadeIn == true)
	{
		lightCol += 1.5f * DELTA;
		if (lightCol >= 0.5f)
		{
			lightCol = 0.5f;
			fadeIn = false;
			mesNum = 0;
		}
		LIGHT->light.inColor = Color(lightCol, lightCol, lightCol, 0.5f);

	}
	else
	{
		Evol();
		if (mesNum == 5)
		{
			if (TIMER->GetTick(mesTime, 1.5f))
			{
				mesNum = 0;
				mesIndex = 0;
				player->myPokemon.erase(player->myPokemon.begin() + player->myPokemonNum);
				player->myPokemon.insert(player->myPokemon.begin() + player->myPokemonNum, evolPoke);
				player->myPokemon[player->myPokemonNum]->pokeFront->isVisible = false;
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
			
		}
	}
	for (int i = 0; i < 2; i++)
	{
		battleGround[i]->Update();
	}
	player->myPokemon[player->myPokemonNum]->pokeFront->Update();
	evolPoke->pokeFront->Update();

}

void Evolution::LateUpdate()
{
}

void Evolution::Render()
{
	for (int i = 0; i < 2; i++)
	{
		battleGround[i]->Render();
	}
	player->myPokemon[player->myPokemonNum]->pokeFront->Render();
	evolPoke->pokeFront->Render();
	EvolRander();

}

void Evolution::ResizeScreen()
{
}

void Evolution::Evol()
{
	if (mesNum == 0)
	{
		if (mesIndex == battleMes.size())
		{
			if (battleGround[0]->color != Color(0.0f, 0.0f, 0.0f, 0.5f))
			{
				backCol -= DELTA;
				if (backCol <= 0.0f)
				{
					backCol = 0.0f;
				}
				battleGround[0]->color = Color(backCol, backCol, backCol, 0.5f);
			}
			else if (player->myPokemon[player->myPokemonNum]->pokeFront->color != Color(1.0f, 1.0f, 1.0f, 0.5f))
			{
				pokeCol += DELTA;
				if (pokeCol >= 1.0f)
				{
					pokeCol = 1.0f;
				}
				player->myPokemon[player->myPokemonNum]->pokeFront->color = Color(pokeCol, pokeCol, pokeCol, 0.5f);
				evolPoke->pokeFront->color = Color(pokeCol, pokeCol, pokeCol, 0.5f);

			}
			else if (bsCount < 10)
			{
				evolPoke->pokeFront->isVisible = true;

				if (evolPoke->pokeFront->scale != evolPoke->pokeFront->imageSize * 5.0f)
				{
					bsScale1 += DELTA * bsCount;
					if (bsScale1 >= 1.0f)
					{
						bsScale1 = 1.0f;
					}
					bsScale2 -= DELTA * bsCount;
					if (bsScale2 <= 0.0f)
					{
						bsScale2 = 0.0f;
					}
					evolPoke->pokeFront->scale = evolPoke->pokeFront->imageSize * 5.0f * bsScale1;
					player->myPokemon[player->myPokemonNum]->pokeFront->scale = player->myPokemon[player->myPokemonNum]->pokeFront->imageSize * 5.0f * bsScale2;
				}
				else
				{
					mesNum = 1;
				}
			}
			else if (bsCount == 10)
			{
				if (evolPoke->pokeFront->scale != evolPoke->pokeFront->imageSize * 5.0f)
				{
					bsScale1 += DELTA * bsCount;
					if (bsScale1 >= 1.0f)
					{
						bsScale1 = 1.0f;
					}
					bsScale2 -= DELTA * bsCount;
					if (bsScale2 <= 0.0f)
					{
						bsScale2 = 0.0f;
					}
					evolPoke->pokeFront->scale = evolPoke->pokeFront->imageSize * 5.0f * bsScale1;
					player->myPokemon[player->myPokemonNum]->pokeFront->scale = player->myPokemon[player->myPokemonNum]->pokeFront->imageSize * 5.0f * bsScale2;
				}
				else
				{
					mesNum = 2;
				}
			}
		}
	}
	else if (mesNum == 1)
	{
		if (player->myPokemon[player->myPokemonNum]->pokeFront->scale != player->myPokemon[player->myPokemonNum]->pokeFront->imageSize * 5.0f)
		{
			bsScale2 += DELTA * bsCount;
			if (bsScale2 >= 1.0f)
			{
				bsScale2 = 1.0f;
			}
			bsScale1 -= DELTA * bsCount;
			if (bsScale1 <= 0.0f)
			{
				bsScale1 = 0.0f;
			}
			
			evolPoke->pokeFront->scale = evolPoke->pokeFront->imageSize * 5.0f * bsScale1;
			player->myPokemon[player->myPokemonNum]->pokeFront->scale = player->myPokemon[player->myPokemonNum]->pokeFront->imageSize * 5.0f * bsScale2;
		}
		else
		{
			bsCount++;
			mesNum = 0;
		}
	}
	else if (mesNum == 2)
	{
		if (battleGround[0]->color != Color(1.0f, 1.0f, 1.0f, 0.5f))
		{
			
			backCol += 2.0f * DELTA;
			if (backCol >= 1.0f)
			{
				backCol = 1.0f;
			}
			battleGround[0]->color = Color(backCol, backCol, backCol, 0.5f);
		}
		else
		{
			mesNum = 3;
		}
	}
	else if (mesNum == 3)
	{
	    if (battleGround[0]->color != Color(0.5f, 0.5f, 0.5f, 0.5f))
	    {
	    	backCol -= DELTA;
	    	if (backCol <= 0.5f)
	    	{
	    		backCol = 0.5f;
	    	}
	    	battleGround[0]->color = Color(backCol, backCol, backCol, 0.5f);
	    }
		else if (evolPoke->pokeFront->color != Color(0.5f, 0.5f, 0.5f, 0.5f))
		{
			pokeCol -= DELTA;
			if (pokeCol <= 0.5f)
			{
				pokeCol = 0.5f;
			}
			evolPoke->pokeFront->color = Color(pokeCol, pokeCol, pokeCol, 0.5f);
		}
		else
		{
			SOUND->Stop("EVO1");
			SOUND->Play("EVO2");
			mesNum = 4;
			mesIndex = 0;
		}
	}
	else if (mesNum == 4)
	{
	    if (mesIndex == battleMes.size())
	       {
	    	mesNum = 5;
	    	}
    }
}

void Evolution::EvolRander()
{
	if (mesNum == 0 || mesNum == 1 || mesNum == 2 || mesNum == 3)
	{
		long leftR = 65;
		long topR = 595;
		long rightR = leftR + 1200;
		long botR = topR + 100;
		battleMes = L"……어라!?\n" + player->myPokemon[player->myPokemonNum]->name + L"의　모습이……!";
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
	else if (mesNum == 4 || mesNum == 5)
	{
		long leftR = 65;
		long topR = 595;
		long rightR = leftR + 1200;
		long botR = topR + 100;
		battleMes = L"축하합니다!　" + player->myPokemon[player->myPokemonNum]->name + L"(은)는\n" + evolPoke->name + L"(으)로　진화했다!";
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
