#pragma once
#include <gamelib.hpp>
class RunnerActorComponent : public GameLib::ActorComponent {
public:
	virtual ~RunnerActorComponent() {}
	void update(GameLib::Actor& actor, GameLib::World& world) override;

//private:
	glm::vec3 oldPosition;
};