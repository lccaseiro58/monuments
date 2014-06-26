package com.example.prjmonument;

import org.opencv.core.Mat;

public class NativeServer {
	public void resultado(Mat input, Mat server, String url){
		nativeRes(input.getNativeObjAddr(),server.getNativeObjAddr(),url);
	}
	public native String nativeRes(long input,long server, String url);

}
