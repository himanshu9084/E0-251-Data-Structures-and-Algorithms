
1) Work flow : 

	Step 1 : 
		First output, *For CSC * CSR , press 1 otherwise 0..*
		For matrix multiplication, enter 1
		For rest of operations press 0
	
	Step 2 :
		On pressing 1
		For matrix multiplication, am generating two random matrices and multiplying them.
		First matrix dimensions, non zero density and -ve numbers density needs to be entered.
		Similarly, for 2nd matrix.
		
		After input details for matrices, am outputting the matrices using ; for row breaker, So 			that the same matrix can be copied and pasted into matlab/octave , for verification purpose.

		After multiplication am outputting the result into COO Row sorted format, and providing 		additional option if you want to print matrix as m x n structure. Press 1, to print in m x n 			format.
		
	Step 3 : 
		On pressing 0
		To genrate COO, CSR, CSC and CSC trnsform
		Matrix dimensions, non zero density and -ve numbers density needs to be entered.
		
		Again am outputting the matrix using ; for row breaker.
		After this, am directly converting the input matrix into CSR and CSC format, and outputting 			the CSR format and CSC format only.
	
	Step 4 :
		In this step, am giving options to print the input matrix in form of CSR, CSC or COO as 		matrix structure of m x n.
		Also, am givng option to perform Row operations. 
		*Print options <20x20 COO-1, CSR-2, CSC-3 
		CSC transform-4*
		Using options 1,2 and 3 matrix can be printed into structure of m x n by sendind respective 			CSR or Format's data to printmatrix().

	Step 5 :
		For Performing row transfomations on CSC format :
		*Enter r1, k1, r2, k2*
		A[r2] = k1*A[r1] + k2*A[r2]
		Input r1,k1,r2,k2 for performing row operation on CSC format.
		
		After input, am outputting the transformed row, and later printing the matrix in COO Column 			CSC sorted format, and also outputting the CSC Format.



2) Function description :

	*	Range of values : -10 to 10

	*	main()
		main() is taking input that whether you want to multiply matrices or perform rest of 			operations.

	*	struct node{..}
		Defining the structure for linked list storing position and position data, with next pointer.

	* 	void push(..)
		push() function is taking input as start pointer address, position, position data, and 			adding it to linked list.
	
	*	coogenerate()
		for generating random matrix in COO Format, and also converting into CSR and CSC, with the 	option to print matrix.

	*	input()
		generates COO matrix.

	*	cootocsr()
		generates CSR and prints it.

	*	cootocsc()
		generates CSC and prints it.

	*	sort()
		Using selection sort for sorting on the basis of first array input.

	*	generate2()
		generating 2 matrices for multiplication.

	*	multiply()
		Multiplies 2 matrices.

	*	csctrans()
		For performing row operations on CSC matrix.

	*	printmatrix()
		Prints matrix in m X n structure, having inputs as any one of CSR, CSC, COO.


		
	
		

