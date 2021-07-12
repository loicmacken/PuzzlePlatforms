// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "MainMenu.generated.h"

// Forward declarations
class UButton;
class UWidgetSwitcher;
class UWidget;
class UEditableTextBox;
class UPanelWidget;
class UUserWidget;
class UServerRow;

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	uint16 Ping;
	FString HostUsername;
};

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerNames);

	void SetSelectIndex(uint32 Index);
	
private:
	TSubclassOf<UUserWidget> ServerRowClass;
	
	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;
	
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinMenu_BackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinMenu_JoinButton;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* JoinMenu_IPAddressTextBox;

	UPROPERTY(meta = (BindWidget))
	UWidget* ServerListMenu;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ServerListMenu_ScrollBox;

	UPROPERTY(meta = (BindWidget))
	UButton* ServerListMenu_BackButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ServerListMenu_JoinButton;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenServerListMenu();

	UFUNCTION()
	void CloseSubMenu();

	// UFUNCTION()
	// void JoinServerByIP();

	UFUNCTION()
	void JoinServerBySelection();

	UFUNCTION()
	void QuitPressed();

	TOptional<uint32> SelectedIndex;

	void UpdateChildren();
	
protected:
	virtual bool Initialize() override;

};
