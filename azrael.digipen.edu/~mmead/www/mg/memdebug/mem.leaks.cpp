
/*
 * Sun 11 May 2008 09:34:14 PM PDT (dvolper)
 * Updated: Tue Sep  9 10:18:15 PDT 2014 (mmead, just comments at bottom)
 * Updated: Wed Jan 13 09:01:33 PDT 2016 (mmead, just comments at bottom)
 * ALL tests in this file are BAD: most of them are illegal (from 
 * C++ standard point of view at least).
 *---------------------------------------------------------------------
 * The really bad news is that most of these tests run without crashing.
 * Therefore these errors may stay un-noticed till later time, usually 
 * when you are presenting your program to someone. 
 *
 *   "...the results are undefined, and we all know what "undefined" 
 *    means: it means it works during development, it works during 
 *    testing, and it blows up in your most important customers' 
 *    faces." --Scott Meyers
 *
 * So, what is the answer -- memory debuggers.
 *---------------------------------------------------------------------
 *
 * File format:
 * each test has a short description, for each test there is
 * a result of running the executable obtained with the following compilers:
 * GNU 4.8.2 on Linux Mint 17 <-- updated on Tue 09 Sep 2014
 * Clang 3.6 on Mac OS X <-- updated Tue 12 Jan 2016
 * Borland 5.82
 * MicroSoft 8.0 (or whatever is VS2005)
 * (see Makefile)
 *
 * +++You can use newer versions of the compilers.
 *
 * The result of using memory debuggers is presented at the end of this file.
 * */
#include <iostream>
#include <cstdlib>
#include <stdlib.h> /*free*/
#include <string>
#include <stdio.h>

void test0() {
    std::cout << "test0" << std::endl;
    int* pI = new int;
    *pI=2;
    delete(pI);
    std::cout << "Now deleting a pointer twice..." << std::endl;
    delete(pI);
    std::cout << "Did you notice?" << std::endl;
}
/* Runs - deleting PODs twice usually doesn't cause any error,
 * since there is no destructor, which may fail. See test1 - an
 * example with a non-trivial dtor.
 * gcc: crashes "*** Error in `./a.out': double free or corruption (fasttop): 0x0000000000679010 ***"
 * msc: OK
 * bcc: OK
 */

class TestDoubleDelete {
    int * data;
    public:
    TestDoubleDelete(int _i) : data(new int(_i)) {}
    ~TestDoubleDelete() { delete data; }
};

void test1() {
    std::cout << "test1" << std::endl;
    TestDoubleDelete* p = new TestDoubleDelete(11);
    std::cout << "Now deleting a pointer ..." << std::endl;
    delete p;
    std::cout << "Now deleting a pointer one more time ..." << std::endl;
    delete p;
    std::cout << "Did you notice?" << std::endl;
}
/* Runs - 
 * gcc: crashes "*** Error in `./a.out': free(): invalid pointer: 0x000000000139f020 ***"
 * msc: OK
 * bcc: OK
 */

void test2() {
    std::cout << "test2" << std::endl;
    int* pI = new int(2);
    std::cout << "Now freeing a pointer instead of deleting it..." << std::endl;
    free(pI);
    std::cout << "Did you notice?" << std::endl;
}
/* Runs - as we'll discuss in class, delete is actually a "free" + "dtor",
 * thus calling free instead of delete skips a dtor, which doesn't 
 * cause an error, but results in a memory leak.
 * gcc: OK
 * msc: OK
 * bcc: OK
 */

void test3() {
    std::cout << "test3" << std::endl;
    int* pI = new int;
    std::cout << "Now reading uninitialized memory" << std::endl;
    int j = *pI+2;
    std::cout << "Did you notice? (value was " << j << ") probably garbage" 
        << std::endl;
    delete pI; /*no leaks*/
}
/* Runs - this is not a legal C++ code, C++ standard says that program
 * is not supposed to use unintialized memory. So memory has to be 
 * 1) allocated (done in test3)
 * 2) initialized (not done in test3)
 *
 * gcc: OK (value was 0)
 * msc: OK (value was garbage)
 * bcc: OK (value was garbage)
 */

void test4() {
    std::cout << "test4" << std::endl;
    int* pJ;
    std::cout << "Now writing to uninitialized pointer (un-allocated memory) pJ = " << pJ << std::endl;
    *pJ = 100;
    std::cout << "Did you notice?" << std::endl;
}
/* Runs - notice that this is much worse than what we did in test3, 
 * in test4 memory for the int wasn't even allocated. So what happens is
 * pJ contains garbage, then this garbage is treated as an address, and we 
 * attempt to write to that address.
 * gcc: crashes "Segmentation fault"
 * msc: crashes (memory could not be written), it also warns at compile time 
 "mem.leaks.cpp(82) : warning C4700: 
 uninitialized local variable 'pJ' used"
 * bcc: OK, but!!! there was a warning 
 *     "Warning W8013 mem.leaks.cpp 82: 
 *      Possible use of 'pJ' before definition in function test4()" 
 */

