/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Vector2
*/

#ifndef VECTOR2_HPP_
	#define VECTOR2_HPP_

	#include <raylib.h>

namespace Indie {
	class CppVector2 {
		public:
			CppVector2() = default;
			CppVector2(const float &x, const float &y);
			Vector2 getVector2() const;
			void setVector2(const float &x, const float &y);
			float getVectorX() const;
			float getVectorY() const;
			~CppVector2() = default;
		private:
			Vector2 _vector;
	};
}
#endif /* !VECTOR2_HPP_ */
