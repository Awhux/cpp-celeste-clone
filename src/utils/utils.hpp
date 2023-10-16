#pragma once
#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

namespace utils {
  /**
   * Get the timestamp of a file.
   *
   * @param file The file to get the timestamp of.
   * @return The timestamp of the file.
   */
  long long get_timestamp(char* file) {
    struct stat st = {};

    if(stat(file, &st) == -1) { return -1; }

    return st.st_mtime;
  }

  /**
   * Check if a file exists.
   *
   * @param file_path The path to the file to check.
   * @return Whether or not the file exists.
   */
  bool file_exists(char* file_path) {
    if(FILE* file = fopen(file_path, "r")) {
      fclose(file);
      return true;
    } else {
      return false;
    }
  }

  /**
   * Get the size of a file.
   *
   * @param file_path The path to the file to get the size of.
   * @return The size of the file.
   */
  long get_file_size(char* file_path) {
    if(!file_exists(file_path)) { return -1; }

    FILE* file = fopen(file_path, "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    return size;
  }

  /**
   * Read a file.
   *
   * @param file_path The path to the file to read.
   * @return The contents of the file.
   */
  char* read_file(char* file_path) {
    if(!file_exists(file_path)) { return nullptr; }

    FILE* file = fopen(file_path, "r");
    long size  = get_file_size(file_path);
    char* data = (char*)malloc(size + 1);

    fread(data, size, 1, file);
    data[size] = '\0';

    fclose(file);

    return data;
  }

  /**
   * Write to a file.
   *
   * @param file_path The path to the file to write to.
   * @param data The data to write to the file.
   */
  void write_file(char* file_path, char* data) {
    FILE* file = fopen(file_path, "w");
    fwrite(data, strlen(data), 1, file);
    fclose(file);
  }

  /**
   * Copy a file.
   *
   * @param source The source file to copy.
   * @param destination The destination to copy the file to.
   */
  void copy_file(char* source, char* destination) {
    FILE* source_file      = fopen(source, "r");
    FILE* destination_file = fopen(destination, "w");

    char buffer[1024];
    size_t bytes;

    while((bytes = fread(buffer, 1, sizeof(buffer), source_file)) != 0) { fwrite(buffer, 1, bytes, destination_file); }

    fclose(source_file);
    fclose(destination_file);
  }
}  // namespace utils

#endif  // _UTILS_HPP