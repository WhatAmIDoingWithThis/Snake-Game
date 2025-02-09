# Snake Game
The classic snake game, implemented using C++ in the console

# How to Install
## Runnable Executable (Recommended)
This way is the most painless way to test the code. No effort on your part, but not necessarily the latest release.
1. Download the .exe from the releases
2. Run the .exe
## Build From Source Code (Latest)
This requires that you have Visual Studio installed, but allows you to compile the latest code directly, meaning you're not waiting for releases.
1. Download the repo to your local machine
2. Open the .sln folder with Visual Studio
3. Click Build

Note: This project makes use of a number of Windows only commands, so it only runs on windows. I could fix it to run on Linux/Unix as well, but without a device to test it, I don't think it would be worth it

# Version History

## Version 1.1 (Current)
Added color now. Also sped up frame generation
### Added Features
- Color! Snake is green, apples are red. Pretty basic stuff
- 300% frame generation speed. Turns out clearing the screen between frames is very inefficient. So now I just draw over the previous
### Known Issues
- Still have the double keypress for game over
- Apparantly a bug from 1.0, but sometimes restarting the game doesn't restart the input listener thread, meaning you have no controls. Need to look into why this is happening.

## Version 1.0 (Release)
Full feature completion. This does not mean end of development. I still have plans for adding some more stuff, but I feel at this point it is enough to call the game complete
### Added Features
- You can replay the game when you die
- Before starting, you can set certain parameters, like size or speed
### Known Issues
- Sometimes you have to press a key twice during the gameover screen. This occurs because the way I implemented the user input listener. I could have done a polling thread, where it is constantly checking to see if any keys are currently being pressed, but this is very cpu intensive, and I didn't want to do that. So what I have implemented now is a event listener, which waits for the user to input a character and then decides what to do. Unfortunately, there is no way to tell it to stop actively listening, so I have to have it check to see if it should still be running before each listen. This means that sometimes you have to press a key during the end screen to make the thread know it should be closed, then press another key to loop back to the main menu.

## Version 0.3
Functionality update. You can play the game now
### Added Features
- Finally added movement back in (Remember that from ver 0.1?)
- Movement is way better now. Instead of constantly checking if you were pressing direction keys, it now listens for keyboard presses.
- Body parts all follow (Hah, version 0.1 didn't do that!)
- Implemented corners for body parts, so they aren't just vertical and horizontal
- You can eat apples to grow
### Known Issues
- I haven't fixed the one game per run issue yet. I kinda forgot about it.

## Version 0.2
Rewrote the code in order to make it cleaner and easier to modify for future versions
### Added Features
- Seperated classes into their own files to make code cleaner
- Sped up frame generation by changing the way the snake is drawn to the screen. It is now O(n) time instead of O(n^2) time
- Moved a majority of the game logic from main into the GameBoard object. Main still handles determining game state though
### Known Issues
- Had to remove movement for the moment. I was hoping to change it from checking every frame to listening for keyboard input, but in order to do that I would need to implement threading. I will have to change how the program decides to sleep instead, making controll checks run each frame, and only having the frame redrawn on certain intervals
- Still have the game over being the end of the application. I will likely fix this in the next push

## Version 0.1
First implementation of the game. Needs major work in a number of areas
### Added Features
- All different textures are mapped to their own characters
- Movement is implemented for the head
### Known issues
- The movement is very janky and unreliable at the moment
- The body pieces don't follow the head, and can potentially become stuck
- Upon game over, the program ends, meaning if the user wants to play again, they must rerun the application
