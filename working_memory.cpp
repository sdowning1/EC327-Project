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
using std::to_string;


string gen_random(const int len) {
    
    string tmp;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    srand( (unsigned) time(NULL) * getpt());

    tmp.reserve(len);

    for (int i = 0; i < len; ++i) 
        tmp += alphanum[rand() % (sizeof(alphanum) - 1)];

    return tmp;
}

int main() {
  // initialize variables
  sf::Event event;
  int randlen = 3;
  int window_size = 800;
  sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Memory Game");
  sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x / 3.0f,
                              window.getSize().y / 2.0f);
  window.setFramerateLimit(10);

  string welcome_msg = "Hello,\n";
  welcome_msg = welcome_msg + "\nYou'll be shown a set of characters on the screen,";
  welcome_msg = welcome_msg + "\ntry to remember them.";
  welcome_msg = welcome_msg + "\n\nAfter they disappear, type the EXACT sequence";
  welcome_msg = welcome_msg + "\nand press ENTER.";
  welcome_msg = welcome_msg + "\n\nPress ENTER to start.";
  sf::Text welcome;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  welcome.setFont(font);
  welcome.setFillColor(sf::Color::White);
  welcome.setCharacterSize(window_size/30);
  welcome.setString(welcome_msg);
  welcome.setPosition(window_size/10,window_size/10);

  // For User Input
  sf::String userin;
  sf::Text user_input;
  user_input.setFont(font);
  user_input.setFillColor(sf::Color::White);
  user_input.setCharacterSize(window_size/20);
  user_input.setPosition(windowCenter);

  // For random Gen
  sf::String rangen;
  sf::Text ran_gen;
  ran_gen.setFont(font);
  ran_gen.setFillColor(sf::Color::White);
  ran_gen.setCharacterSize(window_size/20);
  ran_gen.setPosition(windowCenter);
  //rangen = gen_random(randlen);
  //ran_gen.setString(rangen);

  // For comparison
  sf::String compans;
  sf::Text comp_ans;
  comp_ans.setFont(font);
  comp_ans.setFillColor(sf::Color::White);
  comp_ans.setCharacterSize(window_size/20);
  comp_ans.setPosition(windowCenter);

  string stimulus_str = "Remember the sequence:";
  sf::Text stimulus_msg;
  stimulus_msg.setFont(font);
  stimulus_msg.setFillColor(sf::Color::White);
  stimulus_msg.setCharacterSize(window_size/30);
  stimulus_msg.setString(stimulus_str);
  stimulus_msg.setPosition(window_size/10,window_size/10);

  string answer_str = "Type the sequence and press ENTER";
  sf::Text answer_msg;
  answer_msg.setFont(font);
  answer_msg.setFillColor(sf::Color::White);
  answer_msg.setCharacterSize(window_size/30);
  answer_msg.setString(answer_str);
  answer_msg.setPosition(window_size/10,window_size/10);

  int answering_time = 30;
  int consecutive_wrong = 0;

  int correct_answers = 0;
  int total_answers = 0;
  int max_randlen = 3;

  std::time_t now;
  std::time_t then;
  std::time_t time_lapsed;

  std::tm seconds_passed;

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

  bool refresh_stimulus = true;

  then = std::time(NULL);

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      // Close window request
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      }      
    }

    if (refresh_stimulus) {
      rangen = gen_random(randlen);
      ran_gen.setString(rangen);
      refresh_stimulus = false;
    }

    now = std::time(NULL);
    time_lapsed = now - then;
    seconds_passed = *std::localtime(&time_lapsed);
    if (seconds_passed.tm_sec >= 3)
      goto answer_screen;

    window.clear();
    window.draw(ran_gen);
    window.draw(stimulus_msg);
    window.display();
  }

  answer_screen:

  then = std::time(NULL);

  while (window.isOpen()) {
    now = std::time(NULL);
    time_lapsed = now - then;
    seconds_passed = *std::localtime(&time_lapsed);
    if (answering_time - seconds_passed.tm_sec <= 0){
      userin = "";
      user_input.setString(userin);
      goto end_screen;
    }

    while (window.pollEvent(event)) {
      // Close window request
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      } 
      // Read in user intput and display
      if (event.type == sf::Event::TextEntered) {
        userin += event.text.unicode;
      }     
      // Key presses
      if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Enter){
          total_answers++;
          if (rangen == userin) {
            if (max_randlen < randlen)
              max_randlen = randlen;
            correct_answers++;
            randlen++;
            consecutive_wrong = 0;
            compans = "Correct";
          } 
          else{
            if (consecutive_wrong > 1){
              consecutive_wrong = 0;
              randlen = randlen - 1;
            } 
            else consecutive_wrong++;
            compans = "Try Again";
          }
          //cout << consecutive_wrong << endl;
          userin = "";
          now = std::time(NULL);
          time_lapsed = now - then;
          seconds_passed = *std::localtime(&time_lapsed);
          answering_time = answering_time - seconds_passed.tm_sec;
          goto feedback_screen;
        }
        if (event.key.code == sf::Keyboard::BackSpace){
          // userin.erase(userin.getSize() - 1,1);
          userin.erase(userin.getSize() - 1);
        }
      }
    }
    user_input.setString(userin);
    window.clear();
    window.draw(user_input);
    window.draw(answer_msg);
    window.display();
  }

  feedback_screen:

  then = std::time(NULL);

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      // Close window request
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      }      
    }

    now = std::time(NULL);
    time_lapsed = now - then;
    seconds_passed = *std::localtime(&time_lapsed);
    if (seconds_passed.tm_sec >= 1)
      goto stimulus_screen;

    //compans = checkans(rangen, userin);
    comp_ans.setString(compans);
    window.clear();
    window.draw(comp_ans);
    window.display();
  }

  end_screen:

  string end_str = "You got " + to_string(correct_answers);
  end_str = end_str + "/" + to_string(total_answers) + " correct.\n";
  end_str = end_str + "Your longest sequence was " + to_string(max_randlen) + " characters long.\n";
  end_str = end_str + "Press ENTER to play again!";
  sf::Text end_msg;
  end_msg.setFont(font);
  end_msg.setFillColor(sf::Color::White);
  end_msg.setCharacterSize(window_size/30);
  end_msg.setString(end_str);
  end_msg.setPosition(window_size/10,window_size/10);

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
          answering_time = 10;
          goto stimulus_screen;
        }
      }
    }
    window.clear();
    window.draw(end_msg);
    window.display();
  }
}