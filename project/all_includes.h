/*
Тут всі інклуди , дефайни і темплейти
*/
#ifndef MAIN_HEAD_H_INCLUDED

    #define MAIN_HEAD_H_INCLUDED

    #include <GL/glut.h>
    #include <IL/ilut.h>
    #include <bits/stdc++.h>

    #define INF 1e9
    #define pb push_back
    #define mp make_pair
    #define fi first
    #define se second
    #define x first
    #define y second
    #define I "%d"
    #define II "%d%d"
    #define III "%d%d%d"
    #define IIII "%d%d%d%d"

    using namespace std;

    typedef GLuint Sprite;  //GLuint - номер текстури
    typedef vector<int> vi;
    typedef pair <int, int> pii;
    typedef vector<pii> vii;
    typedef long long ll;
    typedef unsigned long long ull;
    typedef long double ld;

    const ld PI = acos(-1.0);

    template <typename type> inline type sqr(type x)
    {
        return x*x;
    }

#endif // MAIN_HEAD_H_INCLUDED


// TODO: reference additional headers your program requires here
