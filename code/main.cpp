#include "ComplexPlane.h"


int width = VideoMode::getDesktopMode().width;
int height = VideoMode::getDesktopMode().height;

VideoMode vm(width /2, height /2);
ComplexPlane plane(width /2, height /2);
RenderWindow window(vm, "WINDOW", Style::Default);

Text text;
Font font;


int main() {
	font.loadFromFile("type_writer_font.ttf");
	text.setFont(font);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::White);
	text.setPosition(0, 0);
	


	while (window.isOpen()) {
		Event aevent;
		if (window.pollEvent(aevent)) {
			
			//Handle player input
			if (aevent.type == Event::MouseButtonPressed) {
				//zoom in
				if (Mouse::isButtonPressed(Mouse::Left)) {
					plane.setCenter(Mouse::getPosition());
					plane.zoomIn();
				}
				//zoom out
				else if (Mouse::isButtonPressed(Mouse::Right)) {
					plane.setCenter(Mouse::getPosition());
					plane.zoomOut();
					
				}
			}
			
			//track mouse position
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

		//handle updating
		plane.updateRender();
		plane.loadText(text);
		//handle drawing		
		window.clear();
		window.draw(plane);
		window.draw(text);
		window.display();
		
	}
	return 0;
}