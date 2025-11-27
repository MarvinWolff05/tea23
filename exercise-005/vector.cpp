#include "vector.hpp"
#include <cstdlib>   // malloc, realloc, free
#include <iostream>

static const size_t VECTOR_INITIAL_CAPACITY = 4;

// Initialisiert den Vector
void vector_init(Vector_t* vec)
{
    if (vec == NULL) {
        return;
    }

    vec->size = 0;
    vec->capacity = VECTOR_INITIAL_CAPACITY;
    vec->data = static_cast<unsigned int*>(
        std::malloc(vec->capacity * sizeof(unsigned int))
    );

    if (vec->data == NULL) {
        // Allocation fehlgeschlagen
        vec->capacity = 0;
    }
}

// Gibt den Speicher wieder frei
void vector_clear(Vector_t* vec)
{
    if (vec == NULL) {
        return;
    }

    if (vec->data != NULL) {
        std::free(vec->data);
        vec->data = NULL;
    }

    vec->size = 0;
    vec->capacity = 0;
}

// Fügt ein Element am Ende ein, verdoppelt Kapazität falls nötig
int vector_push_back(Vector_t* vec, unsigned int value)
{
    if (vec == NULL) {
        return -1;
    }

    // Falls noch nicht initialisiert oder kaputt
    if (vec->data == NULL || vec->capacity == 0) {
        vector_init(vec);
        if (vec->data == NULL || vec->capacity == 0) {
            return -1;
        }
    }

    if (vec->size >= vec->capacity) {
        size_t newCapacity = vec->capacity * 2;
        unsigned int* newData = static_cast<unsigned int*>(
            std::realloc(vec->data, newCapacity * sizeof(unsigned int))
        );

        if (newData == NULL) {
            return -1; // Realloc fehlgeschlagen
        }

        vec->data = newData;
        vec->capacity = newCapacity;
    }

    vec->data[vec->size] = value;
    vec->size++;

    return 0;
}

// Liest ein Element an Index index
int vector_get(const Vector_t* vec, size_t index, unsigned int* outValue)
{
    if (vec == NULL || outValue == NULL) {
        return -1;
    }

    if (index >= vec->size) {
        // Index außerhalb des Bereichs
        return -1;
    }

    *outValue = vec->data[index];
    return 0;
}

// Gibt den Inhalt des Vectors aus
void vector_print(const Vector_t* vec)
{
    if (vec == NULL) {
        return;
    }

    std::cout << "Vector(size=" << vec->size
              << ", capacity=" << vec->capacity << "): [";

    for (size_t i = 0; i < vec->size; ++i) {
        std::cout << vec->data[i];
        if (i + 1 < vec->size) {
            std::cout << ", ";
        }
    }

    std::cout << "]\n";
}
