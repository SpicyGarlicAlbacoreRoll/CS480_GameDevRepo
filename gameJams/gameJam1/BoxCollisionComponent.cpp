#include "BoxCollisionComponent.hpp"
#include "RunnerActorComponent.hpp"
#include <typeinfo>
BoxCollisionComponent::BoxCollisionComponent(std::string target_tag)
{
	setCollisionTag(target_tag);
}
void BoxCollisionComponent::update(GameLib::Actor& actor, GameLib::World& world)
{
	for (auto& a : world.actors) {
		if (a->getId() == actor.getId() || !a->active) {
			continue;
		}
		else if (collides(*a, actor)) {
			//if (a->)
			//HFLOGDEBUG(actor.name.name);
			if (tag == BoxCollisionComponent::CollisionTag::Player)
				actor.position = originalPosition;
			
		}
	}
	if (tag != BoxCollisionComponent::CollisionTag::Environment) {
		originalPosition = actor.position;
	}
}

void BoxCollisionComponent::setCollisionTag(std::string tagString)
{
	if (tagString == "player") {
		tag = CollisionTag::Player;
	}
	else if (tagString == "enemy") {
		tag = CollisionTag::Enemy;
	}
	else if (tagString == "environment") {
		tag = CollisionTag::Environment;
	}
}

BoxCollisionComponent::CollisionTag BoxCollisionComponent::getCollisionTag()
{
	return tag;
}

bool BoxCollisionComponent::collides(GameLib::Actor& a, GameLib::Actor& b)
{
	if (a.position.x == b.position.x && a.position.y == b.position.y) {
		HFLOGDEBUG("Collision!");
		if (a.spriteId == 1) {
			return true;
		}
	}

	return false;
}
