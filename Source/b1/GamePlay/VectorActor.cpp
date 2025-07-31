// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorActor.h"

#include "b1/ThirdPlayer/ThirdPersonPlayerCharacter.h"
#include "b1/ThirdPlayer/ThirdPersonPlayerController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVectorActor::AVectorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VectorBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VectorBoxComponent"));
	check(VectorBoxComponent);
	VectorBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AVectorActor::OnVectorBoxBeginOverlap);
	SetRootComponent(VectorBoxComponent);
}

// Called when the game starts or when spawned
void AVectorActor::BeginPlay()
{
	Super::BeginPlay();
	if (VectorParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, VectorParticleSystem, GetActorLocation());
	}
}

// Called every frame
void AVectorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVectorActor::OnVectorBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (VectorSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, VectorSound, GetActorLocation(),
			1, FMath::FRandRange(0.3f, 0.5f), 0, VectorSoundAttenuation);
	}
	if (TObjectPtr<AThirdPersonPlayerCharacter> PlayerCharacter = Cast<AThirdPersonPlayerCharacter>(OtherActor))
	{
		// ����ʤ��UI(��UI���һ�¿��Խ�����Ϸ)(��װ��HUD�ڣ�Ȼ��PlayController����HUD�����������������PlayerController����)
		if (TObjectPtr<AThirdPersonPlayerController> PlayerController =Cast<AThirdPersonPlayerController>( GetWorld()->GetFirstPlayerController()))
		{
			PlayerController->CreateAndShowVictoryWidget();
		}
	}
}

