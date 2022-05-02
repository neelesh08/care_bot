package com.example.stealth.profile;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentTransaction;

import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.ViewConfiguration;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.NumberPicker;
import android.widget.RadioButton;
import android.widget.Toast;

import com.example.stealth.R;
import com.example.stealth.databinding.ActivityEditProfileBinding;
import com.example.stealth.models.profileModels;
import com.google.android.gms.tasks.Continuation;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.StorageReference;
import com.google.firebase.storage.StorageTask;
import com.squareup.picasso.Picasso;
import com.theartofdev.edmodo.cropper.CropImage;
import com.theartofdev.edmodo.cropper.CropImageView;

import java.util.Calendar;
import java.util.HashMap;

public class editProfileActivity extends AppCompatActivity {
    ActivityEditProfileBinding binding;
    private profileModels profileModels;
    private FirebaseAuth uAuth;
    private DatabaseReference databaseReference;
    private Uri imageUri;
    private String myUri = "";
    private StorageTask uploadTask;
    private StorageReference storageProfilePicsRef;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityEditProfileBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        uAuth = FirebaseAuth.getInstance();
        //binding.toolbar.setNavigationIcon(R.drawable.ic_back);
        binding.backPressed.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
             onBackPressed();
            }
        });
        databaseReference = FirebaseDatabase.getInstance().getReference().child("User");
        storageProfilePicsRef = FirebaseStorage.getInstance().getReference().child("Profile Pic");
        binding.weightCard.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                weightDialog();
            }
        });
        binding.heightCard.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                heightDialog();
            }
        });
        //////////uidUpdate/////////
        String uid = uAuth.getUid();
        HashMap<String ,Object> uidMAP = new HashMap<>();
        uidMAP.put("uid",uid);
        databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(uidMAP);

        ///////user id///////////////////
        binding.idNo.setText(uAuth.getCurrentUser().getUid());
        binding.idCard.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                idCopied();
            }
        });
        ////////birthdate/////////
        binding.birthDateCard.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });
        binding.genderCard.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                genderDialog();
            }
        });


        ///setPic/////
        binding.profilePictureCard.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                CropImage.activity()
                        .setGuidelines(CropImageView.Guidelines.ON)
                        .start(editProfileActivity.this);
            }
        });
        binding.nickNameCard.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                nicknameDialog();
            }
        });
        getProfileImageInfo();
        getNameInfo();
        getHeightInfo();
        getWeightInfo();
        getBirthOfDateInfo();
    }

    private void getProfileImageInfo(){
        databaseReference.child(uAuth.getCurrentUser().getUid()).addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                if(snapshot.exists() && snapshot.getChildrenCount()>0){
                    if(snapshot.hasChild("profileImage")){
                            String image = snapshot.child("profileImage").getValue().toString();
                            Picasso.get().load(image).into(binding.profileEditedPic);
                    }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

    }
    private void getNameInfo(){
        databaseReference.child(uAuth.getCurrentUser().getUid()).addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                if(snapshot.exists() && snapshot.getChildrenCount()>0){
                    if(snapshot.hasChild("name")){
                        String name = snapshot.child("name").getValue().toString();
                        binding.nickNameText.setText(name);
                    }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

    }
    private void getHeightInfo(){
        databaseReference.child(uAuth.getCurrentUser().getUid()).addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                if(snapshot.exists() && snapshot.getChildrenCount()>0){
                    if(snapshot.hasChild("height")){
                        String height = snapshot.child("height").getValue().toString();
                        binding.heightText.setText(height + " Cm");
                    }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

    }
    private void getWeightInfo(){
        databaseReference.child(uAuth.getCurrentUser().getUid()).addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                if(snapshot.exists() && snapshot.getChildrenCount()>0){
                    if(snapshot.hasChild("weight")){
                        String weight = snapshot.child("weight").getValue().toString();
                        binding.weightText.setText(weight);

                    }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }
    private void getBirthOfDateInfo(){
        databaseReference.child(uAuth.getCurrentUser().getUid()).addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                if(snapshot.exists() && snapshot.getChildrenCount()>0){
                    if(snapshot.hasChild("dateOfBirth")){
                        String dateOfBirth = snapshot.child("dateOfBirth").getValue().toString();
                        binding.birthDateText.setText(dateOfBirth);

                    }
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }
    /////setPic///////

    private void  uploadProfileImage() {
        final ProgressDialog progressDialog = new ProgressDialog(this);
        progressDialog.setTitle("set your profile");
        progressDialog.setMessage("Please wait, while we are setting you data");
        progressDialog.show();
        if (imageUri!=null){
            final StorageReference fileRef = storageProfilePicsRef.child(uAuth.getCurrentUser().getUid()+".jpeg");
            uploadTask = fileRef.putFile(imageUri);
            uploadTask.continueWithTask(new Continuation() {
                @Override
                public Object then(@NonNull Task task) throws Exception {
                    if(!task.isSuccessful()){
                        throw task.getException();
                    }
                    return fileRef.getDownloadUrl();
                }
            }).addOnCompleteListener((OnCompleteListener<Uri>) task -> {
                if (task.isSuccessful()){
                    Uri downloadUrl = task.getResult();
                    myUri = downloadUrl.toString();
                    HashMap<String ,Object> userMap = new HashMap<>();
                    userMap.put("profileImage",myUri);
                    databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);

                }
                progressDialog.dismiss();
            });
        }
    }
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == CropImage.CROP_IMAGE_ACTIVITY_REQUEST_CODE) {
            CropImage.ActivityResult result = CropImage.getActivityResult(data);
            if (resultCode == RESULT_OK) {
                imageUri = result.getUri();
                binding.profileEditedPic.setImageURI(imageUri);
                uploadProfileImage();
            } else if (resultCode == CropImage.CROP_IMAGE_ACTIVITY_RESULT_ERROR_CODE) {
                Exception error = result.getError();
            }
        }
    }
    //////set id///////////
    private void  idCopied(){
        ClipboardManager clipboard = (ClipboardManager) getSystemService(Context.CLIPBOARD_SERVICE);
        ClipData clip = ClipData.newPlainText("id",uAuth.getCurrentUser().getUid());
        clipboard.setPrimaryClip(clip);
        Toast.makeText(this, "copied", Toast.LENGTH_SHORT).show();
    }
    //////////gender////////////////
    private void genderDialog(){
        final Dialog dialog = new Dialog(this);
        dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
        dialog.setContentView(R.layout.gender_dialog);
        RadioButton male = dialog.findViewById(R.id.male);
        RadioButton female = dialog.findViewById(R.id.female);
        Button cancelButton = dialog.findViewById(R.id.genderCancelButton);
        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dialog.dismiss();
            }
        });
        male.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });
        female.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });
        dialog.show();
        dialog.getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT,ViewGroup.LayoutParams.WRAP_CONTENT);
        dialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        dialog.getWindow().getAttributes().windowAnimations = R.style.DialogAnimation;
        dialog.getWindow().setGravity(Gravity.BOTTOM);
    }
    private void nicknameDialog(){
        final Dialog dialog = new Dialog(this);
        dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
        dialog.setContentView(R.layout.name_dialog);
        Button saveButton = dialog.findViewById(R.id.nameSaveButton);
        Button cancelButton = dialog.findViewById(R.id.nameCancelButton);
        EditText nickNameInput = dialog.findViewById(R.id.nickNameInput);
        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                binding.nickNameText.setText(nickNameInput.getText().toString());
                HashMap<String ,Object> userMap = new HashMap<>();
                userMap.put("name",nickNameInput.getText().toString());
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(userMap);
                dialog.dismiss();

            }
        });
        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dialog.dismiss();
            }
        });

        dialog.show();
        dialog.getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT,ViewGroup.LayoutParams.WRAP_CONTENT);
        dialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        dialog.getWindow().getAttributes().windowAnimations = R.style.DialogAnimation;
        dialog.getWindow().setGravity(Gravity.BOTTOM);

    }
    private void weightDialog(){
        final Dialog dialog = new Dialog(this);
        dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
        dialog.setContentView(R.layout.weight_dialog);
        NumberPicker weightNumberPicker = dialog.findViewById(R.id.weightNumberPicker);
        Button saveButton = dialog.findViewById(R.id.weightSaveButton);
        Button cancelButton = dialog.findViewById(R.id.weightCancelButton);
        weightNumberPicker.setMaxValue(242);
        weightNumberPicker.setMinValue(30);
        weightNumberPicker.setValue(50);
        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int weightValue = weightNumberPicker.getValue();
                HashMap<String ,Object> weight = new HashMap<>();
                weight.put("weight",weightValue);
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(weight);
                binding.weightText.setText(weightValue + " Kg");
                dialog.dismiss();
            }
        });
        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dialog.dismiss();
            }
        });
        dialog.show();
        dialog.getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT,ViewGroup.LayoutParams.WRAP_CONTENT);
        dialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        dialog.getWindow().getAttributes().windowAnimations = R.style.DialogAnimation;
        dialog.getWindow().setGravity(Gravity.BOTTOM);
    }
    private void heightDialog(){
        final Dialog dialog = new Dialog(this);
        dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
        dialog.setContentView(R.layout.height_dialog);
        NumberPicker heightNumberPicker = dialog.findViewById(R.id.heightNumberPicker);
        Button saveButton = dialog.findViewById(R.id.heightSaveButton);
        Button cancelButton = dialog.findViewById(R.id.heightCancelButton);
        heightNumberPicker.setMaxValue(242);
        heightNumberPicker.setMinValue(30);
        heightNumberPicker.setValue(50);
        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int heightValue = heightNumberPicker.getValue();
                HashMap<String ,Object> height = new HashMap<>();
                height.put("height",heightValue);
                databaseReference.child(uAuth.getCurrentUser().getUid()).updateChildren(height);
                binding.heightText.setText(heightValue + " Cm");
                dialog.dismiss();
            }
        });
        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dialog.dismiss();
            }
        });
        dialog.show();
        dialog.getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT,ViewGroup.LayoutParams.WRAP_CONTENT);
        dialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        dialog.getWindow().getAttributes().windowAnimations = R.style.DialogAnimation;
        dialog.getWindow().setGravity(Gravity.BOTTOM);

    }

}