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
};//���ڳ����з����Ĵ���
//use Fraction as coefficient in the division result,including Fraction's mother number and Fraction's child number.
ostream& operator<< (ostream& out, const Fraction & x)
{
	if (x.child%x.mother == 0)out << x.child / x.mother;
	else out << x.child << '/' << x.mother;
	return out;
}//���������<<ʹ�������ܳ���ʱ�������������ڲ��ܳ���ʱ�����������
bool InsertEle(list<pair<int, int>>& Poly, pair<int, int> Element);
bool InsertEle(list<pair<Fraction , int>>& Poly, pair<Fraction , int> Element);
inline bool InsertEle(list<pair<int, int>>& Poly, pair<int, int>Element)
{
	if (Element.first == 0)return true;//���ϵ��Ϊ0���򲻽��в��봦��
	if (Poly.empty())
	{
		Poly.push_back(Element);
		return true;
	}//�����Ϊ�գ����ڱ�βֱ�Ӳ���
	list<pair<int, int>>::iterator p=Poly.begin(),next;//���б��������ĵ�����
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
	}//���б������ҵ�����λ�ã��������Ԫ��ָ����С�ڲ���Ԫ�أ����ڱ�β�����Ԫ��
	if (p->second == Element.second)
	{
		p->first += Element.first;
		if (p->first == 0)Poly.erase(p);
		return true;
	}//�������λ�ú��Ԫ��ָ�����ڲ���Ԫ�ص�ָ������ϵ����ӣ�����Ӻ�ϵ��Ϊ0���򽫸�Ԫ��ȡ��
	if (p->second > Element.second)
	{
		if (p == Poly.begin())
		{
			Poly.push_front(Element);
			return true;
		}
		Poly.insert(p, Element);
		return true;
	}//�������λ�ú��Ԫ��ָ�����ڲ���Ԫ�ص�ָ��������в������
	return false;//��δ�������ϲ���������false
}//���ݲ���������
inline bool InsertEle(list<pair<Fraction , int>>& Poly, pair<Fraction , int>Element)
{
	if (Element.first.child == 0)return true;//���ϵ��Ϊ0���򲻽��в��봦��
	if (Poly.empty())
	{
		Poly.push_front(Element);
		return true;
	}//�����Ϊ�գ����ڱ�ͷֱ�Ӳ���
	list<pair<Fraction , int>>::iterator p = Poly.begin(), next;//���б��������ĵ�����
	if (Element.first.mother < 0)
	{
		Element.first.child = 0 - Element.first.child;
		Element.first.mother = 0 - Element.first.mother;
	}//����ĸ�ĸ�����������
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
	}//���б������ҵ�����λ�ã��������Ԫ��ָ�������ڲ���Ԫ�أ����ڱ�β�����Ԫ��
	if (p->second == Element.second)
	{
		p->first.child *= Element.first.mother;
		Element.first.child *= p->first.mother;
		p->first.mother *= Element.first.mother;
		p->first.child += Element.first.child;//���з����ӷ�
		if (p->first.child == 0)Poly.erase(p);
		return true;
	}//�������λ�ú��Ԫ��ָ�����ڲ���Ԫ�ص�ָ������ϵ����ӣ�����Ӻ�ϵ��Ϊ0���򽫸�Ԫ��ȡ��
	if (p->second < Element.second)
	{
		if (p == Poly.begin())
		{
			Poly.push_front(Element);
			return true;
		}
		Poly.insert(p, Element);
		return true;
	}//�������λ�ú��Ԫ��ָ��С���ڲ���Ԫ�ص�ָ��������в������
	return false;//��δ�������ϲ���������false
}//���ݲ��������
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
					input.get();//���⻻�з����´β���������Ӱ��
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
	Poly.reverse();//�Խ�����ʽ�������ʽ
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
	}//�����һ����һ��
	output << endl;
	return true;
}
bool OutPut(ostream& output, list < pair<Fraction , int>>& Poly)
{
	Poly.reverse();//�Խ�����ʽ�������ʽ
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
	}//�����һ����һ��
	output << endl;
	return true;
}

