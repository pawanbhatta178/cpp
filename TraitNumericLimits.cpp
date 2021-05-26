/* general numeric limits as default for any type */
template <typename T>
class numeric_limits
{
public:
    // no specialization for numeric limit exists
    static const bool is_specialized = false;
};

template <>
class numeric_limits<int>
{
public:
    // Now we have a specialization for numeric limit for int.
    // It does exists.
    static const bool is_specialized = true;
    static int min() throw()
    {
        return -2147483648;
    }
    static int max() throw()
    {
        return 2147483647;
    }
    static const int digits = 31;
};