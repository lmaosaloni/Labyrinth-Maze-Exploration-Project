// grid.h
// 
// This header file introduces the Grid<T> class, tailored for the creation and manipulation of 2D grids. 
// Such an abstraction is crucial for the development and evaluation of mazes and labyrinth escape algorithms.
// Each grid is characterized by its dimensions in terms of rows and columns, with all elements initially set to 
// the default value specified by C++ (typically a 4x4 grid).



#pragma once

#include <iostream>

#include <exception>

#include <stdexcept>

#include <algorithm>

using namespace std;

template < typename T >
  class Grid {
    private:
      struct CELL {
        CELL * Next;
        T Val;
        size_t NumCols; // total # of columns (0..NumCols-1)
        CELL(CELL * _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
          Next = _Next;
          Val = _Val;
          NumCols = _NumCols;
        }
      };

    size_t NumRows; // total # of rows (0..NumRows-1)
    CELL ** Rows; // C array of linked lists
    public:
      //
      // default constructor:
      //
      // Called automatically by C++ to construct a 4x4 Grid.  All
      // elements are initialized to the default value of T.
      //
      Grid() {
        // initialize 4 rows
        Rows = new CELL * [4];
        NumRows = 4;

        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
          Rows[r] = new CELL(nullptr, T(), 4);
          CELL * cur = Rows[r];

          // create the linked list for this row.
          for (size_t c = 1; c < Rows[r] -> NumCols; ++c) {
            cur -> Next = new CELL(nullptr, T());
            cur = cur -> Next;
          }
        }

      }

    //
    // parameterized constructor:
    //
    // Called automatically by C++ to construct a Grid with R rows,
    // where each row has C columns. All elements are initialized to 
    // the default value of T.
    //
    Grid(size_t R, size_t C) {

      // TO DO:  Write this parameterized constructor.
      // initialize 4 rows
      Rows = new CELL * [R];
      NumRows = R;

      // modified from default constructor to account for number of specific columns.
      for (size_t r = 0; r < NumRows; ++r) {
        Rows[r] = new CELL(nullptr, T(), C);
        CELL * cur = Rows[r];

        // this for loop is the same default
        for (size_t c = 1; c < Rows[r] -> NumCols; ++c) {
          cur -> Next = new CELL(nullptr, T());
          cur = cur -> Next;
        }
      }
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the vector.
    //
    virtual~Grid() {

      CELL * cur;
      CELL * prev;

      for (int i = 0; i < NumRows; ++i) { // loop thorugh the array
        cur = Rows[i]; // following each linked list’s path
        prev = nullptr;
        while (cur != nullptr) { // while traversing, deleting the cell last visited
          prev = cur;
          cur = cur -> Next;
          delete prev;
        } // traversing example from jumpstart, linked-list slide
      }
      delete[] Rows; // all done and deleteing the array completely
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to construct a Grid that contains a
    // copy of an existing Grid.  Example: this occurs when passing
    // Grid as a parameter by value
    //
    //   void somefunction(Grid<int> G2)  <--- G2 is a copy:
    //   { ... }
    //
    Grid(const Grid < T > & other) {

      Rows = new CELL * [other.NumRows];
      NumRows = other.NumRows;

      for (size_t r = 0; r < NumRows; ++r) {
        Rows[r] = new CELL(nullptr, other.Rows[r] -> Val, other.Rows[r] -> NumCols);
        CELL * cur = Rows[r];
        CELL * cur2 = other.Rows[r];
        cur2 = cur2 -> Next;

        for (size_t c = 1; c < Rows[r] -> NumCols; ++c) {
          cur -> Next = new CELL(nullptr, cur2 -> Val);
          cur = cur -> Next;
          cur2 = cur2 -> Next;
        }
      }
    }

    //
    // copy operator=
    //
    // Called when you assign one vector into another, i.e. this = other;
    //
    Grid & operator = (const Grid & other) {
      Grid < T > temp;
      CELL * cur;
      CELL * prev;
      // resetting array, deallocating everything (linked lists & array)
      for (int i = 0; i < NumRows; ++i) {
        cur = Rows[i]; // copy number of rows
        prev = nullptr;

        while (cur != nullptr) {
          prev = cur;
          cur = cur -> Next;
          delete prev;
        }
      }

      delete[] Rows;
      Rows = new CELL * [other.NumRows]; // new array with new size
      NumRows = other.NumRows;

      for (size_t r = 0; r < NumRows; ++r) {
        Rows[r] = new CELL(nullptr, other.Rows[r] -> Val, other.Rows[r] -> NumCols); // new cell for the head pointer
        CELL * cur = Rows[r]; // 2 pointers to traverse both lists
        CELL * cur2 = other.Rows[r]; // loop through curr2 list
        cur2 = cur2 -> Next;

        for (size_t c = 1; c < Rows[r] -> NumCols; ++c) { // making a new cell, copying the values NumCols and Val
          cur -> Next = new CELL(nullptr, cur2 -> Val);
          cur = cur -> Next;
          cur2 = cur2 -> Next; // repeating till cur2's Next field is null
        }
      }
      return *this;
    }

    //
    // numrows
    //
    // Returns the # of rows in the Grid.  The indices for these rows
    // are 0..numrows-1.
    //
    size_t numrows() const {

      return NumRows;
    }

    //
    // numcols
    //
    // Returns the # of columns in row r.  The indices for these columns
    // are 0..numcols-1.  For now, each row will have the same number of columns.
    //
    size_t numcols(size_t r) const {

      return Rows[r] -> NumCols;

    }

    //
    // size
    //
    // Returns the total # of elements in the grid.
    //
    size_t size() const {

      return (NumRows * Rows[0] -> NumCols); // using index of 0 because it's always a set position
    }

    //
    // ()
    //
    // Returns a reference to the element at location (r, c); this
    // allows you to access the element or change it:
    //
    //    grid(r, c) = ...
    //    cout << grid(r, c) << endl;
    //
    T & operator()(size_t r, size_t c) {
      // inavlid inputs of rows or columns
      if (r < 0) {
        throw runtime_error("**ERROR**: rows/columns doesn't exist");
      } else if (c < 0) {
        throw runtime_error("**ERROR**: rows/columns doesn't exist");
      } else if (r >= NumRows) {
        throw runtime_error("**ERROR**: rows/columns doesn't exist");
      } else if (c >= Rows[r] -> NumCols) {
        throw runtime_error("**ERROR**: rows/columns doesn't exist");
      }

      CELL * cur = Rows[r];
      int temp = 0;

      while (cur != nullptr) {
        if (temp == c) { // loop till you hit actual c value
          return cur -> Val;
        }
        temp += 1;
        cur = cur -> Next;
      }

      return cur -> Val;
    }

    //
    // _output
    //
    // Outputs the contents of the grid; for debugging purposes.  This is not
    // tested.
    //
    void _output() {

    }

  }; // styled using C++ beautifier to pass style points