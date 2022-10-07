/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Sound
*/

#include "Sound.hpp"
#include "Raylib.hpp"

Indie::CppSound::CppSound(const std::string &soundFilepath, const float &volume)
:  _raylib(std::make_unique<Raylib>()), _volume(volume)
{
	_sound = LoadSound(soundFilepath.c_str());
}

Indie::CppSound::~CppSound()
{
	UnloadSound(_sound);
}

const Sound &Indie::CppSound::getSound() const
{
	return _sound;
}

void Indie::CppSound::play()
{
	_raylib->playSound(*this);
}

void Indie::CppSound::stop()
{}

void Indie::CppSound::pause()
{}

void Indie::CppSound::resume()
{}

void Indie::CppSound::update()
{}

void Indie::CppSound::setVolume(const float &volume)
{
	std::cout << volume << std::endl;
	_raylib->setSoundVolume(*this, volume);
	_volume = volume;
}

float Indie::CppSound::getVolume() const
{
	return _volume;
}