#include "Framework.h"

Player::Player() : ModelAnimator("NPC")
{
    ClientToScreen(hWnd, &clientCenterPos);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    //CAM->SetTarget(this);
    //CAM->TargetOptionLoad("test3");


    CamTransform = new Transform();
    CAM->SetParent(CamTransform);

    frontPoint = new Transform();
    frontPoint->SetParent(this);
    frontPoint->Pos() = { 0,0,-200 };

    Hand = new Transform();

    Pos() = { 100, 0, 100 };

    ReadClip("B_Idle");
    ReadClip("B_Walk");
    ReadClip("B_Run");
    ReadClip("B_Make");
    ReadClip("B_Build");


    ReadClip("J_Start");
    ReadClip("J_End");
    ReadClip("J_Loop");

    ReadClip("R_Idle");
    ReadClip("R_Run");
    ReadClip("R_Aim");
    ReadClip("R_Reload");
    ReadClip("R_Draw");

    ReadClip("RA_Run");

    ReadClip("BW_Aim");
    ReadClip("BW_Fire");

    ReadClip("M_Mining");
    ReadClip("M_Attack");

    ReadClip("S_Aim");
    ReadClip("S_Throw");

    //ReadClip("BW_Run");
    //ReadClip("BW_A_Ready");


    Scale() *= 0.01f;

    action = (ACTION)frameBuffer->Get().cur.clip;

    PlayClip(0);

    // 테스트 포획
    testPalSpear = new SphereCollider(0.2f);
    testPalSpear->SetActive(false);

    testFrontSphere = new SphereCollider();

    summonPalSpear = new Model("PalSpear");
    summonPalSpear->Scale() = { 0.02f, 0.02f, 0.02f };
    summonPalSpear->Pos() = { -0.05f, 0.05f, -0.12f };
    summonPalSpear->Rot().x = XM_PIDIV2;
    summonPalSpear->SetParent(Hand);
    summonPalSpear->SetActive(false);
    summonPalSpearThrow = new Model("PalSpear");
    summonPalSpearThrow->Scale() = { 0.02f, 0.02f, 0.02f };
    //summonPalSpearThrow->Pos() = { -0.05f, 0.05f, -0.12f };
    summonPalSpearThrow->Rot().x = XM_PIDIV2;
    summonPalSpearThrow->SetActive(false);
    summonPalSpearCollider = new SphereCollider();
    summonPalSpearCollider->SetParent(summonPalSpear);
    summonPalSpearCollider->Scale() = { 7, 7, 7 }; //크기 기본값은 1.0
    summonPalSpearCollider->Pos() = {};            //위치 기본값 : 부모 위치
    summonPalSpearDIr = {};

    // ???? : ??
    particle = new ParticleSystem("TextData/Particles/GunH.fx");
    
    MiningCollider = new SphereCollider(0.3f);
    MiningCollider->SetActive(false);
    GetClip(J_START)->SetEvent(bind(&Player::SetState, this, J_LOOP), 0.3f);
    GetClip(J_END)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);

    GetClip(S_THROW)->SetEvent(bind(&Player::SetState, this, IDLE), 0.55f);

    GetClip(R_DRAW)->SetEvent(bind(&Player::SetState, this, R_IDLE), 0.3f);
    GetClip(R_RELOAD)->SetEvent(bind(&Player::SetState, this, R_IDLE), 0.3f);

    GetClip(BW_FIRE)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);
    GetClip(M_ATTACK)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);
    GetClip(M_MINING)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);

    playerCollider = new CapsuleCollider(0.25f, 1.2f);
    playerLastPos = {};
    isCollision = false;

    weapons.resize(4);
       

    //ItemManager::Get()->GetConsumDV()[1].second = 3;
    ItemManager::Get()->GetBulletDV()[1].second = 20;

}

Player::~Player()
{
    delete CamTransform;
    delete frontPoint;
    delete testPalSpear;
    delete particle;
    delete playerCollider;
    delete summonPalSpear;
    delete summonPalSpearCollider;
    delete MiningCollider;

    weapons.clear();
}

