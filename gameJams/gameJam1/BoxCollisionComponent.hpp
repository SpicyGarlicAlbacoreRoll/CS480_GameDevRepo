#pragma once
#include <gamelib.hpp>

class BoxCollisionComponent : public GameLib::SimplePhysicsComponent {
public:

	virtual ~BoxCollisionComponent() {}
	void update(GameLib::Actor& actor, GameLib::World& world) override;

private:
	bool collides(GameLib::Actor& a, GameLib::Actor& b);
};