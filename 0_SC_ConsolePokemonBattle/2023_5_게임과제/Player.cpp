#include "Player.h"


void Player::Move(int _move, int _xSize,int _ySize)
{
	switch (_move)
	{
	case UP:
		if (y > 0) --y;
		break;

	case DOWN:
		if (y < (_ySize - 1)) ++y;
		break;

	case LEFT:
		if (x > 0) --x;
		break;

	case RIGHT:
		if (x < (_xSize - 1)) ++x;
		break;
	}
}

void Player::ShowSkillFight(Character* _char)
{
	int size = 4;
	for (int i = 0; i < 2; i++)
	{
		if (Player::y == 0 && Player::x == i)
		{
			std::cout << "▶ ";
		}
		else
		{
			std::cout << "　 ";
		}
		std::cout << "* " << (*_char->skill->skillName)[i] << "   ";
	}
	std::cout << std::endl;

	for (int i = 2; i < size; i++)
	{
		if (Player::y == 1 && Player::x == i - 2)
		{
			std::cout << "▶ ";
		}
		else
		{
			std::cout << "　 ";
		}
		std::cout << "* " << (*_char->skill->skillName)[i] << "   ";
	}
	std::cout << std::endl;

}

void Player::ShowYesNo()
{
	string yesNo[2] = { "예", "아니요" };

	for (int i = 0; i < 2; i++)
	{
		if (Player::x == i)
		{
			std::cout << "▶ ";
		}
		else
		{
			std::cout << "　 ";
		}
		std::cout << yesNo[i] << "   ";
	}
}

void Player::SelCom()
{
	if (Player::selCom == 3)
	{
		progress = 11;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (Player::selChar == i || Player::selCom == i)
			{
				continue;
			}
			else if (Player::selCom > i)
			{
				continue;
			}
			selCom = i;
			break;
		}
	}
	
}

void Player::ShowFightOrBag()
{
	string fightOrBag[2] = { "싸운다", "가방" };


	for (int i = 0; i < 2; i++)
	{
		if (Player::x == i)
		{
			std::cout << "▶ ";
		}
		else
		{
			std::cout << "　 ";
		}
		std::cout << "*" << fightOrBag[i] << "   ";
	}
	std::cout << std::endl;

}

void Player::SkillEffect(float _findProperty)
{
	if (_findProperty > 1)
	{
		std::cout << "효과는 굉장했다!" << std::endl;
	}
	else if (_findProperty < 1 && _findProperty > 0)
	{
		std::cout << "효과는 별로였다!" << std::endl;

	}
	else if (_findProperty <= 0)
	{
		std::cout << "효과가 없었다!" << std::endl;

	}
}

