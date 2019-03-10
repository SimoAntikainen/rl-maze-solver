# Q-learning-8 build instructions
From command line navigate to q-learner-8 ‘/src’ folder. From there type into command line ‘make’. This will create an executable called 'learner'. To run this, type './learner'.

To delete .o-files type ‘make clean’.

NOTE: this requires the 2.3.2 SFML-library, which is installed in the default install directory!

## Q-learning-8 build test
From command line navigate to q-learner-8 ‘/test’ folder. From there type into command line ‘make run’. To delete .o-files type ‘make clean’.

For Valgrind test navigate to q-learner-8 ‘/src’ folder. From there type into command line  ‘make valgrind’.

## Manual:

First, it takes a while to open the window, as a pre-defined number of calculations are done already. You can follow the progress in the command line. 

Once the window opens, you can see the calculated optimal route after the initial calculations from a pre-defined starting point. 

You can close the window by pressing the 'x' button on top-left corner (the default button for closing a window).


## Descriptions for different buttons:

'Reset': This resets all generations on the window to start from their starting points. No learning or calculations is included in this function.

'New Gen': This will calculate a pre-defined number of new iterations. The calculation process can be seen in command line. Once the calculations are finished, a new generation will appear on the screen.

'Learn': This will give the latest Q-matrix to all generations that are currently running on the screen, i.e haven't reached the goal state yet. The calculations might take a while, so the visualization is stopped meanwhile. Note, that this will set the generations' starting point to the point where 'Learn' was pressed: if you press 'Reset' afterwards, the routes will reset from this point, not the original starting point!

## Config file

There are many options, which haven't been implemented in the graphics window, but have been implemented in the 'config.txt' file. Here are the descriptions for each variable:

num_iterations=10 : The number of iterations to be calculated *before* the window is opened

alpha=0.1 : Qlearning variable. "The learning rate, set between 0 and 1. Setting it to 0 means that the Q-values are never updated, hence nothing is learned. Setting a high value such as 0.9 means that learning can occur quickly"

gamma=0.9 : Qlearning variable. "Discount factor, also set between 0 and 1. This models the fact that future rewards are worth less than immediate rewards. Mathematically, the discount factor needs to be set less than 0 for the algorithm to converge."

png_filename=png/pics/50x50_2.png : The picture to be used as the map. There are many different maps in the 'pics' folder (/src/png/pics).

read_q=false : true, if you want to load a previous Q-matrix from a file. false, if not

q_readfile=qmatrix.txt : if read_q=true, the file which the Q-matrix is loaded from

save_q=false : true, if you want to save the learning process when you close the window. false, if not

q_filename=qmatrix.txt : if save_q = true, the file which the Q-matrix will be saved in

set_start=true : true, if you want to set your own starting point. If this is false, the starting point will be random

start_state=0 : if set_start = true, then this will be the starting point. Note, that this is a single value, not coordinates. The values start from the top-left corner and increase horizontally to the right.

keep_learning=false : if read_q = true, and this is false, then, when opening the program, the initial calculations are skipped

num_new_iterations=50 : when 'New Gen'-button is pressed, this number determines the number of iterations to be calculated.

Source for alpha and gamma: http://www.cse.unsw.edu.au/~cs9417ml/RL1/algorithms.html


