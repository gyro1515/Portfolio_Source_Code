#pragma once
class HpBar :public CompoObject
{
private:
	ObRect hpBar[2];
	float* maxHp;
	float* currentHp;

public:
	HpBar(CompoObject* gameObject);

	void Update() override;
	void Render() override;

	void SetBarScale(Vector2 _scale);
	float GetCurrentHp() { return *currentHp; };
};
