#ifndef NATIVESERVER_H
#define NATIVESERVER_H
#include <utils/Mutex.h>
#include <INServer.h>

#include <utils/String16.h>
#if defined(__ANDROID__)
#include <android/log.h>
#endif

#define LOGDBG_ENABLE

inline void empty_log_format_func(const char*, ...){}
#ifdef LOGDBG_ENABLE 

#define LOGDBG_TAG "NATIVE_SERVER"

#if defined(__ANDROID__)
#define LOGDBG(...) __android_log_print(ANDROID_LOG_INFO, LOGDBG_TAG, __VA_ARGS__)
#else
#define LOGDBG empty_log_format_func
#endif
#else
#define LOGDBG empty_log_format_func
#endif

namespace android
{
    class NativeServer : public BnNServer,
                  public IBinder::DeathRecipient{
    public:
        
        void binderDied(const wp<IBinder>& who);
      

        void SetDataReaderCallback(const sp<IDataReaderCallback>& data_reader_callback);
        void SetOperation(String16 operation);
        void Start();
        void Stop();


    private:
        Mutex mNServerLock;


    };
}
#endif

