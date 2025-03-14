#include "Framework.h"

#include "Scenes/StudyScene/CubeScene.h"
#include "Scenes/StudyScene/GridScene.h"
#include "Scenes/StudyScene/SphereScene.h"
#include "Scenes/StudyScene/TerrainEditorScene.h"
#include "Scenes/StudyScene/CollisionScene.h"
#include "Scenes/StudyScene/ModelExportScene.h"
#include "Scenes/StudyScene/ModelRenderScene.h"
#include "Scenes/StudyScene/ModelAnimationScene.h"
#include "Scenes/StudyScene/IntancingScene.h"
#include "Scenes/StudyScene/GameScene.h"
#include "Scenes/StudyScene/BillboardScene.h"
#include "Scenes/StudyScene/RenderTargetScene.h"
#include "Scenes/StudyScene/ShadowScene.h"
#include "Scenes/StudyScene/DijkstraScene.h"
#include "Scenes/StudyScene/AStarScene.h"
#include "Scenes/StudyScene/ParticleScene.h"
#include "Scenes/StudyScene/ParticleConfigScene.h"
#include "Scenes/StudyScene/HumanScene.h"
#include "Scenes/StudyScene/QuadTreeScene.h"
#include "Scenes/StudyScene/TerrainLODScene.h"
#include "Scenes/StudyScene/WaterScene.h"
#include "Scenes/GameScene/TitleScene.h"
#include "Scenes/GameScene/LoadingScene.h"
#include "Scenes/GameScene/LoadingScene_2.h"
#include "Scenes/GameScene/BaseScene1.h"
#include "Scenes/GameScene/BossScene.h"

GameManager::GameManager()
{
    Create();

    SetSound();
    Collider::RenderOnOff();

    //SceneManager::Get()->Create("NewScene", new BaseScene1());
    //SceneManager::Get()->Create("Loading_2", new LoadingScene_2());
    //SceneManager::Get()->Create("Loading", new LoadingScene());
    SceneManager::Get()->Create("Title", new TitleScene());

    //SceneManager::Get()->Add("NewScene
    SceneManager::Get()->Add("Loading_2");
    SceneManager::Get()->Add("Loading");
    SceneManager::Get()->Add("Title");

    SceneManager::Get()->ChangeScene("Title");

    //SceneManager::Get()->Add("NewScene");
    //SceneManager::Get()->ChangeScene("NewScene");

    //SceneManager::Get()->Add("Loading");

    //SceneManager::Get()->Create("ModelExport", new ModelExportScene());
    //SceneManager::Get()->Create("Grid", new GridScene());
    //SceneManager::Get()->Create("Cube", new CubeScene());
    //SceneManager::Get()->Create("Sphere", new SphereScene());
    //SceneManager::Get()->Create("Terrain", new TerrainEditorScene());
    //SceneManager::Get()->Create("Collision", new CollisionScene());
    //SceneManager::Get()->Create("ModelRender", new ModelRenderScene());
    //SceneManager::Get()->Create("ModelAnimationScene", new ModelAnimationScene());
    //SceneManager::Get()->Create("Instancing", new IntancingScene());
    //SceneManager::Get()->Create("Game", new GameScene());
    //SceneManager::Get()->Create("BillboardScene", new BillboardScene());
    //SceneManager::Get()->Create("RenderTarget", new RenderTargetScene());
    //SceneManager::Get()->Create("ShadowScene", new ShadowScene());
    //SceneManager::Get()->Create("Dijkstra", new DijkstraScene());
    //SceneManager::Get()->Create("AStar", new AStarScene());
    //SceneManager::Get()->Create("Particle", new ParticleScene());
    //SceneManager::Get()->Create("ParticleConfig", new ParticleConfigScene());
    //SceneManager::Get()->Create("HumanScene", new HumanScene());
    //SceneManager::Get()->Create("QuadTree", new QuadTreeScene());
    //SceneManager::Get()->Create("LOD", new TerrainLODScene());
    //SceneManager::Get()->Create("WaterScene", new WaterScene());

    //SceneManager::Get()->Add("Grid");
    //SceneManager::Get()->Add("ModelExport");
    //SceneManager::Get()->Add("ModelRender");
    //SceneManager::Get()->Add("ModelAnimationScene");
    //SceneManager::Get()->Add("Collision");
    //SceneManager::Get()->Add("Instancing");
    //SceneManager::Get()->Add("Game");
    //SceneManager::Get()->Add("BillboardScene");
    //SceneManager::Get()->Add("RenderTarget");
    //SceneManager::Get()->Add("ShadowScene");
    //SceneManager::Get()->Add("Dijkstra");
    //SceneManager::Get()->Add("AStar");
    //SceneManager::Get()->Add("Particle");
    //SceneManager::Get()->Add("ParticleConfig");
    //SceneManager::Get()->Add("HumanScene");
    //SceneManager::Get()->Add("QuadTree");
    //SceneManager::Get()->Add("LOD");
    //SceneManager::Get()->Add("WaterScene");

    


}

