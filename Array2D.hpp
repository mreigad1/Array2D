#ifdef ARRAY2D_ASSERT
    #include <assert.h>
#endif
#ifdef ARRAY2D_FUNCTIONAL
    #include <functional>
#endif

template<class T> class Array2D {
    public:
        //public read-only references for dimensions
        const unsigned int& Height;
        const unsigned int& Width;

        Array2D(unsigned int _h, unsigned int _w) :
            h(_h),
            w(_w),
            Height(h),
            Width(w),
            array(new T[_h * _w]) {
                #ifdef ARRAY2D_ASSERT
                    assert(0 != h);
                    assert(0 != w);
                #endif
        }

        Array2D(const Array2D<T>& other) :
            h(other.h),
            w(other.w),
            Height(h),
            Width(w),
            array(NULL) {
                #ifdef ARRAY2D_ASSERT
                    assert(0 != h);
                    assert(0 != w);
                #endif
                array = new T[h * w];
                for (int i = 0; i < h * w; i++) {
                    array[i] = other.array[i];
                }
        }
        
        ~Array2D() {
            #ifdef ARRAY2D_ASSERT
                assert(nullptr != array);
            #endif
            delete[] array;
            array = nullptr;
        }

        const T& read(unsigned int y, unsigned int x) const {
            return array[y * Width + x];
        }
    
        //returns address of first item in row
        //non-const access. reads on const arrays done with read
        T* operator[](const unsigned int k) {
            #ifdef ARRAY2D_ASSERT
                assert(k < h);
            #endif
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
            #ifdef ARRAY2D_ASSERT
                assert(0 != h);
                assert(0 != w);
            #endif
            array = new T[h * w];
            for (int i = 0; i < h * w; i++) {
                array[i] = other.array[i];
            }
            return *this;
        }

        #ifdef ARRAY2D_FUNCTIONAL
            Array2D<T> transform(const std::function<T(T)>& func) const {
                Array2D<T> rv = *this;
                for (unsigned int i = 0; i < Height; i++) {
                    for (unsigned int j = 0; j < Width; j++) {
                        rv[i][j] = func(rv[i][j]);
                    }
                }
                return rv;
            }

            //avoids overhead of copying, cannot be performed on const
            void inPlace_Transform(const std::function<T(T)>& func) {
                for (unsigned int i = 0; i < Height; i++) {
                    for (unsigned int j = 0; j < Width; j++) {
                        rv[i][j] = func(rv[i][j]);
                    }
                }
            }
        #endif

    private:
        T* array;
        unsigned int h;
        unsigned int w;
};

