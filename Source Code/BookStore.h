#pragma once

#include <iostream>
#include "mysql_connection.h"
#include "Database.h"
#include <string>
#include <iomanip>

using namespace sql;
using namespace std;

//print command manual
void commandList();

//print all books that are in stock
void printBooks();

//print orders list
void printOrders();

//print customers list
void printCustomers();

//print suppliers list
void printSuppliers();

//print transactions between StartDate and EndDate
void transactions(const string StartDate, const string EndDate);

//prints all discouts (that are not specified to a customer)
void printDiscounts();

//check if book is in stock
bool isInStock(const string BookName);

//prints all suppliers for specified book
void printBookSuppliers(const string BookName);

//returns total amount of specified book bought since StartDate
int booksBought(const string BookName, const string StartDate);

//returns amount of books bought by customer identified by CustomerNumber since StartDate
int CustomerBooks(const int CustomerNumber, const string StartDate);

//prints details of customer who bought the most books since StartDate
void CustomerWithMostBoughtBooks(const string StartDate);

//prints details of supplier from whom the highest amount of books were ordered
void SupplierWithMostOrders();

//print all amounts of books ordered between StartDate and EndDate
void printOrderBookAmount(const string StartDate, const string EndDate);

//print all amounts of sold books that were ordered between StartDate and EndDate
void printOrderSold(const string StartDate, const string EndDate);

//returns total amount of discounted price that the customer received
double customerDiscounts(const int Customer_Number, const string StartDate);

//return book store revenue from year ordered by Q1, Q2, Q3, Q4
void printYearRevenue(const string Year);

//amount of new customers since StartDate
int newCustomers(const string StartDate);

//price of all orders from supplier between StartDate and EndDate
double supplierOrdersPrice(const int SupplierId, const string StartDate, const string EndDate);

//returns number of transactions performed by a salesman 
int transactionsBySalesman(const int SalesmanId);

//print top 10 most sold books
void printTop10Books();