void Player::Update()
{
    //if (!isCollision) // 테스트
    //{
    //    playerLastPos = ModelAnimator::GlobalPos();
    //}
    playerLastPos = ModelAnimator::GlobalPos();

    
    if (isAiming)
    {
        //CAM->Pos() = foCam;
        CAM->Pos() = Lerp(ogCam, foCam, 0.8f);
    }
    else
    {
        //CAM->Pos() = ogCam;
        CAM->Pos() = Lerp(foCam, ogCam, 0.8f);

    }
    if (isBuild)
    {
        SetState(BUILD);
        if (!SOUND->IsPlaySound("Build"))
        {
            SOUND->Play("Build");
        }
        
    }
    else
    {
        if (curState == BUILD) SetState(IDLE);
        SOUND->Stop("Build");
    }
    if (isWork)
    {
        SetState(WORK);
        if (!SOUND->IsPlaySound("Work"))
        {
            SOUND->Play("Work");
        }
       
    }
    else
    {
        if (curState == WORK) SetState(IDLE);
        SOUND->Stop("Work");
    }

    CamTransform->Pos() = this->Pos();

    testFrontSphere->Pos() = frontPoint->GlobalPos();

    //ClipSync();
    CamTransform->UpdateWorld();
    frontPoint->UpdateWorld();

    if (!UiManager::Get()->GetUiOn())
    {
        Control();
    }

    SetAnimation();

    //
    playerCollider->Pos() = this->Pos() + Vector3(0, 0.8f, 0);
        
    
    Hand->SetWorld(GetTransformByNode(68));

    if (curState == IDLE) MiningCollider->SetActive(false);
    FOR(weapons.size())
    {
        if (weapons[i] != nullptr)
        {
            if (ItemManager::Get()->GetEquipV()[i]->num == 3)
            {
                MiningCollider->SetParent(weapons[i]->GetParent());
                MiningCollider->Pos() = Vector3(0.0f, 0.3f, 0.0f);
            }

            weapons[i]->SetParent(Hand);
            weapons[i]->UpdateWorld();
        }


    }
    
    MoveSound();

    ModelAnimator::Update();
    PalSpearManager::Get()->Update();
    playerCollider->UpdateWorld();

    testFrontSphere->UpdateWorld();

    particle->Update();
    if (MiningCollider->Active()) MiningCollider->UpdateWorld();

    // 팰 스피어 던지기 관련
    ThrowPalSpear();
    summonPalSpear->UpdateWorld();
    summonPalSpearThrow->UpdateWorld();
    summonPalSpearCollider->UpdateWorld();

    Collision();

    Audio::Get()->Update();
}

void Player::Render()
{
    particle->Render();

    testPalSpear->Render();
    testFrontSphere->Render();

    ModelAnimator::Render();
    PalSpearManager::Get()->Render();

    //
    
    playerCollider->Render();

    summonPalSpear->Render();
    summonPalSpearThrow->Render();
    summonPalSpearCollider->Render();

    //
    FOR(weapons.size())
    {
        if (weapons[select - 1] != nullptr)  weapons[select - 1]->Render();

    }
    if (MiningCollider->Active()) MiningCollider->Render();
}

void Player::ShadowRender()
{
    ModelAnimator::SetShader(L"Light/DepthMap.hlsl");
    ModelAnimator::Render();
    ModelAnimator::SetShader(L"Model/ModelAnimation.hlsl");

}

void Player::GUIRender()
{
    //ModelAnimator::GUIRender();
    
    //PalSpearManager::Get()->GUIRender();
    //ImGui::Text("selNum : %d", curState);
    ImGui::Text("runTime : %f", runTime);

}

void Player::ClipSync()
{
    if ((ACTION)frameBuffer->Get().cur.clip != action)
    {
        PlayClip((int)action);
    }
}

