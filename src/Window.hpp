#ifndef WIN_HH
#define WIN_HH
#include <vector>
#include "Qlearner.hpp"
#include "windowException.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window {
	private:
		int height; // Pixels in y-dimension of png picture
		int width; // Pixels in x-dimension of png picture
		float scale; // Scale, automatically calculated at calcScale();
		std::vector<std::vector<int>> map; // 2D-vector of the map, doesn't change
		std::vector<std::pair<std::vector<int>, int>> routes; // vector for routes that have been calculated after learning.
																													// first part of pair is the route(as a vector of states, not coordinates!)
																													// second part of pair is the count, how many steps have been already drawn
		sf::RenderWindow window; // the graphics window
		bool isRunning; // the state whether the window is running or not
		bool isCalculating; // whether there is a thread calculating new iterations
		bool isLearning; // whether the learning thread is on
		std::vector<sf::Color> colors; // vector of different colors that can be used in plotting (initialized in the constructor)
		
	//function explanations found in .cpp file	
	public:
		Window(int h, int w, std::vector<std::vector<int>> m, std::vector<std::pair<std::vector<int>, int>> r = std::vector<std::pair<std::vector<int>, int>>());
		~Window();
		Window(const Window &windowIN);
		Window &operator=(const Window &windowIN);
		void initHeight(int h) { height = h; }
		void initWidth(int w) { width = w; }
		void initMap(std::vector<std::vector<int>> m) { map = m; }
		void initRoutes(std::vector<std::pair<std::vector<int>, int>> r) { routes = r; }
		std::vector<std::pair<std::vector<int>, int>> getRoutes() { return routes; }
		void calcScale();
		void addRoute(std::vector<int> route);
		void draw_map();
		void draw_routes();
		void draw_text(std::string string, int size, std::pair<float, float> position, sf::Color color);
		void draw_frame(std::pair<float, float> size, std::pair<float, float> position, int thickness, sf::Color color);
		void draw_reset();
		void draw_newGenButton();
		void draw_loading();
		void draw_learn();
		void draw_learn_loading();
		void draw_iterCount(int count);
		void start_window(const char* name);
		bool isOpened();
		bool isitCalc();
		void isntCalc();
		void isCalc();
		bool isitLearn();
		void isLearn();
		void isntLearn();
		void close();
		bool checkEvent(sf::Event &event);
		bool isClosed(sf::Event &event);
		void clear(sf::Color);
		void display();
		void delay(int time);
		bool resetIsPressed(sf::Event &event);
		bool newGenIsPressed(sf::Event &event);
		bool learnIsPressed(sf::Event &event);
		void reset_routes();
};

#endif
