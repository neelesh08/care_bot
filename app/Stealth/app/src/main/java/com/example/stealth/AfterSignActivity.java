package com.example.stealth;

import androidx.appcompat.app.AppCompatActivity;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.NavigationUI;

import android.os.Bundle;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;

import com.example.stealth.models.profileModels;
import com.google.android.material.bottomnavigation.BottomNavigationView;

public class AfterSignActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_after_sign);
        View fragment = findViewById(R.id.navHostFragment);
        BottomNavigationView bottomNavigationView = findViewById(R.id.bottomNavigationView);
        NavController navController = Navigation.findNavController(this, R.id.navHostFragment);
        NavigationUI.setupWithNavController(bottomNavigationView, navController);
        fragment.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bottomNavigationView.setVisibility(View.VISIBLE);
            }
        });
        fragment.setOnTouchListener(new View.OnTouchListener() {
            GestureDetector gestureDetector = new GestureDetector(getApplicationContext(), new GestureDetector.SimpleOnGestureListener() {
                @Override
                public boolean onDoubleTapEvent(MotionEvent e) {
                    bottomNavigationView.setVisibility(View.GONE);
                    return super.onDoubleTapEvent(e);
                }

                @Override
                public boolean onDoubleTap(MotionEvent e) {
                    bottomNavigationView.setVisibility(View.GONE);
                    return super.onDoubleTap(e);

                }
            });

            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                gestureDetector.onTouchEvent(motionEvent);

                return false;
            }
        });
    }
}