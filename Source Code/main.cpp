#include "BookStore.h"

int main(int argc, char *argv[])
{
	commandList();

	while (1)
	{
		int cmdNum;
		int num;
		string name, d1, d2;

		cout << "Choose command number: ";
		cin >> cmdNum;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
		}

		cout << endl;

		switch (cmdNum)
		{
		case 0:
			commandList();
			break;
		case 1:
			printBooks();
			break;
		case 2:
			printOrders();
			break;
		case 3:
			printCustomers();
			break;
		case 4:
			printSuppliers();
			break;
		case 5:
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d1;
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d2;
			transactions(d1, d2);
			break;
		case 6:
			printDiscounts();
			break;
		case 7:
			cout << "Enter book name: ";
			cin.ignore();
			getline(cin, name);
			if (isInStock(name))
				cout << endl << "Yes, the book is in stock.";
			else
				cout << endl << "No, the book isn't in stock.";
			break;
		case 8:
			cout << "Enter book name: ";
			cin.ignore();
			getline(cin, name);
			printBookSuppliers(name);
			break;
		case 9:
			cout << "Enter book name: ";
			cin.ignore();
			getline(cin, name);
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d1;
			cout << "Amount of '" << name << "' sold since " << d1 << ": " << booksBought(name, d1) << endl;
			break;
		case 10:
			cout << "Enter customer number: ";
			cin >> num;
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d1;
			cout << "Amount of books acquired by customer #" << num << " since " << d1 << ": " << CustomerBooks(num, d1) << endl;
			break;
		case 11:
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d1;
			CustomerWithMostBoughtBooks(d1);
			break;
		case 12:
			SupplierWithMostOrders();
			break;
		case 13:
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d1;
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d2;
			printOrderBookAmount(d1, d2);
			break;
		case 14:
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d1;
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d2;
			printOrderSold(d1, d2);
			break;
		case 15:
			cout << "Enter customer number: ";
			cin >> num;
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d1;
			cout << "Total discount that customer received: " << customerDiscounts(num, d1) << endl;
			break;
		case 16:
			cout << "Enter year in format yyyy: ";
			cin >> d1;
			printYearRevenue(d1);
			break;
		case 17:
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d1;
			cout << "New customers since " << d1 << ": " << newCustomers(d1) << endl;
			break;
		case 18:
			cout << "Enter supplier id: ";
			cin >> num;
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d1;
			cout << "Enter start date in format yyyy-mm-dd: ";
			cin >> d2;
			cout << "Price of orders from supplier: " << supplierOrdersPrice(num, d1, d2) << endl;
			break;
		case 19:
			cout << "Enter salesman id: ";
			cin >> num;
			cout << "Number of transactions performed by salesman: " << transactionsBySalesman(num) << endl;
			break;
		case 20:
			printTop10Books();
			break;
		default:
			cout << "Invalid commmand number!" << endl;
			break;
		}

		cout << endl;
	}

	return 0;
}

