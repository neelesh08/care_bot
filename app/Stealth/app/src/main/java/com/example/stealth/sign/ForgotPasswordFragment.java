package com.example.stealth.sign;

import android.app.ProgressDialog;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;

import android.util.Patterns;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.example.stealth.R;
import com.example.stealth.databinding.FragmentForgotPasswordBinding;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.FirebaseAuth;


public class ForgotPasswordFragment extends Fragment {
    FragmentForgotPasswordBinding binding;
    FirebaseAuth uAuth;


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        binding =   FragmentForgotPasswordBinding.inflate(getLayoutInflater());
        return binding.getRoot();
    }
    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        NavController navController = Navigation.findNavController(view);
        uAuth = FirebaseAuth.getInstance();
        binding.forgotPasswordButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String forgotEmail = binding.forgotPasswordEmail.getEditText().getText().toString().trim();
                if(forgotEmail.isEmpty()){
                    binding.forgotPasswordEmail.setError("field can't be empty");

                }
                else if (!Patterns.EMAIL_ADDRESS.matcher(forgotEmail).matches()){
                    binding.forgotPasswordEmail.setError("invalid email id");

                }
                else{
                    final ProgressDialog progressDialog = new ProgressDialog(getActivity());
                    progressDialog.setTitle("Signing in");
                    progressDialog.setMessage("Please wait,while we are creating your account");
                    progressDialog.show();
                    FirebaseAuth auth = FirebaseAuth.getInstance();
                    auth.sendPasswordResetEmail(forgotEmail)
                            .addOnCompleteListener(new OnCompleteListener<Void>() {
                                @Override
                                public void onComplete(@NonNull Task<Void> task) {
                                    if(task.isSuccessful()){
                                        Toast.makeText(getActivity(), "Check your email", Toast.LENGTH_SHORT).show();
                                        navController.navigate(R.id.action_forgotPasswordFragment_to_logInFragment);
                                    }
                                    else{
                                        Toast.makeText(getActivity(), "Error!:"+task.getException().getMessage(), Toast.LENGTH_SHORT).show();
                                    }
                                    progressDialog.dismiss();

                                }
                            });
                }

            }
        });

    }
}