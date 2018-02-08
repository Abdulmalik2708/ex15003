#ifndef SPAWINDOW_HPP_
#define SPAWINDOW_HPP_

#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_draw.h>
#include <vector>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 500
#endif

#ifndef M_E
#define M_E 500
#endif

namespace SPA {
class Point   {
public:
	Point(float x = 0, float y = 0) :
			x(x), y(y) {
		;
	}
	float x;
	float y;
};

class Line {
public:
	Line() {
		;
	}
	void addPoint(Point p) {
		points.push_back(p);
	}
	void clear() {
		points.clear();
	}
	void draw() {
		fl_begin_line();
		for (int i = 0, n = points.size(); i < n; ++i) {
			Point & p = points[i];
			fl_vertex(round(p.x), round(p.y));
		}
		fl_end_line();

	}
	int size() {
		return points.size();
	}

private:
	std::vector<Point> points;
};

class Window: public Fl_Window {
public:
	Window(int w, int h, const char * l = 0) :
			Fl_Window(h, w, l), currentLine(), currentPoint(0, 0), currentAngle(
					0) {
	}

	~Window();

	void draw() {
		for (int i = 0, n = lines.size(); i < n; ++i) {
			Line & l = lines[i];
			l.draw();
		}
	}

    void display() {
        show(0,0);
    }

	void addPoint(double x, double y) {
		if (currentLine.size() == 0) {
			// start a new line
			startNewLine(round(x), round(y));
		} else {
			Point p(round(x), round(y));
			currentPoint = p;
			currentLine.addPoint(p);
		}
	}

	void startNewLine(int x, int y) {
		if (currentLine.size() > 0) {
			stopCurrentLine();
		}
		//
		currentLine.clear();
		currentPoint.x = x;
		currentPoint.y = y;
		currentLine.addPoint(currentPoint);
	}

	void stopCurrentLine() {
		lines.push_back(currentLine);
		currentLine.clear();
	}

	void penSetAngle(float angle) {
		currentAngle = angle * M_PI / 180.;
	}

	void penForward(float l) {
		Point p;
		p.x = currentPoint.x + l * std::cos(currentAngle);
		p.y = currentPoint.y + l * std::sin(currentAngle);
		currentPoint = p;
		currentLine.addPoint(p);
	}

	// a clockwise rotation
	void penRotateDegrees(float angle) {
		float radians = angle * M_PI / 180.;
		currentAngle += radians;
	}

private:
	std::vector<Line> lines;
	Line currentLine;
	Point currentPoint;
	float currentAngle;
};

}

#endif /* SPAWINDOW_HPP_ */
