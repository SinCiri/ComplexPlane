#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	m_pixel_size.x = pixelWidth;
	m_pixel_size.y = pixelHeight;
	m_aspectRatio = pixelHeight * 1.0f / pixelWidth * 1.0f;
	//initialize vector2F
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray = VertexArray(Points);
	m_vArray.resize(pixelWidth *pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_vArray);
}


void ComplexPlane::zoomIn() {
	m_zoomCount++;
	double x, y;
	x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { float(x),float(y)};
	m_state = CALCULATING;
}

void ComplexPlane::zoomOut() {
	m_zoomCount--;
	double x, y;
	x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { float(x),float(y) };
	m_state = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel) {

}

Vector2f ComplexPlane::mapPixelToCoord(Vector2i mousePixel) {
	Vector2f mouseLocation;

	mouseLocation.x = ((mousePixel.x) * (m_pixel_size.x)) * (m_pixel_size.x - m_plane_size.x) + (m_plane_size.y);
	mouseLocation.y = ((mousePixel.y) * (m_pixel_size.y)) * (m_pixel_size.y - m_plane_size.x) + (m_plane_size.y);
	cout << "X: " << mouseLocation.x << "\tY: " << mouseLocation.y << endl;
	return mouseLocation;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel){}
//Melody
void ComplexPlane::loadText(Text& text) {}
void ComplexPlane::updateRender() {}

int ComplexPlane::countIterationsCoord(Vector2f coords) { return 1; }
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {}