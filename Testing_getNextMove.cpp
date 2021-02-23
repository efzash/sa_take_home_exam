#include "Testing_getNextMove.h"
#include "Player_EF.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

Player_EF test_player; // create test player object from Player_EF - class (class in which Emil Faizrakhmanov's (EF) algorithm is implemented)

/* Write results into "test_results.txt" file that allocated near project folder
   // That how test result looks like in the file
        ____Test ¹1____
    3 | 0 | 0 | 3 | 
    0 | 0 | 0 | 2 | 
    0 | 0 | 0 | 1 | 
    0 | 0 | 0 | 3 | 
    Returned result: 13
    Should return: 13
    Number of successful tests: 1/1
    -------------------------------
    ____Test ¹2____
    3 | 0 | 0 | 3 |
    0 | 0 | 0 | 0 |
    0 | 0 | 0 | 0 |
    3 | 0 | 0 | 3 |
    Returned result: 2
    Should return: not (0, 1, 4, 13, 16)
    Number of successful tests: 2/2
    -------------------------------
*/
void writeResultToFile(int test_n, int field[], int pos, std::string should_return, int sucess_number)
{
    /*Crete object for working with files*/
    std::ofstream myfile;

    /* open .txt file and clear file content */
    if (test_n == 1) myfile.open("../test_results.txt", std::ofstream::trunc);
    else  myfile.open("../test_results.txt", std::ofstream::app);

    myfile << "____Test ¹" << test_n << "____\n";
    for (int i = 1; i < 17; i++)
    {
        myfile << field[i] << " | ";
        if (i % 4 == 0) myfile << "\n";
    }
    myfile << "Returned result: " << pos << "\n";
    myfile << "Should return: " << should_return << "\n";
    myfile << "Number of successful tests: " << sucess_number << "/" << test_n << "\n";
    myfile << "-------------------------------\n";

    myfile.close();
}

