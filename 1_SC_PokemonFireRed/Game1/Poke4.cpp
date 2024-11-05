#include "stdafx.h"

Poke4::Poke4()
{
	pokeFront = new ObImage(L"Pokemon004-1.png");
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	pokeBack = new ObImage(L"Pokemon004-2.png");
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));

	pokeAni = new ObImage(L"Pokemon004-3.png");
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));

	name = L"파이리";
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
	skill[1] = 0;
	skill[2] = 0;
	skill[3] = 0;
}

Poke4::~Poke4()
{
}

Poke4::Poke4(const Poke4& src) : Pokemon(src)
{
}

void Poke4::SetPokemon()
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
		skill[1] = new Ember();
		evol = true;
	}
}

void Poke4::OutSound()
{
	SOUND->Stop("004");
	SOUND->Play("004");
}

Pokemon* Poke4::Create(const Pokemon* src)
{
	return new Poke4(*(Poke4*)src);
}

Poke5::Poke5()
{
	pokeFront = new ObImage(L"Pokemon005-1.png");
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	pokeBack = new ObImage(L"Pokemon005-2.png");
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));

	pokeAni = new ObImage(L"Pokemon005-3.png");
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));

	name = L"리자드";
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
	evol = false;
	pokeDie = false;
	skill[0] = new BodySlam();
	skill[1] = 0;
	skill[2] = 0;
	skill[3] = 0;
}

Poke5::~Poke5()
{
}

Poke5::Poke5(const Poke5& src) : Pokemon(src)
{
}

void Poke5::SetPokemon()
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
		skill[1] = new Ember();
	}
	else if (lv >= 3)
	{
		skill[1] = new Ember();
		evol = true;
	}
}

void Poke5::OutSound()
{
	SOUND->Stop("005");
	SOUND->Play("005");
}

Pokemon* Poke5::Create(const Pokemon* src)
{
	return new Poke5(*(Poke5*)src);
}

Poke6::Poke6()
{
	pokeFront = new ObImage(L"Pokemon006-1.png");
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	pokeBack = new ObImage(L"Pokemon006-2.png");
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));

	pokeAni = new ObImage(L"Pokemon006-3.png");
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));

	name = L"리자몽";
	maxHP = 130;
	hp = maxHP;
	changeHp = hp;
	lv = 1;
	atk = 40;
	def = 40;
	spd = 40;
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

Poke6::~Poke6()
{
}

Poke6::Poke6(const Poke6& src) : Pokemon(src)
{
}

void Poke6::SetPokemon()
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
		skill[1] = new Ember();
	}
}

void Poke6::OutSound()
{
	SOUND->Stop("006");
	SOUND->Play("006");
}

Pokemon* Poke6::Create(const Pokemon* src)
{
	return new Poke6(*(Poke6*)src);
}
