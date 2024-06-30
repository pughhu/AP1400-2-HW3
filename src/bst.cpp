#include "bst.h"
#include <queue>
#include <iostream>
#include <iomanip>

BST::Node*& BST::get_root(){
    return root;
}

std::ostream& operator<<(std::ostream& os, BST& bst){
    os<<"********************************************************************************"<<std::endl;
    auto f = [&os](BST::Node*& node){
        os<<std::setw(17)<<std::left<< node<<"=> value:"<<std::setw(10)<<std::left<<node->value<<"left:"<<
        std::setw(16)<<std::left<<node->left<<"right:"<<node->right<<std::endl;
    };
    bst.bfs(f);
    os<<"binary search tree size: "<<bst.length()<<std::endl;
    os<<"********************************************************************************"<<std::endl;
    return os;
}
// 下面这样写会报错：非成员运算符要求类类型或枚举类型的参数
// BST& operator++(int value){
//     this->bfs([](Node*& node){++(node->value);});
//     return *this;
// }
BST& BST::operator++(){
    this->bfs([](Node*& node){++(node->value);});
    return *this;
}

// 后缀形式 bst++
BST BST::operator++(int){
    BST temp(*this); // 创建一个副本，保存原始值
    // 进行递增操作
    this->bfs([](Node*& node){++(node->value);});    
    // 返回保存原始值的副本
    return temp;    
}

std::ostream& operator<<(std::ostream& os, BST::Node& node){
    // 0x188dee70       => value:25        left:0x188dedd0      right:0x188dedf0
    os<<std::setw(17)<<std::left<< &node<<"=> value:"<<std::setw(10)<<std::left<<node.value<<"left:"<<
    std::setw(16)<<std::left<<node.left<<"right:"<<node.right<<std::endl;

    return os;
}

// 这样写报错了，为什么?
// bool operator>(BST::Node node, int n){
//     return node.value > n;
// }

bool BST::Node::operator>(int n){
    return this->value > n;
}

bool BST::Node::operator>=(int n){
    return this->value >= n;
}

bool BST::Node::operator<(int n){
    return this->value < n;
}

bool BST::Node::operator<=(int n){
    return this->value <= n;
}

bool BST::Node::operator==(int n){
    return value == n;
}

// 下面这些函数如果不在头文件里声明，那么unit_test.cpp里面会报错，
bool operator>(int n, BST::Node& node){
    return n > node.value;
}

bool operator>=(int n, BST::Node& node){
    return n >= node.value;
}

bool operator<(int n, BST::Node& node){
    return n < node.value;
}

bool operator<=(int n, BST::Node& node){
    return n <= node.value;
}

bool operator==(int n, BST::Node& node){
    return node.value == n;
}

// BST::~BST()
// {
//     std::vector<Node*> nodes;
//     bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
//     for(auto& node: nodes)
//         delete node;
// }

// void BST::bfs(std::function<void(Node*& node)> func){
//     std::deque<Node*> deq{root};
//     std::queue<Node*> que(deq);
    
//     while(!que.empty()){
//         auto front = que.front();
//         que.pop();
//         que.push(front->left);
//         que.push(front->right);
//         func(front);
//     }
// }

void BST::bfs(std::function<void(Node*& node)> func) {
    if (root == nullptr) return;

    std::queue<Node*> que;
    que.push(root);

    while (!que.empty()) {
        Node* front = que.front();
        que.pop();

        func(front);

        if (front->left != nullptr) {
            que.push(front->left);
        }
        if (front->right != nullptr) {
            que.push(front->right);
        }
    }
}

void BST::bfs_s(std::function<void(Node**& node)> func) {
    if (root == nullptr) return;

    std::queue<Node**> que;
    que.push(&root);

    while (!que.empty()) {
        Node** front = que.front();
        que.pop();

        func(front);

        if ((*front)->left != nullptr) {
            que.push(&((*front)->left));
        }
        if ((*front)->right != nullptr) {
            que.push(&((*front)->right));
        }
    }
}

size_t BST::length(){
    size_t n{};

    auto f = [&n](Node*& node){++n;};
    BST::bfs(f);
    return n;
}

static BST::Node* add_node_(BST::Node* node, int value){
    if(node == nullptr)
        return new BST::Node{value, nullptr, nullptr};
    if(value < node->value) 
        node->left = add_node_(node->left, value);
    else if(value > node->value)
        node->right = add_node_(node->right, value);

    return node;
}

// bool BST::add_node(int value){
//     bool added = false;
//     std::function<BST::Node*(BST::Node*,int)> f = [&added,&f](BST::Node* node, int value)->BST::Node*{
//         if(node == nullptr){
//             added = true;
//             return new BST::Node(value, nullptr, nullptr);
//         }
//         if(value < node->value) 
//             node->left = f(node->left, value);
//         else if(value > node->value)
//             node->right = f(node->right, value);

