#pragma once

class Main : public Scene
{
private:
	Town* townScene;
	Battle* battleScene;
	Shop* shopScene;
	Cave* caveScene;
	Evolution* evoScene;
	Player* player;

	//���� �׽�Ʈ
	RECT rectT;
	int lefT;
	int toP;
	int righT;
	int boT;
	int sizE;
	int numR;

	int leftR;
	int topR;
	int rightR;
	int botR;
	int sizeR;

	wstring testInt;
	float testTIme;
	int testIndex;
	int testStart;


	//�̹��� �׽�Ʈ
	int imgX;
	int imgY;
	int scaleX;
	int scaleY;
	ObImage* testImg;
	float test_gravi;

public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
