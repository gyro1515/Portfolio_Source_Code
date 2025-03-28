#include "Framework.h"

PalSpear::PalSpear(Transform* transform) : transform(transform)
{
    transform->Scale() = { 0.02f, 0.02f, 0.02f }; // 크기 기본값은 1
                                      // 나중에 크기가 바뀌어야 하면 와서 수정하게
    transform->Rot().x = XM_PIDIV2;

    terrain = nullptr;
    pal = nullptr;

    collider = new SphereCollider();
    collider->SetParent(transform);

    collider->Scale() = { 7, 7, 7 }; //크기 기본값은 1.0
    collider->Pos() = {};            //위치 기본값 : 부모 위치

    state = State::THROW;

    // StateHitPal용
    hitPalTime = 0.0f;

    // StateCatching용
    catchingTime = 0.0f;
    shakeNum = 0;
    shakeTime = 0;

    // 팰 흰색
    //renderTarget = new RenderTarget(2048, 2048); // 수동으로 투사할 공간의 크기 지정
    //depthStencil = new DepthStencil(2048, 2048);
    //
    //whitePal = new Quad(Vector2(1280, 720));
    //whitePal->Pos() = { 640, 360, 0 }; // 사각형을 (실제보다)살짝 당기는 이유 = 실제 위치가 사각형
    //whitePal->SetTag("WhitePal");
    //Texture* texture = Texture::Add(L"WhitePalTex", renderTarget->GetSRV());
    //// 실시간으로 생성되는 이미지를 텍스처화해서 "일렁임"이라는 이름으로
    //
    //whitePal->GetMaterial()->SetDiffuseMap(texture);
    ////whitePal->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
    //whitePal->UpdateWorld(); //

    //palSpearParticle = new ParticleSystem("TextData/Particles/PalSpear.fx");
    palSpearParticle = new ParticleSystem("TextData/Particles/PalSpearNotBill1.fx");
    particleTime = 0.0f;

}

PalSpear::~PalSpear()
{
    delete collider;
    delete palSpearParticle;
}

void PalSpear::Update()
{
    //비활성화 중에는 안 움직임
    if (!transform->Active()) return;

    switch (state)
    {
    case PalSpear::State::THROW:
        StateThrow();
        break;
    case PalSpear::State::HITPAL:
        StateHitPal();
        break;
    case PalSpear::State::ABSORB:
        StateAbsorb();
        break;
    case PalSpear::State::CATCHING:
        StateCatching();
        break;
    case PalSpear::State::SUCCESS:
        StateSuccess();
        break;
    case PalSpear::State::FAIL:
        StateFail();
        break;
    default:
        break;
    }

    collider->UpdateWorld();
    Vector3 tmpRot;
    Vector3 c = CAM->Forward();
    tmpRot.y = atan2(c.x, c.z);
    Vector2 a = { c.x, c.z };
    tmpRot.x = atan2(a.Length(), c.y) - XM_PIDIV2;
    //tmpRot.x = atanf(a.Length() / c.y);
    palSpearParticle->GetQuad()->Rot().x = tmpRot.x;
    palSpearParticle->GetQuad()->Rot().y = tmpRot.y;
    palSpearParticle->GetQuad()->Rot().z += 80* DELTA;

    palSpearParticle->Update();
}

void PalSpear::PreRender()
{
    
}

void PalSpear::Render()
{
    if (!transform->Active()) return;

    collider->Render();
    palSpearParticle->Render();

}

void PalSpear::PostRender()
{
    //whitePal->Render();
}

void PalSpear::GUIRender()
{
    //whitePal->GUIRender();
    if (!transform->Active()) return;
    ImGui::Text("Shake : %d", shakeNum);
    ImGui::Text("catchingTime : %f", catchingTime);
}

void PalSpear::Throw(Vector3 pos, Vector3 dir)
{
    //활성화
    transform->SetActive(true);
    collider->SetActive(true);
    transform->Pos() = pos;
    direction = dir;

    //방향에 맞게 모델(=트랜스폼) 회전 적용
    transform->Rot().y = atan2(dir.x, dir.z); //방향 적용 + 모델 정면에 따른 보정
    //transform->Rot().y = CAM->Rot().y; //방향 적용 + 모델 정면에 따른 보정
                                                          //쿠나이 모델은 90도 돌아가 있었음
    //transform->Rot().y = atan2(dir.x, dir.z) - XMConvertToRadians(90);
    //                                           ↑ 각도를 호도로 바꿔주는 함수

    time = 0; //경과시간 리셋
    downForce = 0.0f;
    state = State::THROW;
    // StateHitPal용
    hitPalTime = 0.0f;
    // StateCatching용
    catchingTime = 0.0f;
    shakeNum = 0;

    
}

