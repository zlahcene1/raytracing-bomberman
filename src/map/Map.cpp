/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Map
*/

#include "Map.hpp"
#include "Raylib.hpp"
#include "raymath.h"
#include "unistd.h"
#include <cstring>

#define TRANSPARENT   CLITERAL(Color){ 0, 250, 0, 0 }

Map::Map(const std::vector<std::string> &map)
: _raylib(std::make_unique<Raylib>())
{
    if (map.empty())
        this->baseMap = {
            "222222222222222",
            "200000000000002", // 1
            "204040404040402",
            "200000000000002",
            "204040404040402",
            "200000000000002",
            "204040404040402",
            "200000000000002",
            "204040404040402",
            "200000000000002",
            "204040404040402",
            "200000000000002",
            "200040404040002", // 12
            "222222222222222"
        };
    else
        baseMap = map;
    this->cubeSize = { 2.0f, 2.0f, 2.0f };
    this->camera.position = (Vector3){ 13.01f, 7.49f, 26.78f };
    this->camera.target = (Vector3){ 13.01f, -9.21f, 18.43f };
    this->camera.up = (Vector3){ 0.0f, 4.0f, 0.0f };
    this->camera.fovy = 70.0f;
    this->camera.projection = CAMERA_PERSPECTIVE;
    this->image_crate = LoadImage("../assets/crate/crate_wood.png");
    this->box_crate = LoadTextureFromImage(this->image_crate);
    this->map_image = LoadImage("../assets/floor/map_test.png");
    this->cubicmap = LoadTextureFromImage(this->map_image);
    this->image_background =  LoadImage("../assets/background/background.png");
    this->background = LoadTextureFromImage(this->image_background);
    this->mesh = GenMeshCubicmap(this->map_image, (Vector3){ 2.0f, 2.0f, 2.0f });
    this->model2 = LoadModelFromMesh(this->mesh);
    this->texture2 = LoadTexture("../assets/floor/texture_map_floor.png");
    this->model2.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->texture2;
    this->casesPositions = {};
    if (map.empty())
        this->generateWalls();
    std::cout << std::vector<std::string> {{{}}}.empty() << std::endl;
    this->pitch = 0.0f;
    this->roll = 0.0f;
    this->yaw = 0.0f;
    this->animsCount = 0;
    this->anims = LoadModelAnimations("../assets/test/char3Anim4.iqm", &animsCount);
    std::memset(this->animFrameCounter, 0, sizeof(int) * 4);
    this->rotationAxis = {1.0f, 0.0f, 0.0f};
    this->rotationAngle = -90.0f;
    this->scale = {0.02f, 0.02f, 0.02f};
    std::memset(this->animRunningRight, 0, sizeof(bool) * 4);
    std::memset(this->animRunningLeft, 0, sizeof(bool) * 4);
    std::memset(this->animRunningDown, 0, sizeof(bool) * 4);
    std::memset(this->animRunningUp, 0, sizeof(bool) * 4);

    this->explosion = LoadTexture("../assets/crate/explosion.png");
    this->frameWidth = (float)(explosion.width/5);
    this->frameHeight = (float)(explosion.height/5);
    this->currentFrame = 0;
    this->currentLine = 0;
    this->frameRec = { 0, 0, frameWidth, frameHeight };
    this->position = {0.0f, 0.0f};
    this->active = false;
    this->framesCounter = 0;

    this->modelExplo = LoadModel("../assets/crate/Smoke.obj");
    this->textureExplo = LoadTexture("../assets/crate/fire.png");
    this->modelExplo.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = this->textureExplo;
    this->exploPos = {2.0f, -8.0f, 2.0f};
    this->exploScale = 0.15f;
    this->font = LoadFont("../assets/background/font.png");
    this->textPos = {13.01f, 26.78f};
    this->textPos2 = {15.01f, 26.78f};
    this->textPos3 = {17.01f, 26.78f};

    this->fontSize = 50.0f;
    this->spacing = 2.0f;

    SetCameraMode(this->camera, CAMERA_FREE);
    std::srand(std::time(nullptr));
}

Map::~Map()
{
    UnloadImage(this->image_crate);
    UnloadTexture(this->box_crate);
    UnloadTexture(this->cubicmap);
    UnloadImage(this->map_image);
    UnloadImage(this->image_background);
    UnloadTexture(this->background);
    UnloadModel(this->model2);
    UnloadTexture(this->texture2);
    UnloadTexture(this->explosion);
    UnloadModel(this->modelExplo);
}

