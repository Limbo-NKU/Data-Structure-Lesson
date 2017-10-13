#include<iostream>
#include<fstream>
#include<string>
#include<list>
using namespace std;
ifstream input("inputfile.txt");
ofstream output("outputfile.txt");
bool Input(istream& input, list<pair<int, int>>& Poly)
{

}
bool OutPut(ostream& output, list < pair<int, int>>& Poly)
{

}
bool AND(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2)
{

}
bool SUB(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2)
{

}
bool MUL(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2)
{

}
bool DIV(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2,bool& IsClear)
{

}
bool DIFF(list<pair<int, int>>& Poly)
{

}
int main()
{
	list<pair<int, int>> Poly1, Poly2;
	bool Input1, Input2;
	Input1 = Input(input, Poly1);
	Input2 = Input(input, Poly2);
	if (Input1 == false || Input2==false)
	{
		cout << "输入多项式出错";
		return 0;
	}
	string OperFlag;
	input >> OperFlag;
	bool OperSucc, OutSucc;
	if (OperFlag == "AND(#,#)")
	{
		OperSucc=AND(Poly1, Poly2);
		OutSucc=OutPut(output, Poly1);
	}
	if (OperFlag == "SUB(#,#)")
	{
		OperSucc=SUB(Poly1, Poly2);
		OutSucc=OutPut(output, Poly1);
	}
	if (OperFlag == "MUL(#,#)")
	{
		OperSucc=MUL(Poly1, Poly2);
		OutSucc=OutPut(output, Poly1);
	}
	if (OperFlag == "DIV(#,#)")
	{
		bool IsClear;
		OperSucc=DIV(Poly1, Poly2,IsClear);
		if (IsClear)OutSucc = OutPut(output, Poly1);
		else OutSucc = OutPut(output, Poly1) && OutPut(output, Poly2);
	}
	if (OperFlag == "DIFF(#,#)")
	{
		OperSucc=DIFF(Poly1)&&DIFF(Poly2);
		OutSucc=OutPut(output, Poly1)&&OutPut(output, Poly2);
	}
	if (OperSucc == false)
	{
		cout << "计算操作错误";
		return 0;
	}
	if (OutSucc == false)
	{
		cout << "输出多项式出错";
		return 0;
	}
	return 0;
}