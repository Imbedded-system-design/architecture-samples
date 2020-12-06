package com.example.android.architecture.blueprints.todoapp.taskdetail;

import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TimePicker;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.example.android.architecture.blueprints.todoapp.AlarmReceiver;
import com.example.android.architecture.blueprints.todoapp.R;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;

public class TaskDetailAlarmActivity extends AppCompatActivity {

    public static final String ARGUMENT_ALARM_TASK_ID = "ALARM_TASK_ID";
    public static final String ARGUMENT_ALARM_TASK_TITLE = "ALARM_TASK_TITLE";
    String taskId;
    boolean isThreadRunning = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_task_detail_alarm);

        final Button b1 = findViewById(R.id.btn1);
        final Button b2 = findViewById(R.id.btn2);
        final Button b3 = findViewById(R.id.btn3);
        final Button b4 = findViewById(R.id.btn4);
        Button back = findViewById(R.id.goBackBtn);
        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onBackPressed();
            }
        });

        SharedPreferences sharedPreferences = getSharedPreferences("alarm", 0);
        String savedAlarm = sharedPreferences.getString("savedAlarm", "0000");
        b1.setText(String.valueOf(savedAlarm.charAt(0)));
        b2.setText(String.valueOf(savedAlarm.charAt(1)));
        b3.setText(String.valueOf(savedAlarm.charAt(2)));
        b4.setText(String.valueOf(savedAlarm.charAt(3)));

        b1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                waitPushButton(b1);
            }
        });
        b2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                waitPushButton(b2);
            }
        });
        b3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                waitPushButton(b3);
            }
        });
        b4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                waitPushButton(b4);
            }
        });


        taskId = getIntent().getStringExtra(ARGUMENT_ALARM_TASK_ID);

        Button button = (Button) findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View arg0) {
                int hour_24, minute;
                String hour = b1.getText().toString() + b2.getText().toString();
                String min = b3.getText().toString() + b4.getText().toString();
                hour_24 = Integer.parseInt(hour);
                minute = Integer.parseInt(min);

                // 현재 지정된 시간으로 알람 시간 설정
                Calendar calendar = Calendar.getInstance();
                calendar.setTimeInMillis(System.currentTimeMillis());
                calendar.set(Calendar.HOUR_OF_DAY, hour_24);
                calendar.set(Calendar.MINUTE, minute);
                calendar.set(Calendar.SECOND, 0);

                Date currentDateTime = calendar.getTime();
                String date_text = new SimpleDateFormat("a hh:mm~", Locale.getDefault()).format(currentDateTime);
                Toast.makeText(getApplicationContext(),"We are going to tell you at" + date_text, Toast.LENGTH_SHORT).show();

                //  Preference에 설정한 값 저장
                SharedPreferences.Editor editor = getSharedPreferences("alarm", MODE_PRIVATE).edit();
                editor.putString("savedAlarm", hour + min);
                editor.apply();

//                SharedPreferences sharedPreferences = context.getSharedPreferences("alarm", 0);
//                String taskTitle = sharedPreferences.getString("alarmTitle", "");


                diaryNotification(calendar);
                onBackPressed();
            }

        });
    }

    void changeButtonText(Button button) {
        if(button.getText() != "__") {
            button.setText("__");
            isThreadRunning = true;
        } else {
            button.setText("0");
            isThreadRunning = false;
        }

    }

    void waitPushButton(final Button button) {
        changeButtonText(button);
        class NewRunnable implements Runnable {
            @Override
            public void run() {
                while (true) {
                    try {
                        // Thread가 돌고 있을 때 다른 버튼을 누르면 안됨.
                        // 다시 한번 눌러 숫자 0을 만들고 다른 button을 눌러야 함
                        if(!isThreadRunning) break;
                        int pushButtonNum = 0;
                        //TODO 3) pushButtonNum = push button 누른 값을 받아온다. (1~9)
                        if(pushButtonNum > 0) {
                            button.setText(String.valueOf(pushButtonNum));
                            break;
                        }
                        Thread.sleep(400);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }
        NewRunnable nr = new NewRunnable();
        Thread t = new Thread(nr);
        t.start();
    }

    void diaryNotification(Calendar calendar) {
        Intent alarmIntent = new Intent(this, AlarmReceiver.class);
        alarmIntent.putExtra(TaskDetailAlarmActivity.ARGUMENT_ALARM_TASK_ID, taskId);
        PendingIntent pendingIntent = PendingIntent.getBroadcast(this, 0, alarmIntent, 0);
        AlarmManager alarmManager = (AlarmManager) getSystemService(Context.ALARM_SERVICE);
        alarmManager.set(AlarmManager.RTC_WAKEUP, calendar.getTimeInMillis(), pendingIntent);
    }
}