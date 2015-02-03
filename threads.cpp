//THread.cpp
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

char public_class[10];

void *thread1(void *ptr)
{
	for(int i=0;i<10;i++)
	{
		public_class[i] = 'a';
		cout<<"This is a pthread1.\n"<<endl;
		sleep(1);
	}
	
	
	return 0;
}

void *thread2(void *ptr)
{
	for(int i=0;i<10;i++)
	{
		public_class[i] = 'b';
		cout<<"This is a pthread2.\n"<<endl;
		sleep(1);
		
	}
	
	return 0;
}

int main()
{
	pthread_t id1,id2;
	int ret1 = pthread_create(&id1,NULL,thread1,NULL);
	int ret2 = pthread_create(&id2,NULL,thread2,NULL);
	if(ret1)
	{
		cout<<"Creat pthread error!.\n"<<endl;
		return 1;
	}
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	//sleep(4);
	for(int i=0;i<10;i++)
	{
		cout<<public_class[i]<<endl;
		//public_class = 100-i;
		//cout<<"This is in main process!\t"<<public_class<<"\n"<<endl;
	}
	//pthread_join(id,NULL);

	return 0;
}