/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(Vector3 playerPos)
{
    this->bombModel = LoadModel("../assets/Dynamite/dinamite.obj");
    this->bombTex = LoadTexture("../assets/Dynamite/D.png");
    this->bombModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->bombTex;
    this->bombPos = playerPos;
    this->bombClk = std::chrono::steady_clock::now();
    this->isSetMap = 0;
    this->inOnce = false;
    this->inOnceDel = false;
}

Bomb::~Bomb()
{
    UnloadTexture(bombTex);
	UnloadModel(bombModel);
}

void Bomb::drawBomb()
{
    DrawModel(this->bombModel, this->bombPos, 1.0f, WHITE);
}