void Map::emptyBoxVec()
{
    this->casesPositions.clear();
}

static bool notInSpawn(int x, int y)
{
    if ((x == 1 && y == 1) ||
        (x == 1 && y == 12) ||
        (x == 13 && y == 1) ||
        (x == 13 && y == 12) ||
        (x == 2 && y == 1) ||
        (x == 2 && y == 12) ||
        (x == 12 && y == 1) ||
        (x == 12 && y == 12) ||
        (x == 1 && y == 2) ||
        (x == 1 && y == 11) ||
        (x == 13 && y == 2) ||
        (x == 13 && y == 11))
        return false;
    return true;
}

void Map::setBombMap(std::vector<std::shared_ptr<Bomb>> &bombVec)
{
    for (auto &i : bombVec) {
        if (i->isSetMap == 0) {
            std::cout << "Bomb pos x = " << i->bombPos.x << std::endl;
            std::cout << "Bomb pos y = " << i->bombPos.z << std::endl;
            this->baseMap[i->bombPos.z / 2][i->bombPos.x / 2] = '7';
            i->isSetMap = 1;
        }
    }
}

void Map::delBombMap(std::shared_ptr<Bomb> &bombElem, std::shared_ptr<IMovable> &player)
{
    int z = bombElem->bombPos.z / 2;
    int x = bombElem->bombPos.x / 2;
    int randomNb = 0;

    this->baseMap[z][x] = '3';
    for (int i = 1; i < 2 + player->getPower()->getFireUp(); i++) {
        if (z - i > 0 && this->baseMap[z - i][x] == '0')
            this->baseMap[z - i][x] = '3';
        else if (z - i > 0 && this->baseMap[z - i][x] == '1') {
            if (std::rand() % 2 == 0) {
                randomNb = std::rand() % 4;
                if (randomNb == 0)
                    player->getPower()->setBombUp(player->getPower()->getBombUp() + 1);
                else if (randomNb == 1)
                    player->getPower()->setFireUp(player->getPower()->getFireUp() + 1);
                else if (randomNb == 2)
                    player->getPower()->setSpeedUp(player->getPower()->getSpeedUp() + 1);
                else
                    player->getPower()->setWallPass(true);
            }
            this->baseMap[z - i][x] = '0';
            break;
        } else if (z - i > 0 && this->baseMap[z - i][x] == '4')
            break;
    }
    for (int i = 1; i < 2 + player->getPower()->getFireUp(); i++) {
        if (z + i < 13 && this->baseMap[z + i][x] == '0')
            this->baseMap[z + i][x] = '3';
        else if (z + i < 13 && this->baseMap[z + i][x] == '1') {
            if (std::rand() % 2 == 0) {
                randomNb = std::rand() % 4;
                if (randomNb == 0)
                    player->getPower()->setBombUp(player->getPower()->getBombUp() + 1);
                else if (randomNb == 1)
                    player->getPower()->setFireUp(player->getPower()->getFireUp() + 1);
                else if (randomNb == 2)
                    player->getPower()->setSpeedUp(player->getPower()->getSpeedUp() + 1);
                else
                    player->getPower()->setWallPass(true);
            }
            this->baseMap[z + i][x] = '0';
            break;
        } else if (z + i < 13 && this->baseMap[z + i][x] == '4')
            break;
    }
    for (int i = 1; i < 2 + player->getPower()->getFireUp(); i++) {
        if (x + i < 14 && this->baseMap[z][x + i] == '0')
            this->baseMap[z][x + i] = '3';
        else if (x + i < 14 && this->baseMap[z][x + i] == '1') {
            if (std::rand() % 2 == 0) {
                randomNb = std::rand() % 4;
                if (randomNb == 0)
                    player->getPower()->setBombUp(player->getPower()->getBombUp() + 1);
                else if (randomNb == 1)
                    player->getPower()->setFireUp(player->getPower()->getFireUp() + 1);
                else if (randomNb == 2)
                    player->getPower()->setSpeedUp(player->getPower()->getSpeedUp() + 1);
                else
                    player->getPower()->setWallPass(true);
            }
            this->baseMap[z][x + i] = '0';
            break;
        } else if (x + i < 14 && this->baseMap[z][x + i] == '4')
            break;
    }
    for (int i = 1; i < 2 + player->getPower()->getFireUp(); i++) {
        if (x - i > 0 && this->baseMap[z][x - i] == '0')
            this->baseMap[z][x - i] = '3';
        else if (x - i > 0 && this->baseMap[z][x - i] == '1') {
            if (std::rand() % 2 == 0) {
                randomNb = std::rand() % 4;
                if (randomNb == 0)
                    player->getPower()->setBombUp(player->getPower()->getBombUp() + 1);
                else if (randomNb == 1)
                    player->getPower()->setFireUp(player->getPower()->getFireUp() + 1);
                else if (randomNb == 2)
                    player->getPower()->setSpeedUp(player->getPower()->getSpeedUp() + 1);
                else
                    player->getPower()->setWallPass(true);
            }
            this->baseMap[z][x - i] = '0';
            break;
        } else if (x - i > 0 && this->baseMap[z][x - i] == '4')
            break;
    }
}

