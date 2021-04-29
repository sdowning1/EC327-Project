// Copyright 2021
// Avani Sheth asheth@bu.edu
// Daniel Cabrera dcabrera@bu.edu
// Joshua Monroy jmonroy@bu.edu
// Samantha Downing sdown@bu.edu

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::to_string;
using std::vector;

// return average accuracy and average longest sequence
vector<float> get_averages(){
  vector<float> averages;
  std::ifstream scoreboard;
  scoreboard.open("scoreboard.txt");
  string str;
  int count = 0;
  vector<string> accuracies;
  vector<string> max_lengths;

  // get data from txt file
  while (scoreboard >> str){
    if(count == 0){
      accuracies.push_back(str);
      count++;
    }
    else{
      max_lengths.push_back(str);
      count = 0;
    }
  }

  // compute average accuracy
  float average_accuracy;
  float current_value;
  float running_sum = 0;
  for (int i = 0; i < accuracies.size(); ++i) {
    current_value = std::stof(accuracies.at(i));
    running_sum = running_sum + current_value;
  }
  average_accuracy = running_sum / (float) accuracies.size();
  averages.push_back(average_accuracy);

  // compute average max_length
  float average_length;
  running_sum = 0;
  for (int i = 0; i < max_lengths.size(); ++i) {
    current_value = std::stoi(max_lengths.at(i));
    running_sum = running_sum + current_value;
  }
  average_length = running_sum / (float) max_lengths.size();
  averages.push_back(average_length);

  scoreboard.close();

  return averages;
}

// appends accuracy and max_length to the text file
void update_scoreboard(float accuracy, float max_length){
  std::ofstream scoreboard;
  scoreboard.open("scoreboard.txt", std::ios_base::app);
  scoreboard << '\n' << to_string(accuracy) << " " << to_string(max_length) << endl;
  scoreboard.close();
}

