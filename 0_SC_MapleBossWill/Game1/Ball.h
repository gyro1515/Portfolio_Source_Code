#pragma once
class Ball : public CompoObject
{
private:
	Collider* _collider;
	static vector<ObImage*>* GetLoopAnim();
	vector<ObImage*>* hitAnim;

public:
	Ball();
	~Ball();

	Vector2 direction;

	float speed;
	AnimState animState;
	Animation* animation;
	CompoObject* player;

	void Update() override;
	void Render() override;

	void SetState(AnimState _animState);
	void Shoot(Vector2 _direction, Vector2 _shootPos);
};
