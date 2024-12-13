package com.example.proj2_and_2019202050;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.w3c.dom.Text;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class TitleFragment extends Fragment {

    private ListView view;
    private List<DTO> dtoList = new ArrayList<>();
    private MyListAdapter lAdapter;
    //데이터베이스에 저장되는 테이블과 필드가 동일한 dto사용
    public class DTO{
        private Long id;
        private String title;
        private String content;
        private String photoPath;
        private String createdDate;

        public void setId(Long id){this.id = id;}
        public void setTitle(String title){this.title = title;}
        public void setContent(String content){this.content = content;}
        public void setPhotoPath(String photoPath){this.photoPath = photoPath;}
        public void setCreatedDate(String createdDate){this.createdDate = createdDate;}
        public Long getId(){return id;}
        public String getTitle(){return title;}
        public String getContent(){return content;}
        public String getPhotoPath(){return photoPath;}
        public String getCreatedDate(){return createdDate;}
    }

    @Nullable
    @Override
    public ListView onCreateView(LayoutInflater inflater, ViewGroup container,
                                 Bundle savedInstanceState) {
        //프래그먼트 뷰로 보여주기
        view = (ListView)inflater.inflate(R.layout.fragment_title, container, false);
        lAdapter = new MyListAdapter(getActivity());
        view.setAdapter(lAdapter);
        return view;
    }

    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        fetchImageData();//서버에서 데이터 가져오기
    }
    private void fetchImageData() {
        String serverUrl = "http://10.0.2.2:8080/info/loadAll";//이쪽으로 요청 보낼거

        OkHttpClient client = new OkHttpClient();
        //요청 생성해서
        Request request = new Request.Builder()
                .url(serverUrl)
                .build();
        //요청 보내고
        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                e.printStackTrace();//실패시 예외처리
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                if (response.isSuccessful()) {
                    //응답 성공했으면
                    String json = response.body().string();
                    dtoList = parseDTOListFromJson(json);//json 파싱해서 리스트에 저장

                    // UI 업데이트할때 스레드를 필요로 하면
                    requireActivity().runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            updateGridViewWithData(dtoList);
                        }
                    });
                } else {

                }
            }
        });
    }
    private List<DTO> parseDTOListFromJson(String json) {
        List<DTO> dtoList = new ArrayList<>();
        //json형식으로 온 데이터를 dtolist에 저장하기 위한 파싱 작업
        //dto의 각 필드마다 다 변환해서 넣어주기
        try {
            JSONArray jsonArray = new JSONArray(json);
            for (int i = 0; i < jsonArray.length(); i++) {
                JSONObject jsonObject = jsonArray.getJSONObject(i);

                DTO dto = new DTO();
                dto.setId(jsonObject.getLong("id"));
                dto.setTitle(jsonObject.getString("title"));
                dto.setContent(jsonObject.getString("content"));
                dto.setPhotoPath(jsonObject.getString("photoPath"));
                dto.setCreatedDate(jsonObject.getString("createdDate"));

                dtoList.add(dto);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }

        return dtoList;
    }

    private void updateGridViewWithData(List<DTO> dtoList) {
        lAdapter.setDTOList(dtoList);
        lAdapter.notifyDataSetChanged();
    }
    //리스트뷰 어댑터 dtoList 기반으로 뷰 형성
    public class MyListAdapter extends BaseAdapter {
        Context context;
        List<DTO> dtoList;

        public MyListAdapter(Context c){
            context = c;
        }
        public void setDTOList(List<DTO> dtoList) {
            this.dtoList = dtoList;
        }
        public int getCount(){
            return dtoList != null ? dtoList.size() : 0;
        }
        public Object getItem(int position){
            return dtoList != null ? dtoList.get(position) : null;
        }
        public long getItemId(int position){
            return position;
        }
        public View getView(int position,View convertView,ViewGroup parent){
            TextView textView;
            if (convertView == null) {
                textView = new TextView(context);
            } else {
                textView = (TextView) convertView;
            }
            textView.setText(dtoList.get(position).getTitle());
            textView.setTextSize(58);
            //게시물을 클릭하면 리스너 동작
            textView.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View v)
                {
                    //인텐트로 상세 페이지인 Article 액티비티를 실행하게 되고 필요한 정보를 번들에 담아서 보내기
                    Intent intent = new Intent(getActivity().getApplicationContext(),Article.class);
                    Bundle bundle = new Bundle();
                    bundle.putLong("id",dtoList.get(position).getId());
                    bundle.putString("title",dtoList.get(position).getTitle());
                    bundle.putString("content",dtoList.get(position).getContent());
                    bundle.putString("photoPath",dtoList.get(position).getPhotoPath());
                    intent.putExtras(bundle);
                    startActivity(intent);
                }
            });
            return textView;
        }
    }

}