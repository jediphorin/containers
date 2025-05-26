#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H

#include <utility>
#include <iostream>
#include <initializer_list>

namespace s21
{
    template <class T>
    class ListIterator;

    template <class T>
    class ListConstIterator;

    template <class T>
    class List
    {
        friend class ListIterator<T>;
        friend class ListConstIterator<T>;

    public:
        // List Member type
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = ListIterator<T>;
        using const_iterator = ListConstIterator<T>;
        using size_type = size_t;

    private:
        // friend class ListIterator<T>;
        // friend class ListConstIterator<T>;
        //  поля
        
        struct Node
        {
            T data;
            Node *next;
            Node *prev;

            friend class ListIterator<T>;
            friend class ListConstIterator<T>;

            //  конструктор структуры
            Node(const_reference value, Node *n = nullptr, Node *p = nullptr)
                : data(value), next(n), prev(p) {}
        };
        typedef Node* NodePtr;

        Node* head;
        Node* tail;
        size_type m_size;

    public:
        // конструктор поумолчанию
        List() : head(nullptr), tail(nullptr), m_size(0) {}
        // конструктор с инициализацией
        List(std::initializer_list<value_type> const &items)
            : head(nullptr), tail(nullptr), m_size(0)
        {
            for (const auto &item : items)
            {
                push_back(item);
            }
        }
        //  конструктор копирования
        List(const List& other) : head(nullptr), tail(nullptr), m_size(0)
        {
            // for (const auto &item : other)
            // {
            //     push_back(item);
            // }
            for (Node* current = other.head; current != nullptr; current = current->next)
            {
                push_back(current->data);
            }
        }
        // template <class T>
        List(List&& other) noexcept 
            : head(other.head), tail(other.tail), m_size(other.m_size)
        {
            other.head = nullptr;
            other.tail = nullptr;
            other.m_size = 0;
        }
        // деструктор
        ~List()
        {
            clear();
        }

        void print_list(Node* current = nullptr)
        {
            if (!this->empty())
            {
                std::cout << "Список: ";
                for (auto i = begin(); i != end(); i++)
                {
                    if (current && i.get_current() == current)
                    {
                        std::cout << "<" << *i << "> ";
                    }
                    else
                    {
                        std::cout << *i << " ";
                    }                    
                }
                std::cout << std::endl;
            }
            else
            {
                std::cout << "Список пуст." << std::endl;
            }
        }
        
        // оператор присваивания
        List& operator=(const List& other) noexcept
        {
            if (this != &other)
            {
                clear();
                for (const auto& item : other)
                // {
                //     push_back(item);
                // }
                for (Node* current = other.head; current != nullptr; current = current->next)
                {
                    push_back(current->data);
                }
            }
            return *this;
        }

        List& operator=(List&& other) noexcept
        {
            if (this != &other)
            {
                clear();
                
                head = other.head;
                tail = other.tail;
                m_size = other.m_size;
                
                other.head = nullptr;
                other.tail = nullptr;
                other.m_size = 0;
            }
            return *this;
        }

        // List Element access - для чтения
        const_reference front() const;
        reference front();
        const_reference back() const;
        reference back();

        // List Iterators - для модификаций
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;
        iterator get_iter(Node* input) noexcept;

        iterator get_tail() noexcept;
        iterator get_head() noexcept;

        // List Capacity
        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;

        // List Modifiers
        void clear();
        iterator insert(iterator pos, const_reference value);
        // iterator erase(iterator pos);
        void erase(iterator pos);
        void push_back(const_reference value);
        void pop_back();
        void push_front(const_reference value);
        void pop_front();
        void swap(List &other);        
        void splice(const_iterator pos, List &other);
        // void splice(iterator pos, List &other);
        void reverse();
        void unique();
        
