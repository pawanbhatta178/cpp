// template <class T>
// class Matrix
// {
// private:
//     int low, high;
//     SA<T> *p;

// public:
//     Matrix()
//     {
//         low = 0;
//         high = -1;
//         p = NULL;
//     }
//     Matrix(int l, int h)
//     {
//         if (h < l)
//         {
//             cout << "Matrix constructor error in bounds definition" << endl;
//             exit(1);
//         }
//         low = l;
//         high = h;
//         p = new SA<T>[h - l + 1];
//         cout << "Matrix constructor with double args ran: low: " << low << " high: " << high << endl;
//     }

//     SA<T> &operator[](int i)
//     {
//         cout << "Overloaded [] operator called: " << low << " high: " << high << endl;
//         if (i < low || i > high)
//         {
//             cout << "index " << i << " out of range" << endl;
//             exit(1);
//         }
//         return p[i - low];
//     }

//     ~Matrix()
//     {
//         cout << "Matrix destructor with double args ran: low: " << low << " high: " << high << endl;
//         delete[] p;
//     }
// };