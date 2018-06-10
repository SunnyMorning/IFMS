/*
 * Copyright (C) 2014 Johan Simonsson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef  __SYSFSGPIO_H
#define  __SYSFSGPIO_H

#include <QString>

#include "gpio_ifms1000.h"

static const QString GPIO_DIRECTION_INPUT("in");   ///< sysfs gpio config direction string, in
static const QString GPIO_DIRECTION_OUTPUT("out"); ///< sysfs gpio config direction string, out

#define     GPIO_LEVEL_LOW  0
#define     GPIO_LEVEL_HIGH 1

class SysfsGPIO
{
    private:
    public:
        bool configureGPIO(int gpionr, QString direction);
        int  readGPIO(int gpionr);
        bool writeGPIO(int gpionr, int value);
};

#endif // __SYSFSGPIO_H
