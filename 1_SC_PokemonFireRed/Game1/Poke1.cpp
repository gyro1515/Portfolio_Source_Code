#include "stdafx.h"

Poke1::Poke1()
{
	pokeFront = new ObImage(L"Pokemon001.png");
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	pokeBack = new ObImage(L"Pokemon001-1.png");
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));

	pokeAni = new ObImage(L"Pokemon001-2.png");
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));

	name = L"이상해씨";
	maxHP = 100;
	hp = maxHP;
	changeHp = hp;
	lv = 1;
	atk = 20;
	def = 20;
	spd = 20;
	exp = 0;
	changeExp = 0;
	evol = false;
	pokeDie = false;
	maxExp = lv * 50;
	skill[0] = new BodySlam();
}

Poke1::~Poke1()
{
}

Poke1::Poke1(const Poke1& src) : Pokemon(src)
{
}

Pokemon* Poke1::Create(const Pokemon* src)
{
	return new Poke1(*(Poke1*)src);
}

void Poke1::SetPokemon()
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
		skill[1] = new VineWhip();
		evol = true;
	}
}

void Poke1::OutSound()
{
	SOUND->Stop("001");
	SOUND->Play("001");
}

Poke2::Poke2()
{
	pokeFront = new ObImage(L"Pokemon002-1.png");
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	pokeBack = new ObImage(L"Pokemon002-2.png");
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));

	pokeAni = new ObImage(L"Pokemon002-3.png");
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));

	name = L"이상해풀";
	maxHP = 110;
	hp = maxHP;
	changeHp = hp;
	lv = 1;
	atk = 30;
	def = 30;
	spd = 30;
	exp = 0;
	changeExp = 0;
	evol = false;
	pokeDie = false;
	maxExp = lv * 50;
	skill[0] = new BodySlam();
	skill[1] = 0;
	skill[2] = 0;
	skill[3] = 0;
}

Poke2::~Poke2()
{
}

Poke2::Poke2(const Poke2& src) : Pokemon(src)
{
}

Pokemon* Poke2::Create(const Pokemon* src)
{
	return new Poke2(*(Poke2*)src);
}

void Poke2::SetPokemon()
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
		skill[1] = new VineWhip();
	}
	else if (lv >= 3)
	{
		skill[1] = new VineWhip();
		evol = true;
	}
}

void Poke2::OutSound()
{
	SOUND->Stop("002");
	SOUND->Play("002");
}

Poke3::Poke3()
{
	pokeFront = new ObImage(L"Pokemon003-1.png");
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	pokeBack = new ObImage(L"Pokemon003-2.png");
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));

	pokeAni = new ObImage(L"Pokemon003-3.png");
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));

	name = L"이상해꽃";
	maxHP = 130;
	hp = maxHP;
	changeHp = hp;
	lv = 1;
	atk = 40;
	def = 40;
	spd = 40;
	exp = 0;
	changeExp = 0;
	maxExp = lv * 50;
	evol = false;
	pokeDie = false;
	skill[0] = new BodySlam();
	skill[1] = 0;
	skill[2] = 0;
	skill[3] = 0;
}

Poke3::~Poke3()
{
}

Poke3::Poke3(const Poke3& src) : Pokemon(src)
{
}

Pokemon* Poke3::Create(const Pokemon* src)
{
	return new Poke3(*(Poke3*)src);
}

void Poke3::SetPokemon()
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
	atk = 40 + (lv-1) * 4;
	def = 40 + (lv-1) * 4;
	spd = 40 + (lv-1) * 4;
	maxExp = lv * 50;
	if (lv >= 2)
	{
		skill[1] = new VineWhip();
	}
}

void Poke3::OutSound()
{
	SOUND->Stop("003");
	SOUND->Play("003");
}
