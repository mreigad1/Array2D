#include <assert.h>
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

        Array2D(const Array2D<T>& other) : h(other.h), w(other.w), array(NULL) {
            array = new T[h * w];
            for (int i = 0; i < h * w; i++) {
                array[i] = other.array[i];
            }
        }
        
        ~Array2D() {
            delete[] array;
            array = NULL;
        }
    
        //returns address of first item in row
        T* operator[](const unsigned int k) {
            assert(k < h);
            return &array[k * w];
        }

        //copies each data item in array into new array
        Array2D<T>& operator=(const Array2D<T>& other) {
            if (NULL != array) {
                delete[] array;
                array = NULL;
            }
            h = other.h;
            w = other.w;
            array = new T[h * w];
            for (int i = 0; i < h * w; i++) {
                array[i] = other.array[i];
            }
            return *this;
        }
};

