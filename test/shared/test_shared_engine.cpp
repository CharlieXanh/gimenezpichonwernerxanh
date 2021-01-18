#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine.h"

using namespace ::std;
using namespace ::engine;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestEngineNamespace)
{
  //engine
  {
    Engine ngine {"engine"};
    BOOST_CHECK_EQUAL(ngine.getEtat().getMode(),"engine");
    ngine.getEtat().initializeMapCell();
    ngine.getEtat().initJoueurs();
    unique_ptr<Commande> ptr_cmd(new AttaquerCommande(*ngine.getEtat().getJoueurs()[0],*ngine.getEtat().getJoueurs()[1]));
    ngine.ajoutCommande(move(ptr_cmd),0);
    ngine.update();
    BOOST_CHECK_GT(ngine.getEtat().getTour(),0);
  }
}
