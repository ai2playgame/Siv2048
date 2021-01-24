#pragma once
#include <Siv3D.hpp>

struct FusionTest {
	const Array<Point> rowPos
		{ {100, 300}, {200, 300}, {300, 300}, {400, 300} };
	// ����Index�̒l
	Array<int32> rowVal{ 2, 0, 2, 4 };
	// ���̃Z�����ړ�����O�ɂ���Index�ԍ��i-1�Ŗ����j
	Array<int32> oldPosIdx{ -1, -1, -1, -1 };
	// ���̂���O�̃Z��������t���O
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
