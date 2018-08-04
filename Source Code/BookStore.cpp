#include "BookStore.h"

void commandList()
{
	cout << "List of commands:" << endl
		<< "0. Command manual" << endl
		<< "1. Print all books in stock" << endl
		<< "2. Print all book orders" << endl
		<< "3. Print list of all customers" << endl
		<< "4. Print list of all suppliers" << endl
		<< "5. Print transactions between the specified dates" << endl
		<< "6. Print books with discount (not specific to customer)" << endl
		<< "7. Check if book X is in stock" << endl
		<< "8. List of all suppliers for book X" << endl
		<< "9. Amount of book X sold since date Y" << endl
		<< "10. How many books in total customer Y acquired since date Z" << endl
		<< "11. Details of customer who acquired the most books since date Y" << endl
		<< "12. Details of supplier from whom most books were ordered" << endl
		<< "13. Number of ordered books between the specified dates" << endl
		<< "14. Number of ordered books between the specified dates that were bought" << endl
		<< "15. Total amount of discounts that customer Z received since date Y" << endl
		<< "16. Revenue of the store in Q1, Q2, Q3, Q4 in a year" << endl
		<< "17. How many new customers since date Y" << endl
		<< "18. Total amount of purchases from supplier X between dates" << endl
		<< "19. Total amount of sales of salesman X in store between dates" << endl
		<< "20. List of 10 most sold books between dates" << endl;

}

void printBooks()
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	Statement *stmt = con->createStatement();
	ResultSet *rset = stmt->executeQuery("SELECT * FROM Book WHERE In_Stock>0");
	//print book table header
	cout << left << setw(10) << setfill(' ') << "--Id--"
		<< left << setw(20) << setfill(' ') << "--Name--"
		<< left << setw(20) << setfill(' ') << "--Author--"
		<< left << setw(15) << setfill(' ') << "--In Stock--"
		<< left << setw(15) << setfill(' ') << "--Price--" << endl;
	//print book data from result set
	rset->beforeFirst();
	while (rset->next()) 
	{
		cout << left << setw(10) << setfill(' ') << rset->getInt("Book_Id")
			<< left << setw(20) << setfill(' ') << rset->getString("Book_Name")
			<< left << setw(20) << setfill(' ') << rset->getString("Author")
			<< left << setw(15) << setfill(' ') << rset->getString("In_Stock")
			<< left << setiosflags(std::ios::fixed) << setprecision(2) << setw(15) << setfill(' ') << rset->getDouble("Price")
			<< endl;
	}

	delete con;
	delete stmt;
	delete rset;
}

void printOrders()
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	Statement *stmt = con->createStatement();
	ResultSet *rset = stmt->executeQuery("SELECT o.Order_Id, o.Order_Status, o.Amount, b.Book_Name, s.Supplier_Name FROM Orders o INNER JOIN Book b ON o.Book_Id = b.Book_Id INNER JOIN Supplier s ON s.Supplier_Id = o.Supplier_Id");
	//print order table header
	cout << left << setw(10) << setfill(' ') << "--Id--"
		<< left << setw(15) << setfill(' ') << "--Status--"
		<< left << setw(15) << setfill(' ') << "--Amount--"
		<< left << setw(18) << setfill(' ') << "--Title--"
		<< left << setw(22) << setfill(' ') << "--Supplier--" << endl;
	//print order data from result set
	rset->beforeFirst();
	while (rset->next()) 
	{
		try {
			cout << left << setw(10) << setfill(' ') << rset->getInt("Order_Id")
				<< left << setw(15) << setfill(' ') << rset->getString("Order_Status")
				<< left << setw(15) << setfill(' ') << rset->getInt("Amount")
				<< left << setw(18) << setfill(' ') << rset->getString("Book_Name")
				<< left << setw(22) << setfill(' ') << rset->getString("Supplier_Name")
				<< endl;
		}
		catch (SQLException &e) {
			cout << e.getErrorCode() << " " << e.what() << " " << e.getSQLState();
		}
	}

	delete con;
	delete stmt;
	delete rset;
}