GameManager::~GameManager()
{
    Delete();
}

void GameManager::Update()
{
    //m.lock();

    Keyboard::Get()->Update();
    Timer::Get()->Update();    

    SceneManager::Get()->Update();

    Environment::Get()->Update();
    //m.unlock();

}

void GameManager::Render()
{

    SceneManager::Get()->PreRender();
    
    Device::Get()->Clear();
    Font::Get()->GetDC()->BeginDraw();
    
    Environment::Get()->Set();    
    SceneManager::Get()->Render();
    
    Environment::Get()->PostSet();
    SceneManager::Get()->PostRender();

    m.lock();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    Font::Get()->RenderText(fps, { 10, WIN_HEIGHT - 3 });
    
    //static bool isActive = true;
    static bool isActive = false;

    if (isActive)
    {
        ImGui::Begin("Inspector", &isActive);
        Environment::Get()->GUIRender();
        SceneManager::Get()->GUIRender();
        ImGui::End();
    }    

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    

    Font::Get()->GetDC()->EndDraw();

    Device::Get()->Present();
    m.unlock();

}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();
    Observer::Get();
    Audio::Get();
    
    Font::Get()->AddColor("White", 1, 1, 1);
    Font::Get()->AddColor("Gray", 
        149.0f/ 255.0f, 
        214.0f / 255.0f, 
        181.0f / 255.0f);

    Font::Get()->AddStyle("Default", L"배달의민족 주아");
    Font::Get()->AddStyle("Default2", L"배달의민족 주아", 20.0f,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_CENTER);
    // partyBox
    Font::Get()->AddStyle("PartyBoxNum", L"Oxanium", 20.0f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_LEADING);
    Font::Get()->AddStyle("PartyBoxLV", L"Noto Sans", 12.0f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_LEADING);
    Font::Get()->AddStyle("PartyBoxName", L"Noto Sans KR", 15.0f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_LEADING);
    

    // Field UI
    Font::Get()->AddStyle("HpUI", L"Oxanium", 13.0f,
        DWRITE_FONT_WEIGHT_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_LEADING);
    Font::Get()->AddStyle("FieldLvNum", L"Oxanium", 14.0f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_LEADING);
    Font::Get()->AddStyle("FieldLv", L"Noto Sans", 8.4f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_LEADING);
    Font::Get()->AddStyle("FieldName", L"Noto Sans KR", 11.0f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_LEADING);
    Font::Get()->AddStyle("FieldEquibName", L"Noto Sans KR", 11.0f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_CENTER);
    Font::Get()->AddStyle("FieldPlay", L"Noto Sans KR", 11.0f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_TRAILING);
    Font::Get()->AddStyle("FieldNum1", L"Oxanium", 28.0f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_CENTER);
    Font::Get()->AddStyle("FieldNum2", L"Oxanium", 31.0f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_CENTER);
    Font::Get()->AddStyle("FieldNum3", L"Oxanium", 15.0f,
        DWRITE_FONT_WEIGHT_MEDIUM,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT_CENTER);


    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");

    Texture::Add(L"Textures/Color/White.png");
    
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();    
    Observer::Delete();
    Font::Delete();
    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    
    ImGui::DestroyContext();
}

