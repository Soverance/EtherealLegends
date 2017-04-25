// Â© 2014 - 2017 Soverance Studios
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
#include "EtherealCharacterMaster.h"

// Sets default values
AEtherealCharacterMaster::AEtherealCharacterMaster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/Shapes/SM_TargetingReticle.SM_TargetingReticle'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> MapMarkerParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/ICE/P_MapMarker.P_MapMarker'"));
	
	SM_TargetingReticle = StaticMeshObject.Object;
	P_MapMarkerFX = MapMarkerParticleObject.Object;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore); // sets capsule to ignore camera collision
	GetMesh()->bReceivesDecals = false;  // make this mesh ignore all decals
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);  // make this mesh ignore collision
	GetMesh()->bCastCapsuleIndirectShadow = true;  // make this mesh cast physics based capsule shadows

	// Create Combat Text Component
	CombatTextComponent = ObjectInitializer.CreateDefaultSubobject<UCombatTextComponent>(this, TEXT("Combat Text Component"));

	// Map Marker Component
	MapMarkerFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("MapMarkerFX"));
	MapMarkerFX->SetupAttachment(RootComponent);
	MapMarkerFX->Template = P_MapMarkerFX;
	MapMarkerFX->bAutoActivate = false;
	MapMarkerFX->SetRelativeRotation(FRotator(90, 0, 0));

	// configure Melee Radius
	MeleeRadius = CreateDefaultSubobject<USphereComponent>(TEXT("MeleeRadius"));
	MeleeRadius->SetupAttachment(RootComponent);
	MeleeRadius->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	// Set Default Objects
	TargetingReticle = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Targeting Reticle"));
	TargetingReticle->SetStaticMesh(SM_TargetingReticle);
	UCommonLibrary::SetupSMComponentsWithCollision(TargetingReticle);
	TargetingReticle->SetupAttachment(GetMesh());

	IsDead = false;
	IsHit = false;
	Targetable = true;  // Set targeting to true
}

// Called when the game starts or when spawned
void AEtherealCharacterMaster::BeginPlay()
{
	Super::BeginPlay();

	// iterate through the world for all Ethereal Audio Managers
	for (TActorIterator<AEtherealAudioManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AudioManager = *ActorItr; // get the instance of the Audio Manager
	}
}

// Called every frame
void AEtherealCharacterMaster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Activates the Map Marker effect
void AEtherealCharacterMaster::ShowMapMarker()
{
	if (!IsDead)
	{
		MapMarkerFX->Activate();
	}	
}

// Deactivates the Map Marker
void AEtherealCharacterMaster::HideMapMarker()
{
	MapMarkerFX->Deactivate();
}

// Called to bind functionality to input
void AEtherealCharacterMaster::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);
}

// Activate the Targeting Reticle when Locked On (only used by the player)
void AEtherealCharacterMaster::ToggleReticle(bool Visible)
{
	if (Visible)
	{
		TargetingReticle->SetVisibility(true);
		AudioManager->Play_Target_Notify();
	}
	else
	{
		TargetingReticle->SetVisibility(false);
	}
}

// Activate the Targeting Reticle when Locked On (only used by the player)
void AEtherealCharacterMaster::ShowCombatDamageText(bool IsCritical, float Damage)
{
	if (IsCritical)
	{
		// CRITICAL DAMAGE
		FString String = FString::SanitizeFloat(Damage);  // Get string from Damage value
		CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_CritDmg, FText::FromString(String));  // show combat text
	}
	else
	{
		// STANDARD DAMAGE
		FString String = FString::SanitizeFloat(Damage);  // Get string from Damage value
		CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_Damage, FText::FromString(String));  // show combat text
	}
}
