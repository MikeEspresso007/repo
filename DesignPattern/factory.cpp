#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;
 
enum VehicleType 
{
    VT_TwoWheeler,    VT_ThreeWheeler,    VT_FourWheeler
};
 
// Library classes
class Vehicle 
{
	public:
		
		virtual void printVehicle() = 0;
		
		// Add this method, so this method can be passed to client constructor
		static Vehicle* Create(VehicleType type); 
};

class TwoWheeler : public Vehicle 
{
	public:
		void printVehicle() 
		{
			cout << "I am two wheeler" << endl;
		}
};

class ThreeWheeler : public Vehicle 
{
	public:
		void printVehicle() 
		{
			cout << "I am three wheeler" << endl;
		}
};

class FourWheeler : public Vehicle 
{
    public:
    void printVehicle() 
	{
        cout << "I am four wheeler" << endl;
    }
};
 
// object instantiation is done outside of client constructor.
// it is bind through pointer with different type
Vehicle* Vehicle::Create(VehicleType type) 
{
    if (type == VT_TwoWheeler)
        return new TwoWheeler();
    else if (type == VT_ThreeWheeler)
        return new ThreeWheeler();
    else if (type == VT_FourWheeler)
        return new FourWheeler();
    else return NULL;
}
 
// Client class
class Client 
{
	public: 
		// Client doesn't explicitly create objects
		// but passes type to factory method "Create()"
		Client()
		{
			VehicleType type = VT_ThreeWheeler;
			pVehicle = Vehicle::Create(type);
		}
		
		~Client() 
		{
			if (pVehicle) {
				delete[] pVehicle;
				pVehicle = NULL;
			}
		}
		
		Vehicle* getVehicle()  
		{
			return pVehicle;
		}
	 
	private:
		Vehicle *pVehicle;
};
 
// Driver program
int main() 
{
    Client *pClient = new Client();
    Vehicle * pVehicle = pClient->getVehicle();
    pVehicle->printVehicle();
    return 0;
}
























/*
// Assume below are libraries,
//=========================================================================
class Vehicle 
{
	public:
		virtual void printVehicle() = 0;
};

class TwoWheeler : public Vehicle 
{
	public:
		void printVehicle()  
		{
			cout << "I am two wheeler" << endl;
		}
};

class FourWheeler : public Vehicle 
{
    public:
		void printVehicle()  
		{
			cout << "I am four wheeler" << endl;
		}
};
//=========================================================================








 
class Client 
{
	public:
		//if there is new library, say ThreeWheeler, then it will affect client , and will need it to be recompiled.
		Client(int type)  
		{
			if (type == 1)
				pVehicle = new TwoWheeler();
			else if (type == 2)
				pVehicle = new FourWheeler();
			else
				pVehicle = NULL;
		}
	 
		~Client()   
		{
			if (pVehicle)
			{
				delete[] pVehicle;
				pVehicle = NULL;
			}
		}
	 
		Vehicle* getVehicle() 
		{
			return pVehicle;
		}

	private:
		Vehicle *pVehicle;
};
 



// Driver program
int main() 
{
    Client *pClient = new Client(2);
    Vehicle * pVehicle = pClient->getVehicle();
    pVehicle->printVehicle();
    return 0;
}
*/