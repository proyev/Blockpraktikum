#ifndef INC_3_2_LINKEDLIST_H
#define INC_3_2_LINKEDLIST_H
#include <iostream>
#include <memory>

template <typename T>//as we want our linked list to be used for different types
class List{
    private:
        class ListELement{
            public:
                ListELement(const T &data, std::shared_ptr<ListElement> next);
                T data;
                std::shared_ptr<ListElement> next;t

            private:
                std::size_t _size;
                std::shared_ptr<ListELement> _first;
                T _dummy;
                bool _validData;


        };
    public:
        List(const T& initvalue, )
};

template <typename T>
class  ListElement{
    private:

    public:
        ListElement(const T& initvalue, std::shared_ptr<T> next{})

};

template<class T> void printList(const LinkedList<T> &list);


#endif //INC_3_2_LINKEDLIST_H
