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

#include <View/Fps.h>

#include <OgreRoot.h>
#include <OgreRenderWindow.h>

#include <View/MyGuiBinding.h>

namespace BFG {
namespace View {

Fps::Fps() :
HudElement("FPS.layout", "FPS")
{
}

Fps::~Fps()
{
}

void Fps::internalUpdate(f32 /*time*/)
{
	Ogre::RenderWindow* rw = Ogre::Root::getSingleton().getAutoCreatedWindow();

	const Ogre::RenderTarget::FrameStats& stats = rw->getStatistics();

	TextBound<float> lastFPS("FPSValue");
	TextBound<float> avgFPS("AvFPSValue");
	TextBound<float> worstFPS("WorstFPSValue");
	TextBound<float> bestFPS("BestFPSValue");
	TextBound<size_t> triangleCount("TriCountValue");
	TextBound<size_t> batchCount("BatchCountValue");

	lastFPS = stats.lastFPS;
	avgFPS = stats.avgFPS;
	worstFPS = stats.worstFPS;
	bestFPS = stats.bestFPS;
	triangleCount = stats.triangleCount;
	batchCount = stats.batchCount;
}


} // namespace View
} // namespace BFG
