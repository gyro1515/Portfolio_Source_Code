#pragma once
class Move
{
public:
	vector<ObImage*> move;

public:
	Move();
	~Move();
	void Update();
	void LateUpdate();
	void Render();
};

