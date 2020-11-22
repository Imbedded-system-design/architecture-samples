//
// Created by jihun on 2020-11-22.
//

#include <jni.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>

JNIEXPORT jint JNICALL Java_com_example_android_architecture_blueprints_todoapp_tasks_TasksFragment_DotmatrixWrite(JNIEnv *env, jobject thiz, jint data) {
    int fd, ret;

    // Check Data
    if(data < 0){
        __android_log_print(ANDROID_LOG_ERROR, "DotMatrixWrite", "invalid data");
        return -1;
    }

    fd = open("/dev/matrix", O_RDWR);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "DotMatrixWrite", "device open error");
        return -1;
    }

    write(fd, &data, sizeof(data));
    if (ret < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "DotMatrixWrite", "write error");
        return -1;
    }

    close(fd);
    return 0;
}