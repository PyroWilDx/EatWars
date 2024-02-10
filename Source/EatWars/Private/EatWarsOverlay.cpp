#include "EatWarsOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

void UEatWarsOverlay::SetSkillImgAlpha(float Alpha) {
	if (SkillImg != nullptr) {
		SkillImg->SetOpacity(Alpha);
	}
}

void UEatWarsOverlay::SetSkillCdPercent(float Percent) {
	if (SkillCd != nullptr) {
		SkillCd->SetPercent(Percent);
	}
}

void UEatWarsOverlay::SetUltimateImgAlpha(float Alpha) {
	if (UltimateImg != nullptr) {
		UltimateImg->SetOpacity(Alpha);
	}
}

void UEatWarsOverlay::SetUltimateCdPercent(float Percent) {
	if (UltimateCd != nullptr) {
		UltimateCd->SetPercent(Percent);
	}
}
