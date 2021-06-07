#include "pch.h"
#include "CppUnitTest.h"
#include "../DevTask/DevTask.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(TestLineIntersect)
		{
			Line* line1 = new Line();
			line1->set(Point(-1, -1), Point(1, 1));
			Line* line2 = new Line();
			line2->set(Point(-1, 1), Point(1, -1));
			Point actualResult = Point();
			intersect(line1, line2, actualResult);
			Point expectedResult = Point(0, 0);
			Assert::AreEqual(expectedResult.x, actualResult.x);
			Assert::AreEqual(expectedResult.y, actualResult.y);
		}

		TEST_METHOD(TestBoundingBox)
		{
			BaseObject* triangle = factory(3);
			Point point1(2.0, 2.0);
			Point point2(6.0, 0);
			Point point3(5.0, 6.0);
			((Triangle*)triangle)->set(point1, point2, point3);
			Rect* expectedRect = new Rect();
			Point point4(2.0, 0);
			Point point5(6.0, 6.0);
			expectedRect->set(point4, point5);
			Rect* actualRect = new Rect();
			actualRect = boundingBox(triangle, 3);
			Point* expectedArr = expectedRect->getPoints();
			Point* actualArr = actualRect->getPoints();
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(expectedArr[i].x, actualArr[i].x);
				Assert::AreEqual(expectedArr[i].y, actualArr[i].y);
			}
		}

		TEST_METHOD(TestBoundingBoxMinimum)
		{
			BaseObject* triangle = factory(3);
			Point point1(1.0, 1.0);
			Point point2(3.0, 3.0);
			Point point3(4.0, 2.0);
			((Triangle*)triangle)->set(point1, point2, point3);
			Rect* expectedRect = new Rect();
			Point point4(1.0, 1.0);
			Point point5(0.600, 2.2);
			Point point6(3.6, 3.2);
			Point point7(4.0, 2.0);
			expectedRect->set(point4, point5, point6, point7);
			Rect* actualRect = new Rect();
			actualRect = boundingBoxMinimum(triangle, 3);
			Point* expectedArr = expectedRect->getPoints();
			Point* actualArr = actualRect->getPoints();
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(float(expectedArr[i].x), float(actualArr[i].x));
				Assert::AreEqual(float(expectedArr[i].y), float(actualArr[i].y));
			}
		}
	};
}
