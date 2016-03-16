#pragma once

#include "Object.h"
#include "FlareFleet.generated.h"


class UFlareSimulatedSector;
class UFlareSimulatedSpacecraft;
class AFlareGame;
class UFlareCompany;
class UFlareTravel;
class UFlareTradeRoute;
struct FFlareSpacecraftSave;

/** Fleet save data */
USTRUCT()
struct FFlareFleetSave
{
	GENERATED_USTRUCT_BODY()

	/** Given Name */
	UPROPERTY(EditAnywhere, Category = Save)
	FText Name;

	/** Sector identifier */
	UPROPERTY(EditAnywhere, Category = Save)
	FName Identifier;

	/** Fleet ships */
	UPROPERTY(VisibleAnywhere, Category = Save)
	TArray<FName> ShipImmatriculations;
};

UCLASS()
class HELIUMRAIN_API UFlareFleet : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/*----------------------------------------------------
	  Save
	----------------------------------------------------*/

	/** Load the fleet from a save file */
	virtual void Load(const FFlareFleetSave& Data);

	/** Save the fleet to a save file */
	virtual FFlareFleetSave* Save();


	/*----------------------------------------------------
		Gameplay
	----------------------------------------------------*/

	/** Get a name for this fleet (capital ship's name, etc) */
	FText GetName();

	virtual void AddShip(UFlareSimulatedSpacecraft* Ship);

	virtual void RemoveShip(UFlareSimulatedSpacecraft* Ship);

	/** Remove all ship from the fleet and delete it. Not possible during travel */
	virtual void Disband();

	virtual bool CanMerge(UFlareFleet* Fleet);

	virtual void Merge(UFlareFleet* Fleet);

	virtual void SetCurrentSector(UFlareSimulatedSector* Sector);

	void SetCurrentTravel(UFlareTravel* Travel);

	virtual void SetCurrentTradeRoute(UFlareTradeRoute* TradeRoute)
	{
		CurrentTradeRoute = TradeRoute;
	}

	virtual void InitShipList();


protected:

	TArray<UFlareSimulatedSpacecraft*>     FleetShips;

	UFlareCompany*			               FleetCompany;
	FFlareFleetSave                        FleetData;
	AFlareGame*                            Game;
	bool                                   IsShipListLoaded;
	UFlareSimulatedSector*                 CurrentSector;
	UFlareTravel*                          CurrentTravel;
	UFlareTradeRoute*                      CurrentTradeRoute;


public:

	/*----------------------------------------------------
		Getters
	----------------------------------------------------*/

	AFlareGame* GetGame() const
	{
		return Game;
	}

	FText GetFleetName() const
	{
		return FleetData.Name;
	}

	UFlareCompany* GetFleetCompany() const
	{
		return FleetCompany;
	}

	FName GetIdentifier() const
	{
		return FleetData.Identifier;
	}

	FFlareFleetSave* GetData()
	{
		return &FleetData;
	}

	TArray<UFlareSimulatedSpacecraft*>& GetShips();

	bool IsTraveling();

	bool CanTravel();

	uint32 GetImmobilizedShipCount();

	/** Return null if traveling */
	inline UFlareSimulatedSector* GetCurrentSector()
	{
		return CurrentSector;
	}

	/** Return null if not traveling */
	inline UFlareTravel* GetCurrentTravel()
	{
		return CurrentTravel;
	}

	/** Return null if not in a trade route */
	inline UFlareTradeRoute* GetCurrentTradeRoute()
	{
		return CurrentTradeRoute;
	}

};
