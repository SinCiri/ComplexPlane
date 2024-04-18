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
	m_plane_center = mapPixelToCoord(mousePixel);
	m_state = CALCULATING;
	cout << "X center: " << m_plane_center.x << "\t\t Y center: " << m_plane_center.y << endl;
}

//not too sure if this is working correctly
Vector2f ComplexPlane::mapPixelToCoord(Vector2i mousePixel) {
	cout << "mouse  X Actual: " << mousePixel.x << "\t\t mouse Y Actual: " << mousePixel.y << endl;
	Vector2f mouseLocation;
	cout << "pixel Size X: " << m_pixel_size.x << "\t\t pixel Size Y: " << m_pixel_size.y << endl;
	cout << "plane size X: " << m_plane_size.x << "\t\t plane Size Y: " << m_plane_size.y << endl;
	cout << "plane Center X: " << m_plane_center.x << "\t\t Plane Center Y: " << m_plane_center.y << endl;
	mouseLocation.x = ((float(mousePixel.x - 0)) / (m_pixel_size.x - 0)) * (m_plane_size.x) + (m_plane_center.x - m_plane_size.x / 2.0);
	mouseLocation.y = ((float(mousePixel.y)) / (m_pixel_size.y)) * ( m_plane_size.y) + (m_plane_center.y - m_plane_size.y / 2.0);
	cout << "x: " << mouseLocation.x << "\t y: " << mouseLocation.y << endl;
	return mouseLocation;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel){
	m_mouseLocation = mapPixelToCoord(mousePixel);
}
//Melody
void ComplexPlane::loadText(Text& text) {}
void ComplexPlane::updateRender() {}

int ComplexPlane::countIterationsCoord(Vector2f coords) { return 1; }


void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {
	//calculate j+i*pixelwidth while passing argument into function
	m_vArray[count].color = {r, g, b};
	m_state = DISPLAYING;
}