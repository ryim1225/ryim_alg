#include "mat.h"
#include <math.h>
 
//----------------------------------------------------------------------------------
//构造矩阵：默认
matrix::matrix(void)
{
	Row = 0;
	Col = 0;
	Size = Row * Col;
	Elem = NULL;
}
//构造矩阵：按行列
matrix::matrix(int Cols, int Rows, long double val)
{
	Row = Rows;
	Col = Cols;
	Size = Row * Col;
	Elem = new long double [Row * Col];
	for(int i = 0 ; i < Row * Col; i++)
		Elem[i] = val;
}
//构造矩阵：生成对角阵，默认为单位阵
matrix::matrix(int lines, double val)
{
	Col = Row = lines;
	Size = Col * Row;
	Elem = new long double [Size];
	for(int i = 0 ; i < Col; i++)
	{
		for(int j = 0; j < Row; j++)
		{
			Elem[i * Row + j] = ( j == i ? val : 0.0);
		}
	}
}
//构造矩阵：由一维数组
matrix::matrix(int Cols, int Rows, long double* array)
{
	Col = Cols;
	Row = Rows;
	Size = Col * Row;
	Elem = new long double [Size];
	for(int i = 0; i < Size; i++)
	{
		//局限性：不能检查array的大小是否大于matrix.Size
		Elem[i] = array[i];
	}
}
matrix::matrix(int Cols, int Rows, long double **Array)
{
	Col = Cols;
	Row = Rows;
	Size = Col * Row;
	Elem = new long double [Size];
	for(int i = 0; i < Col; i++)
		for(int j = 0; j < Row; j++)
			Elem[i * Row + j] = Array[i][j];
}
//构造矩阵：由类构造
matrix::matrix(const matrix& M)
{
	Col = M.Col;
	Row = M.Row;
	Size = M.Size;
	Elem = new long double [M.Size];
	for(int i = 0; i < M.Size; i++)
		Elem[i] = M.Elem[i];
}
//析构函数
matrix::~matrix(void)
{
	delete []Elem;            //矩阵所在函数块运行结束时才释放
}
//-----------------------------------------------------------------------------------
long double& matrix::operator()(int L,int R)
{
	return Elem[(L - 1) * Row + (R - 1)];
}
//操作符 = 重载
matrix& matrix::operator=(const matrix& M) 
{
	//一定要创建临时矩阵，防止同一矩阵赋值（重新分配内在的同时，已经将此矩阵改变！！！！！！）
	if (this == &M)
	{
		return *this;
	}
	Col = M.Col;
	Row = M.Row;
	Size = M.Size;
	Elem = new long double [Size];
	for(int i = 0; i < Size; i++)
		Elem[i] = M.Elem[i];
	return *this;
}
 
//操作符 += 重载(矩阵加)
matrix& matrix::operator+=(const matrix& M)
{
	if(Col == M.Col && Row == M.Row)
	{
		Elem = new long double [M.Size];
		for(int i = 0; i < M.Size; i++)
			Elem[i] += M.Elem[i];
		return *this;
	}
	else
	{
		std::cout << "矩阵行或列数不相等，不可相加(matrix::operator+)" << std::endl;
		return *this;
	}
}
//操作符 +＝ 重载(数加)
matrix& matrix::operator+=(long double val)
{
	for(int i = 0; i < this->Size; i++)
		this->Elem[i] += val;
	return *this;
}
 
 
 
//操作符 -= 重载(矩阵减)
matrix& matrix::operator-=(const matrix& M)
{
	if(Col == M.Col && Row == M.Row)
	{
		Elem = new long double [M.Size];
		for(int i = 0; i < M.Size; i++)
			Elem[i] -= M.Elem[i];
		return *this;
	}
	else
	{
		std::cout << "矩阵行或列数不相等，不可相加(matrix::operator+)" << std::endl;
		return *this;
	}
}
//操作符 -= 重载(数减)
matrix& matrix::operator-=(long double val)
{
	for(int i = 0; i < this->Size; i++)
		this->Elem[i] -= val;
	return *this;
}
 
