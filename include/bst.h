#ifndef BST_H
#define BST_H

#include <functional>
#include <initializer_list>
#include <iostream>

// bool operator>(int n, BST::Node node);
// bool operator>=(int n, BST::Node node);
// bool operator<(int n, BST::Node node);
// bool operator<=(int n, BST::Node node);
// bool operator==(int n, BST::Node node);
// std::ostream& operator<<(std::ostream& os, BST::Node& node);
class BST
{
public:
class Node
{
public:
	Node(int value, Node* left, Node* right)
        :value{value},left{left},right{right}{

    }
	Node():value{0},left{nullptr},right{nullptr}{

    }
    Node(const Node& node)
        :value{node.value},
         left(node.left),
         right(node.right){

    }

	int value;
	Node* left;
	Node* right;

    bool operator>(int);
    bool operator>=(int);
    bool operator<(int);   
    bool operator<=(int);
    bool operator==(int); 
};

    BST():root{nullptr}{
        // std::cout<<"BST():root{nullptr}{}"<<std::endl;
    }

    BST(std::initializer_list<int> nums) : root(nullptr) {
        for (int num : nums) {
            add_node(num);
        }
        // std::cout<<"BST(std::initializer_list<int> nums) : root(nullptr) {}"<<std::endl;
    }

    BST(BST& bst){
        std::function<BST::Node*(BST::Node*)> copy = [&copy](BST::Node* root)->BST::Node*{
            if(root == nullptr)  return nullptr;
            // 创建新节点，值为原节点的值
            BST::Node* new_root = new BST::Node(root->value,nullptr,nullptr);
            // 递归复制左子树和右子树
            new_root->left = copy(root->left);
            new_root->right = copy(root->right);
            return new_root;
        };
        root = copy(bst.get_root());
    }

    BST(BST&& bst){
        root = bst.get_root();
        auto& old_root = bst.get_root();
        old_root = nullptr;
    }

    BST& operator=(BST& bst){
        if(this == &bst)  return *this;

        std::vector<Node*> nodes;
        bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
        for(auto& node: nodes)
            delete node;
            
        std::function<BST::Node*(BST::Node*)> copy = [&copy](BST::Node* root)->BST::Node*{
            if(root == nullptr)  return nullptr;
            // 创建新节点，值为原节点的值
            BST::Node* new_root = new BST::Node(root->value,nullptr,nullptr);
            // 递归复制左子树和右子树
            new_root->left = copy(root->left);
            new_root->right = copy(root->right);
            return new_root;
        };

        root = copy(bst.get_root());
        return *this;
    }

    BST& operator=(BST&& bst){
        if(this == &bst)  return *this;

        // 删除旧的对象占用的内存
        std::vector<Node*> nodes;
        bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
        for(auto& node: nodes)
            delete node;

        root = bst.get_root();
        auto& old_root = bst.get_root();
        old_root = nullptr;
        return *this;             
    }

    ~BST()
    {
        std::vector<Node*> nodes;
        bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
        for(auto& node: nodes)
            delete node;
    }

    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    void bfs_s(std::function<void(Node**& node)> func);    
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& os, BST& bst);
    BST& operator++();
    BST operator++(int);
private:

    Node* root;
};

bool operator>(int n, BST::Node& node);
bool operator>=(int n, BST::Node& node);
bool operator<(int n, BST::Node& node);
bool operator<=(int n, BST::Node& node);
bool operator==(int n, BST::Node& node);
std::ostream& operator<<(std::ostream& os, BST::Node& node);

#endif //BST_H