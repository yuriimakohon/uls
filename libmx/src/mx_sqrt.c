static int compare(int current, int x);

int mx_sqrt(int x) {
    if (x == 1) 
        return 1;
    for (int i = 1; i <= x / 2 && i < 46341; i++)
        if (i * i == x)
            return i;
    return 0;
}

