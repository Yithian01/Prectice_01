// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRocket.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/BP/Rocket/Mesh/SM_Rocket.SM_Rocket'"));
	if (SM_Rocket.Succeeded())
	{
		Body->SetStaticMesh(SM_Rocket.Object);
	}
	Body->SetRelativeRotation(FRotator(-90,0,0));

	Movement->ProjectileGravityScale = 0;
	Movement->InitialSpeed = 600;
}

// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMyRocket::ProcessBeginOverlap);

	SetLifeSpan(3.f);
}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AMyRocket::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

	UE_LOG(LogTemp, Warning, TEXT("Begin Oberlap"));

	if (!(OtherActor->ActorHasTag("Player")))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			ExplotionTemplate,
			GetActorLocation());

		UGameplayStatics::SpawnSoundAtLocation(
			GetWorld(),
			ExplotionSound,
			GetActorLocation());

		Destroy();
	}
}

