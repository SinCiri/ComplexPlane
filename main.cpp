#include "ComplexPlane.h"


int main() {
	VideoMode vm(VideoMode::getDesktopMode().height / 2, VideoMode::getDesktopMode().width/4);
	ComplexPlane plane(VideoMode::getDesktopMode().height / 2, VideoMode::getDesktopMode().width / 2);
	RenderWindow window(vm, "WINDOW", Style::Default);

	while (window.isOpen()) {
		Event aevent;
		while (window.pollEvent(aevent)) {
			//Handle player input
			if (aevent.type == Event::MouseButtonPressed) {
				if (aevent.type == Mouse::Button::Left) {
					plane.setMouseLocation(Mouse::getPosition());

				}
			}

			//handle closing
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
			if (aevent.type == Event::Closed) {
				window.close();
			}
		}

		//handle drawing
	}

	return 0;
}