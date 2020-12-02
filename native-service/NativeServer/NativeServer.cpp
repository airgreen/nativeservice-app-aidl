#include "NativeServer.h"
#include <chrono>
#include <thread>
#include <atomic>
#include <sys/prctl.h>
#include <fstream>
#include <vector>


void SendData();
void StartDataReader(); 
void StopDataReader();


android::sp<android::NativeServer>  mNativeServer;
android::sp<android::IDataReaderCallback>  mDataReaderCallback;
std::atomic<bool> isDataReaderStart(false);

namespace android
{


    void NativeServer::binderDied(const wp<IBinder>& who) {
        printf("NativeServer binderDied\n");
        LOGDBG("NativeServer binderDied");
    }
    

    void NativeServer::SetDataReaderCallback(const sp<IDataReaderCallback>& data_reader_callback) {


        printf("NativeServer SetDataReaderCallback \n");
        LOGDBG("NativeServer SetDataReaderCallback \n");
        {
		if (data_reader_callback == NULL)
		    return;
		Mutex::Autolock _l(mNServerLock);
		if (IInterface::asBinder(mDataReaderCallback) == IInterface::asBinder(data_reader_callback)) {
		  return;
		}
		mDataReaderCallback = data_reader_callback;
		IInterface::asBinder(data_reader_callback)->linkToDeath(this);
         }

    }
		
    /**
     * start reader
     */
    void NativeServer::Start(){
        int ret = 0;
        printf("DMSCServer Start\n");
        LOGDBG("DMSCServer Start\n");
          
	StartDataReader();            
    }

    /**
     * stop reader
     */
    void NativeServer::Stop(){
        int ret = 0;
        printf("DMSCServer Stop\n");
        LOGDBG("DMSCServer Stop\n");
        StopDataReader();           
    }


    /**
     * set operation
     */
    void NativeServer::SetOperation(String16 operation){
        int ret = 0;
        printf("DMSCServer Stop\n");
        LOGDBG("DMSCServer Stop\n");
          
        String8 str8Operation = String8(operation);       
        std::string strOperation(str8Operation.string()); 
        LOGDBG("NativeServer operation: %s",strOperation.c_str());
            
    }

}

    /**
     *  sendData
     */
    void SendData() {

        while(isDataReaderStart){

            printf("sendData \n");

            auto now_t = std::chrono::system_clock::now().time_since_epoch();
            int64_t time = now_t / std::chrono::nanoseconds(1);

            std::string timeStr = std::to_string(time);
            if (mDataReaderCallback != nullptr){
                mDataReaderCallback->SendData(android::String16(timeStr.c_str()));
            }
       
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    /**
     * start data reader
     */
    void StartDataReader() {
        printf("NativeServer StartDataReader\n");
        LOGDBG("NativeServer StartDataReader\n");
        if (!isDataReaderStart){
	    isDataReaderStart = true;
            std::thread thread_send(SendData);
            thread_send.detach();
        }
    }

    /**
     * stop data reader
     */        
    void StopDataReader() {
        printf("NativeServer StopDataReader\n");
        LOGDBG("NativeServer StopDataReader\n");
	if (isDataReaderStart){
            isDataReaderStart = false;
        }
    }



//======================MAIN=============================
    int main() {
      
        
        printf("NativeServer start\n");
        LOGDBG("NativevServer start\n");
 

        android::sp<android::ProcessState> proc(android::ProcessState::self());
        android::sp<android::IServiceManager> sm = android::defaultServiceManager();
        
        mNativeServer = new android::NativeServer();
        sm->addService(android::String16("nativeservice"), mNativeServer);
        printf("Native server starts to work\n");
        LOGDBG("Native server starts to work\n");
        android::ProcessState::self()->startThreadPool();
        android::IPCThreadState::self()->joinThreadPool();
        
        return 0;
    }


