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

#include <Controller/Action.h>

#include <Controller/Enums.hh>
#include <Controller/ControllerEvents_fwd.h>

namespace BFG {
namespace Controller_ {

void fillWithDefaultActions(ActionMapT& actions)
{
	Event::IdT first = ID::A_FIRST_CONTROLLER_ACTION + 1;
	Event::IdT last = ID::A_LAST_CONTROLLER_ACTION;
	for (Event::IdT i=first; i < last; ++i)
	{
		ID::ControllerAction ca = static_cast<ID::ControllerAction>(i);
		actions[i] = ID::asStr(ca);
	}
}

//! \todo Send ActionMap directly as a whole.
void sendActionsToController(Event::Lane& eventLane, const ActionMapT& actions)
{
	ActionMapT::const_iterator it = actions.begin();
	for (; it != actions.end(); ++it)
	{
		ActionDefinition ad(it->first, stringToArray<128>(it->second));
		eventLane.emit(ID::CE_ADD_ACTION, ad);
	}
}

} // namespace Controller_
} // namespace BFG
