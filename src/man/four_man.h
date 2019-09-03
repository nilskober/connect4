// Copyright 2019 Nils Kober
// Author: Nils Kober <nils.kober@students.uni-freiburg.de>
// Published under MIT License

#ifndef SRC_MAN_FOUR_MAN_H_
#define SRC_MAN_FOUR_MAN_H_

const char manual[] = "\n********** Connect 4 Manual **********\n\n"
    "This is a simple implementation of the game connect 4.\n"
    "Alternately both players put a counter in one column.\n"
    "The goal of the game is to get 4 counters in a row, "
    "either per line, column or diagonally.\n\n"
    "Command line options: \n"
    "-h, --help \t\tShow manual.\n"
    "-a, --ai \t\tPlay against the computer.\n"
    "-i, --input FILE \tLoad game state from file.\n"
    "-d, -diff NUMBER \tSet the difficulty of the AI (search depth \n"
    "\t\t\tfrom 1 to 42, anything from 7 will be slow).\n"
    "\t\t\tWill have no effect if --ai is not activated.\n"
    "\t\t\tDefault value is 6.\n\n";


#endif  // SRC_MAN_FOUR_MAN_H_