void Player::Control()
{
    Move();

    // ???? : ?? ???, ???? ?????? ???? ?????? ?????? ????
    testPalSpear->SetActive(false);

    if (KEY_PRESS(VK_LSHIFT))
    {
        isRun = true;
    }
    else
    {
        isRun = false;
    }

    if (mouseWheel == 1)
    {
        mouseWheel = 0;
        select++;
        //SetState(R_DRAW);
        if (select > 4)
        {
            select = 1;

        }
    }
    else if (mouseWheel == 2)
    {
        mouseWheel = 0;

        select--;
        if (select < 1)
        {
            select = 4;
        }
    }

    if (ItemManager::Get()->GetEquipV()[select - 1] != nullptr)
    {
        switch (ItemManager::Get()->GetEquipV()[select - 1]->num)
        {
        case 1:
            isGun = true;
            isBow = false;
            if (KEY_DOWN('R') && (0 <= ItemManager::Get()->GetBulletDV()[1].second < 30))
            {
                SetState(R_RELOAD);
                SOUND->Play("Gun_Reload");
                int bullet = 30 - ItemManager::Get()->GetBulletDV()[1].second;
                int reload = min(bullet, ItemManager::Get()->GetConsumDV()[2].second);

                ItemManager::Get()->GetConsumDV()[2].second -= reload;
                ItemManager::Get()->GetBulletDV()[1].second += reload;

            }

            break;
        case 2:
            isBow = true;
            isGun = false;
            break;
        case 3:
            // mining or spear
            isGun = false;
            isBow = false;
            break;
        default:
            isGun = false;
            isBow = false;
            //othere weapon
            break;

        }

    }
    else
    {
        isGun = false;
        isBow = false;

    }


    if (KEY_PRESS(VK_RBUTTON))
    {
        isAiming = true;


        if (ItemManager::Get()->GetEquipV()[select - 1] != nullptr)
        {
            W_Aiming = true;

            switch (ItemManager::Get()->GetEquipV()[select - 1]->num)
            {
            case 1:
                isGaim = true;
                break;
            case 2:
                isBaim = true;
                break;
            case 3:
                //  isSpearAiming = true;
                break;
            default:
                isGaim = false;
                isBaim = false;
                break;
            }
            if (KEY_DOWN(VK_LBUTTON)) // ?? ????
            {
                AttackPal();
            }


        }
    }
    else if (KEY_UP(VK_RBUTTON))
    {
        isAiming = false;
        W_Aiming = false;
        isGaim = false;
        isBaim = false;
    }
    else if ((KEY_PRESS('Q') && ItemManager::Get()->GetConsumDV()[1].second > 0)
        || 
        (KEY_PRESS('E') && PlayerPalsManager::Get()->GetSelPal() != -1 &&
            selPal != -1 &&
            PlayerPalsManager::Get()->GetPal(selPal) != nullptr &&
!PlayerPalsManager::Get()->GetPal(selPal)->isDead )) // 소환은 소환할 팰이 죽지 않았을 때만
    {
        if (curState != S_THROW )//&& ItemManager::Get()->GetConsumDV()[1].second != 0)
        {
            SetState(ACTION::S_AIM);
            isAiming = true;
            summonPalSpear->SetActive(true);
        }
    }
    else if (KEY_UP('Q'))
    {
        if (curState == S_AIM)
        {
            CatchPal();
            isAiming = false;
            summonPalSpear->SetActive(false);
            Float3 tmpPos = summonPalSpear->GlobalPos();
            SOUND->Stop("Sphere_Flash");
            SOUND->Play("Sphere_Flash", tmpPos);
            ItemManager::Get()->GetConsumDV()[1].second--;

        }
    }
    else if (KEY_UP('E'))
    {
        if (curState == S_AIM)
        {
            PlayerPalsManager::Get()->SetSelPal(selPal);
            SummonsPal();
            isAiming = false;
            summonPalSpear->SetActive(false);
            summonPalSpearThrow->SetActive(true);
            summonPalSpearThrow->Pos() = summonPalSpear->GlobalPos();
            CAM->UpdateWorld();
            summonPalSpearDIr = CAM->Forward();
            PlayerPalsManager::Get()->SUmmonedPalActiveFalse();
            Float3 tmpPos = summonPalSpear->GlobalPos();
            SOUND->Stop("Sphere_Flash");
            SOUND->Play("Sphere_Flash", tmpPos);
        }

    }
    else if (KEY_UP('G'))
    {
        if (ItemManager::Get()->GetEquipV()[select - 1] != nullptr &&
            ItemManager::Get()->GetEquipV()[select-1]->num == 3)
        {
            MiningCollider->SetActive(true);
            SetState(M_MINING);
        }
        //else MiningCollider->SetActive(false);

    }

    if (KEY_DOWN('Z'))
    {
        test = !test;
        if (test)
        {
            ShowCursor(false);
        }
        else
        {
            ShowCursor(true);
        }
    }



    if (test)
    {
        Rotate();
    }
    Jump(LandScapeManager::Get()->GetTerrain()->GetHeight(Pos()));
}

