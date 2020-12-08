package com.example.android.architecture.blueprints.todoapp;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.util.Log;

import androidx.core.app.NotificationCompat;

import com.example.android.architecture.blueprints.todoapp.taskdetail.TaskDetailActivity;
import com.example.android.architecture.blueprints.todoapp.taskdetail.TaskDetailAlarmActivity;
import com.example.android.architecture.blueprints.todoapp.tasks.TasksActivity;

import java.text.SimpleDateFormat;
import java.util.Date;

public class AlarmReceiver extends BroadcastReceiver {
    static {
        System.loadLibrary("7segment");     // 7-Segment
    }
    public native int SSegmentWriteTime(int data);

    @Override
    public void onReceive(Context context, Intent intent) {
        NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        Intent notificationIntent = new Intent(context, TaskDetailActivity.class);
        notificationIntent.putExtra(TaskDetailActivity.EXTRA_TASK_ID,
                intent.getStringExtra(TaskDetailAlarmActivity.ARGUMENT_ALARM_TASK_ID));
        notificationIntent.putExtra(TaskDetailActivity.EXTRA_TASK_FROM_ALARM, true);

        notificationIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP
                | Intent.FLAG_ACTIVITY_SINGLE_TOP);

        PendingIntent pendingI = PendingIntent.getActivity(context, 0,
                notificationIntent, 0);


        NotificationCompat.Builder builder = new NotificationCompat.Builder(context, "default");

        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
            builder.setSmallIcon(R.drawable.ic_check_circle_24dp);

            String channelName ="task alarm";
            int importance = NotificationManager.IMPORTANCE_HIGH;
            NotificationChannel channel = new NotificationChannel("default", channelName, importance);

            if (notificationManager != null) {
                notificationManager.createNotificationChannel(channel);
            }
        } else builder.setSmallIcon(R.mipmap.ic_launcher);

        final SharedPreferences sharedPreferences = context.getSharedPreferences("alarm", 0);
        String taskTitle = sharedPreferences.getString("alarmTitle", "");
        builder.setAutoCancel(true)
                .setDefaults(NotificationCompat.DEFAULT_ALL)
                .setWhen(System.currentTimeMillis())
                .setTicker("{Time to watch some cool stuff!}")
                .setContentTitle("You have something to do!")
                .setContentText(taskTitle)
                .setContentInfo("INFO")
                .setContentIntent(pendingI);

        if (notificationManager != null) {
            // 노티피케이션 동작시킴
            notificationManager.notify(1234, builder.build());
        }
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("HHmm");
        int time = Integer.parseInt(sdf.format(date));
        // LED_WRITE(time);
        //TODO 1) : LED에 time을 출력한다. 출력 예시 : 2210 or 22.10 (오후 10시 10분)
        SSegmentWriteTime(time);
        class NewRunnable implements Runnable {
            @Override
            public void run() {
                while (sharedPreferences.getBoolean("isNotificationWait", true)) {
                    try {
                        // TODO LED_WRITE(8)
                        Thread.sleep(1000);
                        // TODO LED_EMPTY()
                    } catch (Exception e) {
                        Log.e("thread에러", e.getMessage());
                        e.printStackTrace();
                    }
                }
            }
        }

        NewRunnable nr = new NewRunnable();
        Thread t = new Thread(nr);
        t.start();
    }
}