void printCustomers()
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	Statement *stmt = con->createStatement();
	ResultSet *rset = stmt->executeQuery("SELECT * FROM Customer");
	//print customer table header
	cout << left << setw(10) << setfill(' ') << "--Id--"
		<< left << setw(15) << setfill(' ') << "--First Name--"
		<< left << setw(15) << setfill(' ') << "--Last Name--"
		<< left << setw(15) << setfill(' ') << "--Phone--"
		<< left << setw(25) << setfill(' ') << "--Date--" << endl;
	//print customer data from result set
	rset->beforeFirst();
	while (rset->next()) 
	{
		cout << left << setw(10) << setfill(' ') << rset->getInt("Customer_Number")
		<< left << setw(15) << setfill(' ') << rset->getString("Firstname")
		<< left << setw(15) << setfill(' ') << rset->getString("Lastname")
		<< left << setw(15) << setfill(' ') << rset->getString("Phone")
		<< left << setw(25) << setfill(' ') << rset->getString("Customer_Date")
		<< endl;
	}

	delete con;
	delete stmt;
	delete rset;
}

void printSuppliers()
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	Statement *stmt = con->createStatement();
	ResultSet *rset = stmt->executeQuery("SELECT * FROM Supplier");
	//print supplier table header
	cout << left << setw(15) << setfill(' ') << "--Id--";
	cout << left << setw(30) << setfill(' ') << "--Name--";
	cout << left << setw(50) << setfill(' ') << "--Phone--";
	cout << endl;
	//print supplier data from result set
	rset->beforeFirst();
	while (rset->next()) 
	{
		cout << left << setw(15) << setfill(' ') << rset->getInt("Supplier_Id");
		cout << left << setw(30) << setfill(' ') << rset->getString("Supplier_Name");
		cout << left << setw(50) << setfill(' ') << rset->getString("Supplier_Phone");
		cout << endl;
	}

	delete con;
	delete stmt;
	delete rset;
}

void printDiscounts()
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	Statement *stmt = con->createStatement();
	ResultSet *rset = stmt->executeQuery("SELECT d.Discount_Id, b.Book_Name, d.Start_Date, d.End_date, d.Amount FROM Discount d INNER JOIN Book b ON d.Book_Id=b.Book_Id WHERE is_Specific_Discount=false");
	//print discount table header
	cout << left << setw(10) << setfill(' ') << "--Id--"
		<< left << setw(20) << setfill(' ') << "--Book--"
		<< left << setw(15) << setfill(' ') << "--Start--"
		<< left << setw(20) << setfill(' ') << "--End--"
		<< left << setw(20) << setfill(' ') << "--Amount--"
	   << endl;
	//print discount data from result set
	rset->beforeFirst();
	while (rset->next()) 
	{
		cout << left << setw(10) << setfill(' ') << rset->getInt("Discount_Id")
			<< left << setw(20) << setfill(' ') << rset->getString("Book_Name")
			<< left << setw(15) << setfill(' ') << rset->getString("Start_Date")
			<< left << setw(20) << setfill(' ') << rset->getString("End_Date")
			<< left << rset->getInt("Amount") << "%" << endl;
		cout << endl;
	}

	delete con;
	delete stmt;
	delete rset;
}

