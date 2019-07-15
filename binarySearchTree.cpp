#include<iostream>
#include<cmath>
#include<queue>
using namespace std;

class node{
public:
        int data;
        node* left;
        node* right;

        node(int data){
                this->data = data;
                this->left = NULL;
                this->right = NULL;
        }
};


int findDigits(int num){
        int n=0;
        while(num != 0){
                num=num/10;
                n++;
        }
        return n;
}

int findHeight(node* root){
        if(root == NULL) return 0;
        return max(findHeight(root->left), findHeight(root->right)) + 1;
}

void visualise(node* root){
        if (root == NULL) return;
        int height = findHeight(root);
        queue<node*> n;
        queue<node*> e;
        n.push(root);
        int i;
        int digits = 1;
        node* temp = NULL;
        for(int level = 0; level < height; level++){
                temp = n.front();
                e.push(n.front());
                n.pop();
                for(i = 0; i < pow(2, height - level) - 2; i++) cout<<" ";

                if(temp != NULL) cout<<temp->data;
                else cout<<" ";
                for(int k = 1; k < pow(2, level); k++){
                        if(temp != NULL) digits = findDigits(temp->data);
                        temp = n.front();
                        e.push(n.front());
                        n.pop();
                        for(i = 0; i < pow(2, height + 1 - level) - digits; i++) cout<<" ";
                        digits = 1;
                        if(temp != NULL) cout<<temp->data;
                        else cout<<" ";
                }

                for(i = 0; i < pow(2, height - level) - 2; i++) cout<<" ";
                cout<<"\n";

                if(level != height - 1){
                        for(i = 0; i < (pow(2, height - level) - 2 - pow(2, height - level - 2)); i++) cout<<" ";

                        for(int k = 0; k<pow(2, level); k++){
                                temp = e.front();
                                if(temp == NULL) temp = new node(0);
                                n.push(temp->left);
                                if(temp->left != NULL) cout<<"/";
                                else cout<<" ";
                                for(i = 0; i < pow(2, height - level - 1) - 1; i++) cout<<" ";
                                n.push(temp->right);
                                if(temp->right != NULL) cout<<"\\";
                                else cout<<" ";
                                for(i = 0; i < (pow(2, height - level + 1) - 1 - pow(2, height - level - 1)); i++) cout<<" ";
                                e.pop();
                        }

                        for(i = 0; i < (pow(2, height - level) - 2 - pow(2, height - level - 2)); i++) cout<<" ";
                        cout<<"\n";
                }
        }
}

node* insert(node* root, int data){
        if (root == NULL){
                node* temp = new node(data);
                return temp;
        }

        else if (data <= root->data) root->left = insert(root->left, data);
        else root->right = insert(root->right, data);

        return root;
}

node* findMax(node* root){
        if (root == NULL) return root;
        while (root->right != NULL)
                root = root->right;
        return root;
}

node* remove(node* root, int data){
        if (root == NULL) return root;
        else if (data < root->data) root->left = remove(root->left, data);
        else if (data > root->data) root->right = remove(root->right, data);
        else{
                if (root->left == NULL  && root->right == NULL){
                        delete(root);
                        return NULL;
                }
                else if (root->left == NULL){
                        node* temp = root->right;
                        delete(root);
                        return temp;
                }
                else if (root->right == NULL){
                        node* temp = root->left;
                        delete(root);
                        return temp;
                }
                else{
                        node* leftMax = findMax(root->left);
                        root->data = leftMax->data;
                        root->left = remove(root->left, leftMax->data);
                }
        }
        return root;
}

void inorder(node* root){
        if(root != NULL){
                inorder(root->left);
                cout<<root->data<<" ";
                inorder(root->right);
        }
}

void display(node* root){
        if (root != NULL) inorder(root);
        else cout<<"the bst is empty";
        cout<<"\n";
}

void bft(node* root){
  queue<node*> q;
  q.push(root);
  while(!q.empty()){
    node* temp = q.front();
    q.pop();
    cout<<temp->data<<" ";
    if(temp->left != NULL) q.push(temp->left);
    if(temp->right != NULL) q.push(temp->right);
  }
}

void preorder(node* root){
  if(root != NULL){
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
  }
}



int main(){
        node* root = NULL;
        int choice;
        char ch = 'y';

        while (ch == 'y'){
                cout<<"1. insert\n2. remove\n3. display\n4. find height\n5. visualise\n6. BFT\n7. DFT\n";
                cin>>choice;
                switch (choice){
                        case 1 :
                                int n;
                                cout<<"Enter the number of values\n";
                                cin>>n;
                                cout<<"Enter the values\n";
                                for(int i=0; i<n; i++){
                                        int data;
                                        cin>>data;
                                        root = insert(root, data);
                                }
                                visualise(root);
                                break;
                        case 2 :
                                int data;
                                cout<<"Enter the data\n";
                                cin>>data;
                                root = remove(root, data);
                                visualise(root);
                                break;
                        case 3 :
                                display(root);
                                break;
                        case 4 :
                                cout<<"height: "<<findHeight(root)<<"\n";
                                break;
                        case 5 :
                                visualise(root);
                                break;
                        case 6 :
                                bft(root);
                                break;
                        case 7 :
                                preorder(root);
                                break;
                        default:
                                cout<<"enter a valid option\n";
                }
                cout<<"press y to continue\n";
                cin>>ch;
        }
        return 0;
}
