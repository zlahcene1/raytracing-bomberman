/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
    #define BOMB_HPP_
    
    #include "Utils.hpp"
    #include "chrono"

class Bomb {
    public:
        Bomb(Vector3 playerPos);
        ~Bomb();

        Model bombModel;
        Texture2D bombTex;
        Vector3 bombPos;
        int isSetMap;
        bool inOnce;
        bool inOnceDel;
        std::chrono::steady_clock::time_point bombClk;
        void drawBomb();
    private:
};

#endif /* !BOMB_HPP_ */
