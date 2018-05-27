#pragma once
#include <string>
#include <list>
#include <algorithm>
#include <iostream>
using namespace  std;

namespace SchAlgorithm
{
	class Process
	{
	public:

		string	processName;//进程名字
		double		reachTime = 0;//到达时间
		double		runTime;//服务时间
		double		beginTime=-1;//开始时间
		double		endTime;//结束时间
		double		turnoverTime;//周转时间
		double		normalizedResponseTime;//Tr/Ts
		double     responseRatio ;;//响应比
		double		waitTime;//等待时间
		double		lastTime=0;//已经运行时间
		friend 	ostream & operator << (ostream &out,Process &pro) 
		{
			cout << pro.endTime << "\t" << pro.turnoverTime << "\t" << pro.normalizedResponseTime << endl;
			return out;
		}
	};
	
	class Algorithm
	{
	public:
		virtual ~Algorithm() = default;
		//进程队列
		typedef  list<Process*> ProcessesList;
		typedef ProcessesList::iterator ProcessIterator;
		//初始队列
		ProcessesList processes_list;
		//就绪队列
		ProcessesList ready_list;

		ProcessIterator iterator;
		//定义时间轴
		double axisTime = 0;
		virtual void run() = 0;

		//添加进程
		int add(Process &process)
		{
			processes_list.push_back(&process);
			return 1;
		}

		int add(ProcessesList &pro)
		{
			processes_list = pro;
			return  1;
		}
		//计算周转时间平均值
		static  double	turnoverTimeAverage( ProcessesList &pro)
		{
			double ave = 0;
			for (ProcessIterator iterator1 = pro.begin();iterator1!=pro.end();++iterator1)
			{
				ave += (*iterator1)->turnoverTime;
			}
			return  ave / pro.size();
		}
		//计算归一化响应时间平均值
		static  double	normalizedResponseTimeAverage(ProcessesList &pro)
		{
			double ave = 0;
			for (ProcessIterator iterator1 = pro.begin(); iterator1 != pro.end(); ++iterator1)
			{
				ave += (*iterator1)->normalizedResponseTime;
			}
			return  ave / pro.size();
		}


	};


	//先来先服务
	class FCFS : public Algorithm
	{
	private:

	public:
	
		void run() override
		{
			for (iterator=processes_list.begin();iterator!=processes_list.end();++iterator)
			{
				(*iterator)->beginTime = axisTime;
				//时间轴前进
				axisTime += (*iterator)->runTime;
				//计算结束时间
				(*iterator)->endTime = axisTime;
				//计算周转时间 结束时间减到达时间
				(*iterator)->turnoverTime = (*iterator)->endTime - (*iterator)->reachTime;
				//计算归一化响应时间 Tr/Ts
				(*iterator)->normalizedResponseTime = (*iterator)->turnoverTime / (*iterator)->runTime;
			} 
		}
	};


	//最短响应比优先
	class HRRN :public Algorithm
	{

	public:

		//计算到达时间
		void WaitTime()
		{
		
				for (iterator = processes_list.begin(); iterator != processes_list.end(); ++iterator)
				{
					//等待时间等于当前时间减到达时间
					(*iterator)->waitTime = axisTime - (*iterator)->reachTime;
				}
		
		
		}
		//计算响应比
		void  ResponseRatio()
		{
		
		
			for (iterator = processes_list.begin(); iterator != processes_list.end(); ++iterator)
			{
				//响应比为（等待时间+要求服务时间）/要求服务时间=等待时间/要求服务时间+1
				(*iterator)->responseRatio = (*iterator)->waitTime / (*iterator)->runTime + 1;
			}
	
	
		}
		//按响应比返回最大的元素
		Process * MaxResponseRatio()
		{
		
				Process *max = (*processes_list.begin());
				for (iterator = processes_list.begin(); iterator != processes_list.end(); ++iterator)
				{

					if ((*iterator)->responseRatio > max->responseRatio)
					{

						max = (*iterator);
					}
				}
				return max;
		}
		void run() override
		{
			Process *now=(*processes_list.begin());
			while (!processes_list.empty())
			{
				
				//计算开始时间
				now->beginTime = axisTime;
				//时间轴前进
				axisTime =axisTime+ now->runTime;
				//结束时间
				now->endTime = axisTime;
				//周转时间
				now->turnoverTime = now->endTime - now->reachTime;
				//Tr/Ts
				now->normalizedResponseTime = now->turnoverTime / now->runTime;
				//运行完毕后移出队列，避免二次计算
				processes_list.remove(now);
			//再次计算响应比，拿到最大的元素
				if(!processes_list.empty())
				{
					WaitTime();
					ResponseRatio();
					now = MaxResponseRatio();
				}					
			}
		};
	};

