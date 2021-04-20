#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stoi;


// void resize(sf::RenderWindow& window, sf::Text& welcome) {
//   sf::Vector2u size = window.getSize();
//   unsigned int width = size.x;
//   unsigned int height = size.y;

//   welcome.setCharacterSize(width/30);
//   welcome.setPosition(width/10,height/10);
// }


int main() {
  // initialize variables
  sf::Event event;
  
  int window_size = 800;
  sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Memory Game");
  window.setFramerateLimit(10);

  string welcome_msg = "Hello,\n";
  welcome_msg = welcome_msg + "\nYou'll be shown a set of shapes/numbers on the screen,";
  welcome_msg = welcome_msg + "\ntry to remember them.";
  welcome_msg = welcome_msg + "\n\nInput your answers by [instruction].\n\nPress ENTER to start.";
  sf::Text welcome;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  welcome.setFont(font);
  welcome.setFillColor(sf::Color::White);
  welcome.setCharacterSize(window_size/30);
  welcome.setString(welcome_msg);
  welcome.setPosition(window_size/10,window_size/10);

  string stimulus_str = "STIMULUS SCREEN";
  sf::Text stimulus_msg;
  stimulus_msg.setFont(font);
  stimulus_msg.setFillColor(sf::Color::White);
  stimulus_msg.setCharacterSize(window_size/30);
  stimulus_msg.setString(stimulus_str);
  stimulus_msg.setPosition(window_size/10,window_size/10);

  string answer_str = "ANSWER SCREEN";
  sf::Text answer_msg;
  answer_msg.setFont(font);
  answer_msg.setFillColor(sf::Color::White);
  answer_msg.setCharacterSize(window_size/30);
  answer_msg.setString(answer_str);
  answer_msg.setPosition(window_size/10,window_size/10);

  string feedback_str = "Correct! / Try Again";
  sf::Text feedback_msg;
  feedback_msg.setFont(font);
  feedback_msg.setFillColor(sf::Color::White);
  feedback_msg.setCharacterSize(window_size/30);
  feedback_msg.setString(feedback_str);
  feedback_msg.setPosition(window_size/10,window_size/10);

  string end_str = "END SCREEN";
  sf::Text end_msg;
  end_msg.setFont(font);
  end_msg.setFillColor(sf::Color::White);
  end_msg.setCharacterSize(window_size/30);
  end_msg.setString(end_str);
  end_msg.setPosition(window_size/10,window_size/10);

  int answering_time = 6;

  std::time_t time;
  std::tm then;
  std::tm now;

  std::tm tic;
  std::tm toc;

  // home screen
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      // Close window request
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      }      
      // Key presses
      if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Enter){
          goto stimulus_screen;
        }
      }
    }
    window.clear();
    window.draw(welcome);
    window.display();
  }

  stimulus_screen:

  time = std::time(NULL);
  then = *std::localtime(&time);

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      // Close window request
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      }      
    }
    time = std::time(NULL);
    now = *std::localtime(&time);
    if (now.tm_sec == (then.tm_sec + 3) % 60)
      goto answer_screen;
    window.clear();
    window.draw(stimulus_msg);
    window.display();
  }

  answer_screen:

  time = std::time(NULL);
  tic = *std::localtime(&time);

  while (window.isOpen()) {
    time = std::time(NULL);
    toc = *std::localtime(&time);
    int time_lapsed = toc.tm_sec - tic.tm_sec;
    //cout << time_lapsed << endl;
    if (time_lapsed >= answering_time)
      goto end_screen;
    while (window.pollEvent(event)) {
      // Close window request
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      }      
      // Key presses
      if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Enter){
          answering_time = answering_time - time_lapsed;
          cout << "answering time: " << answering_time << endl;
          if (answering_time <= 0)
            goto end_screen;
          goto feedback_screen;
        }
      }
    }
    window.clear();
    window.draw(answer_msg);
    window.display();
  }

  feedback_screen:

  time = std::time(NULL);
  then = *std::localtime(&time);

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      // Close window request
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      }      
    }
    time = std::time(NULL);
    std::tm now = *std::localtime(&time);
    if (now.tm_sec == (then.tm_sec + 1) % 60)
      goto stimulus_screen;
    window.clear();
    window.draw(feedback_msg);
    window.display();
  }

  end_screen:

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      // Close window request
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      }      
      // Key presses
      if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Enter){
          answering_time = 6;
          goto stimulus_screen;
        }
      }
    }
    window.clear();
    window.draw(end_msg);
    window.display();
  }
}