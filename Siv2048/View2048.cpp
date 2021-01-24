#include "View2048.h"

constexpr Color getCellColor(int32 value) {
	if (value == 2) return Color(237, 228, 222);
	if (value == 4) return Color(233, 218, 194);
	if (value == 8) return Color(242, 177, 118);
	if (value == 16) return Color(237, 141, 75);
	if (value == 32) return Color(237, 119, 94);
	if (value == 64) return Color(231, 76, 35);
	if (value == 128) return Color(242, 214, 104);
	if (value == 256) return Color(238, 209, 73);
	if (value == 512) return Color(227, 189, 45);
	return Color(226, 186, 15);
}

constexpr Color getFontColor(int32 value) {
	if (value == 2 || value == 4) return Palette::Dimgray;
	return Palette::White;
}

void View2048::draw() const
{
	Rect(offset.x - boardWallSize, offset.y - boardWallSize,
		BOARD_WIDTH * cellSize + boardWallSize * 2,
		BOARD_HEIGHT * cellSize + boardWallSize * 2).draw(boardBackground);

	for (auto i : step(BOARD_HEIGHT* BOARD_WIDTH)) {
		const Rect cellRect(calcCellPosition(i), cellSize - boardWallSize * 2);
		cellRect.draw(cellBackground);
		auto cellValue = logic->getValue(i);

		if (cellValue) {
			cellRect.draw(getCellColor(cellValue));
			font(cellValue).draw(Arg::center(cellRect.center()), getFontColor(cellValue));
		}
	}
}

Point View2048::calcCellPosition(size_t idx) const
{
	return Point{ idx % BOARD_WIDTH * cellSize, idx / BOARD_WIDTH * cellSize }
	.moveBy(offset).moveBy(boardWallSize, boardWallSize);
}
