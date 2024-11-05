#pragma once
class Item
{
public:
	wstring name;
	wstring explanation;
	ObImage* itemImg;
	int num;
	int price;
public:
	Item();
	~Item();
	Item(const Item& src);
	Item* Create();
};

class Portion : public Item
{
public:
	int heal;
public:
	Portion();
	~Portion();
};

class PokeBall : public Item
{
public:
	PokeBall();
	~PokeBall();
};

