//=================================================================
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*     D i a m o n d   S e a r c h
Student Name: Janah Abu Hassan
Date: 10/03/2022

ECE 2035 Project 1-1

This is the only file that should be modified for the C implementation
of Project 1.

Do not include any additional libraries.
------------------------------------------
This program finds the lowest cost 5-step path out of a diamond of weighted 
squares. */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

/* Example from Proiect description (illustrated in Fig.1):
int Array[121] = {
    10000, 10000, 10000, 10000, 10000, -99,  10000, 10000, 10000, 10000, 10000,
    10000, 10000, 10000, 10000,   -49, -37,  83, 10000, 10000, 10000, 10000,
    10000, 10000, 10000,   -64,    19,  67, -82,    -2, 10000, 10000, 10000,
    10000, 10000,   -30,   -37,    64, -68,  92,    40,     2, 10000, 10000,
    10000,    27,   -70,    52,    79, -77, -31,   -41,   -77,   -81, 10000,
        80,   -73,    -8,   -59,    53,   0, -47,    46,   -32,    98,   -98,
    10000,    13,   -99,   -47,   -60, -14, -45,    80,    15,    69, 10000,
    10000, 10000,    -9,     8,   -88,  69,  54,    12,    53, 10000, 10000,
    10000, 10000, 10000,   -21,     3, -61, -43,    29, 10000, 10000, 10000,
    10000, 10000, 10000, 10000,    45, -34, -85, 10000, 10000, 10000, 10000,
    10000, 10000, 10000, 10000, 10000,  59, 10000, 10000, 10000, 10000, 10000 };

    DO NOT use this to provide a test case to your program.
    Instead, provide the test case as a command-line argument in the form of
    a test file (e.g., test-307.txt).  The code below uses Load_Mem to read the
    values in a given test file into the local Array in main.
    */

    #define ArraySize 121

    int main(int argc, char *argv[]) {
    int Array[ArraySize];
    int Length, MinCost = 10000;
    int  Load_Mem(char *, int *);

    if (argc != 2) {
        printf("usage: P1-1 valuefile\n");
        exit(1);
    }
    Length = Load_Mem(argv[1], Array);
    if (Length != ArraySize) {
        printf("valuefile does not contain valid data.\n");
        exit(1);
    }

    /* Your diamond search code goes here */
    int moves = 5;
    int index = 60;
    MinCost = MinCost - 10000;
    int MinCostArr[112] = {}; // of form {index 5, index 55, index 65, index 115, level 1 box 1 path 1, level 1 box 1 path 2, level 1 box 1 path 3, level 1 box 1 path 4, level 1 box 2 path 1, level 1 box 2 path 2, level 2 box 1 path 3, level 1 box 2 path 4...}
    int indexofArr = 0;

    int sumUp = 0;
    int sumDown = 0;
    int sumLeft = 0;
    int sumRight = 0;
    int sumUpLeft = 0;
    int sumUpRight = 0;
    int sumDownLeft = 0;
    int sumDownRight = 0;
    int minim = 0;
    // Start from the green box and check every single test case that is 5 moves -> go up 5, go up 4, then check left and right, go up 3, then check 2 right and 2 left
    // then go 3 up and then check 1 right and 1 up, then check 1 left and 1 up. Basically check every single possibility

    // checking for corner boxes (index 5, 55, 65, and 115)
    for (int i = 1; i < 6; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
        sumDown = sumDown + Array[index + (11 * i)];
        sumLeft = sumLeft + Array[index - (1 * i)];
        sumRight = sumRight + Array[index + (1 * i)];
    }
    MinCostArr[indexofArr] = sumUp;
    indexofArr++;
    MinCostArr[indexofArr] = sumLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumRight;
    indexofArr++;
    MinCostArr[indexofArr] = sumDown;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    index = 60;

    // Checking all paths for index 15 and 17
    // calculate sum of boxes going up to level 1 (two paths to index 15 and 17)
    for (int i = 1; i < 5; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
    }
    index = 16;

    //checks boxes on the left and right
    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    MinCostArr[indexofArr] = sumUp + sumLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumUp + sumRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    index = 60;

    // calculate sum of boxes going up to level 2 (the other two paths for index 15 and 17)
    for (int i = 1; i < 4; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
    }
    index = 27;

    // checks boxes on the left and right (goes 1 step left, 1 step up and 1 step right, 1 step up)
    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    sumUpLeft += Array[(index - 1) - 11];
    sumUpRight += Array[(index + 1) - 11];
    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;


    // calculate sum of boxes going up to level 3
    for (int i = 1; i < 3; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
        moves--;
    }
    index = 38;

    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    moves--;
    for (int i = 1; i < moves + 1; i++) {
        sumUpLeft += Array[(index - 1) - (11 * i)];
        sumUpRight += Array[(index + 1) - (11 * i)];
    }
    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    // calculate sum of boxes going up to level 4
    for (int i = 1; i < 2; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
        moves--;
    }
    index = 49;

    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    moves--;
    for (int i = 1; i < moves + 1; i++) {
        sumUpLeft += Array[(index - 1) - (11 * i)];
        sumUpRight += Array[(index + 1) - (11 * i)];
    }
    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    // calculate sum of boxes starting from level 5
    index = 60;

    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    moves--;
    for (int i = 1; i < moves + 1; i++) {
        sumUpLeft += Array[(index - 1) - (11 * i)];
        sumUpRight += Array[(index + 1) - (11 * i)];
    }
    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    // Checking all paths for index 25 and 29
    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;


    // goes up to level 2 (to check for two paths to get to index 25 and 29)
    for (int i = 1; i < 4; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
        moves--;
    }
    index = 27;


    // checks boxes on the left and right
    for (int i = 1; i < moves + 1; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
    }

    MinCostArr[indexofArr] = sumUp + sumLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumUp + sumRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    // check for other two paths to get to index 25 and 29 (go up to level 3, and then go left, up, left OR level 3, left by 2, then up, and same for right)
    for (int i = 1; i < 3; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
        moves--;
    }
    index = 38;

    sumLeft += Array[index - 1];
    sumLeft += Array[index - 2];
    sumRight += Array[index + 1];
    sumRight += Array[index + 2];
    moves--;

    sumUpLeft += Array[index - 2 - 11];
    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumUpLeft += Array[index - 1 - 11];
    sumLeft += Array[index - 1 - 11 - 1];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumUpRight += Array[index + 2 - 11];
    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumUpRight += Array[index + 1 - 11];
    sumRight += Array[index + 1 - 11 + 1];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    // checks paths from going up to level 4 to index 25 and 29
    for (int i = 1; i < 2; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
        moves--;
    }
    index = 49;
    int tempMoves = moves;

    for (int i = 1; i < tempMoves - 1; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    tempMoves = moves;

    for (int i = 1; i < tempMoves + 1; i++) {
        sumUpLeft += Array[index - 2 - (11 * i)];
        sumUpRight += Array[index + 2 - (11 * i)];
        moves--;
    }

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumUpLeft += Array[index - 1 - 11];
    sumLeft += Array[index - 1 - 11 - 1];
    sumUpLeft += Array[index - 1 - 11 - 1 - 11];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumUpRight += Array[index + 1 - 11];
    sumRight += Array[index + 1 - 11 + 1];
    sumUpRight += Array[index + 1 - 11 + 1 - 11];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumUpLeft += Array[index - 1 - 11];
    sumUpLeft += Array[index - 1 - 22];
    sumLeft += Array[index - 1 - 22 - 1];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumUpRight += Array[index + 1 - 11];
    sumUpRight += Array[index + 1 - 22];
    sumRight += Array[index + 1 - 22 + 1];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;
    tempMoves = 0;

    // checks paths from level 5 going left and right to index 25 and 29
    index = 60;

    for (int i = 1; i < 3; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    tempMoves = moves;

    for (int i = 1; i < tempMoves + 1; i++) {
        sumUpLeft += Array[index - 2 - (11 * i)];
        sumUpRight += Array[index + 2 - (11 * i)];
        moves--;
    }

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumUpLeft += Array[index - 1 - 11];
    sumLeft += Array[index - 1 - 11 - 1];
    sumUpLeft += Array[index - 1 - 11 - 1 - 11];
    sumUpLeft += Array[index - 1 - 11 - 1 - 22];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumUpRight += Array[index + 1 - 11];
    sumRight += Array[index + 1 - 11 + 1];
    sumUpRight += Array[index + 1 - 11 + 1 - 11];
    sumUpRight += Array[index + 1 - 11 + 1 - 22];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumUpLeft += Array[index - 1 - 11];
    sumUpLeft += Array[index - 1 - 22];
    sumLeft += Array[index - 1 - 22 - 1];
    sumUpLeft += Array[index - 1 - 22 - 1 - 11];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumUpRight += Array[index + 1 - 11];
    sumUpRight += Array[index + 1 - 22];
    sumRight += Array[index + 1 - 22 + 1];
    sumUpRight += Array[index + 1 - 22 + 1 - 11];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    sumRight = 0;
    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    for (int i = 1; i < 4; i++) {
        sumUpLeft += Array[index - 1 - (11 * i)];
        sumUpRight += Array[index + 1 - (11 * i)];
    }

    sumLeft += Array[index - 1 - 33 - 1];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight += Array[index + 1 - 33 + 1];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    // Checking all paths for index 35 and 41
    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;


    // goes up to level 3 (to check for two paths to get to index 35 and 41)
    for (int i = 1; i < 3; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
        moves--;
    }
    index = 38;


    // checks boxes on the left and right
    for (int i = 1; i < moves + 1; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
    }

    MinCostArr[indexofArr] = sumUp + sumLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumUp + sumRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;
    tempMoves = 0;

    // checks paths from going up to level 4 to index 35 and 41
    for (int i = 1; i < 2; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
        moves--;
    }
    index = 49;

    tempMoves = moves;

    for (int i = 1; i < tempMoves; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    sumUpLeft += Array[index - (1 * 3) - 11];
    sumUpRight += Array[index + (1 * 3) - 11];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumUpLeft += Array[index - 1 - 11];
    sumLeft += Array[index - 1 - 11 - 1];
    sumLeft += Array[index - 1 - 11 - 1 - 1];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumUpRight += Array[index + 1 - 11];
    sumRight += Array[index + 1 - 11 + 1];
    sumRight += Array[index + 1 - 11 + 1 + 1];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumLeft += Array[index - 1 - 1];
    sumUpLeft += Array[index - 1 - 1 - 11];
    sumLeft += Array[index - 2 - 11 - 1];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumRight += Array[index + 1 + 1];
    sumUpRight += Array[index + 2 - 11];
    sumRight += Array[index + 2 - 11 + 1];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    // checks paths from level 5 going left and right to index 35 and 41
    index = 60;

    for (int i = 1; i < 4; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    tempMoves = moves;

    for (int i = 1; i < tempMoves + 1; i++) {
        sumUpLeft += Array[index - 3 - (11 * i)];
        sumUpRight += Array[index + 3 - (11 * i)];
        moves--;
    }

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumUpLeft += Array[index - 1 - 11];
    sumLeft += Array[index - 1 - 11 - 1];
    sumUpLeft += Array[index - 1 - 11 - 1 - 11];
    sumLeft += Array[index - 1 - 11 - 1 - 11 - 1];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumUpRight += Array[index + 1 - 11];
    sumRight += Array[index + 1 - 11 + 1];
    sumUpRight += Array[index + 1 - 11 + 1 - 11];
    sumRight += Array[index + 1 - 11 + 1 - 11 + 1];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumLeft += Array[index - 1 - 1];
    sumUpLeft += Array[index - 2 - 11];
    sumLeft += Array[index - 2 - 11 - 1];
    sumUpLeft += Array[index - 2 - 11 - 1 - 11];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumRight += Array[index + 1 + 1];
    sumUpRight += Array[index + 2 - 11];
    sumRight += Array[index + 2 - 11 + 1];
    sumUpRight += Array[index + 2 - 11 + 1 - 11];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumLeft += Array[index - 1 - 1];
    sumUpLeft += Array[index - 2 - 11];
    sumUpLeft += Array[index - 2 - 22];
    sumLeft += Array[index - 2 - 22 - 1];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumRight += Array[index + 1 + 1];
    sumUpRight += Array[index + 2 - 11];
    sumUpRight += Array[index + 2 - 22];
    sumRight += Array[index + 2 - 22 + 1];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumUpLeft += Array[index - 1 - 11];
    sumUpLeft += Array[index - 1 - 22];
    sumLeft += Array[index - 1 - 22 - 1];
    sumLeft += Array[index - 2 - 22 - 1];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumUpRight += Array[index + 1 - 11];
    sumUpRight += Array[index + 1 - 22];
    sumRight += Array[index + 1 - 22 + 1];
    sumRight += Array[index + 2 - 22 + 1];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumLeft = 0;
    sumUpLeft = 0;
    sumLeft += Array[index - 1];
    sumUpLeft += Array[index - 1 - 11];
    sumLeft += Array[index - 1 - 11 - 1];
    sumLeft += Array[index - 2 - 11 - 1];
    sumUpLeft += Array[index - 3 - 11 - 11];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    sumRight = 0;
    sumUpRight = 0;
    sumRight += Array[index + 1];
    sumUpRight += Array[index + 1 - 11];
    sumRight += Array[index + 1 - 11 + 1];
    sumRight += Array[index + 2 - 11 + 1];
    sumUpRight += Array[index + 3 - 11 - 11];

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    // Checking all paths for index 45 and 53
    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    for (int i = 1; i < 2; i++) {
        sumUp = sumUp + Array[index - (11 * i)];
        moves--;
    }
    index = 49;

    tempMoves = moves;

    for (int i = 1; i < tempMoves + 1; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    // checks paths to index 45 and 53 from level 5
    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    tempMoves = moves;

    for (int i = 1; i < tempMoves; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    sumUpLeft += Array[index - 4 - 11];
    sumUpRight += Array[index + 4 - 11];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    tempMoves = moves;

    for (int i = 1; i < tempMoves - 1; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    sumUpLeft += Array[index - 3 - 11];
    sumUpRight += Array[index + 3 - 11];

    sumLeft += Array[index - 3 - 11 - 1];
    sumRight += Array[index + 3 - 11 + 1];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    tempMoves = moves;

    for (int i = 1; i < tempMoves - 2; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    sumUpLeft += Array[index - 2 - 11];
    sumUpRight += Array[index + 2 - 11];

    sumLeft += Array[index - 2 - 11 - 1];
    sumLeft += Array[index - 2 - 11 - 2];
    sumRight += Array[index + 2 - 11 + 1];
    sumRight += Array[index + 2 - 11 + 2];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    tempMoves = moves;

    for (int i = 1; i < tempMoves - 3; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    sumUpLeft += Array[index - 1 - 11];
    sumUpRight += Array[index + 1 - 11];

    sumLeft += Array[index - 1 - 11 - 1];
    sumLeft += Array[index - 1 - 11 - 2];
    sumLeft += Array[index - 1 - 11 - 3];
    sumRight += Array[index + 1 - 11 + 1];
    sumRight += Array[index + 1 - 11 + 2];
    sumRight += Array[index + 1 - 11 + 3];

    MinCostArr[indexofArr] = sumUp + sumLeft + sumUpLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumUp + sumRight + sumUpRight;
    indexofArr++;

    // REPEAT FOR LOWER PART OF THE DIAMOND

    sumUp = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumUpLeft = 0;
    sumUpRight = 0;
    moves = 5;
    index = 60;

    // Checking all paths for index 103 and 105
    // calculate sum of boxes going down to level 9 (two paths to index 103 and 105)
    for (int i = 1; i < 5; i++) {
        sumDown = sumDown + Array[index + (11 * i)];
    }
    index = 104;

    //checks boxes on the left and right
    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    MinCostArr[indexofArr] = sumDown + sumLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumDown + sumRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    index = 60;

    // calculate sum of boxes going down to level 8 (the other two paths for index 103 and 105)
    for (int i = 1; i < 4; i++) {
        sumDown = sumDown + Array[index + (11 * i)];
    }
    index = 93;

    // checks boxes on the left and right (goes 1 step left, 1 step down and 1 step right, 1 step down)
    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    sumDownLeft += Array[(index - 1) + 11];
    sumDownRight += Array[(index + 1) + 11];
    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;


    // calculate sum of boxes going down to level 7
    for (int i = 1; i < 3; i++) {
        sumDown = sumDown + Array[index + (11 * i)];
        moves--;
    }
    index = 82;

    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    moves--;
    for (int i = 1; i < moves + 1; i++) {
        sumDownLeft += Array[(index - 1) + (11 * i)];
        sumDownRight += Array[(index + 1) + (11 * i)];
    }
    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;

    // calculate sum of boxes going down to level 6
    for (int i = 1; i < 2; i++) {
        sumDown = sumDown + Array[index + (11 * i)];
        moves--;
    }
    index = 71;

    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    moves--;
    for (int i = 1; i < moves + 1; i++) {
        sumDownLeft += Array[(index - 1) + (11 * i)];
        sumDownRight += Array[(index + 1) + (11 * i)];
    }
    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;

    // calculate sum of boxes starting from level 5
    index = 60;

    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    moves--;

    for (int i = 1; i < moves + 1; i++) {
        sumDownLeft += Array[(index - 1) + (11 * i)];
        sumDownRight += Array[(index + 1) + (11 * i)];
    }

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    // Checking all paths for index 91 and 95
    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;


    // goes down to level 8 (to check for two paths to get to index 91 and 95)
    for (int i = 1; i < 4; i++) {
        sumDown = sumDown + Array[index + (11 * i)];
        moves--;
    }
    index = 93;


    // checks boxes on the left and right
    for (int i = 1; i < moves + 1; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
    }

    MinCostArr[indexofArr] = sumDown + sumLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumDown + sumRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;

    // check for other two paths to get to index 91 and 95 (go down to level 7, and then go left, down, left OR level 7, left by 2, then down, and same for right)
    for (int i = 1; i < 3; i++) {
        sumDown = sumDown + Array[index + (11 * i)];
        moves--;
    }
    index = 82;

    sumLeft += Array[index - 1];
    sumLeft += Array[index - 2];
    sumRight += Array[index + 1];
    sumRight += Array[index + 2];
    moves--;

    sumDownLeft += Array[index - 2 + 11];
    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumDownLeft += Array[index - 1 + 11];
    sumLeft += Array[index - 1 + 11 - 1];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumDownRight += Array[index + 2 + 11];
    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumDownRight += Array[index + 1 + 11];
    sumRight += Array[index + 1 + 11 + 1];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;

    // checks paths from going down to level 6 to index 91 and 95
    for (int i = 1; i < 2; i++) {
        sumDown = sumDown + Array[index + (11 * i)];
        moves--;
    }
    index = 71;
    tempMoves = moves;

    for (int i = 1; i < tempMoves - 1; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    tempMoves = moves;

    for (int i = 1; i < tempMoves + 1; i++) {
        sumDownLeft += Array[index - 2 + (11 * i)];
        sumDownRight += Array[index + 2 + (11 * i)];
        moves--;
    }

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumDownLeft += Array[index - 1 + 11];
    sumLeft += Array[index - 1 + 11 - 1];
    sumDownLeft += Array[index - 1 + 11 - 1 + 11];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumDownRight += Array[index + 1 + 11];
    sumRight += Array[index + 1 + 11 + 1];
    sumDownRight += Array[index + 1 + 11 + 1 + 11];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumDownLeft += Array[index - 1 + 11];
    sumDownLeft += Array[index - 1 + 22];
    sumLeft += Array[index - 1 + 22 - 1];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumDownRight += Array[index + 1 + 11];
    sumDownRight += Array[index + 1 + 22];
    sumRight += Array[index + 1 + 22 + 1];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;
    tempMoves = 0;

    // checks paths from level 5 going left and right to index 91 and 95
    index = 60;

    for (int i = 1; i < 3; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    tempMoves = moves;

    for (int i = 1; i < tempMoves + 1; i++) {
        sumDownLeft += Array[index - 2 + (11 * i)];
        sumDownRight += Array[index + 2 + (11 * i)];
        moves--;
    }

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumDownLeft += Array[index - 1 + 11];
    sumLeft += Array[index - 1 + 11 - 1];
    sumDownLeft += Array[index - 1 + 11 - 1 + 11];
    sumDownLeft += Array[index - 1 + 11 - 1 + 22];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumDownRight += Array[index + 1 + 11];
    sumRight += Array[index + 1 + 11 + 1];
    sumDownRight += Array[index + 1 + 11 + 1 + 11];
    sumDownRight += Array[index + 1 + 11 + 1 + 22];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumDownLeft += Array[index - 1 + 11];
    sumDownLeft += Array[index - 1 + 22];
    sumLeft += Array[index - 1 + 22 - 1];
    sumDownLeft += Array[index - 1 + 22 - 1 + 11];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumDownRight += Array[index + 1 + 11];
    sumDownRight += Array[index + 1 + 22];
    sumRight += Array[index + 1 + 22 + 1];
    sumDownRight += Array[index + 1 + 22 + 1 + 11];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    sumRight = 0;
    sumLeft += Array[index - 1];
    sumRight += Array[index + 1];
    for (int i = 1; i < 4; i++) {
        sumDownLeft += Array[index - 1 + (11 * i)];
        sumDownRight += Array[index + 1 + (11 * i)];
    }

    sumLeft += Array[index - 1 + 33 - 1];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight += Array[index + 1 + 33 + 1];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    // Checking all paths for index 79 and 85
    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;


    // goes down to level 7 (to check for two paths to get to index 79 and 85)
    for (int i = 1; i < 3; i++) {
        sumDown = sumDown + Array[index + (11 * i)];
        moves--;
    }
    index = 82;


    // checks boxes on the left and right
    for (int i = 1; i < moves + 1; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
    }

    MinCostArr[indexofArr] = sumDown + sumLeft;
    indexofArr++;
    MinCostArr[indexofArr] = sumDown + sumRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;
    tempMoves = 0;

    // checks paths from going down to level 6 to index 79 and 85
    for (int i = 1; i < 2; i++) {
        sumDown = sumDown + Array[index + (11 * i)];
        moves--;
    }
    index = 71;

    tempMoves = moves;

    for (int i = 1; i < tempMoves; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    sumDownLeft += Array[index - (1 * 3) + 11];
    sumDownRight += Array[index + (1 * 3) + 11];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumDownLeft += Array[index - 1 + 11];
    sumLeft += Array[index - 1 + 11 - 1];
    sumLeft += Array[index - 1 + 11 - 1 - 1];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumDownRight += Array[index + 1 + 11];
    sumRight += Array[index + 1 + 11 + 1];
    sumRight += Array[index + 1 + 11 + 1 + 1];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumLeft += Array[index - 1 - 1];
    sumDownLeft += Array[index - 1 - 1 + 11];
    sumLeft += Array[index - 2 + 11 - 1];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumRight += Array[index + 1 + 1];
    sumDownRight += Array[index + 2 + 11];
    sumRight += Array[index + 2 + 11 + 1];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;

    // checks paths from level 5 going left and right to index 79 and 85
    index = 60;

    for (int i = 1; i < 4; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    tempMoves = moves;

    for (int i = 1; i < tempMoves + 1; i++) {
        sumDownLeft += Array[index - 3 + (11 * i)];
        sumDownRight += Array[index + 3 + (11 * i)];
        moves--;
    }

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumDownLeft += Array[index - 1 + 11];
    sumLeft += Array[index - 1 + 11 - 1];
    sumDownLeft += Array[index - 1 + 11 - 1 + 11];
    sumLeft += Array[index - 1 + 11 - 1 + 11 - 1];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumDownRight += Array[index + 1 + 11];
    sumRight += Array[index + 1 + 11 + 1];
    sumDownRight += Array[index + 1 + 11 + 1 + 11];
    sumRight += Array[index + 1 + 11 + 1 + 11 + 1];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumLeft += Array[index - 1 - 1];
    sumDownLeft += Array[index - 2 + 11];
    sumLeft += Array[index - 2 + 11 - 1];
    sumDownLeft += Array[index - 2 + 11 - 1 + 11];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumRight += Array[index + 1 + 1];
    sumDownRight += Array[index + 2 + 11];
    sumRight += Array[index + 2 + 11 + 1];
    sumDownRight += Array[index + 2 + 11 + 1 + 11];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumLeft += Array[index - 1 - 1];
    sumDownLeft += Array[index - 2 + 11];
    sumDownLeft += Array[index - 2 + 22];
    sumLeft += Array[index - 2 + 22 - 1];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumRight += Array[index + 1 + 1];
    sumDownRight += Array[index + 2 + 11];
    sumDownRight += Array[index + 2 + 22];
    sumRight += Array[index + 2 + 22 + 1];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumDownLeft += Array[index - 1 + 11];
    sumDownLeft += Array[index - 1 + 22];
    sumLeft += Array[index - 1 + 22 - 1];
    sumLeft += Array[index - 2 + 22 - 1];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumDownRight += Array[index + 1 + 11];
    sumDownRight += Array[index + 1 + 22];
    sumRight += Array[index + 1 + 22 + 1];
    sumRight += Array[index + 2 + 22 + 1];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumLeft = 0;
    sumDownLeft = 0;
    sumLeft += Array[index - 1];
    sumDownLeft += Array[index - 1 + 11];
    sumLeft += Array[index - 1 + 11 - 1];
    sumLeft += Array[index - 2 + 11 - 1];
    sumDownLeft += Array[index - 3 + 11 + 11];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    sumRight = 0;
    sumDownRight = 0;
    sumRight += Array[index + 1];
    sumDownRight += Array[index + 1 + 11];
    sumRight += Array[index + 1 + 11 + 1];
    sumRight += Array[index + 2 + 11 + 1];
    sumDownRight += Array[index + 3 + 11 + 11];

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    // Checking all paths for index 67 and 75
    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;

    for (int i = 1; i < 2; i++) {
        sumDown = sumDown + Array[index + (11 * i)];
        moves--;
    }
    index = 71;

    tempMoves = moves;

    for (int i = 1; i < tempMoves + 1; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    // checks paths to index 67 and 75 from level 5
    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;

    tempMoves = moves;

    for (int i = 1; i < tempMoves; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    sumDownLeft += Array[index - 4 + 11];
    sumDownRight += Array[index + 4 + 11];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;

    tempMoves = moves;

    for (int i = 1; i < tempMoves - 1; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    sumDownLeft += Array[index - 3 + 11];
    sumDownRight += Array[index + 3 + 11];

    sumLeft += Array[index - 3 + 11 - 1];
    sumRight += Array[index + 3 + 11 + 1];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;

    tempMoves = moves;

    for (int i = 1; i < tempMoves - 2; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    sumDownLeft += Array[index - 2 + 11];
    sumDownRight += Array[index + 2 + 11];

    sumLeft += Array[index - 2 + 11 - 1];
    sumLeft += Array[index - 2 + 11 - 2];
    sumRight += Array[index + 2 + 11 + 1];
    sumRight += Array[index + 2 + 11 + 2];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    sumDown = 0;
    sumLeft = 0;
    sumRight = 0;
    sumDown = 0;
    sumDownLeft = 0;
    sumDownRight = 0;
    moves = 5;
    index = 60;

    tempMoves = moves;

    for (int i = 1; i < tempMoves - 3; i++) {
        sumLeft += Array[index - (1 * i)];
        sumRight += Array[index + (1 * i)];
        moves--;
    }

    sumDownLeft += Array[index - 1 + 11];
    sumDownRight += Array[index + 1 + 11];

    sumLeft += Array[index - 1 + 11 - 1];
    sumLeft += Array[index - 1 + 11 - 2];
    sumLeft += Array[index - 1 + 11 - 3];
    sumRight += Array[index + 1 + 11 + 1];
    sumRight += Array[index + 1 + 11 + 2];
    sumRight += Array[index + 1 + 11 + 3];

    MinCostArr[indexofArr] = sumDown + sumLeft + sumDownLeft;
    indexofArr++;

    MinCostArr[indexofArr] = sumDown + sumRight + sumDownRight;
    indexofArr++;

    minim = MinCostArr[0];
    int lengthOfArr = sizeof(MinCostArr)/sizeof(int);

    for (int i = 0; i < lengthOfArr; i++) {
        printf("%d: %d\n", i, MinCostArr[i]);
        if (MinCostArr[i] < minim) {
            minim = MinCostArr[i];
        }
    }

    MinCost = minim;

    if (DEBUG){
        printf("Remember to reset DEBUG to 0 before submitting your code.");
    }
    /* include this print statement. */ 
    printf("The shortest path cost is [%d]\n", MinCost);
    return 0;
    }

/* This routine loads in up to ArraySize newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
    int	N, Addr, Value, NumVals;
    FILE	*FP;

    FP = fopen(InputFileName, "r");
    if (FP == NULL) {
        printf("%s could not be opened; check the filename\n", InputFileName);
        return 0;
    } else {
        for (N=0; N < ArraySize; N++) {
            NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
            if (NumVals == 2)
            IntArray[N] = Value;
            else
            break;
        }
        fclose(FP);
        return N;
    }
}
