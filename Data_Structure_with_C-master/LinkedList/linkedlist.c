#include <stdio.h>
#define true 1;
#define false 0;
typedef int LData;

//��� ����ü
typedef struct _node {
	LData data;
	struct _node *next;
}Node;

typedef struct _linkedList {
	Node * head;
	Node * cur;
	Node * before;
	int numOfData;
	int(*comp)(LData d1, LData d2); //�Լ� ������
}LinkdedList;

typedef LinkdedList List;

void ListInit(List * plist);
void LInsert(List * plist, LData data);

int LFirst(List *plist, LData *pdata);
int LNext(List *plist, LData *pdata);

void FInsert(List *plist, LData data);
void SInsert(List *plist, LData data);

LData LRemove(List *plist);
int LCount(List *plist);

void SetSortRule(List *plist, int(*comp)(LData d1, LData d2));

int WhoIsPrecede(int d1, int d2) {
	if (d1 < d2)
		return 0;
	else
		return 1;
}

int main() {

	List list;
	int data;
	ListInit(&list);

	SetSortRule(&list, WhoIsPrecede);

	LInsert(&list, 11); LInsert(&list, 11);
	LInsert(&list, 55); LInsert(&list, 22);
	LInsert(&list, 33);

	printf("A number of data now: %d\n", LCount(&list));

	if (LFirst(&list, &data)) {
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");

	if (LFirst(&list, &data)) {
		if (data == 22)
			LRemove(&list);

		while (LNext(&list, &data)) {
			if (data == 22)
				LRemove(&list);
		}
	}
	printf("A number of data now: %d\n", LCount(&list));

	if (LFirst(&list, &data)) {
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);
	}
	system("PAUSE");
	return 0;
}

void ListInit(List * plist) {
	plist->head = (Node *)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}

void LInsert(List * plist, LData data) {
	if (plist->comp == NULL)
		FInsert(plist, data);
	else
		SInsert(plist, data);
}
void FInsert(List *plist, LData data) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head->next;
	plist->head->next = newNode;

	(plist->numOfData)++;
}
void SInsert(List *plist, LData data) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	Node *pred = plist->head; //���� ��带 ����Ŵ
	newNode->data = data;

	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0) {
		pred = pred->next;
	}
	newNode->next = pred->next;
	pred->next = newNode;

	(plist->numOfData)++;
}
int LFirst(List *plist, LData *pdata) {
	if (plist->head->next == NULL)
		return false;

	plist->before = plist->head; //���� ��带 ����Ű�� ����
	plist->cur = plist->head->next; //���� ��带 ����Ű�� ����

	*pdata = plist->cur->data; //������ ��ȯ
	return true;
}

int LNext(List *plist, LData *pdata) {
	if (plist->cur->next == NULL)
		return false;
	plist->before = plist->cur; //���� ���
	plist->cur = plist->cur->next; //�� ���� ���

	*pdata = plist->cur->data;
	return true;
}
LData LRemove(List *plist) {
	Node *rpos = plist->cur;
	LData rdata = rpos->data;

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}
int LCount(List *plist) {
	return plist->numOfData;
}

void SetSortRule(List *plist, int(*comp)(LData d1, LData d2)) { //comp�� �ʱ�ȭ �ϴ� �Լ�
	plist->comp = comp;
}