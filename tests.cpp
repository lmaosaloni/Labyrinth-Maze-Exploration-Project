#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include "maze.h"
#include "grid.h"
#include "EscapeTheLabyrinth.h"


TEST(grid, defaultConstructor){
    
    // TO DO:  Write 100s of asserts per member function.
    
    // Default Constructor Tests:
    Grid<int> g1;
    ASSERT_EQ(g1.size(), 16);
  
    Grid<string> g2;
    ASSERT_EQ(g2.size(), 16);
  
    Grid<char> g3;
    ASSERT_EQ(g3.size(), 16);
  
    Grid<double> g4;
    ASSERT_EQ(g4.size(), 16);
  
}

TEST(grid, parameterizedConstructor){
  
    Grid<int> g1(10,5);
    ASSERT_EQ(g1.size(), 50);
  
    Grid<string> g2(5,10);
    ASSERT_EQ(g2.size(), 50);
  
    Grid<char> g3(8,8);
    ASSERT_EQ(g3.size(), 64);
  
    Grid<double> g4(100,200);
    ASSERT_EQ(g4.size(), 20000);
}

TEST(grid2, parameterizedConstructor){
  
    Grid<int> g1(10,10);
    ASSERT_EQ(g1.size(), 100);
  
    Grid<string> g2(2,2);
    ASSERT_EQ(g2.size(), 4);
  
    Grid<char> g3(8,9);
    ASSERT_EQ(g3.size(), 72);
  
    Grid<double> g4(300,200);
    ASSERT_EQ(g4.size(), 60000);
}

TEST(grid, numrows){
    Grid<int> g1;
    ASSERT_EQ(g1.numrows(), 4);
  
    Grid<string> g2(10,5);
    ASSERT_EQ(g2.numrows(), 10);
  
    Grid<char> g3(8,8);
    ASSERT_EQ(g3.numrows(), 8);
  
    Grid<double> g4(100,200);
    ASSERT_EQ(g4.numrows(), 100);
}

TEST(grid2, numrows){
    Grid<int> g1;
    ASSERT_EQ(g1.numrows(), 4);
  
    Grid<string> g2(7,2);
    ASSERT_EQ(g2.numrows(), 7);
  
    Grid<char> g3(9,8);
    ASSERT_EQ(g3.numrows(), 9);
  
    Grid<double> g4(20000,300);
    ASSERT_EQ(g4.numrows(), 20000);
}

TEST(grid, numcols){
    Grid<int> g1;
    ASSERT_EQ(g1.numcols(0), 4);
  
    Grid<string> g2(10,5);
    ASSERT_EQ(g2.numcols(1), 5);
  
    Grid<char> g3(8,8);
    ASSERT_EQ(g3.numcols(2), 8);
  
    Grid<double> g4(100,200);
    ASSERT_EQ(g4.numcols(3), 200);
}

TEST(grid, getter){
  Grid<int> g1(10,5);
  ASSERT_EQ(g1(6,2), 0);
  
  g1(0,3) = 57;
  ASSERT_EQ(g1(0,3), 57);
  
}

TEST(grid, copy){
  Grid<int> g1;
  ASSERT_EQ(g1.size(), 16);
  
  Grid<int> g2(g1);
  ASSERT_EQ(g2.size(), 16);
  
  if (g1(1,1) == g2(1,1))
  {
    cout << "**TRUE**" << endl;
  }
  else
  {
    cout << "**FAIL**" << endl;
  }
  
//   for (int i = 0; i < g1.size(); i++){
// 		ASSERT_EQ(g1(i,i), g2(i,i));
// 	}
  
}

TEST(grid2, copy){
  Grid<int> g1(10,10);
  ASSERT_EQ(g1.size(), 100);
  
  Grid<int> g2(g1);
  ASSERT_EQ(g2.size(), 100);
  
  if (g1(2,2) == g2(2,2))
  {
    cout << "**TRUE**" << endl;
  }
  else
  {
    cout << "**FAIL**" << endl;
  }
  
//   for (int i = 0; i < g1.size(); i++){
// 		ASSERT_EQ(g1(i,i), g2(i,i));
// 	}
  
}

TEST(grid3, copy){
  Grid<int> g1(5,5);
  ASSERT_EQ(g1.size(), 25);
  
  Grid<int> g2(g1);
  ASSERT_EQ(g2.size(), 25);
  
  if (g1(1,1) == g2(3,3))
  {
    cout << "**TRUE**" << endl;
  }
  else
  {
    cout << "**FAIL**" << endl;
  }
  
//   for (int i = 0; i < g1.size(); i++){
// 		ASSERT_EQ(g1(i,i), g2(i,i));
// 	}
  
}






// TO DO:  Write many TESTs, at least one for, if not more,
// for each member function.  Each tests should have 100s of assertions.






// TO DO:  As you get to each milestone, you can comment out these provided
// tests.  They currently use grid.h and will segfault until you implement
// grid correctly.  


