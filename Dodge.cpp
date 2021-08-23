
#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
int x2 = 200; //Players car position
int y2 = 710;
int x = 40; //Opponents car
int y = 600;
int x3 = 40; //Opponent car 2 position
int y3 = 600;
int food[12][12] = {}; //To store and eat food , 12 lanes and food is less than or equal to 12 in all lanes
int speedO = 5;        //Speed of opponent car
int speedP = 5;        //Speed of player car
int lives = 3;
int pass = 1; //For menu
int levels = 1;
int score_first = 0;
int high_Scores[11];   //Array ro store highest scores
int Score_Highest = 0; //To check for the Highest Scores
void SetCanvasSize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * */
//Board *b;
void Timer(int m)
{

    // implement your functionality here

    // once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0, Timer, 0);
    glutPostRedisplay();
}
void GameDisplay() /**/
{

    // set the background color using function glClearColor.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

    glClearColor(0 /*Red Component*/, 0,                         //148.0/255/*Green Component*/,
                 0.0 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);                                //Update the colors
    if (pass == 1)
    { //When we want to view menu
        DrawString(400, 800, "1. START A NEW GAME", colors[GRAY]);
        DrawString(400, 600, "2.  SEE HIGH SCORES", colors[GRAY]);
        DrawString(400, 400, "3.           HELP", colors[GRAY]);
        DrawString(400, 200, "4.           EXIT", colors[GRAY]);
    }
    else if (pass == 0)
    { //When we select start a new game

        // calling some functions from util.cpp file to help students

        //Square at 400,20 position
        //DrawSquare( 400 , 20 ,40,colors[RED]);
        //Square at 250,250 position
        //DrawSquare( 250 , 250 ,20,colors[GREEN]);
        //Display Score
        //Triangle at 300, 450 position
        //DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] );
        //Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
        //Circle at 50, 670 position
        //DrawCircle(70,770,10,colors[BROWN]); //Left circles
        //Line from 550,50 to 550,480 with width 10
        //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
        //DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );

        /* * * * * * * * * * * *  * * * * DRAWING FOOD SQUARES AND CONDITIONS FOR FOOD EATING * * * * * * * * * * * * * * */
        //There are 12 lanes in arena , we move clockwise in lanes so left is '0' lane , top is '1' lane , right is '2' lane and
        // bottom is '3' lane etc

        //These all squares are for Outer Arena
        //For left squares
        for (int loop = 700; loop >= 70; loop -= 70)
        { //y values change
            if (y2 == loop && x2 == 40)
            {
                for (int j = 0; j < 10; j++) //10 food items
                {
                    if (food[0][j] != loop)
                        ;
                    {
                        food[0][((loop) / 70) - 1] = loop;
                        break;
                    }
                }
            }
            if (food[0][((loop) / 70) - 1] != loop)
            {
                DrawSquare(70, loop, 20, colors[GREEN]); //to display food
            }
        }
        //For top squares
        for (int loop = 690; loop >= 130; loop -= 70)
        { //x values change
            if (y2 == 710 && x2 == loop)
            {
                for (int j = 0; j < 9; j++) //9 food items
                {
                    if (food[1][j] != loop)
                        ;
                    {
                        food[1][((loop - 60) / 70) - 1] = loop;
                        break;
                    }
                }
            }
            if (food[1][((loop - 60) / 70) - 1] != loop)
            {
                DrawSquare(loop, 750, 20, colors[GREEN]); //to display food
            }
        }
        //For right squares
        for (int loop = 700; loop >= 70; loop -= 70)
        { //y values change
            if (y2 == loop && x2 == 720)
            {
                for (int j = 0; j < 10; j++) //10 food items
                {
                    if (food[2][j] != loop)
                        ;
                    {
                        food[2][((loop) / 70) - 1] = loop;
                        break;
                    }
                }
            }
            if (food[2][((loop) / 70) - 1] != loop)
            {
                DrawSquare(750, loop, 20, colors[GREEN]); //to display food
            }
        }
        //For bottom squares
        for (int loop = 690; loop >= 130; loop -= 70)
        { //x values change
            if (y2 == 30 && x2 == loop)
            {
                for (int j = 0; j < 9; j++) //9 food items
                {
                    if (food[3][j] != loop)
                        ;
                    {
                        food[3][((loop - 60) / 70) - 1] = loop;
                        break;
                    }
                }
            }
            if (food[3][((loop - 60) / 70) - 1] != loop)
            {
                DrawSquare(loop, 60, 20, colors[GREEN]); //to display food
            }
        }

        //These all squares are for Arena Anna
        //For top squares
        for (int loop = 570; loop >= 220; loop -= 70)
        { //x values change
            if (y2 == 600 && x2 == loop)
            {
                for (int j = 0; j < 6; j++) //6 food items
                {
                    if (food[5][j] != loop)
                        ;
                    {
                        food[5][((loop - 10) / 70) - 3] = loop;
                        break;
                    }
                }
            }
            if (food[5][((loop - 10) / 70) - 3] != loop)
            {
                DrawSquare(loop, 630, 20, colors[GREEN]); //to display food
            }
        }
        //For left squares
        for (int loop = 570; loop >= 220; loop -= 70)
        { //y values change
            if (y2 == loop && x2 == 140)
            {
                for (int j = 0; j < 6; j++) //6 food items
                {
                    if (food[4][j] != loop)
                        ;
                    {
                        food[4][((loop - 10) / 70) - 3] = loop;
                        break;
                    }
                }
            }
            if (food[4][((loop - 10) / 70) - 3] != loop)
            {
                DrawSquare(170, loop, 20, colors[GREEN]); //to display food
            }
        }
        //For right squares
        for (int loop = 560; loop >= 210; loop -= 70)
        { //y values change
            if (y2 == loop && x2 == 610)
            {
                for (int j = 0; j < 6; j++) //6 food items
                {
                    if (food[6][j] != loop)
                        ;
                    {
                        food[6][((loop) / 70) - 3] = loop;
                        break;
                    }
                }
            }
            if (food[6][((loop) / 70) - 3] != loop)
            {
                DrawSquare(630, loop, 20, colors[GREEN]); //to display food
            }
        }
        //For bottom squares
        for (int loop = 570; loop >= 220; loop -= 70)
        { //x values change
            if (y2 == 150 && x2 == loop)
            {
                for (int j = 0; j < 6; j++) //6 food items
                {
                    if (food[7][j] != loop)
                        ;
                    {
                        food[7][((loop - 10) / 70) - 3] = loop;
                        break;
                    }
                }
            }
            if (food[7][((loop - 10) / 70) - 3] != loop)
            {
                DrawSquare(loop, 180, 20, colors[GREEN]); //to display food
            }
        }

        //Thess all squares are for Arena Anna2
        //For top squares
        for (int loop = 460; loop >= 320; loop -= 70)
        { //x values change
            if (y2 == 480 && x2 == loop)
            {
                for (int j = 0; j < 3; j++) //3 food items
                {
                    if (food[9][j] != loop)
                        ;
                    {
                        food[9][((loop + 30) / 70) - 5] = loop;
                        break;
                    }
                }
            }
            if (food[9][((loop + 30) / 70) - 5] != loop)
            {
                DrawSquare(loop, 510, 20, colors[GREEN]); //to display food
            }
        }
        //For left squares
        for (int loop = 470; loop >= 330; loop -= 70)
        { //y values change
            if (y2 == loop && x2 == 260)
            {
                for (int j = 0; j < 3; j++) //3 food items
                {
                    if (food[8][j] != loop)
                        ;
                    {
                        food[8][((loop + 20) / 70) - 5] = loop;
                        break;
                    }
                }
            }
            if (food[8][((loop + 20) / 70) - 5] != loop)
            {
                DrawSquare(280, loop, 20, colors[GREEN]); //to display food
            }
        }
        //For right squares
        for (int loop = 470; loop >= 330; loop -= 70)
        { //y values change
            if (y2 == loop && x2 == 480)
            {
                for (int j = 0; j < 3; j++) //3 food items
                {
                    if (food[10][j] != loop)
                        ;
                    {
                        food[10][((loop + 20) / 70) - 5] = loop;
                        break;
                    }
                }
            }
            if (food[10][((loop + 20) / 70) - 5] != loop)
            {
                DrawSquare(500, loop, 20, colors[GREEN]); //to display food
            }
        }
        //For bottom squares
        for (int loop = 460; loop >= 320; loop -= 70)
        { //x values change
            if (y2 == 270 && x2 == loop)
            {
                for (int j = 0; j < 3; j++) //3 food items
                {
                    if (food[11][j] != loop)
                        ;
                    {
                        food[11][((loop + 20) / 70) - 5] = loop;
                        break;
                    }
                }
            }
            if (food[11][((loop + 20) / 70) - 5] != loop)
            {
                DrawSquare(loop, 290, 20, colors[GREEN]); //to display food
            }
        }

        /*************************************************CALCULATING SCORE*******************************************************/
        int Score = score_first; //Score is initialised with the first score
        for (int loop = 0; loop < 12; loop++)
        { //12 LANES
            int TotalEaten;
            if (loop == 0)
            {                    //Loop checks the lane value in array and TotalEaten shows the
                TotalEaten = 10; //food items in each lane
            }
            if (loop == 1)
            {
                TotalEaten = 9;
            }
            if (loop == 2)
            {
                TotalEaten = 10;
            }
            if (loop == 3)
            {
                TotalEaten = 9;
            }
            if (loop == 4)
            {
                TotalEaten = 6;
            }
            if (loop == 5)
            {
                TotalEaten = 6;
            }
            if (loop == 6)
            {
                TotalEaten = 6;
            }
            if (loop == 7)
            {
                TotalEaten = 6;
            }
            if (loop == 8)
            {
                TotalEaten = 3;
            }
            if (loop == 9)
            {
                TotalEaten = 3;
            }
            if (loop == 10)
            {
                TotalEaten = 3;
            }
            if (loop == 11)
            {
                TotalEaten = 3;
            }
            for (int k = 0; k < TotalEaten; k++)
            {
                if (food[loop][k] != 0)
                { //loop is for lanes and k is for food
                    Score++;
                }
            }
        }
        DrawString(50, 900, "Score=" + Num2Str(Score), colors[GRAY]); //To display Score at the top
        if (Score == 73 * levels)
        { //To move on to next levels. For Example 73*2=146 , after that you can move to level 3
            levels++;
            score_first = Score; //To calculate the total score for all levels
            x2 = 270;            //Players car position
            y2 = 710;
            x = 40; //Opponents car
            y = 270;

            for (int lane = 0; lane < 12; lane++)
            { //To display food again
                for (int item = 0; item < 12; item++)
                {
                    food[lane][item] = 0;
                }
            }
            if (levels == 5) //When level 4 is ended , it moves to 5 and player wins the game
            {
                pass = 5;
            }
            if (levels == 3) //At level 3 , speed of opponent car is doubled
            {
                speedO = speedO * 2; //Speed of opponent gets doubled
            }
        }
        DrawString(350, 900, "Levels=" + Num2Str(levels), colors[GRAY]); //To display levels on top
                                                                         /* * * * * * * * * * * * * * * * * * * * * * DRAWING ARENAS * * * * * * * * * * * * * * * * * * * * * * * * * */
        // Drawing Arena (outer Arena)
        int gap_turn = 120;
        int sx = 20;
        int sy = 10;
        int swidth = 800 / 2 - gap_turn / 2; // half width
        int sheight = 10;
        float *scolor = colors[BLUE_VIOLET];
        DrawRectangle(sx, sy, swidth, sheight, scolor);                                                           // bottom left
        DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor);                                       // bottom right
        DrawRectangle(sx + swidth * 2 + gap_turn, sy + sheight, sheight * 2, swidth, scolor);                     // right down
        DrawRectangle(sx + swidth * 2 + gap_turn, sy + sheight + swidth + gap_turn, sheight * 2, swidth, scolor); // right up
        DrawRectangle(sx + swidth + gap_turn, sy + 810, swidth, sheight, scolor);                                 // top left
        DrawRectangle(sx, sy + 810, swidth, sheight, scolor);                                                     // top right
        DrawRectangle(sx - sheight * 2, sy + sheight + swidth + gap_turn, sheight * 2, swidth, scolor);           // left up
        DrawRectangle(sx - sheight * 2, sy + sheight, sheight * 2, swidth, scolor);                               // left down

        //Drawing Arena Anna(inner arena)
        int gap_turn2 = 120;
        int sx2 = 140;
        int sy2 = 130;
        int swidth2 = 550 / 2 - gap_turn2 / 2; // half width
        int sheight2 = 10;
        float *scolor2 = colors[DARK_BLUE];
        DrawRectangle(sx2, sy2, swidth2, sheight2, scolor2);                                                                // bottom left
        DrawRectangle(sx2 + swidth2 + gap_turn2, sy2, swidth2, sheight2, scolor2);                                          // bottom right
        DrawRectangle(sx2 + swidth2 * 2 + gap_turn2, sy2 + sheight2, sheight2 * 2, swidth2, scolor2);                       // right down
        DrawRectangle(sx2 + swidth2 * 2 + gap_turn2, sy2 + sheight2 + swidth2 + gap_turn2, sheight2 * 2, swidth2, scolor2); // right up
        DrawRectangle(sx2 + swidth2 + gap_turn2, sy2 + 560, swidth2, sheight2, scolor2);                                    // top left
        DrawRectangle(sx2, sy2 + 560, swidth2, sheight2, scolor2);                                                          // top right
        DrawRectangle(sx2 - sheight2 * 2, sy2 + sheight2 + swidth2 + gap_turn2, sheight2 * 2, swidth2, scolor2);            // left up
        DrawRectangle(sx2 - sheight2 * 2, sy2 + sheight2, sheight2 * 2, swidth2, scolor2);                                  // left down

        //Drawing Arena Anna2(last arena for travelling)
        int gap_turn3 = 120;
        int sx3 = 260;
        int sy3 = 250;
        int swidth3 = 300 / 2 - gap_turn3 / 2; // half width
        int sheight3 = 10;
        float *scolor3 = colors[ROYAL_BLUE];
        DrawRectangle(sx3, sy3, swidth3, sheight3, scolor3);                                                                // bottom left
        DrawRectangle(sx3 + swidth3 + gap_turn3, sy3, swidth3, sheight3, scolor3);                                          // bottom right
        DrawRectangle(sx3 + swidth3 * 2 + gap_turn3, sy3 + sheight3, sheight3 * 2, swidth3, scolor3);                       // right down
        DrawRectangle(sx3 + swidth3 * 2 + gap_turn3, sy3 + sheight3 + swidth3 + gap_turn3, sheight3 * 2, swidth3, scolor3); // right up
        DrawRectangle(sx3 + swidth3 + gap_turn3, sy3 + 310, swidth3, sheight3, scolor3);                                    // top left
        DrawRectangle(sx3, sy3 + 310, swidth3, sheight3, scolor3);                                                          // top right
        DrawRectangle(sx3 - sheight3 * 2, sy3 + sheight3 + swidth3 + gap_turn3, sheight3 * 2, swidth3, scolor3);            // left up
        DrawRectangle(sx3 - sheight3 * 2, sy3 + sheight3, sheight3 * 2, swidth3, scolor3);                                  // left down

        // Drawing Arena Anna3(the box arena in the middle)
        int gap_turn4 = 0;
        int sx4 = 380;
        int sy4 = 370;
        int swidth4 = 50 / 2 - gap_turn4 / 2; // half width
        int sheight4 = 10;
        float *scolor4 = colors[MEDIUM_PURPLE];
        DrawRectangle(sx4, sy4, swidth4, sheight4, scolor4);                                                                // bottom left
        DrawRectangle(sx4 + swidth4 + gap_turn4, sy4, swidth4, sheight4, scolor4);                                          // bottom right
        DrawRectangle(sx4 + swidth4 * 2 + gap_turn4, sy4 + sheight4, sheight4 * 2, swidth4, scolor4);                       // right down
        DrawRectangle(sx4 + swidth4 * 2 + gap_turn4, sy4 + sheight4 + swidth4 + gap_turn4, sheight4 * 2, swidth4, scolor4); // right up
        DrawRectangle(sx4 + swidth4 + gap_turn4, sy4 + 60, swidth4, sheight4, scolor4);                                     // top left
        DrawRectangle(sx4, sy4 + 60, swidth4, sheight4, scolor4);                                                           // top right
        DrawRectangle(sx4 - sheight4 * 2, sy4 + sheight4 + swidth4 + gap_turn4, sheight4 * 2, swidth4, scolor4);            // left up
        DrawRectangle(sx4 - sheight4 * 2, sy4 + sheight4, sheight4 * 2, swidth4, scolor4);                                  // left down

        /* * * * * * * * * * * * * * * * * * * * * * DRAWING CARS AND CHECKING THEIR DIRECTION * * * * * * * * * * * * * * * * * * * * */
        // Drawing opponent car

        float width = 20;
        float height = 15;
        float *color = colors[BLUE_VIOLET];
        float radius = 5.0;

        //Checking in which Direction to move in outer arena
        //Bottom lane
        if (x <= 720 && y == 30)
        {
            x += speedO;
        }
        //right lane
        if (y <= 720 && x == 720)
        {
            y += speedO;
        }
        //top lane
        if (y == 710 && x >= 40)
        {
            x -= speedO;
        }
        //left lane
        if (x == 40 && y >= 30)
        {
            y -= speedO;
        }
        //Checking in which Direction to move in Arena Anna(inner arena)
        //left Lane
        if (x == 140 && y <= 600 && y >= 140)
        {

            y -= speedO;
        }
        // top lane
        if (y == 600 && x >= 140 && x <= 610)
        {
            x -= speedO;
        }
        //right lane

        if (x == 610 && y <= 600 && y >= 150)
        {
            y += speedO;
        }
        //bottom lane
        if (y == 150 && x >= 140 && x <= 610)
        {
            x += speedO;
        }
        //Checking in which Direction to move for arena anna2(the last arena to travel)
        //left lane
        if (x == 260 && y >= 250 && y <= 480)
        {
            y -= speedO;
        }
        //top lane
        if (y == 480 && x <= 480 && x >= 240)
        {
            x -= speedO;
        }
        //right lane
        if (x == 480 && y >= 270 && y <= 500)
        {
            y += speedO;
        }
        //bottom lane
        if (y == 270 && x >= 240 && x <= 500)
        {
            x += speedO;
        }

        DrawRoundRect(x, y, width, height, color, radius);                              // bottom left tyre
        DrawRoundRect(x + width * 3, y, width, height, color, radius);                  // bottom right tyre
        DrawRoundRect(x + width * 3, y + height * 4, width, height, color, radius);     // top right tyre
        DrawRoundRect(x, y + height * 4, width, height, color, radius);                 // top left tyre
        DrawRoundRect(x, y + height * 2, width, height, color, radius / 2);             // body left rect
        DrawRoundRect(x + width, y + height, width * 2, height * 3, color, radius / 2); // body center rect
        DrawRoundRect(x + width * 3, y + height * 2, width, height, color, radius / 2); // body right rect

        //Drawing Players car
        float width2 = 20;
        float height2 = 15;
        float *color2 = colors[BROWN];
        float radius2 = 5.0;

        //Checkig in which direction to move
        //Conditions of Direction for outer arena
        //Bottom lane
        if (x2 >= 40 && y2 == 30)
        {
            x2 -= speedP;
        }
        //Left lane
        if (y2 <= 710 && x2 == 40)
        {
            y2 += speedP;
        }
        //Top lane
        if (x2 <= 720 && y2 == 710)
        {
            x2 += speedP;
        }
        //Right lane
        if (y2 >= 30 && x2 == 720)
        {
            y2 -= speedP;
        }

        //Conditions of Direction for Arena Anna(inner arena)
        //left Lane
        if (x2 == 140 && y2 <= 600 && y2 >= 140)
        {

            y2 += speedP;
        }
        // top lane
        if (y2 == 600 && x2 >= 140 && x2 <= 610)
        {
            x2 += speedP;
        }
        //right lane
        if (x2 == 610 && y2 <= 600 && y2 >= 150)
        {
            y2 -= speedP;
        }
        //bottom lane
        if (y2 == 150 && x2 >= 140 && x2 <= 610)
        {
            x2 -= speedP;
        }
        //direction for arena anna2(the last arena to travel)
        //left lane
        if (x2 == 260 && y2 >= 250 && y2 <= 480)
        {
            y2 += speedP;
        }
        //top lane
        if (y2 == 480 && x2 <= 480 && x2 >= 240)
        {
            x2 += speedP;
        }
        //right lane
        if (x2 == 480 && y2 >= 270 && y2 <= 500)
        {
            y2 -= speedP;
        }
        //bottom lane
        if (y2 == 270 && x2 >= 240 && x2 <= 500)
        {
            x2 -= speedP;
        }
        DrawRoundRect(x2, y2, width2, height2, color2, radius2);                                // bottom left tyre
        DrawRoundRect(x2 + width2 * 3, y2, width2, height2, color2, radius2);                   // bottom right tyre
        DrawRoundRect(x2 + width2 * 3, y2 + height2 * 4, width2, height2, color2, radius2);     // top right tyre
        DrawRoundRect(x2, y2 + height2 * 4, width2, height2, color2, radius2);                  // top left tyre
        DrawRoundRect(x2, y2 + height2 * 2, width2, height2, color2, radius2 / 2);              // body left rect
        DrawRoundRect(x2 + width2, y2 + height2, width2 * 2, height2 * 3, color2, radius2 / 2); // body center rect
        DrawRoundRect(x2 + width2 * 3, y2 + height2 * 2, width2, height2, color2, radius2 / 2); // body right rect

        /***************************************CHANGING LANES OF OPPONENT CAR 1 (AI MOVEMENT)********************************/

        //From top
        if (y == 710 && x >= 280 && x <= 390) //It checks the gapturn
        {
            if (y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && y > y2) //Checks the position of player
                y -= 110;
        }
        else if (y == 600 && x >= 280 && x <= 390) //It checks the gapturn
        {
            if (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && y < y2) //Checks the position of player
                y += 110;
            else if (y2 >= 250 && y2 <= 500 && x2 >= 260 && x2 <= 500 && y > y2) //Checks the position of player
                y -= 120;
        }
        else if (y == 480 && x >= 280 && x <= 390) //It checks the gapturn
        {
            if ((y2 >= 250 && y2 <= 500 && x2 >= 260 && x2 <= 500 && y < y2) || (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && y < y2)) //Checks the position of player
                y += 120;
        }

        //From bottom
        if (y == 30 && x >= 280 && x <= 390) //It checks the gapturn
        {
            if (y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && y < y2) //Checks the position of player
                y += 120;
        }
        else if (y == 150 && x >= 280 && x <= 390) //It checks the gapturn
        {
            if (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && y > y2) //Checks the position of player
                y -= 120;

            else if (y2 >= 250 && y2 <= 500 && x2 >= 260 && x2 <= 500 && y < y2) //Checks the position of player
                y += 120;
        }
        else if (y == 270 && x >= 280 && x <= 390) //It checks the gapturn
        {
            if ((y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && y > y2) || (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && y > y2)) //Checks the position of player
                y -= 120;
        }

        if (levels >= 2)
        {
            //From Left
            if (x == 40 && y >= 370 && y <= 470) //It checks the gapturn
            {
                if (y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && x < x2) //Checks the position of player
                    x += 100;
            }
            else if (x == 140 && y >= 370 && y <= 470) //It checks the gapturn
            {
                if (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && x > x2) //Checks the position of player
                    x -= 100;
                else if (y2 >= 250 && y2 <= 500 && x2 >= 260 && x2 <= 500 && x < x2) //Checks the position of player
                    x += 120;
            }
            else if (x == 260 && y >= 370 && y <= 470) //It checks the gapturn
            {
                if ((y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && x > x2) || (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && x > x2)) //Checks the position of player
                    x -= 120;
            }

            //From right
            if (x == 720 && y <= 400 && y >= 370) //It checks the gapturn
            {
                if (y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && x > x2) //checks the position of player
                    x -= 110;
            }
            else if (x == 610 && y <= 400 && y >= 370) //It checks the gapturn
            {
                if (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && x < x2) //Checks the position of player
                    x += 110;
                else if (y2 >= 250 && y2 <= 500 && x2 >= 260 && x2 <= 500 && x > x2) //Checks the position of player
                    x -= 130;
            }
            else if (x == 480 && y <= 400 && y >= 370) //It Checks the gapturn
            {
                if ((y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && x < x2) || (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && x < x2)) //Checks the position of player
                    x += 130;
            }
        }

        if (levels == 4)
        {
            // Drawing opponent car 2

            float width3 = 20;
            float height3 = 15;
            float *color3 = colors[GOLD];
            float radius3 = 5.0;
            //Checking in which Direction to move in outer arena
            //Bottom lane
            if (x3 <= 720 && y3 == 30)
            {
                x3 += speedO;
            }
            //right lane
            if (y3 <= 720 && x3 == 720)
            {
                y3 += speedO;
            }
            //top lane
            if (y3 == 710 && x3 >= 40)
            {
                x3 -= speedO;
            }
            //left lane
            if (x3 == 40 && y3 >= 30)
            {
                y3 -= speedO;
            }
            //Checking in which Direction to move in Arena Anna
            //left Lane
            if (x3 == 140 && y3 <= 600 && y3 >= 140)
            {

                y3 -= speedO;
            }
            // top lane
            if (y3 == 600 && x3 >= 140 && x3 <= 610)
            {
                x3 -= speedO;
            }
            //right lane

            if (x3 == 610 && y3 <= 600 && y3 >= 150)
            {
                y3 += speedO;
            }
            //bottom lane
            if (y3 == 150 && x3 >= 140 && x3 <= 610)
            {
                x3 += speedO;
            }
            //Checking in which Direction to move for arena anna2
            //left lane
            if (x3 == 260 && y3 >= 250 && y3 <= 480)
            {
                y3 -= speedO;
            }
            //top lane
            if (y3 == 480 && x3 <= 480 && x3 >= 240)
            {
                x3 -= speedO;
            }
            //right lane
            if (x3 == 480 && y3 >= 270 && y3 <= 500)
            {
                y3 += speedO;
            }
            //bottom lane
            if (y3 == 270 && x3 >= 240 && x3 <= 500)
            {
                x3 += speedO;
            }

            DrawRoundRect(x3, y3, width3, height3, color3, radius3);                                // bottom left tyre
            DrawRoundRect(x3 + width3 * 3, y3, width3, height3, color3, radius3);                   // bottom right tyre
            DrawRoundRect(x3 + width3 * 3, y3 + height3 * 4, width3, height3, color3, radius3);     // top right tyre
            DrawRoundRect(x3, y3 + height3 * 4, width3, height3, color3, radius3);                  // top left tyre
            DrawRoundRect(x3, y3 + height3 * 2, width3, height3, color3, radius3 / 2);              // body left rect
            DrawRoundRect(x3 + width3, y3 + height3, width3 * 2, height3 * 3, color3, radius3 / 2); // body center rect
            DrawRoundRect(x3 + width3 * 3, y3 + height3 * 2, width3, height3, color3, radius3 / 2); // body right rect

            //From top
            if (y3 == 710 && x3 >= 280 && x3 <= 390) //It checks the gapturn
            {
                if (y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && y3 > y2) //Checks the position of player
                    y3 -= 110;
            }
            else if (y3 == 600 && x3 >= 280 && x3 <= 390) //It checks the gapturn
            {
                if (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && y3 < y2) //Checks the position of player
                    y += 110;
                else if (y2 >= 250 && y2 <= 500 && x2 >= 260 && x2 <= 500 && y3 > y2) //Checks the position of player
                    y3 -= 120;
            }
            else if (y3 == 480 && x3 >= 280 && x3 <= 390) //It checks the gapturn
            {
                if ((y2 >= 250 && y2 <= 500 && x2 >= 260 && x2 <= 500 && y3 < y2) || (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && y3 < y2)) //Checks the position of player
                    y3 += 120;
            }

            //From bottom
            if (y3 == 30 && x3 >= 280 && x3 <= 390) //It checks the gapturn
            {
                if (y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && y3 < y2) //Checks the position of player
                    y3 += 120;
            }
            else if (y3 == 150 && x3 >= 280 && x3 <= 390) //It checks the gapturn
            {
                if (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && y3 > y2) //Checks the position of player
                    y3 -= 120;

                else if (y2 >= 250 && y2 <= 500 && x2 >= 260 && x2 <= 500 && y3 < y2) //Checks the position of player
                    y3 += 120;
            }
            else if (y3 == 270 && x3 >= 280 && x3 <= 390) //It checks the gapturn
            {
                if ((y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && y3 > y2) || (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && y3 > y2)) //Checks the position of player
                    y3 -= 120;
            }
            //From Left
            if (x3 == 40 && y3 >= 370 && y3 <= 470) //It checks the gapturn
            {
                if (y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && x3 < x2) //Checks the position of player
                    x3 += 100;
            }
            else if (x3 == 140 && y3 >= 370 && y3 <= 470) //It checks the gapturn
            {
                if (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && x3 > x2) //Checks the position of player
                    x3 -= 100;
                else if (y2 >= 250 && y2 <= 500 && x2 >= 260 && x2 <= 500 && x3 < x2) //Checks the position of player
                    x3 += 120;
            }
            else if (x3 == 260 && y3 >= 370 && y3 <= 470) //It checks the gapturn
            {
                if ((y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && x3 > x2) || (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && x3 > x2)) //Checks the position of player
                    x3 -= 120;
            }

            //From right
            if (x3 == 720 && y3 <= 400 && y3 >= 370) //It checks the gapturn
            {
                if (y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && x3 > x2) //checks the position of player
                    x3 -= 110;
            }
            else if (x3 == 610 && y3 <= 400 && y3 >= 370) //It checks the gapturn
            {
                if (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && x3 < x2) //Checks the position of player
                    x3 += 110;
                else if (y2 >= 250 && y2 <= 500 && x2 >= 260 && x2 <= 500 && x3 > x2) //Checks the position of player
                    x3 -= 130;
            }
            else if (x3 == 480 && y3 <= 400 && y3 >= 370) //It Checks the gapturn
            {
                if ((y2 >= 140 && y2 <= 600 && x2 >= 140 && x2 <= 610 && x3 < x2) || (y2 >= 30 && y2 <= 720 && x2 >= 40 && x2 <= 720 && x3 < x2)) //Checks the position of player
                    x3 += 130;
            }
        }
        /**********************************************LIVES AND COLLISSION****************************************************/
        DrawString(700, 900, "Lives=" + Num2Str(lives), colors[GRAY]); //To display Lives on top
        //The conditions in if are the range to check for the collisiion of two cars
        //x2 is for opponent car 1 in first 3 levels and x3 is for opponent car 3 which appears in 4th level
        if (((x <= x2 + 5 && x >= x2 - 5) && (y <= y2 + 5 && y >= y2 - 5)) || ((x3 <= x2 + 5 && x3 >= x2 - 5) && (y3 <= y2 + 5 && y3 >= y2 - 5)))
        {
            DrawString(400, 600, " GAME OVER", colors[GRAY]);
            lives--;  //Lives decrement when player collides with opponent
            x2 = 270; //Players car position
            y2 = 710;
            x = 40; //Opponents car
            y = 270;
            if (Score >= Score_Highest) //It is to check that in 3 lives ,what is player's highest score
            {
                Score_Highest = Score; //It makes score equal to highest score
            }

            for (int lane = 0; lane < 12; lane++)
            { //The food is displayed again
                for (int item = 0; item < 12; item++)
                {
                    food[lane][item] = 0;
                }
            } 
            if (lives == 0) //When no lives are left behind
            {
                DrawString(400, 600, " GAME OVER", colors[GRAY]);
                //Reading from a file
                int count = 1;
                high_Scores[0] = Score_Highest;
                string score;
                ifstream fin("high score.txt"); //name of the file it is supposed to read
                if (fin.is_open())
                {
                    while (getline(fin, score)) //this loop will run depending on the number of lines in the file
                    {
                        cout << score << '\n';
                        high_Scores[count] = stoi(score);
                        count++;

                        //HINT: use stoi() to convert string into Integer
                    }
                    fin.close();
                }
                else
                    cout << "Unable to open file";
                //Sorting
                int temp;
                for (int iter = 1; iter <= 10; iter++)
                {
                    for (int loop = 0; loop < 11 - iter; loop++)
                    {
                        if (high_Scores[loop] > high_Scores[loop + 1])
                        {
                            temp = high_Scores[loop];
                            high_Scores[loop] = high_Scores[loop + 1];
                            high_Scores[loop + 1] = temp;
                        }
                    }
                }
                for (int j = 0; j < 11; j++)
                {
                    cout << high_Scores[j] << '\n';
                }
                //writing to a file
                ofstream fout;
                fout.open("high score.txt"); //this function takes the name of the file that you are writing to

                for (int i = 1; i < 11; i++)
                {
                    fout << high_Scores[i] << endl;
                }

                fout.close();

                exit(1);
            }
        }
    }
    else if (pass == 2) //To view high scores
    {
        //Reading from a file
        int count1 = 1;
        string score;
        ifstream fin("high score.txt"); //name of the file it is supposed to read
        if (fin.is_open())
        {
            while (getline(fin, score)) //this loop will run depending on the number of lines in the file
            {
                cout << score << '\n';
                high_Scores[count1] = stoi(score);
                //HINT: use stoi() to convert string into Integer
                count1++;
            }
            fin.close();
        }
        else
            cout << "Unable to open file";
        int high_Scores2[10];
        for (int loop = 0; loop < 10; loop++)
        {
            high_Scores2[loop] = high_Scores[loop];
        }
        for (int loop = 0, loop2 = 9; loop < 10 && loop2 >= 0; loop++, loop2--)
        {
            high_Scores[loop] = high_Scores2[loop2];
        }
        DrawString(400, 900, Num2Str(high_Scores2[0]), colors[GRAY]);
        DrawString(400, 850, Num2Str(high_Scores2[1]), colors[GRAY]);
        DrawString(400, 800, Num2Str(high_Scores2[2]), colors[GRAY]);
        DrawString(400, 750, Num2Str(high_Scores2[3]), colors[GRAY]);
        DrawString(400, 700, Num2Str(high_Scores2[4]), colors[GRAY]);
        DrawString(400, 650, Num2Str(high_Scores2[5]), colors[GRAY]);
        DrawString(400, 600, Num2Str(high_Scores2[6]), colors[GRAY]);
        DrawString(400, 550, Num2Str(high_Scores2[7]), colors[GRAY]);
        DrawString(400, 500, Num2Str(high_Scores2[8]), colors[GRAY]);
        DrawString(400, 450, Num2Str(high_Scores2[9]), colors[GRAY]);
    }
    else if (pass == 3) //To get Help for the game
    {
        DrawString(100, 800, "The following are the keyboard movements:", colors[GRAY]);
        DrawString(100, 700, "Use Left arrow Key to move in Left gaps", colors[GRAY]);
        DrawString(100, 600, "Use Right arrow Key to move in Right gaps", colors[GRAY]);
        DrawString(100, 500, "Use Top arrow Key to move in Top gaps", colors[GRAY]);
        DrawString(100, 400, "Use Bottom arrow Key to move in Bottom gaps", colors[GRAY]);

        DrawString(100, 300, "You have to collect all the food items to reach the next level", colors[GRAY]);
        DrawString(100, 200, "There are 4 levels in the game . A collission with the opponent car will end that game", colors[GRAY]);
        DrawString(100, 100, "Your car moves clockwise and opponent car's move anticlockwise", colors[GRAY]);
    }
    else if (pass == 4) //To exit the game
    {
        exit(1);
    }
    else if (pass == 5) //When you finish level 4 and win
    {
        DrawString(300, 600, " CONGRATULATIONS", colors[GRAY]);
        DrawString(300, 400, "YOU HAVE WON THE GAME", colors[GRAY]);
    }
    else if (pass == 6) //When you Pause the game , the following menu is printed
    {
        DrawString(400, 900, "1. START A NEW GAME", colors[GRAY]);
        DrawString(400, 700, "2.  SEE HIGH SCORES", colors[GRAY]);
        DrawString(400, 500, "3.           HELP", colors[GRAY]);
        DrawString(400, 300, "4.           EXIT", colors[GRAY]);
        DrawString(400, 100, "5.           CONTINUE", colors[GRAY]);
    }
    Timer(1000);
    glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *==
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
    {
        // what to do when left key is pressed...
        //To enter into arena anna(inner arena)
        if (y2 <= 400 && y2 >= 370 && x2 == 720)
        {
            x2 -= 110;
        }
        //To enter into arena anna2(last arena)
        else if (y2 <= 400 && y2 >= 370 && x2 == 610)
        {
            x2 -= 130;
        }
        //To get out of arena anna2(last arena)
        else if (x2 == 260 && y2 <= 470 && y2 >= 370)
        {
            x2 -= 120;
        }
        //To get out of arena anna(inner arena)
        else if (x2 == 140 && y2 <= 470 && y2 >= 370)
        {
            x2 -= 100;
        }
    }
    else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
    {
        //To enter into arena anna (inner arena)
        if (y2 <= 470 && y2 >= 370 && x2 == 40)
        {
            x2 += 100;
        }
        //To enter into arena anna2(last arena)
        else if (y2 <= 470 && y2 >= 370 && x2 == 140)
        {
            x2 += 120;
        }
        //To get out of arena anna2(last arena)
        else if (x2 == 480 && y2 <= 400 && y2 >= 370)
        {
            x2 += 130;
        }
        //To get out of arena anna(inner arena)
        else if (x2 == 610 && y2 <= 400 && y2 >= 370)
        {
            x2 += 110;
        }
    }
    else if (key == GLUT_KEY_UP /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
    {
        //To enter into arena anna(inner arena)
        if (y2 == 30 && x2 >= 350 && x2 <= 390)
        {
            y2 += 120;
        }
        //To enter into arena anna2(last arena)
        else if (y2 == 150 && x2 >= 350 && x2 <= 390)
        {
            y2 += 120;
        }
        //To get out of arena anna2(last arena)
        else if (y2 == 480 && x2 >= 360 && x2 <= 470)
        {
            y2 += 120;
        }
        //To get out of arena anna(inner arena)
        else if (y2 == 600 && x2 >= 360 && x2 <= 470)
        {
            y2 += 110;
        }
    }

    else if (key == GLUT_KEY_DOWN /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
    {
        //To enter into arena anna(inner arena)
        if (y2 == 710 && x2 >= 360 && x2 <= 470)
        {
            y2 -= 110;
        }
        //To enter into arena anna2(last arena)
        else if (y2 == 600 && x2 >= 360 && x2 <= 470)
        {
            y2 -= 120;
        }
        //To get out of arena anna2(last arena)
        else if (y2 == 270 && x2 >= 350 && x2 <= 390)
        {
            y2 -= 120;
        }
        //To get out of arena anna(inner arena)
        else if (y2 == 150 && x2 >= 350 && x2 <= 390)
        {
            y2 -= 120;
        }
    }

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

    glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y)
{
    if (key == '1') //To start a new game
    {
        if (pass == 6) //To start a new game after pausing a game
        {              //Everything starts from the initial
            score_first = 0;
            lives = 3;
            levels = 1;
            x2 = 270; //Players car position
            y2 = 710;
            x = 40; //Opponents car
            y = 270;
            for (int lane = 0; lane < 12; lane++)
            { //To display food again
                for (int item = 0; item < 12; item++)
                {
                    food[lane][item] = 0;
                }
            }
        }
        pass = 0; //To start a new game
    }
    if (key == '2') //For High Scores
    {
        pass = 2;
    }
    if (key == '3') //For Help
    {
        pass = 3;
    }
    if (key == '4') //To exit
    {
        pass = 4;
    }
    if (key == '5') //To continue the game from where the player has left
    {
        pass = 0;
    }

    if (key == 27 /* Escape key ASCII*/)
    {
        exit(1); // exit the program when escape key is pressed.
    }

    if (key == 'p' || key == 'P')
    {
        //do something if P is pressed
        pass = 6;
    }
    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y)
{
    cout << x << " " << y << endl;
    glutPostRedisplay();
}
void MouseMoved(int x, int y)
{

    glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON) // dealing only with left button
    {

        cout << GLUT_DOWN << " " << GLUT_UP << endl;
    }
    else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
    {
    }
    glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char *argv[])
{

    //b = new Board(60, 60); // create a new board object to use in the Display Function ...

    int width = 940, height = 940; // i have set my window size to be 800 x 600
    //b->InitalizeBoard(width, height);
    InitRandomizer();                             // seed the random number generator...
    glutInit(&argc, argv);                        // initialize the graphics library...
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50);               // set the initial position of our window
    glutInitWindowSize(width, height);            // set the size of our window
    glutCreateWindow("OOP Centipede");            // set the title of our game window
    SetCanvasSize(width, height);                 // set the number of pixels...

    // Register your functions to the library,
    // you are telling the library names of function to call for different tasks.
    //glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

    glutDisplayFunc(GameDisplay);      // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys);   // tell library which function to call for printable ASCII characters
    // This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(1000.0, Timer, 0);
    glutMouseFunc(MouseClicked);
    glutPassiveMotionFunc(MouseMoved);    // Mouse
    glutMotionFunc(MousePressedAndMoved); // Mouse

    // now handle the control to library and it will call our registered functions when
    // it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* AsteroidS_CPP_ */
