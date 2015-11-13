#ifndef SCREENMODEMANIPULATORLINUX_H
#define SCREENMODEMANIPULATORLINUX_H
#include "iscreenmodemanipulator.h"
#include <QList>
#include "screen.h"


class ScreenModeManipulatorLinux : public IScreenModeManipulator
{
private:
    void SearchAvailableScreens();
    QList<MonitorScreen> mAvailScreens;
public:
    ScreenModeManipulatorLinux();
    virtual bool SetScreenMode(unsigned int screen, ScreenMode mode);
};

#endif // SCREENMODEMANIPULATORLINUX_H
