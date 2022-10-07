/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-tom.fuller
** File description:
** Settings
*/

#include "Settings.hpp"

Indie::Settings::Settings(const std::shared_ptr<IMenu> &menu)
: _raylib(std::make_unique<Raylib>()), _menu(menu)
{
	std::vector<std::unique_ptr<Gui::Button>> content;
	float widthCoef = static_cast<float>(S_DD_WIDTH) / static_cast<float>(WIDTH);
	float heightCoef = static_cast<float>(S_DD_HEIGHT) / static_cast<float>(HEIGHT);
	float musicVolume = 0.5;
	float soundVolume = 0.5;
	float flScreenX = static_cast<float>(FL_SCREEN_WHIDTH) / static_cast<float>(WIDTH);
	float fltScreenY = static_cast<float>(FL_SCREEN_HEIGHT) / static_cast<float>(HEIGHT);

	if (menu->getMusic().size())
		musicVolume = menu->getMusic()[0]->getVolume();
	if (menu->getMusic().size())
		soundVolume = menu->getSound()[0]->getVolume();
	content.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "Resolution  v", WHITE));
	content.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "1920x1080", WHITE));
	content.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "1280x720", WHITE));
	content.push_back(std::make_unique<Gui::Button>(0, 0, widthCoef, heightCoef, BLACK, RED, "800x450", WHITE));
	_resolutionDropDown = std::move(std::make_unique<Gui::DropDown>(content, 40, 200));
	_menuActions = std::make_unique<Indie::CppSound>("../assets/audio/sounds/button_actions.wav", 0.5);
	_music = std::make_unique<Gui::SoundBar<Indie::IAudio>>("../assets/UI/soundbar_cursor.png", "../assets/UI/soundbar_bar.png", soundVolume, menu->getSound());
	_sound = std::make_unique<Gui::SoundBar<Indie::IAudio>>("../assets/UI/soundbar_cursor.png", "../assets/UI/soundbar_bar.png", musicVolume, menu->getMusic());
	_fullScreen = std::make_unique<Gui::Button>(0, 0, flScreenX, fltScreenY, BLACK, RED, "Fullscreen", WHITE);
}

Indie::Settings::~Settings()
{}

int Indie::Settings::run()
{
	_raylib->showCursor();
	while (!closeMenu()) {
		update();
		if (event() == 1)
			return 0;
	}
	return 0;
}

void Indie::Settings::startMenu()
{}

bool Indie::Settings::closeMenu() const
{
    return _raylib->windowShouldClose();
}

void Indie::Settings::update()
{
	int screenHeight = _raylib->getScreenHeight();
	int screenWidth = _raylib->getScreenWidth();
	CppVector2 soundBarPos = _sound->getBarPos();
	CppVector2 soundBarSize = _sound->getBar().getRecSize();
	int fontSize = FONT_SIZE * (screenWidth * screenHeight) / (WIDTH * HEIGHT);
	std::string text;
	int border = 30 * (screenWidth * screenHeight) / (WIDTH * HEIGHT);
	int backgroundBorderX = screenWidth / 5 * 1.1;
	int backgroundBorderY = (screenHeight / 7) * 1.3;
	int backgroundSizeX = (screenWidth / 5 * 3) / 7 * 3;
	int backgroundSizeY = (screenHeight / 7 * 5) / 10 * 9;
	int reverseBackgroundX = screenWidth - backgroundBorderX - backgroundSizeX;
	std::string header = GRAPHICS_HEADER;
	int headerFontSize = screenWidth * screenHeight / 100000 * 1.80;
	int headerSize = _raylib->measureText(header, headerFontSize);

	_menu->drawUi();
	_raylib->drawRectangle(0, 0, screenWidth, screenHeight, Color({0, 0, 0, 70}));
	_raylib->drawRectangle(screenWidth / 5.0, screenHeight / 7,
	screenWidth / 5 * 3, screenHeight / 7 * 5, Color({130, 130, 130, 235}));
	_raylib->drawRectangle(backgroundBorderX, (screenHeight / 7) * 1.3,
	backgroundSizeX, backgroundSizeY, Color(BLACK));
	_raylib->drawRectangle(reverseBackgroundX, (screenHeight / 7) * 1.3,
	backgroundSizeX, backgroundSizeY, Color(BLACK));
	_raylib->drawText(header, backgroundBorderX + (backgroundSizeX / 2) - headerSize / 2, backgroundBorderY + backgroundSizeY / 15, headerFontSize, WHITE);
	header = AUDIO_SETTINGS;
	headerSize = _raylib->measureText(header, headerFontSize);
	_raylib->drawText(header, reverseBackgroundX + (backgroundSizeX / 2) - headerSize / 2, backgroundBorderY + backgroundSizeY / 15, headerFontSize, WHITE);
	_resolutionDropDown->resize(screenWidth, screenHeight);
	_resolutionDropDown->reposition(backgroundBorderX + (backgroundSizeX / 2) - _resolutionDropDown->getHeader()->getWidth() / 2, backgroundBorderY + ((screenHeight / 7 * 5) / 10 * 9) / 5);
	if (border < 10)
		border = 10;

	text = "Music volume: " + std::to_string(static_cast<int>(_sound->getVolume() * 100));
	_raylib->drawText(text, soundBarPos.getVectorX(), soundBarPos.getVectorY() - border, fontSize, WHITE);
	soundBarPos= _music->getBarPos();
	text = "Effects volume: " + std::to_string(static_cast<int>(_music->getVolume() * 100));
	_raylib->drawText(text, soundBarPos.getVectorX(), soundBarPos.getVectorY() - border, fontSize, WHITE);	_sound->setSize(screenWidth, screenHeight);
	_music->setSize(screenWidth, screenHeight);
	_music->setPos(reverseBackgroundX + backgroundSizeX / 2 - soundBarSize.getVectorX() / 2, screenHeight / 10 * 7);
	_sound->setPos(reverseBackgroundX + backgroundSizeX / 2 - soundBarSize.getVectorX() / 2, screenHeight / 10 * 5);
	_fullScreen->reposition(backgroundBorderX + (backgroundSizeX / 2 - _fullScreen->getWidth() / 2), backgroundBorderY + ((screenHeight / 7 * 5) / 10 * 9) / 5 * 3);
	_fullScreen->resize(screenWidth, screenHeight);
	_raylib->drawButton(_fullScreen);
	_raylib->drawSoundBar(_music);
	_raylib->drawSoundBar(_sound);
	_raylib->drawDropDown(_resolutionDropDown);
	_raylib->tick();
}

