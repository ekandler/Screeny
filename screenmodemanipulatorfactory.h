#ifndef SCREENMODEMANIPULATORFACTORY_H
#define SCREENMODEMANIPULATORFACTORY_H
#include "iscreenmodemanipulator.h"


class ScreenModeManipulatorFactory
{
private:
    enum ManipulatorMode {UDEF=-1, LinuxXAPI = 0, Windows = 1, Mac = 2};
    ManipulatorMode mMode;
public:
    ScreenModeManipulatorFactory();
    IScreenModeManipulator * CreateModeManipulator();
};

#endif // SCREENMODEMANIPULATORFACTORY_H
