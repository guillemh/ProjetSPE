#include "../core/premier.hpp"

#include <cstdio>
#include <cstdlib>
#include <ostream>
#include <chrono>

using std::cout;
using std::endl;

void test_performances_premier()
{
    cout << "-- 1. Test de performances pour les 9592 premiers nombres premiers avec getPremier --" << endl;

     Premier<3> p = Premier<3>();

    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::duration<double, std::milli> ms;
    Clock::time_point t0,t1;

    int n;
    int max = 9592;

    t0 = Clock::now();    
    for (int i = 0; i < max; ++i)
        n = p.getPremier(i);
    t1 = Clock::now();
    std::cout << ms(t1-t0).count() << " millisecond\n";

    cout << "-- 2. Test de performances pour les 9592 premiers nombres premiers avec calculPremier --" << endl;

    t0 = Clock::now();
    for (int i = 0; i < max; ++i)
	n = p.calculPremier(i);
    t1 = Clock::now();
    std::cout << ms(t1-t0).count() << " millisecond\n";
}
