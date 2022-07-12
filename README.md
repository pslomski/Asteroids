# Asteroids
Remake of classic Atari's Asteroids game

## 1. Introduction

  This is a classic Atari's Asteroids arcade game remake.
Originally it was released in 1979 by Atari Inc. To this day
dozens of clones has been created on virtually any platform.
I wanted this remake to be quite close to the original game
but with a few enhancements. It retains original's simple
vector graphics enriched with some particle effects. Great
care has been carried to create pleasant movement dynamics.
The ship can catch point bonuses and two weapon powerups.
There is also music added. So I hope You will enjoy this
little game as I do.

## 2. Controls

Left arrow - turn left  
Right arrow - turn right  
Up arrow - move forward  
Space - fire weapon  

## 3. Dependencies

### 3.1
SDL2

### 3.2
SDL TTF
Linux:
  sudo apt-get install libsdl2-ttf-dev

### 3.3
Bass

### 3.4
vectorb.ttf font

## 4. Building
In root dir:
  mkdir build
  cd build
  cmake ..
  ninja

output is
  Asteroids(.exe)
  Test(.exe)
  
## 5. UT
./Test.exe --gtest_color=yes --gtest_filter=Rectangle.shouldInit

## 6. 
Managing game states based on article "TetroGL: An OpenGL Game Tutorial in C++ for Win32 platforms - Part 3"
https://www.codeproject.com/Articles/30775/TetroGL-An-OpenGL-Game-Tutorial-in-Cplusplus-for-W