void PalSpear::StateThrow()
{
    downForce += gravi * DELTA;

    Vector3 tmp = (down * downForce);

    transform->Pos() += direction * speed * DELTA;
    transform->Pos() += tmp * DELTA;
    speed -= DELTA * 5;
    if (speed <= 0.0f)
    {
        speed = 0.0f;
        if (transform->Pos().y <= terrain->GetHeight(transform->GlobalPos()))
        {
            transform->Pos().y = terrain->GetHeight(transform->GlobalPos());
            time += DELTA; // 시간 경과에 따라 변수에 누적
            if (time > LIFE_SPAN)
            {
                transform->SetActive(false);
                speed = 20.0f;
                downForce = 0.0f;
            }
        }
    }
    else if (transform->Pos().y < terrain->GetHeight(transform->GlobalPos()))
    {
        Vector3 normal;
        transform->Pos().y = terrain->GetHeight(transform->GlobalPos(), &normal);
        normal *= -1;
        //Vector3 tmpDir = (direction + tmp.GetNormalized()) * -1;
        Vector3 tmpDir = (direction * speed + tmp) * -1;
        tmpDir = tmpDir.GetNormalized();
        Vector3 tmpD = 2 * normal * (Dot(tmpDir, normal));
        tmpDir *= -1;
        //direction = (tmpDir + tmpD).GetNormalized();
        direction = tmpDir + tmpD;
        //downForce *= -0.6f;
        downForce = 0.0f;
        speed *= 0.8f;
    }
}

void PalSpear::StateHitPal()
{
    hitPalTime += DELTA;
    transform->Pos() += Vector3(0.0f, 1.0f, 0.0f) * 2 * DELTA;  // 위로
    transform->Pos() += PlayerManager::Get()->GetPlayer()->Forward() * DELTA; // 던지는 방향 반대
    transform->Pos() += PlayerManager::Get()->GetPlayer()->Left() * 2 * DELTA; // 오른쪽
    if (hitPalTime > 0.4f)
    {
        state = State::ABSORB;
        hitPalTime = 0.0f;
        pal->GetTransform()->SetActive(false);
        pal->GetCollider()->SetActive(false);

        // 이펙트 활성화
        palSpearParticle->Play(pal->GetCollider()->GlobalPos());
        palToPalSpearVel = transform->Pos() - palSpearParticle->GetPos();
    }
}

void PalSpear::StateAbsorb()
{
    // 이펙트 팰 스피어로 이동
    Vector3 tmp = palSpearParticle->GetPos() + palToPalSpearVel * DELTA;
    palSpearParticle->SetPos(tmp);
    particleTime += DELTA;
    if (particleTime >= 1.3f)
    {
        particleTime = 0.0f;
        state = State::CATCHING;
        Float3 tmpPos = transform->GlobalPos();
        SOUND->Stop("Sphere_Shake");
        SOUND->Play("Sphere_Shake", tmpPos);
    }


}

void PalSpear::StateCatching()
{
    catchingTime += DELTA;
    if (catchingTime > 0.5f)
    {
        transform->Rot().x = XM_PIDIV2;
        transform->Rot().y = 0;
        transform->Rot().z = 0;

        if (catchingTime > 1.0f)
        {
            catchingTime = 0.0f;
            shakeNum++;

            if (shakeNum >= 3)
            {
                shakeNum = 0;
                if (RANDOM->Int(0,1) == 0)
                {
                    state = State::SUCCESS;
                }
                else
                {
                    state = State::FAIL;
                }
            }
            else
            {
                Float3 tmpPos = transform->GlobalPos();
                SOUND->Stop("Sphere_Shake");
                SOUND->Play("Sphere_Shake", tmpPos);
            }
        }
        
    }
    else
    {
        float tmpRX = RANDOM->Float(-45.0f, 45.0f);
        float tmpRY = RANDOM->Float(-90.0f, 90.0f);
        float tmpRZ = RANDOM->Float(-20.0f, 20.0f);
        tmpRX = XM_PIDIV2 + XMConvertToRadians(tmpRX);
        tmpRY = XMConvertToRadians(tmpRY);
        tmpRZ = XMConvertToRadians(tmpRZ);
        transform->Rot().x = Lerp(transform->Rot().x, tmpRX, 0.5f);
        transform->Rot().y = Lerp(transform->Rot().x, tmpRY, 0.5f);
        transform->Rot().z = Lerp(transform->Rot().x, tmpRZ, 0.5f);
    }
    
    
}

void PalSpear::StateSuccess()
{
    PlayerPalsManager::Get()->Caught(pal);
    // 이후 죽음처리, 나중에 다시 스폰될 것
    pal->isDead = true;

    transform->SetActive(false);
    collider->SetActive(false);
    state = State::THROW;
    pal->isInvincible = false;
    Float3 tmpPos = transform->GlobalPos();
    SOUND->Stop("Sphere_Success");
    SOUND->Play("Sphere_Success", tmpPos);
}

void PalSpear::StateFail()
{
    pal->GetTransform()->SetActive(true);
    pal->GetCollider()->SetActive(true);

    transform->SetActive(false);
    collider->SetActive(false);
    state = State::THROW;
    pal->isInvincible = false;

}

void PalSpear::SetRenderTarget()
{
    //renderTarget->Set(depthStencil);
    //renderTarget->Set(depthStencil,Float4(1,1,1,0));

}
