/*    ___  _________     ____          __         
     / _ )/ __/ ___/____/ __/___ ___ _/_/___ ___ 
    / _  / _// (_ //___/ _/ / _ | _ `/ // _ | -_)
   /____/_/  \___/    /___//_//_|_, /_//_//_|__/ 
                               /___/             

This file is part of the Brute-Force Game Engine, BFG-Engine

For the latest info, see http://www.brute-force-games.com

Copyright (c) 2011 Brute-Force Games GbR

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

#include <Model/Property/Concepts/Physical.h>

#include <boost/foreach.hpp>

#include <Core/Math.h>
#include <Model/Environment.h>
#include <Physics/Physics.h>
#include <View/Enums.hh>

namespace BFG {

Physical::Physical(GameObject& owner, PluginId pid) :
Property::Concept(owner, "Physical", pid),
mFirstFullSync(true)
{
	subLane()->connect(ID::PE_FULL_SYNC, this, &Physical::onFullSync, ownerHandle());
	subLane()->connect(ID::PE_POSITION, this, &Physical::onPosition, ownerHandle());
	subLane()->connect(ID::PE_ORIENTATION, this, &Physical::onOrientation, ownerHandle());
	subLane()->connect(ID::PE_VELOCITY, this, &Physical::onVelocity, ownerHandle());
	subLane()->connect(ID::PE_ROTATION_VELOCITY, this, &Physical::onRotationVelocity, ownerHandle());
	subLane()->connect(ID::PE_TOTAL_MASS, this, &Physical::onTotalMass, ownerHandle());
	subLane()->connect(ID::PE_TOTAL_INERTIA, this, &Physical::onTotalInertia, ownerHandle());
}

Physical::~Physical()
{}

void Physical::internalSynchronize()
{
	assert(ownerHandle() != NULL_HANDLE);
	
	synchronizeView();

	if (mFirstFullSync)
	{
		subLane()->emit(ID::VE_SET_VISIBLE, true, ownerHandle());
		mFirstFullSync = false;
	}
}

void Physical::onFullSync(const Physics::FullSyncData& fsd)
{
	Location location(fsd.get<0>(), fsd.get<1>());
	setGoValue(ID::PV_Location, pluginId(), location);

	setGoValue(ID::PV_Velocity, pluginId(), fsd.get<2>());
	setGoValue(ID::PV_RelativeVelocity, pluginId(), fsd.get<3>());

	setGoValue(ID::PV_RotationVelocity, pluginId(), fsd.get<4>());
	setGoValue(ID::PV_RelativeRotationVelocity, pluginId(), fsd.get<5>());
	
	setGoValue(ID::PV_Mass, pluginId(), fsd.get<6>());
	setGoValue(ID::PV_Inertia, pluginId(), fsd.get<7>());
	
	owner().activate();
}

void Physical::onPosition(const v3& newPosition)
{
	Location go = getGoValue<Location>(ID::PV_Location, pluginId());
	go.position = newPosition;
	setGoValue(ID::PV_Location, pluginId(), go);
}

void Physical::onOrientation(const qv4& newOrientation)
{
	Location go = getGoValue<Location>(ID::PV_Location, pluginId());
	go.orientation = newOrientation;
	setGoValue(ID::PV_Location, pluginId(), go);
}

void Physical::onVelocity(const Physics::VelocityComposite& vel)
{
	setGoValue(ID::PV_Velocity, pluginId(), vel.get<0>());
	setGoValue(ID::PV_RelativeVelocity, pluginId(), vel.get<1>());
}

void Physical::onRotationVelocity(const Physics::VelocityComposite& vel)
{
	setGoValue(ID::PV_RotationVelocity, pluginId(), vel.get<0>());
	setGoValue(ID::PV_RelativeRotationVelocity, pluginId(), vel.get<1>());
}

void Physical::onTotalMass(const f32 totalMass)
{
	setGoValue(ID::PV_Mass, pluginId(), totalMass);
}

void Physical::onTotalInertia(const m3x3& inertia)
{
	setGoValue(ID::PV_Inertia, pluginId(), inertia);
}

void Physical::synchronizeView() const
{
	if (owner().docked())
		return;

	const Location& go = getGoValue<Location>(ID::PV_Location, pluginId());
	
#if defined(_DEBUG) || defined (NDEBUG)
	if (length(go.position) > 1.0e15)
	{
		std::stringstream ss;
		ss << "GameObject:" << ownerHandle()
		   << " just entered hyperspace! Position: "
		   << go.position;

		throw std::logic_error(ss.str());
	}
#endif

	subLane()->emit(ID::VE_UPDATE_POSITION, go.position, ownerHandle());
	subLane()->emit(ID::VE_UPDATE_ORIENTATION, go.orientation, ownerHandle());
}

} // namespace BFG