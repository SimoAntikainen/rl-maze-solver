# Q-learning Maze solver 

This C++ project visualizes iterative maze solving using the Q-learning reinforcement learning technique.

## Building the Project

1. Navigate to the `/src` folder in the q-learner-8 directory.
2. Run `make` to create the executable called 'learner'.
3. Execute the program by running `./learner`.
4. To clean up object files, use `make clean`.

**Note**: This project requires SFML library version 2.3.2 installed in the default directory.

## Running Tests

### Unit Tests
1. Navigate to the `/test` folder in the q-learner-8 directory.
2. Run `make run` to execute the tests.
3. Use `make clean` to remove object files.

### Valgrind Test
1. Navigate to the `/src` folder.
2. Run `make valgrind` to perform the Valgrind test.

## User Manual

1. Upon launching, the program performs pre-defined calculations. Progress can be monitored in the command line.
2. Once the window opens, it displays the calculated optimal route from a pre-defined starting point.
3. Close the window using the 'x' button in the top-left corner.

### Button Functionalities

- **Reset**: Resets all generations to their starting points without additional learning or calculations.
- **New Gen**: Calculates a pre-defined number of new iterations. Progress is visible in the command line.
- **Learn**: This will give the latest Q-matrix to all generations that are currently running on the screen, i.e haven't reached the goal state yet. The calculations might take a while, so the visualization is stopped meanwhile. Note, that this will set the generations' starting point to the point where 'Learn' was pressed: if you press 'Reset' afterwards, the routes will reset from this point, not the original starting point!


## Configuration

The `config.txt` file allows customization of various parameters:

| Parameter | Description |
|-----------|-------------|
| `num_iterations=10` | Number of iterations calculated before window opening |
| `alpha=0.1` | Learning rate (0-1). Setting it to 0 means that the Q-values are never updated, hence nothing is learned. Setting a high value such as 0.9 means that learning can occur quickly" |
| `gamma=0.9` | Discount factor (0-1). This models the fact that future rewards are worth less than immediate rewards. Mathematically, the discount factor needs to be set less than 0 for the algorithm to converge |
| `png_filename=png/pics/50x50_2.png` | Map file path.  There are many different maps in the 'pics' folder (/src/png/pics) |
| `read_q=false` | Enable/disable loading previous Q-matrix |
| `q_readfile=qmatrix.txt` | File to load Q-matrix from |
| `save_q=false` | Enable/disable saving Q-matrix on exit |
| `q_filename=qmatrix.txt` | File to save Q-matrix to |
| `set_start=true` | Enable/disable custom starting point |
| `start_state=0` | Starting point value (if `set_start` is true). Note, that this is a single value, not coordinates. The values start from the top-left corner and increase horizontally to the right. |
| `keep_learning=false` | Continue learning if loading previous Q-matrix |
| `num_new_iterations=50` | Iterations calculated when "New Gen" is pressed |

For detailed explanations of `alpha` and `gamma`, refer to: [Reinforcement Learning Algorithms](http://www.cse.unsw.edu.au/~cs9417ml/RL1/algorithms.html)
