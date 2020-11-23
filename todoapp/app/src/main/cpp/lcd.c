//
// Created by jihun on 2020-11-22.
//

#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h>

#include "def.h"

#define LCD_MAGIC           0xBD
#define LCD_SET_CURSOR_POS  _IOW(LCD_MAGIC, 0, int)

// LCD 화면을 비워주는 함수
JNIEXPORT jint JNICALL Java_com_example_android_architecture_blueprints_todoapp_tasks_TasksFragment_LCDEmpty(JNIEnv *env, jobject thiz) {
    int fd, pos;

    // Open File Device
    fd = open("/dev/lcd", O_RDWR);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "LCDEmpty", "device open error");
        return -1;
    }

    // Set Empty
    pos = 0;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    write(fd, "                ", 16);

    pos = 16;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    write(fd, "                ", 16);

    close(fd);
    return 0;
}

// LCD 화면에 글자를 작성하는 함수
JNIEXPORT jint JNICALL Java_com_example_android_architecture_blueprints_todoapp_tasks_TasksFragment_LCDWrite(JNIEnv *env, jobject thiz, jint data, jint delay) {
    int fd, pos;

    // Check Data
    if(data <= 0){
        __android_log_print(ANDROID_LOG_ERROR, "LCDWrite", "invalid data");
        return -1;
    }

    // Open File Device
    fd = open("/dev/lcd", O_RDWR);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "LCDWrite", "device open error");
        return -1;
    }

    // Screen Init (Empty)
    pos = 0;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    write(fd, "                ", 16);

    pos = 16;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    write(fd, "                ", 16);

    pos = 0;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    if(data == LCD_FILTER_ALL) write(fd, "Filter", strlen("Filter"));
    else if(data == LCD_FILTER_ACTIVE) write(fd, "Filter", strlen("Filter"));
    else if(data == LCD_FILTER_COMPLETED) write(fd, "Filter", strlen("Filter"));
    else if(data == LCD_TASK_MARKED_COMPLETE) write(fd, "Task marked comp", strlen("Task marked comp"));
    else if(data == LCD_EMPTY) write(fd, "                ", strlen("                "));

    pos = 16;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    if(data == LCD_FILTER_ALL) write(fd, "All", strlen("All"));
    else if(data == LCD_FILTER_ACTIVE) write(fd, "Active", strlen("Active"));
    else if(data == LCD_FILTER_COMPLETED) write(fd, "Complete", strlen("Complete"));
    else if(data == LCD_TASK_MARKED_COMPLETE) write(fd, "lete", strlen("lete"));
    else if(data == LCD_EMPTY) write(fd, "        ", strlen("        "));

    // Set Empty
    if(delay != 0) {
        sleep(delay);

        pos = 0;
        ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
        write(fd, "                ", 16);

        pos = 16;
        ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
        write(fd, "                ", 16);
    }

    close(fd);
    return 0;
}