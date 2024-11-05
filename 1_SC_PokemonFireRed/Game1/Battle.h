#pragma once
enum class battleState
{
	INTRO1,
	INTRO2,
	TRAINER_INTRO1,
	TRAINER_INTRO2,
	MENU,
	FIGHT,
	FIGHT_FIRST,
	FIGHT_SECEND,
	BAG,
	POKEMON,
	CHANGE_POKE,
	RUN,
	PLAYER_WIN,
	PLAYER_LOSE,
	CATCH_POKE,
	EVOLUTION
};
class Battle : public Scene
{
public:
	ObImage* battleGround[3];
	ObImage* battleHp[2];
	ObImage* battleHpBar[9];
	ObImage* battleUi[4];
	ObImage* playerImg;
	ObImage* ballAni;
	float ballThrowTime;
	float ballAniTime;
	float ballGravi;
	float ballOutScale;
	float ballInScale;

	battleState state;

	//����
	bool playerAttack;
	bool enermyAttack;
	int changeHp;
	float changeHpFloat;
	int fightNum;
	int enermySkillNum;
	float skillTime;
	bool enermyPokeDie;
	int changeExp;
	float changeExpFloat;
	int leftchangeExp;
	bool leveUP;
	float hitTime;
	//�÷��̾� ���ϸ� ���� ��
	int pokeDieCount;

	Player* player;

	Pokemon* playerPoke;
	Pokemon* enermyPoke;
	int intro2State;
	int selMenu;
	//����
	BagMenu* bag;
	//���ͺ�
	ObImage* catchPokeBall;
	float catchPokeBallTime;
	float catchPokeBallGravi;
	int ballBounce;
	float ballTime;
	float ballCol;

	//�޴�
	PokeMenu* pokeMenu;

	//��Ʋ �޼���
	wstring battleMes;
	int mesNum;
	int mesIndex;
	float mesTime;
	ObImage* battelClick;
	//����
	float lightCol;
	float lightTime;
	int battleLightCount;
	bool battleLightOn;
	bool fadeIn;
	bool fadeOut;



public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void Intro1();
	void Intro2();
	void Menu();
	void Fight();
	void FightFirst();
	void FightSecend();
	void Bag();
	void PokemonList();
	void PokemonListChange();
	void Run();
	void PlayerWIn();
	void PlayerLose();
	void PlayerLoseRander();

	void CatchPokemon();
	void CatchPokemonRander();


	void SetPokemon(Pokemon* _playerPoke, Pokemon* _enermyPoke);
	bool BallOutPoke(Pokemon* _Poke, float& _ballOutScale);
	bool BallInPoke(Pokemon* _Poke, float& _ballInScale);

};

