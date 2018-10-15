#include <iostream>

using namespace std;

struct node{
    int key;
    node *parent, *left, *right;
};

class splay_tree{

    void set_parent(node *child, node *parent){
        if (child != NULL)
            child->parent = parent;
    }

    void keep_parent(node *vert){
        set_parent(vert->left, vert);
        set_parent(vert->right, vert);
    }

    void rotating(node *parent, node *child){
        node *gparent = parent->parent;
        if (gparent != NULL){
            if (gparent->left == parent)
                gparent->left = child;
            else
                gparent->right = child;
        }
        if (parent->left == child){
            parent->left = child->right;
            child->right = parent;
        }
        else {
            parent->right = child->left;
            child->left = parent;
        }
        keep_parent(child);
        keep_parent(parent);
        child->parent = gparent;
    }

    node *splay(node *vert){
        node *parent = vert->parent;
        if (parent == NULL)
            return vert;
        node *gparent = parent->parent;
        if (gparent == NULL){
            rotating(parent, vert);
            return vert;
        }
        if (gparent->left == parent && parent->left == vert){  //zig-zig
            rotating(gparent, parent);
            rotating(parent, vert);
        }
        else{
            rotating(parent, vert);
            rotating(gparent, vert);
        }
        return splay(vert);
    }

    node *finding(node *vert, int key){
        if (vert == NULL)
            return NULL;
        if (key == vert->key)
            return splay(vert);
        if (key < vert->key && vert->left!=NULL)
            return finding(vert->left, key);
        if (key >vert->key && vert->right != NULL)
            return finding(vert->right, key);
        return splay(vert);
    }

    void spliting(node *vert, int key, node *&root1, node *&root2){
        if (vert == NULL){
            root1 = NULL;
            root2 = NULL;
            return;
        }
        vert = finding(vert, key);
        if (vert->key == key){
            set_parent(vert->left, NULL);
            set_parent(vert->right, NULL);
            root1 = vert->left;
            root2 = vert->right;
            return;
        }
        if (vert->key < key){
            node *right = vert->right;
            vert->right = NULL;
            set_parent(right, NULL);
            root1 = vert;
            root2 = right;
            return;
        }
        node *left = vert->left;
        vert->left = NULL;
        set_parent(left, NULL);
        root1 = left;
        root2 = vert;
    }

    node *inserting(node *vert, int key){
        node *left, *right;
        spliting(vert, key, left, right);
        keep_parent(vert);
        return vert;
    }

    node *merging(node *left, node *right){
        if (right == NULL)
            return left;
        if (left == NULL)
            return right;
        right = finding (right, left->key);
        right->left = left;
        left->parent = right;
        return right;
    }

    node *removing(node *vert, int key){
        vert = finding(vert, key);
        set_parent(vert->left, NULL);
        set_parent(vert->right, NULL);
        return merging(vert->left, vert->right);
    }

};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
