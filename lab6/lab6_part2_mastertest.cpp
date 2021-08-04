// lab6_mastertest.cpp
// Tests for Part 2:  DLL_node and List (CDLL with sentinel node)
//
// Barb Wahl, 2-23-16
// Revised 3-5-17

// NOTE:  Execution of student code will still be halted by fatal errors such
// as segmentation faults and infinite loops.  Make use of the methods
// `segFault` and `infiniteLoop` in these situations.

// NOTE:  As much as possible, use only *basic* functionality in implementing
// testing code.

// NOTE:  Since the testing code is implemented using the student's
// implementations for basic functionality, any problems in basic functionality
// must be "patched" by the instructor (after recording the relevant info)
// before re-running the tests.  Save the altered code as, for example,
// stdt_code_patched.cpp, then re-compile to evaluate non-basic functionality.

// ========================= Testing Boilerplate =========================
#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include "node1.h"
#include "Person.h"
#include "DLL_node.h"
#include "List.h"

using namespace std;
using namespace main_savitch_5;
using namespace lab6_part2;

// for testing exceptions -- not used for this lab
extern string EXC_OUT_OF_BOUNDS;
extern string EXC_LIST_NOT_ORDERED;

// for tabulating summary of results
const string err = "";
int tests_passed = 0;
int tests_failed = 0;
int segmentation_faults = 0;
int infinite_loops = 0;

// print method
// prints the given string plus endl
void print(string str) {
    cout << str << endl;
}

// segFault method
// When student code creates a segmentation fault, comment out the corresponding
// test call in main and *insert* a call to segFault.
// Use the parameter `desc` to indicate the failing test.
// Result:  prints an appropriate message; increments tests_failed counter and
// segmentation_faults counter.
void segFault(string desc) {
    print("### TEST FAILED ###: " + desc + "; segmentation fault");
    tests_failed++;
    segmentation_faults++;
}

// infiniteLoop method
// When student code creates an infinite loop, comment out the corresponding
// test call in main and *insert* a call to infiniteLoop.
// Use the parameter `desc` to indicate the failing test.
// Result:  prints an appropriate message; increments tests_failed counter and
// infinite_loops counter.
void infiniteLoop(string desc) {
    print("### TEST FAILED ###: " + desc + "; infinite loop");
    tests_failed++;
    infinite_loops++;
}

// itFailedToThrowCorrectException method
// input: string desc, describes the test which was run
void itFailedToThrowCorrectException(string desc) {
    print("### TEST FAILED ###: " + desc + "; threw non-string exeception");
    tests_failed++;
}

// itFailed method
// ## always call this method when a test fails, except when the code under
// test threw the *wrong* exception -- see `itFailedToThrowCorrectException` ##
// prints message for failed test
// increments the count of failed tests
void itFailed(string str) {
    print("### TEST FAILED ###: " + str);
    tests_failed++;
}

// itPassed method
// ## always call this method when a test passes ##
// prints message for passed test
// increments the count of passed tests
void itPassed(string str) {
    print("TEST PASSED: " + str);
    tests_passed++;
}

// stripSpaceAndMakeLowerCase function
// input:  string s
// output: string
//
// makes a copy of string s, strips ' ' and '\n' from
// the copy, and changes all remaining chars to lower case
//
// returns this altered copy of the string
//
// leaves the original string s unchanged
string stripSpacesAndMakeLowerCase(string s)
{
    string str = s;
    for (unsigned int i = 0; i < str.length(); i++)
    {
      if (str[i] == ' ' || str[i] == '\n') {
         str.erase(i, 1);
         i--;
      } else { str[i] = tolower(str[i]); }
    }
    return str;
}

// laxString method
// use for comparing strings generated by stream output (<<)
// ignores whitespace, including newlines
// return:  true iff s1 and s2 are equivalent after ignoring whitespace
bool laxString(string s1, string s2)
{
    string x = stripSpacesAndMakeLowerCase(s1);
    string y = stripSpacesAndMakeLowerCase(s2);
    return x == y;
}

// ========================= Tests =========================

