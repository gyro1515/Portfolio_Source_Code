// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_AIController.h"
#include "AI/C_BasicMonster.h"
#include "C_TopDownCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/C_AIBehaviorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


AC_AIController::AC_AIController()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;


    Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
    Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
    Behavior = CreateDefaultSubobject<UC_AIBehaviorComponent>("Behavior");

    Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
    Sight->SightRadius = 600;
    //Sight->LoseSightRadius = 800;
    Sight->LoseSightRadius = 1600;
    Sight->PeripheralVisionAngleDegrees = 90.0f;
    Sight->SetMaxAge(2);
    Sight->DetectionByAffiliation.bDetectEnemies = true;
    //Sight->DetectionByAffiliation.bDetectNeutrals = false;
    //Sight->DetectionByAffiliation.bDetectFriendlies = false;
    Sight->DetectionByAffiliation.bDetectNeutrals = true;
    Sight->DetectionByAffiliation.bDetectFriendlies = true;


    Perception->ConfigureSense(*Sight);
    Perception->SetDominantSense(*Sight->GetSenseImplementation());

}

void AC_AIController::BeginPlay()
{
    Super::BeginPlay();
}

void AC_AIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AC_AIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    ControlledPawn = Cast<AC_BasicMonster>(InPawn);

    Perception->OnPerceptionUpdated.AddDynamic(this, &AC_AIController::OnPerceptionUpdated);

    UBlackboardComponent* blackboard = Blackboard.Get();
    UseBlackboard(ControlledPawn->GetTree()->BlackboardAsset, blackboard);
    Behavior->SetBolackboard(Blackboard);

    RunBehaviorTree(ControlledPawn->GetTree());


}

void AC_AIController::OnUnPossess()
{
    Super::OnUnPossess();
}

float AC_AIController::GetSightRange()
{
    return Sight->SightRadius;
}

void AC_AIController::IncreaseAggro(AC_TopDownCharacter* Player, float Amount)
{

    if (AggroTable.Num()==0)
    {

        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_TopDownCharacter::StaticClass(), PlayerList);
        for (int i = 0; i < PlayerList.Num(); i++)
        {
            AC_TopDownCharacter* A = Cast<AC_TopDownCharacter>(PlayerList[i]);
            AggroTable.Add(A, 0.0f);
        }

        isAggro = true;
    }

    AggroTable[Player] += (Player->AggroMult * Amount);

    UpdateTarget();
}

AC_TopDownCharacter* AC_AIController::GetHighestAggroTarget()
{
    AC_TopDownCharacter* HighestAggroTarget = nullptr;
    float HighestAggro = -1.0f;
    SubTargets.Empty();

    for (const TPair<AC_TopDownCharacter*, float>& Entry : AggroTable)
    {
        if (Entry.Value > HighestAggro)
        {
            HighestAggro = Entry.Value;
            HighestAggroTarget = Entry.Key;
        }
    }

    for (const TPair<AC_TopDownCharacter*, float>& Entry : AggroTable)
    {
        if (Entry.Key != HighestAggroTarget)
        {
            SubTargets.Add(Entry.Key);
        }
    }

    if (SubTargets.Num() > 0)
    {
        Blackboard->SetValueAsObject("SubTarget_1", SubTargets[0]);
    }

    if (SubTargets.Num() > 1)
    {
        Blackboard->SetValueAsObject("SubTarget_2", SubTargets[1]);
    }


    return HighestAggroTarget;
}

void AC_AIController::ServerIncreaseAggro_Implementation(AC_TopDownCharacter* Player, float Amount)
{
    IncreaseAggro(Player, Amount);
}

void AC_AIController::UpdateTarget_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Update")));

    AC_TopDownCharacter* NewTarget = GetHighestAggroTarget();
    if (NewTarget)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("NEWTARGET")));

        Blackboard->SetValueAsObject("Target", NewTarget);
    }
}

void AC_AIController::OnPerceptionUpdated_Implementation(const TArray<AActor*>& UpdateActors)
{
    if (isAggro) return;

    TArray<AActor*> actors;
    Perception->GetCurrentlyPerceivedActors(nullptr, actors);

    AC_TopDownCharacter* player = nullptr;
    for (AActor* actor : actors)
    {
        player = Cast<AC_TopDownCharacter>(actor);

        if (player != nullptr)
            break;
    }

    if (player)
    {
        Blackboard->SetValueAsObject("Target", player);
        isAggro = true;
    }


    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_TopDownCharacter::StaticClass(), PlayerList);    
    for(int i=0;i<PlayerList.Num();i++)
    {
        AC_TopDownCharacter* A = Cast<AC_TopDownCharacter>(PlayerList[i]);
        AggroTable.Add(A, 0.0f);
    }

    //UpdateTarget();


}
