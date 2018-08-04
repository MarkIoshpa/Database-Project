#include "Database.h"

Database *Database::instance = 0;

Database::Database() : driver(get_driver_instance()) {
	connection_properties["hostName"] = DB_HOST;
	connection_properties["port"] = DB_PORT;
	connection_properties["userName"] = DB_USER;
	connection_properties["password"] = DB_PASS;
	connection_properties["OPT_RECONNECT"] = true;

	// use database
	try {
		Connection *con = driver->connect(connection_properties);
		try {
			con->setSchema("book_store");
		}
		catch (SQLException &e) {
			Statement *stmt = con->createStatement();
			stmt->execute(
				"CREATE DATABASE IF NOT EXISTS book_store");
			con->setSchema("book_store"); // switch database
			stmt->execute("CREATE TABLE IF NOT EXISTS Book("
				"Book_Id INT UNSIGNED PRIMARY KEY,"
				"In_Stock INT UNSIGNED,"
				"Book_Name VARCHAR(50),"
				"Author VARCHAR(50),"
				"Price FLOAT"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS Discount("
				"Discount_Id INT UNSIGNED PRIMARY KEY,"
				"Book_Id INT UNSIGNED,"
				"FOREIGN KEY(Book_Id) REFERENCES Book(Book_Id) ON DELETE RESTRICT ON UPDATE RESTRICT,"
				"Start_Date DATE,"
				"End_Date DATE,"
				"Amount FLOAT,"
				"is_Specific_Discount BOOL"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS Customer("
				"Customer_Number INT UNSIGNED PRIMARY KEY,"
				"Firstname VARCHAR(50),"
				"Lastname VARCHAR(50),"
				"Phone VARCHAR(50),"
				"Customer_Date DATETIME,"
				"Discount_Id INT UNSIGNED,"
				"FOREIGN KEY(Discount_Id) REFERENCES Discount(Discount_Id) ON DELETE RESTRICT ON UPDATE RESTRICT"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS Supplier("
				"Supplier_Id INT UNSIGNED PRIMARY KEY,"
				"Supplier_Name VARCHAR(50),"
				"Supplier_Phone VARCHAR(50)"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS Orders ("
				"Order_Id INT UNSIGNED PRIMARY KEY,"
				"Order_Date DATETIME,"
				"Book_Id INT UNSIGNED,"
				"Amount INT UNSIGNED,"
				"Order_Status ENUM('ordered', 'delivered', 'cancelled'),"
				"FOREIGN KEY(Book_Id) REFERENCES Book(Book_Id) ON DELETE RESTRICT ON UPDATE RESTRICT,"
				"Supplier_Id INT UNSIGNED,"
				"FOREIGN KEY(Supplier_Id) REFERENCES Supplier(Supplier_Id) ON DELETE RESTRICT ON UPDATE RESTRICT"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS Salesman("
				"Salesman_Id INT UNSIGNED PRIMARY KEY,"
				"Firstname VARCHAR(50),"
				"Lastname VARCHAR(50)"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS Transaction("
				"Transaction_Id INT UNSIGNED PRIMARY KEY,"
				"Transaction_Date DATETIME,"
				"Customer_Number INT UNSIGNED,"
				"FOREIGN KEY(Customer_Number) REFERENCES Customer(Customer_Number) ON DELETE RESTRICT ON UPDATE RESTRICT,"
				"Salesman INT UNSIGNED,"
				"FOREIGN KEY(Salesman) REFERENCES Salesman(Salesman_Id) ON DELETE RESTRICT ON UPDATE RESTRICT"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS Buy_Book ("
				"Book_Id INT UNSIGNED,"
				"FOREIGN KEY(Book_Id) REFERENCES Book(Book_Id) ON DELETE RESTRICT ON UPDATE RESTRICT,"
				"Transaction_Id INT UNSIGNED,"
				"FOREIGN KEY(Transaction_Id) REFERENCES Transaction(Transaction_Id) ON DELETE RESTRICT ON UPDATE RESTRICT,"
				"PRIMARY KEY(Book_Id, Transaction_Id),"
				"Amount INT UNSIGNED"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS Has_Supplier ("
				"Book_Id INT UNSIGNED,"
				"FOREIGN KEY(Book_Id) REFERENCES Book(Book_Id) ON DELETE RESTRICT ON UPDATE RESTRICT,"
				"Supplier_Id INT UNSIGNED,"
				"FOREIGN KEY(Supplier_Id) REFERENCES Supplier(Supplier_Id) ON DELETE RESTRICT ON UPDATE RESTRICT,"
				"PRIMARY KEY(Book_Id, Supplier_Id)"
				")");

			delete stmt;
		}

		delete con;
	}
	catch (SQLException &e) {
		cout << e.getErrorCode() << " " << e.what() << " " << e.getSQLState();
	}
}

Database & Database::getInstance() {
	if (Database::instance == 0) {
		instance = new Database();
	}
	return *instance;
}

Connection * Database::getConnection() {
	try {
		Connection *con = driver->connect(connection_properties);
		con->setSchema(DB_NAME);
		return con;
	}
	catch (SQLException &e) {
		cout << e.what();
	}
	return 0;
}
