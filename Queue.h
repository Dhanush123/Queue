// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

template <typename V>
class Queue
{
  struct Node
  {
    V value;
    Node* next;
  };

  Node* firstNode; // the head pointer
  int siz = 0; // tracking the number of nodes
  Node* lastNode; // private data member

  public:
  Queue(); // may have a defaulted parameter, tested
  void push(const V&);
  V& front(); // return a mutable reference to the oldest node, tested
  V& back(); // return a mutable reference to the newest node, tested
  void pop(); // remove the oldest node, tested
  int size() const {return siz;} //tested
  bool empty() const {return siz==0;} //tested
  void clear(); //tested
  ~Queue(){clear();}
  Queue<V>& operator=(const Queue<V>&); //tested
  Queue(const Queue<V>&); //tested
};

template <typename V>
Queue<V>::Queue(){
  lastNode = 0;
  siz = 0;
}

template <typename V>
void Queue<V>::push(const V& value){
  Node* temp = new Node{value}; // C++11
  if (lastNode) lastNode->next = temp;
  else firstNode = temp;
  lastNode = temp;
  ++siz;
}

template <typename V>
V& Queue<V>::front(){
  return firstNode->value;
}

template <typename V>
V& Queue<V>::back(){
  return lastNode->value;
}

template <typename V>
void Queue<V>::pop(){
  if (firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
    --siz;
  }
  if(siz == 0){
    lastNode = 0;
  }
}

template <typename V>
void Queue<V>::clear()
{
  while (firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
    --siz;
  }
  lastNode = 0;
}

template <typename V>
Queue<V>::Queue(const Queue<V>& original)
{
  firstNode = 0;
  lastNode = 0; // temporary tail
  siz = original.siz;
  for (Node* p = original.firstNode; p; p = p->next)
  {
    Node* temp = new Node;
    temp->value = p->value;
    temp->next = 0;
    if (lastNode) lastNode->next = temp;
    else firstNode = temp;
    lastNode = temp;
  }
}

template <typename V>
Queue<V>& Queue<V>::operator=(const Queue<V>& original)
{
  if (this != &original)
  {
    // deallocate existing list
    while (firstNode)
    {
      Node* p = firstNode->next;
      delete firstNode;
      firstNode = p;
    }

    // build new queue
    lastNode = 0; // temporary tail
    for (Node* p = original.firstNode; p; p = p->next)
    {
      Node* temp = new Node;
      temp->value = p->value;
      temp->next = 0;
      if (lastNode) lastNode->next = temp;
      else firstNode = temp;
      lastNode = temp;
    }
    siz = original.siz;
  }
  return *this;
}

#endif //QUEUE_QUEUE_H
