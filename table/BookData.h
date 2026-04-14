#include <iostream>

class BookData{
  public:
    std::string author;
    std::string category;
    size_t pages;
    bool taken;
    BookData(std::string a="", std::string cat="", size_t p=0, bool t=false) : author(a), category(cat), pages(p), taken(t) {};
};
std::ostream& operator<<(std::ostream& o, const BookData &bd){
  o << "author: " << bd.author 
    << " category: " << bd.category 
    << " pages: " << bd.pages 
    << " taken: " << bd.taken << std::endl;
  return o;
}