void  Player::Fight4(Character* player, Character* com)//과정4: 싸움 가방 선택
{
	int input = 0;
	std::cout << "상대: " << std::endl;
	com->ShowCharFight();
	std::cout << "---------------------------" << std::endl;

	std::cout << "플레이어: " << std::endl;
	player->ShowCharFight();
	Player::ShowFightOrBag();
	input = ctrl->GetKey();
	if (input == 224)
	{
		input = ctrl->GetKey();
		Player::Move(input, 2, 1);
		Player::progress = 4;

	}
	else if (input == 122)
	{
		if (Player::x == 0)
		{
			Player::progress = 6;
		}
		else if (Player::x == 1)
		{

			Player::progress = 5;
		}
		x = 0, y = 0;

	}
}
void  Player::Fight6(Character* player, Character* com)//과정6: 스킬 선택
{
	int input = 0;
	std::cout << "상대: " << std::endl;
	com->ShowCharFight();
	std::cout << "---------------------------" << std::endl;

	std::cout << "플레이어: " << std::endl;
	player->ShowCharFight();
	Player::ShowSkillFight(player);
	input = ctrl->GetKey();
	if (input == 224)
	{
		input = ctrl->GetKey();
		Player::Move(input, 2, 2);

	}
	else if (input == 122)
	{
		if (Player::y == 0 && Player::x == 0)
		{
			if ((player->condition[0][0] & SLEEP) == FALSE && Player::selChar == 0)
			{
				std::cout << "잠듦 상태에서만 사용할 수 있습니다." << std::endl;
				Sleep(500);

				Player::progress = 6;
			}
			else
			{
				Player::selSkill = 0;
				Player::progress = 7;
			}
			
		}
		else if (Player::y == 0 && Player::x == 1)
		{
			if ((player->condition[0][0] & SLEEP))
			{
				std::cout << "잠만보가 잠들어서 해당 스킬을 사용할 수 없습니다.";
				Sleep(500);

				Player::progress = 6;
			}
			else
			{
				Player::selSkill = 1;

				Player::progress = 7;
			}
			
		}
		else if (Player::y == 1 && Player::x == 0)
		{
			if ((player->condition[0][0] & SLEEP))
			{
				std::cout << "잠만보가 잠들어서 해당 스킬을 사용할 수 없습니다.";
				Sleep(500);

				Player::progress = 6;
			}
			else
			{
				Player::selSkill = 2;

				Player::progress = 7;
			}
			
		}
		else if (Player::y == 1 && Player::x == 1)
		{
			if ((player->condition[0][0] & SLEEP))
			{
				std::cout << "잠만보가 잠들어서 해당 스킬을 사용할 수 없습니다.";
				Sleep(500);

				Player::progress = 6;
			}
			else
			{
				Player::selSkill = 3;

				Player::progress = 7;
			}
			
		}
		x = 0, y = 0;

	}
	else if (input == 120)
	{
		Player::progress = 4;
		x = 0, y = 0;

	}
}
void Player::Die(Character* attacker, Character* target)
{
	if (target->hp <= 0)
	{
		Sleep(800);

		std::cout << target->name << "이(가) 당했습니다." << std::endl;
	}
	
	x = 0, y = 0;
}
void  Player::Fight7(Character* player, Character* com)//과정7
{
	player->SetRankSpd(&player->rankSpdCount);
	player->SetRankAtk(&player->rankAtkCount);
	player->SetRankDef(&player->rankDefCount);

	com->SetRankSpd(&com->rankSpdCount);
	com->SetRankAtk(&com->rankAtkCount);
	com->SetRankDef(&com->rankDefCount);

	playerSpd = (int)(player->rankSpd * player->spd);
	comSpd = (int)(com->rankSpd * com->spd);

	if ((*player->skill->skillProperty)[selSkill] & SPEED && (*com->skill->skillProperty)[comtmp] & SPEED)
	{
		//둘다 선공기면 기존방식으로 스피드 빠른 캐릭이
	}
	else if ((*player->skill->skillProperty)[selSkill] & SPEED)
	{
		goto PLAYER_FIRST;
	}
	else if ((*com->skill->skillProperty)[comtmp] & SPEED)
	{
		goto COM_FIRST;
	}

	if (playerSpd >= comSpd)// 선후공 체크, 플래이어 선공
	{
		PLAYER_FIRST:
		Player::Fight8(player, com); //플레이어 선 공
		if (com->hp > 0)
		{
			Player::Fight9(player, com);
			progress = 4;
			if (player->hp <= 0)
			{
				progress = 12;

			}
		}
		else
		{
			progress = 4;
			Player::SelCom();
		}
	}
	else //플레이어 후공
	{
		COM_FIRST:
		Player::Fight9(player, com); // 컴 선공
		if (player->hp > 0)
		{
			Player::Fight8(player, com);
			progress = 4;
			if (com->hp <= 0)
			{
				Player::SelCom();
			}
		}
		else
		{
			progress = 12;
		}
	}
	if (com->name == "잠만보")
	{
		if (com->hp > 0 && com->maxHp > com->hp)
		{
			::system("cls");

			std::cout << "상대: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;

			std::cout << "플레이어: " << std::endl;
			player->ShowCharFight();
			jam->jamItem();
			std::cout << "잠만보 아이템 효과 발동." << std::endl;
			::system("pause");

			::system("cls");

			std::cout << "상대: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;

			std::cout << "플레이어: " << std::endl;
			player->ShowCharFight();
			std::cout << "체력을 회복합니다." << std::endl;
			::system("pause");


		}
	}
	else if (player->name == "잠만보")
	{
		if (player->hp > 0 && player->maxHp > player->hp)
		{
			::system("cls");

			std::cout << "상대: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;

			std::cout << "플레이어: " << std::endl;
			player->ShowCharFight();
			jam->jamItem();
			std::cout << "잠만보 아이템 효과 발동." << std::endl;
			::system("pause");

			::system("cls");

			std::cout << "상대: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;

			std::cout << "플레이어: " << std::endl;
			player->ShowCharFight();
			std::cout << "체력을 회복합니다." << std::endl;
			::system("pause");

		}
	}
	//if (player->hp <= 0 && Player::selCom != 3)
	//{
	//	progress = 12;
	//	Player::Die(com, player);
	//	::system("pause");
	//
	//}
	
}

