#pragma once
class Collider :public Component
{
private:

public:
	Collider();
	~Collider();

	GameObject* _collider;

	bool isTrigger;

	void Update() override;
	void Render() override;

	void SetCollider(CompoObject* _parents, Vector2 _scale);
	void SetCollider(Vector2 _position, Vector2 _scale);

	bool Intersect(CompoObject* _collisionObject);
};
