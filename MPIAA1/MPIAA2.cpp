// MPIAA2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <ctime> 
#include <omp.h>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;

int main()
{
   
   int n = 10;
   double s = 0;

   double* x = NULL; // объявление
   if (x == NULL)
      x = new double[n]; // выделение памяти

   ifstream inputFile("vector_x.txt");
   for (int i = 0; i < n; i++)
      inputFile >> x[i];
   inputFile.close();

   double* y = NULL;
   if (y == NULL)
      y = new double[n];
   
   ifstream inputFile2("vector_y.txt");
   for (int i = 0; i < n; i++)
      inputFile2 >> y[i];
   inputFile2.close();

   auto begin = std::chrono::steady_clock::now();

   float start_time = clock();
#pragma omp parallel for num_threads(16) reduction(+:s)
      for (int i = 0; i < n; i++)
         s += x[i] * y[i];
 
   float end_time = clock();
   float search_time = end_time - start_time;

   auto end = chrono::steady_clock::now();

   auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin); cout << "The time: " << elapsed_ms.count() << " ms\n";
   cout << endl;

   cout << search_time / 1000 << " s\n";

   cout << sqrt(s)<<"\n";
   cout << sqrt(search_time);
}
