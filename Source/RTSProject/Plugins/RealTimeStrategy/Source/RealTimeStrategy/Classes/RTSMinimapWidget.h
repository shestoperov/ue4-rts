#pragma once

#include "RealTimeStrategyPCH.h"

#include "Blueprint/UserWidget.h"
#include "Launch/Resources/Version.h" // Included only for IntelliSense.

#include "RTSMinimapWidget.generated.h"


class ARTSFogOfWarActor;
class ARTSMinimapVolume;
class ARTSPlayerController;
class ARTSVisionInfo;
class ARTSVisionVolume;


/**
* Widget for drawing a high-level overview of unit positions.
*/
UCLASS(Blueprintable)
class REALTIMESTRATEGY_API URTSMinimapWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public:
	/** Sets the vision info to draw on the minimap. */
	UFUNCTION(BlueprintCallable)
	void SetupVisionInfo(ARTSVisionInfo* VisionInfo);

    /** Event for custom drawing of units on the minimap (e.g. for drawing hero portraits for hero units). */
    virtual void NotifyOnDrawUnit(
        FPaintContext& Context,
        AActor* Actor,
        APlayerState* ActorOwner,
        const FVector2D& MinimapPosition,
        APlayerState* LocalPlayer) const;

	/** Event for custom drawing of units on the minimap (e.g. for drawing hero portraits for hero units). */
	UFUNCTION(BlueprintImplementableEvent, Category = "RTS", meta = (DisplayName = "OnDrawUnit"))
	void ReceiveOnDrawUnit(
		UPARAM(ref) FPaintContext& Context,
		AActor* Actor,
		APlayerState* ActorOwner,
		const FVector2D& MinimapPosition,
		APlayerState* LocalPlayer) const;

protected:
	void NativeConstruct() override;
    void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

#if ENGINE_MAJOR_VERSION > 4 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 20)
	int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
#else
	void NativePaint(FPaintContext& InContext) const override;
#endif

	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
    /** Brush for drawing the background of the current map. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Background")
    FSlateBrush MinimapBackground;

    /** Brush for drawing own units on the minimap. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Units")
    FSlateBrush OwnUnitsBrush;

    /** Brush for drawing enemy units on the minimap. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Units")
    FSlateBrush EnemyUnitsBrush;

    /** Brush for drawing neutral units on the minimap. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Units")
    FSlateBrush NeutralUnitsBrush;

    /** Whether to draw the minimap background layer. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Background")
    bool bDrawBackground = true;

    /** Whether to draw unit dots on the minimap, with OwnUnitsBrush, EnemyUnitsBrush and NeutralUnitsBrush. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Units")
    bool bDrawUnitsWithTeamColors = true;

    /** Whether to draw vision on the minimap, with UnknownAreasBrush, KnownAreasBrush and VisibleAreasBrush. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Vision")
    bool bDrawVision = true;

    /** Whether to show the current camera frustum on the minimap. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Camera")
    bool bDrawViewFrustum = true;


    /** Material to instance for rendering the fog of war effect. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS|Vision")
    UMaterialInterface* FogOfWarMaterial;

    /** Provides visibility information. */
    UPROPERTY()
    ARTSFogOfWarActor* FogOfWarActor;

    /** User interface material instance for rendering fog of war on the minimap. */
    UPROPERTY()
    UMaterialInstanceDynamic* FogOfWarMaterialInstance;

    /** Brush for drawing fog of war on the minimap. */
    FSlateBrush FogOfWarBrush;

	bool bMouseDown;

    UPROPERTY()
	ARTSMinimapVolume* MinimapVolume;

	FVector MinimapWorldSize;

    UPROPERTY()
	ARTSVisionInfo* VisionInfo;

    UPROPERTY()
	ARTSVisionVolume* VisionVolume;

	void DrawBackground(FPaintContext& InContext) const;
	void DrawUnits(FPaintContext& InContext) const;
	void DrawVision(FPaintContext& InContext) const;
	void DrawViewFrustum(FPaintContext& InContext) const;

	void DrawBoxWithBrush(FPaintContext& InContext, const FVector2D& Position, const FSlateBrush& Brush) const;

	FReply HandleMinimapClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	FVector MinimapToWorld(const FVector2D& MinimapPosition) const;
	bool ViewportToWorld(ARTSPlayerController* Player, const FVector2D& ViewportPosition, FVector& OutWorldPosition) const;
	FVector2D WorldToMinimap(const FVector& WorldPosition) const;
};