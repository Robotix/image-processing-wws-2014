// ComputerVision.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>                            //INCLUDED FOR CANNY


using namespace std;
using namespace cv;
//using namespace Mat;

Mat Glayscale(Mat image);
Mat Binary(Mat image);
int treshold(Mat image);
Mat Histogram(Mat img);
Mat Borderer(Mat image);
Mat Borderpro(Mat image);
int mod(int l);
Mat dilation(Mat image);
int count(int p, int q, int r, int s, int t, int u, int v, int w, int x);
Mat Erosion(Mat image);
Mat Mean(Mat image);
int Avg(int a, int b, int c, int d, int e, int f, int g, int h, int i);
int sortedmed(int a, int b, int c, int d, int e, int f, int g, int h, int i);

int diff(int a, int b, int c, int d, int e, int f, int g, int h, int i);
Mat Medianed(Mat image);
Mat Gaussed(Mat image);

//***************************************************************************

int main()
{
	Mat image;      
	//int A[256];
	image = imread("E:\\Photos\\Scenery\\image.jpg");

	Mat img(image.rows, image.cols, CV_8UC1);       //GRAYSCALE
	Mat img2(image.rows, image.cols, CV_8UC1);      //HISTOGRAM
	Mat img3(image.rows, image.cols, CV_8UC1);      //BORDER
	Mat img4(image.rows, image.cols, CV_8UC1);      //BINARY
	Mat img5(image.rows, image.cols, CV_8UC1);      //BORDER_PRO
	//Mat img6(image.rows, image.cols, CV_8UC1);
	Mat img7(image.rows, image.cols, CV_8UC1);      //DILATION
	Mat img8(image.rows, image.cols, CV_8UC1);      //EROSION
	Mat img9(image.rows, image.cols, CV_8UC1);
	Mat img10(image.rows, image.cols, CV_8UC1);
	Mat img11(image.rows, image.cols, CV_8UC1);
	Mat img12(image.rows, image.cols, CV_8UC1);

	
	img = Glayscale(image);
	img2 = Histogram(image);
	img3 = Borderer(img);
	img4 = Binary(img);
	img5 = Borderpro(img);
	//img6 = Borderpro(img5);
	img7 = dilation(img4);
	img8 = Erosion(img7);
	img9 = Mean(img);
	img10 = Medianed(img);
	img11 = Gaussed(img);
	int y = treshold(img);
	Canny(img,img12, 25, 96);
	//namedWindow("Histogram", WINDOW_AUTOSIZE);  
	//imshow("Histogram", img2);
	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", img);
	namedWindow("Binary", WINDOW_AUTOSIZE);
	imshow("Binary", img4);
	//namedWindow("Border", WINDOW_AUTOSIZE);
	//imshow("Border", img3);
	namedWindow("Dilated", WINDOW_AUTOSIZE);
	imshow("Dilated", img7);
	//namedWindow("Erosion", WINDOW_AUTOSIZE);
	//imshow("Erosion", img8);
	namedWindow("Meaned", WINDOW_AUTOSIZE);
	imshow("Meaned", img9);
	//cout << "*******************" << sortedmed(1, 2, 3, 4, 5, 6, 7, 8, 9);
	namedWindow("Medianed", WINDOW_AUTOSIZE);
	imshow("Medianed", img10);
	namedWindow("Gaussed", WINDOW_AUTOSIZE);
	imshow("Gaussed", img11);
	namedWindow("Canny", WINDOW_AUTOSIZE);
	imshow("Canny", img12);
	waitKey(0);
}

//*****************************************************************************************
Mat Glayscale(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < image.cols; i++)               //Grayscaling
	{
		for (int j = 0; j < image.rows; j++)
		{
			img.at<uchar>(j, i) = 0.56*(image.at<Vec3b>(j, i)[0]) + 0.33*(image.at<Vec3b>(j, i)[1]) + 0.11*(image.at<Vec3b>(j, i)[2]);
		}
	}
	return img;
}

//*****************************************************************************************
Mat Binary(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1);
	int u = treshold(image);
	for (int i = 0; i < image.cols; i++)
	{
		for (int j = 0; j < image.rows; j++)
		{
			if(image.at<uchar>(j, i)>=u)
		    {
				img.at<uchar>(j, i) = 255;
		    }
		    else
		    {
				img.at<uchar>(j, i) = 0;
			}
		}
	}
	return img;
}

