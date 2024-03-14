//
// player.cpp
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health-= trueDamage;

    cout << name << " took " << trueDamage << " damage!" << endl;

    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

void Player::levelUp() {
    level++;
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action = 0;
    cout << "Select an action: " << endl
         << "1. Attack" << endl
         << "2. Defend" << endl
         << "3. Flee" << endl;

    //TODO: Validate input
    cin >> action;
    Action currentAction;
    Character* target = nullptr;

    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target](){
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target](){
                defend();
            };
            currentAction.speed = getSpeed();

            break;
        case 3:
            if (flee(this)) {
                cout << name << " escapo " << endl;
                //TODO: player fleeing from combat
            } else {
                cout << name << " no escapo " << endl;
            }
            break;
        default:
            cout << "Invalid action" << endl;
            break;
    }

    return currentAction;
}

void Player::defend() {
    int damageReduction = rand() % (defense / 5) + defense / 10;
    defense += damageReduction;
    cout << name << " se defiende " << endl;
}

bool Player::flee(Character* target) {
    int speedDifference = this->getSpeed() - target->getSpeed();
    if (speedDifference > 0) {
        cout << name << " fue suficientemente rapido " << endl;
        return true;
    } else if (speedDifference <= 0 && rand() % 2 == 0) {
        cout << name << " no fue mas rapido que " << target->getName() << "pero tubo suerte" << endl;
        return true;
    } else {
        cout << name << " no tiene la oportunidad de desertar " << endl;
        return false;
    }
}