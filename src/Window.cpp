#include "Window.hpp"

/* 
 * Constructor. 
 * Variable explanations in .hpp
 * It will throw an error if height or width are too small (<0) or too large,
 * which would make calculations way too long.
*/
Window::Window(int h, int w, std::vector<std::vector<int>> m, std::vector<std::pair<std::vector<int>, int>> r) {
	if(h <= 0 || w <= 0) {
		throw poorParameterException();
	}
	else if(h > 100 || w > 100) {
		throw tooLargeImageException();
	}
	height = h;
	width = w;
	map = m;
	routes = r;
	calcScale();
	colors = {sf::Color::Yellow, sf::Color::Blue, sf::Color::Green, sf::Color::Cyan, sf::Color::Magenta};
	isRunning = false;
	isCalculating = false;
	isLearning = false;
}

// Destructor
Window::~Window() {
	
}

// Copy constructor
Window::Window(const Window &windowIN) {
	height = windowIN.height;
	width = windowIN.width;
	map = windowIN.map;
	scale = windowIN.scale;
	routes = windowIN.routes;
	colors = windowIN.colors;
	isRunning = windowIN.isRunning;
	isCalculating = windowIN.isCalculating;
	isLearning = windowIN.isLearning;
}

// = operator overload
Window& Window::operator=(const Window &windowIN) {
	height = windowIN.height;
	width = windowIN.width;
	map = windowIN.map;
	scale = windowIN.scale;
	routes = windowIN.routes;
	colors = windowIN.colors;
	isRunning = windowIN.isRunning;
	isCalculating = windowIN.isCalculating;
	isLearning = windowIN.isLearning;
	return *this;
}


//Adds a route to the vector of routes.
void Window::addRoute(std::vector<int> route) {
	std::pair <std::vector<int>, int> pair;
	pair = std::make_pair(route, 0);
	routes.push_back(pair);
}

/*
 * Calculates the scale, so that the graphics window will be
 * approximately the same time, no matter how big the original 
 * png picture is.
*/
void Window::calcScale() {
	int scale_x = 1280/width;
	int scale_y = 720/height;
	if(scale_x > scale_y) {
		scale = (float)scale_y;
	}
	else
		scale = (float)scale_x;
}

//Draws the map. Throws an error, if there is no window running.
void Window::draw_map() {
	
	if(!isRunning) {
		throw notRunningException();
	}
		
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (map[j][i] == -1) {
				sf::RectangleShape rec; // initialize a rectangle
				rec.setSize(sf::Vector2f(1,1)); // sets the size to one pixel
				rec.setPosition(i*scale,j*scale); // sets the position on the window
				rec.setFillColor(sf::Color::White); // set the color
				rec.setScale(1.0f, 1.0f); // initialize the scale
				rec.scale(scale, scale); // make the rectangle bigger for better visualization
				window.draw(rec); // send the rectangle to the window for drawing
													// it doesn't draw it yet: only when window.display() is called
			}
			else if(map[j][i] == 100) {
				sf::RectangleShape rec;
				rec.setSize(sf::Vector2f(1,1));
				rec.setPosition(i*scale,j*scale);
				rec.setFillColor(sf::Color::Red);
				rec.setScale(1.0f, 1.0f);
				rec.scale(scale, scale);
				window.draw(rec);
			}
		}
		// Draw a line to separate the map from the buttons
		sf::RectangleShape rec;
		rec.setSize(sf::Vector2f(1,1));
		rec.setPosition(width*scale,i*scale);
		rec.setFillColor(sf::Color::White);
		rec.setScale(1.0f, 1.0f);
		rec.scale(scale/2, scale);
		window.draw(rec);
	}
}

/*
 * Draws the routes . Throws an error if there is no window running.
*/
void Window::draw_routes() {
	
	if(!isRunning) {
		throw notRunningException();
	}
	
	for(unsigned int r = 0; r < routes.size(); r++) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if(routes[r].first[routes[r].second] == i*width + j) {
					sf::RectangleShape rec; // initalize a rectangle
					rec.setSize(sf::Vector2f(1,1)); // set the size to one pixel
					rec.setPosition(j*scale,i*scale); // set the position on the window
					rec.setFillColor(colors[r%colors.size()]); // set the color of the rectangle
																										 // color is got from colors-array (private variable of the class)
																										 // if there are more routes than rectangles, the colors will restart
																										 // from the first color
					rec.scale(scale, scale); // scale the rectangle for better visualization
					window.draw(rec); // send the rectangle to the window for drawing
													  // it doesn't draw it yet: only when window.display() is called
				}
			}
		}
		// Increase the step-variable by 1, so that next time the function is called, the next step will be displayed.
		if(routes[r].second < (int) routes[r].first.size() - 1 && !isitLearn()) 
			routes[r].second++;
	}
}

