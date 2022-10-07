/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Sound
*/

#ifndef SOUND_HPP_
	#define SOUND_HPP_

	#include <string>
	#include "IAudio.hpp"
	#include <raylib.h>
	#include <memory>

	class Raylib;

namespace Indie {
	class CppSound : public Indie::IAudio {
		public:
			CppSound() = default;
			CppSound(const std::string &soundFilepath, const float &volume);
			const Sound &getSound() const;
			~CppSound();
			void play() override;
			void stop() override;
			void pause() override;
			void resume() override;
			void update() override;
			void setVolume(const float &volume) override;
			float getVolume() const override;
		private:
			std::unique_ptr<Raylib> _raylib;
			Sound _sound;
			float _volume;
	};
}

#endif /* !SOUND_HPP_ */
