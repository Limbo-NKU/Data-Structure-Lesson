#include<iostream>
#include<fstream>
#include<string>
#include<list>
using namespace std;
ifstream input("inputfile.txt");
ofstream output("outputfile.txt");
struct Fraction 
{
	int mother;
	int child;
};//用于除法中分数的处理
//use Fraction as coefficient in the division result,including Fraction's mother number and Fraction's child number.
ostream& operator<< (ostream& out, const Fraction & x)
{
	if (x.child%x.mother == 0)out << x.child / x.mother;
	else out << x.child << '/' << x.mother;
	return out;
}//重载运算符<<使分数在能除尽时输出整除结果，在不能除尽时输出分数本身
bool InsertEle(list<pair<int, int>>& Poly, pair<int, int> Element);
bool InsertEle(list<pair<Fraction , int>>& Poly, pair<Fraction , int> Element);
inline bool InsertEle(list<pair<int, int>>& Poly, pair<int, int>Element)
{
	if (Element.first == 0)return true;//如果系数为0，则不进行插入处理
	if (Poly.empty())
	{
		Poly.push_back(Element);
		return true;
	}//如果表为空，则在表尾直接插入
	list<pair<int, int>>::iterator p=Poly.begin(),next;//进行遍历操作的迭代器
	while (p->second < Element.second)
	{
		next = p;
		next++;
		if (next == Poly.end())
		{
			Poly.push_back(Element);
			return true;
		}
		p++;
	}//进行遍历，找到插入位置，如果表中元素指数均小于插入元素，则在表尾插入该元素
	if (p->second == Element.second)
	{
		p->first += Element.first;
		if (p->first == 0)Poly.erase(p);
		return true;
	}//如果插入位置后的元素指数等于插入元素的指数，则将系数相加，若相加后系数为0，则将该元素取出
	if (p->second > Element.second)
	{
		if (p == Poly.begin())
		{
			Poly.push_front(Element);
			return true;
		}
		Poly.insert(p, Element);
		return true;
	}//如果插入位置后的元素指数大于插入元素的指数，则进行插入操作
	return false;//若未进行以上操作，返回false
}//升幂插入整数项
inline bool InsertEle(list<pair<Fraction , int>>& Poly, pair<Fraction , int>Element)
{
	if (Element.first.child == 0)return true;//如果系数为0，则不进行插入处理
	if (Poly.empty())
	{
		Poly.push_front(Element);
		return true;
	}//如果表为空，则在表头直接插入
	list<pair<Fraction , int>>::iterator p = Poly.begin(), next;//进行遍历操作的迭代器
	if (Element.first.mother < 0)
	{
		Element.first.child = 0 - Element.first.child;
		Element.first.mother = 0 - Element.first.mother;
	}//将分母的负号移至分子
	while (p->second > Element.second)
	{
		next = p;
		next++;
		if (next == Poly.end())
		{
			Poly.push_back(Element);
			return true;
		}
		p++;
	}//进行遍历，找到插入位置，如果表中元素指数均大于插入元素，则在表尾插入该元素
	if (p->second == Element.second)
	{
		p->first.child *= Element.first.mother;
		Element.first.child *= p->first.mother;
		p->first.mother *= Element.first.mother;
		p->first.child += Element.first.child;//进行分数加法
		if (p->first.child == 0)Poly.erase(p);
		return true;
	}//如果插入位置后的元素指数等于插入元素的指数，则将系数相加，若相加后系数为0，则将该元素取出
	if (p->second < Element.second)
	{
		if (p == Poly.begin())
		{
			Poly.push_front(Element);
			return true;
		}
		Poly.insert(p, Element);
		return true;
	}//如果插入位置后的元素指数小于于插入元素的指数，则进行插入操作
	return false;//若未进行以上操作，返回false
}//降幂插入分数项
bool Input(istream& input, list<pair<int, int>>& Poly)
{
	int Input1, Input2;
	pair<int, int> InputEle;
	list<pair<int, int>>::iterator p=Poly.begin();
	if (input.get() == '(')
	{
		input >> Input1;
		if (input.get() == ',')
		{
			input >> Input2;
			if (input.get() == ')')
			{
				if (Input1 || Input2)
				{
					InputEle.first = Input1;
					InputEle.second = Input2;
					InsertEle(Poly, InputEle);
					Input(input, Poly);
					return true;
				}
				else
				{
					input.get();//避免换行符给下次操作带来的影响
					return true;
				}
			}
			else return true;
		}
		else return false;
	}
	else return false;
}
bool OutPut(ostream& output, list < pair<int, int>>& Poly)
{
	Poly.reverse();//以降幂形式输出多项式
	list<pair<int, int>>::iterator  p=Poly.begin();
	for(p=Poly.begin();p!=Poly.end();p++)
	{
		if (p->first > 0)
		{
			if (p == Poly.begin())
			{
				if (p->second == 0)output << p->first;
				else output << p->first << 'x' << p->second;
			}
			else
			{
				if (p->second == 0)output << '+' << p->first;
				else output << '+' << p->first << 'x' << p->second;
			}
		}
		if (p->first < 0)
		{
			if (p->second == 0)output << p->first;
			else output << p->first << 'x' << p->second;
		}
	}//输出第一项到最后一项
	output << endl;
	return true;
}
bool OutPut(ostream& output, list < pair<Fraction , int>>& Poly)
{
	Poly.reverse();//以降幂形式输出多项式
	list<pair<Fraction , int>>::iterator  p = Poly.begin();
	for (p = Poly.begin(); p != Poly.end(); p++)
	{
		if (p->first.child > 0)
		{
			if (p == Poly.begin())
			{
				if (p->second == 0)output << p->first;
				else output << p->first << 'x' << p->second;
			}
			else
			{
				if (p->second == 0)output << '+' << p->first;
				else output << '+' << p->first << 'x' << p->second;
			}
		}
		if (p->first.child < 0)
		{
			if (p->second == 0)output << p->first;
			else output << p->first << 'x' << p->second;
		}
	}//输出第一项到最后一项
	output << endl;
	return true;
}

