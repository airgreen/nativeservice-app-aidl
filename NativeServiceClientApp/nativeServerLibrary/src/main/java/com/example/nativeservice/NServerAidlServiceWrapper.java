package com.example.nativeservice;


import android.content.Context;
import android.os.IBinder;
import android.util.Log;


import java.lang.reflect.Method;

/**
 * remote service aidl wrapper
 */
public class NServerAidlServiceWrapper {

    final static String TAG = "NServerAidlServiceWrapper";
    private Context mContext;
    private INServer iRemoteService;
    private static NServerAidlServiceWrapper nServerAidlServiceWrapper = null;
    private INServerServiceConnectListener mNServerServiceConnectListener;



    public NServerAidlServiceWrapper(Context context) {
        mContext = context;

    }



    public static NServerAidlServiceWrapper getInstance(Context context) {
        if (nServerAidlServiceWrapper == null) {
            synchronized (NServerAidlServiceWrapper.class) {
                if (nServerAidlServiceWrapper == null) {
                    nServerAidlServiceWrapper = new NServerAidlServiceWrapper(context);
                }
            }
        }
        return nServerAidlServiceWrapper;
    }


    public void init(){


        new Thread(new Runnable() {
            @Override
            public void run() {

                try {
                    Class<?> clazz = Class.forName("android.os.ServiceManager");
                    Method method = clazz.getMethod("getService", String.class);
                    IBinder binder=(IBinder) method.invoke(null, "nativeservice");

                    if(binder!= null) {
                        iRemoteService = INServer.Stub.asInterface(binder);
                        if (iRemoteService != null && mNServerServiceConnectListener != null){
                            Log.i(TAG, "Remote Service connectd " );

                            mNServerServiceConnectListener.onConnect();
                        }

                    } else {
                        Log.i(TAG, "failed to get native service");
                    }
                } catch(Exception e) {
                    Log.d(TAG, "ERROR:" + e.getMessage());
                }

            }
        }).start();


    }




    /**
     * check if remote service exist
     * @return
     */
    public boolean isValid() {
        return iRemoteService != null;
    }




    /**
     * register DataReaderCallback
     * @param dataReaderCallback
     */
    public void SetDataReaderCallback(final IDataReaderCallback dataReaderCallback) {
        if (!isValid()) return;


        try {
            iRemoteService.SetDataReaderCallback(dataReaderCallback);
        } catch (Exception e) {
            e.printStackTrace();
        }

    }


    /**
     * Start
     */
    public void  Start(){
        if (!isValid()) return;

        try {
            iRemoteService.Start();

        } catch (Exception e) {
            e.printStackTrace();
        }


    }

    /**
     * Stop
     */
    public void  Stop(){
        if (!isValid()) return;

        try {
            iRemoteService.Stop();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    /**
     * set operation
     * @param operation
     */
    public void  SetOperation(final String operation){
        if (!isValid()) return;

        try {
            iRemoteService.SetOperation(operation);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }



    public void setNServerServiceConnectListener(INServerServiceConnectListener nServiceConnectListener){

        mNServerServiceConnectListener = nServiceConnectListener;
    }

    public interface INServerServiceConnectListener{
        void onConnect();
    }

}
