//You need not to modify this file.

/*! \defgroup Simulator_Localization_Slam Simulator_Localization_Slam
	\ingroup Simulator_Library Localization_Slam_NodeClass
	\brief Simulator_Localization_Slam defines the Localization_Slam in Simulator.
*/

#ifndef SIMULATOR_LOCALIZATION_SLAM_PRIVCOREFUNC_H
#define SIMULATOR_LOCALIZATION_SLAM_PRIVCOREFUNC_H

#include<RobotSDK_Global.h>

/*! \defgroup Simulator_Localization_Slam_PrivCoreFunc Simulator_Localization_Slam_PrivCoreFunc
	\ingroup Simulator_Localization_Slam
	\brief Simulator_Localization_Slam_PrivCoreFunc defines the PrivCoreFunc in Simulator_Localization_Slam.
*/

/*! \addtogroup Simulator_Localization_Slam_PrivCoreFunc
	@{
*/

/*! \file Simulator_Localization_Slam_PrivCoreFunc.h
	 Defines the PrivCoreFunc of Simulator_Localization_Slam
*/

//*******************Please add other headers below*******************


#include "../Edit/Simulator_Localization_Slam_Vars.h"

/*! \def NODECONFIG
	\brief Forcefully defines the NodeType_NodeClass.
*/
#ifdef NODECONFIG
#undef NODECONFIG
#endif
#define NODECONFIG Simulator_Localization_Slam

/*! void Simulator_Localization_Slam_getPortsSize(QList<int> & inputPortsSize, int & outputPortsNumber)
	\brief [required] Function pointer type for interface function of getting node's port(s)' size.
	\param [out] inputPortsSize The size of each input port's data buffer.
	\param [out] outputPortsNumber The number of output ports.
*/
extern "C" ROBOTSDK_OUTPUT void DECOFUNC(getPortsSize)(QList<int> & inputPortsSize, int & outputPortsNumber);

/*! void Simulator_Localization_Slam_initializeParams(boost::shared_ptr<void> & paramsPtr)
	\brief [required] Function pointer type for interface function of initializing node's parameters.
	\param [out] paramsPtr The parameters embelished by boost::shared_pointer<void>.
	\details To initialize parameters:
	- paramsPtr=boost::shared_ptr<void> (new ParametersType);
*/
extern "C" ROBOTSDK_OUTPUT void DECOFUNC(initializeParams)(boost::shared_ptr<void> & paramsPtr);

/*! void Simulator_Localization_Slam_initializeVars(boost::shared_ptr<void> & varsPtr)
	\brief [required] Function pointer type for interface function of initializing node's variables.
	\param [out] varsPtr The variables embelished by boost::shared_pointer<void>.
	\details To initialize variables:
	- varsPtr=boost::shared_ptr<void> (new VariablesType);
*/
extern "C" ROBOTSDK_OUTPUT void DECOFUNC(initializeVars)(boost::shared_ptr<void> & varsPtr);

/*! @}*/ 

#endif