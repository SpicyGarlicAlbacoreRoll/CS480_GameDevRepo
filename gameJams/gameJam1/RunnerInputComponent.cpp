#include <gamelib_locator.hpp>
#include "RunnerInputComponent.hpp"

void RunnerInputComponent::update(GameLib::Actor& actor)
{
	auto yAxis = GameLib::Locator::getInput()->axis1Y;
	auto xAxis = GameLib::Locator::getInput()->axis1X;

	if (yAxis) {
		//actor.velocity.y = yAxis->getAmount();
		if (yAxis->getAmount() != 0 && !buttonPressedY) {
			actor.position.y += yAxis->getAmount();
			buttonPressedY = true;
		}
		else if (yAxis->getAmount() == 0 && buttonPressedY) {
			buttonPressedY = false;
		}
	}

	// shifting movement
	if (xAxis) {
		if (xAxis->getAmount() != 0 && !buttonPressedX) {
			actor.position.x += xAxis->getAmount();
			buttonPressedX = true;
		}
		else if (xAxis->getAmount() == 0 && buttonPressedX) {
			buttonPressedX = false;
		}
	}

}
