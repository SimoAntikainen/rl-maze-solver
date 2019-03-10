#include "Qlearner.hpp"
#include "png/png.hpp"
#include "configException.hpp"
#include <iostream>
#include <algorithm>
#include <thread>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "iterator"
#include "QMatrix.hpp"

/*
 * Thread function to calculate new iterations while visualizing previous routes.
 * Parameters: Qlearner q (learning process), Window w (visualization), Config c (reading the config file),
 * QMatrix Q (reads the png file)
 * bool &calc_thread is changed to true to tell main function that thread has finished
*/
void calc_new_q(Qlearner &q, Window &w, Config &c, QMatrix &Q, bool &calc_thread) {
	w.isCalc(); // tells the window that there is a calculating process going
	q.learnQfrom(Q.getStartState(), c.getNewIterCnt()); // learns some more iterations
	std::vector<int> route2 = q.walkQfromVector(Q.getStartState()); // saves the opitmal path to a vector
	w.addRoute(route2); // gives the vector to the window to plot
	w.isntCalc(); // tells the window that there no longer is a calculating process
  calc_thread = true; // tells the main function that the thread has finished
}

/*
 * Thread function to update the routes according to new Q-matrix. This can take a while, 
 * so better do it by threading, so that the window won't die.
 * Parameters: Qlearner q (learning process), Window w (visualization),
 * bool &learn_thread is changed to true to tell main function that thread has finished
*/
void learn_new_route(Qlearner &q, Window &w, bool &learn_thread) {
	w.isLearn(); // tells the window that there is a learning process going
	w.isCalc(); // tells the window that there is a calculating process going
	std::vector<std::pair<std::vector<int>, int>> temp_routes = w.getRoutes(); // saves the routes to a separate variable
	for(unsigned int r = 0; r < temp_routes.size(); r++) { // loops through each route
		temp_routes[r].first = q.walkQfromVector(temp_routes[r].first[temp_routes[r].second]); // updates the routes to use the 
		                                                                                       // latest Q-matrix values
		                                                                                       // sets the point where the "pixel" is at the moment
		                                                                                       // as the starting point
		temp_routes[r].second = 0; // sets the route to start from the beginning (start where it left)
	}
	w.initRoutes(temp_routes); // gives the new routes to the window
	w.isntCalc(); // calculating has stopped
	w.isntLearn(); // learning has stopped
	learn_thread = true; // tells the main function that the thread has finished
}

int main()
{

	try {
		Config c;
		Qlearner q = Qlearner();
		QMatrix Q=QMatrix();
		q.initParameter(c.getAlpha(),c.getGamma(), Q.getCountOfPixels() , Q.getFinishingPoint());
		q.initBlocked(Q.getBlocked());
		q.fillR(Q.getRMatrix());
		q.fillQ(Q.getQMatrix());
		if (c.getReadState()) {
		  Q = c.Q_read(Q.getHeight(),Q.getWidth());
			q.fillQ(Q.getQMatrix());
			if(c.getKeep()){
			  q.learnQfrom(Q.getStartState(),c.getIterCnt());
			}
		}
		else {
		  q.learnQfrom(Q.getStartState(),c.getIterCnt());
		}

		std::cout << "Chose " << Q.getStartState() << " as starting point." << std::endl;
		
		Window win(Q.getHeight(),Q.getWidth(), Q.getPixels()); // creates a window by the dimensions of the png-file
		std::vector<int> route = q.walkQfromVector(Q.getStartState()); // walks through the map with the current Q-matrix values
		                                                               // from the point defined in the config file
		win.addRoute(route); // gives the route to the graphics window
		

		sf::Event event; // SFML variable
		std::thread calc; // initializes calculating thread
		std::thread learn; // initializes learning thread
    bool calc_thread = false; // variable which tells, when to std::thread.join() the calculating thread
    bool learn_thread = false; // variable which tells, when to std::thread.join() the learning thread
    int iteration_count; // iteration count, will increase when new iterations are count
                         // the initial number depends on a few things
    if(!c.getKeep() && c.getReadState()) // if keep_learning = false in config and Q-matrix has been read from a file
		  iteration_count = c.getUsedIters(); // this is the number of iterations that have been used to get the loaded Q-matrix
		else if(c.getReadState()) // if Q-matrix has been read from a file
		  iteration_count = c.getIterCnt() + c.getUsedIters(); // same number as above, plus the number of iterations that were calculated
		                                                       // while opening the file (keep_learning = true)
		else // if Q-matrix is completely blank, this is the count after initial iterations
		  iteration_count = c.getIterCnt();
			
		win.start_window("Q-learner"); // opens the window

    // loops until the window is closed. More detailed explanations of the functions in Window.cpp
		while(win.isOpened()) { 
			win.clear(sf::Color::Black);
			win.draw_map();
			win.draw_routes();
			win.draw_reset();
			win.draw_iterCount(iteration_count);
			if(!win.isitLearn() && !win.isitCalc()) // whether the actual button is drawn, or Loading button
				win.draw_learn();                     // depends on if there is a calculation process going
			else
				win.draw_learn_loading();
			if(!win.isitCalc() && !win.isitCalc())
				win.draw_newGenButton();
			else
				win.draw_loading();
			win.display(); // only now will everything be drawn
			win.delay(100); // delay of 100ms


			while (win.checkEvent(event)) { // this loops checks for events: button presses and window closings
				if(win.isClosed(event)) {
					win.close();
				}
				else if(win.resetIsPressed(event)) {
					win.reset_routes();
				}
				else if(win.newGenIsPressed(event)) {
			    if(!win.isitCalc() && !win.isitLearn()) {
						// starts the calculating thread
					  calc = std::thread(calc_new_q, std::ref(q), std::ref(win), std::ref(c), std::ref(Q), std::ref(calc_thread));
          }
				}
				else if(win.learnIsPressed(event)) {
					if(!win.isitCalc() && !win.isitLearn())
					  // starts the learning thread
						learn = std::thread(learn_new_route, std::ref(q), std::ref(win), std::ref(learn_thread));
				}
			}
      
      // these two if statements will std::thread.join() the threads when they have finished
      if(!win.isitCalc() && calc_thread) {
				calc.join();
				iteration_count += c.getNewIterCnt();
        calc_thread = false;
      }
      if(!win.isitCalc() && learn_thread) {
				learn.join();
				learn_thread = false;
			}

		}
		// saves the Q-matrix after closing the window, if save_q = true in the config file
		if (c.getSaveState()) {
			c.Q_write(iteration_count,Q.getHeight(),Q.getWidth(), q.outQ());
		}
	}

	catch (invalidDoubleException& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	catch (configIOException& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	catch (readerIOException& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	catch (invalidHeightWidthException& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	catch (configException& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
}
