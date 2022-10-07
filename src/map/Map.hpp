/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

#include "Utils.hpp"
#include "Player.hpp"
#include "Raylib.hpp"
#include "Bomb.hpp"
#include <chrono>
#include <thread>
#include "IMenu.hpp"
#include "Music.hpp"
#include "IAudio.hpp"
#include "Movable.hpp"

class Map {
    public:
        Map(const std::vector<std::string> &map = {});
        ~Map();

        void generateWalls();
        void printMap(std::vector<std::shared_ptr<IMovable>> &player, std::vector<std::shared_ptr<Bomb>> &bombVec);
        bool WindowShouldClose();
        void initParallax();
        void setBombMap(std::vector<std::shared_ptr<Bomb>> &bombVec);
        void delBombMap(std::shared_ptr<Bomb> &bombElem, std::shared_ptr<IMovable> &player);
        void delExplosionMap(std::shared_ptr<Bomb> &bombElem, std::shared_ptr<IMovable> &player);
        void emptyBoxVec();
        std::vector<std::string> getMap() const;
        bool checkColl(float left, float right, float up, float down, Vector3 cubeSize, std::shared_ptr<IMovable> &player);
		void checkInput(std::vector<std::shared_ptr<IMovable>> &player, std::vector<std::shared_ptr<Bomb>> &);
		void movePlayer(std::shared_ptr<IMovable> &player);
        void setCasesPositions();
		void drawAi(std::shared_ptr<IMovable> &ai, std::vector<std::shared_ptr<Bomb>> &bombs);
        void checkIfDead(std::shared_ptr<IMovable> &player);
		//void moveAI(std::shared_ptr<IMovable> &ai);
   //     Model model;
        Texture2D texture;
        Camera3D camera;
        //Vector3 playerPosition;
        Image image_crate;
        Texture2D box_crate;
        Image map_image;
        Texture2D cubicmap;
		Vector3 cubeSize;
        Image image_background;
        Texture2D background;
        Model model2;
        Mesh mesh;
        Texture2D texture2;
        std::clock_t mapClk;
        std::vector<Vector4> casesPositions;
        std::vector<std::string> baseMap;
        unsigned int animsCount;
        ModelAnimation *anims;
        int animFrameCounter[4];
        float pitch;
        float roll;
        float yaw;
        Vector3 rotationAxis;
        float rotationAngle;
        Vector3 scale;
        bool animRunningRight[4];
        bool animRunningLeft[4];
        bool animRunningUp[4];
        bool animRunningDown[4];

        Texture2D explosion;
        float frameWidth;
        float frameHeight;
        int currentFrame;
        int currentLine;
        Rectangle frameRec;
        Vector2 position;
        Vector3 vector3;
        bool active;
        int framesCounter;

        Model modelExplo;
        Texture2D textureExplo;
        Vector3 exploPos;
        float exploScale;

        Font font;
        Vector2 textPos;
        Vector2 textPos2;
        Vector2 textPos3;
        float fontSize;
        float spacing;
    private:
        std::unique_ptr<Raylib> _raylib;
};

#endif /* !MAP_HPP_ */