/*
* Test cases running function*/
void TestModule::runTest()
{
    // Array for test field
    // Field size is the same as the game board from cpuvscpumodel.h
    int test_field_arr[17];

    // Count the success tests
    int succes_count = 0;

    // Crete object for working with files
    std::ofstream myfile;
    // Create array as std::vector<int> to change it during the test.
    std::vector<int> test_field;

    /*------------------------
    *   TESTING BLOCK
    * All code lines in the block are the same except data*/
    /*  
    * TEST #1
    * Test case to check if our player algorithm will choose corner on the 4th move.
    * Should return "13" because it's 4th move and the cell is available.*/
     test_field = { 0,
        3, 0, 0, 3,
        0, 0, 0, 2,
        0, 0, 0, 1,
        0, 0, 0, 3
    };
    std::copy(test_field.begin(), test_field.end(), test_field_arr); // convert from <vector>int type to int array for getNexMove function
    returned_pos = test_player.getNextMove(test_field_arr); // get position from getNextMove function for test field
    if (returned_pos == 13) succes_count++; // count correct results 
    writeResultToFile(1, test_field_arr, returned_pos, "13", succes_count); // write test resultss to test_results.txt

    /*  
    * TEST #2
    * Test case to check if there is no available corners and its the first move.
    * Should return any position except corners because.*/
    test_field = { 0,
        3, 0, 0, 3,
        0, 0, 0, 0,
        0, 0, 0, 0,
        3, 0, 0, 3
    };
    std::copy(test_field.begin(), test_field.end(), test_field_arr);
    returned_pos = test_player.getNextMove(test_field_arr);
    if (returned_pos != 0 && returned_pos != 1 && returned_pos != 4 && returned_pos != 13 && returned_pos != 16) succes_count++;
    writeResultToFile(2, test_field_arr, returned_pos, "not (0, 1, 4, 13, 16)", succes_count);

    /*
    * TEST #3
    * Test case to check if algorithm will block or choose win position on the third row.
    * Should return any position except corners because.*/
    test_field = { 0,
        0, 1, 2, 2,
        0, 2, 3, 0,
        2, 0, 2, 2,
        1, 1, 0, 1
    };
    std::copy(test_field.begin(), test_field.end(), test_field_arr);

    returned_pos = test_player.getNextMove(test_field_arr); // get position from getNextMove function for test field
    if (returned_pos == 10) succes_count++;
    writeResultToFile(3, test_field_arr, returned_pos, "10", succes_count);

    /*
    * TEST #4
    * Test case to check if there is no available cells.
    * Should return -1 because no available moves.*/
    test_field = { 0,
       3, 1, 1, 3,
       1, 2, 2, 1,
       2, 1, 1, 2,
       3, 2, 2, 3
    };
    std::copy(test_field.begin(), test_field.end(), test_field_arr);
    returned_pos = test_player.getNextMove(test_field_arr); // get position from getNextMove function for test field
    if (returned_pos == -1) succes_count++;
    writeResultToFile(4, test_field_arr, returned_pos, "-1", succes_count);

    /*
    * TEST #5
    * Test case to check if algorithm can detect win or block position on the 16. 
    * Its just another check to make sure, that it works fine.
    * Should return 16.*/
    test_field = { 0,
       2, 0, 0, 3,
       0, 2, 1, 0,
       1, 0, 2, 0,
       3, 0, 1, 0
    };
    std::copy(test_field.begin(), test_field.end(), test_field_arr);

    returned_pos = test_player.getNextMove(test_field_arr); // get position from getNextMove function for test field
    if (returned_pos == 16) succes_count++;
    writeResultToFile(5, test_field_arr, returned_pos, "16", succes_count);

    /*
    * TEST #6
    * Test case to check if there is an empty array in the input and with a smaller dimension.
    * Should return -1.*/
    int empty_field[5]; // try to transer empty array with 5 elements

    returned_pos = test_player.getNextMove(empty_field); // get position from getNextMove function for test field
    if (returned_pos == -1) succes_count++;
    writeResultToFile(6, empty_field, returned_pos, "-1", succes_count);

    /*
    * TEST #7
    * Test case to check if alrogithm will block or win in the 5th position.
    * Should return 5 because its ending situation.*/
    test_field = { 0,
       1, 2, 2, 1,
       0, 1, 1, 1,
       0, 0, 2, 1,
       2, 1, 2, 2
    };
    std::copy(test_field.begin(), test_field.end(), test_field_arr);

    returned_pos = test_player.getNextMove(test_field_arr); // get position from getNextMove function for test field
    if (returned_pos == 5) succes_count++;
    writeResultToFile(7, test_field_arr, returned_pos, "5", succes_count);

    /*
    * TEST #8
    * All cells are blocked. Strange situation, but we need to check if the return will be -1
    * Should return -1 because no available cells*/
    test_field = { 0,
        3, 3, 3, 3,
        3, 3, 3, 3,
        3, 3, 3, 3,
        3, 3, 3, 3
    };
    std::copy(test_field.begin(), test_field.end(), test_field_arr);
    returned_pos = test_player.getNextMove(test_field_arr);
    if (returned_pos == -1) succes_count++;
    writeResultToFile(8, test_field_arr, returned_pos, "-1", succes_count);

    /*
    * TEST #9
    * Test case to check if there is there is a choice: win with the current move or block the opponent's move
    * Should return 16, but winnig or losing will depend on whom which line is filled, since the algorithm follows
    * the order specified in the Player_EF.cpp in the win_pos array. This decision was made because the players can switch positions on any move.
    * The principle is either all or nothing (win or draw).*/
    test_field = { 0,
       0, 2, 2, 1,
       2, 2, 1, 1,
       1, 2, 2, 1,
       3, 0, 1, 0
    };
    std::copy(test_field.begin(), test_field.end(), test_field_arr);

    returned_pos = test_player.getNextMove(test_field_arr); // get position from getNextMove function for test field
    if (returned_pos == 16) succes_count++;
    writeResultToFile(9, test_field_arr, returned_pos, "16", succes_count);

    /* END TESTING BLOCK*/
}