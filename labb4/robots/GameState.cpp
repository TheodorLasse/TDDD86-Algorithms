/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {
        Robot *robot = new Robot();
        while(!isEmpty(*robot)){
            delete robot;
            robot = new Robot();
        }
        robots.push_back(robot);
    }
    teleportHero();
}

GameState::GameState(const GameState& gameState) {
    hero = gameState.hero;
    for (Robot* robot: gameState.robots) {
        robots.push_back(robot->clone());
    }
}

GameState::~GameState() {
    deleteRobots();
}

GameState& GameState::operator = (const GameState& newGameState) {
    if (this != &newGameState) {
        deleteRobots();
        hero = newGameState.hero;
        for (Robot* robot: newGameState.robots) {
            robots.push_back(robot->clone());
        }
    }

    return *this;
}

void GameState::deleteRobots() {
    while (robots.size() > 0) {
        delete robots[robots.size() - 1];
        robots.pop_back();
    }
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const Robot* robot: robots)
        robot->draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Robot* robot: robots)
        robot->moveTowards(hero);
}


void GameState::updateCrashes() {
    for(unsigned i=0; i < robots.size(); ++i){
        for(unsigned o=i+1; o < robots.size(); ++o){
            if(robots[i]->at(*robots[o])){
                robots[i]->doCrash();
                robots[o]->doCrash();
            }
        }
    }
}

int GameState::countJustCrashed()const{
    int numberDestroyed =0;
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->justCrashed())
            numberDestroyed++;
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < robots.size(); ++i){
        if (robots[i]->justCrashed()) {
            auto junk = new Junk(robots[i]->asPoint());
            delete robots[i];
            robots[i] = junk;
        }
    }
}

bool GameState::stillLiveRobots() const {
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->canMove())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for(const Robot* robot: robots){
        if(hero.at(*robot)){
            return true;
        }
    }
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit) const {
    for(const Robot* robot: robots)
        if(robot->at(unit))
            return false;
    return true;
}

