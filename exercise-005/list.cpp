#include "list.hpp"
#include <cstdlib>   // malloc, free
#include <cstddef>   // NULL / nullptr

// Hilfs-Konvention: 0 = Erfolg, -1 = Fehler

ListNode_t* NewListNode(void)
{
    ListNode_t* node = static_cast<ListNode_t*>(std::malloc(sizeof(ListNode_t)));
    if (!node) {
        return NULL;
    }
    node->data = 0;
    node->pNext = NULL;
    return node;
}

void FreeListNode(ListNode_t* elem)
{
    if (elem != NULL) {
        std::free(elem);
    }
}

List_t* NewList(void)
{
    List_t* list = static_cast<List_t*>(std::malloc(sizeof(List_t)));
    if (!list) {
        return NULL;
    }

    list->pHead = NULL;
    list->pTail = NULL;
    list->size  = 0;

    return list;
}

void FreeList(List_t* list)
{
    if (list == NULL) {
        return;
    }

    ListNode_t* current = list->pHead;
    while (current != NULL) {
        ListNode_t* next = current->pNext;
        FreeListNode(current);
        current = next;
    }

    std::free(list);
}

int InsertIntoLinkedList(List_t* list, ListNode_t* elem)
{
    if (list == NULL || elem == NULL) {
        return -1;
    }

    // Neues Element wird immer am Ende eingefügt, also next = NULL
    elem->pNext = NULL;

    if (list->pHead == NULL) {
        // Liste war leer
        list->pHead = elem;
        list->pTail = elem;
    } else {
        // Liste war nicht leer
        list->pTail->pNext = elem;
        list->pTail = elem;
    }

    list->size++;
    return 0;
}

int InsertIntoLinkedListAfterNode(List_t* list, ListNode_t* node, ListNode_t* elem)
{
    if (list == NULL || node == NULL || elem == NULL) {
        return -1;
    }

    // elem nach node einfügen
    elem->pNext = node->pNext;
    node->pNext = elem;

    if (list->pTail == node) {
        // Wenn node das letzte Element war, wird elem der neue Tail
        list->pTail = elem;
    }

    list->size++;
    return 0;
}

int RemoveFromList(List_t* list, ListNode_t* elem)
{
    if (list == NULL || elem == NULL) {
        return -1;
    }

    ListNode_t* prev = NULL;
    ListNode_t* current = list->pHead;

    // Vorgänger suchen
    while (current != NULL && current != elem) {
        prev = current;
        current = current->pNext;
    }

    if (current == NULL) {
        // Element nicht in der Liste gefunden
        return -1;
    }

    // current == elem
    if (prev == NULL) {
        // Element ist Head
        list->pHead = current->pNext;

        if (list->pTail == current) {
            // Es war das einzige Element
            list->pTail = NULL;
        }
    } else {
        // Element in der Mitte oder am Ende
        prev->pNext = current->pNext;

        if (list->pTail == current) {
            // Element war Tail
            list->pTail = prev;
        }
    }

    FreeListNode(current);
    list->size--;

    return 0;
}

ListNode_t* GetNext(const List_t* list, ListNode_t* elem)
{
    if (list == NULL) {
        return NULL;
    }

    if (elem == NULL) {
        // Start der Traversierung
        return list->pHead;
    }

    return elem->pNext;
}
