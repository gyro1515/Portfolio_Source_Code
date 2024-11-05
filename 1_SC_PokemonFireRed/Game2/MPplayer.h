#pragma once
enum class PState
{
	IDLE,
	MOVE,
	JUMP,
	ATT
};

class MPplayer
{
public:
	ObRect* col;
	ObImage* run;
	ObImage* jump;
	ObImage* att;

	Vector2 moveDir;
	PState state;
	float gravity;

	bool isDoubleJump;
	float timer;
	float timer2;

	int damage;
	bool isDamaging;

	bool targetCol;

public:
	MPplayer();
	~MPplayer();
	void Update();
	void Render();

	void Idle();
	void Move();
	void Jump();
	void Attack();

	void JumpToIdle();

	void Input();

	void TakeDamage(int damage);
};

