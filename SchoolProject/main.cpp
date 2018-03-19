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
         cout << "Enter age: "; cin>> age; cout<< endl;
         cout << "Enter phone: "; cin>> phone; cout<< endl;
    }
    void show()
    {
         cout << "- Name: "<< name << " age: "<< age << " Phone: "<< phone << endl;
         system("pause");
    }
    void showAll()
    {
         cout<< "- Id: "<< id << " Name: "<< name << " age: "<< age << " Phone: "<< phone << endl;
    }
    void enterId() {
		cout << "Enter id: "; cin >> id; cout << endl;
	}
	bool operator <(const Student & st) const
	{
		return id < st.id;
	}
};

class Teacher
{
    public: string id, name, age, phone;

    void enterAll()
    {
         cout << "Enter name: ";cin>> name; cout<< endl;
         cout << "Enter age: "; cin>> age; cout<< endl;
         cout << "Enter phone: "; cin>> phone; cout<< endl;
    }
    void show()
    {
         cout << "- Name: "<< name << " age: "<< age << " Phone: "<< phone << endl;
         system("pause");
    }
    void showAll()
    {
         cout<< "- Id: "<< id << " Name: "<< name << " age: "<< age << " Phone: "<< phone << endl;
    }
    void enterId() {
		cout << "Enter id: "; cin >> id; cout << endl;
	}
	bool operator <(const Teacher & t) const
	{
		return id < t.id;
	}

};


class Course
{
public:
    string id, name,  tid;
    Teacher t;
public:
    void enterName()
    {
         cout << "Enter name: ";cin>> name; cout<< endl;
    }
    void enterAll()
    {
         cout << "Enter Teachers ID: "; cin>> tid; cout<< endl;

    }
    void showAll()
    {
         cout<< "- Id: "<< id << " Course Name: "<< name << "Teachers Name: "<<t.name << endl;
         system("pause");
    }
    void ShowCourse()
    {
        cout << "- Teachers name: " << t.name << " Course: " << name << endl;
    }
    void enterId()
    {
        cout << "Enter id: "; cin >> id; cout << endl;
    }
	bool operator <(const Course & c) const
	{
		return id < c.id;
	}

};

class Enrolled{
public: string id , student_id, course_id ;
    Student s;
    Course c;

    void enterAll()
    {
        cout << "Enter Student id: "; cin>> student_id; cout<< endl;
        cout << "Enter Course id: "; cin>> course_id; cout<< endl;
    }
    void show()
    {
        cout << s.name << endl;

    }
    void enterId()
    {
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


        students.sort();

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
    //Create Teacher
    void insertStudent(Teacher t)
    {
		string query = "insert into teacher(name, age , phone ) values('" + t.name + "'," + t.age + ",'" + t.phone + "')";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record inserted successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
	}

    //select 1 or all teachers
    Teacher selectTeacher(string id)
    {
		Teacher t;

		string query = "SELECT * FROM `teacher` WHERE id=" + id;
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
                t.id = row[0];
                t.name = row[1];
                t.age = row[2];
                t.phone = row[3];
			}
		}
		else
		{
			cout << "query error: " << mysql_error(conn) << endl;
		}

		return t;
	}

    list<Teacher> selectTeachers()
    {
		list<Teacher> teachers;

		string query = "SELECT * FROM `teacher`";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				Teacher t;
				t.id = row[0];
				t.name = row[1];
				t.age = row[2];
				t.phone = row[3];
				teachers.push_front(t);
			}
		}
		else
		{
			cout << "query error: " << mysql_error(conn) << endl;
		}


        teachers.sort();

		return teachers;
	}


	//Update teacher
	void updateTeacher(Teacher t)
	{

		string query = "UPDATE `teacher` SET `name`='" + t.name + "',`age`=" + t.age + ",`phone`='" + t.phone + "' WHERE id=" + t.id;
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record Updated successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
	}

    //Delete Teacher
	void deleteTeacher(Teacher t)
	{
        string query = "DELETE FROM teacher WHERE id=" + t.id;
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record Deleted successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
	}

