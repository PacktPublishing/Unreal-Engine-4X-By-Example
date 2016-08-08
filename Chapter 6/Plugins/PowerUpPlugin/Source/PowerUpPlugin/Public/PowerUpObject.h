#pragma once
#include "PowerUpObject.generated.h"

enum class EPowerUp : uint8
{
	SPEED = 1 UMETA(DisplayName = "Speed"),
	SMASH = 2 UMETA(DisplayName = "Smash"),
	MAGNET = 3 UMETA(DisplayName = "Magnet")
};

UCLASS()
class POWERUPPLUGIN_API UPowerUpObject : public UObject
{
	GENERATED_UCLASS_BODY()
public:

	EPowerUp GetType();

private:
	EPowerUp Type;
};
