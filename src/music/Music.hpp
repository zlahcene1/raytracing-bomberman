/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Music
*/

#ifndef MUSIC_HPP_
    #define MUSIC_HPP_

	#include "IAudio.hpp"
	#include <raylib.h>
	#include <string>
	#include <memory>

	class Raylib;

namespace Indie {
	class CppMusic : public Indie::IAudio {
		public:
			CppMusic() = default;
			CppMusic(const std::string &soundFilepath, const float &volume);
			~CppMusic();
			const Music &getMusic();
			void play() override;
			void stop() override;
			void pause() override;
			void resume() override;
			void update() override;
			void setVolume(const float &volume) override;
			float getVolume() const override;
		private:
			Music _music;
			std::unique_ptr<Raylib> _raylib;
			float _volume;
	};
}

#endif /* !MUSIC_HPP_ */
