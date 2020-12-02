#include "INServer.h"
namespace android
{

       BpNServer::BpNServer(const sp<IBinder>& impl) :
            BpInterface<INServer>(impl) {
       }


        /**
         * register data reader callback
         * @param reader_callback
         */
        void BpNServer::SetDataReaderCallback(const sp<IDataReaderCallback>& data_reader_callback){
            printf("BpNServer SetDataReaderCallback\n");
            Parcel data;
            data.writeInterfaceToken(INServer::getInterfaceDescriptor());
            data.writeStrongBinder(IInterface::asBinder(data_reader_callback));
            remote()->transact(Transact_SetDataReaderCallback, data, NULL);
        }

     

        /**
         * start
         */
        void BpNServer::Start(){
            printf("BpNServer Start\n");
            Parcel data,reply;
            data.writeInterfaceToken(INServer::getInterfaceDescriptor());
            remote()->transact(Transact_Start, data, &reply);

        }

        /**
         * stop
         */
        void BpNServer::Stop(){
            printf("BpNServer Stop\n");
            Parcel data,reply;
            data.writeInterfaceToken(INServer::getInterfaceDescriptor());
            remote()->transact(Transact_Stop, data, &reply);
        }


        /**
         * set operation
         */
        void BpNServer::SetOperation(String16 operation){
            printf("BpNServer SetOperation\n");
            Parcel data;
            data.writeInterfaceToken(INServer::getInterfaceDescriptor());
            data.writeString16(operation);
            remote()->transact(Transact_SetOperation, data, NULL);
        }




    IMPLEMENT_META_INTERFACE(NServer, "com.example.nativeservice.INServer");



    status_t
    BnNServer::onTransact(uint_t code, const Parcel& data, Parcel* reply, uint32_t flags) {
        switch (code)
            {



       case Transact_SetDataReaderCallback:

            {

                printf("BnNServer Transact_SetDataReaderCallback\n");
                CHECK_INTERFACE(INServer, data, reply);
                sp<IDataReaderCallback> callback =
                interface_cast<IDataReaderCallback>(data.readStrongBinder());
                SetDataReaderCallback(callback);
                return NO_ERROR;
            }
            break;
         case Transact_Start:
            {      
               
                printf("BnNServer Transact_start\n");
                CHECK_INTERFACE(INServer, data, reply);
                Start();

                return NO_ERROR;
            }
            break;
         case Transact_Stop:
            {      
               
                printf("BnDMSC Transact_stop\n");
                CHECK_INTERFACE(INServer, data, reply);
                Stop();

                return NO_ERROR;
            }
            break;

         case Transact_SetOperation:
            {
                printf("BnNServer Transact_SetOperation\n");
                CHECK_INTERFACE(INServer, data, reply);
                String16 operation = data.readString16();
                SetOperation(operation);
                reply->writeInt32(0);
                return NO_ERROR;

            }
            break;

        default:
            break;
            }
        return NO_ERROR;
    }



}
