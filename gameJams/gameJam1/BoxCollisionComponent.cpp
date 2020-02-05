#include "BoxCollisionComponent.hpp"

void BoxCollisionComponent::update(GameLib::Actor& actor, GameLib::World& world)
{
	for (auto& a : world.actors) {
		if (a->getId() == actor.getId() || !a->active) {
			continue;
		}
		else if (collides(*a, actor)) {
			//if (a->)
			
		}
	} 
}

bool BoxCollisionComponent::collides(GameLib::Actor& a, GameLib::Actor& b)
{
	if (a.position.x == b.position.x && a.position.y == b.position.y) {
		HFLOGDEBUG("Collision!");
		return true;
	}

	return false;
}
