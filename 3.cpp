/*write a program that demonstrates the difference between `const`, `constexpr`, and `#define` for defining constants*/

#include <iostream>
#include <array>
#include <typeinfo>
#define MacroValue 100
const int ConstValue = 100;
constexpr int ConstExprValue = 100;
//#define Max(a,b) ((a) > (b) ? (a) : (b))
    //int runtime() {
    //    return 100;
    //}
    //const int z=runtime();

    //void scope_test(){
      //#define Ghost 5
      //const int R = 5;
    //}
    
int main() {
  //checking compilation itme vs runtime issue

    //Array size must be compile time constant
    //so Macro is compile time
    //std::array<int, MacroValue> arr0;
    //std::cout <<"macro array size: " << arr0.size(); 
    
    //const can be compile time or runtime depending on initiation
    //std::array<int, ConstValue> arr1;
    //std::cout <<"const array size: "<< arr1.size();

    //std::array<int, ConstExprValue> arr2;  
    //std::cout << "constexpr array size: " << arr2.size();
    
    
    //std::array<int, z> arr3;
    //std::cout<<"runtime const array size: "<< arr3.size();
    //shows error while saving- cause limitaions are- function is run at runtime, the returned value cannot be array size,compiler doesn't recognize it , it must be compile time.

  //Type safety:compiler makes sure that types are not mixed up.
      //std::cout<< typeid(ConstValue).name();
  
  //scope and debugging
  //#define:(no scope)-> macros don't respect curly braces
  //const and constexpr: (block scope)-> if defined inside a function, they stay there and don't cause naming collisions.
  //while debugging the debugger will tell there is an error with the number set to macro and not the macro itself
  //const/constexpr: these are strored in the symbol table. a breakpoint can be put in the debugger, hovering over the name of the const/constexpr will show the name and value
  //std::cout<< R;-> compiler doesn't recognize R
  //std::cout<< Ghost;-> leaks out of the scope_test function and shows 5
  
  //Macro pitfalls
    //int x = 5;
    //int y = 10;
    //int result = Max(x, ++y);//expected y to be 11
    //std::cout<<y;
    //but shows 12 when checked, because- in the definition formula- y++ appeared twice. now thats just bullshit.
    
  //memory
  //a macro occupies 0bytes and only lives in the sourcecode.and the downside is->if a large string macro is used 1000s of times, the string is copied into machine code that number of times which will make the program file size larger.
  //Macros cannot be addressed.But const and constexpr can be  
    //std::cout<<&ConstValue<<"\n";
    //std::cout<<&ConstExprValue;
  //pointer test
    const int* pointer = &ConstValue;//forcing compiler to give ConstValue a memory address
    //std::cout<<*pointer;//telling -> go to the address held by the pointer and show what is inside.So outputs the value not the address.
    std::cout<< pointer;//this one shows an address.


return 0;}
