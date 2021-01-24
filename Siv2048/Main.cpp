# include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include "Logic2048.h"
#include "View2048.h"
#include "Controller2048.h"

void Main()
{
	constexpr Color SceneBackground(250, 247, 238);

	Scene::SetBackground(SceneBackground);
	Window::Resize(600, 600);
	auto logic = std::make_shared<Logic2048>();
	logic->initBoard();

	View2048 view(logic);
	Controller2048 controller(logic);

	Font font(30, Typeface::Bold);

	while (System::Update())
	{
		ClearPrint();

		controller.update();
		
		view.draw();
		
		Print << logic->getScore();

		if (!logic->canMove()) {
			font(U"Game Over!").draw(Arg::center(Scene::Center().moveBy(Point(0, -240))),
					Palette::Red);
			Print << U"Restart: Press \"R\" Key";
		}

	}
}
