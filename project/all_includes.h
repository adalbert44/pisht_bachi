/*
Тут всі інклуди , дефайни і темплейти
*/

#pragma once

#include <string>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <time.h>
#include <ctime>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define I "%d"
#define II "%d%d"
#define III "%d%d%d"
#define IIII "%d%d%d%d"

#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif

using namespace std;

typedef string Sprite; // TODO: реалізувати класс картинки !!!
typedef vector<int> vi;
typedef pair <int, int> pii;
typedef vector<pii> vii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;


template <typename type> inline type sqr(type x)
{
	return x*x;
}


// TODO: reference additional headers your program requires here