        void merge(List &other);
        void resize_lists(List &other);
        void resize_lists_in_one_shot(List &other);
        void head_and_tail_of_other_list_to_null(List &other);
        bool stop_merge(List &other);
        void cycle_of_merge(List &other);
        void nxt_prv_update(Node* cur, Node* act, Node*& nxt_cur, Node*& nxt_act, Node*& prv_cur);
        void link_of_cur_to_prev_and_act_to_next(Node*& cur, Node*& act);
        void when_act_is_not_tale(Node*& nxt_act, Node*& act, List& other);
        void link_of_prv_cur_to_next_and_act_to_prev(Node*& prv_cur, Node*& act);
        void link_of_cur_to_next_and_act_to_prev(Node*& cur, Node*& act);
        void link_of_nodes_when_nxt_cur_gt_act(Node*& cur, Node*& act, Node*& nxt_cur);
        void left_insert(Node*& prv_cur, Node*& cur, Node*& act, Node*& nxt_act, List &other);
        void right_insert(Node*& cur, Node*& act, Node*& nxt_cur, Node*& nxt_act, List &other);

        void sort();
        void frwrd_bcwrd_update(Node* cur, Node*& frwrd, Node*& bcwrd);
        void sort_in_head(Node* cur, Node*& frwrd, bool& sorted);
        void sort_not_head(Node* cur, Node*& frwrd, Node*& bcwrd);

        template <class... Args>
        void insert_many_back(Args&&... args);

        template <class... Args>
        void insert_many_front(Args&&... args);

        template <class... Args>
        iterator insert_many(const_iterator pos, Args&&... args);

        void check_insert_many(const size_type num_vargs);
    };

    template <class T>
    class ListIterator
    {
        friend class List<T>;

        public:
            using value_type = T;
            using pointer = T*;
            using const_pointer = const T*;
            using reference = T&;
            using const_reference = const T&;
            using iterator = ListIterator<T>;
            using const_iterator = ListConstIterator<T>;
            using size_type = size_t;
        
        private:
            List<T>* list;
            typename List<T>::Node* current;

        public:
            ListIterator() : list(nullptr), current(nullptr) {}
            explicit ListIterator(typename List<T>::Node* node) : list(nullptr), current(node) {}
            // ListIterator() : current(nullptr) {}
            ListIterator(List<T>* parent, typename List<T>::Node* node) : list(parent), current(node) {}
            // ListIterator(typename List<T>::Node* node) : current(node) {}

            ListIterator(const ListIterator& other) = default;

            operator const_iterator() const
            {
                return const_iterator(list, current);
            }

            pointer operator->()
            {
                return &(current->data);
            }
            const_pointer operator->() const
            {
                return &(current->data);
            }

            reference operator*() {
                if (!current)
                {
                    return list->tail->data;
                    // throw std::out_of_range("Итератор не разыменовывается.");
                }
                return current->data;
            }
            const_reference operator*() const {
                if (!current)
                {
                    return list->tail->data;
                    // throw std::out_of_range("Итератор не разыменовывается.");
                }
                return current->data;
            }

            ListIterator &operator++()
            {
                if (current != nullptr)
                {
                    current = current->next;
                }
                return *this;
            }
            ListIterator operator++(int)
            {
                ListIterator buffer = *this;
                ++(*this);
                return buffer;
            }
            ListIterator &operator--()
            {
                if (!current)
                {
                    current = list->tail;
                }
                else if (current != list->head)
                {
                    current = current->prev;
                }
                return *this;
            }
            ListIterator operator--(int)
            {
                ListIterator buffer = *this;
                --(*this);
                
                return buffer;
            }
            /*ListIterator operator-(const size_type offset)
            {
                std::cout << "OPERATOR!" << std::endl;
                ListIterator buffer = *this;
                
                for (size_type i = 0; i < offset; ++i)
                {
                    std::cout << *buffer << " ";
                    --(*this);
                }
                return buffer;

            }*/

            // ListIterator operator=(const ListIterator& other) const
            // {
            //     return (current = other.current);
            // }
            ListIterator operator=(const ListIterator& other)
            {
                current = other.current;
                list = other.list;
                return *this;
            }

            /*typename List<T>::Node* &operator-(const size_type offset)
            {
                // auto iter = get_list()->get_iter();
                // typename List<T>::Node* cur = get_current()
                // std::cout << get_list().
                for (size_type i = 0; i < offset; ++i)
                {
                    current = current->prev;
                }
                return *this;
            }*/

            /*ListIterator operator-(typename List<T>::Node* cur_node, const size_type offset)
            {
                
                
                for (size_t i = 0; i < offset; ++i)
                {
                    
                }
                ListIterator buffer;
            }*/

