// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/FPCUWNetworkDisplay.h"

#include "CommonTextBlock.h"

void UFPCUWNetworkDisplay::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (NetworkLabel)
	{
		const bool bIsServer = GetWorld()->GetFirstPlayerController()->HasAuthority();
		const FText Text = bIsServer ? INVTEXT("Server") : INVTEXT("Client");
		NetworkLabel->SetText(Text);
	}
}