//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

    void insertCourse(Course c)
    {
		string query = "insert into course(name) values('" + c.name + "')";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record inserted successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
	}

	Course selectCourse(string id)
	{
        Course c;
        string tId;

        string query="SELECT * FROM `course` WHERE id="+id;
        const char* q = query.c_str();
        qstate = mysql_query(conn,q);
        if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row=mysql_fetch_row(res))
            {
                c.id = row[0];
                c.name = row [1];
                tId = row[2];
            }
        }
        else
        {
            cout<<"query error: "<<mysql_error(conn)<<endl;
        }


        c.t = selectTeacher(tId);
        return c;
    }

    list<Course> selectCourses()
    {
		list<Course> courses;
		Course c;
		string tId;

		string query = "SELECT * FROM `course`";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				Course c;
				c.id = row[0];
				c.name = row[1];
				c.tid = row[2];
				courses.push_front(c);
			}
		}
		else
		{
			cout << "query error: " << mysql_error(conn) << endl;
		}

		for (c : courses) {
			c.t = selectTeacher(c.tid);
		}

        courses.sort();

		return courses;
	}


	void updateCourse(Course c)
	{
	    string query = "UPDATE `course` SET `teacher_id`=" + c.tid + " WHERE id=" + c.id;
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record Updated successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
	}



	void deleteCourse(Course c)
	{
	    string query = "DELETE FROM course WHERE id=" + c.id;
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record Deleted successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
	}

//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

    void insertEnroll(Enrolled e)
    {
		string query = "insert into enrolled(student_id, course_id ) values('" + e.student_id + "','" + e.course_id + "')";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record inserted successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
    }

    void deleteEnroll(Enrolled e)
    {
        string query = "DELETE FROM course WHERE id=" + e.id;
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
			cout << "record Deleted successfully..." << endl;
		else
			cout << "query problem: " << mysql_error(conn) << endl;
    }


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

void showAllTeachers()
{
	Database db;
	Teacher t;


	list<Teacher> teachers;
	teachers = db.selectTeachers();
	for (t : teachers) {
		t.showAll();
	}
	system("pause");
	db.close();
}

void showAllCourses()
{
	Database db;
	Course c;


	list<Course> courses;
	courses = db.selectCourses();
	for (c : courses) {
		c.ShowCourse();
	}
	system("pause");
	db.close();
}


void AdminMenu();
void AdminTeacherMenu();
void AdminStudentMenu();
void AdminCourseMenu();


int main()
{
    Course c;
    Student s;
    Teacher t;
    Enrolled e;
    Database db;
    int n;
	do {
		system("cls");
		PrintMessage("Main Menu");
		PrintMessage("1. Administrator Menu ", false, false);
		PrintMessage("2. Test Method        ", false, false);
		PrintMessage("3. moreTestMethod     ", false, false);
		PrintMessage("4. Exit               ", false, false);
		PrintMessage("Please Select your option (1-3): ");
		cout<< ">";	cin >> n;
		switch (n)
		{
		case 1:
            AdminMenu();
		    break;
		case 2:
		    showAllCourses();
            break;
		case 3:
		    e.enterAll();
		    db.insertEnroll(e);
            break;
		case 4: exit(0);
		default: "\a"; break;
		}

	} while (n != 4);

	return 0;
}

void AdminMenu()
{

    int n;
    system("cls");
	PrintMessage("Administrator Menu");
	PrintMessage("-------------------------------", false, false);
	PrintMessage("1.  Admin Student Menu         ", false, false);
	PrintMessage("-------------------------------", false, false);
	PrintMessage("                               ", false, false);
	PrintMessage("-------------------------------", false, false);
    PrintMessage("2.  Admin Teacher Menu         ", false, false);
	PrintMessage("-------------------------------", false, false);
	PrintMessage("                               ", false, false);
    PrintMessage("-------------------------------", false, false);
    PrintMessage("3.  Admin Course Menu          ", false, false);
	PrintMessage("-------------------------------", false, false);
    PrintMessage("                               ", false, false);
	PrintMessage("4. Back To Main Menu           ", false, false);
	PrintMessage("Enter Your Choice (1-4)");
	cout<< ">";	cin >> n;
	switch (n)
	{
	case 1:
	    AdminStudentMenu();
	    break;
	case 2:
        AdminTeacherMenu();
        break;
    case 3:
        AdminCourseMenu();
	    break;
   	case 4:return;
	default: cout << "\a";

	}
	AdminMenu();
}

