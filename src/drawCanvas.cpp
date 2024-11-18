#include "gui.hpp"


std::pair<tgui::CanvasSFML*,tgui::Panel*> initDrawCanvas(tgui::Gui& gui) {
    auto drawBackground = tgui::Panel::create();
    drawBackground->setAutoLayout(tgui::AutoLayout::Top);
    drawBackground->getRenderer()->setBackgroundColor(tgui::Color::Black);
    gui.add(drawBackground);
    // return drawBackground.get();
    auto canvas = tgui::CanvasSFML::create();
    // canvas->setAutoLayout(tgui::AutoLayout::Top);
    drawBackground->add(canvas);
    return std::make_pair(canvas.get(), drawBackground.get());
}