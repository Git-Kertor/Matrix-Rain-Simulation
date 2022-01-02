#include "main.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <sfml/Graphics.hpp>

const int columns = 20;
//This array will make sure each column is a fixed length
int rainLengths[20];
//Store possible symbols seen in the rain
std::string symbols[2] = { "0", "1" };

//returns next string in rain sequence
std::string nextFrame(std::string input, int i, bool isGreen)
{
    bool addSpace = rainLengths[i] <= 0;
    if (rainLengths[i] == 15 && !isGreen) {
        input.insert(0, symbols[rand() % 2] + "\n");
    }
    else if (rainLengths[i] != 15 && !addSpace && isGreen) {
        input.insert(0, symbols[rand() % 2] + "\n");
    }
    else {
        input.insert(0, "\n");
    }
    //If rain string is too long, remove end
    if (input.length() > 20) { input.pop_back(); }
    rainLengths[i] -= 1;
    //This will randomize the spaces between each rain segment
    if (addSpace && rand() % 100 < 5) {
        rainLengths[i] = 15;
    }
    return input;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Matrix Rain");
    sf::Font mainFont;
    mainFont.loadFromFile("font.ttf");

    sf::Text greenRain[columns];
    sf::Text whiteRain[columns];

    std::string greenRainString[columns];
    std::string whiteRainString[columns];

    //Initialization
    for (int i = 0; i < columns; i++) {
        greenRain[i].setFont(mainFont);
        greenRain[i].setFillColor(sf::Color::Green);
        greenRain[i].setCharacterSize(30);
        greenRain[i].setPosition(30 * i, 0);
        greenRainString[i] = "";

        whiteRain[i].setFont(mainFont);
        whiteRain[i].setFillColor(sf::Color::White);
        whiteRain[i].setCharacterSize(30);
        whiteRain[i].setPosition(30 * i, 0);
        whiteRainString[i] = "";

        rainLengths[i] = 0;
    }

    while (window.isOpen())
    {
        sf::Event event;
        //Delay between frames
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        for (int i = 0; i < columns; i++) {
            greenRainString[i] = nextFrame(greenRainString[i], i, true);
            whiteRainString[i] = nextFrame(whiteRainString[i], i, false);
            greenRain[i].setString(greenRainString[i]);
            whiteRain[i].setString(whiteRainString[i]);
            window.draw(greenRain[i]);
            window.draw(whiteRain[i]);
        }
        window.display();
    }

    return 0;
}