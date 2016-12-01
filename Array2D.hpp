template<class T> class Array2D {
    public:
        T* array;
        unsigned int h;
        unsigned int w;
        
        Array2D(unsigned int _h, unsigned int _w) :
            h(_h),
            w(_w),
            array(new T[_h * _w]) {
        }
        
        ~Array2D() {
            delete[] array;
            array = NULL;
        }
    
        //writes pointed value, therefore will lock
        T* operator[](const unsigned int k) {
            return &array[k * w];
        }
};

