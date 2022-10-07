/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Save
*/

#include "Save.hpp"
#include "Movable.hpp"
#include "Player.hpp"
#include "IA.hpp"

static const std::vector<std::vector<Input::Button>> keybinds {{
	{Input::Button::LEFT, Input::Button::UP, Input::Button::RIGHT, Input::Button::DOWN, Input::Button::SPACEBAR},
	{Input::Button::KEY_A, Input::Button::KEY_W, Input::Button::KEY_D, Input::Button::KEY_S, Input::Button::KEY_E},
	{Input::Button::KEY_J, Input::Button::KEY_I, Input::Button::KEY_L, Input::Button::KEY_K, Input::Button::KEY_O},
	{Input::Button::KEY_C, Input::Button::KEY_F, Input::Button::KEY_B, Input::Button::KEY_V, Input::Button::KEY_G}
}};

void Indie::Save::loadFile(std::vector<std::shared_ptr<IMovable>> &players, std::vector<std::string> &baseMap)
{
    std::ifstream file("../save.txt", std::ios::in);
	int id = 0;

    if (file) {
        std::string contenu;
        for (int i = 0; i < 14; i++) {
            std::getline(file, contenu);
            baseMap.push_back(contenu);
        }
        file.close();
		for (unsigned int y = 0; y < baseMap[y].size(); y++) {
			for (unsigned int x = 0; x < baseMap[x].size(); x++) {
				if (baseMap[y][x] >= 'a' && baseMap[y][x] <= 'z') {
					players.push_back(std::make_shared<Player>("player", (Vector3){static_cast<float>(x) * 2, -11.0, static_cast<float>(y) * 2}, keybinds[id], baseMap[y][x] - 'a'));
					id += 1;
				} else if (baseMap[y][x] >= 'A' && baseMap[y][x] <= 'Z') {
					players.push_back(std::make_shared<IA>((Vector3){static_cast<float>(x) * 2, -11.0, static_cast<float>(y) * 2}, "ai", baseMap[y][x] - 'A'));
				}
			}
		}
    } else
        std::cerr << "Impossible d'ouvrir le file !" << std::endl;
    return;
}

void Indie::Save::saveFile(const std::vector<std::string> &baseMap)
{
	std::ofstream createFile("../save.txt");
	createFile.close();
    std::ofstream file("../save.txt", std::ios::in);

    if (file) {
        std::string contenu;
        for (auto &line : baseMap) {
            for (auto &col : line)
                contenu += col;
            contenu += "\n";
            file << line << std::endl;
        }
        file.close();
    }
    else
        std::cerr << "Impossible d'ouvrir le file !" << std::endl;
    return;
}