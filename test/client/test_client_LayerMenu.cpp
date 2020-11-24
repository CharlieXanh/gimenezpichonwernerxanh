#include <boost/test/unit_test.hpp>
#include "src/render/LayerMenu.cpp"


BOOST_AUTO_TEST_CASE(TestLayerMenu){
	LayerMenu* menu = new new LayerMenu(1); 

	BOOST_CHECK(menu.updatePosition(sf::Vector2f(16,16)));

}