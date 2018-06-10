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

#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QThread>

#include "SysfsGPIO.h"

bool SysfsGPIO::configureGPIO(int gpionr, QString direction)
{
    //First check that the export file is there,
    //if it is missing then the sysfs gpio "module" is not loaded.
    QFile gpioExport("/sys/class/gpio/export");
    if(!gpioExport.exists())
    {
        qDebug() << "missing file: /sys/class/gpio/export";
        return false;
    }

    //If value does not exist then export
    QFile gpioDirection(QString("/sys/class/gpio/gpio%1/direction").arg(gpionr));
    if(!gpioDirection.exists())
    {
        if (!gpioExport.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << gpioExport.fileName();
            return false;
        }

        QTextStream out(&gpioExport);
        out << gpionr << "\n";
        gpioExport.close();
        QThread::msleep(200);
    }

    {
        if (!gpioDirection.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << gpioDirection.fileName();
            return false;
        }

        QTextStream out(&gpioDirection);
        out << direction << "\n";
        gpioDirection.close();
        QThread::msleep(200);
    }

    return true;
}

int  SysfsGPIO::readGPIO(int gpionr)
{
    QFile gpioFile;
    int value = -1;
    gpioFile.setFileName(QString("/sys/class/gpio/gpio%1/value").arg(gpionr));

    if (!gpioFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "FAILURE can't open gpio file gpioPath:" << gpioFile.fileName();
    }

    value = gpioFile.readAll().trimmed().toInt();
    return value;
}

bool SysfsGPIO::writeGPIO(int gpionr, int value)
{
    //Open and write 1/0 to value file
    QFile gpioFile(QString("/sys/class/gpio/gpio%1/value").arg(gpionr));

    if (!gpioFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "FAILURE can't open gpio file gpioPath:" << gpioFile.fileName();
        return false;
    }

    QTextStream out(&gpioFile);
    out << value << "\n";
    gpioFile.close();

    return true;
}

