#pragma once
#include <gamelib.hpp>

class MonsterActorComponent : public GameLib::ActorComponent {
public:
    virtual ~MonsterActorComponent() {}
    void update(GameLib::Actor& actor, GameLib::World& world) override;

private:
    const float movementSpeed = 1.0f;
    float currentFrame = 0.0f;
};