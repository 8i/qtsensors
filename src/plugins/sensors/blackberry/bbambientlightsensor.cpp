/****************************************************************************
**
** Copyright (C) 2012 Research In Motion
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "bbambientlightsensor.h"

BbAmbientLightSensor::BbAmbientLightSensor(QSensor *sensor)
    : BbSensorBackend<QAmbientLightReading>(devicePath(), SENSOR_TYPE_LIGHT, sensor)
{
    setDescription(QLatin1String("Ambient light brightness"));
}

bool BbAmbientLightSensor::updateReadingFromEvent(const sensor_event_t &event, QAmbientLightReading *reading)
{
    const int lightLevelLux = event.light_s.illuminance;
    if (lightLevelLux < 10)
        reading->setLightLevel(QAmbientLightReading::Dark);
    else if (lightLevelLux < 80)
        reading->setLightLevel(QAmbientLightReading::Twilight);
    else if (lightLevelLux < 400)
        reading->setLightLevel(QAmbientLightReading::Light);
    else if (lightLevelLux < 2500)
        reading->setLightLevel(QAmbientLightReading::Bright);
    else
        reading->setLightLevel(QAmbientLightReading::Sunny);

    return true;
}

QString BbAmbientLightSensor::devicePath()
{
    return QLatin1String("/dev/sensor/light");
}