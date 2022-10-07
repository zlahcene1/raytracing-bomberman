/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include "Utils.hpp"
    #include "Bomb.hpp"
    #include "Power.hpp"
	#include "Movable.hpp"
	#include "Raylib.hpp"

class Map;

class Player : public IMovable {
    public:
        Player(const std::string &name, const Vector3 &playerPos, const std::vector<Input::Button> &keys, const int &playerId);
        Player() = default;
		~Player();
        Input::Button checkAction(const Input::Button &key, std::vector<std::shared_ptr<Bomb>> &bomb, const Map &nMap) override;
        void checkPowerUp() override;
        int getPlayerId() const override;
        std::string getPlayerName() const override;
        Vector3 getPlayerPos() const override;
        Model getPlayerModel() const override;
        void setPlayerTransform(Vector3 trans) override;
        int getActiveBomb() const override;
        void movePlayerUp() override;
        void movePlayerDown() override;
        void movePlayerLeft() override;
        void movePlayerRight() override;
        void drawPlayer() override;
        void movePlayer() override;
        bool collision;
        std::shared_ptr<Power> getPower() const override;
        float roll;
        void setActiveBomb(int nb) override;
		PlayerType getType() const override;
		std::vector<Input::Button> getKeys() const override;
        bool getIsDead() const override;
        void setIsDead(const bool &dead) override;
        Color getColor() const override;
        void setColor(const Color &skin) override;
        float getPlayerRoll() const override;
        void setPlayerRoll(const float &roll) override;
    private:
        Model _playerModel;
        Texture2D _playerTexture;
        int _playerId;
        int _activeBomb;
        float _speed;
        float _roll;
        bool isDead;
        Vector3 _playerPos;
        std::string _name;
        std::vector<Input::Button> _keyBinds;
        std::shared_ptr<Power> _power;
		std::unique_ptr<Raylib> _raylib;
        Color skinColor;
};

#endif /* !PLAYER_HPP_ */
