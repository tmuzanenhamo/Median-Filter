//==============================================================================
// Copyright (C) John-Philip Taylor
// tyljoh010@myuct.ac.za
//
// This file is part of the EEE4084F Course
//
// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
//==============================================================================

#include "Prac2.h"

#define parallel TRUE
//------------------------------------------------------------------------------

// This is each thread's "main" function.  It receives a unique ID
void* Thread_Main(void* Parameter){
 int ID = *((int*)Parameter);

 filter(floor(ID*Input.Height/Thread_Count), floor((ID+1)*Input.Height/Thread_Count));

 return 0;

}

//------------------------------------------------------------------------------------------
 int main(int argc, char** argv){
 int j;

 // Initialise everything that requires initialisation
 tic();
 pthread_mutex_init(&Mutex, 0);

 // Read the input image
 if(!Input.Read("Data/greatwall.jpg")){
  printf("Cannot read image\n");
  return -1;
 }

 // Allocated RAM for the output image
 if(!Output.Allocate(Input.Width, Input.Height, Input.Components)) return -2;

 // Golden measure starts here

    if(!parallel){

        tic();
        filter(0, Input.Height);
        printf("The time taken whilst executing the Golden measure is: %lg ms/n", toc()/1e-3);


    }

    if(parallel){
        //spawn threads starts here
         int       Thread_ID[Thread_Count]; // Structure to keep the tread ID
         pthread_t Thread   [Thread_Count]; // pThreads structure for thread admin

         for(j = 0; j < Thread_Count; j++){
                  Thread_ID[j] = j;
                  pthread_create(Thread+j, 0, Thread_Main, Thread_ID+j);
            }
         // Printing stuff is a critical section...
         pthread_mutex_lock(&Mutex);
         printf("Threads created :-)\n");
         pthread_mutex_unlock(&Mutex);

         tic();

         // Wait for threads to finish
         for(j = 0; j < Thread_Count; j++){
          if(pthread_join(Thread[j], 0)){
           pthread_mutex_lock(&Mutex);
            printf("Problem joining thread %d\n", j);
           pthread_mutex_unlock(&Mutex);
          }
         }

 // This is example code of how to copy image files ----------------------------
 //printf("Start of example code...\n");
 //for(j = 0; j < 10; j++){
  //tic();
  //int x, y;
  //for(y = 0; y < Input.Height; y++){
   //for(x = 0; x < Input.Width*Input.Components; x++){
    //Output.Rows[y][x] = Input.Rows[y][x];
   //}
  //}
  //printf("Time = %lg ms\n", (double)toc()/1e-3);
 //}
 //printf("End of example code...\n\n");
 // End of example -------------------------------------------------------------

 // Spawn threads...
// int       Thread_ID[Thread_Count]; // Structure to keep the tread ID
 //pthread_t Thread   [Thread_Count]; // pThreads structure for thread admin

 //for(j = 0; j < Thread_Count; j++){
  //Thread_ID[j] = j;
  //pthread_create(Thread+j, 0, Thread_Main, Thread_ID+j);
 //}

 // Printing stuff is a critical section...
 //pthread_mutex_lock(&Mutex);
  //printf("Threads created :-)\n");
 //pthread_mutex_unlock(&Mutex);

 //tic();


 // No more active threads, so no more critical sections required
 printf("All threads have quit\n");
 printf("Time taken for threads to run = %lg ms\n", toc()/1e-3);


    }

 // Write the output image
 if(!Output.Write("Data/Output.jpg")){
  printf("Cannot write image\n");
  return -3;
 }

 // Clean-up
 pthread_mutex_destroy(&Mutex);
 return 0;
}
//------------------------------------------------------------------------------

void filter(int start_height, int end_height){
        for(int component = 0; component < Input.Components; component ++){
            for(int row = start_height; row<end_height; row++ ){

                for(int col = 0; col<Input.Width; col++){

                   int pixels[81] = {0};
                   int index = 0;

                   for (int i=-4; i<5;i++){
                    for (int j=-4; j<5; j++){

                         if ( (row+i<0) || (row+i>=Input.Height) || (col+j<0) ||  (col+j>Input.Width*Input.Components)){
                            pixels[index++] =0;
                        }
                         else{
                            pixels[index++] = Input.Rows[row+i][Input.Components*(col+j) + component];
                        }

                    }

                   }

                    if (parallel){
                    int med = quick_median(pixels, 0, 81);
                    pthread_mutex_lock(&Mutex);
                    Output.Rows[row][Output.Components*col+component] = med;
                    pthread_mutex_unlock(&Mutex);
                }
                else{
                    Output.Rows[row][Output.Components*col + component] = quick_median(pixels, 0, 81);
                }


                }
            }

        }
     return;

}

//Bubble sort implementation

int bubble_median(int arr[],int Length)
{
      //flag set to 1 to begin first pass
      int i, j, flag = 1;

      int t;
      for(i =1;(i<=Length)&&flag;i++)
     {
          flag = 0;
          for (j=0;j<(Length-1);j++)
         {
               if (arr[j+1]>arr[j])
              {
                    //switch array elements positions
                    t=arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = t;
                    flag = 1;
               }
          }
     }
     return arr[(Length-1)/2];
}

int quick_median(int arr[],int left,int right) {
      int i = left, j = right;
      int m;
      int pivot=arr[(left+right)/2];

      //divide
      while (i<=j) {
            while (arr[i]<pivot)
                  i++;
            while (arr[j]>pivot)
                  j--;
            if (i<=j) {
                  m=arr[i];
                  arr[i]=arr[j];
                  arr[j]=m;
                  i++;
                  j--;
            }
      };

      //recursive function which allows the code to run untill base case is reached
      if (left<j)
            quick_median(arr, left, j);
      if (i < right)
            quick_median(arr, i, right);

      return arr[40];
}
