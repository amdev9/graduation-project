#include <list>
#include <map>
#include <fstream>
#include <string>
  



using namespace std;


class TestFitness {
   private:

    static TestFitness _tf;
    map<int, int > _days;
    map<int, int > _timess;
    map<int, int > _rms;
 map<int, int > _dur;
 map<int, char* > _groupsmap;


 list<CourseClass*> _courseClassesTest;

  public:
    // Returns reference to global instance
     inline static TestFitness& GetInstance() { return _tf; }

    TestFitness() {}
    void TestCalculateFitness();
    ~TestFitness();

    inline const list<CourseClass*>& GetCourseClassesTest() const { return _courseClassesTest; }

    inline int getRms(int id) const { 
     auto it = _rms.find( id );
      if (it != _rms.end()) {
       return  ( *it ).second;
     }
    }
    inline int getDays(int id) const {
      auto it = _days.find( id );
      
     if (it != _days.end()) {
      return ( *it ).second;
    } 
    }
    inline int getTimess(int id) const  {
      auto it = _timess.find( id );
      if (it != _timess.end()) {
      return ( *it ).second;
    } 
  }

  inline int getDur(int id) const  {
      auto it = _dur.find( id );
      if (it != _dur.end()) {
      return ( *it ).second;
    } 
  }
};
