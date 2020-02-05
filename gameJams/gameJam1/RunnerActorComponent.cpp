#include "RunnerActorComponent.hpp"

void RunnerActorComponent::update(GameLib::Actor& actor, GameLib::World& world)
{
	if (actor.velocity.y != 0) {
		actor.position.y = oldPosition.y;
		actor.velocity.y = 0;
	}
	else if (actor.velocity.x != 0) {
		actor.position.x = oldPosition.x;
		actor.velocity.x = 0;
	}
	oldPosition = actor.position;
}
