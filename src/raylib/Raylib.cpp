/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Raylib
*/

#include "Raylib.hpp"
#include "Utils.hpp"
#include "Image.hpp"

void Raylib::initWindow(int width, int height, int fps, const std::string &title)
{
    InitWindow(width, height, title.c_str());
    SetTargetFPS(fps);
    InitAudioDevice();
}

void Raylib::beginDrawing()
{
    BeginDrawing();
}

bool Raylib::windowShouldClose() const
{
    return WindowShouldClose();
}

void Raylib::drawText(const std::string &text, int x, int y,
int size, const Indie::CppColor &color)
{
    DrawText(text.c_str(), x, y, size, color.getColor());
}

void Raylib::tick()
{
    beginDrawing();
    clearBackground();
    endDrawing();
}

void Raylib::clearBackground()
{
    ClearBackground(BLACK);
}

bool Raylib::isKeyReleased(const Input::Button &key)
{
    return IsKeyReleased(static_cast<int>(key));
}

Input::Button Raylib::isKeyPressed()
{
	int i = static_cast<int>(Input::Button::NONE);
	int end = static_cast<int>(Input::Button::UP);

	for (; i <= end; i++)
		if (IsKeyPressed(i))
			return static_cast<Input::Button>(i);
    return Input::Button::NONE;
}

void Raylib::endDrawing()
{
    EndDrawing();
}

void Raylib::drawRectangle(int x, int y, int width, int height, const Indie::CppColor &color)
{
    DrawRectangle(x, y, width, height, color.getColor());
}

int Raylib::getScreenWidth() const
{
    return GetScreenWidth();
}

int Raylib::getScreenHeight() const
{
    return GetScreenHeight();
}

int Raylib::measureText(const std::string &text, int fontSize) const
{
    return MeasureText(text.c_str(), fontSize);
}

Indie::CppVector2 Raylib::measureTextEx(const std::string &text,
const float &fontSize, const float &spacing)
{
	Vector2 size;

	size = MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, spacing);
	return Indie::CppVector2(size.x, size.y);
}

void Raylib::drawButton(std::unique_ptr<Gui::Button> &but)
{
	std::string text = but->getText();
	int fontSize = but->getFontSize();
	int posX = but->getPosX();
	int posY = but->getPosY();
	int width = but->getWidth();
	int height = but->getHeight();
	Indie::CppColor foreGround = but->getForeGround();
	Indie::CppColor backGround = but->getBackGround();
	Indie::CppColor textColor = but->getTextColor();
	Vector2 vector = MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, 1);
	int border = static_cast<float>(width * height) / 4000;

	if (border % 2)
		border += 1;
	if (border / 2 == 0)
		border = 2;
	drawRectangle(posX, posY, width, height, backGround);
    drawRectangle(posX + border / 2, posY + border / 2, width - border, height - border, foreGround);
    drawText(text, posX + width / 2 - vector.x / 2,
	posY + height / 2 - vector.y * 0.50, fontSize, textColor);
}

bool Raylib::isMouseButtonDown()
{
	return IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}

bool Raylib::isMouseButtonReleased()
{
	return IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}

void Raylib::resizeWindow(const int &width, const int &height)
{
	SetWindowSize(width, height);
}

void Raylib::drawDropDown(std::unique_ptr<Gui::DropDown> &dropdown)
{
	std::vector<std::unique_ptr<Gui::Button>> buttons;

	if (dropdown->getSelected()) {
		for (auto &button : dropdown->getButtons())
			drawButton(button);
	} else
		drawButton(dropdown->getHeader());
}

bool Raylib::checkCollisionPointRec(const Indie::CppVector2 &vector,
const Indie::CppRectangle &rectangle)
{
	Vector2 mousePos = vector.getVector2();
	Rectangle area = rectangle.getRectangle();

	if ((mousePos.x > area.x && mousePos.x <= area.width + area.x)
		&& mousePos.y > area.y && mousePos.y < area.height + area.y)
		return true;
	return false;
}

void Raylib::playSound(const Indie::CppSound &sound)
{
    PlaySound(sound.getSound());
}

void Raylib::setSoundVolume(Indie::CppSound &sound, const float &volume)
{
    SetSoundVolume(sound.getSound(), volume);
}

Indie::CppVector2 Raylib::getMousePosition()
{
	Vector2 vector = GetMousePosition();

	return Indie::CppVector2(vector.x, vector.y);
}

void Raylib::playMusicStream(Indie::CppMusic &music)
{
    PlayMusicStream(music.getMusic());
}

void Raylib::pauseMusicStream(Indie::CppMusic &music)
{
    PauseMusicStream(music.getMusic());
}

void Raylib::resumeMusicStream(Indie::CppMusic &music)
{
    ResumeMusicStream(music.getMusic());
}

void Raylib::setMusicVolume(Indie::CppMusic &music, const float &volume)
{
    SetMusicVolume(music.getMusic(), volume);
}

void Raylib::drawSoundBar(std::unique_ptr<Gui::SoundBar<Indie::IAudio>> &soundBar)
{
	drawTextureRec(soundBar->getBar(), soundBar->getBar().getPos(), Indie::CppColor(WHITE));
	drawTextureRec(soundBar->getCursor(), soundBar->getCursor().getPos(), Indie::CppColor(WHITE));
}

void Raylib::drawTextureRec(Indie::CppImage &image,
const Indie::CppVector2 &pos, const Indie::CppColor &color)
{
	DrawTextureRec(image.getTexture(), image.getRectangle().getRectangle(),
	pos.getVector2(), color.getColor());
}

bool Raylib::isWindowFullScreen()
{
	return IsWindowFullscreen();
}

void Raylib::toggleFullScreen()
{
	ToggleFullscreen();
}

void Raylib::setWindowState(const unsigned int &flags)
{
	SetWindowState(flags);
}

void Raylib::clearWindowState(const unsigned int &flags)
{
	ClearWindowState(flags);
}

void Raylib::drawInputBox(std::unique_ptr<Gui::InputBox> &inputBox)
{
	Indie::CppRectangle bounds = inputBox->getBounds();
	int posX = bounds.getRectangle().x;
	int posY = bounds.getRectangle().y;
	Indie::CppVector2 size = bounds.getRecSize();
	int border = static_cast<float>(size.getVectorX() * size.getVectorY()) / 1500;
	int fontSize = INPUT_FONT_SIZE * size.getVectorX() / INPUT_WIDTH;
	Indie::CppVector2 textSize = measureTextEx(inputBox->getText(), fontSize, 1);

	if (border % 2 != 0)
		border += 1;
	if (!border)
		border = 4;
	drawRectangle(posX, posY, size.getVectorX(), size.getVectorY(), inputBox->getBackgroundColor());
	drawRectangle(posX + border / 2, posY + border / 2, size.getVectorX() - border, size.getVectorY() - border, inputBox->getForeGroundColor());
	drawText(inputBox->getText(), posX + border / 2 + 2, posY + border / 2 + size.getVectorY() - border - textSize.getVectorY() - 2, fontSize, inputBox->getTextColor());
}

void Raylib::hideCursor()
{
	HideCursor();
}

void Raylib::showCursor()
{
	ShowCursor();
}

// void loadModel(const std::string &)
// {

// }

// void loadTexture(const std::string &)
// {

// }

// void unloadModel(Indie::CppImage &)
// {

// }

// void unloadTexture(Indie::CppImage &)
// {

// }