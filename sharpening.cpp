/* #include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;



int main()
{
	Mat image = imread("lena.jpg");
	Mat new_image;
	new_image.create(image.size(), image.type());

	int a,b,c,d,output;
	cout << "Enter a: " << endl; cin >> a;
	cout << "Enter b: " << endl; cin >> b;
	cout << "Enter c: " << endl; cin >> c;
	cout << "Enter d: " << endl; cin >> d;

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) { 
			for (int w = 0; w < 3; w++)
			{
				int value = image.at<Vec3b>(i, j)[w];


				if (0 <= value && value <= a)
					output = (int)(c / a * value);
				else if (a < value && value <= b)
					output = (int)((d - c) / (b - a) * (value - a) + c);
				else if (b < value && value <= 255)
					output = (int)((255 - d) / (255 - b) * (value - b) + d);

				new_image.at<Vec3b>(i,j)[w] = output;
			}
			
		}
	}

	namedWindow("Original Image", 1);
	imshow("Original Image", image);

	namedWindow("New Image", 1);
	imshow("New Image", new_image);

	waitKey();

	return 0;
} 
*/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	/* Mat img = imread("lena.jpg",0);
	Mat new_img;
	new_img.create(img.size(), img.type());
	imshow("Original image", img);

	for (int i = 0; i<img.rows; i++)
	{
		for (int j = 0; j<img.cols; j++)
		{
			int value = img.at<uchar>(i, j);
			int output = 255 - value;
			new_img.at<uchar>(i, j) = output;
		}
	}
	imshow("New image", new_img);
	waitKey();

	Mat img1 = imread("lena.jpg", 0);
	Mat new1_img;
	new1_img.create(img1.size(), img1.type());
	imshow("Original image", img1);
	int c;
	double a,g;

	cout << " enter  gamma " << endl; cin >> g;
	for (int i = 0; i<img1.rows; i++)
	{
		for (int j = 0; j<img1.cols; j++)
		{
			int value1 = img1.at<uchar>(i, j);
			a = (double)value1 / 255.0;
			int output1 = pow(a, g) * 255;
			new1_img.at<uchar>(i, j) = output1;
		}
	}
	imshow("New image2", new1_img);
	waitKey();

	*/

		Mat img = imread("lena.jpg", 0);
		Mat imp = imread("m.png", 0);
		float min = 1000.0, max = -1000.0;
		Mat new_img3, maximg, minimg, lap, lapt, new_image, img3, input, scale;
		new_img3.create(img.size(), img.type());
		maximg.create(img.size(), img.type());
		minimg.create(img.size(), img.type());
		lap.create(imp.size(), imp.type());
		lapt.create(imp.size(), imp.type());
		scale.create(imp.size(), CV_32FC1);
		//imshow("Original image", img);
		//waitKey();
		int sum, t1 = 0;
		int a[10];
		cv::copyMakeBorder(img, img3, 1, 1,
			1, 1, 0);
		cv::copyMakeBorder(imp, input, 1, 1,
			1, 1, 0);
		for (int x = 1; x<img.rows; x++)
		{
			uchar * s = new_img3.ptr<uchar>(x);
			uchar * t = maximg.ptr<uchar>(x);
			uchar * u = minimg.ptr<uchar>(x);

			for (int y = 1; y<img.cols; y++)
			{
				t1 = 0;
				sum = 0;
				for (int i = -1; i <= 1; i++)
				{
					uchar *p = img3.ptr<uchar>(x + i);

					for (int j = -1; j <= 1; j++)
					{
						sum = p[y + j];
						a[t1] = sum;
						t1++;
					}
				}
				sort(a, a + 9);
				s[y] = a[4];
				t[y] = a[8];
				u[y] = a[0];
			}
		}
		/*imshow("Median image", new_img3);
		waitKey();
		imshow("Max image", maximg);
		waitKey();
		imshow("Min image", minimg);
		waitKey(); */

		for (int x = 1; x < imp.rows; x++)
		{
			uchar * in = input.ptr<uchar>(x);
			float * sc = scale.ptr<float>(x);
			uchar * lap1 = lap.ptr<uchar>(x);
			uchar * lapt1 = lapt.ptr<uchar>(x);
			uchar * in1 = input.ptr<uchar>(x - 1);
			uchar * in2 = input.ptr<uchar>(x + 1);

			for (int y = 1; y < imp.cols; y++)
			{
				int r = 8 * in[y] - (in2[y] + in1[y] + in[y + 1] + in[y - 1] + in1[y - 1] + in2[y + 1] + in1[y + 1] + in2[y - 1]);
				if (r < min) min = r;
				if (r > max) max = r;
				sc[y] = r;
				if (r < 0)  r = 0;
				if (r > 255) r = 255;
				lapt1[y] = r;
				int q = in[y] + r;
				if (q < 0) q = 0;
				if (q > 255) q = 255;
				lap1[y] = q;
			}
		}
		for (int x = 1; x < imp.rows; x++)
		{
			float * sc = scale.ptr<float>(x);
			uchar * in = lapt.ptr<uchar>(x);


			for (int y = 1; y < imp.cols; y++)
			{
				sc[y] = sc[y] - min;
				
				if (sc[y] > max) max = sc[y];
			}
		}

		for (int x = 1; x < imp.rows; x++)
		{
			float * sc = scale.ptr<float>(x);
			uchar * in = lapt.ptr<uchar>(x);


			for (int y = 1; y < imp.cols; y++)
			{
				sc[y] = sc[y] / max;
			

			}
		}

		imshow("Original image", imp);
		waitKey();
		imshow("sharpness image", lapt);
		waitKey();

		imshow("scale image", scale);
		waitKey();
		imshow("sharpen Image", lap);
		waitKey();
	

}

