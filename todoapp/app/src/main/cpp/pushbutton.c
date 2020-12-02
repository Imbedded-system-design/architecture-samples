#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>

// Push Button
JNIEXPORT jint JNICALL Java_com_example_android_architecture_blueprints_todoapp_tasks_TasksFragment_PushButton(JNIEnv *env, jobject thiz) {
    int fd, i;
    unsigned char bytevalues[9];
    unsigned char ret;

    fd = open("/dev/pushbutton", O_RDONLY);
    if(fd < 0){
        __android_log_print(ANDROID_LOG_ERROR, "PushButton", "device open error");
        return -1;
    }

    ret = read(fd, &bytevalues, 9);
    for(i = 0; i < 9; i++){
        if(bytevalues[i] == 1){
            close(fd);
            return i;
        }
    }

    close(fd);
    return -1;
}