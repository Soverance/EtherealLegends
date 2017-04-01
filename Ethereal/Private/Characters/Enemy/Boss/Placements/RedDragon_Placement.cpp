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
#include "RedDragon_Placement.h"

// Sets default values
ARedDragon_Placement::ARedDragon_Placement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	FlightSpline = ObjectInitializer.CreateDefaultSubobject<USplineComponent>(this, TEXT("FlightPath"));
	FlightSpline->SetupAttachment(Root);

	FVector Spline0 = FVector(0, 0, 0);
	SplineArray.Add(Spline0);
	FVector Spline1 = FVector(0, 1500, 500);
	SplineArray.Add(Spline1);
	FVector Spline2 = FVector(1000, 3500, 2500);
	SplineArray.Add(Spline2);
	FVector Spline3 = FVector(-1000, 3500, 2500);
	SplineArray.Add(Spline3);
	FVector Spline4 = FVector(-500, 1500, 400);
	SplineArray.Add(Spline4);
	FVector Spline5 = FVector(-500, -500, 400);
	SplineArray.Add(Spline5);
	FVector Spline6 = FVector(-1000, -2000, 1500);
	SplineArray.Add(Spline6);
	FVector Spline7 = FVector(-1250, -3500, 2500);
	SplineArray.Add(Spline7);
	FVector Spline8 = FVector(800, -3500, 2250);
	SplineArray.Add(Spline8);
	FVector Spline9 = FVector(500, -1000, 400);
	SplineArray.Add(Spline9);
	FVector Spline10 = FVector(500, 1000, 400);
	SplineArray.Add(Spline10);
	FVector Spline11 = FVector(1000, 4000, 2500);
	SplineArray.Add(Spline11);
	FVector Spline12 = FVector(-1000, 4000, 2500);
	SplineArray.Add(Spline12);
	FVector Spline13 = FVector(-250, 2000, 650);
	SplineArray.Add(Spline13);
	FVector Spline14 = FVector(-100, 1500, 150);
	SplineArray.Add(Spline14);
	FVector Spline15 = FVector(-100, 1250, 200);
	SplineArray.Add(Spline15);
	
	FlightSpline->SetSplinePoints(SplineArray, ESplineCoordinateSpace::Local, true);
}

// Called when the game starts or when spawned
void ARedDragon_Placement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARedDragon_Placement::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ARedDragon_Placement::FollowSpline_Implementation(ARedDragon* Dragon)
{

}
