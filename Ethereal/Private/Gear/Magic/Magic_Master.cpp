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
#include "Magic_Master.h"

// Sets default values
AMagic_Master::AMagic_Master(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create
	CastAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Cast Audio"));
	CastAudio->SetupAttachment(Root);
	CastFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("Cast VFX"));
	CastFX->SetupAttachment(Root);
	ChargeFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("Charge VFX"));
	ChargeFX->SetupAttachment(Root);

	CastAudio->bAutoActivate = false;
	CastFX->bAutoActivate = false;
	ChargeFX->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AMagic_Master::BeginPlay()
{
	Super::BeginPlay();
}

void AMagic_Master::StopCharge()
{
	IsCharging = false;
	ChargeFX->DeactivateSystem();
	QuitCharging.Broadcast();
}

void AMagic_Master::Charge()
{

}

void AMagic_Master::CastSpell()
{

}