void Player::Move()
{
    if (curState == S_THROW || curState == M_MINING || curState == WORK || curState == BUILD)
    {
        return;
    }
    bool isMoveZ = false;
    bool isMoveX = false;


    if (W_Aiming)
    {

        // CamTransform->Rot().y = Rot().y;

        if (KEY_PRESS('W'))
        {
            velocity.z += DELTA;

            isMoveZ = true;
        }

        if (KEY_PRESS('S'))
        {
            velocity.z -= DELTA;
            isMoveZ = true;
        }

        if (KEY_PRESS('A'))
        {
            velocity.x -= DELTA;
            isMoveX = true;
        }

        if (KEY_PRESS('D'))
        {
            velocity.x += DELTA;
            isMoveX = true;
        }



        if (velocity.Length() > 1) velocity.Normalize();



        if (!isMoveZ)
            velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //???????? ????

        if (!isMoveX)
            velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

        Matrix rotY = XMMatrixRotationY(Rot().y);
        Vector3 direction = XMVector3TransformCoord(velocity, rotY);
        //direction.y;


        Pos() += direction * moveSpeed * DELTA * -1;
    }
    else
    {

        if (KEY_PRESS('W'))
        {
            w = -CamTransform->Forward();
            isMoveZ = true;
        }
        else
        {
            w = z;
        }



        if (KEY_PRESS('S'))
        {
            s = -CamTransform->Back();
            isMoveZ = true;
        }
        else
        {
            s = z;
        }


        if (KEY_PRESS('A'))
        {
            a = -CamTransform->Left();
            isMoveX = true;
        }
        else
        {
            a = z;
        }


        if (KEY_PRESS('D'))
        {
            d = -CamTransform->Right();
            isMoveX = true;
        }
        else
        {
            d = z;
        }

        if (KEY_DOWN(VK_SPACE))
        {
            action = J_START;
            jumpVelocity = jumpForce;
            isJump = true;
            isSpace = true;
        }

        if (w + a + s + d == 0)
        {
            velocity.z = 0;
            velocity.x = 0;
            velocity.y = 0;
            return;
        }
        

        velocity = w + a + s + d;
        velocity.Normalize();

        //???????? ??u???
        Vector3 forward = Forward();
        Vector3 cross = Cross(forward, velocity);

        Pos() += velocity * moveSpeed * DELTA;

        float dotV = Dot(forward, velocity);
        //if (NearlyEqual(dotV, -1.0f)) return;
        if (dotV <= -0.999f && dotV >= -1.0f) return;

        //if (cross.y < -0.01f)
        if (cross.y < 0.0f)
        {
            //Rot().y = Lerp(Rot().y, Rot().y + 5 * DELTA, 0.5f);
            Rot().y += 8 * DELTA;
            
        }
        //else if (cross.y > 0.01f)
        else if (cross.y >= 0.0f)
        {
            //Rot().y = Lerp(Rot().y, Rot().y - 5 * DELTA, 0.5f);

            Rot().y -= 8 * DELTA;
        }



        
    }

    if (velocity.Length() <= 0)
    {
        SOUND->Stop("Run");
        SOUND->Stop("Walk");
    }



}

void Player::Rotate()
{

    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
    CamTransform->Rot().y += delta.x * rotSpeed * DELTA;

    if (isAiming)   Rot().y = CamTransform->Rot().y;



}

