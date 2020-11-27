#include <SFML/Graphics.hpp>
#include <boost/test/unit_test.hpp>
#include "src/render/TileMap.cpp"


BOOST_AUTO_TEST_CASE(TestMap){
	TileMap map;
	BOOST_CHECK(map.load("res/tilemap_packed.png", sf::Vector2u(16,16)));
}