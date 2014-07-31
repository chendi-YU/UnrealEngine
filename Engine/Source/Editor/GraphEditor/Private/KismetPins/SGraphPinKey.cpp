// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.


#include "GraphEditorCommon.h"
#include "SGraphPinComboBox.h"
#include "SGraphPinEnum.h"
#include "SGraphPinKey.h"
#include "SKeySelector.h"

void SGraphPinKey::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	TArray<FKey> KeyList;
	EKeys::GetAllKeys(KeyList);

	SelectedKey = FKey(*InGraphPinObj->GetDefaultAsString());

	if (!SelectedKey.IsValid())
	{
		// Ensure first valid key is always set by default
		SelectedKey = KeyList[0];
		InGraphPinObj->GetSchema()->TrySetDefaultValue(*InGraphPinObj, SelectedKey.ToString());
	}

	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget>	SGraphPinKey::GetDefaultValueWidget()
{
	return SNew(SKeySelector)
			.CurrentKey(this, &SGraphPinKey::GetCurrentKey)
			.OnKeyChanged(this, &SGraphPinKey::OnKeyChanged);
}

FKey SGraphPinKey::GetCurrentKey() const
{
	return SelectedKey;
}

void SGraphPinKey::OnKeyChanged(TSharedPtr<FKey> InSelectedKey)
{
	SelectedKey = *InSelectedKey.Get();
	GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, SelectedKey.ToString());
}