#include <shared_mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <chrono>
#include <string>
#include <mutex>

std::shared_mutex rw_mutex;
std::string shared_data;

void reader(int id) {
    while(true) {
        std::shared_lock lock(rw_mutex);  //读
        std::cout<<"Reader "<<id<<" reads: "<<shared_data<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void writer(const std::string& new_data) {
    while(true) {
        std::unique_lock lock(rw_mutex);
        shared_data = new_data;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::vector<std::thread> readers;
    for(int i = 0; i < 5; i++) {
        readers.emplace_back(reader, i);
    }

    std::thread writer_thread(writer, "Update Data");
    for(auto& t: readers) {
        t.join();
    }
    writer_thread.join();
    getchar();
    return 0;
}