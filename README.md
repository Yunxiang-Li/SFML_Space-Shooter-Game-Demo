# SFML_Space-Shooter-Game

A simple 2d space shooter game created by C++ and SFML(Simple and Fast Multimedia Library) with CLion IDE.

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

## Table of Contents

- [Background](#Background)
- [Exhibition](#Exhibition)
- [Install](#install)
- [Ideas](#Ideas)
- [Structure](#Structure)
- [Maintainers](#Maintainers)
- [License](#license)

## Background

Unlike game engines such like Unity or Unreal, building game by pure C++ is not very convenient. But with the help of SFML(Simple and Fast Multimedia Library), we can build a 2d game from scratch. 

Game development comprises the combination of many different aspects such as game logics, graphics, audio, user input, physics and much more. I want to learn and enjoy this whole process of game development by this project.

## Exhibition

Needs to be updated...

## Install

I Use C++ language, [SFML(Simple and Fast Multimedia Library)](https://www.sfml-dev.org/index.php) and CLion (an IDE) under Windows 10 environment for this project.

[CLion Download](https://www.jetbrains.com/clion/download/#section=windows)<br>

[SFML Tutorials](https://www.sfml-dev.org/tutorials/2.5/)

## Ideas

1. Complete main game loop by processing each event and real time input while window is open and set time fixed for each frame using `sf::Clock` and `sf::Time` class provided by SFML.

2. Use C++ template and inline files to build resource holder for each type of resource(Textures, Fonts and so on).

3. Use multiple inheritance to build the game world. `SceneNode` class as a virtual base class which controls the whole game world and each layer's entrance(for instance, background layer, air layer and son on). `SpriteNode` class is a derived class which inherits `SceneNode` class and take control of background settings. `Entity` class is a intermediate class which inherits `SceneNode` class and represents each entity in the game. `Aircraft` class is a derived class which inherits `Entity` class and take control of all aircraft objects' behaviour.

4. Use Command pattern to handle each user event or real time input as a command, push each command into the command queue and execute and pop each front command one by one later when we need to update and render the game. 

5. Use more C++ template and inline files to write handy methods(`toString`, `CenterOrgin` and so on) to help us reduce redundant codes and meanwhile provide useful functions we need. 

6. Then I consider the game as different states. I create a **State** class indicates a general state and we have **TitleState**, **MenuState**, **GameState** and **PauseState** which inherit the **State** class. When the player play the game, the game state will change according to what player is doing and we push all states into a state stack and handle one by one per update.

## Structure

(Here should be an UML model to display the structure of the program).

The whole project contains four main folders, **Screenshots and GIFs** folder, **Media** folder, **include** folder and **src** folder.

**Screenshots and GIFs** folder contains all screenshots and GIFs needed for exhibition.

**src** folder contains altogether **17** `C++` source(**.cpp**) files:

**include** folder contains altogether **22** `C++` header(20 **.hpp** files and 2 **.inl** files) files:

**Media** folder contains all **media** files(fonts, pictures, textures).

## Maintainers

[@Yunxiang-Li](https://github.com/Yunxiang-Li).

## License

[MIT license](https://github.com/Yunxiang-Li/SFML_Space-Shooter-Game/blob/main/LICENSE)
