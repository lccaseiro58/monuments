package com.example.prjmonument;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Mat;
import org.opencv.highgui.Highgui;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.Toast;


public class MainActivity extends Activity implements CvCameraViewListener2 {
	
	private static final String TAG = "Debug::MainActivity";
	final int ACTIVITY_CHOOSE_FILE = 1;
	
	private Mat mRgba = new Mat();
	private Mat result = new Mat();
	private Button takePhoto;
	private Button uploadPhoto;
	private Imagelib nativelib;
	
	static 
    {
	    try
	    { 
	    // Load necessary libraries.
	    	Log.i(TAG, "try to load libs");
	    	System.loadLibrary("opencv_java");
	    	Log.i(TAG, "load libs 1");
            System.loadLibrary("nonfree");
            Log.i(TAG, "load libs 2");
            System.loadLibrary("ndklib");
            Log.i(TAG, "load libs 3");
	    }
	    catch( UnsatisfiedLinkError e )
	    {
	        System.err.println("Native code library failed to load.\n" + e);
	    }
    }
	
	private CameraBridgeViewBase mOpenCvCameraView;

	private BaseLoaderCallback  mLoaderCallback = new BaseLoaderCallback(this){
		@Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                {
                    Log.i(TAG, "OpenCV loaded successfully");
                    mOpenCvCameraView.enableView();
                    Log.i(TAG, "passou");
                    mOpenCvCameraView.enableFpsMeter();
                    
                    
                } break;
                default:
                {
                    super.onManagerConnected(status);
                } break;
            }
        }
		
	};
	
	@Override
    public void onCreate(Bundle savedInstanceState)
    {
        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(R.layout.activity_main);

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.photo);
        mOpenCvCameraView.setCvCameraViewListener(this);
        takePhoto = (Button) findViewById(R.id.take);
        uploadPhoto = (Button)findViewById(R.id.upload);
        takePhoto.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				result = mRgba.clone();
				Mat descriptors = new Mat();
				
				ProgressDialog dialog = ProgressDialog.show(MainActivity.this, "",
						"Processing Image. Please Please wait...", true);
				
				Toast.makeText(getApplicationContext(), "Image sent to server", Toast.LENGTH_LONG).show();
				
				dialog.dismiss();
				
			}
		});
        uploadPhoto.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Intent chooseFile;
				Intent intent;
				chooseFile = new Intent(Intent.ACTION_GET_CONTENT);
				chooseFile.setType("file/*");
				intent = Intent.createChooser(chooseFile, "Choose a file");
				startActivityForResult(intent, ACTIVITY_CHOOSE_FILE);
				
			}
		});
        
    }
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		switch(requestCode) {
			case ACTIVITY_CHOOSE_FILE: {
				if (resultCode == RESULT_OK){
					Uri uri = data.getData();
					String filePath = uri.getPath();
					Mat image= Highgui.imread(filePath);
					result = image.clone();
					Mat descriptors = new Mat();
					ProgressDialog dialog = ProgressDialog.show(MainActivity.this, "",
							"Processing Image. Please Please wait...", true);
					//CalculateDescriptors(result, descriptors);
					Toast.makeText(getApplicationContext(), "Image sent to server", Toast.LENGTH_LONG).show();
					dialog.dismiss();
				}
			}
		}
	}
	
	void CalculateDescriptors(Mat input, Mat result){
		
		nativelib.getDescriptorsfromMat(input, result);
	}
	

	@Override
    public void onPause()
    {
        super.onPause();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    @Override
    public void onResume()
    {
        super.onResume();
        OpenCVLoader.initAsync( OpenCVLoader.OPENCV_VERSION_2_4_8, this, mLoaderCallback );
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        mOpenCvCameraView.disableView();
    }

    @Override
    public void onCameraViewStarted( int width, int height )
    {
        mRgba = new Mat();
    }
    
    @Override
    public void onCameraViewStopped()
    {
        mRgba.release();
    }
	@Override
	public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
		return inputFrame.rgba();
	}

	public Mat getRgba() {
		return mRgba;
	}

	public void setRgba(Mat mRgba) {
		this.mRgba = mRgba;
	}


}
