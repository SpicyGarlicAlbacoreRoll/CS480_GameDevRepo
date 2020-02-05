#pragma once
#include <gamelib_component.hpp>

class RunnerInputComponent : public GameLib::InputComponent {
	
public:

	virtual ~RunnerInputComponent() {}
	void update(GameLib::Actor& actor) override;

private:
	bool buttonPressed = false;
};