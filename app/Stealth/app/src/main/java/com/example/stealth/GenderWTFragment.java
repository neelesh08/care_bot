package com.example.stealth;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.viewpager2.widget.ViewPager2;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import com.example.stealth.databinding.FragmentDOBMTBinding;
import com.example.stealth.databinding.FragmentGenderWTBinding;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;


public class GenderWTFragment extends Fragment {
    FragmentGenderWTBinding binding;
    private FirebaseAuth uAuth;
    private DatabaseReference databaseReference;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        binding =  FragmentGenderWTBinding.inflate(getLayoutInflater());
        return binding.getRoot();
    }


    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        NavController navController = Navigation.findNavController(view);
        uAuth = FirebaseAuth.getInstance();
        databaseReference = FirebaseDatabase.getInstance().getReference().child("User");
        binding.maleCard.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("gender","Male");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_genderWTFragment_to_DOBMTFragment);
            }
        });
        binding.femaleCard.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("gender","Female");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_genderWTFragment_to_DOBMTFragment);
            }
        });
        binding.buttonNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                navController.navigate(R.id.action_genderWTFragment_to_DOBMTFragment);
            }
        });
        binding.buttonBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                navController.navigate(R.id.action_genderWTFragment_to_cityWTFragment);
            }
        });

    }
}