void transactions(const string StartDate, const string EndDate)
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT t.Transaction_Id, t.Transaction_Date, s.Firstname AS Salesman_Firstname, s.Lastname AS Salesman_Lastname, c.Firstname, c.Lastname FROM Transaction t INNER JOIN Customer c ON t.Customer_Number=c.Customer_Number INNER JOIN Salesman s ON t.Salesman=s.Salesman_Id WHERE Transaction_Date >= ? AND Transaction_Date   <= ?");
	pstmt->setString(1, StartDate);
	pstmt->setString(2, EndDate);
	ResultSet *rset = pstmt->executeQuery();

	rset->beforeFirst();
	while (rset->next())
	{
		cout << "--------Transaction #" << rset->getInt("Transaction_Id") << "--------" << endl
			<< " Date: " << rset->getString("Transaction_Date") << endl
			<< " Salesman: " << rset->getString("Salesman_Firstname") << " " << rset->getString("Salesman_Lastname") << endl
			<< " Customer: " << rset->getString("Firstname") << " " << rset->getString("Lastname") << endl
			<< " Purchases: ";
		//print book list for transaction
		PreparedStatement *pstmtBook = con->prepareStatement("SELECT b.Book_Name, buy.Amount FROM Buy_Book buy INNER JOIN Book b ON b.Book_Id=buy.Book_Id WHERE buy.Transaction_Id = ?");
		pstmtBook->setString(1, rset->getString("Transaction_Id"));
		ResultSet *r2set = pstmtBook->executeQuery();
		r2set->beforeFirst();
		while (r2set->next())
		{
			cout << r2set->getInt("Amount") << "-" << r2set->getString("Book_Name") << "  ";
		}
		cout << endl << endl;

		delete pstmtBook;
		delete r2set;
	}
	delete pstmt;
	delete con;
	delete rset;
}

bool isInStock(const string BookName)
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM Book WHERE Book_Name=?");
	pstmt->setString(1, BookName);
	ResultSet *rset = pstmt->executeQuery();
	//check if rset isn't empty
	if (rset->rowsCount() > 0)
		return true;
	return false;

	delete pstmt;
	delete con;
	delete rset;
}

void printBookSuppliers(const string BookName)
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT s.Supplier_Name FROM Supplier s INNER JOIN has_supplier hs ON hs.Supplier_Id = s.Supplier_Id INNER JOIN Book b ON b.Book_Id = hs.Book_Id WHERE Book_Name = ?");
	pstmt->setString(1, BookName);
	ResultSet *rset = pstmt->executeQuery();

	if (rset->rowsCount() > 0) {
		cout << "Suppliers for " << BookName << " are: ";
		rset->beforeFirst();
		while (rset->next())
		{
			cout << " - " << rset->getString("Supplier_Name");
		}
		cout << endl;
	}
	else
		cout << "Couldn't find suppliers for " << BookName << endl;

	delete pstmt;
	delete con;
	delete rset;
}

int booksBought(const string BookName, const string StartDate)
{
	int result;
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT SUM(bb.Amount) AS TotalAmount FROM Transaction t INNER JOIN Buy_Book bb ON bb.Transaction_Id = t.Transaction_Id INNER JOIN Book b ON b.Book_Id = bb.Book_Id WHERE t.Transaction_Date >= ? AND b.Book_Name = ?");
	pstmt->setString(1, StartDate);
	pstmt->setString(2, BookName);
	ResultSet *rset = pstmt->executeQuery();
	if (rset->rowsCount() > 0) {
		rset->first();
		result = rset->getInt("TotalAmount");
	}
	else
		result = 0;

	delete pstmt;
	delete con;
	delete rset;

	return result;
}

int CustomerBooks(const int CustomerNumber, const string StartDate)
{
	int result;
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT SUM(bb.Amount) AS TotalAmount FROM Transaction t INNER JOIN Buy_Book bb ON bb.Transaction_Id = t.Transaction_Id WHERE t.Transaction_Date >= ? AND t.Customer_Number = ?");
	pstmt->setString(1, StartDate);
	pstmt->setString(2, to_string(CustomerNumber));
	ResultSet *rset = pstmt->executeQuery();
	if (rset->rowsCount() > 0) {
		rset->first();
		result = rset->getInt("TotalAmount");
	}
	else
		result = 0;

	delete pstmt;
	delete con;
	delete rset;

	return result;
}

