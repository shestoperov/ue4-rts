#pragma once

#include "RealTimeStrategyPCH.h"

#include "Components/ActorComponent.h"

#include "RTSPlayerAdvantageComponent.generated.h"


/**
* Attach to player or AI controllers. Provides bonuses for various gameplay elements.
*/
UCLASS(meta = (BlueprintSpawnableComponent))
class REALTIMESTRATEGY_API URTSPlayerAdvantageComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URTSPlayerAdvantageComponent(const FObjectInitializer& ObjectInitializer);

    /** Whether units controlled by the player are invulnerable, or not. */
    bool IsGodModeEnabled() const;

    /** Gets the factor to multiply all construction and production speed with. */
    float GetSpeedBoostFactor() const;

    /** Sets whether units controlled by the player are invulnerable, or not. */
    void SetGodModeEnabled(bool bInGodModeEnabled);

    /** Sets the factor to multiply all construction and production speed with. */
    void SetSpeedBoostFactor(float InSpeedBoostFactor);

private:
    /** Whether units controlled by the player are invulnerable, or not. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Advantage")
    bool bGodModeEnabled;

    /** Factor to multiply all construction and production speed with. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Advantage")
    float SpeedBoostFactor;
};