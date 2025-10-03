// Each node is like a train car.
// Slow pointer walks 1 car at a time, fast pointer walks 2 cars.
// If there’s a loop, fast will eventually catch slow.
// If no loop, fast reaches the end and they never meet.

#include <iostream>
using namespace std;
struct Node
{
    int val;
    Node *next;
    Node(int x) : val(x), next(NULL) {}
};
bool detect(Node *head)
{
    if (!head || !head->next)
    {
        return false;
    }
    Node *slow = head;
    Node *fast = head;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            return true;
        }
    }
    return false;
}
