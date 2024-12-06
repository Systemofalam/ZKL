mkdir -p ZKL/src/frontend ZKL/src/ir ZKL/src/backend ZKL/src/utils ZKL/include ZKL/tests ZKL/examples
cd ZKL
touch src/main.c src/frontend/{lexer.c,lexer.h,parser.c,parser.h} \
      src/ir/{ir_generator.c,ir_generator.h,optimizer.c,optimizer.h} \
      src/backend/{constraint_compiler.c,constraint_compiler.h,proof_generator.c,proof_generator.h,verifier_generator.c,verifier_generator.h} \
      src/utils/{file_io.c,file_io.h,error_handling.c,error_handling.h} \
      include/zkl.h \
      tests/{test_lexer.c,test_parser.c} \
      examples/example1.zkl \
      Makefile README.md
