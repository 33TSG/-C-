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
        d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));//��Բ�ĵľ���
        if (r >= r1) { //����С�� �뾶 �Լ� �뾶�Ĳ� ��Ϊ������ ��Բ�ں��������
            d1 = r - r1;
            minn = r1;
        }
        else {
            d1 = r1 - r;
            minn = r;
        }
        if (d >= r + r1 || r == 0 || r1 == 0)//��������� ��뾶����һ���� 0
            printf("0.000\n");
        else if (d <= d1 && d >= 0) {
            s = acos(-1) * minn * minn;//�ں��� ��*r*r
            printf("%0.3lf\n", s);
        }
        else {
            b = (r * r + d * d - r1 * r1) / (2 * r * d); // ����� ��oAB ������
            c = (r1 * r1 + d * d - r * r) / (2 * r1 * d); //��OBA ������
            b1 = 2 * acos(b); //��OAB==��O1AB ����b1=��OAO1=2*��OAB     acos(b) �ǡ�OAB
            c1 = 2 * acos(c);//ͬ��
            s1 = (double)1 / 2 * r * r * sin(b1); //�����������ʽ
            s2 = (double)1 / 2 * r1 * r1 * sin(c1);
            s3 = (double)1 / 2 * b1 * r * r;// ���������ʽ  b1 �ǽǶ�
            s4 = (double)1 / 2 * c1 * r1 * r1;
            s = (s3 + s4) - (s1 + s2);//��Ӱ�����ʽ=Soao1o+Sobo1o-Soao1b(�������ε����-�ı��ε������
            printf("%0.3lf\n", s);
        }
    }
}
// 0 0 2 2 2 2