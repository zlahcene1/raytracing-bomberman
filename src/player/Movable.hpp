/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Movable
*/

#ifndef MOVABLE_HPP_
#define MOVABLE_HPP_

#include "Utils.hpp"
#include "Bomb.hpp"
#include "Power.hpp"
#include <memory>

class Map;

enum PlayerType {
	IA,
	PLAYER
};

class IMovable {
    public:
		virtual ~IMovable() = default;
		virtual Input::Button checkAction(const Input::Button &key, std::vector<std::shared_ptr<Bomb>> &bomb, const Map &nMap) = 0;
		virtual void checkPowerUp() = 0;
		virtual int getPlayerId() const = 0;
		virtual std::string getPlayerName() const = 0;
		virtual Vector3 getPlayerPos() const = 0;
		virtual Model getPlayerModel() const = 0;
		virtual void setPlayerTransform(Vector3 trans) = 0;
		virtual int getActiveBomb() const = 0;
		virtual void movePlayerUp() = 0;
		virtual void movePlayerDown() = 0;
		virtual void movePlayerLeft() = 0;
		virtual void movePlayerRight() = 0;
		virtual void drawPlayer() = 0;
		virtual void movePlayer() = 0;
		virtual std::shared_ptr<Power> getPower() const = 0;
		virtual void setActiveBomb(int nb) = 0;
		virtual PlayerType getType() const = 0;
		virtual std::vector<Input::Button> getKeys() const = 0;
		virtual bool getIsDead() const = 0;
		virtual void setIsDead(const bool &dead) = 0;
		virtual Color getColor() const = 0;
		virtual void setColor(const Color &skin) = 0;
		virtual float getPlayerRoll() const = 0;
		virtual void setPlayerRoll(const float &roll) = 0;
};

#endif /* !MOVABLE_HPP_ */
