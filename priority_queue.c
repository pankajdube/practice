/* Priority_Queue: Imaplementation of Priority Queue using Heap
 * Author: Pankaj Dubey <dubepankaj1980@gmail.com>
 * Program Input Format: HEAP_TYPE ( 0 OR 1) SIZE DATA
 */

#include <stdio.h>
#include <malloc.h>
#include <time.h>

enum Heap_Type
{
	MAX_HEAP = 0,
	MIN_HEAP = 1,
};

struct Heap
{
	int *data;
	int count;
	int size;
	int heap_type;
};

struct Heap *CreateHeap(int size, int heap_type)
{
	int i;
	struct Heap *h = (struct Heap *) malloc(sizeof(struct Heap));
	if (!h) {
		printf("Out of memory\n");
		return NULL;
	}
	h->size = size;
	h->heap_type = heap_type;
	h->data = (int *) malloc(h->size * sizeof(int));
	if (!h->data) {
		printf("Out of memory\n");
		free(h);
		h = NULL;
		return h;
	}
	return h;
}
/*
 * Returns index of Parent element
 */
int Parent(struct Heap *h, int i)
{
	if (i <= 0 || i >= h->count)
		return -1;
	return (i-1)/2;
}

/*
 * Returns index of Left Child element
 */
int LeftChild(struct Heap *h, int i)
{
	int left = 2 * i + 1;
	if (left >= h->count)
		return -1;
	return left;
}

/*
 * Returns index of Right Child element
 */
int RightChild(struct Heap *h, int i)
{
	int right = 2 * i + 2;
	if (right >= h->count)
		return -1;
	return right;
}


/*
 * Returns Max element Value
 */
int GetMaximum(struct Heap *h)
{
	if (h->count == 0)
		return -1;
	return h->data[0];
}

void HeapifyTopDown(struct Heap *h, int i)
{
	int l, r, max, temp;

	l = LeftChild(h, i);
	r = RightChild(h, i);

	if (h->heap_type == MAX_HEAP) {
			if (l != -1 && h->data[l] > h->data[i])
					max = l;
			else
					max = i;

			if (r != -1 && h->data[r] > h->data[max])
					max = r;
	}
	else {
			if (l != -1 && h->data[l] < h->data[i])
					max = l;
			else
					max = i;

			if (r != -1 && h->data[r] < h->data[max])
					max = r;
	}

	if (max != i) {
		temp = h->data[i];
		h->data[i] = h->data[max];
		h->data[max] = temp;
		HeapifyTopDown(h, max);
	}
}

int DeleteMinMax(struct Heap *h)
{
	int data;
	if(h->count == 0)
		return -1;
	data = h->data[0];
	h->data[0] = h->data[h->count - 1];
	h->count--;
	HeapifyTopDown(h, 0);
	return data;		
}

void DestroyHeap(struct Heap *h)
{
	if(h == NULL)
		return;
	free(h->data);
	free(h);
	h = NULL;
}

int ResizeHeap(struct Heap *h)
{
	int i;
	int *old_data = h->data;
	h->data = (int *) malloc(sizeof(int) * h->size * 2);
	if (h->data == NULL) {
		printf("Memory Allocation Failed\n");
		return -1;
	}

	for (i = 0; i < h->size; i++)
		h->data[i] = old_data[i];

	h->size *= 2;
	free(old_data);
	return 0;
}

void Insert(struct Heap *h, int data)
{
	int i, ret = 0;
	if (h->count == h->size) {
		ret = ResizeHeap(h);
		if (ret != 0) {
			printf("Insert of %d Failed\n", data);
			return;
		}
	}

	h->count++;
	i = h->count - 1;
	if(h->heap_type == MAX_HEAP) {
			while (i >0 && data > h->data[(i-1)/2]) {
					h->data[i] = h->data[(i-1)/2];
					i = (i-1)/2;
			}
	}
	else {
			while (i >0 && data < h->data[(i-1)/2]) {
					h->data[i] = h->data[(i-1)/2];
					i = (i-1)/2;
			}
	}
	h->data[i] = data;
}

int main()
{
	struct Heap *h;
	int i, type, size;
	int data;
	clock_t start;
	double duration;


	scanf("%d%d", &type, &size);
	printf("type: %d size: %d\n", type, size);
	if (type != MAX_HEAP && type != MIN_HEAP) {
			printf("Enter valid heap type 0 OR 1\n");
			return 0;
	}

	start = clock();
	h = CreateHeap(size, type);
	if (h) {
			printf("Heap Created: %p\n", h);
			for (i = 0; i < h->size; i++) {
					scanf("%d", &h->data[i]);
					h->count++;
			}
			for (i = 0; i < h->size; i++)
					printf("%d ", h->data[i]);
			for (i = (size-1)/2; i >= 0; i--)
				HeapifyTopDown(h, i);
	}
	duration =(double)((clock() - start)/CLOCKS_PER_SEC);
	printf("\nSorted Order of Heap Elements are: ");
	data = DeleteMinMax(h);
	while (data >= 0) {
			printf("%d ",data);
			data = DeleteMinMax(h);
	}
	DestroyHeap(h);
	printf("\n");
	return 0;
}
