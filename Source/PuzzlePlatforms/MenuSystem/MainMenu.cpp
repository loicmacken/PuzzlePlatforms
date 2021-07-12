// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/ServerRow_WBP"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;

	ServerRowClass = ServerRowBPClass.Class;
}

void UMainMenu::SetServerList(TArray<FServerData> ServerDataArray)
{
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	ServerListMenu_ScrollBox->ClearChildren();

	uint32 i = 0;
	for (const FServerData& ServerData : ServerDataArray)
	{
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(ServerRow != nullptr)) return;

		ServerRow->ServerName->SetText(FText::FromString(ServerData.Name));
		ServerRow->SetNumPlayers(ServerData.CurrentPlayers, ServerData.MaxPlayers);
		ServerRow->Ping->SetText(FText::FromString(FString::Printf(TEXT("%d"), ServerData.Ping)));
		ServerRow->HostUserName->SetText(FText::FromString(ServerData.HostUsername));
		ServerRow->Setup(this, i);
		++i;
		
		ServerListMenu_ScrollBox->AddChild(ServerRow);
	}

	// TESTING AREA

	for (int32 j = 0; j < 10; j++)
	{
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(ServerRow != nullptr)) return;

		ServerRow->ServerName->SetText(FText::FromString(FString::Printf(TEXT("40FE728A4471F7F2D5C50E9D8565ADA%d"), j)));
		ServerRow->SetNumPlayers(FMath::RandRange(0,10), FMath::RandRange(10,20));
		ServerRow->Ping->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::RandRange(1,100))));
		ServerRow->HostUserName->SetText(FText::FromString(TEXT("DESKTOP-9QJT7VP-DF2C057B4CB158CB6D910C93E54D0A7D")));
		ServerRow->Setup(this, i);
		++i;
		
		ServerListMenu_ScrollBox->AddChild(ServerRow);
	}
	
	// TESTING AREA
}

void UMainMenu::SetSelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenServerListMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(ServerListMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(ServerListMenu);

	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshServerList();
	}
}

void UMainMenu::CloseSubMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

// void UMainMenu::JoinServerByIP()
// {
// 	if (MenuInterface != nullptr)
// 	{
// 		if (!ensure(JoinMenu_IPAddressTextBox != nullptr)) return;
// 		const FString& IPAddress = JoinMenu_IPAddressTextBox->GetText().ToString();
//
// 		MenuInterface->Join(IPAddress);
// 	}
// }

void UMainMenu::JoinServerBySelection()
{
	if (SelectedIndex.IsSet() && MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index: %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index is not set"));
	}
}

void UMainMenu::QuitPressed()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

void UMainMenu::UpdateChildren()
{
	for (int32 i = 0; i < ServerListMenu_ScrollBox->GetChildrenCount(); i++)
	{
		auto Row = Cast<UServerRow>(ServerListMenu_ScrollBox->GetChildAt(i));
		if (Row != nullptr)
		{
			Row->bSelected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}

bool UMainMenu::Initialize()
{
	bool bIsSuccesful = Super::Initialize();
	if (!bIsSuccesful) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	// if (!ensure(JoinButton != nullptr)) return false;
	// JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenServerListMenu);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);

	// if (!ensure(JoinMenu_BackButton != nullptr)) return false;
	// JoinMenu_BackButton->OnClicked.AddDynamic(this, &UMainMenu::CloseSubMenu);
	//
	// if (!ensure(JoinMenu_JoinButton != nullptr)) return false;
	// JoinMenu_JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServerByIP);

	if (!ensure(JoinMenu_BackButton != nullptr)) return false;
	ServerListMenu_BackButton->OnClicked.AddDynamic(this, &UMainMenu::CloseSubMenu);

	if (!ensure(JoinMenu_JoinButton != nullptr)) return false;
	ServerListMenu_JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServerBySelection);

	return true;
}
