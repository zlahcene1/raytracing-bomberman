/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Core
*/

#include "Utils.hpp"
#include "Core.hpp"
#include "Game.hpp"
#include "MainMenu.hpp"
#include "Raylib.hpp"
#include "EndMenu.hpp"

Indie::Core::Core()
{
    _menu = std::make_shared<MainMenu>();
}

Indie::Core::~Core()
{}

void Indie::Core::program()
{
	_menu->run();
}