void  Player::Fight8(Character* player, Character* com)
{
	::system("cls");

	std::cout << "상대: " << std::endl;
	com->ShowCharFight();
	std::cout << "---------------------------" << std::endl;

	std::cout << "플레이어: " << std::endl;
	player->ShowCharFight();
	Sleep(500);
	player->damage = player->Attack(selSkill);

	player->ShowAttack(selSkill);

	if (player->damage > 0)
	{
		Sleep(500);
		player->mySkillNum = Player::selSkill;
		player->findProperty = player->FindProperty((*player->skill->skillProperty)[player->mySkillNum], com->property);
		com->SetRankDef(&com->rankDefCount);
		com->Defense(player->damage, player);
		::system("cls");
		std::cout << "상대: " << std::endl;
		com->ShowCharFight();
		std::cout << "---------------------------" << std::endl;
		std::cout << "플레이어: " << std::endl;
		player->ShowCharFight();
		player->ShowAttack(selSkill);
		Player::Die(player, com);
		Player::SkillEffect(player->findProperty);
		if (com->characteristic == "까칠한피부")
		{
			han->Reflex(player);
			::system("pause");

			::system("cls");
			std::cout << "상대: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;
			std::cout << "플레이어: " << std::endl;
			player->ShowCharFight();
			std::cout << player->name << "의 체력이 줄어듭니다." << std::endl;
			Player::Die(com, player);

		}

	}

	else if (player->damage == -1)
	{
		Sleep(500);

		std::cout << "빗나갔다." << std::endl;
	}

	if (player->condition[0][0] & SLEEP)
	{
		if (player->condition[0][1] > 0)
		{
			player->condition[0][1]--;

		}
		else
		{
			player->condition[0][0] &= ~SLEEP;
		}
	}

	
	::system("pause");

	
}
void  Player::Fight9(Character* player, Character* com)
{
	::system("cls");
	std::cout << "상대: " << std::endl;
	com->ShowCharFight();
	std::cout << "---------------------------" << std::endl;


	std::cout << "플레이어: " << std::endl;
	player->ShowCharFight();
	Sleep(500);

	if (com->condition[0][0] & SLEEP && Player::selCom == 0)
	{
		com->damage = com->Attack(0);

		com->ShowAttack(0);

		if (com->damage > 0)
		{
			com->mySkillNum = 0;
			com->findProperty = com->FindProperty((*com->skill->skillProperty)[0], player->property);

			player->SetRankDef(&player->rankDefCount);
			player->Defense(com->damage, com);
			Sleep(500);

			::system("cls");
			std::cout << "상대: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;
			std::cout << "플레이어: " << std::endl;
			player->ShowCharFight();
			com->ShowAttack(com->mySkillNum);
			Player::Die(com, player);
			Player::SkillEffect(com->findProperty);
			if (player->characteristic == "까칠한피부")
			{

				han->Reflex(com);
				::system("pause");

				::system("cls");
				std::cout << "상대: " << std::endl;
				com->ShowCharFight();
				std::cout << "---------------------------" << std::endl;
				std::cout << "플레이어: " << std::endl;
				player->ShowCharFight();
				std::cout << com->name << "의 체력이 줄어듭니다." << std::endl;
				Player::Die(player, com);
			}
		}
		else if (com->damage == -1)
		{
			Sleep(500);

			std::cout << "빗나갔다." << std::endl;
		}
	}
	else if ((com->condition[0][0] & SLEEP) == FALSE && Player::selCom == 0)
	{
		skillTmp = rand() % 3 + 1;
		com->damage = com->Attack(skillTmp);

		com->ShowAttack(skillTmp);
		if (com->damage > 0)
		{
			com->mySkillNum = skillTmp;
			com->findProperty = com->FindProperty((*com->skill->skillProperty)[skillTmp], player->property);

			player->SetRankDef(&player->rankDefCount);
			player->Defense(com->damage, com);
			Sleep(500);

			::system("cls");
			std::cout << "상대: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;
			std::cout << "플레이어: " << std::endl;
			player->ShowCharFight();
			com->ShowAttack(com->mySkillNum);
			Player::Die(com, player);
			Player::SkillEffect(com->findProperty);
			if (player->characteristic == "까칠한피부")
			{

				han->Reflex(com);
				::system("pause");

				::system("cls");
				std::cout << "상대: " << std::endl;
				com->ShowCharFight();
				std::cout << "---------------------------" << std::endl;
				std::cout << "플레이어: " << std::endl;
				player->ShowCharFight();
				std::cout << com->name << "의 체력이 줄어듭니다." << std::endl;
				Player::Die(player, com);

			}
		}
		else if (com->damage == -1)
		{
			Sleep(500);

			std::cout << "빗나갔다." << std::endl;
		}
	}
	else
	{
		com->damage = com->Attack(comtmp);

		com->ShowAttack(comtmp);
		if (com->damage > 0)
		{
			com->mySkillNum = comtmp;
			com->findProperty = com->FindProperty((*com->skill->skillProperty)[comtmp], player->property);

			player->SetRankDef(&player->rankDefCount);
			player->Defense(com->damage, com);
			Sleep(500);

			::system("cls");
			std::cout << "상대: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;
			std::cout << "플레이어: " << std::endl;
			player->ShowCharFight();
			com->ShowAttack(com->mySkillNum);
			Player::Die(com, player);
			Player::SkillEffect(com->findProperty);
			if (player->characteristic == "까칠한피부")
			{

				han->Reflex(com);
				::system("pause");

				::system("cls");
				std::cout << "상대: " << std::endl;
				com->ShowCharFight();
				std::cout << "---------------------------" << std::endl;
				std::cout << "플레이어: " << std::endl;
				player->ShowCharFight();
				std::cout << com->name << "의 체력이 줄어듭니다." << std::endl;
				Player::Die(player, com);

			}
		}
		else if (com->damage == -1)
		{
			Sleep(500);

			std::cout << "빗나갔다." << std::endl;
		}
		
	}
	
	
	if (com->condition[0][0] & SLEEP)
	{
		if (com->condition[0][1] > 0)
		{
			com->condition[0][1]--;

		}
		else
		{
			com->condition[0][0] &= ~SLEEP;
		}
	}

	
	::system("pause");

}