bool AND(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2)
{
	pair<int, int> Ele;
	list<pair<int, int>>::iterator p=Poly2.begin();
	while (p != Poly2.end())
	{
		Ele = *p;//取出当前元素
		InsertEle(Poly1, Ele);//将当前元素加至Poly1多项式中
		Poly2.pop_front();//将当前元素从Poly2多项式中删除
		p = Poly2.begin();//迭代器重置为Poly2多项式的第一项
	}		//进行加和
	return true;
}
bool SUB(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2)
{
	pair<int, int> Ele;
	list<pair<int, int>>::iterator p = Poly2.begin();
	while (p != Poly2.end())
	{
		Ele = *p;
		Ele.first = 0 - Ele.first;//将系数取相反数再加和
		InsertEle(Poly1, Ele);
		Poly2.pop_front();
		p = Poly2.begin();
	}
	return true;
}
bool MUL(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2)
{
	list<pair<int, int>> Temp;
	list<pair<int, int>>::iterator p1=Poly1.begin(), p2=Poly2.begin();
	pair<int, int> Result,Ele1,Ele2;
	while (p2 != Poly2.end())
	{
		Ele2 = *p2;
		while (p1 != Poly1.end())
		{
			Ele1 = *p1;
			Result.first = Ele1.first*Ele2.first;
			Result.second = Ele1.second + Ele2.second;
			InsertEle(Temp, Result);
			p1++;
		}			//将Poly1的所有项与Poly2的当前元素依次相乘并添加到结果多项式Temp中
		p1 = Poly1.begin();//重置Poly1迭代器至表头
		Poly2.pop_front();//Poly2弹出表顶元素
		p2 = Poly2.begin();//当前元素顺延
	}//进行乘法操作
	Poly1.clear();//清空Poly1，防止留下内存溢出
	Poly1 = Temp;//将存放结果多项式的Temp拷贝赋值给Poly1
	return true;
}
bool DIV(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2,bool& IsClear,list<pair<Fraction ,int>>& TempResult,list<pair<Fraction ,int>>& TempMinused)
{
	Poly1.reverse();
	Poly2.reverse();//翻转两个多项式使元素降幂排列
	list<pair<Fraction , int>> TempMinus;
	list<pair<int, int>>::iterator p2=Poly2.begin(),p1=Poly1.begin();
	list<pair<Fraction , int>>::iterator pTemp;
	int maxMinus = p2->second;//maxMinus为除式最高次项的指数
	pair<Fraction , int> Ele1, Ele2;
	while (p1 != Poly1.end())
	{
		Ele1.first.child = p1->first;
		Ele1.first.mother = 1;
		Ele1.second = p1->second;
		InsertEle(TempMinused, Ele1);
		p1++;
	}//初始化被除式多项式，并将其系数的分子赋值为Poly1的系数，分母设置为1，指数设置为Poly1的指数
	pTemp = TempMinused.begin();
	while (pTemp != TempMinused.end())
	{
		p2 = Poly2.begin();
		if (pTemp->second < maxMinus)break;//如果被除式第一项指数小于除式最高项指数，则退出计算
		TempMinus.clear();
		Ele1.first = pTemp->first;
		Ele1.first.mother *= p2->first;
		Ele1.second = pTemp->second - p2->second;
		InsertEle(TempResult, Ele1);//被除式的第一项除以除式的最高次项
		p2 = Poly2.begin();
		while (p2 != Poly2.end())
		{
			Ele2.first = Ele1.first;
			Ele2.first.child *= p2->first;
			Ele2.second = Ele1.second + p2->second;
			InsertEle(TempMinus, Ele2);
			p2++;
		}//上一操作的结果乘以除式，作为余式
		pTemp = TempMinus.begin();
		while (pTemp != TempMinus.end())
		{
			Ele2 = *pTemp;
			Ele2.first.child = 0 - Ele2.first.child;//将系数取相反数再加和
			InsertEle(TempMinused, Ele2);
			TempMinus.pop_front();
			pTemp = TempMinus.begin();
		}//用被除式减去余式作为新的被除式，继续循环
		pTemp = TempMinused.begin();
	}
	//退出计算后，TempMinused即为余式，TempRes即为结果
	IsClear = TempMinused.empty();
	Poly1.clear();
	Poly2.clear();
	return true;
}
bool DIFF(list<pair<int, int>>& Poly)
{
	list<pair<int, int>>::iterator p=Poly.begin(),next;
	pair<int, int>Ele;
	if (p->second == 0) 
	{ 
		Poly.pop_front();
		p = Poly.begin();
	}//先将原多项式常数项清空
	while (p != Poly.end())
	{
		Ele = *p;
		Ele.first = Ele.first*Ele.second;
		Ele.second--;
		InsertEle(Poly, Ele);
		next = p;
		next++;
		Poly.erase(p);
		p = next;
	}//逐项将系数与指数相乘，填充至前一项
	return true;
}
int main()
{
	int ProcessNum=0;//总运算次数
	while (input)
	{
		ProcessNum++;//总运算次数累加
		output << "第"<<ProcessNum<<"次运算" << endl;
		list<pair<int, int>> Poly1, Poly2;
		bool Input1, Input2;
		Input1 = Input(input, Poly1);
		Input2 = Input(input, Poly2);
		if (Input1 == false || Input2 == false)
		{
			output << "输入多项式出错"<<endl;
			return 0;
		}
		string OperFlag;
		input >> OperFlag;
		bool OperSucc, OutSucc;
		if (OperFlag == "AND(#,#)")
		{
			output << "进行运算：加法" << endl << "结果为："<<endl;
			OperSucc = AND(Poly1, Poly2);
			OutSucc = OutPut(output, Poly1);
		}
		if (OperFlag == "SUB(#,#)")
		{
			output << "进行运算：减法" << endl << "结果为：" << endl;
			OperSucc = SUB(Poly1, Poly2);
			OutSucc = OutPut(output, Poly1);
		}
		if (OperFlag == "MUL(#,#)")
		{
			output << "进行运算：乘法" << endl << "结果为：" << endl;
			OperSucc = MUL(Poly1, Poly2);
			OutSucc = OutPut(output, Poly1);
		}
		if (OperFlag == "DIV(#,#)")
		{
			output << "进行运算：除法" << endl;
			bool IsClear;
			list<pair<Fraction , int>> Result, Minus;
			OperSucc = DIV(Poly1, Poly2, IsClear,Result,Minus);
			if (IsClear) 
			{ 
				output << "多项式已除尽，结果为："<<endl;
				OutSucc = OutPut(output, Result); 
			}
			else 
			{ 
				output << "多项式未除尽，结果为：" << endl;
				bool Output1 = OutPut(output, Result);
				output << "余式为：" << endl;
				bool Output2 = OutPut(output,Minus);
				OutSucc = Output1 && Output2; 
			}
		}
		if (OperFlag == "DIFF(#,#)")
		{
			output << "进行运算：微分" << endl;
			OperSucc = DIFF(Poly1) && DIFF(Poly2);
			output << "第一个多项式微分结果为：" << endl;
			bool output1 = OutPut(output, Poly1);
			output << "第二个多项式微分结果为：" << endl;
			bool output2 = OutPut(output, Poly2);
			OutSucc = output1 && output2;
		}
		if (OperSucc == false)
		{
			output << "计算操作错误"<<endl;
			return 0;
		}
		if (OutSucc == false)
		{
			output << "输出多项式出错"<<endl;
			return 0;
		}
		input.get();
	}
	return 0;
}