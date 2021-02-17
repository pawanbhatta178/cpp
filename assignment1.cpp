#include <iostream>
using namespace std;
class queue
{
private:
    char *s;
    int F, R, size;

public:
    queue(int i = 4)
    {
        s = new char[i];
        size = i;
        F = R = -1;
    }

    ~queue()
    {
        delete[] s;
    }

    bool empty()
    {
        return F == R;
    }

    /*	bool full()//this is for a non circular queue
	{
		if (F==-1 && R==size-1)
			return true;
		for (int i=0; i<=F; i++)
			s[i]=s[F+i+1];
		R=R-F-1;
		F=-1;
		return false;
	}*/

    bool full()
    {
        if ((R + 1) % 5 == F)
            return true;
        return false;
    }

    /*	void add (char c)//non circular add
	{
		if (full())
		{
			cout << "queue is full";
			exit(1);
		}
		R++;
		s[R]=c;
	}*/

    char add(char c)
    {
        if (full())
        {
            cout << "queue is full";
            exit(1);
        }
        R = (R + 1) % size;
        s[R] = c;
        return s[R];
    }

    /*	char del()// non circular
	{
		if (empty())
		{
			cout << "queue empty";
			exit(1);
		}
		F++;
		return s[F];
	}*/

    char del()
    {
        if (empty())
        {
            cout << "queue empty";
            exit(1);
        }
        F = (F + 1) % size; //only difference
        return s[F];
    }
};
//Because char arrays are treated differently to other arrays when you stream them to cout - the << operator is overloaded for const char*. This is for compatibility with C, so that null-terminated char arrays are treated as strings.
int main()
{
    queue q;
    q.add('a');
    q.add('b');
    q.add('c');
    // cout << q.add('a') << q.add('b') << q.add('c') << endl;
    cout << q.del() << q.del() << q.del() << endl;
    return 0;
}