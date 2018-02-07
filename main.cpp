#include <iostream>

using namespace std;

struct node {
    int data, degree;
    node *right, *child;
};

class heap {
    node *root;

    bool comparetion(node *a, node *b){
        if (a->degree < b->degree)
            return true;
        return false;
    }

    node *merge_2trees(node *a, node *b){
        b->right = a->child;
        a->child = b;
        a->degree++;
        return a;
    }

    node *merge_same_trees(node *a){
        if (!a)
            return a;
        if (!a->right)
            return a;

        node *next = a->right, *next2 = next->right;
        if ((next2 && a->degree == next->degree && next->degree == next2->degree)
                            || a->degree < next->degree)
            a->right = merge_same_trees(next);

        else{
            if (comparetion(a,next)){
                a = merge_2trees(a, next);
                a->right = next2;
            }
            else
                a = merge_2trees(next,a);
        }
        return a;
    }

    node *tsil(node *a){
        if (!a)
            return a;
        if (!a->right)
            return a;
        node *next = a->right, *next2 = next->right;
        while(next2){
            next->right = a;
            a = next;
            next = next2;
            next2 = next->right;
        }
        next->right = a;
        return next;
    }

    //////////
    //public
    /////////

    /////dopisat chtoto tam s heap and friend
    /////i mozhet nuzhno & dobavit
public:

    node *merge_heap(node *a, node *b){
        /////////
        if(!a)
            return b;
        if(!b)
            return a;
        node *resheap;
        node *cura = a, *curb = b, *cur;
        //////////
        if (cura->degree <= curb->degree){
            resheap = cura;
            cura = cura->right;
        }
        else{
            resheap= curb;
            curb = curb->right;
        }
        cur = resheap;

        while (cura && curb){
            if (cura->degree <= curb->degree){
                cur->right = cura;
                cur = cura;
                cura = cura->right;
            }
            else{
                cur->right = curb;
                cur = curb;
                curb = curb->right;
            }
        }

        if (cura)
            cur->right = cura;
        else
            cur->right = curb;

        //resheap.root = merge_same_trees(resheap.root);
        return merge_same_trees(resheap);
    }

    node *inserting(node *heap, int data){
        node *temp = new node;
        temp->child = NULL;
        temp->data = data;
        temp->degree = 0;
        temp->right = heap;
        heap = merge_same_trees(temp);
        return heap;
    }

    int get_min(node *heap){
        if (!heap)
            return -1;

        node *cur = heap;
        int mini = cur->data;
        cur = cur->right;
        while (cur){
            if (cur->data < mini)
                mini = cur->data;
            cur = cur->right;
        }
        return mini;
    }

    node *extract_min(node *heap){
        if (!heap)
            return NULL;
        node *cur = heap, *prev = NULL, *del = NULL;

        int mini = get_min(heap);
        while (cur){
            if (cur->data == mini){
                if (prev)
                    prev->right = cur->right;
                else
                    heap = cur->right;
                del = cur;
                cur = NULL;
                break;
            }
            cur = cur->right;
        }
        node *new_heap = tsil(del->child);
        return merge_heap(heap,new_heap);
    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
