#ifndef SPLAY_TREE_H_INCLUDED
#define SPLAY_TREE_H_INCLUDED

template<class T>
class splay_tree{
    struct node{
    T key;
    node *parent, *left, *right;
    };

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
        if (parent == NULL){
            main_root = vert;
            return vert;
        }
        node *gparent = parent->parent;
        if (gparent == NULL){
            rotating(parent, vert);
            main_root = vert;
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
        main_root = vert;
        return splay(vert);
    }

    void spliting(node *vert, T key, node *&root1, node *&root2){
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
public:
    node *main_root;
		Red_Black_Tree(){
			main_root = NULL;
		}

    node *removing(node *vert, T key){
        vert = finding(vert, key);
        set_parent(vert->left, NULL);
        set_parent(vert->right, NULL);
        return merging(vert->left, vert->right);
    }

    node *inserting(node *vert, T key){
        node *left = new node, *right = new node;
        spliting(vert, key, left, right);
        node *new_node = new node;
        new_node->left = left;
        new_node->right = right;
        new_node->key = key;
        main_root = new_node;
        keep_parent(new_node);
        return vert;
    }

    node *finding(node *vert, T key){
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

    void print(node *p, int level){
		    if (p == NULL){
                for(int i = 0; i < level; i++)
                    std::cout<<"\t";
                std::cout <<"NULL"<<'\n';
                return;
		    }
            print(p->right, level+1);
            for(int i = 0; i < level; i++)
                std::cout<<"\t";
            std::cout<< p->key <<'\n';
            print(p->left, level+1);
        }
};


#endif // SPLAY_TREE_H_INCLUDED
