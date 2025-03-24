int BinarySearch(struct Array arr, int key)
{
    int l, mid, h;
    l=0;
    h=arr.lenght-1;
    
    while (l<=h)
    {
        mid=(l+h)/2;
        if(key == arr.A[mid])
            return mid;
        else if(key<arr.A[mid])
            h=mid-1;
        else
            l=mid+1;
    }
    return -1;
}