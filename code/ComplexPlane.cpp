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
	Vector2f mouseLocation;
	//range of x = [0, m_plane_size.x] aka [a, b]
	//range of y = [m_plane_size.y, 0] aka [c, d]
	//((n  - a) / (b - a)) * (d - c) + c
	mouseLocation.x = ((float(mousePixel.x)) / (m_pixel_size.x)) * (m_plane_size.x) + (m_plane_center.x - m_plane_size.x / 2.0);
	mouseLocation.y = ((float(mousePixel.y)- m_plane_size.y) / (m_pixel_size.y)) * ( m_plane_size.y) + (m_plane_center.y - m_plane_size.y / 2.0);
	cout << "x: " << mouseLocation.x << "\t y: " << mouseLocation.y << endl;
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
	complex<double> z(0, 0);
	complex<double> c(coords.x, coords.y);
	for (int i = 0; i < MAX_ITER; i++) {
		cout << "i: " << i << "\nz: " << z << endl;
		z = (z*z) + c;
		cout << "(z*z) + c: " << z << endl;
		if (abs(z) >= 2) {
			cout << "final iteration: " << i << endl << endl;
			return i;
		}
	}
	return 0;
}


void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {
	//calculate j+i*pixelwidth while passing argument into function
	m_vArray[count].color = { r, g, b };
}