	//最短进程优先
	class SPN:public Algorithm
	{
	private:

		
	public:
	
		//返回最短时间进程
		Process *MinTimeProcess()
		{
			Process *min=(*ready_list.begin());
			for (iterator=ready_list.begin();iterator!=ready_list.end();++iterator)
			{
				if ((*iterator)->runTime<min->runTime)
				{
					min = (*iterator);
				}
			}
			return  min;
		}
		//将到达的进程加入就绪队列
		void Insert()
		{
			for (iterator=processes_list.begin();iterator!=processes_list.end();++iterator)
			{
				if (axisTime>=(*iterator)->reachTime)
				{
					ready_list.push_back((*iterator));
				}
			}
		}
		void run() override
		{
			int count = processes_list.size();
			while (count > 0)
			{
				Insert();
				Process *now = MinTimeProcess();

				//计算开始时间
				now->beginTime = axisTime;
				//时间轴前进
				axisTime = axisTime + now->runTime;
				//结束时间
				now->endTime = axisTime;
				//周转时间
				now->turnoverTime = now->endTime - now->reachTime;
				//Tr/Ts
				now->normalizedResponseTime = now->turnoverTime / now->runTime;
				ready_list.remove(now);
				processes_list.remove(now);
				count--;
			}
		
		}
	};
	//轮转
	class RR :public Algorithm
	{
	private:
		//定义时间片长度
		int round = 1;
	public:
	

		//设置时间片值
		void setRound(int value)
		{
			round = value;
		}
		//初始化一些值
		void init()
		{
		for (iterator = processes_list.begin(); iterator != processes_list.end(); ++iterator)
			{
				//初始化剩余时间
				(*iterator)->lastTime = (*iterator)->runTime;
			}

		}
	
	
		//将到达的进程插入就绪队列
		void Insert()
		{			
			for (iterator = processes_list.begin(); iterator != processes_list.end(); )
			{
				if (axisTime >= (*iterator)->reachTime)
				{
			
					ready_list.push_back(*iterator);
					iterator = processes_list.erase(iterator);
				}
				else
					++iterator;
			}
		}
	 	void run() override
		{
			init();
			Insert();
			Process *now=*ready_list.begin();
			now->beginTime = axisTime;
			while (!ready_list.empty())
			{	
				//在时间片内执行完毕	
				if(now->lastTime<=round)
				{
					axisTime += now->lastTime;
					now->endTime = axisTime;
					//周转时间
					now->turnoverTime = now->endTime - now->reachTime;
					//Tr/Ts
					now->normalizedResponseTime = now->turnoverTime / now->runTime;
					ready_list.pop_front();
					Insert();
					if (!ready_list.empty())
					{
						now = *ready_list.begin();
						now->beginTime = axisTime;
					}
				}
				
				//在时间片内未执行完毕 
				else if (now->lastTime>round)
				{
					axisTime += round;
					now->lastTime -= round;
					Insert();
					ready_list.push_back(now);
					ready_list.pop_front();					
					now = *ready_list.begin();
				}
			}
		}
	};
}
