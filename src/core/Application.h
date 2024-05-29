#pragma once
#include "src/config.h"
#include <QApplication>

class Application : public QApplication {
public:
    static constexpr auto Name = "AprilBrush";
    static constexpr auto Version = PROJECT_VERSION;
    static constexpr auto Url = "https://github.com/krre/aprilbrush";
    static constexpr auto Years = "2012-2024";
    static constexpr auto BuildDate = __DATE__;
    static constexpr auto BuildTime = __TIME__;

    Application(int& argc, char* argv[]);

private:
    void installTranslators();
};
