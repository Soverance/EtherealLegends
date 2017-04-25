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
#include "Gear/Weapons/Weapon_Master.h"
#include "EtherealPlayerMaster.h"

// Sets default values
AEtherealPlayerMaster::AEtherealPlayerMaster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Morgan.Morgan'"));
	//static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Morgan/Anim_Morgan.Anim_Morgan'_C'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ExclamationMesh(TEXT("StaticMesh'/Game/EtherealParty/Apprentice/exclamation.exclamation'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> LevelUpParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/ICE/P_levelUp_Eth.P_levelUp_Eth'"));
	static ConstructorHelpers::FObjectFinder<UClass> LevelUpCamShakeObject(TEXT("Blueprint'/Game/Blueprints/CamShakes/CS_LevelUp.CS_LevelUp_C'"));

	SM_Exclamation = ExclamationMesh.Object;
	P_LevelUpFX = LevelUpParticleObject.Object;

	LevelUpCamShake = LevelUpCamShakeObject.Object->GetClass()->StaticClass(); 

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FColor::Cyan);

	//GetMesh()->SkeletalMesh = SkeletalMeshObject.Object;
	//GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	
	// configure the NPC exclamation
	PawnNoiseEmitter = ObjectInitializer.CreateDefaultSubobject<UPawnNoiseEmitterComponent>(this, TEXT("PawnNoiseComponent"));
	PawnNoiseEmitter->bAutoActivate = true;

	// configure the NPC exclamation
	Exclamation = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Exclamation"));
	Exclamation->SetupAttachment(GetMesh());
	Exclamation->SetStaticMesh(SM_Exclamation);
	Exclamation->SetVisibility(false);
	Exclamation->SetRelativeLocation(FVector(0, 0, 220.0f));
	Exclamation->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	UCommonLibrary::SetupSMComponentsWithCollision(Exclamation);

	MeleeRadius->SetRelativeLocation(FVector(100, 0, -90));
	MeleeRadius->SetSphereRadius(200);

	// configure the targeting reticle
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 200.0f));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	TargetingReticle->SetVisibility(false);

	LevelUpFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("LevelUpFX"));
	LevelUpFX->SetupAttachment(GetMesh());
	LevelUpFX->Template = P_LevelUpFX;
	LevelUpFX->SetRelativeLocation(FVector(0, 0, 30));
	LevelUpFX->SetRelativeRotation(FRotator(0, 90, 0));
	LevelUpFX->SetWorldScale3D(FVector(0.7f, 0.7f, 0.7f));
	LevelUpFX->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AEtherealPlayerMaster::BeginPlay()
{
	Super::BeginPlay();

	// Gets and stores a reference to the Player State
	EtherealPlayerState = Cast<AEtherealPlayerState>(GetController()->PlayerState);
	EtherealGameInstance = Cast<UEtherealGameInstance>(GetGameInstance());
	EtherealPlayerController = Cast<AEtherealPlayerController>(GetController());

	if (EtherealPlayerState)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "EtherealPlayerState reference was successfully initialized from code.");
		EtherealPlayerState->Player = this;  // Sets a reference to itself inside the PlayerState
		EtherealPlayerState->Regen();  // start the regen tick
		EtherealPlayerState->Refresh();  // start the refresh tick
	}

	if (EtherealPlayerController)
	{
		EtherealPlayerController->EtherealPlayer = this;  // sets a reference to itself inside the player controller
	}

	// Bind the Map Marker functions
	MapOpened.AddDynamic(this, &AEtherealCharacterMaster::ShowMapMarker);
	MapClosed.AddDynamic(this, &AEtherealCharacterMaster::HideMapMarker);
}

// Called every frame
void AEtherealPlayerMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEtherealPlayerMaster::SetSkinOpacityMask_Implementation()
{

}

void AEtherealPlayerMaster::ReportFootstep(UAudioComponent* SoundToPlay)
{
	if (SoundToPlay)
	{
		// make no footstep noise if wearing sneak shoes
		if (!HasSneak)
		{
			//Play the footstep sound
			//SoundToPlay->SetVolumeMultiplier(Volume);
			SoundToPlay->Play();

			//Report to Enemy A.I. that we've played a sound with a certain volume in a specific location
			MakeNoise(1, this, GetActorLocation());
		}		
	}
}

