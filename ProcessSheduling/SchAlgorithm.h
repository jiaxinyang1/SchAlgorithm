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

		string	processName;//��������
		double		reachTime = 0;//����ʱ��
		double		runTime;//����ʱ��
		double		beginTime=-1;//��ʼʱ��
		double		endTime;//����ʱ��
		double		turnoverTime;//��תʱ��
		double		normalizedResponseTime;//Tr/Ts
		double     responseRatio ;;//��Ӧ��
		double		waitTime;//�ȴ�ʱ��
		double		lastTime=0;//�Ѿ�����ʱ��
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
		//���̶���
		typedef  list<Process*> ProcessesList;
		typedef ProcessesList::iterator ProcessIterator;
		//��ʼ����
		ProcessesList processes_list;
		//��������
		ProcessesList ready_list;

		ProcessIterator iterator;
		//����ʱ����
		double axisTime = 0;
		virtual void run() = 0;

		//��ӽ���
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
		//������תʱ��ƽ��ֵ
		static  double	turnoverTimeAverage( ProcessesList &pro)
		{
			double ave = 0;
			for (ProcessIterator iterator1 = pro.begin();iterator1!=pro.end();++iterator1)
			{
				ave += (*iterator1)->turnoverTime;
			}
			return  ave / pro.size();
		}
		//�����һ����Ӧʱ��ƽ��ֵ
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


	//�����ȷ���
	class FCFS : public Algorithm
	{
	private:

	public:
	
		void run() override
		{
			for (iterator=processes_list.begin();iterator!=processes_list.end();++iterator)
			{
				(*iterator)->beginTime = axisTime;
				//ʱ����ǰ��
				axisTime += (*iterator)->runTime;
				//�������ʱ��
				(*iterator)->endTime = axisTime;
				//������תʱ�� ����ʱ�������ʱ��
				(*iterator)->turnoverTime = (*iterator)->endTime - (*iterator)->reachTime;
				//�����һ����Ӧʱ�� Tr/Ts
				(*iterator)->normalizedResponseTime = (*iterator)->turnoverTime / (*iterator)->runTime;
			} 
		}
	};


	//�����Ӧ������
	class HRRN :public Algorithm
	{

	public:

		//���㵽��ʱ��
		void WaitTime()
		{
		
				for (iterator = processes_list.begin(); iterator != processes_list.end(); ++iterator)
				{
					//�ȴ�ʱ����ڵ�ǰʱ�������ʱ��
					(*iterator)->waitTime = axisTime - (*iterator)->reachTime;
				}
		
		
		}
		//������Ӧ��
		void  ResponseRatio()
		{
		
		
			for (iterator = processes_list.begin(); iterator != processes_list.end(); ++iterator)
			{
				//��Ӧ��Ϊ���ȴ�ʱ��+Ҫ�����ʱ�䣩/Ҫ�����ʱ��=�ȴ�ʱ��/Ҫ�����ʱ��+1
				(*iterator)->responseRatio = (*iterator)->waitTime / (*iterator)->runTime + 1;
			}
	
	
		}
		//����Ӧ�ȷ�������Ԫ��
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
				
				//���㿪ʼʱ��
				now->beginTime = axisTime;
				//ʱ����ǰ��
				axisTime =axisTime+ now->runTime;
				//����ʱ��
				now->endTime = axisTime;
				//��תʱ��
				now->turnoverTime = now->endTime - now->reachTime;
				//Tr/Ts
				now->normalizedResponseTime = now->turnoverTime / now->runTime;
				//������Ϻ��Ƴ����У�������μ���
				processes_list.remove(now);
			//�ٴμ�����Ӧ�ȣ��õ�����Ԫ��
				if(!processes_list.empty())
				{
					WaitTime();
					ResponseRatio();
					now = MaxResponseRatio();
				}					
			}
		};
	};

	//��̽�������
	class SPN:public Algorithm
	{
	private:

		
	public:
	
		//�������ʱ�����
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
		//������Ľ��̼����������
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

				//���㿪ʼʱ��
				now->beginTime = axisTime;
				//ʱ����ǰ��
				axisTime = axisTime + now->runTime;
				//����ʱ��
				now->endTime = axisTime;
				//��תʱ��
				now->turnoverTime = now->endTime - now->reachTime;
				//Tr/Ts
				now->normalizedResponseTime = now->turnoverTime / now->runTime;
				ready_list.remove(now);
				processes_list.remove(now);
				count--;
			}
		
		}
	};
	//��ת
	class RR :public Algorithm
	{
	private:
		//����ʱ��Ƭ����
		int round = 1;
	public:
	

		//����ʱ��Ƭֵ
		void setRound(int value)
		{
			round = value;
		}
		//��ʼ��һЩֵ
		void init()
		{
		for (iterator = processes_list.begin(); iterator != processes_list.end(); ++iterator)
			{
				//��ʼ��ʣ��ʱ��
				(*iterator)->lastTime = (*iterator)->runTime;
			}

		}
	
	
		//������Ľ��̲����������
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
				//��ʱ��Ƭ��ִ�����	
				if(now->lastTime<=round)
				{
					axisTime += now->lastTime;
					now->endTime = axisTime;
					//��תʱ��
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
				
				//��ʱ��Ƭ��δִ����� 
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
