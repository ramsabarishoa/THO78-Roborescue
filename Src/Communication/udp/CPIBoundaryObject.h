#ifndef __CPIBOUNDARYOBJECT__
#define __CPIBOUNDARYOBJECT__


#include <cstdint>
#include "Socket.h"
#include <iostream>
#include <thread>



/**
*               __
*    _________ / /_  ____  ________  ____________  _____
*   /___/ __ \/ __ \/ __ \/ ___/ _ \/ ___/ ___/ / / / _ \
*  / / / /_/ / /_/ / /_/ / /  /  __(__  ) /__/ /_/ /  __/
* /_/  \____/_.___/\____/_/   \___/____/\___/\__,_/\___/
*
*
* @file CPIBoundaryObject
* @date Created: 27-5-2015
*
* @author Rene Keijzer
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


/// \class CPIBoundaryObject
/// \brief A boundary object for all the vehicles in the project, an id is used as identification and a device has socket to communicate over
/// \brief CPiBoundary object is always a thread this thread should be implemented by the subclasses

class CPIBoundaryObject
{
public:

	CPIBoundaryObject(){ 
		
	}
	~CPIBoundaryObject(){}
protected:

	/// \brief Starts implemented robot thread
	void start(){ robotThread = std::thread(&CPIBoundaryObject::run, this); }
	/// \brief Pure virtual getid, this method should return the identifier of boundary object
	/// \return Id of the boundary object
	virtual int getId() = 0;

	/// \brief Robotlogic method this method should be overwritten
	/// \return void
	virtual void run(){}
private:
	std::thread robotThread;
	};
#endif