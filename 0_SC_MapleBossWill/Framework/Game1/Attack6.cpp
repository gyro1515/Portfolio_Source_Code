#include "stdafx.h"

Attack6::Attack6()
{
	attack6Img = *new vector<ObImage*>(20);
	attack6Img[0] = new ObImage(L"attack6 (1).png");
	attack6Img[1] = new ObImage(L"attack6 (2).png");
	attack6Img[2] = new ObImage(L"attack6 (3).png");
	attack6Img[3] = new ObImage(L"attack6 (4).png");
	attack6Img[4] = new ObImage(L"attack6 (5).png");
	attack6Img[5] = new ObImage(L"attack6 (6).png");
	attack6Img[6] = new ObImage(L"attack6 (7).png");
	attack6Img[7] = new ObImage(L"attack6 (8).png");
	attack6Img[8] = new ObImage(L"attack6 (9).png");
	attack6Img[9] = new ObImage(L"attack6 (10).png");
	attack6Img[10] = new ObImage(L"attack6 (11).png");
	attack6Img[11] = new ObImage(L"attack6 (12).png");
	attack6Img[12] = new ObImage(L"attack6 (13).png");
	attack6Img[13] = new ObImage(L"attack6 (14).png");
	attack6Img[14] = new ObImage(L"attack6 (15).png");
	attack6Img[15] = new ObImage(L"attack6 (16).png");
	attack6Img[16] = new ObImage(L"attack6 (17).png");
	attack6Img[17] = new ObImage(L"attack6 (18).png");
	attack6Img[18] = new ObImage(L"attack6 (19).png");
	attack6Img[19] = new ObImage(L"attack6 (20).png");

	for (auto& _image : attack6Img)
	{
		_image->animInterval = 0.09f;
		_image->SetWorldPos(Vector2(188.0f, -82.0f));
	}

	attack6Hit = *new vector<ObImage*>(7);
	attack6Hit[0] = new ObImage(L"attack6_hit (1).png");
	attack6Hit[1] = new ObImage(L"attack6_hit (2).png");
	attack6Hit[2] = new ObImage(L"attack6_hit (3).png");
	attack6Hit[3] = new ObImage(L"attack6_hit (4).png");
	attack6Hit[4] = new ObImage(L"attack6_hit (5).png");
	attack6Hit[5] = new ObImage(L"attack6_hit (6).png");
	attack6Hit[6] = new ObImage(L"attack6_hit (7).png");

	for (auto& _image : attack6Hit)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos(Vector2(-70.0f, -44.0f));
	}
}

Attack6::~Attack6()
{
}

void Attack6::Update()
{
}

void Attack6::LateUpdate()
{
}

void Attack6::Render()
{
}