package com.example.stealth;

import static android.content.Context.MODE_PRIVATE;

import android.app.Activity;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.viewpager2.widget.ViewPager2;

import android.util.Patterns;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import com.example.stealth.databinding.FragmentForgotPasswordBinding;
import com.example.stealth.databinding.FragmentNameWTBinding;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;


public class NameWTFragment extends Fragment {
    FragmentNameWTBinding binding;
    private int currentValue =1 ;
    private FirebaseAuth uAuth;
    private DatabaseReference databaseReference;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        binding = FragmentNameWTBinding.inflate(getLayoutInflater());
        return binding.getRoot();
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        NavController navController = Navigation.findNavController(view);
        uAuth = FirebaseAuth.getInstance();
        databaseReference = FirebaseDatabase.getInstance().getReference().child("User");
        binding.buttonNext.setEnabled(true);
        binding.buttonNext.setTextColor(Color.WHITE);
        binding.buttonNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("name",binding.nickName.getText().toString());
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_nameWTFragment_to_cityWTFragment);
            }
        });

    }

}