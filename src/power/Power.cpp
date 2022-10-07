/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Power
*/

#include "Power.hpp"

Power::Power()
{
    this->bombUp = 0;
    this->fireUp = 0;
    this->speedUp = 0;
    this->wallPass = false;
}

Power::~Power()
{
}

int Power::getBombUp() const
{
    return this->bombUp;
}

int Power::getSpeedUp() const
{
    return this->speedUp;
}

int Power::getFireUp() const
{
    return this->fireUp;
}

bool Power::getWallPass() const
{
    return this->wallPass;
}

void Power::setBombUp(int newBombUp)
{
    this->bombUp = newBombUp;
}

void Power::setSpeedUp(int newSpeedUp)
{
    this->speedUp = newSpeedUp;
}

void Power::setFireUp(int newFireUp)
{
    this->fireUp = newFireUp;
}

void Power::setWallPass(bool pass)
{
    this->wallPass = pass;
}