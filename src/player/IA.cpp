/*
** EPITECH PROJECT, 2022
** indie
** File description:
** IA
*/

#include "IA.hpp"
#include "raymath.h"
#include "Map.hpp"

Indie::IA::IA(const Vector3 &spawn, const std::string &name, const int &id)
: _name(name), _id(id), isDead(false), _clock(std::chrono::steady_clock::now())
{
	_posX = spawn.x;
	_posY = spawn.z;
	_posGoalX = _posX;
	_posGoalY = _posY;
	_playerModel = LoadModel("../assets/test/char3.iqm");
    _playerTexture = LoadTexture("../assets/character/venom.png");
	_playerModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _playerTexture;
	_power = std::make_shared<Power>();
	if (this->_id == 0)
        this->skinColor = WHITE;
    else if (this->_id == 1)
        this->skinColor = YELLOW;
    else if (this->_id == 2)
        this->skinColor = BLUE;
    else if (this->_id == 3)
        this->skinColor = RED;
}

Indie::IA::~IA()
{
	UnloadTexture(_playerTexture);
	UnloadModel(_playerModel);
}

void Indie::IA::newGoal(const std::vector<std::string> &map)
{
   if (!isDangerous(map, _posY / 2, _posX / 2))
       return newGoalOffense(map);
   else
       return newGoalDefense(map);
}

Input::Button Indie::IA::checkAction(const Input::Button &key, std::vector<std::shared_ptr<Bomb>> &bomb, const Map &map)
{
	std::chrono::steady_clock::time_point tmp = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(tmp - _clock);
	Input::Button choice = Input::Button::NONE;

	static_cast<void>(key);
	if (time_span.count() < 1.2)
		return Input::Button::NONE;
	_clock = std::chrono::steady_clock::now();
	if (_posX > _posGoalX && (_posX - 2) >= 0) {
		choice = Input::Button::LEFT;
	} else if (_posX < _posGoalX && (_posX + 2) <= 24) {
		choice = Input::Button::RIGHT;
	} else if (_posY > _posGoalY && (_posY - 2) >= 0) {
		choice = Input::Button::UP;
	} else if (_posY < _posGoalY && (_posY + 2) <= 22) {
		choice = Input::Button::DOWN;
	}
    if ((this->_activeBomb < this->getPower()->getBombUp() + 1)
        && (map.getMap()[_posY / 2][_posX / 2] != '1') && (std::rand() % (3-1 + 1) + 1) == 1) {
        bomb.push_back(std::make_shared<Bomb>(getPlayerPos()));
        this->_activeBomb += 1;
    }
	if (_posX == _posGoalX && _posY == _posGoalY)
		newGoal(map.getMap());
	_saveMap = map.getMap();
	return choice;
}

void Indie::IA::newGoalOffense(const std::vector<std::string> &map)
{
  short n = std::rand() % 4;
  char dir_x[] = {-1,0,1,0};
  char dir_y[] = {0,-1,0,1};

   if (_posX == 0 && dir_x[n] == -1)
       dir_x[n] = 0;
   if (_posY == 0 && dir_y[n] == -1)
       dir_y[n] = 0;
   if (_posX == 24 && dir_x[n] == 1)
       dir_x[n] = 0;
   if (_posY == 22 && dir_y[n] == 1)
       dir_y[n] = 0;
   if (!isDangerous(map, _posY / 2 + dir_y[n], _posX / 2 + dir_x[n]) &&
       map[_posY / 2 + dir_y[n]][_posX / 2 + dir_x[n]] == '0') {
       _posGoalX = _posX + dir_x[n] * 2;
       _posGoalY = _posY + dir_y[n] * 2;
   }
}

bool Indie::IA::isDangerous(const std::vector<std::string> &map, int y, int x)
{
   if (y == -1)
       y += 1;
   if (x == -1)
       x += 1;
   if (x == 13)
       x -= 1;
   if (y == 12)
       y -= 1;
   return map[y][x] == '1';
}

void Indie::IA::newGoalDefense(const std::vector<std::string> &map)
{
   if (static_cast<std::size_t>(_posX / 2 + 1) < map[_posY / 2].size() - 1 && map[_posY / 2][_posX / 2 + 1] == 0 && !isDangerous(map, _posY / 2, _posX / 2 + 1)) {
       _posGoalX = _posX + 2;
       _posGoalY = _posY;
   }
   else if (_posX / 2 - 1 >= 0 && map[_posY / 2][_posX / 2 - 1] == '0' && !isDangerous(map, _posY / 2, _posX / 2 - 1)) {
       _posGoalX = _posX - 2;
       _posGoalY = _posY;
   }
   else if (static_cast<std::size_t>(_posY / 2 + 1) < map.size() - 1 && map[_posY / 2 + 1][_posX / 2] == 0 && !isDangerous(map, _posY / 2 + 1, _posX / 2)) {
       _posGoalY = _posY + 2;
       _posGoalX = _posX;
   }
   else if (_posY / 2 - 1 >= 0 && map[_posY / 2 - 1][_posX / 2] == '0' && !isDangerous(map, _posY / 2 - 1, _posX / 2)) {
       _posGoalY = _posY - 2;
       _posGoalX = _posX;
   }
   else {
       _posGoalY = _posY;
       _posGoalX = _posX;
   }
}

PlayerType Indie::IA::getType() const
{
	return PlayerType::IA;
}

void Indie::IA::checkPowerUp()
{}

float Indie::IA::getPosX() const
{
   return (_posX);
}

float Indie::IA::getPosY() const
{
   return (_posY);
}

int Indie::IA::getPlayerId() const
{
   return _id;
}

std::string Indie::IA::getPlayerName() const
{
   return _name;
}

Vector3 Indie::IA::getPlayerPos() const
{
	return {static_cast<float>(_posX), -11.0, static_cast<float>(_posY)};
}

Model Indie::IA::getPlayerModel() const
{
	return _playerModel;
}

void Indie::IA::setPlayerTransform(Vector3 trans)
{
	_playerModel.transform = MatrixRotateXYZ(trans);
}

int Indie::IA::getActiveBomb() const
{
	return _activeBomb;
}

void Indie::IA::movePlayerUp()
{
	_posY -= 2.0;
}

void Indie::IA::movePlayerDown()
{
	_posY += 2.0;
}

void Indie::IA::movePlayerLeft()
{
	_posX -= 2.0;
}

void Indie::IA::movePlayerRight()
{
	_posX += 2.0;
}

void Indie::IA::drawPlayer()
{}

void Indie::IA::movePlayer()
{}

std::shared_ptr<Power> Indie::IA::getPower() const
{
	return _power;
}

void Indie::IA::setActiveBomb(int nb)
{
	_activeBomb += nb;
}
std::vector<Input::Button> Indie::IA::getKeys() const
{
	return {};
}

bool Indie::IA::getIsDead() const
{
    return this->isDead;
}

void Indie::IA::setIsDead(const bool &dead)
{
    this->isDead = dead;
}

Color Indie::IA::getColor() const
{
    return this->skinColor;
}

void Indie::IA::setColor(const Color &skin)
{
    this->skinColor = skin;
}

void Indie::IA::setPlayerRoll(const float &roll)
{
    this->_roll = roll;
}

float Indie::IA::getPlayerRoll() const
{
    return (this->_roll);
}