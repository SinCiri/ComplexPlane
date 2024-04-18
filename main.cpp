#include "ComplexPlane.h"


int main() {
	VideoMode vm(VideoMode::getDesktopMode().height / 2, VideoMode::getDesktopMode().width/2);
	ComplexPlane plane(VideoMode::getDesktopMode().height / 2, VideoMode::getDesktopMode().width / 2);
	RenderWindow window(vm, "WINDOW", Style::Default);

	while (window.isOpen()) {
		Event aevent;
		while (window.pollEvent(aevent)) {
			//Handle player input
			if (aevent.type == Event::MouseButtonPressed) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					cout << "Click" << endl;
					plane.setCenter(Mouse::getPosition());

				}
			}
			if (aevent.type == Event::MouseMoved) {
				plane.setMouseLocation(Mouse::getPosition());
			}

			//handle closing
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
			if (aevent.type == Event::Closed) {
				window.close();
			}
		}
		window.clear();
		window.display();
		

		//handle drawing
	}

	return 0;
}