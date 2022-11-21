// Definition of function exchange
void exchange(float* a, float* b)
{
    // Create temporal variable for swapping
    float temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
}