void  Map::delExplosionMap(std::shared_ptr<Bomb> &bombElem, std::shared_ptr<IMovable> &player)
{
    int z = bombElem->bombPos.z / 2;
    int x = bombElem->bombPos.x / 2;

    this->baseMap[z][x] = '0';
    for (int i = 1; i < 2 + player->getPower()->getFireUp(); i++) {
        if (z - i > 0 && this->baseMap[z - i][x] == '3')
            this->baseMap[z - i][x] = '0';
    }
    for (int i = 1; i < 2 + player->getPower()->getFireUp(); i++) {
        if (z + i < 13 && this->baseMap[z + i][x] == '3')
            this->baseMap[z + i][x] = '0';
    }
    for (int i = 1; i < 2 + player->getPower()->getFireUp(); i++) {
        if (x + i < 14 && this->baseMap[z][x + i] == '3')
            this->baseMap[z][x + i] = '0';
    }
    for (int i = 1; i < 2 + player->getPower()->getFireUp(); i++) {
        if (x - i > 0 && this->baseMap[z][x - i] == '3')
            this->baseMap[z][x - i] = '0';
    }
}

void Map::generateWalls()
{
    std::vector<int> v1;

    for (int y = 1; y < 13; y++) {
        for (unsigned int x = 0; x < this->baseMap[y].size(); x++) {
            if (std::rand() % 2 == 0 && baseMap[y][x] != '1' && baseMap[y][x] != '2'
                && baseMap[y][x] != '4' && notInSpawn(x, y))
                baseMap[y][x] = '1';
        }
    }
}

std::vector<std::string> Map::getMap() const
{
    return this->baseMap;
}

