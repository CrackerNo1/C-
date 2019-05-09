#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <string>
using namespace std;
float w[3];
float x1[80], x2[80];
float d[80];
float y, error, error_max = 0.01;
int maxepoch = 10000;
float nuy = 0.5;
int count_true = 0;
int k = 0;
int main()
{
	srand(static_cast<unsigned>(time(0)));
	const int maximum_number = 1;
	const int minimum_number = -3;
	for (int i = 0; i < 3; i++)
	{
		float new_number = (rand() % (maximum_number + 1 - minimum_number)) + minimum_number;
		w[i] = new_number / 10;
		cout << w[i] << "\n";
	}
	
    fstream file;
    file.open("train0408.dat");
    char *data;
    for(int i = 0; i < 81; i++)
    {
        file >> data;
        x1[i] = atof(data);
        file >> data;
        x2[i] = atof(data);;
        file >> data;
        d[i] = atof(data);;
        cout << x1[i] << "--";
        cout << x2[i] << "--";
        cout << d[i] << endl;
    }
    file.close();
    
	// ostd::fstream weightp;
	file.open("error.txt");
	for (k = 0; k < maxepoch; k++)
	{
		for (int i = 0; i < 81; i++)
		{
			y = w[0] + w[1] * x1[i] + w[2] * x2[i];
			y = 1 / (1 + exp(-y));
			float t_1 = (float)d[i];
			float delta = (t_1 - y) * y * (1 - y);
			w[0] = w[0] + nuy * delta;
			w[1] = w[1] + nuy * delta * (float)x1[i];
			w[2] = w[2] + nuy * delta * (float)x2[i];
			error = error + 0.5 * abs((t_1 - y));
		}
		file << error << endl;
		if (error < error_max)
			break;
		error = 0;
	}
	// cout << error << "\n";
	// cout << k << "\n";
	// cout << fixed << showpoint;
	// cout << setprecision(3);
	// weightp << w[0] << endl;
	// weightp << w[1] << endl;
	// weightp << w[2] << endl;
	cout << "w[0] = " << w[0] << endl;
	cout << "w[1] = " << w[1] << endl;
	cout << "w[2] = " << w[2] << endl;
	return 0;
}
