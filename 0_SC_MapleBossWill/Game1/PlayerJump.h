#pragma once
class Player;

class PlayerJump
{
private:
	float _force;

	float _gravity;
	Vector2 _direction;

public:
	PlayerJump();

	Player* player;
	float floorHeight;
	int jumpCount;

	void Jump(Vector2 _direction, float _force);

	void Update();
};