            /*VectorIterator operator-(const size_t offset) const
            {
                std::cout << "VectorIterator operator-" << std::endl;
                VectorIterator buffer(this->ptr_ - offset);
                return buffer;
            }
            size_t operator-(const VectorIterator &other) const
            {
                std::cout << "VectorIterator operator-" << std::endl;
                return ptr_ - other.ptr_;
            }*/

            bool operator==(const ListIterator &other) const
            {
                return (current == other.current);
            }
            bool operator!=(const ListIterator &other) const
            {
                return (current != other.current);
            }

            /*bool operator>(const ListIterator &other)
            {
                return(current > other.current);
            }
            bool operator>=(const ListIterator &other)
            {
                return(current >= other.current);
            }
            bool operator<(const ListIterator &other)
            {
                return(current < other.current);
            }
            bool operator<=(const ListIterator &other)
            {
                return(current <= other.current);
            }*/
            
            typename List<T>::Node* get_current() const
            {
                return current;
            }
            // void set_current(Node* actual)
            void set_current(typename List<T>::Node* actual)
            {
                current = actual;
            }
            // ? ВЕРНО ЛИ List<T>* list; 
            List<T>* get_list() const
            {
                return list;
            }
            void set_list(List<T>* lst)
            {
                list = lst;
            }
    };

    template <class T>
    class ListConstIterator
    {
        friend class List<T>;

        public:
            using value_type = T;
            using pointer = T*;
            using const_pointer = const T*;
            using reference = T&;
            using const_reference = const T&;
            using iterator = ListIterator<T>;
            using const_iterator = ListConstIterator<T>;
            using size_type = size_t;
        
        private:
            const List<T>* list;
            typename List<T>::Node* current;
        
        public:
            ListConstIterator() : list(nullptr), current(nullptr) {}
            ListConstIterator(List<T>* parent, typename List<T>::Node* node) : list(parent), current(node) {}
            ListConstIterator(const List<T>* parent, typename List<T>::Node* node) : list(parent), current(node) {}
            ListConstIterator(const ListConstIterator& other) = default;

            pointer operator->()
            {
                return &(current->data);
            }
            const_pointer operator->() const
            {
                return &(current->data);
            }

            reference operator*() {
                if (!current)
                {
                    return list->tail->data;
                    // throw std::out_of_range("Итератор не разыменовывается.");
                }
                return current->data;
            }
            const_reference operator*() const {
                if (!current)
                {
                    return list->tail->data;
                    // throw std::out_of_range("Итератор не разыменовывается.");
                }
                return current->data;
            }

            ListConstIterator &operator++()
            {
                if (current != nullptr)
                {
                    current = current->next;
                }
                return *this;
            }
            ListConstIterator operator++(int)
            {
                ListConstIterator buffer = *this;
                ++(*this);
                return buffer;
            }
            ListConstIterator &operator--()
            {
                if (!current)
                {
                    current = list->tail;
                }
                else if (current != list->head)
                {
                    current = current->prev;
                }
                return *this;
            }
            ListConstIterator operator--(int)
            {
                ListConstIterator buffer = *this;
                --(*this);
                
                return buffer;
            }

            ListConstIterator operator=(const ListConstIterator& other)
            {
                current = other.current;
                list = other.list;
                return *this;
            }

            bool operator==(const ListConstIterator &other) const
            {
                return (current == other.current);
            }
            bool operator!=(const ListConstIterator &other) const
            {
                return (current != other.current);
            }
            
            typename List<T>::Node* get_current() const
            {
                return current;
            }

            void set_current(typename List<T>::Node* actual)
            {
                current = actual;
            }
            // ? ВЕРНО ЛИ List<T>* list; 
            List<T>* get_list() const
            {
                return list;
            }
            void set_list(List<T>* lst)
            {
                list = lst;
            }
    };

    template <class T>
    inline const T& List<T>::front() const
    {
        if (!head)
        {
            throw std::out_of_range("Список пуст.");
        }
        return head->data;
    }
    template <class T>
    inline T& List<T>::front()
    {
        if (!head)
        {
            throw std::out_of_range("Список пуст.");
        }
        return head->data;
    }

