// lab6_mastertest.cpp
// Tests for
//       - Part 1:  node1 and list toolkit functions (Main/Savitch ch.5)
//       - Part 2:  DLL_node and List (CDLL with sentinel node)
//
// Barb Wahl, 2-23-16

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

using namespace std;
using namespace main_savitch_5;

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

Person personArray2[] = {p0, p1, p2, p3, p4};

// PART ONE TESTS:  node1 class; list toolkit functions

void test_node_1() {
    string desc = "node default constructor";
    try {
      node n0;
      if (n0.data() != default_person) { throw err; }
      if (n0.link() != NULL) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_node_2() {
    string desc = "node constructor 1 arg";
    try {
      node n1(Mickey_Mouse);
      if (n1.data() != Mickey_Mouse) { throw err; }
      if (n1.link() != NULL) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_node_3() {
    string desc = "node constructor 2 arg";
    try {
      node n0;
      node n1(Mickey_Mouse);
      node n2(Ziggy_Wilson, &n1);
      if (n2.link() != &n1) { throw err; }
      if (n2.link() -> data() != Mickey_Mouse) { throw err; }
      if (n2.data() != Ziggy_Wilson) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_node_4() {
    string desc = "set_data and set_link";
    try {
      node n0;
      node n1(Mickey_Mouse);
      node n2(Ziggy_Wilson, &n1);
      n2.set_data(Skye_Wilson);
      if (n2.data() != Skye_Wilson) { throw err; }
      n1.set_link(&n0);  // n2 -> n1 -> n0
      if (n1.link() != &n0) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_node_5() {
    string desc = "const version of `link()`";
    try {
      node ziggy(Ziggy_Wilson);
      node * zig_ptr = &ziggy;
      // a const node for testing const link()
      const node c_skye(Skye_Wilson, zig_ptr);
      // c_skye -> ziggy
      if (c_skye.link() -> data() != Ziggy_Wilson) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_length_and_head_insert_1() {
    string desc = "list_length, list_head_insert -- empty list";
    try {
      node * hd = NULL;
      node::value_type val1 = Peter_Pan;
      if (list_length(hd) != 0) { throw err; }

      hd = list_head_insert(hd, val1);
      if (list_length(hd) != 1) { throw err; }
      if (hd -> data() != val1) { throw err; }
      if (hd -> link() != NULL) { throw err; }
      itPassed(desc);

      // Clean up memory
      delete hd;
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_length_and_head_insert_2() {
    string desc = "list_length, list_head_insert -- nonempty list";
    try {
      node * hd = NULL;
      node::value_type val1 = Peter_Pan;
      node::value_type val2 = Peter_Piper;
      hd = list_head_insert(hd, val1);
      hd = list_head_insert(hd, val2);

      if (list_length(hd) != 2) { throw err; }
      node * curr = hd;
      if (curr -> data() != val2) { throw err; }
      curr = curr -> link();
      if (curr -> data() != val1) { throw err; }
      itPassed(desc);

      // Clean up memory
      delete hd -> link();
      delete hd;
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_length_and_head_insert_3() {
    string desc = "list_length, list_head_insert -- long list";
    try {
      node * hd = NULL;
      node::value_type val1 = Peter_Pan;
      node::value_type val2 = Peter_Piper;
      for (int i = 0; i < 999; i++){
        hd = list_head_insert(hd, val1);
      }
      hd = list_head_insert(hd, val2);

      if (list_length(hd) != 1000) { throw err; }
      node * curr = hd;
      if (curr -> data() != val2) { throw err; }
      curr = curr -> link();
      if (curr -> data() != val1) { throw err; }
      itPassed(desc);

      // Clean up memory
      for (int i = 0; i < 1000; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_insert_1() {
    string desc = "list_insert -- at tail";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Mickey_Mouse);
      if (list_length(hd) != 1) { throw err; }
      list_insert(hd, Minnie_Mouse);
      if (list_length(hd) != 2) { throw err; }
      list_insert(hd -> link(), Ziggy_Wilson);
      if (list_length(hd) != 3) { throw err; }
      itPassed(desc);

      // Clean up memory
      delete hd -> link() -> link();
      delete hd -> link();
      delete hd;
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_insert_2() {
    string desc = "list_insert -- position 2 or 3 in longer list";
    // Person default_person;
    // Person Mickey_Mouse("Mickey", "Mouse", 45);
    // Person Minnie_Mouse("Minnie", "Mouse", 45);
    // Person Peter_Pan("Peter", "Pan", 100);
    // Person Ziggy_Wilson("Ziggy", "Wilson", 5);
    // Person Skye_Wilson("Skye", "Wilson", 4);
    // Person Peter_Piper("Peter", "Piper", 0);
    // Person Dopey_Dwarf("Dopey", "Dwarf", 73);
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Peter_Pan);
      hd = list_head_insert(hd, Ziggy_Wilson);
      // position 2 has prev = hd
      list_insert(hd, Dopey_Dwarf);
      if (list_length(hd) != 5) { throw err; }
      // position 3 has prev = hd -> link()
      list_insert(hd -> link(), Skye_Wilson);
      if (list_length(hd) != 6) { throw err; }

      // iterate through the list and check the data
      node * curr = hd;
      if (curr -> data() != Ziggy_Wilson) { throw err; }
      curr = curr -> link();
      if (curr -> data() != Dopey_Dwarf) { throw err; }
      curr = curr -> link();
      if (curr -> data() != Skye_Wilson) { throw err; }
      curr = curr -> link();
      if (curr -> data() != Peter_Pan) { throw err; }
      curr = curr -> link();
      if (curr -> data() != Minnie_Mouse) { throw err; }
      curr = curr -> link();
      if (curr -> data() != Mickey_Mouse) { throw err; }
      if (curr -> link() != NULL) { throw err; }
      itPassed(desc);

      // Clean up memory
      for (int i = 0; i < 6; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_insert_3() {
    string desc = "list_insert -- position n-1 in longer list";
    // Person default_person;
    // Person Mickey_Mouse("Mickey", "Mouse", 45);
    // Person Minnie_Mouse("Minnie", "Mouse", 45);
    // Person Peter_Pan("Peter", "Pan", 100);
    // Person Ziggy_Wilson("Ziggy", "Wilson", 5);
    // Person Skye_Wilson("Skye", "Wilson", 4);
    // Person Peter_Piper("Peter", "Piper", 0);
    // Person Dopey_Dwarf("Dopey", "Dwarf", 73);
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Peter_Pan);
      hd = list_head_insert(hd, Ziggy_Wilson);
      // position 2 has prev = hd
      list_insert(hd, Dopey_Dwarf);
      // position 3 has prev = hd -> link()
      list_insert(hd -> link(), Skye_Wilson);

      // iterate through the list and check the data
      node * curr = hd;
      curr = curr -> link();
      curr = curr -> link();
      curr = curr -> link();
      curr = curr -> link();
      list_insert(curr, Peter_Piper);
      curr = curr -> link();
      if (curr -> data() != Peter_Piper)  { throw err; }
      curr = curr -> link();
      if (curr -> data() != Mickey_Mouse) { throw err; }
      if (curr -> link() != NULL) { throw err; }
      itPassed(desc);

      // Clean up memory
      for (int i = 0; i < 7; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_search_1() {
    string desc = "list_search: const pointers, successful search";
    try {
      node * hd = NULL;

      // build a list referred to by hd: [Ziggy, Dopey, Minnie, Mickey]
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Ziggy_Wilson);

      const node * c_hd = &(*hd);
      const node * c_ptr;
      c_ptr = list_search(c_hd, Ziggy_Wilson);
      if (c_ptr -> data() != Ziggy_Wilson) { throw err; }
      if (c_ptr != c_hd) { throw err; }
      c_ptr = list_search(c_hd, Dopey_Dwarf);
      if (c_ptr -> data() != Dopey_Dwarf) { throw err; }
      c_ptr = list_search(c_hd, Minnie_Mouse);
      if (c_ptr -> data() != Minnie_Mouse) { throw err; }
      c_ptr = list_search(c_hd, Mickey_Mouse);
      if (c_ptr -> data() != Mickey_Mouse) { throw err; }

      itPassed(desc);

      // Clean up memory
      node* curr = NULL;
      for (int i = 0; i < 4; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_search_2() {
    string desc = "list_search: const pointers, unsuccessful search";
    try {
      node * hd = NULL;

      // build a list referred to by hd: [Ziggy, Dopey, Minnie, Mickey]
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Ziggy_Wilson);

      const node * c_hd = &(*hd);
      const node * c_ptr;
      c_ptr = list_search(c_hd, Skye_Wilson);
      if (c_ptr != NULL) { throw err; }

      itPassed(desc);

      // Clean up memory
      node* curr = NULL;
      for (int i = 0; i < 4; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_search_3() {
    string desc = "list_search: non-const pointers, successful search";
    try {
      node * hd = NULL;
      node * n_ptr;

      // build a list referred to by hd: [Ziggy, Dopey, Minnie, Mickey]
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Ziggy_Wilson);

      n_ptr = list_search(hd, Ziggy_Wilson);
      if (n_ptr -> data() != Ziggy_Wilson) { throw err; }
      if (n_ptr != hd) { throw err; }
      n_ptr = list_search(hd, Dopey_Dwarf);
      if (n_ptr -> data() != Dopey_Dwarf) { throw err; }
      n_ptr = list_search(hd, Minnie_Mouse);
      if (n_ptr -> data() != Minnie_Mouse) { throw err; }
      n_ptr = list_search(hd, Mickey_Mouse);
      if (n_ptr -> data() != Mickey_Mouse) { throw err; }

      itPassed(desc);

      // Clean up memory
      node* curr = NULL;
      for (int i = 0; i < 4; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_search_4() {
    string desc = "list_search: non-const pointers, unsuccessful search";
    try {
      node * hd = NULL;
      node * n_ptr;

      // build a list referred to by hd: [Ziggy, Dopey, Minnie, Mickey]
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Ziggy_Wilson);

      n_ptr = list_search(hd, Skye_Wilson);
      if (n_ptr != NULL) { throw err; }
      itPassed(desc);

      // Clean up memory
      node* curr = NULL;
      for (int i = 0; i < 4; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_locate_1() {
    string desc = "list_locate: const pointers, successful search";
    try {
      node * hd = NULL;

      // build a list referred to by hd: [Ziggy, Dopey, Minnie, Mickey]
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Ziggy_Wilson);

      // ********** version one, use const pointer **********
      const node * c_hd = &(*hd);
      if (list_locate(c_hd, 1) -> data() != Ziggy_Wilson) { throw err; }
      if (list_locate(c_hd, 2) -> data() != Dopey_Dwarf)  { throw err; }
      if (list_locate(c_hd, 3) -> data() != Minnie_Mouse) { throw err; }
      if (list_locate(c_hd, 4) -> data() != Mickey_Mouse) { throw err; }
      itPassed(desc);

      // Clean up memory
      node* curr = NULL;
      for (int i = 0; i < 4; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_locate_2() {
    string desc = "list_locate: const pointers, unsuccessful search";
    try {
      node * hd = NULL;

      // build a list referred to by hd: [Ziggy, Dopey, Minnie, Mickey]
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Ziggy_Wilson);

      // ********** version one, use const pointer **********
      const node * c_hd = &(*hd);
      if (list_locate(c_hd, 5) != NULL) { throw err; }
      itPassed(desc);

      // Clean up memory
      node* curr = NULL;
      for (int i = 0; i < 4; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_locate_3() {
    string desc = "list_locate: non-const pointers, successful search";
    try {
      node * hd = NULL;

      // build a list referred to by hd: [Ziggy, Dopey, Minnie, Mickey]
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Ziggy_Wilson);

      // ********** non-const pointer **********
      if (list_locate(hd, 1) -> data() != Ziggy_Wilson) { throw err; }
      if (list_locate(hd, 2) -> data() != Dopey_Dwarf)  { throw err; }
      if (list_locate(hd, 3) -> data() != Minnie_Mouse) { throw err; }
      if (list_locate(hd, 4) -> data() != Mickey_Mouse) { throw err; }
      itPassed(desc);

      // Clean up memory
      node* curr = NULL;
      for (int i = 0; i < 4; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_locate_4() {
    string desc = "list_locate: non-const pointers, unsuccessful search";
    try {
      node * hd = NULL;

      // build a list referred to by hd: [Ziggy, Dopey, Minnie, Mickey]
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Ziggy_Wilson);

      // ********** non-const pointer **********
      if (list_locate(hd, 5) != NULL) { throw err; }
      itPassed(desc);

      // Clean up memory
      node* curr = NULL;
      for (int i = 0; i < 4; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_locate_5() {
    string desc = "list_locate: empty list";
    try {
      node * hd = NULL;
      if (list_locate(hd, 1) != NULL) { throw err; }
      if (list_locate(hd, 2) != NULL) { throw err; }
      if (list_locate(hd, 3) != NULL) { throw err; }
      if (list_locate(hd, 4) != NULL) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_locate_6() {
    string desc = "list_locate: list of length 1";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Ziggy_Wilson);
      if (list_locate(hd, 1) == NULL) { throw err; }
      if (list_locate(hd, 2) != NULL) { throw err; }
      itPassed(desc);

      // Clean up memory
      delete hd;
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_head_remove_1() {
    string desc = "list_head_remove: list of length 1";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Ziggy_Wilson);
      hd = list_head_remove(hd);
      if (list_length(hd) != 0) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_head_remove_2() {
    string desc = "list_head_remove: list of length 2";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Ziggy_Wilson);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_remove(hd);
      if (list_length(hd) != 1) { throw err; }
      if (hd -> data() != Ziggy_Wilson) { throw err; }
      itPassed(desc);

      // Clean up memory
      delete hd;
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_head_remove_3() {
    string desc = "list_head_remove: longer list";
    try {
      node * hd = NULL;
      for (int i = 0; i < 999; i++)
      {
         hd = list_head_insert(hd, Ziggy_Wilson);
      }
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_remove(hd);
      if (hd -> data() != Mickey_Mouse) { throw err; }
      if (list_length(hd) != 1000) { throw err; }
      itPassed(desc);

      // Clean up memory
      node* curr = NULL;
      for (int i = 0; i < 1000; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

//   void list_remove(node* previous_ptr)
//     Precondition: previous_ptr points to a node in a linked list, and this
//        is not the tail node of the list.
//     Postcondition: The node after previous_ptr has been removed from the
//        linked list.

void test_list_remove_1() {
    string desc = "list_remove: list of length 2, remove position 2";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      list_remove(hd);
      if (hd -> data() != Minnie_Mouse) { throw err; }
      if (list_length(hd) != 1) { throw err; }
      itPassed(desc);

      // Clean up memory
      delete hd;
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_remove_2() {
    string desc = "list_remove: list of length 3, remove position 2";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      list_remove(hd);
      if (hd -> data() != Minnie_Mouse) { throw err; }
      if (hd -> link() -> data() != Dopey_Dwarf) { throw err; }
      if (list_length(hd) != 2) { throw err; }
      itPassed(desc);

      // Clean up memory
      delete hd -> link();
      delete hd;
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_remove_3() {
    string desc = "list_remove: list of length 3, remove position 3";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      // minnie -> mickey -> dopey
      list_remove(hd -> link());
      // minnie -> mickey
      if (hd -> data() != Minnie_Mouse) { throw err; }
      if (hd -> link() -> data() != Mickey_Mouse) { throw err; }
      if (list_length(hd) != 2) { throw err; }
      itPassed(desc);

      // Clean up memory
      delete hd -> link();
      delete hd;
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_remove_4() {
    string desc = "list_remove: list of length 10, remove position 2";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Skye_Wilson);   // pos 3
      hd = list_head_insert(hd, Minnie_Mouse);  // pos 2
      hd = list_head_insert(hd, Ziggy_Wilson);  // pos 1
      list_remove(hd);
      if (hd -> data() != Ziggy_Wilson) { throw err; }   // pos 1
      if (hd -> link() -> data() != Skye_Wilson) { throw err; }   // pos 2
      if (list_length(hd) != 9) { throw err; }
      itPassed(desc);

      // Clean up memory
      node* curr = NULL;
      for (int i = 0; i < 9; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_remove_5() {
    string desc = "list_remove: list of length 10, remove position 5";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Dopey_Dwarf);
      hd = list_head_insert(hd, Mickey_Mouse);
      hd = list_head_insert(hd, Minnie_Mouse);
      hd = list_head_insert(hd, Skye_Wilson);
      hd = list_head_insert(hd, Peter_Pan);     // 6
      hd = list_head_insert(hd, Ziggy_Wilson);  // 5 << remove
      hd = list_head_insert(hd, Happy_Dwarf);   // 4
      hd = list_head_insert(hd, Mickey_Mouse);  // 3
      hd = list_head_insert(hd, Minnie_Mouse);  // 2
      hd = list_head_insert(hd, Dopey_Dwarf);   // 1
      node * curr = hd;   // 1
      curr = curr -> link();   // 2
      curr = curr -> link();   // 3
      curr = curr -> link();   // 4
      // cout << (curr -> data()) << endl; // should print Dopey
      list_remove(curr);  // remove the guy after dopey ==> Ziggy
      if (hd -> data() != Dopey_Dwarf) { throw err; }    // pos 1
      if (curr -> data() != Happy_Dwarf) { throw err; }  // pos 4
      if (curr -> link() -> data() != Peter_Pan) { throw err; }  // pos 5
      if (list_length(hd) != 9) { throw err; }
      itPassed(desc);

      // Clean up memory
      for (int i = 0; i < 9; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_remove_6() {
    string desc = "list_remove: list of length 10, remove position 10";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Dopey_Dwarf);  // 10
      hd = list_head_insert(hd, Ziggy_Wilson);  // 9
      hd = list_head_insert(hd, Peter_Piper);  // 8
      hd = list_head_insert(hd, Skye_Wilson);  // 7
      hd = list_head_insert(hd, Peter_Pan);    // 6
      hd = list_head_insert(hd, Minnie_Mouse);  // 5
      hd = list_head_insert(hd, Dopey_Dwarf);  // 4
      hd = list_head_insert(hd, Mickey_Mouse);  // 3
      hd = list_head_insert(hd, Minnie_Mouse);  // 2
      hd = list_head_insert(hd, Happy_Dwarf);   // 1
      node * curr = hd;  // 1
      for (int i = 0; i < 8; i++)
      {
         curr = curr -> link();
      }
      // cout << (curr -> data()) << endl; // should print Ziggy
      list_remove(curr);  // remove the guy after Ziggy ==> Dopey
      if (hd -> data() != Happy_Dwarf) { throw err; }  // pos 1
      if (curr -> data() != Ziggy_Wilson) { throw err; }  // pos 9
      if (curr -> link() != NULL) { throw err; }
      if (list_length(hd) != 9) { throw err; }
      itPassed(desc);

      // Clean up memory
      for (int i = 0; i < 9; i++){
        curr = hd;
        hd = hd -> link();
        delete curr;
      }
      hd = NULL;
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_clear_1() {
    string desc = "list_clear: list of length 0";
    try {
      node * hd = NULL;
      list_clear(hd);
      if (list_length(hd) != 0) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_clear_2() {
    string desc = "list_clear: list of length 1";
    try {
      node * hd = NULL;
      hd = list_head_insert(hd, Mickey_Mouse);
      list_clear(hd);
      if (list_length(hd) != 0) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

void test_list_clear_3() {
    string desc = "list_clear: list of length 100";
    try {
      node * hd = NULL;
      for (int i = 0; i < 100; i++)
      {
         hd = list_head_insert(hd, Mickey_Mouse);
      }
      list_clear(hd);
      if (list_length(hd) != 0) { throw err; }
      itPassed(desc);
    }
    catch(string s){ itFailed(desc + " " + s); }
}

int main() {
    print("\ntests for Lab 6 Part 1 -- node1; list toolkit ...");
    test_node_1();
    test_node_2();
    test_node_3();
    test_node_4();
    test_node_5();
    test_length_and_head_insert_1();
    test_length_and_head_insert_2();
    test_length_and_head_insert_3();
    test_list_insert_1();
    test_list_insert_2();
    test_list_insert_3();
    test_list_search_1();
    test_list_search_2();
    test_list_search_3();
    test_list_search_4();
    test_list_locate_1();
    test_list_locate_2();
    test_list_locate_3();
    test_list_locate_4();
    test_list_locate_5();
    test_list_locate_6();
    test_list_head_remove_1();
    test_list_head_remove_2();
    test_list_head_remove_3();
    test_list_remove_1();
    test_list_remove_2();
    test_list_remove_3();
    test_list_remove_4();
    test_list_remove_5();
    test_list_remove_6();
    test_list_clear_1();
    test_list_clear_2();
    test_list_clear_3();

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
