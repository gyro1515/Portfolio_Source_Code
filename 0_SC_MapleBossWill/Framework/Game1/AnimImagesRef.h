#pragma once
class AnimImagesRef :public Singleton<AnimImagesRef>
{
public:
	Attack1 attack1;
	Attack2 attack2;
	Attack3 attack3;
	Attack4 attack4;
	Attack5 attack5;
	Attack6 attack6;
	Attack7 attack7;
	Ball ball;
	Die1 die1;
	Hit1 hit1;
	Move move;
	Skill1 skill1;
	Stand stand;
};

#define ANIMREF AnimImagesRef::GetInstance()
#define WILL_ATTACK3 AnimImagesRef::GetInstance()->attack3
