#include "Framework.h"

ItemManager::ItemManager()
{


	weapons.resize(30);
	invEquip.resize(4);


	Item* test = new Equipment(1);
	Item* test2 = new Equipment(2);
	Item* test3 = new Ingredient(1);
	Item* test4 = new Ingredient(2);
	Item* test5 = new Consumable(1);
	Item* test6 = new Equipment(3);

	weapons.push_back(test);
	weapons.push_back(test2);
	weapons.push_back(test6);

	FOR(30)
	{
		Mining(test3);
		Mining(test4);
		Mining(test5);
	}



}

ItemManager::~ItemManager()
{
	weapons.clear();
	invEquip.clear();
	for (auto& pair : items)
	{
		for (auto item : pair.second)
		{
			delete item;
		}
		pair.second.clear();

	}
	for (auto& pair : consumItems)
	{
		for (auto item : pair.second)
		{
			delete item;
		}
		pair.second.clear();

	}

}

void ItemManager::Update()
{

	FOR(invEquip.size())
	{
		if (invEquip[i] != nullptr) PlayerManager::Get()->GetPlayer()->SetModel(i, invEquip[i]->GetModel());
		else PlayerManager::Get()->GetPlayer()->SetModel(i, nullptr);

	}

}

void ItemManager::Render()
{



}

void ItemManager::PostRender()
{



}


void ItemManager::Mining(Item* item)
{

	if (item == nullptr)
		return;


	if (item->type == Item::Type::CONSUMABLE)
	{

		if (consumData[item->num].second == 0)
		{
			consumData[item->num].first = item->num;
			consumData[item->num].second++;
		}
		else
		{
			for (auto& data : consumData)
			{
				if (data.second.first == item->num)
				{
					data.second.second++;
					break;
				}
			}
		}
		consumItems[item->num - 1].push_back(item);
	}
	else if (item->type == Item::Type::INGREDIENT)
	{

		if (itemData[item->num].second == 0)
		{
			itemData[item->num].first = item->num;
			itemData[item->num].second++;
		}
		else
		{
			for (auto& data : itemData)
			{
				if (data.second.first == item->num)
				{
					data.second.second++;
					break;
				}
			}
		}
		items[item->num - 1].push_back(item);
	}
	else if (item->type == Item::Type::WEAPON)
	{

		weapons.push_back(item);


	}

}

void ItemManager::MakeItem(int EquipNum)
{
	Item* test = nullptr;

	switch (EquipNum)
	{
	case 0:
		test = new Equipment(1);
		break;
	case 1:
		test = new Equipment(2);
		break;
	case 2:
		test = new Consumable(1);
		break;
	case 3:
		test = new Consumable(2);
		break;
	case 4:
		test = new Consumable(3);
		break;
	default:
		test = new Equipment(3);
		break;
	}

	StructureManager::Get()->GetWorkBench()->SetItem(test);


}

string ItemManager::GetEquipVN(int NUM)
{
	if (invEquip[NUM-1] != nullptr) return invEquip[NUM-1]->name;
	return "�������";
}



