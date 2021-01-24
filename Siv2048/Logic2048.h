#pragma once
#include <Siv3D.hpp>
#include "BoardParams.h"

class Logic2048 {
public:
	void initBoard();

	void createNewPiece();

	void flipHorizontal();
	void swapXY();

	int32 getValue(size_t idx) const;
	
	bool moveRight();
	bool moveLeft();
	bool moveUp();
	bool moveDown();

	bool canMove() const;

	[[nodiscard]] inline auto getScore() const noexcept { return score; }

private:
	Grid<int32> board;
	int64 score;
};
