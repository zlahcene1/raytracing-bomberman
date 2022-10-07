/*
** EPITECH PROJECT, 2022
** indie
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
    #define MAINMENU_HPP_

    #include "Utils.hpp"
    #include "IMenu.hpp"
	#include "Button.hpp"
    #include "Raylib.hpp"
	#include <memory>
	#include <array>
	#include <filesystem>

class MainMenu : public IMenu, public std::enable_shared_from_this<MainMenu> {
    public:
        MainMenu();
        ~MainMenu() = default;

		void loadingScreen();

		int run() override;
        void update() override;
        Return_Status event() override;
        void startMenu() override;
        bool closeMenu() const override;
        void drawUi() override;
		std::vector<std::shared_ptr<Indie::IAudio>> getSound() const override;
		std::vector<std::shared_ptr<Indie::IAudio>> getMusic() const override;
		std::shared_ptr<IMenu> getptr();
    private:
        std::unique_ptr<Raylib> _raylib;
		std::size_t _cursIdx;
		std::vector<std::unique_ptr<Gui::Button>> _buttons;
		std::vector<std::shared_ptr<Indie::IAudio>> _menuActions;
		std::vector<std::shared_ptr<Indie::IAudio>> _menuMusic;
		bool _savedMap;
};

#endif /* !MAINMENU_HPP_ */