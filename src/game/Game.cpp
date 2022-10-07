/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Game
*/

#include "Game.hpp"
#include "Raylib.hpp"
#include "MainMenu.hpp"
#include "Settings.hpp"
#include "Pause.hpp"
#include "EndMenu.hpp"
#include "Save.hpp"

Game::Game(const std::vector<std::shared_ptr<IMovable>> &movable,
std::vector<std::shared_ptr<Indie::IAudio>> &music,
std::vector<std::shared_ptr<Indie::IAudio>> &audio,
const std::vector<std::string> &map)
: _music(music), _audio(audio), _players(movable)
{
	_newMap = std::make_unique<Map>(map);
}

int Game::run()
{
	Return_Status status = NOTHING;

	_raylib->hideCursor();
	while (1) {
		update();
		status = event();
		if (status == EXIT)
			return 1;
		if (event() == LAST_MENU)
			break;
	}
	return 0;
}

void Game::startMenu()
{}

bool Game::closeMenu() const
{
    return _raylib->windowShouldClose();
}

void Game::update()
{
	_raylib->clearBackground();
	_raylib->beginDrawing();
	drawUi();
	_raylib->endDrawing();
}

std::shared_ptr<IMenu> Game::getptr()
{
	return shared_from_this();
}

void Game::saveMap()
{
	std::vector<std::string> map = _newMap->getMap();
	Vector3 pos;
	Indie::Save save;

	for (auto &player : _players) {
		pos = player->getPlayerPos();
		if (player->getType() == PLAYER)
			map[pos.z / 2][pos.x / 2] = player->getPlayerId() + 'a';
		else
			map[pos.z / 2][pos.x / 2] = player->getPlayerId() + 'A';
	}
	save.saveFile(map);
}

Return_Status Game::event()
{
	Input::Button key = _raylib->isKeyPressed();
	std::unique_ptr<IMenu> menu;
	int playersAlive = 0;
	int botsAlive = 0;

	for (auto &player : _players) {
		if (player->getType() == PLAYER)
			player->checkAction(key, _bombVec, *_newMap);
	}
	_newMap->checkInput(_players, _bombVec);

	for (unsigned int i = 0; i < _players.size(); i++) {
		_newMap->checkIfDead(_players[i]);
		if (_players[i]->getIsDead() == true && !_players.empty()) {
			std::cout << _players[i]->getPlayerPos().x << std::endl;
			_players.erase(_players.begin() + i);
		}
	}
	for (auto &player : _players) {
		if (player->getType() == PLAYER)
			playersAlive += 1;
		else
			botsAlive += 1;
	}
	if (playersAlive == 1 && !botsAlive) {
		std::shared_ptr<IMenu> ptr = getptr();
		menu = std::make_unique<Menu::EndMenu>(ptr, true, _players[0]->getPlayerName());
		menu->run();
		std::remove("../save.txt");
		return LAST_MENU;
	} else if (!playersAlive) {
		std::shared_ptr<IMenu> ptr = getptr();
		menu = std::make_unique<Menu::EndMenu>(ptr, false, _players[0]->getPlayerName());
		menu->run();
		std::remove("../save.txt");
		return LAST_MENU;
	}
	for (auto &player : _players)
		if (player->getType() == PLAYER)
			player->checkAction(key, _bombVec, *_newMap);
	_newMap->checkInput(_players, _bombVec);
	if (_players.empty())
		return NOTHING;
    if (key == Input::Button::KEY_P) {
		std::shared_ptr<IMenu> ptr = getptr();
		menu = std::make_unique<Menu::Pause>(ptr, _music, _audio);
		if (menu->run() == 1) {
			saveMap();
			return EXIT;
		}
	}
	return NOTHING;
}

void Game::drawUi()
{
	_newMap->printMap(_players, _bombVec);
	_newMap->setCasesPositions();
	_music[0]->update();
}

std::vector<std::shared_ptr<Indie::IAudio>> Game::getMusic() const
{
	return _music;
}

std::vector<std::shared_ptr<Indie::IAudio>> Game::getSound() const
{
	return _audio;
}