void Map::movePlayer(std::shared_ptr<IMovable> &player)
{
    std::vector<Input::Button> playerKeys = player->getKeys();
    Input::Button key = _raylib->isKeyPressed();
    int playerId = player->getPlayerId();

    if (!player)
        return;
    if ((key == playerKeys[2] && !checkColl(2.0f, 0.0f, 0.0f, 0.0f, cubeSize, player)) || this->animRunningRight[playerId]) {
        if (this->animRunningRight[playerId] || (this->animRunningRight[playerId] == false && this->animRunningLeft[playerId] == false && this->animRunningUp[playerId] == false && this->animRunningDown[playerId] == false)) {
            this->animRunningRight[playerId] = true;
            this->animFrameCounter[playerId] += (1 + player->getPower()->getSpeedUp());
            UpdateModelAnimation(player->getPlayerModel(), this->anims[0], this->animFrameCounter[playerId]);
            player->setPlayerRoll(-90.0f);
            if (this->animFrameCounter[playerId] >= 20) {
                player->movePlayerRight();
                this->animFrameCounter[playerId] = 0;
                this->animRunningRight[playerId] = false;
            }
        }
    }
    else if ((key == playerKeys[0] && !checkColl(0.0f, 2.0f, 0.0f, 0.0f, cubeSize, player)) || this->animRunningLeft[playerId]) {
        if (this->animRunningLeft[playerId] || (this->animRunningLeft[playerId] == false && this->animRunningRight[playerId] == false && this->animRunningUp[playerId] == false && this->animRunningDown[playerId] == false)) {
            this->animRunningLeft[playerId] = true;
            this->animFrameCounter[playerId] += (1 + player->getPower()->getSpeedUp());
            UpdateModelAnimation(player->getPlayerModel(), this->anims[0], this->animFrameCounter[playerId]);
            player->setPlayerRoll(90.0f);
            if (this->animFrameCounter[playerId] >= 20) {
                player->movePlayerLeft();
                this->animFrameCounter[playerId] = 0;
                this->animRunningLeft[playerId] = false;
            }
        }
    }
    else if ((key == playerKeys[3] && !checkColl(0.0f, 0.0f, 0.0f, 2.0f, cubeSize, player)) || this->animRunningDown[playerId]) {
        if (this->animRunningDown || (this->animRunningDown[playerId] == false && this->animRunningLeft[playerId] == false && this->animRunningUp[playerId] == false && this->animRunningRight[playerId] == false)) {
            this->animRunningDown[playerId] = true;
            this->animFrameCounter[playerId] += (1 + player->getPower()->getSpeedUp());
            UpdateModelAnimation(player->getPlayerModel(), this->anims[0], this->animFrameCounter[playerId]);
            player->setPlayerRoll(0.0f);
            if (this->animFrameCounter[playerId] >= 20) {
                player->movePlayerDown();
                this->animFrameCounter[playerId] = 0;
                this->animRunningDown[playerId] = false;
            }
        }
    }
    else if ((key == playerKeys[1] && !checkColl(0.0f, 0.0f, 2.0f, 0.0f, cubeSize, player)) || this->animRunningUp[playerId]) {
        if (this->animRunningUp[playerId] || (this->animRunningUp[playerId] == false && this->animRunningLeft[playerId] == false && this->animRunningDown[playerId] == false && this->animRunningRight[playerId] == false)) {
            this->animRunningUp[playerId] = true;
            this->animFrameCounter[playerId] += (1 + player->getPower()->getSpeedUp());
            UpdateModelAnimation(player->getPlayerModel(), this->anims[0], this->animFrameCounter[playerId]);
            player->setPlayerRoll(-180.0f);
            if (this->animFrameCounter[playerId] >= 20) {
                player->movePlayerUp();
                this->animFrameCounter[playerId] = 0;
                this->animRunningUp[playerId] = false;
            }
        }
    }
}

void Map::drawAi(std::shared_ptr<IMovable> &ai, std::vector<std::shared_ptr<Bomb>> &bombs)
{
    Input::Button aiKey = ai->checkAction(Input::Button::NONE, bombs, *this);
    int playerId = ai->getPlayerId();

    if (!ai)
        return;
    if ((aiKey == Input::Button::RIGHT && !checkColl(2.0f, 0.0f, 0.0f, 0.0f, cubeSize, ai)) || this->animRunningRight[playerId]) {
        if (this->animRunningRight[playerId] || (this->animRunningRight[playerId] == false && this->animRunningLeft[playerId] == false && this->animRunningUp[playerId] == false && this->animRunningDown[playerId] == false)) {
            this->animRunningRight[playerId] = true;
            this->animFrameCounter[playerId] += (1 + ai->getPower()->getSpeedUp());
            UpdateModelAnimation(ai->getPlayerModel(), this->anims[0], this->animFrameCounter[playerId]);
            ai->setPlayerRoll(-90.0f);
            if (this->animFrameCounter[playerId] >= 20) {
                ai->movePlayerRight();
                this->animFrameCounter[playerId] = 0;
                this->animRunningRight[playerId] = false;
            }
        }
    }
    else if ((aiKey == Input::Button::LEFT && !checkColl(0.0f, 2.0f, 0.0f, 0.0f, cubeSize, ai)) || this->animRunningLeft[playerId]) {
        if (this->animRunningLeft[playerId] || (this->animRunningLeft[playerId] == false && this->animRunningRight[playerId] == false && this->animRunningUp[playerId] == false && this->animRunningDown[playerId] == false)) {
            this->animRunningLeft[playerId] = true;
            this->animFrameCounter[playerId] += (1 + ai->getPower()->getSpeedUp());
            UpdateModelAnimation(ai->getPlayerModel(), this->anims[0], this->animFrameCounter[playerId]);
            ai->setPlayerRoll(90.0f);
            if (this->animFrameCounter[playerId] >= 20) {
                ai->movePlayerLeft();
                this->animFrameCounter[playerId] = 0;
                this->animRunningLeft[playerId] = false;
            }
        }
    }
    else if ((aiKey == Input::Button::DOWN && !checkColl(0.0f, 0.0f, 0.0f, 2.0f, cubeSize, ai)) || this->animRunningDown[playerId]) {
        if (this->animRunningDown || (this->animRunningDown[playerId] == false && this->animRunningLeft[playerId] == false && this->animRunningUp[playerId] == false && this->animRunningRight[playerId] == false)) {
            this->animRunningDown[playerId] = true;
            this->animFrameCounter[playerId] += (1 + ai->getPower()->getSpeedUp());
            UpdateModelAnimation(ai->getPlayerModel(), this->anims[0], this->animFrameCounter[playerId]);
            ai->setPlayerRoll(0.0);
            if (this->animFrameCounter[playerId] >= 20) {
                ai->movePlayerDown();
                this->animFrameCounter[playerId] = 0;
                this->animRunningDown[playerId] = false;
            }
        }
    }
    else if ((aiKey == Input::Button::UP && !checkColl(0.0f, 0.0f, 2.0f, 0.0f, cubeSize, ai)) || this->animRunningUp[playerId]) {
        if (this->animRunningUp[playerId] || (this->animRunningUp[playerId] == false && this->animRunningLeft[playerId] == false && this->animRunningDown[playerId] == false && this->animRunningRight[playerId] == false)) {
            this->animRunningUp[playerId] = true;
            this->animFrameCounter[playerId] += (1 + ai->getPower()->getSpeedUp());
            UpdateModelAnimation(ai->getPlayerModel(), this->anims[0], this->animFrameCounter[playerId]);
            ai->setPlayerRoll(-180.0);
            if (this->animFrameCounter[playerId] >= 20) {
                ai->movePlayerUp();
                this->animFrameCounter[playerId] = 0;
                this->animRunningUp[playerId] = false;
            }
        }
    }
}