/*
#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;


int main()
{

	

	const double PI = 3.1416;
	double sigma = 2;
	const int maskrow = 5;
	const int maskcol = 5;

	float mask[maskrow][maskcol];

	double total = 0;

	
	for (int row = 0; row<maskrow; row++) {

		for (int col = 0; col<maskcol; col++) {

			float value = (1 / (2 * PI*pow(sigma, 2)))*exp(-(pow(row - maskrow / 2, 2) + pow(col - maskcol / 2, 2)) / (2 * pow(sigma, 2)));

			mask[row][col] = value;
			// cout << value << " ";
			total += value;
		}
		cout << endl;
	}
	cout << "mask weights : " << endl;
	for (int row = 0; row<maskrow; row++) {
		for (int col = 0; col < maskcol; col++) {

			mask[row][col] = mask[row][col] / total;
			cout << mask[row][col] << " ";

		}
		cout << endl;
	}



	Mat Image;

	Image = imread("lena.jpg",0);

	Mat FilterImage;
	FilterImage.create(Image.size(),Image.type());



	int rows = Image.rows;
	int cols = Image.cols;


	int rowstart = (maskrow - 1) / 2;
	int colstart = (maskcol - 1) / 2;

	

	for (int row = rowstart; row<rows - rowstart; row++) {
	      uchar *ptr1 = FilterImage.ptr<uchar>(row);
		for (int col = colstart; col<cols - colstart; col++) {

			float value = 0.0;

			for (int mRow = 0; mRow<maskrow; mRow++) {
				uchar *ptr = Image.ptr<uchar>(mRow + row - rowstart);
				for (int mCol = 0; mCol<maskcol; mCol++) {
					uchar pix = ptr[mCol + col - colstart];
			
					float pixel = pix *mask[mRow][mCol];
					value += pixel;
				}
			}
			
			ptr1[col]= cvRound(value);

		}

	}

	

	namedWindow("Original Image", 1);
	imshow("Original Image", Image);

	namedWindow("Filtered Image", 1);
	imshow("Filtered Image", FilterImage);

	waitKey();
	return 0;
} 

*/
/*
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

uchar gaussin_index(int x, int y, float sigma)
{
	float temp = 2 * 3.1416*(sigma*sigma);
	float temp2 = ((x*x) + (y*y)) / (2 * sigma*sigma);
	float e = 2.71828;
	temp2 = pow(e, -temp2);
	return temp2 / temp;
}




int main()
{
	Mat img = imread("lena.jpg", 0);
	imshow("start", img);
	waitKey(0);
	int r = img.rows;
	int c = img.cols;
	float sig;
	cout << "Enter sigma: ";
	cin >> sig;
	int f_size = 5 * sig;
	int l_size = f_size / 2;
	Mat img2 = img;


	for (int x = 0; x < r; x++) {


		uchar *ptr1 = img2.ptr<uchar>(x);

		for (int y = 0; y < c; y++) {

			float val = 0.0;
			for (int i = -l_size; i <= l_size; i++) {
				//const double* Mi = img.ptr<double>(i);
				uchar *ptr = img.ptr<uchar>(i + x);
				for (int j = -l_size; j <= l_size; j++) {


					if (i + x < 0 || i + x >= r || j + y < 0 || j + y >= c) {
						val = val + 0;
					}
					else {
						uchar temp = ptr[j + y];
						//int temp = img.at<uchar>(i + x, j + y);
						//int temp = Mi[j];
						temp = temp*gaussin_index(i, j, sig);
						val = val + temp;

					}
				}
			}
			ptr1[y] = cvRound(val);
			//img2.at<uchar>(x, y) = val;
		}
	}
	for (int i = -l_size; i <= l_size; i++) {
		for (int j = -l_size; j <= l_size; j++) {
			cout << gaussin_index(i, j, sig) << " ";
		}
		cout << endl;
	}
	imshow("second", img2);
	waitKey(0);




	return 0;
}

*/














