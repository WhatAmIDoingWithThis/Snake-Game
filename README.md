# Snake Game
The classic snake game, implemented using C++ in the console

# How to Install
1. Download the repo to your local machine
2. Open the .sln folder with Visual Studio
3. Click Build

Note: This project makes use of a number of Windows only commands, so it only runs on windows. I could fix it to run on Linux/Unix as well, but without a device to test it, I don't think it would be worth it

# Version History
## Version 0.2 (latest)
### Added Features
- Refactored a majority of the code
- Seperated classes into their own files to make code cleaner
- Sped up frame generation by changing the way the snake is drawn to the screen. It is now O(n) time instead of O(n^2) time
- Moved a majority of the game logic from main into the GameBoard object. Main still handles determining game state though
### Known Issues
- Had to remove movement for the moment. I was hoping to change it from checking every frame to listening for keyboard input, but in order to do that I would need to implement threading. I will have to change how the program decides to sleep instead, making controll checks run each frame, and only having the frame redrawn on certain intervals
- Still have the game over being the end of the application. I will likely fix this in the next push
## Version 0.1
### Added Features
- First implementation of the game. Needs major work in a number of areas
- All different textures are mapped to their own characters
- Movement is implemented for the head
### Known issues
- The movement is very janky and unreliable at the moment
- The body pieces don't follow the head, and can potentially become stuck
- Upon game over, the program ends, meaning if the user wants to play again, they must rerun the application
