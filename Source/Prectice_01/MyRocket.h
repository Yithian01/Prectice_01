// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRocket.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class USoundBase;

UCLASS()
class PRECTICE_01_API AMyRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyRocket();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	TObjectPtr<UBoxComponent> Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> Body;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UProjectileMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UNiagaraSystem> ExplotionTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<USoundBase> ExplotionSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
