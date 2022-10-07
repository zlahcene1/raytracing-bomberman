/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Power
*/

#ifndef POWER_HPP_
    #define POWER_HPP_

    #include "Utils.hpp"

class Power {
    public:
        Power();
        ~Power();

        bool getWallPass() const;
        int getBombUp() const;
        int getSpeedUp() const;
        int getFireUp() const;

        void setWallPass(bool pass);
        void setBombUp(int newB);
        void setSpeedUp(int newS);
        void setFireUp(int newF);
    private:
        bool wallPass;
        int bombUp;
        int speedUp;
        int fireUp;
};

#endif /* !POWER_HPP_ */
