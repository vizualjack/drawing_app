#include "gui.hpp"
#include "global.hpp"
#include "consolePrinter.hpp"
#include <thread>


bool colorPickerOpen = false;
tgui::Button* colorButton;
void openColorPicker() {
    sf::RenderWindow colorPickerWindow(sf::VideoMode(550, 250), "Select a color");
    tgui::Gui colorPickerGui{colorPickerWindow};
    auto colorPicker = tgui::ColorPicker::create("", Settings::brushColor);
    colorPicker->onOkPress([](const tgui::Color& color) {
        // std::cout << "Color selected: " << std::to_string(color.getRed()) << ", " << std::to_string(color.getGreen()) << ", " << std::to_string(color.getBlue()) << std::endl;
        printToConsole("Color selected: " + std::to_string(color.getRed()) + ", " + std::to_string(color.getGreen()) + ", " + std::to_string(color.getBlue()));
        Settings::brushColor = color;
        colorButton->getRenderer()->setBackgroundColor(Settings::brushColor);
    });
    colorPicker->onClose([&colorPickerWindow](){
        colorPickerOpen = false;
        colorPickerWindow.close();
    });
    colorPicker->setAutoLayout(tgui::AutoLayout::Fill);
    // std::cout << "Open color picker..." << std::endl;
    printToConsole("Open color picker...");
    colorPickerGui.add(colorPicker);
    colorPickerOpen = true;
    colorPickerGui.mainLoop();
    colorPickerOpen = false;
}

void initToolbar(tgui::Gui& gui) {
    auto settingsBar = tgui::Grid::create();
    settingsBar->setAutoLayout(tgui::AutoLayout::Top);
    settingsBar->setHeight(40);
    gui.add(settingsBar);
    auto brushSizeLabel = tgui::Label::create("Brush size: 1");
    brushSizeLabel->setIgnoreMouseEvents(true);
    brushSizeLabel->setWidth(100);
    settingsBar->addWidget(brushSizeLabel, 0, 0, tgui::Grid::Alignment::Left, {10,0});
    auto brushSizeSlider = tgui::Slider::create(1, 20);
    brushSizeSlider->onValueChange([brushSizeLabel](float newValue) {
        Settings::brushSize = newValue;
        brushSizeLabel->setText("Brush size: " + std::to_string(Settings::brushSize)); 
    });
    settingsBar->addWidget(brushSizeSlider, 0, 1);
    auto colorButtonPtr = tgui::Button::create();
    colorButton = colorButtonPtr.get();
    colorButton->getRenderer()->setBackgroundColor(Settings::brushColor);
    colorButtonPtr->onPress([](){
        if(!colorPickerOpen) {
            std::thread([](){
                openColorPicker();
            }).detach();
        }
    });
    settingsBar->addWidget(colorButtonPtr, 0, 2);
}