void test5() {
    std::cout << "test5" << std::endl;
    int* pI = new int[10];
    std::cout << "Let's delete instead of delete [] " << std::endl;
    delete pI;
    std::cout << "Did you notice?" << std::endl;
}
/* Runs - delete [] is actually quite complicated. It calls a destructor on
 * each element of the array, and than frees the array itself.  Thus, calling
 * "delete" instead of "delete []" doesn't produce an error, but it skips all
 * destructors, which may be a memory leak (if the objects in the array had
 * dynamically allocated memory) 
 * gcc: OK 
 * msc: OK 
 * bcc: OK 
 * This particular example doesn't have a leak, since there is no dynamically 
 * allocated memory inside int objects. But it's still an illegal code.
 */

class CTest1 {
    int * pi;
    public:
    CTest1() : pi(new int (2)) {}
    ~CTest1() { std::cout << "In ~CTest1()" << std::endl; delete pi; }
};

void test6() {
    std::cout << "test6" << std::endl;
    CTest1* p = new CTest1[10];
    std::cout << "Let's free instead of delete [] " << std::endl;
    free(p);
    std::cout << "Did you notice?" << std::endl;
}
/* Runs - this is a continuation of test5. Again, there MAY be run-time 
 * crashes, and definitely there is a leak. 
 * What happens: NO destructor is called, so all 10 dynamically allocated 
 * integers (pi pointer) are still on the heap 
 *
 * Those compilers that pay attention to the type information (array vs.
 * single) may crash when calling free, others won't (but leak dynamically
 * allocated memory, if any, from the other 9 objects).
 * gcc: crashes "*** Error in `./a.out': munmap_chunk(): invalid pointer: 0x0000000001d17018 ***"
 * msc: OK
 * bcc: OK
 * Here is the output that proves that NO destructor is called.
 * Change "delete" to "delete []" and you'll see 10 destructors.
 ===================================
 Let's delete instead of delete []
 Did you notice?
 ===================================
 * Note: gcc on Linux (4.1.3) crashes!!! (CygWin gcc is 3.4.4)
 */

class CTest2 {
    int i;
    public:
    CTest2() : i(2) {}
    ~CTest2() { std::cout << "In ~CTest2()" << std::endl; }
};

void test7() {
    std::cout << "test7" << std::endl;
    CTest2* p = new CTest2[10];
    std::cout << "Let's delete instead of delete [] " << std::endl;
    delete p;
    std::cout << "Did you notice?" << std::endl;
}
/* Runs - this is a continuation of test5. Again, there MAY be run-time 
 * crashes, and definitely there is a leak. 
 * What happens: 
 * when delete is called, it calls a SINGLE destructor on the 
 * pointer "p", and then free.
 *
 * Those compilers that pay attention to the type information (array vs.
 * single) may crash when calling free, others won't (but leak dynamically
 * allocated memory, if any, from the other 9 objects).
 * gcc: crashes "*** Error in `./a.out': munmap_chunk(): invalid pointer: 0x000000000126a018 ***"
 * msc: OK
 * bcc: OK
 * Here is the output that proves that only one destructor is called.
 * Change "delete" to "delete []" and you'll see 10 destructors.
 ===================================
 Let's delete instead of delete []
 In ~CTest2() 
 Did you notice?
 ===================================
 * Note: gcc on Linux (4.1.3) crashes!!! (CygWin gcc is 3.4.4)
 */


void test8() {
    std::cout << "test8" << std::endl;
    int ar[10]={0}; //array
    std::cout << "Let's read out of bounds " << std::endl;
    std::cout << "ar[10] = " << ar[10] << std::endl;
    std::cout << "Did you notice?" << std::endl;
}
/* Runs - 
 * gcc: OK
 * msc: OK
 * bcc: OK
 */

void test9() {
    std::cout << "test9" << std::endl;
    int ar[10]={0}; //array
    std::cout << "Let's write out of bounds " << std::endl;
    ar[10] = 7;
    std::cout << "Did you notice?" << std::endl;
}
/* Runs - 
 * gcc: OK
 * msc: OK
 * bcc: OK
 */

void test10() {
    std::cout << "test10" << std::endl;
    int * ar = new int[3];
    std::cout << "Let's read out of bounds " << std::endl;
    std::cout << "ar[3] = " << ar[3] << std::endl;
    std::cout << "Did you notice?" << std::endl;
    delete [] ar;
}
/* Runs - 
 * gcc: OK
 * msc: OK
 * bcc: OK
 */

