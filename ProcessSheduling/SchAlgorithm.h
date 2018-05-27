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
		ostream &operator<<(ostream &out,Process &pro)
		{
			cout<<
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
		virtual void run() = 0;
	};


	//�����ȷ���
	class FCFS : public Algorithm
	{
	private:
		ProcessesList processes_list;
		ProcessIterator iterator;
		//����ʱ����
		double axisTime=0;
		
	public:
		int add(Process &process)
		{
			processes_list.push_back(&process);
			return 1;
		}
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
	private:
		//��ʼ����
		ProcessesList processes_list;
		ProcessIterator iterator;
		//����ʱ����
		double axisTime = 0;
	public:

		int add(Process &process)
		{
			processes_list.push_back(&process);
			return 1;
		}
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
		//��ʼ����
		ProcessesList processes_list;
		//��������
		ProcessesList ready_list;

		ProcessIterator iterator;
		//����ʱ����
		double axisTime = 0;
		
	public:
		int add(Process &process)
		{
			processes_list.push_back(&process);
			return 1;
		}
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

		//��ʼ����
		ProcessesList processes_list;
		//��������
		ProcessesList ready_list;
		ProcessIterator iterator;
		//����ʱ����
		double axisTime = 0;

		//����ʱ��Ƭ����
		int round=4;

	public:
		int add(Process &process)
		{
			processes_list.push_back(&process);
			return 1;
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
