#include "../core/noyauLissage.hpp"

#include <cstdio>
#include <cstdlib>
#include <ostream>
#include <assert.h>

using std::cout;
using std::endl;

void test_noyauLissage() {
  cout << "-- 1. Test du noyau de lissage par défaut pour le noyau par défaut --" << endl ;
  cout << "Construction d'un noyau de dimension 3 : " << endl ;
  NoyauLissage<3> w = NoyauLissage<3>(5,DEFAUT);
  cout << "Construction d'un vecteur a trois elements : " << endl ;
  Vecteur<3> r;
  r(1) = 1.5;
  r(2) = 1.5;
  r(3) = 1.5;
  double res1 = w.defaut(r);
  assert((res1 <= 0.0049) && (res1 >= 0.0048));
  cout << "Resultat : " << res1 << endl;

  cout << "-- 2. Test du noyau de lissage gradient pour le noyau par défaut --" << endl ;
  Vecteur<3>  res2 = w.gradient(r);
  assert((res2(1) <= -0.0024) && (res2(1) >= -0.0025));
  cout << "Resultat : " << res2 << endl;

    
  cout << "-- 3. Test du noyau de lissage laplacien pour le noyau par défaut --" << endl ;
  double res3 = w.laplacien(r);
  assert((res3 <= -0.0024) && (res3 >= -0.0025));
  cout << "Resultat : " << res3 << endl;

  cout << "-- 4. Test du noyau de lissage par défaut pour le noyau pression --" << endl ;
  NoyauLissage<3> w2 = NoyauLissage<3>(5,PRESSION);
  double res4 = w2.defaut(r);
  //assert((res4 <= ) && (res4 >= ));
  cout << "Resultat : " << res4 << endl;

  cout << "-- 5. Test du noyau de lissage gradient pour le noyau pression --" << endl ;
  Vecteur<3> res5 = w2.gradient(r);
  //assert((res2 <= ) && (res2 >= ));
  cout << "Resultat : " << res5 << endl;
    
  cout << "-- 6. Test du noyau de lissage laplacien pour le noyau pression --" << endl ;
  double res6 = w2.laplacien(r);
  //assert((res2 <= ) && (res2 >= ));
  cout << "Resultat : " << res6 << endl;

    
  cout << "-- 7. Test du noyau de lissage par defaut pour le noyau viscosite --" << endl ;
  NoyauLissage<3> w3 = NoyauLissage<3>(5,VISCOSITE);
  double res7 = w3.defaut(r);
  //assert((res2 <= ) && (res2 >= ));
  cout << "Resultat : " << res7 << endl;

  cout << "-- 8. Test du noyau de lissage laplacien pour le noyau pression --" << endl ;
  Vecteur<3> res8 = w3.gradient(r);
  // assert((res2 <= ) && (res2 >= ));
  cout << "Resultat : " << res8 << endl;

  cout << "-- 9. Test du noyau de lissage laplacien pour le noyau pression --" << endl ;
  double res9 = w3.laplacien(r);
  //assert((res2 <= ) && (res2 >= ));
  cout << "Resultat : " << res9 << endl;
    
}
