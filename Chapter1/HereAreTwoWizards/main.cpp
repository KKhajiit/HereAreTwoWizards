#include "Game2D.h"
#include "MyGameExample.h"

namespace jm
{

}

int main(void)
{
	
	//jm::MouseExample().init("This is my digital canvas!", 1000, 1000, false).run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::RotatingStarExample().init("Rotating Star Example", 1280, 960, false).run();
	//jm::PrimitivesGallery().init("Primitive Gallery", 1280, 960, false).run();
	//jm::SolarSystem().run();
	//jm::FaceExample().run();
	//jm::WalkingPerson().run();
	//jm::TankExample().run();
	jm::MyGameExample().init("Here Are Two Wizards", 1920, 1080, false).run();

	return 0;
}
