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
import com.example.stealth.databinding.FragmentSignInBinding;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseAuthUserCollisionException;

import java.util.regex.Pattern;


public class SignInFragment extends Fragment {
    private static final Pattern PASSWORD_PATTERN =
            Pattern.compile("^" +
                    "(?=.*[0-9])" +         //at least 1 digit
                    "(?=.*[a-z])" +         //at least 1 lower case letter
                    "(?=.*[A-Z])" +         //at least 1 upper case letter
                    //"(?=.*[a-zA-Z])" +      //any letter
                    "(?=.*[@#$%^&+=])" +    //at least 1 special character
                    "(?=\\S+$)" +           //no white spaces
                    ".{4,}" +               //at least 4 characters
                    "$");
    FragmentSignInBinding binding;
    FirebaseAuth uAuth;



    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        binding = FragmentSignInBinding.inflate(getLayoutInflater());
        return binding.getRoot();
    }
    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        uAuth = FirebaseAuth.getInstance();
        binding.toolbar.setNavigationIcon(R.drawable.ic_back);
        NavController navController = Navigation.findNavController(view);
        binding.toolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                navController.navigate(R.id.action_signInFragment_to_logInFragment);

            }
        });
        binding.buttonSignUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String email = binding.signEmail.getEditText().getText().toString().trim();
                String password = binding.signPassword.getEditText().getText().toString().trim();
                if (validateEmail() && validatePassword()) {
                    Toast.makeText(getActivity(), "Fields are invalid", Toast.LENGTH_SHORT).show();

                } else {
                    final ProgressDialog progressDialog = new ProgressDialog(getActivity());
                    progressDialog.setTitle("Signing in");
                    progressDialog.setMessage("Please wait,while we are creating your account");
                    progressDialog.show();
                    uAuth.createUserWithEmailAndPassword(email,password).addOnCompleteListener(new OnCompleteListener<AuthResult>() {
                        public void onComplete(@NonNull Task<AuthResult> task) {
                            if (task.isSuccessful()) {
                                Toast.makeText(getActivity(), "SignUp Successful",Toast.LENGTH_SHORT).show();
                                navController.navigate(R.id.action_signInFragment_to_logInFragment);
                                progressDialog.dismiss();
                            }
                            else if (task.getException() instanceof FirebaseAuthUserCollisionException) {
                                Toast.makeText(getActivity(),
                                        "User already exist.", Toast.LENGTH_SHORT).show();
                                progressDialog.dismiss();
                            }

                            else{
                                Toast.makeText(getActivity(), "Error!:"+task.getException().getMessage(), Toast.LENGTH_SHORT).show();
                                progressDialog.dismiss();
                            }
                        }
                    });


                }

            }
        });

    }
    private boolean validatePassword() {
        String passwordInput = binding.signPassword.getEditText().getText().toString().trim();
        if (passwordInput.isEmpty()) {
            binding.signPassword.setError("Field can't be empty");
            return true;
        } else if (!PASSWORD_PATTERN.matcher(passwordInput).matches()) {
            binding.signPassword.setError("Password too weak");
            return true;
        }
        else {
            binding.signPassword.setError(null);
            return false;
        }
    }

    private boolean validateEmail() {
        String emailInput = binding.signEmail.getEditText().getText().toString().trim();

        if (emailInput.isEmpty()) {
            binding.signEmail.setError("Field can't be empty");
            return true;
        } else if (!Patterns.EMAIL_ADDRESS.matcher(emailInput).matches()) {
            binding.signEmail.setError("Please enter a valid email address");
            return true;
        } else {
            binding.signEmail.setError(null);
            return false;
        }
    }
}