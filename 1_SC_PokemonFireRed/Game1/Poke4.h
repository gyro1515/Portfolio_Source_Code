#pragma once
class Poke4 : public Pokemon
{
public:
	Poke4();
	~Poke4();
	Poke4(const Poke4& src);

	// Pokemon을(를) 통해 상속됨
	void SetPokemon();
	void OutSound();
	Pokemon* Create(const Pokemon* src);

};
class Poke5 : public Pokemon
{
public:
	Poke5();
	~Poke5();
	Poke5(const Poke5& src);

	// Pokemon을(를) 통해 상속됨
	void SetPokemon();
	void OutSound();
	Pokemon* Create(const Pokemon* src);

};
class Poke6 : public Pokemon
{
public:
	Poke6();
	~Poke6();
	Poke6(const Poke6& src);

	// Pokemon을(를) 통해 상속됨
	void SetPokemon();
	void OutSound();
	Pokemon* Create(const Pokemon* src);

};

