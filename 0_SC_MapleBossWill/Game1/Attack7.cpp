#include "stdafx.h"

Attack7::Attack7()
{
	attack7Img = *new vector<ObImage*>(16);
	attack7Img[0] = new ObImage(L"attack7 (1).png");
	attack7Img[1] = new ObImage(L"attack7 (2).png");
	attack7Img[2] = new ObImage(L"attack7 (3).png");
	attack7Img[3] = new ObImage(L"attack7 (4).png");
	attack7Img[4] = new ObImage(L"attack7 (5).png");
	attack7Img[5] = new ObImage(L"attack7 (6).png");
	attack7Img[6] = new ObImage(L"attack7 (7).png");
	attack7Img[7] = new ObImage(L"attack7 (8).png");
	attack7Img[8] = new ObImage(L"attack7 (9).png");
	attack7Img[9] = new ObImage(L"attack7 (10).png");
	attack7Img[10] = new ObImage(L"attack7 (11).png");
	attack7Img[11] = new ObImage(L"attack7 (12).png");
	attack7Img[12] = new ObImage(L"attack7 (13).png");
	attack7Img[13] = new ObImage(L"attack7 (14).png");
	attack7Img[14] = new ObImage(L"attack7 (15).png");
	attack7Img[15] = new ObImage(L"attack7 (16).png");
	for (auto& _image : attack7Img)
	{
		_image->animInterval = 0.09f;
		_image->SetWorldPos(Vector2(-65.0f, 13.0f));
	}

	
}

Attack7::~Attack7()
{
}

void Attack7::Update()
{
}

void Attack7::LateUpdate()
{
}

void Attack7::Render()
{
}
