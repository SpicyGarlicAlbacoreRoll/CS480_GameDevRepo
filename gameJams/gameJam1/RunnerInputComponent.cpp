#include <gamelib_locator.hpp>
#include "RunnerInputComponent.hpp"

void RunnerInputComponent::update(GameLib::Actor& actor)
{
	auto yAxis = GameLib::Locator::getInput()->axis1Y;
	auto xAxis = GameLib::Locator::getInput()->axis1X;

	if (yAxis) {
		actor.velocity.y = yAxis->getAmount();
	}

	// shifting movement
	if (xAxis) {
		if (xAxis->getAmount() != 0 && !buttonPressed) {
			actor.position.x += xAxis->getAmount();
			buttonPressed = true;
		}
		else if (xAxis->getAmount() == 0 && buttonPressed) {
			buttonPressed = false;
		}
	}

}
