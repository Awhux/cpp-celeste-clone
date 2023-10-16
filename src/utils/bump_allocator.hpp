#pragma once
#ifndef _BUMP_ALLOCATOR_H
#define _BUMP_ALLOCATOR_H

#include <stdlib.h>
#include <string.h>

#include "logger.hpp"

namespace bump_allocator {
  /**
   * Struct to save the state of the bump allocator.
   */
  struct BumpAllocator {
    void* memory;     // pointer to the memory
    size_t used;      // in bytes
    size_t capacity;  // in bytes
  };

  /**
   * Create a bump allocator.
   *
   * @param size The size of the allocator in bytes.
   * @return The bump allocator.
   */
  BumpAllocator create_allocator(size_t size) {
    BumpAllocator allocator;
    allocator.memory   = malloc(size);
    allocator.used     = 0;
    allocator.capacity = size;

    // If we can manage to allocate the memory, log it.
    if(allocator.memory) {
      SM_TRACE("Successfully allocated {} bytes of memory for the bump allocator.", size);
    } else {
      SM_ERROR("Failed to allocate {} bytes of memory for the bump allocator.", size);
    }

    return allocator;
  }

  /**
   * Allocate memory from the bump allocator.
   *
   * @param allocator The allocator to allocate memory from.
   * @param size The size of the memory to allocate.
   * @return The pointer to the allocated memory.
   */
  void* allocate(BumpAllocator* allocator, size_t size) {
    // If we don't have enough memory, log it.
    if(allocator->used + size > allocator->capacity) {
      SM_ERROR("Failed to allocate {} bytes of memory from the bump allocator, not enough memory.", size);
      return nullptr;
    }

    // Allocate the memory.
    void* memory = (char*)allocator->memory + allocator->used;
    allocator->used += size;

    return memory;
  }
}  // namespace bump_allocator

#endif  // _BUMP_ALLOCATOR_H