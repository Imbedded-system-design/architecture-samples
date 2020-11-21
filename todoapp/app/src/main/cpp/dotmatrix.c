//
// Created by jihun on 2020-11-22.
//

#include <jni.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>

JNIEXPORT void JNICALL
Java_com_example_android_architecture_blueprints_todoapp_tasks_TasksFragment_DotmatrixWrite(JNIEnv *env, jobject thiz, jint data) {
    // TODO: implement DotmatrixWrite()
    int fd, ret;

    if ((data < 0) || (data > 9999)) {
        printf("Invalid range!\n");
    }

    fd = open("/dev/dotmatrix2", O_RDWR);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "SSegmentWrite", "device open error");
    }

    ret = write(fd, &data, sizeof(data));
    if (ret < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "SSegmentWrite", "write error");
    }

    close(fd);
}