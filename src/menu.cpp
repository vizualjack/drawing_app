#include "gui.hpp"
#include "global.hpp"
#include <vector>
#include <thread>
#include <functional>
#include <string>


void saveImage(std::string fileName) {
    Settings::canvasTexture.getTexture().copyToImage().saveToFile(fileName);
}

void loadImage(std::string fileName) {
    sf::Texture imageTexture;
    imageTexture.loadFromFile(fileName);
    sf::Sprite imageSprite;
    imageSprite.setTexture(imageTexture);
    Settings::canvasTexture.create(imageTexture.getSize().x, imageTexture.getSize().y);
    Settings::canvasTexture.clear(sf::Color::White);
    Settings::canvasTexture.draw(imageSprite);
    Settings::canvasTexture.display();
}

bool fileDialogOpen = false;
void openFileDialog(void (*onSelectedFunc)(std::string) ) {
    sf::RenderWindow dialogWindow(sf::VideoMode(550, 550), "File Selection");
    tgui::Gui dialogGui{dialogWindow};
    tgui::FileDialog::Ptr fileDialog;
    if (onSelectedFunc == loadImage) fileDialog = tgui::FileDialog::create("Open file", "Open");
    else {
        fileDialog = tgui::FileDialog::create("Save file", "Save");
        fileDialog->setFileMustExist(false);
    }
    fileDialog->setFileTypeFilters({{"*.png",{"*.png"}}, {"*.jpg",{"*.jpg"}}, {"*.bmp",{"*.bmp"}}, {"*.gif",{"*.gif"}}});
    fileDialog->onFileSelect([&](std::vector<tgui::Filesystem::Path> files) {
        auto selectedFilterType = fileDialog->getFileTypeFilters()[fileDialog->getFileTypeFiltersIndex()];
        auto fileType = selectedFilterType.first.replace("*", "");
        auto file = files[0];
        if(fileDialog->getFileMustExist()) onSelectedFunc(file.getFilename().toStdString());
        else {
            auto fullFileName = file.getFilename() + fileType;
            onSelectedFunc(fullFileName.toStdString());
        }
    });
    fileDialog->onClose([&dialogWindow](){
        fileDialogOpen = false;
        dialogWindow.close();
    });
    fileDialog->setAutoLayout(tgui::AutoLayout::Fill);
    std::cout << "Open color picker..." << std::endl;
    dialogGui.add(fileDialog);
    fileDialogOpen = true;
    dialogGui.draw();
    dialogWindow.display();
    dialogGui.mainLoop();
    fileDialogOpen = false;
}

bool sizeDialogOpen = false;
void openSizeDialog() {
    sf::RenderWindow dialogWindow(sf::VideoMode(230, 100), "New image", sf::Style::Titlebar | sf::Style::Close);
    tgui::Gui dialogGui{dialogWindow};
    sizeDialogOpen = true;
    sf::Event event;
    bool wannaClose = false;
    auto label = tgui::Label::create("Width:");
    label->setPosition({10,10});
    dialogGui.add(label);
    label = tgui::Label::create("Height:");
    label->setPosition({10,40});
    dialogGui.add(label);
    auto widthInput = tgui::EditBox::create();
    widthInput->setInputValidator("[0-9]*");
    widthInput->setPosition({70,10});
    auto heightInput = tgui::EditBox::create();
    heightInput->setInputValidator("[0-9]*");
    heightInput->setPosition({70,40});
    auto createButton = tgui::Button::create("Create");
    createButton->onClick([&wannaClose, &widthInput, &heightInput]() {
        auto width = widthInput->getText().toInt();
        auto height = heightInput->getText().toInt();
        std::cout << "New image size: " << width << ", " << height << std::endl;
        Settings::canvasTexture.create(width, height);
        Settings::canvasTexture.clear(sf::Color::White);
        wannaClose = true;
    });
    createButton->setPosition({160,70});
    auto cancelButton = tgui::Button::create("Cancel");
    cancelButton->onClick([&wannaClose]() {
        wannaClose = true;
    });
    cancelButton->setPosition({10,70});
    dialogGui.add(widthInput);
    dialogGui.add(heightInput);
    dialogGui.add(cancelButton);
    dialogGui.add(createButton);
    dialogGui.draw();
    dialogWindow.display();
    while(dialogWindow.isOpen()) {
        while(dialogWindow.pollEvent(event)) {
            dialogGui.handleEvent(event);
            if(event.type == sf::Event::Closed) wannaClose = true;
            if(wannaClose) dialogWindow.close();
            dialogGui.draw();
            dialogWindow.display();
        }
    }
    sizeDialogOpen = false;
}

void initMenu(tgui::Gui& gui) {
    auto menuBar = tgui::MenuBar::create();
    menuBar->addMenu("File");
    menuBar->addMenuItem("New");
    menuBar->addMenuItem("Save");
    menuBar->addMenuItem("Load");
    menuBar->connectMenuItem({"File", "New"}, []{
        if(!sizeDialogOpen) {
            std::thread([](){
                openSizeDialog();
            }).detach();
        }
    });
    menuBar->connectMenuItem({"File", "Save"}, []{
        if(!fileDialogOpen) {
            std::thread([](){
                openFileDialog(saveImage);
            }).detach();
        }
    });
    menuBar->connectMenuItem({"File", "Load"}, []{
        std::thread([](){
            openFileDialog(loadImage);
        }).detach();
    });
    menuBar->setAutoLayout(tgui::AutoLayout::Top);
    menuBar->setHeight(20);
    gui.add(menuBar);
    menuBar->getRenderer()->setBackgroundColor(tgui::Color(100,100,100));
    menuBar->getRenderer()->setTextColor(tgui::Color::White);
}