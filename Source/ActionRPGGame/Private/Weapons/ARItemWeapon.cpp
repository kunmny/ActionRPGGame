// Fill out your copyright notice in the Description page of Project Settings.

#include "ARItemWeapon.h"

#include "Effects/GABlueprintLibrary.h"

#include "ARCharacter.h"
#include "ARPlayerController.h"
#include "Attributes/ARGunAttributes.h"
#include "UI/ARHUD.h"
#include "UI/Inventory/ARUIInventoryComponent.h"
#include "UI/Inventory/ARInventoryScreenWidget.h"
#include "UI/Inventory/Weapons/Modifications/ARItemMagazineView.h"

#include "Weapons/ARWeaponAbilityBase.h"
#include "Weapons/ARMagazineUpgradeItem.h"
#include "Weapons/ARWeaponInventoryComponent.h"
#include "Weapons/ARMagazineUpgradeEffect.h"

void UARItemWeapon::SetAbility(class UARWeaponAbilityBase* InAbility)
{
	AbilityInstance = InAbility;
	AbilityInstance->SetWeaponItem(this);
	if (Attributes)
	{
		if (AbilityInstance)
		{
			AbilityInstance->GetAttributes()->CopyFromOtherAttributes(Attributes);
		}
	}
}
void UARItemWeapon::AddMagazineUpgrade(class UARMagazineUpgradeItem* InMagazineUpgrade)
{
	if (!AbilityInstance)
	{
		return; //add log.
	}

	UARWeaponInventoryComponent* WeaponComponent = Cast<UARWeaponInventoryComponent>(GetOuter());
	//might also check for PC inventory.

	if (!WeaponComponent)
		return;

	AARCharacter* Character = Cast<AARCharacter>(WeaponComponent->GetOwner());
	if (!Character)
		return;

	MagazineModification = DuplicateObject<UARMagazineUpgradeItem>(InMagazineUpgrade, this);

	//this part only on server.
	if (Character->Role >= ENetRole::ROLE_Authority)
	{
		MagazineUpgradeValue = InMagazineUpgrade->MagazineUpgradeValue;
		AbilityInstance->AddMagazineUpgrade(InMagazineUpgrade->UpgradeEffect, MagazineUpgradeValue);
	}
	OnMagazineUpdateAdded();
}
void UARItemWeapon::OnMagazineUpdateAdded()
{
}

UARMagazineUpgradeItem* UARItemWeapon::RemoveMagazineUpgrade()
{
	AbilityInstance->RemoveMagazineUpgrade();

	return MagazineModification;
}


void UARItemWeapon::OnItemAdded(uint8 LocalIndex)
{

}
void UARItemWeapon::OnItemRemoved(uint8 LocalIndex)
{

}


void UARItemWeapon::OnItemAddedEquipment(uint8 LocalIndex) 
{

};
void UARItemWeapon::OnItemChangedEquipment(uint8 LocalIndex) 
{
};
void UARItemWeapon::OnItemRemovedEquipment(uint8 LocalIndex) 
{
};

void UARItemWeapon::OnServerItemAddedEquipment(uint8 LocalIndex) 
{
};
void UARItemWeapon::OnServerItemChangedEquipment(uint8 LocalIndex) 
{
};
void UARItemWeapon::OnServerItemRemovedEquipment(uint8 LocalIndex) 
{
};

void UARItemWeapon::PostItemLoad()
{

}

TArray<FARItemTooltipData> UARItemWeapon::GetTooltipData()
{
	TArray<FARItemTooltipData> Data;

	UARGunAttributes* ABAttr = AbilityInstance->GetAttributesTyped<UARGunAttributes>();

	FARItemTooltipData ItemName("ItemName", AbilityInstance->GetName());
	Data.Add(ItemName);

	if (ABAttr)
	{
		FARItemTooltipData BaseDamage("BaseDamage", FString::FormatAsNumber(ABAttr->BaseDamage.GetCurrentValue()));
		Data.Add(BaseDamage);

		FARItemTooltipData CritChance("CritChance", FString::FormatAsNumber(ABAttr->CritChance.GetCurrentValue()));
		Data.Add(CritChance);

		FARItemTooltipData Magazine("Magazine", FString::FormatAsNumber(ABAttr->Magazine.GetCurrentValue()));
		Data.Add(Magazine);

		FARItemTooltipData RateOfFire("RateOfFire", FString::FormatAsNumber(ABAttr->RateOfFire.GetCurrentValue()));
		Data.Add(RateOfFire);

		FARItemTooltipData ReloadSpeed("ReloadSpeed", FString::FormatAsNumber(ABAttr->ReloadSpeed.GetCurrentValue()));
		Data.Add(ReloadSpeed);

		FARItemTooltipData HorizontalStability("HorizontalStability", FString::FormatAsNumber(ABAttr->HorizontalStability.GetCurrentValue()));
		Data.Add(HorizontalStability);

		FARItemTooltipData VerticalStability("VerticalStability", FString::FormatAsNumber(ABAttr->VerticalStability.GetCurrentValue()));
		Data.Add(VerticalStability);

		FARItemTooltipData Spread("Spread", FString::FormatAsNumber(ABAttr->Spread.GetCurrentValue()));
		Data.Add(Spread);

	}

	return Data;
}