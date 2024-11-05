#include "stdafx.h"

Player::Player()
{

	playerFront = new ObImage(L"Hero & Heroine1.png");
	playerFront->scale = playerFront->imageSize * 5;
	playerFront->scale.x /= 4.0f;
	playerFront->maxFrame.x = 4;
	//playerFront->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	playerBack = new ObImage(L"Hero & Heroine2.png");
	playerBack->scale = playerBack->imageSize * 5;
	playerBack->scale.x /= 4.0f;
	playerBack->maxFrame.x = 4;
	//playerBack->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	playerLeft = new ObImage(L"Hero & Heroine3.png");
	playerLeft->scale = playerLeft->imageSize * 5;
	playerLeft->scale.x /= 4.0f;
	playerLeft->maxFrame.x = 4;
	//playerLeft->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	playerRight = new ObImage(L"Hero & Heroine4.png");
	playerRight->scale = playerRight->imageSize * 5;
	playerRight->scale.x /= 4.0f;
	playerRight->maxFrame.x = 4;
	//playerRight->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
	aniFrame = 0;
	money = 5000000;
	firstSet = true;
	inTown = false;
	inCave = false;
	caveToBattle = false;
	findJam = false; // 테스트 가능
	myPokemonNum = 0;
}

Player::~Player()
{
}

void Player::Update()
{
	playerFront->Update();
	playerBack->Update();
	playerLeft->Update();
	playerRight->Update();
}

void Player::LateUpdate()
{
}

void Player::Render()
{
	playerFront->Render();
	playerBack->Render();
	playerLeft->Render();
	playerRight->Render();
}

void Player::SetPlayerPos(Vector2 _playerPos)
{
	playerFront->SetWorldPos(_playerPos);
	playerBack->SetWorldPos(_playerPos);
	playerLeft->SetWorldPos(_playerPos);
	playerRight->SetWorldPos(_playerPos);
}

void Player::SetPlayerVisible(bool _isVisible)
{
	playerFront->isVisible = _isVisible;
	playerBack->isVisible = _isVisible;
	playerLeft->isVisible = _isVisible;
	playerRight->isVisible = _isVisible;
}

void Player::MovePlayerPos(Vector2 _playerPos)
{
	playerFront->MoveWorldPos(_playerPos);
	playerBack->MoveWorldPos(_playerPos);
	playerLeft->MoveWorldPos(_playerPos);
	playerRight->MoveWorldPos(_playerPos);
}

void Player::SetPlayerAni(ANIMSTATE ani, float interval)
{
	playerLeft->ChangeAnim(ani, interval);
	playerRight->ChangeAnim(ani, interval);
	playerFront->ChangeAnim(ani, interval);
	playerBack->ChangeAnim(ani, interval);
}

void Player::SetPlayerAniFrame(int _frame)
{
	playerLeft->frame.x = _frame;
	playerRight->frame.x = _frame;
	playerFront->frame.x = _frame;
	playerBack->frame.x = _frame;
}
