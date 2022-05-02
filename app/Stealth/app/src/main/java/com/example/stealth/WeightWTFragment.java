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

import com.example.stealth.databinding.FragmentHealthBinding;
import com.example.stealth.databinding.FragmentWeightWTBinding;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;


public class WeightWTFragment extends Fragment {
    FragmentWeightWTBinding binding;
    private FirebaseAuth uAuth;
    private DatabaseReference databaseReference;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        binding =  FragmentWeightWTBinding.inflate(getLayoutInflater());
        return binding.getRoot();
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        uAuth = FirebaseAuth.getInstance();
        databaseReference = FirebaseDatabase.getInstance().getReference().child("User");
        NavController navController = Navigation.findNavController(view);
        binding.weightNumberPicker.setMinValue(50);
        binding.weightNumberPicker.setMaxValue(300);
        binding.weightNumberPicker.setValue(100);
        binding.weightDecimalPicker.setMinValue(0);
        binding.weightDecimalPicker.setMaxValue(10);
        binding.weightDecimalPicker.setValue(0);
        binding.buttonNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int weightValue = binding.weightNumberPicker.getValue();
                int weightDecimalValue = binding.weightDecimalPicker.getValue();
                String totalWeightString = (weightValue + "." +weightDecimalValue);
                HashMap<String ,Object> weight = new HashMap<>();
                weight.put("weight",totalWeightString);
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(weight);
                navController.navigate(R.id.action_weightWTFragment_to_afterSignActivity2);
            }
        });
        binding.buttonBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                navController.navigate(R.id.action_weightWTFragment_to_heightWTFragment);
            }
        });


    }
}