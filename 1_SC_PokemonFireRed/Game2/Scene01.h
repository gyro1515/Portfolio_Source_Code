#pragma once
class Scene01 : public Scene
{
public:
	ObTileMap* map;
	ObImage* player;

	//��ã��� ����
	vector<Tile*> PlWay;
	//�̵���ų ��ġ
	Vector2 plDest;
	Vector2 plSour;
	//����
	float   g;

	Vector2 lastPos;

	bool fadeOut;
	float fadeIn;

	RECT rectT;
	int lefT;
	int toP;
	int righT;
	int boT;
	int sizE;


public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