// Stops the player's movement
void AEtherealPlayerMaster::StopActions()
{
	GetCharacterMovement()->StopMovementImmediately();
	SpeedForward = 0;
	SpeedRight = 0;
	StopAttacking();
	StopBlocking();
}

void AEtherealPlayerMaster::StopAttacking_Implementation()
{
}

void AEtherealPlayerMaster::StopBlocking_Implementation()
{
}

// Toggle Run State
void AEtherealPlayerMaster::ToggleRunState()
{
	if (IsRunning) // player is currently running, so set to walk speed
	{
		IsRunning = false;

		SetMovementSpeed();  // set movement speed
		
	}
	else // player is currently walking, so set to run speed
	{
		IsRunning = true;
		
		SetMovementSpeed();  // set movement speed
	}
}

// Set Movement Speed
void AEtherealPlayerMaster::SetMovementSpeed()
{
	// If the player is Hasted, ignore all walk modes, and set to high speed
	if (IsHasted)
	{
		if (HasFastPants)
		{
			GetCharacterMovement()->MaxWalkSpeed = 190;
		}
		if (!HasFastPants)
		{
			GetCharacterMovement()->MaxWalkSpeed = 170;
		}
	}
	// If the player is not hasted, do the regular stuff.
	else
	{
		if (!IsRunning) // player is currently walking, so set to walk speed
		{
			if (HasFastPants)
			{
				GetCharacterMovement()->MaxWalkSpeed = 80;
			}
			if (!HasFastPants)
			{
				GetCharacterMovement()->MaxWalkSpeed = 60;
			}

		}
		if (IsRunning) // player is currently running, so set to run speed
		{
			if (HasFastPants)
			{
				GetCharacterMovement()->MaxWalkSpeed = 140;
			}
			if (!HasFastPants)
			{
				GetCharacterMovement()->MaxWalkSpeed = 120;
			}
		}
	}	
}

// This function sets the DamageOutput variable, based on the BaseAtk value of an attack. Returns the ultimate value of damage dealt to an enemy.
void AEtherealPlayerMaster::PlayerDealDamage(float BaseAtk)
{
	// The next three lines are pure Black Magic
	float mod1 = ((BaseAtk + EtherealPlayerState->ATK) / 32);
	float mod2 = ((BaseAtk * EtherealPlayerState->ATK) / 32);
	float mod3 = (((mod1 * mod2) + EtherealPlayerState->ATK) * 40);
	float adjusted = mod3;  // set adjusted to base value of mod3

	// if the player is in the One-Handed weapon mode and is wearing a One-Handed Boost armor item
	if (EtherealPlayerState->WeaponMode == EWeaponModes::WM_OneHanded && BoostOneHanded)
	{
		adjusted = mod3 * 1.25f;  // increase output by 25%
	}

	// if the player is in the Two-Handed weapon mode and is wearing a Two-Handed Boost armor item
	if (EtherealPlayerState->WeaponMode == EWeaponModes::WM_TwoHanded && BoostTwoHanded)
	{
		adjusted = mod3 * 1.25f;  // increase output by 25%
	}

	// if the player is in the Ranged weapon mode and is wearing a Ranged Boost armor item
	if (EtherealPlayerState->WeaponMode == EWeaponModes::WM_Ranged && BoostRanged)
	{
		adjusted = mod3 * 1.25f;  // increase output by 25%
	}

	DamageOutput = adjusted;  // Set Damage Output
}

