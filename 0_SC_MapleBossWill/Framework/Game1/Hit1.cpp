#include "stdafx.h"

Hit1::Hit1()
{
	hit1 = *new vector<ObImage*>(16);
	hit1[0] = new ObImage(L"will_hit (1).png");
	hit1[1] = new ObImage(L"will_hit (2).png");
	hit1[2] = new ObImage(L"will_hit (3).png");
	hit1[3] = new ObImage(L"will_hit (4).png");
	hit1[4] = new ObImage(L"will_hit (5).png");
	hit1[5] = new ObImage(L"will_hit (6).png");
	hit1[6] = new ObImage(L"will_hit (7).png");
	hit1[7] = new ObImage(L"will_hit (8).png");
	hit1[8] = new ObImage(L"will_hit (9).png");
	hit1[9] = new ObImage(L"will_hit (10).png");
	hit1[10] = new ObImage(L"will_hit (11).png");
	hit1[11] = new ObImage(L"will_hit (12).png");
	hit1[12] = new ObImage(L"will_hit (13).png");
	hit1[13] = new ObImage(L"will_hit (14).png");
	hit1[14] = new ObImage(L"will_hit (15).png");
	hit1[15] = new ObImage(L"will_hit (16).png");
	for (auto& _image : hit1)
	{
		_image->animInterval = 0.09f;
		_image->SetWorldPos(Vector2(1.0f, -22.0f));
	}
}

Hit1::~Hit1()
{
}

void Hit1::Update()
{
}

void Hit1::LateUpdate()
{
}

void Hit1::Render()
{
}
