#include <stdio.h>
#include <stdlib.h>


struct Node {
    int priority;
    struct Node* left;
    struct Node* right;
};

struct Node* root;


//Reference
int _print_t(struct Node *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->priority);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) { for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

void print_t(struct Node *tree)
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}


struct Node* GetNewNodes(){
    int random;
    random = rand() % 41;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->priority = random;
    newNode->left = NULL;
    newNode->right = NULL;
}

struct Node* rightRot(struct Node* n){
    struct Node* temp = n->left;
    if(n->left != NULL) {
        n->left = temp->right;
    }
    temp->right = n;
    return temp;
}

struct Node* leftRot(struct Node* n){
    struct Node* temp = n->right;
    if(n->right != NULL) {
        n->right = temp->left;
    }
    temp->left = n;
    return temp;
}

struct Node* splay(struct Node*root, int prio){
    if(root == NULL || root->priority == prio){
        return root;
}
    //Left side of root
    if(root->priority > prio){
        if(root->left == NULL){
            return root;
        }
            //If node is left of parent and parent is left of grand-parent, we do a zig-zig right-right rotation.
        else if (root->left->priority > prio && root->left->left != NULL){
            root->left = rightRot(root->left);
            root = rightRot(root);
            splay(root, prio);
        }
            //If node is right of parent but parent is left or grand-parent, we do a zig-zag left-right rotation.
        else if (root->left->priority < prio  && root->left->right != NULL){
            root->left = leftRot(root->left);
            root = rightRot(root);
            splay(root, prio);
        }
        else{
            root = rightRot(root);
        }
    }


    //Right side of root
    else if(root->priority < prio){
        if(root->right == NULL){
            return root;
        }
        //If node is right of parent and parent is right of grand-parent, we do a zig-zig left-left rotation.
        else if(root->right->priority < prio  && root->right->right != NULL){
            root->right = leftRot(root->right);
            root = leftRot(root);
            splay(root, prio);
        }
        //If node is left of parent but parent is right of grand-parent, we do a zig-zag right-left rotation.
        else if(root->right->priority > prio  && root->right->left != NULL){
            root->right = rightRot(root->right);
            root = leftRot(root);
            splay(root,prio);
        }
        else{
            leftRot(root);
        }
    }
    return root;

}

/*
struct Node* insert(struct Node* root, struct Node* newNode) {
    if (newNode->priority <= root->priority)
        if(root->left == NULL){
            root->left = newNode;
        }
        else {
            root->left = insert(root->left, newNode);
        }
    else  // key >= root->key
        if(root->right == NULL){
            root->right = newNode;
        }
        else {
            root->right = insert(root->right, newNode);
        }
}
*/

void insertNodes(int numOfNodes) {
    for(int i = 0; i< numOfNodes; i++){
        struct Node *newNode = GetNewNodes();
        if(!root){
            root = newNode;
        }
        else {
            root = splay(root, newNode->priority);
            if(newNode->priority >= root->priority){
                newNode->left = root;
                newNode->right = root->right;
            }
            else {
                newNode->right = root;
                newNode->left = root->left;
            }
        }
        root = newNode;
        print_t(root);
    }
}





int main(){
    insertNodes(10);
}
