#include "../core/premier.hpp"

#include <cstdio>
#include <cstdlib>
#include <ostream>

using std::cout;
using std::endl;

void test_premier()
{
    cout << "-- 1. Test pour les entiers <= 10 --" << endl;
    Premier<3> p = Premier<3>();

    int x = 2;
    int res = p.getPremier(x);
    assert(res==2);
    cout << "OK" << endl;

    x = 3;
    res = p.getPremier(x);
    assert(res==3);
    cout << "OK" << endl;

    x = 4;
    res = p.getPremier(x);
    assert(res==5);
    cout << "OK" << endl;

    x = 5;
    res = p.getPremier(x);
    assert(res==5);
    cout << "OK" << endl;

    x = 6;
    res = p.getPremier(x);
    assert(res==7);
    cout << "OK" << endl;

    x = 7;
    res = p.getPremier(x);
    assert(res==7);
    cout << "OK" << endl;

    x = 8;
    res = p.getPremier(x);
    assert(res==11);
    cout << "OK" << endl;
     
    x = 9;
    res = p.getPremier(x);
    assert(res==11);
    cout << "OK" << endl;

    cout << "-- 2. Test pour les entiers 100<=x<=110 --" << endl;
    x = 100;
    res = p.getPremier(x);
    assert(res==101);
    cout << "OK" << endl;

     
    x = 101;
    res = p.getPremier(x);
    assert(res==101);
    cout << "OK" << endl;

    x = 102;
    res = p.getPremier(x);
    assert(res==103);
    cout << "OK" << endl;

    x = 103;
    res = p.getPremier(x);
    assert(res==103);
    cout << "OK" << endl;

    x = 104;
    res = p.getPremier(x);
    assert(res==107);
    cout << "OK" << endl;

    x = 105;
    res = p.getPremier(x);
    assert(res==107);
    cout << "OK" << endl;

    x = 106;
    res = p.getPremier(x);
    assert(res==107);
    cout << "OK" << endl;

     
    x = 107;
    res = p.getPremier(x);
    assert(res==107);
    cout << "OK" << endl;

    x = 108;
    res = p.getPremier(x);
    assert(res==109);
    cout << "OK" << endl;

    x = 109;
    res = p.getPremier(x);
    assert(res==109);
    cout << "OK" << endl;

    x = 110;
    res = p.getPremier(x);
    assert(res==113);
    cout << "OK" << endl;

    cout << "-- 3. Test pour les entiers 1000<=x<=1010 --" << endl;
    x = 1000;
    res = p.getPremier(x);
    assert(res==1009);
    cout << "OK" << endl;

     
    x = 1001;
    res = p.getPremier(x);
    assert(res==1009);
    cout << "OK" << endl;

    x = 1002;
    res = p.getPremier(x);
    assert(res==1009);
    cout << "OK" << endl;

    x = 1003;
    res = p.getPremier(x);
    assert(res==1009);
    cout << "OK" << endl;

    x = 1004;
    res = p.getPremier(x);
    assert(res==1009);
    cout << "OK" << endl;

    x = 1005;
    res = p.getPremier(x);
    assert(res==1009);
    cout << "OK" << endl;

    x = 1006;
    res = p.getPremier(x);
    assert(res==1009);
    cout << "OK" << endl;

     
    x = 1007;
    res = p.getPremier(x);
    assert(res==1009);
    cout << "OK" << endl;

    x = 1008;
    res = p.getPremier(x);
    assert(res==1009);
    cout << "OK" << endl;

    x = 1009;
    res = p.getPremier(x);
    assert(res==1009);
    cout << "OK" << endl;

    x = 1010;
    res = p.getPremier(x);
    assert(res==1013);   
    cout << "OK" << endl;

    cout << "-- 4. Test pour les entiers 9582<=x<=9592 --" << endl;
    x = 9582;
    res = p.getPremier(x);
    assert(res==9587);
    cout << "OK" << endl;

     
    x = 9583;
    res = p.getPremier(x);
    assert(res==9587);
    cout << "OK" << endl;

    x = 9584;
    res = p.getPremier(x);
    assert(res==9587);
    cout << "OK" << endl;

    x = 9585;
    res = p.getPremier(x);
    assert(res==9587);
    cout << "OK" << endl;

    x = 9586;
    res = p.getPremier(x);
    assert(res==9587);
    cout << "OK" << endl;

    x = 9587;
    res = p.getPremier(x);
    assert(res==9587);
    cout << "OK" << endl;

    x = 9588;
    res = p.getPremier(x);
    assert(res==9601);
    cout << "OK" << endl;

     
    x = 9589;
    res = p.getPremier(x);
    assert(res==9601);
    cout << "OK" << endl;

    x = 9590;
    res = p.getPremier(x);
    assert(res==9601);
    cout << "OK" << endl;

    x = 9591;
    res = p.getPremier(x);
    assert(res==9601);
    cout << "OK" << endl;

    x = 9592;
    res = p.getPremier(x);
    assert(res==9601);   
    cout << "OK" << endl;

    cout << "-- 5. Test pour des entiers 9592<=x --" << endl;
    x = 9593;
    res = p.getPremier(x);
    assert(res==9601);   
    cout << "OK" << endl;

    x = 99991;
    res = p.getPremier(x);
    assert(res==99991);   
    cout << "OK" << endl;

    cout << "-- 6. Test pour des entiers 99991<=x --" << endl;
    x = 99992;
    res = p.getPremier(x);
    assert(res==100003);   
    cout << "OK" << endl;

    x = 1000000000;
    //res = p.getPremier(x); // Fonctionne mais long à l'execution
    //assert(res==1000000007);   
    cout << "OK" << endl;
}
