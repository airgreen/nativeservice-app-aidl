package com.example.nativeservice;


import android.content.Context;
import android.util.Log;


/**
 * Presenter for remote service actions
 */
public class NServerPresenter {

    final static String TAG = "NServerPresenter";

    private Context mContext;
    private static NServerPresenter mNServerPresenter = null;
    private NServerAidlServiceWrapper mNServerAidlServiceWrapper = null;
    private INServerView mNServerView;




    public NServerPresenter(Context context) {
        mContext = context;
    }

    public static NServerPresenter getInstance(Context context) {
        if (mNServerPresenter == null) {
            synchronized (NServerPresenter.class) {
                if (mNServerPresenter == null) {
                    mNServerPresenter = new NServerPresenter(context);
                }
            }
        }
        return mNServerPresenter;
    }



    public void init(NServerAidlServiceWrapper.INServerServiceConnectListener nServiceConnectListener){
        mNServerAidlServiceWrapper = NServerAidlServiceWrapper.getInstance(mContext);
        mNServerAidlServiceWrapper.setNServerServiceConnectListener(nServiceConnectListener);
        mNServerAidlServiceWrapper.init();
    }


    public void setNServerView(INServerView nServerView){
        mNServerView = nServerView;
    }


    public void setCallback(){
        mNServerAidlServiceWrapper.SetDataReaderCallback(iDataReaderCallback);
    }


    private IDataReaderCallback.Stub iDataReaderCallback = new IDataReaderCallback.Stub() {


        /**
         * data from native server
         *
         * @param data
         */
        @Override
        public void SendData(String data) {

            Log.i(TAG, "SendData: " + data);

            if (mNServerView != null) {
                mNServerView.onDataReaderCallback("data： " + data);
            }
        }
    };


    /**
     * register DataReaderCallback
     * @param dataReaderCallback
     */
    public void SetDataReaderCallback(final IDataReaderCallback dataReaderCallback) {
        Log.i(TAG, "SetDataReaderCallback");
        mNServerAidlServiceWrapper.SetDataReaderCallback(dataReaderCallback);
    }


    /**
     * Start
     */
    public void Start(){

        Log.i(TAG, "Start ");
        mNServerAidlServiceWrapper.Start();
    }


    /**
     * Stop
     */
    public void Stop(){
        Log.i(TAG, "Stop ");
        mNServerAidlServiceWrapper.Stop();
    }



    /**
     * set operation
     * @param operation
     */
    public void SetOperation(final String operation){

        Log.i(TAG, "SetOperation ");
        mNServerAidlServiceWrapper.SetOperation(operation);

    }

}
