package com.example.prjmonument;

import org.opencv.core.Mat;



public class Imagelib {
	
	public long getDescriptorsfromMat(Mat input , Mat result){
		return getNativeDescriptorsfromMat(input.getNativeObjAddr(),result.getNativeObjAddr());
	}
	public native long getNativeDescriptorsfromMat(long image, long result);

}
