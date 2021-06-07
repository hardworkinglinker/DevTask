#include <iostream>


struct Point
{
    double x;
    double y;

    Point()
    {
        x = 0.0;
        y = 0.0;
    };

    Point(double x1, double y1)
    {
        x = x1;
        y = y1;
    }
};
class BaseObject
{
public:

    BaseObject()
    {
        center_ = new Point();
    };
    virtual bool isPossible()
    {
        return true;
    };
    virtual Point* getCenter()
    {
        return center_;
    };
    bool isSamePoint(Point p1, Point p2)
    {
        if (p1.x == p2.x && p1.y == p2.y)
            return true;
        else return false;
    }

protected:
    Point* center_;
};
class Rect : public BaseObject
{
public:

    Rect() : BaseObject()
    {
        printf("Rectangle  was created successfully\n");
    };

    void set(Point p1, Point p2, Point p3, Point p4)
    {

        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
        points[3] = p4;

        if (!isPossible())
            printf("Angles of rectangle are not 90 degrees");
    }

    void set(Point p1, Point p3)
    {


        points[0] = p1;
        points[2] = p3;
        points[1] = Point(p1.x, p3.y);
        points[3] = Point(p3.x, p1.y);


        if (!isPossible())
            printf("Angles of rectangle are not 90 degrees");

    }

    Point* getCenter() override
    {
        center_ = new Point(

            ((points[3].x + points[0].x) / 2),
            ((points[1].y + points[0].y) / 2)

        );
        return center_;
    }
    /*checking 90deg angle by vectors*/
    bool is90degrees(Point p1, Point p2, Point p3)
    {
        //the structure op Point and vector is basicly the same so there is no need to overuse our memory
        Point vector1 = Point(p1.x - p2.x, p1.y - p2.y);
        Point vector2 = Point(p3.x - p2.x, p3.y - p2.y);

        if ((vector1.x * vector2.x + vector1.y * vector2.y) == 0)
            return true;
        else return false;
    }

    bool isPossible() override
    {
        //checking 90deg angles of Rec

        if (is90degrees(points[0], points[1], points[2]) &
            is90degrees(points[1], points[2], points[3]) &
            is90degrees(points[2], points[3], points[0]))
            return true;
        else return false;
    }
    /*minimum boundingbox of rectangle is rectangle itself*/

    Point* getPoints() {
        return points;
    }
private:

    Point points[4];


};
class Circle : public BaseObject
{
public:

    Circle()
    {
        printf("Circle was created successfully\n");
    };


    void set(Point p1, double r)
    {
        center_->x = p1.x;
        center_->y = p1.y;
        radius_ = r;
        if (!isPossible())
            printf("Radius cannot be equal or lower than 0");
    }
    //circles can`t have negatiave or 0 radius
    bool isPossible() override
    {
        if (radius_ > 0)
            return true;
        else return false;
    }


    double getRadius()
    {
        return radius_;
    }

private:
    double radius_;
};
class Line : public BaseObject
{
public:

    Line() : BaseObject()
    {
        printf("Line was created successfully\n");
    }


    void set(Point p1, Point p2)
    {
        p1_ = p1;
        p2_ = p2;
        getCoeficients();
        if (!isPossible())
            printf("Line cannot be built on 1 point\n");
    }

    // ax + bx - c = 0

    void getCoeficients()
    {
        a = p1_.y - p2_.y;
        b = p2_.x - p1_.x;
        c = (p1_.x * p2_.y - p2_.x * p1_.y) * -1;

    }

    bool isPossible() override
    {
        return isSamePoint(p1_, p2_);
    }

    double getA()
    {
        return a;
    }

    double getB()
    {
        return b;
    }

    double getC()
    {
        return c;
    }
    Point getFirstPoint()
    {
        return p1_;
    }
    Point getSecondPoint()
    {
        return p2_;
    }
private:

    Point p1_;
    Point p2_;
    double a;
    double b;
    double c;
};
class Triangle : public BaseObject
{
public:

    Triangle()
    {
        printf("Triagle was created successfully\n");
    };

    Point* getPoints()
    {
        return points;
    }

    void set(Point p1, Point p2, Point p3)
    {
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;

        if (!isPossible())
            printf("Points of triangle cannot be the same\n");
    }

    Point* getCenter() override
    {
        center_->x = (points[0].x + points[1].x + points[2].x) / 3;
        center_->y = (points[0].y + points[1].y + points[2].y) / 3;


        return center_;
    }

    bool isPossible() override
    {
        //the only restriction on triangles is for it to have 3 different points
        if (!isSamePoint(points[0], points[1])
            && !isSamePoint(points[1], points[2])
            && !isSamePoint(points[2], points[0]))
            return true;
        else return false;
    }
private:

    Point points[3];
};

