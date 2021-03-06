/**
*               __
*    _________ / /_  ____  ________  ____________  _____
*   /___/ __ \/ __ \/ __ \/ ___/ _ \/ ___/ ___/ / / / _ \
*  / / / /_/ / /_/ / /_/ / /  /  __(__  ) /__/ /_/ /  __/
* /_/  \____/_.___/\____/_/   \___/____/\___/\__,_/\___/
*
*
* @file WayPoint.h
* @date Created: 4/28/2015
* @version 1.0
*
* @author Coen Andriessen
* @author Mathijs Arends
* @author Jacob Visser
*
* @section LICENSE
* License: newBSD
*
* Copyright © 2015, HU University of Applied Sciences Utrecht.
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

#ifndef WAYPOINT_H
#define WAYPOINT_H

class WayPoint
{
public:
	/**
	* @fn	WayPoint(int x, int y);
	*
	* @brief	Constructor of the class WayPoint.
	*
	* @param	int x
	* @param	int y
	*/
    WayPoint(int x, int y);
	/**
	* @fn	~WayPoint();
	*
	* @brief	Destructor of the class WayPoint.
	*/
    ~WayPoint();
	/**
	* @fn	bool operator==(const WayPoint &other) const;
	*
	* @brief	Operator for class WayPoint.
	*
	* @return	bool
	*/
	bool operator==(const WayPoint &other) const {
		if (other.x == this->x &&other.y == this->y){ return true; }
		else return false;
	}
	/**
	* @brief	int x variable. Variable to store x location of WayPoint.
	*/
	int x;
	/**
	* @brief	int y variable. Variable to store y location of WayPoint.
	*/
    int y;
};

#endif // WAYPOINT_H