void Map::checkInput(std::vector<std::shared_ptr<IMovable>> &players, std::vector<std::shared_ptr<Bomb>> &bombs)
{
    for (auto &player : players) {
        if (player->getType() == PLAYER)
            movePlayer(player);
        else
            drawAi(player, bombs);
    }
}

bool Map::checkColl(float right, float left, float up, float down, Vector3 cubeSize, std::shared_ptr<IMovable> &player)
{
    Vector3 playerPosition = player->getPlayerPos();

    for (auto it = std::begin(this->casesPositions); it != std::end(this->casesPositions); ++it) {
        if ((it->w != 1.0f && player->getPower()->getWallPass() == true) || player->getPower()->getWallPass() == false) {
            if (CheckCollisionBoxes((BoundingBox){(Vector3) {
                playerPosition.x - left - 0.5f/2,
                playerPosition.y - 0.5f/2,
                playerPosition.z - up - 0.5f/2 },
                (Vector3) {
                    playerPosition.x + right + 0.5f/2,
                    playerPosition.y + 0.5f/2,
                    playerPosition.z + down + 0.5f/2
                }},
                (BoundingBox){(Vector3){
                    it->x - cubeSize.x/2,
                    it->y - cubeSize.y/2,
                    it->z - cubeSize.z/2 },
                    (Vector3) {
                        it->x + cubeSize.x/2,
                        it->y + cubeSize.y/2,
                        it->z + cubeSize.z/2
                }}))
            return 1;
        }
    }
    return 0;
}

void Map::setCasesPositions()
{
    std::vector<std::string> realMap = this->getMap();
    Vector3 cubePosition = { 0.0f, -10.0f, 0.0f };

    for (unsigned int y = 0; y < realMap.size(); y++) {
        for (unsigned int x = 0; x < realMap[y].size(); x++) {
            if (realMap[y][x] == '0' || realMap[y][x] == '7') {
                cubePosition.x += cubeSize.x;
            } else if (realMap[y][x] == '1') {
                casesPositions.push_back((Vector4) { cubePosition.x, cubePosition.y, cubePosition.z, 1.0f });
                cubePosition.x += cubeSize.x;
            } else if (realMap[y][x] == '2') {
                casesPositions.push_back((Vector4) { cubePosition.x, cubePosition.y, cubePosition.z, 2.0f });
                cubePosition.x += cubeSize.x;
            } else if (realMap[y][x] == '3') {
                cubePosition.x += cubeSize.x;
            } else if (realMap[y][x] == '4') {
                casesPositions.push_back((Vector4) { cubePosition.x, cubePosition.y, cubePosition.z, 2.0f });
                cubePosition.x += cubeSize.x;
            }
        }
        cubePosition.x = 0.0f;
        cubePosition.z += cubeSize.z;
    }
}

