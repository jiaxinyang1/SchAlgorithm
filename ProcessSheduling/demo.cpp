
#include "SchAlgorithm.h"
#include <iostream>
using namespace SchAlgorithm;
void show(Algorithm::ProcessesList &pro);
int main(void)
{

	Process p1;
	Process p2;
	Process p3;
	Process p4;
	Process p5;
	p1.processName = "p1";
	p1.reachTime = 0;
	p1.runTime = 3;

	p2.processName = "p2";
	p2.reachTime = 2;
	p2.runTime = 6;

	p3.processName = "p3";
	p3.reachTime = 4;
	p3.runTime = 4;

	p4.processName = "p4";
	p4.reachTime = 6;
	p4.runTime = 5;

	p5.processName = "p5";
	p5.reachTime = 8;
	p5.runTime = 2;
	Algorithm::ProcessesList test;
	test.push_back(&p1);
	test.push_back(&p2);
	test.push_back(&p3);
	test.push_back(&p4);
	test.push_back(&p5);

	FCFS test_fcfs;
	test_fcfs.add(test);
	test_fcfs.run();
	cout << "先来先服务:" << endl;
	show(test);

	HRRN test_hrrn;
	test_hrrn.add(test);
	test_hrrn.run();
	cout << "最短响应比优先:" << endl;
	show(test);
	SPN test_spn;
	test_spn.add(test);
	test_spn.run();
	cout << "最短进程优先:" << endl;
	show(test);

	RR test_rr1;
	test_rr1.add(test);
	test_rr1.setRound(1);
	test_rr1.run();
	cout << "轮转 \t q=1" << endl;
	show(test);
	RR test_rr2;
	test_rr2.add(test);
	test_rr2.setRound(4);
	test_rr2.run();
	cout << "轮转 \t q=4" << endl;
	show(test);
	//FCFS test;
	//test.add(p1);
	//test.add(p2);
	//test.add(p3);
	//test.add(p4);
	//test.add(p5);

	//test.run();
	//std::cout << p1.processName << ":" << p1.beginTime << "  " << p1.endTime <<p1.normalizedResponseTime<< endl;
	//std::cout << p2.processName << ":" << p2.beginTime << "  " << p2.endTime << p2.normalizedResponseTime << endl;
	//std::cout << p3.processName << ":" << p3.beginTime << "  " << p3.endTime << p3.normalizedResponseTime << endl;
	//std::cout << p4.processName << ":" << p4.beginTime << "  " << p4.endTime << p4.normalizedResponseTime << endl;
	//std::cout << p5.processName << ":" << p5.beginTime << "  " << p5.endTime << p5.normalizedResponseTime << endl;

	//HRRN test_hrrn;
	//test_hrrn.add(p1);
	//test_hrrn.add(p2);
	//test_hrrn.add(p3);
	//test_hrrn.add(p4);
	//test_hrrn.add(p5);
	//test_hrrn.run();
	//std::cout << p1.processName << ":" << p1.beginTime << "  " << p1.endTime << "  " <<p1.normalizedResponseTime<< endl;
	//std::cout << p2.processName << ":" << p2.beginTime << "  " << p2.endTime << "  " << p2.normalizedResponseTime << endl;
	//std::cout << p3.processName << ":" << p3.beginTime << "  " << p3.endTime << "  " << p3.normalizedResponseTime << endl;
	//std::cout << p4.processName << ":" << p4.beginTime << "  " << p4.endTime << "  " << p4.normalizedResponseTime << endl;
	//std::cout << p5.processName << ":" << p5.beginTime << "  " << p5.endTime << "  " << p5.normalizedResponseTime << endl;


	//SPN test_spn;
	//test_spn.add(p1);
	//test_spn.add(p2);
	//test_spn.add(p3);
	//test_spn.add(p4);
	//test_spn.add(p5);
	//test_spn.run();
	//std::cout << p1.processName << ":" << p1.beginTime << "  " << p1.endTime << "  " << p1.normalizedResponseTime << endl;
	//std::cout << p2.processName << ":" << p2.beginTime << "  " << p2.endTime << "  " << p2.normalizedResponseTime << endl;
	//std::cout << p3.processName << ":" << p3.beginTime << "  " << p3.endTime << "  " << p3.normalizedResponseTime << endl;
	//std::cout << p4.processName << ":" << p4.beginTime << "  " << p4.endTime << "  " << p4.normalizedResponseTime << endl;
	//std::cout << p5.processName << ":" << p5.beginTime << "  " << p5.endTime << "  " << p5.normalizedResponseTime << endl;


	//RR test_rr;
	//test_rr.add(p1);
	//test_rr.add(p2);
	//test_rr.add(p3);
	//test_rr.add(p4);
	//test_rr.add(p5);
	//test_rr.run();
	//std::cout << p1.processName << ":" << p1.beginTime << "  " << p1.endTime << "  " << p1.normalizedResponseTime << endl;
	//std::cout << p2.processName << ":" << p2.beginTime << "  " << p2.endTime << "  " << p2.normalizedResponseTime << endl;
	//std::cout << p3.processName << ":" << p3.beginTime << "  " << p3.endTime << "  " << p3.normalizedResponseTime << endl;
	//std::cout << p4.processName << ":" << p4.beginTime << "  " << p4.endTime << "  " << p4.normalizedResponseTime << endl;
	//std::cout << p5.processName << ":" << p5.beginTime << "  " << p5.endTime << "  " << p5.normalizedResponseTime << endl;


	int n;
	std::cin >> n;

}

void show(Algorithm::ProcessesList &pro)
{
	Algorithm::ProcessIterator iterator;
	cout << "完成时间" << "\t" << "周转时间" << "\t" << "归一化响应时间" << "\t"<< endl;
	for (iterator=pro.begin();iterator!=pro.end();++iterator)
	{		
		cout << (*iterator)->endTime << "\t\t" << (*iterator)->turnoverTime << "\t\t" << (*iterator)->normalizedResponseTime << endl;
	}
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
}