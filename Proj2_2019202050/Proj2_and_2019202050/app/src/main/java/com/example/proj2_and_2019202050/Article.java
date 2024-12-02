package com.example.proj2_and_2019202050;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class Article extends AppCompatActivity {

    private TextView ArtTitle;
    private TextView ArtContent;
    private TextView ArtPhotoPath;
    //인텐트내 번들로 프래그먼트에서 데이터를 넣어 보내면 이를 저장할 변수들
    private Long ArtId;
    String titleValue;
    String contentValue;
    String photoValue;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_article);

        //인텐트로 함께 보내진 데이터 사용
        Bundle bundle = getIntent().getExtras();
        if(bundle != null){
            ArtId = bundle.getLong("id");
            titleValue = bundle.getString("title");
            contentValue = bundle.getString("content");
            photoValue = bundle.getString("photoPath");
        }
        //번들 내의 데이터로 뷰에 데이터 형성
        ArtTitle = findViewById(R.id.titleId);
        ArtContent = findViewById(R.id.contentId);
        ArtPhotoPath = findViewById(R.id.photoId);
        ArtTitle.setText(titleValue);
        ArtContent.setText(contentValue);
        ArtPhotoPath.setText(photoValue);

        Button ReturnButton = (Button) findViewById(R.id.ReturnButton);
        Button ModifyButton = (Button) findViewById(R.id.ModifyButton);
        Button DeleteButton = (Button) findViewById(R.id.DeleteButton);
        //각 버튼에 따른 리스터 생성
        //뒤로가기 버튼이 눌리면 현재 액티비티 종료하고 메인으로 돌아가기
        ReturnButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });
        //수정 버튼이 눌리면 현재 데이터와 함께 인텐트로 업로드 액티비티 실행하고 Article 액티비티는 종료
        ModifyButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(),Upload.class);
                Bundle bundle = new Bundle();
                bundle.putLong("id",ArtId);
                bundle.putString("title",titleValue);
                bundle.putString("content",contentValue);
                bundle.putString("photoPath",photoValue);
                intent.putExtras(bundle);
                startActivity(intent);
                finish();
            }
        });
        //삭제 버튼을 누르면 현재 게시물 id를 서버로 보내 데이터베이스에서 삭제하게끔 요청보냄
        DeleteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                deletePost();
            }
        });
    }
    private void deletePost() {

        //id를 json형식으로 변환해서 sendJsonToServer함수 실행
        try {
            JSONObject jsonObject = new JSONObject();
            jsonObject.put("id",ArtId);

            String jsonPayload = jsonObject.toString();

            //로그 형성
            Log.d("JSON Payload", jsonPayload);

            sendJsonToServer(jsonPayload);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
    //통신을 위해 OkHttp사용
    private void sendJsonToServer(String jsonPayload) {
        OkHttpClient client = new OkHttpClient();
        //미디어 타입을 json형식으로 하고
        MediaType mediaType = MediaType.parse("application/json; charset=utf-8");
        //requestbody 만들기
        RequestBody requestBody = RequestBody.create(mediaType, jsonPayload);
        //url과 delete요청임을 명시하고
        Request request = new Request.Builder()
                .url("http://10.0.2.2:8080/info/delete")
                .delete(requestBody)
                .build();
        //요청 보내기
        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                //응답이 안오면
                e.printStackTrace();
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                //응답이 오면
                if (response.isSuccessful()) {
                    // Request successful
                    Log.d("Response", response.body().string());
                } else {
                    // Request failed
                    Log.d("Response", "Request failed: " + response.code());
                }
            }
        });
    }
}