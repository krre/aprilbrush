/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre@mail.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef WACOM_H
#define WACOM_H

#include <QObject>

class Wacom : public QObject
{
public:
    Wacom();
    ~Wacom();
    qreal pressure();

private:
    void wacomInit();

    int pressureRange;
    unsigned int wacomId;
};

#endif // WACOM_H