void Player::Start() //여기서 다 구현
{
 
	//3. 1vs3: 내가 죽으면 게임 오버(11: 최종, 12: 다시 도전하시겠습니까? 예스면 다시 0으로, 노면 게임 끝), 상대가 죽으면 다음 전투 전 가방 무료 1회 사용 가능(8 -> 4-> 5-> 3), 사용여부 선택하면 다시 3으로, 다 이기면 승리
	//
	//4. 2vs2: 내거 하나 죽으면 내 남은 포켓몬 선택(9), 상대가 죽으면 3과 같음

	srand((unsigned)GetTickCount64());

	string startSel[2] = { "캐릭터 설명", "게임 시작" };// 시작화면 용

	string charName[4] = { "잠만보", "핫삼", "한카리아스", "망나뇽" };//선택에 사용

	
	//시작

	while (true)
	{
		int input = 0;

		Player::playerSpd = 0;//과정 8에 쓰임
		Player::comSpd = 0;
		Player::comtmp = rand() % 4; //적 스킬 무작위

		//진행
		::system("cls");

		switch (progress)
		{
		case 0: // 시작화면
			std::cout << "　　　포켓몬스터 (금)" << std::endl;
			std::cout << "" << std::endl;
			std::cout << "" << std::endl;


			std::cout << "" << std::endl;
			std::cout << "" << std::endl;



			for (int i = 0; i < 2; i++)
			{
				if (Player::y == i)
				{
					std::cout << "▶ ";
				}
				else
				{
					std::cout << "　 ";
				}
				
				std::cout << startSel[i] << std::endl;
			}
			std::cout << "" << std::endl;
			std::cout << "" << std::endl;
			std::cout << "" << std::endl;

			std::cout << "*이동: 방향키, 선택: z, 취소: x" << std::endl;


			input = ctrl->GetKey();

			if (input == 224)
			{
				input = ctrl->GetKey();
				Player::Move(input, 1, 2);

				continue;
			}
			else if (input == 122)
			{
				if (Player::y == 0)
				{
					Player::progress = 1; 
					x = 0, y = 0;
				}
				else if (Player::y == 1)
				{
					Player::progress = 2;
					x = 0, y = 0;

				}
			}

			break;
		case 1: //1. 캐릭터,아이템 설명
			std::cout << "*포켓몬 리스트*" << std::endl;
			std::cout << "---------------" << std::endl;

			jam->ShowChar();
			std::cout << "보유 스킬: " << std::endl;
			jam->ShowSkill();
			std::cout << "---------------------------------------------------------" << std::endl;
			hots->ShowChar();
			std::cout << "보유 스킬: " << std::endl;
			hots->ShowSkill();
			std::cout << "---------------------------------------------------------" << std::endl;
			han->ShowChar();
			std::cout << "보유 스킬: " << std::endl;
			han->ShowSkill();
			std::cout << "---------------------------------------------------------" << std::endl;
			mang->ShowChar();
			std::cout << "보유 스킬: " << std::endl;
			mang->ShowSkill();
			std::cout << "---------------------------------------------------------" << std::endl;
			
			std::cout << "뒤로 가려면 x를 눌러주세요.";
			input = ctrl->GetKey();
			if (input == 120)
			{
				Player::progress = 0;
			}

			break;

		case 2: //2. 캐릭터 고르기
			std::cout << "플레이 하실 포켓몬을 선택해주세요. " << std::endl;
			std::cout << "----------------------------" << std::endl;
			std::cout << std::endl;


			for (int i = 0; i < 4; i++)
			{
				if (Player::y == i)
				{
					std::cout << "▶ ";
				}
				else
				{
					std::cout << "　 ";
				}
				std::cout << "*" << charName[i] << std::endl;
				std::cout << std::endl;


			}

			input = ctrl->GetKey();
			if (input == 224)
			{
				input = ctrl->GetKey();
				Player::Move(input, 1, 4);

				continue;
			}
			else if (input == 122)
			{
				if (Player::y == 0)
				{
					Player::selChar = 0;
				}
				else if (Player::y == 1)
				{
					Player::selChar = 1;

				}
				else if (Player::y == 2)
				{
					Player::selChar = 2;

				}
				else if (Player::y == 3)
				{
					Player::selChar = 3;

				}
			}
			Player::SelCom();
			Player::progress = 4;

			x = 0, y = 0;
			


			break;
		case 3: //아이템 구매 -> 미구현, 스킵하기
			std::cout << "필요한 아이템을 구매해주세요." << std::endl;
			::system("pause");
			x = 0, y = 0;
			progress = 4;

			::system("cls");
			std::cout << "전투를 시작합니다." << std::endl;
			Sleep(500);
			break;
		case 4: //전투 가방 선택
			
			switch (selChar)
			{
			case 0:
				switch (selCom)
				{
				case 1:
					Player::Fight4(jam, hots);

					break;
				case 2:
					Player::Fight4(jam, han);

					break;
				case 3:
					Player::Fight4(jam, mang);

					break;
				}
				break;
			case 1:
				switch (selCom)
				{
				case 0:
					Player::Fight4(hots, jam);

					break;
				case 2:
					Player::Fight4(hots, han);

					break;
				case 3:
					Player::Fight4(hots, mang);

					break;
				}

				break;
			case 2:
				switch (selCom)
				{
				case 0:
					Player::Fight4(han, jam);

					break;
				case 1:
					Player::Fight4(han, hots);

					break;
				case 3:
					Player::Fight4(han, mang);

					break;
				}
				break;
			case 3:
				switch (selCom)
				{
				case 0:
					Player::Fight4(mang, jam);

					break;
				case 1:
					Player::Fight4(mang, hots);

					break;
				case 2:
					Player::Fight4(mang, han);

					break;
				}
				break;
			}


			break;
		case 5: // 가방 선택시
			std::cout << "사용할 아이템을 선택해주세요." << std::endl;
			std::cout << "나가기: x" << std::endl;
			input = ctrl->GetKey();
			if (input == 120)
			{
				Player::progress = 4;
			}
			x = 0, y = 0;

			break;
		case 6: //전투 선택시
			switch (selChar) //나 선택
			{
			case 0:
				switch (selCom)
				{
				case 1:
					Player::Fight6(jam, hots);

					break;
				case 2:
					Player::Fight6(jam, han);

					break;
				case 3:
					Player::Fight6(jam, mang);

					break;
				}
				break;
			case 1:
				switch (selCom)
				{
				case 0:
					Player::Fight6(hots, jam);

					break;
				case 2:
					Player::Fight6(hots, han);

					break;
				case 3:
					Player::Fight6(hots, mang);

					break;
				}

				break;
			case 2:
				switch (selCom)
				{
				case 0:
					Player::Fight6(han, jam);

					break;
				case 1:
					Player::Fight6(han, hots);

					break;
				case 3:
					Player::Fight6(han, mang);

					break;
				}
				break;
			case 3:
				switch (selCom)
				{
				case 0:
					Player::Fight6(mang, jam);

					break;
				case 1:
					Player::Fight6(mang, hots);

					break;
				case 2:
					Player::Fight6(mang, han);

					break;
				}
				break;
			}

			
			break;
		case 7: // 스킬 선택 후, 선 후공 계산,
			switch (selChar)//나 선택
			{
			case 0:
				switch (selCom)
				{
				case 1:
					Player::Fight7(jam, hots);

					break;
				case 2:
					Player::Fight7(jam, han);

					break;
				case 3:
					Player::Fight7(jam, mang);

					break;
				}
				break;
			case 1:
				switch (selCom)
				{
				case 0:
					Player::Fight7(hots, jam);

					break;
				case 2:
					Player::Fight7(hots, han);

					break;
				case 3:
					Player::Fight7(hots, mang);

					break;
				}

				break;
			case 2:
				switch (selCom)
				{
				case 0:
					Player::Fight7(han, jam);

					break;
				case 1:
					Player::Fight7(han, hots);

					break;
				case 3:
					Player::Fight7(han, mang);

					break;
				}
				break;
			case 3:
				switch (selCom)
				{
				case 0:
					Player::Fight7(mang, jam);

					break;
				case 1:
					Player::Fight7(mang, hots);

					break;
				case 2:
					Player::Fight7(mang, han);

					break;
				}
				break;
			}
			x = 0, y = 0;
			break;
		case 8:// 스킬 선택 안하고 아이템 선택시: 나-> 아이템 사용, 컴-> 공격
			

			switch (selChar)
			{
			case 0:

				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}


			break;
		case 9:// 다음 상대 만나기 전 가방 1회 사용
			switch (selChar)
			{
			case 0:

				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}

			break;
		case 10:
			switch (selChar)
			{
			case 0:

				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
			break;

		case 11:
			std::cout << "최종우승" << std::endl;
			::system("pause");
			if (progress == 11)
			{
				break;
			}
			break;
		case 12:
			std::cout << "게임 오버" << std::endl;
			::system("pause");
			if (progress == 12)
			{
				break;
			}
			break;
		}


	}
	


}