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
	name = L"��ó��";
	explanation = L"�������̽���  ��ó��\n���ϸ�  1  ������  HP��\n50��ŭ  ȸ���Ѵ�.";
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
	name = L"���ͺ�";
	explanation = L"�߻�  ���ϸ󿡰�  ������\n���  ����  ��.\nĸ��������  �Ǿ��ִ�.";
	num = 1;
	price = 200;
	itemImg = new ObImage(L"Items1.png");
	itemImg->scale = itemImg->imageSize * 5;
	itemImg->SetWorldPos(Vector2(-502.0f, -280.0f));
}

PokeBall::~PokeBall()
{
}
