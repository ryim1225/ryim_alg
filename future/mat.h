#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>

namespace troodon
{
class matrix
{
  private:
    int Col;           //矩阵的行
    int Row;           //矩阵的列
    int Size;          //矩阵元素的数目
    long double *Elem; //矩阵指针，根据需要分配大小（请查看构造函数)
  public:
    matrix(void);                                    //默认构造矩阵
    matrix(int Cols, int Rows, long double Val = 0); //按行列数构造矩阵,默认值元素值为0
    matrix(int Cols, double Val = 1);                //构造对角方阵，默认为单位矩阵(初始化时，第二个参数必须强制转换为double型,否则将生成L行，Val列元素为零的矩阵)
    matrix(int Cols, int Rows, long double *Array);  //用一维数组构造矩阵
    matrix(int Cols, int Rows, long double **Array);
    matrix(const matrix &matrix);                //用已存在的矩阵对象构造矩阵
    void show();                                 //在屏幕上打印矩阵
    void rerange(int Cols, int Rows);            //按行列重置矩阵
    long double GetElem(int L, int R) const;     //查看第L行第R列元素的值
    void SetElem(int L, int R, long double val); //修改第L行第R列元素的值
    int GetCols() const { return Col; };         //获取行数
    int GetRows() const { return Row; };         //获取列数
    int GetSize() const { return Row * Col; };   //获取数组大小

    long double &operator()(int L, int R);

    matrix T();                                //矩阵转置
    matrix Inv();                              //矩阵求逆
    matrix &operator=(const matrix &matrix);   //矩阵的赋值操作符重载
    matrix &operator+=(const matrix &matrix2); //矩阵的加法操作符重载
    matrix &operator+=(long double val);       //矩阵与数的加法操作符重载
    matrix &operator-=(const matrix &matrix2); //矩阵的减法操作符重载
    matrix &operator-=(long double val);       //矩阵与数的减法操作符重载
    matrix &operator*=(const matrix &matrix2); //矩阵的乘法操作符重载
    matrix &operator*=(long double val);       //矩阵与数的乘法操作符重载

    ~matrix(void);

  public:
    friend matrix operator+(const matrix &matrix1, const matrix &matrix2);   //矩阵与矩阵加法－操作符重载
    friend matrix operator-(const matrix &matrix1, const matrix &matrix2);   //矩阵与矩阵减法－操作符重载
    friend matrix operator*(const matrix &matrix1, const matrix &matrix2);   //矩阵与矩阵乘法－操作符重载
    friend matrix operator+(const matrix &matrix1, const long double val);   //矩阵与数加法－操作符重载（1）
    friend matrix operator+(const long double val, const matrix &matrix1);   //矩阵与数加法－操作符重载（2）
    friend matrix operator-(const matrix &matrix1, const long double val);   //矩阵与数减法－操作符重载（1）
    friend matrix operator-(const long double val, const matrix &matrix1);   //矩阵与数减法－操作符重载（2）
    friend matrix operator*(const matrix &matrix1, const long double val);   //矩阵与数乘法－操作符重载（1）
    friend matrix operator*(const long double val, const matrix &matrix1);   //矩阵与数乘法－操作符重载（2）
    friend std::ostream &operator<<(std::ostream &os, const matrix &matrix); //输出矩阵.为什么必须以友元的方式声明<<操作符？？？？？？？
};
} // namespace troodon
#endif