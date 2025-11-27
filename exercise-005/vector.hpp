#ifndef MINI_VECTOR_HPP__
#define MINI_VECTOR_HPP__

#include <cstddef>  // size_t

typedef struct Vector {
    unsigned int* data;
    size_t size;
    size_t capacity;
} Vector_t;

void vector_init(Vector_t* vec);
void vector_clear(Vector_t* vec);

int vector_push_back(Vector_t* vec, unsigned int value);
int vector_get(const Vector_t* vec, size_t index, unsigned int* outValue);
void vector_print(const Vector_t* vec);

#endif
