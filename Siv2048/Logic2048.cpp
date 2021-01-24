#include "Logic2048.h"

void Logic2048::initBoard() {
	board = Grid<int32>(BOARD_WIDTH + 2, BOARD_HEIGHT + 2, 0);
	// 壁設定
	for (auto i : step(board.width())) {
		board[0][i] = WALL_CELL;
		board[board.height() - 1][i] = WALL_CELL;
	}
	for (auto i : step(board.height())) {
		board[i][0] = WALL_CELL;
		board[i][board.width() - 1] = WALL_CELL;
	}
	createNewPiece();
	createNewPiece();

}

void Logic2048::createNewPiece() {
	// 空き場所へのポインタを配列に保持
	Array<int32*> freeCellPtrs;
	for (auto y = 1; y <= BOARD_HEIGHT; ++y) {
		for (auto x = 1; x <= BOARD_WIDTH; ++x) {
			if (board[y][x] == 0) {
				freeCellPtrs.push_back(&board[y][x]);
			}
		}
	}

	if (freeCellPtrs.size() == 0) {
		return;
	}
	// 75%の確率で2、25%の確率で4を生成
	auto newValue = RandomBool(0.75) ? 2 : 4;
	auto* choiceCell = freeCellPtrs.choice();
	*choiceCell = newValue;
}

void Logic2048::flipHorizontal() {
	for (auto y : step(1, BOARD_HEIGHT)) {
		for (auto x : step(1, BOARD_WIDTH / 2)) {
			std::swap(board[y][x], board[y][BOARD_WIDTH + 1 - x]);
		}
	}
}

void Logic2048::swapXY() {
	for (auto y = 1; y < BOARD_HEIGHT; ++y){
		for (auto x = y + 1; x <= BOARD_WIDTH; ++x){
			std::swap(board[y][x], board[x][y]);
		}
	}
}

int32 Logic2048::getValue(size_t idx) const {
	auto x = idx % BOARD_WIDTH;
	auto y = idx / BOARD_HEIGHT;
	return board[y + 1][x + 1];
}

bool Logic2048::moveRight() {
	bool moved = false;
	for (auto y = 1; y <= BOARD_HEIGHT; ++y) {
		auto dst = BOARD_WIDTH;	// セル移動先のx座標
		for (auto src = BOARD_WIDTH; src >= 1; --src) {
			auto srcValue = board[y][src];
			if (srcValue != 0) {
				if (src == BOARD_WIDTH) continue; // 右端の場合はスキップ
				if (board[y][dst] == 0) {	// dstが0 -> 移動先が空
					if (dst != src) {
						board[y][src] = 0;
						board[y][dst] = srcValue;
						moved = true;
					}
				}
				else if (board[y][dst] == srcValue) { // 移動先と同じ数字
					score += srcValue * 2;
					board[y][src] = 0;
					board[y][dst] = srcValue * 2;
					--dst;	// 移動先候補の座標を一つ左にずらす
					moved = true;
				}
				else { // 移動先に既に数字が入っている
					--dst;
					if (dst != src) {
						board[y][src] = 0;
						board[y][dst] = srcValue;
						moved = true;
					}
				}
			}
		}
	}

	createNewPiece();

	return moved;
}

bool Logic2048::moveLeft() {
	flipHorizontal();
	bool ret = moveRight();
	flipHorizontal();
	return ret;
}

bool Logic2048::moveUp() {
	swapXY();
	flipHorizontal();
	bool ret = moveRight();
	flipHorizontal();
	swapXY();
	return ret;
}

bool Logic2048::moveDown() {
	swapXY();
	bool ret = moveRight();
	swapXY();
	return ret;
}

bool Logic2048::canMove() const {
	for (auto y : step(1, BOARD_HEIGHT)) {
		for (auto x : step(1, BOARD_WIDTH)) {
			if (board[y][x] == 0 ||
				board[y][x] == board[y][x + 1] ||
				board[y][x] == board[y + 1][x]) {
				return true;
			}
		}
	}
	return false;
}