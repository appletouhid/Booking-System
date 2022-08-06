#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int boatCount = 0, marinaSize = 150, maxBoatLength = 15;
int totalBoatLength = 0, availableRoom = 0;

class Boat
{
	public:
	    string OwnerName, BoatName;
        int BoatLength;

		void setOwnerName( string boatOwnerName)
		{
			OwnerName = boatOwnerName;
		}

		void setBoatName( string boatName)
		{
			BoatName = boatName;
		}

		void setBoatLength(int boatLength)
		{
			BoatLength = boatLength;
		}
};

class BoatType : public Boat
{
public :
    string BoatType;

    void setBoatType(string boatType)
		{
			BoatType = boatType;
		}

	void displayInfo()
		{
		    totalBoatLength = totalBoatLength + this->BoatLength;
            availableRoom = marinaSize - totalBoatLength;

			cout << "Owner Name : " << this->OwnerName << endl;
			cout << "Boat Name : " << this->BoatName << endl;
			cout << "Boat Type : " << this->BoatType << endl;
			cout << "Boat Length (m) : " << this->BoatLength << endl;
		}
};

BoatType st[100];
BoatType st2[100];

void addBoat()
{
	string name;
	int boatLength, month, agreement;

	cout << "\n###### Add Boat ######\n" << endl;

	cout << "Enter Boat Length (m) : ";
	cin >> boatLength;
	if(boatLength <= maxBoatLength)
    {
        st[boatCount].setBoatLength(boatLength);

        cout << "How many months you want to book? 10 pounds/month" << endl;
        cin >> month;
        cout << "You need to pay "<< month*10 << " pounds for " << month << " month" << endl;
        cout << "If agree press 1 : ";
        cin >> agreement;

        if(agreement == 1)
        {
            cout << "\nEnter Owner name : ";
            cin >> name;
            st[boatCount].setOwnerName(name);

            cout << "Enter Boat name : ";
            cin >> name;
            st[boatCount].setBoatName(name);

            cout << "Enter Boat Type : ";
            cin >> name;
            st[boatCount].setBoatType(name);

            boatCount++;
        }
        else
        {
            cout << "Tarima Kashi, Jumpa Lagi" << endl;
        }
    }
    else
    {
        cout << "Sorry Your Boat is too Large" << endl;
    }
}

void storeBoat()
{
    ifstream infile;
	ofstream outfile;
    outfile.open ("Input.txt");

    for( int i=0; i<boatCount; i++ )
	{
        outfile << st[i].OwnerName;
        outfile << '\t';
        outfile << st[i].BoatName;
        outfile << '\t';
        outfile << st[i].BoatType;
        outfile << '\t';
        outfile << st[i].BoatLength;
        outfile << '\n';
	}

	outfile.close();

	cout << "Boat Added Successfully" << endl;
}

void displayBoat()
{
    for( int i=0; i<boatCount; i++ )
	{
		cout << "\nBoat " << i + 1 << endl;
		st[i].displayInfo();
	}

	cout << "\nAvailable Room (m) : " << availableRoom <<"\n" << endl;
}

void readFromFile()
{
      BoatType objBType;
      totalBoatLength = 0, availableRoom = 0;

      ifstream myfile ("Input.txt");
      if (!myfile)
      {
        perror ("File error: ");
      }

      int i = 0;

      while (myfile >> objBType.OwnerName >> objBType.BoatName >> objBType.BoatType >> objBType.BoatLength && i++ != EOF)
      {
        // use the input
        //cout << objBType.OwnerName << '\t' << objBType.BoatName << '\t' << objBType.BoatType << '\t' << objBType.BoatLength << '\n';

        st2[i-1].setOwnerName(objBType.OwnerName);
        st2[i-1].setBoatName(objBType.BoatName);
        st2[i-1].setBoatType(objBType.BoatType);
        st2[i-1].setBoatLength(objBType.BoatLength);

        st[i-1] = st2[i-1];

        boatCount = i;
      }

      displayBoat();
}

void deleteBoat()
{
    int boatNo;
    int choice;

    readFromFile();

    cout << "Which Boat You Want to Delete : ";
    cin >> boatNo;

    cout << "Are you sure (1/0) : ";
    cin >> choice;

    if(choice == 1)
    {
        st2[boatNo-1].setOwnerName("");
        st2[boatNo-1].setBoatName("");
        st2[boatNo-1].setBoatType("");
        st2[boatNo-1].setBoatLength(0);
    }

    ofstream outfile;
    outfile.open ("Input.txt");

    for( int i=0; i<boatCount; i++ )
	{
        outfile << st2[i].OwnerName;
        outfile << '\t';
        outfile << st2[i].BoatName;
        outfile << '\t';
        outfile << st2[i].BoatType;
        outfile << '\t';
        outfile << st2[i].BoatLength;
        outfile << '\n';
	}

	outfile.close();

	cout << "Boat Deleted Successfully" << endl;
}

int main()
{
	int n;

    while(n != 5)
    {
        cout << "******** Main Menu ********" << endl;
        cout << " 1. Add Boat" << endl;
        cout << " 2. Save to File" << endl;
        cout << " 3. Delete Boat" << endl;
        cout << " 4. Display Boat" << endl;
        cout << " 5. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> n;

        if(n == 1)
        {
            readFromFile();
            addBoat();
        }
        else if(n == 2)
            storeBoat();
        else if(n == 3)
            deleteBoat();
        else if(n == 4)
            readFromFile();
    }

	return 0;
}