void CustomerWithMostBoughtBooks(const string StartDate)
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT Customer_Number, MAX(TotalAmount) AS Max FROM(SELECT t.Customer_Number, SUM(bb.Amount) AS TotalAmount FROM Transaction t INNER JOIN Buy_Book bb ON bb.Transaction_Id = t.Transaction_Id WHERE t.Transaction_Date >= ? GROUP BY t.Transaction_Id, t.Customer_Number) AS AmountSums");
	pstmt->setString(1, StartDate);
	ResultSet *rset = pstmt->executeQuery();

	if (rset->rowsCount() > 0) {
		PreparedStatement *pstmtC = con->prepareStatement("SELECT * FROM Customer WHERE Customer_Number = ?");
		rset->first();
		pstmtC->setString(1, rset->getString("Max"));
		ResultSet *r2set = pstmtC->executeQuery();
		r2set->first();
		cout << "Customer who bought the most books (" << rset->getString("Max") << ") since " << StartDate << " is:" << endl;
		cout << "Id: " << r2set->getInt("Customer_Number") << endl
			<< "First name: " << setfill(' ') << r2set->getString("Firstname") << endl
			<< "Last name: " << r2set->getString("Lastname") << endl
			<< "Phone: " << r2set->getString("Phone") << endl
			<< "Date: " << r2set->getString("Customer_Date") << endl;

		delete pstmtC;
		delete r2set;
	}

	delete pstmt;
	delete con;
	delete rset;
	
}

void SupplierWithMostOrders()
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	Statement *stmt = con->createStatement();
	ResultSet *rset = stmt->executeQuery("SELECT Max(AmountSum) AS TotalAmount, Supplier_Name FROM(SELECT SUM(o.Amount) AS AmountSum, s.Supplier_Name FROM Orders o INNER JOIN Supplier s ON o.Supplier_Id = s.Supplier_Id GROUP BY o.Supplier_Id) AS SupplierAmount");
	
	if (rset->rowsCount() > 0)
	{
		rset->first();
		cout << "Supplier with highest amount of ordered books is: " << rset->getString("Supplier_Name") << endl;
		cout << "Amount of books ordered: " << rset->getString("TotalAmount") << endl;
	}

	delete stmt;
	delete con;
	delete rset;
}

