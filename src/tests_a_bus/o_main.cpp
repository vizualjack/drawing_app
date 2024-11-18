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
    initMenu(gui);
    initToolbar(gui);
    auto [drawCanvas, drawBackground] = initDrawCanvas(gui);
    drawCanvas->setAutoLayoutUpdateEnabled(false);
    // gui.mainLoop(); // See below for how to use your own main loop
    tgui::Color baseColor(225,225,225);
    // Create an SFML RenderTexture for the canvas
    Settings::canvasTexture.create(100, 100); // Set appropriate size
    Settings::canvasTexture.clear(sf::Color::White);
    sf::Sprite canvasSprite(Settings::canvasTexture.getTexture());  // To display on the panel
    // drawCanvas->draw(canvasSprite);
    bool drawing = false;
    bool panning = false;
    sf::Vector2i lastMousePosition;
    float zoomLevel = 1.f;
    sf::View canvasView = drawCanvas->getView();
    sf::View windowView = window.getView();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed) window.close();
            else if(event.type == sf::Event::MouseMoved && drawing) {
                tgui::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
                // std::cout << "mousePos x" << std::to_string(mousePos.x) << ", y" << std::to_string(mousePos.y) << std::endl;
                mousePos.y -= drawCanvas->getAbsolutePosition().y;
                // std::cout << "mousePos x" << std::to_string(mousePos.x) << ", y" << std::to_string(mousePos.y) << std::endl;
                // std::cout << "window size - width: " << std::to_string(window.getSize().x) << ", height: " << std::to_string(window.getSize().y) << std::endl;
                // std::cout << "window view size - width: " << std::to_string(window.getView().getSize().x) << ", height: " << std::to_string(window.getView().getSize().y) << std::endl;
                // std::cout << "canvas view size - width: " << std::to_string(drawCanvas->getView().getSize().x) << ", height: " << std::to_string(drawCanvas->getView().getSize().y) << std::endl;
                // auto v = drawCanvas->getView();
                // v.setSize(window.getSize().x, window.getSize().y);
                // v.setViewport({0,0,1,1});
                // auto drawCanvasView = drawCanvas->getView();
                // drawCanvasView.setSize(drawCanvas->getSize().x, drawCanvas->getSize().y);
                auto mousePosInView = window.mapPixelToCoords(mousePos, window.getView());
                // drawCanvas
                // mousePosInView.y -= (drawCanvas->getAbsolutePosition().y*zoomLevel);
                // std::cout << "mousePos in view x" << std::to_string(mousePosInView.x) << ", y" << std::to_string(mousePosInView.y) << std::endl;
                if(drawCanvas->isMouseOnWidget(tgui::Vector2f(mousePos.x, mousePos.y))) {
                    // std::cout << "jkhjkh" << std::endl;
                    // tgui::Vector2f posOnDrawCanvas(mousePos.x - drawCanvasPos.x, mousePos.y - drawCanvasPos.y);
                    tgui::Vector2f posOnDrawCanvas(mousePosInView.x, mousePosInView.y);
                    // std::cout << "Drawing at pos x" << std::to_string(mousePos.x) << ", y" << std::to_string(mousePos.y) << std::endl;
                    // std::cout << "Pos on draw canvas x" << std::to_string(posOnDrawCanvas.x) << ", y" << std::to_string(posOnDrawCanvas.y) << std::endl;
                    // canvasSprite.setPosition()
                    // std::cout << "View center pos x" << std::to_string(canvasView.getCenter().x) << ", y" << std::to_string(canvasView.getCenter().y) << std::endl;
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
                // std::cout << "Move view with offset" << std::to_string(offset.x) << ", y" << std::to_string(offset.y) << std::endl;
                // drawCanvas->set
                // canvasView = drawCanvas->getView();
                canvasView = drawCanvas->getView();
                canvasView.move(offset);
                drawCanvas->setView(canvasView);
                lastMousePosition = mousePosition;
            }
            else if (event.type == sf::Event::MouseWheelScrolled) {
                tgui::Vector2f mousePos(event.mouseWheelScroll.x, event.mouseWheelScroll.y);
                canvasView = drawCanvas->getView();
                if(drawCanvas->isMouseOnWidget(mousePos)) {
                    if (event.mouseWheelScroll.delta > 0) {
                        canvasView.zoom(0.9f);
                        zoomLevel *= 0.9f;
                    }
                    else {
                        canvasView.zoom(1.1f);
                        zoomLevel *= 1.1f;
                    }
                    drawCanvas->setView(canvasView);
                    std::cout << "New zoom level: " << std::to_string(zoomLevel) << std::endl;
                }
            }
            else if (event.type == sf::Event::Resized) {
                auto wView = window.getView();
                wView.setSize(event.size.width, event.size.height);
                window.setView(wView);
                drawCanvas->setSize({event.size.width, event.size.height});
                // canvasView = drawCanvas->getView();
                // std::cout << "current zoom level: " << std::to_string(zoomLevel) << std::endl;
                // std::cout << "current canvas view size - width: " << std::to_string(canvasView.getSize().x) << ", height: " << std::to_string(canvasView.getSize().y) << std::endl;
                // std::cout << "new window size -  width: " << std::to_string(event.size.width) << ", height: " << std::to_string(event.size.height) << std::endl;
                // canvasView.setSize(event.size.width * zoomLevel, event.size.height * zoomLevel);
                // canvasView.reset({0,0,event.size.width, event.size.height});
                // canvasView.setSize(event.size.width, event.size.height);
                // canvasView.
                // canvasView.setViewport(sf::FloatRect(0.f,0.f,1.f,1.f));
                // drawCanvas->setSize({event.size.width, event.size.height});
                // drawCanvas->clear();
                // drawCanvas->setHeight(event.size.height);
                // drawCanvas->setWidth(event.size.width);
                // auto newView = drawCanvas->getView();
                // auto defView = drawCanvas->getDefaultView();
                // auto size = drawCanvas->getSize();
                // newView.setSize(event.size.width, event.size.height);
                // std::cout << "drawCanvas size - width: " << std::to_string(size.x) << ", height:" << std::to_string(size.y) << std::endl;
                // std::cout << "drawCanvas view size - width: " << std::to_string(newView.getSize().x) << ", height:" << std::to_string(newView.getSize().y) << std::endl;
                // std::cout << "drawCanvas view viewport - top: " << std::to_string(newView.getViewport().top) << ", left: " << std::to_string(newView.getViewport().left) << ", width: " << std::to_string(newView.getViewport().width) << ", height: " << std::to_string(newView.getViewport().height) << std::endl;
                // std::cout << "drawCanvas defView size - width: " << std::to_string(defView.getSize().x) << ", height:" << std::to_string(defView.getSize().y) << std::endl;
                // std::cout << "drawCanvas defView viewport - top: " << std::to_string(defView.getViewport().top) << ", left: " << std::to_string(defView.getViewport().left) << ", width: " << std::to_string(defView.getViewport().width) << ", height: " << std::to_string(defView.getViewport().height) << std::endl;
                // drawCanvas->setView(newView);
                // newView.setSize(drawCanvas->getSize());
                // drawCanvas->setView(newView);
                // newView.setCenter(canvasView.getCenter());
                // newView.zoom(zoomLevel);
                // canvasView = newView;
                // std::cout << "current drawBackground size - width: " << std::to_string(drawBackground->getSize().x) << ", height: " << std::to_string(drawBackground->getSize().y) << std::endl;
                // std::cout << "current drawBackground full size - width: " << std::to_string(drawBackground->getFullSize().x) << ", height: " << std::to_string(drawBackground->getFullSize().y) << std::endl;
                // std::cout << "current drawCanvas size - width: " << std::to_string(drawCanvas->getSize().x) << ", height: " << std::to_string(drawCanvas->getSize().y) << std::endl;
                // std::cout << "current drawCanvas pos - x: " << std::to_string(drawCanvas->getAbsolutePosition().x) << ", y: " << std::to_string(drawCanvas->getAbsolutePosition().y) << std::endl;
                // std::cout << "new canvas view size - width: " << std::to_string(canvasView.getSize().x) << ", height: " << std::to_string(canvasView.getSize().y) << std::endl;
                // std::cout << "current window size - width: " << std::to_string(window.getSize().x) << ", height: " << std::to_string(window.getSize().y) << std::endl;
                // std::cout << "event size view - width: " << std::to_string(event.size.width) << ", height: " << std::to_string(event.size.height) << std::endl;
                // std::cout << "gui window view - width: " << std::to_string(gui.getWindow()->getSize().x) << ", height: " << std::to_string(gui.getWindow()->getSize().y) << std::endl;
                // canvasView.setSize(event.size.width, event.size.height);
                // drawCanvas->resizeWithAnimation({event.size.width, event.size.height}, 0);
                // auto windowView = window.getView();
                // windowView.setSize(event.size.width, event.size.height);
                // window.setView(windowView);
                // window.setSize({event.size.width, event.size.height});
                // drawCanvas->setSize(event.size.width, event.size.height);
                // auto canvasView = drawCanvas->getView();
                // canvasView.setSize(event.size.width, event.size.height);
                // drawCanvas->setView(canvasView);
                // canvasView = drawCanvas->getView();
                // windowView = window.getView();
                // // drawCanvas->resizeWithAnimation({event.size.width, event.size.height}, 0);
                // window.setSize({event.size.width, event.size.height});
                // drawCanvas->setSize(event.size.width, event.size.height);
                // canvasView.setSize(event.size.width, event.size.height);
                // windowView.setSize(event.size.width, event.size.height);
                // canvasView.reset({0.f, 0.f, event.size.width, event.size.height});
                // windowView.reset({0.f, 0.f, event.size.width, event.size.height});
            }
            window.clear(baseColor);
            drawCanvas->clear();
            drawCanvas->draw(canvasSprite);
            drawCanvas->display();
            gui.draw();
            window.display();
            std::cout << "window size - width: " << std::to_string(window.getSize().x) << " height: " << std::to_string(window.getSize().y) << std::endl;
            std::cout << "window view size - width: " << std::to_string(window.getView().getSize().x) << " height: " << std::to_string(window.getView().getSize().y) << std::endl;
            std::cout << "canvas size - width: " << std::to_string(drawCanvas->getSize().x) << " height: " << std::to_string(drawCanvas->getSize().y) << std::endl;
            std::cout << "canvas view size - width: " << std::to_string(drawCanvas->getView().getSize().x) << " height: " << std::to_string(drawCanvas->getView().getSize().y) << std::endl;
            std::cout << "================" << std::endl;
        }
        // OOOLD
        // window.clear(baseColor);
        // // window.setView(canvasView);
        // drawCanvas->clear();
        // drawCanvas->draw(canvasSprite);
        // drawCanvas->display();
        // gui.draw();
        // window.display();
    }
}


//////////// OLD STUFF / MAYBE USEFUL STUFF
// sf::Clock clock;
// sf::sleep(sf::milliseconds(10));

// sf::Mutex mutex;
// sf::Lock lock(mutex); // mutex.lock()

// sf::Thread thread(&funcToRunInThread);
// sf::Thread thread(&func, 5);
// sf::Time elapsed = clock.restart();

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
// {
//     sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!!!");
//     tgui::Gui gui{window};
//     gui.mainLoop(); // See below for how to use your own main loop
//     // sf::CircleShape shape(100.f);
//     // shape.setFillColor(sf::Color::Red);

//     // while (window.isOpen())
//     // {
//     //     sf::Event event;
//     //     while (window.pollEvent(event))
//     //     {
//     //         if (event.type == sf::Event::Closed)
//     //             window.close();
//     //     }

//     //     window.clear();
//     //     window.draw(shape);
//     //     window.display();
//     // }

//     return 0;l
// }
