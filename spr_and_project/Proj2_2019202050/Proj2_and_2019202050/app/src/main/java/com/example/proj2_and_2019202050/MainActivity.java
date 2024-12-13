package com.example.proj2_and_2019202050;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

import com.google.android.material.bottomnavigation.BottomNavigationView;

public class MainActivity extends AppCompatActivity {

    private BottomNavigationView BottomNV;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        BottomNV = findViewById(R.id.nav_view);
        //밑에 네비게이션뷰를 눌렀을 때
        BottomNV.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem menuItem) {
                BottomNavigate(menuItem.getItemId());//누른 버튼 id값 전달
                return true;
            }
        });
        BottomNV.setSelectedItemId(R.id.navigation_1);
        //add 버튼을 눌렀을 때 업로드 액티비티로 이동할 수 있게끔 함
        Button UploadButton = (Button) findViewById(R.id.UploadButton);
        UploadButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(),Upload.class);
                startActivity(intent);
            }
        });
    }

    private void BottomNavigate(int id){
        String tag = String.valueOf(id);
        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();

        Fragment currentFragment = fragmentManager.getPrimaryNavigationFragment();
        if (currentFragment != null) {
            fragmentTransaction.remove(currentFragment);//현재 프래그먼트를 제거함
        }

        Fragment fragment = fragmentManager.findFragmentByTag(tag);
        if (fragment == null) {
            if (id == R.id.navigation_1) {
                fragment = new GalleryFragment();

            } else if (id == R.id.navigation_2){

                fragment = new TitleFragment();
            }else {
                fragment = new SettingsFragment();
            }

            fragmentTransaction.add(R.id.content_layout, fragment, tag);//프래그먼트 새로 추가
        } else {
            fragmentTransaction.show(fragment);//화면에 보여주기
        }

        fragmentTransaction.setPrimaryNavigationFragment(fragment);
        fragmentTransaction.setReorderingAllowed(true);
        fragmentTransaction.commitNow();
    }
}