package com.example.stealth;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;

import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;

import com.example.stealth.databinding.FragmentGenderWTBinding;
import com.example.stealth.databinding.FragmentHealthBinding;
import com.example.stealth.databinding.FragmentHeightWTBinding;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;


public class HeightWTFragment extends Fragment {
    FragmentHeightWTBinding binding;
    private FirebaseAuth uAuth;
    private DatabaseReference databaseReference;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
         binding =   FragmentHeightWTBinding.inflate(getLayoutInflater());
        return binding.getRoot();
    }
    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        uAuth = FirebaseAuth.getInstance();
        databaseReference = FirebaseDatabase.getInstance().getReference().child("User");
        NavController navController = Navigation.findNavController(view);
        binding.heightPicker.setMinValue(50);
        binding.heightPicker.setMaxValue(300);
        binding.heightPicker.setValue(100);
        binding.buttonNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int heightValue = binding.heightPicker.getValue();
                HashMap<String ,Object> height = new HashMap<>();
                height.put("height",heightValue);
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(height);
                navController.navigate(R.id.action_heightWTFragment_to_weightWTFragment);
            }
        });
        binding.buttonBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                navController.navigate(R.id.action_heightWTFragment_to_DOBMTFragment2);
            }
        });

    }
}