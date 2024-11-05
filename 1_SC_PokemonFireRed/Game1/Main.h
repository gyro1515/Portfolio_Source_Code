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

	//글자 테스트
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


	//이미지 테스트
	int imgX;
	int imgY;
	int scaleX;
	int scaleY;
	ObImage* testImg;
	float test_gravi;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
