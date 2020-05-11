struct node
{
    int data;
    node *next;
};


class LinkedList
{
private:
    node* m_head;
	node* m_tail;
public:
    linked_list()
    {
        m_head = NULL;
        m_tail = NULL;
    }

    void append(int n)
    {
        node *tmp = new node;
        tmp->data = n;
        tmp->next = NULL;

        if(m_head == NULL){
            m_head = tmp;
            m_tail = tmp;
        }
        else{
            m_tail->next = tmp;
            m_tail = m_tail->next;
        }
    }
};
