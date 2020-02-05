#pragma once
#include <gamelib.hpp>

class BoxCollisionComponent : public GameLib::SimplePhysicsComponent {
public:

	BoxCollisionComponent(std::string tag);
	virtual ~BoxCollisionComponent() {}
	void update(GameLib::Actor& actor, GameLib::World& world) override;



	enum class CollisionTag {Player, Environment, Enemy};


	void setCollisionTag(std::string tagString);
	CollisionTag getCollisionTag();

private:
	glm::vec3 originalPosition;
	CollisionTag tag = CollisionTag::Environment;
	bool collides(GameLib::Actor& a, GameLib::Actor& b);
};