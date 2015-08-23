/*
 * This program helps in computing following operations on an AVL tree
 * 0 - Serach (x) - Search given element 'x' in AVL tree, if present return TRUE else FALSE
 * 1 - Insert (x) - Insert an element 'x' in AVL tree.
 * 2 - Delete (x) - Delete an element 'x' from AVL tree if it's already present in tree else NOP
 * 3 - Rank (x) - Find Rank of an element 'x' of given AVL tree.
 * 4 - Select (k) - Find element having Rank 'k' from given AVL tree.
 * Author: Pankaj Dubey <pankaj.dubey@samsung.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Disable the debugging prints by default */
#define DEBUG 0 
/* Macro for printing debug prints */
#define debug_print(...) \
            do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

// An AVL tree node
struct node
{
    long long int key;
    struct node *left;
    struct node *right;
	struct node *parent;
    int height;
	int size;
};

// A utility function to print preorder traversal of the tree.
void preOrder(struct node *root)
{
    if(root != NULL)
    {
        debug_print("%llu ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }

}
 
// A utility function to print inorder traversal of the tree.
void inOrder(struct node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        debug_print("%llu %d %d\n", root->key, root->height, root->size);
        inOrder(root->right);
    }

}
 
// A utility function to get height of the tree
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int size(struct node *N)
{
	if (N == NULL)
		return 0;
	return N->size;
} 
// A utility function to get maximum of two integers
long long int max(long long int a, long long int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
 *    NULL left and right pointers.
 */
struct node* newNode(long long int key)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
	node->parent = NULL;
    node->height = 1;  // new node is initially added at leaf
	node->size 	= 1; //new node has size 1
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
    // Perform rotation
    x->right = y;
	x->parent = y->parent;
	y->parent = x;
    y->left = T2;
	if (T2 != NULL)
		T2->parent = y;
 
    // Update height and size
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
	y->size = size(y->left) + size(y->right) + 1;
	x->size = size(x->left) + size(x->right) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
	y->parent = x->parent;
	x->parent = y;
    x->right = T2;
	if (T2 != NULL)
		T2->parent = x;
 
    //  Update height and size
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
	x->size = size(x->left) + size(x->right) + 1;
	y->size = size(y->left) + size(y->right) + 1;
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
struct node* Insert(struct node* node, long long int key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));
    if (key < node->key) {
		node->size++;
        node->left  = Insert(node->left, key);
		if (node->left->parent == NULL) {
			node->left->parent = node;
		}
    }
	else {
		node->size++;
        node->right = Insert(node->right, key);
		if (node->right->parent == NULL) {
			node->right->parent = node;
		}
 	}
    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;
 
    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key) 
        return rightRotate(node);
	
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
	
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
	
    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary Search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be Searched. */
struct node * minValueNode(struct node* node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
struct node* Delete(struct node* root, long long int key)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
    // If the key to be Deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( key < root->key )
        root->left = Delete(root->left, key);
 
    // If the key to be Deleted is greater than the root's key,
    // then it lies in right subtree
    else if( key > root->key )
        root->right = Delete(root->right, key);
 
    // if key is same as root's key, then This is the node
    // to be Deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left : root->right;
 
            // No child case
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            {
				temp->parent = root->parent;
				 *root = *temp; // Copy the contents of the non-empty child
			}
 		
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            struct node* temp = minValueNode(root->right);
 
            // Copy the inorder successor's data to this node
            root->key = temp->key;
 
            // Delete the inorder successor
            root->right = Delete(root->right, temp->key);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = max(height(root->left), height(root->right)) + 1;
    root->size = size(root->left) + size(root->right) + 1;
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    //  this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}
 
struct node* Search(struct node* root, struct node* nearest_node, long long int key)
{
	struct node* found_node = NULL;
	if (root == NULL) 
			return nearest_node;
	else
			found_node = root;

	if (root->key == key)
		found_node = root;
	if (key < root->key && root->left)
		found_node = Search(root->left, root, key);
	if (key > root->key && root->right) 
		found_node = Search(root->right, root, key);
	

	return found_node;
}

int Rank(struct node *root, long long int key)
{
	struct node *x = NULL;
	struct node *y = NULL;
	int rank;
	x = Search(root, root, key);
	
	if (x == NULL)
		return -1;

	if (key > x->key)
			rank = size(x) + 1;
	else
			rank = size(x->left) + 1;
	y = x;
	
	while (y != root)
	{
		if (y == y->parent->right)
			rank = 	rank + size(y->parent->left) + 1;
		y = y->parent;
	}
	return rank;	
}

long long int Select(struct node *root, int rank)
{
	int r;

	if (root == NULL)
		return -0xFFFF;

	r = size(root->left) + 1;
	
	if (r == rank)
		return root->key;
	else if (rank < r)
		return Select(root->left, rank);
	else
		return Select(root->right, rank - r);	
}

/*
 * main: Entry point for the program.
 */
int main()
{
	int i, rank;
	struct node *avl_root = NULL;
	struct node *found_node = NULL;
	int total_nodes, operation;
	long long int node_val;
	double duration;
	clock_t start;

	scanf("%d\n", &total_nodes);
	printf("total_nodes: %d\n",total_nodes);
	printf("=============================================================================\n");
	printf("Operation\t\tOperand\t\t\tResult\t\tTime_Taken(sec)\n");
	printf("=============================================================================\n");
	for (i = 0; i < total_nodes; i++) {
		found_node = NULL;
		scanf("%d", &operation);
		scanf("%llu\n", &node_val);
		switch(operation)
		{
			case 0:
				start = clock();
				found_node = Search(avl_root, avl_root, node_val);
				duration = (double) ((clock() - start))/CLOCKS_PER_SEC;
				printf("Search\t\tNode=%-10llu\t\t%-20s\t%f\n", node_val,(found_node != NULL) ? ((found_node->key == node_val ? "PRESENT" : "NOT PRESENT")): "NOT PRESENT", duration);
				break;
			case 1:
				start = clock();
				avl_root = Insert(avl_root, node_val);
				duration = (double) ((clock() - start))/CLOCKS_PER_SEC;
				printf("Insert\t\tNode=%-10llu\t%10s\t\t\t%f\n", node_val, (avl_root != NULL ? "OK" : "NOT_OK"), duration);
				break;
			case 2:
				start = clock();
				avl_root = Delete(avl_root, node_val);
				duration = (double) ((clock() - start))/CLOCKS_PER_SEC;
				printf("Delete\t\tNode=%-10llu\t%10s\t\t\t%f\n", node_val, (avl_root != NULL ? "OK" : "NOT_OK"), duration);
				break;
			case 3:
				start = clock();
			 	rank = Rank(avl_root, node_val);
				duration = (double) ((clock() - start))/CLOCKS_PER_SEC;
				printf("Rank\t\tnode=%-10llu\t\trank=%-10d\t\t%f\n", node_val, rank, duration);
				break;
			case 4:
				start = clock();
				rank = node_val;
			 	node_val = Select(avl_root, rank);
				duration = (double) ((clock() - start))/CLOCKS_PER_SEC;
				if (node_val == -0xFFFF)
						printf("Error!!! in Selecting node having rank=%-10d\n", rank);
				else
						printf("Select\t\trank=%-10d\t\tnode=%-10llu\t\t%f\n", rank, node_val, duration);
				break;
			case 5:
				inOrder(avl_root);
				printf("\n");
				break;
			default:
				debug_print("ERROR!!! Invalid Operation\n");
				return -1;
		}
	}
	return 0;
}
