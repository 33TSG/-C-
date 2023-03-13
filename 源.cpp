#include<stdio.h>
#include<iostream>
#include<math.h>

using namespace std;

int main()
{
    double x, y, r, x1, y1, r1;
    double s, s1, s2, s3, s4, s5, s6;
    double b, b1, b2, c, c1, c2;
    double d, d1, minn;
    while (scanf_s("%lf %lf %lf", &x, &y, &r) != EOF) {
        scanf_s("%lf %lf %lf", &x1, &y1, &r1);
        d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));//两圆心的距离
        if (r >= r1) { //求最小的 半径 以及 半径的差 （为了讨论 两圆内含的情况）
            d1 = r - r1;
            minn = r1;
        }
        else {
            d1 = r1 - r;
            minn = r;
        }
        if (d >= r + r1 || r == 0 || r1 == 0)//相离或相切 或半径至少一个是 0
            printf("0.000\n");
        else if (d <= d1 && d >= 0) {
            s = acos(-1) * minn * minn;//内含的 π*r*r
            printf("%0.3lf\n", s);
        }
        else {
            b = (r * r + d * d - r1 * r1) / (2 * r * d); // 求出来 ∠oAB 的余弦
            c = (r1 * r1 + d * d - r * r) / (2 * r1 * d); //∠OBA 的余弦
            b1 = 2 * acos(b); //∠OAB==∠O1AB 所以b1=∠OAO1=2*∠OAB     acos(b) 是∠OAB
            c1 = 2 * acos(c);//同上
            s1 = (double)1 / 2 * r * r * sin(b1); //三角形面积公式
            s2 = (double)1 / 2 * r1 * r1 * sin(c1);
            s3 = (double)1 / 2 * b1 * r * r;// 扇形面积公式  b1 是角度
            s4 = (double)1 / 2 * c1 * r1 * r1;
            s = (s3 + s4) - (s1 + s2);//阴影面积公式=Soao1o+Sobo1o-Soao1b(两个扇形的面积-四边形的面积）
            printf("%0.3lf\n", s);
        }
    }
}
// 0 0 2 2 2 2