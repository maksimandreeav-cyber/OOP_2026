namespace {
    const int kMinSizeContainer = 4;
}

template <typename T>
class Container {
    private:
    int max_size;
    int size;
    T* pdata;

    public:
    Container(int s = kMinSizeContainer);

    Container(Container other);

    int GetMaxSize() const;

    int GetSize() const;

    T* GetPData() const;


};