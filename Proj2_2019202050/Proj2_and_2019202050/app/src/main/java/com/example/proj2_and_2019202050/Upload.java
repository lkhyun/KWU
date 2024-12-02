package com.example.proj2_and_2019202050;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;

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


public class Upload extends AppCompatActivity {
    private static final int REQUEST_IMAGE_PICK = 1;
    private ImageView imageView;
    private EditText titleText;
    private EditText contentText;
    private Button picSelectBtn;//사진 선택버튼
    private Button picSubmitBtn;//게시물 업로드 버튼
    private String photoPath;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_upload);

        imageView = findViewById(R.id.picture);
        titleText = findViewById(R.id.picTitle);
        contentText = findViewById(R.id.picContent);
        picSelectBtn = findViewById(R.id.picSelect);
        picSubmitBtn = findViewById(R.id.PostButton);

        //사진 선택버튼 눌렀을 때
        picSelectBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openGallery();
            }//openGallery 실행
        });
        //게시물 업로드 버튼 눌렀을 때
        picSubmitBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                uploadPost();
            }//uploadPost 실행
        });

        Button ReturnButton = (Button) findViewById(R.id.ReturnButton);
        ReturnButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }//현재 액티비티 종료
        });
    }
    private void openGallery() {
        //암시적 인텐트로 사진을 고를수 있게끔
        Intent intent = new Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        startActivityForResult(intent, REQUEST_IMAGE_PICK);
    }

    private void uploadPost() {
        //번들은 수정 시 아무것도 입력되지 않은 항목이 있으면 기존 데이터를 유지하기 위함임.
        Bundle bundle = getIntent().getExtras();
        String title = titleText.getText().toString();
        if(title.isEmpty())//아무항목도 입력되지 않으면
        {
            if(bundle != null)//번들로 가져온 title을 유지
            {
                title = bundle.getString("title");
            }
        }
        String content = contentText.getText().toString();
        if(content.isEmpty())//아무항목도 입력되지 않으면
        {
            if(bundle != null)//번들로 가져온 content을 유지
            {
                content = bundle.getString("content");
            }
        }
        if(photoPath == null){//사진도 없으면
            if(bundle != null)//기존 사진을 사용
            {
                photoPath = bundle.getString("photoPath");
            }
        }

        try {
            JSONObject jsonObject = new JSONObject();
            if(bundle != null)//번들이 있는 건 수정한다는 소리니까 id도 함께 보내기
            {
                jsonObject.put("id",bundle.getLong("id"));
            }
            jsonObject.put("title", title);
            jsonObject.put("content", content);
            jsonObject.put("photoPath", photoPath);

            String jsonPayload = jsonObject.toString();

            Log.d("JSON Payload", jsonPayload);

            //json으로 서버에 보내기
            sendJsonToServer(jsonPayload);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    private void sendJsonToServer(String jsonPayload) {
        OkHttpClient client = new OkHttpClient();

        MediaType mediaType = MediaType.parse("application/json; charset=utf-8");
        RequestBody requestBody = RequestBody.create(mediaType, jsonPayload);
        //post 요청 생성
        Request request = new Request.Builder()
                .url("http://10.0.2.2:8080/info/upload")
                .post(requestBody)
                .build();

        //요청 보내기
        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
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

    //사진을 가져오는 암시적 인텐트가 끝나면 실행되는 함수
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_IMAGE_PICK && resultCode == RESULT_OK && data != null) {
            Uri imageUri = data.getData();
            if (imageUri != null) {
                //사진 경로 얻어내기
                String[] filePathColumn = {MediaStore.Images.Media.DATA};
                Cursor cursor = getContentResolver().query(imageUri, filePathColumn, null, null, null);
                if (cursor != null && cursor.moveToFirst()) {
                    int pathColumnIndex = cursor.getColumnIndex(filePathColumn[0]);
                    photoPath = cursor.getString(pathColumnIndex);
                    cursor.close();

                    //선택된 사진 보여주기
                    imageView.setImageURI(imageUri);
                }
            }
        }
    }

}