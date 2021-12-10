#pragma once
#include<iostream>
#include<thread>
#include<random>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<chrono>
using namespace std;

static const int bufSize=6;          //缓存区数量
static const int num_of_product=20; //产品数


struct Item {
	int ID;
	int value;
};




