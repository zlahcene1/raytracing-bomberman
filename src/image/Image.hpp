/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Image
*/

#ifndef IMAGE_HPP_
    #define IMAGE_HPP_

    #include "Utils.hpp"
    #include <raylib.h>
	#include "Image.hpp"
	#include "Rectangle.hpp"
	#include "Vector2.hpp"
	#include <memory>

namespace Indie {
    class CppImage {
        public:
			CppImage() = default;
            CppImage(const std::string &filePath);
            ~CppImage();
			const Texture2D &getTexture();
			CppRectangle getRectangle() const;
			CppRectangle getRectangleBounds() const;
			CppVector2 getRecSize() const;
			CppVector2 getPos() const;
			void setRecSize(const int &width, const int &height);
			void setPos(const int &posX, const int &posY);
        private:
            Texture2D _tex;
            CppRectangle _rec;
			CppVector2 _pos;
			CppVector2 _initSize;
    };
}

#endif /* !IMAGE_HPP_ */