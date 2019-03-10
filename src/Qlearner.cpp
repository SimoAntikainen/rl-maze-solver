#include "Qlearner.hpp"
#include "qlearnerException.hpp"
#include "string"
#include <iostream>
#include <algorithm>

Qlearner::~Qlearner() {

}

//Copy constructor for Qlearner
Qlearner::Qlearner(const Qlearner &learnerIN) {
  R = learnerIN.R;
  Q = learnerIN.Q;
  alpha = learnerIN.alpha;
  gamma = learnerIN.gamma;
  states = learnerIN.states;
  endState = learnerIN.endState;
  blocked = learnerIN.blocked;
}
//Copy assignment for Qlearner
Qlearner& Qlearner::operator=(const Qlearner & learnerIN) {
  R = learnerIN.R;
  Q = learnerIN.Q;
  alpha = learnerIN.alpha;
  gamma = learnerIN.gamma;
  states = learnerIN.states;
  endState = learnerIN.endState;
  blocked = learnerIN.blocked;
  return *this;
}

//fills the R matrix with passed values
void Qlearner::fillR( std::vector<std::vector<int> > inR) {
  R = inR;

}
//fills the Q matrix with passed values
void Qlearner::fillQ(std::vector<std::vector<double>> inQ) {
  Q = inQ;

}
//return a reference to R matrix
const std::vector<std::vector<int> > & Qlearner::outR() const {
  return R;

}
//return a reference to Q matrix
const std::vector<std::vector<double> > & Qlearner::outQ() const {
  return Q;

}

void Qlearner::learnQfrom(int startingPoint, int iterAmount) {
  //check for unacceptable startingPoint and iterAmount and throw error
  if(startingPoint < 0 || startingPoint >= states || iterAmount <= 0) {
    throw qlearnerOutOfBoundsException();
  }

  //Q learning algorith from http://mnemstudio.org/path-finding-q-learning-tutorial.htm
  for(int i=0;i<iterAmount;i++) {
    //Select a specified startingPoint
    int atState = startingPoint;
    //Do While the goal state hasn't been reached. or the the state is a block
    //traverse the matrix until endState is reached
    while (!(atState == endState) && !(std::find(blocked.begin(), blocked.end(), atState) != blocked.end()) ) {
        atState = traverseR(atState);
        //std::cout << "at iteration end" << i << std::endl;
    }
    std::cout << "At iteration end " << i << std::endl;
  }
}


void Qlearner::learnQ(int iterAmount) {
  //check for unacceptable iterAmount and throw error
  if(iterAmount <= 0) {
    throw qlearnerOutOfBoundsException();
  }

  //Q learning algorith from http://mnemstudio.org/path-finding-q-learning-tutorial.htm
  for(int i=0;i<iterAmount;i++) {
    //Select a random initial state.
    int atState = rand() % states;
    //Do While the goal state hasn't been reached. or the the state is a block
    //traverse the matrix until endState is reached
    while (!(atState == endState) && !(std::find(blocked.begin(), blocked.end(), atState) != blocked.end()) ) {
        atState = traverseR(atState);
        //std::cout << "at iteration end" << i << std::endl;
    }
    std::cout << "at iteration end" << i << std::endl;
  }
}

int Qlearner::traverseR(int atState) {
  //Select one among all possible actions for the current state (by random).

  std::vector<int> allPosAct = allPossibleActions(atState);
  int index = rand() % allPosAct.size();
  //Using this possible action, consider going to the next state.
  int nextState = allPosAct[index];
  //value iteration algorithm http://www.cse.unsw.edu.au/~cs9417ml/RL1/algorithms.html
  //Get maximum Q value for this next state based on all possible actions.
  //Q(s,a) <-- Q(s,a) + alpha * (R(s,a) + gamma * MaxQ(s', a') – Q(s,a))
  Q[atState][nextState] = (Q[atState][nextState] + alpha * (R[atState][nextState] +
      gamma * maxinumFutureQ(nextState) - Q[atState][nextState]));
  return nextState;
}

std::vector<int> Qlearner::allPossibleActions(int fromState){
  //return a list of all possbile future states (linearly) from a current state.
  std::vector<int> possibleActions;
  for (int i = 0; i < states; i++) {
    if (R[fromState][i] != -1) {
      possibleActions.push_back(i);
    }
  }
  return possibleActions;
}


double Qlearner::maxinumFutureQ(int St1State){
  //return the largest future Q value possible to get from next state s(t+1)
  std::vector<int> allPossibleAct = allPossibleActions(St1State);
  //initialize the max value by setting a floor value
  double maxFutureQ = 00.00001;
  for (int possibleAction : allPossibleAct) {
    double posBiggerQ = Q[St1State][possibleAction];
    if (posBiggerQ  > maxFutureQ ) {
                maxFutureQ  = posBiggerQ;
    }
  }
  return maxFutureQ;
}

