#pragma once
class Snail :public CompoObject
{
private:
	vector<ObImage*> snail;
	vector<ObImage*> snailHit;
	float _duration;
	Vector2 _direction;
	Collider* _collider;

public:
	Snail();
	~Snail();

	Animation* animation;
	CompoObject* enemy;

	void Update() override;
	void Render() override;

	void Throw(Vector2 _position, Vector2 _direction);
};
