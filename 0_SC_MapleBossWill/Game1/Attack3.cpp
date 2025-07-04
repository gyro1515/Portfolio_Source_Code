#include "stdafx.h"

Attack3::Attack3()
{
	attack3Img = *new vector<ObImage*>(20);
	attack3Img[0] = new ObImage(L"attack3 (1).png");
	attack3Img[1] = new ObImage(L"attack3 (2).png");
	attack3Img[2] = new ObImage(L"attack3 (3).png");
	attack3Img[3] = new ObImage(L"attack3 (4).png");
	attack3Img[4] = new ObImage(L"attack3 (5).png");
	attack3Img[5] = new ObImage(L"attack3 (6).png");
	attack3Img[6] = new ObImage(L"attack3 (7).png");
	attack3Img[7] = new ObImage(L"attack3 (8).png");
	attack3Img[8] = new ObImage(L"attack3 (9).png");
	attack3Img[9] = new ObImage(L"attack3 (10).png");
	attack3Img[10] = new ObImage(L"attack3 (11).png");
	attack3Img[11] = new ObImage(L"attack3 (12).png");
	attack3Img[12] = new ObImage(L"attack3 (13).png");
	attack3Img[13] = new ObImage(L"attack3 (14).png");
	attack3Img[14] = new ObImage(L"attack3 (15).png");
	attack3Img[15] = new ObImage(L"attack3 (16).png");
	attack3Img[16] = new ObImage(L"attack3 (17).png");
	attack3Img[17] = new ObImage(L"attack3 (18).png");
	attack3Img[18] = new ObImage(L"attack3 (19).png");
	attack3Img[19] = new ObImage(L"attack3 (20).png");

	for (auto& _image : attack3Img)
	{
		_image->animInterval = 0.1f;
		_image->SetWorldPos(Vector2(206.0f, -83.0f));
	}

	attack3Hit = *new vector<ObImage*>(6);
	attack3Hit[0] = new ObImage(L"attack3_hit (1).png");
	attack3Hit[1] = new ObImage(L"attack3_hit (2).png");
	attack3Hit[2] = new ObImage(L"attack3_hit (3).png");
	attack3Hit[3] = new ObImage(L"attack3_hit (4).png");
	attack3Hit[4] = new ObImage(L"attack3_hit (5).png");
	attack3Hit[5] = new ObImage(L"attack3_hit (6).png");

	for (auto& _image : attack3Hit)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos(Vector2(-70.0f, -44.0f));
	}
}

Attack3::~Attack3()
{
}

void Attack3::Update()
{
}

void Attack3::LateUpdate()
{
}

void Attack3::Render()
{
}