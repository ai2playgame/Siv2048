#pragma once
#include <Siv3D.hpp>

struct RowMoveTest {
	// セルの合体抜きに考えるなら、動きに必要なのは、
	// 1. イージング係数
	// 2. 「移動完了後における」各セルの値（空の場合0）
	// 3. 移動後のセルの「移動前のインデックス」

	const Array<Point> rowPos
		{ {100, 200}, {200, 200}, {300, 200}, {400, 200} };
	Array<int32> rowVal{ 2, 0, 4, 0 };
	Array<int32> oldPosIdx{ -1, -1, -1, -1 };
	bool moveEnd = true;

	void moveLeft() {
		oldPosIdx = { 0, 2, -1, -1 };
		rowVal = { 2, 4, 0, 0 };
		moveEnd = false;
	}

	void moveRight() {
		oldPosIdx = { -1, -1, 0, 2 };
		rowVal = { 0, 0, 2, 4 };
		moveEnd = false;
	}

	void reset() {
		rowVal = { 2, 0, 4, 0 };
		oldPosIdx = { -1, -1, -1, -1 };
		moveEnd = true;
	}
};
