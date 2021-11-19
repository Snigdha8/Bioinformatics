#include <bits/stdc++.h>

using namespace std;

double sum = 0.0;

string getString(char x) 
{ 
    	string s(1, x); 
    	return s;    
}

void get_gamma(double** gamma, double** alpha, double** beta, int size_obs_seq, int num_states, double last_row_sum)
{
	int i,j;
	for( i=0 ; i<size_obs_seq ; i++ )
	{
		for( j=0 ; j<num_states ; j++ )
		{
			gamma[i][j] = alpha[i][j] * beta[i][j];
		}
	}
	
	cout << "\nGAMMA DASH is\n";
    	for( i=0 ; i<size_obs_seq ; i++)
    	{   
        	for( j = 0; j < num_states ; j++)
        	{
        		printf( "%f1000 ", gamma[i][j] );
        	}
        	cout << endl;
    	}
    	
    	for( i=0 ; i<size_obs_seq ; i++ )
	{
		for( j=0 ; j<num_states ; j++ )
		{
			gamma[i][j] = gamma[i][j] / last_row_sum;
		}
	}
}

void get_beta(double** beta, int* obs_seq, int size_obs_seq, int num_states, float** a, float** b, float** pi)
{
	int i,j,k;
	for( i=0 ; i<num_states ; i++ )
	{
		beta[size_obs_seq-1][i] = 1;
	}
	
	for( i=size_obs_seq-2 ; i>=0 ; i-- )
	{
		for( j=0 ; j<num_states ; j++ )
		{
			beta[i][j] = 0.0;
			for( k=0 ; k<num_states ; k++ )
			{
				beta[i][j] = beta[i][j] + beta[i+1][k] * a[j][k] * b[k][obs_seq[i+1]];
			}
		}
	}
}	

double get_alpha(double** alpha, int* obs_seq, int size_obs_seq, int num_states, float** a, float** b, float** pi)
{
	int start_state_ind;
	start_state_ind = obs_seq[0];
	int i,j,k;
	
	for( i=0 ; i<num_states ; i++ )
	{
		alpha[0][i] = pi[0][i] * b[i][start_state_ind];
	}
	
	for( i=1 ; i<size_obs_seq ; i++ )
	{
		for( j=0 ; j<num_states ; j++ )
		{
			alpha[i][j] = 0.0;
			for( k=0 ; k<num_states ; k++ )
			{
				alpha[i][j] = alpha[i][j] + alpha[i-1][k] * a[k][j] * b[j][obs_seq[i]];
			}
		}
	}
	
	double last_row_sum = 0.0;
	for( i=0 ; i<num_states ; i++ )
	{
		last_row_sum = last_row_sum + alpha[size_obs_seq-1][i];
	}
	return last_row_sum;
}

void table1_probability(string prefix, int* obs_seq, double* table1, float** a, float** b, float** pi, int val, int size_obs_seq )
{
	int i;
	int ind1,ind2,ind3;
	int start_state_ind;
	start_state_ind = prefix[0] - '0';
	cout << "\n^^ " << pi[0][start_state_ind] << " ";
	
	double product = 1;
	product = product * pi[0][start_state_ind];
	
	for( i=0 ; i<size_obs_seq ; i++ )
	{
		ind1 = prefix[i] - '0';
		ind2 = obs_seq[i];
		product = product * b[ind1][ind2];
		cout << b[ind1][ind2] << " ";
		if( i+1 < size_obs_seq )
		{
			ind3 = prefix[i+1] - '0';
			product = product * a[ind1][ind3];
			cout << a[ind1][ind3] << " ";
		}
	}
	cout << " ^^" << endl;
	table1[val] = product;
	sum = sum + product;
}
	

void printAllKLengthRec(char set[], string prefix, int n, int k, int* p_ind, int* obs_seq, double* table1, float** a, float** b, float** pi, int size_obs_seq) 
{ 
	if (k == 0) 
	{ 
		int val = *p_ind;
		//cout << "val is " << val << endl;
		table1_probability(prefix,obs_seq,table1,a,b,pi,val,size_obs_seq);
      		cout << (prefix) << endl; 
      		*p_ind = *p_ind + 1;
		return; 
	} 

	// One by one add all characters 
	// from set and recursively 
	// call for k equals to k-1 
	for (int i = 0; i < n; i++) 
	{ 
		string newPrefix; 
		
		// Next character of input added 
		newPrefix = prefix + set[i]; 
		
		// k is decreased, because 
		// we have added a new character 
		printAllKLengthRec(set, newPrefix, n, k - 1, p_ind, obs_seq, table1,a,b,pi,size_obs_seq); 
	} 

} 

void printAllKLength(char set[], int k,int n, int* obs_seq, double* table1, float** a, float** b, float** pi) 
{ 
	int p_ind = 0;
	int size_obs_seq = k;
	printAllKLengthRec(set, "", n, k, &p_ind, obs_seq, table1,a,b,pi,size_obs_seq); 
}

