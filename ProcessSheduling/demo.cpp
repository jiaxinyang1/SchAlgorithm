
#include "SchAlgorithm.h"
#include <iostream>
using namespace SchAlgorithm;
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
	p2.reachTime =2;
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


	RR test_rr;
	test_rr.add(p1);
	test_rr.add(p2);
	test_rr.add(p3);
	test_rr.add(p4);
	test_rr.add(p5);
	test_rr.run();
	std::cout << p1.processName << ":" << p1.beginTime << "  " << p1.endTime << "  " << p1.normalizedResponseTime << endl;
	std::cout << p2.processName << ":" << p2.beginTime << "  " << p2.endTime << "  " << p2.normalizedResponseTime << endl;
	std::cout << p3.processName << ":" << p3.beginTime << "  " << p3.endTime << "  " << p3.normalizedResponseTime << endl;
	std::cout << p4.processName << ":" << p4.beginTime << "  " << p4.endTime << "  " << p4.normalizedResponseTime << endl;
	std::cout << p5.processName << ":" << p5.beginTime << "  " << p5.endTime << "  " << p5.normalizedResponseTime << endl;


	int n;
	std::cin >> n;

}

