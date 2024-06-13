#include< iostream>
using namespace std;
/*
Parking Lot:
Vehicle
spots: spot of different types, bool parked 
ParkingFloor
ParkingStatergy : 
user : name, vehicle, parkingspot
ticket: user, vehicle, spot, time
ParkingFloorManagement :  Crud to Parking Floor by adding spot
ParkingLot : multiple ParkingFloor
ParkingLotManagement : Crud to ParkingLot by adding ParkingFloor
ParkingLotSystem : list<parkingLotManagement> ,parkingStatergy , findspot(), parkVehicle(), unparkVehicle(), list<vehicle,spot>,list<user>
step 1: rough flow
-> vechile->parkingLotSystem->findspot()->parkVehicle()->unparkVehicle()



entrancegate(find spot, update spot, generateticket)
exitgate(costcalculation, payment,update spot)
ticket(parkingspot,time)
vehichle: number,type(enum)
parkingspot : different types of spot: two wheeler, four wheeler, heavy vehicle(id,vehicle,occupied,spottype,price)
payment: hourly, minutely


*/
int main()
{
    cout<<"working";
    return 0;
}
