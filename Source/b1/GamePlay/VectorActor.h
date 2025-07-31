//ʤ�����ӣ�����������ж�ʱ������ʤ����Ч������һ��ʤ��UI,ʤ��UI����Խ�����Ϸ��
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
	//ʤ�����ӣ���������ж�ʱ������ʤ����Ч�Լ���Ч������һ��ʤ��UI,ʤ��UI����Խ�����Ϸ��
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Core")
	TObjectPtr<UBoxComponent> VectorBoxComponent;
	//ʤ����Ч
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Core")
	TObjectPtr<USoundBase> VectorSound;
	//ʤ����Ч˥��
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Core")
	TObjectPtr<USoundAttenuation> VectorSoundAttenuation;
	//ʤ����Ч
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	TObjectPtr<UParticleSystem> VectorParticleSystem;

	UFUNCTION()
	void OnVectorBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);

};
