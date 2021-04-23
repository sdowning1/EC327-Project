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

string checkans(string rand_s, string user_s) {
    string compstr = "";
    int x = rand_s.compare(user_s);

    if (x != 0) {
        compstr = "Incorrect";
    } else {
        compstr = "Correct";
    }
    return compstr;
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
  rangen = gen_random(randlen);
  ran_gen.setString(rangen);

  // For comparison
  sf::String compans;
  sf::Text comp_ans;
  comp_ans.setFont(font);
  comp_ans.setFillColor(sf::Color::White);
  comp_ans.setCharacterSize(window_size/20);
  comp_ans.setPosition(windowCenter);

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
    window.draw(ran_gen);
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

    // Read in user intput and display
    if (event.type == sf::Event::TextEntered) {
      userin += event.text.unicode;
      user_input.setString(userin);
    }

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
    window.draw(user_input);
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

    compans = checkans(rangen, userin);
    comp_ans.setString(compans);

    if (now.tm_sec == (then.tm_sec + 1) % 60)
      goto stimulus_screen;
    window.clear();
    window.draw(comp_ans);
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