// Provided Test: sample maze from handout, make lots more yourself!
TEST(maze, basic) {
   vector<string> textMaze;

   textMaze.push_back("* *-W *");
   textMaze.push_back("| |   |");
   textMaze.push_back("*-* * *");
   textMaze.push_back("  | | |");
   textMaze.push_back("S *-*-*");
   textMaze.push_back("|   | |");
   textMaze.push_back("*-*-* P");

   Maze m(textMaze);

   MazeCell* start = m.getStart(2, 2);

   /* These paths are the ones in the handout. They all work. */
   EXPECT_TRUE(isPathToFreedom(start, "ESNWWNNEWSSESWWN"));
   EXPECT_TRUE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES"));
   EXPECT_TRUE(isPathToFreedom(start, "WNNEWSSESWWNSEENES"));

   /* These paths don't work, since they don't pick up all items. */
   EXPECT_FALSE(isPathToFreedom(start, "ESNW"));
   EXPECT_FALSE(isPathToFreedom(start, "SWWN"));
   EXPECT_FALSE(isPathToFreedom(start, "WNNE"));

   /* These paths don't work, since they aren't legal paths. */
   EXPECT_FALSE(isPathToFreedom(start, "WW"));
   EXPECT_FALSE(isPathToFreedom(start, "NN"));
   EXPECT_FALSE(isPathToFreedom(start, "EE"));
   EXPECT_FALSE(isPathToFreedom(start, "SS"));
}

// Provided Test: don't allow going through walls
TEST(maze, tryingToGoThroughWalls) {
   vector<string> textMaze;

   textMaze.push_back("* S *");
   textMaze.push_back("     ");
   textMaze.push_back("W * P");
   textMaze.push_back( "     ");
   textMaze.push_back( "* * *");

   Maze m(textMaze);

   MazeCell* start = m.getStart(1, 1);

   EXPECT_FALSE(isPathToFreedom(start, "WNEES"));
   EXPECT_FALSE(isPathToFreedom(start, "NWSEE"));
   EXPECT_FALSE(isPathToFreedom(start, "ENWWS"));
   EXPECT_FALSE(isPathToFreedom(start, "SWNNEES"));
}

// Provided Test: Works when starting on an item
TEST(maze, startOnItem) {
   vector<string> textMaze;

   textMaze.push_back("P-S-W");

   Maze m(textMaze);
   MazeCell* start = m.getStart(0, 0);

   EXPECT_TRUE(isPathToFreedom(start, "EE"));
   start = m.getStart(0, 1);
   EXPECT_TRUE(isPathToFreedom(start, "WEE"));
   start = m.getStart(0, 2);
   EXPECT_TRUE(isPathToFreedom(start, "WW"));

}

// Provided Test: Reports errors if given illegal characters.
TEST(maze, invalidChar) {
   vector<string> textMaze;

   textMaze.push_back("* *-W *");
   textMaze.push_back("| |   |");
   textMaze.push_back("*-* * *");
   textMaze.push_back("  | | |");
   textMaze.push_back("S *-*-*");
   textMaze.push_back("|   | |");
   textMaze.push_back("*-*-* P");

   Maze m(textMaze);
   MazeCell* start = m.getStart(0, 0);

   /* These paths contain characters that aren't even close to permissible. */
   EXPECT_FALSE(isPathToFreedom(start, "Q"));
   EXPECT_FALSE(isPathToFreedom(start, "X"));
   EXPECT_FALSE(isPathToFreedom(start, "!"));
   EXPECT_FALSE(isPathToFreedom(start, "?"));

   EXPECT_FALSE(isPathToFreedom(start, "n"));
   EXPECT_FALSE(isPathToFreedom(start, "s"));
   EXPECT_FALSE(isPathToFreedom(start, "e"));
   EXPECT_FALSE(isPathToFreedom(start, "w"));

   ///* These are tricky - they're legal paths that happen to have an unexpected
   // * character at the end.
   start = m.getStart(2, 2);
   EXPECT_FALSE(isPathToFreedom(start, "ESNWWNNEWSSESWWNQ"));
   EXPECT_FALSE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES!!!"));
   EXPECT_FALSE(isPathToFreedom(start, "WNNEWSSESWWNSEENES??"));

}

// Provided Test: This tests your personalized regular maze to see if you were
// able to escape.
TEST(maze, escapeRegularMaze) {
   Maze m(4, 4);
   MazeCell* start = m.mazeFor(kYourName);
   EXPECT_TRUE(isPathToFreedom(start, kPathOutOfRegularMaze));
}

// Provided Test: This tests your personalized twisty maze to see if you were
// able to escape.
TEST(maze, escapeTwistyMaze) {
   Maze m(4, 4);
   MazeCell* start = m.twistyMazeFor(kYourName);
   EXPECT_TRUE(isPathToFreedom(start, kPathOutOfTwistyMaze));
}

