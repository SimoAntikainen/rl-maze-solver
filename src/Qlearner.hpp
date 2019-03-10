#ifndef QLRN_HH
#define QLRN_HH

#include <vector>


class Qlearner {
  private:
    //The learning rate or step size determines to what extent the newly acquired information will override the old information
    double alpha;// = 0.1;
    /**
    The Gamma parameter has a range of 0 to 1 (0 <= Gamma > 1).  If Gamma is closer to zero, the agent
     will tend to consider only immediate rewards.  If Gamma is closer to one, the agent will consider
    future rewards with greater weight, willing to delay the reward.
    **/
    double gamma; // = 0.9;

    //amount of states in the system, from 1 to n
    int states;// = 6;
    //end state of the matrix from 0 to 1-n
    int endState;// = 5;


    std::vector<int> blocked;

    //R traverse matrix
    std::vector<std::vector<int>> R; /** = {{-1, -1, -1, -1, 0, -1},
      {-1, -1, -1, 0, -1, 100},
      {-1, -1, -1, 0, -1, -1},
      {-1, 0, 0, -1, 0, -1},
      {0, -1, -1, 0, -1, 100},
      {-1, 0, -1, -1, 0, 100}};**/



    // Q reward matrix
    std::vector<std::vector<double>> Q; /** = {{00.00,00.00,00.00,00.00,00.00,00.00},
                                          {00.00,00.00,00.00,00.00,00.00,00.00},
                                          {00.00,00.00,00.00,00.00,00.00,00.00},
                                          {00.00,00.00,00.00,00.00,00.00,00.00},
                                          {00.00,00.00,00.00,00.00,00.00,00.00},
                                          {00.00,00.00,00.00,00.00,00.00,00.00}
                                        };**/



    int traverseR(int atState);//learns every iteration
    std::vector<int> allPossibleActions(int fromState);
    double maxinumFutureQ(int St1State);


  public:
    Qlearner() {}
    ~Qlearner();
    Qlearner(const Qlearner &learnerIN);
    Qlearner & operator=(const Qlearner& learnerIn);
    void fillR( std::vector<std::vector<int> > inR);
    void fillQ(std::vector<std::vector<double>> inQ);
    void initParameter(double alphaIN,double gammaIN, int statesIN, int endStateIN){
      alpha = alphaIN;
      gamma = gammaIN;
      states = statesIN;
      endState = endStateIN;
    };
    void initBlocked(std::vector<int> blocksIN)  {
      blocked = blocksIN;
    };
    // init_ methods for individually initializing and changing variables
    void initAlpha(double alphaIN) {
      alpha = alphaIN;
    };
    void initGamma(double gammaIN) {
      gamma = gammaIN;
    };
    void initStates(int statesIN) {
      states = statesIN;
    };
    void initEndState(int endStateIN) {
      endState = endStateIN;
    };
    // _Out methods for outputting const variable references
    const double & alphaOut() const {
      return alpha;
    }
    const double &  gammaOut() const {
      return gamma;
    }
    const int & statesOut() const {
      return states;
    }
    const int & endStateOut() const {
      return endState;
    }
    const std::vector<int> & blockedOut() const {
      return blocked;
    }
    const std::vector<std::vector<int> > & outR() const;
    const std::vector<std::vector<double> > & outQ() const;

    void learnQ(int iterAmount); //learning iteration loop
    void learnQfrom(int startingPoint, int iterAmount);
    void printQ();
    void printR();
    void walkQ();
    void walkQfrom(int startingState);// state indexing starts at zero
    std::vector<int> walkQfromVector(int startingState);
    int nextStateFrom(int startingState);
    int bestQtransition(int fromState);
};

#endif
