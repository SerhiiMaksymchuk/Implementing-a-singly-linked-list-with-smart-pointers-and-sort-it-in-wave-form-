#include <iostream>
#include <memory>

using namespace std;

struct Node 
{
    int data;
    std::unique_ptr<Node> next;
    Node(int data) : data{ data }, next{ nullptr } {}
};

struct List 
{
    List() : head{ nullptr }
    {
    };
    // Adds a new element at the end of the list container
    void push(int data)
    {
        auto temp{ std::make_unique<Node>(data) };
        if (head) 
        {
            temp->next = std::move(head);
            head = std::move(temp);
        }
        else 
             head = std::move(temp);
    }
    // Removes the last element in the list container
    void pop()
     {
        if (head == nullptr) 
           return;
        std::unique_ptr<Node> temp = std::move(head);
        head = std::move(temp->next);
    }
    // Gets size of the list 
    int listSize()
    {
        int counter = 0;
        Node* temp = head.get();
        while (temp != nullptr) 
        {
            counter++;
            temp = temp->next.get();
        }
        return counter;
    }
    // Function to swap two integers 
    void swap(int* a, int* b)
    {
        int temp;
        temp = *a;
        *a = *b;
        *b = temp;
    }
    // Sorts the list in a wave form
    void SortInWave()
    {
        Node* prev = NULL;
        int i = 0;
        Node* current = head.get();
        Node* head2 = current;
        // Traverse all even positioned nodes 
        while (current)
        {
            if (i % 2 == 0)
            {
                if (i > 0 && (prev->data > current->data))
                    swap(&(current->data), &(prev->data));
                if (current->next && (current->data < current->next->data))
                    swap(&(current->data), &(current->next->data));
            }
            i++;
            prev = current;
            current = current->next.get();
        }
    }
    // Removes all elements from the list container 
    // and leaving the container with a size of 0
    void clean()
    {
        if (head == nullptr) 
            return;
        while (head->next) 
        {
            std::unique_ptr<Node> temp = std::move(head->next);
            head = std::move(temp);
        }
        head.reset();
    }
    friend std::ostream& operator<<(std::ostream& os, const List& list);
    ~List()
    {
        clean();
    }
private:
    std::unique_ptr<Node> head;
};

std::ostream& operator<<(std::ostream& os, const List& list)
{
    Node* head = list.head.get();
    while (head)
    {
        os << head->data << ' ';
        head = head->next.get();
    }
    return os;
}
int main()
{
    List list;
    list.push(20);
    list.push(10);
    list.push(8);
    list.push(6);
    list.push(4);
    list.push(2);
    std::cout << "list size:" << list.listSize() << std::endl;
    std::cout << "list: " << list << std::endl;
    list.SortInWave();
    std::cout << "List after sorting:  " << list << std::endl;
    list.clean();
    list.push(20);
    list.push(7);
    list.push(10);
    list.push(5);
    list.push(6);
    list.push(3);
    std::cout << "Unsorted list: " << list << std::endl;
    list.SortInWave();
    std::cout << "List after sorting:  " << list << std::endl;
    list.clean();
    return 0;
}

