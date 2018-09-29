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
#include "GaiaTortoise.h"

AGaiaTortoise::AGaiaTortoise(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/Adamantoise/Adamantoise.Adamantoise'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Adamantoise/Adamantoise_AnimBP.Adamantoise_AnimBP_C'"));

	// Set Default Objects
	
	// Default Config
	Name = EEnemyNames::EN_GaiaTortoise;
	Realm = ERealms::R_Yggdrasil;
	BattleType = EBattleTypes::BT_Boss;
	CommonDrop = EMasterGearList::GL_Elixer;
	UncommonDrop = EMasterGearList::GL_EurytosBow;
	RareDrop = EMasterGearList::GL_Hauteclaire;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetCharacterMovement()->MaxAcceleration = 30;

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FLinearColor::Yellow);

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 150;
	PawnSensing->LOSHearingThreshold = 200;
	PawnSensing->SightRadius = 250;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 25.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(2, 2, 2));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(100);
	MeleeRadius->SetRelativeLocation(FVector(15, 0, 0));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 130));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	// TO DO : Enemy Specific Objects
}

// Called when the game starts or when spawned
void AGaiaTortoise::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AGaiaTortoise::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AGaiaTortoise::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AGaiaTortoise::CustomDeath); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AGaiaTortoise::MeleeAttack);  // bind the attack function to the OnReachedTarget event 
}

// Called every frame
void AGaiaTortoise::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void AGaiaTortoise::MeleeAttack()
{
	EnemyDealDamage(25);
	
	// TO DO :  attack stuff
}

void AGaiaTortoise::CustomDeath()
{
	IsDead = true;
}

// A.I. Hearing
void AGaiaTortoise::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			Aggro(PawnInstigator);
			RunToTarget();
		}
	}
}

// A.I. Sight
void AGaiaTortoise::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			Aggro(Pawn);
			RunToTarget();
		}
	}	
}
