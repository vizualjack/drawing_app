#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "gui.hpp"
#include "global.hpp"

int Settings::brushSize = 3;
tgui::Color Settings::brushColor = tgui::Color::Black;
sf::RenderTexture Settings::canvasTexture;

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "SFML + TGUI");
    tgui::Gui gui{window};
    // auto customTheme = tgui::Theme::create();
    // auto buttonRenderer = customTheme->getRenderer("Button");
    // customTheme->get
    auto theme = tgui::Theme::getDefault();
    tgui::ButtonRenderer btnRenderer = theme->getRenderer("Button");
    btnRenderer.setBackgroundColor(tgui::Color::Black);
    btnRenderer.setTextColor(tgui::Color::White);
    tgui::LabelRenderer labelRenderer = theme->getRenderer("Label");
    labelRenderer.setTextColor(tgui::Color::White);
    // tgui::Theme::setDefault(customTheme);
    initMenu(gui);
    initToolbar(gui);
    auto [drawCanvas, drawBackground] = initDrawCanvas(gui);
    drawCanvas->setAutoLayoutUpdateEnabled(false);
    tgui::Color baseColor(150,150,150);
    Settings::canvasTexture.create(100, 100); 
    Settings::canvasTexture.clear(sf::Color::White);
    bool drawing = false;
    bool panning = false;
    sf::Vector2i lastMousePosition;
    float zoomLevel = 1.f;
    sf::RenderTexture renderTexture;
    renderTexture.create(600,400);
    renderTexture.clear(sf::Color::Black);
    auto view = renderTexture.getView();
    auto imageSize = Settings::canvasTexture.getSize();
    view.setCenter(imageSize.x/2, imageSize.y);
    renderTexture.setView(view);
    // FIRST RENDERING
    window.clear(baseColor);
    drawCanvas->clear();
    renderTexture.clear(sf::Color::Black);
    renderTexture.draw(sf::Sprite(Settings::canvasTexture.getTexture()));
    renderTexture.display();
    drawCanvas->draw(sf::Sprite(renderTexture.getTexture()));
    drawCanvas->display();
    gui.draw();
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed) window.close();
            else if(event.type == sf::Event::MouseMoved && drawing) {
                tgui::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
                mousePos.y -= drawCanvas->getAbsolutePosition().y;
                auto mousePosInView = window.mapPixelToCoords(mousePos, renderTexture.getView());
                if(drawCanvas->isMouseOnWidget(tgui::Vector2f(mousePos.x, mousePos.y))) {
                    tgui::Vector2f posOnDrawCanvas(mousePosInView.x, mousePosInView.y);
                    auto acutalSize = Settings::brushSize / 2.0f;
                    sf::CircleShape brush(acutalSize);
                    brush.setPosition(posOnDrawCanvas.x - acutalSize, posOnDrawCanvas.y - acutalSize);
                    brush.setFillColor(Settings::brushColor);
                    Settings::canvasTexture.draw(brush);
                    Settings::canvasTexture.display();
                }
            }
            else if(event.mouseButton.button == sf::Mouse::Button::Left && event.type == sf::Event::MouseButtonPressed) drawing = true;
            else if((event.mouseButton.button == sf::Mouse::Button::Left && event.type == sf::Event::MouseButtonReleased) || event.type == sf::Event::MouseLeft) drawing = false;
            else if(event.mouseButton.button == sf::Mouse::Button::Right && event.type == sf::Event::MouseButtonPressed) {
                panning = true;
                lastMousePosition = sf::Mouse::getPosition(window);
            }
            else if((event.mouseButton.button == sf::Mouse::Button::Right && event.type == sf::Event::MouseButtonReleased) || event.type == sf::Event::MouseLeft) panning = false;
            else if(event.type == sf::Event::MouseMoved && panning) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f offset(
                    float(lastMousePosition.x - mousePosition.x) * zoomLevel,
                    float(lastMousePosition.y - mousePosition.y) * zoomLevel
                );
                std::cout << "Move view with offset" << std::to_string(offset.x) << ", y" << std::to_string(offset.y) << std::endl;
                auto canvasView = renderTexture.getView();
                canvasView.move(offset);
                renderTexture.setView(canvasView);
                lastMousePosition = mousePosition;
            }
            else if (event.type == sf::Event::MouseWheelScrolled) {
                tgui::Vector2f mousePos(event.mouseWheelScroll.x, event.mouseWheelScroll.y);
                auto canvasView = renderTexture.getView();
                if(drawCanvas->isMouseOnWidget(mousePos)) {
                    if (event.mouseWheelScroll.delta > 0) {
                        canvasView.zoom(0.9f);
                        zoomLevel *= 0.9f;
                    }
                    else {
                        canvasView.zoom(1.1f);
                        zoomLevel *= 1.1f;
                    }
                    renderTexture.setView(canvasView);
                    std::cout << "New zoom level: " << std::to_string(zoomLevel) << std::endl;
                }
            }
            else if (event.type == sf::Event::Resized) {
                auto wView = window.getView();
                wView.setSize(event.size.width, event.size.height);
                window.setView(wView);
                renderTexture.create(drawCanvas->getSize().x, drawCanvas->getSize().y);
                zoomLevel = 1.f;
                auto view = renderTexture.getView();
                auto imageSize = Settings::canvasTexture.getSize();
                view.setCenter(imageSize.x/2, imageSize.y);
                renderTexture.setView(view);
            }
            window.clear(baseColor);
            drawCanvas->clear();
            renderTexture.clear(sf::Color::Black);
            renderTexture.draw(sf::Sprite(Settings::canvasTexture.getTexture()));
            renderTexture.display();
            drawCanvas->draw(sf::Sprite(renderTexture.getTexture()));
            drawCanvas->display();
            gui.draw();
            window.display();
            // std::cout << "window size - width: " << std::to_string(window.getSize().x) << " height: " << std::to_string(window.getSize().y) << std::endl;
            // std::cout << "window view size - width: " << std::to_string(window.getView().getSize().x) << " height: " << std::to_string(window.getView().getSize().y) << std::endl;
            // std::cout << "canvas size - width: " << std::to_string(drawCanvas->getSize().x) << " height: " << std::to_string(drawCanvas->getSize().y) << std::endl;
            // std::cout << "canvas view size - width: " << std::to_string(drawCanvas->getView().getSize().x) << " height: " << std::to_string(drawCanvas->getView().getSize().y) << std::endl;
            // std::cout << "================" << std::endl;
        }
    }
}