Return_Status Indie::Settings::event()
{
	Input::Button key = _raylib->isKeyPressed();
	Indie::CppVector2 mousePos = _raylib->getMousePosition();
	bool isReleased = _raylib->isMouseButtonReleased();
	bool isPressed = _raylib->isMouseButtonDown();
	int newWindowWidth = 0;
	int newWindowHeight = 0;
	Indie::CppVector2 posRec;
	Indie::CppVector2 sizeRec;
	std::string res;
	CppRectangle _fullScreenRec = CppRectangle({static_cast<float>(_fullScreen->getPosX()),
	 											static_cast<float>(_fullScreen->getPosY()),
												static_cast<float>(_fullScreen->getWidth()),
												static_cast<float>(_fullScreen->getHeight())});

	if (_resolutionDropDown->getSelected() && _raylib->isMouseButtonReleased()
		&& _resolutionDropDown->isMouseOnButton(mousePos)) {
		res = _resolutionDropDown->selectButton(mousePos)->getText();
		if (!res.compare("Resolution  v"))
			return NOTHING;
		if (IsWindowFullscreen())
			_raylib->clearWindowState(FLAG_FULLSCREEN_MODE);
		_raylib->setWindowState(FLAG_WINDOW_RESIZABLE);
		newWindowWidth = std::stoi(res.substr(0, res.find("x")));
		newWindowHeight = std::stoi(res.substr(res.find("x") + 1, res.length()));
		_raylib->resizeWindow(newWindowWidth, newWindowHeight);
		_raylib->playSound(*_menuActions);
	}
	if (isReleased)
		_resolutionDropDown->setSelected(false);
	if (!_resolutionDropDown->getSelected() &&
	_resolutionDropDown->isMouseOnButton(mousePos) && isReleased)
		_resolutionDropDown->setSelected(true);
	posRec = _sound->getCursor().getPos();
	sizeRec = _sound->getCursor().getRecSize();
	if (isPressed && _raylib->checkCollisionPointRec(mousePos, _sound->getBar().getRectangleBounds())) {
		_sound->setVolume(mousePos.getVectorX());
		_menuActions->setVolume(_sound->getVolume());
	}
	if (_raylib->isWindowFullScreen()) {
		_fullScreen->setState(Gui::DISABLED);
	} else
		_fullScreen->setState(Gui::NOT_SELECTED);
	if (_fullScreen->getState() != Gui::DISABLED) {
		if (_raylib->checkCollisionPointRec(mousePos, _fullScreenRec))
			_fullScreen->setState(Gui::SELECTED);
		if (_raylib->checkCollisionPointRec(mousePos, _fullScreenRec) && isPressed) {
			_fullScreen->setState(Gui::PRESSED);
			_raylib->toggleFullScreen();
		} if (!_raylib->checkCollisionPointRec(mousePos, _fullScreenRec))
			_fullScreen->setState(Gui::NOT_SELECTED);
	}
	if (isPressed && _raylib->checkCollisionPointRec(mousePos, _music->getBar().getRectangleBounds()))
		_music->setVolume(mousePos.getVectorX());
	_resolutionDropDown->refreshButtonsState();
	if (_resolutionDropDown->isMouseOnButton(mousePos))
		_resolutionDropDown->selectButton(mousePos)->setState(Gui::SELECTED);
	if (_resolutionDropDown->isMouseOnButton(mousePos) && _raylib->isMouseButtonDown())
		_resolutionDropDown->selectButton(mousePos)->setState(Gui::PRESSED);
    if (key == Input::Button::ENTER)
		return LAST_MENU;
	return NOTHING;
}

void Indie::Settings::drawUi()
{}

std::vector<std::shared_ptr<Indie::IAudio>> Indie::Settings::getSound() const
{
	return {};
}

std::vector<std::shared_ptr<Indie::IAudio>> Indie::Settings::getMusic() const
{
	return {};
}