void Player::Jump(float _ground)
{
    jumpVelocity -= 9.8f * gravityMult * DELTA;
    Pos().y += jumpVelocity;

    if (Pos().y > _ground + 0.5f)
    {
        if (action != J_LOOP) action = J_LOOP;

        isJump = true;
        if (SOUND->IsPlaySound("Run")) SOUND->Stop("Run");
        if (SOUND->IsPlaySound("Walk")) SOUND->Stop("Walk");
    }
    else if (Pos().y < _ground)
    {

        //Pos().y = _ground;
        Pos().y = Lerp(Pos().y, _ground, 10 * DELTA);
        jumpVelocity = 0;
        if (curState == J_LOOP)
        {
            SetState(J_END);
            SOUND->Play("JumpLanding", 0.4f);
        }
        isJump = false;
        isSpace = false;

    }
    

}

void Player::Collision()
{
    //isCollision = false; // 끼임 방지, 충돌하면 라스트 포스 갱신안함

    // 필드 스킬에 맞으면
    if (FieldPalSkillManager::Get()->GetFieldSkills().size() != 0)
    {
        for (int i = 0; i < FieldPalSkillManager::Get()->GetFieldSkills().size(); i++)
        {
            if (FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetCol()->IsCollision(playerCollider))
                // 스킬이 매개변수 'collider'에 충돌했다면
            {
                if (FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetName() == "얼음창")
                {
                    FieldPalSkillManager::Get()->GetFieldSkills()[i]->SetActive(false); // <-이 줄이 없으면 관통탄이 된다
                    curHP -= FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetDamage();

                }
                else if (FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetName() == "스파이크")
                {
                    curHP -= FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetDamage();
                    FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetCol()->SetActive(false);
                }
                else
                {
                    curHP -= DELTA * FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetDamage();
                }
                //skill->SetActive(false); // <-이 줄이 없으면 관통탄이 된다
                if (curHP < 0)
                {
                    curHP = 0;
                }
                FieldPalSkillManager::Get()->GetFieldSkills()[i]->SkillHitSound(GlobalPos());
                return;
            }
        }
    }
    

    // 필드 팰 충돌시
    for (Pal* pal : PalsManager::Get()->GetPalsVector())
    {
        if (playerCollider->IsCollision(pal->GetCollider()))
        {
            Vector3 nol = GlobalPos() - pal->GetTransform()->GlobalPos();
            nol.y = 0;
            nol = nol.GetNormalized();
            Vector3 dir = GlobalPos() - playerLastPos;
            dir.y = 0;
            Vector3 tmpV1 = dir;
            Vector3 tmpV2 = pal->GetTransform()->GlobalPos() - GlobalPos();
            tmpV2.y = 0;
            if (Dot(tmpV1, tmpV2) <= 0.0f) continue;
            Vector3 mDir = dir * -1;
            Vector3 tmp = nol * Dot(mDir, nol);
            Vector3 fDir = dir + tmp;
            ModelAnimator::Pos() = playerLastPos + fDir;
            ModelAnimator::UpdateWorld();
            //isCollision = true;
        }
    }
    // 장애물
    for (Collider* obs : LandScapeManager::Get()->GetObstacles())
    {
        if (playerCollider->IsCollision(obs) && obs->Active())
        {
            Vector3 nol = GlobalPos() - obs->GlobalPos();
            nol.y = 0;
            nol = nol.GetNormalized();
            Vector3 dir = GlobalPos() - playerLastPos;
            dir.y = 0;
            Vector3 tmpV1 = dir;
            Vector3 tmpV2 = obs->GlobalPos() - GlobalPos();
            tmpV2.y = 0;
            if (Dot(tmpV1, tmpV2) <= 0.0f) continue;
            Vector3 mDir = dir * -1;
            Vector3 tmp = nol * Dot(mDir, nol);
            Vector3 fDir = dir + tmp;
            ModelAnimator::Pos() = playerLastPos + fDir;
            ModelAnimator::UpdateWorld();
            //isCollision = true;
        }
    }


    // 나무
    //for (Tree* tree : LandScapeManager::Get()->GetTrees())
    //{
    //    if (playerCollider->IsCollision(tree->GetCollider()) && tree->GetTransform()->Active())
    //    {
    //        Vector3 nol = GlobalPos() - tree->GetTransform()->GlobalPos();
    //        nol.y = 0;
    //        nol = nol.GetNormalized();
    //        Vector3 dir = GlobalPos() - playerLastPos;
    //        dir.y = 0;
    //        Vector3 tmpV1 = dir;
    //        Vector3 tmpV2 = tree->GetTransform()->GlobalPos() - GlobalPos();
    //        tmpV2.y = 0;
    //        if (Dot(tmpV1, tmpV2) <= 0.0f) continue;
    //        Vector3 mDir = dir * -1;
    //        Vector3 tmp = nol * Dot(mDir, nol);
    //        Vector3 fDir = dir + tmp;
    //        ModelAnimator::Pos() = playerLastPos + fDir;
    //        ModelAnimator::UpdateWorld();
    //        //isCollision = true;
    //
    //    }
    //}
    //// 돌
    //for (Rock* rock : LandScapeManager::Get()->GetRocks())
    //{
    //    if (playerCollider->IsCollision(rock->GetCollider()))
    //    {
    //        Vector3 nol = GlobalPos() - rock->GetTransform()->GlobalPos();
    //        nol.y = 0;
    //        nol = nol.GetNormalized();
    //        Vector3 dir = GlobalPos() - playerLastPos;
    //        dir.y = 0;
    //        Vector3 tmpV1 = dir;
    //        Vector3 tmpV2 = rock->GetTransform()->GlobalPos() - GlobalPos();
    //        tmpV2.y = 0;
    //        if (Dot(tmpV1, tmpV2) <= 0.0f) continue;
    //        Vector3 mDir = dir * -1;
    //        Vector3 tmp = nol * Dot(mDir, nol);
    //        Vector3 fDir = dir + tmp;
    //        ModelAnimator::Pos() = playerLastPos + fDir;
    //        ModelAnimator::UpdateWorld();
    //        //isCollision = true;
    //    }
    //}
}