// create some global Person objects to use in tests
Person default_person;
Person Mickey_Mouse("Mickey", "Mouse", 45);
Person Minnie_Mouse("Minnie", "Mouse", 45);
Person Peter_Pan("Peter", "Pan", 100);
Person Ziggy_Wilson("Ziggy", "Wilson", 5);
Person Skye_Wilson("Skye", "Wilson", 4);
Person Peter_Piper("Peter", "Piper", 0);
Person Dopey_Dwarf("Dopey", "Dwarf", 73);
Person Sleepy_Dwarf("Dopey", "Dwarf", 73);
Person Happy_Dwarf("Dopey", "Dwarf", 73);
Person Sneezy_Dwarf("Sneezy", "Dwarf", 48);
Person Snow_White("Snow", "White", 21);

// an array of 10 persons
Person personArray[] =
    {Skye_Wilson, Dopey_Dwarf, Happy_Dwarf, Sneezy_Dwarf, Snow_White,
     Mickey_Mouse, Minnie_Mouse, Peter_Piper, Peter_Pan, Ziggy_Wilson};

Person p0("Skye", "Wilson", 4);
Person p1("Dopey", "Dwarf", 10);
Person p2("Happy", "Dwarf", 25);
Person p3("Sneezy", "Dwarf", 48);
Person p4("Snow", "White", 21);

// an array of 5 persons
Person personArray2[] = {p0, p1, p2, p3, p4};

/**************** Part Two Tests ***********************/

