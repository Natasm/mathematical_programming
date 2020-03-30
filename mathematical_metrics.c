#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double mean(double* numbers, int size){
   double sum = 0;
   for(int i = 0; i < size; i++) sum += numbers[i];
   return sum / size;
}

int cmp(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

double median(double* numbers, int size){
   qsort(numbers, size, sizeof(double), cmp);
   if (size % 2 == 0) return (numbers[size/2 - 1] + numbers[size/2]) / 2.0;
   else return numbers[size/2];
}

int cmp_double(const void* a, const void* b){
    return (*(double*)a - *(double*)b);
}

double* mode(double* numbers, int size){
   qsort(numbers, size, sizeof(double), cmp_double);

   int index[size];
   int value_count[size];
   int j = 0;

   int count_max = 0;

   double value_current = numbers[0];
   int count_current = 1;

   for(int i = 1; i <= size; i++){
      if(i == size){
        if(count_current > count_max) count_max = count_current;

        index[j] = i - 1;
        value_count[j] = count_current;

        j++;
        break;
      }
      if(numbers[i] == value_current) count_current++;
      else {
            if(count_current > count_max) count_max = count_current;

            value_current = numbers[i];

            index[j] = i - 1;
            value_count[j] = count_current;
            j++;

            count_current = 1;
      }
   }

   double values[j];
   j = 0;

   for(int i = 0; i < size; i++){
        if(value_count[i] != NULL && value_count[i] > 1){
            if (value_count[i] == count_max){
                values[j] = numbers[index[i]];
                j++;
            }
        }
   }

   printf("Mode: ");
   for (int i = 0; i < j; i++) printf(" %f ", values[i]);

   return values;
}

double standard_deviation(double* numbers, int size){
   double mean_numbers = mean(numbers, size);

   double sum = 0;
   for(int i = 0; i < size; i++){
       sum = sum + (numbers[i] - mean_numbers)*(numbers[i] - mean_numbers);
   }
   sum = sum / (double) size;
   return sqrt(sum);
}

double coefficient_of_variation(double* numbers, int size){
    return (standard_deviation(numbers, size) / mean(numbers, size)) * 100;
}

double first_quartil(double* numbers, int size){
    qsort(numbers, size, sizeof(double), cmp_double);
    return numbers[(int) floor(0.25 * (size))];
}

double second_quartil(double* numbers, int size){
    qsort(numbers, size, sizeof(double), cmp_double);

    if (size % 2 == 0){
        return (numbers[(int) (size / 2) - 1] + numbers[(int) (size / 2)]) / 2.0;
    }
    else return numbers[(int) (size + 1 / 2) - 1];
}

double third_quartil(double* numbers, int size){
    qsort(numbers, size, sizeof(double), cmp_double);
    return numbers[(int) floor(0.75 * (size))];
}

void main(){
   double d[] = {1,3,3,4,2,4};

   printf("Median: %f\n", median(d, 6));
   printf("Mean: %f\n", mean(d, 6));

   mode(d, 6);

   printf("\nStandard deviation: %f\n", standard_deviation(d, 6));

   printf("\nCoefficient of variation: %f\n", coefficient_of_variation(d, 6));

   printf("\nFirst quartil: %f\n", first_quartil(d, 6));
   printf("Second quartil: %f\n", second_quartil(d, 6));
   printf("Third quartil: %f\n", third_quartil(d, 6));
}
