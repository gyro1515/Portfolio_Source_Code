#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

//포켓몬 속성, 스킬
#define NORMAL 1 	 //0x1
#define FIRE 2		 //0x2
#define WATER 4		 //0x4
#define ELECTIRC 8	 //0x8
#define GRASS 16	 //0x10
#define ICE 32		 //0x20
#define FIGHTING 64	 //0x40
#define POISON 128	 //0x80
#define GROUND 256	 //0x100
#define FLYING 512	 //0x200
#define PSYCHIC 1024 //0x400
#define BUG 2048	 //0x800
#define ROCK 4096	 //0x1000
#define GHOST 8192	 //0x2000
#define DRAGON 16384 //0x4000
#define DARK 32768	 //0x8000
#define STEEL 65536	 //0x10000
#define SPEED 131072 //0x20000

class Status
{
private:
	
	

protected:

public:
	int hp;
	int atk;
	int def;
	int spd;
	std::string name;

	Status()
	{
		hp = 0;
		atk = 0;
		def = 0;
		spd = 0;
		name = "없음";

	}
	void SetName(string _name) { name = _name; }
	void SetHp(int _hp) { hp = _hp; };
	void SetAtk(int _atk) { atk = _atk; };
	void SetDef(int _def) { def = _def; };
	void SetSpd(int _spd) { spd = _spd; };
	string GetName() { return name; }
	int GetHp() { return hp; };
	int GetAtk() { return atk; };
	int GetDef() { return def; };
	int GetSpd() { return spd ; };


};

