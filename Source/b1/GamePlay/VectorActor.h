//胜利盒子，但玩家走入判定时，播放胜利音效，并打开一个胜利UI,胜利UI里可以结束游戏。
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VectorActor.generated.h"

class UVectorUserWidget;
class UBoxComponent;

UCLASS()
class B1_API AVectorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVectorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//胜利盒子，玩家走入判定时，播放胜利音效以及特效，并打开一个胜利UI,胜利UI里可以结束游戏。
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Core")
	TObjectPtr<UBoxComponent> VectorBoxComponent;
	//胜利音效
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Core")
	TObjectPtr<USoundBase> VectorSound;
	//胜利音效衰减
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Core")
	TObjectPtr<USoundAttenuation> VectorSoundAttenuation;
	//胜利特效
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	TObjectPtr<UParticleSystem> VectorParticleSystem;

	UFUNCTION()
	void OnVectorBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);

};
