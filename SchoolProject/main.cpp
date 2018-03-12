#include <list>
#include <iostream>
#include <string>
#include <windows.h>
#include <mysql.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
	if (printTop)
	{

		cout << "+----------------------------------------+" << endl;
		cout << "|";
	}
	else
	{
		cout << "|";
	}
	bool front = true;
	for (int i = message.length(); i < 40; i++)
	{
		if (front)
		{
			message = " " + message;
		}
		else
		{
			message = message + " ";

		}
		front = !front;
	}
	cout << message.c_str();
	if (printBottom)
	{
		cout << "|" << endl;
		cout << "+----------------------------------------+" << endl;
	}
	else
	{
		cout << "|" << endl;
	}
}

class Student
{
public:
    string id, name, age, phone;

    void enterAll()
    {
         cout << "Enter name: ";cin>> name; cout<< endl;
         cout << "Enter phone: "; cin>> phone; cout<< endl;
         cout << "Enter age: "; cin>> age; cout<< endl;
    }
    void show()
    {
         cout<< "- Id: "<< id << " Name: "<< name << " age: "<< age << " Phone: "<< phone << endl;
         system("pause");
    }
    void showAll()
    {
         cout<< "- Id: "<< id << " Name: "<< name << " age: "<< age << " Phone: "<< phone << endl;
    }
    void enterId() {
		cout << "Enter id: "; cin >> id; cout << endl;
	}
};


class Database
{
public:
    string s,t,c;
protected:
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    int qstate;
public:
    Database()
    {
        s = "student"; t= "teacher"; c = "course";
         conn = mysql_init(0);
        if(conn)
            cout<<"connection object ok, conn="<<conn<<endl;
        else
            cout<<"conn object problem: "<<mysql_error(conn);

        conn = mysql_real_connect(conn,"localhost","root","","project",0,NULL,0);
        if(conn)
        {
            cout<< "connection to databse done"<<endl;
        }
        else{
            cout<<"conn object problem: "<<mysql_error(conn)<<endl;
        }
    }
    void close()
    {
         mysql_close(conn);
    }


//--------------------------------------------------------STUDENT-----------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
    //Create Student
    void insertStudent(Student s)
    {
		string query = "insert into student(name, age , phone ) values('" + s.name + "'," + s.age + ",'" + s.phone + "')";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record inserted successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
	}

	//Select 1 or all student to show
    Student selectStudent(string id)
    {
		Student s;

		string query = "SELECT * FROM `student` WHERE id=" + id;
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
                s.id = row[0];
                s.name = row[1];
                s.age = row[2];
                s.phone = row[3];
			}
		}
		else
		{
			cout << "query error: " << mysql_error(conn) << endl;
		}

		return s;
	}

    list<Student> selectStudents()
    {
		list<Student> students;

		string query = "SELECT * FROM `student`";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				Student s;
				s.id = row[0];
				s.name = row[1];
				s.age = row[2];
				s.phone = row[3];
				students.push_front(s);
			}
		}
		else
		{
			cout << "query error: " << mysql_error(conn) << endl;
		}



		return students;
	}


	//Update Student
	void updateStudent(Student s)
	{

		string query = "UPDATE `student` SET `name`='" + s.name + "',`age`=" + s.age + ",`phone`='" + s.phone + "' WHERE id=" + s.id;
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record Updated successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
	}


	//Delete Student
	void deleteStudent(Student s)
	{
        string query = "DELETE FROM student WHERE id=" + s.id;
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record Deleted successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
	}

//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

    //void Delete(string id, string table) {
	//	string query = "DELETE FROM `" + table + "` WHERE id=" + id;
	//	const char* q = query.c_str();
	//	qstate = mysql_query(conn, q);
	//	if (!qstate)
	//		cout << "record Deleted successfully..." << endl;
	//	else
	//		cout << "query problem: " << mysql_error(conn) << endl;
	//}
};

void showAllStudents()
{
	Database db;
	Student s;


	list<Student> students;
	students = db.selectStudents();
	for (s : students) {
		s.showAll();
	}
	system("pause");
	db.close();
}



int main()
{
    int n;
	do {
		system("cls");
		PrintMessage("Main Menu");
		PrintMessage("1  Student Menu      ", false, false);
		PrintMessage("3. Administrator Menu", false, false);
		PrintMessage("4. Exit              ", false, false);
		PrintMessage("Please Select your option (1-4): ");
		cin >> n;
		switch (n)
		{
		case 1:

		    break;
		case 2: break;
		case 4: exit(0);
		default: "\a"; break;
		}

	} while (n != 4);


	return 0;
}

//---------- create student -------------
//    s.enterAll();
//    db.insertStudent(s);
//    s.show();
//---------------------------------------


//---------- delete student -------------
//    s.enterId();
//    db.deleteStudent(s);
//    s.show();
//---------------------------------------


//---------- Show All student -----duh---
//    showAllStudents();
//---------------------------------------


//---------- Show student by ID ---------
//    s.enterId();
//    s = db.selectStudent(s.id);
//    s.show();
//---------------------------------------



//---------- update student -------------
//    s.enterId();
//    s.enterAll();
//    db.updateStudent(s);
//    s.show();
//---------------------------------------



//---------- delete student -------------
//---------------------------------------



//---------- delete student -------------
//---------------------------------------

