#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "buffer.cc"
#include "string.cc"
#include "vector.cc"


namespace cp {


inline void print(u32 value, const char* end = "") {
    printf("%u%s", value, end);
}
inline void print(u64 value, const char* end = "") {
    printf("%lu%s", value, end);
}
inline void print(i32 value, const char* end = "") {
    printf("%i%s", value, end);
}
inline void print(i64 value, const char* end = "") {
    printf("%li%s", value, end);
}
inline void print(f32 value, const char* end = "") {
    printf("%f%s", value, end);
}
inline void print(f64 value, const char* end = "") {
    printf("%lf%s", value, end);
}
inline void print(char value, const char* end = "") {
    printf("%c%s", value, end);
}
inline void print(bool value, const char* end = "") {
    printf("%i%s", value, end);
}
inline void print(const char* value, const char* end = "") {
    printf("%s%s", value, end);
}

template <typename T>
void print(vec2<T> v) {
    print(v.x); printf(" "); 
    print(v.y);
}

template <typename T>
void print(vec3<T> v) {
    print(v.x); printf(" "); 
    print(v.y); printf(" "); 
    print(v.z);
}

template <typename T>
void print(vec4<T> v) {
    print(v.x); printf(" "); 
    print(v.y); printf(" "); 
    print(v.z); printf(" "); 
    print(v.w);
}


template <typename t_c_arg, typename... t_rest_args>
void print(t_c_arg c_arg, t_rest_args... rest_args) {
    print(c_arg);
    printf(" ");
    print(rest_args...);
}

//template <typename... Args>
//void print(Args... args) {
    //print(args...);
//}



i64 file_size(FILE* file) {
    i64 init_pos = ftell(file);
    fseek(file, 0, SEEK_END);
    i64 size = ftell(file);
    fseek(file, init_pos, SEEK_SET);
    return size;
}

template <typename T>
void read_array(dbuff<T> buffer, FILE* file) {
    fread(buffer.buffer, sizeof(T), cap(&buffer), file);
}

bool read_whole(dstrb *out_str, const char* file_name) {

    FILE* file = fopen(file_name, "r");
    if (file == null) {
        return false;
    }

    i64 fsize = file_size(file);
    init(out_str, fsize);
    out_str->len = fsize;
    fread(beginp(out_str), sizeof(u8), cap(out_str), file);
    fclose(file);
    return true;
}

template <typename t_buff>
bool output_to_file(const char* file_name, t_buff buffer) {

    FILE* file = fopen(file_name, "w");
    if (file == null) {
        return false;
    }

    fwrite(beginp(&buffer), sizeof(typename t_buff::type), len(&buffer), file);
    fclose(file);
    return true;
}

} // namespace cp
