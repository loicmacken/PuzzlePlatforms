// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"

void UInGameMenu::CancelMenu()
{
	Teardown();
}

void UInGameMenu::ReturnToMainMenu()
{
}

bool UInGameMenu::Initialize()
{
	bool bIsSuccesful = Super::Initialize();
	if (!bIsSuccesful) return false;

	if (!ensure(InGameMenu_CancelButton != nullptr)) return false;
	InGameMenu_CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelMenu);

	if (!ensure(InGameMenu_ExitButton != nullptr)) return false;
	InGameMenu_ExitButton->OnClicked.AddDynamic(this, &UInGameMenu::ReturnToMainMenu);

	return true;
}
