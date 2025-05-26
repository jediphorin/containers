#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

#include <iostream>
#include <initializer_list>
#include <utility>

/*
HEADER FILE
*/
namespace s21
{
    template <class T>
    class VectorIterator;

    template <class T>
    class VectorConstIterator;

    // Test vector class with some basic example operations and concepts
    template <class T>
    class Vector
    {
        // private attributes
    private:
        size_t m_size;
        size_t m_capacity;
        T *arr;
        // public attribures
    public:
        // member types
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        // using iterator = T *;
        using iterator = VectorIterator<T>;
        // using const_iterator = const T *;
        using const_iterator = VectorConstIterator<T>;
        using size_type = size_t;
        // private method
        // private:
        //     void reserve_more_capacity(size_type size);
        // public methods
    public:
        // Vector Member functions
        // default constructor (simplified syntax for assigning values to attributes)
        Vector() noexcept : m_size(0U), m_capacity(0U), arr(nullptr)
        {
            std::cout << "default constructor" << std::endl;
        }

        // TESTED
        explicit Vector(size_type n) : m_size(n), m_capacity(n), arr(n ? new T[n]() : nullptr) {}
        // parametrized constructor for fixed size vector (explicit was used in order to
        // avoid automatic type conversion)
        /*explicit Vector(size_type n) : m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr)
        {
            std::cout << "parametrized constructor" << std::endl;

            if (n == 0)
                std::cout << "n = 0" << std::endl;
        }*/
        // initializer list constructor (allows creating lists with initializer lists, see main.cpp)
        Vector(std::initializer_list<value_type> const &items);
        //  TESTED
        Vector(const Vector &v) : m_size(v.m_size), m_capacity(v.m_capacity)
        {
            std::cout << "copy constructor" << std::endl;
            arr = new T[m_capacity];
            try
            {
                for (long unsigned int i = 0; i < m_size; i++)
                {
                    this->arr[i] = v.arr[i];
                }
                // Копируем элементы
                // std::copy(v.arr, v.arr + m_size, arr);
            }
            catch (...)
            {
                delete[] arr; // Освобождаем память в случае исключения
                throw;        // Пробрасываем исключение дальше
            }
        }
        // copy constructor with simplified syntax
        /*Vector(const Vector &v) : m_size(v.m_size), m_capacity(v.m_capacity)
        {
            std::cout << "copy constructor" << std::endl;
            arr = new T[m_capacity];
            // std::copy(v.arr, v.arr + m_size, arr);
            for (long unsigned int i = 0; i < m_size; i++)
            {
                this->arr[i] = v.arr[i];
            }
        }*/
        // TESTED
        // move constructor with simplified syntax
        Vector(Vector &&v) noexcept : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr)
        {
            std::cout << "move constructor" << std::endl;
            v.arr = nullptr;
            v.m_size = 0;
            v.m_capacity = 0;
        }

        // TESTED destructor
        ~Vector()
        {
            delete[] arr; // delete[] безопасно работает с nullptr
        }
        /*~Vector()
        {
            std::cout << "destructor" << std::endl;
            if (arr)
            {
                delete[] arr;
                arr = nullptr;
                m_capacity = 0;
                m_size = 0;
            }
        }*/
        // TESTED
        Vector &operator=(Vector &&v) noexcept
        {
            if (this != &v)
            {
                delete[] arr;
                arr = v.arr;
                m_size = v.m_size;
                m_capacity = v.m_capacity;
                v.arr = nullptr;
                v.m_size = 0;
                v.m_capacity = 0;
            }
            return *this;
        }
        /*Vector &operator=(Vector &&v)
        {
            std::cout << "operator=" << std::endl;
            if (this != &v)
            {
                if (arr)
                {
                    delete[] arr;
                    arr = nullptr;
                    m_capacity = 0;
                    m_size = 0;
                }
                m_size = v.m_size;
                m_capacity = v.m_capacity;
                arr = v.arr;
                v.arr = nullptr;
                v.m_size = 0;
                v.m_capacity = 0;
            }
            return *this;
        }*/

        // Vector Element access
        const_reference at(size_type pos) const;
        reference at(size_type pos);
        // value_type at(size_type i);
        reference operator[](size_type pos) noexcept;
        const_reference operator[](size_type pos) const noexcept;
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;
        T *data() const noexcept;

        // Vector Iterators
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        iterator end() noexcept;

        // Vector Capacity
        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;
        void reserve(size_type size);
        size_type capacity() const noexcept;
        void shrink_to_fit();

