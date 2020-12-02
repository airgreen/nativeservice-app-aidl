#ifndef IDMSC_H
#define IDMSC_H
#include <stdio.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/String16.h>
#include <callbacks/IDataReaderCallback.h>

#include <utils/Log.h>  
//using namespace android;
namespace android
{
    class INServer : public IInterface
    {
    public:
        DECLARE_META_INTERFACE(NServer); // declare macro
      


        virtual void SetDataReaderCallback(const sp<IDataReaderCallback>& data_reader_callback)=0;
        virtual void Start()=0;
        virtual void Stop()=0;
        virtual void SetOperation(String16 operation)=0;

    };


     enum
    {
        Transact_SetDataReaderCallback = IBinder::FIRST_CALL_TRANSACTION,
        Transact_Start,
        Transact_Stop,
        Transact_SetOperation
    };



    class BpNServer: public BpInterface<INServer> {
    public:
        BpNServer(const sp<IBinder>& impl);

        virtual void SetDataReaderCallback(const sp<IDataReaderCallback>& data_reader_callback);
        virtual void Start();
        virtual void Stop();
        virtual void SetOperation(String16 operation);
   };

   class BnNServer: public BnInterface<INServer> {
    public:
        virtual status_t
        onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);

    };
}
#endif


