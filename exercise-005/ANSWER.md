# ANSWER – Vergleich Liste vs. Mini-Vector

## Vorteile der verketteten Liste

- Einfügen und Löschen in der Mitte der Liste ist (mit bekanntem Knoten) O(1), kein Verschieben von Elementen nötig.
- Größe ist vollständig dynamisch, kein fester Speicherblock notwendig.
- Kein Realloc nötig, daher bleiben Zeiger auf Knoten (solange sie nicht gelöscht werden) stabil.

## Nachteile der verketteten Liste

- Kein direkter Zugriff per Index – man muss immer von vorn (oder einem bekannten Knoten) traversieren.
- Schlechte Cache-Lokalität, da die Knoten oft verteilt im Speicher liegen → langsamer bei vielen Zugriffen.
- Speicher-Overhead pro Element (zusätzlicher Zeiger `pNext`).
- Viele kleine Heap-Allocations (NewListNode), was langsam sein kann.

## Vorteile des Mini-Vectors

- Direkter Zugriff per Index in O(1).
- Gute Cache-Lokalität, da alle Daten in einem zusammenhängenden Speicherblock liegen.
- Weniger Speicher-Overhead pro Element (nur das nackte `unsigned int`).
- Sehr praktisch für Iteration und Verwendung mit Algorithmen (z. B. Sortieren).

## Nachteile des Mini-Vectors

- Einfügen/Löschen in der Mitte erfordert Verschieben von vielen Elementen → O(n).
- Wenn die Kapazität erschöpft ist, muss neu allokiert und kopiert werden (Realloc) → temporärer Overhead.
- Realloc kann Zeiger/Referenzen auf Elemente ungültig machen.

## Wann benutzt man welche Struktur?

- **Verkettete Liste**:
  - Viele Einfügungen/Löschungen an beliebiger Stelle.
  - Kein häufiger zufälliger Zugriff per Index nötig.
  - Wenn stabile Knoten-Adressen wichtig sind (solange man nicht löscht).

- **Mini-Vector (dynamisches Array)**:
  - Viele Lesezugriffe, vor allem sequentiell oder per Index.
  - Viele Push-Back-Operationen am Ende.
  - Datenanalyse, numerische Berechnungen, allgemein „Standardfall“.

In der Praxis verwendet man sehr oft einen Vector; Listen lohnen sich nur in speziellen Szenarien.

## Was passiert, wenn man die Elemente sortiert?

### Beim Mini-Vector

- Man kann einfach eine Sortierfunktion wie `std::sort` verwenden (da zufälliger Zugriff möglich ist).
- Sortieren arbeitet effizient mit dem zusammenhängenden Speicher, ist meistens sehr schnell.
- Komplexität typischerweise O(n log n).

### Bei der Liste

- `std::sort` kann man nicht direkt verwenden, da es Random-Access-Iteratoren erwartet.
- Entweder:
  - eigenen Sortieralgorithmus für Listen implementieren (typisch: Mergesort auf einer verketteten Liste), oder
  - alle Elemente zuerst in ein Array/Vector kopieren, dort sortieren, und wieder zurückschreiben.
- Pointer-Chasing macht das Sortieren in einer Liste oft langsamer als bei einem Vector, obwohl die theoretische Komplexität auch O(n log n) ist.

## Wie würden Sie einen Binären Baum strukturieren?

Ein einfacher binärer Suchbaum könnte so aussehen:

```cpp
typedef struct TreeNode {
    unsigned int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode_t;

typedef struct Tree {
    TreeNode_t* root;
    unsigned int size;
} Tree_t;