//         return node;        
//     };
//     f(root, value);
//     return added;
// }

bool BST::add_node(int value) {
    if (root == nullptr) {
        root = new Node(value, nullptr, nullptr);
        return true;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        } else if (value > current->value) {
            current = current->right;
        } else {
            return false;  // Node with the same value already exists
        }
    }

    if (value < parent->value) {
        parent->left = new Node(value, nullptr, nullptr);
    } else {
        parent->right = new Node(value, nullptr, nullptr);
    }

    return true;
}

BST::Node** BST::find_node(int value){
    std::function<Node**(Node**, int)>  f = [&f](Node** x, int value)->Node**{
        if(*x == nullptr)
            return nullptr;
        if((*x)->value == value)
            return x;
        if(value < (*x)->value){
            return f((&(*x)->left), value);
        }else{
            return f(&((*x)->right), value);
        }    
    };

    return f(&root, value);
}

// BST::Node** BST::find_parrent(int value){
//     Node** parrent{};
//     auto f = [value, &parrent](Node*& node){
//         if((node->left)!=nullptr && node->left->value==value){
//             std::cout<<"parent: "<<node->value<<std::endl;
//             std::cout<<"left: "<<node->left->value<<std::endl;
//             std::cout<<"right: "<<node->right->value<<std::endl;              
//             parrent = &node;
//         }
//         if((node->right)!=nullptr && node->right->value==value){
//             std::cout<<"parent: "<<node->value<<std::endl;
//             std::cout<<"left: "<<node->left->value<<std::endl;
//             std::cout<<"right: "<<node->right->value<<std::endl;          
//             parrent = &node;
//         }
//     };
//     BST::bfs(f);
//     return parrent;
// }

BST::Node** BST::find_parrent(int value){
    Node** parrent{};
    auto f = [value, &parrent](Node**& node){
        if(((*node)->left)!=nullptr && (*node)->left->value==value)           
            parrent = node;
        if(((*node)->right)!=nullptr && (*node)->right->value==value) 
            parrent = node;
    };
    BST::bfs_s(f);
    return parrent;
}

BST::Node** BST::find_successor(int value){
    std::function<Node**(Node**,int)>f = [&f](Node** root, int value)->Node**{
        if(*root == nullptr)
            return nullptr;        
        if(value <= (*root)->value){
            if((*root)->left == nullptr)
                return nullptr;
            else
                return f(&((*root)->left), value);
        }
        Node** t{};
        if((*root)->right == nullptr){
            return root;
        }
        else{
            t = f(&((*root)->right), value);
        }
        if(t == nullptr)
            return root;
        else
            return t;
    };

    return f(&root,value); 
}

// Node* successor(Node* root, int value){
//     if(value >= root->value)
//         return successor(root->right, value);
//     if(root == nullptr)
//         return nullptr;
//     Node* t = successor(root->left, value);
//     if(t == nullptr)
//         return root;
//     else
//         return t;
// }

// 返回值表示对父节点的左子节点或右子节点的更新，具体比较value和node.value值大小决定更新左右
static BST::Node* dele(BST::Node* node, int value){
    // 删除最小节点的函数deleteMin
    std::function<BST::Node*(BST::Node*)> deleteMin = [&deleteMin](BST::Node* node)->BST::Node*{
        if(node == nullptr) return nullptr;
        if(node->left == nullptr){
            auto result = node->right;
            delete node;
            return result;
        }
        node->left = deleteMin(node->left);
        return node;
    };
    // 求最小节点的函数min
    std::function<BST::Node*(BST::Node*)> min = [&min](BST::Node* node)->BST::Node*{
        if(node == nullptr) return nullptr;
        if(node->left == nullptr) return node;
        return min(node->left);
    };
    // 如果找不到对应的节点
    if(node == nullptr) 
        return nullptr;
    // 继续找要删除的节点
    if(value < node->value) 
    {
        node->left = dele(node->left, value);
    }else if(value > node->value){
        node->right = dele(node->right, value);
    }else{
    // 找到了对应的节点
        // 边界处理
        if(node->left == nullptr){
            auto temp = node->right;
            delete node;
            return temp;
        }else if(node->right == nullptr){
            auto temp = node->left;
            delete node;
            return temp;
        }
        // 待删除的结点有左右两子节点
        BST::Node* temp = min(node->right);
        BST::Node* replaced = new BST::Node(temp->value, nullptr, nullptr);
        // debug
        replaced->right = deleteMin(node->right);
        replaced->left = node->left;
        delete node;
        return replaced;
    }
    return node;
}

bool BST::delete_node(int value){
    auto find = BST::find_node(value);
    root = dele(root, value);   // 一定要更新root的值，因为有可能删除的是root，否则root会成为空指针
    if(find == nullptr)
        return false;
    else    
        return true;
}