//操作符 *= 重载(矩阵乘)
matrix& matrix::operator*=(const matrix& M)
{
	if(Row == M.Col)
	{
		for(int i = 0; i < Col; i++)
			for(int j = 0; j < Row; j++)
			{
				long double temp = 0.0;
				for(int k = 0; k < Row; k++)
				{
					temp += GetElem(i+1,k+1) * M.Elem[k * M.Row + j];
					SetElem(i+1,j+1,temp);
				}
			}
			return *this;
	}
	else
	{
		std::cout << "被乘矩阵的列数与乘矩阵的行数不相等，不能相乘(matrix::operator*)" << std::endl;
		return *this;
	}
}
//操作符 *= 重载(数减)
matrix& matrix::operator*=(long double val)
{
	for(int i = 0; i < this->Size; i++)
		this->Elem[i] *= val;
	return *this;
}
 
 
 
 
 
 
 
 
 
//操作符 + 重载(矩阵加)
matrix operator+(const matrix& matrix1, const matrix& matrix2)
{
	matrix temp(matrix1);
	if(matrix1.Col == matrix2.Col && matrix1.Row == matrix2.Row)
	{
		for(int i = 0; i < matrix1.Size; i++)
			temp.Elem[i] += matrix2.Elem[i];
		return temp;
	}
	else
	{
		std::cout << "矩阵行或列数不相等，不可相加(friend operator-)" << std::endl;
		return temp;
	}
}
//操作符 - 重载(矩阵减)
matrix operator-(const matrix& matrix1, const matrix& matrix2)
{
	if(matrix1.Col == matrix2.Col && matrix1.Row == matrix2.Row)
	{
		for(int i = 0; i < matrix1.Size; i++)
			matrix1.Elem[i] += -(matrix2.Elem[i]);
		return matrix1;
	}
	else
	{
		std::cout << "矩阵行或列数不相等，不可相减(friend operator-)" << std::endl;
		return matrix1;
	}
}
//操作符 - 重载(矩阵乘)
matrix operator*(const matrix& matrix1, const matrix& matrix2)
{
	matrix Temp(matrix1.Col,matrix2.Row);
	if(matrix1.Row == matrix2.Col)
	{
		for(int i = 0; i < Temp.Col; i++)
			for(int j = 0; j < Temp.Row; j++)
			{
				long double temp = 0.0;
				for(int k = 0; k < matrix1.Row; k++)
				{
					temp += matrix1.GetElem(i+1,k+1) * matrix2.Elem[k * matrix2.Row + j];
					Temp.SetElem(i+1,j+1,temp);
				}
			}
			return Temp;
	}
	else
	{
		std::cout << "被乘矩阵的列数与乘矩阵的行数不相等，不能相乘(matrix::operator*)" << std::endl;
		return matrix1;
	}
}
//操作符 + 重载(数加1)
matrix operator+(const matrix& matrix,const long double val)
{
	for(int i=0; i < matrix.Size; i++)
		matrix.Elem[i] += val;
	return matrix;
}
//操作符 + 重载(数加2)
matrix operator+(const long double val,const  matrix& matrix)
{
	return matrix + val;
}
//操作符 + 重载(数减1)
matrix operator-(const matrix& matrix, const long double val)
{
	return (matrix + val) * (-1) ;
}
//操作符 + 重载(数减2)
matrix operator-(const long double val, const matrix& matrix)
{
	return matrix + val;
}
//操作符 * 重载(数乘1)
matrix operator*(const matrix& matrix1,const long double val)
{
	for(int i = 0; i < matrix1.Size; i++)
		matrix1.Elem[i] = matrix1.Elem[i] * val;
	return matrix1;
}
//操作符 * 重载(数乘2)
matrix operator*(const long double val,const  matrix& matrix)
{
	return matrix * val;
}
//矩阵输出
std::ostream& operator<<(std::ostream& OS, const matrix& matrix)
{
	for(int i = 0; i < matrix.Col; i++)
	{
		for(int j = 0; j < matrix.Row; j++)
		{
			OS << matrix.Elem[i * matrix.Row + j]<< " ";
		}
		OS << std::endl;
	}
	return OS;
}
//------------------------------------------------------------------------------------
//按行列重组矩阵
void matrix::rerange(int Cols, int Rows)
{
	if(Cols * Rows != Size)
	{
		std::cout << "所要重置矩阵的行列数参数错误，请查正！(matrix::rerange)" << std::endl;
		return ;
	}
	else
	{
		Col = Cols;
		Row = Rows;
	}
}
//打印矩阵
void matrix::show()
{
	std::cout << *this;
}
//矩阵转置
matrix  matrix::T()
{
	matrix Temp(Row,Col);
	for(int i = 0; i < Temp.Col; i++)
		for(int j = 0; j < Temp.Row; j++)
			Temp.Elem[i * Temp.Row +j] = Elem[j * Temp.Col +i];
	Temp.rerange(Temp.Col,Temp.Row);
	return Temp;
}
//查看第L行第R列元素的值
long double matrix::GetElem(int L,int R)  const                  
{
	return Elem[(L - 1) * Row + (R - 1)];
}
//修改第L行第R列元素的值
void matrix::SetElem(int L, int R, long double val)         
{
	Elem[(L - 1) * Row + (R - 1)] = val;
}
//矩阵求逆
matrix matrix::Inv()
{
	if(Col != Row)    //先判断是否为方阵
	{
		std::cout << "矩阵不是方阵不可进行求逆运算！(matrix::Inv)" << std::endl;
		exit(1);
	}
	matrix E(Col);    //创建同维数的单位矩阵
	double Max;        //用于记录每一列中最大的数
	int Max_Label;             //标记每列中最大数位于
	for(int i = 0; i < Col; i++)  //按列循环，将其进行行变换，并消去主元上下的元素
	{
		Max = GetElem(i+1,i+1);
		Max_Label = 0;
		if(i < Col - 1)
		{
			//进行行变换，使主元素的值最大
			for(int l = i + 1; l < Col; l++)   //i行后的每一行和第i行进行比较，并进行行变换
			{
				if(abs(Max) < abs(GetElem(l+1,i+1)))  //找出每一列主元素所在列的向下最大元素
				{
					Max = GetElem(l+1,i+1);
					Max_Label = l;
					for(int k = 1; k <= Col; k++)
					{
						long double* Swap = new long double;
						*Swap = GetElem(Max_Label+1,k);
						SetElem(Max_Label+1,k,GetElem(i+1,k));
						SetElem(i+1,k,*Swap);
						*Swap = E.GetElem(Max_Label+1,k);
						E.SetElem(Max_Label+1,k,E.GetElem(i+1,k));
						E.SetElem(i+1,k,*Swap);
						delete Swap;
					}
					Max = GetElem(i+1,i+1);
				}
			}
			if(Max == 0)
			{
				this->show();
				std::cout << "非满秩矩阵，不可求逆" << std::endl;
				exit(1);
			}
			//this->show();
			//E.show();
			//消去主元素上下的元素
			//this->show();
			for(int l = 0; l < Col; l++)
			{
				if( l == i)
					continue;
				else
				{
					if(GetElem(l+1,i+1) != 0)
					{
						long double a = GetElem(l+1,i+1);
						for(int k = 0; k < Col; k++)
						{
							//long double temp = Max * GetElem(l+1,k+1)/a - GetElem(i+1,k+1);
							SetElem(l+1,k+1,Max * GetElem(l+1,k+1)/a - GetElem(i+1,k+1));
							E.SetElem(l+1,k+1,Max * E.GetElem(l+1,k+1)/a - E.GetElem(i+1,k+1));
						}
 
					}
				}
			}
		}
		else
		{
			//处理最后一列数
			for(int j = 1; j <= Col -1; j++)
			{
				long double a = GetElem(j,Col);
				if(abs(a) < 1.0E-016)
					continue;
				else
				{
					for(int k = 1; k <= Col; k++)
					{
						SetElem(j,k,Max * GetElem(j,k)/a - GetElem(Col,k));
						E.SetElem(j,k,Max * E.GetElem(j,k)/a -  E.GetElem(Col,k));
					}
				}
			}
		}
	}
	//将主元素化为1
	for(int i = 1; i <= Col; i++)
	{
		long double a = GetElem(i,i);
		for(int j = 1; j <= Col; j++)
		{
			SetElem(i,j,GetElem(i,j)/a);
			E.SetElem(i,j,E.GetElem(i,j)/a);
		}
	}
	return E;
}
 
