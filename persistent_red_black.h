#ifndef RED_BLACK_TREE_H_INCLUDED
#define RED_BLACK_TREE_H_INCLUDED

#include <vector>
#include <string>

namespace spacePersistent_Red_Black_Tree{
	template<class T>
	class Red_Black_Tree{
		struct TreeNode{
			T data;
			bool red;
			TreeNode *left;
			TreeNode *right;
			TreeNode *parent;
			TreeNode() = default;

			TreeNode(T _data, bool _red = false):
			    data(_data), red(_red), left(nullptr), right(nullptr), parent(nullptr) {};

			TreeNode(TreeNode * node):
			    data(node->data), red(node->red), left(node->left), right(node->right), parent(nullptr) {};

			TreeNode(T _data, TreeNode * _parent) :
			    data(_data), red(true), parent(_parent), left(nullptr), right(nullptr) {}
		};

		//
		//TreeNode *nil;
	public:
		Red_Black_Tree(){
			//nil = new TreeNode();
			//nil->red = false;
			//nil->left = nil;
			//nil->right = nil;
			//nil->parent = nil;
		}

		/////////
		~Red_Black_Tree(){
			//delete nil;
			//this->nil = nullptr;
		}

		//////

		void Insert(T data, int version = -1){
		    if (find_(data, version))
                return;
            TreeNode *parent_node = nullptr, *new_root = nullptr,
                    *new_node;
            if (version < 0)
                new_node = GetLastRoot();
            else
                new_node = roots[version];
            if (new_node){
                new_root = new TreeNode(new_node);
                new_node = new_root;
            }
            while(new_node){
                new_node->parent = parent_node;
                parent_node = new_node;
                if (new_node->data < data){
                    if (new_node->right)
                        new_node->right = new TreeNode(new_node->right);
                    new_node = new_node->right;
                }
                else{
                    if (new_node->left)
                        new_node->left = new TreeNode(new_node->left);
                    new_node = new_node->left;
                }
            }
            new_node = new TreeNode(data, true);
            new_node->parent = parent_node;
            if (!parent_node){
                new_node->red = false;
                new_root = new_node;
            }
            else if (parent_node->data < data)
                parent_node->right = new_node;
            else
                parent_node->left = new_node;
            if (version < 0)
                version = roots.size(); /////
            roots.push_back(new_root);
            std::cout<<"Before balance" << std::endl;
            insertBalance(new_node, version);
            std::cout<<"After balance " << new_node->red << std::endl;
		}

		void Delete(T data, int version = -1){
            TreeNode *node;/* = find_(data, version);
            if (!node)
                return;*/

            TreeNode *new_root = nullptr, *parent_node = nullptr;
            if (version < 0)
                node = GetLastRoot();
            else
                node = roots[version];
            if (node) {
                new_root = new TreeNode(node);
                node = new_root;
            }
            if (version < 0)
                version = roots.size()-1; ///////
                ////
            if (!find_(data, version)){
                std::cout << "searching say no" << std::endl;
                return;
            }
                ////
            roots.push_back(new_root);
            bool found = false;
            while (!found) {
                node->parent = parent_node;
                parent_node = node;
                if (node->data < data) {
                    if (node->right)
                        node->right = new TreeNode(node->right);
                    node = node->right;
                }
                else if (data < node->data) {
                    if (node->left)
                    node->left = new TreeNode(node->left);
                    node = node->left;
                }
                else {
                    found = true;
                }
            }
            std::cout << "before fix_up" << std::endl;
            TreeNode *successor = node, *fix_up_node = nullptr;
            bool node_original_color = successor->red;


            ////////
            if (!node->left) {
                if (node->right) {
                node->right = new TreeNode(node->right);
                node->right->parent = node;
                }
                fix_up_node = node->right;
                replace_(node, node->right, version);
            }
            else if (!node->right) {
                if (node->left) {
                    node->left = new TreeNode(node->left);
                    node->left->parent = node;
                }
                fix_up_node = node->left;
                replace_(node, node->left, version);
            }
            else {
                node->right = new TreeNode(node->right);
                node->right->parent = node;
                successor = TreeMin(node->right);
                node_original_color = successor->red;
                if (successor->right) {
                    successor->right = new TreeNode(successor->right);
                successor->right->parent = successor;
                }
                fix_up_node = successor->right;
                if (successor->parent == node) {
                    if (fix_up_node)
                        fix_up_node->parent = successor;
                }
                else {
                    replace_(successor, successor->right, version);
                    successor->right = node->right;
                    if (successor->right)
                        successor->right->parent = successor;
                }
                replace_(node, successor, version);
                successor->left = node->left;
                successor->left->parent = successor;
                successor->red = node->red;
            }
            std::cout << "before balance" << std::endl;
            if (node_original_color == false)
                deleteBalance(fix_up_node, version);
            std::cout << "after balance" << std::endl;
            delete node;
        }