/*
 * Draws text with the given parametres.
 * String: the string to be drawn
 * Size: font size of the text
 * Position: the coordinates, where the text will be set
 * Color: the color of the text
 * 
 * Will throw an error if there is no window running.
*/
void Window::draw_text(std::string string, int size, std::pair<float, float> position, sf::Color color) {
	if(!isRunning) {
		throw notRunningException();
	}
	sf::Font font;
	if(!font.loadFromFile("arial.ttf")) // Load the font. The font file has to be in the same folder.
		throw fontLoadException();  // Throw an error if the font was not found.
	
	sf::Text text; // initalize the text
	text.setFont(font); // set the font
	text.setString(string); // set the string to be written
	text.setCharacterSize(size); // set the size
	text.setColor(color); // set the color
	text.setPosition(position.first, position.second); // set the position
	window.draw(text); // send the text to the window to draw. It will, however, not draw until window.display() is called.
	
}

/*
 * Draw frames, over a text for example, according to given parameters.
 * Size: the dimensions of the frame: width, height
 * Position: position on the window
 * Thickness: the thickness of the frame
 * Color: the color of the frame
 * 
 * Will throw an error if there is no window running
*/

void Window::draw_frame(std::pair<float, float> size, std::pair<float, float> position, int thickness, sf::Color color) {
	if(!isRunning) {
		throw notRunningException();
	}
	sf::RectangleShape rec; // initialize the rectangle
	rec.setSize(sf::Vector2f(size.first, size.second)); // set the size of the rectangle
	rec.setPosition(position.first, position.second); // set the position of the rectangle
	rec.setOutlineThickness(thickness); // set the thickess of the frame borders
	rec.setOutlineColor(color); // set the color of the frame
	rec.setFillColor(sf::Color::Transparent); // set the color of the inside of the rectangle to transparent,
																						// so that it is a frame, not a rectangle
	window.draw(rec); // send the text to the window to draw. It will, however, not draw until window.display() is called.
}


/*
 * Draw the reset button. It uses draw_text and draw_frame functions from this class.
 * The position and size have been eye-balled.
 * Throws an error if the window is not running.
*/
void Window::draw_reset() {
	if(!isRunning) {
		throw notRunningException();
	}
	draw_text("Reset", 30, std::make_pair(780, 600), sf::Color::Red);
	draw_frame(std::make_pair(100,50), std::make_pair(770,595), 5, sf::Color::Red);
}

/*
 * Draw the 'New Gen' button. It uses draw_text and draw_frame functions from this class.
 * The position and size have been eye-balled.
 * Throws an error if the window is not running.
*/
void Window::draw_newGenButton() {
	if(!isRunning) {
		throw notRunningException();
	}
	draw_text("New Gen", 27, std::make_pair(765, 400), sf::Color::Red);
	draw_frame(std::make_pair(120,50), std::make_pair(762, 393), 5, sf::Color::Red);
}

/*
 * Draw the 'Loading...' button on top of 'New Gen'-button. It uses draw_text and draw_frame functions from this class.
 * The position and size have been eye-balled.
 * Throws an error if the window is not running.
*/
void Window::draw_loading() {
	if(!isRunning) {
		throw notRunningException();
	}
	draw_text("Loading...", 26, std::make_pair(765, 400), sf::Color::Red);
	draw_frame(std::make_pair(120,50), std::make_pair(762, 393), 5, sf::Color::Red);
}

/*
 * Draw the 'Learn!' button. It uses draw_text and draw_frame functions from this class.
 * The position and size have been eye-balled.
 * Throws an error if the window is not running.
*/
void Window::draw_learn() {
	if(!isRunning) {
		throw notRunningException();
	}
	draw_text("Learn!", 30, std::make_pair(780, 200), sf::Color::Red);
	draw_frame(std::make_pair(110,50), std::make_pair(770,195), 5, sf::Color::Red);
}

/*
 * Draw the 'Loading' button on top of 'Learn!'-button. It uses draw_text and draw_frame functions from this class.
 * The position and size have been eye-balled.
 * Throws an error if the window is not running.
*/
void Window::draw_learn_loading() {
	if(!isRunning) {
		throw notRunningException();
	}
	draw_text("Loading", 25, std::make_pair(780, 205), sf::Color::Red);
	draw_frame(std::make_pair(110,50), std::make_pair(770,195), 5, sf::Color::Red);
}

