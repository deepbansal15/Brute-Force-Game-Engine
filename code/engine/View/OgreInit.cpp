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

#ifdef _MSC_VER
  // Many many warnings coming from Ogre...
  #pragma warning (push)
  #pragma warning (once: 4251)
  #pragma warning (once: 4244)
#endif

#include <View/OgreInit.h>

#ifdef _WIN32
#include <windows.h> 
#endif //_WIN32

#include <boost/filesystem.hpp>
#include <string>

#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <Base/Logger.h>

#include <Core/Enums.hh>
#include <Core/GameHandle.h>
#include <Core/Path.h>

#include <View/Camera.h>
#include <View/Console.h>
#include <View/Defs.h>
#include <View/Enums.hh>
#include <View/Fps.h>
#include <View/LoadMesh.h>

namespace BFG {
namespace View {

OgreInit::OgreInit(Event::Lane& lane, const std::string& windowTitle) :
mLane(lane),
mSubLane(lane.createSubLane()),
mShutdown(false),
mWindowTitle(windowTitle),
mSceneMgr(NULL)
{
	mSubLane->connectV(ID::VE_SHUTDOWN, this, &OgreInit::onShutdown);
	mSubLane->connect(ID::VE_DEBUG_FPS, this, &OgreInit::onDebugFps);
	mSubLane->connectV(ID::VE_SCREENSHOT, this, &OgreInit::onScreenShot);
	mSubLane->connect(ID::VE_CONSOLE, this, &OgreInit::onConsole);
	mSubLane->connect(ID::VE_REQUEST_MESH, this, &OgreInit::onRequestMesh);
	
	initOgre();
	initMyGui();

	mLane.connectLoop(this, &OgreInit::onTick);
}

OgreInit::~OgreInit()
{
	mSubLane.reset();

	mConsole.reset();
	mFps.reset();
	mMainCamera.reset();

	if (mGui)
	{
		mGui->shutdown();
		mGui.reset();
	}

	if (mPlatform)
	{
		mPlatform->shutdown();
		mPlatform.reset();
	}

	if (mRoot)
	{
		mRoot->shutdown();
		mRoot.reset();
	}
}

void OgreInit::onTick(Event::TickData)
{
	if (! doRenderTick() || mShutdown)
	{
		mSubLane->emit(ID::EA_FINISH, Event::Void());
	}
}

bool OgreInit::doRenderTick()
{
	Ogre::WindowEventUtilities::messagePump();

	return mRoot->renderOneFrame();
}

void OgreInit::initOgre()
{
	initializeRoot();
	
	loadResources();

	createSceneManager();
	
	createMainCamera();
}

void OgreInit::initializeRoot()
{
	using namespace Ogre;

	infolog << "OGRE: Initializing Ogre Root ...";

#ifdef _WIN32
	const std::string pluginCfg = "plugins-win.cfg";
#else
	const std::string pluginCfg = "plugins-linux.cfg";
#endif

	Path p;
	
	mRoot.reset
	(
		new Root(pluginCfg, "ogre.cfg", p.Get(ID::P_LOGS) + "ogre.log")
	);

	if(mRoot->restoreConfig() || mRoot->showConfigDialog())
	{
		mRoot->initialise(true, mWindowTitle);
	}
	else
		throw std::runtime_error("OgreInit: failed to restore config dialog!");

	infolog << "OGRE: Initializing Ogre Root done.";
}

void OgreInit::loadResources()
{
	using namespace Ogre;
	
	infolog << "OGRE: Add ResourcesLocations ...";

#ifdef _WIN32
	const std::string resourcesCfg = "resources-win.cfg";
#else
	const std::string resourcesCfg = "resources-linux.cfg";
#endif
	ConfigFile cf;
	std::string secName, typeName, archName;

	infolog << "OGRE: Load resource.cfg ...";

	try
	{
		cf.load(resourcesCfg);
	}
	catch (Ogre::Exception& e)
	{
		std::stringstream ss;
		ss << "OgreInit: failed to load \""
		   << resourcesCfg 
		   << "\". OgreException: "
		   << e.getFullDescription();
		throw std::runtime_error(ss.str());
	}

	infolog << "OGRE: Load resource.cfg done.";

	infolog << "OGRE: Reading Sections of resource.cfg ...";

	ConfigFile::SectionIterator seci = cf.getSectionIterator();

	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		ConfigFile::SettingsMultiMap* settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			ResourceGroupManager::getSingleton().addResourceLocation
			(
				archName,
				typeName,
				secName
			);
		}
	}
	infolog << "OGRE: Reading Sections of resource.cfg done.";

	infolog << "OGRE: Add ResourcesLocations done.";


	infolog << "OGRE: Init Resources ...";

	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	infolog << "OGRE: Init Resources done.";
}

void OgreInit::createSceneManager()
{
	infolog << "OGRE: Create SceneManager ...";

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_EXTERIOR_REAL_FAR, BFG_SCENEMANAGER);

	infolog << "OGRE: Create SceneManager done.";
}

void OgreInit::createMainCamera()
{
	infolog << "OGRE: Create main camera ...";

	GameHandle camHandle = generateHandle();
	
	mMainCamera.reset(new Camera(mLane, camHandle, NULL, mRoot->getAutoCreatedWindow()));

	infolog << "OGRE: Create main camera done.";
}

void OgreInit::initMyGui()
{
	infolog << "MyGui: Initialize MyGui ...";
	Path p;
	
	const std::string log = p.Get(ID::P_LOGS) + "MyGUI.log";
	
	mPlatform.reset(new MyGUI::OgrePlatform);
	mPlatform->initialise
	(
		mRoot->getAutoCreatedWindow(),
		mSceneMgr,
		"General",
		log
	);
	mPlatform->getRenderManagerPtr()->setActiveViewport(0); 
	mGui.reset(new MyGUI::Gui);
	mGui->initialise("guiBase.xml");
	
	infolog << "MyGui: Initialize MyGui done.";
}

void OgreInit::onDebugFps(bool enable)
{
	if (enable)
		mFps.reset(new Fps);
	else
		mFps.reset();
}

void OgreInit::onConsole(bool enable)
{
	if (!mConsole)
		mConsole.reset(new Console(mLane, mRoot));

	mConsole->toggleVisible(enable);
}

void OgreInit::onShutdown()
{
	mShutdown = true;
}

void OgreInit::onScreenShot()
{
	Path p;
	const std::string path = p.Get(ID::P_SCREENSHOTS);

	size_t index = 0;
	std::ostringstream ss;
	do 
	{
		ss.str("");
		ss << path << "/Screenshot_" << index << ".jpg";
		++index;
	} while (boost::filesystem::exists(ss.str()));

	mRoot->getAutoCreatedWindow()->writeContentsToFile(ss.str());
}

void OgreInit::onRequestMesh(const std::string& meshName, GameHandle sender)
{
	const Mesh mesh = loadMesh(meshName);
	NamedMesh namedMesh(meshName, mesh);
	dbglog << "Processing mesh request \"" << meshName << "\" for #" << sender;
	mLane.emit(ID::VE_DELIVER_MESH, namedMesh);
}

#ifdef _WIN32

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#endif // _WIN32

} // namespace View

} // namespace BFG

#ifdef _MSC_VER
  #pragma warning (pop)
#endif
