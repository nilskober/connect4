# connect4
This is a simple, command-line based implementation of the board game _Connect 4_ created in the context of the lecture _Advanced Programming in C_ at the University of Freiburg in the summer term of 2019.

### Rules
Alternately both players put a counter in one column by entering the number of the respective column.
The goal of the game is to get 4 counters in a row, either per line, column or diagonally.

### About the AI
The AI uses a very pramatic algorithm which is calculating all possible game states in the given depth.
It does not use any kind of alpha-beta pruning, thus its runtime is exponential.
On an average computer any search depth above 6 is expected to run noticable slow.

### Build
    make compile  # execute in the main directory of the repository

### Test
    make test  # execute in the main directory of the repository

### Usage
    -h, --help          Show manual.
    -a, --ai            Play against the computer.
    -i, --input FILE    Load game state from file.
    -d, -diff NUMBER    Set the difficulty of the AI (0,...,42).
                        Will have no effect if --ai is not activated.
                        Default value is 6.

### License
This work is published under MIT License. For details see the enclosed LICENSE file.
