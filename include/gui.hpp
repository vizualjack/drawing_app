#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <utility>

void initMenu(tgui::Gui& gui);
void initToolbar(tgui::Gui& gui);
std::pair<tgui::CanvasSFML*,tgui::Panel*> initDrawCanvas(tgui::Gui& gui);