void AdminTeacherMenu()
{
    Database db;
    Teacher t;

    int n;
    system("cls");
	PrintMessage("Admin Teacher Menu");
	PrintMessage("-----------Teacher-------------", false, false);
    PrintMessage("1.  Create Teacher Record      ", false, false);
	PrintMessage("2.  Display All Teachers Record", false, false);
	PrintMessage("3.  Search Teacher Record      ", false, false);
	PrintMessage("4.  Modify Teacher Record      ", false, false);
	PrintMessage("5.  Delete Teacher Record      ", false, false);
	PrintMessage("-------------------------------", false, false);
	PrintMessage("6.  Back To Admin Menu         ", false, false);
	PrintMessage("Enter Your Choice (1-6)");
	cout<< ">";	cin >> n;
	switch (n)
	{
    case 1:
	    t.enterAll();
	    db.insertStudent(t);
	    t.show();
	    break;
	case 2:
	    showAllTeachers();
	    break;
    case 3:
        t.enterId();
        t = db.selectTeacher(t.id);
        t.show();
	    break;
	case 4:
        t.enterId();
        t.enterAll();
        db.updateTeacher(t);
        t.show();
	    break;
	case 5:
        t.enterId();
        db.deleteTeacher(t);
        t.show();
	    break;
   	case 6:return;
	default: cout << "\a";

	}
	AdminTeacherMenu();
}

void AdminStudentMenu()
{
    Database db;
    Student s;

    int n;
    system("cls");
	PrintMessage("Admin Student Menu");
	PrintMessage("-----------Student-------------", false, false);
	PrintMessage("1.  Create Student Record      ", false, false);
	PrintMessage("2.  Display All Students Record", false, false);
	PrintMessage("3.  Search Student Record      ", false, false);
	PrintMessage("4.  Modify Student Record      ", false, false);
	PrintMessage("5.  Delete Student Record      ", false, false);
	PrintMessage("-------------------------------", false, false);
	PrintMessage("6.  Back To Admin Menu         ", false, false);
	PrintMessage("Enter Your Choice (1-6)");
	cout<< ">";	cin >> n;
	switch (n)
	{
	case 1:
	    s.enterAll();
	    db.insertStudent(s);
	    s.show();
	    break;
	case 2:
	    showAllStudents();
	    break;
    case 3:
        s.enterId();
        s = db.selectStudent(s.id);
        s.show();
	    break;
	case 4:
        s.enterId();
        s.enterAll();
        db.updateStudent(s);
        s.show();
	    break;
	case 5:
        s.enterId();
        db.deleteStudent(s);
        s.show();
	    break;
   	case 6:return;
	default: cout << "\a";

	}
	AdminStudentMenu();

}

void AdminCourseMenu()
{
    Database db;
    Teacher t;
    Course c;
    Enrolled e;

    int n;
    system("cls");
	PrintMessage("Admin Course Menu");
	PrintMessage("-------------------------------", false, false);
    PrintMessage("1.  Create Course Record       ", false, false);
	PrintMessage("2.  enroll                     ", false, false);
	PrintMessage("3.  Search Course Record       ", false, false);
	PrintMessage("4.  Modify Course Record       ", false, false);
	PrintMessage("5.  Delete Course Record       ", false, false);
	PrintMessage("-------------------------------", false, false);
	PrintMessage("6.  Back To Admin Menu         ", false, false);
	PrintMessage("Enter Your Choice (1-6)");
	cout<< ">";	cin >> n;
	switch (n)
	{
    case 1:
        c.enterName();
        db.insertCourse(c);
        c.ShowCourse();
        system("pause");
	    break;
	case 2:
        showAllCourses();
	    break;
    case 3:
        c.enterId();
        c = db.selectCourse(c.id);
        c.showAll();
	    break;
	case 4:
        c.enterId();
        c.enterAll();
        db.updateCourse(c);
        c.showAll();
	    break;
	case 5:
        c.enterId();
        db.deleteCourse(c);
        c.showAll();
        system("pause");
	    break;
	case 6:
	    showAllStudents();
	    showAllCourses();
	    e.enterAll();
        db.insertEnroll(e);
	    break;
   	case 7:return;
	default: cout << "\a";

	}
	AdminCourseMenu();
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

