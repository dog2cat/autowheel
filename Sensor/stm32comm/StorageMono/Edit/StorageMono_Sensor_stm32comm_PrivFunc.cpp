//You need to program this file.

#include "../NoEdit/StorageMono_Sensor_stm32comm_PrivFunc.h"

//*******************Please add static libraries in .pro file*******************
//e.g. unix:LIBS += ... or win32:LIBS += ...

bool DECOFUNC(setParamsVarsOpenNode)(QString qstrConfigName, QString qstrNodeType, QString qstrNodeClass, QString qstrNodeName, void * paramsPtr, void * varsPtr)
{
	XMLDomInterface xmlloader(qstrConfigName,qstrNodeType,qstrNodeClass,qstrNodeName);
	StorageMono_Sensor_stm32comm_Params * params=(StorageMono_Sensor_stm32comm_Params *)paramsPtr;
	StorageMono_Sensor_stm32comm_Vars * vars=(StorageMono_Sensor_stm32comm_Vars *)varsPtr;
	/*======Please Program below======*/
	/*
	Function: open node.
	Procedure:
	1: load parameters (params). [GetParamValue(xmlloader,params,tag); GetEnumParamValue(xmlloader,params,tag); GetUEnumParamValue(xmlloader,params,tag)]
	2: initialize variables (vars).
	3: If everything is OK, return 1 for successful opening and vice versa.
    */
    GetParamValue(xmlloader, params, filename);
    GetParamValue(xmlloader, params, storagepath);

    QDateTime now = QDateTime::currentDateTime();
    QString subFolder = now.toString("MMdd_hhmm");
    QDir target(params->storagepath+"/"+subFolder);
    if (!target.exists())
    {
        target.mkpath("./");
    }

    QString tmpfilename = QString("%1/%2/%3").arg(params->storagepath).arg(subFolder).arg(params->filename);
    const char* filename = tmpfilename.toStdString().c_str();
    vars->storagefile.open(filename);

    vars->storagefile<<"time\tx\ty\ttheta\tyaw\tleftodom\trightodom\tleftspeed\trightspeed\n";
    return 1;
}

bool DECOFUNC(handleVarsCloseNode)(void * paramsPtr, void * varsPtr)
{
	StorageMono_Sensor_stm32comm_Params * params=(StorageMono_Sensor_stm32comm_Params *)paramsPtr;
	StorageMono_Sensor_stm32comm_Vars * vars=(StorageMono_Sensor_stm32comm_Vars *)varsPtr;
	/*======Please Program below======*/
	/*
	Function: close node.
	Procedure:
	1: handle/close variables (vars).
	2: If everything is OK, return 1 for successful closing and vice versa.
	*/
    if(vars->storagefile.is_open())
        vars->storagefile.close();
	return 1;
}

void DECOFUNC(getInternalTrigger)(void * paramsPtr, void * varsPtr, QObject * & internalTrigger, QString & internalTriggerSignal)
{
	StorageMono_Sensor_stm32comm_Params * params=(StorageMono_Sensor_stm32comm_Params *)paramsPtr;
	StorageMono_Sensor_stm32comm_Vars * vars=(StorageMono_Sensor_stm32comm_Vars *)varsPtr;
	internalTrigger=NULL;
	internalTriggerSignal=QString();
	/*======Occasionally Program above======*/
	/*
	Function: get internal trigger [defined in vars] for node.
	You need to program here when you need internal trigger (internalTrigger + internalTriggerSignal) for node.
	E.g.
	internalTrigger=&(vars->trigger);
	internalTriggerSignal=QString(SIGNAL(triggerSignal()));
	*/
}

void DECOFUNC(getMonoDrainDataSize)(void * paramsPtr, void * varsPtr, int & drainDataSize)
{
	StorageMono_Sensor_stm32comm_Params * params=(StorageMono_Sensor_stm32comm_Params *)paramsPtr;
	StorageMono_Sensor_stm32comm_Vars * vars=(StorageMono_Sensor_stm32comm_Vars *)varsPtr;
	drainDataSize=0;
	/*======Please Program above======*/
	/*
	Function: get drain data size to be grabbed from buffer.
	Rules:
	drainDataSize=0: grab and remove all data from buffer.
	drainDataSize>0: grab drainDataSize latest data from buffer.
	drainDataSize<0: grab and remove drainDataSize ancient data from buffer.
	*/
}

//Input Port #0: Buffer_Size = 0, Params_Type = SourceDrainMono_Sensor_stm32comm_Params, Data_Type = SourceDrainMono_Sensor_stm32comm_Data
bool DECOFUNC(processMonoDrainData)(void * paramsPtr, void * varsPtr, QVector<void *> drainParams, QVector<void *> drainData)
{
	StorageMono_Sensor_stm32comm_Params * params=(StorageMono_Sensor_stm32comm_Params *)paramsPtr;
	StorageMono_Sensor_stm32comm_Vars * vars=(StorageMono_Sensor_stm32comm_Vars *)varsPtr;
	QVector<SourceDrainMono_Sensor_stm32comm_Params *> drainparams; copyQVector(drainparams,drainParams);
	QVector<SourceDrainMono_Sensor_stm32comm_Data *> draindata; copyQVector(draindata,drainData);
	if(draindata.size()==0){return 0;}
	/*======Please Program below======*/
	/*
	Function: process draindata.
	*/
//    SourceDrainMono_Sensor_stm32comm_Data *data = draindata.front();
//    int time = ((data->timestamp.hour()*60 + data->timestamp.minute())*60  + data->timestamp.second()) *1000+data->timestamp.msec();
//    vars->storagefile<<time<<'\t'<<data->x<<'\t'<<data->y<<'\t'<<data->theta<<'\t'<<data->yaw<<'\t'<<data->leftodom<<'\t'<<data->rightodom<<'\t'<<std::endl;
    int i, n=draindata.size();
//    for(i=0; i<n; i++)
//    {
//        SourceDrainMono_Sensor_stm32comm_Data *data = draindata[i];
//        int time = ((data->timestamp.hour()*60 + data->timestamp.minute())*60  + data->timestamp.second()) *1000
//                +data->timestamp.msec();
//        vars->storagefile<<time<<'\t'<<data->x<<'\t'<<data->y<<'\t'<<data->theta<<'\t'
//                        <<data->yaw<<'\t'<<data->leftodom<<'\t'<<data->rightodom<<'\t'<<std::endl;
//    }
    for(i=n-1; i>=0; i--)
    {
        SourceDrainMono_Sensor_stm32comm_Data *data = draindata[i];
        int time = ((data->timestamp.hour()*60 + data->timestamp.minute())*60  + data->timestamp.second()) *1000
                +data->timestamp.msec();
        vars->storagefile<<time<<'\t'<<data->x<<'\t'<<data->y<<'\t'<<data->theta<<'\t'
                        <<data->yaw<<'\t'<<data->leftodom<<'\t'<<data->rightodom<<'\t'
                       <<data->leftspeed<<'\t'<<data->rightspeed<<std::endl;
    }
	return 1;
}

