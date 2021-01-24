#pragma once
#include "Logic2048.h"

class Controller2048 {
public:
	Controller2048(std::shared_ptr<Logic2048> logic)
		: logic(logic)
	{}

	void update();

private:
	std::shared_ptr<Logic2048> logic;

};