// This function deals damage to the player, based on a DamageTaken value supplied by an enemy. This function is usually called by the enemy itself.
void AEtherealPlayerMaster::PlayerTakeDamage(float DamageTaken)
{
	if (!IsDead)  // take no damage if you're already dead!
	{
		IsHit = true;

		// Calculate damage taken
		float critical = FMath::FRandRange(1, 1.5f); // sets a random critical rate
		float mod1 = (critical * (EtherealPlayerState->DEF - 512) * DamageTaken); 
		float mod2 = (mod1 / (16 * 512));
		float mod3 = FMath::Abs(mod2);
		float FinalDamage = mod3;

		// DAMAGE WALL REDUCTION
		if (HasDefenseWall)
		{
			FinalDamage = (mod3 * 0.5f);  // reduce damage by 50%
		}

		// BLOCKING REDUCTION
		if (IsBlocking)
		{
			FinalDamage = (mod3 * 0.25f);  // if you're blocking, reduce damage by 75%
		}

		// SHADOW GEAR REDUCTION
		if (HasShadowGear)
		{
			int32 RandomShadow = FMath::RandRange(0, 3);  // get a random int

			// give 25% chance for Shadow Gear to nullify damage
			if (RandomShadow == 3)
			{
				FinalDamage = 0;  // Shadow absorbed all damage
			}
		}		
		
		EtherealPlayerState->HP_Current = (EtherealPlayerState->HP_Current - FinalDamage);  // apply new HP value

		if (critical > 1.4f)
		{
			// Display Critical Damage
			CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_CritDmg, UCommonLibrary::GetFloatAsTextWithPrecision(FinalDamage, 0, true));
		}
		else
		{
			// Display Normal Damage
			CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_Damage, UCommonLibrary::GetFloatAsTextWithPrecision(FinalDamage, 0, true));
		}

		EtherealPlayerState->ForceHPCaps();
	}
}

void AEtherealPlayerMaster::TeleportReturn_Implementation(bool ShouldRaise)
{

}

void AEtherealPlayerMaster::StartDeathCycle_Implementation()
{

}

void AEtherealPlayerMaster::HideAllBoundWeapons()
{
	AEtherealGearMaster* Gear1 = EtherealPlayerState->GetInventoryItem(EtherealPlayerState->Binding_Weapon_OneHanded);
	AEtherealGearMaster* Gear2 = EtherealPlayerState->GetInventoryItem(EtherealPlayerState->Binding_Weapon_TwoHanded);
	AEtherealGearMaster* Gear3 = EtherealPlayerState->GetInventoryItem(EtherealPlayerState->Binding_Weapon_Ranged);
	AEtherealGearMaster* Gear4 = EtherealPlayerState->GetInventoryItem(EtherealPlayerState->Binding_Weapon_Shield);
	AEtherealGearMaster* Gear5 = EtherealPlayerState->GetInventoryItem(EtherealPlayerState->Binding_Weapon_Ammo);

	if (Gear1)
	{
		AWeapon_Master* OneHanded = Cast<AWeapon_Master>(Gear1);
		
		if (OneHanded)
		{
			OneHanded->RemoveWeapon();  // Hide One-Handed Weapon
		}
	}

	if (Gear2)
	{
		AWeapon_Master* TwoHanded = Cast<AWeapon_Master>(Gear2);

		if (TwoHanded)
		{
			TwoHanded->RemoveWeapon();  // Hide Two-Handed Weapon
		}
	}

	if (Gear3)
	{
		AWeapon_Master* Ranged = Cast<AWeapon_Master>(Gear3);

		if (Ranged)
		{
			Ranged->RemoveWeapon();  // Hide Ranged Weapon
		}
	}

	if (Gear4)
	{
		AWeapon_Master* Shield = Cast<AWeapon_Master>(Gear4);

		if (Shield)
		{
			Shield->RemoveWeapon();  // Hide Shield
		}
	}

	if (Gear5)
	{
		AWeapon_Master* Ammo = Cast<AWeapon_Master>(Gear5);

		if (Ammo)
		{
			Ammo->RemoveWeapon();  // Hide Ammo
		}
	}
}

void AEtherealPlayerMaster::EnemyCloseMenu_Implementation()
{

}

// Interact with a NPC
void AEtherealPlayerMaster::Interact()
{
	InteractTarget->Interact();  // Interact with the NPC
	Exclamation->SetVisibility(false); // disables the exclamation notification, because you obviously are aware of the NPC
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None); // disable player movement
	DoInteractAnim = true;  // Play interact animation
}
