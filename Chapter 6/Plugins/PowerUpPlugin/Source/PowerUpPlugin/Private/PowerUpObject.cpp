#include "PowerUpPluginPrivatePCH.h"
#include "PowerUpObject.h"

UPowerUpObject::UPowerUpObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	int iType = FMath::Rand() % 3;

	switch (iType)
	{
	case 0:
	{
		Type = EPowerUp::SPEED;
		break;
	}
	case 1:
	{
		Type = EPowerUp::SMASH;
		break;
	}
	case 2:
	{
		Type = EPowerUp::MAGNET;
		break;
	}
	default:
		break;
	}
}

EPowerUp UPowerUpObject::GetType()
{
	return Type;
}
