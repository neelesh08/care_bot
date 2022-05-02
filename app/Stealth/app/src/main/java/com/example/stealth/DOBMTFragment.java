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
import com.example.stealth.databinding.FragmentDOBMTBinding;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;


public class DOBMTFragment extends Fragment {
   FragmentDOBMTBinding binding;
    private FirebaseAuth uAuth;
    private DatabaseReference databaseReference;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
      binding = FragmentDOBMTBinding.inflate(getLayoutInflater());
        return binding.getRoot();
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        uAuth = FirebaseAuth.getInstance();
        databaseReference = FirebaseDatabase.getInstance().getReference().child("User");
        NavController navController = Navigation.findNavController(view);
        binding.agePicker.setMinValue(1);
        binding.agePicker.setMaxValue(101);
        binding.agePicker.setValue(20);

        binding.agePicker.setWrapSelectorWheel(true);
        binding.buttonNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int ageValue = binding.agePicker.getValue();
                HashMap<String ,Object> age = new HashMap<>();
                age.put("Age",ageValue);
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(age);
                navController.navigate(R.id.action_DOBMTFragment_to_heightWTFragment);
            }
        }); binding.buttonBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                navController.navigate(R.id.action_DOBMTFragment_to_genderWTFragment);
            }
        });
    }
}