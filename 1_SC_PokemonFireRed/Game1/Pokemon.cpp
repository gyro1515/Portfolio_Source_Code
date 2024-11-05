#include "stdafx.h"

Pokemon::Pokemon()
{
	pokeFront = NULL;
	pokeBack = NULL;
	pokeAni = NULL;

	name = L"";
	maxHP = 0;
	hp = 0;
	changeHp = 0;
	atk = 0;
	def = 0;
	spd = 0;
	lv = 0;
	exp = 0;
	maxExp = 0;
	changeExp = 0;
	pokeDie = false;
	evol = false;
}

Pokemon::~Pokemon()
{
}

Pokemon::Pokemon(const Pokemon& src)
{
	pokeFront = new ObImage(src.pokeFront->file);   //pokeFront;
	pokeFront->scale = pokeFront->imageSize * 5;
	pokeFront->pivot = OFFSET_B;
	pokeFront->SetWorldPos(Vector2(1400, 600));
	//pokeFront->Update();
	pokeBack = new ObImage(src.pokeBack->file);
	pokeBack->scale = pokeBack->imageSize * 5;
	pokeBack->pivot = OFFSET_B;
	pokeBack->SetWorldPos(Vector2(1400, 600));
	//pokeBack->Update();

	pokeAni = new ObImage(src.pokeAni->file);
	pokeAni->maxFrame.x = 2;
	pokeAni->scale.x = pokeAni->imageSize.x / 2 * 5;
	pokeAni->scale.y = pokeAni->imageSize.y * 5;
	pokeAni->SetWorldPos(Vector2(1200, 600));
	//pokeAni->Update();

	name = src.name;
	maxHP = src.maxHP;
	hp = src.hp;
	changeHp = src.changeHp;
	lv = src.lv;
	atk = src.atk;
	def = src.def;
	spd = src.spd;
	exp = src.exp;
	changeExp = src.changeExp;
	maxExp = src.maxExp;

	skill[0] = src.skill[0];
	skill[1] = src.skill[1];
	skill[2] = src.skill[2];
	skill[3] = src.skill[3];
}

Pokemon* Pokemon::Create(const Pokemon* src)
{
	return new Pokemon(*src);
}

void Pokemon::SetPokemon()
{

}

void Pokemon::OutSound()
{
	
}

Bulbasaur::Bulbasaur()
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

	name = L"ÀÌ»óÇØ¾¾";
	maxHP = 100;
	hp = maxHP;
	atk = 20;
	def = 20;
	spd = 20;
}

Bulbasaur::~Bulbasaur()
{
}