    template <class T>
    inline const T& List<T>::back() const
    {
        if (!tail)
        {
            throw std::out_of_range("Список пуст.");
        }
        return tail->data;
    }
    template <class T>
    inline T& List<T>::back()
    {
        if (!tail)
        {
            throw std::out_of_range("Список пуст.");
        }
        return tail->data;
    }

    template <class T>
    inline ListIterator<T> List<T>::begin() noexcept
    {
        //  новострой, которого нет в оригинале
        /*if (!head)
        {
            throw std::out_of_range("List is empty.");
        }*/
        // return iterator(head);
        return iterator(this, head);
    }
    template <class T>
    inline ListConstIterator<T> List<T>::begin() const noexcept
    {
        return const_iterator(this, head);
    }
    template <class T>
    inline ListConstIterator<T> List<T>::cbegin() const noexcept
    {
        return const_iterator(this, head);
    }
    template <class T>
    inline ListIterator<T> List<T>::end() noexcept
    {
        // return iterator(nullptr);
        return iterator(this, nullptr);
    }
    template <class T>
    inline ListConstIterator<T> List<T>::end() const noexcept
    {
        return const_iterator(this, nullptr);
    }
    template <class T>
    inline ListConstIterator<T> List<T>::cend() const noexcept
    {
        return const_iterator(this, nullptr);
    }

    template <class T>
    inline ListIterator<T> List<T>::get_iter(typename List<T>::Node* input) noexcept
    {
        return iterator(this, input);
    }

    template <class T>
    inline ListIterator<T> List<T>::get_tail() noexcept
    {
        // return iterator(tail);
        return iterator(this, tail);
    }
    template <class T>
    inline ListIterator<T> List<T>::get_head() noexcept
    {
        return iterator(this, head);
    }

    template <class T>
    inline bool List<T>::empty() const noexcept
    {
        return m_size == 0;
    }

    template <class T>
    inline size_t List<T>::size() const noexcept
    {
        return m_size;
    }

    template <class T>
    inline size_t List<T>::max_size() const noexcept
    {
        return std::numeric_limits<size_t>::max() / sizeof(NodePtr);
    }

    template <class T>
    inline void List<T>::clear()
    {
        while (head)
        {
            Node* current = head;
            head = head->next;
            delete current;
        }
        tail = nullptr;
        m_size = 0;
    }
    template <class T>
    inline ListIterator<T> List<T>::insert(iterator pos, const_reference value)
    // template <class T>
    // inline ListIterator<T> List<T>::insert(ListIterator<T> pos, const T &value)
    {     
        //  проверка лишняя 
        // if (pos.get_current() == nullptr && pos != end())
        // {
        //     throw std::invalid_argument("Итератор-инвалид.");
        // }
        
        iterator result;
        if (pos == begin())
        {
            push_front(value);
            // return begin();
            result = begin();
        }
        else if (pos == end())
        {    
            push_back(value);
            // return --end();
            result = --end();
        }
        // если вставляемый узел находится где-то между началом и концом списка
        else
        {
            std::cout << "1256"<< std::endl;
            Node* to_insert = new Node(value);
            iterator nxt = pos;
            iterator prv = pos;
            --prv;
            Node* p = prv.get_current();
            Node* n = nxt.get_current();
            p->next = to_insert;
            to_insert->prev = p;
            n->prev = to_insert;
            to_insert->next = n;
            result.set_current(to_insert);
            result.set_list(this);
            ++m_size;
        }
    //    return iterator(to_insert);
        // return ListIterator<T>(this, nullptr);
        return result;
    }

    template <class T>
    inline void List<T>::erase(iterator pos)
    {
        //  если pos соответствует nullptr
        if (pos == end())
        {
            // throw std::out_of_range("Список пуст.");
            return;
        }
        Node* to_delete = pos.get_current();

        //  если pos в первом узле списка
        if (pos == this->begin())
        {
            pop_front();
        }
        //  если удаляемый не в начале
        else
        {
            Node* prev = to_delete->prev;
            Node* next = to_delete->next;
            prev->next = next;
            //  если после удаляемого узла существует следующий
            if (next)
            {
                next->prev = prev;
            }
            //  если удаляемый узел - последний в списке
            else
            {
                // std::cout << "last el" << std::endl;
                tail = prev;
                prev->next = nullptr;
            }
            delete to_delete;
            --m_size;
        }
    }

