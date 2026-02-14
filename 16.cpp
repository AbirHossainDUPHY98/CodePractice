//Use structured bindings ('auto[x,y]= ....') to unpack a 'std::pair' returned from a function.

#include<iostream>
#include<string>
#include<utility>
std::pair<std::string, double> weather_data(){
  return {"Dhaka", 21.4};
} 
//When you use structured bindings, must use the keyword auto.
int main(){
  auto [city, temp] = weather_data();
  std::cout<< "Location: "<< city <<"\n";
  std::cout<< "Temperature: "<< temp <<" degC\n";
  return 0;
}

/*Data Count , Types , Best Tool
Exactly 2 , Can be different , std::pair
3 to 5 , Can be different , std::tuple
Complex/Many , Can be different , struct (Cleaner names)
Hundreds , Must be same , std::vector*/