/*
 * Draws the number of iterations calculated so far. 
 * Count: number of iterations so far.
 * Throws an error if the window is not running.
*/
void Window::draw_iterCount(int count) {
	if(!isRunning) {
		throw notRunningException();
	}
	std::string print = "Iteration\ncount: ";
	print += std::to_string(count);
	draw_text(print, 25, std::make_pair(770, 60), sf::Color::Red);
}


/*
 * Checks whether 'Reset'-button has been pressed.
 * sf::Event is an SFML union type variable. It will change every time there is an event,
 * like closing the window, moving mouse etc...
 * Returns: true if it has, false otherwise. 
*/
bool Window::resetIsPressed(sf::Event &event) {
	if(event.type == sf::Event::MouseButtonPressed) {
		if(event.mouseButton.x > 770 && event.mouseButton.x < 870 
		&& event.mouseButton.y > 595 && event.mouseButton.y < 645)
			return true;
	}
	return false;
}

/*
 * Checks whether 'New Gen'-button has been pressed.
 * sf::Event is an SFML union type variable. It will change every time there is an event,
 * like closing the window, moving mouse etc...
 * Returns: true if it has, false otherwise. 
*/
bool Window::newGenIsPressed(sf::Event &event) {
	if(event.type == sf::Event::MouseButtonPressed) {
		if(event.mouseButton.x > 762 && event.mouseButton.x < 882 
		&& event.mouseButton.y > 393 && event.mouseButton.y < 443)
			return true;
	}
	return false;
	
}

/*
 * Checks whether 'Learn!'-button has been pressed.
 * sf::Event is an SFML union type variable. It will change every time there is an event,
 * like closing the window, moving mouse etc...
 * Returns: true if it has, false otherwise. 
*/
bool Window::learnIsPressed(sf::Event &event) {
	if(event.type == sf::Event::MouseButtonPressed) {
		if(event.mouseButton.x > 770 && event.mouseButton.x < 880 
		&& event.mouseButton.y > 195 && event.mouseButton.y < 245)
			return true;
	}
	return false;
}

/*
 * Starts the window.
 * Name is the name of the window, displayed on top of the window
*/
void Window::start_window(const char* name) {
	window.create(sf::VideoMode(scale*width+200,scale*height), name); // sf::Videomode is an SFML variable,
																																		// takes the window width and height as a variable
																																		// They are multiplied by the scale for better visualization
	isRunning = true; // variable to help other functions know that the window is running
}

// Wheter the window is still open
bool Window::isOpened() {
	return window.isOpen();
}

// Whether the window is calculating e.g a new generation
bool Window::isitCalc() {
	return isCalculating;
}

// if the calculation has stopped, set the variable to false
void Window::isntCalc() {
	isCalculating = false;
}

// if calculation has begun, set the variable to true
void Window::isCalc() {
	isCalculating = true;
}

// Whether there is a learning process going, i.e the learning thread is running in the main function.
bool Window::isitLearn() {
	return isLearning;
}

// if learning has stopped, set the variable to false
void Window::isntLearn() {
	isLearning = false;
}

// if learning has begun, set the variable to true
void Window::isLearn() {
	isLearning = true;
}

// close the window
void Window::close() {
	window.close(); // SFML function
	isRunning = false;
}

// checks whether there has been an event. sf::Event is an SFML union variable
bool Window::checkEvent(sf::Event &event) {
	if(window.pollEvent(event)) { // an SFML function. 
																// Will be true, if there has been an event, e.g closing the window, mouse button pressed
		return true;
	}
	else
		return false;
}

// checks whether the window has been closed, i.e there has been an event sf::Event::Closed
bool Window::isClosed(sf::Event &event) {
	if(event.type == sf::Event::Closed) { 
		return true;
	}
	return false;
}

// clears the window, and flushes it with the given color
void Window::clear(sf::Color col) {
	window.clear(col); // an SFML function
}

// displays everything that has been drawn with window.draw()
void Window::display() {
	window.display(); // an SFML function
}

// Makes the window sleep for a short time, given as parameter. 'time' is in milliseconds (ms)
void Window::delay(int time) {
	sf::Time delay = sf::milliseconds(time); // SFML variables
	sf::sleep(delay); // SFML function
}

// Resets every route to start from its starting state
void Window::reset_routes() {
	for(unsigned int i = 0; i < routes.size(); i++) {
		routes[i].second = 0;
	}
}