void test11() {
    std::cout << "test11" << std::endl;
    int * ar = new int[3];
    std::cout << "Let's write out of bounds " << std::endl;
    ar[3] = 7;
    std::cout << "Did you notice?" << std::endl;
    delete [] ar;
}
/* Runs - 
 * gcc: OK
 * msc: OK
 * bcc: OK
 */

void test12() {
    std::cout << "test12" << std::endl;
    int* pI = new int;
    std::cout << "Let's leak a pointer to int" << std::endl;
    *pI = 303;
}
/* Runs - just a leak, so all 3 OK */

void (*pTests[])() = {
    test0,test1,test2,test3,test4,test5,test6,
    test7,test8,test9,test10,test11,test12
};

#include <cstdio> /* sscanf */

int main(int argc, char *argv[] ) {
    if (argc >1) {
        int test = 0;
        std::sscanf(argv[1],"%i",&test);
        try {
            pTests[test]();
        } catch( const char* msg) {
            std::cerr << msg << std::endl;
        }
    }
    return 0;
}

/*
 * Here are results from using:
 * Borland CodeGuard (Windows only)
 * Valgrind (Linux/Mac only)
 * Dr. Memory (Linux/Mac/Windows, 32-bit only)
 * Rational Purify (Windows only)
 * =================================================
 * To use CodeGuard :
 * 1) This is a one-time step
 *    a) Run from the command line: cgconfig
 *    b) in Preferences check "Resource Leaks" and "Repeated Errors",
 *       uncheck the rest
 *    c) in "Error Message Box" - check it if you want a pop-up message box,
 *       otherwise you'll have to look into "exec_name.cgl" file each time.
 *    d) in "Debugging Information" check the "Read debug info"
 *    e) click OK
 *    f) there are more tabs, you don't modify defaults there to run this code,
 *       but "Ignored Modules" may be useful when working with STL.
 * 2) Compile you code with Borland using additional "-v -vG" flags, like
 *    bcc32.exe -emy.exe -v -vG -w <source files>
 *    executable "my.exe" is created
 *    run it normally - if there is an error, a log file will be created named
 *    "my.cgl" (CodeGuard Log). Read it and weep.
 * =================================================
 * To use valgrind:
 * 1) install valgrind and, optionally, electric fence:
 *    sudo-apt-get install valgrind electric-fence
 *    (pretty dumb! - that's why Linux rocks)
 * 2) compile code using debug information and electric fence's malloc
 *    g++ -ggdb -pedantic -ansi -Wall -Wextra -lefence <source> -omy.exe
 * 3) run it
 *    valgrind -q ./my.exe <test#>
 *    output will be displayed in the terminal. Read it and weep.
 * 4) there is a nice add-on to valgrind - kcachegrind
 * Note: You don't need electric fence, it's just optional.
 * =================================================
 * To use Dr. Memory
 * 1) Compile your program as a 32-bit program (gcc/clang use -m32)
 * 2) Run it like this: drmemory -- my.exe <test#>
 * Read the manual that explains all of the options it has.
 * =================================================
 * To use Purify: see http://digipen.edu/~dvolper,
 * search for "Rational Purify" -
 * close to bottom of the page
 * =================================================
 *
 *          CodeGuard        Valgrind             Dr. Memory             Purify
 *          Windows          Linux/Mac         Linux/Mac/Windows         Windows       Type of test run  
 * ================================================================================================================
 * test0  | caught         caught/caught      caught/caught/caught       caught     | double delete POD
 * test1  | caught         caught/caught      caught/caught/caught       caught     | double delete user-defined type
 * test2  | caught         caught/caught      caught/caught/not          caught     | free instead of delete
 * test3  | not            caught/caught      caught/caught/caught       caught     | read uninitialized data
 * test4  | not            caught/caught      caught/caught/not (!!)     caught     | write uninitialized data
 * test5  | caught         caught/not         caught/caught/not          not        | delete instead of delete [] POD
 * test6  | caught         caught/caught      caught/caught/caught       caught     | free instead of delete []
 * test7  | caught         caught/caught      caught/caught/caught       caught     | delete instead of delete [] user-defined type
 * test8  | caught         caught/not         not/not/not                not        | static array, out-of-bound read
 * test9  | caught         not/caught         not/caught/not (!!)        not        | static array, out-of-bound write
 * test10 | caught         caught/caught      caught/caught/caught       caught     | dynamic array, out-of-bound read
 * test11 | caught         caught/caught      caught/caught/caught       caught     | dynamic array, out-of-bound write
 * test12 | caught         caught/caught      caught/caught/caught       caught     | just a stupid leak
 *
 * (!!) The program crashed and Dr. Memory couldn't prevent/detect anything.
 *
 */