void test_node_functions()  // provided to students!
{
    string desc = "test node functions -- provided to students";
    try
    {
      // 0, 1, 2, and 3-arg constructor calls
      DLL_node n0;
      Person defPerson;
      if (n0.data() != defPerson) {throw err;}
      if (n0.prev() != NULL){throw err;}
      if (n0.next() != NULL){throw err;}

      DLL_node * ptr_n0 = &n0;
      DLL_node n1(p1);
      if (n1.data() != p1){throw err;}
      if (n1.prev() != NULL){throw err;}
      if (n1.next() != NULL){throw err;}

      DLL_node * ptr_n1 = &n1;
      DLL_node n2(p2, ptr_n1);
      if (n2.data() != p2){throw err;}
      if (n2.prev() != ptr_n1){throw err;}
      if (n2.next() != NULL){throw err;}

      DLL_node * ptr_n2 = &n2;
      DLL_node n3(p3, ptr_n2, ptr_n0);
      if (n3.data() != p3){throw err;}
      if (n3.prev() != ptr_n2){throw err;}
      if (n3.next() != ptr_n0){throw err;}

      // try set_data, set_prev, set_next
      n0.set_data(p3);
      if (n0.data() != p3){throw err;}
      n1.set_prev(ptr_n0);
      if (n1.prev() != ptr_n0){throw err;}
      n1.set_next(ptr_n2);
      if (n1.next() != ptr_n2){throw err;}

      // test the const versions of prev(), next()
      n0.set_data(p0);
      DLL_node n4(p4);
      DLL_node * ptr_n4 = &n4;
      const DLL_node c_happy(p2, ptr_n0, ptr_n1);
      if (c_happy.prev() -> data() != p0){throw err;}
      if (c_happy.next() -> data() != p1){throw err;}
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}


/*
   Basic functions:
      default constructor
      is_empty
      clear
      front
      back
      head_insert
      tail_insert
*/

void test_list_basic_functions_1()
{
    string desc = "default constructor makes an empty list";
    try {
      List l1;

      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_basic_functions_2()
{
    string desc = "head_insert, is_empty, front, back";
    try {
      List l1;
      l1.head_insert(Ziggy_Wilson);
      if (l1.is_empty()){ throw err; }
      if (l1.front() != Ziggy_Wilson){ throw err; }
      if (l1.back() != Ziggy_Wilson){ throw err; }
      l1.head_insert(p0);
      if (l1.is_empty()){ throw err; }
      if (l1.front() != p0){ throw err; }
      if (l1.back() != Ziggy_Wilson){ throw err; }
      l1.head_insert(p1);
      if (l1.is_empty()){ throw err; }
      if (l1.front() != p1){ throw err; }
      if (l1.back() != Ziggy_Wilson){ throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_basic_functions_3()
{
    string desc = "tail_insert, is_empty, front, back";
    try {
      List l1;
      l1.tail_insert(Ziggy_Wilson);
      if (l1.is_empty()){ throw err; }
      if (l1.front() != Ziggy_Wilson){ throw err; }
      if (l1.back() != Ziggy_Wilson){ throw err; }
      l1.tail_insert(p0);
      if (l1.is_empty()){ throw err; }
      if (l1.back() != p0){ throw err; }
      if (l1.front() != Ziggy_Wilson){ throw err; }
      l1.tail_insert(p1);
      if (l1.is_empty()){ throw err; }
      if (l1.front() != Ziggy_Wilson){ throw err; }
      if (l1.back() != p1){ throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_basic_functions_4()
{
    string desc = "clear an empty list";
    try {
      List l1;
      l1.clear();
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_basic_functions_5()
{
    string desc = "clear a non-empty list";
    try {
      List l1;
      l1.head_insert(p0);
      l1.clear();
      if (!l1.is_empty()) { throw err; }
      l1.head_insert(p0);
      l1.head_insert(p0);
      l1.head_insert(p0);
      l1.clear();
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}
// head_remove
// remove an item from the front of the list
// Postcondition:  Return value is `true` iff an item was removed.
//    If the list was empty before head_remove(), return value is
//    `false`.
// EXAMPLE:  If the list had items A, B, C before the call to
//    head_remove(), after the call the list has: B, C
void test_head_remove_1()
{
    string desc = "head_remove from empty list, return = false";
    try {
      List l1;
      bool removed = l1.head_remove();
      if (removed) { throw err; }
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_head_remove_2()
{
    string desc = "head_remove from list of length 1, return = true";
    try {
      List l1;
      l1.head_insert(p0);
      bool removed = l1.head_remove();
      if (!removed) { throw err; }
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_head_remove_3()
{
    string desc = "head_remove from list of length 5, return = true";
    try {
      List l1;
      for (int i = 0; i < 5; i++)
      {
         l1.tail_insert(personArray[i]);
      }
      bool removed = l1.head_remove();
      if (!removed) { throw err; }
      for (int i = 1; i < 5; i++)
      {
         if (l1.front() != personArray[i]) { throw err; }
         l1.head_remove();
      }
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_tail_remove_1()
{
    string desc = "tail_remove from empty list, return = false";
    try {
      List l1;
      bool removed = l1.tail_remove();
      if (removed) { throw err; }
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_tail_remove_2()
{
    string desc = "tail_remove from list of length 1, return = true";
    try {
      List l1;
      l1.head_insert(p0);
      bool removed = l1.tail_remove();
      if (!removed) { throw err; }
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_tail_remove_3()
{
    string desc = "tail_remove from list of length 5, return = true";
    try {
      List l1;
      for (int i = 0; i < 5; i++)
      {
         l1.head_insert(personArray[i]);
      }
      // l1 = (pa4, pa3, pa2, pa1, pa0)
      bool removed = l1.tail_remove();
      if (!removed) { throw err; }
      for (int i = 1; i < 5; i++)
      {
         if (l1.back() != personArray[i]) { throw err; }
         l1.tail_remove();
      }
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}
// contains
// checks for an item in the list
// Postcondition: Returns true iff there is an item equivalent to
//    `val` in this list.
void test_contains_1()
{
    string desc = "contains == false, empty list";
    try {
      List l1;
      if (l1.contains(personArray[0])) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_contains_2()
{
    string desc = "contains == false, list of length 5";
    try {
      List l1;
      for (int i = 0; i < 5; i++)
      {
         l1.head_insert(personArray[i]);
      }
      if (l1.contains(Ziggy_Wilson)) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_contains_3()
{
    string desc = "contains == true, success at front";
    try {
      List l1;
      for (int i = 0; i < 5; i++)
      {
         l1.head_insert(personArray[i]);
      }
      if (!l1.contains(personArray[4])) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_contains_4()
{
    string desc = "contains == true, success in middle";
    try {
      List l1;
      for (int i = 0; i < 5; i++)
      {
         l1.head_insert(personArray[i]);
      }
      if (!l1.contains(personArray[2])) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_contains_5()
{
    string desc = "contains == true, success at back";
    try {
      List l1;
      for (int i = 0; i < 5; i++)
      {
         l1.head_insert(personArray[i]);
      }
      if (!l1.contains(personArray[0])) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}
// remove_first_of
// tries to remove the first instance of an item from the list
// Postcondition: Removes the front-most item in the list that is
//    equivalent (==) to the given value `val`.  Return value is
//    true iff an item was removed from the list.
// NOTE: If no item in the list is equivalent to `val`, the list
//    is unchanged and `false` is returned.
// EXAMPLE: The list has items: A, B, C, B, X.  A call to
//    remove_first_of('B') will return true, and the list items
//    are now: A, C, B, X.
void test_remove_first_of_1()
{
    string desc = "remove_first_of: unsuccessful, length 0";
    try {
      List l0;
      if (l0.remove_first_of(Mickey_Mouse)) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_remove_first_of_2()
{
    string desc = "remove_first_of: unsuccessful, length 1";
    try {
      List l0;
      l0.head_insert(Minnie_Mouse);
      if (l0.remove_first_of(Mickey_Mouse)) { throw err; }
      if (l0.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}
void test_remove_first_of_3()
{
    string desc = "remove_first_of: unsuccessful, length 5";
    try {
      List l0;
      for (int i = 0; i < 5; i++)
      {
         l0.tail_insert(personArray[i]);
      }
      // l0 = (pa0, pa1, pa2, pa3, pa4)
      if (l0.remove_first_of(personArray[5])) { throw err; }

      // check that l0 was not changed
      for (int i = 0; i < 5; i++)
      {
         if (l0.front() != personArray[i]) { throw err; }
         l0.head_remove();
      }
      if (!l0.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_remove_first_of_4()
{
    string desc = "remove_first_of: successful, length 1";
    try {
      List l1;
      l1.head_insert(Ziggy_Wilson);
      if (!l1.remove_first_of(Ziggy_Wilson)) { throw err; }
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_remove_first_of_5()
{
    string desc = "remove_first_of: successful, length 5, found at front";
    try {
      List l1;
      bool removed;

      l1.head_insert(Ziggy_Wilson);
      l1.head_insert(Minnie_Mouse);
      l1.tail_insert(Mickey_Mouse);
      l1.tail_insert(Mickey_Mouse);
      l1.tail_insert(Minnie_Mouse);
      // l1 = (Minnie, Ziggy, Mickey, Mickey, Minnie)

      removed = l1.remove_first_of(Minnie_Mouse);
      if (!removed) { throw err; }
      if (l1.front() != Ziggy_Wilson) { throw err; }
      l1.head_remove();
      if (l1.front() != Mickey_Mouse) { throw err; }
      l1.head_remove();
      if (l1.front() != Mickey_Mouse) { throw err; }
      l1.head_remove();
      if (l1.front() != Minnie_Mouse) { throw err; }
      l1.head_remove();
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_remove_first_of_6()
{
    string desc = "remove_first_of: successful, length 5, found at middle";
    try {
      List l1;
      bool removed;

      l1.head_insert(Ziggy_Wilson);
      l1.head_insert(Minnie_Mouse);
      l1.tail_insert(Mickey_Mouse);
      l1.tail_insert(Mickey_Mouse);
      l1.tail_insert(Minnie_Mouse);
      // l1 = (Minnie, Ziggy, Mickey, Mickey, Minnie)

      removed = l1.remove_first_of(Mickey_Mouse);
      if (!removed) { throw err; }
      if (l1.front() != Minnie_Mouse) { throw err; }
      l1.head_remove();
      if (l1.front() != Ziggy_Wilson) { throw err; }
      l1.head_remove();
      if (l1.front() != Mickey_Mouse) { throw err; }
      l1.head_remove();
      if (l1.front() != Minnie_Mouse) { throw err; }
      l1.head_remove();
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_remove_first_of_7()
{
    string desc = "remove_first_of: successful, length 5, found at back";
    try {
      List l1;
      bool removed;

      l1.head_insert(Ziggy_Wilson);
      l1.head_insert(Minnie_Mouse);
      l1.tail_insert(Mickey_Mouse);
      l1.tail_insert(Mickey_Mouse);
      l1.tail_insert(Skye_Wilson);
      // l1 = (Minnie, Ziggy, Mickey, Mickey, Skye)

      removed = l1.remove_first_of(Skye_Wilson);
      if (!removed) { throw err; }
      if (l1.front() != Minnie_Mouse) { throw err; }
      l1.head_remove();
      if (l1.front() != Ziggy_Wilson) { throw err; }
      l1.head_remove();
      if (l1.front() != Mickey_Mouse) { throw err; }
      l1.head_remove();
      if (l1.front() != Mickey_Mouse) { throw err; }
      l1.head_remove();
      if (!l1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_assignment_1()
{
    string desc = "assignment: assign length 0 to length 2";
    try {
      List l0;  // length 0
      List l2;  // length 2
      l2.tail_insert(personArray[0]);
      l2.tail_insert(personArray[1]);
      l2 = l0;
      if (!l2.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_assignment_2()
{
    string desc = "assignment: assign length 2 to length 4";
    try {
      List l2, l4;
      // list length 2
      l2.tail_insert(Mickey_Mouse);
      l2.tail_insert(Minnie_Mouse);

      // list length 4
      l4.tail_insert(personArray[0]);
      l4.tail_insert(personArray[1]);
      l4.tail_insert(personArray[2]);
      l4.tail_insert(personArray[3]);

      l4 = l2;
      if (l4.front() != Mickey_Mouse) { throw err; }
      if (l4.back() != Minnie_Mouse) { throw err; }
      l4.head_remove(); l4.head_remove();
      if (!l4.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_assignment_3()
{
    string desc = "assignment: assign length 5 to length 2";
    try {
      List l5, l2;
      for (int i = 0; i < 5; i++)
      {
         l5.head_insert(personArray[i]);
      }
      l2.tail_insert(Mickey_Mouse);
      l2.tail_insert(Minnie_Mouse);
      l2 = l5;
      if ( l2.contains(Mickey_Mouse) ) { throw err; }
      if ( l2.contains(Minnie_Mouse) ) { throw err; }
      for (int i = 0; i < 5; i++)
      {
         if (l2.front() != personArray[4 - i]) { throw err; }
         l2.head_remove();
      }
      if (!l2.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_assignment_4()
{
    string desc = "assignment: self-assignment test";
    try {
      List l5;
      for (int i = 0; i < 5; i++)
      {
         l5.tail_insert(personArray[i]);
      }
      l5 = l5;
      if (l5.is_empty()) { throw err; }
      for (int i = 0; i < 5; i++)
      {
         if (l5.front() != personArray[i]) { throw err; }
         l5.head_remove();
      }
      if (!l5.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_assignment_5()
{
    string desc = "assignment chaining";
    try {
      List l1, l2, l3;
      for (int i = 0; i < 3; i++)   // make two different 3-person lists
      {
         l1.tail_insert(personArray[i]);
         l2.tail_insert(personArray[i + 2]);
      }
      // put a 4th node on the end of l1:
      l1.tail_insert(personArray[3]);

      // activate chaining -- l3 and l1 become clones of l2
      l3 = l1 = l2;

      if (l3.front() != l2.front()) { throw err; }
      if (l1.front() != l2.front()) { throw err; }
      l1.head_remove();
      l2.head_remove();
      l3.head_remove();

      if (l3.front() != l2.front()) { throw err; }
      if (l1.front() != l2.front()) { throw err; }
      l1.head_remove();
      l2.head_remove();
      l3.head_remove();

      if (l3.front() != l2.front()) { throw err; }
      if (l1.front() != l2.front()) { throw err; }
      l1.head_remove();
      l2.head_remove();
      l3.head_remove();

      if (!l1.is_empty()) { throw err; }
      if (!l3.is_empty()) { throw err; }

      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_copy_constructor_1()
{
    string desc = "copy constructor: length 0";
    try {
      List l0;
      List copy0(l0);
      if (!copy0.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_copy_constructor_2()
{
    string desc = "copy constructor: length 1";
    try {
      List l1;
      l1.head_insert(Mickey_Mouse);
      List copy1(l1);
      if (copy1.front() != Mickey_Mouse) { throw err; }
      copy1.head_remove();
      if (!copy1.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_copy_constructor_3()
{
    string desc = "copy constructor: length 5";
    try {
      List l5;
      for (int i = 0; i < 5; i++)
      {
         l5.tail_insert(personArray[i]);
      }
      List copy5(l5);
      for (int i = 0; i < 5; i++)
      {
         if (copy5.front() != personArray[i])
         {
            throw err;
         }
         copy5.head_remove();
      }
      if (!copy5.is_empty()) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

// EXTRA CREDIT
// operator[]
// Postcondition: If myList is a list with more than i elements, then
//    myList[i] returns the ith item in myList (indexing starts at 0).
// EXAMPLE: If myList has items A, B, C, D, then myList[0] returns 'A'
//    and myList[2] returns 'C'.
void test_bracket_operator()
{
    string desc = "bracket operator (extra credit)";
    try {
      List l1;
      l1.tail_insert(Mickey_Mouse);
      if (l1[0] != Mickey_Mouse) { throw err; }
      l1.tail_insert(Ziggy_Wilson);
      if (l1[1] != Ziggy_Wilson) { throw err; }
      l1.tail_insert(Sleepy_Dwarf);
      l1.tail_insert(Happy_Dwarf);
      if (l1[0] != Mickey_Mouse) { throw err; }
      if (l1[1] != Ziggy_Wilson) { throw err; }
      if (l1[2] != Sleepy_Dwarf) { throw err; }
      if (l1[3] != Happy_Dwarf) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

int main() {
    print("\ntests for Lab 6 Part 2 -- DLL_node; List (CDLL w/SN) ...");

    // DLL_node implementation was provided -- just put tests into 1 function
    test_node_functions();

    // basic functions:  constructor, head_insert, tail_insert, front, back
    test_list_basic_functions_1();
    test_list_basic_functions_2();
    test_list_basic_functions_3();
    test_list_basic_functions_4();
    test_list_basic_functions_5();
    test_head_remove_1();
    test_head_remove_2();
    test_head_remove_3();
    test_tail_remove_1();
    test_tail_remove_2();
    test_tail_remove_3();
    test_contains_1();
    test_contains_2();
    test_contains_3();
    test_contains_4();
    test_contains_5();
    test_remove_first_of_1();
    test_remove_first_of_2();
    test_remove_first_of_3();
    test_remove_first_of_4();
    test_remove_first_of_5();
    test_remove_first_of_6();
    test_remove_first_of_7();
    test_assignment_1();
    test_assignment_2();
    test_assignment_3();
    test_assignment_4();
    // segFault("test assignment chaining");
    test_assignment_5();
    test_copy_constructor_1();
    test_copy_constructor_2();
    test_copy_constructor_3();
    test_bracket_operator();  // extra credit

    // ======================== SUMMARY INFORMATION ====================== //
    int num_tests = tests_passed + tests_failed;
    double passed = (double) tests_passed;
    double total = (double) num_tests;
    cout << "\nNumber of segmentation faults encountered during testing = "
        << segmentation_faults << endl;
    cout << "Number of infinite loops encountered during testing = "
        << infinite_loops << endl;
    cout << "Number of tests passed = " << tests_passed << " out of "
        << num_tests << endl;
    cout << "Number of tests failed = " << tests_failed << " out of "
        << num_tests << endl;
    cout << "Percent of tests passed = " << (100 * passed / total)
        << "%" << endl << endl;

    return 0;
}
