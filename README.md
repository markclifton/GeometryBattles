# Geometry Battles (Geometry Wars Clone)

## 1GAM - January 2019 - Big Bang

### Technical Details     
* Will be written in C++/OpenGL in a Linux environment
* Will use the game engine I have been working on (WIP)
* Will only support keyboard input

* Will start with a project that links the engine and required headers
* Code will be available on a github page, tbd.

### Design Details 
* Player will be a shape that can fire projectiles
* Enemies will be different shapes that will follow the player
* If enemy reaches the player, the game ends
* A score will be kept 
    - Enemies will have different point values (killing rewards points)
    - Time played will reward points
* The player and enemies will be restricted to the same 2d field of play
* The field of play will have clearly defined bounds

### Stretch Goals
* Distort Screen space and add particle effects
* Display the score on the game window (need font handling added to engine)
* Add power-ups and auto-win events

