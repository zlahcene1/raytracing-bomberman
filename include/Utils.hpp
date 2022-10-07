/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Utils
*/

#ifndef UTILS_HPP_
    #define UTILS_HPP_

    #include <iostream>
    #include <raylib.h>
    #include <vector>
	#include <ctime>
	#define UNUSED(x) (void)(x)

namespace Input {
	enum class Button {
		NONE = 0,
		SPACEBAR = 32,
		KEY_A = 65,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		QUIT = 256,
		ENTER,
		SETTING,
		DELETE = 259,
		RIGHT = 262,
		LEFT,
		DOWN,
		UP,
	};
}

#endif