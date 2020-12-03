#include <iostream>
#include <vector>
#include "Point2D.h"
#include "Rectangle.h"

using namespace std;

int main(){
    Point2D p1(4,3), p2(17,9), p3(9,3.5), p4(8,10), p5(7,2), p6(10,8);
    Rectangle rec1(p1, p2), rec2(p5, p2);
    vector<Point2D> contained, inboth;

    cout << "Add p3? " << rec1.add_point(p3) << endl;
    cout << "Add p4? " << rec1.add_point(p4) << endl;
    cout << "p3 is in rec1?  " << rec1.is_point_within(p3) << endl;
    cout << "p4 is in rec1?  " << rec1.is_point_within(p4) << endl << endl;
    print_rectangle(rec1);
    cout << endl;

    rec2.add_point(p3); rec2.add_point(p4); rec2.add_point(p6);
    print_rectangle(rec2);
    cout << endl;

    inboth = points_in_both(rec1, rec2);
    cout << "Points in both rec1 and rec2: " << endl;
    for (int i = 0; i < inboth.size(); i++)
        cout << inboth[i].x() << ',' << inboth[i].y() << endl;



}