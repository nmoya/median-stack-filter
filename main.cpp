#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Create a displacement vector to access the adjacent pixels. An
// adjacent pixel q is computed by:
// q = p + displacement
vector<Point> create_adjacency8() {
  vector<Point> adjacency;
  adjacency.push_back(Point(0, 0));
  adjacency.push_back(Point(1, 0));
  adjacency.push_back(Point(1, -1));
  adjacency.push_back(Point(0, -1));
  adjacency.push_back(Point(-1, -1));
  adjacency.push_back(Point(-1, 0));
  adjacency.push_back(Point(-1, 1));
  adjacency.push_back(Point(0, 1));
  adjacency.push_back(Point(1, 1));
  return adjacency;
}

// Returns whether a point p is inside the image domain
bool valid_point(const Mat img, const Point p) {
  Rect r = Rect(0, 0, img.cols, img.rows);
  return p.inside(r);
}

// Sort function between two integers
bool sortFn(int i, int j) { return (i < j); }

// Given a sorted array, returns the median value
float median(vector<int> values) {
  int middle = (int)(values.size() / 2) - 1;
  if (values.size() % 2 == 0) {
    return (values[middle] + values[middle + 1]) / 2.0;
  } else {
    return values[middle];
  }
}

// Wrapper function around median to ensure the array is sorted
int median_filter(vector<int> values) {
  sort(values.begin(), values.end(), sortFn); // in-place sort
  return (int)median(values);
}

// Same as medianBlur(mat, 3) from opencv (educational purposes only)
Mat my_median_filter(const Mat image) {
  CV_Assert(image.depth() == CV_8U);
  vector<Point> adjacents = create_adjacency8();
  vector<int> adjacency_values;
  Mat filtered = Mat::zeros(image.size(), CV_8U);
  Point p, q;
  int i, j, k;

  for (i = 0; i < image.rows; i++) {
    for (j = 0; j < image.cols; j++) {
      p = Point(j, i);
      adjacency_values.clear();
      for (k = 0; k < adjacents.size(); k++) {
        q = p + adjacents[k];
        if (valid_point(image, q)) {
          adjacency_values.push_back(image.at<uchar>(q));
        }
      }
      filtered.at<uchar>(p) = median_filter(adjacency_values);
    }
  }
  return filtered;
}

// median_stack function for grayscale images
Mat median_stack(vector<Mat> imgs) {
  CV_Assert(imgs[0].channels() == 1);
  int rows = imgs[0].rows;
  int cols = imgs[0].cols;
  Mat output = Mat::zeros(imgs[0].size(), CV_8U);
  int i, j, k;
  Point p;
  vector<int> values;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      p = Point(j, i);
      values.clear();
      for (k = 0; k < imgs.size(); k++) {
        values.push_back(imgs[k].at<uchar>(p));
      }
      output.at<uchar>(p) = median_filter(values);
    }
  }
  return output;
}

// median stack function for color images
Mat median_stack_color(vector<Mat> imgs) {
  int rows = imgs[0].rows;
  int cols = imgs[0].cols;
  int num_channels = imgs[0].channels();
  CV_Assert(num_channels == 3);
  Mat output = Mat(imgs[0].size(), CV_8UC3, Scalar(0, 0, 0));
  int i, j, k, channel;
  Point p;
  vector<int> values;
  Vec3b filteredValue;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      p = Point(j, i);
      for (channel = 0; channel < num_channels; channel++) {
        values.clear();
        for (k = 0; k < imgs.size(); k++) {
          values.push_back((int)imgs[k].at<Vec3b>(p)[channel]);
        }
        filteredValue[channel] = median_filter(values);
      }
      output.at<Vec3b>(p) = filteredValue;
    }
  }
  return output;
}

int main(int argc, char **argv) {
  vector<Mat> imgs;
  Mat img, cvtImg;
  char *folder = argv[1];
  for (int i = 0;; i++) {
    char buffer[255];
    sprintf(buffer, "%s%d.jpg", folder, i);
    img = imread(buffer, CV_LOAD_IMAGE_COLOR);
    if (img.empty()) {
      sprintf(buffer, "%s%d.jpg", folder, i - 1);
      cout << "Last image loaded: " << buffer << endl;
      break;
    }
    cvtColor(img, img, CV_BGR2HSV);
    // comment the line below for original image size output
    resize(img, img, Size(1024, 768), 0, 0, INTER_LINEAR);
    imgs.push_back(img);
  }
  Mat filteredCvtImage = median_stack_color(imgs);
  cvtColor(filteredCvtImage, filteredCvtImage, CV_HSV2BGR);
  imshow("Media stack color", filteredCvtImage);

  waitKey();
  return 0;
}