void GameManager::SetSound()
{
    // action
//SOUND->Add("Walk", "Sounds/Action/WalkGrass.wav", false, true);
//SOUND->Add("Run", "Sounds/Action/RunGrass.wav", false, true);
    SOUND->Add("Walk", "Sounds/Action/WalkGrass.wav");
    SOUND->Add("Run", "Sounds/Action/RunGrass.wav");
    SOUND->Add("JumpLanding", "Sounds/Action/JumpLanding.wav");
    SOUND->Add("Work", "Sounds/Action/WorkBenchWork.wav", false, true);
    SOUND->Add("Build", "Sounds/Action/Hammer.wav", false, true);
    SOUND->Add("Gun_Aim", "Sounds/Action/Gun_Aim.wav");
    SOUND->Add("Gun_Draw", "Sounds/Action/Gun_Draw.wav");
    SOUND->Add("Gun_Fire", "Sounds/Action/Gun_Fire.wav");
    SOUND->Add("Gun_Reload", "Sounds/Action/Gun_Reload.wav");
    SOUND->Add("Pick_Attack", "Sounds/Action/Pick_Attack.wav", false, true);
    //SOUND->Add("Pickdraw", "Sounds/Action/pickdraw.wav");
    SOUND->Add("Pick_HitWood", "Sounds/Action/pickhit1.wav");
    //SOUND->Add("Pickhit2", "Sounds/Action/pickhit2.wav");
    SOUND->Add("Pick_HitRock", "Sounds/Action/pickhit3.wav");


    // skill
    SOUND->Add("IceMissileHit_1", "Sounds/Skill/IceMissileHit_1.wav");
    SOUND->Add("IceMissileHit_2", "Sounds/Skill/IceMissileHit_2.wav");
    SOUND->Add("IceMissileShoot", "Sounds/Skill/IceMissileShoot.wav");
    SOUND->Add("WindCutterHit", "Sounds/pal/WindCutterHit.mp3");
    //SOUND->Add("WindCutterHit", "Sounds/Skill/WindCutterHit.wav");
    SOUND->Add("WindCutterShoot", "Sounds/Skill/WindCutterShoot.wav");
    SOUND->Add("EarthQuakeHit", "Sounds/pal/EarthQuakeHit.wav");
    SOUND->Add("EarthQuaSet", "Sounds/pal/earthQuaSet.wav");

    // ui
    //SOUND->Add("BGM_Battle", "Sounds/UI/BGM_Battle.wav", true, true);
    SOUND->Add("BGM_Title", "Sounds/UI/Title.wav", true, true);
    SOUND->Add("BGM", "Sounds/UI/BGM.wav", true, true);
    SOUND->Add("LevelUp", "Sounds/UI/LevelUp.wav");
    SOUND->Add("UI_1", "Sounds/UI/UI_1.wav");
    SOUND->Add("UI_2", "Sounds/UI/UI_2.wav");
    SOUND->Add("UI_3", "Sounds/UI/UI_3.wav");


    // sphere
    SOUND->Add("Sphere_Flash", "Sounds/pal/Sphere_Flash.wav", false, false, true);
    SOUND->Add("Sphere_Hit", "Sounds/pal/Sphere_Hit.wav", false, false, true);
    SOUND->Add("Sphere_Shake", "Sounds/pal/Sphere_Shake.wav", false, false, true);
    SOUND->Add("Sphere_Success", "Sounds/pal/Sphere_Success.wav", false, false, true);

}
