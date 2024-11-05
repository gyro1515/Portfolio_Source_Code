#include "stdafx.h"

Item::Item()
{
	name = L"";
	explanation = L"";
	num = 0;
	price = 0;
	itemImg = 0;
}

Item::~Item()
{
}

Item::Item(const Item& src)
{
	name = src.name;
	explanation = src.explanation;
	num = src.num;
	price = src.price;
	itemImg = new ObImage(src.itemImg->file);
	itemImg->scale = src.itemImg->imageSize * 5;
	itemImg->SetWorldPos(Vector2(-502.0f, -280.0f));
}

Item* Item::Create()
{
	return new Item(*this);
}

Portion::Portion()
{
	name = L"상처약";
	explanation = L"스프레이식의  상처약\n포켓몬  1  마리의  HP를\n50만큼  회복한다.";
	num = 1;
	price = 100;
	heal = 50;
	itemImg = new ObImage(L"Items2.png");
	itemImg->scale = itemImg->imageSize * 5;
	itemImg->SetWorldPos(Vector2(-502.0f, -280.0f));
}

Portion::~Portion()
{
}

PokeBall::PokeBall()
{
	name = L"몬스터볼";
	explanation = L"야생  포켓몬에게  던져서\n잡기  위한  볼.\n캡슐식으로  되어있다.";
	num = 1;
	price = 200;
	itemImg = new ObImage(L"Items1.png");
	itemImg->scale = itemImg->imageSize * 5;
	itemImg->SetWorldPos(Vector2(-502.0f, -280.0f));
}

PokeBall::~PokeBall()
{
}
