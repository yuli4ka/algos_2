#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

using namespace std;

namespace spacebinary_tree{
template <class T>
class btree{

    struct node{
        T key_value;
        node *left;
        node *right;
    };

public:

    btree(){
        root=NULL;
    };
    ~btree(){
			this->root = nullptr;
		};

    void Insert(T key){
  if(root!=NULL)
    insert(key, root);
  else
  {
    root=new node;
    root->key_value=key;
    root->left=NULL;
    root->right=NULL;
  }
};

    node *search(T key){
  return search(key, root);
};

    void destroy_tree(){
  destroy_tree(root);
};

    void print(){
        print(root, 0);
    }
    ////
    void make_gv(string output_file)
{
  ofstream fout(output_file);
  fout << "digraph g{" << endl;
  fout << "node [shape = record,height = .1];" << endl;
  sub_gv(root, fout);
  fout << "}" << endl;
}

/////
private:
////
void sub_gv(node *node, ofstream& file)
{
  if (node->left != nullptr) {
    file << node->key_value << "->" << node->left->key_value << ";\n";
    sub_gv(node->left, file);
  }
  if (node->right != nullptr) {
    file << node->key_value << "->" << node->right->key_value << ";\n";
    sub_gv(node->right, file);
  }
}
/////

    void print(node *p, int level){
		    if (p == NULL){
                for(int i = 0; i < level; i++)
                    std::cout<<"\t\t";
                std::cout <<"NULL"<<'\n';
                return;
		    }
            print(p->right, level+1);
            for(int i = 0; i < level; i++)
                std::cout<<"\t\t";
            std::cout<< p->key_value <<'\n';
            print(p->left, level+1);
        }

    void destroy_tree(node *leaf){
    if(leaf!=NULL)
  {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
};

    void insert(T key, node *leaf){
  if(key< leaf->key_value)
  {
    if(leaf->left!=NULL)
     insert(key, leaf->left);
    else
    {
      leaf->left=new node;
      leaf->left->key_value=key;
      leaf->left->left=NULL;
      leaf->left->right=NULL;
    }
  }
  else if(key>=leaf->key_value)
  {
    if(leaf->right!=NULL)
      insert(key, leaf->right);
    else
    {
      leaf->right=new node;
      leaf->right->key_value=key;
      leaf->right->left=NULL;
      leaf->right->right=NULL;
    }
  }
};

    node *search(T key, node *leaf){
  if(leaf!=NULL)
  {
    if(key==leaf->key_value)
      return leaf;
    if(key<leaf->key_value)
      return search(key, leaf->left);
    else
      return search(key, leaf->right);
  }
  else return NULL;
};

    node *root;
};
}

#endif // BINARY_TREE_H_INCLUDED
