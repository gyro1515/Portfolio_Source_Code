#pragma once
enum class TownState
{
	TOWN,
	POKEMENU,
	POKEMON,
	BAG
};
class Town : public Scene
{
public:
	TownState state;
	ObTileMap* town;
	ObImage* townBack;
	ObImage* building1;
	ObImage* pokeCenter;
	ObImage* shop;
	ObImage* building1Roof;
	ObImage* pokeCenterRoof;
	ObImage* shopRoof;
	ObImage* door[3];
	//�޴�
	ObImage* mapMenu;
	ObImage* mapMenuSel;
	int menuSel;
	//�޴� ���ϸ�
	PokeMenu* pokeMenu;
	//�޴� ����
	BagMenu* bag;


	Player* player;
	//�̵���ų ��ġ
	Vector2 plDest;
	Vector2 plSour;
	//����
	float   g;
	Vector2 lastPos;
	//�� ĭ�� �̵�
	bool playerGo;
	bool playerTurn;
	ObImage* onGrassImg;
	bool goWall;
	bool goShop;
	bool goCave;

	//���ϸ�
	Pokemon* fieldPoke[10];
	Poke3* testPoke;
	//������
	Item* setItem[2];

	//�����
	float wallTime;

	//��������
	bool battleStart;

	//��ü������ Ÿ��
	float sceneTime;
	//����
	float lightCol;
	int battleLightCount;
	bool battleLightOn;
	float lightTime;
	bool fadeIn;
	bool fadeOut;

	//�׽�Ʈ
	int imgX;
	int imgY;

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void FAIDEIN();
	void SCENE_TO_TOWN();
	void TOWN();
	void POKEMENU();
	void POKEMON();
	void BAG();
	void SetSound();


};

