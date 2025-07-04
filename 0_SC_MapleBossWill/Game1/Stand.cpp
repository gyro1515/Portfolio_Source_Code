#include "stdafx.h"

Stand::Stand()
{
	stand = *new vector<ObImage*>(16);
	stand[0] = new ObImage(L"will_stand (1).png");
	stand[1] = new ObImage(L"will_stand (2).png");
	stand[2] = new ObImage(L"will_stand (3).png");
	stand[3] = new ObImage(L"will_stand (4).png");
	stand[4] = new ObImage(L"will_stand (5).png");
	stand[5] = new ObImage(L"will_stand (6).png");
	stand[6] = new ObImage(L"will_stand (7).png");
	stand[7] = new ObImage(L"will_stand (8).png");
	stand[8] = new ObImage(L"will_stand (9).png");
	stand[9] = new ObImage(L"will_stand (10).png");
	stand[10] = new ObImage(L"will_stand (11).png");
	stand[11] = new ObImage(L"will_stand (12).png");
	stand[12] = new ObImage(L"will_stand (13).png");
	stand[13] = new ObImage(L"will_stand (14).png");
	stand[14] = new ObImage(L"will_stand (15).png");
	stand[15] = new ObImage(L"will_stand (16).png");
	for (auto& _image : stand)
	{
		_image->animInterval = 0.06f;
		_image->SetWorldPos(Vector2(0.0f, -61.0f));
	}
}

Stand::~Stand()
{
}

void Stand::Update()
{
}

void Stand::LateUpdate()
{
}

void Stand::Render()
{
}
