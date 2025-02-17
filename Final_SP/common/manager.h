#pragma once
#include "timer.h"
#include <vector>
#include "../swalib_example/rapidjson/document.h"
#include "../swalib_example/rapidjson/filereadstream.h"

const unsigned int NUM_BALLS = 3;  // Max. num balls.
const float MAX_BALL_SPEED = 480.0f;   // Max vel. of ball (pixels/?).
const float GRAVITY = -150.f;
const float FLOOR = 64.f;

class Entity;
class vec2;
class Document;
class BaseLevel;

class Manager {
private:
    static Manager* instance;
    Timer timer;
public:
    // this three should be private
    Entity* player;
    rapidjson::Document doc;
    std::vector<Entity*> entities;
    std::vector<Entity*> platforms;
    std::vector<Entity*> ladders;
    std::vector<Entity*> powerUps;
    BaseLevel* m_CurrentLevel;

    int reset = 0;

    //singleton
    static Manager* getInstance();
    //getters
    std::vector<Entity*> getEntities();
    std::vector<Entity*> getPlatforms();
    std::vector<Entity*> getLadders();
    std::vector<Entity*> getPowerUps();

    void addEntity(Entity* entity);
    void addPowerUp(Entity* powerUp);

    Entity* getPlayer();
    Timer* getTimer();

    void SetReset(int value);

    void CreateGame();
    void ResetLevel();

    void update();
    const char* entitiesFile = "data/entities.json";
};
