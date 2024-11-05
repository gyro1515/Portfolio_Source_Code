#pragma once
enum class CaveState
{
	CAVE,
	POKEMENU,
	POKEMON,
	BAG
};
class Cave : public Scene
{
public:
	CaveState state;
	ObTileMap* cave;
	ObImage* jam;
	Int2 ranJam[9];
	int tempRan;
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
	//��ã��� ����
	vector<Tile*> PlWay;
	//��ã�� �� ����� ����;
	vector<Tile*> TmpPlWay;

	bool playAni;
	//����
	float   g;
	Vector2 lastPos;
	//�� ĭ�� �̵�
	bool playerGo;
	bool playerTurn;
	ObImage* onGrassImg;
	bool goWall;
	bool goShop;

	//���ϸ�
	Pokemon* fieldPoke;
	
	//�����
	float wallTime;

	//��������
	bool battleStart;

	//����ȯ
	bool goTown;
	float sceneTime;
	//����
	float lightCol;
	float lightTime;
	bool fadeIn;
	bool fadeOut;
	int battleLightCount;
	bool battleLightOn;

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
	void CAVE();
	void POKEMENU();
	void POKEMON();
	void BAG();
};

