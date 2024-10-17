#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

class DoublyLinkedList
{
private:
    struct Node
    {
        string name;
        Node *prev;
        Node *next;
        Node(string n, Node *p = nullptr, Node *ne = nullptr)
        {
            name = n;
            prev = p;
            next = ne;
        }
    };
    Node *head;
    Node *tail;

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }
    void insert_after(string value, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
            return;
        }
        Node *temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp)
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }
    void delete_val(string value)
    {
        if (!head)
            return;
        Node *temp = head;
        while (temp && temp->name != value)
            temp = temp->next;
        if (!temp)
            return;
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;
        delete temp;
    }
    void delete_pos(int pos)
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }
        if (pos == 1)
        {
            pop_front();
            return;
        }
        Node *temp = head;
        for (int i = 1; i < pos; i++)
        {
            if (!temp)
            {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp)
        {
            cout << "Position doesn't exist." << endl;
            return;
        }
        if (!temp->next)
        {
            pop_back();
            return;
        }
        Node *tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }
    void push_back(string v)
    {
        Node *newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void push_front(string v)
    {
        Node *newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void pop_front()
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = head;
        if (head->next)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }
    void pop_back()
    {
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = tail;
        if (tail->prev)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }
    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print()
    {
        Node *current = head;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << "\t\t" << current->name << endl;
            current = current->next;
        }
        cout << endl;
    }
    void print_reverse()
    {
        Node *current = tail;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->name << " ";
            current = current->prev;
        }
        cout << endl;
    }
    // Function to return the length of the list.
    int get_length() {
        Node *temp = head;
        int count = 0;
        while(temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    string get_head_val() {
        if (!head) {
            return " ";
        }
        return head->name;
    }
    string get_tail_val() {
        if (!tail) {
            return " ";
        }
        return tail->name;
    }
};
int main()
{
    srand(time(0));
    DoublyLinkedList line;

    int rand_index;

    ifstream names_list("names.txt");
    vector<string> names;
    string name;

    // Store all the names from the txt file to the vector.
    while (getline(names_list, name)) {
        names.push_back(name);
    }
    names_list.close();

    cout << "Store opens:" << endl;

    for (int i = 0; i < 5; i++) {
        rand_index = rand() % 103;
        name = names[rand_index];
        cout << "\t" << name << " joins the line" << endl;
        line.push_back(name);
    }
    
    cout << "\tResulting line: " << endl;
    line.print();
    for (int minute = 2; minute <= 20; minute++){
        cout << "Time step #" << minute << ":" << endl; 
        int prob = rand() % 100 + 1; // returns random number 1-100
        if (prob <= 40) {
            cout << "\t" << line.get_head_val() << "is served" << endl;
            line.pop_front();
        }
        else if (prob <= 60) {
            rand_index = rand() % (103 +1);
            name = names[rand_index];
            cout << "\t" << name << " joins the line" << endl;
            line.push_back(name);
        }
        else if (prob <=20) {
            cout << "\t" << line.get_tail_val() << " (at the rear) left the line" << endl;
            line.pop_back();
        }

        cout << "\t\tResulting line:" << endl;
        line.print();
    }
    return 0;
}
