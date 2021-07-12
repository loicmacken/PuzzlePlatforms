// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UServerRow::Setup(UMainMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::SetNumPlayers(uint16 CurrentPlayers, uint16 MaxPlayers)
{
	NumPlayers->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), CurrentPlayers, MaxPlayers)));
}

void UServerRow::OnClicked()
{
	Parent->SetSelectIndex(Index);
}
