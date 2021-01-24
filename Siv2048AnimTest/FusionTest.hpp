#pragma once
#include <Siv3D.hpp>

struct FusionTest {
	const Array<Point> rowPos
		{ {100, 300}, {200, 300}, {300, 300}, {400, 300} };
	// 今のIndexの値
	Array<int32> rowVal{ 2, 0, 2, 4 };
	// そのセルが移動する前にいたIndex番号（-1で無効）
	Array<int32> oldPosIdx{ -1, -1, -1, -1 };
	// 合体する前のセルがいるフラグ
	Array<int32> preFusionVal{ 0, 0, 0, 0 };
	bool moveEnd = true;

	void moveLeft() {
		oldPosIdx = { 2, 3, -1, -1 };
		rowVal = { 4, 4, 0, 0 };
		preFusionVal = { 2, 0, 0, 0 };
		moveEnd = false;
	}

	void reset() {
		rowVal = { 2, 0, 2, 4 };
		oldPosIdx = { -1, -1, -1, -1 };
		preFusionVal = { 0, 0, 0, 0 };
		moveEnd = false;
	}
};
