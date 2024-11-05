#pragma once
class Poke1 : public Pokemon
{
public:
	Poke1();
	~Poke1();
	Poke1(const Poke1& src);

	Pokemon* Create(const Pokemon* src);
	// Pokemon을(를) 통해 상속됨
	void SetPokemon();
	void OutSound();


};
class Poke2 : public Pokemon
{
public:
	Poke2();
	~Poke2();
	Poke2(const Poke2& src);

	Pokemon* Create(const Pokemon* src);
	// Pokemon을(를) 통해 상속됨
	void SetPokemon();
	void OutSound();

};
class Poke3 : public Pokemon
{
public:
	Poke3();
	~Poke3();
	Poke3(const Poke3& src);

	Pokemon* Create(const Pokemon* src);
	// Pokemon을(를) 통해 상속됨
	void SetPokemon();
	void OutSound();

};
