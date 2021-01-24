#pragma once
#include <Siv3D.hpp>
#include "Logic2048.h"
#include "BoardParams.h"

namespace {
	constexpr Color boardBackground(142, 133, 125);
	constexpr Color cellBackground(204, 192, 180);
}

class View2048 {
public:
	View2048(std::shared_ptr<Logic2048> logic) : logic(logic) {}
	
	void draw() const;

private:
	Point calcCellPosition(size_t idx) const;

	std::shared_ptr<Logic2048> logic;
	
	Point offset = Point{ 100, 100 };
	int32 cellSize = 100;
	int32 boardWallSize = 5;
	Font font = Font(28, Typeface::Bold);
};
