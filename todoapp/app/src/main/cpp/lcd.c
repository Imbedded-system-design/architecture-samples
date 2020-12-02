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

//  LCD EMPTY
int EmptyLCD(){
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

JNIEXPORT jint JNICALL
Java_com_example_android_architecture_blueprints_todoapp_taskdetail_TaskDetailFragment_LCDEmpty(
        JNIEnv *env, jobject thiz) {
    return EmptyLCD();
}

JNIEXPORT jint JNICALL Java_com_example_android_architecture_blueprints_todoapp_tasks_TasksFragment_LCDEmpty(JNIEnv *env, jobject thiz) {
    return EmptyLCD();
}

// LCD 화면에 날짜를 작성하는 함수
JNIEXPORT jint JNICALL
Java_com_example_android_architecture_blueprints_todoapp_taskdetail_TaskDetailFragment_LCDWriteDate(JNIEnv *env, jobject thiz, jstring text) {
    const char *data = (*env)->GetStringUTFChars(env, text, NULL);
    char date[10];
    char time[5];
    int i = 0, j = 0;
    int isNext = 0;

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

    // Parsing
    while (*(data + i) != '\0') {
        if (*(data + i) != '\n') {
            if (isNext == 0) date[j++] = *(data + i);
            else time[j++] = *(data + i);
        }
        else {
            j = 0;
            isNext = 1;
        }
        i++;
    }

    // Set Date to LCD
    pos = 0;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    write(fd, &date, sizeof(date));

    pos = 16;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    write(fd, &time, sizeof(time));

    close(fd);
    return 0;
}



// LCD 화면에 정해진 문구를 작성하는 함수
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

    pos = 16;
    ioctl(fd, LCD_SET_CURSOR_POS, &pos, _IOC_SIZE(LCD_SET_CURSOR_POS));
    if(data == LCD_FILTER_ALL) write(fd, "All", strlen("All"));
    else if(data == LCD_FILTER_ACTIVE) write(fd, "Active", strlen("Active"));
    else if(data == LCD_FILTER_COMPLETED) write(fd, "Complete", strlen("Complete"));
    else if(data == LCD_TASK_MARKED_COMPLETE) write(fd, "lete", strlen("lete"));

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