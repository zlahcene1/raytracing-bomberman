/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP_
	#define RECTANGLE_HPP_

	#include <raylib.h>
	#include "Vector2.hpp"

namespace Indie {
	class CppRectangle {
		public:
			CppRectangle() = default;
			CppRectangle(const float &, const float &,
			const float &, const float &);
			~CppRectangle() = default;
			Rectangle getRectangle() const;
			CppVector2 getRecSize() const;
			void setRectanglePos(const float &, const float &);
			void setRectangleSize(const float &, const float &);
		private:
			Rectangle _rectangle;
	};
}

#endif /* !RECTANGLE_HPP_ */
