/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Save
*/

#ifndef SAVE_HPP_
	#define SAVE_HPP_

	#include "Utils.hpp"
	#include <iostream>
	#include <fstream>
	#include <memory>
	#include "Movable.hpp"
namespace Indie {
	class Save {
		public:
			Save() = default;
			~Save() = default;

			void loadFile(std::vector<std::shared_ptr<IMovable>> &players, std::vector<std::string> &);
			void saveFile(const std::vector<std::string> &);

		private:
			int _nbLines;
			int _nbCols;
	};
}
#endif /* !SAVE_HPP_ */