        // Vector Modifiers
        void clear() noexcept;
        iterator insert(iterator pos, const_reference value);
        // void erase(iterator pos);
        void erase(const_iterator pos);
        void push_back(value_type v);
        void pop_back() noexcept;
        void swap(Vector &other) noexcept;
        // Inserts new elements into the container directly before pos.	List, Vector.
        template <class... Args>
        iterator insert_many(const_iterator pos, Args &&...args);
        // Appends new elements to the end of the container.	List, Vector, Queue, Stack.
        template <class... Args>
        void insert_many_back(Args &&...args);
    };

    template <class T>
    class VectorIterator
    {
        friend class Vector<T>;
        friend class VectorConstIterator<T>;

        using value_type = T;
        using pointer = T *;
        using reference = T &;

    private:
        pointer ptr_;

    public:
        VectorIterator()
        {
            std::cout << "VectorIterator def constructor" << std::endl;
            ptr_ = nullptr;
        }
        VectorIterator(pointer ptr)
        {
            std::cout << "VectorIterator param constructor" << std::endl;
            ptr_ = ptr;
        }

        pointer operator->() const
        {
            std::cout << "VectorIterator operator->" << std::endl;
            return ptr_;
        }

        value_type &operator*() const
        {
            // std::cout << "VectorIterator operator*" << std::endl;
            if (ptr_ == nullptr)
            {
                throw std::out_of_range("Cannot dereference nullptr.");
            }
            return *ptr_;
        }
        //  только для чтения
        /*value_type operator*() const
        {
            // std::cout << "VectorIterator operator*" << std::endl;
            if (ptr_ == nullptr) {
                throw std::out_of_range("Cannot dereference nullptr.");
            }
            return *ptr__;
        }*/

        VectorIterator &operator--()
        {
            std::cout << "VectorIterator operator pre--" << std::endl;

            if (ptr_ == nullptr)
            {
                throw std::out_of_range("Iterator cannot be decremented: nullptr.");
            }
            --ptr_;
            return *this;
        }
        VectorIterator operator--(int)
        {
            std::cout << "VectorIterator operator post--" << std::endl;

            if (ptr_ == nullptr)
            {
                throw std::out_of_range("Iterator cannot be decremented: nullptr.");
            }
            VectorIterator buffer = *this;
            --ptr_;
            return buffer;
        }
        // TESTED
        VectorIterator &operator++()
        {
            std::cout << "VectorIterator operator pre++" << std::endl;
            ptr_++;
            return *this;
        }
        // TESTED
        VectorIterator operator++(int)
        {
            //  в оригинале этой проверки нет
            /*if (ptr_ == nullptr) {
                throw std::out_of_range("Iterator cannot be incremented: nullptr.");
            }*/

            std::cout << "VectorIterator operator post++" << std::endl;
            VectorIterator buffer = *this;
            ++(*this);
            return buffer;
        }

        VectorIterator operator+(const size_t offset)
        {
            std::cout << "VectorIterator operator+" << std::endl;
            VectorIterator buffer(this->ptr_ + offset);
            return buffer;
        }

        VectorIterator operator-(const size_t offset) const
        {
            std::cout << "VectorIterator operator-" << std::endl;
            VectorIterator buffer(this->ptr_ - offset);
            return buffer;
        }

        size_t operator-(const VectorIterator &other) const
        {
            std::cout << "VectorIterator operator-" << std::endl;
            return ptr_ - other.ptr_;
        }
        /*VectorIterator operator-(const size_t offset) {
            VectorIterator buffer(this->ptr_ - offset);
            std::cout << "VectorIterator operator-" << std::endl;
            return buffer;
        }*/
        bool operator==(const VectorIterator &other) const
        {
            std::cout << "VectorIterator operator==" << std::endl;
            return (ptr_ == other.ptr_);
        }
        bool operator!=(const VectorIterator &other) const
        {
            std::cout << "VectorIterator operator!=" << std::endl;
            return (ptr_ != other.ptr_);
        }
        bool operator>(const VectorIterator &other)
        {
            std::cout << "VectorIterator operator>" << std::endl;
            return (ptr_ > other.ptr_);
        }

        bool operator>=(const VectorIterator &other)
        {
            std::cout << "VectorIterator operator>=" << std::endl;
            return (ptr_ >= other.ptr_);
        }

        bool operator<(const VectorIterator &other)
        {
            std::cout << "VectorIterator operator<" << std::endl;
            return (ptr_ < other.ptr_);
        }

        bool operator<=(const VectorIterator &other)
        {
            std::cout << "VectorIterator operator<=" << std::endl;
            return (ptr_ <= other.ptr_);
        }

        operator VectorConstIterator<T>() const
        {
            std::cout << "VectorIterator operator VectorConstIterator" << std::endl;
            return VectorConstIterator<T>(ptr_);
        }
    };

    template <class T>
    class VectorConstIterator
    {

        friend class Vector<T>;
        friend class VectorIterator<T>;

        using value_type = T;
        using pointer = T *;
        using reference = T &;

    private:
        pointer ptr__;

    public:
        VectorConstIterator()
        {
            std::cout << "VectorConstIterator def constructor" << std::endl;
            ptr__ = nullptr;
        }
        VectorConstIterator(pointer ptr)
        {
            std::cout << "VectorConstIterator param constructor" << std::endl;
            ptr__ = ptr;
        }

        pointer operator->() const
        {
            std::cout << "VectorConstIterator operator->" << std::endl;
            return ptr__;
        }
        //  только для чтения
        /*value_type operator*() const
        {
            // std::cout << "VectorConstIterator operator*" << std::endl;
            if (ptr__ == nullptr) {
                throw std::out_of_range("Cannot dereference nullptr.");
            }
            return *ptr__;
        }*/
        value_type &operator*() const
        {
            // std::cout << "VectorConstIterator operator*" << std::endl;
            if (ptr__ == nullptr)
            {
                throw std::out_of_range("Cannot dereference nullptr.");
            }
            return *ptr__;
        }

        VectorConstIterator &operator++()
        {
            std::cout << "VectorConstIterator operator pre++" << std::endl;
            ptr__++;
            return *this;
        }
        VectorConstIterator &operator--()
        {
            std::cout << "VectorConstIterator operator pre--" << std::endl;
            --ptr__;
            return *this;
        }
        VectorConstIterator operator++(int)
        {
            std::cout << "VectorConstIterator operator post++" << std::endl;
            VectorConstIterator buffer = *this;
            ++(this);
            return buffer;
        }
        VectorConstIterator operator--(int)
        {
            std::cout << "VectorConstIterator operator post--" << std::endl;
            VectorConstIterator buffer = *this;
            --(this);
            return buffer;
        }
        VectorConstIterator operator+(const size_t offset)
        {
            std::cout << "VectorConstIterator operator+" << std::endl;
            VectorIterator buffer(this->ptr__ + offset);
            return buffer;
        }

        VectorConstIterator operator-(const size_t offset) const
        {
            std::cout << "VectorConstIterator operator-" << std::endl;
            VectorConstIterator buffer(this->ptr__ - offset);
            return buffer;
        }

        size_t operator-(const VectorConstIterator &other) const
        {
            std::cout << "VectorConstIterator operator-" << std::endl;
            return ptr__ - other.ptr__;
        }

        bool operator==(const VectorConstIterator &other) const
        {
            std::cout << "VectorConstIterator operator==" << std::endl;
            return (ptr__ == other.ptr__);
        }

        /*bool operator!=(const VectorConstIterator &other)
        {
            std::cout << "VectorConstIterator operator!=" << std::endl;
            return (ptr__ != other.ptr__);
        }*/
        bool operator!=(const VectorConstIterator &other) const
        {
            std::cout << "VectorConstIterator operator!=" << std::endl;
            return (ptr__ != other.ptr__);
        }

        bool operator>=(const VectorConstIterator &other)
        {
            std::cout << "VectorConstIterator operator>=" << std::endl;
            return (ptr__ >= other.ptr__);
        }
        bool operator<(const VectorConstIterator &other)
        {
            std::cout << "VectorConstIterator operator<" << std::endl;
            return (ptr__ < other.ptr__);
        }
        operator VectorIterator<T>() const
        {
            std::cout << "VectorConstIterator operator VectorIterator" << std::endl;
            return VectorIterator<T>(ptr__);
        }
    };
    // TESTED
    template <class T>
    inline Vector<T>::Vector(std::initializer_list<value_type> const &items)
        : m_size(items.size()), m_capacity(items.size())
    {
        arr = new value_type[m_capacity];
        try
        {
            // Копируем элементы
            // std::copy(items.begin(), items.end(), arr);
            int i = 0;
            for (auto it = items.begin(); it != items.end(); it++)
            {
                arr[i] = *it;
                i++;
            }
        }
        catch (...)
        {
            delete[] arr; // Освобождаем память в случае исключения
            throw;        // Пробрасываем исключение дальше
        }
    }
    /*template <class T>
    inline Vector<T>::Vector(std::initializer_list<value_type> const &items)
    {
        std::cout << "init constructor" << std::endl;
        arr = new value_type[items.size()];
        int i = 0;
        for (auto it = items.begin(); it != items.end(); it++)
        {
            arr[i] = *it;
            i++;
        }
        m_size = items.size();
        m_capacity = items.size();
    }*/

    /*template <class T>
    inline T Vector<T>::at(size_type i)
    {
        std::cout << "at" << std::endl;
        if (i >= m_size)
        {
            throw std::out_of_range("Index out of range.");
        }
        return arr[i];
    }*/
    // TESTED
    template <class T>
    inline T &Vector<T>::at(size_type i)
    {
        if (i >= m_size)
        {
            throw std::out_of_range("Index out of range.");
        }
        return arr[i];
    }
    // TESTED
    template <class T>
    inline const T &Vector<T>::at(size_type i) const
    {
        if (i >= m_size)
        {
            throw std::out_of_range("Index out of range.");
        }
        return arr[i];
    }

    /*template <class T>
    inline T &Vector<T>::operator[](size_type pos) noexcept
    {
        std::cout << "operator[]" << std::endl;
        return arr[pos];
    }*/
    //    TESTED
    template <class T>
    inline T &Vector<T>::operator[](size_type pos) noexcept
    {
        std::cout << "operator[]" << std::endl;
        return arr[pos];
    }
    // TESTED
    template <class T>
    inline const T &Vector<T>::operator[](size_type pos) const noexcept
    {
        std::cout << "operator[] const" << std::endl;
        return arr[pos];
    }
    // TESTED
    //  Можно вернуть noexcept и убрать исключение, чтобы соответствовать std::vector
    template <class T>
    inline T &Vector<T>::front()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Index out of range.");
        }
        std::cout << "front()" << std::endl;
        return arr[0];
    }
    // TESTED
    //  Можно вернуть noexcept и убрать исключение, чтобы соответствовать std::vector
    template <class T>
    inline const T &Vector<T>::front() const
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Index out of range.");
        }
        std::cout << "front() const" << std::endl;
        return arr[0];
    }

    /*template <class T>
    inline const T &Vector<T>::back() noexcept
    {
        std::cout << "back()" << std::endl;
        int index = m_size - 1;
        return arr[index];
    }*/

    // TESTED
    //  Можно вернуть noexcept и убрать исключение, чтобы соответствовать std::vector
    template <class T>
    inline T &Vector<T>::back()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Index out of range.");
        }
        std::cout << "back()" << std::endl;
        return arr[m_size - 1];
    }
    // TESTED
    //  Можно вернуть noexcept и убрать исключение, чтобы соответствовать std::vector
    template <class T>
    inline const T &Vector<T>::back() const
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Index out of range.");
        }
        std::cout << "back() const" << std::endl;
        return arr[m_size - 1];
    }
    /*
    // First element.
      constexpr const_iterator
      begin() const noexcept { return _M_array; }

      // One past the last element.
      constexpr const_iterator
      end() const noexcept { return begin() + size(); }*/

    // TESTED
    template <class T>
    inline VectorIterator<T> Vector<T>::begin() noexcept
    {
        std::cout << "begin()" << std::endl;
        return iterator(arr);
    }
    // TESTED
    template <class T>
    inline VectorConstIterator<T> Vector<T>::begin() const noexcept
    {
        return const_iterator(arr);
    }

    // TESTED
    template <class T>
    inline VectorIterator<T> Vector<T>::end() noexcept
    {
        std::cout << "end()" << std::endl;
        return iterator(arr + m_size);
    }

    // TESTED
    template <class T>
    inline bool Vector<T>::empty() const noexcept
    {
        std::cout << "empty()" << std::endl;
        return (m_size == 0) ? true : false;
    }

    // TESTED
    template <class T>
    inline size_t Vector<T>::size() const noexcept
    {
        std::cout << "getter size - size()" << std::endl;
        return m_size;
    }

    // TESTED. Версия, выдающая правильный результат НА МОЕЙ МАШИНЕ.
    template <class T>
    inline size_t Vector<T>::max_size() const noexcept
    {
        std::cout << "max_size()" << std::endl;
        size_t result = (pow(2, (64 - log(sizeof(T)) / log(2))));
        return result - 1;
    }

    /*template <class T>
    inline void Vector<T>::reserve_more_capacity(size_type size)
    {
        std::cout << "reserve_more_capacity()" << std::endl;
        if (size > m_capacity) {
            value_type *buff = new value_type[size];
            for (size_t i = 0; i < m_size; ++i)
                buff[i] = std::move(arr[i]);

            delete[] arr;
            arr = buff;
            m_capacity = size;
        }
    }*/
    /*template <class T>
    inline void Vector<T>::reserve(size_type size)
    {
        std::cout << "reserve()" << std::endl;
        if (size > m_capacity) {
            value_type *buff = new value_type[size];
            for (size_t i = 0; i < m_size; ++i) {
                // buff[i] = std::move(arr[i]);
                buff[i] = this->arr[i];
            }
            delete[] arr;
            arr = buff;
            m_capacity = size;
        }
    }*/

    // TESTED
    template <class T>
    inline void Vector<T>::reserve(size_type size)
    {
        if (size > m_capacity)
        {
            value_type *buff = new value_type[size];
            for (size_t i = 0; i < m_size; ++i)
            {
                buff[i] = this->arr[i];
                // buff[i] = std::move(arr[i]);  // Используем std::move для эффективного копирования
            }
            delete[] arr;
            arr = buff;
            m_capacity = size;
        }
    }

    // TESTED
    template <class T>
    inline size_t Vector<T>::capacity() const noexcept
    {
        std::cout << "getter capacity - capacity()" << std::endl;
        return m_capacity;
    }

    // TESTED
    template <class T>
    inline void Vector<T>::shrink_to_fit()
    {
        if (m_size < m_capacity)
        {
            // Освобождаем лишнюю память
            T *reduced_arr = new T[m_size];
            for (size_type i = 0; i < m_size; ++i)
            {
                reduced_arr[i] = arr[i];
                // reduced_arr[i] = std::move(arr[i]);
            }
            delete[] arr;
            arr = reduced_arr;
            m_capacity = m_size;
        }
    }
    /*template <class T>
    inline void Vector<T>::shrink_to_fit()
    {
        std::cout << "shrink_to_fit()" << std::endl;
        if (m_size < m_capacity)
        {
            m_capacity = m_size;
            T* reduced_arr = new T[m_capacity];

            for (size_t i = 0; i < m_size; i++)
            {
                reduced_arr[i] = arr[i];
            }
            delete[] arr;
            arr = reduced_arr;
            reduced_arr = nullptr;
        }
    }*/

    // TESTED
    template <class T>
    inline void Vector<T>::clear() noexcept
    {
        // Уничтожаем все элементы
        for (size_type i = 0; i < m_size; ++i)
        {
            arr[i].~T();
        }

        // Устанавливаем размер в 0
        m_size = 0;
    }
    /*template <class T>
    inline void Vector<T>::clear()
    {
        std::cout << "clear()" << std::endl;
        delete[] arr;
        m_size = 0;
        arr = nullptr;
    }*/

    //  TESTED
    template <class T>
    // inline void Vector<T>::erase(iterator pos)
    inline void Vector<T>::erase(const_iterator pos)
    {
        std::cout << "erase()" << std::endl;
        //  отсутствующая в оригинале проверка на то, что удаляемый элемент внутри вектора
        if (pos >= this->end() || pos < this->begin())
        {
            throw std::out_of_range("Iterator out of range.");
        }
        //  если удаляем последний элемент
        iterator zond_iter = pos;
        zond_iter++;
        if (zond_iter == this->end())
        {
            std::cout << " LAST " << std::endl;
        }
        else
        {
            //  позиция, куда смещать элемент справа
            iterator where_to = pos;
            //  элемент справа
            iterator right = where_to + 1;
            for (; right != this->end(); where_to++, right++)
            {
                *where_to = *right;
            }
        }
        this->m_size--;
    }

    // TESTED
    template <class T>
    inline T *Vector<T>::data() const noexcept
    {
        std::cout << "getter array - data()" << std::endl;
        return arr;
    }

    // TESTED
    template <class T>
    inline void Vector<T>::push_back(value_type v)
    {
        std::cout << "push_back()" << std::endl;
        if (m_size == m_capacity)
        {
            // reserve_more_capacity(m_size * 2);
            reserve(m_size * 2);
        }
        arr[m_size++] = v;
    }

    // TESTED
    template <class T>
    inline void Vector<T>::pop_back() noexcept
    {
        std::cout << "pop_back()" << std::endl;
        //  проверка на пустоту
        if (this->empty())
        {
            std::cout << "EMPTY VECTOR" << std::endl;
        }
        else
        {
            this->m_size--;
            // this->arr[this->m_size].~T();
            //  если после удаления элемента, вектор больше не имеет элементов
            if (this->empty())
            {
                std::cout << "already empty" << std::endl;
                this->clear();
            }
        }
    }

    // TESTED
    template <class T>
    inline void Vector<T>::swap(Vector &other) noexcept
    {
        std::cout << "swap()" << std::endl;
        size_type size_this = this->m_size;
        size_type capacity_this = this->m_capacity;
        value_type *arr_this = this->arr;

        this->m_size = other.m_size;
        this->m_capacity = other.m_capacity;
        this->arr = other.arr;

        other.m_size = size_this;
        other.m_capacity = capacity_this;
        other.arr = arr_this;
    }

    //  TESTED
    template <class T>
    inline VectorIterator<T> Vector<T>::insert(iterator pos, const_reference value)
    {
        // Проверяем, что pos находится в допустимых пределах
        if (pos < begin() || pos > end())
        {
            throw std::out_of_range("Iterator out of range");
        }

        // Сохраняем значение для вставки (на случай, если value ссылается на элемент вектора)
        T value_copy = value;

        // Вычисляем позицию вставки
        size_type position = pos - begin();

        // Расширяем емкость, если нужно
        if (m_size >= m_capacity)
        {
            size_type next_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            reserve(next_capacity);
        }

        // Обновляем итератор pos после возможного перевыделения памяти
        pos = begin() + position;

        // Сдвигаем элементы вправо
        if (pos != end())
        {
            for (iterator i = end(); i != pos; --i)
            {
                *i = *(i - 1);
            }
        }

        // Вставляем новый элемент
        *pos = value_copy;
        ++m_size;

        // Возвращаем итератор на вставленный элемент
        return pos;
    }

    //  TESTED
    template <class T>
    template <class... Args>
    inline VectorIterator<T> Vector<T>::insert_many(const_iterator pos, Args &&...args)
    {
        const size_type num_vargs = sizeof...(args);
        if (!num_vargs)
        {
            return (iterator)pos;
        }
        bool emptyVectorFlag = 0;
        iterator iter;
        // Если вектор пустой, выделяем память и добавляем элементы
        if (this->empty())
        {
            m_size = num_vargs;
            m_capacity = num_vargs;
            arr = new value_type[m_capacity];

            // Добавляем элементы в массив
            size_t i = 0;
            for (const auto &arg : {args...})
            {
                arr[i++] = arg;
            }
            emptyVectorFlag = 1;
            iter = this->begin();
            // return this->begin();
        }
        if (!emptyVectorFlag)
        {
            // Сохраняем позицию вставки
            size_type position = pos - this->begin();

            // Проверяем, нужно ли расширять емкость
            if (m_size + num_vargs > m_capacity)
            {
                reserve(m_size + num_vargs);
            }

            // Обновляем итератор после возможного перевыделения памяти
            // iterator iter = this->begin() + position;
            iter = this->begin() + position;

            // Вставляем элементы
            value_type vargs[num_vargs] = {args...};
            for (size_type i = 0; i < num_vargs; ++i)
            {
                iter = this->insert(iter, vargs[i]);
                iter++; // Перемещаем итератор на следующий элемент
            }
        }
        return iter;
    }

    // TESTED
    template <class T>
    template <class... Args>
    inline void Vector<T>::insert_many_back(Args &&...args)
    {
        const size_type num_vargs = sizeof...(args);
        if (!num_vargs)
        {
            return;
        }

        bool emptyVectorFlag = 0;
        // Если вектор пустой, выделяем память и добавляем элементы
        if (this->empty())
        {
            m_size = num_vargs;
            m_capacity = num_vargs;
            arr = new value_type[m_capacity];

            // Добавляем элементы в массив
            size_type i = 0;
            for (const auto &arg : {args...})
            {
                arr[i++] = arg;
            }
            emptyVectorFlag = 1;
        }
        if (!emptyVectorFlag)
        {
            size_type position = this->size() - 1;
            size_type upd_capacity = m_size + num_vargs;
            if (upd_capacity > m_capacity)
            {
                reserve(upd_capacity);
            }
            value_type vargs[num_vargs] = {args...};
            for (size_type i = position, j = 0; i < num_vargs + position; i++, j++)
            {
                push_back(vargs[j]);
            }
        }
    }
}

#endif
