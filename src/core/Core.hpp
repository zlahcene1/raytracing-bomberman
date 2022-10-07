/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include "Utils.hpp"
    #include "IMenu.hpp"

namespace Indie {
    class Core {
        public:
            Core();
            ~Core();

            void program();
            void saveGame();

        private:
            std::shared_ptr<IMenu> _menu;           // The current menu && move menu
    };
}

#endif /* !CORE_HPP_ */