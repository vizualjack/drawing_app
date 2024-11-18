#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "gui.hpp"
#include "global.hpp"

int Settings::brushSize = 3;
tgui::Color Settings::brushColor = tgui::Color::Black;
sf::RenderTexture Settings::canvasTexture;

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "SFML");
    tgui::Color baseColor(0,0,0);
    Settings::canvasTexture.create(100, 100);
    Settings::canvasTexture.clear(sf::Color::White);
    sf::Sprite canvasSprite(Settings::canvasTexture.getTexture());
    tgui::Gui gui(window);
    // auto menuBar = tgui::MenuBar::create();
    // menuBar->addMenu("View");
    // menuBar->addMenuItem("Center 0 0");
    // menuBar->connectMenuItem({"View", "Center 0 0"}, [&window](){
    //     auto wView = window.getView();
    //     wView.setCenter(0, 0);
    //     window.setView(wView);
    // });
    // menuBar->addMenuItem("Set default view");
    // menuBar->connectMenuItem({"View", "Set default view"}, [&window](){
    //     window.setView(window.getDefaultView());
    // });
    // gui.add(menuBar);
    auto drawCanvas = tgui::CanvasSFML::create({600, 400});
    gui.add(drawCanvas);
    bool panning = false;
    sf::Vector2i lastMousePosition;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            // else if(event.mouseButton.button == sf::Mouse::Button::Right && event.type == sf::Event::MouseButtonPressed) {
            //     panning = true;
            //     lastMousePosition = sf::Mouse::getPosition(window);
            // }
            // else if((event.mouseButton.button == sf::Mouse::Button::Right && event.type == sf::Event::MouseButtonReleased) || event.type == sf::Event::MouseLeft) panning = false;
            // else if(event.type == sf::Event::MouseMoved && panning) {
            //     sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            //     sf::Vector2f offset(
            //         float(lastMousePosition.x - mousePosition.x), // * zoomLevel,
            //         float(lastMousePosition.y - mousePosition.y)  // * zoomLevel
            //     );
            //     // std::cout << "Move view with offset" << std::to_string(offset.x) << ", y" << std::to_string(offset.y) << std::endl;
            //     // drawCanvas->set
            //     auto canvasView = drawCanvas->getView();
            //     canvasView.move(offset);
            //     drawCanvas->setView(canvasView);
            //     lastMousePosition = mousePosition;
            // }
            else if (event.type == sf::Event::Resized) {
                // auto wView = window.getView();
                // wView.setSize(event.size.width, event.size.height);
                window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
                drawCanvas->setSize({event.size.width, event.size.height});
                // auto dView = drawCanvas->getView();
                // dView.setSize(event.size.width, event.size.height);
                // drawCanvas->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
            }
            window.clear(baseColor);
            drawCanvas->clear();
            drawCanvas->draw(canvasSprite);
            // mouse pos viewer
            sf::Vector2i mouseWindowPosition = sf::Mouse::getPosition(window);
            auto mouseViewPos = window.mapPixelToCoords(mouseWindowPosition, window.getView());
            std::cout << "mouse window pos - x: " << std::to_string(mouseWindowPosition.x) << " y: " << std::to_string(mouseWindowPosition.y) << std::endl;
            std::cout << "mouse view pos - x: " << std::to_string(mouseViewPos.x) << " y: " << std::to_string(mouseViewPos.y) << std::endl;
            sf::CircleShape mouseCircle(5.f);
            mouseCircle.setFillColor(sf::Color::Transparent);
            mouseCircle.setOutlineColor(sf::Color::Red);
            mouseCircle.setOutlineThickness(1.f);
            mouseCircle.setPosition(mouseViewPos.x-2.5f, mouseViewPos.y-2.5f);
            drawCanvas->draw(mouseCircle);
            // ################
            drawCanvas->display();
            gui.draw();
            window.display();
            std::cout << "window size - width: " << std::to_string(window.getSize().x) << " height: " << std::to_string(window.getSize().y) << std::endl;
            std::cout << "window view size - width: " << std::to_string(window.getView().getSize().x) << " height: " << std::to_string(window.getView().getSize().y) << std::endl;
            std::cout << "drawCanvas size - width: " << std::to_string(drawCanvas->getSize().x) << " height: " << std::to_string(drawCanvas->getSize().y) << std::endl;
            std::cout << "drawCanvas view size - width: " << std::to_string(drawCanvas->getView().getSize().x) << " height: " << std::to_string(drawCanvas->getView().getSize().y) << std::endl;
            std::cout << "drawCanvas full size - width: " << std::to_string(drawCanvas->getFullSize().x) << " height: " << std::to_string(drawCanvas->getFullSize().y) << std::endl;
            std::cout << "================" << std::endl;
        }
    }
}
