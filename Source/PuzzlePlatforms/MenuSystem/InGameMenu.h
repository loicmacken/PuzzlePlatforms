// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

// Forward declarations
class UButton;
class UWidget;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	UWidget* InGameMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* InGameMenu_CancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* InGameMenu_ExitButton;

	UFUNCTION()
	void CancelMenu();

	UFUNCTION()
	void ReturnToMainMenu();

protected:
	virtual bool Initialize() override;
};
