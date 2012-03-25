/*    ___  _________     ____          __         
     / _ )/ __/ ___/____/ __/___ ___ _/_/___ ___ 
    / _  / _// (_ //___/ _/ / _ | _ `/ // _ | -_)
   /____/_/  \___/    /___//_//_|_, /_//_//_|__/ 
                               /___/             

This file is part of the Brute-Force Game Engine, BFG-Engine

For the latest info, see http://www.brute-force-games.com

Copyright (c) 2012 Brute-Force Games GbR

The BFG-Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The BFG-Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the BFG-Engine. If not, see <http://www.gnu.org/licenses/>.
*/

#include <Audio/OpenALListener.h>
#include <Audio/Main.h>
#include <Audio/Enums.hh>

namespace BFG {
namespace Audio {

OpenALListener::OpenALListener()
{
	AudioMain::eventLoop()->connect(ID::AE_MASTER_GAIN, this, &OpenALListener::eventHandler);
	AudioMain::eventLoop()->connect(ID::AE_POSITION_PLAYER, this, &OpenALListener::eventHandler);
	AudioMain::eventLoop()->connect(ID::AE_ORIENTATION_PLAYER, this, &OpenALListener::eventHandler);
	AudioMain::eventLoop()->connect(ID::AE_VELOCITY_PLAYER, this, &OpenALListener::eventHandler);
}

OpenALListener::~OpenALListener()
{
	AudioMain::eventLoop()->disconnect(ID::AE_MASTER_GAIN);
	AudioMain::eventLoop()->connect(ID::AE_POSITION_PLAYER);
	AudioMain::eventLoop()->connect(ID::AE_ORIENTATION_PLAYER);
	AudioMain::eventLoop()->connect(ID::AE_VELOCITY_PLAYER);

	AudioMain::eventLoop()->setExitFlag(true);
	AudioMain::eventLoop()->doLoop();
}

void OpenALListener::eventHandler(AudioEvent* AE)	
{
	switch (AE->getId())
	{
	case ID::AE_MASTER_GAIN:
		onEventMasterGain(AE->getData());
		break;
	case ID::AE_POSITION_PLAYER:
		onEventPositionPlayer(AE->getData());
		break;
	case ID::AE_ORIENTATION_PLAYER:
		onOrientationPlayer(AE->getData());
		break;
	case ID::AE_VELOCITY_PLAYER:
		onVelocityPlayer(AE->getData());
		break;
	default:
		throw std::logic_error("Unhandled event!");
	}
}

void Audio::onVelocityPlayer(const AudioPayloadT& payload)
{
	v3 velocity = boost::get<v3>(payload);
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}

void Audio::onOrientationPlayer(const AudioPayloadT& payload)
{
	v3 orientation = boost::get<v3>(payload);
	alListener3f(AL_ORIENTATION, orientation.x, orientation.y, orientation.z);
}

void Audio::onEventMasterGain(const AudioPayloadT& payload)
{
	ALfloat gain = static_cast<ALfloat>(boost::get<float>(payload));
	alListenerf(AL_GAIN, gain);
}

void Audio::onEventPositionPlayer(const AudioPayloadT& payload)
{
	v3 position = boost::get<v3>(payload);
	alListener3f(AL_POSITION, position.x, position.y, position.z);
}

} // namespace Audio
} // namespace BFG
