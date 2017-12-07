This set of files is inspired by [this awesome slide deck](http://conradsanderson.id.au/misc/sanderson_templates_lecture_uqcomp7305.pdf) on how to use templating to reduce the runtime cost of matrix addition. I've cut some corners like error checking and memory safety to emphasize what actually matters about the template techniques.

Take 1:
This is a naive implementation of matrix addition without any templating. The memory cost of doing C = A + B is twice what is necessary because operator+() creates a tempory matrix. The asympototic runtime is twice what is necessary because operator=() copies the tempory matrix into C.

Take 2:
This handels the case of C = A + B optimally. A + B relies on the new operator+() to turn the two matrices into a Glue which just points to two matrices. The new operator=() adds A and B elementwise in place into C. The remaining problem is that it can't manage D = A + B + C, which would require recursively nesting Matrices and Glues. One point here I'm not totally clear on is slide 15: "the C++ compiler can legally remove temporary and purely const instances as long as the results are the same" and "by looking at the resulting machine code, it's as if the instance of the Glue class never existed !" I don't really follow. Looking at the dissassembly, it's full of mentions of "Glue". What is lacking from the executable that confirms this property?

Take 3:
This is simply a hard coded version that deals with D = A + B + C. I think it's super helpful for seeing exactly what needs to be duplicated if you refuse to write a general solution to the problem. Nothing technically interesting here, but helpful to fully grock the technique presented in Take 2.

Take 4:
Fully general solution for arbitrary number of matrices. Pretty elegant solution. Relies on static polymorphism using the Curiously Recurring Template Pattern. CRTP allows us to get a ref to either Matrices or Glues using the same notation get_ref(). I think this pattern is pretty common and worth understanding better. This allows an elegant operator+() which runs the Glue constructor using the get_ref()s on a Base<Matrix> or Base<Glue<...>> object. 

Note, this solution relies on the fact that operator+() is left associative in C++: A + B + C => (A + B) + C. This is not spelled out in the slides. For example, using the code in the slides you will only explore the left hand side of glue trees when counting the number of matrices. If you try to parenthesize your own expressions like A + (B + C), you will encounter contradictions like different numbers of matrices in:

Glue<Glue<Matrix, Matrix>, Matrix> and Glue <Matrix, Glue<Matrix, Matrix>>