    template <class T>
    inline void List<T>::push_back(const_reference value)
    {
        if (!head)
        {
            head = new Node(value);
            tail = head;
        }
        else {
            Node* input = new Node(value);
            tail->next = input;
            input->prev = tail;
            tail = tail->next;
            tail->next = nullptr;
        }
        ++m_size;
    }

    template <class T>
    inline void List<T>::pop_back()
    {
        if (tail) 
        {
            Node* to_delete = tail;
            tail = tail->prev;
            if (tail)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }
            delete to_delete;
            --m_size;
        }
    }

    template <class T>
    inline void List<T>::push_front(const_reference value)
    {
        if (!head)
        {
            head = new Node(value);
            tail = head;
        }
        else
        {
            Node* input = new Node(value);
            input->prev = nullptr;
            input->next = head;
            head->prev = input;
            head = head->prev;
        }
        ++m_size;
    }
    template <class T>
    inline void List<T>::pop_front()
    {
        if (this->empty())
        {
            return;
        }
        if (head)
        {
            Node* to_delete = head;
            head = head->next;

            if (head)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }
            delete to_delete;
            --m_size;
        }
    }

    template <class T>
    inline void List<T>::swap(List &other)
    {
        Node* buffer_head = this->head;
        Node* buffer_tail = this->tail;
        size_type buffer_m_size = this->m_size;

        this->head = other.head;
        this->tail = other.tail;
        this->m_size = other.m_size;

        other.head = buffer_head;
        other.tail = buffer_tail;
        other.m_size = buffer_m_size;
    }

    template <class T>
    inline void List<T>::merge(List &other)
    {
        if (stop_merge(other))
        {
            return;
        }
        cycle_of_merge(other);
    }
    
    template <class T>
    inline void List<T>::splice(const_iterator pos, List &other)
    // inline void List<T>::splice(iterator pos, List &other)
    {
        //  return или throw
        if (other.empty() || this == &other)
        {
            return;
        }
        // iterator non_const_pos = iterator(pos.get_current());
        iterator non_const_pos(const_cast<List<T>*>(pos.list), pos.current);
        Node* cr = other.head;
        while (cr)
        {
            // insert(pos, cr->data);
            insert(non_const_pos, cr->data);
            cr = cr->next;  
        } 
        other.clear();
    }

    // ? НУЖНЫ ЛИ ИСКЛЮЧЕНИЯ ПО ПУСТОМУ СПИСКУ ИЛИ СПИСКУ НА ОДИН УЗЕЛ
    template <class T>
    inline void List<T>::reverse()
    {
        if (empty() || size() == 1) {
            return;
        }
        Node* cr = head;
        Node* tmp = nullptr;
        while (cr)
        {
            Node* nxt = cr->next;
            if (cr == head)
            {
                cr->prev = cr->next;
                cr->next = nullptr;
            }
            else if (cr == tail)
            {
                cr->next = cr->prev;
                cr->prev = nullptr;
            }
            else
            {
                tmp = cr->prev;
                cr->prev = cr->next;
                cr->next = tmp;
            }
            cr = nxt;
        }
        tmp = head;
        head = tail;
        tail = tmp;
    }

    template <class T>
    inline void List<T>::unique()
    {
        //  если в списке узлов меньше двух, то закрываем банкет
        if (size() < 2)
        {
            return;
        }
        Node* crrnt = head;
        Node* start = nullptr;
        Node* finish = nullptr;
        
        while (crrnt && crrnt->next)
        {
            if (crrnt->data == crrnt->next->data)
            {
                start = crrnt;
                finish = crrnt->next;
                //  цикл поиска внутри цикла
                while (finish && start->data == finish->data)
                {                    
                    Node* to_delete = finish;
                    start->next = finish->next;

                    if (finish->next)
                    {
                        finish->next->prev = start;
                    }
                    else
                    {
                        tail = start;
                    }
                    finish = finish->next;
                    delete to_delete;
                    --m_size;
                }            
            }
            crrnt = crrnt->next;
        }
    }
    
    template <class T>
    inline void List<T>::resize_lists(List &other)
    {
        ++m_size;
        --other.m_size;
    }
    template <class T>
    inline void List<T>::resize_lists_in_one_shot(List &other)
    {
        m_size += other.m_size;
        other.m_size = 0;
    }
    template <class T>
    inline void List<T>::head_and_tail_of_other_list_to_null(List &other)
    {
        other.head = nullptr;
        other.tail = nullptr;
    }
    template <class T>
    inline bool List<T>::stop_merge(List &other)
    {
        bool stop = 0;
        if ((other.empty() || this == &other) || empty())
        {
            if (empty() && !other.empty())
            {
                head = other.head;
                other.head = nullptr;

                tail = other.tail;
                other.tail = nullptr;
            
                m_size = m_size + other.m_size;
                other.m_size = 0;
            }
            else if (this == &other)
            {

            }
            stop = 1;
        }
        return stop;
    }
    template <class T>
    inline void List<T>::cycle_of_merge(List &other)
    {
        Node* cur = head;
        Node* act = other.head;
        Node* nxt_cur = nullptr;
        Node* nxt_act = nullptr;
        Node* prv_cur = nullptr;
        while (!other.empty())
        {
            nxt_prv_update(cur, act, nxt_cur, nxt_act, prv_cur);
            if (cur->data > act->data)
            {     
                left_insert(prv_cur, cur, act, nxt_act, other);
            }
            // cur <= act
            else
            {
                right_insert(cur, act, nxt_cur, nxt_act, other);                
            }
        }
    }
    template <class T>
    inline void List<T>::nxt_prv_update(Node* cur, Node* act, Node*& nxt_cur, Node*& nxt_act, Node*& prv_cur)
    {
        nxt_cur = cur->next;
        nxt_act = act->next;
        prv_cur = cur->prev;
    }
    template <class T>
    inline void List<T>::link_of_cur_to_prev_and_act_to_next(Node *&cur, Node *&act)
    {
        cur->prev = act;
        act->next = cur;
    }
    template <class T>
    inline void List<T>::when_act_is_not_tale(Node*& nxt_act, Node*& act, List& other)
    {
        nxt_act->prev = nullptr;
        other.head = nxt_act;
        act = nxt_act;
    }
    template <class T>
    inline void List<T>::link_of_prv_cur_to_next_and_act_to_prev(Node *&prv_cur, Node *&act)
    {
        prv_cur->next = act;
        act->prev = prv_cur;
    }
    template <class T>
    inline void List<T>::link_of_cur_to_next_and_act_to_prev(Node *&cur, Node *&act)
    {
        cur->next = act;
        act->prev = cur;
    }
    template <class T>
    inline void List<T>::link_of_nodes_when_nxt_cur_gt_act(Node *&cur, Node *&act, Node *&nxt_cur)
    {
        link_of_cur_to_next_and_act_to_prev(cur, act);
        // cur->next = act;
        // act->prev = cur;
        nxt_cur->prev = act;
        act->next = nxt_cur;
    }
    template <class T>
    inline void List<T>::left_insert(Node *&prv_cur, Node *&cur, Node *&act, Node *&nxt_act, List &other)
    {
        link_of_cur_to_prev_and_act_to_next(cur, act);
        if (cur == head)
        {                                        
            head = act;
            if (act == other.tail)
            {
                head_and_tail_of_other_list_to_null(other);
            }
            else
            {
                when_act_is_not_tale(nxt_act, act, other);
            }                    
        }
        else
        {
            link_of_prv_cur_to_next_and_act_to_prev(prv_cur, act);
            if (act == other.tail)
            {
                head_and_tail_of_other_list_to_null(other);
            }
            else
            {
                when_act_is_not_tale(nxt_act, act, other);
            }                    
        }
        resize_lists(other);
    }
    template <class T>
    inline void List<T>::right_insert(Node *&cur, Node *&act, Node *&nxt_cur, Node *&nxt_act, List &other)
    {
        if (cur == tail)
        {
            link_of_cur_to_next_and_act_to_prev(cur, act);
            tail = other.tail;
            head_and_tail_of_other_list_to_null(other);
            resize_lists_in_one_shot(other);
        }                                
        else
        {
            if (nxt_cur->data <= act->data) 
            {
                cur = cur->next;
            }
            else
            {
                link_of_nodes_when_nxt_cur_gt_act(cur, act, nxt_cur);
                if (act == other.tail)
                {
                    head_and_tail_of_other_list_to_null(other);
                }
                else
                {
                    when_act_is_not_tale(nxt_act, act, other);
                    cur = cur->next;                            
                }
                resize_lists(other);
            }
        }
    }

    template <class T>
    inline void List<T>::sort()
    {
        if (m_size < 2)
        {
            return;
        }
        bool sorted = 0;
        Node* cur = head;
        Node* frwrd = nullptr;
        Node* bcwrd = nullptr;
        while (!sorted)
        {     
            if (frwrd == tail && (cur->prev->data <= cur->data))
            {
                sorted = 1;
            }
            else if (!sorted)
            {
                frwrd_bcwrd_update(cur, frwrd, bcwrd);
                if (cur->data > cur->next->data)
                {                 
                    if (cur == head)
                    {
                        sort_in_head(cur, frwrd, sorted);                        
                    }                    
                    else
                    {   
                        sort_not_head(cur, frwrd, bcwrd);                        
                    }
                    cur = head;
                }
                else
                {                                    
                    cur = cur->next;
                }
            }
        }
    }
    template <class T>
    inline void List<T>::frwrd_bcwrd_update(Node *cur, Node *&frwrd, Node *&bcwrd)
    {
        frwrd = cur->next;
        bcwrd = cur->prev;
    }
    template <class T>
    inline void List<T>::sort_in_head(Node *cur, Node *&frwrd, bool &sorted)
    {

        frwrd->prev = nullptr;
        cur->prev = frwrd;
        if (m_size == 2)
        {
            cur->next = nullptr;
            tail = cur;
            sorted = 1;
        }
        else
        {
            frwrd->next->prev = cur;
            cur->next = frwrd->next;                        
            }
            frwrd->next = cur;
            head = frwrd;
    }
    template <class T>
    inline void List<T>::sort_not_head(Node *cur, Node *&frwrd, Node *&bcwrd)
    {
        bcwrd->next = frwrd;
        frwrd->prev = bcwrd;                        
        if (frwrd == tail)
        {
            print_list(cur);
            cur->next = nullptr;
            tail = cur;
        }   
        else
        {
            frwrd->next->prev = cur;
            cur->next = frwrd->next;
        }
        frwrd->next = cur;
        cur->prev = frwrd;
    }

    template <class T>
    inline void List<T>::check_insert_many(const size_type num_vargs)
    {
        if (!num_vargs)
        {
            return;
        }
    }

    template <class T>
    template <class... Args>
    inline void List<T>::insert_many_back(Args &&...args)
    {
        const size_type num_vargs = sizeof...(args);
        check_insert_many(num_vargs);
        value_type vargs[num_vargs] = {args...};
        for (size_type i = 0; i < num_vargs; ++i)
        {
            push_back(vargs[i]);
        }
    }

    template <class T>
    template <class... Args>
    inline void List<T>::insert_many_front(Args &&...args)
    {
        const size_type num_vargs = sizeof...(args);
        check_insert_many(num_vargs);
        value_type vargs[num_vargs] = {args...};
        for (size_type i = 0; i < num_vargs; ++i)
        {
            push_front(vargs[num_vargs - i - 1]);
        }
    }

    template <class T>
    template <class... Args>
    inline ListIterator<T> List<T>::insert_many(const_iterator pos, Args &&...args)
    {
        const size_type num_vargs = sizeof...(args);
        if (!num_vargs)
        {
            // return (iterator) pos;
            return iterator(pos.get_current());
        }
        value_type vargs[num_vargs] = {args...};
        iterator iter(pos.get_current());
        for (size_type i = 0; i < num_vargs; ++i)
        {
            
            iter = this->insert(iter, vargs[i]);
            ++iter; // Перемещаем итератор на следующий узел
        }
        return --iter;
    }
} //  namespace s21
#endif