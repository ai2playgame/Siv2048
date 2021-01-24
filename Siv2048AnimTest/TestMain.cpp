#include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include "RowMoveTest.hpp"
#include "FusionTest.hpp"

Color getColor(int32 val) {
	if (val == 2) return Color(241, 176, 122);
	else return Color(246, 93, 59);
}

template <class Type>
[[nodiscard]]
inline constexpr auto map(double value, double start1, double stop1, const Type& start2, const Type& stop2) noexcept
{
	return Math::Lerp(start2, stop2, Math::InvLerp(start1, stop1, value));
}

void Main()
{
	constexpr Point p1{ 100, 100 };
	constexpr Point p2{ 300, 100 };
	constexpr int32 boxSize = 80;

	Font font(30, Typeface::Bold);
		
	RowMoveTest test;
	FusionTest fusion;

	Stopwatch stopwatch;
	stopwatch.pause();

	constexpr double moveTime = 0.3; // [sec]で移動
	constexpr double timerSpeed = moveTime / 1.0;

	while (System::Update()) {
		/* ========== 入力処理 ========== */
		ClearPrint();

		if (KeyRight.down()) {
			stopwatch.restart();
			test.moveRight();
		}
		else if (KeyLeft.down()) {
			stopwatch.restart();
			test.moveLeft();
			fusion.moveLeft();
		}
		else if (KeyUp.down()) {
			stopwatch.reset();
			test.reset();
			// fusion.reset();
		}

		/* ========== イージング係数計算 ========== */
		const double t = Min(stopwatch.sF() / timerSpeed, 1.0);
		const double e = EaseInOutExpo(t);

		/* ========== セルの縮退なしの移動テスト ========== */
		for (auto [i, value] : Indexed(test.rowVal)) {
			if (test.moveEnd) {
				// 動きが止まっているなら、rowValをそのまま描画
				if (value) {
					Rect rect(test.rowPos[i], boxSize);
					rect.draw(getColor(value));
					font(value).draw(Arg::center(rect.center()));
				}
			}
			else {
				// 動いている途中なら、イージングで移動
				if (value) {
					const Vec2 movingPos = test.rowPos[test.oldPosIdx[i]]
						.lerp(test.rowPos[i], e);
					Rect rect(movingPos.asPoint(), boxSize);
					rect.draw(getColor(value));
					font(value).draw(Arg::center(rect.center()));
				}
				if (t == 1.0) test.moveEnd = true;
			}
		}

		/* ========== セルの合体ありの移動テスト ========== */
		if (fusion.moveEnd) {
			for (auto [i, value] : Indexed(fusion.rowVal)) {
				// 動きが止まっているならそのまま描画
				if (value) {
					Rect rect(fusion.rowPos[i], boxSize);
					rect.draw(getColor(value));
					font(value).draw(Arg::center(rect.center()));
				}
			}
		} else {
			// 動いている最中のときは、
			// まず吸収されるセルだけ描画する
			for (auto [i_old, value_old] : Indexed(fusion.preFusionVal)) {
				if (value_old) {
					Rect rect(fusion.rowPos[i_old], boxSize);
					rect.draw(getColor(value_old));
					font(value_old).draw(Arg::center(rect.center()));
				}
			}
			// その後動きのあるセルを描画
			for (auto [i, value] : Indexed(fusion.rowVal)) {
				if (value) {
					if (fusion.preFusionVal[i] != 0) {
						const Vec2 movingPos = fusion.rowPos[fusion.oldPosIdx[i]]
							.lerp(fusion.rowPos[i], e);
						Rect rect(movingPos.asPoint(), boxSize);
						double cellScale = map(e, 0.0, 1.0, 1.1, 1.0);
						Mat3x2 scaledMat = Mat3x2::Scale(cellScale, rect.center());
						const Transformer2D t(scaledMat, false);
						rect.draw(getColor(value));
						font(value).draw(Arg::center(rect.center()));
					}
					else {
						const Vec2 movingPos = fusion.rowPos[fusion.oldPosIdx[i]]
							.lerp(fusion.rowPos[i], e);
						Rect rect(movingPos.asPoint(), boxSize);
						rect.draw(getColor(value));
						font(value).draw(Arg::center(rect.center()));
					}
				}
				if (t == 1.0) fusion.moveEnd = true;
			}
		}
	}
}
