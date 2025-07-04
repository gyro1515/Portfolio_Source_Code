#include "stdafx.h"

Attack2::Attack2()
{
	attack2Img = *new vector<ObImage*>(20);
	attack2Img[0] = new ObImage(L"attack2 (1).png");
	attack2Img[1] = new ObImage(L"attack2 (2).png");
	attack2Img[2] = new ObImage(L"attack2 (3).png");
	attack2Img[3] = new ObImage(L"attack2 (4).png");
	attack2Img[4] = new ObImage(L"attack2 (5).png");
	attack2Img[5] = new ObImage(L"attack2 (6).png");
	attack2Img[6] = new ObImage(L"attack2 (7).png");
	attack2Img[7] = new ObImage(L"attack2 (8).png");
	attack2Img[8] = new ObImage(L"attack2 (9).png");
	attack2Img[9] = new ObImage(L"attack2 (10).png");
	attack2Img[10] = new ObImage(L"attack2 (11).png");
	attack2Img[11] = new ObImage(L"attack2 (12).png");
	attack2Img[12] = new ObImage(L"attack2 (13).png");
	attack2Img[13] = new ObImage(L"attack2 (14).png");
	attack2Img[14] = new ObImage(L"attack2 (15).png");
	attack2Img[15] = new ObImage(L"attack2 (16).png");
	attack2Img[16] = new ObImage(L"attack2 (17).png");
	attack2Img[17] = new ObImage(L"attack2 (18).png");
	attack2Img[18] = new ObImage(L"attack2 (19).png");
	attack2Img[19] = new ObImage(L"attack2 (20).png");

	for (auto& _image : attack2Img)
	{
		_image->animInterval = 0.1f;
		_image->SetWorldPos(Vector2(-249.0f, -47.0f));
	}

	attack2Hit = *new vector<ObImage*>(6);
	attack2Hit[0] = new ObImage(L"attack2_hit (1).png");
	attack2Hit[1] = new ObImage(L"attack2_hit (2).png");
	attack2Hit[2] = new ObImage(L"attack2_hit (3).png");
	attack2Hit[3] = new ObImage(L"attack2_hit (4).png");
	attack2Hit[4] = new ObImage(L"attack2_hit (5).png");
	attack2Hit[5] = new ObImage(L"attack2_hit (6).png");

	for (auto& _image : attack2Hit)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos(Vector2(-70.0f, -44.0f));
	}
}

Attack2::~Attack2()
{
}

void Attack2::Update()
{
}

void Attack2::LateUpdate()
{
}

void Attack2::Render()
{
}