#include "BoxCollisionComponent.hpp"
#include "RunnerActorComponent.hpp"
#include <typeinfo>
BoxCollisionComponent::BoxCollisionComponent(std::string target_tag, std::vector<BoxCollisionComponent*> & colliders): colliders(colliders)
{
	setCollisionTag(target_tag);
	colliders.push_back(this);
}
void BoxCollisionComponent::update(GameLib::Actor& actor, GameLib::World& world)
{
	//for (auto& a : world.actors) {
	//	if (a->getId() == actor.getId() || !a->active) {
	//		continue;
	//	}
	//	else if (collides(*a, actor)) {
	//		//if (a->)
	//		//HFLOGDEBUG(actor.name.name);
	//		if (tag == BoxCollisionComponent::CollisionTag::Player)
	//			actor.position = originalPosition;
	//		
	//	}
	//}
	if (tag != BoxCollisionComponent::CollisionTag::Environment) {
		for (auto& a : colliders) {
			if (a->getActor()->getId() == this->actor->getId() || !a->getActor()->active) {
				continue;
			}
			else if (collides(a, this)) {
				if (tag == BoxCollisionComponent::CollisionTag::Player)
					if (a->tag == BoxCollisionComponent::CollisionTag::Environment) {
						actor.position = originalPosition;
					}
					else {
						HFLOGDEBUG("HIT ENEMY");
						actor.position = { 0, 0, 0 };
					}
				else if (tag == BoxCollisionComponent::CollisionTag::Enemy) {
						a->getActor()->position = { 2, 2, 0 };
					}
			}
		}
			originalPosition = actor.position;
	}
}

void BoxCollisionComponent::setActor(GameLib::Actor* targetActor)
{
	actor = targetActor;
}

GameLib::Actor * BoxCollisionComponent::getActor()
{
	return actor;
}

void BoxCollisionComponent::setCollisionTag(std::string tagString)
{
	if (tagString == "player") {
		tag = CollisionTag::Player;
	}
	else if (tagString == "enemy") {
		HFLOGDEBUG("ENEMY TAG SET");
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
		if (a.spriteId == 1 || a.spriteId == 2 || a.spriteId == 3) {
			return true;
		}
	}

	return false;
}

bool BoxCollisionComponent::collides(BoxCollisionComponent* a, BoxCollisionComponent* b)
{
	if (a->getActor()->position.x == b->getActor()->position.x && a->getActor()->position.y == b->getActor()->position.y) {
		HFLOGDEBUG("Collision via tag!");

		//if (a->tag == CollisionTag::Enemy || a->tag == CollisionTag::Environment) {
			return true;
		//}
	}

	return false;
}