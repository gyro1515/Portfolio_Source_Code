#pragma once
class Skill
{
public:
	wstring name;
	wstring skillType;
	int dam;
	ObImage* skillImg;
	ObImage* skillTypeImg;

public:
	Skill();
	~Skill();
	virtual void OutSound();
};

class BodySlam : public Skill
{
public:
	BodySlam();
	~BodySlam();
	void OutSound();
};
class VineWhip : public Skill
{
public:
	VineWhip();
	~VineWhip();
	void OutSound();
};
class Ember : public Skill
{
public:
	Ember();
	~Ember();
	void OutSound();
};
class WaterGun : public Skill
{
public:
	WaterGun();
	~WaterGun();
	void OutSound();
};

