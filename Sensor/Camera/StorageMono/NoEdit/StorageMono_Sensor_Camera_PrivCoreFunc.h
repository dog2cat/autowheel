//You need not to modify this file.

/*! \defgroup StorageMono_Sensor_Camera StorageMono_Sensor_Camera
	\ingroup StorageMono_Library Sensor_Camera_NodeClass
	\brief StorageMono_Sensor_Camera defines the Sensor_Camera in StorageMono.
*/

#ifndef STORAGEMONO_SENSOR_CAMERA_PRIVCOREFUNC_H
#define STORAGEMONO_SENSOR_CAMERA_PRIVCOREFUNC_H

#include<RobotSDK_Global.h>

/*! \defgroup StorageMono_Sensor_Camera_PrivCoreFunc StorageMono_Sensor_Camera_PrivCoreFunc
	\ingroup StorageMono_Sensor_Camera
	\brief StorageMono_Sensor_Camera_PrivCoreFunc defines the PrivCoreFunc in StorageMono_Sensor_Camera.
*/

/*! \addtogroup StorageMono_Sensor_Camera_PrivCoreFunc
	@{
*/

/*! \file StorageMono_Sensor_Camera_PrivCoreFunc.h
	 Defines the PrivCoreFunc of StorageMono_Sensor_Camera
*/

//*******************Please add other headers below*******************


#include "../Edit/StorageMono_Sensor_Camera_Vars.h"

/*! \def NODECONFIG
	\brief Forcefully defines the NodeType_NodeClass.
*/
#ifdef NODECONFIG
#undef NODECONFIG
#endif
#define NODECONFIG StorageMono_Sensor_Camera

/*! void StorageMono_Sensor_Camera_getPortsSize(QList<int> & inputPortsSize, int & outputPortsNumber)
	\brief [required] Function pointer type for interface function of getting node's port(s)' size.
	\param [out] inputPortsSize The size of each input port's data buffer.
	\param [out] outputPortsNumber The number of output ports.
*/
extern "C" ROBOTSDK_OUTPUT void DECOFUNC(getPortsSize)(QList<int> & inputPortsSize, int & outputPortsNumber);

/*! void StorageMono_Sensor_Camera_initializeParams(boost::shared_ptr<void> & paramsPtr)
	\brief [required] Function pointer type for interface function of initializing node's parameters.
	\param [out] paramsPtr The parameters embelished by boost::shared_pointer<void>.
	\details To initialize parameters:
	- paramsPtr=boost::shared_ptr<void> (new ParametersType);
*/
extern "C" ROBOTSDK_OUTPUT void DECOFUNC(initializeParams)(boost::shared_ptr<void> & paramsPtr);

/*! void StorageMono_Sensor_Camera_initializeVars(boost::shared_ptr<void> & varsPtr)
	\brief [required] Function pointer type for interface function of initializing node's variables.
	\param [out] varsPtr The variables embelished by boost::shared_pointer<void>.
	\details To initialize variables:
	- varsPtr=boost::shared_ptr<void> (new VariablesType);
*/
extern "C" ROBOTSDK_OUTPUT void DECOFUNC(initializeVars)(boost::shared_ptr<void> & varsPtr);

/*! @}*/ 

#endif