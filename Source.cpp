#include<iostream>
#include<math.h>
using namespace std;
                                     //SHAPE3D (ABSTRACT CLASS)
class Shape3D
{
protected:
	double X_ref;
	double Y_ref;
	double Z_ref;
public:
	
	Shape3D(double inX, double inY, double inZ);
	virtual double CalculateArea() = 0; //pure virtual
	virtual double CalculateVolume() = 0; //pure virtual
	int Compare(Shape3D* Shape2); //pure virtual
	void TranslateShape(double x, double y, double z);
	virtual void PrintInfo();
	virtual ~Shape3D();
};

Shape3D::Shape3D(double inX, double inY, double inZ) {
	X_ref = inX;
	Y_ref = inY;
	Z_ref = inZ;
}
void Shape3D::TranslateShape(double x, double y, double z) {
	X_ref = X_ref + x;
	Y_ref = Y_ref + y;
	Z_ref = Z_ref + z;
}
void Shape3D::PrintInfo() {
	cout << "X= " << X_ref << endl;
	cout << "Y= " << Y_ref << endl;
	cout << "Z= " << Z_ref << endl;
	cout << "Area= " << CalculateArea() << endl;
	cout << "Volume= " << CalculateVolume() << endl;
}
int Shape3D::Compare(Shape3D* Shape2) {
	if (CalculateVolume() > Shape2->CalculateVolume()) {
		return 1;
	}
	else if (CalculateVolume() < Shape2->CalculateVolume()) {
		return -1;
	}
	else {
		return 0;
	}
}
Shape3D::~Shape3D() {

}
                                       //CUBOID(CONCRETE CLASS)
class Cuboid : public Shape3D
{
private:
	double Length;
	double Width;
	double Height;
public:
	Cuboid(double L, double W, double H, double x, double y, double z);
	double CalculateArea() override;
	double CalculateVolume() override;
	void SetLength(double inL);
	void SetWidth(double inW);
	void SetHeight(double inH);
	double GetLength();
	double GetWidth();
	double GetHeight();
	void PrintInfo() override;
};
Cuboid::Cuboid(double L, double W, double H, double x, double y, double z) :Shape3D(x, y, z) {
	SetLength(L);
	SetWidth(W);
	SetHeight(H);
	X_ref = x;
	Y_ref = y;
	Z_ref = z;
}
double Cuboid::CalculateArea() {
	double Area = (2 * Length * Width) + (2 * Width * Height) + (2 * Length * Height);
	return Area;
}
double Cuboid::CalculateVolume() {
	double Volume = Length * Width * Height;
	return Volume;
}
void Cuboid::SetLength(double inL) {
	Length = (inL > 0) ? inL : 1;
}
void Cuboid::SetWidth(double inW) {
	Width = (inW > 0) ? inW : 1;
}
void Cuboid::SetHeight(double inH) {
	Height = (inH > 0) ? inH : 1;
}
double Cuboid::GetLength() {
	return Length;
}
double Cuboid::GetWidth() {
	return Width;
}
double Cuboid::GetHeight() {
	return Height;
}

void Cuboid::PrintInfo() {
	cout << "Printing Cuboid info:" << endl;
	cout << "Length= " << Length << endl;
	cout << "Width= " << Width << endl;
	cout << "Height= " << Height << endl;
	Shape3D::PrintInfo();
}
                                       //SPHERE(CONCRETE CLASS)
class Sphere : public Shape3D
{
private:
	double Radius;
public:
	Sphere(double r, double x, double y, double z);
	double CalculateArea()override;
	double CalculateVolume() override;
	void SetRadius(double r);
	double GetRadius();
	void PrintInfo() override;
};
Sphere::Sphere(double r, double x, double y, double z): Shape3D(x, y, z) {
	SetRadius(r);
	X_ref = x;
	Y_ref = y;
	Z_ref = z;
}
double Sphere::CalculateArea() {
	double Area = 4 * 3.14 * (pow(Radius, 2));
	return Area;
}
double Sphere::CalculateVolume() {
	double Volume = (4 * 3.14 * (pow(Radius, 3))) / 3;
	return Volume;
}
void Sphere::SetRadius(double r) {
	Radius = (r > 0) ? r : 1;
}
double Sphere::GetRadius() {
	return Radius;
}
void Sphere::PrintInfo() {
	cout << "Printing Sphere info:" << endl;
	cout << "Radius= " << Radius << endl;
	Shape3D::PrintInfo();
}
                                  //MAIN
