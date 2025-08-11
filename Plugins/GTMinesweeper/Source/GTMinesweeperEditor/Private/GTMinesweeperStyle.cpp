// Copyright Epic Games, Inc. All Rights Reserved.

#include "GTMinesweeperStyle.h"
#include "GTMinesweeperEditor.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FGTMinesweeperStyle::StyleInstance = nullptr;

void FGTMinesweeperStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FGTMinesweeperStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FGTMinesweeperStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("GTMinesweeperStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FGTMinesweeperStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("GTMinesweeperStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("GTMinesweeper")->GetBaseDir() / TEXT("Resources"));

	Style->Set("GTMinesweeper.PluginAction", new IMAGE_BRUSH_SVG(TEXT("SimpleIcon"), Icon20x20));
	return Style;
}

void FGTMinesweeperStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FGTMinesweeperStyle::Get()
{
	return *StyleInstance;
}
