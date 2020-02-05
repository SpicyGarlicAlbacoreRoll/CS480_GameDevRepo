#include "MonsterActorComponent.hpp"

void MonsterActorComponent::update(GameLib::Actor& actor, GameLib::World& world)
{
	currentFrame += actor.dt;

	// after enough time...
	if (currentFrame > movementSpeed) {
		HFLOGDEBUG("Enemy Moving");
		actor.position.y += 1;
		currentFrame = 0;
	}
}


