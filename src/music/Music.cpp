/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Music
*/

#include "Music.hpp"
#include "Raylib.hpp"

Indie::CppMusic::CppMusic(const std::string &soundFilepath, const float &volume)
: _raylib(std::make_unique<Raylib>()), _volume(volume)
{
	_music = LoadMusicStream(soundFilepath.c_str());
}

Indie::CppMusic::~CppMusic()
{
    UnloadMusicStream(_music);
}

void Indie::CppMusic::play()
{
	_raylib->playMusicStream(*this);
}

void Indie::CppMusic::pause()
{
	_raylib->pauseMusicStream(*this);
}

const Music &Indie::CppMusic::getMusic()
{
	return _music;
}

void Indie::CppMusic::stop()
{}

void Indie::CppMusic::resume()
{}

void Indie::CppMusic::update()
{
	UpdateMusicStream(_music);
}

void Indie::CppMusic::setVolume(const float &volume)
{
	_raylib->setMusicVolume(*this, volume);
	_volume = volume;
}

float Indie::CppMusic::getVolume() const
{
	return _volume;
}