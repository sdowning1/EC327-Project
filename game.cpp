#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>
using std::cout;
using std::cin;
using std::string;

class Button{
public: 
  Button(){ }

  Button(std::string text, sf::Vector2f size, sf::Color textColor) {
  text.setString(text);
  text.setColor(textColor);
  button.setSize(size);
  button.setFillColor(bigColor)
  }
private:
  sf::RectangleShape button;
  sf::Text text;
};

int main(){
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "Memory Game");
  sf::Text name;
  sf::Font font;
  sf::Button start{"Start", [100,100], sf::Color::Blue};
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  name.setFont(font);
  name.setString("Memory Game");
  name.setFillColor(sf::Color::White);

  window.setFramerateLimit(10);
  while (window.isOpen()) {
    sf::Event event;
    name.setPosition(300,50);
    window.draw(name);
    window.draw(start);
    window.display();
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }
  return 0;
}
