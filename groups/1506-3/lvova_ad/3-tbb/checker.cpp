#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm> 
#include <iostream>
using namespace std;

// Èñïîëüçóåòñÿ äëÿ âçàèìîäåéñòâèÿ ñ òåñòèðóþùåé ñèñòåìîé
////////////////////////////////////////////////////////////////////////////////////////////
/*
// Checker ìîæåò óñòàíàâëèâàòü âîò ýòè òðè âåðäèêòà:
AC = Accepted = Ðåøåíèå âûäà¸ò êîððåêòíûé ðåçóëüòàò íà äàííîì òåñòå
WA = Wrong Answer = Ðåøåíèå âûäà¸ò íåêîððåêòíûé ðåçóëüòàò íà äàííîì òåñòå
PE = Presentation Error = Îøèáêà ôîðìàòà âûõîäíûõ äàííûõ
// Îñòàëüíûå âåðäèêòû checker íå ìîæåò óñòàíàâëèâàòü
NO = No verdict = Âåðäèêò îòñóòñòâóåò
CE = Compilation Error = Îøèáêà êîìïèëÿöèè
ML = Memory Limit Exceeded = Ïðåâûøåíî îãðàíè÷åíèå ïî ïàìÿòè
TL = Time Limit Exceeded = Ïðåâûøåíî îãðàíè÷åíèå ïî âðåìåíè ðàáîòû
RE = Runtime Error = Îøèáêà âðåìåíè èñïîëíåíèÿ ïðîãðàììû
IL = Idle Limit Exceeded = Ïðåâûøåíî âðåìÿ ïðîñòîÿ (áåçäåéñòâèÿ) ïðîãðàììû
DE = Deadly Error = Îøèáêà òåñòèðóþùåé ñèñòåìû
*/

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };
class result
{
private:
	FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };

	result(bool read = false)
	{
		if (read) bur = fopen("result.txt", "r"); else bur = fopen("result.txt", "w");
	}

	~result() 
	{ 
		fclose(bur);
	}

	void write_type(ext_cls t)
	{
		fwrite(&t, sizeof(t), 1, bur);
	}

	// Ñîîáùèòü òåñòèðóþùåé ñèñòåìå, ÷òî ðåøåíèå ïîëó÷èëî îäèí èç âåðäèêòîâ verdict
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT); fwrite(&v, sizeof(v), 1, bur);
	}

	// Íàïèñàòü ñîîáùåíèå îò checker' a ïîëüçîâàòåëþ.
	//  Íàïðèìåð, ÷òî ðåøåíèå âåðíîå, èëè íåâåðíîå.
	// Èñïîëüçîâàòü òîëüêî ëàòèíñêèå áóêâû è çíàêè ïðåïèíàíèÿ
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE); int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}

	// Ñîîáùèòü òåñòèðóþùåé ñèñòåìå âðåìÿ ðàáîòû ïðîãðàììû ó÷àñòíèêà,
	// âû÷èñëåííîå ñ ïîìîùüþ before_code
	// x èìååò ðàçìåðíîñòü 100 íñ = 10 ^ ( -7) ñåê

	void write_time(long long x)
	{
		write_type(ext_cls::TIME); fwrite(&x, sizeof(x), 1, bur);
	}

	// Ñîîáùèòü òåñòèðóþùåé ñèñòåìå, ïàìÿòü çàòðåáîâàííóþ ïðîãðàììîé ó÷àñòíèêà
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY); fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;
////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	// Îòêðûâàåì ôàéë âõîäíûõ äàííûõ, ôàéë âûõîäíûõ äàííûõ è îòâåò ó÷àñòíèêà
	FILE * bui = fopen("../massiv.in", "rb");
	FILE * buo = fopen("../massiv.out", "rb");
	int size;
	double res_time;


	// Ñ÷èòûâàåì âðåìÿ ðàáîòû ïðîãðàììû ó÷àñòíèêà
	fread(&res_time, sizeof(res_time), 1, buo);

	// Ñ÷èòûâàåì ðàçìåðíîñòü ìàññèâà
	fread(&size, sizeof(size), 1, bui);
	fread(&size, sizeof(size), 1, buo);


	// Âûäåëÿåì ïàìÿòü äëÿ ìàññèâà îòâåòà æþðè è îòâåòà ó÷àñòíèêà
	double * answer = new double[size], * result = new double[size];
	
	// Ñ÷èòûâàåì  ìàññèâ ó÷àñòíèêà
	fread(result, sizeof(*result), size, buo);

	// Ñ÷èòûâàåì èñõîäíûå äàííûå äëÿ ïðîâåðêè ñòàíäàðòíîé ôóíêöèåé
	fread(answer, sizeof(*answer), size, bui);

	//ñîðòèðóåì èñõîäíûå äàííûå ñîðòèðîâêîé std
	sort(answer, answer+size);

	//Ñðàâíèâàåì îòâåòû
    
	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		if (answer[i] != result[i])
		{
            double k = result[i];
            std::cout << std::endl << "Numbers isn't equal -> iteration = " << i << ";  answer = " << answer[i] << ";  result = " << k << std::endl;
            flag = true;
            break;
		}
	}
	if(!flag)
	{
		std::cout << std::endl << "Numbers are equal" << std::endl;
		checker_result.write_message("AC. Numbers are equal.");
		checker_result.write_verdict(verdict::AC);
	}
	
	// Çàïèñûâàåì âðåìÿ â ïðàâèëüíîé ðàçìåðíîñòè ( èíòåðâàëû ïî 100 íñ = 10 ^ (-7) ñåê).
	checker_result.write_time(res_time * 1e7);
	fclose(bui);
	fclose(buo);
	return 0;
}
