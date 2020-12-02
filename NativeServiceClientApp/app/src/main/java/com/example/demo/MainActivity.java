package com.example.demo;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;


import android.view.KeyEvent;
import android.view.View;

import android.app.Activity;
import android.widget.Button;
import android.widget.TextView;

import com.example.nativeservice.INServerView;
import com.example.nativeservice.NServerAidlServiceWrapper;
import com.example.nativeservice.NServerPresenter;

public class MainActivity extends Activity  implements INServerView {

    private Button btnStart, btnStop;
    private TextView tvDataReaderCallback,tvStartStatus;
    private boolean isServiceConnected = false;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnStart = findViewById(R.id.btn_start_system);
        btnStop = findViewById(R.id.btn_stop_system);
        tvStartStatus = findViewById(R.id.tv_status);
        tvDataReaderCallback = findViewById(R.id.tv_data_reader_callback);


        btnStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if (!isServiceConnected){
                    tvStartStatus.setText("service not connected");
                }

                tvStartStatus.setText("Start");
                NServerPresenter.getInstance(MainActivity.this).Start();

            }
        });

        btnStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isServiceConnected){
                    tvStartStatus.setText("service not connected");
                }

                tvStartStatus.setText("Stop");
                NServerPresenter.getInstance(MainActivity.this).Stop();

            }
        });

        NServerPresenter.getInstance(this).setNServerView(this);
        NServerPresenter.getInstance(this).init(mNServerServiceConnectListener);

    }




    @Override
    protected void onResume(){
        super.onResume();

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }


    @Override
    public void onDataReaderCallback(final String data){
        runOnUiThread(new Runnable() {
            @Override
            public void run() {

                tvDataReaderCallback.setText(data);
            }
        });
    }



    NServerAidlServiceWrapper.INServerServiceConnectListener mNServerServiceConnectListener = new NServerAidlServiceWrapper.INServerServiceConnectListener(){
        @Override
        public  void onConnect(){
            NServerPresenter.getInstance(MainActivity.this).setCallback();
            isServiceConnected = true;
        }

    };



    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {


            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("");
            builder.setMessage("Are you sure you want to exit APP?");
            builder.setPositiveButton("sure", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    finish();
                }
            });

            builder.setNegativeButton("cancel", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                }
            });
            builder.show();
            return true;
        }

        return super.onKeyDown(keyCode, event);
    }



}