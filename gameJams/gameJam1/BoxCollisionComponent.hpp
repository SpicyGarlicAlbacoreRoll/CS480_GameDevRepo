#pragma once
#include <gamelib.hpp>

class BoxCollisionComponent : public GameLib::SimplePhysicsComponent {
public:

	BoxCollisionComponent(std::string tag, std::vector<BoxCollisionComponent*>& colliders);
	virtual ~BoxCollisionComponent() {}
	void update(GameLib::Actor& actor, GameLib::World& world) override;



	enum class CollisionTag {Player, Environment, Enemy};
	void setActor(GameLib::Actor * targetActor);
	GameLib::Actor * getActor();
	void setCollisionTag(std::string tagString);
	CollisionTag getCollisionTag();

private:
	glm::vec3 originalPosition;
	GameLib::Actor * actor;
	std::vector<BoxCollisionComponent*> colliders;
	CollisionTag tag = CollisionTag::Environment;
	bool collides(GameLib::Actor& a, GameLib::Actor& b);
	bool collides(BoxCollisionComponent* a, BoxCollisionComponent* b);
};