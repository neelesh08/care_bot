package com.example.stealth.sign;

import static android.content.Context.MODE_PRIVATE;

import android.app.ProgressDialog;
import android.content.SharedPreferences;
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
import android.widget.CompoundButton;
import android.widget.Toast;

import com.example.stealth.R;
import com.example.stealth.databinding.FragmentLogInBinding;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;

import java.util.regex.Pattern;


public class LogInFragment extends Fragment {
    private static final Pattern PASSWORD_PATTERN =
            Pattern.compile("^" +
                    //"(?=.*[0-9])" +         //at least 1 digit
                    //"(?=.*[a-z])" +         //at least 1 lower case letter
                    //"(?=.*[A-Z])" +         //at least 1 upper case letter
                    "(?=.*[a-zA-Z])" +      //any letter
                    "(?=.*[@#$%^&+=])" +    //at least 1 special character
                    "(?=\\S+$)" +           //no white spaces
                    ".{4,}" +               //at least 4 characters
                    "$");
    FragmentLogInBinding binding;
    FirebaseAuth uAuth;


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        binding = FragmentLogInBinding.inflate(getLayoutInflater());
        return binding.getRoot();
    }
    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        NavController navController = Navigation.findNavController(view);
        uAuth = FirebaseAuth.getInstance();
        binding.forgotPassword.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                navController.navigate(R.id.action_logInFragment_to_forgotPasswordFragment);
            }
        });
        binding.createAccount.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                navController.navigate(R.id.action_logInFragment_to_signInFragment);
            }
        });
        SharedPreferences preferences = getActivity().getSharedPreferences("checkbox", MODE_PRIVATE);
        String checkbox = preferences.getString("remember", "");
        if (checkbox.equals("true")) {
            navController.navigate(R.id.action_logInFragment_to_afterSignActivity);
        }
        binding.rememberMe.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

                boolean b1 = validateEmail();
                boolean b2 = validatePassword();
                if (b1 && b2) {
                    if (buttonView.isChecked()) {
                        SharedPreferences preferences = getActivity().getSharedPreferences("checkbox", MODE_PRIVATE);
                        SharedPreferences.Editor editor = preferences.edit();
                        editor.putString("remember", "true");
                        editor.apply();

                    } else if (!buttonView.isChecked()) {

                        SharedPreferences preferences = getActivity().getSharedPreferences("checkbox", MODE_PRIVATE);
                        SharedPreferences.Editor editor = preferences.edit();
                        editor.putString("remember", "false");
                        editor.apply();

                    }

                }
            }

        });
        binding.loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String Email= binding.loginEmail.getEditText().getText().toString().trim();
                String Password= binding.loginPassword.getEditText().getText().toString().trim();
                if(!validateEmail() | !validatePassword()){
                    Toast.makeText(getActivity(), "Enter valid credentials", Toast.LENGTH_SHORT).show();
                }
                else{
                    final ProgressDialog progressDialog = new ProgressDialog(getActivity());
                    progressDialog.setTitle("Login");
                    progressDialog.setMessage("Please wait, while we are login to your account");
                    progressDialog.show();
                    uAuth.signInWithEmailAndPassword(Email,Password).addOnCompleteListener(new OnCompleteListener<AuthResult>() {
                        @Override
                        public void onComplete(@NonNull Task<AuthResult> task) {
                            if(task.isSuccessful()){
                                Toast.makeText(getActivity(), "Login Successful",Toast.LENGTH_SHORT).show();
                                navController.navigate(R.id.action_logInFragment_to_walkThroughScreen);
                                progressDialog.dismiss();

                            }
                            else{
                                Toast.makeText(getActivity(), "Error!:"+task.getException().getMessage(),Toast.LENGTH_SHORT).show();
                                progressDialog.dismiss();
                            }
                        }
                    });
                }
            }
        });
    }
    private boolean validatePassword() {
        String passwordInput = binding.loginPassword.getEditText().getText().toString().trim();
        if (passwordInput.isEmpty()) {
            binding.loginPassword.setError("Field can't be empty");
            return false;
        } else if (!PASSWORD_PATTERN.matcher(passwordInput).matches()) {
            binding.loginPassword.setError("Password too weak");
            return false;
        } else {
            binding.loginPassword.setError(null);
            return true;
        }
    }
    private boolean validateEmail() {
        String emailInput = binding.loginEmail.getEditText().getText().toString().trim();

        if (emailInput.isEmpty()){
            binding.loginEmail.setError("Field can't be empty");
            return false;
        } else if (!Patterns.EMAIL_ADDRESS.matcher(emailInput).matches()) {
            binding.loginEmail.setError("Please enter a valid email address");
            return false;
        } else {
            binding.loginEmail.setError(null);
            return true;
        }
    }

}