void Map::checkIfDead(std::shared_ptr<IMovable> &player)
{
    Vector3 playerPosition = player->getPlayerPos();
    std::vector<std::string> realMap = this->getMap();

    if (realMap[playerPosition.z / 2][playerPosition.x / 2] == '3') {
        player->setIsDead(true);
    }
}

void Map::printMap(std::vector<std::shared_ptr<IMovable>> &players, std::vector<std::shared_ptr<Bomb>> &bombVec)
{
    const int screenWidth = 800;
    std::string str;
    std::string str2;
    std::string str3;
    Vector3 cubePosition = { 0.0f, -10.0f, 0.0f };
    std::vector<std::string> realMap = this->getMap();
    Vector3 mapPosition = { 0.0f, -11.0f, 0.0f };

	UpdateCamera(&this->camera);
	_raylib->clearBackground();
	_raylib->beginDrawing();
	BeginMode3D(this->camera);
    setCasesPositions();
    for (unsigned int y = 0; y < realMap.size(); y++) {
        for (unsigned int x = 0; x < realMap[y].size(); x++) {
            if (realMap[y][x] == '0' || realMap[y][x] == '7') {
                cubePosition.x += cubeSize.x;
            } else if (realMap[y][x] == '1') {
                DrawCubeTexture(this->box_crate, cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, WHITE);
                cubePosition.x += cubeSize.x;
            } else if (realMap[y][x] == '2') {
                cubePosition.x += cubeSize.x;
            } else if (realMap[y][x] == '3') {
                DrawModel(this->modelExplo, (Vector3){(float)(x * 2), -10.0f, (float)(y * 2)}, this->exploScale, WHITE);
                cubePosition.x += cubeSize.x;
            } else if (realMap[y][x] == '4') {
                DrawCubeTexture(this->box_crate, cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, BLUE);
                cubePosition.x += cubeSize.x;
            }
        }
        cubePosition.x = 0.0f;
        cubePosition.z += cubeSize.z;
	}
    for (auto &player : players) {
        if (_raylib->isMouseButtonDown() && !this->active) {
            this->position = { player->getPlayerPos().x, player->getPlayerPos().z };
            active = true;
            this->position.x -= frameWidth/2.0f;
            this->position.y -= frameHeight/2.0f;
        }
        if (active) {
            this->framesCounter++;
            if (this->framesCounter > 2) {
                this->currentFrame++;
                if (this->currentFrame >= 5) {
                    this->currentFrame = 0;
                    this->currentLine++;
                    if (this->currentLine >= 5) {
                        this->currentLine = 0;
                        this->active = false;
                    }
                }
                this->framesCounter = 0;
            }
        }
        this->frameRec.x = this->frameWidth*this->currentFrame;
        this->frameRec.y = this->frameHeight*this->currentLine;
        player->setPlayerTransform((Vector3){ DEG2RAD*pitch, DEG2RAD*yaw, DEG2RAD*player->getPlayerRoll()});

        DrawTexture(this->background, 0, 0, WHITE);
        for (unsigned int i = 0; i < bombVec.size(); i++) {
			std::chrono::steady_clock::time_point tmp = std::chrono::steady_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(tmp - bombVec[i]->bombClk);
			bombVec[i]->drawBomb();
			if ((float)time_span.count() > 3.0f && !bombVec.empty()) {
                if (bombVec[i]->inOnce == false) {
                    delBombMap(bombVec[i], player);
                    bombVec[i]->inOnce = true;
                }
            }
            if ((float)time_span.count() > 4.0f && !bombVec.empty()) {
                delExplosionMap(bombVec[i], player);
                bombVec.erase(bombVec.begin() + i);
                player->setActiveBomb(-1);
                i = 0;
            }
        }
        DrawModel(this->model2, mapPosition, 1.0f, WHITE);
        DrawTextureEx(this->cubicmap, (Vector2){ screenWidth - this->cubicmap.width*4.0f - 20, 20.0f }, 0.0f, 4.0f, WHITE);
        DrawRectangleLines(screenWidth - this->cubicmap.width*4 - 20, 20, this->cubicmap.width*4, this->cubicmap.height*4, GREEN);
        setBombMap(bombVec);
        DrawModelEx(player->getPlayerModel(), player->getPlayerPos(), this->rotationAxis, this->rotationAngle, this->scale, player->getColor());
    }
    EndMode3D();
    emptyBoxVec();
}