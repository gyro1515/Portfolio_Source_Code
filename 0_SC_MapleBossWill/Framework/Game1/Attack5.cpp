#include "stdafx.h"

Attack5::Attack5()
{
	attack5Img = *new vector<ObImage*>(20);
	attack5Img[0] = new ObImage(L"attack5 (1).png");
	attack5Img[1] = new ObImage(L"attack5 (2).png");
	attack5Img[2] = new ObImage(L"attack5 (3).png");
	attack5Img[3] = new ObImage(L"attack5 (4).png");
	attack5Img[4] = new ObImage(L"attack5 (5).png");
	attack5Img[5] = new ObImage(L"attack5 (6).png");
	attack5Img[6] = new ObImage(L"attack5 (7).png");
	attack5Img[7] = new ObImage(L"attack5 (8).png");
	attack5Img[8] = new ObImage(L"attack5 (9).png");
	attack5Img[9] = new ObImage(L"attack5 (10).png");
	attack5Img[10] = new ObImage(L"attack5 (11).png");
	attack5Img[11] = new ObImage(L"attack5 (12).png");
	attack5Img[12] = new ObImage(L"attack5 (13).png");
	attack5Img[13] = new ObImage(L"attack5 (14).png");
	attack5Img[14] = new ObImage(L"attack5 (15).png");
	attack5Img[15] = new ObImage(L"attack5 (16).png");
	attack5Img[16] = new ObImage(L"attack5 (17).png");
	attack5Img[17] = new ObImage(L"attack5 (18).png");
	attack5Img[18] = new ObImage(L"attack5 (19).png");
	attack5Img[19] = new ObImage(L"attack5 (20).png");

	for (auto& _image : attack5Img)
	{
		_image->animInterval = 0.09f;
		_image->SetWorldPos(Vector2(-209.0f, -52.0f));
	}

	attack5Hit = *new vector<ObImage*>(7);
	attack5Hit[0] = new ObImage(L"attack4_hit (1).png");
	attack5Hit[1] = new ObImage(L"attack4_hit (2).png");
	attack5Hit[2] = new ObImage(L"attack4_hit (3).png");
	attack5Hit[3] = new ObImage(L"attack4_hit (4).png");
	attack5Hit[4] = new ObImage(L"attack4_hit (5).png");
	attack5Hit[5] = new ObImage(L"attack4_hit (6).png");
	attack5Hit[6] = new ObImage(L"attack4_hit (7).png");

	for (auto& _image : attack5Hit)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos(Vector2(-70.0f, -44.0f));
	}
}

Attack5::~Attack5()
{
}

void Attack5::Update()
{
}

void Attack5::LateUpdate()
{
}

void Attack5::Render()
{
}