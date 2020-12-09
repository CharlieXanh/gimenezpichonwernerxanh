
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Etat.h"
#include "../../src/shared/state/Combat.h"
#include "../../src/shared/state/Echange.h"
#include "../../src/shared/state/Deplacement.h"




using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestStateNamespace)
{
  //Position
  {
    Position p {1,2,"NORTH"};
    BOOST_CHECK_EQUAL(p.getX(),1);
    BOOST_CHECK_EQUAL(p.getY(), 2);
    BOOST_CHECK_EQUAL(p.getOrientation(), "NORTH");
    p.deplacer(1,1);
    BOOST_CHECK_EQUAL(p.getX(), 2);
    BOOST_CHECK_EQUAL(p.getY(), 3);
    p.placer(5,6);
    BOOST_CHECK_EQUAL(p.getX(), 5);
    BOOST_CHECK_EQUAL(p.getY(), 6);


  //Caracteristiques

    Caracteristiques ca {100,10,9,8,7};
    BOOST_CHECK_EQUAL(ca.getSante(),100);
    BOOST_CHECK_EQUAL(ca.getAttaque(),10);
    BOOST_CHECK_EQUAL(ca.getDefense(),9);
    BOOST_CHECK_EQUAL(ca.getInitiative(),8);
    BOOST_CHECK_EQUAL(ca.getVitesse(),7);
    ca.setSante(ca.getSante() - 10);
    ca.setAttaque(5);
    ca.setDefense(5);
    ca.setInitiative(5);
    ca.setVitesse(5);
    BOOST_CHECK_EQUAL(ca.getSante(),90);
    BOOST_CHECK_EQUAL(ca.getAttaque(),5);
    BOOST_CHECK_EQUAL(ca.getDefense(),5);
    BOOST_CHECK_EQUAL(ca.getInitiative(),5);
    BOOST_CHECK_EQUAL(ca.getVitesse(),5);

  //Entite (TODO)

  //  Entite e {ca,p};

    Curseur curs{2,2};
    BOOST_CHECK_EQUAL(curs.getVisible(),false);
    curs.setVisible(true);
    BOOST_CHECK_EQUAL(curs.getVisible(),true);
    BOOST_CHECK_EQUAL(curs.getLastPosition().getX(),2);
    curs.deplacer(p); // p => {5,6} here
    curs.deplacer(p);
    BOOST_CHECK_EQUAL(curs.getLastPosition().getX(),5);




  //Joueur(TODO)

  //  Joueur j{"Jack",e,10};

  }

//
  //Item
  {
  Caracteristiques ca {100,10,9,8,7};
     Item item {"Epee",30,ca};
    BOOST_CHECK_EQUAL(item.getPrix(),30);
    BOOST_CHECK_EQUAL(item.getNom(),"Epee");
    //BOOST_CHECK_EQUAL(item.getBonus(),&ca);
    item.setPrix(40);
    item.setNom("Hache");
    BOOST_CHECK_EQUAL(item.getPrix(),40);
    BOOST_CHECK_EQUAL(item.getNom(),"Hache");
    Caracteristiques nca {8,8,8,4,8};
    //item.setBonus(&nca);
    //pas besoin de tester les autres getter ici on test le setBonus
   BOOST_CHECK_EQUAL(nca.getSante(),8);
  }
  {
    Caracteristiques ca {100,10,9,8,7};
    Item item {"Epee",30,ca};
    BOOST_CHECK_EQUAL(item.getPrix(),30);
    BOOST_CHECK_EQUAL(item.getNom(),"Epee");
    BOOST_CHECK_EQUAL(item.getBonus().getSante(),ca.getSante());
    item.setPrix(40);
    item.setNom("Hache");
    BOOST_CHECK_EQUAL(item.getPrix(),40);
    BOOST_CHECK_EQUAL(item.getNom(),"Hache");
    Caracteristiques nca {8,8,8,4,8};
    item.setBonus(nca);
    // pas besoin de tester les autres getter ici on test le setBonus
    BOOST_CHECK_EQUAL(item.getBonus().getSante(),8);

  }

  //Obstacle
  {
     Position p {1,2,"NORTH"};
     Obstacle obs {3,7,p};
     std::vector<int> tab {1,2};
     BOOST_CHECK_EQUAL(obs.getTaille()[0],3);

  }

  //Zone
  {
    Position p {1,2,"NORTH"};
    Zone zon {5,6,p,"class"};
  }


  // {
  //   Exemple ex {};
  //   ex.setX(21);
  //   BOOST_CHECK_LE(ex.x, 32); // Less than equal
  //   BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  // }
}
/* vim: set sw=2 sts=2 et : */
