//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Star.h"
#include "GameStart.h"
#include "Sound.h"
//#include "Pause.h"
#include "Vector.h"
#include "WorldManager.h"

void loadResources(void) {
    // Load  saucer  sprite.
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
    // Load  ship  sprite.
    RM.loadSprite("sprites/ship-spr.txt", "ship");
    // Load  bullet  sprite.
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    // Load  explosion  sprite.
    RM.loadSprite("sprites/explosion-spr.txt", "explosion");
    // Load  gameover  sprite.
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    // Load  gamestart  sprite.
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
}

void populateWorld(void) {
    RM.loadSound("sounds/fire.wav", "fire");
    RM.loadSound("sounds/explode.wav", "explode");
    RM.loadSound("sounds/nuke.wav", "nuke");
    RM.loadSound("sounds/game-over.wav", "game over");

    RM.loadMusic("sounds/start-music.wav", "start music");

    for (int i = 0; i < 16; i++) {
        new Star;
    }

    GameStart *g = new GameStart();

    // Enable player to pause the game.
    //new df::Pause(df::Keyboard::F10);
}

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  //LM.setFlush(true);
  LM.setLogToScreen();

  // Set world boundaries to 80 horizontal, 50 vertical
  //df::Vector corner(0, 0);
  //df::Box world_boundary(corner, 80, 50);
  //WM.setBoundary(world_boundary);

  // Set view to 80 horizontal, 24 vertical
  //df::Box view(corner, 80, 24);
  //WM.setView(view);

  // Load game resoures.
  loadResources();

  // Populate game world with some objects.
  populateWorld();

  // Show splash screen.
  // df::splash();

  GM.run();

  // Shut everything down.
  GM.shutDown();
}