/*
num == 1 : create Rect
num == 2 : create Circle
num == 3 : create Triangle
*/
BaseObject* factory(int num)
{
    switch (num)
    {
    case 1:
        return new Rect();
    case 2:
        return new Circle();
    case 3:
        return new Triangle();
    default:
        return  nullptr;
    }
}

bool isParalel(Line* line1, Line* line2)
{
    if (line1->getA() / line2->getA() == line1->getB() / line2->getB())
        return true;
    else return false;
}

bool intersect(Line* line1, Line* line2, Point& intersectionPoint)
{
    double det;

    if (!isParalel(line1, line2))
    {
        det = ((line1->getA() * line2->getB()) - (line2->getA() * line1->getB()));

        intersectionPoint.x = ((line1->getB() * line2->getC()) - (line2->getB() * line1->getC())) / det;
        intersectionPoint.y = ((line2->getA() * line1->getC()) - (line1->getA() * line2->getC())) / det;

        return true;
    }
    else
    {
        return false;
    }
}

Rect* boundingBox(BaseObject* obj, int num);

Rect* boundingBoxMinimum(BaseObject* obj, int num);

void perpendCoeficients(double* arrInput, double* arrOutput, Point p1);

Point pointOfInterseption(double* line1, double* line2);


int main()
{
    {
        BaseObject* pTestFactory = factory(100);
        if (pTestFactory != 0)
            printf("FAIL Factory\n");

        BaseObject* pRect_1 = factory(1);
        Rect* pRect_2 = new Rect();

        BaseObject* pCircle_1 = factory(2);
        Circle* pCircle_2 = new Circle();

        BaseObject* pTriangle_1 = factory(3);
        Triangle* pTriangle_2 = new Triangle();

        {//set rect
            Point p1(1.0, 1.0);
            Point p2(1.0, 5.0);
            Point p3(5.0, 5.0);
            Point p4(5.0, 1.0);
            ((Rect*)pRect_1)->set(p1, p2, p3, p4);
            pRect_2->set(p1, p3);
        }

        {//set triangle
            Point p1(1.0, 1.0);
            Point p2(3.0, 3.0);
            Point p3(4.0, 2.0);
            ((Triangle*)pTriangle_1)->set(p1, p2, p3);
            pTriangle_2->set(p1, p2, p3);
        }

        {//set Circle
            Point p1(1.0, 1.0);
            ((Circle*)pCircle_1)->set(p1, 5.0);
            pCircle_2->set(p1, 5.0);
        }

        if (pRect_1->getCenter()->x != 3.0 || pRect_1->getCenter()->y != 3.0)
            printf("FAIL 1\n");

        if (pRect_2->getCenter()->x != 3.0 || pRect_2->getCenter()->y != 3.0)
            printf("FAIL 2\n");

        if (pCircle_1->getCenter()->x != 1.0 || pCircle_1->getCenter()->y != 1.0)
            printf("FAIL 3\n");

        if (pCircle_2->getCenter()->x != 1.0 || pCircle_2->getCenter()->y != 1.0)
            printf("FAIL 4\n");

        if (std::abs(pTriangle_1->getCenter()->x - 2.6) > 0.1 || pTriangle_1->getCenter()->y != 2.0)
            printf("FAIL 5\n");

        if (std::abs(pTriangle_2->getCenter()->x - 2.6) > 0.1 || pTriangle_2->getCenter()->y != 2.0)
            printf("FAIL 6\n");

        delete pRect_1;
        delete pRect_2;
        delete pCircle_1;
        delete pCircle_2;
        delete pTriangle_1;
        delete pTriangle_2;
    }
    return 0;
}


/*
num == 1 : create Rect
num == 2 : create Circle
num == 3 : create Triangle
*/
Rect* boundingBox(BaseObject* obj, int num)
{
    switch (num)
    {
    case 1:
    {
        Rect* pRect = (Rect*)obj;
        Point points[4];
        double highestX = points[0].x;
        double highestY = points[0].y;
        double lowestX = points[0].x;
        double lowestY = points[0].y;

        for (int i = 1; i < 4; i++)
        {
            if (points[i].x > highestX)
                highestX = points[i].x;
            if (points[i].x < lowestX)
                lowestX = points[i].x;
            if (points[i].y > highestY)
                highestY = points[i].y;
            if (points[i].y < lowestY)
                lowestY = points[i].y;
        }
        Rect* bound = new Rect;
        bound->set(
            Point(lowestX, lowestY),
            Point(lowestX, highestY),
            Point(highestX, highestY),
            Point(highestX, lowestY)
        );
        return bound;
    }
    case 2:
    {
        Circle* pCircl = (Circle*)obj;
        Rect* bounded = new Rect();
        bounded->set(
            Point(pCircl->getCenter()->x - pCircl->getRadius(), pCircl->getCenter()->y - pCircl->getRadius()),
            Point(pCircl->getCenter()->x - pCircl->getRadius(), pCircl->getCenter()->y + pCircl->getRadius()),
            Point(pCircl->getCenter()->x + pCircl->getRadius(), pCircl->getCenter()->y + pCircl->getRadius()),
            Point(pCircl->getCenter()->x + pCircl->getRadius(), pCircl->getCenter()->y - pCircl->getRadius())
        );
        return bounded;
    }
    case 3:
    {
        Triangle* pTri = (Triangle*)obj;
        Point* points = pTri->getPoints();
        double highestX = points[0].x;
        double highestY = points[0].y;
        double lowestX = points[0].x;
        double lowestY = points[0].y;

        for (int i = 1; i < 3; i++)
        {
            if (points[i].x > highestX)
                highestX = points[i].x;
            if (points[i].x < lowestX)
                lowestX = points[i].x;
            if (points[i].y > highestY)
                highestY = points[i].y;
            if (points[i].y < lowestY)
                lowestY = points[i].y;
        }
        Rect* bound = new Rect();
        bound->set(
            Point(lowestX, lowestY),
            Point(lowestX, highestY),
            Point(highestX, highestY),
            Point(highestX, lowestY)
        );
        return bound;
    }

    default:
        return  nullptr;
    }
}

