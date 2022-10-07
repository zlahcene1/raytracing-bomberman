/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include "Utils.hpp"
    #include "IMenu.hpp"
    #include "Map.hpp"
    #include "Player.hpp"
    #include "Music.hpp"

class Game : public IMenu, public std::enable_shared_from_this<Game> {
    public:
        Game(const std::vector<std::shared_ptr<IMovable>> &movable,
		std::vector<std::shared_ptr<Indie::IAudio>> &music,
		std::vector<std::shared_ptr<Indie::IAudio>> &audio,
		const std::vector<std::string> &map = {});
        ~Game() override = default;

        int run();
        void startMenu();
        void update();
        Return_Status event();
        bool closeMenu() const;
        void drawUi();
		std::vector<std::shared_ptr<Indie::IAudio>> getSound() const;
		std::vector<std::shared_ptr<Indie::IAudio>> getMusic() const;
		std::shared_ptr<IMenu> getptr();
		void saveMap();
    private:
        std::unique_ptr<Raylib> _raylib;
        std::unique_ptr<Map> _newMap;
        std::vector<std::shared_ptr<Indie::IAudio>> _music;
		std::vector<std::shared_ptr<Indie::IAudio>> _audio;
        std::vector<std::shared_ptr<Bomb>> _bombVec;
        std::vector<std::shared_ptr<IMovable>> _players;
		float _soundVolume;
		float _musicVolume;
};

#endif /* !GAME_HPP_ */
