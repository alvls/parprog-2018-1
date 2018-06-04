//void hoaraSort(int*&, int, int);
//void IHoaraSort(int*&,const int);


void hoaraSort(double* &arr, int first, int last){

    int leftIndex = first,
        rightIndex = last;
    double tmp,
        x = arr[(first + last) / 2];

    do {
       while (arr[leftIndex] < x)
         leftIndex++;
       while (arr[rightIndex] > x)
         rightIndex--;

       if (leftIndex <= rightIndex)
       {
         if (leftIndex < rightIndex)
         {
           tmp=arr[leftIndex];
           arr[leftIndex]=arr[rightIndex];
           arr[rightIndex]=tmp;
         }
         leftIndex++;
         rightIndex--;
       }
    } while (leftIndex <= rightIndex);

    if (leftIndex < last)
       hoaraSort(arr, leftIndex, last);
    if (first < rightIndex)
       hoaraSort(arr, first,rightIndex);
}

void IHoaraSort(double* &arr,const int sizeArr){
    hoaraSort(arr,0,sizeArr-1);
}
