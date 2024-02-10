#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EatWarsOverlay.generated.h"

class UProgressBar;
class UImage;

UCLASS()
class EATWARS_API UEatWarsOverlay : public UUserWidget {
	GENERATED_BODY()
	
public:
	void SetSkillImgAlpha(float Alpha);

	void SetSkillCdPercent(float Percent);

	void SetUltimateImgAlpha(float Alpha);

	void SetUltimateCdPercent(float Percent);

private:
	UPROPERTY(meta = (BindWidget))
	UImage *SkillImg;

	UPROPERTY(meta = (BindWidget))
	UProgressBar *SkillCd;

	UPROPERTY(meta = (BindWidget))
	UImage *UltimateImg;

	UPROPERTY(meta = (BindWidget))
	UProgressBar *UltimateCd;
};
