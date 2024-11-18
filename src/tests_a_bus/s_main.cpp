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
    // CANVAS
    // auto drawBackground = tgui::Panel::create();
    // drawBackground->setAutoLayout(tgui::AutoLayout::Top);
    // drawBackground->getRenderer()->setBackgroundColor(tgui::Color::Black);
    // return drawBackground.get();
    auto drawCanvas = tgui::CanvasSFML::create();
    // canvas->setAutoLayout(tgui::AutoLayout::Top);
    // drawBackground->add(drawCanvas);
    gui.add(drawCanvas);
    // ==================
    tgui::Color baseColor(225,225,225);
    // Create an SFML RenderTexture for the canvas
    Settings::canvasTexture.create(100, 100); // Set appropriate size
    Settings::canvasTexture.clear(sf::Color::White);
    sf::Sprite canvasSprite(Settings::canvasTexture.getTexture());  // To display on the panel
    sf::View canvasView = drawCanvas->getView();
    sf::View windowView = window.getView();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized) {
                // canvasView = sf::View({0,0}, {event.size.width, event.size.height});
                // canvasView = drawCanvas->getView();
                // windowView = window.getView();
                // windowView.setSize(event.size.width, event.size.height);
                // canvasView.setViewport({0.f,0.f,1.f,1.f});
                // canvasView.setSize(event.size.width, event.size.height);
                // window.setSize({event.size.width, event.size.height});
                // drawCanvas->setSize(event.size.width, event.size.height);
                // windowView.setViewport({0.f,0.f,1.f,1.f});
                // canvasView.reset({0.f,0.f,event.size.width, event.size.height});
                // windowView.reset({0.f,0.f,event.size.width, event.size.height});
                // auto wView = window.getView();
                // auto gView = gui.getView();
                // gui.setV
                // wView.setSize(event.size.width, event.size.height);
                // window.setView(wView);
                // sf::FloatRect visibleArea(0, 0, 1000, 650);
                // window.setView(sf::View(visibleArea));
                // window.setSize({1000, 650});
                // auto newView = drawCanvas->getView();
                // ######
                // drawCanvas->setView(newView);
                // canvasView.setViewport(sf::FloatRect(0.f,0.f,1.f,1.f));
                // canvasView.reset({0.f,0.f,1000.f,1000.f});
            }
            window.clear(baseColor);
            drawCanvas->clear();
            // window.setView(windowView);
            // drawCanvas->setView(canvasView);
            drawCanvas->draw(canvasSprite);
            drawCanvas->display();
            gui.draw();
            window.display();
            std::cout << "gui window size - width: " << std::to_string(gui.getWindow()->getSize().x) << " height: " << std::to_string(gui.getWindow()->getSize().y) << std::endl;
            std::cout << "window size - width: " << std::to_string(window.getSize().x) << " height: " << std::to_string(window.getSize().y) << std::endl;
            std::cout << "window view size - width: " << std::to_string(window.getView().getSize().x) << " height: " << std::to_string(window.getView().getSize().y) << std::endl;
            std::cout << "canvas size - width: " << std::to_string(drawCanvas->getSize().x) << " height: " << std::to_string(drawCanvas->getSize().y) << std::endl;
            std::cout << "canvas view size - width: " << std::to_string(drawCanvas->getView().getSize().x) << " height: " << std::to_string(drawCanvas->getView().getSize().y) << std::endl;
            std::cout << "================" << std::endl;
        }
    }
}
