package com.example.stealth;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.stealth.databinding.FragmentCityWTBinding;
import com.example.stealth.databinding.FragmentNameWTBinding;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;


public class CityWTFragment extends Fragment {
    FragmentCityWTBinding binding;
    private FirebaseAuth uAuth;
    private DatabaseReference databaseReference;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
            binding =FragmentCityWTBinding.inflate(getLayoutInflater());
            return binding.getRoot();
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        uAuth = FirebaseAuth.getInstance();
        databaseReference = FirebaseDatabase.getInstance().getReference().child("User");
        NavController navController = Navigation.findNavController(view);
        binding.Bengaluru.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Bengaluru");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.Mumbai.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Mumbai");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.NewDelhi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","NewDelhi");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.Kolkata.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Kolkata");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.Chennai.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Chennai");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.Hyderabad.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Hyderabad");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.Ahmedabad.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Ahmedabad");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.Surat.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Surat");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.Pune.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Pune");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.Lucknow.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Lucknow");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.Kanpur.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Kanpur");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });
        binding.Jaipur.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("City","Jaipur");
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);
            }
        });


        binding.buttonNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                navController.navigate(R.id.action_cityWTFragment_to_genderWTFragment);

            }
        });
        binding.buttonBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                navController.navigate(R.id.action_cityWTFragment_to_nameWTFragment);
            }
        });
    }
}