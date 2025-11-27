#include <iostream>
#include "list.hpp"
#include "vector.hpp"

int main()
{
    // =========================
    // 4.1 Liste testen
    // =========================
    std::cout << "=== Test: Linked List ===\n";

    List_t* list = NewList();
    if (list == NULL) {
        std::cerr << "Fehler: Konnte Liste nicht anlegen.\n";
        return 1;
    }

    // 5 neue Knoten erzeugen, Werte setzen, einfügen
    ListNode_t* n1 = NewListNode();
    ListNode_t* n2 = NewListNode();
    ListNode_t* n3 = NewListNode();
    ListNode_t* n4 = NewListNode();
    ListNode_t* n5 = NewListNode();

    if (!n1 || !n2 || !n3 || !n4 || !n5) {
        std::cerr << "Fehler: Konnte Knoten nicht anlegen.\n";
        return 1;
    }

    n1->data = 10;
    n2->data = 20;
    n3->data = 30;
    n4->data = 40;
    n5->data = 50;

    InsertIntoLinkedList(list, n1);
    InsertIntoLinkedList(list, n2);
    InsertIntoLinkedList(list, n3);
    InsertIntoLinkedList(list, n4);
    InsertIntoLinkedList(list, n5);

    // Einfügen nach dem zweiten Knoten (n2)
    ListNode_t* nAfter = NewListNode();
    if (!nAfter) {
        std::cerr << "Fehler: Konnte Zusatzknoten nicht anlegen.\n";
        return 1;
    }
    nAfter->data = 25;
    InsertIntoLinkedListAfterNode(list, n2, nAfter);

    // Ein bestimmtes Element entfernen, z.B. n4 (Wert 40)
    RemoveFromList(list, n4);
    // Achtung: n4 ist jetzt freigegeben, nicht mehr benutzen!

    // Traversieren mit GetNext und ausgeben
    std::cout << "Liste (data): ";
    for (ListNode_t* node = GetNext(list, NULL);
         node != NULL;
         node = GetNext(list, node))
    {
        std::cout << node->data << " ";
    }
    std::cout << "\nSize der Liste: " << list->size << "\n";

    // Liste freigeben
    FreeList(list);

    // =========================
    // 4.2 Vector testen
    // =========================
    std::cout << "\n=== Test: Mini-Vector ===\n";

    Vector_t vec;
    vector_init(&vec);

    // 5 Werte einfügen
    vector_push_back(&vec, 100);
    vector_push_back(&vec, 200);
    vector_push_back(&vec, 300);
    vector_push_back(&vec, 400);
    vector_push_back(&vec, 500);

    // Element an Index 2 ausgeben
    unsigned int value = 0;
    if (vector_get(&vec, 2, &value) == 0) {
        std::cout << "Element an Index 2: " << value << "\n";
    } else {
        std::cout << "Fehler beim Lesen von Index 2\n";
    }

    // Vector ausgeben
    vector_print(&vec);

    // Speicher aufräumen
    vector_clear(&vec);

    return 0;
}
