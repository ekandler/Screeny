#include "screen.h"

MonitorScreen::MonitorScreen(unsigned int ID, QString name, QVector<ScreenMode> AvailModes)
{
    mID = ID;
    mName = name;
    mAvailModes = AvailModes;
}

