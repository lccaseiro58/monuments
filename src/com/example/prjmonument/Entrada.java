package com.example.prjmonument;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

public class Entrada extends Activity {

	public void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_entrada);
		Handler handler = new Handler();
		handler.postDelayed(new Runnable(){
			public void run(){
				startActivity(new Intent(getApplicationContext(),MainActivity.class));
				Entrada.this.finish();
			}
		},
				5000);
		
	}

}