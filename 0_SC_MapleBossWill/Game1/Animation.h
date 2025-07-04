#pragma once

enum class AnimState
{
	None, Stand, Jump, Move, Attack1, Attack2, Attack3, Attack4, Attack5, Attack6, Attack7, Ball, Die1, Hit1, Skill1, Start, Loop, End, Walk, Phase2, Phase3
};

class Animation :public Component
{
private:
	vector<ObImage*>* _animImages;
	float _time;
	int _animCount;

public:
	Animation();
	~Animation();

	ObImage _renderingImage = *new ObImage(L"NONE.png");
	bool flipX;
	bool isLoop;
	bool IsOver();

	void Update() override;

	void Render() override;

	void Play();
	void SetAnimation(vector<ObImage*>* _animImages);

	int GetAnimCount() { return _animCount; }
	void SetAnimCount(int animCount) { _animCount = animCount; }

	Vector2 GetAnimScale() { return _renderingImage.scale; }
	Vector2 GetAnimWorldPivot() { return _renderingImage.GetWorldPivot(); }
};
