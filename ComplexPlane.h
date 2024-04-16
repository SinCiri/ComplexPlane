#pragma once
#pragma once
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <sstream>


const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum State {CALCULATING , DISPLAYING};

using namespace sf;
using namespace std;

class ComplexPlane : public Drawable {
private:
	VertexArray m_vArray;
	State m_state;
	Vector2i m_pixel_size;
	Vector2f m_mouseLocation;
	Vector2f m_plane_size;
	int m_zoomCount;
	float m_aspectRatio;
	//Melody //Rami
	int countIterationsCoord(Vector2f coords);
	void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
	Vector2f mapPixelToCoord(Vector2i mousePixel);

public:
	ComplexPlane(int pixelWidth, int pixelHeight);
	void draw(RenderTarget& target, RenderStates states) const;
	//Rami
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2i mousePixel);
	void setMouseLocation(Vector2i mousePixel);
	//Melody
	void loadText(Text& text);
	void updateRender();


};