        void make_gv(std::string output_file, int version = -1)
        {
            std::ofstream fout(output_file);
            fout << "digraph g{" << std::endl;
            //fout << "node [shape = record,height = .1];" << endl;
            TreeNode *root;
            if (version < 0)
                root = GetLastRoot();
            else
                root = roots[version];
            sub_gv(root, fout);
            fout << "}" << std::endl;
        }

	private:
	    std::vector<TreeNode*> roots;

	    void sub_gv(TreeNode *node, std::ofstream& file)
        {
            if (node == NULL)
                return;
            if (node->left != NULL) {
                file << '"' << node->data << '"' << " -> " << '"' << node->left->data << '"' << ";\n";
                sub_gv(node->left, file);
            }
            file << '"' << node->data << '"' << "[style=filled,color=";
            if (node->red)
                file <<"red];\n";
            else
                file <<"gray];\n";
            if (node->right != NULL) {
                file << '"' << node->data << '"' << "->" << '"' << node->right->data << '"' << ";\n";
                sub_gv(node->right, file);
            }
        }

	    TreeNode *GetLastRoot(){
            return (roots.empty() ? nullptr : roots.back());
        }

	    void replace_(TreeNode *old_node, TreeNode *new_node, int version){
            if (!old_node->parent)
                roots[version] = new_node;
            else if (old_node == old_node->parent->left)
                old_node->parent->left = new_node;
            else
                old_node->parent->right = new_node;
            if (new_node)
                new_node->parent = old_node->parent;
	    }

		void insertBalance(TreeNode *node, int version){
		    ////
		    if (!node->parent) return;
		    if (!node->parent->red) return;
		    ////
			TreeNode *uncle;
            if (node->parent->red) { ////////////////////there was "while"
                std::cout <<"shit_in" << std::endl;
                if (node->parent == node->parent->parent->left) {
                    std::cout <<"shit_left_in" << std::endl;
                    uncle = node->parent->parent->right;

                    if (uncle && uncle->red) {
                        node->parent->red = uncle->red = false;
                        node->parent->parent->red = true;
                        node = node->parent->parent;
                    } else {
                        if (node == node->parent->right) {
                        node = node->parent;
                        L_rotate(node, version);
                    }
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    R_rotate(node->parent->parent, version);
                    std::cout <<"shit_left_out" << std::endl;
                }
                } else {
                    std::cout <<"shit_right_in" << std::endl;
                    uncle = node->parent->parent->left;

                    if (uncle && uncle->red) {
                        node->parent->red = uncle->red = false;
                        node->parent->parent->red = true;
                        node = node->parent->parent;
                    } else {
                        if (node == node->parent->left) {
                            node = node->parent;
                            R_rotate(node, version);
                        }
                        node->parent->red = false;
                        node->parent->parent->red = true;
                        L_rotate(node->parent->parent, version);
                    }
                    std::cout <<"shit_right_out" << std::endl;
                }
                std::cout <<"shit_out" << std::endl;
          }
          std::cout <<"version_out" << std::endl;
            roots[version]->red = false;
          std::cout <<"version_out" << std::endl;
        }

