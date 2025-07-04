#include "stdafx.h"

Attack4::Attack4()
{
	attack4Img = *new vector<ObImage*>(30);
	attack4Img[0] = new ObImage(L"attack4 (1).png");
	attack4Img[1] = new ObImage(L"attack4 (2).png");
	attack4Img[2] = new ObImage(L"attack4 (3).png");
	attack4Img[3] = new ObImage(L"attack4 (4).png");
	attack4Img[4] = new ObImage(L"attack4 (5).png");
	attack4Img[5] = new ObImage(L"attack4 (6).png");
	attack4Img[6] = new ObImage(L"attack4 (7).png");
	attack4Img[7] = new ObImage(L"attack4 (8).png");
	attack4Img[8] = new ObImage(L"attack4 (9).png");
	attack4Img[9] = new ObImage(L"attack4 (10).png");
	attack4Img[10] = new ObImage(L"attack4 (11).png");
	attack4Img[11] = new ObImage(L"attack4 (12).png");
	attack4Img[12] = new ObImage(L"attack4 (13).png");
	attack4Img[13] = new ObImage(L"attack4 (14).png");
	attack4Img[14] = new ObImage(L"attack4 (15).png");
	attack4Img[15] = new ObImage(L"attack4 (16).png");
	attack4Img[16] = new ObImage(L"attack4 (17).png");
	attack4Img[17] = new ObImage(L"attack4 (18).png");
	attack4Img[18] = new ObImage(L"attack4 (19).png");
	attack4Img[19] = new ObImage(L"attack4 (20).png");
	attack4Img[20] = new ObImage(L"attack4 (21).png");
	attack4Img[21] = new ObImage(L"attack4 (22).png");
	attack4Img[22] = new ObImage(L"attack4 (23).png");
	attack4Img[23] = new ObImage(L"attack4 (24).png");
	attack4Img[24] = new ObImage(L"attack4 (25).png");
	attack4Img[25] = new ObImage(L"attack4 (26).png");
	attack4Img[26] = new ObImage(L"attack4 (27).png");
	attack4Img[27] = new ObImage(L"attack4 (28).png");
	attack4Img[28] = new ObImage(L"attack4 (29).png");
	attack4Img[29] = new ObImage(L"attack4 (30).png");

	for (auto& _image : attack4Img)
	{
		_image->animInterval = 0.09f;
		_image->SetWorldPos(Vector2(-119.0f, -101.0f));
	}

	attack4Hit = *new vector<ObImage*>(7);
	attack4Hit[0] = new ObImage(L"attack4_hit (1).png");
	attack4Hit[1] = new ObImage(L"attack4_hit (2).png");
	attack4Hit[2] = new ObImage(L"attack4_hit (3).png");
	attack4Hit[3] = new ObImage(L"attack4_hit (4).png");
	attack4Hit[4] = new ObImage(L"attack4_hit (5).png");
	attack4Hit[5] = new ObImage(L"attack4_hit (6).png");
	attack4Hit[6] = new ObImage(L"attack4_hit (7).png");

	for (auto& _image : attack4Hit)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos(Vector2(-70.0f, -44.0f));
	}
}

Attack4::~Attack4()
{
}

void Attack4::Update()
{
}

void Attack4::LateUpdate()
{
}

void Attack4::Render()
{
}