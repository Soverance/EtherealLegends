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

using System.IO;
using UnrealBuildTool;

public class Ethereal : ModuleRules
{
    public Ethereal(TargetInfo Target)
    {
        PrivateIncludePaths.AddRange(
            new string[] {
                "Ethereal/Private/Management",
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "OnlineSubsystem",
                "OnlineSubsystemUtils",
                "AssetRegistry",
                "AIModule",
                "GameplayTasks",
                "UMG",

                //////////////////
                // THE TRUESKY PLUGIN HAS BEEN DEPRECATED FROM ETHEREAL LEGENDS AS OF VERSION 1.2.1
                //////////////////
                //"TrueSkyPlugin"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "InputCore",
                "Slate",
                "SlateCore",
            }
        );

        DynamicallyLoadedModuleNames.AddRange(
            new string[] {
                "OnlineSubsystemNull",
                "NetworkReplayStreaming",
                "NullNetworkReplayStreaming",
                "HttpNetworkReplayStreaming"
            }
        );

        PrivateIncludePathModuleNames.AddRange(
            new string[] {
                "NetworkReplayStreaming"
            }
        );

        // Steam Integration
        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Linux))
        {
            DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        }
    }
}
