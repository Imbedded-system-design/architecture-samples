//
// Created by jihun on 2020-11-22.
//

#include <jni.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>
JNIEXPORT jint JNICALL Java_com_example_android_architecture_blueprints_todoapp_tasks_TasksActivity_LEDWrite(JNIEnv *env, jobject thiz, jint data) {
    // TODO: implement LEDWrite()
    int fd, ret;

    // Check Range
    if(data < 0 || data > 8){
        __android_log_print(ANDROID_LOG_ERROR, "LEDWrite", "invalid range");
        return -1;
    }

    // Open File Device
    fd = open("/dev/led", O_RDWR);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "LEDWrite", "device open error");
        return -1;
    }

    if(data == 0) data = 0;
    else if(data == 1) data = 128;
    else if(data == 2) data = 192;
    else if(data == 3) data = 224;
    else if(data == 4) data = 240;
    else if(data == 5) data = 248;
    else if(data == 6) data = 252;
    else if(data == 7) data = 254;
    else if(data == 8) data = 255;

    ret = write(fd, &data, 1);
    if(ret < 0){
        __android_log_print(ANDROID_LOG_ERROR, "LEDWrite", "write error");
        return -1;
    }

    close(fd);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_example_android_architecture_blueprints_todoapp_tasks_TasksFragment_LEDWrite(JNIEnv *env, jobject thiz, jint data) {
    int fd, ret;

    // Check Range
    if(data < 0 || data > 8){
        __android_log_print(ANDROID_LOG_ERROR, "LEDWrite", "invalid range");
        return -1;
    }

    // Open File Device
    fd = open("/dev/led", O_RDWR);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "LEDWrite", "device open error");
        return -1;
    }

    if(data == 0) data = 0;
    else if(data == 1) data = 128;
    else if(data == 2) data = 192;
    else if(data == 3) data = 224;
    else if(data == 4) data = 240;
    else if(data == 5) data = 248;
    else if(data == 6) data = 252;
    else if(data == 7) data = 254;
    else if(data == 8) data = 255;

    ret = write(fd, &data, 1);
    if(ret < 0){
        __android_log_print(ANDROID_LOG_ERROR, "LEDWrite", "write error");
        return -1;
    }

    close(fd);
    return 0;
}