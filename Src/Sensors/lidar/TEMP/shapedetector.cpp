#include "shapedetector.h"

ShapeDetector::ShapeDetector()
{
}

ShapeDetector::~ShapeDetector()
{

}

void ShapeDetector::writeCirclesToConsole(const vector<Circle> circles){
	std::cout << "found circles: " << (circles.size()) << std::endl << std::endl;
	for (Circle c : circles){ // walk through the circles
		std::cout << "(" << c.getCircle().originX << "," << c.getCircle().originY << ")    \t" << c.getCircle().radius << "\n\n";
	}
}

void ShapeDetector::drawCircles(const std::vector<Circle> circles, Mat & image){
	for (Circle c : circles){ //Walk through all the circles
		// round the floats to an int
		cv::Point center(c.getCircle().originX, c.getCircle().originY);
		int radius = c.getCircle().radius;

		// draw the circle center
		circle(image, center, CIRCLE_CENTER_RADIUS, CIRCLE_CENTER_COLOR, CENTER_THICKNESS, CIRCLE_LINE_TYPE);
		// draw the circle outline
		circle(image, center, radius, CIRCUMFERENCE_COLOR, CIRCLE_THICKNESS, CIRCLE_LINE_TYPE);
	}
	//Show Image with the detected circles
}

std::vector<Circle> ShapeDetector::detectCircles(const Mat & image){
	Mat newImage = image.clone();
	Mat frame;
	cv::GaussianBlur(newImage, frame, cv::Size(0, 0), 3);
	cv::addWeighted(frame, 100, newImage, -100, 10, newImage);
	IplImage img = newImage;

	IplImage* gray = cvCreateImage(cvGetSize(&img), IPL_DEPTH_8U, 1); // create a new image with only black and white pixels
	CvMemStorage* storage = cvCreateMemStorage(0);

	cvCvtColor(&img, gray, CV_BGR2GRAY); // transform the created image into the black/white image

	cvSmooth(gray, gray, CV_GAUSSIAN, SMOOTH, SMOOTH); // This is done so as to prevent a lot of false circles from being detected
	IplImage* canny = cvCreateImage(cvGetSize(&img), IPL_DEPTH_8U, 1); // Create a image which will only contain the edges of the objects
	cvCanny(gray, canny, EDGE_TRESHHOLD, EDGE_TRESHHOLD); // Detect edges int he image

	CvSeq* circles = cvHoughCircles(gray, storage, CV_HOUGH_GRADIENT, RESOLUTION_INVERSERATIO, gray->height / MIN_DISTANCE_CIRCLES, EDGE_TRESHHOLD * 3, CIRCLE_CENTER_TRESHHOLD); // Detect circles in the gray image
	std::vector<Circle> newCircles;
	for (int i = 0; i < circles->total; i++) // walk through the circles
	{
		// round the floats to an int
		std::cout << "Circle " << i + 1 << std::endl;
		float* p = (float*)cvGetSeqElem(circles, i);
		Circle c(cvRound(p[0]), cvRound(p[1]), cvRound(p[2]));
		newCircles.push_back(c);
	}
	return newCircles;
}

bool ShapeDetector::callCvSmooth(const Mat & m_src, const Mat & m_dest, const int smooth_type, const int param1, const int param2) {
	if (m_src.empty()) {
		return false;
	}
	IplImage src = m_src;
	IplImage dst = m_dest;
	cvSmooth(&src, &dst, smooth_type, param1, param2);
	return true;
}

Mat ShapeDetector::createImage(Pointcloud & source, int DEVIDEIMAGESIZE){
	int minX = source.getMinValues().X;
	int minY = source.getMinValues().Y;
	size_t imageHeight = source.getCloudHeight();
	size_t imageWidth = source.getCloudWidth();
		std::cout << imageHeight << " width: " << imageWidth << std::endl;

	Mat mat((int)(imageWidth / DEVIDEIMAGESIZE)+1, (int)(imageHeight / DEVIDEIMAGESIZE)+1, CV_8UC1); //Create a Mat object which will represent the image with all the pixels
	imwrite("output2.jpg", mat);
	std::cout << " first forloop from creatimage" ;
	for (int y = 0; y < imageHeight; ++y){
		for (int x = 0; x < imageWidth; ++x){
			mat.at<uchar>(Point((int)(y / DEVIDEIMAGESIZE),(int)( x / DEVIDEIMAGESIZE))) = BLACK_PIXEL;
		}
	}
	imwrite("output4.jpg", mat);
	int i = 0;
	std::cout << "second forloop from creatcircle" ;
	for (Pointcloud::Point p : *source.getPoints()){
		//std::cout << i << " + " << p.X << " + " << p.Y << " +++ " << p.Y + (abs(minY)) << " +++ " <<  p.X + (abs(minX)) << " ++++ " << imageHeight << " ++++ " << imageWidth << "\n";
		std::cout << (int) ((p.Y + abs(minY+1)) / DEVIDEIMAGESIZE) << " && " << (int)((p.X + abs(minX+1)) / DEVIDEIMAGESIZE) << "\n";
		i++;
		mat.at<uchar>(Point( (int) ((p.Y + abs(minY+1)) / DEVIDEIMAGESIZE), (int)((p.X + abs(minX+1)) / DEVIDEIMAGESIZE))) = WHITE_PIXEL;
	}
	std::cout << " save image in createcircle" ;
	imwrite("FINALIMAGE2.jpg", mat); // save the 
	imwrite("output.jpg",mat);
	Mat image(imread("FINALIMAGE2.jpg")); //read and return the image
	return image;
}

