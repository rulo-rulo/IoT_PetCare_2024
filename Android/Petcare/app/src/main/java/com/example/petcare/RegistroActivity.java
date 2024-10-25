package com.example.petcare;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.auth.AuthResult;

public class RegistroActivity extends AppCompatActivity {

    private EditText nombreEditText, apellidosEditText, correoEditText, contraseñaEditText;
    private Button registerButton;
    private FirebaseAuth mAuth;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.registro);

        // Inicializa Firebase Auth
        mAuth = FirebaseAuth.getInstance();

        nombreEditText = findViewById(R.id.nombre);
        apellidosEditText = findViewById(R.id.apellidos);
        correoEditText = findViewById(R.id.correo);
        contraseñaEditText = findViewById(R.id.contraseña);
        registerButton = findViewById(R.id.register);

        registerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                registrarUsuario();
            }
        });
    }

    private void registrarUsuario() {
        String nombre = nombreEditText.getText().toString().trim();
        String apellidos = apellidosEditText.getText().toString().trim();
        String correo = correoEditText.getText().toString().trim();
        String contraseña = contraseñaEditText.getText().toString().trim();

        // Validación de campos
        if (nombre.isEmpty() || apellidos.isEmpty() || correo.isEmpty() || contraseña.isEmpty()) {
            Toast.makeText(this, "Por favor, rellena los campos", Toast.LENGTH_SHORT).show();
            return;
        }

        // Registro en Firebase
        mAuth.createUserWithEmailAndPassword(correo, contraseña)
                .addOnCompleteListener(this, new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {
                        if (task.isSuccessful()) {
                            // Registro exitoso
                            FirebaseUser user = mAuth.getCurrentUser();
                            Toast.makeText(RegistroActivity.this, "Registro completado", Toast.LENGTH_SHORT).show();
                            // Puedes redirigir al usuario a otra actividad aquí
                        } else {
                            // Si el registro falla, muestra un mensaje al usuario.
                            Toast.makeText(RegistroActivity.this, "Error al registrarse", Toast.LENGTH_SHORT).show();
                        }
                    }
                });
        TextView iniciarText = findViewById(R.id.IniciarSesion);
        iniciarText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(RegistroActivity.this, "Abriendo pantalla de inicio de sesión...", Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(RegistroActivity.this, IniciarSesionActivity.class);
                startActivity(intent);
            }
        });
    }
}