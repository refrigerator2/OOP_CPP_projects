#include <iostream>
#include <vector>



template<typename Key, typename Value>
class Map{
  private:
    struct Pair{ Key key; Value val; };
    std::vector<Pair> arr;
  public:
   void add(const Key &key, const Value &val){
    arr.push_back({key, val});
   }; 
   Value* find(const Key& k){
      for(unsigned long int i = 0; i < arr.size(); i++){
        if(arr[i].key == k) return &arr[i].val;
      }
      return nullptr;
   };
   friend std::ostream& operator<<(std::ostream& o, const Map& m){
     for(long unsigned int i = 0; i<m.arr.size(); i++){
       o << "Key: " << m.arr[i].key << std::endl << " value: " << m.arr[i].val;
     }
     return o;
   };
   Map(){};
   ~Map(){};
};
