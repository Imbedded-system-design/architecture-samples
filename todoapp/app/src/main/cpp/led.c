//
// Created by jihun on 2020-11-22.
//

#include <jni.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>

JNIEXPORT jint JNICALL Java_com_example_android_architecture_blueprints_todoapp_tasks_TasksFragment_LEDWrite(JNIEnv *env, jobject thiz, jint data) {
    int fd, ret;

    // Check Range
    if(data < 0 || data > 255){
        __android_log_print(ANDROID_LOG_ERROR, "LEDWrite", "invalid range");
        return -1;
    }

    // Open File Device
    fd = open("/dev/led", O_RDWR);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "LEDWrite", "device open error");
        return -1;
    }

    ret = write(fd, &data, 1);
    if(ret < 0){
        __android_log_print(ANDROID_LOG_ERROR, "LEDWrite", "write error");
        return -1;
    }

    close(fd);
    return 0;
}