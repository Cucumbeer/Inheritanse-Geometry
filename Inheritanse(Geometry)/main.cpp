#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color//enum (Enumeration - ������������) - ��� ����� ������������� ����������� ��������.
	{
		//0x - Hexadecimal. ���� ������� ����������, ��� ������ ���� ����������������� �����: http://cplusplus.com/doc/tutorial/constants/
		//0xAF - \
		A - ���� ����;\
		� - ���� ������;
		CONSOLE_DEFAULT = 0x07,
		CONSOLE_RED = 0xCC,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_BLUE = 0x99,

		RED = 0x000000FF,	//0xAlphaBlueGreenRed
		GREEN = 0x0000FF00,
		BLUE = 0x00FF0000
	};

	class Shape
	{
	protected:
		Color color;//����� �������������� ������ ����� ����������, 
		//� ��� ����� ������� ������ �����-�� ������������ ������.
	public:
		Color get_color()const
		{
			return color;
		}
		void set_color(Color color)
		{
			this->color = color;
		}
		Shape(Color color = Color::CONSOLE_DEFAULT) :color(color)
		{
			//this->color = color;
		}
		virtual ~Shape() {}//Virtual Destructor

		virtual double get_area() const = 0;//Pure-virtual function
		virtual double get_perimeter() const = 0;
		virtual void draw()const = 0;
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return this->side;
		}
		void set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
		}
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			//#define SIMPLE_DRAW
					//TODO: Color
#ifdef SIMPLE_DRAW
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//�������� ���������� ���� �������, 
	//����� ���� ���������� ����� ��������� � ���� ������� ����� ���������.
			SetConsoleTextAttribute(hConsole, get_color());//������ ���� ������ � ��������� ���� �������
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);//���������� ���� �� �����  
#endif // SIMPLE_DRAW

		//1) �������� �������� ���� (Handler to Window - HWND)
			HWND hwnd = GetConsoleWindow();
			hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			//2) �������� �������� ����������:
			HDC hdc = GetDC(hwnd);//HDC - Handler to Device Context
			//3) ������� �������� � �����, �������� ����� ��������:
			HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));//PS_SOLID - �������� �����, 5 - ������� ����� � ��������
			//pen (��������) - ������ ������ ������.
			HBRUSH hBrush = CreateSolidBrush(color);

			//4) ����� ��������� �������� � �����:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) ������ �������:
			::Rectangle(hdc, 100, 100, side, side);
			//:: - Global scope (Global namespace)

			//����������� �������:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};

	class Rectangle :public Shape
	{

	};

	class Triangle :public Shape
	{
	public:
		Triangle(Color color) :Shape(color) {}
		~Triangle() {}

		virtual double get_height()const = 0;
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		double set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
			return this->side;
		}
		EquilateralTriangle(double side, Color color) :Triangle(color)
		{
			set_side(side);
		}
		~EquilateralTriangle()
		{

		}
		double get_height()const
		{
			return sqrt(3) / 2 * side;
		}
		double get_area()const
		{
			return get_height() * side / 2;
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		void draw()const
		{
			HWND hwnd = GetDesktopWindow();
			hwnd = GetConsoleWindow();
			//hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			unsigned int start_x = 400;
			unsigned int start_y = 400;

			POINT points[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};

			Polygon(hdc, points, sizeof(points) / sizeof(POINT));

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
	};
}

void main()
{
	setlocale(LC_ALL, "Russian");
	//Shape shape(Color::CONSOLE_BLUE);
	//cout <<hex<< shape.get_color() << endl;

	Geometry::Square square(500, Geometry::Color::BLUE);
	cout << "����� �������:    " << square.get_side() << endl;
	cout << "������� ��������: " << square.get_area() << endl;
	cout << "�������� ��������:" << square.get_perimeter() << endl;
	square.draw();

	Geometry::EquilateralTriangle e3(100, Geometry::Color::GREEN);
	cout << "����� �������:    " << e3.get_side() << endl;
	cout << "������� ��������: " << e3.get_area() << endl;
	cout << "�������� ��������:" << e3.get_perimeter() << endl;
	e3.draw();
	//	Geometry::Rectangle rect;
}