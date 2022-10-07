/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP_
	#define IAUDIO_HPP_

namespace Indie {
	class IAudio {
		public:
			virtual ~IAudio() = default;
			virtual void play() = 0;
			virtual void stop() = 0;
			virtual void pause() = 0;
			virtual void resume() = 0;
			virtual void update() = 0;
			virtual void setVolume(const float &) = 0;
			virtual float getVolume() const = 0;
	};
}

#endif