void Player::AttackPal()
{
    // *???? ??? ???
    //Ray ray;
    //ray.pos = GlobalPos();
    //ray.dir = CamTransform->Forward();
    //Vector3 hitPoint;

    Ray ray = CAM->ScreenPointToRay(mousePos);
    Vector3 hitPoint;
            
    switch (ItemManager::Get()->GetEquipV()[select - 1]->num)
    {
    case 1:
        if (0 < ItemManager::Get()->GetBulletDV()[1].second)
        {
            SOUND->Play("Gun_Fire");
            ItemManager::Get()->GetBulletDV()[1].second--;
          
            if (PalsManager::Get()->IsCollision(ray, hitPoint))
            {
                particle->Play(hitPoint);
            }
        }
        break;
    case 2:
        SetState(BW_FIRE);
        break;
    case 3:
        SetState(M_ATTACK);
        SOUND->Play("Pick_Attack",1,1);
             

        break;
    default:

        break;
    }



    //  BulletManager::Get()->Throw(Gun->GlobalPos(), ray.dir);

}

void Player::CatchPal()
{
    if (curState == S_THROW)
    {
        return;
    }
    SetState(S_THROW);

    //Ray ray = CAM->ScreenPointToRay(mousePos);

    //Ray ray;
    //ray.pos = CAM->GlobalPos();
    //ray.dir = CAM->Forward();
    //Vector3 hitPoint;

    // ????? ????? ????
    CAM->UpdateWorld();
    Vector3 tmpF = CAM->Forward();
    tmpF.y = 0.0f;
    tmpF = tmpF.GetNormalized(); // 앞에서
    Vector3 tmp = CAM->GlobalPos() + CAM->Left() * 0.4f + tmpF * 1.5f + Vector3(0.0f, 1.0f, 0.0f) * 0.2f;
    //tmp.x -= 0.3f;
    //tmp.y += 1.7f;
    //ray.dir += {0, 0.3f, 0};
   // PalSpearManager::Get()->Throw(tmp, ray.dir);
    PalSpearManager::Get()->Throw(summonPalSpear->GlobalPos(), CAM->Forward());

}

void Player::SummonsPal()
{
    SetState(ACTION::S_THROW);
}

