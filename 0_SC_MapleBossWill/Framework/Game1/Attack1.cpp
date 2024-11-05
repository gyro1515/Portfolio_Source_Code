#include "stdafx.h"

Attack1::Attack1()
{
	attack1Img = *new vector<ObImage*>(20);
	attack1Img[0] = new ObImage(L"attack1 (1).png");
	attack1Img[1] = new ObImage(L"attack1 (2).png");
	attack1Img[2] = new ObImage(L"attack1 (3).png");
	attack1Img[3] = new ObImage(L"attack1 (4).png");
	attack1Img[4] = new ObImage(L"attack1 (5).png");
	attack1Img[5] = new ObImage(L"attack1 (6).png");
	attack1Img[6] = new ObImage(L"attack1 (7).png");
	attack1Img[7] = new ObImage(L"attack1 (8).png");
	attack1Img[8] = new ObImage(L"attack1 (9).png");
	attack1Img[9] = new ObImage(L"attack1 (10).png");
	attack1Img[10] = new ObImage(L"attack1 (11).png");
	attack1Img[11] = new ObImage(L"attack1 (12).png");
	attack1Img[12] = new ObImage(L"attack1 (13).png");
	attack1Img[13] = new ObImage(L"attack1 (14).png");
	attack1Img[14] = new ObImage(L"attack1 (15).png");
	attack1Img[15] = new ObImage(L"attack1 (16).png");
	attack1Img[16] = new ObImage(L"attack1 (17).png");
	attack1Img[17] = new ObImage(L"attack1 (18).png");
	attack1Img[18] = new ObImage(L"attack1 (19).png");
	attack1Img[19] = new ObImage(L"attack1 (20).png");

	for (auto& _image : attack1Img)
	{
		_image->animInterval = 0.1f;
		_image->SetWorldPos(Vector2(-70.0f, -44.0f));
	}

	attack1Hit = *new vector<ObImage*>(6);
	attack1Hit[0] = new ObImage(L"attack1_hit (1).png");
	attack1Hit[1] = new ObImage(L"attack1_hit (2).png");
	attack1Hit[2] = new ObImage(L"attack1_hit (3).png");
	attack1Hit[3] = new ObImage(L"attack1_hit (4).png");
	attack1Hit[4] = new ObImage(L"attack1_hit (5).png");
	attack1Hit[5] = new ObImage(L"attack1_hit (6).png");

	for (auto& _image : attack1Hit)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos(Vector2(-70.0f, -44.0f));
	}
}

Attack1::~Attack1()
{
}

void Attack1::Update()
{
}

void Attack1::LateUpdate()
{
}

void Attack1::Render()
{
}