#include "IDataReaderCallback.h"
namespace android
{


    BpDataReaderCallback::BpDataReaderCallback(const sp<IBinder>& impl) :
            BpInterface<IDataReaderCallback>(impl) {
    }

    

    void BpDataReaderCallback::SendData(String16 send_data) {
        printf("BpDataReaderCallback SendData\n");
        Parcel data, reply;
        data.writeInterfaceToken(IDataReaderCallback::getInterfaceDescriptor());
        data.writeString16(send_data);
        remote()->transact(Transact_SendData, data, &reply);
    }



    IMPLEMENT_META_INTERFACE(DataReaderCallback, "com.example.nativeservice.IDataReaderCallback");

}



