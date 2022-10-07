/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Raylib
*/

#ifndef RAYLIB_HPP_
    #define RAYLIB_HPP_

    #include "Utils.hpp"
	#include "Button.hpp"
	#include "DropDown.hpp"
	#include "SoundBar.hpp"
	#include "Input.hpp"
	#include "Sound.hpp"
    #include "Music.hpp"
    #include "Image.hpp"
	#include "Color.hpp"
	#include "Vector2.hpp"
	#include "Rectangle.hpp"
	#include "IMenu.hpp"
    #include <vector>

class Raylib {
    public:
        Raylib() = default;
        ~Raylib() = default;


        /******** WINDOW ********/
        void initWindow(int, int, int, const std::string &);
        void beginDrawing();
        bool windowShouldClose() const;
        int getScreenWidth() const;
        int getScreenHeight() const;
        void tick();
        void clearBackground();
        void endDrawing();
		void resizeWindow(const int &width, const int &height);
		void hideCursor();
		void showCursor();

        /******** EVENTS ********/
        Input::Button isKeyPressed();
		bool isKeyReleased(const Input::Button &);
		Indie::CppVector2 getMousePosition();
		bool checkCollisionPointRec(const Indie::CppVector2 &,
		const Indie::CppRectangle &);
		bool isMouseButtonDown();
		bool isMouseButtonReleased();

        /******** DRAW GUI ********/
        void drawDropDown(std::unique_ptr<Gui::DropDown> &dropdown);
        void drawRectangle(int, int, int, int, const Indie::CppColor &);
		void drawButton(std::unique_ptr<Gui::Button> &);
		void drawSoundBar(std::unique_ptr<Gui::SoundBar<Indie::IAudio>> &soundBar);
		void drawInputBox(std::unique_ptr<Gui::InputBox> &inputBox);
        /******** DRAW TEXT ********/
        void drawText(const std::string &, int, int, int, const Indie::CppColor &);
        int measureText(const std::string &, int) const;
		Indie::CppVector2 measureTextEx(const std::string &, const float &, const float &);

        /******** SOUND MUSIC ********/
        void playMusicStream(Indie::CppMusic &);
        void pauseMusicStream(Indie::CppMusic &);
        void resumeMusicStream(Indie::CppMusic &);
        void setMusicVolume(Indie::CppMusic &, const float &);
		void StopMusicStream(Indie::CppMusic &);

        /******** SOUND ********/
		void playSound(const Indie::CppSound &);
        void setSoundVolume(Indie::CppSound &, const float &);


        /******* IMAGE *******/
        void drawTextureRec(Indie::CppImage &, const Indie::CppVector2 &, const Indie::CppColor &);
		bool isWindowFullScreen();
		void toggleFullScreen();
		void setWindowState(const unsigned int &);
		void clearWindowState(const unsigned int &);


        /********* LOAD *********/
        // void loadModel(const std::string &);
        // void loadTexture(const std::string &);
        /********* UNLOAD *********/
        // void unloadModel(Indie::CppImage &);
        // void unloadTexture(Indie::CppImage &);


        // bomb.cpp = drawModel, loadModel, loadTexture
        // image.cpp = loadTexture, unloadTexture

        // map.cpp = all file 
        // music.cpp = loadMusicStream, UNloadMusicStream, UpdateMusicStream
        // sound.cpp = loadSound, unloadSound

        // player.cpp = loadModel, loadTexture, matrixRotateXYZ, drawModel, 

    private:
};

#endif /* !RAYLIB_HPP_ */