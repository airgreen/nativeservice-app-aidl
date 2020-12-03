This is a simple example for native service and app communcation via aidl on android platform. Native service server will add service nativeservice in service manager and app will connect nativeservice via ServiceManager.<br> 
When click start button, app will send start command to native service and native service will continues to return timestamps to app. Native service will stop sending data when click stop button.<br> 
<br> 
<br> 
#### How to build native service server<br> 
1. Download AOSP code. I built the server on Oreo 8.1.0 version.<br> 
2. Make a full build<br> 
3. Put native-service to the root path of AOSP code.<br> 
4. In the root path of AOSP code execute command source ./build/envsetup.sh<br> 
5. Enter the directory native-service and execute command mm to build native-service and generate bin native_server.<br> 

#### Manually start native service server with the following steps:
1. adb root<br> 
2. adb remount<br> 
3. adb push native_server /system/bin/<br> 
6. adb shell setenforce 0<br> 
7. adb shell<br> 
8. cd /system/bin<br> 
9. execute ./native_server to start native service<br> 
<br> 
Sometimes app can not connect to native service due to selinux permission problem. The step 6 setenforce 0 above used to put selinux in permissive mode and close selinux temporarily.<br> 
When native_server is running you can install and start app to connect it.<br>  
 

