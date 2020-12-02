package com.example.nativeservice;

import java.lang.String;
import com.example.nativeservice.IDataReaderCallback;


interface INServer {


    /**
     * register callback
     * @param data_reader_callback
     */
    void SetDataReaderCallback(IDataReaderCallback dataReaderCallback);


    /**
     * start
     */
    void Start();

    /**
     * stop
     */
    void Stop();


    /**
     * set operation
     * @param operation
     */
    void SetOperation(String operation);

}