bool AND(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2)
{
	pair<int, int> Ele;
	list<pair<int, int>>::iterator p=Poly2.begin();
	while (p != Poly2.end())
	{
		Ele = *p;//ȡ����ǰԪ��
		InsertEle(Poly1, Ele);//����ǰԪ�ؼ���Poly1����ʽ��
		Poly2.pop_front();//����ǰԪ�ش�Poly2����ʽ��ɾ��
		p = Poly2.begin();//����������ΪPoly2����ʽ�ĵ�һ��
	}		//���мӺ�
	return true;
}
bool SUB(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2)
{
	pair<int, int> Ele;
	list<pair<int, int>>::iterator p = Poly2.begin();
	while (p != Poly2.end())
	{
		Ele = *p;
		Ele.first = 0 - Ele.first;//��ϵ��ȡ�෴���ټӺ�
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
		}			//��Poly1����������Poly2�ĵ�ǰԪ��������˲���ӵ��������ʽTemp��
		p1 = Poly1.begin();//����Poly1����������ͷ
		Poly2.pop_front();//Poly2������Ԫ��
		p2 = Poly2.begin();//��ǰԪ��˳��
	}//���г˷�����
	Poly1.clear();//���Poly1����ֹ�����ڴ����
	Poly1 = Temp;//����Ž������ʽ��Temp������ֵ��Poly1
	return true;
}
bool DIV(list<pair<int, int>>& Poly1, list<pair<int, int>>& Poly2,bool& IsClear,list<pair<Fraction ,int>>& TempResult,list<pair<Fraction ,int>>& TempMinused)
{
	Poly1.reverse();
	Poly2.reverse();//��ת��������ʽʹԪ�ؽ�������
	list<pair<Fraction , int>> TempMinus;
	list<pair<int, int>>::iterator p2=Poly2.begin(),p1=Poly1.begin();
	list<pair<Fraction , int>>::iterator pTemp;
	int maxMinus = p2->second;//maxMinusΪ��ʽ��ߴ����ָ��
	pair<Fraction , int> Ele1, Ele2;
	while (p1 != Poly1.end())
	{
		Ele1.first.child = p1->first;
		Ele1.first.mother = 1;
		Ele1.second = p1->second;
		InsertEle(TempMinused, Ele1);
		p1++;
	}//��ʼ������ʽ����ʽ��������ϵ���ķ��Ӹ�ֵΪPoly1��ϵ������ĸ����Ϊ1��ָ������ΪPoly1��ָ��
	pTemp = TempMinused.begin();
	while (pTemp != TempMinused.end())
	{
		p2 = Poly2.begin();
		if (pTemp->second < maxMinus)break;//�������ʽ��һ��ָ��С�ڳ�ʽ�����ָ�������˳�����
		TempMinus.clear();
		Ele1.first = pTemp->first;
		Ele1.first.mother *= p2->first;
		Ele1.second = pTemp->second - p2->second;
		InsertEle(TempResult, Ele1);//����ʽ�ĵ�һ����Գ�ʽ����ߴ���
		p2 = Poly2.begin();
		while (p2 != Poly2.end())
		{
			Ele2.first = Ele1.first;
			Ele2.first.child *= p2->first;
			Ele2.second = Ele1.second + p2->second;
			InsertEle(TempMinus, Ele2);
			p2++;
		}//��һ�����Ľ�����Գ�ʽ����Ϊ��ʽ
		pTemp = TempMinus.begin();
		while (pTemp != TempMinus.end())
		{
			Ele2 = *pTemp;
			Ele2.first.child = 0 - Ele2.first.child;//��ϵ��ȡ�෴���ټӺ�
			InsertEle(TempMinused, Ele2);
			TempMinus.pop_front();
			pTemp = TempMinus.begin();
		}//�ñ���ʽ��ȥ��ʽ��Ϊ�µı���ʽ������ѭ��
		pTemp = TempMinused.begin();
	}
	//�˳������TempMinused��Ϊ��ʽ��TempRes��Ϊ���
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
	}//�Ƚ�ԭ����ʽ���������
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
	}//���ϵ����ָ����ˣ������ǰһ��
	return true;
}
int main()
{
	int ProcessNum=0;//���������
	while (input)
	{
		ProcessNum++;//����������ۼ�
		output << "Processing #"<<ProcessNum<<" calculation." << endl;
		list<pair<int, int>> Poly1, Poly2;
		bool Input1, Input2;
		Input1 = Input(input, Poly1);
		Input2 = Input(input, Poly2);
		if (Input1 == false || Input2 == false)
		{
			output << "Input polynomial error."<<endl;
			return 0;
		}
		string OperFlag;
		input >> OperFlag;
		bool OperSucc, OutSucc;
		if (OperFlag == "AND(#,#)")
		{
			output << "Calculating:Addition." << endl << "The result is:"<<endl;
			OperSucc = AND(Poly1, Poly2);
			OutSucc = OutPut(output, Poly1);
		}
		if (OperFlag == "SUB(#,#)")
		{
			output << "Calculating:Subtraction." << endl << "The result is:" << endl;
			OperSucc = SUB(Poly1, Poly2);
			OutSucc = OutPut(output, Poly1);
		}
		if (OperFlag == "MUL(#,#)")
		{
			output << "Calculating:Multiplication." << endl << "The result is:" << endl;
			OperSucc = MUL(Poly1, Poly2);
			OutSucc = OutPut(output, Poly1);
		}
		if (OperFlag == "DIV(#,#)")
		{
			output << "Calculating:Division." << endl;
			bool IsClear;
			list<pair<Fraction , int>> Result, Minus;
			OperSucc = DIV(Poly1, Poly2, IsClear,Result,Minus);
			if (IsClear) 
			{ 
				output << "The polynomial is divisible.The result is:"<<endl;
				OutSucc = OutPut(output, Result); 
			}
			else 
			{ 
				output << "The polynomial is not divisible.The result is:" << endl;
				bool Output1 = OutPut(output, Result);
				output << "The remainder is:" << endl;
				bool Output2 = OutPut(output,Minus);
				OutSucc = Output1 && Output2; 
			}
		}
		if (OperFlag == "DIFF(#,#)")
		{
			output << "Calculating:Differentiation" << endl;
			OperSucc = DIFF(Poly1) && DIFF(Poly2);
			output << "The first differentiation result is:" << endl;
			bool output1 = OutPut(output, Poly1);
			output << "The second differentiation result is:" << endl;
			bool output2 = OutPut(output, Poly2);
			OutSucc = output1 && output2;
		}
		if (OperSucc == false)
		{
			output << "Calculate operation error."<<endl;
			return 0;
		}
		if (OutSucc == false)
		{
			output << "Outputting polynomial error."<<endl;
			return 0;
		}
		input.get();
	}
	return 0;
}