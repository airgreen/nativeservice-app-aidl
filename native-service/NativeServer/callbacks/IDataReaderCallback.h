#ifndef IREADERCALLBACK_H
#define IREADERCALLBACK_H
#include <stdio.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/String16.h>
#include <utils/Log.h>  
//using namespace android;
namespace android
{
    class IDataReaderCallback : public IInterface
    {
    public:
        DECLARE_META_INTERFACE(DataReaderCallback); // declare macro
      
   

    virtual void SendData(String16 send_data)=0;

    };


 
    enum
    {
        Transact_SendData = IBinder::FIRST_CALL_TRANSACTION+0,
        
    };

     



    class BpDataReaderCallback: public BpInterface<IDataReaderCallback> {
    public:
        BpDataReaderCallback(const sp<IBinder>& impl);
	virtual void SendData(String16 send_data);

    };

}
#endif

