#pragma once
class Pokemon
{
public:
	ObImage* pokeFront;
	ObImage* pokeBack;
	ObImage* pokeAni;

	wstring name;
	int maxHP;
	int hp;
	int changeHp;
	int atk;
	int def;
	int spd;
	int lv;
	int exp;
	int maxExp;
	int changeExp;
	bool pokeDie;
	bool evol;

	Skill* skill[4];


public:
	Pokemon();
	virtual ~Pokemon();
	//복사생성자 source
	Pokemon(const Pokemon& src);
	virtual Pokemon* Create(const Pokemon* src);
	virtual void SetPokemon();
	virtual void OutSound();
};

class Bulbasaur : public Pokemon
{
public:
	Bulbasaur();
	~Bulbasaur();
};