int CountCuboids(Shape3D** Array, int n) { //Function takes an array of pointers to shape objects & the size of the array
	int CuboidCount = 0;
	for (int i = 0;i < n;i++) {
		Cuboid* ptr = dynamic_cast<Cuboid*>(Array[i]); //Determining the type of shape
		if (ptr != NULL) {
			CuboidCount++;
		}
	}
	return CuboidCount;
}
int CountSpheres(Shape3D** Arr, int n) { //Function takes an array of pointers to shape objects & the size of the array
	int SphereCount = 0;
	for (int i = 0;i < n; i++) {
		Sphere* ptr = dynamic_cast<Sphere*>(Arr[i]); //Determining the type of Shape
		if (ptr != NULL) {
			SphereCount++;
		}
	}
	return SphereCount;
}
void TranslateAll(Shape3D** A, int n, int x, int y, int z) {
	for (int i = 0;i < n; i++) {
		A[i]->TranslateShape(x, y, z);
	}
}

int main() {
	Shape3D* C1 = new Cuboid(3, 4, 5, 1, 1, 1);
	Shape3D* C2 = new Cuboid(2, 5, 7, 2, 3, 4);
	Shape3D* S1 = new Sphere(4, 0, 0, 0);
	Shape3D* S2 = new Sphere(6, 0, 0, 0);
	Shape3D* S3 = new Sphere(10, 0, 0, 0);

	Shape3D** Arr = new Shape3D * [5]; //Array of pointers to shape3D 
	Arr[0] = C1; Arr[1] = C2; Arr[2] = S1; Arr[3] = S2; Arr[4] = S3; //Filling the array

	cout << "Calculating volumes:" << endl;

	for (int i = 0;i < 5;i++) {
		cout << "Volume of Shape" << i + 1 << " = " << Arr[i]->CalculateVolume() << endl;
	}
	int t = 0;
	for (int i = 1;i < 5;i++) {
		if (Arr[0]->Compare(Arr[i]) == -1) {
			t = i;
		}
	}
	cout << "The Shape of the largest volume is shape number: " << t + 1 << endl;
	cout << "                                                                 " << endl;
	cout << "Calculating the surface areas: " << endl;

	for (int i = 0;i < 5;i++) {
		cout << "Surface area of Shape " << i + 1 << " = " << Arr[i]->CalculateArea() << endl;
	}

	cout << "                                                                   " << endl;

	//Counting Cuboids
	cout << "Count of Cuboids: " << CountCuboids(Arr, 5) << endl;
	//Counting Spheres
	cout << "Count of Spheres: " << CountSpheres(Arr, 5) << endl;
	cout << "                              " << endl;
	//Translating first Cuboid
	C1->TranslateShape(2, 0, -1);

	//Translating second Sphere
	S2->TranslateShape(-2, 1, 2);

	//Printing Cuboids info
	C1->PrintInfo();
	C2->PrintInfo();
	cout << "                               " << endl;

	//Printing Spheres info
	S1->PrintInfo();
	S2->PrintInfo();
	S3->PrintInfo();

	//Translating all shapes
	TranslateAll(Arr, 5, 10, 20, 30);

	//Printing Cuboids info
	C1->PrintInfo();
	C2->PrintInfo();
	cout << "                               " << endl;

	//Printing Spheres info
	S1->PrintInfo();
	S2->PrintInfo();
	S3->PrintInfo();

	//Cleanup
	delete[] Arr;
	delete C1;
	delete C2;
	delete S1;
	delete S2;
	delete S3;
	return 0;
}