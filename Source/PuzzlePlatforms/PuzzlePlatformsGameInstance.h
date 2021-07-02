// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MenuSystem/MenuInterface.h"

#include "PuzzlePlatformsGameInstance.generated.h"

// Forward declarations
class UUserWidget;
class UMainMenu;
class UInGameMenu;
class UMenuWidget;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);

	void Init();

private:
	TSubclassOf<UUserWidget> MainMenuClass;

	UMainMenu* MainMenu;

	TSubclassOf<UUserWidget> InGameMenuClass;


public:
	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(Exec)
	void Host() override;
	
	UFUNCTION(Exec)
	void Join(const FString& Address) override;

	virtual void ReturnToMainMenu() override;
};
