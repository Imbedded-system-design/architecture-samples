//
// Created by jihun on 2020-11-22.
//

#include <jni.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>

JNIEXPORT jint JNICALL Java_com_example_android_architecture_blueprints_todoapp_tasks_TasksFragment_SSegmentWrite(JNIEnv *env, jobject thiz, jint data) {
    int fd, ret;
    unsigned char bytevalues[4];

    // Check Range
    if ((data < 0) || (data > 9999)) {
        __android_log_print(ANDROID_LOG_ERROR, "SSegmentWrite", "invalid range");
        return -1;
    }

    // Check File Driver
    fd = open("/dev/7segment", O_RDWR);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "SSegmentWrite", "device open error");
        return -1;
    }

    bytevalues[0] = data / 1000;
    data = data % 1000;
    bytevalues[1] = data / 100;
    data = data % 100;
    bytevalues[2] = data / 10;
    data = data % 10;
    bytevalues[3] = data;

    ret = write(fd, bytevalues, sizeof(bytevalues));
    if (ret < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "SSegmentWrite", "write error");
        return -1;
    }

    close(fd);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_example_android_architecture_blueprints_todoapp_addedittask_AddEditTaskFragment_SSegmentWrite(JNIEnv *env, jobject thiz, jint data){
    int fd, ret;
    unsigned char bytevalues[4];

    // Check Range
    if ((data < 0) || (data > 9999)) {
        __android_log_print(ANDROID_LOG_ERROR, "SSegmentWrite", "invalid range");
        return -1;
    }

    // Check File Driver
    fd = open("/dev/7segment", O_RDWR);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "SSegmentWrite", "device open error");
        return -1;
    }

    bytevalues[0] = data / 1000;
    data = data % 1000;
    bytevalues[1] = data / 100;
    data = data % 100;
    bytevalues[2] = data / 10;
    data = data % 10;
    bytevalues[3] = data;

    ret = write(fd, bytevalues, sizeof(bytevalues));
    if (ret < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "SSegmentWrite", "write error");
        return -1;
    }

    close(fd);
    return 0;
}