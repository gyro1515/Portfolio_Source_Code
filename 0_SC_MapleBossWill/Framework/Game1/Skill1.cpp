#include "stdafx.h"

Skill1::Skill1()
{
	skill1 = *new vector<ObImage*>(16);
	skill1[0] = new ObImage(L"will_skill (1).png");
	skill1[1] = new ObImage(L"will_skill (2).png");
	skill1[2] = new ObImage(L"will_skill (3).png");
	skill1[3] = new ObImage(L"will_skill (4).png");
	skill1[4] = new ObImage(L"will_skill (5).png");
	skill1[5] = new ObImage(L"will_skill (6).png");
	skill1[6] = new ObImage(L"will_skill (7).png");
	skill1[7] = new ObImage(L"will_skill (8).png");
	skill1[8] = new ObImage(L"will_skill (9).png");
	skill1[9] = new ObImage(L"will_skill (10).png");
	skill1[10] = new ObImage(L"will_skill (11).png");
	skill1[11] = new ObImage(L"will_skill (12).png");
	skill1[12] = new ObImage(L"will_skill (13).png");
	skill1[13] = new ObImage(L"will_skill (14).png");
	skill1[14] = new ObImage(L"will_skill (15).png");
	skill1[15] = new ObImage(L"will_skill (16).png");
	for (auto& _image : skill1)
	{
		_image->animInterval = 0.09f;
		_image->SetWorldPos(Vector2(-65.0f, 13.0f));
	}
}

Skill1::~Skill1()
{
}



void Skill1::Update()
{
}

void Skill1::LateUpdate()
{
}

void Skill1::Render()
{
}
