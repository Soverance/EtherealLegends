// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EtherealTarget : TargetRules
{
    public EtherealTarget(TargetInfo Target)
    {
        Type = TargetType.Game;
        bUsesSteam = true;
    }

    //
    // TargetRules interface.
    //

    public override void SetupBinaries(
        TargetInfo Target,
        ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
        ref List<string> OutExtraModuleNames
        )
    {
        OutExtraModuleNames.Add("Ethereal");
    }

    public override void SetupGlobalEnvironment(
            TargetInfo Target,
            ref LinkEnvironmentConfiguration OutLinkEnvironmentConfiguration,
            ref CPPEnvironmentConfiguration OutCPPEnvironmentConfiguration
            )
    {
        if (Target.Platform == UnrealTargetPlatform.PS4)
        {
            OutCPPEnvironmentConfiguration.Definitions.Add("GARLIC_HEAP_SIZE=(2600ULL * 1024 * 1024)");
            OutCPPEnvironmentConfiguration.Definitions.Add("ONION_HEAP_SIZE=(200ULL * 1024 * 1024)");
            OutCPPEnvironmentConfiguration.Definitions.Add("RESERVED_MEMORY_SIZE=(1ULL * 1024 * 1024)");
            OutCPPEnvironmentConfiguration.Definitions.Add("LIBC_MALLOC_SIZE=(32ULL * 1024 * 1024)");
            OutCPPEnvironmentConfiguration.Definitions.Add("LIBC_MALLOC_SIZE=(32ULL * 1024 * 1024)");

            //for a real game these could be behind a call to a virtual function defined in a partial class in a protected folder also.
            OutCPPEnvironmentConfiguration.Definitions.Add("UE4_PROJECT_NPTITLEID=NPXX51358_00");
            OutCPPEnvironmentConfiguration.Definitions.Add("UE4_PROJECT_NPTITLESECRET=81ae213eafbc64777574955bf921c9be3c60a3bddef70c357d8fe49ad64e0d0402d2249de390174832c5e4098114c93c33705b597cfbe9b1153d58fe9fae1f0de1466daf18ef25d06122cff7c95bde07bc060109e20c865305692dfbf9d7b726460893c4abd86dc9e8fd6b5db7dca4ffd4eefcb1771baccd576109bea862d6d4");
        }
    }

    public override List<UnrealTargetPlatform> GUBP_GetPlatforms_MonolithicOnly(UnrealTargetPlatform HostPlatform)
    {
		List<UnrealTargetPlatform> Platforms = null;

		switch (HostPlatform)
		{
			case UnrealTargetPlatform.Mac:
				Platforms = new List<UnrealTargetPlatform> { HostPlatform };
				break;

			case UnrealTargetPlatform.Win64:
				Platforms = new List<UnrealTargetPlatform> { HostPlatform, UnrealTargetPlatform.Win32, UnrealTargetPlatform.XboxOne, UnrealTargetPlatform.PS4 };
				break;

			default:
				Platforms = new List<UnrealTargetPlatform>();
				break;
		}

		return Platforms;
    }

    public override List<UnrealTargetConfiguration> GUBP_GetConfigs_MonolithicOnly(UnrealTargetPlatform HostPlatform, UnrealTargetPlatform Platform)
    {
        return new List<UnrealTargetConfiguration> { UnrealTargetConfiguration.Development };
    }
    public override List<GUBPFormalBuild> GUBP_GetConfigsForFormalBuilds_MonolithicOnly(UnrealTargetPlatform HostPlatform)
    {
        if (HostPlatform == UnrealTargetPlatform.Win64)
        {
            return new List<GUBPFormalBuild> 
            {
                new GUBPFormalBuild(UnrealTargetPlatform.Linux, UnrealTargetConfiguration.Development),
                new GUBPFormalBuild(UnrealTargetPlatform.Win64, UnrealTargetConfiguration.Development),
                new GUBPFormalBuild(UnrealTargetPlatform.XboxOne, UnrealTargetConfiguration.Development),
                new GUBPFormalBuild(UnrealTargetPlatform.PS4, UnrealTargetConfiguration.Development),
            };
        }
        else
        {
            return new List<GUBPFormalBuild> 
            {
                new GUBPFormalBuild(UnrealTargetPlatform.Mac, UnrealTargetConfiguration.Development),
            };
        }
    }
}
