#include <boost/test/unit_test.hpp>
#include "src/render/TileMenu.cpp"

BOOST_AUTO_TEST_CASE(TestMenu){

	std::string image = "res/button/b_button00.png";
	std::string text = "bonjour";
	std::string font = "res/DS-DIGI.TTF";
	int position[2];
	position[0] = -180;
	position[1] = 180;

	TileMenu* tileMenu = new TileMenu(image,text,font,position);

	BOOST_CHECK_EQUAL(tileMenu.getText(),text);

	sf::Texture texture;
	if (texture.loadFromFile(image))
    {
        std::cout << "Error loading image menu\n";
        exit(-1);
    }
	sf::Sprite sprite;
	sprite.setTexture(>texture);
	sprite.setPosition(sf::Vector2f(position[0],position[1]));

	BOOST_CHECK_EQUAL(tileMenu.getSprite(),sprite);
	BOOST_CHECK(tileMenu.changeSprite());
	BOOST_CHECK(tileMenu.setOffset(sf::Vector2f(position[0],position[1])));

}