package com.example.petcare;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

public class IniciarSesionActivity extends AppCompatActivity {

    private EditText correoEditText;
    private EditText contraseñaEditText;
    private Button loginButton;
    private FirebaseAuth mAuth;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.iniciar_sesion);

        // Inicializa Firebase Auth
        mAuth = FirebaseAuth.getInstance();

        // Referencia a los elementos del layout
        correoEditText = findViewById(R.id.correo);
        contraseñaEditText = findViewById(R.id.contraseña);
        loginButton = findViewById(R.id.login);

        // Configura el clic del botón de inicio de sesión
        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                iniciarSesion();
            }
        });
    }

    private void iniciarSesion() {
        String correo = correoEditText.getText().toString().trim();
        String contraseña = contraseñaEditText.getText().toString().trim();

        // Verifica que los campos no estén vacíos
        if (correo.isEmpty() || contraseña.isEmpty()) {
            Toast.makeText(IniciarSesionActivity.this, "Por favor, completa todos los campos", Toast.LENGTH_SHORT).show();
            return;
        }

        // Inicia sesión con Firebase
        mAuth.signInWithEmailAndPassword(correo, contraseña)
                .addOnCompleteListener(this, task -> {
                    if (task.isSuccessful()) {
                        // Inicio de sesión exitoso, redirige a la actividad "Acerca_de"
                        Intent intent = new Intent(IniciarSesionActivity.this, AcercaDeActivity.class);
                        startActivity(intent);
                        finish(); // Opcional: finaliza la actividad de inicio de sesión
                    } else {
                        // Si el inicio de sesión falla, muestra un toast
                        Toast.makeText(IniciarSesionActivity.this, "Datos incorrectos", Toast.LENGTH_SHORT).show();
                    }
                });
    }
}