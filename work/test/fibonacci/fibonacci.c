
long long fibonacci(long i)
{
    long long fib1 = 1;
    long long fib2 = 1;
    long long temp;
    while(i > 2) {
	temp = fib2;
	fib2 = fib2 + fib1;
	fib1 = temp;
	i--;
    }

    return fib2;
}

int main(int argc, char *argv[])
{
    (void)fibonacci(30000000);
    return 0;
}
