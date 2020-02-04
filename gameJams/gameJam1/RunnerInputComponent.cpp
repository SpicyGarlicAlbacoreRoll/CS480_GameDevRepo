#include <gamelib_locator.hpp>
#include "RunnerInputComponent.hpp"

void RunnerInputComponent::update(GameLib::Actor& actor)
{
	auto yAxis = GameLib::Locator::getInput()->axis1Y;

	if (yAxis) {
		actor.velocity.y = yAxis->getAmount();
	}


}
