#include "ComplexPlane.h"


int main() {
	VideoMode vm(1920/2, 1080/2);
	ComplexPlane plane(1920/2, 1080/2);
	RenderWindow window(vm, "WINDOW", Style::Default);

	while (window.isOpen()) {
		Event aevent;
		while (window.pollEvent(aevent)) {
			//Handle player input
			if (aevent.type == Event::MouseButtonPressed) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					cout << "Click" << endl;
					plane.setCenter(Mouse::getPosition());
					plane.zoomIn();
				}
				if (Mouse::isButtonPressed(Mouse::Right)) {
					plane.setCenter(Mouse::getPosition());
					plane.zoomOut();
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
		plane.updateRender();
		window.clear();
		window.draw(plane);
		window.display();
		

		//handle drawing
	}

	return 0;
}