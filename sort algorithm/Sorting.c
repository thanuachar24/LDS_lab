#include <stdio.h>
#include <stdlib.h>

struct node{
	int data; // Node Data
	struct node *nextPtr; //Address  to the next node
};

struct node *firstNode; //address of the first node in the linked list

//Sorting algorithms
void bubblesort();
void mergesort();

//function prototypes (three functions we consider)
//create linked list with specified number of nodes
void createLinkedList(int numberOfNodes);

//sort the node of linker list
void sortLinkedList(int numberOfNodes);

//Display yhe number of nodes
void displayLinkedList();

int main()
{
    int choice;
    printf("Enter 1 for Bubble sort\nEnter 2 for Merge Sort\n\n");
    scanf("%d", &choice);

    if (choice == 1)
        bubblesort();
    else if (choice == 2)
        mergesort();
    else
        printf("Please enter valid choice");
    return 0;
}


/* ===== Bubble Sort ===== */

void bubblesort(){

    int numberOfNodes;

	//Initialixe first nodeof the linked list
	firstNode = NULL;

	printf("input the number of elements");
	scanf("%d",&numberOfNodes);
	//first step to create the linked list
	createLinkedList(numberOfNodes);
	//second step to sort the elements - bubble sort
	bubblesortLinkedList(numberOfNodes);
	// display
	printf("Sorted Order is:");
	displayLinkedList();
}

void createLinkedList(int numberOfNodes){
	struct node *newNode;
	struct node *currentNode;
	int nodeData;
	int nodeCtr;

	firstNode = (struct node*)malloc(sizeof(struct node));

	//Generate a node list if memory was sucessfully allocated
	if(firstNode == NULL){
		printf("Memory cannot be allocated");
	}
	else{
		printf("Input the elements in the linked list: \n");
		scanf("%d",&nodeData);

		//save input data to the node
		firstNode->data = nodeData;

		// initialize pointer to the next ndoe to NULL
		firstNode->nextPtr = NULL;

		//Copy the address of the first node
		currentNode = firstNode;

		//loop until the specified number of ndoes are geenrated
		for(nodeCtr=2;nodeCtr<=numberOfNodes;nodeCtr++){
			newNode = (struct node *) malloc(sizeof(struct node));
			//Exit fucntion if memoery allocation failed
			if(newNode ==NULL){
				printf("Mmeory cannot be allocated");
				break;
			}
			else{
				scanf("%d", &nodeData);
				//Save input data to the new node
				newNode->data = nodeData;
				//Initializae pointer to the next node to NULL
				newNode->nextPtr = NULL;

				//Append to the new node to th elast node of the list
				currentNode->nextPtr = newNode;
				//set the new node as the current node
				currentNode = currentNode->nextPtr;
			}

		}

	}
}

void bubblesortLinkedList(int numberOfNodes){
	int nodeCtr;
	int ctr;
	int nodeDataCopy;
	struct node *currentNode;
	struct node *nextNode;

	//loop until all the nodes are sorted in increasing order
	for(nodeCtr = numberOfNodes -2;nodeCtr >=0;nodeCtr--){
			//point to the first and second ndoe of the linked list
			currentNode = firstNode;
			nextNode = currentNode->nextPtr;

			//loop until the smallest value rise in the top

			for (ctr=0;ctr<=nodeCtr;ctr++){
				//switch the data if current node data is larger than next node data
				if(currentNode->data > nextNode->data)
				{
					nodeDataCopy = currentNode->data;
					currentNode->data=nextNode->data;
					nextNode->data = nodeDataCopy;

				}
				//Traverse to the next ndoes
				currentNode = nextNode;
				nextNode = nextNode->nextPtr;

			}

	}

}


void displayLinkedList(){
	struct node *currentNode;
	currentNode =firstNode;
	//loop until all the nodes are traversed
	while(currentNode != NULL){
		printf("%d\t",currentNode->data);
		//traverse to the enxt node
		currentNode = currentNode->nextPtr;
	}

}




/* ===== Merge Soring ===== */


/* function prototypes */
struct node* SortedMerge(struct node* a, struct node* b);
void FrontBackSplit(struct node* source,
					struct node** frontRef, struct node** backRef);

/* sorts the linked list by changing nextPtr pointers (not data) */
void MergeSort(struct node** headRef)
{
	struct node* head = *headRef;
	struct node* a;
	struct node* b;

	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->nextPtr == NULL)) {
		return;
	}

	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b);

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b);
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
struct node* SortedMerge(struct node* a, struct node* b)
{
	struct node* result = NULL;

	/* Base cases */
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	/* Pick either a or b, and recur */
	if (a->data <= b->data) {
		result = a;
		result->nextPtr = SortedMerge(a->nextPtr, b);
	}
	else {
		result = b;
		result->nextPtr = SortedMerge(a, b->nextPtr);
	}
	return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
	and return the two lists using the reference parameters.
	If the length is odd, the extra node should go in the front list.
	Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct node* source,
					struct node** frontRef, struct node** backRef)
{
	struct node* fast;
	struct node* slow;
	slow = source;
	fast = source->nextPtr;

	/* Advance 'fast' two nodes, and advance 'slow' one node */
	while (fast != NULL) {
		fast = fast->nextPtr;
		if (fast != NULL) {
			slow = slow->nextPtr;
			fast = fast->nextPtr;
		}
	}

	/* 'slow' is before the midpoint in the list, so split it in two
	at that point. */
	*frontRef = source;
	*backRef = slow->nextPtr;
	slow->nextPtr = NULL;
}

/* Function to print nodes in a given linked list */
void printList(struct node* node)
{
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->nextPtr;
	}
}

/* Function to insert a node at the beginning of the linked list */
void push(struct node** head_ref, int new_data)
{
	/* allocate node */
	struct node* new_node = (struct node*)malloc(sizeof(struct node));

	/* put in the data */
	new_node->data = new_data;

	/* link the old list off the new node */
	new_node->nextPtr = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

/* Driver program to test above functions*/
void mergesort()
{
	/* Start with the empty list */
	struct node* res = NULL;
	struct node* a = NULL;

	/* Let us create a unsorted linked lists to test the functions
Created lists shall be a: 2->3->20->5->10->15 */
    int n, value, i;
    printf("Enter the size of the list to be sorted\n");
    scanf("%d", &n);

    for(i = 0; i<n; i++){
    printf("Enter the element: ");
    scanf("%d", &value);.
    push(&a,value);
    }
	/*
	push(&a, 10);
	push(&a, 5);
	push(&a, 20);
	push(&a, 3);
	push(&a, 2);*/

	/* Sort the above created Linked List */
	MergeSort(&a);

	printf("Sorted Linked List is: \n");
	printList(a);

	getchar();
}
