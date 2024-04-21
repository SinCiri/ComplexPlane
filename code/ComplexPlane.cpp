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
	// cout << "mouse  X Actual: " << mousePixel.x << "\t\t mouse Y Actual: " << mousePixel.y << endl;
	Vector2f mouseLocation;
	// cout << "pixel Size X: " << m_pixel_size.x << "\t\t pixel Size Y: " << m_pixel_size.y << endl;
	// cout << "plane size X: " << m_plane_size.x << "\t\t plane Size Y: " << m_plane_size.y << endl;
	// cout << "plane Center X: " << m_plane_center.x << "\t\t Plane Center Y: " << m_plane_center.y << endl;
	mouseLocation.x = ((float(mousePixel.x - 0)) / (m_pixel_size.x - 0)) * (m_plane_size.x) + (m_plane_center.x - m_plane_size.x / 2.0);
	mouseLocation.y = ((float(mousePixel.y - 0)) / (m_pixel_size.y - 0)) * (m_plane_size.y) + (m_plane_center.y - m_plane_size.y / 2.0);
	// cout << "x: " << mouseLocation.x << "\t y: " << mouseLocation.y << endl;
	return mouseLocation;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel){
	m_mouseLocation = mapPixelToCoord(mousePixel);
}

//Melody
void ComplexPlane::loadText(Text& text) {
	stringstream output;
	output << "Mandelbrot Set\n" <<
		"Center: " << "(" << m_plane_center.x << ", " << m_plane_center.y << ")\n" <<
		"Cursor: " << "(" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n" <<
		"Left-click to Zoom in\n" <<
		"Right-click to Zoom out\n";
	text.setString(output.str());
}

void ComplexPlane::updateRender() {
	size_t iterations = 0;
	Vector2f coordinate;
	if (m_state == CALCULATING) {
		//loop through all pixels, (x, y)screen = (j, i)vector
		for (int j = 0; j < m_plane_size.x; j++) {
			for (int i = 0; i < m_plane_size.y; i++) {
				m_vArray[j + i * m_pixel_size.x].position = { (float)j,(float)i };
				coordinate = mapPixelToCoord(m_pixel_size);
				iterations = countIterationsCoord(coordinate);
				Uint8 r = iterations;
				Uint8 g = iterations;
				Uint8 b = iterations;
				iterationsToRGB(iterations, r, g, b);
				m_vArray[j + i * m_pixel_size.x].color = { r,g,b };
			}
		}
		
	}
	m_state = DISPLAYING;
}

int ComplexPlane::countIterationsCoord(Vector2f coords) {
	complex<float> c(coords.x, coords.y);
	complex<float> z(0, 0);
	size_t i = 0;
	for (i = 0; i < MAX_ITER; i++) {
		z = z * z + c;
		if (abs(z) > 2.0) {
			return i;
		}
	}
	return i;
}


void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {
	if (count == MAX_ITER) {
		r = 0; b = 0; g = 0;
	}
	else if (0 < count && count < 10) {
		r = 51; b = 34; g = 66;
	}
	else if (11 < count && count < 24) {
		r = 65; b = 155; g = 55;
	}
	else if (25 < count && count < 50) {
		r = 42; g = 44; b = 86;
	}
	else {
		r = 144; b = 23; g = 44;
	}
}