Rect* boundingBoxMinimum(BaseObject* obj, int num)
{
    switch (num)
    {
    case 1:
    {
        Rect* boundedBox = new Rect();
        Rect* pRect = (Rect*)obj;
        Point* arr = pRect->getPoints();
        boundedBox->set(arr[0], arr[1], arr[2], arr[3]);
        return boundedBox;
    }

    case 2:
    {
        Circle* pCircl = (Circle*)obj;
        Rect* bound = new Rect();
        bound->set(
            Point(pCircl->getCenter()->x - pCircl->getRadius(), pCircl->getCenter()->y - pCircl->getRadius()),
            Point(pCircl->getCenter()->x - pCircl->getRadius(), pCircl->getCenter()->y + pCircl->getRadius()),
            Point(pCircl->getCenter()->x + pCircl->getRadius(), pCircl->getCenter()->y + pCircl->getRadius()),
            Point(pCircl->getCenter()->x + pCircl->getRadius(), pCircl->getCenter()->y - pCircl->getRadius())
        );
        return bound;
    }
    case 3:
    {
        Rect* boundBox = new Rect();
        Triangle* pTri = (Triangle*)obj;
        double maxLength = 0, length = 0;
        Point* points = pTri->getPoints();
        Point firstPoint = Point();
        Point secondPoint = Point();
        Point thirdPoint = Point();

        for (int i = 0; i < 2; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {
                length = sqrt(pow((points[j].x - points[i].x), 2) + pow((points[j].y - points[i].y), 2));
                if (length > maxLength)
                {
                    maxLength = length;
                    firstPoint = points[i];
                    secondPoint = points[j];
                    if (j == 1) thirdPoint = points[2];
                    if (j == 2 && i == 0) thirdPoint = points[1];
                    if (j == 2 && i == 1) thirdPoint = points[0];
                }
            }
        }

        // finding equation for parallel line going through 3ed point
        Line* baseOfTriangle = new Line();
        baseOfTriangle->set(firstPoint, secondPoint);
        double CoefParal[3] = {
            baseOfTriangle->getA(),
            baseOfTriangle->getB(),
           (baseOfTriangle->getA() * thirdPoint.x) + (baseOfTriangle->getB() * thirdPoint.y)
        };

        // finding equation for perpendicular to parallel line from point1
        double CoefPerpendicalarOne[3];
        perpendCoeficients(CoefParal, CoefPerpendicalarOne, firstPoint);

        //finding intersection of parallel going through 3ed point and perpendicular from 1st point
        Point point2 = pointOfInterseption(CoefPerpendicalarOne, CoefParal);
        perpendCoeficients(CoefParal, CoefPerpendicalarOne, secondPoint);
        Point point3 = pointOfInterseption(CoefPerpendicalarOne, CoefParal);

        boundBox->set(firstPoint, point2, point3, secondPoint);
        return boundBox;
    }
    default:
        return  nullptr;
    }

}

void perpendCoeficients(double* arrInput, double* arrOutput, Point p1)
{
    arrOutput[0] = (-1) * (arrInput[1] / arrInput[0]);
    arrOutput[1] = 1;
    arrOutput[2] = (p1.y + (arrOutput[0] * p1.x));
}

//simplified solution for system a1x + b1y -c1 = 0; a2x + b2y - c2 = 0
Point pointOfInterseption(double* line1, double* line2)
{
    double y = ((line2[2] - ((line2[0] * line1[2]) / line1[0])) / (line2[1] - ((line2[0] * line1[1]) / line1[0])));
    double x = ((line1[2] - (line1[1] * y)) / line1[0]);
    return Point(x, y);
}

