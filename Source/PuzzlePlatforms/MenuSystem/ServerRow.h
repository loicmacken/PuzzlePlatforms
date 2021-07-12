// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

// Forward declarations
class UTextBlock;
class UMainMenu;
class UButton;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget));
	UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget));
	UTextBlock* Ping;
	
	UPROPERTY(meta = (BindWidget));
	UTextBlock* HostUserName;

	UPROPERTY(BlueprintReadOnly)
	bool bSelected = false;
	
	void Setup(UMainMenu* InParent, uint32 InIndex);
	void SetNumPlayers(uint16 CurrentPlayers, uint16 MaxPlayers);

private:
	UPROPERTY(meta = (BindWidget));
	UButton* RowButton;

	UPROPERTY(meta = (BindWidget));
	UTextBlock* NumPlayers;

	UPROPERTY()
	UMainMenu* Parent;
	
	uint32 Index;

	UFUNCTION()
	void OnClicked();
};