int main()
{
	int num_states, num_tree_ring_size;
	cin >> num_states;
	cin >> num_tree_ring_size;
	
	int i,j;
	float** a = new float*[num_states];
    	for (i = 0; i < num_states; i++)
    	{   
        	a[i] = new float[num_states];
    	}
    	
    	for( i = 0; i < num_states; i++)
    	{   
        	for( j = 0; j < num_states; j++)
        	{
        		cin >> a[i][j];
        		//scanf("%d",&a[i][j]);
        	}
    	}
    	
    	
    	float** b = new float*[num_states];
    	for (i = 0; i < num_states; i++)
    	{   
        	b[i] = new float[num_tree_ring_size];
    	}
    	
    	for( i = 0; i < num_states; i++)
    	{   
        	for( j = 0; j < num_tree_ring_size ; j++)
        	{
        		cin >> b[i][j];
        	}
    	}
    	
    	
    	float** pi = new float*[1];
    	for (i = 0; i < 1; i++)
    	{   
        	pi[i] = new float[num_states];
    	}
    	
    	for( i = 0; i < 1; i++)
    	{   
        	for( j = 0; j < num_states ; j++)
        	{
        		cin >> pi[i][j];
        	}
    	}
    	
    	cout << "\nGRID A is \n";
    	for( i = 0; i < num_states; i++)
    	{   
        	for( j = 0; j < num_states ; j++)
        	{
        		cout << a[i][j] << " ";
        	}
        	cout << endl;
    	}
    	
    	cout << "\nGRID B is \n";
    	for( i = 0; i < num_states; i++)
    	{   
        	for( j = 0; j < num_tree_ring_size ; j++)
        	{
        		cout << b[i][j] << " ";
        	}
        	cout << endl;
    	}
    	
    	cout << "\nGRID PI is \n";
    	for( i = 0; i < 1; i++)
    	{   
        	for( j = 0; j < num_states ; j++)
        	{
        		cout << pi[i][j] << " ";
        	}
        	cout << endl;
    	}
    	
    	int size_obs_seq;
    	cin >> size_obs_seq;
    	int* obs_seq = new int[size_obs_seq];
    	
    	for( i=0 ; i<size_obs_seq ; i++ )
    	{
    		cin >> obs_seq[i];
    	}
    	
    	cout << "\nObservation sequence is \n";
    	for( i=0 ; i<size_obs_seq ; i++ )
    	{
    		cout << obs_seq[i] << " ";
    	}
    	cout << endl;
    	
    	char set1[num_states];
    	for( i=0 ; i<num_states ; i++ )
    	{
    		set1[i] = i + '0';
    	}
    	
    	for( i=0 ; i<num_states ; i++ )
    	{
    		set1[i] = i + '0';
    	}
    	
    	int p = pow(num_states,size_obs_seq);
  	cout << "p is " << p << endl;
  	
    	double* table1 = new double[p];
    	for( i=0 ; i<p ; i++ )
    	{
    		table1[i] = -1.0;
    	}
    	cout << "\nAll permutations are\n";
    	printAllKLength(set1, size_obs_seq , num_states, obs_seq, table1, a, b, pi );
    	
    	cout << "\nTABLE-1 is\n";
    	cout << "probability       normalized probability\n";
    	for( i=0 ; i<p ; i++ )
    	{
    		//cout << table1[i] << "\n";
    		printf( "%f1000       ", table1[i] );
    		printf( "%f1000\n", table1[i]/sum );
    	}
    	cout << endl;
    	
    	//CONSTRUCTING ALPHA
    	double** alpha = new double*[size_obs_seq];
    	for (i = 0; i < size_obs_seq; i++)
    	{   
        	alpha[i] = new double[num_states];
    	}
    	
    	double last_row_sum = get_alpha(alpha,obs_seq,size_obs_seq,num_states,a,b,pi);
    	
    	cout << "ALPHA is\n";
    	for( i=0 ; i<size_obs_seq ; i++)
    	{   
        	for( j = 0; j < num_states ; j++)
        	{
        		printf( "%f1000 ", alpha[i][j] );
        	}
        	cout << endl;
    	}
    	
    	printf("\nLast row sum of ALPHA is %f1000\n",last_row_sum);
    	
    	//CONSTRUCTING BETA
    	double** beta = new double*[size_obs_seq];
    	for (i = 0; i < size_obs_seq; i++)
    	{   
        	beta[i] = new double[num_states];
    	}
    	
    	get_beta(beta,obs_seq,size_obs_seq,num_states,a,b,pi);
    	cout << "\nBETA is\n";
    	for( i=0 ; i<size_obs_seq ; i++)
    	{   
        	for( j = 0; j < num_states ; j++)
        	{
        		printf( "%f1000 ", beta[i][j] );
        	}
        	cout << endl;
    	}
    	
    	//CONSTRUCTING GAMMA
    	double** gamma = new double*[size_obs_seq];
    	for (i = 0; i < size_obs_seq; i++)
    	{   
        	gamma[i] = new double[num_states];
    	}
    	
    	get_gamma(gamma,alpha,beta,size_obs_seq,num_states,last_row_sum);
    	cout << "\nGAMMA is\n";
    	for( i=0 ; i<size_obs_seq ; i++)
    	{   
        	for( j = 0; j < num_states ; j++)
        	{
        		printf( "%f1000 ", gamma[i][j] );
        	}
        	cout << endl;
    	}
    	
    	
    	return 0;
}


/* 

INPUT
2 3
0.7 0.3 0.4 0.6
0.1 0.4 0.5
0.7 0.2 0.1
0.6 0.4
4
0 1 0 2
*/