//******************************************************************************************
int treshold(Mat image)
{
	int A[256];
	for (int i = 0; i < 256; i++)
		A[i] = 0;
	for (int i = 0; i < image.cols; i++)
	{
		for (int j = 0; j < image.rows; j++)
		{
			A[image.at<uchar>(j, i)]++;
		}
	}

	int k = image.rows*image.cols / 2;
	int count = 0;
	int d;
	for (d = 0; d < 256; d++)
	{
		count = count + A[d];
		if (count >= k)
			break;
	}

	return d;

}

//**********************************************************************************************

Mat Histogram(Mat img)
{
	int A[256];
	for (int i = 0; i < 256; i++)
		A[i] = 0;
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			A[img.at<uchar>(j, i)]++;
		}
	}

	for (int i = 0; i < 256; i++)
		A[i] = A[i] / 100;
	
	Mat iml(img.rows, img.cols, CV_8UC1);
	for (int i = 0; i < iml.cols; i++)
	for (int j = 0; j < iml.rows; j++)
	{
		iml.at<uchar>(j, i) = 255;
	}
	for (int i = 0; i < 256; i++)
	{
		for (; A[i]>0; A[i]--)
		{
			iml.at<uchar>(iml.rows - A[i],i ) = 0;
		}
	}
	return iml;
}

//***********************************************************************************************

Mat Borderer(Mat image)
{
	
	
	Mat imres(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < imres.cols;i++)
	for (int j = 0; j < imres.rows; j++)
	{
		imres.at<uchar>(j, i) = 255;
	}

	for (int i = 1; i < imres.cols - 1; i++)
	for (int j = 1; j < imres.rows - 1; j++)
	{
		//int avgb = treshold(image);
		//int minb = min(image.at<uchar>(j, i));
		//int diff = maxb - minb;
		if (diff(image.at<uchar>(j, i), image.at<uchar>(j - 1, i - 1), image.at<uchar>(j - 1, i), image.at<uchar>(j, i - 1), image.at<uchar>(j - 1, i + 1), image.at<uchar>(j + 1, i - 1), image.at<uchar>(j + 1, i + 1), image.at<uchar>(j + 1, i), image.at<uchar>(j, i + 1)) <= 45)
			imres.at<uchar>(j, i) = 0;
	}

	return imres;
	
	
}

//***************************************************************************************

int diff(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
	int B[9];
	B[0] = a; B[1] = b; B[2] = c; B[3] = d; B[4] = e; B[5] = f; B[6] = g; B[7] = h; B[8] = i;
	int max = 0;
	int min = a;
	for (int k = 0; k < 9; k++)
	{
		if (B[k]>max)
			max = B[k];
	}

	for (int k = 0; k < 9; k++)
	{
		if (B[k]<min)
			min = B[k];
	}
	
	int diffl = max - min;
	return diffl;
	
}

//**********************************************************************************************

Mat Borderpro(Mat image)
{
	 Mat impro(image.rows, image.cols, CV_8UC1);
	 for (int i = 1; i < impro.cols - 1; i++)
	 for (int j = 1; j < impro.rows - 1; j++)
	 {
		int p = mod(image.at<uchar>(j - 1, i + 1) + image.at<uchar>(j, i + 1) + image.at<uchar>(j + 1, i + 1) - image.at<uchar>(j - 1, i - 1) - image.at<uchar>(j, i - 1) - image.at<uchar>(j + 1, i - 1));
		int q = mod(-image.at<uchar>(j - 1, i + 1) + image.at<uchar>(j + 1, i) + image.at<uchar>(j + 1, i + 1) - image.at<uchar>(j - 1, i - 1) - image.at<uchar>(j - 1, i) + image.at<uchar>(j + 1, i - 1));
		impro.at<uchar>(j, i) = sqrt(q*p*100);
		// if (impro.at<uchar>(j, i)>45)
		//	 impro.at<uchar>(j, i) = 0;
		// else
		//	 impro.at<uchar>(j, i) = 255;	 
	 }

	 return impro;
	 
}

//********************************************************************************************

int mod(int l)
{
	int p;
	p = l;
	if (l < 0)
		p = -l;
	return l;
}

//********************************************************************************************
Mat dilation(Mat image)
{
	Mat imr(image.rows, image.cols, CV_8UC1);
	for (int i = 1; i < imr.cols - 1; i++)
	for (int j = 1; j < imr.rows - 1; j++)
	{
		if (count(image.at<uchar>(j, i), image.at<uchar>(j - 1, i - 1), image.at<uchar>(j - 1, i), image.at<uchar>(j - 1, i + 1), image.at<uchar>(j, i - 1), image.at<uchar>(j, i + 1), image.at<uchar>(j + 1, i - 1), image.at<uchar>(j + 1, i), image.at<uchar>(j + 1, i + 1)))
			imr.at<uchar>(j, i) = 0;
		else
			imr.at<uchar>(j, i) = 255;
	}
	return imr;
}

