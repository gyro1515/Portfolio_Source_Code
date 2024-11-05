#include "stdafx.h"
Poke7::Poke7()
{
	pokeFront = new ObImage(L"Pokemon007-1.png");
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	pokeBack = new ObImage(L"Pokemon007-2.png");
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));

	pokeAni = new ObImage(L"Pokemon007-3.png");
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));

	name = L"²¿ºÎ±â";
	maxHP = 100;
	hp = maxHP;
	changeHp = hp;
	lv = 1;
	atk = 20;
	def = 20;
	spd = 20;
	exp = 0;
	changeExp = 0;
	maxExp = lv * 50;
	pokeDie = false;
	evol = false;


	skill[0] = new BodySlam();
	skill[1] = 0;
	skill[2] = 0;
	skill[3] = 0;
}

Poke7::~Poke7()
{
}

Poke7::Poke7(const Poke7& src) : Pokemon(src)
{

}

void Poke7::SetPokemon()
{
	if (hp == maxHP)
	{
		maxHP = 100 + (lv - 1) * 5;
		hp = maxHP;
	}
	else
	{
		maxHP = 100 + (lv - 1) * 5;
		hp += 5;
	}
	changeHp = hp;

	atk = 20 + (lv-1) * 2;
	def = 20 + (lv-1) * 2;
	spd = 20 + (lv-1) * 2;
	maxExp = lv * 50;
	if (lv >= 2)
	{
		evol = true;
		skill[1] = new WaterGun();
	}
}

void Poke7::OutSound()
{
	SOUND->Stop("007");
	SOUND->Play("007");
}

Pokemon* Poke7::Create(const Pokemon* src)
{
	return new Poke7(*(Poke7*)src);
}

Poke8::Poke8()
{
	pokeFront = new ObImage(L"Pokemon008-1.png");
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	pokeBack = new ObImage(L"Pokemon008-2.png");
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));

	pokeAni = new ObImage(L"Pokemon008-3.png");
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));

	name = L"¾î´ÏºÎ±â";
	maxHP = 110;
	hp = maxHP;
	changeHp = hp;
	lv = 1;
	atk = 30;
	def = 30;
	spd = 30;
	exp = 0;
	changeExp = 0;
	maxExp = lv * 50;
	pokeDie = false;
	evol = false;


	skill[0] = new BodySlam();
	skill[1] = 0;
	skill[2] = 0;
	skill[3] = 0;
}

Poke8::~Poke8()
{
}

Poke8::Poke8(const Poke8& src) : Pokemon(src)
{
}

void Poke8::SetPokemon()
{
	if (hp == maxHP)
	{
		maxHP = 110 + (lv - 1) * 7;
		hp = maxHP;
	}
	else
	{
		maxHP = 110 + (lv - 1) * 7;
		hp += 7;
	}
	changeHp = hp;

	atk = 30 + (lv-1) * 3;
	def = 30 + (lv-1) * 3;
	spd = 30 + (lv-1) * 3;
	maxExp = lv * 50;
	if (lv == 2)
	{
		skill[1] = new WaterGun();
	}
	else if (lv >= 3)
	{
		skill[1] = new WaterGun();
		evol = true;
	}
}

void Poke8::OutSound()
{
	SOUND->Stop("008");
	SOUND->Play("008");
}

Pokemon* Poke8::Create(const Pokemon* src)
{
	return new Poke8(*(Poke8*)src);
}

Poke9::Poke9()
{
	pokeFront = new ObImage(L"Pokemon009-1.png");
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	pokeBack = new ObImage(L"Pokemon009-2.png");
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));

	pokeAni = new ObImage(L"Pokemon009-3.png");
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));

	name = L"°ÅºÏ¿Õ";
	maxHP = 130;
	hp = maxHP;
	changeHp = hp;
	lv = 1;
	atk = 40;
	def = 40;
	spd = 40;
	exp = 0;
	changeExp = 0;
	pokeDie = false;
	maxExp = lv * 50;
	evol = false;

	skill[0] = new BodySlam();
	skill[1] = 0;
	skill[2] = 0;
	skill[3] = 0;
}

Poke9::~Poke9()
{
}

Poke9::Poke9(const Poke9& src) : Pokemon(src)
{
}

void Poke9::SetPokemon()
{
	if (hp == maxHP)
	{
		maxHP = 130 + (lv - 1) * 10;
		hp = maxHP;
	}
	else
	{
		maxHP = 130 + (lv - 1) * 10;
		hp += 10;
	}
	changeHp = hp;
	atk = 40 + (lv - 1) * 4;
	def = 40 + (lv - 1) * 4;
	spd = 40 + (lv - 1) * 4;
	maxExp = lv * 50;
	if (lv >= 2)
	{
		skill[1] = new WaterGun();
	}
}

void Poke9::OutSound()
{
	SOUND->Stop("009");
	SOUND->Play("009");
}

Pokemon* Poke9::Create(const Pokemon* src)
{
	return new Poke9(*(Poke9*)src);
}

Poke143::Poke143()
{
	pokeFront = new ObImage(L"Pokemon143-1.png");
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	pokeBack = new ObImage(L"Pokemon143-2.png");
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));

	pokeAni = new ObImage(L"Pokemon143-3.png");
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));

	name = L"Àá¸¸º¸";
	maxHP = 150;
	hp = maxHP;
	changeHp = hp;
	lv = 1;
	atk = 50;
	def = 50;
	spd = 50;
	exp = 0;
	changeExp = 0;
	maxExp = lv * 50;
	pokeDie = false;
	evol = false;

	skill[0] = new BodySlam();
	skill[1] = 0;
	skill[2] = 0;
	skill[3] = 0;
}

Poke143::~Poke143()
{
}

Poke143::Poke143(const Poke143& src) : Pokemon(src)
{
}

void Poke143::SetPokemon()
{
	if (hp == maxHP)
	{
		maxHP = 150 + (lv - 1) * 15;
		hp = maxHP;
	}
	else
	{
		maxHP = 150 + (lv - 1) * 15;
		hp += 15;
	}
	changeHp = hp;
	atk = 50 + (lv - 1) * 5;
	def = 50 + (lv - 1) * 5;
	spd = 50 + (lv - 1) * 5;
	maxExp = lv * 50;
	//maxHP = 150 + (lv - 1) * 15;
	//hp += 15;
	//if (hp > maxHP)
	//{
	//	hp = maxHP;
	//}
	//changeHp = hp;
	//
	//atk = 50 + (lv - 1) * 5;
	//def = 50 + (lv - 1) * 5;
	//spd = 50 + (lv - 1) * 5;
	//maxExp = lv * 50;
	if (lv == 2)
	{
		skill[1] = new WaterGun();
	}
	else if (lv == 3)
	{
		skill[1] = new WaterGun();
		skill[2] = new Ember();

	}
	if (lv >= 4)
	{
		skill[1] = new WaterGun();
		skill[2] = new Ember();
		skill[3] = new VineWhip();
	}
	
}

void Poke143::OutSound()
{
	SOUND->Stop("143");
	SOUND->Play("143");
}

Pokemon* Poke143::Create(const Pokemon* src)
{
	return new Poke143(*(Poke143*)src);
}
