    #include<iostream>
    #include<stdlib.h>
    #include<omp.h>
    #include<chrono>
    using namespace std;
    using namespace std::chrono;

    void swap(int &a, int &b)
        {
            int test=a;
            a=b;
            b=test;
        }
    void bubble(int a[], int n)
    {
        for( int i = 0; i < n; i++ )
        {
            int first = i % 2;
            #pragma omp parallel for shared(a,first)
            for( int j = first; j < n-1; j += 2 )
        {
            if( a[ j ] > a[ j+1 ] )
            {
                swap( a[ j ], a[ j+1 ] );
        }
        }
        }
    }
    
    
    int main()
    {
        int n;
        cout<<"\n enter total no of elements=>";
        cin>>n;
        int a[n];
        // a=new int[n];
        cout<<"\n enter elements=>";
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
        }

        // Start the timer
        auto start = high_resolution_clock::now();

        // Perform the algorithm
        bubble(a,n);

        // Stop the timer
        auto stop = high_resolution_clock::now();

        // Calculate the duration
        auto duration = duration_cast<milliseconds>(stop - start);
        
        cout<<"\n sorted array is=>";
        for(int i=0;i<n;i++)
        {
            cout<<a[i]<<endl;
        }

         // Print the execution time
        cout << "Execution time: " << duration.count() << " milliseconds" << endl;
        
    }