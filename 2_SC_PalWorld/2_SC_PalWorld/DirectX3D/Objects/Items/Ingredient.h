#pragma once
class Ingredient : public Item
{

private:

	float LIFE_SPAN = 5;

public:

	Ingredient(int num);
	~Ingredient();

	void Update();
	void Render();


	Transform* GetTransform() { return transform; }
	CapsuleCollider* GetCollider() { return collider; }
	Texture* GetTexture() { return icon; }
	Model* GetModel() { return test; }
	//void SetTerrain(class Terrain* terrain) { this->terrain = terrain; }

	void SetPos(Transform* transform);
	void SetActive();

	bool isColPlayer();


private:

	Transform* transform;
	CapsuleCollider* collider;

	//Terrain* terrain;

	float time;



};

