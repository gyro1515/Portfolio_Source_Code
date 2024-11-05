#pragma once
class Scene02 : public Scene
{
public:
	ObTileMap* map;
	ObImage* player;

	//길찾기용 변수
	vector<Tile*> PlWay;
	//이동시킬 위치
	Vector2 plDest;
	Vector2 plSour;
	//비율
	float   g;

	Vector2 lastPos;

	bool whiteOut;
	float whiteIn;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

