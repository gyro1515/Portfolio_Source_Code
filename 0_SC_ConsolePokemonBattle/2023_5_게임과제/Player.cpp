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
			std::cout << "�� ";
		}
		else
		{
			std::cout << "�� ";
		}
		std::cout << "* " << (*_char->skill->skillName)[i] << "   ";
	}
	std::cout << std::endl;

	for (int i = 2; i < size; i++)
	{
		if (Player::y == 1 && Player::x == i - 2)
		{
			std::cout << "�� ";
		}
		else
		{
			std::cout << "�� ";
		}
		std::cout << "* " << (*_char->skill->skillName)[i] << "   ";
	}
	std::cout << std::endl;

}

void Player::ShowYesNo()
{
	string yesNo[2] = { "��", "�ƴϿ�" };

	for (int i = 0; i < 2; i++)
	{
		if (Player::x == i)
		{
			std::cout << "�� ";
		}
		else
		{
			std::cout << "�� ";
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
	string fightOrBag[2] = { "�ο��", "����" };


	for (int i = 0; i < 2; i++)
	{
		if (Player::x == i)
		{
			std::cout << "�� ";
		}
		else
		{
			std::cout << "�� ";
		}
		std::cout << "*" << fightOrBag[i] << "   ";
	}
	std::cout << std::endl;

}

void Player::SkillEffect(float _findProperty)
{
	if (_findProperty > 1)
	{
		std::cout << "ȿ���� �����ߴ�!" << std::endl;
	}
	else if (_findProperty < 1 && _findProperty > 0)
	{
		std::cout << "ȿ���� ���ο���!" << std::endl;

	}
	else if (_findProperty <= 0)
	{
		std::cout << "ȿ���� ������!" << std::endl;

	}
}

void  Player::Fight4(Character* player, Character* com)//����4: �ο� ���� ����
{
	int input = 0;
	std::cout << "���: " << std::endl;
	com->ShowCharFight();
	std::cout << "---------------------------" << std::endl;

	std::cout << "�÷��̾�: " << std::endl;
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
void  Player::Fight6(Character* player, Character* com)//����6: ��ų ����
{
	int input = 0;
	std::cout << "���: " << std::endl;
	com->ShowCharFight();
	std::cout << "---------------------------" << std::endl;

	std::cout << "�÷��̾�: " << std::endl;
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
				std::cout << "��� ���¿����� ����� �� �ֽ��ϴ�." << std::endl;
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
				std::cout << "�Ḹ���� ��� �ش� ��ų�� ����� �� �����ϴ�.";
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
				std::cout << "�Ḹ���� ��� �ش� ��ų�� ����� �� �����ϴ�.";
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
				std::cout << "�Ḹ���� ��� �ش� ��ų�� ����� �� �����ϴ�.";
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

		std::cout << target->name << "��(��) ���߽��ϴ�." << std::endl;
	}
	
	x = 0, y = 0;
}
void  Player::Fight7(Character* player, Character* com)//����7
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
		//�Ѵ� ������� ����������� ���ǵ� ���� ĳ����
	}
	else if ((*player->skill->skillProperty)[selSkill] & SPEED)
	{
		goto PLAYER_FIRST;
	}
	else if ((*com->skill->skillProperty)[comtmp] & SPEED)
	{
		goto COM_FIRST;
	}

	if (playerSpd >= comSpd)// ���İ� üũ, �÷��̾� ����
	{
		PLAYER_FIRST:
		Player::Fight8(player, com); //�÷��̾� �� ��
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
	else //�÷��̾� �İ�
	{
		COM_FIRST:
		Player::Fight9(player, com); // �� ����
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
	if (com->name == "�Ḹ��")
	{
		if (com->hp > 0 && com->maxHp > com->hp)
		{
			::system("cls");

			std::cout << "���: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;

			std::cout << "�÷��̾�: " << std::endl;
			player->ShowCharFight();
			jam->jamItem();
			std::cout << "�Ḹ�� ������ ȿ�� �ߵ�." << std::endl;
			::system("pause");

			::system("cls");

			std::cout << "���: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;

			std::cout << "�÷��̾�: " << std::endl;
			player->ShowCharFight();
			std::cout << "ü���� ȸ���մϴ�." << std::endl;
			::system("pause");


		}
	}
	else if (player->name == "�Ḹ��")
	{
		if (player->hp > 0 && player->maxHp > player->hp)
		{
			::system("cls");

			std::cout << "���: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;

			std::cout << "�÷��̾�: " << std::endl;
			player->ShowCharFight();
			jam->jamItem();
			std::cout << "�Ḹ�� ������ ȿ�� �ߵ�." << std::endl;
			::system("pause");

			::system("cls");

			std::cout << "���: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;

			std::cout << "�÷��̾�: " << std::endl;
			player->ShowCharFight();
			std::cout << "ü���� ȸ���մϴ�." << std::endl;
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

	std::cout << "���: " << std::endl;
	com->ShowCharFight();
	std::cout << "---------------------------" << std::endl;

	std::cout << "�÷��̾�: " << std::endl;
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
		std::cout << "���: " << std::endl;
		com->ShowCharFight();
		std::cout << "---------------------------" << std::endl;
		std::cout << "�÷��̾�: " << std::endl;
		player->ShowCharFight();
		player->ShowAttack(selSkill);
		Player::Die(player, com);
		Player::SkillEffect(player->findProperty);
		if (com->characteristic == "��ĥ���Ǻ�")
		{
			han->Reflex(player);
			::system("pause");

			::system("cls");
			std::cout << "���: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;
			std::cout << "�÷��̾�: " << std::endl;
			player->ShowCharFight();
			std::cout << player->name << "�� ü���� �پ��ϴ�." << std::endl;
			Player::Die(com, player);

		}

	}

	else if (player->damage == -1)
	{
		Sleep(500);

		std::cout << "��������." << std::endl;
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
	std::cout << "���: " << std::endl;
	com->ShowCharFight();
	std::cout << "---------------------------" << std::endl;


	std::cout << "�÷��̾�: " << std::endl;
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
			std::cout << "���: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;
			std::cout << "�÷��̾�: " << std::endl;
			player->ShowCharFight();
			com->ShowAttack(com->mySkillNum);
			Player::Die(com, player);
			Player::SkillEffect(com->findProperty);
			if (player->characteristic == "��ĥ���Ǻ�")
			{

				han->Reflex(com);
				::system("pause");

				::system("cls");
				std::cout << "���: " << std::endl;
				com->ShowCharFight();
				std::cout << "---------------------------" << std::endl;
				std::cout << "�÷��̾�: " << std::endl;
				player->ShowCharFight();
				std::cout << com->name << "�� ü���� �پ��ϴ�." << std::endl;
				Player::Die(player, com);
			}
		}
		else if (com->damage == -1)
		{
			Sleep(500);

			std::cout << "��������." << std::endl;
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
			std::cout << "���: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;
			std::cout << "�÷��̾�: " << std::endl;
			player->ShowCharFight();
			com->ShowAttack(com->mySkillNum);
			Player::Die(com, player);
			Player::SkillEffect(com->findProperty);
			if (player->characteristic == "��ĥ���Ǻ�")
			{

				han->Reflex(com);
				::system("pause");

				::system("cls");
				std::cout << "���: " << std::endl;
				com->ShowCharFight();
				std::cout << "---------------------------" << std::endl;
				std::cout << "�÷��̾�: " << std::endl;
				player->ShowCharFight();
				std::cout << com->name << "�� ü���� �پ��ϴ�." << std::endl;
				Player::Die(player, com);

			}
		}
		else if (com->damage == -1)
		{
			Sleep(500);

			std::cout << "��������." << std::endl;
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
			std::cout << "���: " << std::endl;
			com->ShowCharFight();
			std::cout << "---------------------------" << std::endl;
			std::cout << "�÷��̾�: " << std::endl;
			player->ShowCharFight();
			com->ShowAttack(com->mySkillNum);
			Player::Die(com, player);
			Player::SkillEffect(com->findProperty);
			if (player->characteristic == "��ĥ���Ǻ�")
			{

				han->Reflex(com);
				::system("pause");

				::system("cls");
				std::cout << "���: " << std::endl;
				com->ShowCharFight();
				std::cout << "---------------------------" << std::endl;
				std::cout << "�÷��̾�: " << std::endl;
				player->ShowCharFight();
				std::cout << com->name << "�� ü���� �پ��ϴ�." << std::endl;
				Player::Die(player, com);

			}
		}
		else if (com->damage == -1)
		{
			Sleep(500);

			std::cout << "��������." << std::endl;
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




void Player::Start() //���⼭ �� ����
{
 
	//3. 1vs3: ���� ������ ���� ����(11: ����, 12: �ٽ� �����Ͻðڽ��ϱ�? ������ �ٽ� 0����, ��� ���� ��), ��밡 ������ ���� ���� �� ���� ���� 1ȸ ��� ����(8 -> 4-> 5-> 3), ��뿩�� �����ϸ� �ٽ� 3����, �� �̱�� �¸�
	//
	//4. 2vs2: ���� �ϳ� ������ �� ���� ���ϸ� ����(9), ��밡 ������ 3�� ����

	srand((unsigned)GetTickCount64());

	string startSel[2] = { "ĳ���� ����", "���� ����" };// ����ȭ�� ��

	string charName[4] = { "�Ḹ��", "�ֻ�", "��ī���ƽ�", "������" };//���ÿ� ���

	
	//����

	while (true)
	{
		int input = 0;

		Player::playerSpd = 0;//���� 8�� ����
		Player::comSpd = 0;
		Player::comtmp = rand() % 4; //�� ��ų ������

		//����
		::system("cls");

		switch (progress)
		{
		case 0: // ����ȭ��
			std::cout << "���������ϸ��� (��)" << std::endl;
			std::cout << "" << std::endl;
			std::cout << "" << std::endl;


			std::cout << "" << std::endl;
			std::cout << "" << std::endl;



			for (int i = 0; i < 2; i++)
			{
				if (Player::y == i)
				{
					std::cout << "�� ";
				}
				else
				{
					std::cout << "�� ";
				}
				
				std::cout << startSel[i] << std::endl;
			}
			std::cout << "" << std::endl;
			std::cout << "" << std::endl;
			std::cout << "" << std::endl;

			std::cout << "*�̵�: ����Ű, ����: z, ���: x" << std::endl;


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
		case 1: //1. ĳ����,������ ����
			std::cout << "*���ϸ� ����Ʈ*" << std::endl;
			std::cout << "---------------" << std::endl;

			jam->ShowChar();
			std::cout << "���� ��ų: " << std::endl;
			jam->ShowSkill();
			std::cout << "---------------------------------------------------------" << std::endl;
			hots->ShowChar();
			std::cout << "���� ��ų: " << std::endl;
			hots->ShowSkill();
			std::cout << "---------------------------------------------------------" << std::endl;
			han->ShowChar();
			std::cout << "���� ��ų: " << std::endl;
			han->ShowSkill();
			std::cout << "---------------------------------------------------------" << std::endl;
			mang->ShowChar();
			std::cout << "���� ��ų: " << std::endl;
			mang->ShowSkill();
			std::cout << "---------------------------------------------------------" << std::endl;
			
			std::cout << "�ڷ� ������ x�� �����ּ���.";
			input = ctrl->GetKey();
			if (input == 120)
			{
				Player::progress = 0;
			}

			break;

		case 2: //2. ĳ���� ����
			std::cout << "�÷��� �Ͻ� ���ϸ��� �������ּ���. " << std::endl;
			std::cout << "----------------------------" << std::endl;
			std::cout << std::endl;


			for (int i = 0; i < 4; i++)
			{
				if (Player::y == i)
				{
					std::cout << "�� ";
				}
				else
				{
					std::cout << "�� ";
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
		case 3: //������ ���� -> �̱���, ��ŵ�ϱ�
			std::cout << "�ʿ��� �������� �������ּ���." << std::endl;
			::system("pause");
			x = 0, y = 0;
			progress = 4;

			::system("cls");
			std::cout << "������ �����մϴ�." << std::endl;
			Sleep(500);
			break;
		case 4: //���� ���� ����
			
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
		case 5: // ���� ���ý�
			std::cout << "����� �������� �������ּ���." << std::endl;
			std::cout << "������: x" << std::endl;
			input = ctrl->GetKey();
			if (input == 120)
			{
				Player::progress = 4;
			}
			x = 0, y = 0;

			break;
		case 6: //���� ���ý�
			switch (selChar) //�� ����
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
		case 7: // ��ų ���� ��, �� �İ� ���,
			switch (selChar)//�� ����
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
		case 8:// ��ų ���� ���ϰ� ������ ���ý�: ��-> ������ ���, ��-> ����
			

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
		case 9:// ���� ��� ������ �� ���� 1ȸ ���
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
			std::cout << "�������" << std::endl;
			::system("pause");
			if (progress == 11)
			{
				break;
			}
			break;
		case 12:
			std::cout << "���� ����" << std::endl;
			::system("pause");
			if (progress == 12)
			{
				break;
			}
			break;
		}


	}
	


}