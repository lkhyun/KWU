package com.example.proj2_and_2019202050;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

public class logo extends AppCompatActivity {
    //로고 액티비티, manifest를 수정해서 처음 앱을 실행할때 로고 액티비티를 먼저 실행하게 끔 하고
    //로고 액티비티를 1초 보여준 후 메인 액티비티를 실행하게 하였음. 메인액티비티가 실행되면 자신을
    //finish로 종료함

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_logo);
        Handler handler = new Handler();
        handler.postDelayed(new Runnable(){
            @Override
            public void run() {
                Intent intent = new Intent (getApplicationContext(), MainActivity.class);
                startActivity(intent); //인트로 실행 후 바로 Main Activity로 넘어감.
                finish();
            }
        },1000); //1초 후 인트로 실행
    }
    @Override
    protected void onPause(){
        super.onPause();
        finish();
    }
}