void ShapeDetector::checkLines(std::vector<Line> & lines) {
	for(int i = 0; i < lines.size(); ++i){
		for (auto it = lines.begin(); it != lines.end();){
			int value = lines[i].intersect(*it);
			if (value != 0 && value != 100) {
				//std::cout << value << "\n";
			}
			if(value > 95){
				if (lines[i].getLength() >= (*it).getLength()){
					if (!(lines[i].getLine().begin_pos == it->getLine().begin_pos && lines[i].getLine().end_pos == it->getLine().end_pos)){
						it = lines.erase(it);
					}
				}
			}
			++it;
		}
	}
}

vector<Line> ShapeDetector::searchLines(const Mat & image) {

	if (image.empty()) { //check if there is an image
		std::cout << "could not read image" << std::endl;
		exit(-1);
	}
	Mat newImage = image.clone();
	Mat frame;

	
	blur(newImage, frame, Size(5, 5), Point(-1, -1));
	cv::addWeighted(frame, 10, newImage, -10, 0, newImage);            								
	imwrite("lines1.jpg", frame);
	imwrite("lines2.jpg", newImage);
	Mat dest;
	
	imwrite("lines3.jpg", newImage);
	Canny(newImage, dest, CANNY_THRESHHOLD1, CANNY_THRESHHOLD2); //extracts the egdes of an image
	imwrite("linesdest1.jpg", dest);
	vector<Vec4i> lines;  // container to save the lines
	cvtColor(newImage, newImage, CV_RGB2GRAY);
	HoughLinesP(newImage, lines, HOUGHLINES_RHO, HOUGHLINES_THETA, HOUGHLINES_THRESHHOLD,			
		HOUGHLINES_MINLINELENGTH, HOUGHLINES_MAXLINEGAP);  //search the lines

	
	vector<Line> newLines;
	for (Vec4i line : lines){
		Line::Point begin{ (float)line[0],  (float)line[1] };
		Line::Point end{ (float)line[2], (float)line[3] };
		Line newLine(begin,end);
		newLines.push_back(newLine);
	}
	std::cout << "tot hier gaat het goed\n";
	//checkLines(newLines); //check for double lines
	//checkLines(newLines); //check for double lines
	std::cout << "tot hier gaat het ook nog goed\n";
	return newLines;  // return the saved lines
}

void ShapeDetector::writeLinesToConsole(const vector<Line> & lines){
	std::stringstream stream;
	stream << "found lines: " << lines.size() << std::endl << std::endl;
	int i = 0;
	for (Line l : lines) {
		stream << "line " << i + 1 << std::endl;
		stream << "(x1, y1) (" << l.getLine().begin_pos.x << ',' << l.getLine().begin_pos.y << ')' << std::endl;
		stream << "(x2, y2) (" << l.getLine().end_pos.x << ',' << l.getLine().end_pos.y << ')' << std::endl << std::endl;
		++i;
	}
	std::cout << stream.str();
}

void ShapeDetector::drawLines(const std::vector<Line> lines, Mat & final_dest) {
	for (Line l : lines){
		l.getLine().end_pos.x;
		line(final_dest, Point(l.getLine().begin_pos.x, l.getLine().begin_pos.y), Point(l.getLine().end_pos.x, l.getLine().end_pos.y), LINECOLOR, THICKNESS, CV_AA);
	}
}

void ShapeDetector::writeObjectsToConsole(const std::vector<Line> & lines, const std::vector<Circle> circles) {
	writeCirclesToConsole(circles);
	writeLinesToConsole(lines);
}

void ShapeDetector::showObjects(const vector<Line> & lines, const std::vector<Circle> circles, const Mat & orginal_image, Mat & custom_image){
	drawLines(lines, custom_image);
	imwrite("newImage.png",custom_image);
	drawCircles(circles, custom_image);
	imshow("orginal image", orginal_image);
	imshow("detected lines & circles", custom_image);
}