void Qlearner::printQ() {
  int yDimQ = Q.size(); //removes casting warning from unsigned int to int
  int xDimQ = Q[0].size(); //removes casting warning from unsigned int to int

  std::cout << "Printing Q: " << std::endl;
  for(int i=0;i<yDimQ;i++) {
      std::cout << "[ ";
    for(int j= 0; j<xDimQ;j++) {
      std::cout << "" << Q[i][j] << " ";
    }
    std::cout << "]" << std::endl;
  }

}

void Qlearner::printR() {
  int yDimR = R.size(); //removes casting warning from unsigned int to int
  int xDimR = R[0].size(); //removes casting warning from unsigned int to int
  std::cout << "Printing R: " << std::endl;


  for(int i=0;i<yDimR;i++) {
      std::cout << "[ ";
    for(int j= 0; j<xDimR;j++) {
      std::cout << "" << R[i][j] << " ";
    }
    std::cout << "]" << std::endl;
  }
}

//Prints the every optimal nextState from current state
//if the state is an obstacle or the endState. state -> state is returned
void Qlearner::walkQ() {
  std::cout << "Printing every optimal next state: " << std::endl;
  for (int i = 0; i < states; i++) {
    std::cout << "Transition: " << i << " -> " << bestQtransition(i) << std::endl;
  }

}

//Prints the every optimal nextState from a startingState
void Qlearner::walkQfrom(int startingState) {
  //check for unacceptable startingState and throw error.
  if(startingState< 0 || startingState >= states) {
    throw qlearnerOutOfBoundsException();
  }

  std::cout << "Starting from: " << startingState << std::endl;
  //check if the startingState is an obstacle and terminate
  if((std::find(blocked.begin(), blocked.end(), startingState) != blocked.end())) {
    if(startingState != endState) {
      std::cout << "Starting state: " << startingState << " is an obstacle cannot proceed!" << std::endl;
      return;
    }
  }
  int atState = startingState;
  while(atState != endState) {
    std::cout << "Transition: " << atState;
    atState = bestQtransition(atState);
    std::cout << " -> " << atState << std::endl;
  }
  //finally print the last endState
  std::cout << "End state: " << atState << " reached." << std::endl;


}


std::vector<int> Qlearner::walkQfromVector(int startingState) {
  //check for unacceptable startingState and throw error.
  if(startingState< 0 || startingState >= states) {
    throw qlearnerOutOfBoundsException();
  }
  std::vector<int> routeStates;
  routeStates.push_back(startingState);
  if((std::find(blocked.begin(), blocked.end(), startingState) != blocked.end())) {
    if(startingState != endState) {
      routeStates.push_back(startingState);
      return routeStates;
    }
  }
  int atState = startingState;
  while(atState != endState) {
    atState = bestQtransition(atState);
    routeStates.push_back(atState);
  }
  //finally print the last endState
  routeStates.push_back(atState);
  return routeStates;

}











//returns the best possible next state
int Qlearner::nextStateFrom(int startingState) {
  //check for unacceptable startingState and throw error.
  if(startingState< 0 || startingState >= states) {
    throw qlearnerOutOfBoundsException();
  }
  std::cout << "Next state from: " << startingState << std::endl;
  //check if the startingState is an obstacle and terminate
  if((std::find(blocked.begin(), blocked.end(), startingState) != blocked.end())) {
    if(startingState != endState) {
      std::cout << "Starting state: " << startingState << " is an obstacle cannot proceed!" << std::endl;
      //return -1 when the starting state is an obstacle
      return -1;
    }
  }

  int atState = startingState;
  if(atState != endState) {
    return bestQtransition(atState);
  } else {
    //best next State from endState is the endstate
    return atState;
  }
}


//Helper method. picks the best nextState from a state.
int Qlearner::bestQtransition(int fromState) {
  //return the largest future Q value possible to get from next state s(t+1)
  std::vector<int> allPossibleAct = allPossibleActions(fromState);
  //initialize the max value by setting a floor value
  //if there does not exist a better state: because the endState is reached or
  //the fromState is an obstacle fromState is returned
  double maxFutureQ = 00.00001;
  int nextState = fromState;

  for (int possibleAction : allPossibleAct) {
    double posBiggerQ = Q[fromState][possibleAction];
    if (posBiggerQ > maxFutureQ ) {
      maxFutureQ = posBiggerQ;
      nextState = possibleAction;
    }
  }
  if(nextState == fromState) {
		int index = rand() % allPossibleAct.size();
		nextState = allPossibleAct[index];
	}
  return nextState;
}
