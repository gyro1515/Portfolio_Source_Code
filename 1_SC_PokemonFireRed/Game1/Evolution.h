#pragma once
class Evolution : public Scene
{
public:
	ObImage* battleGround[2];
	Player* player;
	Pokemon* evolPoke;
	float backCol;
	float pokeCol;
	int bsCount;
	float bsScale1;
	float bsScale2;

	//��Ʋ �޼���
	wstring battleMes;
	int mesNum;
	int mesIndex;
	float mesTime;
	//����
	float lightCol;
	float lightTime;
	bool fadeIn;
	bool fadeOut;

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void Evol();
	void EvolRander();

};

