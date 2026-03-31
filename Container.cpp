Container::Container(int s = kMinSizeContainer) : max_size(s), size(0), pdata(new T[s]) {}

Container::Container(Container other) : max_size(other.GetMaxSize()), size(other.GetSize), pdata(new T[max_size]) {
    for (size_t i = 0; i < size; ++i) {
        if constexpr (std::is_same_v<T, char*>) {
            size_t len = strlen(other.GetPData()[i]) + 1;
            pdata[i] = new char[len];
            strcpy(pdata[i], other.GetPData()[i]);
        } else {
            pdata[i] = other.GetPData()[i];
        }
    }  
}






int Container::GetMaxSize() const {
    return max_size;
}

int Container::GetSize() const {
    return size;
}

T* Container::GetPData() const {
    return pdata;
}