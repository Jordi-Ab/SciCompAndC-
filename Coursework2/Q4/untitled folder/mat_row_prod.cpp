//==========================================================================================
//Gareth Calvert - 4265464 - University of Nottingham - 2016/2017
//==========================================================================================

void mat_row_prod(int n, double **D, double *u)
{
    double *u_prime;
    u_prime = new double [n];
    
    //Allocation f=of memeory for pointer double
    double *dps;
    dps = new double;

    //==========================================================================================
    //In this section the for loop computes the dot product sum of row element by column element.
    //std::cout<<"The vector Ax is: \n"; //Test Print during debug
    for (int i=0; i<n; i++)

        {
            *dps = 0; //reset as zero
            for (int j = 0; j<n; j++)
            {
                *dps += D[i][j]*u[j];
            }

            u_prime[i] = *dps;
        }
    //==========================================================================================
    //Delete dps double as it is no longer needed.
    delete dps;

    for (int i =0; i<n; i++)
    {
        u[i] = u_prime[i];
    }
    
    delete u_prime;
}


