/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Player
*/

#include "Player.hpp"
#include "Map.hpp"
#include "raymath.h"
#include "unistd.h"

Player::Player(const std::string &name, const Vector3 &playerPos, const std::vector<Input::Button> &keys, const int &playerId)
: _raylib(std::make_unique<Raylib>())
{
    this->_name = name;
    this->_playerPos = playerPos;
    this->_keyBinds = keys;
    this->_playerId = playerId;
    this->_activeBomb = 0;
    this->_playerModel = LoadModel("../assets/test/char3.iqm");
    this->_playerTexture = LoadTexture("../assets/character/venom.png");
    this->_playerModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->_playerTexture;
    this->collision = false;
    this->roll = 0.0f;
    this->isDead = false;
	_power = std::make_shared<Power>();
    if (this->_playerId == 0)
        this->skinColor = WHITE;
    else if (this->_playerId == 1)
        this->skinColor = YELLOW;
    else if (this->_playerId == 2)
        this->skinColor = BLUE;
    else if (this->_playerId == 3)
        this->skinColor = RED;
}

void Player::setPlayerRoll(const float &roll)
{
    this->_roll = roll;
}

float Player::getPlayerRoll() const
{
    return (this->_roll);
}

Player::~Player()
{
	UnloadTexture(_playerTexture);
	UnloadModel(_playerModel);
}

void Player::setPlayerTransform(Vector3 trans)
{
    this->_playerModel.transform = MatrixRotateXYZ(trans);
}

Model Player::getPlayerModel() const
{
    return this->_playerModel;
}

void Player::drawPlayer()
{
    DrawModel(this->_playerModel, this->_playerPos, 1.0f, WHITE);
}

int Player::getPlayerId() const
{
    return (this->_playerId);
}

bool Player::getIsDead() const
{
    return this->isDead;
}

void Player::setIsDead(const bool &dead)
{
    this->isDead = dead;
}

std::string Player::getPlayerName() const
{
    return (this->_name);
}

Vector3 Player::getPlayerPos() const
{
    return (this->_playerPos);
}

void Player::movePlayerUp()
{
    this->_playerPos.z -= 2.0f;
}

void Player::movePlayerDown()
{
    this->_playerPos.z += 2.0f;
}

void Player::movePlayerLeft()
{
    this->_playerPos.x -= 2.0f;
}

void Player::movePlayerRight()
{
    this->_playerPos.x += 2.0f;
}

int Player::getActiveBomb() const
{
    return (this->_activeBomb);
}

void Player::movePlayer()
{
    //if ( (KEY_RIGHT))
    //    this->_playerPos.x += 0.2f;
    //else if (IsKeyDown(KEY_LEFT))
    //    this->_playerPos.x -= 0.2f;
    //else if (IsKeyDown(KEY_DOWN))
    //    this->_playerPos.z += 0.2f;
    //else if (IsKeyDown(KEY_UP))
    //    this->_playerPos.z -= 0.2f;
}

Input::Button Player::checkAction(const Input::Button &key, std::vector<std::shared_ptr<Bomb>> &bomb, const Map &nMap)
{
    //Bomb newBomb = new Bomb(this->_playerPos);
    //Bomb newBomb = Bomb(this->_playerPos);

    // if (key == Input::Button::UP)
    //     this->movePlayerUp();
    // else if (key == Input::Button::DOWN)
    //     this->movePlayerDown();
    // else if (key == Input::Button::LEFT)
    //     this->movePlayerLeft();
    // else if (key == Input::Button::RIGHT)
    //     this->movePlayerRight();
    // else if (key == Input::Button::SPACEBAR) {
    //     bomb.push_back(newBomb);                ///////// A AJOUTER
    // }
	if (key == _keyBinds.back())
		std::cout << (key == _keyBinds.back()) << " && active = " << this->_activeBomb << std::endl;
    if (key == _keyBinds.back() && (this->_activeBomb < this->getPower()->getBombUp() + 1)
        && nMap.getMap()[_playerPos.z / 2][_playerPos.x / 2] != '1') {
        bomb.push_back(std::make_shared<Bomb>(_playerPos));
        this->_activeBomb += 1;
    }
	return Input::Button::NONE;
}

void Player::setActiveBomb(int nb)
{
    this->_activeBomb += nb;
}

std::shared_ptr<Power> Player::getPower() const
{
    return _power;
}

void Player::checkPowerUp()
{}

PlayerType Player::getType() const
{
	return PLAYER;
}

std::vector<Input::Button> Player::getKeys() const
{
	return _keyBinds;
}

Color Player::getColor() const
{
    return this->skinColor;
}

void Player::setColor(const Color &skin)
{
    this->skinColor = skin;
}