void printOrderBookAmount(const string StartDate, const string EndDate)
{

	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT Book_Name, SUM(o.Amount) AS AmountSum FROM Orders o INNER JOIN Book b ON b.Book_Id = o.Book_Id WHERE o.Order_Date >= ? AND o.Order_Date <= ? GROUP BY o.Book_Id");
	pstmt->setString(1, StartDate);
	pstmt->setString(2, EndDate);
	ResultSet *rset = pstmt->executeQuery();

	cout << left << setw(20) << setfill(' ') << "--Book Name--"
	<< left << setw(20) << setfill(' ') << "--Amount Ordered--"
	<< endl;
	
	rset->beforeFirst();
	while (rset->next())
	{
		cout << left << setw(20) << setfill(' ') << rset->getString("Book_Name") 
			<< left << setw(20) << setfill(' ') << rset->getInt("AmountSum");
		cout << endl << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}

void printOrderSold(const string StartDate, const string EndDate)
{

	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT Book_Name, SUM(o.Amount) - b.In_Stock AS AmountSold FROM Orders o INNER JOIN Book b ON b.Book_Id = o.Book_Id WHERE o.Order_Date >= ? AND o.Order_Date <= ? GROUP BY o.Book_Id");
	pstmt->setString(1, StartDate);
	pstmt->setString(2, EndDate);
	ResultSet *rset = pstmt->executeQuery();

	cout << left << setw(20) << setfill(' ') << "--Book Name--"
		<< left << setw(20) << setfill(' ') << "--Amount Sold--"
		<< endl;

	rset->beforeFirst();
	while (rset->next())
	{
		cout << left << setw(20) << setfill(' ') << rset->getString("Book_Name")
			<< left << setw(20) << setfill(' ') << rset->getInt("AmountSold");
		cout << endl << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}

double customerDiscounts(const int Customer_Number, const string StartDate)
{
	double TotalDiscount = 0;
	
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT t.Transaction_Date, b.Price, bb.Book_Id, bb.Amount FROM Transaction t INNER JOIN Buy_Book bb ON bb.Transaction_Id = t.Transaction_Id INNER JOIN Book b ON b.Book_Id = bb.Book_Id WHERE t.Customer_Number = ? AND t.Transaction_Date >= ?");
	pstmt->setString(1, to_string(Customer_Number));
	pstmt->setString(2, StartDate);
	ResultSet *rset = pstmt->executeQuery();

	//calculate non specific discount
	rset->beforeFirst();
	while (rset->next())
	{
		float DiscountPercent = 0;

		PreparedStatement *pstmt2 = con->prepareStatement("SELECT d.Amount FROM Discount d WHERE Book_Id = ? AND ? >= d.Start_Date AND ? <= End_Date AND is_specific_discount = false");
		pstmt2->setString(1, rset->getString("Book_Id"));
		pstmt2->setString(2, rset->getString("Transaction_Date"));
		pstmt2->setString(3, rset->getString("Transaction_Date"));
		ResultSet *rset2 = pstmt->executeQuery();
		rset2->beforeFirst();
		while (rset2->next())
		{
			DiscountPercent += rset2->getDouble("Amount") / 100;
		}
		TotalDiscount += DiscountPercent*rset->getDouble("Amount")*rset->getDouble("Price");

		delete pstmt2;
		delete rset2;
	}

	//calculate specific discount for customer
	rset->beforeFirst();
	while (rset->next())
	{
		float DiscountPercent = 0;

		PreparedStatement *pstmt2 = con->prepareStatement("SELECT d.Amount FROM Discount d INNER JOIN Customer c ON c.Discount_Id = d.Discount_Id WHERE Book_Id = ? AND ? >= d.Start_Date AND ? <= d.End_Date AND d.is_specific_discount = true AND c.Customer_Number = ?");
		pstmt2->setString(1, rset->getString("Book_Id"));
		pstmt2->setString(2, rset->getString("Transaction_Date"));
		pstmt2->setString(3, rset->getString("Transaction_Date"));
		pstmt2->setString(4, to_string(Customer_Number));
		ResultSet *rset2 = pstmt->executeQuery();
		rset2->beforeFirst();
		while (rset2->next())
		{
			DiscountPercent += rset2->getDouble("Amount") / 100;
		}
		TotalDiscount += DiscountPercent*rset->getDouble("Amount")*rset->getDouble("Price");

		delete pstmt2;
		delete rset2;
	}

	delete con;
	delete pstmt;
	delete rset;

	return TotalDiscount;
}

int newCustomers(const string StartDate)
{
	int result = 0;
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("Select COUNT(Customer_Number) AS New_Customer FROM Customer WHERE Customer_Date >= ?");

	pstmt->setString(1, StartDate);
	ResultSet *rset = pstmt->executeQuery();

	rset->first();
	result = rset->getInt("New_Customer");

	delete con;
	delete pstmt;
	delete rset;

	return result;
}

double supplierOrdersPrice(const int SupplierId, const string StartDate, const string EndDate)
{
	double result = 0;
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT SUM(o.Amount * b.Price) AS OrdersPrice FROM Orders o INNER JOIN Book b ON o.Book_Id = b.Book_Id WHERE Supplier_Id = ? AND Order_Date >= ? AND Order_Date <= ? GROUP BY Supplier_Id");
	pstmt->setString(1, to_string(SupplierId));
	pstmt->setString(2, StartDate);
	pstmt->setString(3, EndDate);
	ResultSet *rset = pstmt->executeQuery();

	rset->first();
	result = rset->getDouble("OrdersPrice");

	delete con;
	delete pstmt;
	delete rset;

	return result;
}

;

int transactionsBySalesman(const int SalesmanId)
{
	int result = 0;
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement("SELECT COUNT(Transaction_Id) AS Transactions FROM Transaction WHERE Salesman = ? ");

	pstmt->setString(1, to_string(SalesmanId));
	ResultSet *rset = pstmt->executeQuery();

	rset->first();
	result = rset->getInt("Transactions");

	delete con;
	delete pstmt;
	delete rset;

	return result;
}

void printTop10Books()
{
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	Statement *stmt = con->createStatement();
	ResultSet *rset = stmt->executeQuery("SELECT b.Book_Name, SUM(bb.Amount) AS Total_Amount FROM Book b INNER JOIN Buy_Book bb ON bb.Book_Id = b.Book_Id GROUP BY b.Book_Id ORDER BY Total_Amount DESC LIMIT 10");
	//print book table header
	cout << left << setw(25) << setfill(' ') << "--Book Title--"
		<< left << setw(25) << setfill(' ') << "--Amount Sold--" << endl;
	//print book data from result set
	rset->beforeFirst();
	while (rset->next())
	{
		cout << left << setw(32) << setfill(' ') << rset->getString("Book_Name")
			<< left << setw(25) << setfill(' ') << rset->getString("Total_Amount") << endl;
	}

	delete con;
	delete stmt;
	delete rset;
}


void printYearRevenue(const string Year)
{
	string Q1 = Year + "-01-01";
	string Q2 = Year + "-03-01";
	string Q3 = Year + "-06-01";
	string Q4 = Year + "-09-01";
	string end = Year + "-12-31";
	//connect to database
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	//execute select query
	PreparedStatement *pstmt = con->prepareStatement(
		"SELECT 'Q1',SUM(bb.Amount * b.Price) AS Total_Amount FROM Book b INNER JOIN Buy_Book bb ON bb.Book_Id = b.Book_Id INNER JOIN Transaction t ON bb.Transaction_Id = t.Transaction_Id WHERE t.Transaction_Date >= ? AND t.Transaction_Date <= ? "
		"UNION SELECT 'Q2',SUM(bb.Amount * b.Price) AS Total_Amount FROM Book b INNER JOIN Buy_Book bb ON bb.Book_Id = b.Book_Id INNER JOIN Transaction t ON bb.Transaction_Id = t.Transaction_Id WHERE t.Transaction_Date > ? AND t.Transaction_Date <= ? "
		"UNION SELECT 'Q3', SUM(bb.Amount * b.Price) AS Total_Amount FROM Book b INNER JOIN Buy_Book bb ON bb.Book_Id = b.Book_Id INNER JOIN Transaction t ON bb.Transaction_Id = t.Transaction_Id WHERE t.Transaction_Date > ? AND t.Transaction_Date <= ? "
		"UNION SELECT 'Q4', SUM(bb.Amount * b.Price) AS Total_Amount FROM Book b INNER JOIN Buy_Book bb ON bb.Book_Id = b.Book_Id INNER JOIN Transaction t ON bb.Transaction_Id = t.Transaction_Id WHERE t.Transaction_Date > ? AND t.Transaction_Date <= ? ");
	pstmt->setString(1, Q1);
	pstmt->setString(2, Q2);
	pstmt->setString(3, Q2);
	pstmt->setString(4, Q3);
	pstmt->setString(5, Q3);
	pstmt->setString(6, Q4);
	pstmt->setString(7, Q4);
	pstmt->setString(8, end);

	ResultSet *rset = pstmt->executeQuery();

	cout << endl << "Revenue in year " << Year << ": " << endl;
	rset->first();
	cout << "Q1: " << rset->getDouble("Total_Amount") << endl;
	rset->next();
	cout << "Q2: " << rset->getDouble("Total_Amount") << endl;
	rset->next();
	cout << "Q3: " << rset->getDouble("Total_Amount") << endl;
	rset->next();
	cout << "Q4: " << rset->getDouble("Total_Amount") << endl;

	delete con;
	delete pstmt;
	delete rset;
}