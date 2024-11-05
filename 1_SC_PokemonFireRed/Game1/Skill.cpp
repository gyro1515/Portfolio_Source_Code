#include "stdafx.h"

Skill::Skill()
{
	name = L"";
	skillType = L"";
	dam = 0;
	skillImg = 0;
	skillTypeImg = 0;
}

Skill::~Skill()
{
}

void Skill::OutSound()
{
}

BodySlam::BodySlam()
{
	name = L"¸öÅë¹ÚÄ¡±â";
	skillType = L"³ë¸Ö";
	dam = 30;
	skillImg = new ObImage(L"AttackEffects4.png");
	skillImg->scale = skillImg->imageSize * 5.0f;
	skillImg->scale.x /= 5;
	skillImg->pivot = OFFSET_B;
	skillImg->maxFrame.x = 5;

	skillTypeImg = new ObImage(L"Type Status Icons2.png");
	skillTypeImg->scale = skillTypeImg->imageSize * 5.0f;
	skillTypeImg->pivot = OFFSET_B;
}

BodySlam::~BodySlam()
{

}

void BodySlam::OutSound()
{
	SOUND->SetVolume("NORMAL", 2.0f);
	SOUND->Stop("NORMAL");
	SOUND->Play("NORMAL");
}

VineWhip::VineWhip()
{
	name = L"µ¢±¼Ã¤Âï";
	skillType = L"Ç®";
	dam = 50;
	skillImg = new ObImage(L"AttackEffects1.png");
	skillImg->scale = skillImg->imageSize * 5.0f;
	skillImg->scale.x /= 5;
	skillImg->pivot = OFFSET_B;
	skillImg->maxFrame.x = 5;

	skillTypeImg = new ObImage(L"Type Status Icons5.png");
	skillTypeImg->scale = skillTypeImg->imageSize * 5.0f;
	skillTypeImg->pivot = OFFSET_B;
}

VineWhip::~VineWhip()
{
}

void VineWhip::OutSound()
{
	SOUND->SetVolume("GRASS", 2.0f);
	SOUND->Stop("GRASS");
	SOUND->Play("GRASS");
}

Ember::Ember()
{
	name = L"ºÒ²É¼¼·Ê";
	skillType = L"ºÒ";
	dam = 50;
	skillImg = new ObImage(L"AttackEffects3.png");
	skillImg->scale = skillImg->imageSize * 5.0f;
	skillImg->scale.x /= 9;
	skillImg->pivot = OFFSET_B;
	skillImg->maxFrame.x = 9;

	skillTypeImg = new ObImage(L"Type Status Icons3.png");
	skillTypeImg->scale = skillTypeImg->imageSize * 5.0f;
	skillTypeImg->pivot = OFFSET_B;
}

Ember::~Ember()
{
}

void Ember::OutSound()
{
	SOUND->SetVolume("FIRE", 2.0f);
	SOUND->Stop("FIRE");
	SOUND->Play("FIRE");
}

WaterGun::WaterGun()
{
	name = L"¹°´ëÆ÷";
	skillType = L"¹°";
	dam = 50;
	skillImg = new ObImage(L"AttackEffects2.png");
	skillImg->scale = skillImg->imageSize * 5.0f;
	skillImg->scale.x /= 16;
	skillImg->pivot = OFFSET_B;
	skillImg->maxFrame.x = 16;

	skillTypeImg = new ObImage(L"Type Status Icons4.png");
	skillTypeImg->scale = skillTypeImg->imageSize * 5.0f;
	skillTypeImg->pivot = OFFSET_B;
}

WaterGun::~WaterGun()
{
}

void WaterGun::OutSound()
{
	SOUND->Stop("WATER");
	SOUND->Play("WATER");
}
