// © 2014 - 2017 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Ethereal.h"
#include "Kismet/KismetMathLibrary.h"
#include "DropRegen.h"

// Sets default values
ADropRegen::ADropRegen(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Blueprints/Gear/Magic/Spells/Drops/Curve_Orbit.Curve_Orbit'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/P_Regen.P_Regen'"));

	OrbitCurve = Curve.Object;
	P_OrbitFX = CastParticleObject.Object;

	// Creates a scene component and sets it as the root
	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	OrbitFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("Orbit VFX"));
	OrbitFX->Template = P_OrbitFX;
	OrbitFX->SetupAttachment(Root);

	OrbitTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("OrbitTimeline"));
	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->SetUpdatedComponent(OrbitFX);  // set the updated component
	RotatingMovement->PivotTranslation = FVector(5, 5, 0);  // offset the rotation's orbit
}

// Called when the game starts or when spawned
void ADropRegen::BeginPlay()
{
	Super::BeginPlay();
	
	// Play Orbit Timeline
	OrbitTimeline->AddInterpFloat(OrbitCurve, InterpFunction, FName{ TEXT("Float") });
	OrbitTimeline->SetTimelineLength(2.0f);
	OrbitTimeline->SetLooping(true);
	OrbitTimeline->PlayFromStart();

	// Destroy this object after 60 seconds
	FTimerHandle BlastTimer;
	GetWorldTimerManager().SetTimer(BlastTimer, this, &ADropRegen::DestroyDrop, 60.0f, false);
}

// Called every frame
void ADropRegen::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Orbit Timeline
void ADropRegen::TimelineFloatReturn(float val)
{
	RotatingMovement->RotationRate = UKismetMathLibrary::RLerp(FRotator(90, 180, 0), FRotator(-60, 180, 0), val, false);  // rotate the OrbitFX
}

// Destroy the actor!
void ADropRegen::DestroyDrop()
{
	Destroy();
}
