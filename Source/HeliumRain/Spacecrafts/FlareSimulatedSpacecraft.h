#pragma once

#include "Object.h"
#include "../Game/FlareSimulatedSector.h"
#include "Subsystems/FlareSimulatedSpacecraftDamageSystem.h"
#include "Subsystems/FlareSimulatedSpacecraftWeaponsSystem.h"
#include "../Economy/FlareResource.h"
#include "FlareSimulatedSpacecraft.generated.h"

class UFlareSimulatedSector;
class UFlareFleet;
class UFlareCargoBay;
class UFlareFactory;

UCLASS()
class HELIUMRAIN_API UFlareSimulatedSpacecraft : public UObject
{
	 GENERATED_UCLASS_BODY()

public:

	/*----------------------------------------------------
		Save
	----------------------------------------------------*/

	/** Load the ship from a save file */
	virtual void Load(const FFlareSpacecraftSave& Data);

	/** Save the ship to a save file */
	virtual FFlareSpacecraftSave* Save();

	/** Get the parent company */
	virtual UFlareCompany* GetCompany() const;

	/** Get the ship size class */
	virtual EFlarePartSize::Type GetSize();

	virtual FName GetImmatriculation() const;

	/** Check if this is a military ship */
	virtual bool IsMilitary() const;

	/** Check if this is a station ship */
	virtual bool IsStation() const;

	virtual bool CanFight() const;

	virtual bool CanTravel() const;


	/*----------------------------------------------------
		Sub system
	----------------------------------------------------*/

	virtual UFlareSimulatedSpacecraftDamageSystem* GetDamageSystem() const;

	virtual UFlareSimulatedSpacecraftWeaponsSystem* GetWeaponsSystem() const;

    /*----------------------------------------------------
        Gameplay
    ----------------------------------------------------*/

	virtual void SetCurrentSector(UFlareSimulatedSector* Sector);

	virtual void SetCurrentFleet(UFlareFleet* Fleet)
	{
		CurrentFleet = Fleet;
	}

	virtual void SetSpawnMode(EFlareSpawnMode::Type SpawnMode);

	virtual bool CanBeFlown(FText& OutInfo) const;

	/** Set asteroid data from an asteroid save */
	void SetAsteroidData(FFlareAsteroidSave* Data);

	void SetDynamicComponentState(FName Identifier, float Progress = 0.f);

	void Upgrade()
	{
		SpacecraftData.Level++;
	}

	void SetActiveSpacecraft(AFlareSpacecraft* Spacecraft)
	{
		if(Spacecraft)
		{
			FCHECK(ActiveSpacecraft == NULL || ActiveSpacecraft == Spacecraft);
		}
		ActiveSpacecraft = Spacecraft;
	}

	void ForceUndock();

	void SetTrading(bool Trading);

	void SetRepairing(bool Repairing);

	void SetRefilling(bool Refilling);

	/** This ship was harpooned */
	void SetHarpooned(UFlareCompany* OwnerCompany);

	bool IsHarpooned()
	{
		return SpacecraftData.HarpoonCompany != NAME_None;
	}

	UFlareCompany* GetHarpoonCompany();

	void ResetCapture(UFlareCompany* Company = NULL);

	bool TryCapture(UFlareCompany* Company, int32 CapturePoint);

	/*----------------------------------------------------
		Resources
	----------------------------------------------------*/

	bool CanTradeWith(UFlareSimulatedSpacecraft* OtherSpacecraft);

	EFlareResourcePriceContext::Type GetResourceUseType(FFlareResourceDescription* Resource);
	void LockResources();

protected:

	void RemoveCapturePoint(FName CompanyIdentifier, int32 CapturePoint);

    /*----------------------------------------------------
        Protected data
    ----------------------------------------------------*/

    // Gameplay data
	FFlareSpacecraftSave          SpacecraftData;
	FFlareSpacecraftDescription*  SpacecraftDescription;

	AFlareGame*                   Game;

	AFlareSpacecraft*                   ActiveSpacecraft;

	UFlareFleet*                  CurrentFleet;
	UFlareSimulatedSector*        CurrentSector;

	// Systems
	UPROPERTY()
	UFlareSimulatedSpacecraftDamageSystem*                  DamageSystem;
	UPROPERTY()
	UFlareSimulatedSpacecraftWeaponsSystem*                 WeaponsSystem;

	UPROPERTY()
	TArray<UFlareFactory*>                                  Factories;

	UPROPERTY()
	UFlareCargoBay*                                         CargoBay;
public:

    /*----------------------------------------------------
        Getters
    ----------------------------------------------------*/

	inline AFlareGame* GetGame() const
	{
		return Game;
	}	

	inline bool IsActive() const
	{
		return ActiveSpacecraft != NULL;
	}

	inline AFlareSpacecraft* GetActive() const
	{
		return ActiveSpacecraft;
	}

	inline FFlareSpacecraftSave& GetData()
	{
		return SpacecraftData;
	}

	inline FText GetNickName() const
	{
		return SpacecraftData.NickName;
	}

	/** Return null if traveling */
	inline UFlareSimulatedSector* GetCurrentSector() const
	{
		return CurrentSector;
	}

	/** Return null if not in a fleet */
	inline UFlareFleet* GetCurrentFleet() const
	{
		return CurrentFleet;
	}

	/** Return null if not in a trade route */
	inline UFlareTradeRoute* GetCurrentTradeRoute( )const
	{
		return (CurrentFleet ? CurrentFleet->GetCurrentTradeRoute() : NULL);
	}

	inline FFlareSpacecraftDescription* GetDescription() const
	{
		return SpacecraftDescription;
	}

	inline UFlareCargoBay* GetCargoBay() const
	{
		return CargoBay;
	}

	inline TArray<UFlareFactory*>& GetFactories()
	{
		return Factories;
	}

	inline FVector GetSpawnLocation() const
	{
		return SpacecraftData.Location;
	}

	inline int32 GetLevel() const
	{
		return SpacecraftData.Level;
	}

	inline bool IsTrading() const
	{
		return SpacecraftData.IsTrading;
	}

	inline bool IsRepairing() const
	{
		return SpacecraftData.IsRepairing;
	}

	inline bool IsRefilling() const
	{
		return SpacecraftData.IsRefilling;
	}

	inline bool IsConsumeResource(FFlareResourceDescription* Resource) const
	{
		return HasCapability(EFlareSpacecraftCapability::Consumer) && !SpacecraftData.SalesExcludedResources.Contains(Resource->Identifier);
	}

	int64 GetStationUpgradeFee() const
	{
		return SpacecraftData.Level * SpacecraftDescription->CycleCost.ProductionCost;
	}

	inline bool HasCapability(EFlareSpacecraftCapability::Type Capability) const
	{
		return GetDescription()->Capabilities.Contains(Capability);
	}

	EFlareHostility::Type GetPlayerWarState() const;

	int32 GetCapturePoint(UFlareCompany* Company) const;

	int32 GetCapturePointThreshold() const;

	float GetStationEfficiency();
};