		void deleteBalance(TreeNode *node, int version){
			TreeNode *brother = nullptr;
            while (node != roots[version] && node){//} && node->red == false && node) { /////there was while
                if (node == node->parent->left) {
                    brother = node->parent->right;
                    if (brother->red == true) {
                        brother->red = false, node->parent->red = true;
                        L_rotate(node->parent, version);
                        brother = node->parent->right;
                    }
                    if (brother->left->red == false && brother->right->red == false) {
                        brother->red = true;
                        node = node->parent;
                    }
                    else {
                        if (brother->right->red == false) {
                            std::swap(brother->red, brother->left->red);
                            R_rotate(brother, version);
                            brother = node->parent->right;
                        }
                        brother->red = node->parent->red;
                        node->parent->red = false;
                        brother->right->red = false;
                        L_rotate(node->parent, version);
                        node = roots[version];
                    }
                }
                else {
                    brother = node->parent->left;
                    if (brother->red == true) {
                        brother->red = false, node->parent->red = true;
                        R_rotate(node->parent, version);
                        brother = node->parent->left;
                    }
                    if (brother->left->red == false && brother->right->red == false) {
                        brother->red = true;
                        node = node->parent;
                    }
                    else {
                        if (brother->left->red == false) {
                            std::swap(brother->red, brother->right->red);
                            L_rotate(brother, version);
                            brother = node->parent->left;
                        }
                        brother->red = node->parent->red;
                        node->parent->red = false;
                        brother->left->red = false;
                        R_rotate(node->parent, version);
                        node = roots[version];
                    }
                }
            }
            if (node)
                node->red = false;
		}
		//
		void L_rotate(TreeNode *node, int version){
		    std::cout << "L_in" << std::endl;
			TreeNode *right_son = node->right;
            if (right_son) {
                node->right = right_son->left;
                if (right_son->left)
                    right_son->left->parent = node;
                right_son->parent = node->parent;
            }
            if (!node->parent)
                roots[version] = right_son;
            else if (node == node->parent->left)
                node->parent->left = right_son;
            else node->parent->right = right_son;
            if (right_son)
                right_son->left = node;
            node->parent = right_son;
            std::cout << "L_out" << std::endl;
        }

		void R_rotate(TreeNode *node, int version){
		    std::cout << "R_in" << std::endl;
			TreeNode *left_son = node->left;
            if (left_son) {
                node->left = left_son->right;
                if (left_son->right)
                    left_son->right->parent = node;
                left_son->parent = node->parent;
            }
            if (!node->parent)
                roots[version] = left_son;
            else if (node == node->parent->left)
                node->parent->left = left_son;
            else node->parent->right = left_son;
            if (left_son)
                left_son->right = node;
            node->parent = left_son;
            std::cout << "R_out" << std::endl;
        }

            TreeNode *TreeMin(TreeNode * node){
                TreeNode * cur_node = node, *parent_node = node;
                while(cur_node->left){
                    cur_node->left = new TreeNode(cur_node->left);
                    cur_node->left->parent = parent_node;
                    parent_node = cur_node;
                    cur_node = cur_node->left;
                }
                return cur_node;
            }

            TreeNode *TreeMax(TreeNode * node){
                TreeNode * cur_node = node, *parent_node = node;
                while(cur_node->right){
                    cur_node->right = new TreeNode(cur_node->right);
                    cur_node->right->parent = parent_node;
                    parent_node = cur_node;
                    cur_node = cur_node->right;
                }
                return cur_node;
            }

		//
	public:
	    TreeNode *find_(T data, int version = -1){
            if (version >= roots.size())
                return nullptr;
            TreeNode *node;
            if (version < 0 )
                node = GetLastRoot();
            else
                node = roots[version];
            while (node){
                if (node->data < data)
                    node = node->right;
                else if (data < node->data)
                    node = node->left;
                else
                    return node;
            }
            return nullptr;
	    }

		/*void print(TreeNode *p, int level){
		    if (p == nil){
                for(int i = 0; i < level; i++)
                    std::cout<<"\t";
                std::cout <<"NIL"<<'\n';
                return;
		    }
            print(p->right, level+1);
            for(int i = 0; i < level; i++)
                std::cout<<"\t";
            std::cout<< p->data <<'\n';
            print(p->left, level+1);
        }*/
	};
}


#endif // RED_BLACK_TREE_H_INCLUDED
