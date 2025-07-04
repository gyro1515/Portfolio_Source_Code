#include "stdafx.h"

Move::Move()
{
	move = *new vector<ObImage*>(16);
	move[0] = new ObImage(L"will_move (1).png");
	move[1] = new ObImage(L"will_move (2).png");
	move[2] = new ObImage(L"will_move (3).png");
	move[3] = new ObImage(L"will_move (4).png");
	move[4] = new ObImage(L"will_move (5).png");
	move[5] = new ObImage(L"will_move (6).png");
	move[6] = new ObImage(L"will_move (7).png");
	move[7] = new ObImage(L"will_move (8).png");
	move[8] = new ObImage(L"will_move (9).png");
	move[9] = new ObImage(L"will_move (10).png");
	move[10] = new ObImage(L"will_move (11).png");
	move[11] = new ObImage(L"will_move (12).png");
	move[12] = new ObImage(L"will_move (13).png");
	move[13] = new ObImage(L"will_move (14).png");
	move[14] = new ObImage(L"will_move (15).png");
	move[15] = new ObImage(L"will_move (16).png");
	for (auto& _image : move)
	{
		_image->animInterval = 0.09f;
		_image->SetWorldPos(Vector2(0.0f, -62.0f));
	}
}

Move::~Move()
{
}

void Move::Update()
{
}

void Move::LateUpdate()
{
}

void Move::Render()
{
}
