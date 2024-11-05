#pragma once

class Player
{
public:
	deque<Pokemon*> myPokemon;
	int myPokemonNum;
	deque<Pokemon*> enemyPokemon;
	deque<Item*> myItem;

	ObImage* playerFront;
	ObImage* playerBack;
	ObImage* playerLeft;
	ObImage* playerRight;

	int aniFrame;

	bool firstSet;
	bool inTown;
	bool inCave;
	bool caveToBattle;
	bool findJam;

	int money;

public:
	Player();
	~Player();
	void Update();
	void LateUpdate();
	void Render();

	void SetPlayerPos(Vector2 _playerPos);
	void SetPlayerVisible(bool _isVisible);
	void MovePlayerPos(Vector2 _playerPos);
	void SetPlayerAni(ANIMSTATE ani, float interval);
	void SetPlayerAniFrame(int _frame);


};

