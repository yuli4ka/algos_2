#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

#define INF 0x3F3F3F3F

using namespace std;

namespace spacebinary_tree{
template <class T>
class btree{

    struct node{
        T key_value;
        node *left;
        node *right;
        long long p;
    };
    long long p_global;
    vector<node*> pr;
    vector<vector<long long>>weight, sum, rooted;
public:

    btree(){
        p_global = 0;
        root=NULL;
    };
    btree(node t){
        this->key_value = t->key_value;
        this->left = NULL;
        this->right = NULL;
        this->p = t->p;
    };
    ~btree(){
			this->root = nullptr;
    };

    const T & operator=(const T& t) {
        if (this != &t) {
            this->~T();
            new (this) T(t);
        }
        return *this;
    }

    void Insert(T key){
        node *n = new node;
        n->left = NULL;
        n->right = NULL;
        n->key_value = key;
        n->p = 0;
        pr.push_back(n);
    };

    node *search(T key){
        node* s= search(key, root);
        s->p = s->p+1;
        p_global++;
        return s;
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
        make_graph();
        ofstream fout(output_file);
        fout << "digraph g{" << endl;
        //fout << "node [shape = record,height = .1];" << endl;
        sub_gv(root, fout);
        fout << "}" << endl;
    }

    node *build_graph(int left, int right){
        if (left <= right){
            node* nnode = new node;
            nnode = pr[rooted[left][right]-1];
            nnode->left = build_graph(left, rooted[left][right]-1);
            nnode->right = build_graph(rooted[left][right]+1, right);
            return nnode;
        }
        return NULL;
    }

    void make_graph(){
        cout << "start" << endl;
        /*sum.clear();
        rooted.clear();
        weight.clear();*/
        sum.resize(pr.size()+2);
        rooted.resize(pr.size()+2);
        weight.resize(pr.size()+2);
        for (long long i = 0 ; i < pr.size()+2; i++){
            sum[i].resize(pr.size()+2);
            rooted[i].resize(pr.size()+2);
            weight[i].resize(pr.size()+2);
        }
        cout << "after resize" << endl;
        /*for (long long i = 0; i <= pr.size(); i++){
            sum[i][i-1] = 0;
            weight[i][i-1] = 0;
        }*/
        for (long long l = 1; l <= pr.size(); l++)
        for (long long i = 1; i <= pr.size()-l+1; i++){
            long long j = i+l-1;
            sum[i][j] = INF;
            weight[i][j] = weight[i][j-1]+pr[j-1]->p;
            for (long long r = i; r <= j; r++){
                long long t = sum[i][r-1]+sum[r+1][j]+weight[i][j];
                if (t < sum[i][j]){
                    sum[i][j] = t;
                    rooted[i][j] = r;
                }
            }
        }
        cout << "after fill rooted and sum and weight" << endl;
        for (int i = 0; i<=pr.size(); i++){
            for (int j = 0; j <=pr.size(); j++)
                cout << rooted[i][j] << ' ';
            cout << endl;
        }
        cout << "before search" << endl;
        root = nullptr;
        if (root != nullptr){
            for (long long l = 0; l < pr.size(); l++){
                node *t = search(pr[l]->key_value);
                t->p -= 1;
                pr[l]->p = t->p;
            }
        }
        cout << "after search" << endl;
        cout << "before build" << endl;
        root = build_graph(1, pr.size());
        cout << "after build" << endl;
    }




/////
private:
////
void sub_gv(node *node, ofstream& file)
{
    if (node == NULL)
        return;
  if (node->left != NULL) {
    file << '"' << node->key_value << '"' << " -> " << '"' << node->left->key_value << '"' << ";\n";
    sub_gv(node->left, file);
  }
  if (node->right != NULL) {
    file << '"' << node->key_value << '"' << "->" << '"' << node->right->key_value << '"' << ";\n";
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
