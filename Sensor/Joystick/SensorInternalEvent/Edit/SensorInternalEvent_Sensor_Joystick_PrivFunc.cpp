//You need to program this file.

#include "../NoEdit/SensorInternalEvent_Sensor_Joystick_PrivFunc.h"

//*******************Please add static libraries in .pro file*******************
//e.g. unix:LIBS += ... or win32:LIBS += ...

bool DECOFUNC(setParamsVarsOpenNode)(QString qstrConfigName, QString qstrNodeType, QString qstrNodeClass, QString qstrNodeName, void * paramsPtr, void * varsPtr)
{
	XMLDomInterface xmlloader(qstrConfigName,qstrNodeType,qstrNodeClass,qstrNodeName);
	SensorInternalEvent_Sensor_Joystick_Params * params=(SensorInternalEvent_Sensor_Joystick_Params *)paramsPtr;
	SensorInternalEvent_Sensor_Joystick_Vars * vars=(SensorInternalEvent_Sensor_Joystick_Vars *)varsPtr;
	/*======Please Program below======*/
	/*
	Function: open node.
	Procedure:
	1: load parameters (params). [GetParamValue(xmlloader,params,tag); GetEnumParamValue(xmlloader,params,tag); GetUEnumParamValue(xmlloader,params,tag)]
	2: initialize variables (vars).
	3: If everything is OK, return 1 for successful opening and vice versa.
	*/
    GetParamValue(xmlloader, vars, topic);
    GetParamValue(xmlloader, vars, angular_index);
    GetParamValue(xmlloader, vars, linear_index);
    GetParamValue(xmlloader, vars, angular_scale);
    GetParamValue(xmlloader, vars, linear_scale);
    GetParamValue(xmlloader, vars, startsimple_index);
    GetParamValue(xmlloader, vars, endsimple_index);
    GetParamValue(xmlloader, vars, manual_index);

    if(vars->joysticksub == NULL)
    {
        return 0;
    }
    if(vars->topic != vars->joysticksub->getTopic())
    {
        vars->joysticksub->resetTopic(vars->topic, 200);
    }
    vars->joysticksub->startReceiveSlot();

    vars->lastControlMode = 0;
    vars->currentControlMode = 1;
    vars->controlMode = 1;
	return 1;
}

bool DECOFUNC(handleVarsCloseNode)(void * paramsPtr, void * varsPtr)
{
	SensorInternalEvent_Sensor_Joystick_Params * params=(SensorInternalEvent_Sensor_Joystick_Params *)paramsPtr;
	SensorInternalEvent_Sensor_Joystick_Vars * vars=(SensorInternalEvent_Sensor_Joystick_Vars *)varsPtr;
	/*======Please Program below======*/
	/*
	Function: close node.
	Procedure:
	1: handle/close variables (vars).
	2: If everything is OK, return 1 for successful closing and vice versa.
	*/
    if(vars->joysticksub != NULL)
    {
        vars->joysticksub->stopReceiveSlot();
    }
    return 1;
}

void DECOFUNC(getInternalTrigger)(void * paramsPtr, void * varsPtr, QObject * & internalTrigger, QString & internalTriggerSignal)
{
	SensorInternalEvent_Sensor_Joystick_Params * params=(SensorInternalEvent_Sensor_Joystick_Params *)paramsPtr;
	SensorInternalEvent_Sensor_Joystick_Vars * vars=(SensorInternalEvent_Sensor_Joystick_Vars *)varsPtr;
    internalTrigger=vars->joysticksub;
    internalTriggerSignal=QString(SIGNAL(receiveMessageSignal()));
	/*======Occasionally Program above======*/
	/*
	Function: get internal trigger [defined in vars] for node.
	You need to program here when you need internal trigger (internalTrigger + internalTriggerSignal) for node.
	E.g.
	internalTrigger=&(vars->trigger);
	internalTriggerSignal=QString(SIGNAL(triggerSignal()));
	*/
}

void DECOFUNC(initializeOutputData)(void * paramsPtr, void * varsPtr, boost::shared_ptr<void> & outputDataPtr)
{
	SensorInternalEvent_Sensor_Joystick_Params * params=(SensorInternalEvent_Sensor_Joystick_Params *)paramsPtr;
	SensorInternalEvent_Sensor_Joystick_Vars * vars=(SensorInternalEvent_Sensor_Joystick_Vars *)varsPtr;
	outputDataPtr=boost::shared_ptr<void>(new SensorInternalEvent_Sensor_Joystick_Data());
	/*======Occasionally Program below/above======*/
	/*
	Function: initial output data.
	You need to program here when you need to manually initialize output data.
	*/
	
}

bool DECOFUNC(generateSourceData)(void * paramsPtr, void * varsPtr, void * outputData, QList<int> & outputPortIndex, QTime & timeStamp)
{
	SensorInternalEvent_Sensor_Joystick_Params * params=(SensorInternalEvent_Sensor_Joystick_Params *)paramsPtr;
	SensorInternalEvent_Sensor_Joystick_Vars * vars=(SensorInternalEvent_Sensor_Joystick_Vars *)varsPtr;
	SensorInternalEvent_Sensor_Joystick_Data * outputdata=(SensorInternalEvent_Sensor_Joystick_Data *)outputData;
	outputPortIndex=QList<int>();
	timeStamp=QTime();
	/*======Please Program below======*/
	/*
	Step 1: fill outputdata.
	Step 2 [optional]: determine the outputPortIndex. (if not, outputdata will be sent by all ports)
	E.g. outputPortIndex=QList<int>()<<(outportindex1)<<(outportindex2)...
	Step 3: set the timeStamp for Simulator.
	*/
    if(vars->joysticksub == NULL)
    {
        return 0;
    }
    sensor_msgs::JoyConstPtr msg = vars->joysticksub->getMessage();
    if(msg==NULL)
    {
        return 0;
    }
    outputdata->timestamp = QTime::fromMSecsSinceStartOfDay(msg->header.stamp.sec * 1000 + msg->header.stamp.nsec / 1000);
    outputdata->angular_vel = -msg->axes[ vars->angular_index];
    outputdata->linear_vel = msg->axes[ vars->linear_index];

    //可视化部分
    outputdata->back = outputdata->linear_vel <-0.5 ? 1 : 0;
    outputdata->forward = outputdata->linear_vel >0.5 ? 1 : 0;

    outputdata->left = outputdata->angular_vel <-0.5 ? 1 : 0;
    outputdata->right = outputdata->angular_vel >0.5 ? 1 : 0;

    //数据采集指示

    outputdata->startsimple = msg->buttons[vars->startsimple_index];
    outputdata->endsimple = msg->buttons[vars->endsimple_index];
/////////////////
    vars->currentControlMode = msg->buttons[vars->manual_index];

    if(vars->currentControlMode == 0 && vars->lastControlMode == 1)
        vars->controlMode = !vars->controlMode; //1-manual control; 0-auto control;下降沿改变

    vars->lastControlMode = vars->currentControlMode;
    //output
    outputdata->manual_control = vars->controlMode;

	return 1;
}

