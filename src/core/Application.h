#pragma once
#include <QApplication>

class Application : public QApplication {
public:
    static constexpr auto Name = "AprilBrush";
    static constexpr auto Version = "0.3.0";
    static constexpr auto Url = "https://github.com/krre/aprilbrush";
    static constexpr auto CopyrightYear = "2012-2024";
    static constexpr auto BuildDate = __DATE__;
    static constexpr auto BuildTime = __TIME__;

    Application(int& argc, char* argv[]);
};
