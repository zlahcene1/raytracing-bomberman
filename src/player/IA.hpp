/*
** EPITECH PROJECT, 2022
** indie
** File description:
** IA
*/

#ifndef IA_HPP_
   #define IA_HPP_

    #include "Utils.hpp"
	#include "Movable.hpp"
    #include <vector>

namespace Indie {
   class IA  : public IMovable {
       public:
            IA(const Vector3 &vector, const std::string &name, const int &id);
            IA() = default;
            ~IA();

            void newGoal(const std::vector<std::string> &);
            bool isDangerous(const std::vector<std::string> &, int, int);
            void newGoalOffense(const std::vector<std::string> &);
            void newGoalDefense(const std::vector<std::string> &);

		    Input::Button checkAction(const Input::Button &, std::vector<std::shared_ptr<Bomb>> &, const Map &map);
			void checkPowerUp() override;
			int getPlayerId() const;
			std::string getPlayerName() const override;
			float getPosX() const;
			float getPosY() const;
			PlayerType getType() const override;
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
			std::shared_ptr<Power> getPower() const override;
			void setActiveBomb(int nb) override;
			std::vector<Input::Button> getKeys() const override;
			bool getIsDead() const override;
			void setIsDead(const bool &dead) override;
			Color getColor() const override;
			void setColor(const Color &skin) override;
			float getPlayerRoll() const override;
			void setPlayerRoll(const float &roll) override;
       private:
            int _posX;
            int _posY;
            int _posGoalX;
            int _posGoalY;
			std::string _name;
			int _id;
			bool isDead;
			Model _playerModel;
        	Texture2D _playerTexture;
			std::shared_ptr<Power> _power;
			int _activeBomb;
			std::chrono::steady_clock::time_point _clock;
			std::vector<std::string> _saveMap;
			Color skinColor;
			float _roll;
   };
}

#endif /* !IA_HPP_ */