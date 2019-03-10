#include <exception>
//Error exclusivively for the class Qlearner.cpp
class qlearnerException : public std::exception {

//should be only thrown when unspesified exception happends
public:
  virtual const char* what() const throw() {
    return "Unspesified qlearner exception.";
  }

};
/**Exception meant for cases when Q-learner.cpp has been accidentally USER
inputted with values not in the acceptable range**/
class qlearnerOutOfBoundsException : public qlearnerException {


public:
  virtual const char* what() const throw() {
    return "Qlearner value out of bounds";
  }




};
