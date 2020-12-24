#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#define PI 3.14159265358
using namespace std;
class City
{
public:
    string Country;
    string City;
    string AccentCity;
    string Region;
    long Population;
    double Latitude;
    double Longitude;
};

City parse(string line)
{
    City result;
    string c = line;
    stringstream ss(c);
    vector<string >word{};
    
    string token;
    while (getline(ss,token, ','))
    {
        word.push_back(token);
    }

    result.Country = word[0];
    result.City = word[1];
    result.AccentCity = word[2];
    result.Region = word[3];
    if(word[4]=="")
    {
        result.Population = 0;
    }
   
    result.Latitude = stod(word[5]);        //
    result.Longitude = stod(word[6]);       //
    
    return result;
}
double getDistance(City city1,City city2)
{
    double theta1,theta2,lambda1,lambda2;
    theta1 = city1.Latitude/180.0*PI;
    theta2 = city2.Latitude/180.0*PI;
    lambda1 = city1.Longitude/180.0*PI;
    lambda2 = city2.Longitude/180.0*PI;
    double delta_lambda = lambda2-lambda1;
    
    double a = pow(cos(theta2)*sin(delta_lambda), 2);
    double b = pow((cos(theta1)*sin(theta2))-(sin(theta1)*cos(theta2)*cos(delta_lambda)),2);
    double c = sin(theta1)*sin(theta2)+cos(theta1)*cos(theta2)*cos(delta_lambda);
    
    double delta_rho = atan(sqrt((a+b)/c));
    return 6371*delta_rho;
}
int main(int argc, const char * argv[]) {
    string cityname;
    string countryname;
    double distance;
    int isFound = 0;
    
    
    cout<<"\ninput city name : ";
    cin>>cityname;
    cout<<"\ninput country name(ex. th for Thailand) : ";
    cin>>countryname;
    cout<<"\ninput distance in km. : ";
    cin>>distance;
    
    
    ifstream ist("/worldcitiespop.txt"); //-------------------->>>>> INSERT FILE HERE
    
    string read;
    City city_A ;
    
    while (getline(ist,read)) {
       
        City c = parse(read);
        if (c.City == cityname && c.Country == countryname ) {
            isFound++;
            city_A = c;
            break;
        }
    }
    if (isFound == 0) {
        cout<<"CITY NOT FOUND !!!!!"<<endl;
        exit(1);
    }
    
    while (ist) {
        
        string s;
        getline(ist,s);
        City c = parse(s);
        if (c.Country > city_A.Country) {
            break;
        }
        double dist = getDistance(c, city_A);
        if (abs(dist)<distance) {
            cout<<c.Country<<" "<<c.City<<" "<<c.AccentCity<<" "<<c.Region<<" ("<<c.Latitude<<","<<c.Latitude<<")"<<endl;
        }
        
    }
    
    return 0;
}