//***********************************************************************************

int count(int p, int q, int r, int s, int t, int u, int v, int w, int x)
{
	int B[9];
	int c1 = 0;
	int	c2 = 0;
	B[0] = p; B[1] = q; B[2] = r; B[3] = s; B[4] = t; B[5] = u; B[6] = v; B[7] = w; B[8] = x;
	for (int i = 0; i < 9; i++)
	{
		if (B[i] == 0)
			c1++;
		else
			c2++;

	}
	if (c1>c2)
		return 1;
	else 
		return 0;
}

//**********************************************************************************
Mat Erosion(Mat image)
{
	Mat imr(image.rows, image.cols, CV_8UC1);
	for (int i = 1; i < imr.cols - 1; i++)
	for (int j = 1; j < imr.rows - 1; j++)
	{
		if (count(image.at<uchar>(j, i), image.at<uchar>(j - 1, i - 1), image.at<uchar>(j - 1, i), image.at<uchar>(j - 1, i + 1), image.at<uchar>(j, i - 1), image.at<uchar>(j, i + 1), image.at<uchar>(j + 1, i - 1), image.at<uchar>(j + 1, i), image.at<uchar>(j + 1, i + 1)))
			imr.at<uchar>(j, i) = 255;
		else
			imr.at<uchar>(j, i) = 0;
	}
	return imr;
}

//*********************************************************************************

Mat Mean(Mat image)
{
	Mat imr(image.rows, image.cols, CV_8UC1);
	for (int i = 1; i < imr.cols - 1; i++)
	for (int j = 1; j < imr.rows - 1; j++)
	{
		imr.at<uchar>(j, i) = Avg(image.at<uchar>(j, i) , image.at<uchar>(j - 1, i - 1) , image.at<uchar>(j - 1, i) , image.at<uchar>(j, i - 1) , image.at<uchar>(j - 1, i + 1) , image.at<uchar>(j + 1, i - 1) , image.at<uchar>(j + 1, i) ,image.at<uchar>(j, i + 1) , image.at<uchar>(j + 1, i + 1));
	}
	return imr;
}

//***************************************************************************

int Avg(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
	int B[9];
	B[0] = a; B[1] = b; B[2] = c; B[3] = d; B[4] = e; B[5] = f; B[6] = g; B[7] = h; B[8] = i;
	int p = 0;
	for (int i = 0; i < 9; i++)
	{
		p =p+ B[i];
	}
	p = p / 9;
	return p;
}

//*********************************************************************

Mat Medianed(Mat image)
{
	Mat imr(image.rows, image.cols, CV_8UC1);
	for (int i = 1; i < imr.cols - 1; i++)
	for (int j = 1; j < imr.rows - 1; j++)
	{
		imr.at<uchar>(j, i) = sortedmed(image.at<uchar>(j, i), image.at<uchar>(j - 1, i - 1), image.at<uchar>(j - 1, i), image.at<uchar>(j - 1, i + 1), image.at<uchar>(j, i - 1), image.at<uchar>(j, i + 1), image.at<uchar>(j + 1, i - 1), image.at<uchar>(j + 1, i), image.at<uchar>(j + 1, i + 1));
	}

	return imr;
}

//**********************************************************************

int sortedmed(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
	int B[9];
	B[0] = a; B[1] = b; B[2] = c; B[3] = d; B[4] = e; B[5] = f; B[6] = g; B[7] = h; B[8] = i;
	int A[5];
	for (int j = 0; j < 5; j++)
	{
		int max = 0;
		for (int i = 0; i < 9; i++)
		{
			if (B[i]>max)
				max = B[i];
		}
		A[j] = max;
		for (int i = 0; i < 9; i++)
		{
			if (max == B[i])
			{
				B[i] = 0;
				break;
			}
		}
	}
	return A[4];
}
//***********************************************************************

Mat Gaussed(Mat image)
{
	Mat imr(image.rows, image.cols, CV_8UC1);
	for (int i = 1; i < imr.cols - 1; i++)
	for (int j = 1; j < imr.rows - 1; j++)
	{
		imr.at<uchar>(j, i) = 0.06*(image.at<uchar>(j - 1, i - 1) + image.at<uchar>(j - 1, i + 1) + image.at<uchar>(j + 1, i + 1) + image.at<uchar>(j + 1, i - 1)) + 0.098*(image.at<uchar>(j - 1, i) + image.at<uchar>(j + 1, i) + image.at<uchar>(j, i - 1) + image.at<uchar>(j, i + 1)) + 0.168*(image.at<uchar>(j, i));

	}
	return imr;
}