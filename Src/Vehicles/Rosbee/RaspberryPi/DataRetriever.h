/**
*               __
*    _________ / /_  ____  ________  ____________  _____
*   /___/ __ \/ __ \/ __ \/ ___/ _ \/ ___/ ___/ / / / _ \
*  / / / /_/ / /_/ / /_/ / /  /  __(__  ) /__/ /_/ /  __/
* /_/  \____/_.___/\____/_/   \___/____/\___/\__,_/\___/
*
*
* @file DataRetriever.h
* @date Created: 22-6-2015
*
* @author Kjeld Perquin
* @author Edwin Koek - Added Compass and IMU
* @version 2.0
*
* @section LICENSE
* License: newBSD
*
* Copyright � 2015, HU University of Applied Sciences Utrecht.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
* - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
* - Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
* GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef _DATARETRIEVER_H
#define _DATARETRIEVER_H
#include "SerialLinux.h"
#include "roborescueV1/mavlink.h"
#include "Compass.h"
#include "IMU.h"
/**
 * @brief The DataRetriever class
 */
class DataRetriever{
public:
    /**
     * @brief DataRetriever
     * @param deviceName
     * @param baudrate
     * @param compass
     * @param imu
     */
    DataRetriever(const char* deviceName, unsigned int baudrate, Compass& compass, IMU& imu);
    /**
     * @brief operator ()
     */
    void operator()();
    /**
     * @brief getIMUValues
     * @return
     */
    __mavlink_scaled_imu2_t getIMUValues();
    /**
     * @brief getAttitudeValues
     * @return
     */
    __mavlink_attitude_t getAttitudeValues();
    /**
     * @brief getCompassValues
     * @return
     */
    __mavlink_global_position_int_t getCompassValues();
    /**
     * @brief newIMUAvailable
     * @return
     */
    bool newIMUAvailable();
    /**
     * @brief newAttitudeAvailable
     * @return
     */
    bool newAttitudeAvailable();
    /**
     * @brief newCompassAvailable
     * @return
     */
    bool newCompassAvailable();

private:
    SerialLinux serialPort;
    //! Mavlink packets
    __mavlink_scaled_imu2_t IMU2Values;
    __mavlink_attitude_t attitude;
    __mavlink_global_position_int_t compassValues;
    //! Compass and IMU classes that contain the measurement data
    Compass& compass;
    IMU& imu;
    //! Unpacked mavlink
    bool newCompass;
    bool newAttitude;
    bool newIMU;

    /**
     * @brief readMAVLinkMessage
     * @param message
     * @return
     */
    bool readMAVLinkMessage(mavlink_message_t& message);

};
#endif