// generates random sequence of len numbers and letters
string gen_random(const int len) {
    
    string tmp;
    static const char alphanum[] =
        "0123456789"
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

  // Window
  int window_size = 800;
  sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Memory Game");
  sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x / 2.5f,
                              window.getSize().y / 2.0f);
  window.setFramerateLimit(10);

  //Welcome Message
  string welcome_msg = "                     WELCOME TO MEMORY TESTER!\n";
  string welcome_msg2 = "\nYou'll be shown a set of characters on the screen,";
  welcome_msg2 = welcome_msg2 + "\n             Try to remember the precise order.";
  welcome_msg2 = welcome_msg2 + "\n\nAfter it disappears, type the EXACT sequence";
  welcome_msg2 = welcome_msg2 + "\n                                and press ENTER.";
  string welcome_msg3 = "Press";
  string welcome_msg4 = "  ENTER";
  string welcome_msg5 = "     to start MEMORY TESTER.";
  sf::Text welcome, welcome2, welcome3, welcome4, welcome5;
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  welcome.setFont(font);
  welcome.setFillColor(sf::Color::Blue);
  welcome.setCharacterSize(window_size/30);
  welcome.setString(welcome_msg);
  welcome.setPosition(window_size/10,window_size/10);

  welcome2.setFont(font);
  welcome2.setFillColor(sf::Color::White);
  welcome2.setCharacterSize(window_size/30);
  welcome2.setString(welcome_msg2);
  welcome2.setPosition(100,100);

  welcome3.setFont(font);
  welcome3.setFillColor(sf::Color::White);
  welcome3.setCharacterSize(window_size/30);
  welcome3.setString(welcome_msg3);
  welcome3.setPosition(170,400);

  welcome4.setFont(font);
  welcome4.setFillColor(sf::Color::Green);
  welcome4.setCharacterSize(window_size/30);
  welcome4.setString(welcome_msg4);
  welcome4.setPosition(230,400);

  welcome5.setFont(font);
  welcome5.setFillColor(sf::Color::White);
  welcome5.setCharacterSize(window_size/30);
  welcome5.setString(welcome_msg5);
  welcome5.setPosition(300,400);

  // For User Input
  sf::String userin;
  sf::Text user_input;
  user_input.setFont(font);
  user_input.setFillColor(sf::Color::White);
  user_input.setCharacterSize(window_size/20);
  user_input.setPosition(windowCenter);

  // For random Gen
  int randlen = 1;
  sf::String rangen;
  sf::Text ran_gen;
  ran_gen.setFont(font);
  ran_gen.setFillColor(sf::Color::White);
  ran_gen.setCharacterSize(window_size/20);
  ran_gen.setPosition(windowCenter);

  // For comparison
  sf::String compans;
  sf::Text comp_ans;
  comp_ans.setFont(font);
  comp_ans.setFillColor(sf::Color::White);
  comp_ans.setCharacterSize(window_size/20);
  comp_ans.setPosition(window_size/3, window_size/2.1);

  // Instructions
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

  // Timer
  string timer_str = "30";
  sf::Text timer_msg;
  timer_msg.setFont(font);
  timer_msg.setFillColor(sf::Color::White);
  timer_msg.setCharacterSize(window_size/30);
  timer_msg.setString(timer_str);
  timer_msg.setPosition(window_size/10,window_size*9/10);

  // Game variables
  int answering_time = 30;
  int consecutive_wrong = 0;
  int correct_answers = 0;
  int total_answers = 0;
  int max_randlen = 0;

  // Timing variables
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
    window.draw(welcome2);
    window.draw(welcome3);
    window.draw(welcome4);
    window.draw(welcome5);
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
    window.draw(timer_msg);
    window.display();
  }

  answer_screen:

  then = std::time(NULL);

  while (window.isOpen()) {
    now = std::time(NULL);
    time_lapsed = now - then;
    seconds_passed = *std::localtime(&time_lapsed);
    if(seconds_passed.tm_sec >= 1){
      then = std::time(NULL);
      answering_time = answering_time - 1;
      timer_str = to_string(answering_time);
      timer_msg.setString(timer_str);
    }
    if(answering_time <= 0)
      goto end_screen;

    while (window.pollEvent(event)) {
      // Close window request
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      } 
      // Read in user intput and display
      if (event.type == sf::Event::TextEntered) {
        userin += event.text.unicode;
      } else if (event.key.code == sf::Keyboard::BackSpace and !(userin.isEmpty())) {
          userin.erase(userin.getSize() - 1);
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
            consecutive_wrong++;
            if (consecutive_wrong > 1 and randlen != 1){
              consecutive_wrong = 0;
              randlen = randlen - 1;
            } 
            compans = "Try Again";
          }
          userin = "";
          now = std::time(NULL);
          time_lapsed = now - then;
          seconds_passed = *std::localtime(&time_lapsed);
          //answering_time = answering_time - seconds_passed.tm_sec;
          goto feedback_screen;
        }
      }
    }
    user_input.setString(userin);
    window.clear();
    window.draw(user_input);
    window.draw(answer_msg);
    window.draw(timer_msg);
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
    if (seconds_passed.tm_sec >= 2){
      window.clear();
      goto stimulus_screen;
    }

    if (compans == "Correct"){
      window.clear(sf::Color(0, 200, 0, 255));
    }
    else
      window.clear(sf::Color(255, 0, 0, 255));
    comp_ans.setString(compans);
    window.draw(comp_ans);
    window.display();
  }

  end_screen:

  std::vector<float> averages = get_averages();
  float average_accuracy = averages.at(0);
  float average_maxlength = averages.at(1);
  float accuracy = (float)correct_answers/(float)total_answers;
  float percent_accuracy = accuracy/average_accuracy;
  float percent_maxlength = (float)max_randlen/average_maxlength;

  string end_str = "You got " + to_string(correct_answers);
  end_str = end_str + "/" + to_string(total_answers) + " correct.\n" + to_string(percent_accuracy) + " compared to average.\n\n";
  end_str = end_str + "Your longest sequence was " + to_string(max_randlen) + " characters long.\n";
  end_str = end_str + to_string(percent_maxlength) + " compared to average.\n\n";
  end_str = end_str + "Press ENTER to play again!";
  sf::Text end_msg;
  end_msg.setFont(font);
  end_msg.setFillColor(sf::Color::White);
  end_msg.setCharacterSize(window_size/30);
  end_msg.setString(end_str);
  end_msg.setPosition(window_size/10,window_size/10);

  update_scoreboard(accuracy, max_randlen);

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
          answering_time = 30;
          timer_str = to_string(answering_time);
          timer_msg.setString(timer_str);
          consecutive_wrong = 0;
          correct_answers = 0;
          total_answers = 0;
          max_randlen = 0;
          randlen = 1;
          goto stimulus_screen;
        }
      }
    }
    window.clear();
    window.draw(end_msg);
    window.display();
  }
}
