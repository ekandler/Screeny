#include "screenmodemanipulatorfactory.h"
#include <iostream>
#include "screenmodemanipulatorlinux.h"
#include <QtGlobal>

ScreenModeManipulatorFactory::ScreenModeManipulatorFactory()
{
#ifdef _WIN32
    mMode = Windows;
#elif defined __unix__
    mMode = LinuxXAPI; // FIXME other graphic servers
#elif defined __APPLE__
    mMode = Mac;
#endif
}

IScreenModeManipulator *ScreenModeManipulatorFactory::CreateModeManipulator()
{
    switch (mMode) {
    case LinuxXAPI:
        return new ScreenModeManipulatorLinux();
        break;
    default:
        qFatal("Unsupported operating system or unable to detect.");
    }
}

