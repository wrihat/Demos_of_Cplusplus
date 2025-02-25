#include "include/lruk.h"
#include <string>
#include <stdexcept>
int main() {
    LRU_Cache<int, std::string> cache(3, 2);
    cache.put(1, "A");
    cache.put(2, "B");
    cache.put(3, "C");
    std::cout<<"Get 1:"<<cache.get(1)<<std::endl;
    try{
        std::cout<<"Get 2:"<<cache.get(2)<<std::endl;
    } catch(std::exception& e){
        std::cout<<"Key 2 not found"<<std::endl;
    }
    std::cout<<"Get 3: "<<cache.get(3)<<std::endl;
    std::cout<<"Get 4: "<<cache.get(4)<<std::endl;

    return 0;
}