/*
** EPITECH PROJECT, 2022
** indie
** File description:
** IMenu
*/

#ifndef IMENU_HPP_
    #define IMENU_HPP_

    #include "Utils.hpp"
    #include "IMenu.hpp"
    #include "Raylib.hpp"
	#include "Music.hpp"
	#include "Sound.hpp"

	#define WIDTH 1920
	#define HEIGHT 1080

	#define BUTTON_WIDTH 400
	#define BUTTON_HEIGHT 100
	#define DEFAULT_FONT_SIZE 40

enum Return_Status {
	NOTHING = 0,
	LAST_MENU,
	EXIT,
};

class IMenu {
    public:
        virtual ~IMenu() = default;
        virtual void startMenu() = 0;
        virtual void update() = 0;
        virtual Return_Status event() = 0;
        virtual bool closeMenu() const = 0;
		virtual int run() = 0;
        virtual void drawUi() = 0;
		virtual std::vector<std::shared_ptr<Indie::IAudio>> getSound() const = 0;
		virtual std::vector<std::shared_ptr<Indie::IAudio>> getMusic() const = 0;
};

#endif /* !IMENU_HPP_ */