void Player::ThrowPalSpear()
{
    if (!summonPalSpearThrow->Active()) return;
    downForce += gravi * DELTA;

    Vector3 tmp = (down * downForce);

    summonPalSpearThrow->Pos() += summonPalSpearDIr * speed * DELTA;
    summonPalSpearThrow->Pos() += tmp * DELTA;
    if (summonPalSpearThrow->Pos().y < LandScapeManager::Get()->GetTerrain()->GetHeight(summonPalSpearThrow->GlobalPos()))
    {
        summonPalSpearThrow->Pos().y = LandScapeManager::Get()->GetTerrain()->GetHeight(summonPalSpearThrow->GlobalPos());
        downForce = 0.0f;
        speed = 20.0f;
        summonPalSpearThrow->SetActive(false);
        PlayerPalsManager::Get()->Summons(summonPalSpearThrow->GlobalPos());
    }
}

void Player::MoveSound()
{
    if (curState == RUN || curState == R_RUN)
    {
        walkTime = 0.0f;
        runTime += DELTA;
        if (runTime > 0.45f)
        {
            //if (!SOUND->IsPlaySound("Run")) SOUND->Play("Run");
            SOUND->Stop("Run"), SOUND->Play("Run");
            runTime = 0.0f;
        }
    }
    else if (curState == WALK || curState == S_AIM || curState == BW_AIM || curState == R_Aim || curState == RA_FWD)
    {
        runTime = 0.0f;
        walkTime += DELTA;
        if (walkTime > 0.47f)
        {
            //if (!SOUND->IsPlaySound("Walk")) SOUND->Play("Walk");
            SOUND->Stop("Walk"), SOUND->Play("Walk");
            walkTime = 0.0f;
        }
    }
    else
    {
        SOUND->Stop("Walk"), SOUND->Stop("Run");
        walkTime = 0.0f;
        runTime = 0.0f;
    }

}

void Player::UiMode()
{
    UiOn = !UiOn;
}

void Player::SetAnimation()
{

    if (curState == J_LOOP)
    {
        ClipOnce();
        return;
    }
    else if (curState == S_THROW || curState == S_AIM || curState == R_RELOAD || curState == BW_FIRE || curState == M_ATTACK || curState == M_MINING
       || curState == WORK || curState == BUILD)
    {
        return;
    }

    if (isBow)
    {
        if (isBaim) SetState(BW_AIM);
        else
        {
            if (velocity.Length() > 0) SetState(RUN);
            else  SetState(IDLE);
        }

        return;
    }
    else if (isGun)
    {
        if (isGaim)
        {
            //if (SOUND->IsPlaySound("Run")) SOUND->Stop("Run");

            if (velocity.Length() > 0) SetState(RA_FWD);
            else SetState(R_Aim);
        }
        else
        {
            if (velocity.Length() > 0)
            {
                SetState(R_RUN);
                //if (SOUND->IsPlaySound("Walk"))SOUND->Stop("Walk");
                //if (!SOUND->IsPlaySound("Run")) SOUND->Play("Run");
            }
            else SetState(R_IDLE);
        }
        return;
    }

    if (isJump)
    {
        SetState(J_START);
    }
    else
    {
        if (velocity.Length() > 0)
        {
           
            if (isRun)
            {
                SetState(RUN);
                //SOUND->Stop("Walk");
                //walkTime = 0.0f;
                //runTime += DELTA;
                //if (runTime > 0.45f)
                //{
                //    //if (!SOUND->IsPlaySound("Run")) SOUND->Play("Run");
                //    SOUND->Stop("Run"), SOUND->Play("Run");
                //    runTime = 0.0f;
                //}

            }
            else
            {
                SetState(WALK);
                //SOUND->Stop("Run");
                //runTime = 0.0f;
                //walkTime += DELTA;
                //if (walkTime > 0.47f)
                //{
                //    //if (!SOUND->IsPlaySound("Walk")) SOUND->Play("Walk");
                //    SOUND->Stop("Walk"), SOUND->Play("Walk");
                //    walkTime = 0.0f;
                //}
            }

        }
        else
        {
            SetState(IDLE);
            walkTime = 0.0f;
            runTime = 0.0f;

        }
    }

}

void Player::SetState(ACTION state)
{
    if (state == curState) return;

    curState = state;
    PlayClip((int)state);

}
