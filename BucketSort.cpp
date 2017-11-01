#include "BucketSort.h"

#include <string>
#include <algorithm>
#include <cmath>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <sstream>



int getDigit(unsigned num,int d){ //get a digit of a number , d ranges from left(0) to right(9)
	int n_digits = 1;
	unsigned num_copy = num;
	while(num_copy/10!=0){
		n_digits++;
		num_copy=num_copy/10;
	}
	if(d>=n_digits)return -1;  //padding -1
	int temp =1;	
	for (int i=0;i<n_digits-1-d;i++){temp*=10;}
	return (num/temp)%10;
}


std::vector<unsigned int>* msdsort(std::vector<unsigned int>* numbersToSort,int pider){ //MSD redix sort using resursion  
	if((*numbersToSort).size()==0||(*numbersToSort).size()==1){
		return numbersToSort;
		}
	
	std::vector <std::vector<unsigned int>> bins; //create bins
	for (unsigned i = 0;i<11;i++){    // bins form #0 to #10 represent digit: -1,0,1,2,3,4,5,6,7,8,9
		std::vector <unsigned int> digit_container;
		bins.push_back(digit_container);
	}
		
	int digit ; 
	std::vector<unsigned int>* ContainerToSort; //container for all numbers to be sorted in a thread
	ContainerToSort = numbersToSort;

	//assign into bins
	for (auto iter = (*ContainerToSort).begin();iter!=(*ContainerToSort).end();iter++){
		auto num = *iter;

		digit = getDigit(num,pider);
		(bins[digit+1]).push_back(*iter);
	}
	(*ContainerToSort).clear();
	pider++;

	if (pider <=9){
		for (int i=0;i<11;i++){// for each bin
			
				auto newbin = msdsort(&(bins[i]),pider);//resursion
				(bins[i]) = *newbin;
		}
	}	
	//collect numbers in bins
	for(int i =0;i<11;i++){
		auto thisbin = bins[i];
		(*ContainerToSort).insert((*ContainerToSort).end(),thisbin.begin(),thisbin.end());
	}	
	numbersToSort = ContainerToSort;
	return ContainerToSort;
}


bool aLessB(const unsigned int& x, const unsigned int& y) { //Define less
	if(x==y)return false;
	for (int i=0;i<10;i++){
		if(getDigit(x,i)<getDigit(y,i))return true;
		if(getDigit(x,i)>getDigit(y,i))return false;
	}
	return false;
}




void BucketSort::sort(unsigned int numCores) {
	const unsigned int Cores = std::thread::hardware_concurrency();
	if (numCores>Cores){numCores = Cores;}//Examine number of cores

	std::vector <std::vector<unsigned int>> inputs;// contains several buckets = number of threads

	for (unsigned i = 0;i<numCores;i++){   //Create the buckets containing numbers
		std::vector <unsigned int> newVector;
		inputs.push_back(newVector);
	}

	//Devide all thr numbers to be sorted into buckets
	int idx = 0;
	for (auto iter = numbersToSort.begin();iter!=numbersToSort.end();iter++){
		(inputs[idx%numCores]).push_back(*iter);
		idx ++;
	}

	//MultiThreading
	for (unsigned i = 0; i < numCores; i++) { 
		
		std::thread new_thread(msdsort,&(inputs[i]),0);
		new_thread.join();
	}

	//Merge the results from multithreaded approach
	std::vector <unsigned int> result;
	int small_idx = 0;
	unsigned int smallest = 999999999; //Maximum in this unsigned int case
	
	while(result.size()<numbersToSort.size()){
		small_idx = 0;
		smallest = 999999999;
		
		for (unsigned i = 0; i < numCores; i++) { 
			if((inputs[i]).size()==0){continue;}
			if (aLessB( (inputs[i])[0] , smallest ) ){ //select the smallest one
				small_idx = i;
				smallest = (inputs[i])[0];
			}
		}
			result.push_back(smallest);
			(inputs[small_idx]).erase((inputs[small_idx]).begin());
		}

	numbersToSort = result;
}
