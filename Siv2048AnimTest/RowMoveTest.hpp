#pragma once
#include <Siv3D.hpp>

struct RowMoveTest {
	// �Z���̍��̔����ɍl����Ȃ�A�����ɕK�v�Ȃ̂́A
	// 1. �C�[�W���O�W��
	// 2. �u�ړ�������ɂ�����v�e�Z���̒l�i��̏ꍇ0�j
	// 3. �ړ���̃Z���́u�ړ��O�̃C���f�b�N�X�v

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
