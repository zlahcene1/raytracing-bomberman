/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

	#include <raylib.h>

namespace Indie {
	class CppColor {
		public:
			CppColor() = default;
			CppColor(const Color &);
			~CppColor() = default;
			Color getColor() const;
			void setColor(const CppColor &color);
		private:
			Color _color;
	};
}

#endif /* !COLOR_HPP_ */
